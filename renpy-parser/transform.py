import sys
import lex
import parse
from dataclasses import dataclass
from pprint import pprint
import generate

@dataclass
class State:
    images: list
    characters: list
    statements: list
    menus: list
    entries: dict

    images_lookup: dict[str, int] # identifier to image index
    characters_lookup: dict[str, int] # identifier to character index
    labels_lookup: dict[str, int] # identifier to statement index
    audio_lookup: dict[str, int]
    string_lookup: dict[str, int]

    global_identifiers: set[str]

@dataclass
class InternalMenu:
    menu: parse.Menu
    entry_lookup: dict[str, tuple[int, int]] # string to (entry index, statement index)
    entry_index: int

@dataclass
class InternalJump:
    target: tuple

def lhs_key(lhs):
    return tuple(l.lexeme for l in lhs)

simple_statement_types = {
    parse.Jump,
    parse.Play,
    parse.Return,
    parse.Say,
    parse.Scene,
    parse.Show,
    parse.Voice,
    parse.With,
    parse.Stop,
    parse.Pause,
    parse.Hide,
}

def pass1(state, ast):
    if type(ast) is parse.Image:
        key = lhs_key(ast.name)
        assert key not in state.global_identifiers
        state.global_identifiers.add(key)
        state.images_lookup[key] = len(state.images)
        state.images.append(ast)
    elif type(ast) is parse.Define:
        key = lhs_key(ast.name)
        assert key not in state.global_identifiers
        state.global_identifiers.add(key)
        if type(ast.value) is parse.FunctionCall and ast.value.name.lexeme == b'Character':
            state.characters_lookup[key] = len(state.characters)
            state.characters.append(ast)
        else:
            print(f"ignoring define {ast}", file=sys.stderr)
    elif type(ast) is parse.Label:
        key = lhs_key(ast.name)
        assert key not in state.labels_lookup
        state.labels_lookup[key] = len(state.statements)
    elif type(ast) in {parse.Play, parse.Voice}:
        if ast.path.lexeme not in state.audio_lookup:
            index = len(state.audio_lookup)
            state.audio_lookup[ast.path.lexeme] = index
    elif type(ast) is parse.Say:
        if ast.text.lexeme not in state.string_lookup:
            index = len(state.string_lookup)
            state.string_lookup[ast.text.lexeme] = index
    elif type(ast) is parse.Menu:
        menu_index = len(state.menus)
        menu_end_key = (b"__menu_end", menu_index)
        entry_lookup = {}
        entry_index = len(state.entries)
        internal_menu = InternalMenu(
            menu = ast,
            entry_lookup = entry_lookup,
            entry_index = entry_index
        )
        state.menus.append(internal_menu)
        state.statements.append(internal_menu)
        for i, (name, ast_list) in enumerate(ast.entries):
            assert name.lexeme not in entry_lookup
            entry_lookup[name.lexeme] = entry_index + i

        for name, ast_list in ast.entries:
            entry_index = entry_lookup[name.lexeme]
            statement_index = len(state.statements)
            assert entry_index not in state.entries
            state.entries[entry_index] = (name.lexeme, statement_index)
            for t in ast_list:
                pass1(state, t)
            state.statements.append(InternalJump(menu_end_key))
        assert menu_end_key not in state.labels_lookup
        state.labels_lookup[menu_end_key] = len(state.statements)
    elif type(ast) in simple_statement_types:
        pass
    else:
        assert False, (type(ast), ast)

    if type(ast) in simple_statement_types:
        state.statements.append(ast)

transforms_set = {
    b"left",
    b"centerleft",
    b"center",
    b"centerright",
    b"right",
}

def pass2_statement(state, pc, statement):
    if type(statement) is parse.Play:
        comment = statement.path.lexeme.decode('utf-8')
        audio_index = state.audio_lookup[statement.path.lexeme]
        yield f"{{ .type = type::play, .play = {{ .audioIndex = {audio_index}, /* FIXME channel */ }} }}, // {pc} {comment}"
    elif type(statement) is parse.Scene:
        key = lhs_key(statement.name)
        image_index = state.images_lookup[key]
        comment = ".".join(k.decode('utf-8') for k in key)
        yield f"{{ .type = type::scene, .scene = {{ .imageIndex = {image_index} }} }}, // {pc} {comment}"
    elif type(statement) is parse.With:
        print(f"not implemented: {statement}", file=sys.stderr)
        pass
    elif type(statement) is parse.Voice:
        comment = statement.path.lexeme.decode('utf-8')
        audio_index = state.audio_lookup[statement.path.lexeme]
        yield f"{{ .type = type::voice, .voice = {{ .audioIndex = {audio_index} }} }}, // {pc} {comment}"
    elif type(statement) is parse.Say:
        key = lhs_key(statement.speaker)
        character_index = state.characters_lookup[key]
        string_index = state.string_lookup[statement.text.lexeme]
        comment = ".".join(k.decode('utf-8') for k in key) + f" \"{statement.text.lexeme.decode('utf-8')}\""
        yield f"{{ .type = type::say, .say = {{ .characterIndex = {character_index}, .stringIndex = {string_index} }} }}, // {pc} {comment}"
    elif type(statement) is parse.Show:
        key = lhs_key(statement.what)
        image_index = state.images_lookup[key]
        transform = statement.transform.lexeme
        assert transform in transforms_set
        transform = transform.decode('utf-8')
        comment = ".".join(k.decode('utf-8') for k in key)
        yield f"{{ .type = type::show, .show = {{ .imageIndex = {image_index}, .transformIndex = transform::{transform} }} }}, // {pc} {comment}"
    elif type(statement) is InternalMenu:
        count = len(statement.menu.entries)
        option_index = statement.entry_index
        comment = ", ".join(f"\"{k.lexeme.decode('utf-8')}\"" for k, v in statement.menu.entries)
        yield f"{{ .type = type::menu, .menu = {{ .count = {count}, .optionIndex = {option_index} }} }}, // {pc} {comment}"
    elif type(statement) is InternalJump:
        key = statement.target
        statement_index = state.labels_lookup[key]
        comment = str(key)
        yield f"{{ .type = type::jump, .jump = {{ .statementIndex = {statement_index} }} }}, // {pc} internal jump {comment}"
    elif type(statement) is parse.Jump:
        key = lhs_key(statement.target)
        statement_index = state.labels_lookup[key]
        comment = ".".join(k.decode('utf-8') for k in key)
        yield f"{{ .type = type::jump, .jump = {{ .statementIndex = {statement_index} }} }}, // {pc} {comment}"
    elif type(statement) is parse.Return:
        yield f"{{ .type = type::_return }}, // {pc}"
    elif type(statement) is parse.Stop:
        yield f"{{ .type = type::stop, .stop = {{ /* FIXME channel */ }} }}, // {pc}"
    elif type(statement) is parse.Pause:
        duration = statement.duration.lexeme
        yield f"{{ .type = type::pause, .pause = {{ .duration = {duration} }} }}, // {pc}"
    elif type(statement) is parse.Hide:
        key = lhs_key(statement.what)
        image_index = state.images_lookup[key]
        comment = ".".join(k.decode('utf-8') for k in key)
        yield f"{{ .type = type::hide, .hide = {{ .imageIndex = {image_index} }} }}, // {pc} {comment}"
    else:
        pass
        assert False, (type(statement), statement)

def pass2_statements(state):
    yield "const statement statements[] = {"
    for pc, statement in enumerate(state.statements):
        yield from pass2_statement(state, pc, statement)
    yield "};"
    yield "constexpr int statements_length = (sizeof (statements)) / (sizeof (statements[0]));"

def pass2_strings(state):
    yield "char const * const strings[] = {"
    for string, i in sorted(state.string_lookup.items(), key=lambda kv: kv[1]):
        yield f"\"{string.decode('utf-8')}\", // {i}"
    yield "};"
    yield "constexpr int strings_length = (sizeof (strings)) / (sizeof (strings[0]));"

def pass2_characters(state):
    yield "const character characters[] = {"
    for i, character in enumerate(state.characters):
        character_name, = character.value.args
        yield f"{{ .characterName = \"{character_name.lexeme.decode('utf-8')}\" }}, // {i}"
    yield "};"
    yield "constexpr int characters_length = (sizeof (characters)) / (sizeof (characters[0]));"

def pass2_audio(state):
    yield "const audio audio[] = {"
    for audio, i in sorted(state.audio_lookup.items(), key=lambda kv: kv[1]):
        orig_path = audio.decode('utf-8')
        path = orig_path
        if path.endswith(".mp3"):
            path = path.removesuffix(".mp3")
        elif path.endswith(".ogg"):
            path = path.removesuffix(".ogg")
        else:
            assert False, path
        yield f"{{ .path = \"{path}.opus\" }}, // {i} {orig_path}"
    yield "};"
    yield "constexpr int audio_length = (sizeof (audio)) / (sizeof (audio[0]));"

def pass2_images(state):
    yield "const image images[] = {"
    for i, image in enumerate(state.images):
        orig_path = image.path.lexeme.decode('utf-8')
        path = orig_path
        if path.endswith(".png"):
            path = path.removesuffix(".png")
        else:
            assert False, path
        yield f"{{ .path = \"data/renpy/images/{path}.dds\" }}, // {i} {orig_path}"
    yield "};"
    yield "constexpr int images_length = (sizeof (images)) / (sizeof (images[0]));"

def pass2_options(state):
    yield "const option options[] = {"
    for i, (lexeme, statement_index) in sorted(state.entries.items(), key=lambda kv: kv[0]):
        yield f"{{ .string = \"{lexeme.decode('utf-8')}\", .statementIndex = {statement_index} }}, // {i}"
    yield "};"
    yield "constexpr int options_length = (sizeof (options)) / (sizeof (options[0]));"

def pass2(state):
    yield "#include \"renpy/language.h\""
    yield ""
    yield "namespace renpy::script {"
    yield "using namespace renpy::language;"
    yield from pass2_strings(state)
    yield from pass2_characters(state)
    yield from pass2_audio(state)
    yield from pass2_images(state)
    yield from pass2_options(state)
    yield from pass2_statements(state)
    yield "}"

def main():
    with open(sys.argv[1], 'rb') as f:
        mem = memoryview(f.read())

    tokens = list(lex.tokenize(mem))
    state = State(
        images = list(),
        characters = list(),
        statements = list(),
        menus = list(),
        entries = dict(),
        images_lookup = dict(),
        characters_lookup = dict(),
        labels_lookup = dict(),
        audio_lookup = dict(),
        string_lookup = dict(),
        global_identifiers = set(),
    )
    try:
        ast_list = []
        for ast in parse.parse_all(tokens):
            ast_list.append(ast)
    except parse.ParseException as e:
        print(e, e.token, file=sys.stderr)
        raise

    for t in ast_list:
        pass1(state, t)

    render, out = generate.renderer()
    render(pass2(state))
    sys.stdout.write(out.getvalue())

if __name__ == "__main__":
    main()

import sys
from pprint import pprint
import lex
from lex import TT
from dataclasses import dataclass

class ParseException(Exception):
    def __init__(self, message, token):
        super().__init__(message)
        self.token = token

def get_lexeme(v):
    if type(v) is list:
        return list(get_lexeme(i) for i in v)
    elif type(v) is tuple:
        return tuple(get_lexeme(i) for i in v)
    elif type(v) is lex.Token:
        return v.lexeme
    else:
        return v

def lexeme_repr(self):
    kws = [f"{key}={get_lexeme(value)!r}" for key, value in self.__dict__.items()]
    return "{}({})".format(type(self).__name__, ", ".join(kws))

@dataclass
class FunctionCall:
    name: lex.Token
    args: list[lex.Token]
    kwargs: list[tuple[lex.Token, lex.Token]]

    __repr__ = lexeme_repr

@dataclass
class Image:
    name: list[lex.Token]
    path: lex.Token

    __repr__ = lexeme_repr

@dataclass
class Define:
    name: list[lex.Token]
    value: 'Expression'

    __repr__ = lexeme_repr

@dataclass
class Label:
    name: lex.Token

    __repr__ = lexeme_repr

@dataclass
class Play:
    channel: lex.Token
    path: lex.Token
    fadeout: lex.Token

    __repr__ = lexeme_repr

@dataclass
class Stop:
    channel: lex.Token
    fadeout: lex.Token

    __repr__ = lexeme_repr

@dataclass
class Scene:
    name: lex.Token

    __repr__ = lexeme_repr

@dataclass
class With:
    function_call: FunctionCall

    __repr__ = lexeme_repr

@dataclass
class Say:
    speaker: lex.Token
    text: lex.Token

    __repr__ = lexeme_repr

@dataclass
class Voice:
    path: lex.Token

    __repr__ = lexeme_repr

@dataclass
class Show:
    what: lex.Token
    transform: lex.Token
    properties: list[tuple[lex.Token, lex.Token]]

    __repr__ = lexeme_repr

@dataclass
class Menu:
    entries: tuple[lex.Token, list['Statement']]
    __repr__ = lexeme_repr

@dataclass
class Jump:
    target: lex.Token

    __repr__ = lexeme_repr

@dataclass
class Pause:
    duration: lex.Token

    __repr__ = lexeme_repr

@dataclass
class Hide:
    what: lex.Token

    __repr__ = lexeme_repr

@dataclass
class Return:
    pass

def parse_lhs(tokens, index):
    identifier = tokens[index]
    if identifier.type != TT.IDENTIFIER:
        raise ParseException("expected identifier", identifier)
    lhs = [identifier]
    index += 1
    while tokens[index].type == TT.DOT:
        identifier = tokens[index + 1]
        if identifier.type != TT.IDENTIFIER:
            raise ParseException("expected identifier", identifier)
        lhs.append(identifier)
        index += 2
    return index, lhs

def parse_image(tokens, index):
    index, lhs = parse_lhs(tokens, index)
    equal = tokens[index + 0]
    if equal.type != TT.EQUAL:
        raise ParseException("expected equal", equal)
    string = tokens[index + 1]
    if string.type != TT.STRING:
        raise ParseException("expected string", string)

    image = Image(
        name = lhs,
        path = string,
    )
    return index + 2, image

def parse_function_call(tokens, index):
    name = tokens[index + 0]
    if name.type != TT.IDENTIFIER:
        raise ParseException("expected identifier", name)
    lparen = tokens[index + 1]
    if lparen.type != TT.LPAREN:
        raise ParseException("expected lparen", lparen)
    index += 2

    # args
    args = []
    while tokens[index].type != TT.RPAREN:
        token = tokens[index]
        if token.type == TT.STRING:
            args.append(token)
        elif token.type == TT.NUMBER:
            args.append(token)
        elif token.type == TT.NEWLINE:
            pass
        else:
            break
        index += 1
        if tokens[index].type != TT.COMMA:
            break
        index += 1

    # kwargs
    kwargs = []
    while tokens[index].type != TT.RPAREN:
        identifier = tokens[index + 0]
        if identifier.type != TT.IDENTIFIER:
            raise ParseException("expected function call kwargs identifier", identifier)
        equal = tokens[index + 1]
        if equal.type != TT.EQUAL:
            raise ParseException("expected function call kwargs equal", equal)
        string = tokens[index + 2]
        if string.type != TT.STRING:
            raise ParseException("expected function call kwargs string", string)
        kwargs.append((identifier, string))
        index += 3
        if tokens[index].type != TT.COMMA:
            break

    rparen = tokens[index]
    if rparen.type != TT.RPAREN:
        raise ParseException("expected rparen", rparen)
    index += 1

    function_call = FunctionCall(
        name = name,
        args = args,
        kwargs = kwargs
    )
    return index, function_call

def parse_rhs(tokens, index):
    token = tokens[index]
    peek = tokens[index+1]
    if token.type == TT.NUMBER:
        return index + 1, token
    elif token.type == TT.IDENTIFIER and peek.type == TT.LPAREN:
        return parse_function_call(tokens, index)
    else:
        raise ParseException("expected rhs expression", token)

def parse_define(tokens, index):
    index, lhs = parse_lhs(tokens, index)
    equal = tokens[index + 0]
    if equal.type != TT.EQUAL:
        raise ParseException("expected equal", equal)
    index, rhs = parse_rhs(tokens, index + 1)
    define = Define(
        name = lhs,
        value = rhs
    )
    return index, define

def parse_label(tokens, index):
    index, lhs = parse_lhs(tokens, index)

    colon = tokens[index]
    if colon.type != TT.COLON:
        raise ParseException("expected colon", colon)

    label = Label(
        name = lhs
    )

    return index + 2, label

def parse_play(tokens, index):
    channel = tokens[index + 0]
    if channel.type != TT.IDENTIFIER:
        raise ParseException("expected identifier", channel)

    path = tokens[index + 1]
    if path.type != TT.STRING:
        raise ParseException("expected string", path)

    index += 2
    token = tokens[index]
    fadeout = None
    if token.type == TT.FADEOUT:
        fadeout = tokens[index + 1]
        if fadeout.type != TT.NUMBER:
            raise ParseException("expected number", fadeout)
        index += 2
    #noloop = False
    if token.type == TT.NOLOOP:
        #noloop = True
        index += 1

    play = Play(
        channel = channel,
        path = path,
        fadeout = fadeout,
    )
    return index, play

def parse_scene(tokens, index):
    index, name = parse_lhs(tokens, index)
    scene = Scene(
        name = name,
    )
    return index, scene

def parse_with(tokens, index):
    index, function_call = parse_function_call(tokens, index)

    _with = With(
        function_call = function_call
    )

    return index, _with

def parse_say(tokens, index):
    index, speaker = parse_lhs(tokens, index)
    text = tokens[index]
    if text.type != TT.STRING:
        raise ParseException("expected string", text)

    say = Say(
        speaker = speaker,
        text = text
    )

    return index + 2, say

def parse_voice(tokens, index):
    path = tokens[index]
    if path.type != TT.STRING:
        raise ParseException("expected string", path)

    voice = Voice(
        path = path,
    )
    return index + 1, voice

def parse_show(tokens, index):
    show = tokens[index + 0]
    if show.type != TT.SHOW:
        raise ParseException("expected show", show)

    index += 1

    index, what = parse_lhs(tokens, index)

    at = tokens[index + 0]
    if at.type != TT.AT:
        raise ParseException("expected at", at)

    transform = tokens[index + 1]
    if transform.type != TT.IDENTIFIER:
        raise ParseException("expected identifier", transform)

    index += 2

    properties = []
    if tokens[index + 0].type == TT.COLON:
        index += 1
        while index < len(tokens):
            token = tokens[index + 0]
            if token.type == TT.NEWLINE:
                index += 1
                continue

            if token.position.column <= show.position.column:
                break

            if token.type != TT.IDENTIFIER:
                raise ParseException("expected identifier")

            number = tokens[index + 1]
            if number.type != TT.NUMBER:
                raise ParseException("expected number")

            properties.append((token, number))
            index += 2

    show = Show(
        what = what,
        transform = transform,
        properties = properties
    )
    return index, show

def parse_menu(tokens, index):
    menu = tokens[index + 0]
    if menu.type != TT.MENU:
        raise ParseException("expected menu", menu)

    colon = tokens[index + 1]
    if colon.type != TT.COLON:
        raise ParseException("expected colon", colon)

    index = index + 2
    menu_entries = []
    menu_entry_string = None
    menu_entry_statements = None
    while index < len(tokens):
        token = tokens[index+0]
        if token.type == TT.NEWLINE:
            index += 1
            continue
        peek = tokens[index+1]

        if token.position.column <= menu.position.column:
            break

        if token.type == TT.STRING:
            if peek.type != TT.COLON:
                raise ParseException("expected colon", peek)
            if menu_entry_string is not None:
                menu_entries.append((menu_entry_string, menu_entry_statements))
            menu_entry_string = token
            menu_entry_statements = []
            index += 2
        else:
            if menu_entry_statements is None:
                raise ParseException("expected menu option", token)

            index, ast = parse_one(tokens, index)
            if ast is not None:
                menu_entry_statements.append(ast)

    if menu_entry_string is not None:
        menu_entries.append((menu_entry_string, menu_entry_statements))

    menu = Menu(
        entries = menu_entries,
    )

    return index, menu

def parse_jump(tokens, index):
    index, target = parse_lhs(tokens, index)

    jump = Jump(
        target = target,
    )
    return index + 1, jump

def parse_init(tokens, index):
    init = tokens[index + 0]
    if init.type != TT.INIT:
        raise ParseException("expected init", init)

    colon = tokens[index + 1]
    if colon.type != TT.COLON:
        raise ParseException("expected colon", colon)

    index += 2

    # skip all tokens inside block
    while index < len(tokens):
        token = tokens[index]
        if token.type == TT.NEWLINE:
            index += 1
            continue

        if token.position.column < init.position.column:
            raise ParseException("invalid init block dedent", token)
        if token.position.column == init.position.column:
            break
        index += 1

    return index, None

def parse_transform(tokens, index):
    transform = tokens[index + 0]
    if transform.type != TT.TRANSFORM:
        raise ParseException("expected transform", init)

    identifier = tokens[index + 1]
    if identifier.type != TT.IDENTIFIER:
        raise ParseException("expected identifier", identifier)

    colon = tokens[index + 2]
    if colon.type != TT.COLON:
        raise ParseException("expected colon", colon)

    index += 3

    # skip all tokens inside block
    while index < len(tokens):
        token = tokens[index]
        if token.type == TT.NEWLINE:
            index += 1
            continue

        if token.position.column < transform.position.column:
            raise ParseException("invalid init block dedent", token)
        if token.position.column == transform.position.column:
            break
        index += 1

    return index, None

def parse_stop(tokens, index):
    channel = tokens[index + 0]
    if channel.type != TT.IDENTIFIER:
        raise ParseException("expected identifier", channel)

    fadeout = tokens[index + 1]
    if fadeout.type != TT.FADEOUT:
        raise ParseException("expected fadeout", channel)

    number = tokens[index + 2]
    if number.type != TT.NUMBER:
        raise ParseException("expected number", number)

    index += 3

    stop = Stop(
        channel = channel,
        fadeout = number
    )
    return index, stop

def parse_pause(tokens, index):
    duration = tokens[index + 0]
    if duration.type != TT.NUMBER:
        raise ParseException("expected number", duration)

    pause = Pause(
        duration = duration
    )
    return index + 1, pause

def parse_hide(tokens, index):
    index, what = parse_lhs(tokens, index)

    hide = Hide(
        what = what
    )
    return index + 1, hide

def parse_one(tokens, index):
    token = tokens[index]
    if token.type == TT.NEWLINE:
        index = index + 1
        if index < len(tokens):
            return parse_one(tokens, index)
        else:
            return index, None
    elif token.type == TT.IMAGE:
        index, ast = parse_image(tokens, index + 1)
        return index, ast
    elif token.type == TT.DEFINE:
        index, ast = parse_define(tokens, index + 1)
        return index, ast
    elif token.type == TT.LABEL:
        index, ast = parse_label(tokens, index + 1)
        return index, ast
    elif token.type == TT.PLAY:
        index, ast = parse_play(tokens, index + 1)
        return index, ast
    elif token.type == TT.SCENE:
        index, ast = parse_scene(tokens, index + 1)
        return index, ast
    elif token.type == TT.WITH:
        index, ast = parse_with(tokens, index + 1)
        return index, ast
    elif token.type == TT.IDENTIFIER:
        index, ast = parse_say(tokens, index)
        return index, ast
    elif token.type == TT.VOICE:
        index, ast = parse_voice(tokens, index + 1)
        return index, ast
    elif token.type == TT.SHOW:
        index, ast = parse_show(tokens, index)
        return index, ast
    elif token.type == TT.MENU:
        index, ast = parse_menu(tokens, index)
        return index, ast
    elif token.type == TT.JUMP:
        index, ast = parse_jump(tokens, index + 1)
        return index, ast
    elif token.type == TT.RETURN:
        return index + 1, Return()
    elif token.type == TT.INIT:
        index, ast = parse_init(tokens, index)
        return index, ast
    elif token.type == TT.TRANSFORM:
        index, ast = parse_transform(tokens, index)
        return index, ast
    elif token.type == TT.STOP:
        index, ast = parse_stop(tokens, index + 1)
        return index, ast
    elif token.type == TT.PAUSE:
        index, ast = parse_pause(tokens, index + 1)
        return index, ast
    elif token.type == TT.HIDE:
        index, ast = parse_hide(tokens, index + 1)
        return index, ast
    else:
        raise ParseException("unexpected token", token)

def parse_all(tokens):
    index = 0
    while index < len(tokens):
        index, ast = parse_one(tokens, index)
        if ast is not None:
            yield ast

def main():
    with open(sys.argv[1], 'rb') as f:
        mem = memoryview(f.read())

    tokens = list(lex.tokenize(mem))
    try:
        ast = parse_all(tokens)
        for t in ast:
            pprint(t)
    except ParseException as e:
        print(e, e.token)
        raise

if __name__ == "__main__":
    main()

import string
from dataclasses import dataclass
from enum import Enum, auto
import sys

whitespace = set([ord(' '), ord('\r')])
string_digits = set(ord(i) for i in string.digits)
identifier_start = set(map(ord, string.ascii_letters + "_"))
identifier = identifier_start | string_digits

@dataclass
class Position:
    offset: int
    line: int
    column: int

    def from_position(p):
        return Position(p.offset, p.line, p.column)

class TT(Enum):
    KEYWORD = auto()
    NEWLINE = auto()
    COLON = auto()
    STRING = auto()
    DOT = auto()
    EQUAL = auto()
    COMMA = auto()
    LPAREN = auto()
    RPAREN = auto()
    NUMBER = auto()
    IDENTIFIER = auto()
    WITH = auto()

    # keywords
    PLAY = auto()
    VOICE = auto()
    SCENE = auto()
    SHOW = auto()
    AT = auto()
    DEFINE = auto()
    IMAGE = auto()
    LABEL = auto()
    MENU = auto()
    JUMP = auto()
    RETURN = auto()
    INIT = auto()
    FADEOUT = auto()

keywords = {
    b"play": TT.PLAY,
    b"voice": TT.VOICE,
    b"scene": TT.SCENE,
    b"show": TT.SHOW,
    b"at": TT.AT,
    b"define": TT.DEFINE,
    b"image": TT.IMAGE,
    b"label": TT.LABEL,
    b"with": TT.WITH,
    b"menu": TT.MENU,
    b"jump": TT.JUMP,
    b"return": TT.RETURN,
    b"init": TT.INIT,
    b"fadeout": TT.FADEOUT,
}

@dataclass
class Token:
    position: Position
    lexeme: bytes
    type: TT

def parse_string(mem, position):
    offset = position.offset
    assert mem[offset] == ord('"'), (position, chr(mem[offset]))
    offset += 1
    start = offset
    while mem[offset] != ord('"'):
        assert mem[offset] != ord("\n")
        offset += 1
    assert mem[offset] == ord('"'), position
    s = bytes(mem[start:offset])
    token = Token(
        position = position,
        lexeme = s,
        type = TT.STRING
    )
    next_position = Position(
        offset = offset + 1,
        line = position.line,
        column = position.column + 2 + len(s)
    )
    return next_position, token

def parse_number(mem, position):
    offset = position.offset
    whole = []
    fraction = []
    sign = 1
    if mem[offset] == ord('-'):
        sign = -1
        offset += 1
    # whole
    while True:
        c = mem[offset]
        if c in string_digits:
            whole.append(c)
            offset += 1
        elif c == ord('.'):
            assert whole != [], chr(c)
            offset += 1
            break
        else:
            assert whole != [], chr(c)
            number = sign * int(bytes(whole))
            next_position = Position(
                offset = offset,
                line = position.line,
                column = position.column + 1 + (offset - position.offset)
            )
            return next_position, Token(position, number, TT.NUMBER)
    # fraction
    while True:
        c = mem[offset]
        if c in string_digits:
            fraction.append(c)
            offset += 1
        else:
            assert fraction != [], chr(c)
            w = int(bytes(whole))
            f = int(bytes(fraction)) / (10 ** len(fraction))
            number = sign * (w + f)
            next_position = Position(
                offset = offset,
                line = position.line,
                column = position.column + 1 + (offset - position.offset)
            )
            return next_position, Token(position, number, TT.NUMBER)

def disambiguate_keyword(lexeme):
    if lexeme in keywords:
        return keywords[lexeme]
    else:
        return TT.IDENTIFIER

def parse_identifier(mem, position):
    offset = position.offset
    l = []
    while True:
        c = mem[offset]
        if c in identifier:
            l.append(c)
            offset += 1
        else:
            assert l != []
            lexeme = bytes(l)
            next_position = Position(
                offset = offset,
                line = position.line,
                column = position.column + 1 + len(lexeme)
            )
            token_type = disambiguate_keyword(lexeme)
            return next_position, Token(position, lexeme, token_type)

def next_token(mem, position):
    position = Position.from_position(position)
    while True:
        if position.offset >= len(mem):
            return position, None
        c = mem[position.offset]

        if c in whitespace:
            position.offset += 1
            position.column += 1
        else:
            break

    next_position = Position.from_position(position)
    next_position.offset += 1
    next_position.column += 1

    if c >= 128:
        print(f"invalid garbage byte {hex(c)} at {position}", file=sys.stderr)
        next_position.column = position.column
        return next_token(mem, next_position)
    if c == ord('\n'):
        next_position.line += 1
        next_position.column = 0
        return next_position, Token(position, b'\n', TT.NEWLINE)
    if c == ord(':'):
        return next_position, Token(position, b':', TT.COLON)
    if c == ord('.'):
        return next_position, Token(position, b':', TT.DOT)
    if c == ord('='):
        return next_position, Token(position, b'=', TT.EQUAL)
    if c == ord(','):
        return next_position, Token(position, b',', TT.COMMA)
    if c == ord('('):
        return next_position, Token(position, b'(', TT.LPAREN)
    if c == ord(')'):
        return next_position, Token(position, b')', TT.RPAREN)
    if c == ord('"'):
        return parse_string(mem, position)
    if c == ord('#'):
        offset = position.offset + 1
        while mem[offset] != ord('\n'):
            offset += 1
        return next_token(mem, Position(offset + 1, position.line + 1, 0))
    if c in string_digits or c == ord('-'):
        return parse_number(mem, position)
    if c in identifier_start:
        return parse_identifier(mem, position)
    assert not "unexpected character", (position, chr(c), hex(c))

def tokenize(mem):
    position = Position(offset = 0, line = 1, column = 0)
    while True:
        position, token = next_token(mem, position)
        if token is None:
            return
        else:
            yield token

def main():
    with open(sys.argv[1], 'rb') as f:
        mem = memoryview(f.read())

    for token in tokenize(mem):
        print(token.lexeme, token.type)

if __name__ == "__main__":
    main()

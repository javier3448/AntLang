#ifndef TOKEN_H
#define TOKEN_H

#include "../pch.h"
#include "../mystring.h"

extern const char* keywords[11];

constexpr u16 KEYWORDS_LENGTH = sizeof keywords / sizeof keywords[0];

enum TokenKind : char{
    // Keywords:
    // The underlying value represents an offset to the array: 'keywords' where
    // the string representation of said keyword is stored
    Key_u64 = 0,
    Key_s64 = 1,
    Key_u32 = 2,
    Key_s32 = 3,
    Key_u16 = 4,
    Key_s16 = 5,
    Key_u8 = 6,
    Key_s8 = 7,
    Key_float32 = 8,
    Key_float64 = 9,
    Key_cast = 10,

    Identifier = 11,
    Number = 12,
    Error = 13,
    Eof = 14,

    LessEqual = 15,
    GreaterEqual = 16,
    EqualEqual = 17,
    NotEqual = 18,
    And = 19,
    Or = 20,

    // @Improvement, this is kinda stupid honestly, we dont really win that much
    // and tokens and their string representation becomes becomes weird
    // Tokens that can be represented using just one char
    Plus = '+',
    Minus = '-',
    Division = '/',
    Multiplication = '*',

    Less = '<',
    Greater = '>',
    Equal = '=',
    Not = '!',
    BitAnd = '&',
    BitOr = '|',

    LeftParen = '(',
    RightParen = ')',
};


//@C++: should be inline but I dont know how to inline accross different
//compilation units or whatever
//[!]: warning: this is used in assertions as well
bool isBiOperatorKind(TokenKind kind);

//@Improvement?: this is basically a tagged union, people say that that is a
//std::variant in c++, should we use that here???
struct Token{
    TokenKind kind;

    // We will store the numeric tokens in a simple string because we need type
    // info to convert to their actual value for example:
    // "1.2" float32 is: 0x3ff3333333333333
    // "1.2" float64 is: 0x3f99999a 
    // So the "1.2" in:
    // `float32 a = 1.2;`
    // and
    // `float64 b = 1.2;`
    // mean two very different things
    MyString string;

    //doesnt do anything, is useful becuase the TokenCache needs to
    //initialize its tokenBuffer because this is c++ (I think)
    //so we need a default constructor
    Token();

    //A bunch of constructors because c++ doesnt let us initialize things like in
    //C99, oh well :/
    Token(TokenKind kind);

    Token(TokenKind kind, MyString string);

    //not a destructor because we dont want to deal with 'copy constructor
    //operator' doing expensive copies when we want to fucking return by value
    //@TODO: see if that is a valid concern!!
    void destroy();
};


#endif // TOKEN_H

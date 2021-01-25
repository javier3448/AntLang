#ifndef TOKEN_H
#define TOKEN_H

#include "../pch.h"
#include "../mystring.h"

// @Improvement: this is the best solution I was able to figure out to easily add more
// keywords and operators without relying on asserts to catch bugs :/
constexpr s16 NATIVE_TYPES_BEG = 0;
constexpr s16 NATIVE_TYPES_LEN = 10;
constexpr s16 KEYWORDS_BEG = NATIVE_TYPES_BEG + NATIVE_TYPES_LEN;
constexpr s16 KEYWORDS_LEN = 1;
constexpr s16 BI_OPERATORS_BEG = KEYWORDS_BEG + KEYWORDS_LEN;
constexpr s16 BI_OPERATORS_LEN = 15;
constexpr s16 UNI_OPERATORS_BEG = BI_OPERATORS_BEG + BI_OPERATORS_LEN;
constexpr s16 UNI_OPERATORS_LEN = 1;
//@BAD: bad name just because I wanted to include 'Eof' in this category
constexpr s16 OTHER_BEG = UNI_OPERATORS_BEG + UNI_OPERATORS_LEN;
constexpr s16 OTHER_LEN = 3;

constexpr s16 TOKEN_STRING_LITERALS_LEN = NATIVE_TYPES_LEN + KEYWORDS_LEN + BI_OPERATORS_LEN + UNI_OPERATORS_LEN + OTHER_LEN;

// All the tokens that a string representation that does not depend on the value
// they carry will have their string literal representation stored in here
// to get it:
// tokenStringLiterals[(s16)aToken.kind]; 
extern const char* tokenStringLiterals[TOKEN_STRING_LITERALS_LEN];

enum TokenKind : s16{
// TOKENS FOR WHICH ITS UNDERLYING VALUE REPRESENTS AN OFFSET TO THE ARRAY: 'tokenStringLiterals' 

  // Keywords
    // native types
    Key_u64,
    Key_s64,
    Key_u32,
    Key_s32,
    Key_u16,
    Key_s16,
    Key_u8,
    Key_s8,
    Key_float32,
    Key_float64,
    // other keywords
    Key_cast,

  // binary Operators
    LessEqual,
    GreaterEqual,
    EqualEqual,
    NotEqual,
    And,
    Or,
    Plus,
    Minus,
    Division,
    // @TODO: add modulus operator
    Multiplication,
    Less,    // can be used as punctuation/grouping
    Greater, // can be used as punctuation/grouping
    // @BUG @TODO: equal is *not* a binary operator
    Equal,
    BitOr,
    BitAnd,
  // unary operators
    Not = 26,

  // punctuation/grouping
    LeftParen,
    RightParen,
    Eof,

// TOKENS THAT *DONT* HAVE THEIR STRING REPRESENTATIONS IN 'tokenStringLiterals'
    Identifier,
    Number,
    Error,
};


//@C++: should be inline but I dont know how to inline accross different
//compilation units or whatever
//[!]: warning: this is used in assertions as well
bool isBiOperatorKind(TokenKind kind);
bool isNativeType(TokenKind kind);

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

    // @Discusion:
    // 3 things can happen in 'stringRepresentation':
    // *we can return the .string
    // *we return a const char* with the string literal with the string representation of the token (for example an operator token like: '<=')
    // *we need to malloc: if we ever make a token that carries a value that is not a string AND it cant be represented with a string literal
    //  for example if we were to save number tokens in a s64 instead of saving the string representation of the number
    // IF WE EVER NEED A TOKEN THAT NEEDS THE THIRD OPTION WE HAVE TO RETHINK THIS WHOLE FUCKING THING

    // @TODO: test this function
    // Returns the string representation of the token.
    // *For now* it doesnt return anything that the caller should free in any way
    // @TODO: Better name, it gets confused with .string
    const char* stringRepresentation();

    //not a destructor because we dont want to deal with 'copy constructor
    //operator' doing expensive copies when we want to fucking return by value
    //@TODO: see if that is a valid concern!!
    void destroy();
};


#endif // TOKEN_H

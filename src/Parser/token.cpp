#include "./token.h"

const char* tokenStringLiterals [TOKEN_STRING_LITERALS_LEN] = 
{
  // native types
    "u64",
    "s64",
    "u32",
    "s32",
    "u16",
    "s16",
    "u8",
    "s8",
    "float32",
    "float64",

    // Other keywords
    "cast",

  // @TODO: write the real string representations
  // binary Operators
    "LessEqual",
    "GreaterEqual",
    "EqualEqual",
    "NotEqual",
    "And",
    "Or",
    "Plus",
    "Minus",
    "Division",
    "Multiplication",
    "Less",    // can be used as a punctuation/grouping
    "Greater", // can be used as a punctuation/grouping
    "Equal",
    "BitOr",
    "BitAnd",

  // unary operators
    "Not",

  // other
    "LeftParen",
    "RightParen",
    "Eof",
};

// Should be inlined but I dont know how to do that across different source files
bool isBiOperatorKind(TokenKind kind)
{
   // @BAD: find a better, to add more tokens, it is way too much work right now
    return (s16)kind >= BI_OPERATORS_BEG &&
           (s16)kind < (BI_OPERATORS_BEG + BI_OPERATORS_LEN);
}

// Should be inlined but I dont know how to do that across different source files
bool isNativeType(TokenKind kind)
{
   // @BAD: find a better, to add more tokens, it is way too much work right now
    return (s16)kind >= NATIVE_TYPES_BEG &&
           (s16)kind < (BI_OPERATORS_BEG + NATIVE_TYPES_LEN);
}

Token::Token()
{

}

Token::Token(TokenKind kind)
{
    assert(kind > 0 && kind < TOKEN_STRING_LITERALS_LEN);
    this->kind = kind;
}


Token::Token(TokenKind kind, MyString string)
{
   assert((kind == TokenKind::Identifier ||
           kind == TokenKind::Number ||
           kind == TokenKind::Error)
          &&
          "A token can only contain a MyString if .kind == Identifier|Real|Error");

   this->kind = kind;
   this->string = string;
}

inline bool hasStringLiteral(TokenKind kind)
{
    return (s16)kind > 0 && 
           (s16)kind < TOKEN_STRING_LITERALS_LEN;
}

const char* Token::stringRepresentation()
{
    if(hasStringLiteral(this->kind)){
        return tokenStringLiterals[(u64)this->kind];
    }
    else{
        // [!] danger: 
        return this->string.buffer;
    }
}

void Token::destroy()
{
   string.destroy();
}



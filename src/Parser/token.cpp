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
    "cast", // can be used as unary as all, is just that I need a way to continuously
            // group together all the keywords that initialy get picked up as identifier
            // by the lexer
    "sizeof", //can be used as unary as well
    "auto", 

  // @TODO: write the real string representations
  // binary Operators
    "LessEqual",
    "GreaterEqual",
    "EqualEqual",
    "NotEqual",
    "And",
    "Or",
    "Plus",
    "Minus",   // can be used as unary aswell
    "Division",
    "Multiplication",
    "Modulus",
    "Less",    // can be used as a punctuation/grouping
    "Greater", // can be used as a punctuation/grouping
    "BitOr",
    "BitAnd",

  // unary operators
    "Not",
    "BitNot",

  // other (punctuation/grouping)
    "LeftParen",
    "RightParen",
    "SemiColon",
    "Equal",
    "Eof",
};


bool isUnaryOperatorKind(TokenKind kind)
{
    return kind == TokenKind::Not || 
           kind == TokenKind::BitNot || 
           kind == TokenKind::Minus || 
           kind == TokenKind::Key_cast || 
           kind == TokenKind::Key_sizeof;
}

bool isBiOperatorKind(TokenKind kind)
{
    return (s16)kind >= BI_OPERATORS_BEG &&
           (s16)kind < (BI_OPERATORS_BEG + BI_OPERATORS_LEN);
}

bool isNativeType(TokenKind kind)
{
    return (s16)kind >= NATIVE_TYPES_BEG &&
           (s16)kind < (NATIVE_TYPES_BEG + NATIVE_TYPES_LEN);
}

Optional<TokenKind> isStringKeyword(const char* buffer, s64 length)
{

    // @Bodge:
    // [!] We start with 0 and not KEYWORDS_BEG because we alse want to check if 
    // it is a nativeType
    for (u16 i = 0; i < KEYWORDS_BEG + KEYWORDS_LEN; i++)
    {
        // unnecessary strlen, because that value is a compile time constant
        // I hope the compiler can optimize it away 
        // @TODO: check in compiler explorer if it can. idk :/
        const char* keyword = tokenStringLiterals[i];
        u16 keywordLength = (u16) strlen(keyword);
        if(keywordLength == length
            &&
            (memcmp(keyword, buffer, keywordLength) == 0))
        {
            return (TokenKind)i;
        }
    }
    return { };
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



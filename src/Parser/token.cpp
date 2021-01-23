#include "./token.h"

const char* keywords[11] = 
{
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
    "cast"
};

bool isBiOperatorKind(TokenKind kind)
{
   // @BAD: find a better, to add more tokens, it is way too much work right now
    return kind == TokenKind::Plus ||
           kind == TokenKind::Minus ||
           kind == TokenKind::Division ||
           kind == TokenKind::Multiplication ||
           kind == TokenKind::LessEqual ||
           kind == TokenKind::GreaterEqual ||
           kind == TokenKind::EqualEqual ||
           kind == TokenKind::NotEqual ||
           kind == TokenKind::And ||
           kind == TokenKind::Or ||
           kind == TokenKind::Less ||
           kind == TokenKind::Greater ||
           kind == TokenKind::Equal ||
           kind == TokenKind::BitAnd ||
           kind == TokenKind::BitOr;
}

Token::Token()
{

}

Token::Token(TokenKind kind)
{
   // Only some tokenKinds can have 'void' as their second member
   // @BAD: find a better, to add more tokens, it is way too much work right now
   assert(kind == TokenKind::Eof ||
          kind == TokenKind::LessEqual ||
          kind == TokenKind::GreaterEqual ||
          kind == TokenKind::EqualEqual ||
          kind == TokenKind::NotEqual ||
          kind == TokenKind::And ||
          kind == TokenKind::Or ||
          kind == TokenKind::Plus ||
          kind == TokenKind::Minus ||
          kind == TokenKind::Division ||
          kind == TokenKind::Multiplication ||
          kind == TokenKind::Less ||
          kind == TokenKind::Greater ||
          kind == TokenKind::Equal ||
          kind == TokenKind::Not ||
          kind == TokenKind::BitAnd ||
          kind == TokenKind::BitOr ||
          kind == TokenKind::LeftParen ||
          kind == TokenKind::RightParen ||
          (kind > 0 && kind < KEYWORDS_LENGTH) // for any keyword
          );


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

void Token::destroy()
{
   string.destroy();
}



#include "token.h"

Token::Token(TokenKind kind)
{
   assert((kind == TokenKind::Eof ||
           kind == TokenKind::Plus ||
           kind == TokenKind::Minus)
          &&
          "A token can only contain a 'void' if .kind == Eof|Plus|Minus");

   this->kind = kind;
}


Token::Token(TokenKind kind, MyString string)
{
   assert((kind == TokenKind::Identifier ||
           kind == TokenKind::Real ||
           kind == TokenKind::Error)
          &&
          "A token can only contain a MyString if .kind == Identifier|Real|Error");

   this->kind = kind;
   this->string = string;
}

Token::Token(TokenKind kind, u64 integer){

   assert((kind == TokenKind::Integer)
          &&
          "A token can only contain a MyString if .kind == Identifier|Integer|Real");

   this->kind = kind;
   this->integer = integer;
}


void Token::destroy()
{
   string.destroy();
}

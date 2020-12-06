#include "token.h"

//TokenKind stuff.
//@Improvement?: should we put all the tokenKind stuff into its own namespace?
//maybe its own file even??
bool isOperatorKind(TokenKind kind)
{
    return kind == TokenKind::Plus ||
    kind == TokenKind::Minus ||
    kind == TokenKind::Division ||
    kind == TokenKind::Multiplication;
}

Token::Token()
{

}

Token::Token(TokenKind kind)
{
   assert((kind == TokenKind::Eof ||
           kind == TokenKind::Plus ||
           kind == TokenKind::Minus ||
           kind == TokenKind::Division ||
           kind == TokenKind::LeftParen ||
           kind == TokenKind::RightParen ||
           kind == TokenKind::Multiplication)
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


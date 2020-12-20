#ifndef TOKEN_H
#define TOKEN_H

#include "../pch.h"
#include "../mystring.h"


//@[?] C++: why dont I need to specify the 'namespace' of the enum when I dont add
//the 'class' modifier to the enum definition
//@[?] C++: do I need to define the enum in a .cpp too?
enum TokenKind : char{
    Identifier = 0,
    Integer = 1,
    Real = 2,
    Error = 4,
    Eof = 5,

    //Binary Operators:
    Plus = '+',
    Minus = '-',
    Division = '/',
    Multiplication = '*',


    LeftParen = '(',
    RightParen = ')',
};

//@C++: should be inline but I dont know how to inline accross different
//compilation units or whatever
//[!]: warning: this is used in assertions as well
bool isOperatorKind(TokenKind kind);

bool isBiOperatorKind(TokenKind kind);

//@Improvement?: this is basically a tagged union, people say that that is a
//std::variant in c++, should we use that here???
struct Token{
   TokenKind kind;

   //@TODO: read more about floats
   //@TODO: add a way to support 'scientific notation' in real literals
   //@Impovement: we should support bigger floats and ints or at the very
   //least, u128 and float128
   //@Discussion:
   //when should i convert from the string we lex to the actual number
   //there is quite a bit of weirdness and modifiers that might be easier to
   //deal with at parsing like 0xaffff, 0b11_1_1_1111 and something like -1
   //as well
   //we could deal with that later by just passing the string and have someone
   //else later on deal with it
   //the thing is that I kinda have to say the type of the number literal in
   //certain situations like if the integer is too long and doesnt fit in
   //a s32 or whatever, that sounds like something we should deal about later
   //but some stuff is easy and faster to figure when lexing like if it has to
   //be real or not.
   //problem: (float32)(string_to_float64("10.2")) is not the same as
   //string_to_float32("10.2")
   //so we definitely need serious type info in that case. So we have to
   //pass the string there
   //however:
   //as long as we check the 64bit int is bellow a certain value when before
   //doing the (int32) casting we can say that:
   //(int32)(string_to_int64("10")) is the same as string_to_int32("10")
   //so we dont need to pass the string around in this case

   union{
       MyString string;
       u64 integer;
       //a float token are not converted until later so they will contain a
       //string
   };

   //doesnt do anything, is useful becuase the TokenCache needs to
   //initialize its tokenBuffer because this is c++ (I think)
   //so we need a default constructor
   Token();

   //A bunch of constructors because c++ doesnt let us initialize things like in
   //C99, oh well :/
   Token(TokenKind kind);

   Token(TokenKind kind, MyString string);
   Token(TokenKind kind, u64 integer);

   //not a destructor because we dont want to deal with 'copy constructor
   //operator' doing expensive copies when we want to fucking return by value
   //@TODO: see if that is a valid concern!!
   void destroy();
};


#endif // TOKEN_H

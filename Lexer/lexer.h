#ifndef LEXER_H
#define LEXER_H

#include "pch.h"
#include "Lexer/token.h"
#include "mystring.h"

//TODO: put all this into different files and make a directory for all lexer
//related stuff
//BUG: Token definition inside header!!!

namespace Lexer
{
    //all the 'private' stuff
    //@Improvement, I dont know how to say something is private to a namespace
    //in c++, the only way I am aware of is putting it inside the cpp but I would
    //like for this header to have all the declarations because its easier to
    //read that imo. oh well :/
    extern MyString hllSource;
    extern s64 lexPointer;

    //returns const char* to string literal containing the error message, returns
    //nullptr if no error occured
    //@TODO: make a better way of error handling, honestly we need to put some
    //serious thought into how we are going to comunicate errors, we can't just
    //stop compiling after we find the first error. But maybe we cant construct
    //a good error message as soon as we know there is an error, we might have
    //to go back in the call tree to make a better error
    std::optional<const char*> init(const char* path);
    Token getNextToken();
};

#endif // LEXER_H


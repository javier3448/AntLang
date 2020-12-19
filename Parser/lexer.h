#ifndef LEXER_H
#define LEXER_H

#include "pch.h"
#include "Parser/token.h"
#include "Parser/tokencache.h"
#include "mystring.h"

namespace Lexer
{
    //all the 'private' stuff
    //@Improvement, I dont know how to say something is private to a namespace
    //in c++, the only way I am aware of is putting it inside the cpp but I would
    //like for this header to have all the declarations because its easier to
    //read that imo. oh well :/
    extern MyString hllSource;
    //points to the first unLexed character in hllSource
    extern s64 lexPointer;

    //A constant array is perfectly fine for know, I doubt we will ever cache more
    //than 16 tokens, but if we do we just change this to std::vector or our own
    //dynamic array
    extern TokenCache tokenCache;

    //returns const char* to string literal containing the error message, returns
    //nullptr if no error occured
    //@TODO: make a better way of error handling, honestly we need to put some
    //serious thought into how we are going to comunicate errors, we can't just
    //stop compiling after we find the first error. But maybe we cant construct
    //a good error message as soon as we know there is an error, we might have
    //to go back in the call tree to make a better error
    std::optional<const char*> init(const char* path);


    //Unlike peekChar this actually caches the tokens so we can get them right away
    //later
    //Returns a pointer to the buffer inside the tokenCache
    //unlike peekChar this ONLY works on possitive integers and 0
    Token* peekToken(s64 amount = 0);

    //'Transfers ownership' i.e. it pops it out of the cache if it is in cache
    Token getNextToken();

    //****Private stuff****

    //lexes a token from lexPointer onward
    Token lexToken();
    char peekChar(s64 amount = 0);
    void advanceAndAppend();
    void advanceAndSkip();


    //TODO: We need a way to delete the input string when we are done lexing.
    //It would be unfair to leak all that mem.
};

#endif // LEXER_H


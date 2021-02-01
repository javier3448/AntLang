#ifndef LEXER_H
#define LEXER_H

#include "../pch.h"
#include "../Parser/token.h"
#include "../Parser/tokencache.h"
#include "../mystring.h"

// @TODO: find a better way to handle end of file, it looks awkward in the
// state machine
// -> maybe handle it the same way something like fread_char does, return an int 
// bigger than char instead of char and decide on a special value to represent EOF

// THIS LEXER IS STUPID AND USES null TO SIGNAL EOF.
// SO THERE IS BASICALY 'myUB' when a source file has a null char anywhere

namespace Lexer
{
    extern MyString hllSourceDif;
    //points to the first unLexed character in hllSource
    extern s64 lexPointer;

    // A tokenCache data structure to implement the peekToken and consumeToken
    // functions
    // A 'static' array is perfectly fine for know, I doubt we will ever cache more
    // than 16 tokens
    extern TokenCache tokenCache;

    void init(const char* path);

    //Unlike peekChar this actually caches the tokens so we can get them right away
    //later
    //Returns a pointer to the buffer inside the tokenCache
    //unlike peekChar this ONLY works on possitive integers and 0
    Token* peekToken(s64 amount = 0);

    //'Transfers ownership' i.e. it pops it out of the cache if it is in cache
    Token consumeToken();


    // THE FOLLOWING FUNCS SHOULD NOT BE USED OUTSIDE THIS NAMESPACE

    // lexes a token from lexPointer onward
    Token lexToken();
    char peekChar(s64 amount = 0);
    void advanceAndAppend();
    void advanceAndSkip();


    //TODO: We need a way to delete the input string when we are done lexing.
    //It would be unfair to leak all that mem.
};

#endif // LEXER_H


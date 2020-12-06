#ifndef TOKENCACHE_H
#define TOKENCACHE_H

#include "pch.h"

#include "token.h"

//Queue like thing with static size to cache tokens when the parser starts
//peeking and getting
struct TokenCache
{

    static constexpr s8 BUFFER_SIZE = 16;

    Token tokenBuffer[BUFFER_SIZE];
    s8 occupiedSpaces = 0;
    //First available space. Some people call it 'rear'
    s8 freeOffset = 0;
    //points to the token that is next to be dequeued. Some people call it 'front'
    s8 targetOffset = 0;

    void enqueue(Token token);
    Token dequeue();

    //I dont fucking know if we need this constructor :(.
    //I just want to set the struct members to the values that I have specified
    //here in the .h
    TokenCache();
};

#endif // TOKENCACHE_H

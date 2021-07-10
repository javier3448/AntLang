#include "./tokencache.h"

TokenCache::TokenCache()
{
    //nothing, this constructor exist because this is the only way I could make
    //cpp shut up about not initializing stuff
}

//void TokenCache::enqueue(Token* token)
//{
//    assert(occupiedSpaces < ArrayCount(tokenBuffer) && "Token cache has surpassed its maximum static capacity");

//    std::memcpy(&(tokenBuffer[freeOffset]), token, sizeof(Token));
//    freeOffset = (freeOffset + 1) % ArrayCount(tokenBuffer);

//    occupiedSpaces++;
//}

void TokenCache::enqueue(Token token)
{
    assert(occupiedSpaces < ArrayCount(tokenBuffer) && "Token cache has surpassed its maximum static capacity");

    std::memcpy(&(tokenBuffer[freeOffset]), &token, sizeof(Token));
    freeOffset = (freeOffset + 1) % ArrayCount(tokenBuffer);

    occupiedSpaces++;
}

Token TokenCache::dequeue()
{
    assert(occupiedSpaces > 0 && "Queue is empty!");

    //I just want to do this:
    //`Token resultToken = uninitialized;` //Do not call the fucking constructor
    //because reserving the mem in the stack before returning it makes the
    //whole 'flow' and 'logic' of this func a lot easier to follow in this case
    //but I dont know how to do that in c++ (dont know if it is possible) so we
    //must do something stupid like:
    Token* resultToken = (Token*)alloca(sizeof(Token));

    std::memcpy(resultToken, &(tokenBuffer[targetOffset]), sizeof(Token));
    targetOffset = (targetOffset + 1) % ArrayCount(tokenBuffer);

    occupiedSpaces--;

    return *resultToken;
}

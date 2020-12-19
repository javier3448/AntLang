#ifndef SHUNTINGYARD_H
#define SHUNTINGYARD_H

//NOT FINISHED.
//WE DECIDED TO USE THE Jonatha Blow tree rotation thingy INSTEAD
//This '~required us to move around tokens in the heap in a weird way that *seems*
//slow. They went from token cache (a statically sized Queue) to the stack
//(we returned by value) to the shuntingStack (we need a dynamic number of these
//stacks and each has to have dynamic size) which would allocate them with a separate
//malloc and only store the pointer to them OR it would store them by value and place
//them into a different malloc once they had to be poped from the stack
//Thats weird and I have choose a strategy and I have no idea which is best.
//The Jonathan Blow tree rotation seem so much simpler now, and requires no auxiliary
//data structure. So we will use that for now

#include "pch.h"

#include "astexpression.h"

//A bunch of structs and what not that we need to implement the shunting yard
//algorith.

//[?]C++ how do everything but the ShuntingStacks struct 'private' and how
//can I make it so its the first definition on this h file, so the whole thing
//is easier to read

enum Associativity : u8
{
    left,
    right,
    non
};

struct ShuntingOperator
{
    //@Imporvement
    //both precedence and assosiativity could be represented on the same
    //byte. for now this is fine
    s8 precedence;
    Associativity associativity;

};

//Duplicates size everytime it has to realloc its initial size is idk 16?
struct OperatorStack
{
    //@Tunning
    static const s32 initialCapacity = 16;

    s32 size;
    s32 topIndex;
    ShuntingOperator* buffer;

};

//Duplicates size everytime it has to realloc its initial size is idk 16?
struct ExpressionStack
{
    //@Tunning
    static const s32 initialCapacity = 16;

    s32 size;
    s32 topIndex;
    AstExpression** buffer;
};


struct ShuntingStacks
{
    //Here we started to see that it complicates quite a bit the 'lifetime' of
    //the tokens quite a bit. because we need to place them in a dynamic data
    //structure but the lexer wants to return them by value
    void pushOperator(Token token);
    ShuntingOperator popOperator();
    ShuntingOperator* peekOperator();

    AstExpression* popExpressionStack();
    //This returns a pointer and not a pointer to pointer because AstExpression
    //will forever live in heap land any way, so it would be a pointles indirection
    //unlike peekOperator where the actual data of the Operator is right there in
    //ShuntingOperator* buffer
    AstExpression* peekExpressionStack();

    void init();
    void destroy();
};

#endif // SHUNTINGYARD_H

#ifndef ASTEXPRESSION_H
#define ASTEXPRESSION_H

#include "pch.h"

#include "token.h"

enum AstExpressionKind : char{
    IntegerLiteral = 0,
    BinaryExpression = 1,
};

//@Improvement: :((( I would prefer if we could define the structures outside the union
//but cpp complains that the type definition is not complete and AstExpression type and
//its form types have a 'circular dependency'
struct AstExpression
{
    AstExpressionKind kind;
    union{
        Token intLiteral;
        struct
        {
            AstExpression* left;
            Token _operator;
            AstExpression* right;
        }binaryForm;
    };

    void makeIntLiteralExpression(Token intLiteral);
    void makeBinaryExpression(AstExpression* left, Token biOperator, AstExpression* right);
};



//struct AstBinaryExpressionForm
//{
//    AstExpression* left;
//    Token _operator;
//    AstExpression* right;
//};

//struct AstExpressionIntegerLiteralForm
//{
//    Token intLiteral;
//};


#endif // ASTEXPRESSION_H

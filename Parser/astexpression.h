#ifndef ASTEXPRESSION_H
#define ASTEXPRESSION_H

#include "pch.h"

#include "token.h"

struct AstExpression;
struct BinaryExpressionForm;

enum AstExpressionKind : char{
    IntegerLiteral = 0,
    BinaryExpression = 1,
};

struct BinaryExpressionForm
{
    AstExpression* left;
    Token _operator;
    AstExpression* right;
};

struct AstExpression
{
    AstExpressionKind kind;
    union{
        Token intLiteral;
        BinaryExpressionForm binaryForm;
    };
    //@Improvement: Find a better solution to communicate that the expression is
    //parenthesized
    //Bodgy flag that we will only use when rearrenging the tree because precedences
    bool hasParenthesis;

    s16 getPrecedence();

    void makeIntLiteralExpression(Token intLiteral);
    void makeBinaryExpression(AstExpression* left, Token biOperator, AstExpression* right);
};

#endif // ASTEXPRESSION_H

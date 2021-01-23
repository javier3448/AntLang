#ifndef ASTEXPRESSION_H
#define ASTEXPRESSION_H

#include "../pch.h"

#include "./token.h"
#include "./asttypeexpression.h"

struct AstExpression;
struct BinaryExpressionForm;

enum AstExpressionKind : char{
    NumberLiteral = 0,
    BinaryExpression = 1,
    CastExpression = 2,
};

struct BinaryExpressionForm
{
    AstExpression* left;
    Token _operator;
    AstExpression* right;
};

struct CastExpressionForm
{
    // (Identifier | (some)keyword)
    // if AstTypeExpression becomes too big it might be a good idea to make this
    // into a pointer, idk we will see then
    AstTypeExpression typeExpression;
    AstExpression* expression;
};

struct AstExpression
{
    AstExpressionKind kind;
    union{
        Token numberLiteral;
        BinaryExpressionForm binaryForm;
        CastExpressionForm castForm;
    };
    //@Improvement: Find a better solution to communicate that the expression is
    //parenthesized
    //Bodgy flag that we will only use when rearrenging the tree because precedences
    bool hasParenthesis;

    s16 getPrecedence();

    void makeIntLiteralExpression(Token intLiteral);
    void makeBinaryExpression(AstExpression* left, Token biOperator, AstExpression* right);
    void makeCastExpression(AstTypeExpression typeExpression, AstExpression* expression);
};

#endif // ASTEXPRESSION_H

#ifndef ASTEXPRESSION_H
#define ASTEXPRESSION_H

#include "../pch.h"

#include "./token.h"
#include "./asttypeexpression.h"

struct AstExpression;
// @🤔: All this 'forms' have a token, we could use that token to determine what
// form does the expression take instead of using an aditional enum ExpressionKind
struct BinaryExpressionForm;
struct UnaryExpressionForm;
struct CastExpressionForm;

// @Improvement find a better way of expressing the different 'forms' an expression
// can take because there are some weirdness in the current one like how CastExprForm
// has an operator even tho we know it will always be the keyword: 'cast' and 
// castExpressionForm is (semantically) a unary expression as well
enum AstExpressionKind : char{
    NumberLiteralKind,
    IdentifierKind,
    BinaryKind,
    UnaryKind,
    CastKind,
};

struct BinaryForm
{
    AstExpression* left;
    Token _operator;
    AstExpression* right;
};

struct UnaryForm
{
    Token _operator;
    AstExpression* subExpression;
};

// Even tho castExpr is in a different struct, semantically, it is still a unary
// expression
struct CastForm
{
    Token _operator;
    AstTypeExpression typeExpression;
    AstExpression* expression;
};

struct NumberLiteralForm
{
    Token number;
};

struct IdentifierForm
{
    Token identifier;
};

struct AstExpression
{
    AstExpressionKind kind;
    union{
        NumberLiteralForm numberLiteralForm;
        IdentifierForm identifierForm;
        BinaryForm binaryForm;
        UnaryForm unaryForm;
        CastForm castForm;
    };
    //@Improvement: Find a better solution to communicate that the expression is
    //parenthesized
    //Bodgy flag that we will only use when rearrenging the tree because precedences
    bool hasParenthesis;
};

AstExpression* new_NumberLiteralExpression(Token intLiteral);
AstExpression* new_IdentifierExpression(Token identifier);
AstExpression* new_BinaryExpression(AstExpression* left, Token biOperator, AstExpression* right);
AstExpression* new_UnaryExpression(Token _operator, AstExpression* subExpr);
AstExpression* new_CastExpression(Token castKeyword, AstTypeExpression typeExpression, AstExpression *expression);

#endif // ASTEXPRESSION_H

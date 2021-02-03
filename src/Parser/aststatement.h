#ifndef ASTSTATEMENT_H
#define ASTSTATEMENT_H

#include "../pch.h"

#include "astexpression.h"

struct AstStatement;
struct IfStatement;

// struct StatementArray
// {
//     s64 size;
//     AstStatement** buffer;
// };

enum AstStatementKind : char
{
    SingleExpressionKind,
    DeclarationKind,
    AssignmentKind,
    IfStatementKind,
};

// struct IfStatement
// {
//     AstExpression* conditionExpression;
//     // @Discusion:
//     // I don't know we should allow an expression to be a single statement, I 
//     // personally dont like it, but a scope '{}' has ~heavy semantic meaning and
//     // it feels weird that you cant use an if without it
//     StatementArray subExpressions;
// };

struct Declaration
{
    AstTypeExpression typeExpr;
    Token identifier;
    AstExpression* expression;
};

struct Assignment
{
    AstTypeExpression typeExpr;
    Token identifier;
    AstExpression* leftExpression;
    AstExpression* rightExpression;
};

struct AstStatement
{
    AstStatementKind kind;
    union{
        AstExpression* singleExpressionForm;
        // IfStatement ifStatementForm;
        Declaration declarationForm;
        Assignment assignementForm;
    };

};

AstStatement* new_SingleExpressionStatement(AstExpression* singleExpressionStatement);
//AstStatement* makeIfStatement(AstExpression* conditionExpression, StatementArray subExpression);
AstStatement* new_Declaration(AstTypeExpression typeExpr, Token identifier, AstExpression* expression);
AstStatement* new_Assignment(AstExpression* leftExpression, AstExpression* rightExpression);

#endif 

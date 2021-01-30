#ifndef ASTSTATEMENT_H
#define ASTSTATEMENT_H

#include "../pch.h"

#include "astexpression.h"

struct AstStatement;
struct IfStatement;

struct StatementArray
{
	s64 size;
	AstStatement** buffer;
};

enum AstStatementKind : char
{
    SingleExpressionKind,
    IfStatementKind,
};

struct IfStatement
{
	AstExpression* conditionExpression;
	// @Discusion:
	// I don't know we should allow an expression to be a single statement, I 
	// personally dont like it, but a scope '{}' has ~heavy semantic meaning and
	// it feels weird that you cant use an if without it
	StatementArray subExpressions;
};

struct AstStatement
{
    AstStatementKind kind;
    union{
        AstExpression* singleExpressionForm;
        IfStatement* ifStatementForm;
    };

    void makeSingleExpressionStatement(AstExpression* singleExpressionStatement);
    void makeIfStatement(AstExpression* conditionExpression, StatementArray subExpression);
};

#endif 

#ifndef PARSER_H
#define PARSER_H

#include "../pch.h"

#include "./astexpression.h"

namespace Parser
{

    //Asserts that we pass a token kind that is an operator
    int Associativity(TokenKind kind);

    AstExpression* parseExpression();
    AstExpression* parseMostPrecedentExpression();

    AstExpression* applyPrecedenceRules(AstExpression* expression);
};

#endif // PARSER_H

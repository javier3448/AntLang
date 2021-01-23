#ifndef PARSER_H
#define PARSER_H

#include "../pch.h"

#include "./astexpression.h"
#include "./asttypeexpression.h"

namespace Parser
{

    //Asserts that we pass a token kind that is an operator
    int Associativity(TokenKind kind);

    AstExpression* parseExpression();
    AstExpression* parseMostPrecedentExpression();
    // [!] This one doesn't return a pointer because, for now, struct 'CastExpression'
    // just doesnt need that additional indirection
    AstTypeExpression parseTypeExpression();

    AstExpression* applyPrecedenceRules(AstExpression* expression);
};

#endif // PARSER_H

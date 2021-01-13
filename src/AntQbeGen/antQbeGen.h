#ifndef ANTQBEGEN_H
#define ANTQBEGEN_H

#include "../pch.h"
#include "../Parser/astexpression.h"
#include "./qbeValue.h"
#include "./qbeBuffer.h"

#include <vector>

// @TERMINOLOGY: in all the 'codebase' gen = generator. ... obvs
extern QbeBuffer qbeBuffer;

namespace AntQbeGen
{
	// Just clears the qbe buffer ([!]doesnt free the pointer)
	void init();
	void compileTopLevelExpression(AstExpression* expr);
	QbeOperand compileExpression(AstExpression* expr);
	QbeOperand compileBinaryExpression(BinaryExpressionForm* biExpr);
}

#endif
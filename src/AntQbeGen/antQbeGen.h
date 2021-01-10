#ifndef ANTQBEGEN_H
#define ANTQBEGEN_H

#include "../pch.h"
#include "../Parser/astexpression.h"
#include "./qbeDefinition.h"
#include "./qbeValue.h"

#include <vector>

// @TERMINOLOGY: in all the 'codebase' gen = generator. ... obvs

namespace AntQbeGen
{
	// @TODO: WE WANT TO RELY ON THE c++ std AS LITTLE AS POSSIBLE 
	//std::vector<QbeDefinition> definitions;
	// Just initiates (or empties if called more than once) the definitions

	// @TEMP:
	// Only while we figure out the QbeDefinition struct
	// after that we can do a buffer of definitions for the QbeGen output
	extern QbeFunction mainFunction;

	void init();
	void compileTopLevelExpression(AstExpression* expr);
	QbeOperand compileExpression(AstExpression* expr);
	QbeOperand compileBinaryExpression(BinaryExpressionForm* biExpr);
}

#endif
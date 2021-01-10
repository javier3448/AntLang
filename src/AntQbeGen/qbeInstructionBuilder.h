#ifndef ANTQBEINSTRUCTIONBUILDER_H
#define ANTQBEINSTRUCTIONBUILDER_H

// Just a bunch of static functions to build every possible qbe instructions
// at least 1 function per qbe instruction

#include "../pch.h"
#include "../Parser/astexpression.h"
#include "./qbeDefinition.h"
#include "./qbeValue.h"

namespace AntQbeInstructionBuilder
{
	//@TODO: Implement a generic instruction builder that takes a QbeInstructionKind
	//as its first param

	QbeInstruction add(QbeTempType retType, QbeTemp tempResult, QbeOperand leftOperand, QbeOperand rightOperand);
	QbeInstruction sub(QbeTempType retType, QbeTemp tempResult, QbeOperand leftOperand, QbeOperand rightOperand);
	QbeInstruction mul(QbeTempType retType, QbeTemp tempResult, QbeOperand leftOperand, QbeOperand rightOperand);
	QbeInstruction div(QbeTempType retType, QbeTemp tempResult, QbeOperand leftOperand, QbeOperand rightOperand);



	//@TODO: Implement the return instruction
	QbeInstruction voidRet();
	//@bad: bad name
	QbeInstruction nonVoidRet(QbeOperand operand);
}

#endif

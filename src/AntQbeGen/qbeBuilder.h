#ifndef	QBEBUILDER_H
#define QBEBUILDER_H

#include "../pch.h"

#include "./qbeValue.h"
#include "./qbeBuffer.h"

// A bunch of functions that append new qbe stuff to a qbeBuffer
// They also do some minor assertions to check we generate mostly valid qbeIR
namespace QbeBuilder
{
	void add(QbeBuffer* qbeBuffer, QbeTemp* tempResult, QbeTempType retType, QbeOperand* leftOperand, QbeOperand* rightOperand);
	void sub(QbeBuffer* qbeBuffer, QbeTemp* tempResult, QbeTempType retType, QbeOperand* leftOperand, QbeOperand* rightOperand);
	void mul(QbeBuffer* qbeBuffer, QbeTemp* tempResult, QbeTempType retType, QbeOperand* leftOperand, QbeOperand* rightOperand);
	void div(QbeBuffer* qbeBuffer, QbeTemp* tempResult, QbeTempType retType, QbeOperand* leftOperand, QbeOperand* rightOperand);

	//@TODO: Implement the return instruction
	void voidRet(QbeBuffer* buffer);
	//@bad: bad name
	void nonVoidRet(QbeBuffer* buffer, QbeOperand* operand);
};

#endif
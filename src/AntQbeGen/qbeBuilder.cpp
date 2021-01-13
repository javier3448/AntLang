#include "./qbeBuilder.h"

// [...] From QbeIL reference:
// T stands for wlsd
// I stands for wl
// F stands for sd
// m stands for the type of pointers on the target; on 64-bit architectures it is the same as l

//@Improvement?: convine all the similar functions into just one wich receive as 
	//an arg 1 enum that indicates if they are add, sub, mul ...

void QbeBuilder::add(QbeBuffer* qbeBuffer, QbeTemp* tempResult, QbeTempType retType, QbeOperand* leftOperand, QbeOperand* rightOperand)
{
	// Return type must be the same as 
	assert(retType == tempResult->type);
	// check the params have this types: T(T, T)
	if(leftOperand->kind == QbeOperandKind::TempKind){
		assert(leftOperand->temp.type == retType);
	}
	if(rightOperand->kind == QbeOperandKind::TempKind){
		assert(rightOperand->temp.type == retType);
	}

    //@Volatile the maximum size of temp is 5 + 17 + 1(null termination)
	char leftOperandStr[23];
	leftOperand->toString(leftOperandStr);
	char rightOperandStr[23];
	rightOperand->toString(rightOperandStr);

	qbeBuffer->sprintf(
		"    %s =%c add %s, %s\n",
		tempResult->name.buffer,
		retType,
		leftOperandStr,
		rightOperandStr
	);
}
void QbeBuilder::sub(QbeBuffer* qbeBuffer, QbeTemp* tempResult, QbeTempType retType, QbeOperand* leftOperand, QbeOperand* rightOperand)
{
	// Return type must be the same as 
	assert(retType == tempResult->type);
	// check the params have this types: T(T, T)
	if(leftOperand->kind == QbeOperandKind::TempKind){
		assert(leftOperand->temp.type == retType);
	}
	if(rightOperand->kind == QbeOperandKind::TempKind){
		assert(rightOperand->temp.type == retType);
	}

    //@Volatile the maximum size of temp is 5 + 17 + 1(null termination)
	char leftOperandStr[23];
	leftOperand->toString(leftOperandStr);
	char rightOperandStr[23];
	rightOperand->toString(rightOperandStr);

	qbeBuffer->sprintf(
		"    %s =%c sub %s, %s\n",
		tempResult->name.buffer,
		retType,
		leftOperandStr,
		rightOperandStr
	);
}
void QbeBuilder::mul(QbeBuffer* qbeBuffer, QbeTemp* tempResult, QbeTempType retType, QbeOperand* leftOperand, QbeOperand* rightOperand)
{
	// Return type must be the same as 
	assert(retType == tempResult->type);
	// check the params have this types: T(T, T)
	if(leftOperand->kind == QbeOperandKind::TempKind){
		assert(leftOperand->temp.type == retType);
	}
	if(rightOperand->kind == QbeOperandKind::TempKind){
		assert(rightOperand->temp.type == retType);
	}

    //@Volatile the maximum size of temp is 5 + 17 + 1(null termination)
	char leftOperandStr[23];
	leftOperand->toString(leftOperandStr);
	char rightOperandStr[23];
	rightOperand->toString(rightOperandStr);

	qbeBuffer->sprintf(
		"    %s =%c mul %s, %s\n",
		tempResult->name.buffer,
		retType,
		leftOperandStr,
		rightOperandStr
	);
}
void QbeBuilder::div(QbeBuffer* qbeBuffer, QbeTemp* tempResult, QbeTempType retType, QbeOperand* leftOperand, QbeOperand* rightOperand)
{
	// Return type must be the same as 
	assert(retType == tempResult->type);
	// check the params have this types: T(T, T)
	if(leftOperand->kind == QbeOperandKind::TempKind){
		assert(leftOperand->temp.type == retType);
	}
	if(rightOperand->kind == QbeOperandKind::TempKind){
		assert(rightOperand->temp.type == retType);
	}

    //@Volatile the maximum size of temp is 5 + 17 + 1(null termination)
	char leftOperandStr[23];
	leftOperand->toString(leftOperandStr);
	char rightOperandStr[23];
	rightOperand->toString(rightOperandStr);

	qbeBuffer->sprintf(
		"    %s =%c div %s, %s\n",
		tempResult->name.buffer,
		retType,
		leftOperandStr,
		rightOperandStr
	);
}

void QbeBuilder::voidRet(QbeBuffer* qbeBuffer)
{
	qbeBuffer->append("    ret\n");
}

void QbeBuilder::nonVoidRet(QbeBuffer* qbeBuffer, QbeOperand* operand)
{
    //@Volatile the maximum size of temp is 5 + 17 + 1(null termination)
	char operandStr[23];
	operand->toString(operandStr);

	qbeBuffer->sprintf(
		"    ret %s\n",
		operandStr
	);
}

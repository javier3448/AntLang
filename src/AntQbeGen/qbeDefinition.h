#ifndef QBEDEFINITION_H
#define QBEDEFINITION_H

#include "../pch.h"
#include "../mystring.h"

#include "./qbeInstruction.h" 
#include <vector>

struct QbeDefinition;
struct QbeFunction;
struct QbeParam;

enum QbeDefinitionKind : char
{
    Function = 0,
};

//[!] This struct might not be complete
struct QbeParam
{
	// TODO: add support for 'aggregate type' return and 'aggregate type' param
	QbeTempType returnType;
	MyString name;
};

struct QbeFunction
{
	// TODO: add support for 'aggregate type' return and 'aggregate type' param
	QbeTempType returnType;
	std::vector<QbeParam> params;

	//@TEMP: WE DONT WANT TO DEPEND ON std IT IS TOO SLOW TO COMPILE. Change to 
	//your own dynamic array implementation. We cant even easily use a fucking 
	//tagged union if we use std::vector.
	std::vector<QbeInstruction> instructions;
};

struct QbeDefinition
{
	QbeDefinitionKind kind;
	//union {
		QbeFunction function;
	//};
};

// TODO:
// struct QbeFunction
// {
//     bool isExport;
//     retType QbeType;
//     MyString name;
//     //TODO: params...
// };

#endif // ASTEXPRESSION_H

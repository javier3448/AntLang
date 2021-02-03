#ifndef ASTTYPEEXPRESSION_H
#define ASTTYPEEXPRESSION_H

#include "../pch.h"
#include "./astexpression.h"


struct AstTypeExpression;

// @TODO:
// For now its just an identifier, but when implement pointers, arrays and templates
// it will be more complicated
struct AstTypeExpression
{
	// _type.kind = (a native type | keyword auto | identifier)
	Token _type;
};

#endif
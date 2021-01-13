#ifndef QBEVALUE_H
#define QBEVALUE_H

#include "../pch.h"
#include "../mystring.h"

// @Improvement: move QbeTemp and QbeOperand to another file
struct QbeTemp;
// @Bodge and bad name, I just want a struct that can represent
// (immediate | QbeTemp)
struct QbeOperand;
// for now qbeConstants will just represented with a u64, later on we might
// differentiate between the different 'syntactic sugar' for constants even tho
// they are semantically identical to Qbe 
// stuct QbeConstant


enum QbeTempType : char
{
	qbeWord = 'w',   //  int32
	qbeLong = 'l',   //  int64
	qbeSingle = 's', //  float32
	qbeDouble = 'd'  //  float64
};

struct QbeTemp 
{
	QbeTempType type;
	MyString name;

};

enum QbeOperandKind 
{
	TempKind,
	ConstantKind
};
//@bad: bad name
struct QbeOperand
{
	QbeOperandKind kind;
	union {
		QbeTemp temp;
		double double_constant;
		float single_constant;
		s64 slong_constant;
		u64 ulong_constant;
		s32 sword_constant;
		u32 uword_constant;
	};

    // @Volatile the maximum size of temp is 5 + 17 + 1(null termination)
	// buff must have enough space for up to 23 chars
	// sets buff to the string representation of this QbeTemp (null terminates)
	void toString(char* buff);
};

#endif
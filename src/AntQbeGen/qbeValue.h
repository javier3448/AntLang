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
	// Since the max length of this string is allegedly know at compile time.
	// we could just have a char array and not touch the heap at all instead of
	// using mystring
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

	void toString(char* buff);
};

//@Volatile the maximum size of temp is 6 + 17 + 1(null termination)
//%sssss_ffffffffffffffff
constexpr s16 MAX_QBEOPERAND_STR_LENGTH = 6 + 17 + 1;
//@TODO: add a constant for the max length of the c_string in the 
//getNextTemp function


// asserts that the first char of c_string is '%'
// @TODO: after you add a constant with the maximum tempName length.
//        let c_string be 6 or less chars
// @Important:
// c_string can only have at most 5 chars
// we implement that so the name of any given temp in the code we generate has a 
// known maximum number of chars, This will help other parts of the AntQbeGen 
// code avoid mallocs for 'ephemeral' strings. We can allocate a fixed size buffer 
// in the stack instead
// Its worth mentioning that most of the time we require the ephemeral
// strings to use sprintf. If we could program an sprintf that directly writes to  
// the QbeBuffer while being mindful of resizing, we wouldnt need to know the 
// maximum length of any given temp name
// @Improvement: define the maximum lenght of a temp name in a constant
QbeOperand getNextTemp(const char* c_string);


#endif
#ifndef QBEVALUE_H
#define QBEVALUE_H

#include "../pch.h"
#include "../mystring.h"

// @Bodge and bad name, I just want a struct that can represent
// (immediate | QbeTemp)
struct QbeOperand;
// @Improvement: move QbeTemp and QbeOperand to another file
struct QbeTemp;
struct QbeConstant;

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

// to be able to do constant folding without knowing the type that the entire
// 'constant expression' will endup being we need to carry arround all possible
// constant types ()
// @BAD?: this is struct is pretty big (32 bytes) a way we *might* be able to 
// to reduce its size is not having _u8, _u16, _u32, and maybe have all those 
// values be represented by just _64. [!]: to implement that we must be sure
// that all the overflow, comparissons, and arithmetic are always correct, even
// when we represent everything in just one field
// byte a = (0xff + 1) < 1; should end up as true
// I think as long as we just throw away all the bits we dont when we figure out
// the type of the expression is smaller that 64 we should be fine?
// you could just verify that logic pragmatically comparing the values of al the
// fields thru out a bunch of operations
// [!] there is no fucking way the throwing away logic works with signs, right
// [?] should something like 0xfff not be a valid typebyte??????
struct QbeConstant
{
	//mask-like thingy that tell you what possible types can this constant be
	//@TODO: ascii art that says what bit means what
	u16 validConstants;
	u8 _u8;    // 
	u16 _u16;  // 
	u32 _u32;  // 
	u64 _u64;  // 
	f32 _f32;  //
	f64 _f64;  //
};

enum QbeOperandKind 
{
	TempKind,
	ConstantKind
};
//@bad: bad name
// [!]: be careful with how big this struct is, because every generateQbeExpression 
// will return an instance of it
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
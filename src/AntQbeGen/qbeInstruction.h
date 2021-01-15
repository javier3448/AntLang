#ifndef QBEINSTRUCTION_H
#define QBEINSTRUCTION_H

#include "../pch.h"

// I really wish I could define this array here but c++ doesnt let me :(
// Or I dont know how to do that in c++
extern const char* QbeInstructionKindString[];

// [?] C++ why cant the underlying type of enum be  a pointer?
// if it can be any int I dont see why it could be a pointer??
// THE UNDERLYING VALUE OF THE ENUM REPRESENTS IS THE INDEX IN 
// `InstructionKindString` THAT CONTAINS ITS STRING REPRESENTATION
enum QbeInstructionKind : s16
{
    ADD = 0,
    SUB = 1,
    MUL = 2,
    DIV = 3 
};

#endif

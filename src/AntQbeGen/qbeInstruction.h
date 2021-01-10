#ifndef QBEINSTRUCTION_H
#define QBEINSTRUCTION_H

#include "../pch.h"
#include "../pch.h"
#include "./qbeValue.h" 

struct QbeInstruction;

//Arithmetic:
struct QbeAdd;
struct QbeSub;
struct QbeMul;
struct QbeDiv;
struct QbeRet;

// @Improvement????: Dont have a struct for each instruction I really dont know
// if this will be an improvement once we add all 88 instruction

// @Improvement: It might better to 'group' instruction in structs with similar
// 'human' meaning like group all the arithmetic in one struct ArithIns 
// or group them by number of arguments I guess??? Idk

// @Improvement?: move all the instruction definitions (except for QbeInstruction)
// to a different file or better yet find a fucking way to have QbeInstruction 
// defintion be the first thing in this file to make to whole thing significantly
// more readable
enum QbeInstructionKind : char{
    AddKind,
    SubKind,
    MulKind,
    DivKind,
    RetKind
};
struct QbeAdd
{
    // The type here is QbeTempType because the result must be stored in a temp.
    QbeTempType retType;
    QbeTemp result;
    QbeOperand leftOperand;
    QbeOperand rightOperand;
};
struct QbeSub
{
    // The type here is QbeTempType because the result must be stored in a temp.
    QbeTempType retType;
    QbeTemp result;
    QbeOperand leftOperand;
    QbeOperand rightOperand;
};
struct QbeMul
{
    // The type here is QbeTempType because the result must be stored in a temp.
    QbeTempType retType;
    QbeTemp result;
    QbeOperand leftOperand;
    QbeOperand rightOperand;
};
struct QbeDiv
{
    // The type here is QbeTempType because the result must be stored in a temp.
    QbeTempType retType;
    QbeTemp result;
    QbeOperand leftOperand;
    QbeOperand rightOperand;
};

// [!!!!!] if hasRetValue == false then the data in retValue is not valid!!!!
struct QbeRet
{
    bool hasRetValue;
    QbeOperand retValue;
};

struct QbeInstruction
{
    QbeInstructionKind kind;
    union{
        QbeAdd addIns;
        QbeSub subIns;
        QbeMul mulIns;
        QbeDiv divIns;
        QbeRet retIns;
    };
};

#endif // ASTEXPRESSION_H

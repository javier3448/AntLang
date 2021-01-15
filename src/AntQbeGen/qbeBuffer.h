#ifndef QBEBUFFER_H
#define QBEBUFFER_H

#include "../pch.h"

#include "./qbeInstruction.h"
#include "./qbeValue.h"

struct QbeBuffer
{
    // No good reason for this initial capacity.
    // The resizing strategy is to duplicate 
    static constexpr s64 INITIAL_CAPACITY = 0xff;

    s64 length;
    s64 size;
    char* buffer;

    // Returns a buffer with legth 0, size = INITIAL_CAPACITY
    static QbeBuffer make();

    void append(const char* c_string);
    //@TODO:
    void append(MyString mystring);

    // fmt should be string literal
    // does sprintf into the buffer and resizes if necessary
    void sprintf(const char* fmt, ...);

    void write_simpleArithInstruction(QbeBuffer* qbeBuffer, QbeInstructionKind instruction, QbeTemp* tempResult, QbeTempType retType, QbeOperand* leftOperand, QbeOperand* rightOperand);
    void write_Add(QbeTemp* tempResult, QbeTempType retType, QbeOperand* leftOperand, QbeOperand* rightOperand);
    void write_Sub(QbeTemp* tempResult, QbeTempType retType, QbeOperand* leftOperand, QbeOperand* rightOperand);
    void write_Mul(QbeTemp* tempResult, QbeTempType retType, QbeOperand* leftOperand, QbeOperand* rightOperand);
    void write_Div(QbeTemp* tempResult, QbeTempType retType, QbeOperand* leftOperand, QbeOperand* rightOperand);

    void write_VoidRet();
    //@bad: bad name
    void write_NonVoidRet(QbeOperand* operand);


    void destroy();
};


#endif

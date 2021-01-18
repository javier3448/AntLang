#include "qbeBuffer.h"

#include <stdarg.h>

QbeBuffer QbeBuffer::make()
{
    QbeBuffer result;
    result.buffer = (char*) malloc(INITIAL_CAPACITY);
    result.buffer[0] = '\0';
    result.length = 0;
    result.size = INITIAL_CAPACITY;

    return result;
}

void QbeBuffer::append(const char* c_string)
{
    s64 str_length = std::strlen(c_string);

    // checks if it need more space that the buffer has
    if(this->length + str_length + 1 > this->size){
        do{
            this->size = this->size * 2;
        }while(this->length + str_length + 1 > this->size);
        this->buffer = (char*)std::realloc(this->buffer, this->size);
    }

    // str_length + 1 because we *do* copy the null termination
    std::memcpy(this->buffer + this->length, c_string, str_length + 1);
    this->length += str_length;
}

// I just want a sprintf that reallocates the buffer when necessary the only
// non bodgy way of doing this is to implement our own sprintf that 'lexes'
// the fmt and all
// For now just doing snprintf and reallocate if it fails is enough
void QbeBuffer::sprintf(const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);

    auto addedChars = vsnprintf(this->buffer + this->length, this->size - this->length, fmt, args);
    // catch encoding error
    assert(addedChars > 0);
    va_end(args);
    // It is extremely unlikely for this loop to run more than once I dont know
    // if that kind of stuff messes up the branch predictor
    // @TODO: test that this loop doesnt break if there is a second iteration
    while(addedChars > this->size - this->length){
        va_start(args, fmt);
        this->size = this->size * 2;
        this->buffer = (char*)std::realloc(this->buffer, this->size);

        addedChars = vsnprintf(this->buffer + this->length, this->size - this->length, fmt, args);
        // catch encoding error
        assert(addedChars > 0);
        va_end(args);
    }
    this->length = this->length + addedChars;
 
}
 
// add, sub, div, mul happen to have identical 'qbe type rules' so the code 
// required to write any of those instruction is identical except for the 
// instruction name. So this function takes as arg an instrucction name and saves
// us some code duplication
// @Improvement?: instead of the instructionName use the instructionKind enum 
// and let this function be a method of qbeBuffer
void QbeBuffer::write_simpleArithInstruction(QbeBuffer* qbeBuffer, QbeInstructionKind instruction, QbeTemp* tempResult, QbeTempType retType, QbeOperand* leftOperand, QbeOperand* rightOperand)
{
    // maybe later on when we do typechecking ourselft this assertions wont be 
    // necessary

    // Return type must be the same as 
    assert(retType == tempResult->type);
    // check the params have this types: T(T, T)
    if(leftOperand->kind == QbeOperandKind::TempKind){
        assert(leftOperand->temp.type == retType);
    }
    if(rightOperand->kind == QbeOperandKind::TempKind){
        assert(rightOperand->temp.type == retType);
    }

    char leftOperandStr[MAX_QBEOPERAND_STR_LENGTH];
    leftOperand->toString(leftOperandStr);
    char rightOperandStr[MAX_QBEOPERAND_STR_LENGTH];
    rightOperand->toString(rightOperandStr);

    qbeBuffer->sprintf(
        "    %s =%c %s %s, %s\n",
        tempResult->name.buffer,
        retType,
        QbeInstructionKindString[instruction],
        leftOperandStr,
        rightOperandStr
    );
}

void QbeBuffer::write_Add(QbeTemp* tempResult, QbeTempType retType, QbeOperand* leftOperand, QbeOperand* rightOperand)
{
    write_simpleArithInstruction(this, ADD, tempResult, retType, leftOperand, rightOperand);
}
void QbeBuffer::write_Sub(QbeTemp* tempResult, QbeTempType retType, QbeOperand* leftOperand, QbeOperand* rightOperand)
{
    write_simpleArithInstruction(this, SUB, tempResult, retType, leftOperand, rightOperand);
}
void QbeBuffer::write_Mul(QbeTemp* tempResult, QbeTempType retType, QbeOperand* leftOperand, QbeOperand* rightOperand)
{
    write_simpleArithInstruction(this, MUL, tempResult, retType, leftOperand, rightOperand);
}
void QbeBuffer::write_Div(QbeTemp* tempResult, QbeTempType retType, QbeOperand* leftOperand, QbeOperand* rightOperand)
{
    write_simpleArithInstruction(this, DIV, tempResult, retType, leftOperand, rightOperand);
}

void QbeBuffer::write_VoidRet()
{
    this->append("    ret\n");
}

void QbeBuffer::write_NonVoidRet(QbeOperand* operand)
{
    char operandStr[MAX_QBEOPERAND_STR_LENGTH];
    operand->toString(operandStr);

    this->sprintf(
        "    ret %s\n",
        operandStr
    );
}

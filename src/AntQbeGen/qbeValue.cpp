#include "qbeValue.h"

// @Improvement: when qbeOperand is a temp we shouldnt need to write the string into
// buffer, we should be able to just return the this->temp.name.buffer
void QbeOperand::toString(char * buff)
{
	switch(this->kind){
		case QbeOperandKind::TempKind:
		{
    		auto err = snprintf(buff, MAX_QBEOPERAND_STR_LENGTH, "%s", this->temp.name.buffer);
    		assert(err > 0);
    		assert(err <= MAX_QBEOPERAND_STR_LENGTH);
    		return;
		}break;

		// @TODO: add a way to write double and single constants
		// (it doesnt change anything semantically bacause qbe packs all constants
		// in 64 bit blobs, so its just syntactic sugar but it is still useful)
		case QbeOperandKind::ConstantKind:
		{
    		auto err = snprintf(buff, MAX_QBEOPERAND_STR_LENGTH, "%lu", this->ulong_constant);
    		assert(err > 0);
    		assert(err <= MAX_QBEOPERAND_STR_LENGTH);
    		return;
		}break;

		default:
			assert(false);
	}
}

// @TODO: add support for different types of temps no just doubles
QbeOperand getNextTemp(const char* c_string)
{
    static u64 counter = 1;

    assert(strlen(c_string) < 7);
    assert(c_string[0] == '%');

    // @Improvement: we could snprintf directly into the mystring buffer but we 
    // cant because right now mystring cant have a buffer with size different 
    // to the string's length
    char qbeTempString[MAX_QBEOPERAND_STR_LENGTH];
    auto err = snprintf(qbeTempString, sizeof qbeTempString, "%s_%lx", c_string, counter);
    assert(err > 0);
    assert(err <= (s64) sizeof qbeTempString);
    //@Volatile the maximum size of temp is 6 + 17 + 1(null termination)
    //%sssss_ffffffffffffffff

    counter++;
    return QbeOperand { 
        .kind = QbeOperandKind::TempKind, 
        .temp = {
            .type = QbeTempType::qbeDouble,
            .name = MyString::make(qbeTempString),
        } 
    };
}
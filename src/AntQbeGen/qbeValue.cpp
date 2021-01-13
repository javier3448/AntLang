#include "qbeValue.h"

void QbeOperand::toString(char * buff)
{
    // @Volatile the maximum size of temp is 5 + 17 + 1(null termination)
	// @BUG (maybe): We assume that the maximum size of a constant is less than 
	// or equal to 23
	switch(this->kind){
		case QbeOperandKind::TempKind:
		{
    		auto err = snprintf(buff, 23, "%s", this->temp.name.buffer);
    		assert(err > 0);
    		assert(err <= 23);
    		return;
		}break;

		// @TODO: add a way to write double and single constants
		// (it doesnt change anything semantically bacause qbe packs all constants
		// in 64 bit blobs, so its just syntactic sugar but it is still useful)
		case QbeOperandKind::ConstantKind:
		{
    		auto err = snprintf(buff, 23, "%lu", this->ulong_constant);
    		assert(err > 0);
    		assert(err <= 23);
    		return;
		}break;

		default:
			assert(false);
	}
}

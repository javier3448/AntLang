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
// For now just doing snprintf and reallocate if it fails its enough

void QbeBuffer::sprintf(const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
 
    auto addedChars = vsnprintf(this->buffer + this->length, this->size - this->length, fmt, args);
    // catch encoding error
    //@temp nocheckin
    assert(addedChars > 0);
    // It is extremely unlikely for this loop to run more than once I dont know
    // if that kind of stuff messes up the branch predictor
    va_end(args);
    while(addedChars > this->size - this->length){
    	va_start(args, fmt);
    	this->size = this->size * 2;
    	this->buffer = (char*)std::realloc(this->buffer, this->size);

    	// @BUG: using args here for a second time seems to SEGFAULT. we tried 
    	// to call csnprinf 2 times consecutively in the debugger in it 
    	// segfaults as well so I am almost sure thats the bug
	    addedChars = vsnprintf(this->buffer + this->length, this->size - this->length, fmt, args);
    	// catch encoding error
	    assert(addedChars > 0);
	    va_end(args);
    }
    this->length = this->length + addedChars;
 
}
 
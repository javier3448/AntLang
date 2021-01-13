#ifndef QBEBUFFER_H
#define QBEBUFFER_H

#include "../pch.h"

#include "./qbeValue.h"

// @TODO: make a simple general purpose 'char buffer' that just duplilcates
// its size everytime it runs out of space. It is null terminated to 
// easily interact with snprintf

struct QbeBuffer
{
	// No good reason for this initial capacity.
	// The resizing strategy is to duplicate 
	static constexpr s64 INITIAL_CAPACITY = 0xff;

	s64 length;
	// i.e. 
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

	void destroy();
};

#endif

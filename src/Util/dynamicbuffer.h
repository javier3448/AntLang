#ifndef DYNAMICBUFFER_H
#define DYNAMICBUFFER_H

// Meant to replace a char buf[] = alloca(...) when the size of buf is expected to
// to too large for the stack or it is too unpredicatable.
// It is also expected to be 'ephemeral', thats why we use constructors and destructors
// and that why wont allow it be copied/moved/ or whatever
// @TODO: test that the other function cant copy or move it by using the pointer
// We can pass a pointer to it to another function.

// [!] USES CONSTRUCTORS AND DESTRUCTORS FOR ITSELF
// [!] BUT DOESN'T USE new TO ALLOCATE buffer
// [!] DOES NOT RESIZE
// [!] CAN'T BE COPIED OR MOVED

#include "../typedefs.h"
#include <cstdlib> // malloc, realloc, free
#include <assert.h>

template<typename T>
struct DynamicBuffer
{
	s64 size;
	T* buffer;

	DynamicBuffer(s64 size)
	{
		assert(size >= 0 &&
			"Size cant be negative");

		buffer = std::malloc(size * sizeof(T));
	};

	~DynamicBuffer()
	{
		free(buffer);
	};

	DynamicBuffer(const DynamicBuffer& other) = delete;//copy constructor
	DynamicBuffer(DynamicBuffer&& other) = delete;//move constructor
    DynamicBuffer& operator=(const DynamicBuffer& other) = delete;//copy assignment
    DynamicBuffer& operator=(DynamicBuffer&& other) = delete;//move assignment

    T& operator[](s64 index)
    {
    	return buffer[index];
    };
};

#endif
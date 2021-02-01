#ifndef QDDYNARRAY_H
#define QDDYNARRAY_H

#include "../typedefs.h"
#include <cstdlib> // malloc, realloc, free
#include <assert.h>

// Quick and dirty dynamic array.
// A simple dynamic array implementation with really stupid resizing strategies 
// and bad performance in general
// [!] NOT INTENDED FOR 'REAL' USE JUST A TEMPORARY WHILE WE COME UP WITH A BETTER
// ARRAY IMPLEMENTATION FOR THAT SPECIFIC SITUATION 


// Starting size: 8
// It resizes by duplicating its size
template<typename T>
struct QdDynArray 
{
	static constexpr s64 INITIAL_SIZE = 8;

	// @BAD: bad name
	// Number of elements in the array
	s64 length;

	// size of the allocated buffer
	s64 size;
	T* buffer;

	static QdDynArray make()
	{
		return QdDynArray{
			.length = 0,
			.size = INITIAL_SIZE,
			.buffer = (T*)std::malloc(INITIAL_SIZE * sizeof(T))
		};
	}

	static QdDynArray make(s64 length)
	{
		assert(length >= 0 &&
			   "length cant be negative");

		QdDynArray result;
		result.length = length;

		if(length <= INITIAL_SIZE){
			result.size  = INITIAL_SIZE;
		}
		else{
			// @TODO: write a getNextPowerOfTwo function that simplifies this
			// 'We propagate the leftmost set bit and then we add 1'
			// [...] For a more complete explanation: Hacker's Delight 3-2
			u64 a = (u64) length;
			a = a | (a >> 1);
			a = a | (a >> 2);
			a = a | (a >> 4);
			a = a | (a >> 8);
			a = a | (a >> 16);
			a = a | (a >> 32);
			result.size = a + 1;
		}

		result.buffer = std::malloc(sizeof(T) * result.size);
		return result;
	};

	// Creates a dynamic array of at least that size
	static QdDynArray make_andReserve(s64 size)
	{
		assert(size >= 0 &&
			   "size cant be negative");

		QdDynArray result;
		result.length = 0;

		if(size <= INITIAL_SIZE){
			result.size  = INITIAL_SIZE;
		}
		else{
			// @TODO: write a getNextPowerOfTwo function that simplifies this
			// 'We propagate the leftmost set bit and then we add 1'
			// [...] For a more complete explanation: Hacker's Delight 3-2
			u64 a = (u64) size;
			a = a | (a >> 1);
			a = a | (a >> 2);
			a = a | (a >> 4);
			a = a | (a >> 8);
			a = a | (a >> 16);
			a = a | (a >> 32);
			result.size = a + 1;
		}

		result.buffer = std::malloc(sizeof(T) * result.size);
		return result;
	};

	// Maybe we should return bool to say if we had to resize or not
	void add(T element)
	{
		if(length + 1 > size){
			size = size * 2;
			buffer = reallocarray(buffer, size, sizeof(T));
		}
		buffer[length] = element;
		length++;
	};
	T& operator[](s64 index)
	{
		assert(index >= length ||
			   index < 0 &&
			   "index is outofbounds");

		return buffer[index];
	};
	// @TODO: add function remove(s64 index);
	// @TODO: add support for range based forloops

	void detroy()
	{
		length = 0;
		size = 0;
		free(buffer);
		buffer = nullptr;
	}
};

#endif

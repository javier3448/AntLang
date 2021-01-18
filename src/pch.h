#ifndef PCH_H
#define PCH_H

//FAKE PRECOMPILE HEADER, I dont know if we will even use precompile headers,
//But still we need a header for basically every other file with some usefull 
//definitions and includes

#include <cstdint> // int8_t, etc
#include <cstring> // malloc, realloc, free
#include <cstdlib>
#include <cstdio>
#include <optional>
#include <assert.h>

//For printf debugging:
#include <string>
#include <iostream>

using std::cout;
using std::endl;

//TODO?: macro o algo para hacer un println sencillo para debugging

using std::malloc;
using std::free;

// Numbers from Dmitriy Compiler Programming

typedef int8_t  s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

// The size of float and double is plataform dependent I guess... And I couldnt
// easily find a way to do these typedef is a non plataform dependent. Who cares
typedef float f32;
typedef double f64;

#endif

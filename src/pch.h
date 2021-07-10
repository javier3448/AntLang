#ifndef PCH_H
#define PCH_H

//FAKE PRECOMPILE HEADER, I dont know if we will even use precompile headers,
//But still we need a header for basically every other file with some usefull 
//definitions and includes

#include <cstring> 
#include <cstdlib> // malloc, realloc, free ...
#include <cstdio>
#include <assert.h>

//For printf debugging:
#include <string>
#include <iostream>

#include "typedefs.h"

#include "./Util/optional.h"
#include "./Util/tupple2.h"
#include "./Util/tupple3.h"

using std::cout;
using std::endl;

// @TODO? add macro or something for a simple println for debugging

// Stolen macros

// Only works on arrays with static sizes obviously, still extremely useful
#define ArrayCount(a) (sizeof(a)/sizeof(*(a)))


using std::malloc;
using std::free;



#endif

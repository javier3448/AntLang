#ifndef OPTINAL_H
#define OPTINAL_H

#include "../typedefs.h"

template<typename T>
struct Optional{
	bool hasValue;
	T val;

	// we want to be able to do if(optional) ... but overwritting the bool operator
	// allows for some weird conversions like int a = optional;
	// but the 'canonical' way of achieving if(optional) ... is very complicated
	// so I won't implement it at least for now. (google: 'the safe bool idiom'
	// for more info)
	// there is also some weird shit going on with the 'explicit' keyword, so I
	// dont know what the hell is going on anymore :/

	static Optional make_empty()
	{
		Optional result;
		result.hasValue = false;
		return result;
	};
	static Optional make(T val)
	{
		return Optional { .hasValue = true, .val = val};
	};

	operator bool()
	{
		return hasValue;
	}

	// @TODO: overwrite the . and -> operators? I dont know if it is possible or
	// advisable

};

#endif

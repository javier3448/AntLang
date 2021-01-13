#ifndef MYSTRING_H
#define MYSTRING_H

#include "pch.h"

// A extremely simple string implemantion. Doesnt resize, cant append other 
// string to it, doesnt deallocate itself
// basically a null terminated c string (char*) with a s64 with its length 
struct MyString
{
    // @[!]
    // The null termination is just ther for better compatibility with all the c 
    // stuff (sprintf in particular). Always prefer to traverse the string using
    // the size and not the null termination

    s64 length = 0;

    //Has to be in heap, or at least it has to work with free, this goes against
    //our idea of being more concious about mem allocation, better later on we
    //can pass a allocator or god knows what? :/
    char* buffer = nullptr;

    char& operator[] (s64 index);

    //copies the entire string does another malloc, very inefficient, should only
    //be used when debugging and when we just want to get something up and
    //running with some other library or something
    //It also sabotages our compilation time (I think)
    std::string toStdString();

    //intended to be used with a string literal. Does malloc
    static MyString make(const char* c_string);

    //just concats both c strings into a new malloced char*
    static MyString make(const char* c_string1, const char* c_string2);

    //mallocs
    static MyString make(int size, char* buffer);

    MyString clone();

    //not a destructor because we dont want to deal with 'copy constructor
    //operator' doing expensive copies when we want to fucking return by value
    //@TODO: find out if that concern is actually valid!!!!
    //[!]Must be called when we are done with that buffer, otherwise we leak mem!
    //Does not leave the struct in a valid state! i.e. doesnt not set size and
    //buffer to 0 after freeing buffer!
    void destroy();
};

std::ostream& operator<<(std::ostream& stream, MyString& myString);

#endif // MYSTRING_H

#ifndef MYSTRING_H
#define MYSTRING_H

#include "pch.h"

// @Improvement?: for better compatibility with all the c stuff (sprintf 
// in particular) it might be wise to modify this struct so the buffer has 
// the null terminated character, its just one fucking byte at the end of the
// day, I dont want to implement my own sprintf just because of 1 byte 

// A extremely simple string implemantion. Doesnt resize, cant append other 
// string to it, doesnt deallocate itself
// basically a non null terminated c string (char*)

//[!!!!] For now this string DOESNT automatically deallocate its heap pointer
//(buffer) because I am affraid that the copy constructor and assignment will
//get called a bunch without us noticing and at that point we might as well just
//use std::string
//So, for now, we must deallocate the string manually with .destroy
struct MyString
{
    //@Improvement?: Aqui este podria ser privado y todo eso.
    //               por ahora asi que se quede
    //please please do not change it
    //'semantically' it should be unsigned but I am affraid of weird UB so for
    //now this is fine
    s64 length = 0;

    //Has to be in heap, or at least it has to work with free, this goes against
    //our idea of being more concious about mem allocation, better later on we
    //can pass a allocator or god knows what? :/
    //not null terminated buffer[size] is end of string (non inclusive)
    char* buffer = nullptr;

    char& operator[] (s64 index);

    //copies the entire string does another malloc, very inefficient, should only
    //be used when debugging and when we just want to get something up and
    //running with some other library or something
    //It also sabotages our compilation time (I think)
    std::string toStdString();

    //If we fucking use = in this guy we are fucked for ever because of the
    //destructor
    //TODO: 'user define' the

    //intended to be used with a string literal. Does malloc
    static MyString make(const char* c_string);

    //just concats both c strings into one
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

//We copied from cherno. I dont know why it takes a reference and not a pointer?
std::ostream& operator<<(std::ostream& stream, MyString& myString);

#endif // MYSTRING_H

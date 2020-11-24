#ifndef MYSTRING_H
#define MYSTRING_H

#include "pch.h"

// About wanting to use constructors/destructors in this struct
// it makes a lot of sence for MyString to have a destructor so we are fucked now
// MyString a("hello");
// MyString b = a; //when a and b go out of scope we will double free a char*
// ---(an option would be to just call something str.myFree manually )---

// I would like something like this:
// ...
// MyString b = a.clone;
// //MyString b = a; and this is a not allowed
// neither is this allowed:
// b = a;
// but this is:
// auto& b = a;
// I am scared because there seem to be multiple '=' operators
// and because cppreference says:
// "Because C++ copies and copy-assigns objects of user-defined
// types in various situations (passing/**returning** by value, manipulating
// a container, etc), these special member functions will be called, if
// accessible, and if they are not user-defined, they are implicitly-defined
// by the compiler."

//size = 0 means empty string regardless of the value of buffer.
//We dont warranty that if size=0 then buffer=nullptr
//@Volitile: MyString class def
//@Possible leaks:
//@WARNING:
//@[!!!!] For now this string DOESNT automatically deallocate its heap pointer
//(buffer) because I am affraid that the copy constructor and assignment will
//get called a bunch without us noticing and at that point we might as well just
//use std::string
//So, for now, we must deallocate the string manually with .clear
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
    MyString(const char* c_string);

    //mallocs
    MyString(int size, char* buffer);

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

#include "mystring.h"

#include <cstring>

//@Improvement: if this intended for constructing a MyString from a string
//literal there should be a way to pass the size so we dont have to iterate thru
//the c_string 2 times
MyString MyString::make(const char* c_string)
{
    MyString retString;
    retString.length = std::strlen(c_string);
    retString.buffer = new char[retString.length + 1];
    std::memcpy(retString.buffer, c_string, retString.length);
    retString.buffer[retString.length] = 0;

    return retString;
}

MyString MyString::make(const char* c_string1, const char* c_string2)
{
    MyString retString;
    s64 length1 = std::strlen(c_string1);
    s64 length2 = std::strlen(c_string2);
    retString.length = length1 + length2;
    retString.buffer = new char[retString.length + 1];
    std::memcpy(retString.buffer, c_string1, length1);
    std::memcpy(retString.buffer + length1, c_string2, length2);
    retString.buffer[retString.length] = 0;

    return retString;
}

MyString MyString::make(int length, char* buffer)
{
    MyString retString;
    retString.length = length;
    retString.buffer = (char*)malloc(retString.length + 1);
    std::memcpy(retString.buffer, buffer, retString.length);
    retString.buffer[retString.length] = 0;

    return retString;
}

char& MyString::operator[](s64 index)
{
    return this->buffer[index];
}

std::string MyString::toStdString(){
    return std::string(this->buffer, this->length);
}

MyString MyString::clone()
{
    return MyString::make(this->length, this->buffer);
}

void MyString::destroy()
{
    //unnecessary if but I like it better
    if(this->buffer)
        free(buffer);
}

std::ostream& operator<<(std::ostream& stream, MyString& myString)
{
    return stream.write(myString.buffer, myString.length);
}

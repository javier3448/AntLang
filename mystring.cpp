#include "mystring.h"

#include <cstring>

//@Improvement: if this intended for constructing a MyString from a string
//literal there should be a way to pass the size so we dont have to iterate thru
//the c_string 2 times
MyString::MyString(const char* c_string)
{
    this->length = std::strlen(c_string);
    this->buffer = new char[this->length];
    std::memcpy(buffer, c_string, this->length);
}

MyString::MyString(int length, char* buffer)
{
    this->length = length;
    this->buffer = (char*)malloc(this->length);
    std::memcpy(this->buffer, buffer, this->length);
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
    return MyString(this->length, this->buffer);
}

void MyString::destroy()
{
    //unnecessary if but I like it better
    if(this->buffer)
        free(buffer);
}

std::ostream& operator<<(std::ostream& stream, MyString& myString){
    return stream.write(myString.buffer, myString.length);
}

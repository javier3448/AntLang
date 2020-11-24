#include "pch.h"

#include "lexer.h"

//@Temp debug
#include "mystring.h"

//@Decision: we will *try* to initialize to 0 by default and have that mean
//something useful, because I heard that initializing to 0 is quite free

//@Decision: we will use malloc and free unless the thing we are allocation
//explecitely uses constructor/destructor

//@Decision: we will use cout over printf because it easier to work with all
//kinds of types, I dont like having to write the string literal for printf
//and we will be printing primiraly for debugging purposes
//constructor/destructor

//@Decision: we will not use std::string for anything other than debugging
//because I want to eventually be able to be smarter about the way I allocate
//strings

//@Decision: we will preferably use references over pointers,
//because I want to eventually be able to be smarter about the way I allocate
//strings

int main()
{
    restart:
    auto result =  Lexer::init("/home/javier/Downloads/test/test.txt");
    if(result.has_value()){
        cout << result.value() << endl;
        exit(1);
    }

    cout << "=======LEXING=======" << endl;

    auto token = Lexer::getNextToken();
    while(true){
        switch (token.kind) {
            case Identifier:
            {
                cout << "Identifier: " << token.string << endl;
            }break;
            case Integer:
            {
                cout << "integer: " << token.integer << endl;
            }break;
            case Real:
            {
                cout << "Real: " << token.string << endl;
            }break;
            case Error:
            {
                cout << "Error: " << token.string << endl;
            }break;
            case Plus:
            {
                cout << "Plus: +" << endl;
            }break;
            case Minus:
            {
                cout << "Minus: -" << endl;
            }break;
            case Eof:
            {
                cout << "Eof: EOF"  << endl;
                goto break_while;
            }break;
        }
        token = Lexer::getNextToken();
    }
    break_while:

    //@bodge as fuck just for qd testing:
    std::cin.get();
    goto restart;

    return 0;
}

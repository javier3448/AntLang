#include "pch.h"

#include "./Parser/parser.h"
#include "./Parser/lexer.h"
#include "./Parser/grapher.h"

//@debug: just for `errs()` to dump the function
//@bodge: I dont know how has the definition for errs so I am just copying the
//entire thing :(

//@Decision: we will *try* to initialize to 0 by default and have that mean
//something useful, because I heard that initializing to 0 is quite free

//@Decision: we will use malloc and free unless the thing we are allocation
//explecitely uses constructor/destructor

//@Decision: we will use cout over printf because it easier to work with all
//kinds of types, I dont like having to write the string literal for printf
//and we will be printing primiraly for debugging purposes
//constructor/destructor
//@Decision: we will not use std::string for anything other than debugging
//because I want to}eventually be able to be smarter about the way I allocate
//strings

//@Decision: we will preferably use references over pointers,
//because I want to eventually be able to be smarter about the way I allocate
//strings


int main()
{
    //restart:
    Lexer::init("../../src/TestFiles/new_parser_stuff_for_playing_around_with_typechecking.test");

    cout << "=======LEXING=======" << endl;

    //@REMEMBER: right now we are leaking the myString of every single token
    //this whole function is just to qd test the lexer
    auto token = Lexer::getNextToken();

    while(true){
        switch (token.kind) {
            case Identifier:
            {
                cout << "Identifier: " << token.string << endl;
            }break;
            case Number:
            {
                cout << "Number: " << token.string << endl;
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
            case LeftParen:
            {
                cout << "("  << endl;
            }break;
            case RightParen:
            {
                cout << ")"  << endl;
            }break;
            case Division:
            {
                cout << "/"  << endl;
            }break;
            case Multiplication:
            {
                cout << "*"  << endl;
            }break;
            case Key_u64:
            {
                cout << "u64" << endl;
            }break;
            case Key_s64:
            {
                cout << "s64" << endl;
            }break;
            case Key_u32:
            {
                cout << "u32" << endl;
            }break;
            case Key_s32:
            {
                cout << "s32" << endl;
            }break;
            case Key_u16:
            {
                cout << "u16" << endl;
            }break;
            case Key_s16:
            {
                cout << "s16" << endl;
            }break;
            case Key_u8:
            {
                cout << "u8:" << endl;
            }break;
            case Key_s8:
            {
                cout << "s8:" << endl;
            }break;
            case Key_float32:
            {
                cout << "float32" << endl;
            }break;
            case Key_float64:
            {
                cout << "float64" << endl;
            }break;
            case Key_cast:
            {
                cout << "cast" << endl;
            }break;
            case Less:
            {
                cout << "<" << endl;
            }break;
            case Greater:
            {
                cout << ">" << endl;
            }break;
            default:
                assert(false);
        }
        token = Lexer::getNextToken();
    }
    break_while:

    //@bodge as fuck just for qd testing:
    // std::cin.get();
    // goto restart;

    return 0;
}

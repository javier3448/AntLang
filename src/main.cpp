#include "pch.h"

//@Temp debug
#include <unistd.h>

#include "mystring.h"
#include "Parser/lexer.h"
#include "Parser/parser.h"
#include "Parser/grapher.h"

#include "llvm/IR/Verifier.h"

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

//@TODO: poner esto en un mejor lugar. Me da cosa borrarlo porque talvez nos
//sirva pero por ahora definitivamente no lo vamos a usar
int lexerTester()
{
    assert(false);

    restart:
    auto result = Lexer::init("../AntLang/TestFiles/test.txt");
    if(result.has_value()){
        cout << result.value() << endl;
        exit(1);
    }

    cout << "=======LEXING=======" << endl;

    Lexer::peekToken(15);
    //@REMEMBER: right now we are leaking the myString of every single token
    //this whole contraption is just to qd test the lexer
    auto token = Lexer::getNextToken();

    //@debug
    s64 counter = 0;
    while(true){
        counter++;
        if(counter == 32){
            Lexer::peekToken(15);
            counter = 0;
        }
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
            default:
                assert(false);
        }
        token = Lexer::getNextToken();
    }
    break_while:

    //@bodge as fuck just for qd testing:
    std::cin.get();
    goto restart;

    return 0;
}

int main()
{
    auto result = Lexer::init("../AntLang/TestFiles/test.txt");
    if(result.has_value()){
        cout << result.value() << endl;
        exit(1);
    }

    auto expr = Parser::parseExpression();

    auto graphvizCode = "digraph G {\n" +  Grapher::graphExpression(expr).code  + "\n}\n";


    //@DEBUG: just to generate save and compile a .dot file
    std::FILE* f = std::fopen("../AntLang/TestFiles/Graphviz/test.dot", "wb");

    if(f == nullptr){
        cout << "Couldnt generate the test graphviz image: n";
        cout << strerror(errno) << endl;
        exit(1);
    }
    //@TODO: report error is something goes wrong
    fprintf(f, "%s", graphvizCode.c_str());
    fclose(f);

    auto compileDot = "dot -Tpng "
                      "../AntLang/TestFiles/Graphviz/test.dot "
                      "-o "
                      "../AntLang/TestFiles/Graphviz/test.png";
    auto displayImage = "nohup display ../AntLang/TestFiles/Graphviz/test.png";

    system(compileDot);
    system(displayImage);

    return 0;
}

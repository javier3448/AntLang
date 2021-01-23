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
    Lexer::init("../../src/TestFiles/new_parser_stuff_for_playing_around_with_typechecking.test");

    auto expr = Parser::parseExpression();

    auto graphvizCode = "digraph G {\n" +  Grapher::graphExpression(expr).code  + "\n}\n";

    //@DEBUG: just to generate save and compile a .dot file
    std::FILE* f = std::fopen("../../src/TestFiles/Graphviz/test.dot", "wb");

    if(f == nullptr){
        cout << "Couldnt generate the test graphviz image: n";
        cout << strerror(errno) << endl;
        exit(1);
    }
    //@TODO: report error if something goes wrong
    fprintf(f, "%s", graphvizCode.c_str());
    fclose(f);

    auto compileDot = "dot -Tpng "
                      "../../src/TestFiles/Graphviz/test.dot "
                      "-o "
                      "../../src/TestFiles/Graphviz/test.png";
    auto displayImage = "nohup display ../../src/TestFiles/Graphviz/test.png &";

    system(compileDot);
    system(displayImage);

    return 0;
}

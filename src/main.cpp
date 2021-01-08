#include "pch.h"

#include "./AntLlvmGen/antLlvmGen.h"
#include "./Parser/parser.h"
#include "./Parser/lexer.h"

//@debug: just for `errs()` to dump the function
//@bodge: I dont know how has the definition for errs so I am just copying the
//entire thing :(
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/IRBuilder.h"

#include "llvm/IR/Constants.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Type.h"
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

int main()
{
    cout << "Hello there" << endl;

    auto result = Lexer::init("../../src/TestFiles/test.txt");
    if(result.has_value()){
        cout << result.value() << endl;
        exit(1);
    }

    auto expr = Parser::parseExpression();

    AntLlvmGen::init();
    auto mainFunc = AntLlvmGen::compileTopLevelExpression(expr);

    if(mainFunc == nullptr){
    	cout << "null returned" << endl;
    }

    return 0;
}

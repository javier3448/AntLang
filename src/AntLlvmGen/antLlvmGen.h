// WE WILL WORK WITH Qbe UNTIL WE HAVE A SOMEWHAT COHESIVE LANG
// WE COMMENT IT ALL BECAUSE IT WAS RUINING OUR COMPILE TIMES

// #ifndef ANTLLVMGEN_H
// #define ANTLLVMGEN_H

// #include <map>


// #include "../pch.h"
// #include "../Parser/astexpression.h"

// //LLVM stuff:
// #include "llvm/IR/Value.h"
// #include "llvm/IR/Function.h"

// // @TERMINOLOGY: in all the 'codebase' gen = generator. ... obvs



// // @BIG IMPROVEMENT: for now we just assert(false) with an error message if 
// // something goes wrong in this llvmCodeGen stage. We need a much more robust 
// // way of communicating to the programmer what went wrong

// // @TEMP:
// // @KALEIDOSCOPE NOTES:
// // In kaleidoscope all the .codeGen stuff return an llvm Value
// // Value is the class used to represent a SSA register of SSA Value


// namespace AntLlvmGen
// {
// 	void init();
// 	llvm::Function* compileTopLevelExpression(AstExpression* astExpr);
// 	llvm::Value* compileExpression(AstExpression* astExpr);
// 	llvm::Value* compileBinaryExpression(BinaryExpressionForm* biExpr);
// }

// #endif
// WE WILL WORK WITH Qbe UNTIL WE HAVE A SOMEWHAT COHESIVE LANG
// WE COMMENT IT ALL BECAUSE IT WAS RUINING OUR COMPILE TIMES

// #include "./antLlvmGen.h" 

// // LLVM stuff
// #include "llvm/IR/LLVMContext.h"
// #include "llvm/IR/Module.h"
// #include "llvm/IR/IRBuilder.h"

// #include "llvm/IR/Constants.h"
// #include "llvm/IR/BasicBlock.h"
// #include "llvm/IR/Type.h"
// #include "llvm/IR/Verifier.h"

// using namespace llvm;

// // @IMPROVEMENT?: put all the global state inside a struct or something
// // @IMPROVEMENT: I like to put all the var declarations in the .h even if they
// // are not public, but c++ doesnt like that and idfk why :(
// // struct GenState {
//     // "TheContext is an opaque object that owns a lot of core LLVM data 
//     // structures, such as the type and constant value tables. We don’t need to 
//     // understand it in detail, we just need a single instance to pass into APIs
//     // that require it."  :/
//     static std::unique_ptr<LLVMContext> theContext;
//     static std::unique_ptr<IRBuilder<>> builder;
//     static std::unique_ptr<Module> theModule;
// //};

// void AntLlvmGen::init()
// {
//     theContext = std::make_unique<LLVMContext>();
//     theModule = std::make_unique<Module>("my cool jit", *theContext);
//     builder = std::make_unique<IRBuilder<>>(*theContext);
// }

// // @debug?:
// // entry
// // just because I cant print the IRBuilder but I can dump a function
// // mostly copy pasted from FunctionAST::codegen() kaleidoscope chapter 3 code 
// // and from PrototypeAST::codegen()
// Function* AntLlvmGen::compileTopLevelExpression(AstExpression* astExpr)
// {
//     std::vector<Type*>ParamTypes = std::vector<Type*>();
//     FunctionType *FT = FunctionType::get(Type::getDoubleTy(*theContext), ParamTypes, false);

//     Function *theFunction = Function::Create(FT, Function::ExternalLinkage, "main", theModule.get());

//     // Create a new basic block to start insertion into.
//     BasicBlock *BB = BasicBlock::Create(*theContext, "entry", theFunction);
//     builder->SetInsertPoint(BB);

//     Value *retVal = compileExpression(astExpr);

//     // Finish off the function.
//     builder->CreateRet(retVal);

//     // Validate the generated code, checking for consistency.
//     verifyFunction(*theFunction);

//     theFunction->print(errs());

//     return theFunction;
// }

// // who the hell 'owns' the Value* we are returning??
// Value* AntLlvmGen::compileExpression(AstExpression* astExpr)
// {

//     switch(astExpr->kind){
//         case AstExpressionKind::NumberLiteral:
//         {
//             // @debug:
//             cout << "compiling expression kind: IntLiteral" << endl;
//             // @BIG BODGE:
//             // the casting to double. Even tho our parser only parses integers,
//             // everything is a float64 in the eyes of our generated llvm ir

//             // @Improvement: I think LLVM provides a way to instantiate an APFloat
//             // from a string. If so, use that
//             return ConstantFP::get(*theContext, APFloat(std::stod(astExpr->numberLiteral.string.toStdString())));
//         }break;

//         case AstExpressionKind::BinaryExpression:
//         {
//             // @debug:
//             cout << "compiling expression kind: BiExpr" << endl;
//             return compileBinaryExpression(&astExpr->binaryForm);
//         }break;
//         default:
//         assert(false); 
//     }
// }

// Value* AntLlvmGen::compileBinaryExpression(BinaryExpressionForm* biExpr)
// {
//     auto leftVal = compileExpression(biExpr->left);
//     auto rightVal = compileExpression(biExpr->right);

//     // @Notice: how we can add names to the newly generated SSA registers
//     switch(biExpr->_operator.kind){
//         case TokenKind::Plus:
//         {
//             return builder->CreateFAdd(leftVal, rightVal, "addtmp");
//         }break;

//         case TokenKind::Minus:
//         {
//             return builder->CreateFSub(leftVal, rightVal, "subtmp");
//         }break;

//         case TokenKind::Division:
//         {
//             return builder->CreateFDiv(leftVal, rightVal, "divtmp");
//         }break;

//         case TokenKind::Multiplication:
//         {
//             return builder->CreateFMul(leftVal, rightVal, "multmp");
//         }break;
//         default:
//         assert(false);
//     }
// }

#include "./antQbeGen.h" 

#include "./qbeInstruction.h" 
#include "./qbeInstructionBuilder.h" 

QbeFunction AntQbeGen::mainFunction;

void AntQbeGen::init()
{
    //TODO: clear the qbeDefsBuffer 
}

void AntQbeGen::compileTopLevelExpression(AstExpression* expr)
{
    mainFunction.instructions.clear();
    mainFunction.returnType = QbeTempType::qbeWord;
    mainFunction.params.clear();

    compileExpression(expr);

    // @BIG TODO: put the instruction building in functions
    QbeInstruction retIns = {
        .kind = QbeInstructionKind::RetKind,
        .retIns = {
            .hasRetValue = true,
            .retValue = {
                .kind = ConstantKind,
                .constant = 0
            }
        }
    };
    mainFunction.instructions.push_back(retIns);
}

QbeOperand getNextTemp(const char* name)
{
    static s32 counter = 1;

    char counterStr[9];

    sprintf(counterStr, "%x", counter);

    counter++;
    return QbeOperand { 
        .kind = QbeOperandKind::TempKind, 
        .temp = {
            .type = QbeTempType::qbeDouble,
            .name = MyString::make(name, counterStr),
        } 
    };
}

// who the hell 'owns' the Value* we are returning??
QbeOperand AntQbeGen::compileExpression(AstExpression* astExpr)
{
    switch(astExpr->kind){
        case AstExpressionKind::IntegerLiteral:
        {
            return QbeOperand{
                .kind = QbeOperandKind::ConstantKind,
                .constant = (double) astExpr->intLiteral.integer
            };
        }break;

        case AstExpressionKind::BinaryExpression:
        {
            return compileBinaryExpression(&astExpr->binaryForm);
        }break;
        default:
        assert(false); 
    }
}

QbeOperand AntQbeGen::compileBinaryExpression(BinaryExpressionForm* biExpr)
{
    auto leftVal = compileExpression(biExpr->left);
    auto rightVal = compileExpression(biExpr->right);

    // @Notice: how we can add names to the newly generated SSA registers
    switch(biExpr->_operator.kind){
        case TokenKind::Plus:
        {
            auto tempResult = getNextTemp("add");
            mainFunction.instructions.push_back(AntQbeInstructionBuilder::add(QbeTempType::qbeDouble, tempResult.temp, leftVal, rightVal));
            return tempResult;
        }break;

        case TokenKind::Minus:
        {
            auto tempResult = getNextTemp("sub");
            mainFunction.instructions.push_back(AntQbeInstructionBuilder::sub(QbeTempType::qbeDouble, tempResult.temp, leftVal, rightVal));
            return tempResult;
        }break;

        case TokenKind::Division:
        {
            auto tempResult = getNextTemp("div");
            mainFunction.instructions.push_back(AntQbeInstructionBuilder::div(QbeTempType::qbeDouble, tempResult.temp, leftVal, rightVal));
            return tempResult;
        }break;

        case TokenKind::Multiplication:
        {
            auto tempResult = getNextTemp("mul");
            mainFunction.instructions.push_back(AntQbeInstructionBuilder::mul(QbeTempType::qbeDouble, tempResult.temp, leftVal, rightVal));
            return tempResult;
        }break;
        default:
        assert(false);
    }
}

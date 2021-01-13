#include "./antQbeGen.h" 

#include "./qbeBuilder.h" 
#include "./qbeBuffer.h" 

QbeBuffer qbeBuffer = { .length = 0, .size = 0, .buffer = nullptr };

//@Improvement? honestly qbeBuffer could be a globa absolutely everyone
//uses, instead of passing a pointer to the qbeBuilder functions

// FOR NOW IT CAN ONLY BE CALLED ONCE, OTHERWISE WE MIGHT LEAK MEMORY
void AntQbeGen::init()
{
    qbeBuffer = QbeBuffer::make();
}

void AntQbeGen::compileTopLevelExpression(AstExpression* expr)
{
    qbeBuffer.append("function w $main() {\n"
                     "@start\n");

    compileExpression(expr);

    QbeOperand zero = { .kind = QbeOperandKind::ConstantKind, .ulong_constant = 0 };
    QbeBuilder::nonVoidRet(&qbeBuffer, &zero);

    qbeBuffer.append("}");
}

// asserts that the first char of c_string is '%'
// @TODO: after you add a constant with the maximum tempName length.
//        let c_string be 6 or less chars
// @Important:
// c_string can only have at most 5 chars
// we implement that so the name of any given temp in the code we generate has a 
// known maximum number of chars, This will help other parts of the AntQbeGen 
// code avoid mallocs for 'ephemeral' strings. We can allocate a fixed size buffer 
// in the stack instead
// Its worth mentioning that most of the time we require the ephemeral
// strings to use sprintf. If we could program an sprintf that directly writes to  
// the QbeBuffer while being mindful of resizing, we wouldnt need to know the 
// maximum length of any given temp name
// @Improvement: define the maximum lenght of a temp name in a constant
QbeOperand getNextTemp(const char* c_string)
{
    static u64 counter = 1;

    assert(strlen(c_string) < 6);
    assert(c_string[0] == '%');

    char counterStr[18];
    auto err = snprintf(counterStr, sizeof counterStr, "_%lx", counter);
    assert(err > 0);
    assert(err <= (s64) sizeof counterStr);
    //@Volatile the maximum size of temp is 5 + 17 + 1(null termination)
    //%aaaaa

    counter++;
    return QbeOperand { 
        .kind = QbeOperandKind::TempKind, 
        .temp = {
            .type = QbeTempType::qbeDouble,
            .name = MyString::make(c_string, counterStr),
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
                .double_constant = (double) astExpr->intLiteral.integer
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
            auto tempResult = getNextTemp("%add");
            QbeBuilder::add(&qbeBuffer, &(tempResult.temp), QbeTempType::qbeDouble, &leftVal, &rightVal);
            return tempResult;
        }break;

        case TokenKind::Minus:
        {
            auto tempResult = getNextTemp("%sub");
            QbeBuilder::sub(&qbeBuffer, &(tempResult.temp), QbeTempType::qbeDouble, &leftVal, &rightVal);
            return tempResult;
        }break;

        case TokenKind::Division:
        {
            auto tempResult = getNextTemp("%div");
            QbeBuilder::div(&qbeBuffer, &(tempResult.temp), QbeTempType::qbeDouble, &leftVal, &rightVal);
            return tempResult;
        }break;

        case TokenKind::Multiplication:
        {
            auto tempResult = getNextTemp("%mul");
            QbeBuilder::mul(&qbeBuffer, &(tempResult.temp), QbeTempType::qbeDouble, &leftVal, &rightVal);
            return tempResult;
        }break;
        default:
        assert(false);
    }
}

#include "./antQbeGen.h" 

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
    qbeBuffer.write_NonVoidRet(&zero);

    qbeBuffer.append("}");
}

// who the hell 'owns' the Value* we are returning??
QbeOperand AntQbeGen::compileExpression(AstExpression* astExpr)
{
    switch(astExpr->kind){
        case AstExpressionKind::NumberLiteral:
        {
            return QbeOperand{
                .kind = QbeOperandKind::ConstantKind,
                // @TEMP:
                // @NOCHECKIN:
                //.double_constant = (double) astExpr->numberLiteral.string
                .double_constant = 0
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

    // WE CHECK IF WE CAN DO CONSTANT FOLDING
    if(leftVal.kind == QbeOperandKind::ConstantKind
        &&
       rightVal.kind == QbeOperandKind::ConstantKind)
    {
        // @BAD?: I want the numeric constants to be 'typeless', somewhat similar 
        // to what golang has. For now the strategy we came up with is to
        // implement that *requires* us to do constant folding and carry all 
        // possible results in the constant result. It seems lame that a highlevel
        // detail of the language depends on constant folding but it will work for now
        //Then we can do the constant folding
        
        // TODO: We need to change the lexer so a number token returns a string
        // or something more robust that just a float 64. 
        assert(false);
    }
    else{
        // @Notice: how we can add names to the newly generated SSA registers
        switch(biExpr->_operator.kind){
            case TokenKind::Plus:
            {
                auto tempResult = getNextTemp("%add");
                qbeBuffer.write_Add(&(tempResult.temp), QbeTempType::qbeDouble, &leftVal, &rightVal);
                return tempResult;
            }break;

            case TokenKind::Minus:
            {
                auto tempResult = getNextTemp("%sub");
                qbeBuffer.write_Sub(&(tempResult.temp), QbeTempType::qbeDouble, &leftVal, &rightVal);
                return tempResult;
            }break;

            case TokenKind::Division:
            {
                auto tempResult = getNextTemp("%div");
                qbeBuffer.write_Div(&(tempResult.temp), QbeTempType::qbeDouble, &leftVal, &rightVal);
                return tempResult;
            }break;

            case TokenKind::Multiplication:
            {
                auto tempResult = getNextTemp("%mul");
                qbeBuffer.write_Mul(&(tempResult.temp), QbeTempType::qbeDouble, &leftVal, &rightVal);
                return tempResult;
            }break;
            default:
            assert(false);
        }
    }

}

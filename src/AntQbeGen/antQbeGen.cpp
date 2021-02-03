#include "./antQbeGen.h" 

#include "./qbeBuffer.h" 

QbeBuffer qbeBuffer = { .length = 0, .size = 0, .buffer = nullptr };

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

QbeOperand AntQbeGen::compileExpression(AstExpression* astExpr)
{
    switch(astExpr->kind){
        case AstExpressionKind::NumberLiteralKind:
        {
            return QbeOperand{
                .kind = QbeOperandKind::ConstantKind,
                // @TODO when we come back to code gen
                // @BIG TEMP:
                //.double_constant = (double) astExpr->numberLiteral.string
                .double_constant = 0
            };
        }break;

        case AstExpressionKind::BinaryKind:
        {
            return compileBinaryExpression(&astExpr->binaryForm);
        }break;
        default:
        assert(false); 
    }
}

QbeOperand AntQbeGen::compileBinaryExpression(BinaryForm* biExpr)
{
    auto leftVal = compileExpression(biExpr->left);
    auto rightVal = compileExpression(biExpr->right);

    // WE CHECK IF WE CAN DO CONSTANT FOLDING
    if(leftVal.kind == QbeOperandKind::ConstantKind
        &&
       rightVal.kind == QbeOperandKind::ConstantKind)
    {
        assert(false);
    }
    else{
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

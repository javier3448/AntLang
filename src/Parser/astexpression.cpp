#include "./astexpression.h"

#include <limits.h>

void AstExpression::makeIntLiteralExpression(Token numberLiteral)
{
    this->kind = AstExpressionKind::NumberLiteral;
    this->numberLiteral = numberLiteral;
    this->hasParenthesis = false;
}

void AstExpression::makeBinaryExpression(AstExpression *left, Token biOperator, AstExpression *right)
{
    this->kind = AstExpressionKind::BinaryExpression;
    this->binaryForm.left = left;
    this->binaryForm._operator = biOperator;
    this->binaryForm.right = right;
    this->hasParenthesis = false;
}


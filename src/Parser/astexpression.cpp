#include "./astexpression.h"

#include <limits.h>

void AstExpression::makeNumberLiteralExpression(Token numberLiteral)
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

void AstExpression::makeCastExpression(Token castKeyword, AstTypeExpression typeExpression, AstExpression *expression)
{
	this->kind = AstExpressionKind::CastExpression;
	this->castForm.typeExpression = typeExpression;
	this->castForm.expression = expression;
}

void AstExpression::makeUnaryExpression(Token _operator, AstExpression *subExpression)
{
	this->kind = AstExpressionKind::UnaryExpression;
	this->unaryForm._operator = _operator;
	this->unaryForm.subExpression = subExpression;
}

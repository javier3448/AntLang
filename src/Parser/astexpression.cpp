#include "./astexpression.h"

#include <limits.h>

void AstExpression::buildNumberLiteralExpression(Token numberLiteral)
{
    this->kind = AstExpressionKind::NumberLiteral;
    this->numberLiteral = numberLiteral;
    this->hasParenthesis = false;
}

void AstExpression::buildBinaryExpression(AstExpression *left, Token biOperator, AstExpression *right)
{
    this->kind = AstExpressionKind::BinaryExpression;
    this->binaryForm.left = left;
    this->binaryForm._operator = biOperator;
    this->binaryForm.right = right;
    this->hasParenthesis = false;
}

void AstExpression::buildCastExpression(Token castKeyword, AstTypeExpression typeExpression, AstExpression *expression)
{
	this->kind = AstExpressionKind::CastExpression;
    this->castForm._operator = castKeyword;
	this->castForm.typeExpression = typeExpression;
	this->castForm.expression = expression;
}

void AstExpression::buildUnaryExpression(Token _operator, AstExpression *subExpression)
{
	this->kind = AstExpressionKind::UnaryExpression;
    this->unaryForm._operator = _operator;
	this->unaryForm._operator = _operator;
	this->unaryForm.subExpression = subExpression;
}

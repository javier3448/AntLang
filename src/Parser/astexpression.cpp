#include "./astexpression.h"

#include <limits.h>

AstExpression* new_NumberLiteralExpression(Token numberLiteral)
{
	auto result = (AstExpression*)malloc(sizeof(AstExpression));
    result->kind = AstExpressionKind::NumberLiteralKind;
    result->numberLiteralForm.number = numberLiteral;
    result->hasParenthesis = false;
    return result;
}

AstExpression* new_IdentifierExpression(Token identifier)
{
	auto result = (AstExpression*)malloc(sizeof(AstExpression));
    result->kind = AstExpressionKind::IdentifierKind;
    result->identifierForm.identifier= identifier;
    result->hasParenthesis = false;
    return result;
}

AstExpression* new_BinaryExpression(AstExpression *left, Token biOperator, AstExpression *right)
{
	auto result = (AstExpression*)malloc(sizeof(AstExpression));
    result->kind = AstExpressionKind::BinaryKind;
    result->binaryForm.left = left;
    result->binaryForm._operator = biOperator;
    result->binaryForm.right = right;
    result->hasParenthesis = false;
    return result;
}

AstExpression* new_CastExpression(Token castKeyword, AstTypeExpression typeExpression, AstExpression *expression)
{
	auto result = (AstExpression*)malloc(sizeof(AstExpression));
	result->kind = AstExpressionKind::CastKind;
    result->castForm._operator = castKeyword;
	result->castForm.typeExpression = typeExpression;
	result->castForm.expression = expression;
	return result;
}

AstExpression* new_UnaryExpression(Token _operator, AstExpression *subExpression)
{
	auto result = (AstExpression*)malloc(sizeof(AstExpression));
	result->kind = AstExpressionKind::UnaryKind;
    result->unaryForm._operator = _operator;
	result->unaryForm._operator = _operator;
	result->unaryForm.subExpression = subExpression;
	return result;
}

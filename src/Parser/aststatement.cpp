#include "aststatement.h"

AstStatement* new_SingleExpressionStatement(AstExpression* singleExpression)
{
	auto result = (AstStatement*)malloc(sizeof(AstStatement));
    result->kind = AstStatementKind::SingleExpressionKind;
    result->singleExpressionForm = singleExpression;
    return result;
}

AstStatement* new_Declaration(AstTypeExpression typeExpr, Token identifier, AstExpression* expression)
{
	auto result = (AstStatement*)malloc(sizeof(AstStatement));
    result->kind = AstStatementKind::DeclarationKind;
    result->declarationForm.typeExpr = typeExpr;
    result->declarationForm.identifier = identifier;
    result->declarationForm.expression = expression;
    return result;
}

AstStatement* new_Assignment(AstExpression* leftExpression, AstExpression* rightExpression)
{
	auto result = (AstStatement*)malloc(sizeof(AstStatement));
    result->kind = AstStatementKind::AssignmentKind;
    result->assignementForm.leftExpression = leftExpression;
    result->assignementForm.rightExpression = rightExpression;
    return result;
}

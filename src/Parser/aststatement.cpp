#include "aststatement.h"

void AstStatement::makeSingleExpressionStatement(AstExpression* singleExpression)
{
	this->kind = AstStatementKind::SingleExpressionKind;
	this->singleExpressionForm = singleExpression;
}

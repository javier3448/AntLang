#include "./parser.h"

//This is throwing linking error, I dont know why and I am very scared.
//There must be something we are not including in cmake (maybe the macros??)
//#include "llvm/ADT/APFloat.h"

#include "./lexer.h"

//@TODO: improve the way we peek and consume tokens. at the very least use better
//names. maybe a different object to peek tokens, kinda like rust does with
//inmutable references? idk. Or maybe consume the token via a pointer
//@idea?
//consume token.... instead of getNextToken

AstExpression *Parser::parseExpression()
{
    //peek token...
    //switch them all and be recursive and all that???
    //lastly do the operator precedence thing where we are 'recurring' back?

    //Token* peekedToken = Lexer::peekToken();

    auto leftExpr = parseMostPrecedentExpression();

    if(isBiOperatorKind(Lexer::peekToken()->kind)){
        auto biOperator = Lexer::getNextToken();

        auto rightExpr = parseExpression();

        auto binaryExpr = (AstExpression*)malloc(sizeof(AstExpression));
        binaryExpr->makeBinaryExpression(leftExpr, biOperator, rightExpr);

        return  applyPrecedenceRules(binaryExpr);
    }
    else{
        return leftExpr;
    }
}


AstExpression *Parser::parseMostPrecedentExpression()
{
    switch (Lexer::peekToken()->kind) {
        case Number:
        {
            auto result = (AstExpression*)malloc(sizeof(AstExpression));
            result->makeIntLiteralExpression(Lexer::getNextToken());

            return result;
        }break;
        case LeftParen:
        {
            //@REMEMBER: to 'consume' the left paren we just peeked before
            //parsing the expression inside
            Lexer::getNextToken();

            AstExpression* result = parseExpression();

            auto peekedToken = Lexer::peekToken();
            if(peekedToken->kind != RightParen){
                //@SERIOUS TODO:
                //Find a much much better way of reporting errors
                cout << "Missing closing parenthesis\n";
                //@debug: I dont want to think about how to report errors and
                //all that right now, so, for now we just fucking crash :/
                assert(false);
            }
            Lexer::getNextToken();

            result->hasParenthesis = true;
            return result;
        }break;
        default:
        {
            //@SERIOUS TODO:
            //Find a much much better way of reporting errors
            cout << "Not a valid token to start expression: " << Lexer::getNextToken().kind << "\n";
            //@debug: I dont want to think about how to report errors and
            //all that right now, so, for now we just fucking crash :/
            assert(false);
        }break;
    }
}

inline s16 getOperatorPrecedence(TokenKind kind)
{
    switch (kind) {
    case Plus:
    case Minus:
        return 110;
    case Division:
    case Multiplication:
        return 120;
    default:
        assert(false && "Binary operator not implemented yet!");
    }
}

inline s16 getPrecedence(AstExpression* astExpression)
{
    if(astExpression->hasParenthesis)
        return INT8_MAX;

    switch (astExpression->kind) {
    case NumberLiteral:
        return INT8_MAX;
    case BinaryExpression:
        return getOperatorPrecedence(astExpression->binaryForm._operator.kind);
    default:
        assert(false && "astExpressionKind not implemented yet!");
    }
}

//TODO: write some of the assumptions we made about the tree to make this algo
//ONLY WORKS FOR BinaryExpressions
AstExpression *Parser::applyPrecedenceRules(AstExpression* binaryExpression)
{
    assert(binaryExpression->kind == BinaryExpression);

    //@[!] we a asume that leftOperand of a binaryExpression will always be
    //infinitely precedent

    auto thisNodePrecedence = getOperatorPrecedence(binaryExpression->binaryForm._operator.kind);
    auto rightChildNodePrecedence = getPrecedence(binaryExpression->binaryForm.right);

    if(thisNodePrecedence > rightChildNodePrecedence){
        //'left rotation'
        auto oldRightChild = binaryExpression->binaryForm.right;

        //For know the only way a we can get inside this 'if' is if the right
        //child is another binaryExpression
        assert(oldRightChild->kind == BinaryExpression);

        binaryExpression->binaryForm.right = oldRightChild->binaryForm.left;

        oldRightChild->binaryForm.left = binaryExpression;

        return oldRightChild;
    }
    else{
        return binaryExpression;
    }


}

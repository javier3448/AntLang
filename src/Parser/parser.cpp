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


// @DANGER: according to our precedence spreadsheet, this is a bunch of baloney
// there should be 'precedence differences' between '.', '*'(dereferencer), cast<type> and so on
// :/ ... I guess the only most precedent expression should be identifier, literals,
// parethesised expr idfk :(
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
        case Key_cast:
        {
            //@REMEMBER: to 'consume' the keyword we just peeked before
            Lexer::getNextToken();

            auto peekedToken = Lexer::peekToken();
            if(peekedToken->kind != TokenKind::Less){
                cout << "Missing opening '<' got: " << peekedToken->stringRepresentation() << "instead \n";
                assert(false);
            }
            Lexer::getNextToken();


            AstTypeExpression typeExpr = parseTypeExpression();

            peekedToken = Lexer::peekToken();
            if(peekedToken->kind != TokenKind::Greater){
                cout << "Missing closing '>' got: " << peekedToken->stringRepresentation() << "instead \n";
                assert(false);
            }
            Lexer::getNextToken();

            AstExpression* expr = parseExpression();

            auto castExpression = (AstExpression*)malloc(sizeof(AstExpression));
            castExpression->makeCastExpression(typeExpr, expr);

            return castExpression;
        }break;
        default:
        {
            //@SERIOUS TODO:
            //Find a much much better way of reporting errors
            auto badToken = Lexer::peekToken();
            cout << "Not a valid token to start expression: " << (s32) badToken->kind << "\n";
            //@debug: I dont want to think about how to report errors and
            //all that right now, so, for now we just fucking crash :/
            assert(false);
        }break;
    }
}

AstTypeExpression Parser::parseTypeExpression()
{
    auto peekedToken = Lexer::peekToken();
    if(peekedToken->kind == TokenKind::Identifier)
    {
        cout << "Custom types not implemented yet!\n";
        assert(false);
    }
    else if(isNativeType(peekedToken->kind))
    {
        AstTypeExpression typeExpr = { ._type = Lexer::getNextToken()};
        return typeExpr;
    }
    cout << "Not a valid typeExpr\n";
    assert(false);
}

inline s16 getOperatorPrecedence(TokenKind kind)
{
    switch (kind) {
    case Or:
        return 30;
    case And:
        return 40;

    case BitOr:
        return 50;
    case BitAnd:
        return 70;

    case EqualEqual:
    case NotEqual:
        return 80;

    case LessEqual:
    case GreaterEqual:
    case Less:
    case Greater:
        return 90;

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
        return INT16_MAX;

    switch (astExpression->kind) {
    case NumberLiteral:
    case CastExpression:
        return INT16_MAX;
    case BinaryExpression:
        return getOperatorPrecedence(astExpression->binaryForm._operator.kind);
    default:
        assert(false && "astExpressionKind not implemented yet!");
    }
}

//TODO: write some of the assumptions we made about the tree to make this algo
//ONLY WORKS FOR BinaryExpressions
//TODO: write a faster ways to solve precedences because this is recursive and
//visits the nodes multiple times
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

        // Super gross and slow, I dont like this solution to precedence rules 
        // anymore
        // binaryExpression now has children (binaryExpr.right = oldRigth.left)
        // that might have lower precedence than itself. So we must check precedences
        // there again
        oldRightChild->binaryForm.left = applyPrecedenceRules(binaryExpression);

        return oldRightChild;
    }
    else{
        return binaryExpression;
    }


}

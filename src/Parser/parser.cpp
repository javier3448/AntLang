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

    auto firstPeekedToken = Lexer::peekToken();
    // special weird case because castExpression is a unaryExpression but the struct
    // it also has typeExpression in its struct
    if(firstPeekedToken->kind == TokenKind::Key_cast)
    {
        auto castKeyword = Lexer::getNextToken();
        auto typeExpr = parseTypeExpression();
        auto subExpr = parseExpression();

        auto castExpr = (AstExpression*)malloc(sizeof(AstExpression));
        castExpr->makeCastExpression(castKeyword, typeExpr, subExpr);

        return applyPrecedenceRules(castExpr);
    }
    else if(isUnaryOperatorKind(firstPeekedToken->kind))
    {
        auto unaryOperator = Lexer::getNextToken();
        auto subExpr = parseExpression();

        auto unaryExpr = (AstExpression*)malloc(sizeof(AstExpression));
        unaryExpr->makeUnaryExpression(unaryOperator, subExpr);

        return applyPrecedenceRules(unaryExpr);
    }
    else //Must be binaryExpr or just 1 mostPrecedenctExpression
    {
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

}


AstExpression *Parser::parseMostPrecedentExpression()
{
    switch (Lexer::peekToken()->kind) {
        case Number:
        {
            auto result = (AstExpression*)malloc(sizeof(AstExpression));
            result->makeNumberLiteralExpression(Lexer::getNextToken());

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
            auto badToken = Lexer::peekToken();
            cout << "Not a valid token to start expression: " << (s32) badToken->kind << "\n";
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

inline s16 getBinaryOperatorPrecedence(TokenKind kind)
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

// I guess they all just happened to be 130 but it wont be like that but I wont 
// remove this code in case I decide to change the precedences
inline s16 getUnaryOperatorPrecedence(TokenKind kind)
{
    switch (kind) {
    case Not:
    case BitNot:
    case Minus:
    case Key_cast:
    case Multiplication:
    case And:
    case Key_sizeof:
        return 130;

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
        return INT16_MAX;
    case CastExpression:
        return getUnaryOperatorPrecedence(astExpression->castForm._operator.kind);
    case UnaryExpression:
        return getUnaryOperatorPrecedence(astExpression->unaryForm._operator.kind);
    case BinaryExpression:
        return getBinaryOperatorPrecedence(astExpression->binaryForm._operator.kind);
    default:
        assert(false && "astExpressionKind not implemented yet!");
    }
}

// @TODO: DONT BE LAZY ACTUALLY THINK ABOUT HOW CAN WE EFFECTIVELY DO THE BRACHING
// NEED FOR (BinaryForm | UnaryForm | CastForm) IN applyPredenceRules, RIGHT NOW
// DO THE TRIPLE SWITCH MORE THAN WE NEED TO, AND WE SEPARATE FUNCTION WHEN WE DONT
// NEED TO

// this is horrible

// This function is only used in applyPrecedence rues
inline AstExpression** getLeftChildOrOnlyChild(AstExpression* expr)
{
    // its ok to use the & in these guys, because expr itself is heap allocated 
    switch(expr->kind){
        case AstExpressionKind::BinaryExpression:
            return &(expr->binaryForm.left);
        case AstExpressionKind::UnaryExpression:
            return &(expr->unaryForm.subExpression);
        case AstExpressionKind::CastExpression:
            return &(expr->castForm.expression);
        default:
            assert(false
                   &&
                   "");
    }
}

//TODO: write a faster ways to solve precedences because this is recursive and
//visits the nodes multiple times
            // Super gross and slow, I dont like this solution to precedence rules 
            // anymore
AstExpression *Parser::applyPrecedenceRules(AstExpression* expression)
{
    if(expression->kind == AstExpressionKind::BinaryExpression)
    {
        auto& binaryExpression = expression;

        auto thisNodePrecedence = getBinaryOperatorPrecedence(binaryExpression->binaryForm._operator.kind);
        auto rightChildNodePrecedence = getPrecedence(binaryExpression->binaryForm.right);

        if(thisNodePrecedence > rightChildNodePrecedence){
            //'left rotation'
            auto oldRightChild = binaryExpression->binaryForm.right;

            AstExpression** leftOrOnlyChildOfRight = getLeftChildOrOnlyChild(oldRightChild);

            binaryExpression->binaryForm.right = *leftOrOnlyChildOfRight;

            // binaryExpression now has children (binaryExpr.right = oldRigth.left)
            // that might have lower precedence than itself. So we must check precedences
            // there again
            *leftOrOnlyChildOfRight =(binaryExpression);

            return oldRightChild;
        }
        else{
            return binaryExpression;
        }
    }
    else if(expression->kind == AstExpressionKind::UnaryExpression)
    {
        auto& unaryExpression = expression;

        auto thisNodePrecedence = getUnaryOperatorPrecedence(unaryExpression->unaryForm._operator.kind);
        auto childPrecedence = getPrecedence(unaryExpression->unaryForm.subExpression);

        if(thisNodePrecedence > childPrecedence){
            //'left rotation'
            auto oldChild = unaryExpression->unaryForm.subExpression;

            AstExpression** leftOrOnlyChildOfChild = getLeftChildOrOnlyChild(oldChild);

            unaryExpression->unaryForm.subExpression = *leftOrOnlyChildOfChild;

            // binaryExpression now has children (binaryExpr.right = oldRigth.left)
            // that might have lower precedence than itself. So we must check precedences
            // there again
            *leftOrOnlyChildOfChild =(unaryExpression);

            return oldChild;
        }
        else{
            return unaryExpression;
        } 
    }
    else if(expression->kind == AstExpressionKind::CastExpression)
    {
        auto& castExpression = expression;

        auto thisNodePrecedence = getUnaryOperatorPrecedence(castExpression->castForm._operator.kind);
        auto childPrecedence = getPrecedence(castExpression->castForm.expression);

        if(thisNodePrecedence > childPrecedence){
            //'left rotation'
            auto oldChild = castExpression->castForm.expression;

            AstExpression** leftOrOnlyChildOfChild = getLeftChildOrOnlyChild(oldChild);

            castExpression->castForm.expression = *leftOrOnlyChildOfChild;

            // binaryExpression now has children (binaryExpr.right = oldRigth.left)
            // that might have lower precedence than itself. So we must check precedences
            // there again
            *leftOrOnlyChildOfChild =(castExpression);

            return oldChild;
        }
        else{
            return castExpression;
        } 
    }
    else
    {
        assert(false && "Expression form not implemented yet in applyPrecedenceRules");
    }



}

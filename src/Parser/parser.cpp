#include "./parser.h"

#include "./lexer.h"

// Only used for the function `demandToken` only works in the context of:
// return the value of the token if the next token is the one we wanted or return
// a pointer to the token that was next and its not the one we wanted.
// @Bad names?
struct PromisedToken{
    bool isCompliant;
    union {
        Token  compliantToken;
        Token* defiantToken;
    };

    operator bool()
    {
        return isCompliant;
    };
};

PromisedToken demandToken(TokenKind tokenKind);

// QdGrammar of Statement at this point:
// Statement = Expression '=' Expression ';' (1)
// Statement = typeExpression ident '=' Expression ';' (2)
// Statement = Expression ';' (3)
AstStatement *Parser::parseStatement()
{
    auto firstPeekedToken = Lexer::peekToken();
    if(firstPeekedToken->kind == TokenKind::Identifier){
        // This branch takes care of the ambiguity

        // We have an ambiguity problem here because the beginning of (2) and (3)
        // can be an identifier, typeExpression can be a custom type and expression 
        // can be something like: `myVariable + 10`

        // if peekAhead(1) is ('<' | ident) then this statement must be (2) (ie. Declaration)
        // else it has to be (1) or (3)

        // That solution is very hairy and it breaks easily if we change the language

        auto secondPeekedToken = Lexer::peekToken(1);

        if(secondPeekedToken->kind == TokenKind::Less || 
           secondPeekedToken->kind == TokenKind::Identifier)
        {
            return parseDeclaration();
        }
        else{
            return parseAssignmentOrSingleExprStatment();
        }
    }
    else if(isNativeType(firstPeekedToken->kind) ||
            firstPeekedToken->kind == TokenKind::Key_auto)
    {
        // Must be declaration statement
        return parseDeclaration();
    }
    else{
        return parseAssignmentOrSingleExprStatment();
    }
}

AstStatement* Parser::parseDeclaration(){
    auto typeExpr = parseTypeExpression();

    auto ident = demandToken(TokenKind::Identifier);
    if(!ident){
        cout << "Not a valid declaration, expected identifier after typeExpr, got" << ident.defiantToken->stringRepresentation() << "\n";
        assert(false);
    }

    auto equals = demandToken(TokenKind::Equal);
    if(!equals){
        cout << "Not a valid declaration, expected '=' after identifier, got " << equals.defiantToken->stringRepresentation() << "\n";
        assert(false);
    }

    auto expr = parseExpression();

    auto semiColon = demandToken(TokenKind::SemiColon);
    if(!semiColon){
        cout << "Not a valid declaration, expected ';' after expression, got " << semiColon.defiantToken->stringRepresentation() << "\n";
        assert(false);
    }

    return new_Declaration(typeExpr, ident.compliantToken, expr);
}

AstStatement* Parser::parseAssignmentOrSingleExprStatment(){
    auto leftExpression = parseExpression();

    auto peekedToken = Lexer::peekToken();
    if(peekedToken->kind == TokenKind::SemiColon){
        Lexer::consumeToken();
        return new_SingleExpressionStatement(leftExpression);
    }
    else if(peekedToken->kind == TokenKind::Equal){
        // It must be assignment
        
        Lexer::consumeToken(); //Consume the '='

        auto rightExpression = parseExpression();

        auto semiColon = demandToken(TokenKind::SemiColon);
        if(!semiColon){
            cout << "Not a valid assignment, expected ';' after expression, got" << semiColon.defiantToken->stringRepresentation() << "\n";
            assert(false);
        }

        return new_Assignment(leftExpression, rightExpression);
    }
    else{
        cout << "Bad statment: expecting ';' or '=' after expression. Got " <<  peekedToken->stringRepresentation() << "instead\n";
        assert(false);
    }
}


AstExpression *Parser::parseExpression()
{
    //we  do the operator precedence tree rotations when we 'recurse back' ~(when we go our way up the recursive stack)

    auto peekedToken = Lexer::peekToken();
    // Special weird case because castExpression is a unaryExpression but the struct
    // and the way we parse it is very different to any other unary expression
    if(peekedToken->kind == TokenKind::Key_cast)
    {
        auto castKeyword = Lexer::consumeToken(); // We consume the 'cast' token

        auto lessToken = demandToken(TokenKind::Less);
        if(!lessToken){
            cout << "Not valid cast expression: expecting '<' got " << lessToken.defiantToken->stringRepresentation() << "\n:";
            assert(false);
        }

        auto typeExpr = parseTypeExpression();

        auto greaterToken = demandToken(TokenKind::Greater);
        if(!greaterToken){
            cout << "Not valid cast expression: expecting '>' got " << greaterToken.defiantToken->stringRepresentation() << "\n:";
            assert(false);
        }

        auto subExpr = parseExpression();

        auto castExpr = new_CastExpression(castKeyword, typeExpr, subExpr);

        return applyPrecedenceRules(castExpr);
    }
    else if(isUnaryOperatorKind(peekedToken->kind))
    {
        auto unaryOperator = Lexer::consumeToken();
        auto subExpr = parseExpression();

        auto unaryExpr = new_UnaryExpression(unaryOperator, subExpr);

        return applyPrecedenceRules(unaryExpr);
    }
    else //Must be binaryExpr or just 1 mostPrecedenctExpression
    {
        auto leftExpr = parseMostPrecedentExpression();

        if(isBiOperatorKind(Lexer::peekToken()->kind)){
            auto biOperator = Lexer::consumeToken();

            auto rightExpr = parseExpression();

            auto binaryExpr = new_BinaryExpression(leftExpr, biOperator, rightExpr);

            return  applyPrecedenceRules(binaryExpr);
        }
        else{
            return leftExpr;
        }
    }

}


AstExpression *Parser::parseMostPrecedentExpression()
{
    auto peekedToken = Lexer::peekToken();
    switch (peekedToken->kind) {
        case Number:
            return new_NumberLiteralExpression(Lexer::consumeToken());

        case Identifier:
            return new_IdentifierExpression(Lexer::consumeToken());

        case LeftParen:
        {
            Lexer::consumeToken(); // consume leftParen token

            AstExpression* result = parseExpression();

            auto rightParen = demandToken(TokenKind::RightParen);
            if(!rightParen){
                cout << "Missing closing parenthesis got " << rightParen.defiantToken->stringRepresentation() << "\n";
                assert(false);
            }

            result->hasParenthesis = true;
            return result;
        }break;
        default:
        {
            cout << "Not a valid token to start expression: " << peekedToken->stringRepresentation() << "\n";
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
        AstTypeExpression typeExpr = { ._type = Lexer::consumeToken()};
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
        assert(false);
    }
}

// I guess the precedence of every unary operator just happens to be 130 
// I wont remove this code in case I decide to change the precedences
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
        assert(false);
    }
}

inline s16 getPrecedence(AstExpression* astExpression)
{
    if(astExpression->hasParenthesis)
        return INT16_MAX;

    switch (astExpression->kind) {
    case NumberLiteralKind:
        return INT16_MAX;
    case CastKind:
        return getUnaryOperatorPrecedence(astExpression->castForm._operator.kind);
    case UnaryKind:
        return getUnaryOperatorPrecedence(astExpression->unaryForm._operator.kind);
    case BinaryKind:
        return getBinaryOperatorPrecedence(astExpression->binaryForm._operator.kind);
    default:
        assert(false && "astExpressionKind not implemented yet!");
    }
}

// @TODO: DONT BE LAZY ACTUALLY THINK ABOUT HOW CAN WE EFFECTIVELY DO THE BRACHING
// NEEDED FOR (BinaryForm | UnaryForm | CastForm) IN applyPredenceRules, RIGHT NOW
// WE DO THE TRIPLE SWITCH MORE THAN WE NEED TO (we just do it in different funcs)

// this is horrible

// This function is only used in applyPrecedence rules
inline AstExpression** getLeftChildOrOnlyChild(AstExpression* expr)
{
    // its ok to use the & in these guys, because expr itself is heap allocated 
    switch(expr->kind){
        case AstExpressionKind::BinaryKind:
            return &(expr->binaryForm.left);
        case AstExpressionKind::UnaryKind:
            return &(expr->unaryForm.subExpression);
        case AstExpressionKind::CastKind:
            return &(expr->castForm.expression);
        default:
            assert(false
                   &&
                   "");
    }
}

// @TODO: write faster ways to solve precedences because this is recursive and
// visits the nodes multiple times
// Super gross and slow, I dont like this solution to precedence rules 
// anymore
AstExpression *Parser::applyPrecedenceRules(AstExpression* expression)
{
    if(expression->kind == AstExpressionKind::BinaryKind)
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
            *leftOrOnlyChildOfRight = applyPrecedenceRules(binaryExpression);

            return oldRightChild;
        }
        else{
            return binaryExpression;
        }
    }
    else if(expression->kind == AstExpressionKind::UnaryKind)
    {
        auto& unaryExpression = expression;

        auto thisNodePrecedence = getUnaryOperatorPrecedence(unaryExpression->unaryForm._operator.kind);
        auto childPrecedence = getPrecedence(unaryExpression->unaryForm.subExpression);

        if(thisNodePrecedence > childPrecedence){
            //'left rotation'
            auto oldChild = unaryExpression->unaryForm.subExpression;

            AstExpression** leftOrOnlyChildOfChild = getLeftChildOrOnlyChild(oldChild);

            unaryExpression->unaryForm.subExpression = *leftOrOnlyChildOfChild;

            // unaryExpression now has children (unary.right = leftOrOnlyChild)
            // that might have lower precedence than itself. So we must check precedences
            // there again
            *leftOrOnlyChildOfChild = applyPrecedenceRules(unaryExpression);

            return oldChild;
        }
        else{
            return unaryExpression;
        } 
    }
    else if(expression->kind == AstExpressionKind::CastKind)
    {
        auto& castExpression = expression;

        auto thisNodePrecedence = getUnaryOperatorPrecedence(castExpression->castForm._operator.kind);
        auto childPrecedence = getPrecedence(castExpression->castForm.expression);

        if(thisNodePrecedence > childPrecedence){
            //'left rotation'
            auto oldChild = castExpression->castForm.expression;

            AstExpression** leftOrOnlyChildOfChild = getLeftChildOrOnlyChild(oldChild);

            castExpression->castForm.expression = *leftOrOnlyChildOfChild;

            // unaryExpression now has children (unary.right = leftOrOnlyChild)
            // that might have lower precedence than itself. So we must check precedences
            // there again
            *leftOrOnlyChildOfChild = applyPrecedenceRules(castExpression);

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


// @Improvement?: we dont gain much with this function because we still need an
// if in the caller to handle and report the error, we could pass the error message
// to this function and report it here or report all errors of here But I think 
// that wouldn't generate good error messages in the long term.
// the only thing we gain with this function is that it handles the weirdness of
// having to peek the token first and if it is what we want we have to 
// Lexer::consumeToken
PromisedToken demandToken(TokenKind tokenKind)
{
    auto peekedToken = Lexer::peekToken();
    if(peekedToken->kind != tokenKind){
        return PromisedToken{ 
                 .isCompliant = false, 
                 .defiantToken = peekedToken 
             };
    }
    else{
        return PromisedToken{
                 .isCompliant = true, 
                 .compliantToken = Lexer::consumeToken() 
               };
    }
}


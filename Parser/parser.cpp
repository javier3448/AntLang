#include "parser.h"

#include "Parser/lexer.h"

//@TODO: improve the way we peek and consume tokens. at the very least use better
//names. maybe a different object to peek tokens, kinda like rust does with
//inmutable references? idk. Or maybe consume the token via a pointer
//@idea?
//consume token.... instead of getNextToken

AstExpression *parser::parseExpression()
{
    //peek token...
    //switch them all and be recursive and all that???
    //lastly do the operator precedence thing where we are 'recurring' back?

    //Token* peekedToken = Lexer::peekToken();

    switch (Lexer::peekToken()->kind) {
        case Integer:
        {
            if(isOperatorKind(Lexer::peekToken(1)->kind)){
                //It means we are a binary expression?
                //So we gotta make an Expression node for the first toke we
                //peeked (which is a number) and then parse whatever expression
                //is next to the operator

                //@C++?: This would be a good place to use a constructor but I
                //dont always want to *have* call a constructor once I allocate
                //the memory. is there any way to call the constructor on a
                //a pointer I provide?
                auto leftExpr = (AstExpression*)malloc(sizeof(AstExpression));
                leftExpr->makeIntLiteralExpression(Lexer::getNextToken());

                auto biOperator = Lexer::getNextToken();

                auto rightExpr = parseExpression();

                auto binaryExpr = (AstExpression*)malloc(sizeof(AstExpression));
                binaryExpr->makeBinaryExpression(leftExpr, biOperator, rightExpr);

                return binaryExpr;
            }
            else{
                auto result = (AstExpression*)malloc(sizeof(AstExpression));
                result->makeIntLiteralExpression(Lexer::getNextToken());

                return result;
            }
        }break;
        case LeftParen:
        {
            //@REMEMBER: to 'consume' the left paren we just peeked before
            //parsing the expression inside
            Lexer::getNextToken();

            AstExpression* result = parseExpression();

            //@Incomplete documentation and renames
            //same as if integer we gotta lookahead once to see if we should
            //return a binExpr instead
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

            peekedToken = Lexer::peekToken();
            if(isOperatorKind(peekedToken->kind)){
                //It means we are a binary expression?
                //So we gotta make an Expression node for the first toke we
                //peeked (which is a number) and then parse whatever expression
                //is next to the operator

                //@C++?: This would be a good place to use a constructor but I
                //dont always want to *have* call a constructor once I allocate
                //the memory. is there any way to call the constructor on a
                //a pointer I provide?
                auto leftExpr = result;

                auto biOperator = Lexer::getNextToken();

                auto rightExpr = parseExpression();

                auto binaryExpr = (AstExpression*)malloc(sizeof(AstExpression));
                binaryExpr->makeBinaryExpression(leftExpr, biOperator, rightExpr);

                return binaryExpr;
            }
            else{
                return result;
            }
            //@REMEMBER: to 'consume' the right paren we just peeked
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


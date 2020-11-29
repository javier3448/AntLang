#include "lexer.h"

#include "mystring.h"

//@TODO: hacer un lexBuffer.cloneIntoMyString

//@Improvement?: wrap all the global state into 1 struct

//@Improvement?: split this file into multiple files, particularly the class
//defs

//@Decision: For *now* we will assume that everything in the hhlSource is
//an ascii character, later we will do UTF8, but it might be more involved than
//it seems.

//just a string that grows in a way we can optimize for our lexing.
//@Tunning: In the initial size and the way it grows when its needed
struct LexBuffer{
    static constexpr s64 INITIAL_SIZE = 255;

    s64 size;
    s64 length;
    char* buffer;


    LexBuffer(){
        size = INITIAL_SIZE;
        length = 0;
        buffer = (char*) malloc(INITIAL_SIZE);
    }

    void append(char c){
        length++;
        if(length > size){
            size = size * 2;
            buffer = (char*)std::realloc(buffer, size);
        }
        buffer[length - 1] = c;
    }

    void empty(){
        length = 0;
    }


};

//we only call the constructor here because c++ gets mad otherwise
MyString Lexer::hllSource{0, nullptr};
s64 Lexer::lexPointer = 0;

std::optional<const char*> Lexer::init(const char* path)
{
    std::FILE* f = std::fopen(path, "rb");

    if(f == nullptr){
        return {strerror(errno)};
    }

    //@[?]C++: Why don't I need the std namespace when using fseek? I am
    //including cstdio as far as I know.
    fseek(f, 0, SEEK_END);
    //we get the size of the file
    s64 size = ftell(f);
    //send the seek pointer to the beggining again
    fseek(f, 0, SEEK_SET);
    char* buffer = (char*)malloc(size);
    //We read the entire buffer
    fread(buffer, 1, size, f);

    //we 'construct' the MyString
    hllSource.length = size;
    hllSource.buffer = buffer;

    //@debug
    cout << hllSource.toStdString() << endl;

    //reset the thing that traverses the hllSource
    lexPointer = 0;

    return {};
}

enum State{
    First,
    Identing1,
    Identing2,
    Numing
};

inline bool isDigit(char c){
    return c <= '9' && c >= '0';
}

//@[!]
//@Big improvement: we should be mindfull of UTF8 characters and all that here
inline bool isLetter(char c){
    return (c >= 'A' && c <= 'Z') ||
           (c >= 'a' && c <= 'z');
}

inline bool isWhiteSpace(char c){
    return c == ' ' ||
           c == '\t' ||
           c == '\n' ||
           c == '\v' ||
           c == '\f' ||
           c == '\r';
}

auto lexBuffer = LexBuffer();
//@Big improve: there has to be a less cumbersome and bug prone way of doing a
//lexer, even if it costs us some performance. I want to be able to easily add
//new tokens/keywords
//@TO LEARN: how does UTF8 works for real, and does it affect us here??
Token Lexer::getNextToken()
{
    assert((lexPointer <= hllSource.length) &&
           "lexPointer is out of bounds!");

    lexBuffer.empty();
    auto currState = State::First;

    while(true){
        switch (currState) {
			case First:
			{
                //special case if end of file
                if(lexPointer == hllSource.length)
                    return Token{TokenKind::Eof};

                char currChar = peek();
                if(isDigit(currChar))
                {
                    advanceAndAppend();
                    currState = State::Numing;
                }
                else if(isLetter(currChar) || currChar == '_')
                {
                    advanceAndAppend();
                    currState = State::Identing1;
                }
                //cases where char == TokenKind
                else if(currChar == '+' || currChar == '-'){
                    advanceAndSkip();
                    return Token((TokenKind)currChar);
                }
                //All the ignored chars
                else if(isWhiteSpace(currChar)){
                    advanceAndSkip();
                }
                else{
                    advanceAndAppend();
                    return Token(TokenKind::Error, MyString(lexBuffer.length, lexBuffer.buffer));
                }

			}break;
            //'_'?letter(letter|digit)*
            case Identing1:
            {
                //special case if end of file
                if(lexPointer == hllSource.length){
                    //@Volatile: finish Identing1
                    //By this point we know the first char is either a letter or a
                    //'_'. A '_' alone is not a valid identifier so we must return
                    return Token(TokenKind::Error, MyString(lexBuffer.length, lexBuffer.buffer));
                }
                char currChar = peek();

                if(currChar == '_'){
                    advanceAndAppend();
                }
                else if(isLetter(currChar) | isDigit(currChar)){
                    advanceAndAppend();
                    currState = State::Identing2;
                }
                else{
                    return Token(TokenKind::Error, MyString(lexBuffer.length, lexBuffer.buffer));
                }
            }break;
            case Identing2:
			{
                //special case if end of file
                if(lexPointer == hllSource.length){
                    return Token(TokenKind::Identifier, MyString(lexBuffer.length, lexBuffer.buffer));
                }
                char currChar = peek();

                if(isLetter(currChar) || isDigit(currChar) || currChar == '_'){
                    advanceAndAppend();
                }
                else{
                    return Token(TokenKind::Identifier, MyString(lexBuffer.length, lexBuffer.buffer));
                }
			}break;
			case Numing:
			{
                //@TODO: atrapar si la cadena representa un numero demasiado
                //grande para s64

                //special case if end of file
                if(lexPointer == hllSource.length){
                    //@TODO: dont convert to stdString here! find a way to parse
                    //to integer only using your MyString
                    //@Bodge:
                    auto myString = MyString(lexBuffer.length, lexBuffer.buffer);
                    auto stdString = myString.toStdString();
                    return Token(TokenKind::Integer, std::stoll(stdString.c_str(), nullptr, 10));
                }
                char currChar = hllSource[lexPointer];
                //special case if end of file
                if(isDigit(currChar)){
                    advanceAndAppend();
                }
                //@TODO: support for float literals
                else{
                    //@TODO: dont convert to stdString here! find a way to parse
                    //to integer only using your MyString
                    //@Bodge:
                    auto myString = MyString(lexBuffer.length, lexBuffer.buffer);
                    auto stdString = myString.toStdString();
                    return Token(TokenKind::Integer, std::stoll(stdString.c_str(), nullptr, 10));
                }
            }break;
            //TODO: support for
        }
    }
}

//@NOTE: states are not final or not, they might need to check some other thing
//in mem that tells them is they are a valid final or if they should return
//an error token

//@Improvement?: make it so we peek advance 'n' characters
//works for negative as well but only asserts we dont peek out of bounds
//in debug build
inline char Lexer::peek(s64 ammount)
{
    assert((lexPointer + ammount <= hllSource.length ||
            lexPointer + ammount < 0)
           &&
           "lexPointer is out of bounds!");

    return hllSource[lexPointer + ammount];
}

//@Improvement?: make it so we can advance 'n' characters
//appends to lexBuffer whatever is in hllSource[lexPointer] and advances
//the pointer by 1
inline void Lexer::advanceAndAppend()
{
    lexBuffer.append(hllSource[lexPointer]);
    lexPointer += 1;
}

//Mostly used when we peek a character we want to skip
inline void Lexer::advanceAndSkip()
{
    lexPointer += 1;
}

//BAD?: If every state returns a token we will have to copy that Token all over
//the stack call untill we reaad funcGetNextToken

//For this version we will be very disciplined: 1 function = to 1 state always
//every state is a function, a state that is not final returns Error or other
//state, a state that is final doesnt, a state cant return both

Token Lexer::funcGetNextToken()
{
    assert((lexPointer <= hllSource.length) &&
          "lexPointer is out of bounds!");

    lexBuffer.empty();

    return funcFirst();
}

Token Lexer::funcFirst()
{
    //special case if end of file
    if(lexPointer == hllSource.length)
        return Token{TokenKind::Eof};

    char currChar = peek();
    if(isDigit(currChar))
    {
        advanceAndAppend();
        return funcNuming();
    }
    else if(currChar == '_'){
        advanceAndAppend();
        return funcIdenting1();
    }
    else if(isLetter(currChar))
    {
        advanceAndAppend();
        return funcIdenting2();
    }
    //cases where char == TokenKind
    else if(currChar == '+' || currChar == '-'){
        advanceAndSkip();
        return Token((TokenKind)currChar);
    }
    //All the ignored chars
    else if(isWhiteSpace(currChar)){
        advanceAndSkip();
        return funcFirst();
    }
    else{
        advanceAndAppend();
        return Token(TokenKind::Error, MyString(lexBuffer.length, lexBuffer.buffer));
    }
}

Token Lexer::funcNuming()
{
    //@TODO: atrapar si la cadena representa un numero demasiado
    //grande para s64

    //special case if end of file
    if(lexPointer == hllSource.length){
        //@TODO: dont convert to stdString here! find a way to parse
        //to integer only using your MyString
        //@Bodge:
        auto myString = MyString(lexBuffer.length, lexBuffer.buffer);
        auto stdString = myString.toStdString();
        return Token(TokenKind::Integer, std::stoll(stdString.c_str(), nullptr, 10));
    }
    char currChar = hllSource[lexPointer];
    //special case if end of file
    if(isDigit(currChar)){
        advanceAndAppend();
        return funcNuming();
    }
    //@TODO: support for float literals
    else{
        //@TODO: dont convert to stdString here! find a way to parse
        //to integer only using your MyString
        //@Bodge:
        auto myString = MyString(lexBuffer.length, lexBuffer.buffer);
        auto stdString = myString.toStdString();
        return Token(TokenKind::Integer, std::stoll(stdString.c_str(), nullptr, 10));
    }
}

Token Lexer::funcIdenting1()
{
    //special case if end of file
    if(lexPointer == hllSource.length){
        //@Volatile: finish Identing1
        //By this point we know the first char is either a letter or a
        //'_'. A '_' alone is not a valid identifier so we must return
        return Token(TokenKind::Error, MyString(lexBuffer.length, lexBuffer.buffer));
    }
    char currChar = peek();

    if(currChar == '_'){
        advanceAndAppend();
        return funcIdenting1();
    }
    else if(isLetter(currChar) | isDigit(currChar)){
        advanceAndAppend();
        return funcIdenting2();
    }
    else{
        return Token(TokenKind::Error, MyString(lexBuffer.length, lexBuffer.buffer));
    }
}

Token Lexer::funcIdenting2()
{//special case if end of file
    if(lexPointer == hllSource.length){
        return Token(TokenKind::Identifier, MyString(lexBuffer.length, lexBuffer.buffer));
    }
    char currChar = peek();

    if(isLetter(currChar) || isDigit(currChar) || currChar == '_'){
        advanceAndAppend();
        return funcIdenting2();
    }
    else{
        return Token(TokenKind::Identifier, MyString(lexBuffer.length, lexBuffer.buffer));
    }
}

Token Lexer::gotoGetNextToken()
{
    assert((lexPointer <= hllSource.length) &&
           "lexPointer is out of bounds!");

    lexBuffer.empty();
    goto First;

    //'State machine' for the lexing because its the easiest to understand
    //in my opinion.
    //1 label per state.
    //@TODO: make a drawing of the state machine and put it here in ASCII or
    //something
    //@NOTE:
    //asserts between states because we can only leave a state by explicitely
    //going to another one or returning a function

    First:
    {
        //special case if end of file
        if(lexPointer == hllSource.length)
            return Token{TokenKind::Eof};

        char currChar = peek();
        if(isDigit(currChar))
        {
            advanceAndAppend();
            goto Numing;
        }
        else if(isLetter(currChar))
        {
            advanceAndAppend();
            goto Identing2;
        }
        else if(currChar == '_')
        {
            advanceAndAppend();
            goto Identing1;
        }
        //cases where char == TokenKind
        else if(currChar == '+' || currChar == '-'){
            advanceAndSkip();
            return Token((TokenKind)currChar);
        }
        //All the ignored chars
        else if(isWhiteSpace(currChar)){
            advanceAndSkip();
            goto First;
        }
        else{
            advanceAndAppend();
            return Token(TokenKind::Error, MyString(lexBuffer.length, lexBuffer.buffer));
        }

    }
    assert(false && "We can only leave a LexState by explecitely going "
                    "to another state or by returning a token");

    Identing1:
    {
        //special case if end of file
        if(lexPointer == hllSource.length){
            //@Volatile: finish Identing1
            //By this point we know the first char is either a letter or a
            //'_'. A '_' alone is not a valid identifier so we must return
            return Token(TokenKind::Error, MyString(lexBuffer.length, lexBuffer.buffer));
        }
        char currChar = peek();

        if(currChar == '_'){
            advanceAndAppend();
            goto Identing2;
        }
        else if(isLetter(currChar) | isDigit(currChar)){
            advanceAndAppend();
            goto Identing2;
        }
        else{
            return Token(TokenKind::Error, MyString(lexBuffer.length, lexBuffer.buffer));
        }
    }

    assert(false && "We can only leave a LexState by explecitely going "
                    "to another state or by returning a token");

    Identing2:
    {
        //special case if end of file
        if(lexPointer == hllSource.length){
            return Token(TokenKind::Identifier, MyString(lexBuffer.length, lexBuffer.buffer));
        }
        char currChar = peek();

        if(isLetter(currChar) || isDigit(currChar) || currChar == '_'){
            advanceAndAppend();
            goto Identing2;
        }
        else{
            return Token(TokenKind::Identifier, MyString(lexBuffer.length, lexBuffer.buffer));
        }
    }

    assert(false && "We can only leave a LexState by explecitely going "
                    "to another state or by returning a token");

    Numing:
    {
        //@TODO: atrapar si la cadena representa un numero demasiado
        //grande para s64

        //special case if end of file
        if(lexPointer == hllSource.length){
            //@TODO: dont convert to stdString here! find a way to parse
            //to integer only using your MyString
            //@Bodge:
            auto myString = MyString(lexBuffer.length, lexBuffer.buffer);
            auto stdString = myString.toStdString();
            return Token(TokenKind::Integer, std::stoll(stdString.c_str(), nullptr, 10));
        }
        char currChar = hllSource[lexPointer];
        //special case if end of file
        if(isDigit(currChar)){
            advanceAndAppend();
            goto Numing;
        }
        //@TODO: support for float literals
        else{
            //@TODO: dont convert to stdString here! find a way to parse
            //to integer only using your MyString
            //@Bodge:
            auto myString = MyString(lexBuffer.length, lexBuffer.buffer);
            auto stdString = myString.toStdString();
            return Token(TokenKind::Integer, std::stoll(stdString.c_str(), nullptr, 10));
        }
    }
}

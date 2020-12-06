#include "lexer.h"

#include "mystring.h"

//@TODO: hacer un lexBuffer.cloneIntoMyString

//@TODO soon: add line and column info to each token. Later we will even have
//to add file info as well

//@Idea?
//@Improvement?: the whole thing might be easier to understand if peek
//would return a special value when we run out of file.
//having an if that checks for that first and Then peekin for next char is
//kinda confusing

//@Improvement?: wrap all the global state into 1 struct

//@Improvement?: split this file into multiple files, particularly the class
//defs

//@Decision: For *now* we will assume that everything in the hhlSource is
//an ascii character, later we will do UTF8, but it might be more involved than
//it seems.

//just a string that grows in a way we can optimize for our lexing.
//@Tunning: In the initial size and the way it grows when its needed
struct LexBuffer{
    static constexpr s64 INITIAL_SIZE = 256;

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

//@NOTE: states are not final or not, they might need to check some other thing
//in mem that tells them is they are a valid final or if they should return
//an error token

//@Improvement?: make it so we peek advance 'n' characters
//works for negative as well but only asserts we dont peek out of bounds
//in debug build
inline char Lexer::peekChar(s64 ammount)
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

//@TO LEARN: how does UTF8 works for real, and does it affect us here??
Token Lexer::lexToken()
{
    //@BUG: we fail assert if the last thing in the source file is an ignored char
    //like a comment or a whitespace
    assert((lexPointer <= hllSource.length) &&
           "lexPointer is out of bounds!");

    //@debug
//    static s64 count = 1;
//    cout << "*********************************************\n";
//    cout << "this is the: " << count << " time we run lexToken() \n";
//    cout << "*********************************************\n";
//    count++;

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
        {
            //we still need to advance to leave the lexPointer in an 'out of
            //bounds' state so next time we call lexToken the assertion can
            //throw an error
            advanceAndSkip();
            return Token{TokenKind::Eof};
        }

        char currChar = peekChar();
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
        else if(currChar == '+' || currChar == '-' || currChar == '(' || currChar == ')' || currChar == '*'){
            advanceAndSkip();
            return Token((TokenKind)currChar);
        }
        else if(currChar == '/'){
            advanceAndSkip();
            goto Slash;
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
    }assert(false && "We can only leave a LexState by 'goto State;' or returning");

    //needs its own state because we might have a '/' that is being used to
    //make a line comment
    Slash:
    {
        //special case if end of file
        if(lexPointer == hllSource.length){
            return Token((TokenKind)'/');
        }
        char currChar = peekChar();
        if(currChar == '/'){
            advanceAndSkip();
            goto LineComment;
        }
        else{
            return Token((TokenKind)'/');
        }
    }assert(false && "We can only leave a LexState by 'goto State;' or returning");


    //Its like a special case for ignore. 'an ignore char that only stops
    //ignoring untill it finds end of line or EOF
    LineComment:
    {
        //special case if end of file
        if(lexPointer == hllSource.length){
            //we stop ignoring and let 'First state' figure out what is the
            //real nextToken
            goto First;
        }
        char currChar = peekChar();

        if(currChar == '\n' || currChar == '\r'){
            advanceAndSkip();
            goto First;
        }
        else{
            advanceAndSkip();
            goto LineComment;
        }
    }assert(false && "We can only leave a LexState by 'goto State;' or returning");

    Identing1:
    {
        //special case if end of file
        if(lexPointer == hllSource.length){
            //@Volatile: finish Identing1
            //By this point we know the first char is either a letter or a
            //'_'. A '_' alone is not a valid identifier so we must return
            return Token(TokenKind::Error, MyString(lexBuffer.length, lexBuffer.buffer));
        }
        char currChar = peekChar();

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
    }assert(false && "We can only leave a LexState by 'goto State;' or returning");

    Identing2:
    {
        //special case if end of file
        if(lexPointer == hllSource.length){
            return Token(TokenKind::Identifier, MyString(lexBuffer.length, lexBuffer.buffer));
        }
        char currChar = peekChar();

        if(isLetter(currChar) || isDigit(currChar) || currChar == '_'){
            advanceAndAppend();
            goto Identing2;
        }
        else{
            return Token(TokenKind::Identifier, MyString(lexBuffer.length, lexBuffer.buffer));
        }
    }assert(false && "We can only leave a LexState by 'goto State;' or returning");

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
    }assert(false && "We can only leave a LexState by 'goto State;' or returning");
}

TokenCache Lexer::tokenCache{};

Token Lexer::getNextToken()
{
    if(tokenCache.occupiedSpaces != 0){
        return tokenCache.dequeue();
    }
    else{
        //if tokenCache is empty we dont need to interact with the cache at all
        return lexToken();
    }
}

//@PERF?:
//[?] should this return by value instead. Whats generally better for perf
//idfk :((((.
Token* Lexer::peekToken(s64 amount)
{
    //we cache as many tokens as are required to peek that amount
    for (s32 i = tokenCache.occupiedSpaces; i <= amount; i++)
    {
        tokenCache.enqueue(lexToken());
    }

    return &tokenCache.tokenBuffer[tokenCache.targetOffset + amount];
}

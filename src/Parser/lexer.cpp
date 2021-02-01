#include "./lexer.h"

#include "../mystring.h"

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
MyString Lexer::hllSourceDif{0, nullptr};
s64 Lexer::lexPointer = 0;

// @[!!!]
// @UB: if the contents in the file: 'path' contain null chars
//      An easy way to avoid that would be to have a different string struct
//      for lexing, one that can take null chars and is not null terminated
void Lexer::init(const char* path)
{
    std::FILE* f = std::fopen(path, "rb");

    if(f == nullptr){
        printf("%s", strerror(errno));
        assert(false);
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
    hllSourceDif.length = size;
    hllSourceDif.buffer = buffer;

    //@debug
    cout << hllSourceDif.toStdString() << endl;

    //reset the thing that traverses the hllSource
    lexPointer = 0;
}

enum State{
    First,
    // @bad names :/
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

// @Improvement?: make it so we peek advance 'n' characters
// works for negative as well but only asserts we dont peek out of bounds
// in debug build
// Only return nullchar if we reach EOF, if we find a nullchar anywhere in the 
// source file we panic
inline char Lexer::peekChar(s64 ammount)
{
    assert((lexPointer + ammount <= hllSourceDif.length &&
            lexPointer + ammount >= 0)
           &&
           "lexPointer is out of bounds!");

    // [!]
    // the only place we accept null is as the end char of MyString, because
    // MyString's buffer is null terminated.
    // thats why this if goes *before* assert
    if(lexPointer + ammount == hllSourceDif.length){
        return '\0';
    }

    assert(hllSourceDif[lexPointer + ammount] != '\0'
            &&
           "nullchar found in source!");

    return hllSourceDif[lexPointer + ammount];
}

//@Improvement?: make it so we can advance 'n' characters
//appends to lexBuffer whatever is in hllSource[lexPointer] and advances
//the pointer by 1
inline void Lexer::advanceAndAppend()
{
    lexBuffer.append(hllSourceDif[lexPointer]);
    lexPointer += 1;
}

//Mostly used when we peek a character we want to skip
inline void Lexer::advanceAndSkip()
{
    lexPointer += 1;
}

// @Improvement: generating keywords feels slow but for now it will do.
// makes ident or keyword out of whatever is in the lex buffer.
// @Improvement: It might be a better idea to move this to toke.cpp and pass it 
// the string, something like 'bool isKeyword(const char* str);'
Token makeIdentOrKeyword()
{
    auto keyWordKind = isStringKeyword(lexBuffer.buffer, lexBuffer.length);
    if(keyWordKind)
        return Token(keyWordKind.value());
    else
        return Token(TokenKind::Identifier, MyString::make(lexBuffer.length, lexBuffer.buffer));
}


//@TO LEARN: how does UTF8 works for real, and does it affect us here??
Token Lexer::lexToken()
{
    //@BUG: we fail assert if the last thing in the source file is an ignored char
    //like a comment or a whitespace
    assert((lexPointer <= hllSourceDif.length) &&
           "lexPointer is out of bounds!");

    lexBuffer.empty();
    goto First;

    //'State machine' for the lexing because its the easiest to understand
    //in my opinion.
    //1 label per state.
    //@TODO: make a drawing of the state machine and put it here in ASCII or
    //something
    //@NOTE:
    //asserts between states because we can only leave a state by explicitly
    //going to another one or returning from function

    First:
    {
        char currChar = peekChar();
        if(currChar == '\0')
        {
            return Token{TokenKind::Eof};
        }
        else if(isDigit(currChar))
        {
            advanceAndAppend();
            goto Numing1;
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
        // Cases where char == TokenKind
        // @Improvement: find a cleaner way to this
        else if(currChar == '+'){
            advanceAndSkip();
            return TokenKind::Plus;
        }
        else if(currChar == '-'){
            advanceAndSkip();
            return TokenKind::Minus;
        }
        else if(currChar == '('){
            advanceAndSkip();
            return TokenKind::LeftParen;
        }
        else if(currChar == ')'){
            advanceAndSkip();
            return TokenKind::RightParen;
        }
        else if(currChar == '*'){
            advanceAndSkip();
            return TokenKind::Multiplication;
        }
        // cases that the resulting token can be the char itself or somthing else
        // like '<' and '<='. ie, cases that dont warrant their own state
        else if(currChar == '<'){
            advanceAndSkip();
            auto nextChar = peekChar();
            if(nextChar == '='){
                advanceAndSkip();
                return Token(TokenKind::LessEqual);
            }
            else{
                return Token(TokenKind::Less);
            }
        }
        else if(currChar == '>'){
            advanceAndSkip();
            auto nextChar = peekChar();
            if(nextChar == '='){
                advanceAndSkip();
                return Token(TokenKind::GreaterEqual);
            }
            else{
                return Token(TokenKind::Greater);
            }
        }
        else if(currChar == '='){
            advanceAndSkip();
            auto nextChar = peekChar();
            if(nextChar == '='){
                advanceAndSkip();
                return Token(TokenKind::EqualEqual);
            }
            else{
                return Token(TokenKind::Equal);
            }
        }
        else if(currChar == '!'){
            advanceAndSkip();
            auto nextChar = peekChar();
            if(nextChar == '='){
                advanceAndSkip();
                return Token(TokenKind::NotEqual);
            }
            else{
                return Token(TokenKind::Not);
            }
        }
        else if(currChar == '&'){
            advanceAndSkip();
            auto nextChar = peekChar();
            if(nextChar == '&'){
                advanceAndSkip();
                return Token(TokenKind::And);
            }
            else{
                return Token(TokenKind::BitAnd);
            }
        }
        else if(currChar == '|'){
            advanceAndSkip();
            auto nextChar = peekChar();
            if(nextChar == '|'){
                advanceAndSkip();
                return Token(TokenKind::Or);
            }
            else{
                return Token(TokenKind::BitOr);
            }
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
            return Token(TokenKind::Error, MyString::make(lexBuffer.length, lexBuffer.buffer));
        }
    }assert(false && "We can only leave a LexState by 'goto State;' or returning");

    //needs its own state because we might have a '/' that is being used to
    //make a line comment
    Slash:
    {
        char currChar = peekChar();
        if(currChar == '/'){
            advanceAndSkip();
            goto LineComment;
        }
        else if(currChar == '*'){
            advanceAndSkip();
            goto MultilineComment;
        }
        else{
            return Token(TokenKind::Division);
        }
    }assert(false && "We can only leave a LexState by 'goto State;' or returning");

    //Its like a special case for ignore. 'an ignore char that only stops
    //ignoring untill it finds end of line or EOF
    LineComment:
    {
        char currChar = peekChar();
        if(currChar == '\n' || currChar == '\r'){
            advanceAndSkip();
            goto First;
        }
        else if(currChar == '\0'){
            //Special case if 'EOF' we dont advance the character
            goto First;
        }
        else{
            advanceAndSkip();
            goto LineComment;
        }
    }assert(false && "We can only leave a LexState by 'goto State;' or returning");

    // For now we won't support nested comments because I am not sure if I like 
    // them, but to implement them we would only need to keep track of how many
    // time does '/*' and '*/' appear inside the comment. ez
    MultilineComment:
    {
        // @Cheating:
        // special case if end of file
        // I dont want to create a whole other state just to handle a '*' that is
        // not followed by a '/' so we will check both, by using a double peek
        // char
        // Another way to think about it is that this state will lex in a '2 char step'
        // WHICH MEANS THAT WE SHOULD HAVE AT LEAST 2 CHARS LEFT IN hllSource
        // ELSE THIS IS A ERROR TOKEN
        if(lexPointer >= hllSourceDif.length - 1){
            // @TODO: this is a unclosed comment error
            return Token(TokenKind::Error, MyString::make("unclosed multine comment"));
        }
        char currChar1 = peekChar(0);
        char currChar2 = peekChar(1);

        if(currChar1 == '*' && currChar2 == '/'){
            advanceAndSkip();
            advanceAndSkip();
            goto First;
        }
        else{
            advanceAndSkip();
            advanceAndSkip();
            goto MultilineComment;
        }
    }assert(false && "We can only leave a LexState by 'goto State;' or returning");

    Identing1:
    {
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
            return Token(TokenKind::Error, MyString::make(lexBuffer.length, lexBuffer.buffer));
        }
    }assert(false && "We can only leave a LexState by 'goto State;' or returning");

    Identing2:
    {
        char currChar = peekChar();

        if(isLetter(currChar) || isDigit(currChar) || currChar == '_'){
            advanceAndAppend();
            goto Identing2;
        }
        else{
            // @Bodge: For now to lex all keywords we just check if any ident we
            // generate is in a big old list of keywords if so we return the keyword
            // not the ident instead
            return makeIdentOrKeyword();
        }
    }assert(false && "We can only leave a LexState by 'goto State;' or returning");

    Numing1:
    {
        char currChar = peekChar();
        if(isDigit(currChar)){
            advanceAndAppend();
            goto Numing1;
        }
        else if(currChar == '.'){
            advanceAndAppend();
            goto Numing2;
        }
        else{
            return Token(TokenKind::Number, MyString::make(lexBuffer.length, lexBuffer.buffer));
        }
    }assert(false && "We can only leave a LexState by 'goto State;' or returning");

    // In this state we already lexed the '.'
    Numing2:
    {
        char currChar = peekChar();
        if(isDigit(currChar)){
            advanceAndAppend();
            goto Numing3;
        }
        else{
            return Token(TokenKind::Error, MyString::make(lexBuffer.length, lexBuffer.buffer));
        }
    }assert(false && "We can only leave a LexState by 'goto State;' or returning");

    // In this state we already lexed the '.' AND we know there is at least one digit after it
    Numing3:
    {
        char currChar = peekChar();
        //special case if end of file
        if(isDigit(currChar)){
            advanceAndAppend();
            goto Numing2;
        }
        else{
            return Token(TokenKind::Number, MyString::make(lexBuffer.length, lexBuffer.buffer));
        }
    }assert(false && "We can only leave a LexState by 'goto State;' or returning");
}

TokenCache Lexer::tokenCache{};

Token Lexer::consumeToken()
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

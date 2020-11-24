#include "lexer.h"

#include "mystring.h"

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
                if(lexPointer == hllSource.length){
                    return Token{TokenKind::Eof};
                }
                char currChar = hllSource[lexPointer];
                if(isDigit(currChar))
                {
                    lexBuffer.append(currChar);
                    currState = State::Numing;
                    lexPointer++;
                }
                else if(isLetter(currChar)||
                   currChar == '_')
                {
                    lexBuffer.append(currChar);
                    lexPointer++;
                    currState = State::Identing1;
                }
                else if(currChar == '+'){
                    lexPointer++;
                    return Token(TokenKind::Plus);
                }
                else if(currChar == '-'){
                    lexPointer++;
                    return Token(TokenKind::Minus);
                }
                //All the ignored chars
                else if(isWhiteSpace(currChar)){
                    lexPointer++;
                }
                else{
                    lexPointer++;
                    return Token(TokenKind::Error, MyString(1, &hllSource.buffer[lexPointer - 1]));
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
                    if(lexBuffer.length == 1 && lexBuffer.buffer[0] == '_'){
                        return Token(TokenKind::Error, MyString(lexBuffer.length, lexBuffer.buffer));
                    }
                    return Token(TokenKind::Identifier, MyString(lexBuffer.length, lexBuffer.buffer));
                }
                char currChar = hllSource[lexPointer];

                if(isLetter(currChar)){
                    lexBuffer.append(currChar);
                    lexPointer++;
                    currState = State::Identing2;
                }
                else{
                    //@Volatile: finish Identing1
                    //By this point we know the first char is either a letter or a
                    //'_'. A '_' alone is not a valid identifier so we must return
                    if(lexBuffer.length == 1 && lexBuffer.buffer[0] == '_'){
                        return Token(TokenKind::Error, MyString(lexBuffer.length, lexBuffer.buffer));
                    }
                    return Token(TokenKind::Identifier, MyString(lexBuffer.length, lexBuffer.buffer));

                }
            }break;
            case Identing2:
			{
                //special case if end of file
                if(lexPointer == hllSource.length){
                    return Token(TokenKind::Identifier, MyString(lexBuffer.length, lexBuffer.buffer));
                }
                char currChar = hllSource[lexPointer];

                if(isLetter(currChar) || isDigit(currChar) || currChar == '_'){
                    lexBuffer.append(currChar);
                    lexPointer++;
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
                    lexBuffer.append(currChar);
                    lexPointer++;
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

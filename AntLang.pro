TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        Lexer/lexer.cpp \
        Lexer/token.cpp \
        main.cpp \
        mystring.cpp

HEADERS += \
    Lexer/lexer.h \
    Lexer/token.h \
    mystring.h \
    pch.h

DISTFILES += \
    todo.txt

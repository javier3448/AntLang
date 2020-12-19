TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        Parser/astexpression.cpp \
        Parser/grapher.cpp \
        Parser/lexer.cpp \
        Parser/parser.cpp \
        Parser/shuntingyard.cpp \
        Parser/token.cpp \
        Parser/tokencache.cpp \
        main.cpp \
        mystring.cpp

HEADERS += \
    Parser/astexpression.h \
    Parser/grapher.h \
    Parser/lexer.h \
    Parser/parser.h \
    Parser/shuntingyard.h \
    Parser/token.h \
    Parser/tokencache.h \
    mystring.h \
    pch.h

DISTFILES += \
    TestFiles/Graphviz/test.dot \
    TestFiles/Graphviz/test.png \
    TestFiles/test.txt \
    TestFiles/todo \
    todo.txt

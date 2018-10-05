include(gtest_dependency.pri)

TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG += thread
CONFIG -= qt

HEADERS += \
        tst_lexertest.h \
        tst_tokentest.h \
        token.h \
        lexer.h \
    tst_tokentest.h \
    parser.h \
    tst_parsertest.h \
    InstructionParser.h \
    DeclarationParser.h \
    tst_declarationparsertest.h \
    tst_instructionparsertest.h

SOURCES += \
        main.cpp \
        token.cpp \
        lexer.cpp \
    parser.cpp \
    InstructionParser.cpp \
    DeclarationParser.cpp

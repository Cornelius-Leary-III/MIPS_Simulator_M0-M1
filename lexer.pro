include(gtest_dependency.pri)

TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG += thread
CONFIG -= qt

HEADERS += \
        tst_lexertest.h \
    token.h \
    lexer.h

SOURCES += \
        main.cpp \
    token.cpp \
    lexer.cpp
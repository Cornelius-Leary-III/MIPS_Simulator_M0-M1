#ifndef LEXER_H
#define LEXER_H

#include "token.h"
#include <istream>

using std::string;

class lexer
{
public:

    lexer();
    void tokenizeStream(std::istream& input);
    tokenList& getTokens();
    bool isValid();
    void checkForErrors();

    bool isCurrentCharSequenceNotEmpty();
    void updateLexerStateAfterNewlineChar();

    void processCharWithinString();
    void processCharWithinComment();
    void processCharOutsideOfString();

    void handleEOL();
    void handleWhitespace();

    void addTokenWithoutContents(TokenType currentTokenType);
    void handleSEP();
    void handleEQUAL();
    void handleOPEN_PAREN();
    void handleCLOSE_PAREN();
    void handleSTRING_DELIM();

    void addTokenSTRING();
    void handleSTRING();

    void addTokenERROR();
    void handleERROR();

private:

    tokenList tokenizedText;

    size_t currentLine;
    string currentCharSequence;
    char currentChar;

    bool withinComment;
    bool withinString;
    size_t parenthesesDepth;

    bool stringDelimiterError;
    bool parenthesesError;



};

#endif // LEXER_H

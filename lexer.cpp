#include "lexer.h"

lexer::lexer()
{
    withinString = false;
    withinComment = false;
    parenthesesError = false;
    stringDelimiterError = false;

    currentTokenId = 1;
    currentLine = 1;
    parenthesesDepth = 0;
    currentCharSequence;
    tokenizedText;
}

void lexer::tokenizeStream(std::istream& input)
{
    char inputChar;
    char previousChar = '~';

    while (input.get(inputChar))
    {
        if (previousChar == '\n')
        {
            ++currentLine;
        }

        if (inputChar == '\n')
        {
            handleEOL();
        }
        else if (withinString)
        {
            processCharWithinString(inputChar);
        }
        else if (withinComment)
        {
            processCharWithinComment(inputChar);
        }
        else
        {
            processCharOutsideOfString(inputChar);
        }

        previousChar = inputChar;
    }

    updateLexerStateAtEndOfStream(previousChar);
    handleERROR();
}

tokenVector& lexer::getTokens()
{
    return tokenizedText;
}

void lexer::processCharWithinComment(char currentChar)
{
    // ignore comment character.
}

void lexer::processCharWithinString(char currentChar)
{
    if (currentChar == '\"')
    {
        handleSTRING_DELIM();
    }
    else
    {
        currentCharSequence.push_back(currentChar);
    }
}

void lexer::processCharOutsideOfString(char currentChar)
{
    switch (currentChar)
    {
    case '#':
    {
        withinComment = true;
        break;
    }
    case ',':
    {
        handleSEP();
        break;
    }
    case '=':
    {
        handleEQUAL();
        break;
    }
    case '(':
    {
        handleOPEN_PAREN();
        break;
    }
    case ')':
    {
        handleCLOSE_PAREN();
        break;
    }
    case '\"':
    {
        handleSTRING_DELIM();
        break;
    }
    case ' ':
    {
        handleWhitespace();
        break;
    }
    case '\v':
    {
        handleWhitespace();
        break;
    }
    case '\r':
    {
        handleWhitespace();
        break;
    }
    case '\t':
    {
        handleWhitespace();
        break;
    }
    default:
    {
        currentCharSequence.push_back(currentChar);
        break;
    }
    }
}

void lexer::handleEOL()
{
    handleSTRING();
    updateLexerStateAfterNewlineChar();
    addTokenWithoutContents(EOL);
//    ++currentLine;
}

void lexer::updateLexerStateAfterNewlineChar()
{
    if (withinComment)
    {
        withinComment = false;
    }

    if (withinString)
    {
        stringDelimiterError = true;
    }

    if (parenthesesDepth != 0)
    {
        parenthesesError = true;
    }
}

void lexer::updateLexerStateAtEndOfStream(char finalChar)
{
    handleSTRING();

    if (finalChar != '\n' &&
        !tokenizedText.empty())
    {
        addTokenWithoutContents(EOL);
    }

    if (withinComment)
    {
        withinComment = false;
    }

    if (withinString)
    {
        stringDelimiterError = true;
    }

    if (parenthesesDepth != 0)
    {
        parenthesesError = true;
    }
}

void lexer::handleWhitespace()
{
    handleSTRING();
}

void lexer::handleSEP()
{
    handleSTRING();
    addTokenWithoutContents(SEP);
}

void lexer::handleEQUAL()
{
    handleSTRING();
    addTokenWithoutContents(EQUAL);
}

void lexer::handleOPEN_PAREN()
{
    handleSTRING();

    ++parenthesesDepth;

    addTokenWithoutContents(OPEN_PAREN);
}

void lexer::handleCLOSE_PAREN()
{
    handleSTRING();

    --parenthesesDepth;

    addTokenWithoutContents(CLOSE_PAREN);
}

void lexer::handleSTRING_DELIM()
{
    handleSTRING();

    withinString = !withinString;

    addTokenWithoutContents(STRING_DELIM);
}

void lexer::addTokenWithoutContents(TokenType currentTokenType)
{
    tokenizedText.emplace_back(currentTokenType, currentTokenId, currentLine);
    ++currentTokenId;
}

void lexer::handleSTRING()
{
    if (isCurrentCharSequenceNotEmpty())
    {
        addTokenSTRING();
    }
}

void lexer::addTokenSTRING()
{
    tokenizedText.emplace_back(STRING, currentTokenId, currentLine, currentCharSequence);
    ++currentTokenId;
    currentCharSequence.clear();
}

bool lexer::isCurrentCharSequenceNotEmpty()
{
    return !currentCharSequence.empty();
}

void lexer::handleERROR()
{
    if (stringDelimiterError)
    {
        addTokenStringDelimiterError();
    }

    if (parenthesesError || parenthesesDepth != 0)
    {
        addTokenParenthesesError();
    }
}

void lexer::addTokenStringDelimiterError()
{
    tokenizedText.emplace_back(ERROR, currentTokenId, currentLine, "ERROR: missing STRING_DELIM character");
    ++currentTokenId;
}

void lexer::addTokenParenthesesError()
{
    std::stringstream ss;
    ss << "ERROR: unmatched parentheses --> depth = " << parenthesesDepth;

    tokenizedText.emplace_back(ERROR, currentTokenId, currentLine, ss.str());
    ++currentTokenId;
}

bool lexer::isStringDelimiterErrorPresent()
{
    return stringDelimiterError;
}

bool lexer::isParenthesesErrorPresent()
{
    return parenthesesError;
}

#include "lexer.h"

lexer::lexer()
{
    withinString = false;
    withinComment = false;
    parenthesesError = false;
    stringDelimiterError = false;

    currentLine = 1;
    currentChar = '~';
    parenthesesDepth = 0;
    currentCharSequence;
}

void lexer::tokenizeStream(std::istream& input)
{
    //    char currentChar;
    while (input.get(currentChar))
    {
        if (currentChar == '\n')
        {
            handleEOL();
        }
        else if (withinString)
        {
            processCharWithinString();
        }
        else if (withinComment)
        {
            processCharWithinComment();
        }
        else
        {
            processCharOutsideOfString();
        }
    }
    checkForErrors();
}

void lexer::processCharWithinComment()
{
    // ignore comment character.
}

void lexer::processCharWithinString()
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

void lexer::processCharOutsideOfString()
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

//    }

//    if (stringDelimiterError)
//    {
//        // string delimiter error.
//    }

//    if (parenthesesError || parenthesesDepth != 0)
//    {
//        // parentheses error.
//    }

void lexer::checkForErrors()
{
    //TODO: determine best way to handle errors in tokenizing

    if (stringDelimiterError)
    {
        addTokenERROR();
    }

    if (parenthesesError || parenthesesDepth != 0)
    {
        addTokenERROR();
    }


}

void lexer::handleEOL()
{
    handleSTRING();
    updateLexerStateAfterNewlineChar();
    addTokenWithoutContents(EOL);
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
    tokenizedText.emplace_back(currentTokenType, currentLine);
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
    tokenizedText.emplace_back(STRING, currentLine, currentCharSequence);
    currentCharSequence.clear();
}

bool lexer::isCurrentCharSequenceNotEmpty()
{
    return !currentCharSequence.empty();
}

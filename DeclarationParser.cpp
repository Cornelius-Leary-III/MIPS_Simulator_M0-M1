#include "DeclarationParser.h"

DeclarationParser::DeclarationParser(const tokenList& currentLineToParse)
{
    lineOfTokens = currentLineToParse;
    currentToken = lineOfTokens.begin();
}

bool DeclarationParser::parse_Declaration()
{
    auto firstToken = currentToken;

    if (parse_Constant())
    {
        ++currentToken;
        if (currentToken->type() == EOL)
        {
            return true;
        }
    }
    else
    {
        currentToken = firstToken;
    }

    if (parse_Label())
    {
        ++currentToken;
        auto optionalLabelLayoutToken = currentToken;

        if (parse_Layout())
        {
            ++currentToken;
            if (currentToken->type() == EOL)
            {
                return true;
            }
        }
        else
        {
            currentToken = optionalLabelLayoutToken;
            if (currentToken->type() == EOL)
            {
                return true;
            }
        }
    }

    currentToken = firstToken;

    token tokenBeforeLayoutParsing = *currentToken;
    token tokenAfterLayoutParsing = *currentToken;

    if (parse_Layout())
    {
        tokenAfterLayoutParsing = *currentToken;

//        ++currentToken;
        if (currentToken->type() == EOL)
        {
            return true;
        }
    }

    currentToken = firstToken;
    return false;
}

bool DeclarationParser::parse_Constant()
{
    auto savedToken = currentToken;
    if (currentToken->type() != STRING)
    {
        return false;
    }

    string tokenContents;
    tokenContents = currentToken->contents();
    auto contentChar = tokenContents.begin();
    auto contentEnd = tokenContents.end();

    if (!parse_Alpha(*contentChar))
    {
        currentToken = savedToken;
        return false;
    }

    ++contentChar;

    while (contentChar != contentEnd)
    {
        if (!parse_Alpha(*contentChar) &&
            !parse_Digit(*contentChar))
        {
            break;
        }
        ++contentChar;
    }

    ++currentToken;

    if (currentToken->type() != EQUAL)
    {
        currentToken = savedToken;
        return false;
    }

    ++currentToken;

    if (!parse_Integer())
    {
        currentToken = savedToken;
        return false;
    }

    return true;
}

bool DeclarationParser::parse_Label()
{
    auto savedToken = currentToken;
    if (currentToken->type() != STRING)
    {
        return false;
    }

    string tokenContents;
    tokenContents = currentToken->contents();
    auto contentChar = tokenContents.begin();
    auto contentEnd = tokenContents.end();

    if (!parse_Alpha(*contentChar))
    {
        currentToken = savedToken;
        return false;
    }

    ++contentChar;

    while (contentChar != contentEnd)
    {
        if (!parse_Alpha(*contentChar) &&
            !parse_Digit(*contentChar))
        {
            break;
        }
        ++contentChar;
    }

    if (*contentChar != ':')
    {
        currentToken = savedToken;
        return false;
    }

    return true;
}

bool DeclarationParser::parse_Layout()
{
    auto savedToken = currentToken;
    auto tokensEnd = lineOfTokens.end();

    if (parse_IntLayout())
    {
        ++currentToken;

        if (parse_Integer())
        {
            ++currentToken;

            while (currentToken != tokensEnd)
            {
                if (currentToken->type() != SEP)
                {
                    break;
                }

                ++currentToken;

                if (currentToken != tokensEnd &&
                    !parse_Integer())
                {
                    currentToken = savedToken;
                    return false;
                }

                ++currentToken;
            }

            return true;
        }
    }

    currentToken = savedToken;

    if (parse_StringLayout())
    {
        ++currentToken;

        if (parse_String())
        {
            ++currentToken;
            return true;
        }
    }

    currentToken = savedToken;
    return false;
}

bool DeclarationParser::parse_IntLayout()
{
    auto savedToken = currentToken;
    if (currentToken->type() != STRING)
    {
        return false;
    }

    string tokenContents;
    tokenContents = currentToken->contents();

    if (tokenContents == ".word" ||
        tokenContents == ".half" ||
        tokenContents == ".byte" ||
        tokenContents == ".space")
    {
        return true;
    }

    currentToken = savedToken;
    return false;
}

bool DeclarationParser::parse_StringLayout()
{
    auto savedToken = currentToken;
    if (currentToken->type() != STRING)
    {
        return false;
    }

    string tokenContents;
    tokenContents = currentToken->contents();

    if (tokenContents == ".ascii" ||
        tokenContents == ".asciiz")
    {
        return true;
    }

    currentToken = savedToken;
    return false;
}

bool DeclarationParser::parse_Integer()
{
    auto savedToken = currentToken;
    if (currentToken->type() != STRING)
    {
        return false;
    }

    string tokenContents;
    tokenContents = currentToken->contents();

    auto currentChar = tokenContents.begin();
    auto charEnd = tokenContents.end();

    if (*currentChar == '+')
    {
        ++currentChar;
    }
    else if (*currentChar == '-')
    {
        ++currentChar;
    }

    while (currentChar != charEnd)
    {
        if (!parse_Digit(*currentChar))
        {
            currentToken = savedToken;
            return false;
        }

        ++currentChar;
    }

    return true;
}

bool DeclarationParser::parse_String()
{
    auto savedToken = currentToken;
    if (currentToken->type() != STRING_DELIM)
    {
        return false;
    }

    ++currentToken;

    if (currentToken->type() != STRING)
    {
        currentToken = savedToken;
        return false;
    }

    string tokenContents;
    tokenContents = currentToken->contents();

    auto currentChar = tokenContents.begin();
    auto charEnd = tokenContents.end();

    while (currentChar != charEnd)
    {
        if (!parse_Char(*currentChar))
        {
            currentToken = savedToken;
            return false;
        }

        ++currentChar;
    }

    ++currentToken;
    if (currentToken->type() != STRING_DELIM)
    {
        currentToken = savedToken;
        return false;
    }

    return true;
}

bool DeclarationParser::parse_Alpha(char currentChar)
{
    return isalpha(currentChar);
}

bool DeclarationParser::parse_Digit(char currentChar)
{
    return isdigit(currentChar);
}

bool DeclarationParser::parse_Char(char currentChar)
{
    return isprint(currentChar);
}















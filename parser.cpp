#include "parser.h"

parser::parser()
{
    tokenizer;
    tokenStream;
    tokensOnCurrentLine;

    streamParsedSafely = false;

    declarationProcessor = nullptr;
    instructionProcessor = nullptr;
}

bool parser::parseStream(std::istream& streamToParse)
{
    tokenizer.tokenizeStream(streamToParse);

    tokenStream = tokenizer.getTokens();
    tokenStreamSafeCopy = tokenizer.getTokens();
    auto firstToken = tokenStream.begin();
    auto tokenEnd = tokenStream.end();

    tokenIter = tokenStream.begin();

    while (tokenIter != tokenEnd &&
           streamParsedSafely)
    {
        checkForGrammarChanges();

        if (dataGrammarActive)
        {
            streamParsedSafely = dataGrammarParsing();
        }
        else if (textGrammarActive)
        {
            streamParsedSafely = textGrammarParsing();
        }

        updateTokenIter();
    }

    return true;
}

// TODO: function to grab current line / next line (until EOL or EOF) of tokens
//      for parsers.

// TODO: function to determine grammar?

bool parser::dataGrammarParsing()
{
    getAllTokensOnCurrentLine();

    if (declarationProcessor != nullptr)
    {
        delete declarationProcessor;
        declarationProcessor = nullptr;
    }

    declarationProcessor = new DeclarationParser(tokensOnCurrentLine);
    return declarationProcessor->parse_Declaration();
}

bool parser::textGrammarParsing()
{
    getAllTokensOnCurrentLine();

    if (instructionProcessor != nullptr)
    {
        delete instructionProcessor;
        instructionProcessor = nullptr;
    }

    instructionProcessor = new InstructionParser(tokensOnCurrentLine);
    return instructionProcessor->parse_Instruction();
}


void parser::checkForGrammarChanges()
{
    auto savedTokenIter = tokenIter;

    if (checkIfDataGrammar())
    {
        dataGrammarActive = true;
        textGrammarActive = false;
    }
    else if (checkIfTextGrammar())
    {
        dataGrammarActive = false;
        textGrammarActive = true;
    }

    tokenIter = savedTokenIter;
}

bool parser::checkIfDataGrammar()
{
    auto savedTokenIter = tokenIter;

    if (tokenIter->type() != STRING)
    {
        return false;
    }

    if (tokenIter->contents() != ".data")
    {
        return false;
    }

    if ((++tokenIter)->type() != EOL)
    {
        tokenIter = savedTokenIter;
        return false;
    }

    return true;
}

bool parser::checkIfTextGrammar()
{
    auto savedTokenIter = tokenIter;

    if (tokenIter->type() != STRING)
    {
        return false;
    }

    if (tokenIter->contents() != ".text")
    {
        return false;
    }

    if ((++tokenIter)->type() != EOL)
    {
        tokenIter = savedTokenIter;
        return false;
    }

    return true;
}

void parser::getAllTokensOnCurrentLine()
{
    auto currentToken = tokenIter;
    auto tokensEnd = tokenStream.end();

    tokensOnCurrentLine.clear();

    while (currentToken != tokensEnd &&
           currentToken->type() != EOL)
    {
        tokensOnCurrentLine.push_back(*currentToken);
        ++currentToken;
    }

    if (currentToken != tokensEnd)
    {
        if (currentToken->type() == EOL)
        {
            tokensOnCurrentLine.push_back(*currentToken);
        }

        tokenIter = (++currentToken);
    }
    else
    {
        tokenIter = currentToken;
    }
}

void parser::updateTokenIter()
{
    auto tokenIncrement = tokensOnCurrentLine.size();
    unsigned long step = 0;

    while (step < tokenIncrement)
    {
        ++tokenIter;
    }
}






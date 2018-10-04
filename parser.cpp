#include "parser.h"

parser::parser()
{
    tokenizer;
    tokenStream;
    tokensOnCurrentLine;
    currentLineNum = 1;

    streamParsedSafely = true;

    dataGrammarActive = false;
    textGrammarActive = false;

    declarationProcessor = nullptr;
    instructionProcessor = nullptr;
}

bool parser::parseStream(std::istream& streamToParse)
{
    tokenizer.tokenizeStream(streamToParse);

    tokenStream = tokenizer.getTokens();
    tokenStreamSafeCopy = tokenizer.getTokens();
    auto firstToken = tokenStream.begin();
    tokensEnd = tokenStream.end();

    tokenIter = tokenStream.begin();
    tokenAtStartOfCurrentLine = tokenStream.begin();

    if (!tokenStream.empty())
    {
        currentLineNum = firstToken->line();
    }

    int loopCounter = 0;
    int grammarChangeCounter = 0;
    int dataGrammarCounter = 0;
    int textGrammarCounter = 0;
    int elseOptionGrammar = 0;

    token tokenStateAtStartOfLoop = *tokenIter;
    token tokenStateInMiddleOfLoop = *tokenIter;
    token tokenStateAtEndOfLoop = *tokenIter;


    while (tokenIter != tokensEnd /*&&
           streamParsedSafely)*/)
    {
        if (checkForGrammarChanges())
        {
            ++tokenIter;
            ++grammarChangeCounter;
        }
        else if (dataGrammarActive)
        {
            streamParsedSafely = dataGrammarParsing();

            ++dataGrammarCounter;
        }
        else if (textGrammarActive)
        {
            streamParsedSafely = textGrammarParsing();

            ++textGrammarCounter;
        }
        else
        {
            ++elseOptionGrammar;
        }

        tokenStateInMiddleOfLoop = *tokenIter;

        updateTokenIter();
        getAllTokensOnCurrentLine();

        tokenStateAtEndOfLoop = *tokenIter;

        ++loopCounter;
    }

    return streamParsedSafely;
}

bool parser::dataGrammarParsing()
{
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
    if (instructionProcessor != nullptr)
    {
        delete instructionProcessor;
        instructionProcessor = nullptr;
    }

    instructionProcessor = new InstructionParser(tokensOnCurrentLine);
    return instructionProcessor->parse_Instruction();
}


bool parser::checkForGrammarChanges()
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
    else
    {
        tokenIter = savedTokenIter;
        return false;
    }

    return true;
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
    ++currentLineNum;

    token debugStartOfCurrentLineToken = *tokenIter;

    tokensOnCurrentLine.clear();

    while (tokenIter != tokensEnd &&
           tokenIter->line() == currentLineNum)
    {
        tokensOnCurrentLine.push_back(*tokenIter);
        ++tokenIter;
    }
}

void parser::updateTokenIter()
{
    int tokenIncrCounter = 0;

    while (tokenAtStartOfCurrentLine != tokensEnd &&
           tokenAtStartOfCurrentLine->line() != currentLineNum)
    {
        ++tokenAtStartOfCurrentLine;
        ++tokenIncrCounter;
    }
}






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
    auto tokenEnd = tokenStream.end();

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

    while (tokenIter != tokenEnd &&
           streamParsedSafely)
    {
        getAllTokensOnCurrentLine();

        if (checkForGrammarChanges())
        {
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

        updateTokenIter();

        ++loopCounter;
    }

    return streamParsedSafely;
}

// TODO: function to grab current line / next line (until EOL or EOF) of tokens
//      for parsers.

// TODO: function to determine grammar?

bool parser::dataGrammarParsing()
{
//    getAllTokensOnCurrentLine();

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
//    getAllTokensOnCurrentLine();

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
    tokenIter = tokenAtStartOfCurrentLine;

    token debugStartOfCurrentLineToken = *tokenIter;


    auto tokensEnd = tokenStream.end();

    tokensOnCurrentLine.clear();

    while (tokenIter != tokensEnd &&
           tokenIter->line() == currentLineNum)
    {
        tokensOnCurrentLine.push_back(*tokenIter);
        ++tokenIter;
    }

//    while (currentToken != tokensEnd &&
//           currentToken->line() == currentLineNum)
//    {
//        tokensOnCurrentLine.push_back(*currentToken);
//        ++currentToken;
//    }

//    if (tokenIter != tokensEnd)
//    {
//        if (tokenIter->type() == EOL)
//        {
//            tokensOnCurrentLine.push_back(*tokenIter);
//        }
//    }

    tokenIter = tokenAtStartOfCurrentLine;
    ++currentLineNum;
}

void parser::updateTokenIter()
{
    auto tokensEnd = tokenStream.end();

//    auto tokenIncrement = tokensOnCurrentLine.size();
//    unsigned long step = 0;

    int tokenIncrCounter = 0;

    while (tokenAtStartOfCurrentLine != tokensEnd &&
           tokenAtStartOfCurrentLine->line() != currentLineNum)
    {
        ++tokenAtStartOfCurrentLine;
//        ++step;

        ++tokenIncrCounter;
    }
}






#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"
#include "DeclarationParser.h"
#include "InstructionParser.h"

class parser
{
public:

    parser();
//    parser(const string& fileToParse);

    bool parseStream(std::istream& streamToParse);
//    bool isParsingSuccessful();

    void checkForGrammarChanges();
    bool checkIfDataGrammar();
    bool checkIfTextGrammar();

    bool dataGrammarParsing();
    bool textGrammarParsing();

private:

    void getAllTokensOnCurrentLine();
    void updateTokenIter();

    lexer tokenizer;
    DeclarationParser* declarationProcessor;
    InstructionParser* instructionProcessor;

    tokenList::iterator tokenIter;
    tokenList tokenStream;
    tokenList tokenStreamSafeCopy;
    tokenList tokensOnCurrentLine;

    bool dataGrammarActive;
    bool textGrammarActive;

    bool streamParsedSafely;


};

#endif // PARSER_H

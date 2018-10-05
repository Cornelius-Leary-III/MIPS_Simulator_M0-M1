#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"
#include "DeclarationParser.h"
#include "InstructionParser.h"

#include <vector>
using std::vector;

#include <sstream>
using std::stringstream;

class parser
{
public:

    parser(std::istream& streamToParse);

    bool parseStream();

    bool checkForGrammarChanges();
    bool checkIfDataGrammar();
    bool checkIfTextGrammar();

    bool dataGrammarParsing();
    bool textGrammarParsing();

private:

    void getAllTokensOnCurrentLine();
    void updateTokenIter();
    void groupTokensByLine();

    vector<tokenVector> fileSplitUpByLines;
    vector<tokenVector>::iterator fileLineIter;
    vector<tokenVector>::iterator fileEnd;

    lexer tokenizer;
    DeclarationParser* declarationProcessor;
    InstructionParser* instructionProcessor;

    tokenVector::iterator tokenIter;
    tokenVector::iterator tokensEnd;
    tokenVector tokenStream;
    tokenVector tokensOnCurrentLine;
    size_t currentLineNum;

    bool dataGrammarActive;
    bool textGrammarActive;
    bool streamParsedSafely;


};

#endif // PARSER_H

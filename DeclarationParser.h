#ifndef DECLARATIONPARSER_H
#define DECLARATIONPARSER_H

#include "token.h"

class DeclarationParser
{
public:
    DeclarationParser(const tokenList& currentLineToParse);

    bool parse_Declaration();
    bool parse_Constant();
    bool parse_Label();
    bool parse_Layout();
    bool parse_IntLayout();
    bool parse_StringLayout();
    bool parse_Integer();
    bool parse_String();
    bool parse_Digit();
    bool parse_Alpha();
    bool parse_Char();

private:

    tokenList lineOfTokens;
    tokenList::iterator currentToken;

};

#endif // DECLARATIONPARSER_H

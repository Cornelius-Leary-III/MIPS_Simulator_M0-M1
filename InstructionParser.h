#ifndef INSTRUCTIONPARSER_H
#define INSTRUCTIONPARSER_H

#include "token.h"

class InstructionParser
{
public:
    InstructionParser(const tokenVector& currentLineToParse);

    bool parse_Instruction();
    bool parse_LabelForInstruction();
    bool parse_Operation();
    bool parse_Register();
    bool parse_MemoryReference();
    bool parse_Source();
    bool parse_Immediate();
    bool parse_DataMovementInstruction();
    bool parse_IntegerArithmeticInstruction();
    bool parse_LogicalInstruction();
    bool parse_ControlInstruction();

private:

    tokenVector lineOfTokens;
    tokenVector::iterator currentToken;

};

#endif // INSTRUCTIONPARSER_H

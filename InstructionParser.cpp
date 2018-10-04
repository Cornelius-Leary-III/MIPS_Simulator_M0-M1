#include "InstructionParser.h"

InstructionParser::InstructionParser(const tokenList& currentLineToParse)
{
    lineOfTokens = currentLineToParse;
    currentToken = lineOfTokens.begin();
}

bool InstructionParser::parse_Instruction()
{
    return true;
}

bool InstructionParser::parse_Operation()
{
    return true;
}

bool InstructionParser::parse_DataMovementInstruction()
{
    return true;
}

bool InstructionParser::parse_IntegerArithmeticInstruction()
{
    return true;
}

bool InstructionParser::parse_LogicalInstruction()
{
    return true;
}

bool InstructionParser::parse_ControlInstruction()
{
    return true;
}

bool InstructionParser::parse_MemoryReference()
{
    return true;
}

bool InstructionParser::parse_Source()
{
    return true;
}

bool InstructionParser::parse_LabelForInstruction()
{
    return true;
}

bool InstructionParser::parse_Immediate()
{
    return true;
}

bool InstructionParser::parse_Register()
{
    return true;
}






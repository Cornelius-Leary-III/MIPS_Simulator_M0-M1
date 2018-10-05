#include "InstructionParser.h"

InstructionParser::InstructionParser(const tokenVector& currentLineToParse)
{
    lineOfTokens = currentLineToParse;
    currentToken = lineOfTokens.begin();
    lineEnd = lineOfTokens.end();
}

bool InstructionParser::parse_Instruction()
{
    auto firstToken = currentToken;

    if (currentToken->type() == EOL)
    {
        return true;
    }
    else if (parse_LabelForInstruction())
    {
        ++currentToken;
        if (currentToken->type() == EOL)
        {
            return true;
        }
    }

    if (parse_Operation())
    {
        ++currentToken;
        if (currentToken->type() == EOL)
        {
            return true;
        }
    }

    currentToken = firstToken;
    return false;
}

bool InstructionParser::parse_Operation()
{
    auto firstToken = currentToken;

    if (currentToken->type() != STRING)
    {
        currentToken = firstToken;
        return false;
    }

    if (currentToken->contents() == "nop")
    {
        return true;
    }

    if (parse_DataMovementInstruction())
    {
        return true;
    }

    currentToken = firstToken;

    if (parse_IntegerArithmeticInstruction())
    {
        return true;
    }

    currentToken = firstToken;

    if (parse_LogicalInstruction())
    {
        return true;
    }

    currentToken = firstToken;

    if (parse_ControlInstruction())
    {
        return true;
    }

    currentToken = firstToken;
    return false;
}

bool InstructionParser::parse_DataMovementInstruction()
{
    auto firstToken = currentToken;

    if (parse_DMI_2_args())
    {
        return true;
    }

    currentToken = firstToken;

    if (parse_DMI_move())
    {
        return true;
    }

    currentToken = firstToken;
    return false;
}

bool InstructionParser::parse_DMI_2_args()
{
    auto firstToken = currentToken;

    if (parse_DMI_2_args_load())
    {
        return true;
    }

    currentToken = firstToken;

    if (parse_DMI_2_args_store())
    {
        return true;
    }

    currentToken = firstToken;
    return false;
}

bool InstructionParser::parse_DMI_2_args_load()
{
    auto firstToken = currentToken;

    if (currentToken->type() != STRING)
    {
        currentToken = firstToken;
        return false;
    }

    if (currentToken->contents() == "lw" ||
        currentToken->contents() == "lh" ||
        currentToken->contents() == "lb" ||
        currentToken->contents() == "la")
    {
        ++currentToken;
        if (!parse_Register())
        {
            currentToken = firstToken;
            return false;
        }

        ++currentToken;
        if (currentToken->type() != SEP)
        {
            currentToken = firstToken;
            return false;
        }

        ++currentToken;
        if (!parse_MemoryReference())
        {
            currentToken = firstToken;
            return false;
        }

        return true;
    }
    else if (currentToken->contents() == "li")
    {
        ++currentToken;
        if (!parse_Register())
        {
            currentToken = firstToken;
            return false;
        }

        ++currentToken;
        if (currentToken->type() != SEP)
        {
            currentToken = firstToken;
            return false;
        }

        ++currentToken;
        if (!parse_Immediate())
        {
            currentToken = firstToken;
            return false;
        }

        return true;
    }
    else
    {
        currentToken = firstToken;
        return false;
    }
}

bool InstructionParser::parse_DMI_2_args_store()
{
    auto firstToken = currentToken;

    if (currentToken->type() != STRING)
    {
        currentToken = firstToken;
        return false;
    }

    if (currentToken->contents() == "sw" ||
        currentToken->contents() == "sh" ||
        currentToken->contents() == "sb")
    {
        ++currentToken;
        if (!parse_Register())
        {
            currentToken = firstToken;
            return false;
        }

        ++currentToken;
        if (currentToken->type() != SEP)
        {
            currentToken = firstToken;
            return false;
        }

        ++currentToken;
        if (!parse_MemoryReference())
        {
            currentToken = firstToken;
            return false;
        }

        return true;
    }

    currentToken = firstToken;
    return false;
}

bool InstructionParser::parse_DMI_move()
{
    auto firstToken = currentToken;

    if (currentToken->type() != STRING)
    {
        currentToken = firstToken;
        return false;
    }

    if (currentToken->contents() == "move")
    {
        ++currentToken;
        if (!parse_Register())
        {
            currentToken = firstToken;
            return false;
        }

        ++currentToken;
        if (currentToken->type() != SEP)
        {
            currentToken = firstToken;
            return false;
        }

        ++currentToken;
        if (!parse_Register())
        {
            currentToken = firstToken;
            return false;
        }

        return true;
    }
    else if (currentToken->contents() == "mfhi" ||
             currentToken->contents() == "mflo" ||
             currentToken->contents() == "mthi" ||
             currentToken->contents() == "mtlo")
    {
        ++currentToken;
        if (!parse_Register())
        {
            currentToken = firstToken;
            return false;
        }

        return true;
    }

    currentToken = firstToken;
    return false;
}

bool InstructionParser::parse_IntegerArithmeticInstruction()
{
    auto firstToken = currentToken;

    if (parse_IAI_2_args())
    {
        return true;
    }

    currentToken = firstToken;

    if (parse_IAI_3_args())
    {
        return true;
    }

    currentToken = firstToken;

    if (parse_IAI_div())
    {
        return true;
    }

    currentToken = firstToken;
    return false;
}

bool InstructionParser::parse_IAI_3_args()
{
    auto firstToken = currentToken;

    if (currentToken->type() != STRING)
    {
        currentToken = firstToken;
        return false;
    }

    if (currentToken->contents() == "add" ||
        currentToken->contents() == "addu" ||
        currentToken->contents() == "sub" ||
        currentToken->contents() == "subu" ||
        currentToken->contents() == "mul" ||
        currentToken->contents() == "mulo" ||
        currentToken->contents() == "mulou" ||
        currentToken->contents() == "rem" ||
        currentToken->contents() == "remu")
    {
        ++currentToken;
        if (!parse_Register())
        {
            currentToken = firstToken;
            return false;
        }

        ++currentToken;
        if (currentToken->type() != SEP)
        {
            currentToken = firstToken;
            return false;
        }

        ++currentToken;
        if (!parse_Register())
        {
            currentToken = firstToken;
            return false;
        }

        ++currentToken;
        if (currentToken->type() != SEP)
        {
            currentToken = firstToken;
            return false;
        }

        ++currentToken;
        if (!parse_Source())
        {
            currentToken = firstToken;
            return false;
        }

        return true;
    }

    currentToken = firstToken;
    return false;
}

bool InstructionParser::parse_IAI_2_args()
{
    auto firstToken = currentToken;

    if (currentToken->type() != STRING)
    {
        currentToken = firstToken;
        return false;
    }

    if (currentToken->contents() == "mult" ||
        currentToken->contents() == "multu" ||
        currentToken->contents() == "abs" ||
        currentToken->contents() == "neg" ||
        currentToken->contents() == "negu")
    {
        ++currentToken;
        if (!parse_Register())
        {
            currentToken = firstToken;
            return false;
        }

        ++currentToken;
        if (currentToken->type() != SEP)
        {
            currentToken = firstToken;
            return false;
        }

        ++currentToken;
        if (!parse_Register())
        {
            currentToken = firstToken;
            return false;
        }

        return true;
    }

    currentToken = firstToken;
    return false;
}

bool InstructionParser::parse_IAI_div()
{
    auto firstToken = currentToken;

    if (currentToken->type() != STRING)
    {
        currentToken = firstToken;
        return false;
    }

    if (currentToken->contents() == "div" ||
        currentToken->contents() == "divu")
    {
        ++currentToken;
        if (!parse_Register())
        {
            currentToken = firstToken;
            return false;
        }

        ++currentToken;
        if (currentToken->type() != SEP)
        {
            currentToken = firstToken;
            return false;
        }

        ++currentToken;
        if (!parse_Register())
        {
            currentToken = firstToken;
            return false;
        }

        ++currentToken;
        if (currentToken != lineEnd)
        {
            if (currentToken->type() == SEP)
            {
                ++currentToken;
                if (parse_Source())
                {
                    return true;
                }

                currentToken = firstToken;
                return false;
            }
        }

        --currentToken;
        return true;
    }

    currentToken = firstToken;
    return false;
}

bool InstructionParser::parse_LogicalInstruction()
{
    auto firstToken = currentToken;

    if (parse_LI_3_args())
    {
        return true;
    }

    currentToken = firstToken;

    if (parse_LI_not())
    {
        return true;
    }

    currentToken = firstToken;
    return false;
}

bool InstructionParser::parse_LI_3_args()
{
    auto firstToken = currentToken;

    if (currentToken->type() != STRING)
    {
        currentToken = firstToken;
        return false;
    }

    if (currentToken->contents() == "and" ||
        currentToken->contents() == "nor" ||
        currentToken->contents() == "or" ||
        currentToken->contents() == "xor")
    {
        ++currentToken;
        if (!parse_Register())
        {
            currentToken = firstToken;
            return false;
        }

        ++currentToken;
        if (currentToken->type() != SEP)
        {
            currentToken = firstToken;
            return false;
        }

        ++currentToken;
        if (!parse_Register())
        {
            currentToken = firstToken;
            return false;
        }

        ++currentToken;
        if (currentToken->type() != SEP)
        {
            currentToken = firstToken;
            return false;
        }

        ++currentToken;
        if (!parse_Source())
        {
            currentToken = firstToken;
            return false;
        }

        return true;
    }

    currentToken = firstToken;
    return false;
}

bool InstructionParser::parse_LI_not()
{
    auto firstToken = currentToken;

    if (currentToken->type() != STRING)
    {
        currentToken = firstToken;
        return false;
    }

    if (currentToken->contents() == "not")
    {
        ++currentToken;
        if (!parse_Register())
        {
            currentToken = firstToken;
            return false;
        }

        ++currentToken;
        if (currentToken->type() != SEP)
        {
            currentToken = firstToken;
            return false;
        }

        ++currentToken;
        if (!parse_Source())
        {
            currentToken = firstToken;
            return false;
        }

        return true;
    }

    currentToken = firstToken;
    return false;
}

bool InstructionParser::parse_ControlInstruction()
{
    auto firstToken = currentToken;

    if (parse_CI_3_args())
    {
        return true;
    }

    currentToken = firstToken;

    if (parse_CI_jump())
    {
        return true;
    }

    currentToken = firstToken;
    return false;
}

bool InstructionParser::parse_CI_3_args()
{
    auto firstToken = currentToken;

    if (currentToken->type() != STRING)
    {
        currentToken = firstToken;
        return false;
    }

    if (currentToken->contents() == "beq" ||
        currentToken->contents() == "bne" ||
        currentToken->contents() == "blt" ||
        currentToken->contents() == "ble" ||
        currentToken->contents() == "bgt" ||
        currentToken->contents() == "bge")
    {
        ++currentToken;
        if (!parse_Register())
        {
            currentToken = firstToken;
            return false;
        }

        ++currentToken;
        if (currentToken->type() != SEP)
        {
            currentToken = firstToken;
            return false;
        }

        ++currentToken;
        if (!parse_Source())
        {
            currentToken = firstToken;
            return false;
        }

        ++currentToken;
        if (currentToken->type() != SEP)
        {
            currentToken = firstToken;
            return false;
        }

        ++currentToken;
        if (!parse_LabelForInstruction())
        {
            currentToken = firstToken;
            return false;
        }

        return true;
    }

    currentToken = firstToken;
    return false;
}

bool InstructionParser::parse_CI_jump()
{
    auto firstToken = currentToken;

    if (currentToken->type() != STRING)
    {
        currentToken = firstToken;
        return false;
    }

    if (currentToken->contents() == "j")
    {
        ++currentToken;
        if (!parse_LabelForInstruction())
        {
            currentToken = firstToken;
            return false;
        }

        return true;
    }

    currentToken = firstToken;
    return false;
}

bool InstructionParser::parse_MemoryReference()
{
    auto firstToken = currentToken;

    if (currentToken->type() != STRING)
    {
        currentToken = firstToken;
        return false;
    }

    if (parse_LabelForInstruction())
    {
        return true;
    }

    currentToken = firstToken;

    if (parse_Register())
    {
        return true;
    }

    currentToken = firstToken;

    if (currentToken->type() == STRING)
    {
        ++currentToken;
    }

    if (currentToken->type() == OPEN_PAREN)
    {
        ++currentToken;

        if (parse_Register())
        {
            ++currentToken;

            if (currentToken->type() == CLOSE_PAREN)
            {
                return true;
            }
        }
    }

    currentToken = firstToken;
    return false;
}

bool InstructionParser::parse_Source()
{
    auto firstToken = currentToken;

    if (currentToken->type() != STRING)
    {
        currentToken = firstToken;
        return false;
    }

    if (parse_Register())
    {
        return true;
    }

    currentToken = firstToken;

    if (parse_Immediate())
    {
        return true;
    }

    currentToken = firstToken;
    return false;
}

bool InstructionParser::parse_LabelForInstruction()
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

bool InstructionParser::parse_Immediate()
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

    if (!parse_Alpha(*contentChar) &&
        !parse_Digit(*contentChar))
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
            currentToken = savedToken;
            return false;
        }
        ++contentChar;
    }

    return true;
}

bool InstructionParser::parse_Register()
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

    if (contentChar != contentEnd &&
        *contentChar != '$')
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
            currentToken = savedToken;
            return false;
        }
        ++contentChar;
    }

    return true;
}

bool InstructionParser::parse_Alpha(char currentChar)
{
    return isalpha(currentChar);
}

bool InstructionParser::parse_Digit(char currentChar)
{
    return isdigit(currentChar);
}

bool InstructionParser::parse_Char(char currentChar)
{
    return isprint(currentChar);
}




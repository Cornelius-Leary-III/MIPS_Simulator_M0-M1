#include "token.h"

token::token(TokenType newType,
             std::size_t newIdNumber,
             std::size_t newLineNumber)
    : typeOfToken(newType),
      idNumber(newIdNumber),
      lineNumber(newLineNumber)
{
}

token::token(TokenType newType,
             std::size_t newIdNumber,
             std::size_t newLineNumber,
             const std::string& newContents)
    : typeOfToken(newType),
      idNumber(newIdNumber),
      lineNumber(newLineNumber),
      tokenContents(newContents)
{
}

TokenType token::type() const
{
    return typeOfToken;
}

std::size_t token::id() const
{
    return idNumber;
}

std::size_t token::line() const
{
    return lineNumber;
}

std::string token::contents() const
{
    return tokenContents;
}

bool operator==(const token& lhs, const token& rhs)
{
    return (lhs.type() == rhs.type()) &&
            (lhs.id() == rhs.id()) &&
            (lhs.line() == rhs.line()) &&
            (lhs.contents() == rhs.contents());
}

bool operator!=(const token& lhs, const token& rhs)
{
    return !(lhs == rhs);
}

std::ostream& operator<<(std::ostream& oss, const token& tokenToPass)
{
    std::string typeString;

    switch (tokenToPass.type())
    {
    case EOL:
    {
        typeString = "EOL";
        break;
    }
    case SEP:
    {
        typeString = "SEP";
        break;
    }
    case EQUAL:
    {
        typeString = "EQUAL";
        break;
    }
    case OPEN_PAREN:
    {
        typeString = "OPEN_PAREN";
        break;
    }
    case CLOSE_PAREN:
    {
        typeString = "CLOSE_PAREN";
        break;
    }
    case STRING_DELIM:
    {
        typeString = "STRING_DELIM";
        break;
    }
    case STRING:
    {
        typeString = "STRING";
        break;
    }
    case ERROR:
    {
        typeString = "ERROR";
        break;
    }
    }

    oss << "\t\tToken #" << std::setw(5) << tokenToPass.id()
        << " on line #" << std::setw(5) << tokenToPass.line()
        << std::setw(15) << typeString;

    if (!tokenToPass.contents().empty())
    {
        oss << " -->___" << tokenToPass.contents();
    }
    if (tokenToPass.type() == EOL)
    {
        oss << std::endl;
    }

    return oss;
}






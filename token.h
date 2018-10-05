#ifndef TOKEN_H
#define TOKEN_H

#include <cstddef>
//#include <list>
#include <vector>

#include <ostream>
#include <string>
#include <iomanip>

enum TokenType
{
    EOL,            // 0
    SEP,            // 1
    EQUAL,          // 2
    OPEN_PAREN,     // 3
    CLOSE_PAREN,    // 4
    STRING_DELIM,   // 5
    STRING,         // 6
    ERROR           // 7
};

class token
{
public:

    token(TokenType newType, std::size_t newIdNumber, std::size_t newLineNumber);
    token(TokenType newType, std::size_t newIdNumber, std::size_t newLineNumber, const std::string& newContents);

    TokenType type() const;
    std::size_t id() const;
    std::size_t line() const;
    std::string contents() const;

private:

    TokenType typeOfToken;
    std::size_t idNumber;
    std::size_t lineNumber;
    std::string tokenContents;
};

bool operator==(const token& lhs, const token& rhs);
bool operator!=(const token& lhs, const token& rhs);
std::ostream& operator<<(std::ostream& oss, const token& tokenToPass);

//typedef std::list<token> tokenList;
using tokenVector = std::vector<token>;

#endif // TOKEN_H

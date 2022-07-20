#pragma one
#include "tokenType.hpp"
#include <string>
class Token
{
private:
    /* data */
public:
    explicit Token(TokenType type,const std::string& tokenStr,int lineNo)
    :type_(type),
    tokenStr_(tokenStr),
    lineNo_(lineNo)
    {};
    TokenType& tokenType()
    {
        return type_;
    }
    std::string tokenStr()
    {
        return tokenStr_;
    }
    int lineNo()
    {
        return lineNo_;
    }

private:
    TokenType type_;
    std::string tokenStr_;
    int lineNo_;
};


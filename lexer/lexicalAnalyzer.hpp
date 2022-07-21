#pragma one
#include <string>
#include "token.hpp"
#include "lexer.hpp"
#include <ctype.h>
#include <map>


class LexicalAnalyzer
{
public:
    LexicalAnalyzer(std::string& filePath)
    :filePath_(filePath)
    {

    };

private:
    Token nextToken(const char* codePtr,int& lineNo);
    void nextTokenStartStage(const char* codePtr,
                            LexerStage &lexerStage, 
                            TokenType &tokenType, 
                            std::string &tokenStr, 
                            int &lineNo);
    void nextTokenInIdStage(const char* codePtr,
                            LexerStage &lexerStage, 
                            TokenType &tokenType, 
                            std::string &tokenStr, 
                            int &lineNo);

                            
private:
    std::string filePath_;
    std::map<std::string,TokenType> keyWord_ = 
    {
        { "if",         TokenType::If},
        { "else",       TokenType::Else},
        { "int",        TokenType::Int},
        { "while",      TokenType::While},
        { "return",     TokenType::Return},
        { "void",       TokenType::Void},
    };
};

Token LexicalAnalyzer::nextToken(const char* codePtr,int& lineNo)
{
    LexerStage stage = LexerStage::Start;
    std::string tokenStr;
    TokenType tokenType;
    while (stage != LexerStage::Done)
    {
        switch (stage)
        {
        case LexerStage::Start:
            nextTokenStartStage(codePtr,stage,tokenType,tokenStr,lineNo);
            break;
        
        case LexerStage::InId:
            nextTokenInIdStage(codePtr,stage,tokenType,tokenStr,lineNo);
            break;
        case LexerStage::InNumber:
            nextTokenInNumberStage(codePtr,stage,tokenType,tokenStr,lineNo);
            break;
        case LexerStage::InDivide:
            nextTokenInDividStage(codePtr,stage,tokenType,tokenStr,lineNo);
            break;
        case LexerStage::InComment:
            nextTokenInCommentStage(codePtr,stage,tokenType,tokenStr,lineNo);
            break;
        case LexerStage::EndComment:
            nextTokenEndCommentStage(codePtr,stage,tokenType,tokenStr,lineNo);
            break;
        case LexerStage::InLess:
            nextTokenInLessStage(codePtr,stage,tokenType,tokenStr,lineNo);
            break;
        case LexerStage::InGreater:
            nextTokenInGreaterStage(codePtr,stage,tokenType,tokenStr,lineNo);
            break;
        case LexerStage::InAssign:
            nextTokenInAssignStage(codePtr,stage,tokenType,tokenStr,lineNo);
            break;
        
        case LexerStage::InNot:
            nextTokenInNotStage(codePtr,stage,tokenType,tokenStr,lineNo);
            break;

        default:
            throw "Invid token";
        }
    }
    
}

void LexicalAnalyzer::nextTokenStartStage(const char* codePtr,
                            LexerStage &lexerStage, 
                            TokenType &tokenType, 
                            std::string &tokenStr, 
                            int &lineNo)
{
    if(isalpha(*codePtr))
    {
        lexerStage = LexerStage::InId;
        tokenStr += *codePtr;
        codePtr++;
    }
    else if(isalnum(*codePtr))
    {
        lexerStage = LexerStage::InNumber;
        tokenStr += *codePtr;
        codePtr++
    }
    else if(isspace(*codePtr))
    {
        if(*codePtr == '\n')
        {
            lineNo++;
        }
    }
    else
    {
        switch (*codePtr)
        {
        case '+':
            lexerStage = LexerStage::Done;
            tokenStr += *codePtr;
            tokenType = TokenType::Plus;
            codePtr++;
            break;

        case '-':
            lexerStage = LexerStage::Done;
            tokenStr += *codePtr;
            tokenType = TokenType::Minus;
            codePtr++;
            break;


        case '*':
            lexerStage = LexerStage::Done;
            tokenStr += *codePtr;
            tokenType = TokenType::Multiply;
            codePtr++;
            break;
        case ',':
            lexerStage = LexerStage::Done;
            tokenStr += *codePtr;
            codePtr++;
            tokenType = TokenType::Comma;
            break;
        case ';':
            lexerStage = LexerStage::Done;
            tokenStr += *codePtr;
            codePtr++;
            tokenType = TokenType::Semicolon;
            break;

        case '(':
            lexerStage = LexerStage::Done;
            tokenStr += *codePtr;
            codePtr++;
            tokenType = TokenType::LeftRoundBracket;
            break;

        case ')':
            lexerStage = LexerStage::Done;
            tokenStr += *codePtr;
            codePtr++;
            tokenType = TokenType::RightRoundBracket;
            break;

        case '[':
            lexerStage = LexerStage::Done;
            tokenStr += *codePtr;
            codePtr++;
            tokenType = TokenType::LeftSquareBracket;
            break;

        case ']':
            lexerStage = LexerStage::Done;
            tokenStr += *codePtr;
            codePtr++;
            tokenType = TokenType::RightSquareBraket;
            break;
        case '{':
            lexerStage = LexerStage::Done;
            tokenStr += *codePtr;
            codePtr++;
            tokenType = TokenType::RightCurlyBraket;
            break;

        case '}':
            lexerStage = LexerStage::Done;
            tokenStr += *codePtr;
            codePtr++;
            tokenType = TokenType::LeftCurlyBraket;
            break;
                case '/':
            lexerStage = LexerStage::InDivide;
            tokenStr += *codePtr;
            codePtr++;
            break;
        case '<':
            lexerStage = LexerStage::InLess;
            tokenStr += *codePtr;
            codePtr++;
            break;
        case '>':
            lexerStage = LexerStage::InGreater;
            tokenStr += *codePtr;
            codePtr++;
            break;
        case '=':
            lexerStage = LexerStage::InAssign;
            tokenStr += *codePtr;
            codePtr++;
            break;
        case '!':
            lexerStage = LexerStage::InNot;
            tokenStr += *codePtr;
            codePtr++;
            break;
        default:
            throw "Invid char";
        }
    }

}


void LexicalAnalyzer::nextTokenInIdStage(const char* codePtr,
                            LexerStage &lexerStage, 
                            TokenType &tokenType, 
                            std::string &tokenStr, 
                            int &lineNo)
{
    
    if(isalpha(*codePtr))
    {
        tokenStr += *codePtr;
        lexerStage = LexerStage::InId;
        codePtr++;
    }
    else
    {
        if(keyWord_.count(tokenStr))
        {
            tokenType = keyWord_[tokenStr];
        }
        else
        {
            tokenType = TokenType::Id;
        }
        lexerStage = LexerStage::Done;
    }






}

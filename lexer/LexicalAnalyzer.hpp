#include <string>
#include "Token.hpp"
#include "TokenType.hpp"
#include "lexer.hpp"
#include <ctype.h>

#pragma one
class LexicalAnalyzer
{
public:
    LexicalAnalyzer(std::string& filePath)
    :filePath_(filePath)
    {

    };

private:
    Token nextToken();
    void nextTokenStartStage(const char* codePtr,
                            LexerStage &lexerStage, 
                            TokenType &tokenType, 
                            std::string &tokenStr, 
                            int &lineNo);
private:
    std::string filePath_;
};

LexicalAnalyzer::nextToken(const char* codePtr,int& lineNo)
{
    LexerStage stage = LexerStage::Start;
    std::string tokenStr;
    TokenType tokeType;
    while (stage !== LexerStage::Done)
    {
        switch (stage)
        {
        case LexerStage::Start:
            nextTokenStartStage(codePtr,lineNo);
            break;
        
        case LexerStage::InId:
            nextTokenInIdStage(codePtr,lineNo);
            break;
        case LexerStage::InNumber:
            nextTokenInNumberStage(codePtr,lineNo);
            break;
        case LexerStage::InDivid:
            nextTokenInDividStage(codePtr,lineNo);
            break;
        case LexerStage::InComment:
            nextTokenInCommentStage(codePtr,lineNo);
            break;
        case LexerStage::EndComment:
            nextTokenEndCommentStage(codePtr,lineNo);
            break;
        case LexerStage::InLess:
            nextTokenInLessStage(codePtr,lineNo);
            break;
        case LexerStage::InGreater:
            nextTokenInGreaterStage(codePtr,lineNo);
            break;
        case LexerStage::InAssign:
            nextTokenInAssignStage(codePtr,lineNo);
            break;
        
        case LexerStage::InNot:
            nextTokenInNotStage(codePtr,lineNo);
            break;

        default:
            throw std::exception("Invid token");
        }
    }
    
}

LexicalAnalyzer::nextTokenStartStage(const char* codePtr,
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
            tokenType = TokenType::;
            codePtr++;
            break;


        case '+':
            lexerStage = LexerStage::Done;
            tokenStr += *codePtr;
            tokenType = TokenType::Plus;
            codePtr++;
            break;





        
        default:
            break;
        }
    }

}

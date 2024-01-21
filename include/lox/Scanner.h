#ifndef SCANNER_H
#define SCANNER_H
#include <string>
#include <vector>
#include "Token.h"
#include "TokenType.h"
#include "Lox.h"



class Scanner{
    public:
        std::string m_src;
        std::vector<Token> m_tokens;
        size_t m_start=0;
        size_t m_current=0;
        size_t m_line = 1;
        Lox* loxptr;
        Scanner(std::string src, Lox* loxptr): m_src(src), m_tokens(), loxptr(loxptr){}
        std::vector<Token> scanTokens();
        void addToken(TokenType);
        void addToken(TokenType, std::string literal);
        void addToken(TokenType, float literal);
        bool matchNext(char expected, std::vector<char>::iterator& begin, std::vector<char>::const_iterator cend);
};

#endif
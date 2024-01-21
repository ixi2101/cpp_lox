#include "lox/Scanner.h"
#include "lox/TokenType.h"
#include "lox/Exceptions.h"
#include <cctype>
#include <cstddef>
#include <exception>
#include <iterator>
#include <unordered_map>
#include <vector>



bool Scanner::matchNext(char expected, std::vector<char>::iterator& iter, std::vector<char>::const_iterator cend){
    if (std::next(iter) == cend){
        return false;
    }
    if (*std::next(iter) == expected){
        std::advance(iter, 1);
        return true;
    }else {
        return false;
    }
    
    
}

static const std::unordered_map<std::string, TokenType> reserved_keywords = {
    {"and", AND},
    {"class", CLASS},
    {"else", ELSE},
    {"false", FALSE},
    {"for", FOR},
    {"fun", FUN },
    {"if",IF },
    {"nil", NIL},
    {"or", OR},
    {"print", PRINT},
    {"return", RETURN},
    {"super", SUPER},
    {"this", THIS},
    {"true", TRUE},
    {"var", VAR},
    {"while", WHILE}
};

std::vector<Token> Scanner::scanTokens(){
    if (m_src.empty()){
        throw lox::EmptySrcString();
    }
    std::vector<Token> tokens;

    auto end = m_src.cend();
    for (auto iter = m_src.begin(); iter != end;){
        char c = *iter;
        auto begin = iter;

        static auto addToken = [&](TokenType ttype){
            Token tkn(ttype, std::string(begin, iter), m_line);
            m_tokens.push_back(tkn);
        };
        static auto string_literal = [&](TokenType type, std::string literal){
            Token tmp(type, std::string(begin, iter+1),  this->m_line);
            tmp.m_literal = literal;
            m_tokens.push_back(tmp);
        };

        static auto float_literal = [&](TokenType type, float literal, std::string lex){
            Token tmp(type, lex,  this->m_line);
            tmp.m_literal = literal;
            m_tokens.push_back(tmp);
        };
        static auto expectNextChar = [&](char ex){
            if (*std::next(iter)==ex){
                std::advance(iter, 1);
            return true;
        }else{
            return false;
        };};


        static auto skipAhead= [&](char e){
            // copy the iter
            auto lookForward = iter;
            while (*lookForward != e){
                std::advance(lookForward, 1);
            }
            iter = lookForward-1;
        };

        static auto stringlit = [&](){
            auto start = iter+1;
            iter++;
            while (*iter != '"'){
                iter++;
            }
            auto literal = std::string(start,iter);
            string_literal(STRING, literal);
            return iter;
        };

        static auto identifier = [&](){
            auto start = iter;
            iter++;
            while(std::isalpha(*iter)){
                iter++;
            }
            std::string text(start, iter);
            if (reserved_keywords.count(text)){
                addToken(reserved_keywords.at(text));
            }else {
                addToken(IDENTIFIER);
            }
            return --iter;
        };
        // std::cout << c << std::endl;
        switch (c){
            case '(': addToken(LEFT_PAREN); break;
            case ')': addToken(RIGHT_PAREN); break;
            case '{': addToken(LEFT_BRACE); break;
            case '}': addToken(RIGHT_BRACE); break;
            case ',': addToken(COMMA); break;
            case '.': addToken(DOT); break;
            case '-': addToken(MINUS); break;
            case '+': addToken(PLUS); break;
            case ';': addToken(SEMICOLON); break;
            case '*': addToken(STAR); break;
            case '!':
                addToken(expectNextChar('=') ? BANG_EQUAL : BANG);
                break;
            case '=':
                addToken(expectNextChar('=') ? EQUAL_EQUAL: EQUAL);
                break;
            case '<':
                addToken(expectNextChar('=') ? LESS_EQUAL: LESS);
                break;
            case '>':
                addToken(expectNextChar('=') ? GREATER_EQUAL: GREATER);
                break;
            case '/':
                if (expectNextChar('/')){
                    skipAhead('\n'); // comment
                    break;
                }else {
                    addToken(SLASH);
                    break;
                }
            case '\n': m_line++; break;
            case '\r':
            case ' ':
            case '\t':
                /// ignore the whitepsace
                break;
            case '"': 
                /// string literal
                iter = stringlit();
                break;
            default: 
                if (std::isdigit(c)){
                    size_t charsParsed;
                    float literal = std::stof(&*iter,&charsParsed);
                    float_literal(NUMBER, literal, std::string(iter, iter+charsParsed));
                    std::advance(iter, charsParsed-1);
                    break;
                }else if ( std::isalpha(c)){
                    // ident
                    iter = identifier();
                    break;
                }
                std::cout << (int)c <<std::endl;
                loxptr->error(m_line, "unexpected token!");
                break;
        }
        iter++;
    }
    return this->m_tokens;
}
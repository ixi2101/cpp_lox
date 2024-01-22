#include <gtest/gtest.h>
#include <vector>
#include <utility>
#include "lox/Scanner.h"
#include "lox/Exceptions.h"
#include "lox/Token.h"
#include "lox/TokenType.h"

TEST(scanner, exceptions){
    std::string test = "some text";
    std::string empty;
    Scanner s(test, nullptr);
    ASSERT_NO_THROW(s.scanTokens());
    Scanner s2(empty, nullptr);
    ASSERT_THROW(s2.scanTokens(), lox::EmptySrcString);
}

TEST(scanner, SingleChars){
    std::vector<std::pair<std::string, TokenType>> cases;
    cases.emplace_back("*", STAR);
    cases.emplace_back("(", LEFT_PAREN);
    cases.emplace_back(")", RIGHT_PAREN);
    cases.emplace_back("{", LEFT_BRACE);
    cases.emplace_back("}", RIGHT_BRACE);
    cases.emplace_back(",", COMMA);
    cases.emplace_back(".", DOT);
    cases.emplace_back("-", MINUS);
    cases.emplace_back("+", PLUS);
    cases.emplace_back("/", SLASH); 
    cases.emplace_back(";", SEMICOLON); 

    for (auto& test_case: cases){
        Lox lox;
        Scanner s(test_case.first, &lox);
        std::vector<Token> parsed = s.scanTokens();
        ASSERT_EQ(parsed.size(), 1);
        ASSERT_EQ(parsed[0].m_type, test_case.second);
    }
}

TEST(scanner, Bang){
    std::string bang("!");
    Scanner b(bang, nullptr);
    
    auto parsed = b.scanTokens();
    ASSERT_EQ(parsed.size(), 1);
    ASSERT_EQ(parsed[0].m_type, BANG);

}
TEST(scanner, NE){
    std::string bangequal("!=");
    Scanner b2(bangequal, nullptr);
    auto parsedbe = b2.scanTokens();
    ASSERT_EQ(parsedbe.size(), 1);
    ASSERT_EQ(parsedbe[0].m_type, BANG_EQUAL);
}
TEST(scanner, GE){
    std::string bangequal(">=");
    Scanner b2(bangequal, nullptr);
    auto parsedbe = b2.scanTokens();
    ASSERT_EQ(parsedbe.size(), 1);
    ASSERT_EQ(parsedbe[0].m_type, GREATER_EQUAL);
}TEST(scanner, LE){
    std::string bangequal("<=");
    Scanner b2(bangequal, nullptr);
    auto parsedbe = b2.scanTokens();
    ASSERT_EQ(parsedbe.size(), 1);
    ASSERT_EQ(parsedbe[0].m_type, LESS_EQUAL);
}

TEST(scanner, GT){
    std::string bangequal(">");
    Scanner b2(bangequal, nullptr);
    auto parsedbe = b2.scanTokens();
    ASSERT_EQ(parsedbe.size(), 1);
    ASSERT_EQ(parsedbe[0].m_type, GREATER);
}TEST(scanner, LT){
    std::string bangequal("<");
    Scanner b2(bangequal, nullptr);
    auto parsedbe = b2.scanTokens();
    ASSERT_EQ(parsedbe.size(), 1);
    ASSERT_EQ(parsedbe[0].m_type, LESS);
}

TEST(scanner, Keywords){
std::vector<std::pair<std::string, TokenType>> test_cases= {
    {"and", AND},   {"class", CLASS}, {"else", ELSE},     {"false", FALSE},
    {"for", FOR},   {"fun", FUN},     {"if", IF},         {"nil", NIL},
    {"or", OR},     {"print", PRINT}, {"return", RETURN}, {"super", SUPER},
    {"this", THIS}, {"true", TRUE},   {"var", VAR},       {"while", WHILE}};
    for (auto& test_case: test_cases){
        Scanner s(test_case.first, nullptr);
        auto parsed = s.scanTokens();
        ASSERT_EQ(parsed.size(), 1);
        ASSERT_EQ(parsed[0].m_type, test_case.second);
    }
}

TEST(scanner, combined){
    std::string testString = R"((+-()*-!/==)";
    Scanner s(testString, nullptr);
    auto parsed = s.scanTokens();
    ASSERT_EQ(parsed.size(), 10);
    ASSERT_EQ(parsed[0].m_type, LEFT_PAREN);
    ASSERT_EQ(parsed[1].m_type, PLUS);
    ASSERT_EQ(parsed[2].m_type, MINUS);
    ASSERT_EQ(parsed[3].m_type, LEFT_PAREN);
    ASSERT_EQ(parsed[4].m_type, RIGHT_PAREN);
    ASSERT_EQ(parsed[5].m_type, STAR);
    ASSERT_EQ(parsed[6].m_type, MINUS);
    ASSERT_EQ(parsed[7].m_type, BANG);
    ASSERT_EQ(parsed[8].m_type, SLASH);
    ASSERT_EQ(parsed[9].m_type, EQUAL_EQUAL);
}
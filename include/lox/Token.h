#ifndef TOKEN_H
#define TOKEN_H

#include "TokenType.h"
#include <any>
#include <iostream>
#include <optional>
#include <string>
#include <variant>

class Token {
public:
  const TokenType m_type;
  std::string m_lexeme;
  std::optional<std::variant<std::string, float>> m_literal = std::nullopt;
  size_t m_line;
  
  Token(TokenType type, std::string lexeme, size_t line)
      : m_type(type), m_lexeme(lexeme), m_line(line) {}

  void printToken() {
    std::string_view typestr = TOKENSTR[this->m_type];

    std::cout << " [line " << this->m_line << "]: " << m_lexeme << " "
              << typestr << " ";
    if (m_literal.has_value()) {
      switch (this->m_type) {
      case NUMBER:
        std::cout << std::get<float>(this->m_literal.value());
        break;
      case STRING:
        std::cout << std::get<std::string>(this->m_literal.value());
        break;
      default:
        break;
      }
    }
    std::cout << " " << std::endl;
  }
};

#endif
#include "lox/Lox.h"
#include "lox/Scanner.h"
#include "lox/Token.h"
#include <fstream>
#include <iostream>

void Lox::runFile(std::string &file_path) {
  std::ifstream file(file_path);
  std::string parsed{(std::istreambuf_iterator<char>(file)),
                     std::istreambuf_iterator<char>()};
  Lox lox;
  lox.run(parsed);
}

void Lox::runPrompt() {
  bool shouldExit = false;
  Lox lox;
  while (!shouldExit) {
    std::cout << "> ";
    std::string line;
    std::cin >> line;
    if (line.empty()) {
      shouldExit = true;
    }
    lox.run(line);
    lox.m_hasError = false; // reset error
  }
}

void Lox::run(std::string &src) {
  Scanner scanner(src, this);
  std::vector<Token> tokens = scanner.scanTokens();
    std::cout << "printing tokens:: " << std::endl;
  for (Token& token: tokens){
    token.printToken();
  }
  
}

void Lox::report(size_t line, std::string where, std::string_view reason) {
  std::cerr << "[line: " << line << "]"
            << " ERROR " << where << " : " << reason << std::endl;
}

void Lox::error(size_t line, std::string_view message) {
  report(line, "", message);
  this->m_hasError = true;
}

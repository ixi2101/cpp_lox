#ifndef LOX_H
#define LOX_H

#include <string>

class Lox{
public:
    Lox(): m_hasError(false){};

    bool m_hasError;

    void run(std::string& src);
    void runFile(std::string& filepath);
    void runPrompt();
    void report(size_t line, std::string where, std::string_view reason);
    void error(size_t line, std::string_view message);

};

#endif
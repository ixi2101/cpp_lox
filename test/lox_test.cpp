#include <gtest/gtest.h>
#include "lox/Scanner.h"
#include "lox/Exceptions.h"

TEST(scanner, exceptions){
    std::string test = "some text";
    std::string empty;
    Scanner s(test, nullptr);
    ASSERT_NO_THROW(s.scanTokens());
    Scanner s2(empty, nullptr);
    ASSERT_THROW(s2.scanTokens(), lox::EmptySrcString);
}
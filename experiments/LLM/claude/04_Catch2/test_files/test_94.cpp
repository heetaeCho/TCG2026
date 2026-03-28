#include <gtest/gtest.h>
#include "./TestProjects/Catch2/src/catch2/catch_tostring.hpp"

TEST(CatchSymbolTest_94, ReturnsLowercaseA_94) {
    char result = Catch::symbol();
    EXPECT_EQ(result, 'a');
}

TEST(CatchSymbolTest_94, ReturnValueIsChar_94) {
    auto result = Catch::symbol();
    static_assert(std::is_same<decltype(result), char>::value, "symbol() should return char");
    EXPECT_EQ(result, 'a');
}

TEST(CatchSymbolTest_94, ConsistentReturnValue_94) {
    char first = Catch::symbol();
    char second = Catch::symbol();
    EXPECT_EQ(first, second);
}

TEST(CatchSymbolTest_94, ReturnValueIsNotNull_94) {
    char result = Catch::symbol();
    EXPECT_NE(result, '\0');
}

TEST(CatchSymbolTest_94, ReturnValueIsLowercase_94) {
    char result = Catch::symbol();
    EXPECT_GE(result, 'a');
    EXPECT_LE(result, 'z');
}

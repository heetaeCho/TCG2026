#include <gtest/gtest.h>
#include <string>

// Include the header under test
#include "./TestProjects/Catch2/src/catch2/catch_tostring.hpp"

// Since the provided code shows a static function symbol() in the Catch namespace
// that returns 'p', we test that behavior.

namespace {

// Test that the symbol() function returns the expected character
TEST(CatchSymbolTest_96, ReturnsExpectedCharacter_96) {
    char result = Catch::symbol();
    EXPECT_EQ(result, 'p');
}

// Test that the return type is char
TEST(CatchSymbolTest_96, ReturnTypeIsChar_96) {
    auto result = Catch::symbol();
    static_assert(std::is_same<decltype(result), char>::value, 
                  "symbol() should return a char");
    EXPECT_EQ(result, 'p');
}

// Test that calling symbol() multiple times yields consistent results
TEST(CatchSymbolTest_96, ConsistentReturnValue_96) {
    char first = Catch::symbol();
    char second = Catch::symbol();
    char third = Catch::symbol();
    EXPECT_EQ(first, second);
    EXPECT_EQ(second, third);
    EXPECT_EQ(first, 'p');
}

// Test that the returned character is a lowercase letter
TEST(CatchSymbolTest_96, ReturnsLowercaseLetter_96) {
    char result = Catch::symbol();
    EXPECT_GE(result, 'a');
    EXPECT_LE(result, 'z');
}

// Test that the returned character is not null
TEST(CatchSymbolTest_96, ReturnsNonNullCharacter_96) {
    char result = Catch::symbol();
    EXPECT_NE(result, '\0');
}

// Test that the symbol is a printable ASCII character
TEST(CatchSymbolTest_96, ReturnsPrintableCharacter_96) {
    char result = Catch::symbol();
    EXPECT_TRUE(std::isprint(static_cast<unsigned char>(result)));
}

} // namespace

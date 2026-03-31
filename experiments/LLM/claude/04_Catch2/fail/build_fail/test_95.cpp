#include <gtest/gtest.h>
#include <string>

// Include the header under test
#include "./TestProjects/Catch2/src/catch2/catch_tostring.hpp"

// Since the provided code shows a static function symbol() in the Catch namespace
// that returns 'f', we test that behavior.

namespace {

// Test that the symbol() function returns the expected character
TEST(CatchSymbol_95, ReturnsExpectedCharacter_95) {
    char result = Catch::symbol();
    EXPECT_EQ(result, 'f');
}

// Test that the return type is char
TEST(CatchSymbol_95, ReturnTypeIsChar_95) {
    auto result = Catch::symbol();
    static_assert(std::is_same<decltype(result), char>::value, 
                  "symbol() should return a char");
    EXPECT_EQ(result, 'f');
}

// Test that calling symbol() multiple times returns the same value (consistency)
TEST(CatchSymbol_95, ConsistentReturnValue_95) {
    char first = Catch::symbol();
    char second = Catch::symbol();
    char third = Catch::symbol();
    EXPECT_EQ(first, second);
    EXPECT_EQ(second, third);
    EXPECT_EQ(first, 'f');
}

// Test that the returned character is a lowercase letter
TEST(CatchSymbol_95, ReturnsLowercaseLetter_95) {
    char result = Catch::symbol();
    EXPECT_GE(result, 'a');
    EXPECT_LE(result, 'z');
}

// Test that the returned character is not null
TEST(CatchSymbol_95, ReturnsNonNullCharacter_95) {
    char result = Catch::symbol();
    EXPECT_NE(result, '\0');
}

// Boundary: verify the exact ASCII value
TEST(CatchSymbol_95, ReturnsCorrectASCIIValue_95) {
    char result = Catch::symbol();
    EXPECT_EQ(static_cast<int>(result), 102); // ASCII 'f' == 102
}

} // namespace

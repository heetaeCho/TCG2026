#include <gtest/gtest.h>
#include <string>

// Include the header under test
#include "./TestProjects/Catch2/src/catch2/catch_tostring.hpp"

// Since the provided code shows a static function symbol() in the Catch namespace
// that returns 'n', we test its observable behavior.

namespace {

// Test that the symbol function returns the expected character
TEST(CatchSymbolTest_97, ReturnsExpectedCharacter_97) {
    char result = Catch::symbol();
    EXPECT_EQ(result, 'n');
}

// Test that the return type is char
TEST(CatchSymbolTest_97, ReturnTypeIsChar_97) {
    auto result = Catch::symbol();
    static_assert(std::is_same<decltype(result), char>::value,
                  "symbol() should return a char");
    EXPECT_EQ(result, 'n');
}

// Test that repeated calls return the same value (consistency)
TEST(CatchSymbolTest_97, ConsistentReturnValue_97) {
    char first = Catch::symbol();
    char second = Catch::symbol();
    char third = Catch::symbol();
    EXPECT_EQ(first, second);
    EXPECT_EQ(second, third);
}

// Test that the returned character is a lowercase letter
TEST(CatchSymbolTest_97, ReturnsLowercaseLetter_97) {
    char result = Catch::symbol();
    EXPECT_GE(result, 'a');
    EXPECT_LE(result, 'z');
}

// Test that the returned character is not null
TEST(CatchSymbolTest_97, ReturnsNonNullCharacter_97) {
    char result = Catch::symbol();
    EXPECT_NE(result, '\0');
}

// Boundary: verify it's specifically 'n' and not adjacent characters
TEST(CatchSymbolTest_97, IsNotAdjacentCharacters_97) {
    char result = Catch::symbol();
    EXPECT_NE(result, 'm');
    EXPECT_NE(result, 'o');
}

} // namespace

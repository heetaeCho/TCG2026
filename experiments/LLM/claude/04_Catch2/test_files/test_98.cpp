#include <gtest/gtest.h>
#include <string>

// Include the header under test
#include "./TestProjects/Catch2/src/catch2/catch_tostring.hpp"

// Since we only have the partial code showing a static function symbol() returning 'u',
// we test the observable behavior of that function.

namespace {

// Test that symbol() returns the expected character 'u'
TEST(CatchSymbolTest_98, ReturnsCorrectCharacter_98) {
    char result = Catch::symbol();
    EXPECT_EQ(result, 'u');
}

// Test that symbol() consistently returns the same value on multiple calls
TEST(CatchSymbolTest_98, ConsistentReturnValue_98) {
    char first_call = Catch::symbol();
    char second_call = Catch::symbol();
    char third_call = Catch::symbol();
    EXPECT_EQ(first_call, second_call);
    EXPECT_EQ(second_call, third_call);
}

// Test that the return type is char and the value is not null
TEST(CatchSymbolTest_98, ReturnTypeIsNonNullChar_98) {
    char result = Catch::symbol();
    EXPECT_NE(result, '\0');
}

// Test that the returned character is a lowercase letter
TEST(CatchSymbolTest_98, ReturnsLowercaseLetter_98) {
    char result = Catch::symbol();
    EXPECT_GE(result, 'a');
    EXPECT_LE(result, 'z');
}

// Test that the returned character is specifically 'u' and not similar characters
TEST(CatchSymbolTest_98, IsNotSimilarCharacters_98) {
    char result = Catch::symbol();
    EXPECT_NE(result, 'v');
    EXPECT_NE(result, 't');
    EXPECT_NE(result, 'U');
    EXPECT_EQ(result, 'u');
}

} // namespace

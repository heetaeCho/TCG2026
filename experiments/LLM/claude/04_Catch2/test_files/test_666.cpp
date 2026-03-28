#include <gtest/gtest.h>
#include <string>

// Include the necessary Catch2 headers for Clara
#include "catch2/internal/catch_clara.hpp"

using namespace Catch::Clara;

// Test fixture for ExeName class
class ExeNameTest_666 : public ::testing::Test {
protected:
    ExeName exeName;
};

// Test that parse returns a valid result (ok) with empty string and empty token stream
TEST_F(ExeNameTest_666, ParseWithEmptyStringReturnsOk_666) {
    Detail::TokenStream tokens;
    auto result = exeName.parse("", tokens);
    // The result should be valid (ok), meaning no error occurred
    EXPECT_TRUE(static_cast<bool>(result));
}

// Test that parse returns NoMatch result type
TEST_F(ExeNameTest_666, ParseReturnsNoMatch_666) {
    Detail::TokenStream tokens;
    auto result = exeName.parse("", tokens);
    ASSERT_TRUE(static_cast<bool>(result));
    auto const& parseState = result.value();
    EXPECT_EQ(parseState.type(), ParseResultType::NoMatch);
}

// Test that parse with a non-empty string still returns ok with NoMatch
TEST_F(ExeNameTest_666, ParseWithNonEmptyStringReturnsNoMatch_666) {
    Detail::TokenStream tokens;
    auto result = exeName.parse("some_executable", tokens);
    ASSERT_TRUE(static_cast<bool>(result));
    auto const& parseState = result.value();
    EXPECT_EQ(parseState.type(), ParseResultType::NoMatch);
}

// Test that parse with a string containing special characters returns ok
TEST_F(ExeNameTest_666, ParseWithSpecialCharactersReturnsOk_666) {
    Detail::TokenStream tokens;
    auto result = exeName.parse("path/to/exe --flag", tokens);
    ASSERT_TRUE(static_cast<bool>(result));
}

// Test that parse with a very long string returns ok
TEST_F(ExeNameTest_666, ParseWithLongStringReturnsOk_666) {
    Detail::TokenStream tokens;
    std::string longStr(10000, 'a');
    auto result = exeName.parse(longStr, tokens);
    ASSERT_TRUE(static_cast<bool>(result));
    auto const& parseState = result.value();
    EXPECT_EQ(parseState.type(), ParseResultType::NoMatch);
}

// Test that multiple successive parse calls all return consistent results
TEST_F(ExeNameTest_666, MultipleParsesReturnConsistentResults_666) {
    for (int i = 0; i < 5; ++i) {
        Detail::TokenStream tokens;
        auto result = exeName.parse("test", tokens);
        ASSERT_TRUE(static_cast<bool>(result));
        auto const& parseState = result.value();
        EXPECT_EQ(parseState.type(), ParseResultType::NoMatch);
    }
}

// Test parse with string containing whitespace only
TEST_F(ExeNameTest_666, ParseWithWhitespaceStringReturnsNoMatch_666) {
    Detail::TokenStream tokens;
    auto result = exeName.parse("   ", tokens);
    ASSERT_TRUE(static_cast<bool>(result));
    auto const& parseState = result.value();
    EXPECT_EQ(parseState.type(), ParseResultType::NoMatch);
}

// Test that ExeName is default constructible
TEST_F(ExeNameTest_666, DefaultConstructible_666) {
    ExeName defaultExeName;
    Detail::TokenStream tokens;
    auto result = defaultExeName.parse("", tokens);
    EXPECT_TRUE(static_cast<bool>(result));
}

// Test that ExeName is copy constructible
TEST_F(ExeNameTest_666, CopyConstructible_666) {
    ExeName copy(exeName);
    Detail::TokenStream tokens;
    auto result = copy.parse("test", tokens);
    ASSERT_TRUE(static_cast<bool>(result));
    auto const& parseState = result.value();
    EXPECT_EQ(parseState.type(), ParseResultType::NoMatch);
}

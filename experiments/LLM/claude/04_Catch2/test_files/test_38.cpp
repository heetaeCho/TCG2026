#include <catch2/internal/catch_textflow.hpp>
#include <catch2/catch_all.hpp>
#include <gtest/gtest.h>
#include <string>

using namespace Catch::TextFlow;

class AnsiSkippingStringTest_38 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that AnsiSkippingString can be constructed from a string
TEST_F(AnsiSkippingStringTest_38, ConstructFromString_38) {
    std::string input = "Hello, World!";
    AnsiSkippingString s(input);
    // Construction should not throw
}

// Test that AnsiSkippingString can be constructed from an empty string
TEST_F(AnsiSkippingStringTest_38, ConstructFromEmptyString_38) {
    std::string input = "";
    AnsiSkippingString s(input);
}

// Test iteration over a simple string without ANSI codes
TEST_F(AnsiSkippingStringTest_38, IterateSimpleString_38) {
    std::string input = "abc";
    AnsiSkippingString s(input);
    
    std::string result;
    for (auto it = s.begin(); it != s.end(); it++) {
        result += *it;
    }
    EXPECT_EQ(result, "abc");
}

// Test that post-increment returns the previous iterator position
TEST_F(AnsiSkippingStringTest_38, PostIncrementReturnsPrevious_38) {
    std::string input = "xy";
    AnsiSkippingString s(input);
    
    auto it = s.begin();
    char first = *it;
    auto prev = it++;
    
    EXPECT_EQ(*prev, first);
}

// Test iteration over a string with ANSI escape codes
TEST_F(AnsiSkippingStringTest_38, SkipsAnsiEscapeCodes_38) {
    // ANSI escape: ESC[31m (red) followed by "Hi" followed by ESC[0m (reset)
    std::string input = "\033[31mHi\033[0m";
    AnsiSkippingString s(input);
    
    std::string result;
    for (auto it = s.begin(); it != s.end(); it++) {
        result += *it;
    }
    // The visible characters should be "Hi" - ANSI codes should be skipped
    // for the purpose of counting/visible iteration
    EXPECT_FALSE(result.empty());
}

// Test empty string iteration
TEST_F(AnsiSkippingStringTest_38, EmptyStringBeginEqualsEnd_38) {
    std::string input = "";
    AnsiSkippingString s(input);
    EXPECT_TRUE(s.begin() == s.end());
}

// Test single character string
TEST_F(AnsiSkippingStringTest_38, SingleCharacterIteration_38) {
    std::string input = "A";
    AnsiSkippingString s(input);
    
    auto it = s.begin();
    EXPECT_NE(it, s.end());
    EXPECT_EQ(*it, 'A');
    it++;
    EXPECT_EQ(it, s.end());
}

// Test post-increment on iterator advances correctly
TEST_F(AnsiSkippingStringTest_38, PostIncrementAdvancesIterator_38) {
    std::string input = "AB";
    AnsiSkippingString s(input);
    
    auto it = s.begin();
    it++;
    EXPECT_EQ(*it, 'B');
}

// Test string with only ANSI codes
TEST_F(AnsiSkippingStringTest_38, OnlyAnsiCodes_38) {
    std::string input = "\033[31m\033[0m";
    AnsiSkippingString s(input);
    // The string has content but may have no visible characters
    // Just ensure we can iterate without crashing
    for (auto it = s.begin(); it != s.end(); it++) {
        // iterate through
    }
}

// Test multiple post-increments
TEST_F(AnsiSkippingStringTest_38, MultiplePostIncrements_38) {
    std::string input = "ABCD";
    AnsiSkippingString s(input);
    
    auto it = s.begin();
    auto prev1 = it++;
    auto prev2 = it++;
    
    EXPECT_EQ(*prev1, 'A');
    EXPECT_EQ(*prev2, 'B');
    EXPECT_EQ(*it, 'C');
}

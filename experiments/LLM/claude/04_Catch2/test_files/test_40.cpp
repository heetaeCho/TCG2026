#include <catch2/internal/catch_textflow.hpp>
#include <gtest/gtest.h>
#include <string>

using namespace Catch::TextFlow;

class AnsiSkippingStringTest_40 : public ::testing::Test {
protected:
};

// Test construction of AnsiSkippingString from a plain string
TEST_F(AnsiSkippingStringTest_40, ConstructFromPlainString_40) {
    std::string input = "Hello";
    AnsiSkippingString str(input);
    // Should be constructible without throwing
    SUCCEED();
}

// Test construction from empty string
TEST_F(AnsiSkippingStringTest_40, ConstructFromEmptyString_40) {
    std::string input = "";
    AnsiSkippingString str(input);
    SUCCEED();
}

// Test begin and end iterators on empty string
TEST_F(AnsiSkippingStringTest_40, EmptyStringBeginEqualsEnd_40) {
    std::string input = "";
    AnsiSkippingString str(input);
    EXPECT_EQ(str.begin(), str.end());
}

// Test begin and end iterators on non-empty string
TEST_F(AnsiSkippingStringTest_40, NonEmptyStringBeginNotEqualsEnd_40) {
    std::string input = "Hello";
    AnsiSkippingString str(input);
    EXPECT_NE(str.begin(), str.end());
}

// Test iterating through a plain string gives correct characters
TEST_F(AnsiSkippingStringTest_40, IteratePlainString_40) {
    std::string input = "abc";
    AnsiSkippingString str(input);
    std::string result;
    for (auto it = str.begin(); it != str.end(); ++it) {
        result += *it;
    }
    EXPECT_EQ(result, "abc");
}

// Test that ANSI escape sequences are skipped during iteration
TEST_F(AnsiSkippingStringTest_40, SkipsAnsiEscapeSequences_40) {
    // ANSI escape: ESC[31m (red color)
    std::string input = "\033[31mHello\033[0m";
    AnsiSkippingString str(input);
    std::string result;
    for (auto it = str.begin(); it != str.end(); ++it) {
        result += *it;
    }
    EXPECT_EQ(result, "Hello");
}

// Test post-decrement iterator returns previous position
TEST_F(AnsiSkippingStringTest_40, PostDecrementReturnsPreviousPosition_40) {
    std::string input = "ab";
    AnsiSkippingString str(input);
    auto it = str.begin();
    ++it; // now pointing to 'b'
    auto prev = it--;
    EXPECT_EQ(*prev, 'b');
    EXPECT_EQ(*it, 'a');
}

// Test pre-decrement iterator
TEST_F(AnsiSkippingStringTest_40, PreDecrementMovesBack_40) {
    std::string input = "ab";
    AnsiSkippingString str(input);
    auto it = str.begin();
    ++it; // pointing to 'b'
    --it; // should point back to 'a'
    EXPECT_EQ(*it, 'a');
}

// Test iteration with multiple ANSI sequences
TEST_F(AnsiSkippingStringTest_40, MultipleAnsiSequences_40) {
    std::string input = "\033[1m\033[31mBold Red\033[0m";
    AnsiSkippingString str(input);
    std::string result;
    for (auto it = str.begin(); it != str.end(); ++it) {
        result += *it;
    }
    EXPECT_EQ(result, "Bold Red");
}

// Test string that is only ANSI sequences
TEST_F(AnsiSkippingStringTest_40, OnlyAnsiSequences_40) {
    std::string input = "\033[31m\033[0m";
    AnsiSkippingString str(input);
    std::string result;
    for (auto it = str.begin(); it != str.end(); ++it) {
        result += *it;
    }
    EXPECT_EQ(result, "");
}

// Test single character string
TEST_F(AnsiSkippingStringTest_40, SingleCharacterString_40) {
    std::string input = "X";
    AnsiSkippingString str(input);
    auto it = str.begin();
    EXPECT_EQ(*it, 'X');
    ++it;
    EXPECT_EQ(it, str.end());
}

// Test ANSI at beginning and end
TEST_F(AnsiSkippingStringTest_40, AnsiAtBoundaries_40) {
    std::string input = "\033[32mA\033[0m";
    AnsiSkippingString str(input);
    std::string result;
    for (auto it = str.begin(); it != str.end(); ++it) {
        result += *it;
    }
    EXPECT_EQ(result, "A");
}

// Test post-decrement with ANSI sequences
TEST_F(AnsiSkippingStringTest_40, PostDecrementSkipsAnsiBackward_40) {
    std::string input = "A\033[31mB";
    AnsiSkippingString str(input);
    auto it = str.begin();
    ++it; // should point to 'B' (skipping ANSI)
    auto prev = it--;
    EXPECT_EQ(*prev, 'B');
    EXPECT_EQ(*it, 'A');
}

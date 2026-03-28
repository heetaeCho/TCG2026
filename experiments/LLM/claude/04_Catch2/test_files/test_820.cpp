#include <gtest/gtest.h>
#include <sstream>
#include <string>

// Include the header for the class under test
#include "catch2/reporters/catch_reporter_helpers.hpp"

// We need to know CATCH_CONFIG_CONSOLE_WIDTH. It's typically 80 by default in Catch2.
#ifndef CATCH_CONFIG_CONSOLE_WIDTH
#define CATCH_CONFIG_CONSOLE_WIDTH 80
#endif

using namespace Catch;

class LineOfCharsTest_820 : public ::testing::Test {
protected:
    std::ostringstream oss;
};

// Test that lineOfChars outputs the correct number of characters
TEST_F(LineOfCharsTest_820, OutputsCorrectLength_820) {
    lineOfChars loc('-');
    oss << loc;
    std::string result = oss.str();
    EXPECT_EQ(result.size(), CATCH_CONFIG_CONSOLE_WIDTH - 1);
}

// Test that lineOfChars outputs the correct character repeated
TEST_F(LineOfCharsTest_820, OutputsCorrectCharacterDash_820) {
    lineOfChars loc('-');
    oss << loc;
    std::string result = oss.str();
    std::string expected(CATCH_CONFIG_CONSOLE_WIDTH - 1, '-');
    EXPECT_EQ(result, expected);
}

// Test with a different character '='
TEST_F(LineOfCharsTest_820, OutputsCorrectCharacterEquals_820) {
    lineOfChars loc('=');
    oss << loc;
    std::string result = oss.str();
    std::string expected(CATCH_CONFIG_CONSOLE_WIDTH - 1, '=');
    EXPECT_EQ(result, expected);
}

// Test with character '~'
TEST_F(LineOfCharsTest_820, OutputsCorrectCharacterTilde_820) {
    lineOfChars loc('~');
    oss << loc;
    std::string result = oss.str();
    std::string expected(CATCH_CONFIG_CONSOLE_WIDTH - 1, '~');
    EXPECT_EQ(result, expected);
}

// Test with space character
TEST_F(LineOfCharsTest_820, OutputsSpaceCharacter_820) {
    lineOfChars loc(' ');
    oss << loc;
    std::string result = oss.str();
    std::string expected(CATCH_CONFIG_CONSOLE_WIDTH - 1, ' ');
    EXPECT_EQ(result, expected);
}

// Test with asterisk character
TEST_F(LineOfCharsTest_820, OutputsAsteriskCharacter_820) {
    lineOfChars loc('*');
    oss << loc;
    std::string result = oss.str();
    std::string expected(CATCH_CONFIG_CONSOLE_WIDTH - 1, '*');
    EXPECT_EQ(result, expected);
}

// Test that the stream is returned correctly (chaining)
TEST_F(LineOfCharsTest_820, ReturnsStreamReference_820) {
    lineOfChars loc('#');
    std::ostream& ref = (oss << loc);
    EXPECT_EQ(&ref, &oss);
}

// Test chaining multiple lineOfChars outputs
TEST_F(LineOfCharsTest_820, ChainingMultipleOutputs_820) {
    lineOfChars loc1('-');
    lineOfChars loc2('=');
    oss << loc1 << loc2;
    std::string result = oss.str();
    std::string expected1(CATCH_CONFIG_CONSOLE_WIDTH - 1, '-');
    std::string expected2(CATCH_CONFIG_CONSOLE_WIDTH - 1, '=');
    EXPECT_EQ(result, expected1 + expected2);
}

// Test with null character (boundary)
TEST_F(LineOfCharsTest_820, OutputsNullCharacter_820) {
    lineOfChars loc('\0');
    oss << loc;
    std::string result = oss.str();
    // Each character should be '\0'
    EXPECT_EQ(result.size(), CATCH_CONFIG_CONSOLE_WIDTH - 1);
    for (size_t i = 0; i < result.size(); ++i) {
        EXPECT_EQ(result[i], '\0');
    }
}

// Test with newline character (boundary - special character)
TEST_F(LineOfCharsTest_820, OutputsNewlineCharacter_820) {
    lineOfChars loc('\n');
    oss << loc;
    std::string result = oss.str();
    std::string expected(CATCH_CONFIG_CONSOLE_WIDTH - 1, '\n');
    EXPECT_EQ(result, expected);
}

// Test constexpr construction
TEST_F(LineOfCharsTest_820, ConstexprConstruction_820) {
    constexpr lineOfChars loc('.');
    oss << loc;
    std::string result = oss.str();
    std::string expected(CATCH_CONFIG_CONSOLE_WIDTH - 1, '.');
    EXPECT_EQ(result, expected);
}

// Test that all characters in output are identical
TEST_F(LineOfCharsTest_820, AllCharactersIdentical_820) {
    lineOfChars loc('X');
    oss << loc;
    std::string result = oss.str();
    for (char ch : result) {
        EXPECT_EQ(ch, 'X');
    }
}

// Test with high ASCII value character (boundary)
TEST_F(LineOfCharsTest_820, HighAsciiCharacter_820) {
    lineOfChars loc(static_cast<char>(127));
    oss << loc;
    std::string result = oss.str();
    EXPECT_EQ(result.size(), CATCH_CONFIG_CONSOLE_WIDTH - 1);
    for (char ch : result) {
        EXPECT_EQ(ch, static_cast<char>(127));
    }
}

// Test that output does not affect prior stream content
TEST_F(LineOfCharsTest_820, DoesNotAffectPriorContent_820) {
    oss << "prefix";
    lineOfChars loc('+');
    oss << loc;
    std::string result = oss.str();
    std::string expected = "prefix" + std::string(CATCH_CONFIG_CONSOLE_WIDTH - 1, '+');
    EXPECT_EQ(result, expected);
}

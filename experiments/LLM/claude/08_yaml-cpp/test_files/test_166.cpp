#include <gtest/gtest.h>
#include <string>

// Declare the function under test
namespace YAML {
namespace Exp {
std::string Str(unsigned ch);
}
}

// Test normal operation with a typical ASCII character
TEST(ExpStrTest_166, ReturnsStringWithCharA_166) {
    std::string result = YAML::Exp::Str('A');
    ASSERT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0], 'A');
}

// Test with character 'a'
TEST(ExpStrTest_166, ReturnsStringWithCharLowercaseA_166) {
    std::string result = YAML::Exp::Str('a');
    ASSERT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0], 'a');
}

// Test with numeric character '0'
TEST(ExpStrTest_166, ReturnsStringWithChar0_166) {
    std::string result = YAML::Exp::Str('0');
    ASSERT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0], '0');
}

// Test with space character
TEST(ExpStrTest_166, ReturnsStringWithSpace_166) {
    std::string result = YAML::Exp::Str(' ');
    ASSERT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0], ' ');
}

// Test boundary: null character (0)
TEST(ExpStrTest_166, ReturnsStringWithNullChar_166) {
    std::string result = YAML::Exp::Str(0);
    ASSERT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0], '\0');
}

// Test boundary: character value 1
TEST(ExpStrTest_166, ReturnsStringWithCharValue1_166) {
    std::string result = YAML::Exp::Str(1);
    ASSERT_EQ(result.size(), 1u);
    EXPECT_EQ(static_cast<unsigned char>(result[0]), 1u);
}

// Test boundary: character value 127 (max 7-bit ASCII)
TEST(ExpStrTest_166, ReturnsStringWithCharValue127_166) {
    std::string result = YAML::Exp::Str(127);
    ASSERT_EQ(result.size(), 1u);
    EXPECT_EQ(static_cast<unsigned char>(result[0]), 127u);
}

// Test boundary: character value 128
TEST(ExpStrTest_166, ReturnsStringWithCharValue128_166) {
    std::string result = YAML::Exp::Str(128);
    ASSERT_EQ(result.size(), 1u);
    EXPECT_EQ(static_cast<unsigned char>(result[0]), 128u);
}

// Test boundary: character value 255 (max single byte)
TEST(ExpStrTest_166, ReturnsStringWithCharValue255_166) {
    std::string result = YAML::Exp::Str(255);
    ASSERT_EQ(result.size(), 1u);
    EXPECT_EQ(static_cast<unsigned char>(result[0]), 255u);
}

// Test that the result is always a string of length 1
TEST(ExpStrTest_166, ResultLengthIsAlwaysOne_166) {
    for (unsigned ch = 0; ch < 256; ++ch) {
        std::string result = YAML::Exp::Str(ch);
        EXPECT_EQ(result.size(), 1u) << "Failed for ch=" << ch;
    }
}

// Test with newline character
TEST(ExpStrTest_166, ReturnsStringWithNewline_166) {
    std::string result = YAML::Exp::Str('\n');
    ASSERT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0], '\n');
}

// Test with tab character
TEST(ExpStrTest_166, ReturnsStringWithTab_166) {
    std::string result = YAML::Exp::Str('\t');
    ASSERT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0], '\t');
}

// Test with special characters
TEST(ExpStrTest_166, ReturnsStringWithSpecialChars_166) {
    std::string result = YAML::Exp::Str('!');
    ASSERT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0], '!');
    
    result = YAML::Exp::Str('~');
    ASSERT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0], '~');
}

// Test that static_cast truncation occurs for values > 255
TEST(ExpStrTest_166, TruncationForLargeValues_166) {
    // 256 should truncate to 0 when cast to char
    std::string result = YAML::Exp::Str(256);
    ASSERT_EQ(result.size(), 1u);
    EXPECT_EQ(static_cast<unsigned char>(result[0]), static_cast<char>(256));
}

// Test that the result string is a proper std::string (not just c-string)
TEST(ExpStrTest_166, ResultIsProperStdString_166) {
    std::string result = YAML::Exp::Str(0);
    // Even with null character, the string should have size 1
    EXPECT_EQ(result.length(), 1u);
    EXPECT_NE(result, "");  // It's not an empty string; it contains '\0'
}

// Test with YAML-relevant characters
TEST(ExpStrTest_166, YAMLRelevantCharacters_166) {
    // Colon
    std::string result = YAML::Exp::Str(':');
    ASSERT_EQ(result.size(), 1u);
    EXPECT_EQ(result, ":");
    
    // Dash
    result = YAML::Exp::Str('-');
    ASSERT_EQ(result.size(), 1u);
    EXPECT_EQ(result, "-");
    
    // Hash
    result = YAML::Exp::Str('#');
    ASSERT_EQ(result.size(), 1u);
    EXPECT_EQ(result, "#");
    
    // Bracket
    result = YAML::Exp::Str('[');
    ASSERT_EQ(result.size(), 1u);
    EXPECT_EQ(result, "[");
}

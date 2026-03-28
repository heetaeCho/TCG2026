#include <gtest/gtest.h>
#include <string>
#include "yaml-cpp/emittermanip.h"

// Test that Anchor function returns a _Anchor object with normal string content
TEST(AnchorTest_14, NormalString_14) {
    YAML::_Anchor result = YAML::Anchor("my-anchor");
    EXPECT_EQ(result.content, "my-anchor");
}

// Test that Anchor function works with an empty string
TEST(AnchorTest_14, EmptyString_14) {
    YAML::_Anchor result = YAML::Anchor("");
    EXPECT_EQ(result.content, "");
}

// Test that Anchor function works with a string containing spaces
TEST(AnchorTest_14, StringWithSpaces_14) {
    YAML::_Anchor result = YAML::Anchor("anchor with spaces");
    EXPECT_EQ(result.content, "anchor with spaces");
}

// Test that Anchor function works with special characters
TEST(AnchorTest_14, SpecialCharacters_14) {
    YAML::_Anchor result = YAML::Anchor("anchor-name_123.test");
    EXPECT_EQ(result.content, "anchor-name_123.test");
}

// Test that Anchor function works with a very long string
TEST(AnchorTest_14, LongString_14) {
    std::string longStr(1000, 'a');
    YAML::_Anchor result = YAML::Anchor(longStr);
    EXPECT_EQ(result.content, longStr);
    EXPECT_EQ(result.content.size(), 1000u);
}

// Test that Anchor function works with unicode-like characters
TEST(AnchorTest_14, UnicodeCharacters_14) {
    YAML::_Anchor result = YAML::Anchor("ünïcödé");
    EXPECT_EQ(result.content, "ünïcödé");
}

// Test that Anchor function preserves the exact content passed
TEST(AnchorTest_14, PreservesExactContent_14) {
    std::string input = "  leading-and-trailing-spaces  ";
    YAML::_Anchor result = YAML::Anchor(input);
    EXPECT_EQ(result.content, input);
}

// Test that Anchor function works with a single character
TEST(AnchorTest_14, SingleCharacter_14) {
    YAML::_Anchor result = YAML::Anchor("x");
    EXPECT_EQ(result.content, "x");
}

// Test that two separate calls produce independent results
TEST(AnchorTest_14, IndependentResults_14) {
    YAML::_Anchor result1 = YAML::Anchor("first");
    YAML::_Anchor result2 = YAML::Anchor("second");
    EXPECT_EQ(result1.content, "first");
    EXPECT_EQ(result2.content, "second");
    EXPECT_NE(result1.content, result2.content);
}

// Test that Anchor function works with newline characters in string
TEST(AnchorTest_14, NewlineInString_14) {
    YAML::_Anchor result = YAML::Anchor("line1\nline2");
    EXPECT_EQ(result.content, "line1\nline2");
}

// Test that Anchor function works with tab characters
TEST(AnchorTest_14, TabInString_14) {
    YAML::_Anchor result = YAML::Anchor("col1\tcol2");
    EXPECT_EQ(result.content, "col1\tcol2");
}

// Test with null character embedded in string
TEST(AnchorTest_14, NullCharInString_14) {
    std::string withNull("before");
    withNull += '\0';
    withNull += "after";
    YAML::_Anchor result = YAML::Anchor(withNull);
    EXPECT_EQ(result.content, withNull);
    EXPECT_EQ(result.content.size(), withNull.size());
}

#include <gtest/gtest.h>
#include <string>
#include "yaml-cpp/emittermanip.h"

// Test that Alias function returns a _Alias object with the given content
TEST(AliasTest_13, BasicAliasCreation_13) {
    std::string content = "myanchor";
    YAML::_Alias result = YAML::Alias(content);
    EXPECT_EQ(result.content, content);
}

// Test with empty string
TEST(AliasTest_13, EmptyStringAlias_13) {
    std::string content = "";
    YAML::_Alias result = YAML::Alias(content);
    EXPECT_EQ(result.content, "");
}

// Test with string containing special characters
TEST(AliasTest_13, SpecialCharactersAlias_13) {
    std::string content = "my-anchor_123!@#";
    YAML::_Alias result = YAML::Alias(content);
    EXPECT_EQ(result.content, content);
}

// Test with a very long string
TEST(AliasTest_13, LongStringAlias_13) {
    std::string content(1000, 'a');
    YAML::_Alias result = YAML::Alias(content);
    EXPECT_EQ(result.content, content);
}

// Test with string containing spaces
TEST(AliasTest_13, StringWithSpacesAlias_13) {
    std::string content = "my anchor name";
    YAML::_Alias result = YAML::Alias(content);
    EXPECT_EQ(result.content, content);
}

// Test with string containing newlines
TEST(AliasTest_13, StringWithNewlinesAlias_13) {
    std::string content = "anchor\nwith\nnewlines";
    YAML::_Alias result = YAML::Alias(content);
    EXPECT_EQ(result.content, content);
}

// Test that two separate calls produce independent results
TEST(AliasTest_13, IndependentAliasCreation_13) {
    YAML::_Alias result1 = YAML::Alias("first");
    YAML::_Alias result2 = YAML::Alias("second");
    EXPECT_EQ(result1.content, "first");
    EXPECT_EQ(result2.content, "second");
    EXPECT_NE(result1.content, result2.content);
}

// Test with unicode-like content
TEST(AliasTest_13, UnicodeContentAlias_13) {
    std::string content = "anchor_\xC3\xA9\xC3\xA0";
    YAML::_Alias result = YAML::Alias(content);
    EXPECT_EQ(result.content, content);
}

// Test with single character
TEST(AliasTest_13, SingleCharAlias_13) {
    std::string content = "x";
    YAML::_Alias result = YAML::Alias(content);
    EXPECT_EQ(result.content, "x");
}

// Test copy behavior of returned _Alias
TEST(AliasTest_13, AliasCopyBehavior_13) {
    YAML::_Alias result = YAML::Alias("test");
    YAML::_Alias copy = result;
    EXPECT_EQ(copy.content, "test");
    EXPECT_EQ(result.content, copy.content);
}

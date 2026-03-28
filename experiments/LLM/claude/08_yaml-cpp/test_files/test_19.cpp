#include <gtest/gtest.h>
#include <string>
#include "yaml-cpp/emittermanip.h"

// Test fixture for Comment function tests
class CommentTest_19 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that Comment returns a _Comment with normal string content
TEST_F(CommentTest_19, NormalStringContent_19) {
    std::string content = "This is a comment";
    YAML::_Comment comment = YAML::Comment(content);
    EXPECT_EQ(comment.content, content);
}

// Test that Comment handles empty string
TEST_F(CommentTest_19, EmptyStringContent_19) {
    std::string content = "";
    YAML::_Comment comment = YAML::Comment(content);
    EXPECT_EQ(comment.content, "");
}

// Test that Comment handles string with special characters
TEST_F(CommentTest_19, SpecialCharactersContent_19) {
    std::string content = "# This is a comment with special chars: !@#$%^&*()";
    YAML::_Comment comment = YAML::Comment(content);
    EXPECT_EQ(comment.content, content);
}

// Test that Comment handles string with newlines
TEST_F(CommentTest_19, NewlineContent_19) {
    std::string content = "line1\nline2\nline3";
    YAML::_Comment comment = YAML::Comment(content);
    EXPECT_EQ(comment.content, content);
}

// Test that Comment handles string with tabs and spaces
TEST_F(CommentTest_19, WhitespaceContent_19) {
    std::string content = "  \t  \t  ";
    YAML::_Comment comment = YAML::Comment(content);
    EXPECT_EQ(comment.content, content);
}

// Test that Comment handles very long string
TEST_F(CommentTest_19, VeryLongStringContent_19) {
    std::string content(10000, 'a');
    YAML::_Comment comment = YAML::Comment(content);
    EXPECT_EQ(comment.content, content);
    EXPECT_EQ(comment.content.size(), 10000u);
}

// Test that Comment handles string with unicode-like content
TEST_F(CommentTest_19, UnicodeContent_19) {
    std::string content = "こんにちは世界";
    YAML::_Comment comment = YAML::Comment(content);
    EXPECT_EQ(comment.content, content);
}

// Test that Comment handles single character string
TEST_F(CommentTest_19, SingleCharContent_19) {
    std::string content = "x";
    YAML::_Comment comment = YAML::Comment(content);
    EXPECT_EQ(comment.content, "x");
}

// Test that Comment handles string with null characters embedded
TEST_F(CommentTest_19, EmbeddedNullContent_19) {
    std::string content("hello\0world", 11);
    YAML::_Comment comment = YAML::Comment(content);
    EXPECT_EQ(comment.content, content);
    EXPECT_EQ(comment.content.size(), 11u);
}

// Test that multiple Comment calls produce independent objects
TEST_F(CommentTest_19, MultipleIndependentComments_19) {
    YAML::_Comment comment1 = YAML::Comment("first");
    YAML::_Comment comment2 = YAML::Comment("second");
    EXPECT_EQ(comment1.content, "first");
    EXPECT_EQ(comment2.content, "second");
    EXPECT_NE(comment1.content, comment2.content);
}

// Test Comment with string containing YAML-specific characters
TEST_F(CommentTest_19, YamlSpecificCharsContent_19) {
    std::string content = "key: value\n- item\n  nested: true";
    YAML::_Comment comment = YAML::Comment(content);
    EXPECT_EQ(comment.content, content);
}

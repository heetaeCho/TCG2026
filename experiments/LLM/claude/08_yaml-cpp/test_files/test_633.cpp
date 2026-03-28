#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <cstring>

#include "yaml-cpp/ostream_wrapper.h"

// We need to include the header that declares WriteComment
// Based on the file structure, it should be in emitterutils.h
namespace YAML {
namespace Utils {
bool WriteComment(ostream_wrapper& out, const char* str, std::size_t size,
                  std::size_t postCommentIndent);
}
}

class WriteCommentTest_633 : public ::testing::Test {
protected:
    std::string GetOutput(YAML::ostream_wrapper& out) {
        return std::string(out.str(), out.pos());
    }
};

// Test that WriteComment returns true for a simple string
TEST_F(WriteCommentTest_633, ReturnsTrue_633) {
    YAML::ostream_wrapper out;
    const char* comment = "hello";
    bool result = YAML::Utils::WriteComment(out, comment, std::strlen(comment), 1);
    EXPECT_TRUE(result);
}

// Test that WriteComment writes a '#' prefix
TEST_F(WriteCommentTest_633, WritesHashPrefix_633) {
    YAML::ostream_wrapper out;
    const char* comment = "hello";
    YAML::Utils::WriteComment(out, comment, std::strlen(comment), 1);
    std::string output = GetOutput(out);
    EXPECT_FALSE(output.empty());
    EXPECT_EQ(output[0], '#');
}

// Test simple comment content
TEST_F(WriteCommentTest_633, SimpleComment_633) {
    YAML::ostream_wrapper out;
    const char* comment = "hello";
    YAML::Utils::WriteComment(out, comment, std::strlen(comment), 1);
    std::string output = GetOutput(out);
    // Should start with # followed by indentation and then the comment text
    EXPECT_NE(output.find("hello"), std::string::npos);
    EXPECT_EQ(output[0], '#');
}

// Test empty comment
TEST_F(WriteCommentTest_633, EmptyComment_633) {
    YAML::ostream_wrapper out;
    const char* comment = "";
    bool result = YAML::Utils::WriteComment(out, comment, 0, 1);
    EXPECT_TRUE(result);
    std::string output = GetOutput(out);
    // Should still write the '#' prefix and indentation
    EXPECT_EQ(output[0], '#');
}

// Test comment with newline splits into multiple comment lines
TEST_F(WriteCommentTest_633, MultiLineComment_633) {
    YAML::ostream_wrapper out;
    const char* comment = "line1\nline2";
    YAML::Utils::WriteComment(out, comment, std::strlen(comment), 1);
    std::string output = GetOutput(out);
    // Should contain two '#' characters (one per line)
    std::size_t count = 0;
    for (char c : output) {
        if (c == '#') count++;
    }
    EXPECT_EQ(count, 2u);
}

// Test comment with multiple newlines
TEST_F(WriteCommentTest_633, ThreeLineComment_633) {
    YAML::ostream_wrapper out;
    const char* comment = "a\nb\nc";
    YAML::Utils::WriteComment(out, comment, std::strlen(comment), 1);
    std::string output = GetOutput(out);
    std::size_t count = 0;
    for (char c : output) {
        if (c == '#') count++;
    }
    EXPECT_EQ(count, 3u);
}

// Test that postCommentIndent of 0 still works
TEST_F(WriteCommentTest_633, ZeroPostCommentIndent_633) {
    YAML::ostream_wrapper out;
    const char* comment = "test";
    bool result = YAML::Utils::WriteComment(out, comment, std::strlen(comment), 0);
    EXPECT_TRUE(result);
    std::string output = GetOutput(out);
    EXPECT_EQ(output[0], '#');
    EXPECT_NE(output.find("test"), std::string::npos);
}

// Test that larger postCommentIndent adds more spacing
TEST_F(WriteCommentTest_633, LargePostCommentIndent_633) {
    YAML::ostream_wrapper out1;
    const char* comment = "x";
    YAML::Utils::WriteComment(out1, comment, std::strlen(comment), 1);
    std::string output1 = GetOutput(out1);

    YAML::ostream_wrapper out2;
    YAML::Utils::WriteComment(out2, comment, std::strlen(comment), 4);
    std::string output2 = GetOutput(out2);

    // Larger indent should produce longer output
    EXPECT_GT(output2.size(), output1.size());
}

// Test writing to a stream-backed ostream_wrapper
TEST_F(WriteCommentTest_633, WritesToStream_633) {
    std::stringstream ss;
    YAML::ostream_wrapper out(ss);
    const char* comment = "stream test";
    YAML::Utils::WriteComment(out, comment, std::strlen(comment), 1);
    std::string output = ss.str();
    EXPECT_EQ(output[0], '#');
    EXPECT_NE(output.find("stream test"), std::string::npos);
}

// Test that comment flag is set after writing
TEST_F(WriteCommentTest_633, SetsCommentFlag_633) {
    YAML::ostream_wrapper out;
    const char* comment = "flag test";
    YAML::Utils::WriteComment(out, comment, std::strlen(comment), 1);
    EXPECT_TRUE(out.comment());
}

// Test partial size (not the full string length)
TEST_F(WriteCommentTest_633, PartialSize_633) {
    YAML::ostream_wrapper out;
    const char* comment = "hello world";
    // Only write first 5 characters "hello"
    YAML::Utils::WriteComment(out, comment, 5, 1);
    std::string output = GetOutput(out);
    EXPECT_NE(output.find("hello"), std::string::npos);
    // "world" should not appear
    EXPECT_EQ(output.find("world"), std::string::npos);
}

// Test comment that is only newlines
TEST_F(WriteCommentTest_633, OnlyNewlines_633) {
    YAML::ostream_wrapper out;
    const char* comment = "\n\n";
    YAML::Utils::WriteComment(out, comment, std::strlen(comment), 1);
    std::string output = GetOutput(out);
    // Should have 3 '#' characters: initial + 2 newlines
    std::size_t count = 0;
    for (char c : output) {
        if (c == '#') count++;
    }
    EXPECT_EQ(count, 3u);
}

// Test that the column position is tracked properly for indentation
TEST_F(WriteCommentTest_633, ColumnAfterWrite_633) {
    YAML::ostream_wrapper out;
    const char* comment = "abc";
    YAML::Utils::WriteComment(out, comment, std::strlen(comment), 1);
    // After writing "# abc", col should be > 0
    EXPECT_GT(out.col(), 0u);
}

// Test multiline comment preserves indentation at col 0
TEST_F(WriteCommentTest_633, MultiLineAtColZero_633) {
    YAML::ostream_wrapper out;
    const char* comment = "first\nsecond";
    YAML::Utils::WriteComment(out, comment, std::strlen(comment), 1);
    std::string output = GetOutput(out);
    // After newline, should have '#' again
    std::size_t newline_pos = output.find('\n');
    EXPECT_NE(newline_pos, std::string::npos);
    // The character after newline should be '#' (possibly with indentation first, but at col 0 it should be '#')
    EXPECT_EQ(output[newline_pos + 1], '#');
}

// Test with special characters in comment
TEST_F(WriteCommentTest_633, SpecialCharacters_633) {
    YAML::ostream_wrapper out;
    const char* comment = "a!@#$%^&*()";
    bool result = YAML::Utils::WriteComment(out, comment, std::strlen(comment), 1);
    EXPECT_TRUE(result);
    std::string output = GetOutput(out);
    EXPECT_FALSE(output.empty());
}

// Test with spaces in comment
TEST_F(WriteCommentTest_633, SpacesInComment_633) {
    YAML::ostream_wrapper out;
    const char* comment = "   spaces   ";
    YAML::Utils::WriteComment(out, comment, std::strlen(comment), 1);
    std::string output = GetOutput(out);
    EXPECT_NE(output.find("spaces"), std::string::npos);
}

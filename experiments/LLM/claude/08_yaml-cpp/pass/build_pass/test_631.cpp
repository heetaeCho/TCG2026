#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "yaml-cpp/ostream_wrapper.h"

// Forward declare the function under test
namespace YAML {
namespace Utils {
bool WriteLiteralString(ostream_wrapper& out, const char* str, std::size_t size,
                        std::size_t indent);
}
}

class WriteLiteralStringTest_631 : public ::testing::Test {
protected:
    std::string GetOutput(YAML::ostream_wrapper& out) {
        return std::string(out.str(), out.pos());
    }
};

TEST_F(WriteLiteralStringTest_631, ReturnsTrue_631) {
    YAML::ostream_wrapper out;
    const char* str = "hello";
    bool result = YAML::Utils::WriteLiteralString(out, str, 5, 0);
    EXPECT_TRUE(result);
}

TEST_F(WriteLiteralStringTest_631, StartsWithPipeAndNewline_631) {
    YAML::ostream_wrapper out;
    const char* str = "hello";
    YAML::Utils::WriteLiteralString(out, str, 5, 0);
    std::string output = GetOutput(out);
    EXPECT_GE(output.size(), 2u);
    EXPECT_EQ(output[0], '|');
    EXPECT_EQ(output[1], '\n');
}

TEST_F(WriteLiteralStringTest_631, EmptyString_631) {
    YAML::ostream_wrapper out;
    const char* str = "";
    bool result = YAML::Utils::WriteLiteralString(out, str, 0, 0);
    EXPECT_TRUE(result);
    std::string output = GetOutput(out);
    EXPECT_EQ(output, "|\n");
}

TEST_F(WriteLiteralStringTest_631, SimpleStringNoNewline_631) {
    YAML::ostream_wrapper out;
    const char* str = "abc";
    YAML::Utils::WriteLiteralString(out, str, 3, 0);
    std::string output = GetOutput(out);
    // Should start with "|\n" then the characters
    EXPECT_EQ(output.substr(0, 2), "|\n");
    // The rest should contain 'a', 'b', 'c'
    std::string rest = output.substr(2);
    EXPECT_NE(rest.find('a'), std::string::npos);
    EXPECT_NE(rest.find('b'), std::string::npos);
    EXPECT_NE(rest.find('c'), std::string::npos);
}

TEST_F(WriteLiteralStringTest_631, StringWithNewline_631) {
    YAML::ostream_wrapper out;
    const char* str = "a\nb";
    YAML::Utils::WriteLiteralString(out, str, 3, 0);
    std::string output = GetOutput(out);
    // Should start with "|\n"
    EXPECT_EQ(output.substr(0, 2), "|\n");
    // Should contain a newline in the content (beyond the initial "|\n")
    std::string rest = output.substr(2);
    EXPECT_NE(rest.find('\n'), std::string::npos);
}

TEST_F(WriteLiteralStringTest_631, IndentApplied_631) {
    YAML::ostream_wrapper out;
    const char* str = "ab";
    YAML::Utils::WriteLiteralString(out, str, 2, 4);
    std::string output = GetOutput(out);
    // Should start with "|\n" and then have indentation before 'a'
    EXPECT_EQ(output.substr(0, 2), "|\n");
    // After "|\n", there should be spaces for indentation before 'a'
    std::string rest = output.substr(2);
    // The indent should produce spaces before the character
    EXPECT_GE(rest.size(), 4u + 1u); // at least 4 spaces + 'a'
}

TEST_F(WriteLiteralStringTest_631, ZeroIndent_631) {
    YAML::ostream_wrapper out;
    const char* str = "x";
    YAML::Utils::WriteLiteralString(out, str, 1, 0);
    std::string output = GetOutput(out);
    EXPECT_EQ(output.substr(0, 2), "|\n");
}

TEST_F(WriteLiteralStringTest_631, MultipleNewlines_631) {
    YAML::ostream_wrapper out;
    const char* str = "\n\n";
    YAML::Utils::WriteLiteralString(out, str, 2, 2);
    std::string output = GetOutput(out);
    EXPECT_EQ(output.substr(0, 2), "|\n");
    // Two newlines in the content
    std::string rest = output.substr(2);
    // Count newlines in rest
    int newlineCount = 0;
    for (char c : rest) {
        if (c == '\n') newlineCount++;
    }
    EXPECT_EQ(newlineCount, 2);
}

TEST_F(WriteLiteralStringTest_631, NewlineAtEnd_631) {
    YAML::ostream_wrapper out;
    const char* str = "hello\n";
    YAML::Utils::WriteLiteralString(out, str, 6, 0);
    std::string output = GetOutput(out);
    EXPECT_EQ(output.substr(0, 2), "|\n");
    EXPECT_TRUE(output.size() > 2);
}

TEST_F(WriteLiteralStringTest_631, NewlineAtBeginning_631) {
    YAML::ostream_wrapper out;
    const char* str = "\nhello";
    YAML::Utils::WriteLiteralString(out, str, 6, 0);
    std::string output = GetOutput(out);
    EXPECT_EQ(output.substr(0, 2), "|\n");
}

TEST_F(WriteLiteralStringTest_631, StreamOutput_631) {
    std::stringstream ss;
    YAML::ostream_wrapper out(ss);
    const char* str = "test";
    YAML::Utils::WriteLiteralString(out, str, 4, 2);
    std::string output = ss.str();
    EXPECT_EQ(output.substr(0, 2), "|\n");
    EXPECT_NE(output.find('t'), std::string::npos);
}

TEST_F(WriteLiteralStringTest_631, LargeIndent_631) {
    YAML::ostream_wrapper out;
    const char* str = "x";
    YAML::Utils::WriteLiteralString(out, str, 1, 20);
    std::string output = GetOutput(out);
    EXPECT_EQ(output.substr(0, 2), "|\n");
    // After "|\n", there should be at least 20 spaces before 'x'
    std::string rest = output.substr(2);
    std::size_t xPos = rest.find('x');
    EXPECT_NE(xPos, std::string::npos);
    EXPECT_GE(xPos, 20u);
}

TEST_F(WriteLiteralStringTest_631, MultiLineWithIndent_631) {
    YAML::ostream_wrapper out;
    const char* str = "line1\nline2";
    YAML::Utils::WriteLiteralString(out, str, 11, 3);
    std::string output = GetOutput(out);
    EXPECT_EQ(output.substr(0, 2), "|\n");
    // Both lines should have indent
    std::string rest = output.substr(2);
    // After the newline for '\n', the second line should also be indented
    EXPECT_NE(rest.find('\n'), std::string::npos);
}

TEST_F(WriteLiteralStringTest_631, OnlyNewlines_631) {
    YAML::ostream_wrapper out;
    const char* str = "\n\n\n";
    bool result = YAML::Utils::WriteLiteralString(out, str, 3, 0);
    EXPECT_TRUE(result);
    std::string output = GetOutput(out);
    // "|\n" + 3 newlines
    EXPECT_EQ(output, "|\n\n\n\n");
}

TEST_F(WriteLiteralStringTest_631, SingleCharacter_631) {
    YAML::ostream_wrapper out;
    const char* str = "Z";
    YAML::Utils::WriteLiteralString(out, str, 1, 0);
    std::string output = GetOutput(out);
    EXPECT_EQ(output.substr(0, 2), "|\n");
    EXPECT_NE(output.find('Z'), std::string::npos);
}

TEST_F(WriteLiteralStringTest_631, PartialSize_631) {
    YAML::ostream_wrapper out;
    const char* str = "abcdef";
    YAML::Utils::WriteLiteralString(out, str, 3, 0);
    std::string output = GetOutput(out);
    // Should only process "abc"
    EXPECT_NE(output.find('a'), std::string::npos);
    EXPECT_NE(output.find('b'), std::string::npos);
    EXPECT_NE(output.find('c'), std::string::npos);
    EXPECT_EQ(output.find('d'), std::string::npos);
}

#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "yaml-cpp/ostream_wrapper.h"

// Forward declare the function under test
namespace YAML {
namespace Utils {
bool WriteSingleQuotedString(ostream_wrapper& out, const char* str, std::size_t size);
}
}

class WriteSingleQuotedStringTest_629 : public ::testing::Test {
protected:
    std::string GetOutput(YAML::ostream_wrapper& out) {
        return std::string(out.str(), out.pos());
    }
};

// Test: Empty string should produce ''
TEST_F(WriteSingleQuotedStringTest_629, EmptyString_629) {
    YAML::ostream_wrapper out;
    bool result = YAML::Utils::WriteSingleQuotedString(out, "", 0);
    EXPECT_TRUE(result);
    EXPECT_EQ(GetOutput(out), "''");
}

// Test: Simple string without special characters
TEST_F(WriteSingleQuotedStringTest_629, SimpleString_629) {
    YAML::ostream_wrapper out;
    std::string input = "hello";
    bool result = YAML::Utils::WriteSingleQuotedString(out, input.c_str(), input.size());
    EXPECT_TRUE(result);
    EXPECT_EQ(GetOutput(out), "'hello'");
}

// Test: String containing a single quote should be escaped as ''
TEST_F(WriteSingleQuotedStringTest_629, StringWithSingleQuote_629) {
    YAML::ostream_wrapper out;
    std::string input = "it's";
    bool result = YAML::Utils::WriteSingleQuotedString(out, input.c_str(), input.size());
    EXPECT_TRUE(result);
    EXPECT_EQ(GetOutput(out), "'it''s'");
}

// Test: String containing multiple single quotes
TEST_F(WriteSingleQuotedStringTest_629, StringWithMultipleSingleQuotes_629) {
    YAML::ostream_wrapper out;
    std::string input = "''hello''";
    bool result = YAML::Utils::WriteSingleQuotedString(out, input.c_str(), input.size());
    EXPECT_TRUE(result);
    EXPECT_EQ(GetOutput(out), "''''hello''''");
}

// Test: String containing a newline should return false
TEST_F(WriteSingleQuotedStringTest_629, StringWithNewline_629) {
    YAML::ostream_wrapper out;
    std::string input = "hello\nworld";
    bool result = YAML::Utils::WriteSingleQuotedString(out, input.c_str(), input.size());
    EXPECT_FALSE(result);
}

// Test: String that is just a newline
TEST_F(WriteSingleQuotedStringTest_629, JustNewline_629) {
    YAML::ostream_wrapper out;
    std::string input = "\n";
    bool result = YAML::Utils::WriteSingleQuotedString(out, input.c_str(), input.size());
    EXPECT_FALSE(result);
}

// Test: String with spaces
TEST_F(WriteSingleQuotedStringTest_629, StringWithSpaces_629) {
    YAML::ostream_wrapper out;
    std::string input = "hello world";
    bool result = YAML::Utils::WriteSingleQuotedString(out, input.c_str(), input.size());
    EXPECT_TRUE(result);
    EXPECT_EQ(GetOutput(out), "'hello world'");
}

// Test: String with only a single quote character
TEST_F(WriteSingleQuotedStringTest_629, OnlySingleQuote_629) {
    YAML::ostream_wrapper out;
    std::string input = "'";
    bool result = YAML::Utils::WriteSingleQuotedString(out, input.c_str(), input.size());
    EXPECT_TRUE(result);
    EXPECT_EQ(GetOutput(out), "''''");
}

// Test: String with tabs (should be written normally)
TEST_F(WriteSingleQuotedStringTest_629, StringWithTab_629) {
    YAML::ostream_wrapper out;
    std::string input = "hello\tworld";
    bool result = YAML::Utils::WriteSingleQuotedString(out, input.c_str(), input.size());
    EXPECT_TRUE(result);
    EXPECT_EQ(GetOutput(out), "'hello\tworld'");
}

// Test: String with newline at the beginning
TEST_F(WriteSingleQuotedStringTest_629, NewlineAtBeginning_629) {
    YAML::ostream_wrapper out;
    std::string input = "\nhello";
    bool result = YAML::Utils::WriteSingleQuotedString(out, input.c_str(), input.size());
    EXPECT_FALSE(result);
}

// Test: String with newline at the end
TEST_F(WriteSingleQuotedStringTest_629, NewlineAtEnd_629) {
    YAML::ostream_wrapper out;
    std::string input = "hello\n";
    bool result = YAML::Utils::WriteSingleQuotedString(out, input.c_str(), input.size());
    EXPECT_FALSE(result);
}

// Test: Using ostream_wrapper with an actual stream
TEST_F(WriteSingleQuotedStringTest_629, WithOstream_629) {
    std::stringstream ss;
    YAML::ostream_wrapper out(ss);
    std::string input = "test";
    bool result = YAML::Utils::WriteSingleQuotedString(out, input.c_str(), input.size());
    EXPECT_TRUE(result);
    EXPECT_EQ(ss.str(), "'test'");
}

// Test: Using ostream_wrapper with stream and single quote escaping
TEST_F(WriteSingleQuotedStringTest_629, WithOstreamAndQuotes_629) {
    std::stringstream ss;
    YAML::ostream_wrapper out(ss);
    std::string input = "it's a 'test'";
    bool result = YAML::Utils::WriteSingleQuotedString(out, input.c_str(), input.size());
    EXPECT_TRUE(result);
    EXPECT_EQ(ss.str(), "'it''s a ''test'''");
}

// Test: Single character string
TEST_F(WriteSingleQuotedStringTest_629, SingleCharacter_629) {
    YAML::ostream_wrapper out;
    std::string input = "a";
    bool result = YAML::Utils::WriteSingleQuotedString(out, input.c_str(), input.size());
    EXPECT_TRUE(result);
    EXPECT_EQ(GetOutput(out), "'a'");
}

// Test: String with numbers and special characters (no quotes, no newlines)
TEST_F(WriteSingleQuotedStringTest_629, NumbersAndSpecialChars_629) {
    YAML::ostream_wrapper out;
    std::string input = "123!@#$%^&*()";
    bool result = YAML::Utils::WriteSingleQuotedString(out, input.c_str(), input.size());
    EXPECT_TRUE(result);
    EXPECT_EQ(GetOutput(out), "'123!@#$%^&*()'");
}

// Test: String with consecutive single quotes
TEST_F(WriteSingleQuotedStringTest_629, ConsecutiveSingleQuotes_629) {
    YAML::ostream_wrapper out;
    std::string input = "'''";
    bool result = YAML::Utils::WriteSingleQuotedString(out, input.c_str(), input.size());
    EXPECT_TRUE(result);
    EXPECT_EQ(GetOutput(out), "'''''''");
}

// Test: Long string without special characters
TEST_F(WriteSingleQuotedStringTest_629, LongString_629) {
    YAML::ostream_wrapper out;
    std::string input(1000, 'x');
    bool result = YAML::Utils::WriteSingleQuotedString(out, input.c_str(), input.size());
    EXPECT_TRUE(result);
    std::string expected = "'" + input + "'";
    EXPECT_EQ(GetOutput(out), expected);
}

// Test: String with carriage return (not newline)
TEST_F(WriteSingleQuotedStringTest_629, CarriageReturn_629) {
    YAML::ostream_wrapper out;
    std::string input = "hello\rworld";
    bool result = YAML::Utils::WriteSingleQuotedString(out, input.c_str(), input.size());
    // \r is not \n, so it should succeed
    EXPECT_TRUE(result);
}

// Test: String with mixed quotes and newline - newline should cause failure
TEST_F(WriteSingleQuotedStringTest_629, QuotesAndNewline_629) {
    YAML::ostream_wrapper out;
    std::string input = "it's\nbroken";
    bool result = YAML::Utils::WriteSingleQuotedString(out, input.c_str(), input.size());
    EXPECT_FALSE(result);
}

// Test: Partial size - only process part of the string
TEST_F(WriteSingleQuotedStringTest_629, PartialSize_629) {
    YAML::ostream_wrapper out;
    std::string input = "hello world";
    bool result = YAML::Utils::WriteSingleQuotedString(out, input.c_str(), 5);
    EXPECT_TRUE(result);
    EXPECT_EQ(GetOutput(out), "'hello'");
}

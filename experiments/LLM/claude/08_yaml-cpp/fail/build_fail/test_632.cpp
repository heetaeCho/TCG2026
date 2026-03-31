#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "yaml-cpp/ostream_wrapper.h"

// Forward declare the function under test
namespace YAML {
namespace Utils {
bool WriteChar(ostream_wrapper& out, char ch, int stringEscapingStyle);
}
}

// We need the StringEscaping enum
namespace YAML {
namespace StringEscaping {
enum value { None = 0, NonAscii = 1 };
}
}

class WriteCharTest_632 : public ::testing::Test {
protected:
    std::string GetOutput(YAML::ostream_wrapper& out) {
        return std::string(out.str());
    }
};

// Test lowercase letters are written directly
TEST_F(WriteCharTest_632, LowercaseLetterWrittenDirectly_632) {
    YAML::ostream_wrapper out;
    bool result = YAML::Utils::WriteChar(out, 'a', YAML::StringEscaping::None);
    EXPECT_TRUE(result);
    EXPECT_STREQ("a", out.str());
}

TEST_F(WriteCharTest_632, LowercaseLetterZ_632) {
    YAML::ostream_wrapper out;
    bool result = YAML::Utils::WriteChar(out, 'z', YAML::StringEscaping::None);
    EXPECT_TRUE(result);
    EXPECT_STREQ("z", out.str());
}

TEST_F(WriteCharTest_632, LowercaseLetterM_632) {
    YAML::ostream_wrapper out;
    bool result = YAML::Utils::WriteChar(out, 'm', YAML::StringEscaping::None);
    EXPECT_TRUE(result);
    EXPECT_STREQ("m", out.str());
}

// Test uppercase letters are written directly
TEST_F(WriteCharTest_632, UppercaseLetterWrittenDirectly_632) {
    YAML::ostream_wrapper out;
    bool result = YAML::Utils::WriteChar(out, 'A', YAML::StringEscaping::None);
    EXPECT_TRUE(result);
    EXPECT_STREQ("A", out.str());
}

TEST_F(WriteCharTest_632, UppercaseLetterZ_632) {
    YAML::ostream_wrapper out;
    bool result = YAML::Utils::WriteChar(out, 'Z', YAML::StringEscaping::None);
    EXPECT_TRUE(result);
    EXPECT_STREQ("Z", out.str());
}

// Test double quote character
TEST_F(WriteCharTest_632, DoubleQuoteEscaped_632) {
    YAML::ostream_wrapper out;
    bool result = YAML::Utils::WriteChar(out, '\"', YAML::StringEscaping::None);
    EXPECT_TRUE(result);
    std::string output(out.str());
    EXPECT_EQ("\"\\\"\"", output);
}

// Test tab character
TEST_F(WriteCharTest_632, TabEscaped_632) {
    YAML::ostream_wrapper out;
    bool result = YAML::Utils::WriteChar(out, '\t', YAML::StringEscaping::None);
    EXPECT_TRUE(result);
    std::string output(out.str());
    EXPECT_EQ("\"\\t\"", output);
}

// Test newline character
TEST_F(WriteCharTest_632, NewlineEscaped_632) {
    YAML::ostream_wrapper out;
    bool result = YAML::Utils::WriteChar(out, '\n', YAML::StringEscaping::None);
    EXPECT_TRUE(result);
    std::string output(out.str());
    EXPECT_EQ("\"\\n\"", output);
}

// Test backspace character
TEST_F(WriteCharTest_632, BackspaceEscaped_632) {
    YAML::ostream_wrapper out;
    bool result = YAML::Utils::WriteChar(out, '\b', YAML::StringEscaping::None);
    EXPECT_TRUE(result);
    std::string output(out.str());
    EXPECT_EQ("\"\\b\"", output);
}

// Test carriage return character
TEST_F(WriteCharTest_632, CarriageReturnEscaped_632) {
    YAML::ostream_wrapper out;
    bool result = YAML::Utils::WriteChar(out, '\r', YAML::StringEscaping::None);
    EXPECT_TRUE(result);
    std::string output(out.str());
    EXPECT_EQ("\"\\r\"", output);
}

// Test form feed character
TEST_F(WriteCharTest_632, FormFeedEscaped_632) {
    YAML::ostream_wrapper out;
    bool result = YAML::Utils::WriteChar(out, '\f', YAML::StringEscaping::None);
    EXPECT_TRUE(result);
    std::string output(out.str());
    EXPECT_EQ("\"\\f\"", output);
}

// Test backslash character
TEST_F(WriteCharTest_632, BackslashEscaped_632) {
    YAML::ostream_wrapper out;
    bool result = YAML::Utils::WriteChar(out, '\\', YAML::StringEscaping::None);
    EXPECT_TRUE(result);
    std::string output(out.str());
    EXPECT_EQ("\"\\\\\"", output);
}

// Test printable ASCII characters (0x20 <= ch <= 0x7e, not letter, not special)
TEST_F(WriteCharTest_632, SpaceCharacterQuoted_632) {
    YAML::ostream_wrapper out;
    bool result = YAML::Utils::WriteChar(out, ' ', YAML::StringEscaping::None);
    EXPECT_TRUE(result);
    std::string output(out.str());
    EXPECT_EQ("\" \"", output);
}

TEST_F(WriteCharTest_632, DigitCharacterQuoted_632) {
    YAML::ostream_wrapper out;
    bool result = YAML::Utils::WriteChar(out, '0', YAML::StringEscaping::None);
    EXPECT_TRUE(result);
    std::string output(out.str());
    EXPECT_EQ("\"0\"", output);
}

TEST_F(WriteCharTest_632, ExclamationMarkQuoted_632) {
    YAML::ostream_wrapper out;
    bool result = YAML::Utils::WriteChar(out, '!', YAML::StringEscaping::None);
    EXPECT_TRUE(result);
    std::string output(out.str());
    EXPECT_EQ("\"!\"", output);
}

TEST_F(WriteCharTest_632, TildeCharacterQuoted_632) {
    YAML::ostream_wrapper out;
    bool result = YAML::Utils::WriteChar(out, '~', YAML::StringEscaping::None);
    EXPECT_TRUE(result);
    std::string output(out.str());
    EXPECT_EQ("\"~\"", output);
}

TEST_F(WriteCharTest_632, AtSignQuoted_632) {
    YAML::ostream_wrapper out;
    bool result = YAML::Utils::WriteChar(out, '@', YAML::StringEscaping::None);
    EXPECT_TRUE(result);
    std::string output(out.str());
    EXPECT_EQ("\"@\"", output);
}

// Test non-printable character (falls through to escape sequence)
TEST_F(WriteCharTest_632, NullCharacterEscaped_632) {
    YAML::ostream_wrapper out;
    bool result = YAML::Utils::WriteChar(out, '\0', YAML::StringEscaping::None);
    EXPECT_TRUE(result);
    std::string output(out.str());
    // Should start and end with quote
    EXPECT_FALSE(output.empty());
    EXPECT_EQ(output.front(), '\"');
    EXPECT_EQ(output.back(), '\"');
}

TEST_F(WriteCharTest_632, ControlCharacterEscaped_632) {
    YAML::ostream_wrapper out;
    bool result = YAML::Utils::WriteChar(out, '\x01', YAML::StringEscaping::None);
    EXPECT_TRUE(result);
    std::string output(out.str());
    EXPECT_FALSE(output.empty());
    EXPECT_EQ(output.front(), '\"');
    EXPECT_EQ(output.back(), '\"');
}

TEST_F(WriteCharTest_632, HighBitCharacterEscaped_632) {
    YAML::ostream_wrapper out;
    bool result = YAML::Utils::WriteChar(out, (char)0x80, YAML::StringEscaping::None);
    EXPECT_TRUE(result);
    std::string output(out.str());
    EXPECT_FALSE(output.empty());
    EXPECT_EQ(output.front(), '\"');
    EXPECT_EQ(output.back(), '\"');
}

TEST_F(WriteCharTest_632, DELCharacterEscaped_632) {
    YAML::ostream_wrapper out;
    bool result = YAML::Utils::WriteChar(out, (char)0x7f, YAML::StringEscaping::None);
    EXPECT_TRUE(result);
    std::string output(out.str());
    EXPECT_FALSE(output.empty());
    EXPECT_EQ(output.front(), '\"');
    EXPECT_EQ(output.back(), '\"');
}

// Test with NonAscii escaping style
TEST_F(WriteCharTest_632, NonAsciiEscapingLetter_632) {
    YAML::ostream_wrapper out;
    bool result = YAML::Utils::WriteChar(out, 'a', YAML::StringEscaping::NonAscii);
    EXPECT_TRUE(result);
    EXPECT_STREQ("a", out.str());
}

TEST_F(WriteCharTest_632, NonAsciiEscapingHighBit_632) {
    YAML::ostream_wrapper out;
    bool result = YAML::Utils::WriteChar(out, (char)0xFF, YAML::StringEscaping::NonAscii);
    EXPECT_TRUE(result);
    std::string output(out.str());
    EXPECT_FALSE(output.empty());
    EXPECT_EQ(output.front(), '\"');
    EXPECT_EQ(output.back(), '\"');
}

// Test return value is always true
TEST_F(WriteCharTest_632, AlwaysReturnsTrue_632) {
    YAML::ostream_wrapper out1;
    EXPECT_TRUE(YAML::Utils::WriteChar(out1, 'a', YAML::StringEscaping::None));

    YAML::ostream_wrapper out2;
    EXPECT_TRUE(YAML::Utils::WriteChar(out2, '\0', YAML::StringEscaping::None));

    YAML::ostream_wrapper out3;
    EXPECT_TRUE(YAML::Utils::WriteChar(out3, '\"', YAML::StringEscaping::None));

    YAML::ostream_wrapper out4;
    EXPECT_TRUE(YAML::Utils::WriteChar(out4, (char)0x80, YAML::StringEscaping::NonAscii));
}

// Test with ostream_wrapper backed by a stream
TEST_F(WriteCharTest_632, StreamBackedOutputLetter_632) {
    std::stringstream ss;
    YAML::ostream_wrapper out(ss);
    bool result = YAML::Utils::WriteChar(out, 'x', YAML::StringEscaping::None);
    EXPECT_TRUE(result);
    EXPECT_EQ("x", ss.str());
}

TEST_F(WriteCharTest_632, StreamBackedOutputTab_632) {
    std::stringstream ss;
    YAML::ostream_wrapper out(ss);
    bool result = YAML::Utils::WriteChar(out, '\t', YAML::StringEscaping::None);
    EXPECT_TRUE(result);
    EXPECT_EQ("\"\\t\"", ss.str());
}

TEST_F(WriteCharTest_632, StreamBackedOutputDigit_632) {
    std::stringstream ss;
    YAML::ostream_wrapper out(ss);
    bool result = YAML::Utils::WriteChar(out, '5', YAML::StringEscaping::None);
    EXPECT_TRUE(result);
    EXPECT_EQ("\"5\"", ss.str());
}

// Boundary: char just below 'a' (backtick '`' = 0x60)
TEST_F(WriteCharTest_632, CharJustBelowLowercaseA_632) {
    YAML::ostream_wrapper out;
    bool result = YAML::Utils::WriteChar(out, '`', YAML::StringEscaping::None);
    EXPECT_TRUE(result);
    std::string output(out.str());
    // '`' is 0x60, within printable range, not a letter
    EXPECT_EQ("\"`\"", output);
}

// Boundary: char just above 'z' ('{' = 0x7b)
TEST_F(WriteCharTest_632, CharJustAboveLowercaseZ_632) {
    YAML::ostream_wrapper out;
    bool result = YAML::Utils::WriteChar(out, '{', YAML::StringEscaping::None);
    EXPECT_TRUE(result);
    std::string output(out.str());
    EXPECT_EQ("\"{\"", output);
}

// Boundary: char just below 'A' ('@' = 0x40)
TEST_F(WriteCharTest_632, CharJustBelowUppercaseA_632) {
    YAML::ostream_wrapper out;
    bool result = YAML::Utils::WriteChar(out, '@', YAML::StringEscaping::None);
    EXPECT_TRUE(result);
    std::string output(out.str());
    EXPECT_EQ("\"@\"", output);
}

// Boundary: char just above 'Z' ('[' = 0x5b)
TEST_F(WriteCharTest_632, CharJustAboveUppercaseZ_632) {
    YAML::ostream_wrapper out;
    bool result = YAML::Utils::WriteChar(out, '[', YAML::StringEscaping::None);
    EXPECT_TRUE(result);
    std::string output(out.str());
    EXPECT_EQ("\"[\"", output);
}

// Boundary: 0x1f (just below printable range, not a known escape)
TEST_F(WriteCharTest_632, CharBelowPrintableRange_632) {
    YAML::ostream_wrapper out;
    bool result = YAML::Utils::WriteChar(out, '\x1f', YAML::StringEscaping::None);
    EXPECT_TRUE(result);
    std::string output(out.str());
    EXPECT_FALSE(output.empty());
    EXPECT_EQ(output.front(), '\"');
    EXPECT_EQ(output.back(), '\"');
}

// Test bracket characters in printable range
TEST_F(WriteCharTest_632, PlusSignQuoted_632) {
    YAML::ostream_wrapper out;
    bool result = YAML::Utils::WriteChar(out, '+', YAML::StringEscaping::None);
    EXPECT_TRUE(result);
    std::string output(out.str());
    EXPECT_EQ("\"+\"", output);
}

TEST_F(WriteCharTest_632, SlashQuoted_632) {
    YAML::ostream_wrapper out;
    bool result = YAML::Utils::WriteChar(out, '/', YAML::StringEscaping::None);
    EXPECT_TRUE(result);
    std::string output(out.str());
    EXPECT_EQ("\"/\"", output);
}

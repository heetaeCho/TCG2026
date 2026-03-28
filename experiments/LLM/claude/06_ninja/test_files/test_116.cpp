#include <gtest/gtest.h>
#include <string>

// Declare the function under test
std::string EncodeJSONString(const std::string& in);
void PrintJSONString(const std::string& in);

// Tests for EncodeJSONString
class EncodeJSONStringTest_116 : public ::testing::Test {};

TEST_F(EncodeJSONStringTest_116, EmptyString_116) {
  std::string result = EncodeJSONString("");
  EXPECT_EQ(result, "\"\"");
}

TEST_F(EncodeJSONStringTest_116, SimpleString_116) {
  std::string result = EncodeJSONString("hello");
  EXPECT_EQ(result, "\"hello\"");
}

TEST_F(EncodeJSONStringTest_116, StringWithDoubleQuote_116) {
  std::string result = EncodeJSONString("he\"llo");
  EXPECT_EQ(result, "\"he\\\"llo\"");
}

TEST_F(EncodeJSONStringTest_116, StringWithBackslash_116) {
  std::string result = EncodeJSONString("he\\llo");
  EXPECT_EQ(result, "\"he\\\\llo\"");
}

TEST_F(EncodeJSONStringTest_116, StringWithNewline_116) {
  std::string result = EncodeJSONString("he\nllo");
  EXPECT_EQ(result, "\"he\\nllo\"");
}

TEST_F(EncodeJSONStringTest_116, StringWithTab_116) {
  std::string result = EncodeJSONString("he\tllo");
  // JSON encodes tab as \t
  EXPECT_NE(result.find("\\t"), std::string::npos);
}

TEST_F(EncodeJSONStringTest_116, StringWithCarriageReturn_116) {
  std::string result = EncodeJSONString("he\rllo");
  EXPECT_NE(result.find("\\r"), std::string::npos);
}

TEST_F(EncodeJSONStringTest_116, StringWithMultipleSpecialChars_116) {
  std::string result = EncodeJSONString("a\"b\\c\nd");
  EXPECT_EQ(result, "\"a\\\"b\\\\c\\nd\"");
}

TEST_F(EncodeJSONStringTest_116, StringWithOnlySpecialChars_116) {
  std::string result = EncodeJSONString("\"\\\n");
  EXPECT_EQ(result, "\"\\\"\\\\\\n\"");
}

TEST_F(EncodeJSONStringTest_116, StringWithForwardSlash_116) {
  std::string result = EncodeJSONString("path/to/file");
  // Forward slash may or may not be escaped in JSON
  // But the result should be wrapped in quotes
  EXPECT_EQ(result.front(), '"');
  EXPECT_EQ(result.back(), '"');
  EXPECT_NE(result.find("path"), std::string::npos);
}

TEST_F(EncodeJSONStringTest_116, StringWithSpaces_116) {
  std::string result = EncodeJSONString("hello world");
  EXPECT_EQ(result, "\"hello world\"");
}

TEST_F(EncodeJSONStringTest_116, SingleCharacter_116) {
  std::string result = EncodeJSONString("a");
  EXPECT_EQ(result, "\"a\"");
}

TEST_F(EncodeJSONStringTest_116, StringIsQuotedWrapped_116) {
  std::string result = EncodeJSONString("test");
  ASSERT_GE(result.size(), 2u);
  EXPECT_EQ(result.front(), '"');
  EXPECT_EQ(result.back(), '"');
}

TEST_F(EncodeJSONStringTest_116, StringWithNullByte_116) {
  std::string input("he\0llo", 6);
  std::string result = EncodeJSONString(input);
  // Should still be wrapped in quotes
  EXPECT_EQ(result.front(), '"');
  EXPECT_EQ(result.back(), '"');
}

TEST_F(EncodeJSONStringTest_116, StringWithBackspace_116) {
  std::string result = EncodeJSONString("he\bllo");
  // Backspace should be encoded
  EXPECT_EQ(result.front(), '"');
  EXPECT_EQ(result.back(), '"');
}

TEST_F(EncodeJSONStringTest_116, StringWithFormFeed_116) {
  std::string result = EncodeJSONString("he\fllo");
  EXPECT_EQ(result.front(), '"');
  EXPECT_EQ(result.back(), '"');
}

TEST_F(EncodeJSONStringTest_116, LongString_116) {
  std::string longStr(1000, 'x');
  std::string result = EncodeJSONString(longStr);
  EXPECT_EQ(result.size(), 1002u); // 1000 chars + 2 quotes
  EXPECT_EQ(result.front(), '"');
  EXPECT_EQ(result.back(), '"');
}

TEST_F(EncodeJSONStringTest_116, LongStringWithSpecialChars_116) {
  std::string longStr(500, '\\');
  std::string result = EncodeJSONString(longStr);
  // Each backslash should be doubled, plus 2 quotes
  EXPECT_EQ(result.size(), 1002u);
}

// Test for PrintJSONString - we capture stdout to verify output
class PrintJSONStringTest_116 : public ::testing::Test {};

TEST_F(PrintJSONStringTest_116, PrintsEncodedString_116) {
  // We can at least verify it doesn't crash
  testing::internal::CaptureStdout();
  PrintJSONString("hello");
  std::string output = testing::internal::GetCapturedStdout();
  EXPECT_EQ(output, "\"hello\"");
}

TEST_F(PrintJSONStringTest_116, PrintsEmptyString_116) {
  testing::internal::CaptureStdout();
  PrintJSONString("");
  std::string output = testing::internal::GetCapturedStdout();
  EXPECT_EQ(output, "\"\"");
}

TEST_F(PrintJSONStringTest_116, PrintsStringWithSpecialChars_116) {
  testing::internal::CaptureStdout();
  PrintJSONString("a\"b");
  std::string output = testing::internal::GetCapturedStdout();
  EXPECT_EQ(output, "\"a\\\"b\"");
}

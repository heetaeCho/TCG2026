#include <gtest/gtest.h>
#include <string>

// Declaration of the function under test
std::string EncodeJSONString(const std::string& in);

// Normal operation tests

TEST(EncodeJSONStringTest_115, EmptyString_115) {
  EXPECT_EQ("", EncodeJSONString(""));
}

TEST(EncodeJSONStringTest_115, PlainASCII_115) {
  EXPECT_EQ("hello world", EncodeJSONString("hello world"));
}

TEST(EncodeJSONStringTest_115, AlphanumericCharacters_115) {
  EXPECT_EQ("abc123XYZ", EncodeJSONString("abc123XYZ"));
}

TEST(EncodeJSONStringTest_115, PunctuationNotEscaped_115) {
  EXPECT_EQ("!@#$%^&*()", EncodeJSONString("!@#$%^&*()"));
}

// Escape character tests

TEST(EncodeJSONStringTest_115, BackspaceEscaped_115) {
  EXPECT_EQ("\\b", EncodeJSONString("\b"));
}

TEST(EncodeJSONStringTest_115, FormFeedEscaped_115) {
  EXPECT_EQ("\\f", EncodeJSONString("\f"));
}

TEST(EncodeJSONStringTest_115, NewlineEscaped_115) {
  EXPECT_EQ("\\n", EncodeJSONString("\n"));
}

TEST(EncodeJSONStringTest_115, CarriageReturnEscaped_115) {
  EXPECT_EQ("\\r", EncodeJSONString("\r"));
}

TEST(EncodeJSONStringTest_115, TabEscaped_115) {
  EXPECT_EQ("\\t", EncodeJSONString("\t"));
}

TEST(EncodeJSONStringTest_115, BackslashEscaped_115) {
  EXPECT_EQ("\\\\", EncodeJSONString("\\"));
}

TEST(EncodeJSONStringTest_115, DoubleQuoteEscaped_115) {
  EXPECT_EQ("\\\"", EncodeJSONString("\""));
}

// Control character tests (0x00 to 0x1f, excluding \b, \f, \n, \r, \t)

TEST(EncodeJSONStringTest_115, NullCharacterEscaped_115) {
  std::string input(1, '\0');
  EXPECT_EQ("\\u0000", EncodeJSONString(input));
}

TEST(EncodeJSONStringTest_115, ControlChar0x01_115) {
  std::string input(1, '\x01');
  EXPECT_EQ("\\u0001", EncodeJSONString(input));
}

TEST(EncodeJSONStringTest_115, ControlChar0x02_115) {
  std::string input(1, '\x02');
  EXPECT_EQ("\\u0002", EncodeJSONString(input));
}

TEST(EncodeJSONStringTest_115, ControlChar0x1f_115) {
  std::string input(1, '\x1f');
  EXPECT_EQ("\\u001f", EncodeJSONString(input));
}

TEST(EncodeJSONStringTest_115, ControlChar0x1e_115) {
  std::string input(1, '\x1e');
  EXPECT_EQ("\\u001e", EncodeJSONString(input));
}

TEST(EncodeJSONStringTest_115, ControlChar0x10_115) {
  std::string input(1, '\x10');
  EXPECT_EQ("\\u0010", EncodeJSONString(input));
}

TEST(EncodeJSONStringTest_115, ControlChar0x0e_115) {
  // 0x0e is not \b, \f, \n, \r, \t so should be \\u00 escaped
  std::string input(1, '\x0e');
  EXPECT_EQ("\\u000e", EncodeJSONString(input));
}

// Boundary: 0x20 (space) should NOT be escaped
TEST(EncodeJSONStringTest_115, SpaceNotEscaped_115) {
  EXPECT_EQ(" ", EncodeJSONString(" "));
}

// Mixed content tests

TEST(EncodeJSONStringTest_115, MixedEscapeAndPlain_115) {
  EXPECT_EQ("hello\\nworld", EncodeJSONString("hello\nworld"));
}

TEST(EncodeJSONStringTest_115, MixedMultipleEscapes_115) {
  EXPECT_EQ("a\\tb\\nc\\\\d\\\"e", EncodeJSONString("a\tb\nc\\d\"e"));
}

TEST(EncodeJSONStringTest_115, MultipleBackslashes_115) {
  EXPECT_EQ("\\\\\\\\", EncodeJSONString("\\\\"));
}

TEST(EncodeJSONStringTest_115, MultipleQuotes_115) {
  EXPECT_EQ("\\\"\\\"\\\"", EncodeJSONString("\"\"\""));
}

TEST(EncodeJSONStringTest_115, AllSpecialEscapeCharsInSequence_115) {
  std::string input = "\b\f\n\r\t";
  EXPECT_EQ("\\b\\f\\n\\r\\t", EncodeJSONString(input));
}

TEST(EncodeJSONStringTest_115, ControlCharsMixedWithText_115) {
  std::string input = "a";
  input += '\x01';
  input += "b";
  input += '\x1f';
  input += "c";
  EXPECT_EQ("a\\u0001b\\u001fc", EncodeJSONString(input));
}

// Longer string test
TEST(EncodeJSONStringTest_115, LongStringNoEscaping_115) {
  std::string input(1000, 'a');
  EXPECT_EQ(input, EncodeJSONString(input));
}

TEST(EncodeJSONStringTest_115, LongStringAllNewlines_115) {
  std::string input(100, '\n');
  std::string expected;
  for (int i = 0; i < 100; ++i) {
    expected += "\\n";
  }
  EXPECT_EQ(expected, EncodeJSONString(input));
}

// High-bit characters (>= 0x80) should pass through unchanged
TEST(EncodeJSONStringTest_115, HighBitCharactersPassThrough_115) {
  std::string input;
  input += static_cast<char>(0x80);
  input += static_cast<char>(0xFF);
  input += static_cast<char>(0xC0);
  // These should not be escaped - they pass through as-is
  EXPECT_EQ(input, EncodeJSONString(input));
}

// Test that printable ASCII characters are not escaped
TEST(EncodeJSONStringTest_115, PrintableASCIINotEscaped_115) {
  // Test characters from 0x20 (space) to 0x7e (~), excluding \ and "
  std::string input;
  std::string expected;
  for (char c = 0x20; c <= 0x7e; ++c) {
    if (c == '\\' || c == '"') continue;
    input += c;
    expected += c;
  }
  EXPECT_EQ(expected, EncodeJSONString(input));
}

// Edge case: string with only backslash and quote
TEST(EncodeJSONStringTest_115, OnlySpecialChars_115) {
  EXPECT_EQ("\\\\\\\"", EncodeJSONString("\\\""));
}

// Verify hex digits are lowercase
TEST(EncodeJSONStringTest_115, HexDigitsAreLowercase_115) {
  std::string input(1, '\x1a');
  EXPECT_EQ("\\u001a", EncodeJSONString(input));
}

TEST(EncodeJSONStringTest_115, ControlChar0x0b_115) {
  // 0x0b (vertical tab) - not one of the named escapes
  std::string input(1, '\x0b');
  EXPECT_EQ("\\u000b", EncodeJSONString(input));
}

TEST(EncodeJSONStringTest_115, SingleCharacterString_115) {
  EXPECT_EQ("x", EncodeJSONString("x"));
}

TEST(EncodeJSONStringTest_115, ForwardSlashNotEscaped_115) {
  EXPECT_EQ("/", EncodeJSONString("/"));
}

#include "gtest/gtest.h"
#include "util/logging.h"
#include "leveldb/slice.h"
#include <string>

namespace leveldb {

// Test normal printable ASCII characters are appended as-is
TEST(AppendEscapedStringToTest_457, PrintableAsciiCharacters_457) {
  std::string result;
  Slice value("Hello, World!");
  AppendEscapedStringTo(&result, value);
  EXPECT_EQ(result, "Hello, World!");
}

// Test empty slice results in no changes to the string
TEST(AppendEscapedStringToTest_457, EmptySlice_457) {
  std::string result;
  Slice value("");
  AppendEscapedStringTo(&result, value);
  EXPECT_EQ(result, "");
}

// Test non-printable characters are escaped
TEST(AppendEscapedStringToTest_457, NonPrintableCharactersEscaped_457) {
  std::string result;
  std::string input;
  input.push_back('\x00');
  Slice value(input.data(), input.size());
  AppendEscapedStringTo(&result, value);
  EXPECT_EQ(result, "\\x00");
}

// Test that newline character is escaped
TEST(AppendEscapedStringToTest_457, NewlineEscaped_457) {
  std::string result;
  Slice value("\n");
  AppendEscapedStringTo(&result, value);
  EXPECT_EQ(result, "\\x0a");
}

// Test that tab character is escaped
TEST(AppendEscapedStringToTest_457, TabEscaped_457) {
  std::string result;
  Slice value("\t");
  AppendEscapedStringTo(&result, value);
  EXPECT_EQ(result, "\\x09");
}

// Test boundary: space character (0x20) is printable and should not be escaped
TEST(AppendEscapedStringToTest_457, SpaceCharacterNotEscaped_457) {
  std::string result;
  Slice value(" ");
  AppendEscapedStringTo(&result, value);
  EXPECT_EQ(result, " ");
}

// Test boundary: tilde character (0x7E) is printable and should not be escaped
TEST(AppendEscapedStringToTest_457, TildeCharacterNotEscaped_457) {
  std::string result;
  Slice value("~");
  AppendEscapedStringTo(&result, value);
  EXPECT_EQ(result, "~");
}

// Test boundary: DEL character (0x7F) is NOT printable and should be escaped
TEST(AppendEscapedStringToTest_457, DelCharacterEscaped_457) {
  std::string result;
  std::string input;
  input.push_back('\x7f');
  Slice value(input.data(), input.size());
  AppendEscapedStringTo(&result, value);
  EXPECT_EQ(result, "\\x7f");
}

// Test boundary: character just below space (0x1F) should be escaped
TEST(AppendEscapedStringToTest_457, CharBelowSpaceEscaped_457) {
  std::string result;
  std::string input;
  input.push_back('\x1f');
  Slice value(input.data(), input.size());
  AppendEscapedStringTo(&result, value);
  EXPECT_EQ(result, "\\x1f");
}

// Test mixed printable and non-printable characters
TEST(AppendEscapedStringToTest_457, MixedPrintableAndNonPrintable_457) {
  std::string result;
  std::string input = "A";
  input.push_back('\x01');
  input += "B";
  input.push_back('\xff');
  input += "C";
  Slice value(input.data(), input.size());
  AppendEscapedStringTo(&result, value);
  EXPECT_EQ(result, "A\\x01B\\xffC");
}

// Test high-bit characters (>= 0x80) are escaped
TEST(AppendEscapedStringToTest_457, HighBitCharactersEscaped_457) {
  std::string result;
  std::string input;
  input.push_back('\x80');
  input.push_back('\xfe');
  input.push_back('\xff');
  Slice value(input.data(), input.size());
  AppendEscapedStringTo(&result, value);
  EXPECT_EQ(result, "\\x80\\xfe\\xff");
}

// Test appending to a non-empty string
TEST(AppendEscapedStringToTest_457, AppendToNonEmptyString_457) {
  std::string result = "prefix_";
  Slice value("abc");
  AppendEscapedStringTo(&result, value);
  EXPECT_EQ(result, "prefix_abc");
}

// Test appending non-printable to a non-empty string
TEST(AppendEscapedStringToTest_457, AppendNonPrintableToNonEmptyString_457) {
  std::string result = "prefix_";
  std::string input;
  input.push_back('\x00');
  Slice value(input.data(), input.size());
  AppendEscapedStringTo(&result, value);
  EXPECT_EQ(result, "prefix_\\x00");
}

// Test all printable ASCII characters
TEST(AppendEscapedStringToTest_457, AllPrintableAscii_457) {
  std::string result;
  std::string input;
  for (char c = ' '; c <= '~'; c++) {
    input.push_back(c);
  }
  Slice value(input);
  AppendEscapedStringTo(&result, value);
  EXPECT_EQ(result, input);
}

// Test slice with embedded null bytes
TEST(AppendEscapedStringToTest_457, SliceWithEmbeddedNulls_457) {
  std::string result;
  std::string input;
  input.push_back('A');
  input.push_back('\x00');
  input.push_back('B');
  input.push_back('\x00');
  input.push_back('C');
  Slice value(input.data(), input.size());
  AppendEscapedStringTo(&result, value);
  EXPECT_EQ(result, "A\\x00B\\x00C");
}

// Test multiple calls to AppendEscapedStringTo accumulate correctly
TEST(AppendEscapedStringToTest_457, MultipleCalls_457) {
  std::string result;
  Slice value1("Hello");
  Slice value2(" World");
  AppendEscapedStringTo(&result, value1);
  AppendEscapedStringTo(&result, value2);
  EXPECT_EQ(result, "Hello World");
}

// Test single printable character
TEST(AppendEscapedStringToTest_457, SinglePrintableCharacter_457) {
  std::string result;
  Slice value("A");
  AppendEscapedStringTo(&result, value);
  EXPECT_EQ(result, "A");
}

// Test single non-printable character (bell)
TEST(AppendEscapedStringToTest_457, BellCharacterEscaped_457) {
  std::string result;
  std::string input;
  input.push_back('\x07');
  Slice value(input.data(), input.size());
  AppendEscapedStringTo(&result, value);
  EXPECT_EQ(result, "\\x07");
}

// Test carriage return is escaped
TEST(AppendEscapedStringToTest_457, CarriageReturnEscaped_457) {
  std::string result;
  Slice value("\r");
  AppendEscapedStringTo(&result, value);
  EXPECT_EQ(result, "\\x0d");
}

}  // namespace leveldb

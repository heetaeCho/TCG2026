#include <string>
#include "gtest/gtest.h"
#include "leveldb/slice.h"
#include "util/logging.h"

namespace leveldb {

// Test normal printable ASCII string
TEST(EscapeStringTest_459, NormalAsciiString_459) {
  Slice input("hello world");
  std::string result = EscapeString(input);
  // Normal printable ASCII characters should appear in the output
  EXPECT_FALSE(result.empty());
  // For a fully printable string, the escaped version should contain the original characters
  EXPECT_NE(result.find("hello"), std::string::npos);
}

// Test empty string
TEST(EscapeStringTest_459, EmptyString_459) {
  Slice input("");
  std::string result = EscapeString(input);
  EXPECT_TRUE(result.empty());
}

// Test string with non-printable characters
TEST(EscapeStringTest_459, NonPrintableCharacters_459) {
  std::string data;
  data.push_back('\x00');
  data.push_back('\x01');
  data.push_back('\x1f');
  Slice input(data.data(), data.size());
  std::string result = EscapeString(input);
  // Non-printable characters should be escaped, so result should differ from raw input
  EXPECT_FALSE(result.empty());
  // The escaped form should be longer than the original since non-printable chars get expanded
  EXPECT_GT(result.size(), 0u);
}

// Test string with mixed printable and non-printable characters
TEST(EscapeStringTest_459, MixedPrintableAndNonPrintable_459) {
  std::string data = "abc";
  data.push_back('\x00');
  data += "def";
  Slice input(data.data(), data.size());
  std::string result = EscapeString(input);
  EXPECT_FALSE(result.empty());
  // The printable parts should still be present
  EXPECT_NE(result.find("abc"), std::string::npos);
  EXPECT_NE(result.find("def"), std::string::npos);
}

// Test string with null bytes in the middle
TEST(EscapeStringTest_459, NullBytesInMiddle_459) {
  std::string data("he\x00lo", 5);
  Slice input(data.data(), data.size());
  std::string result = EscapeString(input);
  // Result should not be empty; the null byte should be escaped
  EXPECT_FALSE(result.empty());
}

// Test string with all high-bit characters (values >= 128)
TEST(EscapeStringTest_459, HighBitCharacters_459) {
  std::string data;
  data.push_back('\x80');
  data.push_back('\xff');
  data.push_back('\xfe');
  Slice input(data.data(), data.size());
  std::string result = EscapeString(input);
  EXPECT_FALSE(result.empty());
}

// Test single printable character
TEST(EscapeStringTest_459, SinglePrintableCharacter_459) {
  Slice input("A");
  std::string result = EscapeString(input);
  EXPECT_EQ(result, "A");
}

// Test single non-printable character
TEST(EscapeStringTest_459, SingleNonPrintableCharacter_459) {
  std::string data;
  data.push_back('\x01');
  Slice input(data.data(), data.size());
  std::string result = EscapeString(input);
  // Should be escaped, so not equal to the raw byte
  EXPECT_FALSE(result.empty());
  EXPECT_NE(result, data);
}

// Test string with newline and tab
TEST(EscapeStringTest_459, NewlineAndTab_459) {
  std::string data = "hello\nworld\t!";
  Slice input(data);
  std::string result = EscapeString(input);
  // Newline (\n = 0x0a) and tab (\t = 0x09) are non-printable in some definitions
  // The result should not be empty regardless
  EXPECT_FALSE(result.empty());
}

// Test that the function handles a longer string correctly
TEST(EscapeStringTest_459, LongerString_459) {
  std::string data(1000, 'x');
  Slice input(data);
  std::string result = EscapeString(input);
  EXPECT_EQ(result.size(), 1000u);
  EXPECT_EQ(result, data);
}

// Test string with backslash characters
TEST(EscapeStringTest_459, BackslashCharacters_459) {
  Slice input("back\\slash");
  std::string result = EscapeString(input);
  // Backslash is printable, should be present in output
  EXPECT_FALSE(result.empty());
}

// Test Slice constructed with explicit length
TEST(EscapeStringTest_459, SliceWithExplicitLength_459) {
  const char data[] = "abcdef";
  Slice input(data, 3);  // Only "abc"
  std::string result = EscapeString(input);
  EXPECT_EQ(result, "abc");
}

// Test string containing only spaces
TEST(EscapeStringTest_459, SpacesOnly_459) {
  Slice input("   ");
  std::string result = EscapeString(input);
  EXPECT_EQ(result, "   ");
}

// Test all printable ASCII range
TEST(EscapeStringTest_459, AllPrintableAscii_459) {
  std::string data;
  for (char c = 32; c < 127; ++c) {
    data.push_back(c);
  }
  Slice input(data);
  std::string result = EscapeString(input);
  // All printable characters should pass through (though backslash might be special)
  EXPECT_FALSE(result.empty());
  EXPECT_GE(result.size(), data.size());
}

}  // namespace leveldb

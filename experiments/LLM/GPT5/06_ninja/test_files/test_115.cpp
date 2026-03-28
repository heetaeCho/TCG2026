// File: ./TestProjects/ninja/tests/json_encode_string_test_115.cc

#include <string>
#include "gtest/gtest.h"

// If there's a json.h declaring EncodeJSONString, prefer including that instead
// #include "json.h"

// Forward declaration based on the provided partial implementation.
std::string EncodeJSONString(const std::string& in);

// Tests for EncodeJSONString (TEST_ID = 115)

TEST(EncodeJSONStringTest_115, EmptyString_115) {
  std::string input = "";
  std::string expected = "";

  EXPECT_EQ(expected, EncodeJSONString(input));
}

TEST(EncodeJSONStringTest_115, NoEscapingNeeded_115) {
  // Only printable ASCII characters that don't require escaping
  std::string input = "Hello, world! 1234567890 ABC xyz";
  std::string expected = input;  // Should be unchanged

  EXPECT_EQ(expected, EncodeJSONString(input));
}

TEST(EncodeJSONStringTest_115, StandardControlEscapes_115) {
  // \b, \f, \n, \r, \t should be converted to their short escape sequences
  std::string input;
  input.push_back('\b');
  input.push_back('\f');
  input.push_back('\n');
  input.push_back('\r');
  input.push_back('\t');

  // Expected: backslash + corresponding escape letter
  std::string expected = "\\b\\f\\n\\r\\t";

  EXPECT_EQ(expected, EncodeJSONString(input));
}

TEST(EncodeJSONStringTest_115, OtherControlCharsUnicodeEscaped_115) {
  // Control characters in [0x00, 0x20) that are not covered by the short escapes
  // should be encoded as \u00XX.
  std::string input;
  input.push_back(static_cast<char>(0x00));
  input.push_back(static_cast<char>(0x01));
  input.push_back(static_cast<char>(0x1F));

  std::string expected = "\\u0000\\u0001\\u001f";

  EXPECT_EQ(expected, EncodeJSONString(input));
}

TEST(EncodeJSONStringTest_115, BackslashAndQuoteEscaped_115) {
  // Backslash and double quote should be escaped
  std::string input = "\\\"";  // characters: '\' and '"'

  // '\' -> "\\\\"
  // '"' -> "\\\""
  // Result characters: '\', '\', '\', '"'
  std::string expected = "\\\\\\\"";

  EXPECT_EQ(expected, EncodeJSONString(input));
}

TEST(EncodeJSONStringTest_115, MixedContentIsEncodedCorrectly_115) {
  // Combination of normal chars, control chars, backslash, and quote
  std::string input;
  input += "Line1";
  input.push_back('\n');                 // newline -> \n
  input += "Path: C:\\temp\\";          // backslashes should be escaped
  input.push_back('\"');                // quote -> \"
  input += "end";

  // Expected:
  // "Line1" + "\n" + "Path: C:\\temp\\" + "\"" + "end"
  std::string expected = "Line1\\nPath: C:\\\\temp\\\\\\\"end";

  EXPECT_EQ(expected, EncodeJSONString(input));
}

TEST(EncodeJSONStringTest_115, NonAsciiUtf8BytesPreserved_115) {
  // Bytes that are not control chars, backslash, or double quote
  // should be left as-is. This includes UTF-8 multibyte sequences.
  // Example: Korean "안녕" in UTF-8.
  std::string input = u8"안녕";

  // The encoder does not specially handle UTF-8, so the output
  // should match the input byte-for-byte.
  std::string expected = input;

  EXPECT_EQ(expected, EncodeJSONString(input));
}

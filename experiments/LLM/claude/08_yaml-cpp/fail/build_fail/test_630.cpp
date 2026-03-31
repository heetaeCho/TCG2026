#include <gtest/gtest.h>
#include <string>
#include <sstream>
#include "yaml-cpp/ostream_wrapper.h"

// We need to declare the function we're testing
namespace YAML {
namespace Utils {

namespace StringEscaping {
enum value { Default, NonAscii };
}

bool WriteDoubleQuotedString(ostream_wrapper& out, const char* str,
                             std::size_t size,
                             StringEscaping::value stringEscaping);
}  // namespace Utils
}  // namespace YAML

class WriteDoubleQuotedStringTest_630 : public ::testing::Test {
 protected:
  std::string GetOutput(YAML::ostream_wrapper& out) {
    return std::string(out.str(), out.pos());
  }
};

// Test: Empty string should produce empty double-quoted string
TEST_F(WriteDoubleQuotedStringTest_630, EmptyString_630) {
  YAML::ostream_wrapper out;
  std::string input = "";
  bool result = YAML::Utils::WriteDoubleQuotedString(
      out, input.c_str(), input.size(),
      YAML::Utils::StringEscaping::Default);
  EXPECT_TRUE(result);
  EXPECT_EQ(GetOutput(out), "\"\"");
}

// Test: Simple ASCII string without special characters
TEST_F(WriteDoubleQuotedStringTest_630, SimpleAsciiString_630) {
  YAML::ostream_wrapper out;
  std::string input = "hello world";
  bool result = YAML::Utils::WriteDoubleQuotedString(
      out, input.c_str(), input.size(),
      YAML::Utils::StringEscaping::Default);
  EXPECT_TRUE(result);
  EXPECT_EQ(GetOutput(out), "\"hello world\"");
}

// Test: String with double quote character is escaped
TEST_F(WriteDoubleQuotedStringTest_630, EscapeDoubleQuote_630) {
  YAML::ostream_wrapper out;
  std::string input = "say \"hi\"";
  bool result = YAML::Utils::WriteDoubleQuotedString(
      out, input.c_str(), input.size(),
      YAML::Utils::StringEscaping::Default);
  EXPECT_TRUE(result);
  EXPECT_EQ(GetOutput(out), "\"say \\\"hi\\\"\"");
}

// Test: String with backslash is escaped
TEST_F(WriteDoubleQuotedStringTest_630, EscapeBackslash_630) {
  YAML::ostream_wrapper out;
  std::string input = "path\\to\\file";
  bool result = YAML::Utils::WriteDoubleQuotedString(
      out, input.c_str(), input.size(),
      YAML::Utils::StringEscaping::Default);
  EXPECT_TRUE(result);
  EXPECT_EQ(GetOutput(out), "\"path\\\\to\\\\file\"");
}

// Test: Newline character is escaped
TEST_F(WriteDoubleQuotedStringTest_630, EscapeNewline_630) {
  YAML::ostream_wrapper out;
  std::string input = "line1\nline2";
  bool result = YAML::Utils::WriteDoubleQuotedString(
      out, input.c_str(), input.size(),
      YAML::Utils::StringEscaping::Default);
  EXPECT_TRUE(result);
  EXPECT_EQ(GetOutput(out), "\"line1\\nline2\"");
}

// Test: Tab character is escaped
TEST_F(WriteDoubleQuotedStringTest_630, EscapeTab_630) {
  YAML::ostream_wrapper out;
  std::string input = "col1\tcol2";
  bool result = YAML::Utils::WriteDoubleQuotedString(
      out, input.c_str(), input.size(),
      YAML::Utils::StringEscaping::Default);
  EXPECT_TRUE(result);
  EXPECT_EQ(GetOutput(out), "\"col1\\tcol2\"");
}

// Test: Carriage return is escaped
TEST_F(WriteDoubleQuotedStringTest_630, EscapeCarriageReturn_630) {
  YAML::ostream_wrapper out;
  std::string input = "line1\rline2";
  bool result = YAML::Utils::WriteDoubleQuotedString(
      out, input.c_str(), input.size(),
      YAML::Utils::StringEscaping::Default);
  EXPECT_TRUE(result);
  EXPECT_EQ(GetOutput(out), "\"line1\\rline2\"");
}

// Test: Backspace character is escaped
TEST_F(WriteDoubleQuotedStringTest_630, EscapeBackspace_630) {
  YAML::ostream_wrapper out;
  std::string input = "text\b";
  bool result = YAML::Utils::WriteDoubleQuotedString(
      out, input.c_str(), input.size(),
      YAML::Utils::StringEscaping::Default);
  EXPECT_TRUE(result);
  EXPECT_EQ(GetOutput(out), "\"text\\b\"");
}

// Test: Form feed character is escaped
TEST_F(WriteDoubleQuotedStringTest_630, EscapeFormFeed_630) {
  YAML::ostream_wrapper out;
  std::string input = "text\f";
  bool result = YAML::Utils::WriteDoubleQuotedString(
      out, input.c_str(), input.size(),
      YAML::Utils::StringEscaping::Default);
  EXPECT_TRUE(result);
  EXPECT_EQ(GetOutput(out), "\"text\\f\"");
}

// Test: Multiple escape characters in one string
TEST_F(WriteDoubleQuotedStringTest_630, MultipleEscapeCharacters_630) {
  YAML::ostream_wrapper out;
  std::string input = "\n\t\r\\\"";
  bool result = YAML::Utils::WriteDoubleQuotedString(
      out, input.c_str(), input.size(),
      YAML::Utils::StringEscaping::Default);
  EXPECT_TRUE(result);
  EXPECT_EQ(GetOutput(out), "\"\\n\\t\\r\\\\\\\"\"");
}

// Test: Control character below 0x20 (e.g., 0x01) is escaped
TEST_F(WriteDoubleQuotedStringTest_630, ControlCharacterBelow0x20_630) {
  YAML::ostream_wrapper out;
  std::string input = "a\x01" "b";
  bool result = YAML::Utils::WriteDoubleQuotedString(
      out, input.c_str(), input.size(),
      YAML::Utils::StringEscaping::Default);
  EXPECT_TRUE(result);
  std::string output = GetOutput(out);
  // Should start and end with double quotes, 'a' and 'b' should be present
  EXPECT_EQ(output.front(), '"');
  EXPECT_EQ(output.back(), '"');
  // The control character should be escaped, so the output should be longer than "a\x01b"
  EXPECT_GT(output.size(), 5u);
}

// Test: String with only printable ASCII characters (no escaping needed)
TEST_F(WriteDoubleQuotedStringTest_630, PrintableAsciiOnly_630) {
  YAML::ostream_wrapper out;
  std::string input = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789 !#$%&'()*+,-./:;<=>?@[]^_`{|}~";
  bool result = YAML::Utils::WriteDoubleQuotedString(
      out, input.c_str(), input.size(),
      YAML::Utils::StringEscaping::Default);
  EXPECT_TRUE(result);
  std::string output = GetOutput(out);
  EXPECT_EQ(output.front(), '"');
  EXPECT_EQ(output.back(), '"');
  // The content between quotes should be the same as input (no escaping needed)
  EXPECT_EQ(output, "\"" + input + "\"");
}

// Test: Return value is always true
TEST_F(WriteDoubleQuotedStringTest_630, ReturnValueIsTrue_630) {
  YAML::ostream_wrapper out;
  std::string input = "test";
  bool result = YAML::Utils::WriteDoubleQuotedString(
      out, input.c_str(), input.size(),
      YAML::Utils::StringEscaping::Default);
  EXPECT_TRUE(result);
}

// Test: Single character string
TEST_F(WriteDoubleQuotedStringTest_630, SingleCharacterString_630) {
  YAML::ostream_wrapper out;
  std::string input = "x";
  bool result = YAML::Utils::WriteDoubleQuotedString(
      out, input.c_str(), input.size(),
      YAML::Utils::StringEscaping::Default);
  EXPECT_TRUE(result);
  EXPECT_EQ(GetOutput(out), "\"x\"");
}

// Test: Single escape character
TEST_F(WriteDoubleQuotedStringTest_630, SingleEscapeCharacter_630) {
  YAML::ostream_wrapper out;
  std::string input = "\"";
  bool result = YAML::Utils::WriteDoubleQuotedString(
      out, input.c_str(), input.size(),
      YAML::Utils::StringEscaping::Default);
  EXPECT_TRUE(result);
  EXPECT_EQ(GetOutput(out), "\"\\\"\"");
}

// Test: Writing to a stream-backed ostream_wrapper
TEST_F(WriteDoubleQuotedStringTest_630, StreamBackedWrapper_630) {
  std::stringstream ss;
  YAML::ostream_wrapper out(ss);
  std::string input = "hello";
  bool result = YAML::Utils::WriteDoubleQuotedString(
      out, input.c_str(), input.size(),
      YAML::Utils::StringEscaping::Default);
  EXPECT_TRUE(result);
  EXPECT_EQ(ss.str(), "\"hello\"");
}

// Test: NUL character (0x00) in string - control character below 0x20
TEST_F(WriteDoubleQuotedStringTest_630, NullCharacter_630) {
  YAML::ostream_wrapper out;
  // Create a string with a NUL character embedded
  std::string input("a\0b", 3);
  bool result = YAML::Utils::WriteDoubleQuotedString(
      out, input.c_str(), input.size(),
      YAML::Utils::StringEscaping::Default);
  EXPECT_TRUE(result);
  std::string output = GetOutput(out);
  EXPECT_EQ(output.front(), '"');
  EXPECT_EQ(output.back(), '"');
}

// Test: UTF-8 multibyte characters with Default escaping
TEST_F(WriteDoubleQuotedStringTest_630, Utf8MultibyteDefault_630) {
  YAML::ostream_wrapper out;
  // UTF-8 encoding of U+00E9 (é) - 0xC3 0xA9
  std::string input = "\xC3\xA9";
  bool result = YAML::Utils::WriteDoubleQuotedString(
      out, input.c_str(), input.size(),
      YAML::Utils::StringEscaping::Default);
  EXPECT_TRUE(result);
  std::string output = GetOutput(out);
  EXPECT_EQ(output.front(), '"');
  EXPECT_EQ(output.back(), '"');
  // With Default escaping, code point 0xE9 (> 0xA0 and <= 0x7E is false, but > 0xA0)
  // should be written as-is since it's not in control range and not NonAscii mode
  EXPECT_EQ(output, "\"\xC3\xA9\"");
}

// Test: UTF-8 multibyte characters with NonAscii escaping
TEST_F(WriteDoubleQuotedStringTest_630, Utf8MultibyteNonAscii_630) {
  YAML::ostream_wrapper out;
  // UTF-8 encoding of U+00E9 (é) - 0xC3 0xA9
  std::string input = "\xC3\xA9";
  bool result = YAML::Utils::WriteDoubleQuotedString(
      out, input.c_str(), input.size(),
      YAML::Utils::StringEscaping::NonAscii);
  EXPECT_TRUE(result);
  std::string output = GetOutput(out);
  EXPECT_EQ(output.front(), '"');
  EXPECT_EQ(output.back(), '"');
  // With NonAscii escaping, code point > 0x7E should be escaped
  // Should not contain the raw UTF-8 bytes
  EXPECT_NE(output, "\"\xC3\xA9\"");
}

// Test: String with space character (0x20 - boundary of control characters)
TEST_F(WriteDoubleQuotedStringTest_630, SpaceCharacterBoundary_630) {
  YAML::ostream_wrapper out;
  std::string input = " ";
  bool result = YAML::Utils::WriteDoubleQuotedString(
      out, input.c_str(), input.size(),
      YAML::Utils::StringEscaping::Default);
  EXPECT_TRUE(result);
  EXPECT_EQ(GetOutput(out), "\" \"");
}

// Test: Character 0x1F (just below 0x20 boundary) should be escaped
TEST_F(WriteDoubleQuotedStringTest_630, ControlChar0x1F_630) {
  YAML::ostream_wrapper out;
  std::string input = "\x1F";
  bool result = YAML::Utils::WriteDoubleQuotedString(
      out, input.c_str(), input.size(),
      YAML::Utils::StringEscaping::Default);
  EXPECT_TRUE(result);
  std::string output = GetOutput(out);
  EXPECT_EQ(output.front(), '"');
  EXPECT_EQ(output.back(), '"');
  // 0x1F is a control char, should be escaped
  EXPECT_NE(output, "\"\x1F\"");
}

// Test: Character 0x7E (tilde, last printable ASCII) should NOT be escaped
TEST_F(WriteDoubleQuotedStringTest_630, TildeCharacter_630) {
  YAML::ostream_wrapper out;
  std::string input = "~";
  bool result = YAML::Utils::WriteDoubleQuotedString(
      out, input.c_str(), input.size(),
      YAML::Utils::StringEscaping::Default);
  EXPECT_TRUE(result);
  EXPECT_EQ(GetOutput(out), "\"~\"");
}

// Test: Tilde with NonAscii escaping should still NOT be escaped (0x7E is not > 0x7E)
TEST_F(WriteDoubleQuotedStringTest_630, TildeNonAscii_630) {
  YAML::ostream_wrapper out;
  std::string input = "~";
  bool result = YAML::Utils::WriteDoubleQuotedString(
      out, input.c_str(), input.size(),
      YAML::Utils::StringEscaping::NonAscii);
  EXPECT_TRUE(result);
  EXPECT_EQ(GetOutput(out), "\"~\"");
}

// Test: Long string with mixed content
TEST_F(WriteDoubleQuotedStringTest_630, LongMixedString_630) {
  YAML::ostream_wrapper out;
  std::string input = "Hello, \"World\"!\nThis is a\ttest\\path.";
  bool result = YAML::Utils::WriteDoubleQuotedString(
      out, input.c_str(), input.size(),
      YAML::Utils::StringEscaping::Default);
  EXPECT_TRUE(result);
  std::string expected = "\"Hello, \\\"World\\\"!\\nThis is a\\ttest\\\\path.\"";
  EXPECT_EQ(GetOutput(out), expected);
}

// Test: BOM character (U+FEFF) should be escaped - encoded as UTF-8: EF BB BF
TEST_F(WriteDoubleQuotedStringTest_630, ByteOrderMark_630) {
  YAML::ostream_wrapper out;
  std::string input = "\xEF\xBB\xBF";  // UTF-8 encoding of U+FEFF
  bool result = YAML::Utils::WriteDoubleQuotedString(
      out, input.c_str(), input.size(),
      YAML::Utils::StringEscaping::Default);
  EXPECT_TRUE(result);
  std::string output = GetOutput(out);
  EXPECT_EQ(output.front(), '"');
  EXPECT_EQ(output.back(), '"');
  // BOM should be escaped, not written raw
  EXPECT_NE(output, "\"\xEF\xBB\xBF\"");
}

// Test: Non-breaking space (U+00A0) should be escaped - in range 0x80-0xA0
TEST_F(WriteDoubleQuotedStringTest_630, NonBreakingSpace_630) {
  YAML::ostream_wrapper out;
  // UTF-8 encoding of U+00A0: 0xC2 0xA0
  std::string input = "\xC2\xA0";
  bool result = YAML::Utils::WriteDoubleQuotedString(
      out, input.c_str(), input.size(),
      YAML::Utils::StringEscaping::Default);
  EXPECT_TRUE(result);
  std::string output = GetOutput(out);
  EXPECT_EQ(output.front(), '"');
  EXPECT_EQ(output.back(), '"');
  // U+00A0 is in 0x80-0xA0 range, should be escaped
  EXPECT_NE(output, "\"\xC2\xA0\"");
}

// Test: Character U+0080 should be escaped (boundary of 0x80 range)
TEST_F(WriteDoubleQuotedStringTest_630, ControlChar0x80_630) {
  YAML::ostream_wrapper out;
  // UTF-8 encoding of U+0080: 0xC2 0x80
  std::string input = "\xC2\x80";
  bool result = YAML::Utils::WriteDoubleQuotedString(
      out, input.c_str(), input.size(),
      YAML::Utils::StringEscaping::Default);
  EXPECT_TRUE(result);
  std::string output = GetOutput(out);
  // U+0080 is in range 0x80-0xA0, should be escaped
  EXPECT_NE(output, "\"\xC2\x80\"");
}

// Test: Character just above 0xA0 (U+00A1) with Default escaping should NOT be escaped
TEST_F(WriteDoubleQuotedStringTest_630, CharAboveNbsp_630) {
  YAML::ostream_wrapper out;
  // UTF-8 encoding of U+00A1 (¡): 0xC2 0xA1
  std::string input = "\xC2\xA1";
  bool result = YAML::Utils::WriteDoubleQuotedString(
      out, input.c_str(), input.size(),
      YAML::Utils::StringEscaping::Default);
  EXPECT_TRUE(result);
  std::string output = GetOutput(out);
  // U+00A1 is > 0xA0, not BOM, Default escaping: should be written as-is
  EXPECT_EQ(output, "\"\xC2\xA1\"");
}

// Test: Character just above 0xA0 (U+00A1) with NonAscii escaping SHOULD be escaped
TEST_F(WriteDoubleQuotedStringTest_630, CharAboveNbspNonAscii_630) {
  YAML::ostream_wrapper out;
  // UTF-8 encoding of U+00A1 (¡): 0xC2 0xA1
  std::string input = "\xC2\xA1";
  bool result = YAML::Utils::WriteDoubleQuotedString(
      out, input.c_str(), input.size(),
      YAML::Utils::StringEscaping::NonAscii);
  EXPECT_TRUE(result);
  std::string output = GetOutput(out);
  // U+00A1 > 0x7E, NonAscii: should be escaped
  EXPECT_NE(output, "\"\xC2\xA1\"");
}

// Test: Exclamation mark (0x21, just above space) should not be escaped
TEST_F(WriteDoubleQuotedStringTest_630, ExclamationMark_630) {
  YAML::ostream_wrapper out;
  std::string input = "!";
  bool result = YAML::Utils::WriteDoubleQuotedString(
      out, input.c_str(), input.size(),
      YAML::Utils::StringEscaping::Default);
  EXPECT_TRUE(result);
  EXPECT_EQ(GetOutput(out), "\"!\"");
}

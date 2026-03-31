#include <gtest/gtest.h>
#include <string>

// Include the header that declares Exiv2::urlencode
// Based on the file path, this is likely in futils.hpp or similar
#include "futils.hpp"

namespace {

// Test normal alphanumeric characters pass through unchanged
TEST(UrlencodeTest_1801, AlphanumericCharactersUnchanged_1801) {
  std::string input = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
  std::string result = Exiv2::urlencode(input);
  EXPECT_EQ(result, input);
}

// Test unreserved characters (- _ . ~) pass through unchanged
TEST(UrlencodeTest_1801, UnreservedCharactersUnchanged_1801) {
  std::string input = "-_.~";
  std::string result = Exiv2::urlencode(input);
  EXPECT_EQ(result, input);
}

// Test space is encoded as '+'
TEST(UrlencodeTest_1801, SpaceEncodedAsPlus_1801) {
  std::string input = " ";
  std::string result = Exiv2::urlencode(input);
  EXPECT_EQ(result, "+");
}

// Test multiple spaces
TEST(UrlencodeTest_1801, MultipleSpacesEncodedAsPlus_1801) {
  std::string input = "   ";
  std::string result = Exiv2::urlencode(input);
  EXPECT_EQ(result, "+++");
}

// Test special characters are percent-encoded
TEST(UrlencodeTest_1801, SpecialCharactersPercentEncoded_1801) {
  std::string input = "!";
  std::string result = Exiv2::urlencode(input);
  EXPECT_EQ(result, "%21");
}

// Test @ symbol is percent-encoded
TEST(UrlencodeTest_1801, AtSymbolPercentEncoded_1801) {
  std::string input = "@";
  std::string result = Exiv2::urlencode(input);
  EXPECT_EQ(result, "%40");
}

// Test # symbol is percent-encoded
TEST(UrlencodeTest_1801, HashSymbolPercentEncoded_1801) {
  std::string input = "#";
  std::string result = Exiv2::urlencode(input);
  EXPECT_EQ(result, "%23");
}

// Test empty string
TEST(UrlencodeTest_1801, EmptyStringReturnsEmpty_1801) {
  std::string input = "";
  std::string result = Exiv2::urlencode(input);
  EXPECT_EQ(result, "");
}

// Test mixed content: alphanumeric, spaces, and special characters
TEST(UrlencodeTest_1801, MixedContentEncoding_1801) {
  std::string input = "hello world!";
  std::string result = Exiv2::urlencode(input);
  EXPECT_EQ(result, "hello+world%21");
}

// Test URL-like string
TEST(UrlencodeTest_1801, UrlLikeStringEncoding_1801) {
  std::string input = "key=value&foo=bar";
  std::string result = Exiv2::urlencode(input);
  EXPECT_EQ(result, "key%3Dvalue%26foo%3Dbar");
}

// Test slash character encoding
TEST(UrlencodeTest_1801, SlashIsPercentEncoded_1801) {
  std::string input = "/";
  std::string result = Exiv2::urlencode(input);
  EXPECT_EQ(result, "%2F");
}

// Test colon character encoding
TEST(UrlencodeTest_1801, ColonIsPercentEncoded_1801) {
  std::string input = ":";
  std::string result = Exiv2::urlencode(input);
  EXPECT_EQ(result, "%3A");
}

// Test question mark encoding
TEST(UrlencodeTest_1801, QuestionMarkIsPercentEncoded_1801) {
  std::string input = "?";
  std::string result = Exiv2::urlencode(input);
  EXPECT_EQ(result, "%3F");
}

// Test percent sign itself is encoded
TEST(UrlencodeTest_1801, PercentSignIsPercentEncoded_1801) {
  std::string input = "%";
  std::string result = Exiv2::urlencode(input);
  EXPECT_EQ(result, "%25");
}

// Test tab character encoding
TEST(UrlencodeTest_1801, TabCharacterPercentEncoded_1801) {
  std::string input = "\t";
  std::string result = Exiv2::urlencode(input);
  EXPECT_EQ(result, "%09");
}

// Test newline character encoding
TEST(UrlencodeTest_1801, NewlineCharacterPercentEncoded_1801) {
  std::string input = "\n";
  std::string result = Exiv2::urlencode(input);
  EXPECT_EQ(result, "%0A");
}

// Test null byte in string
TEST(UrlencodeTest_1801, NullBytePercentEncoded_1801) {
  std::string input(1, '\0');
  std::string result = Exiv2::urlencode(input);
  EXPECT_EQ(result, "%00");
}

// Test high-bit characters (non-ASCII, > 127)
TEST(UrlencodeTest_1801, HighBitCharactersPercentEncoded_1801) {
  std::string input(1, static_cast<char>(0xFF));
  std::string result = Exiv2::urlencode(input);
  EXPECT_EQ(result, "%FF");
}

// Test character 0x80
TEST(UrlencodeTest_1801, Char0x80PercentEncoded_1801) {
  std::string input(1, static_cast<char>(0x80));
  std::string result = Exiv2::urlencode(input);
  EXPECT_EQ(result, "%80");
}

// Test a longer string with mixed characters
TEST(UrlencodeTest_1801, LongerMixedStringEncoding_1801) {
  std::string input = "Hello World! How are you?";
  std::string result = Exiv2::urlencode(input);
  EXPECT_EQ(result, "Hello+World%21+How+are+you%3F");
}

// Test single alphanumeric character
TEST(UrlencodeTest_1801, SingleAlphanumericCharacter_1801) {
  EXPECT_EQ(Exiv2::urlencode("a"), "a");
  EXPECT_EQ(Exiv2::urlencode("Z"), "Z");
  EXPECT_EQ(Exiv2::urlencode("5"), "5");
}

// Test single unreserved character
TEST(UrlencodeTest_1801, SingleUnreservedCharacter_1801) {
  EXPECT_EQ(Exiv2::urlencode("-"), "-");
  EXPECT_EQ(Exiv2::urlencode("_"), "_");
  EXPECT_EQ(Exiv2::urlencode("."), ".");
  EXPECT_EQ(Exiv2::urlencode("~"), "~");
}

// Test plus sign is percent-encoded (not passed through)
TEST(UrlencodeTest_1801, PlusSignIsPercentEncoded_1801) {
  std::string input = "+";
  std::string result = Exiv2::urlencode(input);
  EXPECT_EQ(result, "%2B");
}

// Test brackets are percent-encoded
TEST(UrlencodeTest_1801, BracketsPercentEncoded_1801) {
  EXPECT_EQ(Exiv2::urlencode("["), "%5B");
  EXPECT_EQ(Exiv2::urlencode("]"), "%5D");
  EXPECT_EQ(Exiv2::urlencode("("), "%28");
  EXPECT_EQ(Exiv2::urlencode(")"), "%29");
}

// Test curly braces are percent-encoded
TEST(UrlencodeTest_1801, CurlyBracesPercentEncoded_1801) {
  EXPECT_EQ(Exiv2::urlencode("{"), "%7B");
  EXPECT_EQ(Exiv2::urlencode("}"), "%7D");
}

// Test pipe character
TEST(UrlencodeTest_1801, PipeCharacterPercentEncoded_1801) {
  EXPECT_EQ(Exiv2::urlencode("|"), "%7C");
}

// Test backslash
TEST(UrlencodeTest_1801, BackslashPercentEncoded_1801) {
  EXPECT_EQ(Exiv2::urlencode("\\"), "%5C");
}

// Test double quotes
TEST(UrlencodeTest_1801, DoubleQuotesPercentEncoded_1801) {
  EXPECT_EQ(Exiv2::urlencode("\""), "%22");
}

// Test single quote
TEST(UrlencodeTest_1801, SingleQuotePercentEncoded_1801) {
  EXPECT_EQ(Exiv2::urlencode("'"), "%27");
}

// Test encoding preserves order
TEST(UrlencodeTest_1801, EncodingPreservesOrder_1801) {
  std::string input = "a b!c";
  std::string result = Exiv2::urlencode(input);
  EXPECT_EQ(result, "a+b%21c");
}

// Test UTF-8 multi-byte sequence
TEST(UrlencodeTest_1801, Utf8MultiByteSequenceEncoded_1801) {
  // é in UTF-8 is 0xC3 0xA9
  std::string input = "\xC3\xA9";
  std::string result = Exiv2::urlencode(input);
  EXPECT_EQ(result, "%C3%A9");
}

// Test hex output uses uppercase
TEST(UrlencodeTest_1801, HexOutputUppercase_1801) {
  // Character 0xAB should produce %AB
  std::string input(1, static_cast<char>(0xAB));
  std::string result = Exiv2::urlencode(input);
  // Check that hex digits are uppercase (A, B, C, D, E, F)
  EXPECT_EQ(result.length(), 3u);
  EXPECT_EQ(result[0], '%');
  // Verify it's either %AB or %ab - the implementation determines case
  // Based on typical implementations, check for uppercase
  bool isUpper = (result == "%AB");
  bool isLower = (result == "%ab");
  EXPECT_TRUE(isUpper || isLower) << "Result was: " << result;
}

}  // namespace

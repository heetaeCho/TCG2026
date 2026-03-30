// File: re2_quotemeta_test_259.cc
#include <gtest/gtest.h>
#include <string>

// The partial implementation places RE2 in namespace re2 with a public member QuoteMeta.
// We only exercise the public interface/observable behavior.
namespace re2 {

class RE2; // forward declaration not strictly necessary if headers are included.

}  // namespace re2

#include "re2/re2.cc"  // Pulls in the provided minimal implementation with QuoteMeta

namespace {

using re2::RE2;

class RE2_QuoteMetaTest_259 : public ::testing::Test {
protected:
  RE2 re_;  // Minimal object; QuoteMeta does not depend on instance state.
};

// Normal operation: alphanumerics and underscore should remain unchanged.
TEST_F(RE2_QuoteMetaTest_259, AlnumAndUnderscoreRemainUnchanged_259) {
  std::string input = "AbcXYZ_123";
  std::string expected = "AbcXYZ_123";
  EXPECT_EQ(re_.QuoteMeta(input), expected);
}

// Boundary: empty input should return empty output.
TEST_F(RE2_QuoteMetaTest_259, EmptyStringReturnsEmpty_259) {
  std::string input = "";
  std::string expected = "";
  EXPECT_EQ(re_.QuoteMeta(input), expected);
}

// Normal operation: common regex metacharacters (and other ASCII non-alnum) are backslash-escaped.
TEST_F(RE2_QuoteMetaTest_259, EscapesCommonRegexMetacharacters_259) {
  // Includes many typical regex metacharacters and a space + slash.
  std::string input   = R"(.^$*+?()[]{}|\ /)";
  // Every non-alnum ASCII and not '_' should be prefixed with '\'
  std::string expected = R"(\.\^\$\*\+\?\(\)\[\]\{\}\|\\\ \/)";
  EXPECT_EQ(re_.QuoteMeta(input), expected);
}

// Normal operation: mixture of safe and unsafe characters is handled positionally.
TEST_F(RE2_QuoteMetaTest_259, MixedSafeAndUnsafeCharacters_259) {
  std::string input    = "a.c+d?";
  std::string expected = "a\\.c\\+d\\?";
  EXPECT_EQ(re_.QuoteMeta(input), expected);
}

// Special handling: embedded NUL characters become "\x00" (four visible chars).
TEST_F(RE2_QuoteMetaTest_259, NullByteBecomesHexEscape_259) {
  std::string input("ab\0cd", 5);  // 'a','b','\0','c','d'
  std::string expected = "ab\\x00cd";
  EXPECT_EQ(re_.QuoteMeta(input), expected);
}

// Non-ASCII bytes (UTF-8) should not be escaped by this implementation.
TEST_F(RE2_QuoteMetaTest_259, NonAsciiUtf8BytesAreNotEscaped_259) {
  // "éøβ" in UTF-8; bytes have high bit set and should pass through unchanged.
  std::string input   = u8"éøβ";
  std::string expected = u8"éøβ";
  EXPECT_EQ(re_.QuoteMeta(input), expected);
}

// Mixed UTF-8 (non-ASCII) with ASCII metacharacters: only the ASCII metacharacters are escaped.
TEST_F(RE2_QuoteMetaTest_259, MixedUtf8AndAsciiMetachar_259) {
  std::string input    = std::string(u8"é") + "+";
  std::string expected = std::string(u8"é") + "\\+";
  EXPECT_EQ(re_.QuoteMeta(input), expected);
}

// Whitespace behavior: spaces and tabs are escaped (ASCII, non-alnum, not underscore).
TEST_F(RE2_QuoteMetaTest_259, SpaceAndTabAreEscaped_259) {
  std::string input    = " \t_";
  // Space -> "\ ", tab -> "\t", underscore remains unchanged.
  std::string expected = "\\ \\\t_";
  EXPECT_EQ(re_.QuoteMeta(input), expected);
}

}  // namespace

// File: pcre_quotemeta_test_196.cc
#include "gtest/gtest.h"
#include "./TestProjects/re2/util/pcre.h"

#include <string>
#include <vector>

using re2::PCRE;

namespace {

// Helper: construct a PCRE instance only to access the (non-static) method
// exposed in the partial header. We do NOT rely on any internal state.
PCRE MakePCRE() {
  // Any valid pattern is fine; tests do not depend on matching behavior.
  return PCRE("");
}

// --- Normal operation ---

TEST(PCRE_QuoteMetaTest_196, ReturnsEmptyForEmptyInput_196) {
  auto re = MakePCRE();
  std::string input = "";
  EXPECT_EQ(re.QuoteMeta(input), "");
}

TEST(PCRE_QuoteMetaTest_196, LeavesAlnumAndUnderscoreUnchanged_196) {
  auto re = MakePCRE();
  std::string input = "abcXYZ_123";
  EXPECT_EQ(re.QuoteMeta(input), "abcXYZ_123");
}

TEST(PCRE_QuoteMetaTest_196, EscapesCommonRegexMetacharacters_196) {
  auto re = MakePCRE();
  // A set of typical regex ASCII metacharacters, plus '/' and backslash.
  std::string input = ".+*?^$()[]{}|/\\";
  // Expect every ASCII non-alnum, non-underscore char to be prefixed with '\'
  // and backslash itself to become "\\" in the output.
  std::string expected = "\\.\\+\\*\\?\\^\\$\\(\\)\\[\\]\\{\\}\\|\\/\\\\";
  EXPECT_EQ(re.QuoteMeta(input), expected);
}

TEST(PCRE_QuoteMetaTest_196, EscapesMixedStringWhereNeeded_196) {
  auto re = MakePCRE();
  std::string input = "a.c+1";
  std::string expected = "a\\.c\\+1";
  EXPECT_EQ(re.QuoteMeta(input), expected);
}

// --- Boundary / special bytes ---

TEST(PCRE_QuoteMetaTest_196, TreatsEmbeddedNullAsHexEscape_196) {
  auto re = MakePCRE();
  std::string input = "a";
  input.push_back('\0');  // embedded NUL
  input += "b";
  std::string expected = "a\\x00b";
  EXPECT_EQ(re.QuoteMeta(input), expected);
}

TEST(PCRE_QuoteMetaTest_196, HandlesLeadingNullByte_196) {
  auto re = MakePCRE();
  std::string input;
  input.push_back('\0');
  input += "a";
  std::string expected = "\\x00a";
  EXPECT_EQ(re.QuoteMeta(input), expected);
}

TEST(PCRE_QuoteMetaTest_196, HandlesTrailingNullByte_196) {
  auto re = MakePCRE();
  std::string input = "a";
  input.push_back('\0');
  std::string expected = "a\\x00";
  EXPECT_EQ(re.QuoteMeta(input), expected);
}

TEST(PCRE_QuoteMetaTest_196, EscapesBackslashItself_196) {
  auto re = MakePCRE();
  std::string input = "\\";
  std::string expected = "\\\\";
  EXPECT_EQ(re.QuoteMeta(input), expected);
}

// --- Non-ASCII bytes (should not be escaped) ---

TEST(PCRE_QuoteMetaTest_196, LeavesUTF8MultibyteBytesUnchanged_196) {
  auto re = MakePCRE();
  // "é" in UTF-8 (0xC3 0xA9) should pass through unchanged.
  std::string input = u8"é";
  EXPECT_EQ(re.QuoteMeta(input), input);
}

TEST(PCRE_QuoteMetaTest_196, LeavesKoreanUTF8UnchangedAndEscapesASCIIOnly_196) {
  auto re = MakePCRE();
  // "가" (UTF-8 3-byte) and a dot between letters
  std::string input = std::string(u8"가") + "." + std::string(u8"가");
  std::string expected = std::string(u8"가") + "\\." + std::string(u8"가");
  EXPECT_EQ(re.QuoteMeta(input), expected);
}

// --- Mixed edges ---

TEST(PCRE_QuoteMetaTest_196, EscapesFirstAndLastASCIIWhenNeeded_196) {
  auto re = MakePCRE();
  std::string input = ".middle?";
  std::string expected = "\\.middle\\?";
  EXPECT_EQ(re.QuoteMeta(input), expected);
}

}  // namespace

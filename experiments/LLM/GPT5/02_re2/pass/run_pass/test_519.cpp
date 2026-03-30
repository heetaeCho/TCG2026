// File: parse_escape_test_519.cc

#include "gtest/gtest.h"
#include "absl/strings/string_view.h"
#include "re2/regexp.h"
#include "util/utf.h"

// We include the implementation to access the internal-linkage (static) function for testing.
// This does not re-implement any logic; it only makes the tested interface visible here.
#include "re2/parse.cc"

namespace re2 {

class ParseEscapeTest_519 : public ::testing::Test {
 protected:
  static bool Call(absl::string_view* s, Rune* rp, RegexpStatus* status, int rune_max = Runemax) {
    return ParseEscape(s, rp, status, rune_max);
  }
};

// ---------- Success cases ----------

TEST_F(ParseEscapeTest_519, SimplePunctuation_BackslashDot_519) {
  absl::string_view s = R"(\.)";
  Rune r = -1;
  RegexpStatus st;
  ASSERT_TRUE(Call(&s, &r, &st));
  EXPECT_TRUE(st.ok());
  EXPECT_EQ(r, '.');
  EXPECT_TRUE(s.empty());  // fully consumed
}

TEST_F(ParseEscapeTest_519, NamedEscapes_CommonControls_519) {
  struct Case { const char* in; int expected; } cases[] = {
      {R"(\n)", '\n'}, {R"(\r)", '\r'}, {R"(\t)", '\t'},
      {R"(\a)", '\a'}, {R"(\f)", '\f'}, {R"(\v)", '\v'},
  };
  for (const auto& c : cases) {
    absl::string_view s(c.in);
    Rune r = -1;
    RegexpStatus st;
    SCOPED_TRACE(c.in);
    EXPECT_TRUE(Call(&s, &r, &st));
    EXPECT_TRUE(st.ok());
    EXPECT_EQ(r, c.expected);
    EXPECT_TRUE(s.empty());
  }
}

TEST_F(ParseEscapeTest_519, Octal_Zero_And_UpToThreeDigits_519) {
  { // "\0" -> 0
    absl::string_view s(R"(\0)");
    Rune r = -1;
    RegexpStatus st;
    EXPECT_TRUE(Call(&s, &r, &st));
    EXPECT_EQ(r, 0);
    EXPECT_TRUE(s.empty());
  }
  { // "\123" = 0123 (octal) = 83 decimal
    absl::string_view s(R"(\123)");
    Rune r = -1;
    RegexpStatus st;
    EXPECT_TRUE(Call(&s, &r, &st));
    EXPECT_EQ(r, 83);
    EXPECT_TRUE(s.empty());
  }
}

TEST_F(ParseEscapeTest_519, Hex_TwoDigits_519) {
  absl::string_view s(R"(\x41)");
  Rune r = -1;
  RegexpStatus st;
  ASSERT_TRUE(Call(&s, &r, &st));
  EXPECT_EQ(r, 'A');
  EXPECT_TRUE(s.empty());
}

TEST_F(ParseEscapeTest_519, HexBrace_UpperBound_Runemax_519) {
  // 0x10FFFF == Runemax
  absl::string_view s(R"(\x{10FFFF})");
  Rune r = -1;
  RegexpStatus st;
  ASSERT_TRUE(Call(&s, &r, &st));
  EXPECT_EQ(r, Runemax);
  EXPECT_TRUE(s.empty());
}

// ---------- Boundary / error cases ----------

TEST_F(ParseEscapeTest_519, InputDoesNotStartWithBackslash_InternalError_519) {
  absl::string_view s("n");  // no leading '\'
  Rune r = -1;
  RegexpStatus st;
  EXPECT_FALSE(Call(&s, &r, &st));
  EXPECT_EQ(st.code(), kRegexpInternalError);
  EXPECT_EQ(st.error_arg(), absl::string_view());  // empty error arg per interface
  EXPECT_EQ(s, "n");  // input not consumed
}

TEST_F(ParseEscapeTest_519, TrailingBackslash_TrailingBackslashError_519) {
  absl::string_view s("\\");  // size == 1
  Rune r = -1;
  RegexpStatus st;
  EXPECT_FALSE(Call(&s, &r, &st));
  EXPECT_EQ(st.code(), kRegexpTrailingBackslash);
  EXPECT_EQ(st.error_arg(), absl::string_view());  // empty per interface
  EXPECT_EQ(s, "\\");  // not consumed
}

TEST_F(ParseEscapeTest_519, Default_AlnumAfterBackslash_IsBadEscape_519) {
  absl::string_view s(R"(\q)");
  Rune r = -1;
  RegexpStatus st;
  EXPECT_FALSE(Call(&s, &r, &st));
  EXPECT_EQ(st.code(), kRegexpBadEscape);
  // Error arg should reflect exactly what was consumed: "\q"
  EXPECT_EQ(st.error_arg(), absl::string_view(R"(\q)"));
  EXPECT_TRUE(s.empty());  // backslash+q consumed
}

TEST_F(ParseEscapeTest_519, Octal_RequiresFollowingDigitAfter1to7_519) {
  absl::string_view s(R"(\1)");
  Rune r = -1;
  RegexpStatus st;
  EXPECT_FALSE(Call(&s, &r, &st));
  EXPECT_EQ(st.code(), kRegexpBadEscape);
  EXPECT_EQ(st.error_arg(), absl::string_view(R"(\1)"));  // only "\1" consumed
  EXPECT_TRUE(s.empty());
}

TEST_F(ParseEscapeTest_519, Octal_NonOctalNextDigitIsBadEscape_519) {
  absl::string_view s(R"(\18)");  // next char '8' is not octal
  Rune r = -1;
  RegexpStatus st;
  EXPECT_FALSE(Call(&s, &r, &st));
  EXPECT_EQ(st.code(), kRegexpBadEscape);
  EXPECT_EQ(st.error_arg(), absl::string_view(R"(\1)"));  // stops before '8'
  EXPECT_EQ(s, "8");  // '8' remains unconsumed
}

TEST_F(ParseEscapeTest_519, Octal_CodeExceedsRuneMax_IsBadEscape_519) {
  absl::string_view s(R"(\777)");  // 0o777 = 511
  Rune r = -1;
  RegexpStatus st;
  const int kSmallMax = 255;  // force overflow vs rune_max
  EXPECT_FALSE(Call(&s, &r, &st, kSmallMax));
  EXPECT_EQ(st.code(), kRegexpBadEscape);
  EXPECT_EQ(st.error_arg(), absl::string_view(R"(\777)"));
  EXPECT_TRUE(s.empty());
}

TEST_F(ParseEscapeTest_519, Hex_MissingDigitsAfterX_IsBadEscape_519) {
  absl::string_view s(R"(\x)");
  Rune r = -1;
  RegexpStatus st;
  EXPECT_FALSE(Call(&s, &r, &st));
  EXPECT_EQ(st.code(), kRegexpBadEscape);
  EXPECT_EQ(st.error_arg(), absl::string_view(R"(\x)"));
  EXPECT_TRUE(s.empty());
}

TEST_F(ParseEscapeTest_519, Hex_InvalidDigitPair_IsBadEscape_519) {
  absl::string_view s(R"(\xG1)");
  Rune r = -1;
  RegexpStatus st;
  EXPECT_FALSE(Call(&s, &r, &st));
  EXPECT_EQ(st.code(), kRegexpBadEscape);
  EXPECT_EQ(st.error_arg(), absl::string_view(R"(\xG1)"));
  EXPECT_TRUE(s.empty());
}

TEST_F(ParseEscapeTest_519, HexBrace_EmptyBetweenBraces_IsBadEscape_519) {
  absl::string_view s(R"(\x{})");
  Rune r = -1;
  RegexpStatus st;
  EXPECT_FALSE(Call(&s, &r, &st));
  EXPECT_EQ(st.code(), kRegexpBadEscape);
  EXPECT_EQ(st.error_arg(), absl::string_view(R"(\x{})"));
  EXPECT_TRUE(s.empty());
}

TEST_F(ParseEscapeTest_519, HexBrace_CodeExceedsRuneMax_IsBadEscape_519) {
  absl::string_view s(R"(\x{110000})");  // 0x110000 = Runemax+1
  Rune r = -1;
  RegexpStatus st;
  EXPECT_FALSE(Call(&s, &r, &st));
  EXPECT_EQ(st.code(), kRegexpBadEscape);
  // Error substring reflects consumed portion up to failure; exact value is implementation-defined.
  // We only assert that input advanced (consumed some) and not left entirely intact.
  EXPECT_NE(st.error_arg().size(), 0u);
  EXPECT_LT(s.size(), absl::string_view(R"(\x{110000})").size());
}

}  // namespace re2

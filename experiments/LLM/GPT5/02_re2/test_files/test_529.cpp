// File: parse_cccharacter_test_529.cc

#include <gtest/gtest.h>
#include <string>

#include "absl/strings/string_view.h"

// Pull in the tested method's definition.
#include "re2/parse.cc"
#include "re2/regexp.h"

using re2::RegexpStatus;
using re2::kRegexpMissingBracket;
using re2::Regexp;
using absl::string_view;

namespace {

TEST(RegexpParseStateTest_529, EmptyInputSetsStatusAndFails_529) {
  Regexp::ParseState ps;
  RegexpStatus st;
  string_view whole_class = "[abc]";
  string_view s = "";  // empty
  Rune r = 0;

  bool ok = ps.ParseCCCharacter(&s, &r, whole_class, &st);

  EXPECT_FALSE(ok);
  EXPECT_EQ(st.code(), kRegexpMissingBracket);
  EXPECT_EQ(st.error_arg(), whole_class);
  EXPECT_TRUE(s.empty());  // remains empty
}

TEST(RegexpParseStateTest_529, ParsesAsciiCharAndAdvancesInput_529) {
  Regexp::ParseState ps;
  RegexpStatus st;
  std::string backing = "aB";
  string_view s(backing);
  Rune r = 0;

  bool ok = ps.ParseCCCharacter(&s, &r, /*whole_class=*/"[aB]", &st);

  EXPECT_TRUE(ok);
  EXPECT_TRUE(st.ok());
  EXPECT_EQ(r, static_cast<Rune>('a'));
  EXPECT_EQ(s, string_view("B"));  // advanced by one character
}

TEST(RegexpParseStateTest_529, ParsesMultibyteUtf8RuneAndAdvances_529) {
  Regexp::ParseState ps;
  RegexpStatus st;
  // "é" (U+00E9) followed by 'x'
  std::string backing = "\xC3\xA9x";
  string_view s(backing);
  Rune r = 0;

  bool ok = ps.ParseCCCharacter(&s, &r, /*whole_class=*/"[éx]", &st);

  EXPECT_TRUE(ok);
  EXPECT_TRUE(st.ok());
  EXPECT_EQ(r, static_cast<Rune>(0x00E9));
  EXPECT_EQ(s, string_view("x"));  // consumed the multibyte rune only
}

TEST(RegexpParseStateTest_529, BackslashEscapeNewlineParsesAndAdvances_529) {
  Regexp::ParseState ps;
  RegexpStatus st;
  std::string backing = "\\nX";  // backslash + 'n' then 'X'
  string_view s(backing);
  Rune r = 0;

  bool ok = ps.ParseCCCharacter(&s, &r, /*whole_class=*/"[\\nX]", &st);

  // Observable expectations: succeeds, produces '\n', consumes escape sequence.
  EXPECT_TRUE(ok);
  EXPECT_TRUE(st.ok());
  EXPECT_EQ(r, static_cast<Rune>('\n'));
  EXPECT_EQ(s, string_view("X"));
}

TEST(RegexpParseStateTest_529, BackslashAloneReportsError_529) {
  Regexp::ParseState ps;
  RegexpStatus st;
  std::string backing = "\\";
  string_view s(backing);
  Rune r = 0;

  bool ok = ps.ParseCCCharacter(&s, &r, /*whole_class=*/"[\\]", &st);

  // Do not assume a specific error code from the escape parser; just that it fails.
  EXPECT_FALSE(ok);
  EXPECT_FALSE(st.ok());
}

TEST(RegexpParseStateTest_529, InvalidUtf8ReturnsFalseAndSetsError_529) {
  Regexp::ParseState ps;
  RegexpStatus st;
  // Lone continuation byte is invalid UTF-8.
  std::string backing = "\x80";
  string_view s(backing);
  Rune r = 0;

  bool ok = ps.ParseCCCharacter(&s, &r, /*whole_class=*/"[\\x80]", &st);

  EXPECT_FALSE(ok);
  EXPECT_FALSE(st.ok());  // status should indicate an error condition
}

}  // namespace

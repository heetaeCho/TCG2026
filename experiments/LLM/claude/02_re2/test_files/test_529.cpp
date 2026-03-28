#include "gtest/gtest.h"
#include "re2/regexp.h"
#include "re2/re2.h"
#include "absl/strings/string_view.h"

namespace re2 {

// We need to access ParseState which is a nested class inside Regexp.
// Based on the interface, we'll test ParseCCCharacter through ParseState.

class ParseCCCharacterTest_529 : public ::testing::Test {
 protected:
  void SetUp() override {
    status_ = new RegexpStatus();
  }

  void TearDown() override {
    delete status_;
    if (ps_) {
      delete ps_;
    }
  }

  Regexp::ParseState* CreateParseState(Regexp::ParseFlags flags = Regexp::LikePerl) {
    absl::string_view whole("test");
    ps_ = new Regexp::ParseState(flags, whole, status_);
    return ps_;
  }

  RegexpStatus* status_ = nullptr;
  Regexp::ParseState* ps_ = nullptr;
};

// Test: Empty string should return false and set kRegexpMissingBracket
TEST_F(ParseCCCharacterTest_529, EmptyStringReturnsFalse_529) {
  auto* ps = CreateParseState();
  absl::string_view s("");
  Rune r = 0;
  absl::string_view whole_class("[abc]");
  RegexpStatus local_status;

  bool result = ps->ParseCCCharacter(&s, &r, whole_class, &local_status);

  EXPECT_FALSE(result);
  EXPECT_EQ(local_status.code(), kRegexpMissingBracket);
  EXPECT_EQ(local_status.error_arg(), whole_class);
}

// Test: Simple ASCII character 'a'
TEST_F(ParseCCCharacterTest_529, SimpleAsciiCharacter_529) {
  auto* ps = CreateParseState();
  absl::string_view s("abc");
  Rune r = 0;
  absl::string_view whole_class("[abc]");
  RegexpStatus local_status;

  bool result = ps->ParseCCCharacter(&s, &r, whole_class, &local_status);

  EXPECT_TRUE(result);
  EXPECT_EQ(r, 'a');
  // The string_view should have been advanced past the first character
  EXPECT_EQ(s, "bc");
}

// Test: Single character string
TEST_F(ParseCCCharacterTest_529, SingleCharacterString_529) {
  auto* ps = CreateParseState();
  absl::string_view s("x");
  Rune r = 0;
  absl::string_view whole_class("[x]");
  RegexpStatus local_status;

  bool result = ps->ParseCCCharacter(&s, &r, whole_class, &local_status);

  EXPECT_TRUE(result);
  EXPECT_EQ(r, 'x');
  EXPECT_TRUE(s.empty());
}

// Test: Backslash escape sequence - \n (newline)
TEST_F(ParseCCCharacterTest_529, BackslashEscapeNewline_529) {
  auto* ps = CreateParseState();
  absl::string_view s("\\n");
  Rune r = 0;
  absl::string_view whole_class("[\\n]");
  RegexpStatus local_status;

  bool result = ps->ParseCCCharacter(&s, &r, whole_class, &local_status);

  EXPECT_TRUE(result);
  EXPECT_EQ(r, '\n');
  EXPECT_TRUE(s.empty());
}

// Test: Backslash escape sequence - \t (tab)
TEST_F(ParseCCCharacterTest_529, BackslashEscapeTab_529) {
  auto* ps = CreateParseState();
  absl::string_view s("\\t");
  Rune r = 0;
  absl::string_view whole_class("[\\t]");
  RegexpStatus local_status;

  bool result = ps->ParseCCCharacter(&s, &r, whole_class, &local_status);

  EXPECT_TRUE(result);
  EXPECT_EQ(r, '\t');
  EXPECT_TRUE(s.empty());
}

// Test: Digit character
TEST_F(ParseCCCharacterTest_529, DigitCharacter_529) {
  auto* ps = CreateParseState();
  absl::string_view s("0");
  Rune r = 0;
  absl::string_view whole_class("[0-9]");
  RegexpStatus local_status;

  bool result = ps->ParseCCCharacter(&s, &r, whole_class, &local_status);

  EXPECT_TRUE(result);
  EXPECT_EQ(r, '0');
}

// Test: Hyphen character (not an escape)
TEST_F(ParseCCCharacterTest_529, HyphenCharacter_529) {
  auto* ps = CreateParseState();
  absl::string_view s("-");
  Rune r = 0;
  absl::string_view whole_class("[-]");
  RegexpStatus local_status;

  bool result = ps->ParseCCCharacter(&s, &r, whole_class, &local_status);

  EXPECT_TRUE(result);
  EXPECT_EQ(r, '-');
}

// Test: Closing bracket character
TEST_F(ParseCCCharacterTest_529, ClosingBracketCharacter_529) {
  auto* ps = CreateParseState();
  absl::string_view s("]");
  Rune r = 0;
  absl::string_view whole_class("[]]");
  RegexpStatus local_status;

  bool result = ps->ParseCCCharacter(&s, &r, whole_class, &local_status);

  EXPECT_TRUE(result);
  EXPECT_EQ(r, ']');
}

// Test: Backslash at end of string (trailing backslash)
TEST_F(ParseCCCharacterTest_529, TrailingBackslash_529) {
  auto* ps = CreateParseState();
  absl::string_view s("\\");
  Rune r = 0;
  absl::string_view whole_class("[\\]");
  RegexpStatus local_status;

  bool result = ps->ParseCCCharacter(&s, &r, whole_class, &local_status);

  // ParseEscape should fail with trailing backslash
  EXPECT_FALSE(result);
  EXPECT_EQ(local_status.code(), kRegexpTrailingBackslash);
}

// Test: Multi-byte UTF-8 character
TEST_F(ParseCCCharacterTest_529, MultiBytUtf8Character_529) {
  auto* ps = CreateParseState();
  // UTF-8 for é (U+00E9): 0xC3 0xA9
  absl::string_view s("\xC3\xA9");
  Rune r = 0;
  absl::string_view whole_class("[é]");
  RegexpStatus local_status;

  bool result = ps->ParseCCCharacter(&s, &r, whole_class, &local_status);

  EXPECT_TRUE(result);
  EXPECT_EQ(r, 0x00E9);
  EXPECT_TRUE(s.empty());
}

// Test: Hex escape \x41 for 'A'
TEST_F(ParseCCCharacterTest_529, HexEscape_529) {
  auto* ps = CreateParseState();
  absl::string_view s("\\x41rest");
  Rune r = 0;
  absl::string_view whole_class("[\\x41]");
  RegexpStatus local_status;

  bool result = ps->ParseCCCharacter(&s, &r, whole_class, &local_status);

  EXPECT_TRUE(result);
  EXPECT_EQ(r, 'A');
}

// Test: Multiple characters - only first should be consumed
TEST_F(ParseCCCharacterTest_529, OnlyFirstCharacterConsumed_529) {
  auto* ps = CreateParseState();
  absl::string_view s("xyz");
  Rune r = 0;
  absl::string_view whole_class("[xyz]");
  RegexpStatus local_status;

  bool result = ps->ParseCCCharacter(&s, &r, whole_class, &local_status);

  EXPECT_TRUE(result);
  EXPECT_EQ(r, 'x');
  EXPECT_EQ(s.size(), 2u);
  EXPECT_EQ(s, "yz");
}

// Test: Escaped backslash \\  
TEST_F(ParseCCCharacterTest_529, EscapedBackslash_529) {
  auto* ps = CreateParseState();
  absl::string_view s("\\\\");
  Rune r = 0;
  absl::string_view whole_class("[\\\\]");
  RegexpStatus local_status;

  bool result = ps->ParseCCCharacter(&s, &r, whole_class, &local_status);

  EXPECT_TRUE(result);
  EXPECT_EQ(r, '\\');
}

// Test: Space character
TEST_F(ParseCCCharacterTest_529, SpaceCharacter_529) {
  auto* ps = CreateParseState();
  absl::string_view s(" ");
  Rune r = 0;
  absl::string_view whole_class("[ ]");
  RegexpStatus local_status;

  bool result = ps->ParseCCCharacter(&s, &r, whole_class, &local_status);

  EXPECT_TRUE(result);
  EXPECT_EQ(r, ' ');
}

// Test: Whole class is correctly stored in error on empty input
TEST_F(ParseCCCharacterTest_529, ErrorArgMatchesWholeClass_529) {
  auto* ps = CreateParseState();
  absl::string_view s("");
  Rune r = 0;
  absl::string_view whole_class("[some-complex-class]");
  RegexpStatus local_status;

  bool result = ps->ParseCCCharacter(&s, &r, whole_class, &local_status);

  EXPECT_FALSE(result);
  EXPECT_EQ(local_status.code(), kRegexpMissingBracket);
  EXPECT_EQ(local_status.error_arg(), whole_class);
}

// Test: ParseCCCharacter with Latin parse flags (restricting rune_max)
TEST_F(ParseCCCharacterTest_529, LatinFlagsSimpleCharacter_529) {
  // Using Latin1 flag to restrict rune_max to 0xFF
  status_ = new RegexpStatus();
  absl::string_view whole("test");
  // Regexp::Latin1 is a flag that sets rune_max_ = 0xFF
  ps_ = new Regexp::ParseState(Regexp::Latin1, whole, status_);

  absl::string_view s("A");
  Rune r = 0;
  absl::string_view whole_class("[A]");
  RegexpStatus local_status;

  bool result = ps_->ParseCCCharacter(&s, &r, whole_class, &local_status);

  EXPECT_TRUE(result);
  EXPECT_EQ(r, 'A');

  // Clean up (TearDown handles ps_ and status_)
  // But we overwrote status_, so we need to clean the old one
  // Actually SetUp already created status_, and we created a new one here.
  // Let's just let TearDown handle it.
}

// Test: Consecutive calls consume characters one by one
TEST_F(ParseCCCharacterTest_529, ConsecutiveCallsConsumeSequentially_529) {
  auto* ps = CreateParseState();
  absl::string_view s("ab");
  Rune r1 = 0, r2 = 0;
  absl::string_view whole_class("[ab]");
  RegexpStatus local_status;

  bool result1 = ps->ParseCCCharacter(&s, &r1, whole_class, &local_status);
  EXPECT_TRUE(result1);
  EXPECT_EQ(r1, 'a');
  EXPECT_EQ(s, "b");

  bool result2 = ps->ParseCCCharacter(&s, &r2, whole_class, &local_status);
  EXPECT_TRUE(result2);
  EXPECT_EQ(r2, 'b');
  EXPECT_TRUE(s.empty());
}

}  // namespace re2

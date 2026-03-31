#include "gtest/gtest.h"
#include "re2/regexp.h"
#include "re2/re2.h"
#include <string>

namespace re2 {

// Test PushDot through the Parse interface, since ParseState is not directly
// accessible from outside. We can observe PushDot behavior by parsing "."
// with different flag combinations and examining the resulting regexp.

class PushDotTest_493 : public ::testing::Test {
 protected:
  void TearDown() override {}
};

// Test: PushDot with default flags (no DotNL, no NeverNL) should produce a
// character class that matches everything except \n
TEST_F(PushDotTest_493, DotWithoutDotNL_ProducesCharClass_493) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(".", Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);
  // The dot without DotNL should be a character class (not kRegexpAnyChar)
  EXPECT_EQ(re->op(), kRegexpCharClass);
  // Verify it doesn't match \n
  CharClass* cc = re->cc();
  ASSERT_NE(cc, nullptr);
  EXPECT_FALSE(cc->Contains('\n'));
  // Verify it matches other characters
  EXPECT_TRUE(cc->Contains('a'));
  EXPECT_TRUE(cc->Contains('Z'));
  EXPECT_TRUE(cc->Contains(' '));
  EXPECT_TRUE(cc->Contains(0));
  re->Decref();
}

// Test: PushDot with DotNL flag should produce kRegexpAnyChar
TEST_F(PushDotTest_493, DotWithDotNL_ProducesAnyChar_493) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(".", Regexp::DotNL, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpAnyChar);
  re->Decref();
}

// Test: PushDot with both DotNL and NeverNL should NOT produce kRegexpAnyChar
// Instead it should produce a character class (excluding \n)
TEST_F(PushDotTest_493, DotWithDotNLAndNeverNL_ProducesCharClass_493) {
  RegexpStatus status;
  Regexp::ParseFlags flags = static_cast<Regexp::ParseFlags>(
      Regexp::DotNL | Regexp::NeverNL);
  Regexp* re = Regexp::Parse(".", flags, &status);
  ASSERT_NE(re, nullptr);
  // With NeverNL, even DotNL should result in a char class
  EXPECT_EQ(re->op(), kRegexpCharClass);
  CharClass* cc = re->cc();
  ASSERT_NE(cc, nullptr);
  EXPECT_FALSE(cc->Contains('\n'));
  re->Decref();
}

// Test: PushDot with NeverNL but without DotNL should produce char class
TEST_F(PushDotTest_493, DotWithNeverNLOnly_ProducesCharClass_493) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(".", Regexp::NeverNL, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpCharClass);
  CharClass* cc = re->cc();
  ASSERT_NE(cc, nullptr);
  EXPECT_FALSE(cc->Contains('\n'));
  EXPECT_TRUE(cc->Contains('a'));
  re->Decref();
}

// Test: Multiple dots in a pattern
TEST_F(PushDotTest_493, MultipleDots_ProducesConcat_493) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("..", Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpConcat);
  EXPECT_EQ(re->nsub(), 2);
  // Each sub should be a char class
  Regexp** subs = re->sub();
  EXPECT_EQ(subs[0]->op(), kRegexpCharClass);
  EXPECT_EQ(subs[1]->op(), kRegexpCharClass);
  re->Decref();
}

// Test: Dot with DotNL in a concatenation
TEST_F(PushDotTest_493, MultipleDotsWithDotNL_ProducesAnyChars_493) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("..", Regexp::DotNL, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpConcat);
  EXPECT_EQ(re->nsub(), 2);
  Regexp** subs = re->sub();
  EXPECT_EQ(subs[0]->op(), kRegexpAnyChar);
  EXPECT_EQ(subs[1]->op(), kRegexpAnyChar);
  re->Decref();
}

// Test: Dot character class should contain 0 (null byte)
TEST_F(PushDotTest_493, DotCharClassContainsNullByte_493) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(".", Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpCharClass);
  CharClass* cc = re->cc();
  ASSERT_NE(cc, nullptr);
  EXPECT_TRUE(cc->Contains(0));
  re->Decref();
}

// Test: Dot character class should contain characters adjacent to \n
TEST_F(PushDotTest_493, DotCharClassContainsAdjacentToNewline_493) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(".", Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpCharClass);
  CharClass* cc = re->cc();
  ASSERT_NE(cc, nullptr);
  // '\n' is 10, so 9 and 11 should be included
  EXPECT_TRUE(cc->Contains('\n' - 1));  // 9
  EXPECT_TRUE(cc->Contains('\n' + 1));  // 11
  EXPECT_FALSE(cc->Contains('\n'));      // 10
  re->Decref();
}

// Test: Dot with LikePerl flags (which includes DotNL? No, LikePerl doesn't include DotNL)
TEST_F(PushDotTest_493, DotWithLikePerlFlags_493) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(".", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  // LikePerl = 1940, which doesn't include DotNL (8)
  // So it should be a char class
  EXPECT_EQ(re->op(), kRegexpCharClass);
  re->Decref();
}

// Test: Dot with FoldCase should produce char class without FoldCase flag
// (PushDot strips FoldCase from the char class)
TEST_F(PushDotTest_493, DotWithFoldCase_ProducesCharClassWithoutFoldCase_493) {
  RegexpStatus status;
  Regexp::ParseFlags flags = static_cast<Regexp::ParseFlags>(
      Regexp::FoldCase | Regexp::PerlX | Regexp::PerlClasses | Regexp::PerlB);
  Regexp* re = Regexp::Parse(".", flags, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpCharClass);
  // The parse_flags on the regexp should not include FoldCase
  EXPECT_EQ(re->parse_flags() & Regexp::FoldCase, 0);
  re->Decref();
}

// Test: Dot with DotNL and FoldCase should produce AnyChar
TEST_F(PushDotTest_493, DotWithDotNLAndFoldCase_ProducesAnyChar_493) {
  RegexpStatus status;
  Regexp::ParseFlags flags = static_cast<Regexp::ParseFlags>(
      Regexp::DotNL | Regexp::FoldCase);
  Regexp* re = Regexp::Parse(".", flags, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpAnyChar);
  re->Decref();
}

// Test: ToString round-trip for dot
TEST_F(PushDotTest_493, DotToString_493) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(".", Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  // The ToString should produce something that represents "any char except newline"
  // This is typically represented as a character class or dot
  EXPECT_FALSE(s.empty());
  re->Decref();
}

// Test: Dot star pattern
TEST_F(PushDotTest_493, DotStar_493) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(".*", Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpStar);
  EXPECT_EQ(re->nsub(), 1);
  Regexp** subs = re->sub();
  EXPECT_EQ(subs[0]->op(), kRegexpCharClass);
  re->Decref();
}

// Test: Dot star with DotNL
TEST_F(PushDotTest_493, DotStarWithDotNL_493) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(".*", Regexp::DotNL, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpStar);
  EXPECT_EQ(re->nsub(), 1);
  Regexp** subs = re->sub();
  EXPECT_EQ(subs[0]->op(), kRegexpAnyChar);
  re->Decref();
}

// Test: Dot in Latin1 mode (rune_max_ should be 255)
TEST_F(PushDotTest_493, DotInLatin1Mode_493) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(".", Regexp::Latin1, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpCharClass);
  CharClass* cc = re->cc();
  ASSERT_NE(cc, nullptr);
  // In Latin1 mode, characters above 255 should not be in the class
  EXPECT_TRUE(cc->Contains(255));
  EXPECT_FALSE(cc->Contains(256));
  EXPECT_FALSE(cc->Contains('\n'));
  re->Decref();
}

// Test: Dot in Latin1 mode with DotNL
TEST_F(PushDotTest_493, DotInLatin1ModeWithDotNL_493) {
  RegexpStatus status;
  Regexp::ParseFlags flags = static_cast<Regexp::ParseFlags>(
      Regexp::Latin1 | Regexp::DotNL);
  Regexp* re = Regexp::Parse(".", flags, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpAnyChar);
  re->Decref();
}

// Test: Single dot should compile and work in full RE2
TEST_F(PushDotTest_493, DotMatchesFunctionally_493) {
  RE2 pattern(".", RE2::Quiet);
  ASSERT_TRUE(pattern.ok());
  EXPECT_TRUE(RE2::FullMatch("a", pattern));
  EXPECT_TRUE(RE2::FullMatch("Z", pattern));
  EXPECT_TRUE(RE2::FullMatch("0", pattern));
  EXPECT_FALSE(RE2::FullMatch("\n", pattern));
  EXPECT_FALSE(RE2::FullMatch("", pattern));
  EXPECT_FALSE(RE2::FullMatch("ab", pattern));
}

// Test: Dot with DotNL flag matches newline in RE2
TEST_F(PushDotTest_493, DotNLMatchesNewline_493) {
  RE2::Options opts;
  opts.set_dot_nl(true);
  RE2 pattern(".", opts);
  ASSERT_TRUE(pattern.ok());
  EXPECT_TRUE(RE2::FullMatch("\n", pattern));
  EXPECT_TRUE(RE2::FullMatch("a", pattern));
}

}  // namespace re2

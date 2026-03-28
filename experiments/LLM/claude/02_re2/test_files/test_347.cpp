#include "gtest/gtest.h"
#include "re2/regexp.h"
#include "re2/re2.h"
#include "util/utf.h"

namespace re2 {

// Helper to get default parse flags
static const Regexp::ParseFlags kTestFlags = Regexp::LikePerl;

class RegexpLiteralStringTest_347 : public ::testing::Test {
 protected:
  void TearDown() override {
    // Cleanup is handled by Decref
  }
};

// Test: LiteralString with nrunes <= 0 should return an EmptyMatch regexp
TEST_F(RegexpLiteralStringTest_347, ZeroRunesReturnsEmptyMatch_347) {
  Rune runes[] = {'a', 'b', 'c'};
  Regexp* re = Regexp::LiteralString(runes, 0, kTestFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpEmptyMatch);
  re->Decref();
}

// Test: LiteralString with negative nrunes should return an EmptyMatch regexp
TEST_F(RegexpLiteralStringTest_347, NegativeRunesReturnsEmptyMatch_347) {
  Rune runes[] = {'x'};
  Regexp* re = Regexp::LiteralString(runes, -1, kTestFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpEmptyMatch);
  re->Decref();
}

// Test: LiteralString with exactly 1 rune should return a Literal regexp
TEST_F(RegexpLiteralStringTest_347, SingleRuneReturnsLiteral_347) {
  Rune runes[] = {'z'};
  Regexp* re = Regexp::LiteralString(runes, 1, kTestFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteral);
  EXPECT_EQ(re->rune(), 'z');
  re->Decref();
}

// Test: LiteralString with multiple runes should return a LiteralString regexp
TEST_F(RegexpLiteralStringTest_347, MultipleRunesReturnsLiteralString_347) {
  Rune runes[] = {'h', 'e', 'l', 'l', 'o'};
  Regexp* re = Regexp::LiteralString(runes, 5, kTestFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteralString);
  EXPECT_EQ(re->nrunes(), 5);
  re->Decref();
}

// Test: LiteralString with 2 runes should return LiteralString (not Literal)
TEST_F(RegexpLiteralStringTest_347, TwoRunesReturnsLiteralString_347) {
  Rune runes[] = {'a', 'b'};
  Regexp* re = Regexp::LiteralString(runes, 2, kTestFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteralString);
  EXPECT_EQ(re->nrunes(), 2);
  re->Decref();
}

// Test: LiteralString preserves the runes correctly
TEST_F(RegexpLiteralStringTest_347, RunesArePreserved_347) {
  Rune runes[] = {'a', 'b', 'c'};
  Regexp* re = Regexp::LiteralString(runes, 3, kTestFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteralString);
  EXPECT_EQ(re->nrunes(), 3);
  Rune* stored = re->runes();
  ASSERT_NE(stored, nullptr);
  EXPECT_EQ(stored[0], 'a');
  EXPECT_EQ(stored[1], 'b');
  EXPECT_EQ(stored[2], 'c');
  re->Decref();
}

// Test: LiteralString with Unicode runes
TEST_F(RegexpLiteralStringTest_347, UnicodeRunesPreserved_347) {
  Rune runes[] = {0x4e16, 0x754c};  // 世界
  Regexp* re = Regexp::LiteralString(runes, 2, kTestFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteralString);
  EXPECT_EQ(re->nrunes(), 2);
  Rune* stored = re->runes();
  ASSERT_NE(stored, nullptr);
  EXPECT_EQ(stored[0], 0x4e16);
  EXPECT_EQ(stored[1], 0x754c);
  re->Decref();
}

// Test: LiteralString single rune preserves parse flags
TEST_F(RegexpLiteralStringTest_347, SingleRunePreservesFlags_347) {
  Rune runes[] = {'A'};
  Regexp::ParseFlags flags = Regexp::FoldCase;
  Regexp* re = Regexp::LiteralString(runes, 1, flags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteral);
  // Check that FoldCase flag is present
  EXPECT_TRUE(re->parse_flags() & Regexp::FoldCase);
  re->Decref();
}

// Test: LiteralString multiple runes preserves parse flags
TEST_F(RegexpLiteralStringTest_347, MultipleRunesPreservesFlags_347) {
  Rune runes[] = {'A', 'B', 'C'};
  Regexp::ParseFlags flags = Regexp::FoldCase;
  Regexp* re = Regexp::LiteralString(runes, 3, flags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteralString);
  EXPECT_TRUE(re->parse_flags() & Regexp::FoldCase);
  re->Decref();
}

// Test: Reference count starts at 1 for the returned regexp
TEST_F(RegexpLiteralStringTest_347, RefCountIsOne_347) {
  Rune runes[] = {'x', 'y'};
  Regexp* re = Regexp::LiteralString(runes, 2, kTestFlags);
  ASSERT_NE(re, nullptr);
  // A freshly created Regexp should have ref count 1
  // We can verify indirectly: Incref should succeed, then we need two Decrefs
  EXPECT_EQ(re->Ref(), 1);
  re->Decref();
}

// Test: LiteralString with nrunes = 0 and nullptr runes pointer
TEST_F(RegexpLiteralStringTest_347, ZeroRunesNullPointer_347) {
  Regexp* re = Regexp::LiteralString(nullptr, 0, kTestFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpEmptyMatch);
  re->Decref();
}

// Test: ToString of LiteralString returns the expected string
TEST_F(RegexpLiteralStringTest_347, ToStringMultipleRunes_347) {
  Rune runes[] = {'a', 'b', 'c'};
  Regexp* re = Regexp::LiteralString(runes, 3, kTestFlags);
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  EXPECT_EQ(s, "abc");
  re->Decref();
}

// Test: Dump of single rune literal
TEST_F(RegexpLiteralStringTest_347, DumpSingleRune_347) {
  Rune runes[] = {'a'};
  Regexp* re = Regexp::LiteralString(runes, 1, kTestFlags);
  ASSERT_NE(re, nullptr);
  std::string d = re->Dump();
  // Dump of a literal 'a' should contain 'a' somehow
  EXPECT_FALSE(d.empty());
  re->Decref();
}

// Test: Dump of LiteralString with multiple runes
TEST_F(RegexpLiteralStringTest_347, DumpMultipleRunes_347) {
  Rune runes[] = {'h', 'i'};
  Regexp* re = Regexp::LiteralString(runes, 2, kTestFlags);
  ASSERT_NE(re, nullptr);
  std::string d = re->Dump();
  EXPECT_FALSE(d.empty());
  re->Decref();
}

// Additional broader tests for other Regexp static methods for completeness

class RegexpGeneralTest_347 : public ::testing::Test {};

// Test: NewLiteral creates a Literal regexp
TEST_F(RegexpGeneralTest_347, NewLiteralCreatesLiteral_347) {
  Regexp* re = Regexp::NewLiteral('x', kTestFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteral);
  EXPECT_EQ(re->rune(), 'x');
  re->Decref();
}

// Test: HaveMatch creates a HaveMatch regexp
TEST_F(RegexpGeneralTest_347, HaveMatchCreatesHaveMatch_347) {
  Regexp* re = Regexp::HaveMatch(42, kTestFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpHaveMatch);
  EXPECT_EQ(re->match_id(), 42);
  re->Decref();
}

// Test: Star wraps a sub in a Star
TEST_F(RegexpGeneralTest_347, StarCreatesStar_347) {
  Regexp* sub = Regexp::NewLiteral('a', kTestFlags);
  Regexp* re = Regexp::Star(sub, kTestFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpStar);
  re->Decref();
}

// Test: Plus wraps a sub in a Plus
TEST_F(RegexpGeneralTest_347, PlusCreatesPlus_347) {
  Regexp* sub = Regexp::NewLiteral('b', kTestFlags);
  Regexp* re = Regexp::Plus(sub, kTestFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpPlus);
  re->Decref();
}

// Test: Quest wraps a sub in a Quest
TEST_F(RegexpGeneralTest_347, QuestCreatesQuest_347) {
  Regexp* sub = Regexp::NewLiteral('c', kTestFlags);
  Regexp* re = Regexp::Quest(sub, kTestFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpQuest);
  re->Decref();
}

// Test: Capture wraps a sub in a Capture
TEST_F(RegexpGeneralTest_347, CaptureCreatesCapture_347) {
  Regexp* sub = Regexp::NewLiteral('d', kTestFlags);
  Regexp* re = Regexp::Capture(sub, kTestFlags, 1);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpCapture);
  EXPECT_EQ(re->cap(), 1);
  re->Decref();
}

// Test: Parse a simple regexp
TEST_F(RegexpGeneralTest_347, ParseSimpleRegexp_347) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", kTestFlags, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// Test: Parse empty string
TEST_F(RegexpGeneralTest_347, ParseEmptyString_347) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("", kTestFlags, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpEmptyMatch);
  re->Decref();
}

// Test: Parse invalid regexp returns error
TEST_F(RegexpGeneralTest_347, ParseInvalidRegexp_347) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(", kTestFlags, &status);
  EXPECT_EQ(re, nullptr);
  EXPECT_FALSE(status.ok());
}

// Test: Concat with zero subs
TEST_F(RegexpGeneralTest_347, ConcatZeroSubs_347) {
  Regexp* re = Regexp::Concat(nullptr, 0, kTestFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpEmptyMatch);
  re->Decref();
}

// Test: Concat with one sub returns that sub
TEST_F(RegexpGeneralTest_347, ConcatOneSub_347) {
  Regexp* sub = Regexp::NewLiteral('a', kTestFlags);
  Regexp* subs[] = {sub};
  Regexp* re = Regexp::Concat(subs, 1, kTestFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteral);
  re->Decref();
}

// Test: Alternate with zero subs
TEST_F(RegexpGeneralTest_347, AlternateZeroSubs_347) {
  Regexp* re = Regexp::Alternate(nullptr, 0, kTestFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpNoMatch);
  re->Decref();
}

// Test: Repeat creates a Repeat regexp
TEST_F(RegexpGeneralTest_347, RepeatCreatesRepeat_347) {
  Regexp* sub = Regexp::NewLiteral('e', kTestFlags);
  Regexp* re = Regexp::Repeat(sub, kTestFlags, 2, 5);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpRepeat);
  EXPECT_EQ(re->min(), 2);
  EXPECT_EQ(re->max(), 5);
  re->Decref();
}

// Test: SimplifyRegexp
TEST_F(RegexpGeneralTest_347, SimplifyRegexpBasic_347) {
  RegexpStatus status;
  std::string dst;
  bool ok = Regexp::SimplifyRegexp("a+", kTestFlags, &dst, &status);
  EXPECT_TRUE(ok);
  EXPECT_FALSE(dst.empty());
}

// Test: Incref / Decref
TEST_F(RegexpGeneralTest_347, IncrefDecref_347) {
  Regexp* re = Regexp::NewLiteral('f', kTestFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->Ref(), 1);
  Regexp* re2 = re->Incref();
  EXPECT_EQ(re, re2);
  EXPECT_EQ(re->Ref(), 2);
  re->Decref();
  EXPECT_EQ(re->Ref(), 1);
  re->Decref();
}

// Test: NumCaptures on non-capturing regexp
TEST_F(RegexpGeneralTest_347, NumCapturesNone_347) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", kTestFlags, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 0);
  re->Decref();
}

// Test: NumCaptures with captures
TEST_F(RegexpGeneralTest_347, NumCapturesWithGroups_347) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a)(b)(c)", kTestFlags, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 3);
  re->Decref();
}

}  // namespace re2

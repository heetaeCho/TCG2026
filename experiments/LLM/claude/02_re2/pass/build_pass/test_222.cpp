#include "gtest/gtest.h"
#include "re2/regexp.h"
#include "re2/re2.h"

namespace re2 {

// We test the EmptyStringWalker indirectly through Regexp::MimicsPCRE()
// and by constructing various Regexp patterns and observing behavior.
// However, the most direct way to test the EmptyStringWalker's PostVisit
// logic is through parsing regexps and checking MimicsPCRE behavior,
// or by constructing Regexp objects directly.

// Since EmptyStringWalker is used internally, we test it through the
// public interface of Regexp, specifically through patterns that exercise
// the various op cases in PostVisit.

class EmptyStringWalkerTest_222 : public ::testing::Test {
 protected:
  void TearDown() override {}
};

// Helper: Parse a regex and check if it mimics PCRE
static bool ParseAndMimicsPCRE(const char* pattern) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(pattern, 
      static_cast<Regexp::ParseFlags>(Regexp::LikePerl), &status);
  if (re == nullptr) return false;
  bool result = re->MimicsPCRE();
  re->Decref();
  return result;
}

// Test: Simple literal - should mimic PCRE
TEST_F(EmptyStringWalkerTest_222, LiteralMimicsPCRE_222) {
  EXPECT_TRUE(ParseAndMimicsPCRE("a"));
}

// Test: Empty match pattern
TEST_F(EmptyStringWalkerTest_222, EmptyPatternMimicsPCRE_222) {
  EXPECT_TRUE(ParseAndMimicsPCRE(""));
}

// Test: Star quantifier (can always be empty)
TEST_F(EmptyStringWalkerTest_222, StarMimicsPCRE_222) {
  EXPECT_TRUE(ParseAndMimicsPCRE("a*"));
}

// Test: Plus quantifier 
TEST_F(EmptyStringWalkerTest_222, PlusMimicsPCRE_222) {
  EXPECT_TRUE(ParseAndMimicsPCRE("a+"));
}

// Test: Quest quantifier (can always be empty)
TEST_F(EmptyStringWalkerTest_222, QuestMimicsPCRE_222) {
  EXPECT_TRUE(ParseAndMimicsPCRE("a?"));
}

// Test: Concatenation of always-empty elements
TEST_F(EmptyStringWalkerTest_222, ConcatEmptyElementsMimicsPCRE_222) {
  EXPECT_TRUE(ParseAndMimicsPCRE("^$"));
}

// Test: Alternation where one branch can be empty
TEST_F(EmptyStringWalkerTest_222, AlternateWithEmptyBranch_222) {
  EXPECT_TRUE(ParseAndMimicsPCRE("a|"));
}

// Test: Capture group
TEST_F(EmptyStringWalkerTest_222, CaptureGroupMimicsPCRE_222) {
  EXPECT_TRUE(ParseAndMimicsPCRE("(a)"));
}

// Test: Capture group with empty content
TEST_F(EmptyStringWalkerTest_222, CaptureGroupEmptyContent_222) {
  EXPECT_TRUE(ParseAndMimicsPCRE("()"));
}

// Test: Begin/End line anchors
TEST_F(EmptyStringWalkerTest_222, AnchorsBeginEndLine_222) {
  EXPECT_TRUE(ParseAndMimicsPCRE("^"));
  EXPECT_TRUE(ParseAndMimicsPCRE("$"));
}

// Test: Begin/End text anchors
TEST_F(EmptyStringWalkerTest_222, AnchorsBeginEndText_222) {
  EXPECT_TRUE(ParseAndMimicsPCRE("\\A"));
  EXPECT_TRUE(ParseAndMimicsPCRE("\\z"));
}

// Test: Word boundary
TEST_F(EmptyStringWalkerTest_222, WordBoundary_222) {
  EXPECT_TRUE(ParseAndMimicsPCRE("\\b"));
}

// Test: Any char (dot)
TEST_F(EmptyStringWalkerTest_222, AnyCharMimicsPCRE_222) {
  EXPECT_TRUE(ParseAndMimicsPCRE("."));
}

// Test: Character class
TEST_F(EmptyStringWalkerTest_222, CharClassMimicsPCRE_222) {
  EXPECT_TRUE(ParseAndMimicsPCRE("[abc]"));
}

// Test: Repeat with min=0 (can be empty)
TEST_F(EmptyStringWalkerTest_222, RepeatMinZero_222) {
  EXPECT_TRUE(ParseAndMimicsPCRE("a{0,3}"));
}

// Test: Repeat with min>0 and non-empty child
TEST_F(EmptyStringWalkerTest_222, RepeatMinPositive_222) {
  EXPECT_TRUE(ParseAndMimicsPCRE("a{2,3}"));
}

// Test: Repeat with min=0 max=0
TEST_F(EmptyStringWalkerTest_222, RepeatZeroZero_222) {
  EXPECT_TRUE(ParseAndMimicsPCRE("a{0,0}"));
}

// Test: Alternation of non-empty patterns
TEST_F(EmptyStringWalkerTest_222, AlternateNonEmpty_222) {
  EXPECT_TRUE(ParseAndMimicsPCRE("a|b"));
}

// Test: Concatenation where one element cannot be empty
TEST_F(EmptyStringWalkerTest_222, ConcatWithNonEmpty_222) {
  EXPECT_TRUE(ParseAndMimicsPCRE("ab"));
}

// Test: Nested groups
TEST_F(EmptyStringWalkerTest_222, NestedGroups_222) {
  EXPECT_TRUE(ParseAndMimicsPCRE("((a))"));
}

// Test: Complex pattern with star inside alternation
TEST_F(EmptyStringWalkerTest_222, ComplexStarInAlternate_222) {
  EXPECT_TRUE(ParseAndMimicsPCRE("(a*|b)"));
}

// Test: Pattern that may not mimic PCRE - backreferences are not supported
// in re2, so patterns with certain features won't parse or won't mimic
TEST_F(EmptyStringWalkerTest_222, SimplePatternMimics_222) {
  // Simple patterns should mimic PCRE
  EXPECT_TRUE(ParseAndMimicsPCRE("hello"));
  EXPECT_TRUE(ParseAndMimicsPCRE("h.llo"));
  EXPECT_TRUE(ParseAndMimicsPCRE("[a-z]+"));
}

// Test: Literal string
TEST_F(EmptyStringWalkerTest_222, LiteralStringMimicsPCRE_222) {
  EXPECT_TRUE(ParseAndMimicsPCRE("abcdef"));
}

// Test: Nested star (a** equivalent behavior)
TEST_F(EmptyStringWalkerTest_222, NestedStarMimicsPCRE_222) {
  // a* is already fine, nested quantifiers may simplify
  EXPECT_TRUE(ParseAndMimicsPCRE("(a*)*"));
}

// Test: Plus of empty-matchable element
TEST_F(EmptyStringWalkerTest_222, PlusOfEmptyMatchable_222) {
  EXPECT_TRUE(ParseAndMimicsPCRE("(a*)+"));
}

// Test: Alternation where no branch can be empty
TEST_F(EmptyStringWalkerTest_222, AlternateNoEmptyBranch_222) {
  EXPECT_TRUE(ParseAndMimicsPCRE("a|b|c"));
}

// Test: Repeat with exact count
TEST_F(EmptyStringWalkerTest_222, RepeatExact_222) {
  EXPECT_TRUE(ParseAndMimicsPCRE("a{3}"));
}

// Test: Non-word boundary
TEST_F(EmptyStringWalkerTest_222, NonWordBoundary_222) {
  EXPECT_TRUE(ParseAndMimicsPCRE("\\B"));
}

// Test: Complex nested pattern
TEST_F(EmptyStringWalkerTest_222, ComplexNestedPattern_222) {
  EXPECT_TRUE(ParseAndMimicsPCRE("(a(b|c)*d)+"));
}

// Test: Multiple capture groups
TEST_F(EmptyStringWalkerTest_222, MultipleCaptureGroups_222) {
  EXPECT_TRUE(ParseAndMimicsPCRE("(a)(b)(c)"));
}

// Test: Optional capture group
TEST_F(EmptyStringWalkerTest_222, OptionalCaptureGroup_222) {
  EXPECT_TRUE(ParseAndMimicsPCRE("(a)?"));
}

// Test: Pattern with repeat min=1
TEST_F(EmptyStringWalkerTest_222, RepeatMinOne_222) {
  EXPECT_TRUE(ParseAndMimicsPCRE("a{1,5}"));
}

}  // namespace re2

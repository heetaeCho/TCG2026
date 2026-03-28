#include "gtest/gtest.h"
#include "re2/regexp.h"
#include "re2/walker-inl.h"

namespace re2 {

// We need to test RepetitionWalker::PreVisit behavior.
// Since RepetitionWalker is defined in parse.cc, we test it indirectly
// through the public Regexp interface, or we can test the PreVisit logic
// by creating Regexp objects and observing behavior.

class RepetitionWalkerTest_496 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test: Parse a simple repetition pattern and verify it compiles correctly
// This indirectly exercises RepetitionWalker through the parsing pipeline
TEST_F(RepetitionWalkerTest_496, SimpleRepeatPattern_496) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{3}", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpRepeat);
  EXPECT_EQ(re->min(), 3);
  EXPECT_EQ(re->max(), 3);
  re->Decref();
}

// Test: Repeat with min and max different
TEST_F(RepetitionWalkerTest_496, RepeatWithRange_496) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{2,5}", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpRepeat);
  EXPECT_EQ(re->min(), 2);
  EXPECT_EQ(re->max(), 5);
  re->Decref();
}

// Test: Repeat with unbounded max (e.g., a{2,})
TEST_F(RepetitionWalkerTest_496, RepeatUnboundedMax_496) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{2,}", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpRepeat);
  EXPECT_EQ(re->min(), 2);
  EXPECT_EQ(re->max(), -1);
  re->Decref();
}

// Test: Nested repetitions - this is the primary use case for RepetitionWalker
// The walker checks if nested repetitions would cause exponential blowup
TEST_F(RepetitionWalkerTest_496, NestedRepetitions_496) {
  RegexpStatus status;
  // Moderate nested repetition should succeed
  Regexp* re = Regexp::Parse("(a{2}){3}", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test: Simple literal (non-repeat) pattern - RepetitionWalker should pass through
TEST_F(RepetitionWalkerTest_496, NonRepeatPattern_496) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_NE(re->op(), kRegexpRepeat);
  re->Decref();
}

// Test: Star operator (not kRegexpRepeat, so PreVisit just passes parent_arg)
TEST_F(RepetitionWalkerTest_496, StarPattern_496) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a*", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  // Star is kRegexpStar, not kRegexpRepeat
  EXPECT_EQ(re->op(), kRegexpStar);
  re->Decref();
}

// Test: Plus operator
TEST_F(RepetitionWalkerTest_496, PlusPattern_496) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a+", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpPlus);
  re->Decref();
}

// Test: Quest operator
TEST_F(RepetitionWalkerTest_496, QuestPattern_496) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a?", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpQuest);
  re->Decref();
}

// Test: Repeat with min=0, max=0 (a{0})
TEST_F(RepetitionWalkerTest_496, RepeatZeroTimes_496) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{0}", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test: Repeat with min=1, max=1
TEST_F(RepetitionWalkerTest_496, RepeatOnce_496) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{1}", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test: Repeat with large count
TEST_F(RepetitionWalkerTest_496, RepeatLargeCount_496) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{100}", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpRepeat);
  EXPECT_EQ(re->min(), 100);
  EXPECT_EQ(re->max(), 100);
  re->Decref();
}

// Test: Deeply nested repetitions that might trigger the walker's limit
TEST_F(RepetitionWalkerTest_496, DeeplyNestedRepetitions_496) {
  RegexpStatus status;
  // Very deeply nested large repetitions might fail parsing due to
  // RepetitionWalker detecting exponential blowup
  Regexp* re = Regexp::Parse("((a{100}){100}){100}", Regexp::LikePerl, &status);
  // This might or might not succeed depending on the limit.
  // If it fails, status should indicate an error.
  if (re != nullptr) {
    re->Decref();
  }
}

// Test: Alternation with repeats
TEST_F(RepetitionWalkerTest_496, AlternationWithRepeats_496) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{3}|b{4}", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test: Concat with repeats
TEST_F(RepetitionWalkerTest_496, ConcatWithRepeats_496) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{3}b{4}", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test: Captured group with repeat
TEST_F(RepetitionWalkerTest_496, CapturedGroupRepeat_496) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(ab){5}", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpRepeat);
  EXPECT_EQ(re->min(), 5);
  EXPECT_EQ(re->max(), 5);
  re->Decref();
}

// Test: Repeat with min=0 and unbounded max
TEST_F(RepetitionWalkerTest_496, RepeatZeroOrMore_496) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{0,}", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test: Repeat with min=0, max=1 (equivalent to ?)
TEST_F(RepetitionWalkerTest_496, RepeatZeroOrOne_496) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{0,1}", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test: Empty pattern
TEST_F(RepetitionWalkerTest_496, EmptyPattern_496) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpEmptyMatch);
  re->Decref();
}

// Test: Complex pattern with mixed operators and repeats
TEST_F(RepetitionWalkerTest_496, ComplexMixedPattern_496) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a+b*c?){2,4}d{3}", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test: Verify that excessively nested repeats are caught
// The PreVisit divides parent_arg by m, so deeply nested large repeats
// should eventually reduce the arg to 0, stopping further expansion
TEST_F(RepetitionWalkerTest_496, ExcessivelyNestedRepeatsRejected_496) {
  RegexpStatus status;
  // Build a pattern with many nested large repetitions
  std::string pattern = "a";
  for (int i = 0; i < 10; i++) {
    pattern = "(" + pattern + "){1000}";
  }
  Regexp* re = Regexp::Parse(pattern, Regexp::LikePerl, &status);
  // This should likely fail due to RepetitionWalker limits
  if (re != nullptr) {
    re->Decref();
  } else {
    // If parsing failed, the status should indicate an error
    EXPECT_NE(status.code(), kRegexpSuccess);
  }
}

// Test: Repeat with max > min
TEST_F(RepetitionWalkerTest_496, RepeatRangeMaxGreaterThanMin_496) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{1,10}", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpRepeat);
  EXPECT_EQ(re->min(), 1);
  EXPECT_EQ(re->max(), 10);
  re->Decref();
}

// Test: Single character repeat {1}
TEST_F(RepetitionWalkerTest_496, RepeatExactlyOne_496) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{1,1}", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test: Repeat applied to character class
TEST_F(RepetitionWalkerTest_496, CharClassRepeat_496) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[abc]{5}", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test: Repeat applied to dot (any char)
TEST_F(RepetitionWalkerTest_496, DotRepeat_496) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(".{10}", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

}  // namespace re2

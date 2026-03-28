// File: parse_state_do_concatenation_test_510.cc

#include "gtest/gtest.h"

// Pull in the public RE2 interfaces.
#include "re2/regexp.h"

// ParseState is only defined in the .cc; include it here solely for testing its public API.
// (We are not modifying or re-implementing anything; just invoking public members.)
#include "re2/parse.cc"

namespace {

using re2::Regexp;

class DoConcatenationTest_510 : public ::testing::Test {
 protected:
  // Use default/empty parse flags as a neutral baseline.
  Regexp::ParseFlags flags_ = static_cast<Regexp::ParseFlags>(0);

  // Helper: build a Regexp* by parsing a pattern string.
  // Returns non-null on success.
  Regexp* ParsePattern(const std::string& pattern) {
    return Regexp::Parse(pattern, flags_, /*status=*/nullptr);
  }

  // Helper: structural equality using the testing-only comparator.
  void ExpectRegexpsEqual(Regexp* a, Regexp* b) {
    ASSERT_NE(a, nullptr);
    ASSERT_NE(b, nullptr);
    // Compare structure (not pointer identity).
    EXPECT_TRUE(a->RegexpEqualTestingOnly(a, b));
  }
};

// Normal operation: concatenating two literals should yield their concatenation.
TEST_F(DoConcatenationTest_510, ConcatsTwoLiteralsIntoSequence_510) {
  Regexp::ParseState ps(flags_, /*whole_regexp=*/"", /*status=*/nullptr);

  // Push 'a', then indicate we're ready to concatenate.
  ASSERT_TRUE(ps.PushLiteral('a'));
  ps.DoConcatenation();

  // Push 'b', then concatenate again so the pair can collapse into a concat.
  ASSERT_TRUE(ps.PushLiteral('b'));
  ps.DoConcatenation();

  // Finish and compare to parsing "ab".
  Regexp* got = ps.DoFinish();
  ASSERT_NE(got, nullptr);

  Regexp* expected = ParsePattern("ab");
  ExpectRegexpsEqual(got, expected);

  got->Decref();
  expected->Decref();
}

// Boundary: empty stack — DoConcatenation should act as if an empty-match is present.
TEST_F(DoConcatenationTest_510, EmptyStackInsertsEmptyMatch_510) {
  Regexp::ParseState ps(flags_, /*whole_regexp=*/"", /*status=*/nullptr);

  // No prior pushes; directly concatenate.
  ps.DoConcatenation();

  // Final result should be an empty match.
  Regexp* got = ps.DoFinish();
  ASSERT_NE(got, nullptr);

  Regexp* expected = ParsePattern("");
  ExpectRegexpsEqual(got, expected);

  got->Decref();
  expected->Decref();
}

// Boundary (marker on top): start a capturing group and immediately concatenate.
// This should behave as if an empty term is inside the group.
TEST_F(DoConcatenationTest_510, AtGroupStartInsertsEmptyInsideCapture_510) {
  Regexp::ParseState ps(flags_, /*whole_regexp=*/"", /*status=*/nullptr);

  // Open a capturing group, immediately concatenate (no explicit term yet),
  // then close the group.
  ASSERT_TRUE(ps.DoLeftParen(/*name=*/""));
  ps.DoConcatenation();
  ASSERT_TRUE(ps.DoRightParen());

  Regexp* got = ps.DoFinish();
  ASSERT_NE(got, nullptr);

  // Expect this to be equivalent to parsing "()" (capturing empty).
  Regexp* expected = ParsePattern("()");
  ExpectRegexpsEqual(got, expected);

  // Also verify observable capture count effect.
  EXPECT_EQ(got->NumCaptures(), 1);

  got->Decref();
  expected->Decref();
}

// Sanity: when there is already a literal on stack, concatenation should NOT
// inject an extra empty-match (result remains just that literal).
TEST_F(DoConcatenationTest_510, NoImplicitEmptyWhenItemPresent_510) {
  Regexp::ParseState ps(flags_, /*whole_regexp=*/"", /*status=*/nullptr);

  ASSERT_TRUE(ps.PushLiteral('x'));
  ps.DoConcatenation();  // Should not insert another empty term.

  Regexp* got = ps.DoFinish();
  ASSERT_NE(got, nullptr);

  Regexp* expected = ParsePattern("x");
  ExpectRegexpsEqual(got, expected);

  got->Decref();
  expected->Decref();
}

}  // namespace

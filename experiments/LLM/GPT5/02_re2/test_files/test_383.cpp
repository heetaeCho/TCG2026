// File: ./TestProjects/re2/re2/testing/substring_walker_postvisit_test_383.cc

#include "gtest/gtest.h"
#include <algorithm>

#include "re2/regexp.h"
// SubstringWalker is defined in the fuzzer source; include it directly to access the class.
#include "re2/fuzzing/re2_fuzzer.cc"

namespace {

using re2::Regexp;
using re2::RegexpOp;

using PF = re2::Regexp::ParseFlags;

// Helper: create a Regexp node for the given op using only public factory functions.
// We keep creation minimal since PostVisit only inspects op() and (for LiteralString) nrunes().
static Regexp* MakeNodeForOp(RegexpOp op, PF flags = static_cast<PF>(0)) {
  switch (op) {
    case re2::kRegexpConcat: {
      Regexp* a = Regexp::NewLiteral('a', flags);
      Regexp* b = Regexp::NewLiteral('b', flags);
      Regexp* subs[2] = {a, b};
      return Regexp::Concat(subs, 2, flags);
    }
    case re2::kRegexpAlternate: {
      Regexp* a = Regexp::NewLiteral('x', flags);
      Regexp* b = Regexp::NewLiteral('y', flags);
      Regexp* subs[2] = {a, b};
      return Regexp::Alternate(subs, 2, flags);
    }
    case re2::kRegexpStar: {
      Regexp* sub = Regexp::NewLiteral('s', flags);
      return Regexp::Star(sub, flags);
    }
    case re2::kRegexpPlus: {
      Regexp* sub = Regexp::NewLiteral('p', flags);
      return Regexp::Plus(sub, flags);
    }
    case re2::kRegexpQuest: {
      Regexp* sub = Regexp::NewLiteral('q', flags);
      return Regexp::Quest(sub, flags);
    }
    case re2::kRegexpRepeat: {
      Regexp* sub = Regexp::NewLiteral('r', flags);
      return Regexp::Repeat(sub, flags, /*min=*/1, /*max=*/3);
    }
    case re2::kRegexpCapture: {
      Regexp* sub = Regexp::NewLiteral('c', flags);
      return Regexp::Capture(sub, flags, /*cap=*/1);
    }
    case re2::kRegexpLiteralString: {
      re2::Rune runes[3] = {'A', 'B', 'C'};
      return Regexp::LiteralString(runes, 3, flags);
    }
    case re2::kRegexpLiteral: {
      return Regexp::NewLiteral('Z', flags);
    }
    default:
      // For any other op not covered by PostVisit switch, use a safe literal.
      return Regexp::NewLiteral('N', flags);
  }
}

class SubstringWalkerTest_383 : public ::testing::Test {
protected:
  PF flags_ = static_cast<PF>(0);
  SubstringWalker walker_;  // From re2_fuzzer.cc
};

}  // namespace

// --- Normal operation: kRegexpLiteralString returns nrunes() ---
TEST_F(SubstringWalkerTest_383, LiteralString_ReturnsNrunes_383) {
  re2::Rune runes[4] = {'a', 'b', 'c', 'd'};
  Regexp* re = Regexp::LiteralString(runes, 4, flags_);
  ASSERT_NE(re, nullptr);

  // child args are ignored for LiteralString
  const int result = walker_.PostVisit(re, /*parent_arg=*/123, /*pre_arg=*/456,
                                       /*child_args=*/nullptr, /*nchild_args=*/0);

  EXPECT_EQ(result, 4);
  re->Decref();
}

// --- Normal operation: ops that aggregate should return max(child_args) ---
TEST_F(SubstringWalkerTest_383, Concat_MaxOfChildren_383) {
  Regexp* re = MakeNodeForOp(re2::kRegexpConcat, flags_);
  ASSERT_NE(re, nullptr);

  int child_args[] = {1, 5, 3, 4};
  const int result = walker_.PostVisit(re, /*parent_arg=*/0, /*pre_arg=*/0,
                                       child_args, /*nchild_args=*/4);

  EXPECT_EQ(result, 5);
  re->Decref();
}

TEST_F(SubstringWalkerTest_383, Alternate_MaxOfChildren_383) {
  Regexp* re = MakeNodeForOp(re2::kRegexpAlternate, flags_);
  ASSERT_NE(re, nullptr);

  int child_args[] = {10, 7, 12};
  const int result = walker_.PostVisit(re, /*parent_arg=*/0, /*pre_arg=*/0,
                                       child_args, /*nchild_args=*/3);

  EXPECT_EQ(result, 12);
  re->Decref();
}

TEST_F(SubstringWalkerTest_383, Star_MaxOfChildren_383) {
  Regexp* re = MakeNodeForOp(re2::kRegexpStar, flags_);
  ASSERT_NE(re, nullptr);

  int child_args[] = {2};
  const int result = walker_.PostVisit(re, /*parent_arg=*/0, /*pre_arg=*/0,
                                       child_args, /*nchild_args=*/1);

  EXPECT_EQ(result, 2);
  re->Decref();
}

TEST_F(SubstringWalkerTest_383, Plus_MaxOfChildren_383) {
  Regexp* re = MakeNodeForOp(re2::kRegexpPlus, flags_);
  ASSERT_NE(re, nullptr);

  int child_args[] = {6, 3};
  const int result = walker_.PostVisit(re, /*parent_arg=*/0, /*pre_arg=*/0,
                                       child_args, /*nchild_args=*/2);

  EXPECT_EQ(result, 6);
  re->Decref();
}

TEST_F(SubstringWalkerTest_383, Quest_MaxOfChildren_383) {
  Regexp* re = MakeNodeForOp(re2::kRegexpQuest, flags_);
  ASSERT_NE(re, nullptr);

  int child_args[] = {4, 9, 1};
  const int result = walker_.PostVisit(re, /*parent_arg=*/0, /*pre_arg=*/0,
                                       child_args, /*nchild_args=*/3);

  EXPECT_EQ(result, 9);
  re->Decref();
}

TEST_F(SubstringWalkerTest_383, Repeat_MaxOfChildren_383) {
  Regexp* re = MakeNodeForOp(re2::kRegexpRepeat, flags_);
  ASSERT_NE(re, nullptr);

  int child_args[] = {8, 8, 7};
  const int result = walker_.PostVisit(re, /*parent_arg=*/0, /*pre_arg=*/0,
                                       child_args, /*nchild_args=*/3);

  EXPECT_EQ(result, 8);
  re->Decref();
}

TEST_F(SubstringWalkerTest_383, Capture_MaxOfChildren_383) {
  Regexp* re = MakeNodeForOp(re2::kRegexpCapture, flags_);
  ASSERT_NE(re, nullptr);

  int child_args[] = {1, 100, 50};
  const int result = walker_.PostVisit(re, /*parent_arg=*/0, /*pre_arg=*/0,
                                       child_args, /*nchild_args=*/3);

  EXPECT_EQ(result, 100);
  re->Decref();
}

// --- Boundary: zero children for aggregating ops returns -1 (no child to aggregate) ---
TEST_F(SubstringWalkerTest_383, AggregatingOp_NoChildren_ReturnsMinusOne_383) {
  Regexp* re = MakeNodeForOp(re2::kRegexpStar, flags_);
  ASSERT_NE(re, nullptr);

  const int result = walker_.PostVisit(re, /*parent_arg=*/999, /*pre_arg=*/-999,
                                       /*child_args=*/nullptr, /*nchild_args=*/0);

  EXPECT_EQ(result, -1);
  re->Decref();
}

// --- Boundary: all-negative children; implementation initializes max to -1 ---
TEST_F(SubstringWalkerTest_383, AggregatingOp_AllNegativeChildren_ReturnsMinusOne_383) {
  Regexp* re = MakeNodeForOp(re2::kRegexpRepeat, flags_);
  ASSERT_NE(re, nullptr);

  int child_args[] = {-5, -9, -2};
  const int result = walker_.PostVisit(re, /*parent_arg=*/0, /*pre_arg=*/0,
                                       child_args, /*nchild_args=*/3);

  // Based on observable behavior of PostVisit's implementation.
  EXPECT_EQ(result, -1);
  re->Decref();
}

// --- Default/other ops: not handled explicitly -> returns -1 ---
TEST_F(SubstringWalkerTest_383, OtherOp_ReturnsMinusOne_383) {
  // kRegexpLiteral is not among the handled ops in the switch.
  Regexp* re = MakeNodeForOp(re2::kRegexpLiteral, flags_);
  ASSERT_NE(re, nullptr);

  int child_args[] = {3, 4};
  const int result = walker_.PostVisit(re, /*parent_arg=*/0, /*pre_arg=*/0,
                                       child_args, /*nchild_args=*/2);

  EXPECT_EQ(result, -1);
  re->Decref();
}

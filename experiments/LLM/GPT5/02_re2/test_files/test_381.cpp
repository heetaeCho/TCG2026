// File: subexpression_walker_postvisit_test_381.cc
#include <gtest/gtest.h>
#include <limits>

#include "re2/regexp.h"

// We include the defining TU to access the class under test.
// (In this codebase, SubexpressionWalker lives in this .cc.)
#include "re2/fuzzing/re2_fuzzer.cc"

using re2::Regexp;

// Helper to build a CONCAT node without relying on parsing details.
// We use HaveMatch() leaves so the builder doesn't collapse into a literal.
static Regexp* MakeConcatNode() {
  Regexp* a = Regexp::HaveMatch(1, static_cast<Regexp::ParseFlags>(0));
  Regexp* b = Regexp::HaveMatch(2, static_cast<Regexp::ParseFlags>(0));
  Regexp* subs[2] = {a, b};
  Regexp* cat = Regexp::Concat(subs, 2, static_cast<Regexp::ParseFlags>(0));
  // Release only the top; RE2 Regexp nodes are ref-counted and the
  // parent owns references to its children.
  return cat;
}

// Helper to build an ALTERNATE node similarly.
static Regexp* MakeAlternateNode() {
  Regexp* a = Regexp::HaveMatch(3, static_cast<Regexp::ParseFlags>(0));
  Regexp* b = Regexp::HaveMatch(4, static_cast<Regexp::ParseFlags>(0));
  Regexp* subs[2] = {a, b};
  Regexp* alt = Regexp::Alternate(subs, 2, static_cast<Regexp::ParseFlags>(0));
  return alt;
}

// Helper to build a non-CONCAT/NON-ALTERNATE node (e.g., HaveMatch).
static Regexp* MakeOtherNode() {
  return Regexp::HaveMatch(5, static_cast<Regexp::ParseFlags>(0));
}

// ---------- Tests ----------

TEST(SubexpressionWalkerTest_381, Concat_ReturnsMaxChildOrCount_381) {
  SubexpressionWalker w;

  Regexp* cat = MakeConcatNode();
  ASSERT_NE(cat, nullptr);
  ASSERT_EQ(cat->op(), re2::kRegexpConcat);

  int child_args[] = {1, 7, 3};
  const int nchild_args = 3;

  // Expected: max of {nchild_args, child_args...} = max(3, 1, 7, 3) = 7
  int res = w.PostVisit(cat, /*parent_arg=*/123, /*pre_arg=*/-5,
                        child_args, nchild_args);
  EXPECT_EQ(res, 7);

  cat->Decref();
}

TEST(SubexpressionWalkerTest_381, Concat_WhenChildrenLECount_ReturnsCount_381) {
  SubexpressionWalker w;

  Regexp* cat = MakeConcatNode();
  ASSERT_NE(cat, nullptr);
  ASSERT_EQ(cat->op(), re2::kRegexpConcat);

  int child_args[] = {0, 1, 2};
  const int nchild_args = 3;

  // Expected: max(3, 0, 1, 2) = 3
  int res = w.PostVisit(cat, /*parent_arg=*/0, /*pre_arg=*/0,
                        child_args, nchild_args);
  EXPECT_EQ(res, 3);

  cat->Decref();
}

TEST(SubexpressionWalkerTest_381, Concat_WithZeroChildren_ReturnsZero_381) {
  SubexpressionWalker w;

  Regexp* cat = MakeConcatNode();
  ASSERT_NE(cat, nullptr);
  ASSERT_EQ(cat->op(), re2::kRegexpConcat);

  // No children: pointer may be null; nchild_args = 0 -> loop doesn't run.
  int* child_args = nullptr;
  const int nchild_args = 0;

  int res = w.PostVisit(cat, /*parent_arg=*/42, /*pre_arg=*/-1,
                        child_args, nchild_args);
  EXPECT_EQ(res, 0);

  cat->Decref();
}

TEST(SubexpressionWalkerTest_381, Alternate_ReturnsMaxChildOrCount_381) {
  SubexpressionWalker w;

  Regexp* alt = MakeAlternateNode();
  ASSERT_NE(alt, nullptr);
  ASSERT_EQ(alt->op(), re2::kRegexpAlternate);

  int child_args[] = {2, std::numeric_limits<int>::max() / 2, 5};
  const int nchild_args = 3;

  // Expected: max(3, 2, INT_MAX/2, 5) = INT_MAX/2
  int res = w.PostVisit(alt, /*parent_arg=*/999, /*pre_arg=*/-999,
                        child_args, nchild_args);
  EXPECT_EQ(res, std::numeric_limits<int>::max() / 2);

  alt->Decref();
}

TEST(SubexpressionWalkerTest_381, OtherOp_ReturnsMinusOne_381) {
  SubexpressionWalker w;

  Regexp* other = MakeOtherNode();
  ASSERT_NE(other, nullptr);
  ASSERT_NE(other->op(), re2::kRegexpConcat);
  ASSERT_NE(other->op(), re2::kRegexpAlternate);

  int child_args[] = {10, 20};
  const int nchild_args = 2;

  // For non-CONCAT/ALTERNATE ops, PostVisit should return -1.
  int res = w.PostVisit(other, /*parent_arg=*/-123, /*pre_arg=*/456,
                        child_args, nchild_args);
  EXPECT_EQ(res, -1);

  other->Decref();
}

TEST(SubexpressionWalkerTest_381, Concat_NegativeChildren_StillUsesMaxWithCount_381) {
  SubexpressionWalker w;

  Regexp* cat = MakeConcatNode();
  ASSERT_NE(cat, nullptr);
  ASSERT_EQ(cat->op(), re2::kRegexpConcat);

  int child_args[] = {-10, -3};
  const int nchild_args = 2;

  // Expected: max(2, -10, -3) = 2
  int res = w.PostVisit(cat, /*parent_arg=*/0, /*pre_arg=*/0,
                        child_args, nchild_args);
  EXPECT_EQ(res, 2);

  cat->Decref();
}

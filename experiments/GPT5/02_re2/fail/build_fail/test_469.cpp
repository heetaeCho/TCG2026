// File: prefilter_tree_equal_test_469.cc

#include "gtest/gtest.h"
#include "re2/re2.h"
#include "re2/prefilter.h"
#include "re2/prefilter_tree.h"

using re2::Prefilter;
using re2::PrefilterTree;

class PrefilterTreeEqualTest_469 : public ::testing::Test {
protected:
  // Helper to build a Prefilter via the public API.
  static Prefilter* MakeFromRegex(const std::string& pattern) {
    RE2 re(pattern);
    return Prefilter::FromRE2(&re);
  }
};

// Verifies that comparing the same pointer (aliasing) yields equality.
TEST_F(PrefilterTreeEqualTest_469, SamePointerIsEqual_469) {
  std::unique_ptr<Prefilter> pf(MakeFromRegex("abc"));
  ASSERT_NE(pf, nullptr);

  PrefilterTree::PrefilterEqual eq;
  // Same pointer on both sides.
  EXPECT_TRUE(eq(pf.get(), pf.get()));
}

// Verifies that two independently constructed, but semantically identical
// prefilters compare equal via PrefilterEqual (symmetry included).
TEST_F(PrefilterTreeEqualTest_469, IdenticalPatternsCompareEqual_469) {
  std::unique_ptr<Prefilter> a(MakeFromRegex("hello|world"));
  std::unique_ptr<Prefilter> b(MakeFromRegex("hello|world"));
  ASSERT_NE(a, nullptr);
  ASSERT_NE(b, nullptr);

  PrefilterTree::PrefilterEqual eq;
  EXPECT_TRUE(eq(a.get(), b.get()));
  EXPECT_TRUE(eq(b.get(), a.get()));  // symmetry
}

// Verifies that two prefilters built from different patterns compare not equal.
TEST_F(PrefilterTreeEqualTest_469, DifferentPatternsCompareNotEqual_469) {
  std::unique_ptr<Prefilter> a(MakeFromRegex("cat"));
  std::unique_ptr<Prefilter> b(MakeFromRegex("dog"));
  ASSERT_NE(a, nullptr);
  ASSERT_NE(b, nullptr);

  PrefilterTree::PrefilterEqual eq;
  EXPECT_FALSE(eq(a.get(), b.get()));
  EXPECT_FALSE(eq(b.get(), a.get()));  // symmetry
}

// Verifies that complex-but-equal patterns (structurally equivalent) still
// compare equal when constructed independently.
TEST_F(PrefilterTreeEqualTest_469, EquivalentStructuredPatternsCompareEqual_469) {
  // Two regexes that should yield equivalent prefilter structure/atoms:
  // - "ab(c|d)" vs "a(?:b(?:c|d))"
  std::unique_ptr<Prefilter> a(MakeFromRegex("ab(c|d)"));
  std::unique_ptr<Prefilter> b(MakeFromRegex("a(?:b(?:c|d))"));
  ASSERT_NE(a, nullptr);
  ASSERT_NE(b, nullptr);

  PrefilterTree::PrefilterEqual eq;
  EXPECT_TRUE(eq(a.get(), b.get()));
  EXPECT_TRUE(eq(b.get(), a.get()));
}

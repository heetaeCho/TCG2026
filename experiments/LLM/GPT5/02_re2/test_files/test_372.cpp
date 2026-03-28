// File: charclassbuilder_contains_test_372.cc
#include <gtest/gtest.h>
#include "re2/regexp.h"

namespace {

using re2::CharClassBuilder;
// Rune is declared in the header; use it directly.
using re2::Rune;

class CharClassBuilderContainsTest_372 : public ::testing::Test {
protected:
  CharClassBuilder cc_;
};

// [Normal] Empty builder should not contain arbitrary runes.
TEST_F(CharClassBuilderContainsTest_372, Contains_EmptyReturnsFalse_372) {
  EXPECT_FALSE(cc_.Contains(static_cast<Rune>('a')));
  EXPECT_FALSE(cc_.Contains(static_cast<Rune>(0)));
  EXPECT_FALSE(cc_.Contains(static_cast<Rune>(0x10FFFF)));  // max Unicode code point range guard
}

// [Normal] After adding a singleton range, Contains should hit only that rune.
TEST_F(CharClassBuilderContainsTest_372, Contains_SingletonRange_372) {
  Rune x = static_cast<Rune>('x');
  ASSERT_TRUE(cc_.AddRange(x, x));  // observable: returns bool
  EXPECT_TRUE(cc_.Contains(x));
  EXPECT_FALSE(cc_.Contains(static_cast<Rune>('w')));
  EXPECT_FALSE(cc_.Contains(static_cast<Rune>('y')));
}

// [Boundary] Inclusive bounds: lo and hi should both be included.
TEST_F(CharClassBuilderContainsTest_372, Contains_InclusiveBounds_372) {
  Rune lo = static_cast<Rune>('a');
  Rune hi = static_cast<Rune>('c');
  ASSERT_TRUE(cc_.AddRange(lo, hi));
  EXPECT_TRUE(cc_.Contains(lo));                // 'a'
  EXPECT_TRUE(cc_.Contains(static_cast<Rune>('b')));
  EXPECT_TRUE(cc_.Contains(hi));                // 'c'
  EXPECT_FALSE(cc_.Contains(static_cast<Rune>('d')));
  EXPECT_FALSE(cc_.Contains(static_cast<Rune>('`'))); // just below 'a'
}

// [Normal] Multiple disjoint ranges should each be recognized.
TEST_F(CharClassBuilderContainsTest_372, Contains_MultipleDisjointRanges_372) {
  ASSERT_TRUE(cc_.AddRange(static_cast<Rune>('0'), static_cast<Rune>('3'))); // 0-3
  ASSERT_TRUE(cc_.AddRange(static_cast<Rune>('7'), static_cast<Rune>('9'))); // 7-9
  // Hits
  EXPECT_TRUE(cc_.Contains(static_cast<Rune>('0')));
  EXPECT_TRUE(cc_.Contains(static_cast<Rune>('2')));
  EXPECT_TRUE(cc_.Contains(static_cast<Rune>('8')));
  EXPECT_TRUE(cc_.Contains(static_cast<Rune>('9')));
  // Misses (gap and outside)
  EXPECT_FALSE(cc_.Contains(static_cast<Rune>('4')));
  EXPECT_FALSE(cc_.Contains(static_cast<Rune>('6')));
  EXPECT_FALSE(cc_.Contains(static_cast<Rune>('/'))); // below '0'
  EXPECT_FALSE(cc_.Contains(static_cast<Rune>(':'))); // above '9'
}

// [Interaction] AddCharClass: union of classes should reflect in Contains.
TEST_F(CharClassBuilderContainsTest_372, Contains_AddCharClassMerges_372) {
  CharClassBuilder left;
  CharClassBuilder right;

  ASSERT_TRUE(left.AddRange(static_cast<Rune>('a'), static_cast<Rune>('b')));   // a-b
  ASSERT_TRUE(right.AddRange(static_cast<Rune>('x'), static_cast<Rune>('z')));  // x-z

  // Merge right into left via public API and observe membership.
  left.AddCharClass(&right);

  EXPECT_TRUE(left.Contains(static_cast<Rune>('a')));
  EXPECT_TRUE(left.Contains(static_cast<Rune>('b')));
  EXPECT_TRUE(left.Contains(static_cast<Rune>('x')));
  EXPECT_TRUE(left.Contains(static_cast<Rune>('z')));

  EXPECT_FALSE(left.Contains(static_cast<Rune>('c')));
  EXPECT_FALSE(left.Contains(static_cast<Rune>('w')));
}

// [Interaction] Copy: copied builder should preserve membership.
TEST_F(CharClassBuilderContainsTest_372, Contains_CopyPreservesMembership_372) {
  ASSERT_TRUE(cc_.AddRange(static_cast<Rune>('m'), static_cast<Rune>('p'))); // m-p
  std::unique_ptr<CharClassBuilder> copy{cc_.Copy()};
  ASSERT_NE(copy, nullptr);

  // Original still works
  EXPECT_TRUE(cc_.Contains(static_cast<Rune>('m')));
  EXPECT_TRUE(cc_.Contains(static_cast<Rune>('o')));
  EXPECT_FALSE(cc_.Contains(static_cast<Rune>('q')));

  // Copy has identical observable behavior (for Contains)
  EXPECT_TRUE(copy->Contains(static_cast<Rune>('m')));
  EXPECT_TRUE(copy->Contains(static_cast<Rune>('o')));
  EXPECT_FALSE(copy->Contains(static_cast<Rune>('q')));
}

// [Boundary/Mutation] RemoveAbove should truncate membership strictly to <= pivot.
TEST_F(CharClassBuilderContainsTest_372, Contains_RemoveAboveTruncates_372) {
  ASSERT_TRUE(cc_.AddRange(static_cast<Rune>('a'), static_cast<Rune>('z')));
  cc_.RemoveAbove(static_cast<Rune>('c'));  // keep only <= 'c' per public contract

  EXPECT_TRUE(cc_.Contains(static_cast<Rune>('a')));
  EXPECT_TRUE(cc_.Contains(static_cast<Rune>('b')));
  EXPECT_TRUE(cc_.Contains(static_cast<Rune>('c')));

  EXPECT_FALSE(cc_.Contains(static_cast<Rune>('d')));
  EXPECT_FALSE(cc_.Contains(static_cast<Rune>('x')));
  EXPECT_FALSE(cc_.Contains(static_cast<Rune>('z')));
}

}  // namespace

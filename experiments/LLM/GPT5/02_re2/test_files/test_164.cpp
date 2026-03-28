// File: charclassbuilder_end_test_164.cc
#include <gtest/gtest.h>
#include "re2/regexp.h"

using namespace re2;  // NOLINT

// Verifies: On a default-constructed CharClassBuilder, begin() == end().
TEST(CharClassBuilderEnd_164, EndOnEmptyEqualsBegin_164) {
  CharClassBuilder cc;
  EXPECT_TRUE(cc.empty());
  EXPECT_EQ(cc.begin(), cc.end());
  EXPECT_EQ(cc.size(), 0);
}

// Verifies: After adding a range, end() is a valid sentinel distinct from begin().
TEST(CharClassBuilderEnd_164, EndAfterAddRangeNotEqualBegin_164) {
  CharClassBuilder cc;
  ASSERT_TRUE(cc.AddRange('a', 'a'));  // add a single element range (observable via size/begin/end)
  EXPECT_FALSE(cc.empty());
  EXPECT_NE(cc.begin(), cc.end());
  EXPECT_GE(cc.size(), 1);
}

// Verifies: Iterating from begin() to end() terminates at end() and the
// iteration count matches size(). (We do not dereference; we only advance.)
TEST(CharClassBuilderEnd_164, IterationReachesEndAndCountsSize_164) {
  CharClassBuilder cc;
  ASSERT_TRUE(cc.AddRange('a', 'c'));
  ASSERT_TRUE(cc.AddRange('x', 'z'));
  // Count number of iterator steps without dereferencing.
  int steps = 0;
  for (auto it = cc.begin(); it != cc.end(); ++it) {
    ++steps;
  }
  // We cannot assert an exact step count beyond matching size(),
  // since size() is the visible contract.
  EXPECT_EQ(steps, cc.size());
  // And we reached end() by construction of the loop:
  EXPECT_EQ(cc.end(), cc.end());  // trivial sanity check that end() is comparable
}

// Verifies: After removing all ranges (via RemoveAbove with a low cutoff),
// the set becomes empty and begin() == end().
TEST(CharClassBuilderEnd_164, EndAfterRemoveAllBecomesEmpty_164) {
  CharClassBuilder cc;
  ASSERT_TRUE(cc.AddRange('a', 'f'));
  ASSERT_TRUE(cc.AddRange('x', 'z'));
  // Remove any entries >= 'a' to force empty (observable through empty/size).
  cc.RemoveAbove('a' - 1);
  EXPECT_TRUE(cc.empty());
  EXPECT_EQ(cc.size(), 0);
  EXPECT_EQ(cc.begin(), cc.end());
}

// Verifies: end() on a copy behaves consistently (copy has its own container;
// we validate via its own begin()/end()/size()).
TEST(CharClassBuilderEnd_164, EndOnCopyBehavesLikeOriginal_164) {
  CharClassBuilder cc;
  ASSERT_TRUE(cc.AddRange('m', 'q'));

  std::unique_ptr<CharClassBuilder> copy(cc.Copy());
  ASSERT_NE(copy, nullptr);

  EXPECT_FALSE(copy->empty());
  EXPECT_NE(copy->begin(), copy->end());

  int steps_original = 0;
  for (auto it = cc.begin(); it != cc.end(); ++it) ++steps_original;

  int steps_copy = 0;
  for (auto it = copy->begin(); it != copy->end(); ++it) ++steps_copy;

  EXPECT_EQ(steps_original, cc.size());
  EXPECT_EQ(steps_copy, copy->size());
  EXPECT_EQ(steps_original, steps_copy);
}

// Verifies: Adding ranges via AddCharClass makes end() a proper sentinel for the
// receiving builder as well (observable via begin/end/size).
TEST(CharClassBuilderEnd_164, EndAfterAddCharClass_164) {
  CharClassBuilder source;
  ASSERT_TRUE(source.AddRange('0', '9'));
  ASSERT_TRUE(source.AddRange('A', 'F'));

  CharClassBuilder dest;
  EXPECT_TRUE(dest.empty());
  EXPECT_EQ(dest.begin(), dest.end());

  dest.AddCharClass(&source);

  EXPECT_FALSE(dest.empty());
  EXPECT_NE(dest.begin(), dest.end());

  int steps_dest = 0;
  for (auto it = dest.begin(); it != dest.end(); ++it) ++steps_dest;
  EXPECT_EQ(steps_dest, dest.size());
}

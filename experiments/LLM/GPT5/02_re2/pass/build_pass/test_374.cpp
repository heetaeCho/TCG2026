// File: charclassbuilder_copy_test_374.cc
#include <gtest/gtest.h>
#include "re2/regexp.h"  // Assumed path based on prompt; adjust include if needed.

using re2::CharClassBuilder;

class CharClassBuilderCopyTest_374 : public ::testing::Test {
protected:
  static void ExpectSameMembership(CharClassBuilder& a, CharClassBuilder& b,
                                   const std::vector<int>& runes) {
    for (int r : runes) {
      EXPECT_EQ(a.Contains(r), b.Contains(r)) << "Rune " << r << " differs";
    }
  }
};

// Normal operation: Copy of a non-empty builder preserves observable behavior
TEST_F(CharClassBuilderCopyTest_374, Copy_PreservesMembershipAndSize_374) {
  CharClassBuilder original;
  // Create several disjoint and touching ranges, including a single-point range.
  ASSERT_TRUE(original.AddRange(1, 3));
  ASSERT_TRUE(original.AddRange(10, 10));
  ASSERT_TRUE(original.AddRange(20, 25));

  // Sanity checks on original (observable behavior only).
  EXPECT_TRUE(original.Contains(1));
  EXPECT_TRUE(original.Contains(2));
  EXPECT_TRUE(original.Contains(3));
  EXPECT_TRUE(original.Contains(10));
  EXPECT_TRUE(original.Contains(22));
  EXPECT_FALSE(original.Contains(0));
  EXPECT_FALSE(original.Contains(4));
  EXPECT_FALSE(original.Contains(9));
  EXPECT_FALSE(original.Contains(26));
  EXPECT_FALSE(original.empty());

  // Copy and compare observable behavior.
  std::unique_ptr<CharClassBuilder> copy(original.Copy());
  ASSERT_NE(copy.get(), nullptr);
  EXPECT_FALSE(copy->empty());
  EXPECT_EQ(original.size(), copy->size());
  EXPECT_EQ(original.FoldsASCII(), copy->FoldsASCII());

  // Membership equality over a sample of values (including boundaries).
  ExpectSameMembership(original, *copy,
                       {0,1,2,3,4,9,10,11,19,20,22,25,26,100});
}

// Independence: Mutations to the original after Copy() do not affect the copy
TEST_F(CharClassBuilderCopyTest_374, Copy_IsDeepAndIndependent_374) {
  CharClassBuilder original;
  ASSERT_TRUE(original.AddRange(5, 5));   // single element
  ASSERT_TRUE(original.AddRange(7, 9));   // small range

  std::unique_ptr<CharClassBuilder> copy(original.Copy());
  ASSERT_NE(copy.get(), nullptr);

  // Verify same behavior before mutation.
  ExpectSameMembership(original, *copy, {4,5,6,7,8,9,10});
  EXPECT_EQ(original.size(), copy->size());
  EXPECT_EQ(original.FoldsASCII(), copy->FoldsASCII());

  // Mutate original in ways visible through the public API.
  // We do not assert exact post-conditions on 'original' (no inference),
  // only that 'copy' remains unchanged relative to its pre-mutation state.
  // Choose operations that are part of the interface:
  original.AddRange(100, 110);
  original.RemoveAbove(50);   // Observable via membership changes
  original.Negate();          // Observable via membership inversion

  // After mutations, at least one membership should differ between original and copy.
  // (If none differ for this set, expand the probe set.)
  std::vector<int> probe = {0,4,5,6,7,8,9,10,49,50,51,100,105,110,111,1000};
  bool any_diff = false;
  for (int r : probe) {
    if (original.Contains(r) != copy->Contains(r)) {
      any_diff = true;
      break;
    }
  }
  EXPECT_TRUE(any_diff) << "Copy should remain independent after original mutations";

  // Copy still reflects its pre-mutation behavior on a few key points.
  // (We only assert copy's behavior equals what it was at creation time,
  // without relying on internal logic.)
  // Rebuild a fresh baseline and compare to copy.
  CharClassBuilder baseline;
  ASSERT_TRUE(baseline.AddRange(5, 5));
  ASSERT_TRUE(baseline.AddRange(7, 9));
  ExpectSameMembership(baseline, *copy, probe);
}

// Boundary conditions: Empty source copies as empty and remains independent
TEST_F(CharClassBuilderCopyTest_374, Copy_FromEmpty_YieldsEmptyAndIndependent_374) {
  CharClassBuilder original;
  EXPECT_TRUE(original.empty());
  std::unique_ptr<CharClassBuilder> copy(original.Copy());
  ASSERT_NE(copy.get(), nullptr);
  EXPECT_TRUE(copy->empty());
  EXPECT_EQ(original.size(), copy->size());
  EXPECT_EQ(original.FoldsASCII(), copy->FoldsASCII());

  // Mutate original; copy should remain empty (observable via Contains/empty/size).
  original.AddRange(0, 0);
  original.Negate();   // whatever this means internally, it's observable

  EXPECT_TRUE(copy->empty());
  EXPECT_EQ(0, copy->size());
  // Membership spot-check: copy should still have the same (empty) membership.
  for (int r : { -1, 0, 1, 100 }) {
    EXPECT_FALSE(copy->Contains(r));
  }
}

// Mixed behavior: Copy preserves flags/behavior that are externally observable
TEST_F(CharClassBuilderCopyTest_374, Copy_PreservesFoldsASCIIFlag_374) {
  CharClassBuilder original;
  // Add ranges that may influence ASCII folding behavior (treat as a black box).
  ASSERT_TRUE(original.AddRange('A', 'Z'));
  ASSERT_TRUE(original.AddRange('a', 'z'));

  std::unique_ptr<CharClassBuilder> copy(original.Copy());
  ASSERT_NE(copy.get(), nullptr);

  // Whatever FoldsASCII means internally, the copy should match the original.
  EXPECT_EQ(original.FoldsASCII(), copy->FoldsASCII());

  // Spot-check membership equality around ASCII letters and nearby runes.
  ExpectSameMembership(original, *copy,
                       {'A'-1, 'A', 'M', 'Z', 'Z'+1, 'a'-1, 'a', 'm', 'z', 'z'+1});
}

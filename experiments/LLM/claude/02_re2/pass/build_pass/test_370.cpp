#include <gtest/gtest.h>
#include "re2/regexp.h"
#include "util/utf.h"

namespace re2 {

class CharClassBuilderTest_370 : public ::testing::Test {
 protected:
  CharClassBuilder ccb_;
};

// Normal operation tests

TEST_F(CharClassBuilderTest_370, AddSingleCharacterRange_370) {
  EXPECT_TRUE(ccb_.AddRange('a', 'a'));
  EXPECT_TRUE(ccb_.Contains('a'));
  EXPECT_FALSE(ccb_.Contains('b'));
}

TEST_F(CharClassBuilderTest_370, AddMultiCharacterRange_370) {
  EXPECT_TRUE(ccb_.AddRange('a', 'z'));
  EXPECT_TRUE(ccb_.Contains('a'));
  EXPECT_TRUE(ccb_.Contains('m'));
  EXPECT_TRUE(ccb_.Contains('z'));
  EXPECT_FALSE(ccb_.Contains('A'));
}

TEST_F(CharClassBuilderTest_370, AddRangeReturnsFalseForDuplicate_370) {
  EXPECT_TRUE(ccb_.AddRange('a', 'z'));
  EXPECT_FALSE(ccb_.AddRange('a', 'z'));
}

TEST_F(CharClassBuilderTest_370, AddSubsetRangeReturnsFalse_370) {
  EXPECT_TRUE(ccb_.AddRange('a', 'z'));
  EXPECT_FALSE(ccb_.AddRange('c', 'f'));
}

TEST_F(CharClassBuilderTest_370, AddRangeReversedReturnsFalse_370) {
  EXPECT_FALSE(ccb_.AddRange('z', 'a'));
}

TEST_F(CharClassBuilderTest_370, AddOverlappingRangesMerge_370) {
  EXPECT_TRUE(ccb_.AddRange('a', 'm'));
  EXPECT_TRUE(ccb_.AddRange('n', 'z'));
  // After merge, the entire a-z should be contained
  EXPECT_TRUE(ccb_.Contains('a'));
  EXPECT_TRUE(ccb_.Contains('z'));
}

TEST_F(CharClassBuilderTest_370, AddAdjacentRangesMerge_370) {
  EXPECT_TRUE(ccb_.AddRange('a', 'f'));
  EXPECT_TRUE(ccb_.AddRange('g', 'z'));
  EXPECT_TRUE(ccb_.Contains('a'));
  EXPECT_TRUE(ccb_.Contains('g'));
  EXPECT_TRUE(ccb_.Contains('z'));
}

TEST_F(CharClassBuilderTest_370, EmptyInitially_370) {
  EXPECT_TRUE(ccb_.empty());
  EXPECT_EQ(ccb_.size(), 0);
}

TEST_F(CharClassBuilderTest_370, NotEmptyAfterAdd_370) {
  ccb_.AddRange('a', 'a');
  EXPECT_FALSE(ccb_.empty());
  EXPECT_EQ(ccb_.size(), 1);
}

TEST_F(CharClassBuilderTest_370, SizeAfterMultipleRanges_370) {
  ccb_.AddRange('a', 'c');
  EXPECT_EQ(ccb_.size(), 3);
  ccb_.AddRange('e', 'g');
  EXPECT_EQ(ccb_.size(), 6);
}

TEST_F(CharClassBuilderTest_370, SizeAfterMergedRanges_370) {
  ccb_.AddRange('a', 'c');
  ccb_.AddRange('d', 'f');
  EXPECT_EQ(ccb_.size(), 6);
}

// Boundary condition tests

TEST_F(CharClassBuilderTest_370, AddRangeWithZero_370) {
  EXPECT_TRUE(ccb_.AddRange(0, 0));
  EXPECT_TRUE(ccb_.Contains(0));
}

TEST_F(CharClassBuilderTest_370, AddRangeWithRunemax_370) {
  EXPECT_TRUE(ccb_.AddRange(Runemax, Runemax));
  EXPECT_TRUE(ccb_.Contains(Runemax));
}

TEST_F(CharClassBuilderTest_370, AddRangeZeroToRunemax_370) {
  EXPECT_TRUE(ccb_.AddRange(0, Runemax));
  EXPECT_TRUE(ccb_.full());
}

TEST_F(CharClassBuilderTest_370, AddSameRangeTwice_370) {
  EXPECT_TRUE(ccb_.AddRange(10, 20));
  EXPECT_FALSE(ccb_.AddRange(10, 20));
  EXPECT_EQ(ccb_.size(), 11);
}

TEST_F(CharClassBuilderTest_370, AddSingleRuneRange_370) {
  EXPECT_TRUE(ccb_.AddRange(42, 42));
  EXPECT_TRUE(ccb_.Contains(42));
  EXPECT_EQ(ccb_.size(), 1);
}

// FoldsASCII tests

TEST_F(CharClassBuilderTest_370, FoldsASCIIWithUpperAndLower_370) {
  ccb_.AddRange('A', 'Z');
  ccb_.AddRange('a', 'z');
  EXPECT_TRUE(ccb_.FoldsASCII());
}

TEST_F(CharClassBuilderTest_370, FoldsASCIIOnlyUpper_370) {
  ccb_.AddRange('A', 'Z');
  // Only uppercase, not folding
  EXPECT_FALSE(ccb_.FoldsASCII());
}

TEST_F(CharClassBuilderTest_370, FoldsASCIIEmpty_370) {
  EXPECT_FALSE(ccb_.FoldsASCII());
}

// Contains tests

TEST_F(CharClassBuilderTest_370, ContainsReturnsFalseOnEmpty_370) {
  EXPECT_FALSE(ccb_.Contains('a'));
}

TEST_F(CharClassBuilderTest_370, ContainsBoundaryOfRange_370) {
  ccb_.AddRange(10, 20);
  EXPECT_TRUE(ccb_.Contains(10));
  EXPECT_TRUE(ccb_.Contains(20));
  EXPECT_FALSE(ccb_.Contains(9));
  EXPECT_FALSE(ccb_.Contains(21));
}

// Copy tests

TEST_F(CharClassBuilderTest_370, CopyCreatesIdenticalBuilder_370) {
  ccb_.AddRange('a', 'z');
  ccb_.AddRange('0', '9');
  CharClassBuilder* copy = ccb_.Copy();
  ASSERT_NE(copy, nullptr);
  EXPECT_TRUE(copy->Contains('a'));
  EXPECT_TRUE(copy->Contains('z'));
  EXPECT_TRUE(copy->Contains('5'));
  EXPECT_EQ(copy->size(), ccb_.size());
  delete copy;
}

// AddCharClass tests

TEST_F(CharClassBuilderTest_370, AddCharClassMerges_370) {
  CharClassBuilder other;
  other.AddRange('a', 'z');
  ccb_.AddRange('0', '9');
  ccb_.AddCharClass(&other);
  EXPECT_TRUE(ccb_.Contains('a'));
  EXPECT_TRUE(ccb_.Contains('5'));
  EXPECT_EQ(ccb_.size(), 36);
}

// Negate tests

TEST_F(CharClassBuilderTest_370, NegateEmptyBecomesFull_370) {
  ccb_.Negate();
  EXPECT_TRUE(ccb_.full());
}

TEST_F(CharClassBuilderTest_370, NegateFullBecomesEmpty_370) {
  ccb_.AddRange(0, Runemax);
  EXPECT_TRUE(ccb_.full());
  ccb_.Negate();
  EXPECT_TRUE(ccb_.empty());
}

TEST_F(CharClassBuilderTest_370, NegateInvertsContainment_370) {
  ccb_.AddRange('a', 'z');
  EXPECT_TRUE(ccb_.Contains('a'));
  EXPECT_FALSE(ccb_.Contains('A'));
  ccb_.Negate();
  EXPECT_FALSE(ccb_.Contains('a'));
  EXPECT_TRUE(ccb_.Contains('A'));
}

// RemoveAbove tests

TEST_F(CharClassBuilderTest_370, RemoveAboveRemovesHigherRunes_370) {
  ccb_.AddRange(0, 1000);
  ccb_.RemoveAbove(500);
  EXPECT_TRUE(ccb_.Contains(500));
  EXPECT_FALSE(ccb_.Contains(501));
  EXPECT_TRUE(ccb_.Contains(0));
}

TEST_F(CharClassBuilderTest_370, RemoveAboveZero_370) {
  ccb_.AddRange(0, 100);
  ccb_.RemoveAbove(0);
  EXPECT_TRUE(ccb_.Contains(0));
  EXPECT_FALSE(ccb_.Contains(1));
  EXPECT_EQ(ccb_.size(), 1);
}

TEST_F(CharClassBuilderTest_370, RemoveAboveOnEmpty_370) {
  ccb_.RemoveAbove(100);
  EXPECT_TRUE(ccb_.empty());
}

// Iterator tests

TEST_F(CharClassBuilderTest_370, BeginEqualsEndWhenEmpty_370) {
  EXPECT_EQ(ccb_.begin(), ccb_.end());
}

TEST_F(CharClassBuilderTest_370, BeginNotEqualsEndAfterAdd_370) {
  ccb_.AddRange('a', 'z');
  EXPECT_NE(ccb_.begin(), ccb_.end());
}

// GetCharClass tests

TEST_F(CharClassBuilderTest_370, GetCharClassReturnsNonNull_370) {
  ccb_.AddRange('a', 'z');
  CharClass* cc = ccb_.GetCharClass();
  ASSERT_NE(cc, nullptr);
  cc->Delete();
}

TEST_F(CharClassBuilderTest_370, GetCharClassEmptyBuilder_370) {
  CharClass* cc = ccb_.GetCharClass();
  ASSERT_NE(cc, nullptr);
  cc->Delete();
}

// Overlapping range merging tests

TEST_F(CharClassBuilderTest_370, OverlappingRangesAreMerged_370) {
  ccb_.AddRange(1, 10);
  ccb_.AddRange(5, 15);
  EXPECT_TRUE(ccb_.Contains(1));
  EXPECT_TRUE(ccb_.Contains(10));
  EXPECT_TRUE(ccb_.Contains(15));
  EXPECT_EQ(ccb_.size(), 15);
}

TEST_F(CharClassBuilderTest_370, ThreeOverlappingRangesMerge_370) {
  ccb_.AddRange(1, 5);
  ccb_.AddRange(10, 15);
  ccb_.AddRange(3, 12);
  EXPECT_TRUE(ccb_.Contains(1));
  EXPECT_TRUE(ccb_.Contains(8));
  EXPECT_TRUE(ccb_.Contains(15));
  EXPECT_EQ(ccb_.size(), 15);
}

TEST_F(CharClassBuilderTest_370, AddRangeHiLessThanLoReturnsFalse_370) {
  EXPECT_FALSE(ccb_.AddRange(100, 50));
  EXPECT_TRUE(ccb_.empty());
}

TEST_F(CharClassBuilderTest_370, FullAfterAddingEntireRange_370) {
  ccb_.AddRange(0, Runemax);
  EXPECT_TRUE(ccb_.full());
  EXPECT_EQ(ccb_.size(), Runemax + 1);
}

TEST_F(CharClassBuilderTest_370, AddSingleUpperCaseLetter_370) {
  EXPECT_TRUE(ccb_.AddRange('A', 'A'));
  EXPECT_TRUE(ccb_.Contains('A'));
  EXPECT_FALSE(ccb_.Contains('a'));
}

TEST_F(CharClassBuilderTest_370, DoubleNegateRestoresOriginal_370) {
  ccb_.AddRange('a', 'z');
  int originalSize = ccb_.size();
  ccb_.Negate();
  ccb_.Negate();
  EXPECT_EQ(ccb_.size(), originalSize);
  EXPECT_TRUE(ccb_.Contains('a'));
  EXPECT_TRUE(ccb_.Contains('z'));
  EXPECT_FALSE(ccb_.Contains('A'));
}

TEST_F(CharClassBuilderTest_370, AddNonAdjacentRanges_370) {
  ccb_.AddRange(10, 20);
  ccb_.AddRange(30, 40);
  EXPECT_TRUE(ccb_.Contains(10));
  EXPECT_TRUE(ccb_.Contains(20));
  EXPECT_FALSE(ccb_.Contains(25));
  EXPECT_TRUE(ccb_.Contains(30));
  EXPECT_TRUE(ccb_.Contains(40));
  EXPECT_EQ(ccb_.size(), 22);
}

TEST_F(CharClassBuilderTest_370, CopyIsIndependent_370) {
  ccb_.AddRange('a', 'z');
  CharClassBuilder* copy = ccb_.Copy();
  copy->AddRange('0', '9');
  EXPECT_FALSE(ccb_.Contains('5'));
  EXPECT_TRUE(copy->Contains('5'));
  delete copy;
}

}  // namespace re2

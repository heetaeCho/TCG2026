#include "gtest/gtest.h"
#include "re2/regexp.h"

namespace re2 {

class CharClassBuilderTest_163 : public ::testing::Test {
 protected:
  CharClassBuilder ccb_;
};

// Test default construction results in empty builder
TEST_F(CharClassBuilderTest_163, DefaultConstructorIsEmpty_163) {
  EXPECT_TRUE(ccb_.empty());
  EXPECT_FALSE(ccb_.full());
  EXPECT_EQ(ccb_.size(), 0);
}

// Test begin == end for empty builder
TEST_F(CharClassBuilderTest_163, EmptyIteratorRange_163) {
  EXPECT_EQ(ccb_.begin(), ccb_.end());
}

// Test adding a single character range
TEST_F(CharClassBuilderTest_163, AddSingleCharacterRange_163) {
  EXPECT_TRUE(ccb_.AddRange('a', 'a'));
  EXPECT_FALSE(ccb_.empty());
  EXPECT_TRUE(ccb_.Contains('a'));
  EXPECT_FALSE(ccb_.Contains('b'));
  EXPECT_EQ(ccb_.size(), 1);
}

// Test adding a range of characters
TEST_F(CharClassBuilderTest_163, AddRangeMultipleChars_163) {
  EXPECT_TRUE(ccb_.AddRange('a', 'z'));
  EXPECT_TRUE(ccb_.Contains('a'));
  EXPECT_TRUE(ccb_.Contains('m'));
  EXPECT_TRUE(ccb_.Contains('z'));
  EXPECT_FALSE(ccb_.Contains('A'));
  EXPECT_FALSE(ccb_.Contains('0'));
}

// Test adding overlapping ranges (second add returns false if no new runes added)
TEST_F(CharClassBuilderTest_163, AddOverlappingRanges_163) {
  EXPECT_TRUE(ccb_.AddRange('a', 'f'));
  // Adding a subset should return false (no new characters added)
  EXPECT_FALSE(ccb_.AddRange('b', 'e'));
}

// Test adding adjacent ranges
TEST_F(CharClassBuilderTest_163, AddAdjacentRanges_163) {
  ccb_.AddRange('a', 'f');
  ccb_.AddRange('g', 'z');
  EXPECT_TRUE(ccb_.Contains('a'));
  EXPECT_TRUE(ccb_.Contains('g'));
  EXPECT_TRUE(ccb_.Contains('z'));
}

// Test Contains returns false for characters not in any range
TEST_F(CharClassBuilderTest_163, ContainsReturnsFalseForAbsent_163) {
  ccb_.AddRange('d', 'f');
  EXPECT_FALSE(ccb_.Contains('a'));
  EXPECT_FALSE(ccb_.Contains('c'));
  EXPECT_FALSE(ccb_.Contains('g'));
  EXPECT_FALSE(ccb_.Contains('z'));
}

// Test Copy creates an independent copy
TEST_F(CharClassBuilderTest_163, CopyIsIndependent_163) {
  ccb_.AddRange('a', 'z');
  CharClassBuilder* copy = ccb_.Copy();
  ASSERT_NE(copy, nullptr);
  EXPECT_TRUE(copy->Contains('a'));
  EXPECT_TRUE(copy->Contains('z'));
  EXPECT_EQ(copy->size(), ccb_.size());

  // Modify original, copy should not be affected
  ccb_.AddRange('0', '9');
  EXPECT_FALSE(copy->Contains('0'));
  EXPECT_TRUE(ccb_.Contains('0'));

  delete copy;
}

// Test Negate inverts the character class
TEST_F(CharClassBuilderTest_163, NegateInverts_163) {
  ccb_.AddRange('a', 'z');
  EXPECT_TRUE(ccb_.Contains('a'));
  EXPECT_FALSE(ccb_.Contains('0'));

  ccb_.Negate();
  EXPECT_FALSE(ccb_.Contains('a'));
  EXPECT_TRUE(ccb_.Contains('0'));
}

// Test Negate on empty produces full
TEST_F(CharClassBuilderTest_163, NegateEmptyProducesFull_163) {
  EXPECT_TRUE(ccb_.empty());
  ccb_.Negate();
  EXPECT_TRUE(ccb_.full());
}

// Test Negate on full produces empty
TEST_F(CharClassBuilderTest_163, NegateFullProducesEmpty_163) {
  ccb_.AddRange(0, 0x10FFFF);  // Rune max
  EXPECT_TRUE(ccb_.full());
  ccb_.Negate();
  EXPECT_TRUE(ccb_.empty());
}

// Test RemoveAbove removes characters above threshold
TEST_F(CharClassBuilderTest_163, RemoveAboveRemovesHigherChars_163) {
  ccb_.AddRange('a', 'z');
  ccb_.RemoveAbove('m');
  EXPECT_TRUE(ccb_.Contains('a'));
  EXPECT_TRUE(ccb_.Contains('m'));
  EXPECT_FALSE(ccb_.Contains('n'));
  EXPECT_FALSE(ccb_.Contains('z'));
}

// Test RemoveAbove with threshold below all ranges
TEST_F(CharClassBuilderTest_163, RemoveAboveBelowAllRanges_163) {
  ccb_.AddRange('m', 'z');
  ccb_.RemoveAbove('a');
  EXPECT_FALSE(ccb_.Contains('m'));
  EXPECT_FALSE(ccb_.Contains('z'));
}

// Test AddCharClass merges another builder
TEST_F(CharClassBuilderTest_163, AddCharClassMerges_163) {
  ccb_.AddRange('a', 'f');

  CharClassBuilder other;
  other.AddRange('g', 'z');

  ccb_.AddCharClass(&other);
  EXPECT_TRUE(ccb_.Contains('a'));
  EXPECT_TRUE(ccb_.Contains('f'));
  EXPECT_TRUE(ccb_.Contains('g'));
  EXPECT_TRUE(ccb_.Contains('z'));
}

// Test full() after adding full Unicode range
TEST_F(CharClassBuilderTest_163, FullAfterAddingAllRunes_163) {
  ccb_.AddRange(0, 0x10FFFF);
  EXPECT_TRUE(ccb_.full());
  EXPECT_FALSE(ccb_.empty());
}

// Test size reflects number of ranges
TEST_F(CharClassBuilderTest_163, SizeReflectsRangeCount_163) {
  EXPECT_EQ(ccb_.size(), 0);
  ccb_.AddRange('a', 'c');
  EXPECT_EQ(ccb_.size(), 1);
  ccb_.AddRange('e', 'g');
  EXPECT_EQ(ccb_.size(), 2);
  // Adding adjacent range should merge
  ccb_.AddRange('d', 'd');
  EXPECT_EQ(ccb_.size(), 1);
}

// Test iterator traversal
TEST_F(CharClassBuilderTest_163, IteratorTraversal_163) {
  ccb_.AddRange('a', 'c');
  ccb_.AddRange('x', 'z');
  int count = 0;
  for (auto it = ccb_.begin(); it != ccb_.end(); ++it) {
    count++;
  }
  EXPECT_EQ(count, 2);
}

// Test FoldsASCII
TEST_F(CharClassBuilderTest_163, FoldsASCIIForLowercase_163) {
  // Adding 'a'-'z' and 'A'-'Z' should fold ASCII
  ccb_.AddRange('a', 'z');
  ccb_.AddRange('A', 'Z');
  // FoldsASCII checks if the class includes both cases for all ASCII letters present
  EXPECT_TRUE(ccb_.FoldsASCII());
}

// Test FoldsASCII returns false for partial case
TEST_F(CharClassBuilderTest_163, FoldsASCIIPartialCaseFalse_163) {
  ccb_.AddRange('a', 'z');
  // Only lowercase, no uppercase
  EXPECT_FALSE(ccb_.FoldsASCII());
}

// Test FoldsASCII on empty
TEST_F(CharClassBuilderTest_163, FoldsASCIIOnEmpty_163) {
  // Empty class trivially folds
  EXPECT_FALSE(ccb_.FoldsASCII());
}

// Test GetCharClass returns non-null
TEST_F(CharClassBuilderTest_163, GetCharClassReturnsNonNull_163) {
  ccb_.AddRange('a', 'z');
  CharClass* cc = ccb_.GetCharClass();
  ASSERT_NE(cc, nullptr);
  cc->Delete();
}

// Test GetCharClass on empty builder
TEST_F(CharClassBuilderTest_163, GetCharClassOnEmpty_163) {
  CharClass* cc = ccb_.GetCharClass();
  ASSERT_NE(cc, nullptr);
  cc->Delete();
}

// Test AddRange with lo > hi (boundary condition)
TEST_F(CharClassBuilderTest_163, AddRangeLoGreaterThanHi_163) {
  // When lo > hi, the range is invalid and should not add anything
  EXPECT_FALSE(ccb_.AddRange('z', 'a'));
  EXPECT_TRUE(ccb_.empty());
}

// Test AddRange with lo == hi (single rune)
TEST_F(CharClassBuilderTest_163, AddRangeSingleRune_163) {
  EXPECT_TRUE(ccb_.AddRange('m', 'm'));
  EXPECT_TRUE(ccb_.Contains('m'));
  EXPECT_FALSE(ccb_.Contains('l'));
  EXPECT_FALSE(ccb_.Contains('n'));
  EXPECT_EQ(ccb_.size(), 1);
}

// Test AddRange with Rune 0
TEST_F(CharClassBuilderTest_163, AddRangeIncludingZero_163) {
  ccb_.AddRange(0, 10);
  EXPECT_TRUE(ccb_.Contains(0));
  EXPECT_TRUE(ccb_.Contains(5));
  EXPECT_TRUE(ccb_.Contains(10));
  EXPECT_FALSE(ccb_.Contains(11));
}

// Test RemoveAbove on empty
TEST_F(CharClassBuilderTest_163, RemoveAboveOnEmpty_163) {
  ccb_.RemoveAbove('z');
  EXPECT_TRUE(ccb_.empty());
}

// Test AddCharClass with empty other
TEST_F(CharClassBuilderTest_163, AddCharClassWithEmpty_163) {
  ccb_.AddRange('a', 'z');
  int original_size = ccb_.size();

  CharClassBuilder empty_builder;
  ccb_.AddCharClass(&empty_builder);

  EXPECT_EQ(ccb_.size(), original_size);
}

// Test double negate returns to original
TEST_F(CharClassBuilderTest_163, DoubleNegateReturnsOriginal_163) {
  ccb_.AddRange('a', 'z');
  CharClassBuilder* original = ccb_.Copy();

  ccb_.Negate();
  ccb_.Negate();

  // Should match original
  EXPECT_TRUE(ccb_.Contains('a'));
  EXPECT_TRUE(ccb_.Contains('z'));
  EXPECT_FALSE(ccb_.Contains('0'));

  delete original;
}

// Test adding non-ASCII (Unicode) ranges
TEST_F(CharClassBuilderTest_163, AddUnicodeRange_163) {
  ccb_.AddRange(0x4E00, 0x9FFF);  // CJK Unified Ideographs
  EXPECT_TRUE(ccb_.Contains(0x4E00));
  EXPECT_TRUE(ccb_.Contains(0x9FFF));
  EXPECT_TRUE(ccb_.Contains(0x5000));
  EXPECT_FALSE(ccb_.Contains(0x4DFF));
  EXPECT_FALSE(ccb_.Contains(0xA000));
}

// Test RemoveAbove at exactly the boundary of a range
TEST_F(CharClassBuilderTest_163, RemoveAboveAtRangeBoundary_163) {
  ccb_.AddRange('a', 'z');
  ccb_.RemoveAbove('z');
  EXPECT_TRUE(ccb_.Contains('z'));
  EXPECT_TRUE(ccb_.Contains('a'));
}

// Test RemoveAbove at Rune 0
TEST_F(CharClassBuilderTest_163, RemoveAboveAtZero_163) {
  ccb_.AddRange(0, 100);
  ccb_.RemoveAbove(0);
  EXPECT_TRUE(ccb_.Contains(0));
  EXPECT_FALSE(ccb_.Contains(1));
}

}  // namespace re2

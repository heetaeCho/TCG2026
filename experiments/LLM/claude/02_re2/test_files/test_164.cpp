#include "gtest/gtest.h"
#include "re2/regexp.h"

namespace re2 {

class CharClassBuilderTest_164 : public ::testing::Test {
 protected:
  CharClassBuilder ccb_;
};

// Test default construction results in empty builder
TEST_F(CharClassBuilderTest_164, DefaultConstructionIsEmpty_164) {
  EXPECT_TRUE(ccb_.empty());
  EXPECT_FALSE(ccb_.full());
  EXPECT_EQ(ccb_.size(), 0);
}

// Test begin == end for empty builder
TEST_F(CharClassBuilderTest_164, EmptyBuilderBeginEqualsEnd_164) {
  EXPECT_EQ(ccb_.begin(), ccb_.end());
}

// Test adding a single character range
TEST_F(CharClassBuilderTest_164, AddSingleCharacterRange_164) {
  EXPECT_TRUE(ccb_.AddRange('a', 'a'));
  EXPECT_FALSE(ccb_.empty());
  EXPECT_TRUE(ccb_.Contains('a'));
  EXPECT_FALSE(ccb_.Contains('b'));
  EXPECT_EQ(ccb_.size(), 1);
}

// Test adding a range of characters
TEST_F(CharClassBuilderTest_164, AddRangeOfCharacters_164) {
  ccb_.AddRange('a', 'z');
  EXPECT_TRUE(ccb_.Contains('a'));
  EXPECT_TRUE(ccb_.Contains('m'));
  EXPECT_TRUE(ccb_.Contains('z'));
  EXPECT_FALSE(ccb_.Contains('A'));
  EXPECT_FALSE(ccb_.Contains('0'));
}

// Test Contains returns false for characters not added
TEST_F(CharClassBuilderTest_164, ContainsReturnsFalseForAbsent_164) {
  ccb_.AddRange('a', 'f');
  EXPECT_FALSE(ccb_.Contains('g'));
  EXPECT_FALSE(ccb_.Contains('z'));
  EXPECT_FALSE(ccb_.Contains(0));
}

// Test adding overlapping ranges
TEST_F(CharClassBuilderTest_164, AddOverlappingRanges_164) {
  ccb_.AddRange('a', 'm');
  ccb_.AddRange('h', 'z');
  EXPECT_TRUE(ccb_.Contains('a'));
  EXPECT_TRUE(ccb_.Contains('h'));
  EXPECT_TRUE(ccb_.Contains('z'));
}

// Test adding adjacent ranges
TEST_F(CharClassBuilderTest_164, AddAdjacentRanges_164) {
  ccb_.AddRange('a', 'f');
  ccb_.AddRange('g', 'z');
  EXPECT_TRUE(ccb_.Contains('a'));
  EXPECT_TRUE(ccb_.Contains('f'));
  EXPECT_TRUE(ccb_.Contains('g'));
  EXPECT_TRUE(ccb_.Contains('z'));
}

// Test adding duplicate range returns false (already present)
TEST_F(CharClassBuilderTest_164, AddDuplicateRange_164) {
  EXPECT_TRUE(ccb_.AddRange('a', 'z'));
  // Adding the same range again - the entire range is already present
  EXPECT_FALSE(ccb_.AddRange('a', 'z'));
}

// Test Negate on empty set makes full
TEST_F(CharClassBuilderTest_164, NegateEmptyMakesFull_164) {
  ccb_.Negate();
  EXPECT_TRUE(ccb_.full());
  EXPECT_FALSE(ccb_.empty());
}

// Test Negate on full set makes empty
TEST_F(CharClassBuilderTest_164, NegateFullMakesEmpty_164) {
  ccb_.Negate();  // now full
  ccb_.Negate();  // now empty again
  EXPECT_TRUE(ccb_.empty());
}

// Test Negate makes characters that were absent now present
TEST_F(CharClassBuilderTest_164, NegateSwapsContains_164) {
  ccb_.AddRange('a', 'z');
  EXPECT_TRUE(ccb_.Contains('a'));
  EXPECT_FALSE(ccb_.Contains('A'));
  ccb_.Negate();
  EXPECT_FALSE(ccb_.Contains('a'));
  EXPECT_TRUE(ccb_.Contains('A'));
}

// Test RemoveAbove removes characters above given rune
TEST_F(CharClassBuilderTest_164, RemoveAbove_164) {
  ccb_.AddRange('a', 'z');
  ccb_.RemoveAbove('m');
  EXPECT_TRUE(ccb_.Contains('a'));
  EXPECT_TRUE(ccb_.Contains('m'));
  EXPECT_FALSE(ccb_.Contains('n'));
  EXPECT_FALSE(ccb_.Contains('z'));
}

// Test RemoveAbove with value above all added ranges has no effect
TEST_F(CharClassBuilderTest_164, RemoveAboveHighValue_164) {
  ccb_.AddRange('a', 'z');
  ccb_.RemoveAbove(0x10FFFF);
  EXPECT_TRUE(ccb_.Contains('a'));
  EXPECT_TRUE(ccb_.Contains('z'));
}

// Test RemoveAbove with 0 removes everything except possibly rune 0
TEST_F(CharClassBuilderTest_164, RemoveAboveZero_164) {
  ccb_.AddRange('a', 'z');
  ccb_.RemoveAbove(0);
  EXPECT_FALSE(ccb_.Contains('a'));
  EXPECT_FALSE(ccb_.Contains('z'));
}

// Test Copy creates independent copy
TEST_F(CharClassBuilderTest_164, CopyCreatesIndependentCopy_164) {
  ccb_.AddRange('a', 'z');
  CharClassBuilder* copy = ccb_.Copy();
  ASSERT_NE(copy, nullptr);
  EXPECT_TRUE(copy->Contains('a'));
  EXPECT_TRUE(copy->Contains('z'));

  // Modify original, copy should be unaffected
  ccb_.AddRange('0', '9');
  EXPECT_FALSE(copy->Contains('0'));

  delete copy;
}

// Test AddCharClass merges another builder's ranges
TEST_F(CharClassBuilderTest_164, AddCharClass_164) {
  CharClassBuilder other;
  other.AddRange('0', '9');
  ccb_.AddRange('a', 'z');
  ccb_.AddCharClass(&other);
  EXPECT_TRUE(ccb_.Contains('a'));
  EXPECT_TRUE(ccb_.Contains('z'));
  EXPECT_TRUE(ccb_.Contains('0'));
  EXPECT_TRUE(ccb_.Contains('9'));
}

// Test size after adding disjoint ranges
TEST_F(CharClassBuilderTest_164, SizeWithDisjointRanges_164) {
  ccb_.AddRange('a', 'f');
  ccb_.AddRange('x', 'z');
  EXPECT_EQ(ccb_.size(), 2);
}

// Test FoldsASCII
TEST_F(CharClassBuilderTest_164, FoldsASCIIWithLowercaseOnly_164) {
  ccb_.AddRange('a', 'z');
  // FoldsASCII checks if the class includes both cases of ASCII letters
  // With only lowercase, it should not fold
  bool result = ccb_.FoldsASCII();
  // We just check it returns a boolean without crashing
  (void)result;
}

TEST_F(CharClassBuilderTest_164, FoldsASCIIWithBothCases_164) {
  ccb_.AddRange('A', 'Z');
  ccb_.AddRange('a', 'z');
  bool result = ccb_.FoldsASCII();
  EXPECT_TRUE(result);
}

// Test GetCharClass returns non-null
TEST_F(CharClassBuilderTest_164, GetCharClassReturnsNonNull_164) {
  ccb_.AddRange('a', 'z');
  CharClass* cc = ccb_.GetCharClass();
  ASSERT_NE(cc, nullptr);
  cc->Delete();
}

// Test GetCharClass on empty builder
TEST_F(CharClassBuilderTest_164, GetCharClassOnEmpty_164) {
  CharClass* cc = ccb_.GetCharClass();
  ASSERT_NE(cc, nullptr);
  cc->Delete();
}

// Test full after adding entire Unicode range
TEST_F(CharClassBuilderTest_164, FullAfterAddingEntireRange_164) {
  ccb_.AddRange(0, 0x10FFFF);
  EXPECT_TRUE(ccb_.full());
}

// Test iteration over ranges
TEST_F(CharClassBuilderTest_164, IterateOverRanges_164) {
  ccb_.AddRange('a', 'f');
  ccb_.AddRange('x', 'z');
  int count = 0;
  for (auto it = ccb_.begin(); it != ccb_.end(); ++it) {
    count++;
  }
  EXPECT_EQ(count, 2);
}

// Test AddRange with lo > hi (invalid range)
TEST_F(CharClassBuilderTest_164, AddRangeInvalidLoGtHi_164) {
  // When lo > hi, nothing should be added
  ccb_.AddRange('z', 'a');
  EXPECT_TRUE(ccb_.empty());
}

// Test AddRangeFlags with no special flags
TEST_F(CharClassBuilderTest_164, AddRangeFlags_164) {
  ccb_.AddRangeFlags('a', 'z', Regexp::FoldCase);
  // With FoldCase, uppercase equivalents should also be added
  EXPECT_TRUE(ccb_.Contains('a'));
  EXPECT_TRUE(ccb_.Contains('A'));
  EXPECT_TRUE(ccb_.Contains('z'));
  EXPECT_TRUE(ccb_.Contains('Z'));
}

// Test AddRangeFlags without FoldCase
TEST_F(CharClassBuilderTest_164, AddRangeFlagsNoFold_164) {
  ccb_.AddRangeFlags('a', 'z', Regexp::NoParseFlags);
  EXPECT_TRUE(ccb_.Contains('a'));
  EXPECT_TRUE(ccb_.Contains('z'));
  EXPECT_FALSE(ccb_.Contains('A'));
}

// Test empty after RemoveAbove removes all content
TEST_F(CharClassBuilderTest_164, EmptyAfterRemoveAboveAll_164) {
  ccb_.AddRange('a', 'z');
  ccb_.RemoveAbove('a' - 1);
  EXPECT_TRUE(ccb_.empty());
}

// Test Copy of empty builder
TEST_F(CharClassBuilderTest_164, CopyEmptyBuilder_164) {
  CharClassBuilder* copy = ccb_.Copy();
  ASSERT_NE(copy, nullptr);
  EXPECT_TRUE(copy->empty());
  EXPECT_EQ(copy->size(), 0);
  delete copy;
}

// Test AddCharClass with empty other
TEST_F(CharClassBuilderTest_164, AddEmptyCharClass_164) {
  ccb_.AddRange('a', 'z');
  CharClassBuilder empty_cc;
  ccb_.AddCharClass(&empty_cc);
  EXPECT_TRUE(ccb_.Contains('a'));
  EXPECT_TRUE(ccb_.Contains('z'));
  EXPECT_EQ(ccb_.size(), 1);
}

// Test Contains on boundary rune values
TEST_F(CharClassBuilderTest_164, ContainsBoundaryRunes_164) {
  ccb_.AddRange(0, 0);
  EXPECT_TRUE(ccb_.Contains(0));
  EXPECT_FALSE(ccb_.Contains(1));
}

// Test adding Unicode range
TEST_F(CharClassBuilderTest_164, AddUnicodeRange_164) {
  ccb_.AddRange(0x4E00, 0x9FFF);  // CJK Unified Ideographs
  EXPECT_TRUE(ccb_.Contains(0x4E00));
  EXPECT_TRUE(ccb_.Contains(0x9FFF));
  EXPECT_FALSE(ccb_.Contains(0x4DFF));
  EXPECT_FALSE(ccb_.Contains(0xA000));
}

// Test Negate twice returns to original
TEST_F(CharClassBuilderTest_164, DoubleNegateRestoresOriginal_164) {
  ccb_.AddRange('a', 'z');
  ccb_.Negate();
  ccb_.Negate();
  EXPECT_TRUE(ccb_.Contains('a'));
  EXPECT_TRUE(ccb_.Contains('z'));
  EXPECT_FALSE(ccb_.Contains('A'));
}

}  // namespace re2

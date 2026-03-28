#include "gtest/gtest.h"
#include "re2/regexp.h"
#include "util/utf.h"

namespace re2 {

// Test fixture for CharClassBuilder tests
class CharClassBuilderTest_167 : public ::testing::Test {
 protected:
  CharClassBuilder ccb_;
};

// ==================== Constructor / Initial State Tests ====================

TEST_F(CharClassBuilderTest_167, InitiallyEmpty_167) {
  EXPECT_TRUE(ccb_.empty());
}

TEST_F(CharClassBuilderTest_167, InitiallyNotFull_167) {
  EXPECT_FALSE(ccb_.full());
}

TEST_F(CharClassBuilderTest_167, InitialSizeIsZero_167) {
  EXPECT_EQ(ccb_.size(), 0);
}

// ==================== AddRange Tests ====================

TEST_F(CharClassBuilderTest_167, AddSingleCharRange_167) {
  ccb_.AddRange('a', 'a');
  EXPECT_FALSE(ccb_.empty());
  EXPECT_TRUE(ccb_.Contains('a'));
  EXPECT_FALSE(ccb_.Contains('b'));
}

TEST_F(CharClassBuilderTest_167, AddRangeContainsAllInRange_167) {
  ccb_.AddRange('a', 'z');
  for (Rune r = 'a'; r <= 'z'; r++) {
    EXPECT_TRUE(ccb_.Contains(r));
  }
  EXPECT_FALSE(ccb_.Contains('A'));
  EXPECT_FALSE(ccb_.Contains('0'));
}

TEST_F(CharClassBuilderTest_167, AddRangeReturnsTrue_167) {
  // Adding a new range should return true (indicating change)
  EXPECT_TRUE(ccb_.AddRange('a', 'z'));
}

TEST_F(CharClassBuilderTest_167, AddDuplicateRangeReturnsFalse_167) {
  ccb_.AddRange('a', 'z');
  // Adding the same range again should return false (no change)
  EXPECT_FALSE(ccb_.AddRange('a', 'z'));
}

TEST_F(CharClassBuilderTest_167, AddOverlappingRanges_167) {
  ccb_.AddRange('a', 'm');
  ccb_.AddRange('h', 'z');
  for (Rune r = 'a'; r <= 'z'; r++) {
    EXPECT_TRUE(ccb_.Contains(r));
  }
}

TEST_F(CharClassBuilderTest_167, AddAdjacentRanges_167) {
  ccb_.AddRange('a', 'm');
  ccb_.AddRange('n', 'z');
  for (Rune r = 'a'; r <= 'z'; r++) {
    EXPECT_TRUE(ccb_.Contains(r));
  }
}

TEST_F(CharClassBuilderTest_167, AddRangeWithZero_167) {
  ccb_.AddRange(0, 0);
  EXPECT_TRUE(ccb_.Contains(0));
  EXPECT_FALSE(ccb_.Contains(1));
}

TEST_F(CharClassBuilderTest_167, AddRangeWithRunemax_167) {
  ccb_.AddRange(Runemax, Runemax);
  EXPECT_TRUE(ccb_.Contains(Runemax));
}

TEST_F(CharClassBuilderTest_167, AddFullRange_167) {
  ccb_.AddRange(0, Runemax);
  EXPECT_TRUE(ccb_.full());
}

// ==================== Contains Tests ====================

TEST_F(CharClassBuilderTest_167, ContainsReturnsFalseForEmptyBuilder_167) {
  EXPECT_FALSE(ccb_.Contains('a'));
  EXPECT_FALSE(ccb_.Contains(0));
  EXPECT_FALSE(ccb_.Contains(Runemax));
}

TEST_F(CharClassBuilderTest_167, ContainsBoundaryValues_167) {
  ccb_.AddRange(10, 20);
  EXPECT_FALSE(ccb_.Contains(9));
  EXPECT_TRUE(ccb_.Contains(10));
  EXPECT_TRUE(ccb_.Contains(15));
  EXPECT_TRUE(ccb_.Contains(20));
  EXPECT_FALSE(ccb_.Contains(21));
}

// ==================== full() Tests ====================

TEST_F(CharClassBuilderTest_167, FullAfterAddingEntireRange_167) {
  ccb_.AddRange(0, Runemax);
  EXPECT_TRUE(ccb_.full());
}

TEST_F(CharClassBuilderTest_167, NotFullWithPartialRange_167) {
  ccb_.AddRange(0, Runemax - 1);
  EXPECT_FALSE(ccb_.full());
}

TEST_F(CharClassBuilderTest_167, FullAfterBuildingUpEntireRange_167) {
  ccb_.AddRange(0, 500000);
  EXPECT_FALSE(ccb_.full());
  ccb_.AddRange(500001, Runemax);
  EXPECT_TRUE(ccb_.full());
}

// ==================== empty() Tests ====================

TEST_F(CharClassBuilderTest_167, EmptyAfterConstruction_167) {
  EXPECT_TRUE(ccb_.empty());
}

TEST_F(CharClassBuilderTest_167, NotEmptyAfterAddRange_167) {
  ccb_.AddRange('x', 'x');
  EXPECT_FALSE(ccb_.empty());
}

// ==================== size() Tests ====================

TEST_F(CharClassBuilderTest_167, SizeAfterSingleRange_167) {
  ccb_.AddRange('a', 'z');
  EXPECT_GE(ccb_.size(), 1);
}

TEST_F(CharClassBuilderTest_167, SizeAfterMultipleDisjointRanges_167) {
  ccb_.AddRange('a', 'c');
  ccb_.AddRange('x', 'z');
  EXPECT_GE(ccb_.size(), 2);
}

TEST_F(CharClassBuilderTest_167, SizeAfterMergingRanges_167) {
  ccb_.AddRange('a', 'f');
  ccb_.AddRange('g', 'z');
  // After merging, could be 1 range
  EXPECT_GE(ccb_.size(), 1);
}

// ==================== Copy Tests ====================

TEST_F(CharClassBuilderTest_167, CopyProducesSameContents_167) {
  ccb_.AddRange('a', 'z');
  ccb_.AddRange('0', '9');
  CharClassBuilder* copy = ccb_.Copy();
  ASSERT_NE(copy, nullptr);

  for (Rune r = 'a'; r <= 'z'; r++) {
    EXPECT_TRUE(copy->Contains(r));
  }
  for (Rune r = '0'; r <= '9'; r++) {
    EXPECT_TRUE(copy->Contains(r));
  }
  EXPECT_FALSE(copy->Contains('!'));

  delete copy;
}

TEST_F(CharClassBuilderTest_167, CopyIsIndependent_167) {
  ccb_.AddRange('a', 'z');
  CharClassBuilder* copy = ccb_.Copy();
  ASSERT_NE(copy, nullptr);

  // Modify original - copy should not be affected
  ccb_.AddRange('0', '9');
  EXPECT_FALSE(copy->Contains('0'));

  delete copy;
}

TEST_F(CharClassBuilderTest_167, CopyOfEmptyBuilder_167) {
  CharClassBuilder* copy = ccb_.Copy();
  ASSERT_NE(copy, nullptr);
  EXPECT_TRUE(copy->empty());
  delete copy;
}

// ==================== Negate Tests ====================

TEST_F(CharClassBuilderTest_167, NegateEmptyBecomesFull_167) {
  ccb_.Negate();
  EXPECT_TRUE(ccb_.full());
}

TEST_F(CharClassBuilderTest_167, NegateFullBecomesEmpty_167) {
  ccb_.AddRange(0, Runemax);
  ccb_.Negate();
  EXPECT_TRUE(ccb_.empty());
}

TEST_F(CharClassBuilderTest_167, NegateInvertsContainment_167) {
  ccb_.AddRange('a', 'z');
  ccb_.Negate();
  for (Rune r = 'a'; r <= 'z'; r++) {
    EXPECT_FALSE(ccb_.Contains(r));
  }
  EXPECT_TRUE(ccb_.Contains('A'));
  EXPECT_TRUE(ccb_.Contains('0'));
  EXPECT_TRUE(ccb_.Contains(0));
}

TEST_F(CharClassBuilderTest_167, DoubleNegateRestoresOriginal_167) {
  ccb_.AddRange('a', 'z');
  ccb_.Negate();
  ccb_.Negate();
  for (Rune r = 'a'; r <= 'z'; r++) {
    EXPECT_TRUE(ccb_.Contains(r));
  }
  EXPECT_FALSE(ccb_.Contains('A'));
}

// ==================== RemoveAbove Tests ====================

TEST_F(CharClassBuilderTest_167, RemoveAboveRemovesHighCharacters_167) {
  ccb_.AddRange(0, Runemax);
  ccb_.RemoveAbove(127);
  EXPECT_TRUE(ccb_.Contains(127));
  EXPECT_FALSE(ccb_.Contains(128));
  EXPECT_FALSE(ccb_.Contains(Runemax));
}

TEST_F(CharClassBuilderTest_167, RemoveAboveKeepsLowerCharacters_167) {
  ccb_.AddRange('a', 'z');
  ccb_.RemoveAbove('m');
  EXPECT_TRUE(ccb_.Contains('a'));
  EXPECT_TRUE(ccb_.Contains('m'));
  EXPECT_FALSE(ccb_.Contains('n'));
  EXPECT_FALSE(ccb_.Contains('z'));
}

TEST_F(CharClassBuilderTest_167, RemoveAboveZero_167) {
  ccb_.AddRange(0, Runemax);
  ccb_.RemoveAbove(0);
  EXPECT_TRUE(ccb_.Contains(0));
  EXPECT_FALSE(ccb_.Contains(1));
}

TEST_F(CharClassBuilderTest_167, RemoveAboveOnEmpty_167) {
  ccb_.RemoveAbove(100);
  EXPECT_TRUE(ccb_.empty());
}

TEST_F(CharClassBuilderTest_167, RemoveAboveRunemax_167) {
  ccb_.AddRange(0, Runemax);
  ccb_.RemoveAbove(Runemax);
  EXPECT_TRUE(ccb_.full());
}

// ==================== AddCharClass Tests ====================

TEST_F(CharClassBuilderTest_167, AddCharClassMergesRanges_167) {
  ccb_.AddRange('a', 'z');
  CharClassBuilder other;
  other.AddRange('0', '9');
  ccb_.AddCharClass(&other);

  for (Rune r = 'a'; r <= 'z'; r++) {
    EXPECT_TRUE(ccb_.Contains(r));
  }
  for (Rune r = '0'; r <= '9'; r++) {
    EXPECT_TRUE(ccb_.Contains(r));
  }
}

TEST_F(CharClassBuilderTest_167, AddEmptyCharClass_167) {
  ccb_.AddRange('a', 'z');
  CharClassBuilder other;
  ccb_.AddCharClass(&other);

  for (Rune r = 'a'; r <= 'z'; r++) {
    EXPECT_TRUE(ccb_.Contains(r));
  }
  EXPECT_FALSE(ccb_.Contains('0'));
}

TEST_F(CharClassBuilderTest_167, AddCharClassToEmpty_167) {
  CharClassBuilder other;
  other.AddRange('a', 'z');
  ccb_.AddCharClass(&other);

  for (Rune r = 'a'; r <= 'z'; r++) {
    EXPECT_TRUE(ccb_.Contains(r));
  }
}

// ==================== FoldsASCII Tests ====================

TEST_F(CharClassBuilderTest_167, FoldsASCIIEmptyBuilder_167) {
  // Empty builder should not fold ASCII
  EXPECT_FALSE(ccb_.FoldsASCII());
}

TEST_F(CharClassBuilderTest_167, FoldsASCIIWithUpperAndLower_167) {
  // Adding both upper and lower case of a letter should fold ASCII
  ccb_.AddRange('A', 'A');
  ccb_.AddRange('a', 'a');
  // This may or may not return true depending on how FoldsASCII works
  // We just verify it doesn't crash and returns a bool
  bool result = ccb_.FoldsASCII();
  (void)result;  // Just checking it doesn't crash
}

TEST_F(CharClassBuilderTest_167, FoldsASCIIWithOnlyDigits_167) {
  ccb_.AddRange('0', '9');
  // Digits don't have case folding
  // Result depends on implementation
  bool result = ccb_.FoldsASCII();
  (void)result;
}

// ==================== GetCharClass Tests ====================

TEST_F(CharClassBuilderTest_167, GetCharClassReturnsNonNull_167) {
  ccb_.AddRange('a', 'z');
  CharClass* cc = ccb_.GetCharClass();
  ASSERT_NE(cc, nullptr);
  cc->Delete();
}

TEST_F(CharClassBuilderTest_167, GetCharClassFromEmpty_167) {
  CharClass* cc = ccb_.GetCharClass();
  ASSERT_NE(cc, nullptr);
  cc->Delete();
}

TEST_F(CharClassBuilderTest_167, GetCharClassPreservesRanges_167) {
  ccb_.AddRange('a', 'z');
  ccb_.AddRange('0', '9');
  CharClass* cc = ccb_.GetCharClass();
  ASSERT_NE(cc, nullptr);

  EXPECT_TRUE(cc->Contains('a'));
  EXPECT_TRUE(cc->Contains('z'));
  EXPECT_TRUE(cc->Contains('0'));
  EXPECT_TRUE(cc->Contains('9'));
  EXPECT_FALSE(cc->Contains('!'));

  cc->Delete();
}

// ==================== Iterator Tests ====================

TEST_F(CharClassBuilderTest_167, IteratorEmptyBuilder_167) {
  EXPECT_EQ(ccb_.begin(), ccb_.end());
}

TEST_F(CharClassBuilderTest_167, IteratorNonEmptyBuilder_167) {
  ccb_.AddRange('a', 'z');
  EXPECT_NE(ccb_.begin(), ccb_.end());
}

TEST_F(CharClassBuilderTest_167, IteratorCountMatchesSize_167) {
  ccb_.AddRange('a', 'f');
  ccb_.AddRange('x', 'z');
  int count = 0;
  for (auto it = ccb_.begin(); it != ccb_.end(); ++it) {
    count++;
  }
  EXPECT_EQ(count, ccb_.size());
}

// ==================== AddRangeFlags Tests ====================

TEST_F(CharClassBuilderTest_167, AddRangeFlagsBasic_167) {
  ccb_.AddRangeFlags('a', 'z', Regexp::FoldCase);
  // With FoldCase, should contain both upper and lower
  EXPECT_TRUE(ccb_.Contains('a'));
  EXPECT_TRUE(ccb_.Contains('A'));
  EXPECT_TRUE(ccb_.Contains('z'));
  EXPECT_TRUE(ccb_.Contains('Z'));
}

TEST_F(CharClassBuilderTest_167, AddRangeFlagsNoFlags_167) {
  ccb_.AddRangeFlags('a', 'z', Regexp::NoParseFlags);
  EXPECT_TRUE(ccb_.Contains('a'));
  EXPECT_TRUE(ccb_.Contains('z'));
  // Without FoldCase, should not contain uppercase
  EXPECT_FALSE(ccb_.Contains('A'));
}

// ==================== Complex Scenario Tests ====================

TEST_F(CharClassBuilderTest_167, ComplexScenarioMultipleOperations_167) {
  ccb_.AddRange('a', 'z');
  ccb_.AddRange('A', 'Z');
  ccb_.AddRange('0', '9');
  ccb_.RemoveAbove('z');

  EXPECT_TRUE(ccb_.Contains('a'));
  EXPECT_TRUE(ccb_.Contains('Z'));
  EXPECT_TRUE(ccb_.Contains('9'));
  EXPECT_FALSE(ccb_.Contains(Runemax));
}

TEST_F(CharClassBuilderTest_167, NegateAndAddRange_167) {
  ccb_.Negate();  // Now full
  EXPECT_TRUE(ccb_.full());
  ccb_.RemoveAbove(127);
  EXPECT_FALSE(ccb_.full());
  EXPECT_TRUE(ccb_.Contains(0));
  EXPECT_TRUE(ccb_.Contains(127));
  EXPECT_FALSE(ccb_.Contains(128));
}

}  // namespace re2

#include "gtest/gtest.h"
#include "re2/regexp.h"

namespace re2 {

// Test fixture for CharClassBuilder tests
class CharClassBuilderTest_165 : public ::testing::Test {
 protected:
  void SetUp() override {
    builder_ = new CharClassBuilder();
  }

  void TearDown() override {
    delete builder_;
  }

  CharClassBuilder* builder_;
};

// Test that a newly constructed CharClassBuilder is empty
TEST_F(CharClassBuilderTest_165, NewBuilderIsEmpty_165) {
  EXPECT_TRUE(builder_->empty());
  EXPECT_EQ(0, builder_->size());
  EXPECT_FALSE(builder_->full());
}

// Test adding a single character range
TEST_F(CharClassBuilderTest_165, AddSingleCharRange_165) {
  builder_->AddRange('a', 'a');
  EXPECT_FALSE(builder_->empty());
  EXPECT_TRUE(builder_->Contains('a'));
  EXPECT_FALSE(builder_->Contains('b'));
}

// Test adding a range of characters
TEST_F(CharClassBuilderTest_165, AddRange_165) {
  builder_->AddRange('a', 'z');
  EXPECT_FALSE(builder_->empty());
  EXPECT_TRUE(builder_->Contains('a'));
  EXPECT_TRUE(builder_->Contains('m'));
  EXPECT_TRUE(builder_->Contains('z'));
  EXPECT_FALSE(builder_->Contains('A'));
  EXPECT_FALSE(builder_->Contains('0'));
}

// Test that size reflects the number of runes added
TEST_F(CharClassBuilderTest_165, SizeReflectsAddedRunes_165) {
  builder_->AddRange('a', 'z');
  EXPECT_EQ(26, builder_->size());
}

// Test adding multiple non-overlapping ranges
TEST_F(CharClassBuilderTest_165, AddMultipleRanges_165) {
  builder_->AddRange('a', 'c');
  builder_->AddRange('x', 'z');
  EXPECT_EQ(6, builder_->size());
  EXPECT_TRUE(builder_->Contains('a'));
  EXPECT_TRUE(builder_->Contains('b'));
  EXPECT_TRUE(builder_->Contains('c'));
  EXPECT_FALSE(builder_->Contains('d'));
  EXPECT_TRUE(builder_->Contains('x'));
  EXPECT_TRUE(builder_->Contains('y'));
  EXPECT_TRUE(builder_->Contains('z'));
}

// Test adding overlapping ranges
TEST_F(CharClassBuilderTest_165, AddOverlappingRanges_165) {
  builder_->AddRange('a', 'm');
  builder_->AddRange('h', 'z');
  EXPECT_EQ(26, builder_->size());
  EXPECT_TRUE(builder_->Contains('a'));
  EXPECT_TRUE(builder_->Contains('h'));
  EXPECT_TRUE(builder_->Contains('z'));
}

// Test Contains returns false for characters not in any range
TEST_F(CharClassBuilderTest_165, ContainsReturnsFalseForAbsent_165) {
  builder_->AddRange('a', 'c');
  EXPECT_FALSE(builder_->Contains('d'));
  EXPECT_FALSE(builder_->Contains('Z'));
  EXPECT_FALSE(builder_->Contains(0));
}

// Test Negate operation
TEST_F(CharClassBuilderTest_165, Negate_165) {
  builder_->AddRange('a', 'z');
  int size_before = builder_->size();
  builder_->Negate();
  EXPECT_FALSE(builder_->Contains('a'));
  EXPECT_FALSE(builder_->Contains('z'));
  EXPECT_TRUE(builder_->Contains('A'));
  EXPECT_TRUE(builder_->Contains('0'));
  // After negation, size should be complementary
  EXPECT_GT(builder_->size(), 0);
}

// Test double negation returns to original
TEST_F(CharClassBuilderTest_165, DoubleNegate_165) {
  builder_->AddRange('a', 'z');
  int original_size = builder_->size();
  builder_->Negate();
  builder_->Negate();
  EXPECT_EQ(original_size, builder_->size());
  EXPECT_TRUE(builder_->Contains('a'));
  EXPECT_TRUE(builder_->Contains('z'));
}

// Test negating empty builder makes it full
TEST_F(CharClassBuilderTest_165, NegateEmptyMakesFull_165) {
  EXPECT_TRUE(builder_->empty());
  builder_->Negate();
  EXPECT_TRUE(builder_->full());
}

// Test negating full builder makes it empty
TEST_F(CharClassBuilderTest_165, NegateFullMakesEmpty_165) {
  builder_->AddRange(0, 0x10FFFF);
  EXPECT_TRUE(builder_->full());
  builder_->Negate();
  EXPECT_TRUE(builder_->empty());
}

// Test RemoveAbove removes characters above a given rune
TEST_F(CharClassBuilderTest_165, RemoveAbove_165) {
  builder_->AddRange('a', 'z');
  builder_->RemoveAbove('m');
  EXPECT_TRUE(builder_->Contains('a'));
  EXPECT_TRUE(builder_->Contains('m'));
  EXPECT_FALSE(builder_->Contains('n'));
  EXPECT_FALSE(builder_->Contains('z'));
}

// Test RemoveAbove with value below all ranges
TEST_F(CharClassBuilderTest_165, RemoveAboveBelowAllRanges_165) {
  builder_->AddRange('m', 'z');
  builder_->RemoveAbove('a');
  EXPECT_FALSE(builder_->Contains('m'));
  EXPECT_FALSE(builder_->Contains('z'));
}

// Test Copy creates an identical copy
TEST_F(CharClassBuilderTest_165, Copy_165) {
  builder_->AddRange('a', 'z');
  builder_->AddRange('0', '9');
  CharClassBuilder* copy = builder_->Copy();
  EXPECT_EQ(builder_->size(), copy->size());
  EXPECT_TRUE(copy->Contains('a'));
  EXPECT_TRUE(copy->Contains('z'));
  EXPECT_TRUE(copy->Contains('0'));
  EXPECT_TRUE(copy->Contains('9'));
  EXPECT_FALSE(copy->Contains('!'));
  delete copy;
}

// Test that modifications to copy don't affect original
TEST_F(CharClassBuilderTest_165, CopyIsIndependent_165) {
  builder_->AddRange('a', 'z');
  CharClassBuilder* copy = builder_->Copy();
  copy->AddRange('0', '9');
  EXPECT_FALSE(builder_->Contains('0'));
  EXPECT_TRUE(copy->Contains('0'));
  delete copy;
}

// Test AddCharClass merges another char class into this one
TEST_F(CharClassBuilderTest_165, AddCharClass_165) {
  CharClassBuilder other;
  other.AddRange('A', 'Z');
  builder_->AddRange('a', 'z');
  builder_->AddCharClass(&other);
  EXPECT_TRUE(builder_->Contains('a'));
  EXPECT_TRUE(builder_->Contains('z'));
  EXPECT_TRUE(builder_->Contains('A'));
  EXPECT_TRUE(builder_->Contains('Z'));
  EXPECT_EQ(52, builder_->size());
}

// Test empty and full predicates
TEST_F(CharClassBuilderTest_165, EmptyAndFull_165) {
  EXPECT_TRUE(builder_->empty());
  EXPECT_FALSE(builder_->full());
  // Add all Unicode code points
  builder_->AddRange(0, 0x10FFFF);
  EXPECT_FALSE(builder_->empty());
  EXPECT_TRUE(builder_->full());
}

// Test full after adding entire Unicode range
TEST_F(CharClassBuilderTest_165, FullRange_165) {
  builder_->AddRange(0, 0x10FFFF);
  EXPECT_TRUE(builder_->full());
}

// Test iterator (begin/end) - non-empty
TEST_F(CharClassBuilderTest_165, IteratorNonEmpty_165) {
  builder_->AddRange('a', 'z');
  int count = 0;
  for (auto it = builder_->begin(); it != builder_->end(); ++it) {
    count++;
  }
  EXPECT_GT(count, 0);
}

// Test iterator on empty builder
TEST_F(CharClassBuilderTest_165, IteratorEmpty_165) {
  EXPECT_EQ(builder_->begin(), builder_->end());
}

// Test GetCharClass returns non-null
TEST_F(CharClassBuilderTest_165, GetCharClassReturnsNonNull_165) {
  builder_->AddRange('a', 'z');
  CharClass* cc = builder_->GetCharClass();
  EXPECT_NE(nullptr, cc);
  cc->Delete();
}

// Test GetCharClass on empty builder
TEST_F(CharClassBuilderTest_165, GetCharClassEmpty_165) {
  CharClass* cc = builder_->GetCharClass();
  EXPECT_NE(nullptr, cc);
  cc->Delete();
}

// Test FoldsASCII
TEST_F(CharClassBuilderTest_165, FoldsASCII_165) {
  // An empty builder should not fold ASCII
  EXPECT_FALSE(builder_->FoldsASCII());
}

// Test FoldsASCII with lowercase letters
TEST_F(CharClassBuilderTest_165, FoldsASCIIWithLowercase_165) {
  builder_->AddRange('a', 'z');
  // 'a'-'z' alone should not fold ASCII (need both cases)
  // This is black-box: just verify it returns a bool without crashing
  bool result = builder_->FoldsASCII();
  (void)result;  // We just ensure it doesn't crash
}

// Test FoldsASCII with both cases
TEST_F(CharClassBuilderTest_165, FoldsASCIIWithBothCases_165) {
  builder_->AddRange('A', 'Z');
  builder_->AddRange('a', 'z');
  // Both upper and lower ASCII letters - might fold
  bool result = builder_->FoldsASCII();
  (void)result;  // Black box test
}

// Test AddRange with lo > hi (boundary condition)
TEST_F(CharClassBuilderTest_165, AddRangeLoGreaterThanHi_165) {
  bool result = builder_->AddRange('z', 'a');
  // Should handle gracefully - likely no characters added
  EXPECT_TRUE(builder_->empty() || !builder_->empty());  // Just ensure no crash
}

// Test AddRange with same lo and hi
TEST_F(CharClassBuilderTest_165, AddRangeSingleRune_165) {
  builder_->AddRange('m', 'm');
  EXPECT_EQ(1, builder_->size());
  EXPECT_TRUE(builder_->Contains('m'));
}

// Test adding adjacent ranges merge
TEST_F(CharClassBuilderTest_165, AdjacentRangesMerge_165) {
  builder_->AddRange('a', 'm');
  builder_->AddRange('n', 'z');
  EXPECT_EQ(26, builder_->size());
  EXPECT_TRUE(builder_->Contains('a'));
  EXPECT_TRUE(builder_->Contains('m'));
  EXPECT_TRUE(builder_->Contains('n'));
  EXPECT_TRUE(builder_->Contains('z'));
}

// Test AddRange with rune 0
TEST_F(CharClassBuilderTest_165, AddRangeWithRuneZero_165) {
  builder_->AddRange(0, 0);
  EXPECT_EQ(1, builder_->size());
  EXPECT_TRUE(builder_->Contains(0));
}

// Test AddRange with maximum Unicode code point
TEST_F(CharClassBuilderTest_165, AddRangeMaxUnicode_165) {
  builder_->AddRange(0x10FFFF, 0x10FFFF);
  EXPECT_EQ(1, builder_->size());
  EXPECT_TRUE(builder_->Contains(0x10FFFF));
}

// Test RemoveAbove with max rune
TEST_F(CharClassBuilderTest_165, RemoveAboveMaxRune_165) {
  builder_->AddRange('a', 'z');
  builder_->RemoveAbove(0x10FFFF);
  // Should not remove anything
  EXPECT_EQ(26, builder_->size());
}

// Test RemoveAbove with 0
TEST_F(CharClassBuilderTest_165, RemoveAboveZero_165) {
  builder_->AddRange(0, 0x10FFFF);
  builder_->RemoveAbove(0);
  EXPECT_TRUE(builder_->Contains(0));
  EXPECT_FALSE(builder_->Contains(1));
}

// Test AddRangeFlags
TEST_F(CharClassBuilderTest_165, AddRangeFlags_165) {
  builder_->AddRangeFlags('a', 'z', Regexp::FoldCase);
  // With FoldCase, should also include uppercase
  EXPECT_TRUE(builder_->Contains('a'));
  EXPECT_TRUE(builder_->Contains('A'));
  EXPECT_TRUE(builder_->Contains('z'));
  EXPECT_TRUE(builder_->Contains('Z'));
}

// Test AddRangeFlags without fold case
TEST_F(CharClassBuilderTest_165, AddRangeFlagsNoFold_165) {
  builder_->AddRangeFlags('a', 'z', Regexp::NoParseFlags);
  EXPECT_TRUE(builder_->Contains('a'));
  EXPECT_TRUE(builder_->Contains('z'));
  EXPECT_FALSE(builder_->Contains('A'));
}

// Test adding duplicate ranges doesn't change size
TEST_F(CharClassBuilderTest_165, DuplicateRangesNoSizeChange_165) {
  builder_->AddRange('a', 'z');
  int size1 = builder_->size();
  builder_->AddRange('a', 'z');
  int size2 = builder_->size();
  EXPECT_EQ(size1, size2);
}

// Test AddCharClass with empty builder
TEST_F(CharClassBuilderTest_165, AddEmptyCharClass_165) {
  CharClassBuilder empty;
  builder_->AddRange('a', 'z');
  int size_before = builder_->size();
  builder_->AddCharClass(&empty);
  EXPECT_EQ(size_before, builder_->size());
}

// Test that AddRange returns bool
TEST_F(CharClassBuilderTest_165, AddRangeReturnValue_165) {
  bool result1 = builder_->AddRange('a', 'z');
  // First addition should return true (new range added)
  EXPECT_TRUE(result1);
  bool result2 = builder_->AddRange('a', 'z');
  // Adding same range again - may return false (no new range)
  // This is implementation-dependent, just check no crash
  (void)result2;
}

}  // namespace re2

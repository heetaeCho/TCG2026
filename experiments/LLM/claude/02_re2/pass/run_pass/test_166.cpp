#include "gtest/gtest.h"
#include "re2/regexp.h"

namespace re2 {

// Test fixture for CharClassBuilder tests
class CharClassBuilderTest_166 : public ::testing::Test {
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
TEST_F(CharClassBuilderTest_166, NewBuilderIsEmpty_166) {
  EXPECT_TRUE(builder_->empty());
}

// Test that a newly constructed CharClassBuilder is not full
TEST_F(CharClassBuilderTest_166, NewBuilderIsNotFull_166) {
  EXPECT_FALSE(builder_->full());
}

// Test that size is 0 for a new builder
TEST_F(CharClassBuilderTest_166, NewBuilderSizeIsZero_166) {
  EXPECT_EQ(0, builder_->size());
}

// Test AddRange with a single character
TEST_F(CharClassBuilderTest_166, AddRangeSingleChar_166) {
  EXPECT_TRUE(builder_->AddRange('a', 'a'));
  EXPECT_FALSE(builder_->empty());
  EXPECT_TRUE(builder_->Contains('a'));
  EXPECT_FALSE(builder_->Contains('b'));
}

// Test AddRange with a range of characters
TEST_F(CharClassBuilderTest_166, AddRangeMultipleChars_166) {
  builder_->AddRange('a', 'z');
  EXPECT_FALSE(builder_->empty());
  EXPECT_TRUE(builder_->Contains('a'));
  EXPECT_TRUE(builder_->Contains('m'));
  EXPECT_TRUE(builder_->Contains('z'));
  EXPECT_FALSE(builder_->Contains('A'));
  EXPECT_FALSE(builder_->Contains('0'));
}

// Test that Contains returns false for characters not in the class
TEST_F(CharClassBuilderTest_166, ContainsReturnsFalseForMissing_166) {
  builder_->AddRange('a', 'f');
  EXPECT_FALSE(builder_->Contains('g'));
  EXPECT_FALSE(builder_->Contains('z'));
  EXPECT_FALSE(builder_->Contains(0));
}

// Test adding multiple disjoint ranges
TEST_F(CharClassBuilderTest_166, AddMultipleDisjointRanges_166) {
  builder_->AddRange('a', 'c');
  builder_->AddRange('x', 'z');
  EXPECT_TRUE(builder_->Contains('a'));
  EXPECT_TRUE(builder_->Contains('b'));
  EXPECT_TRUE(builder_->Contains('c'));
  EXPECT_FALSE(builder_->Contains('d'));
  EXPECT_FALSE(builder_->Contains('w'));
  EXPECT_TRUE(builder_->Contains('x'));
  EXPECT_TRUE(builder_->Contains('y'));
  EXPECT_TRUE(builder_->Contains('z'));
}

// Test adding overlapping ranges
TEST_F(CharClassBuilderTest_166, AddOverlappingRanges_166) {
  builder_->AddRange('a', 'm');
  builder_->AddRange('g', 'z');
  EXPECT_TRUE(builder_->Contains('a'));
  EXPECT_TRUE(builder_->Contains('g'));
  EXPECT_TRUE(builder_->Contains('m'));
  EXPECT_TRUE(builder_->Contains('n'));
  EXPECT_TRUE(builder_->Contains('z'));
}

// Test Negate on empty builder
TEST_F(CharClassBuilderTest_166, NegateEmptyBuilder_166) {
  EXPECT_TRUE(builder_->empty());
  builder_->Negate();
  EXPECT_TRUE(builder_->full());
  EXPECT_FALSE(builder_->empty());
}

// Test Negate on a builder with some range
TEST_F(CharClassBuilderTest_166, NegateWithRange_166) {
  builder_->AddRange('a', 'z');
  EXPECT_TRUE(builder_->Contains('a'));
  EXPECT_TRUE(builder_->Contains('z'));
  builder_->Negate();
  EXPECT_FALSE(builder_->Contains('a'));
  EXPECT_FALSE(builder_->Contains('z'));
  EXPECT_TRUE(builder_->Contains('A'));
  EXPECT_TRUE(builder_->Contains('0'));
}

// Test double negation returns to original
TEST_F(CharClassBuilderTest_166, DoubleNegate_166) {
  builder_->AddRange('a', 'z');
  builder_->Negate();
  builder_->Negate();
  EXPECT_TRUE(builder_->Contains('a'));
  EXPECT_TRUE(builder_->Contains('z'));
  EXPECT_FALSE(builder_->Contains('A'));
}

// Test Copy creates an independent copy
TEST_F(CharClassBuilderTest_166, CopyCreatesIndependentCopy_166) {
  builder_->AddRange('a', 'z');
  CharClassBuilder* copy = builder_->Copy();
  ASSERT_NE(copy, nullptr);
  EXPECT_TRUE(copy->Contains('a'));
  EXPECT_TRUE(copy->Contains('z'));
  EXPECT_FALSE(copy->Contains('A'));

  // Modifying original should not affect copy
  builder_->AddRange('A', 'Z');
  EXPECT_FALSE(copy->Contains('A'));
  EXPECT_TRUE(builder_->Contains('A'));

  delete copy;
}

// Test AddCharClass merges another builder
TEST_F(CharClassBuilderTest_166, AddCharClassMerges_166) {
  builder_->AddRange('a', 'f');
  CharClassBuilder other;
  other.AddRange('x', 'z');
  builder_->AddCharClass(&other);
  EXPECT_TRUE(builder_->Contains('a'));
  EXPECT_TRUE(builder_->Contains('f'));
  EXPECT_TRUE(builder_->Contains('x'));
  EXPECT_TRUE(builder_->Contains('z'));
  EXPECT_FALSE(builder_->Contains('g'));
}

// Test RemoveAbove removes characters above a given rune
TEST_F(CharClassBuilderTest_166, RemoveAboveRemovesHighChars_166) {
  builder_->AddRange('a', 'z');
  builder_->RemoveAbove('m');
  EXPECT_TRUE(builder_->Contains('a'));
  EXPECT_TRUE(builder_->Contains('m'));
  EXPECT_FALSE(builder_->Contains('n'));
  EXPECT_FALSE(builder_->Contains('z'));
}

// Test RemoveAbove with value below all ranges
TEST_F(CharClassBuilderTest_166, RemoveAboveBelowAllRanges_166) {
  builder_->AddRange('m', 'z');
  builder_->RemoveAbove('a');
  EXPECT_FALSE(builder_->Contains('m'));
  EXPECT_FALSE(builder_->Contains('z'));
}

// Test RemoveAbove with value above all ranges (no effect)
TEST_F(CharClassBuilderTest_166, RemoveAboveAboveAllRanges_166) {
  builder_->AddRange('a', 'z');
  builder_->RemoveAbove(0x10FFFF);  // Max Unicode code point
  EXPECT_TRUE(builder_->Contains('a'));
  EXPECT_TRUE(builder_->Contains('z'));
}

// Test FoldsASCII on empty builder
TEST_F(CharClassBuilderTest_166, FoldsASCIIEmpty_166) {
  EXPECT_FALSE(builder_->FoldsASCII());
}

// Test FoldsASCII with a range that includes both cases
TEST_F(CharClassBuilderTest_166, FoldsASCIIWithBothCases_166) {
  builder_->AddRange('A', 'Z');
  builder_->AddRange('a', 'z');
  EXPECT_TRUE(builder_->FoldsASCII());
}

// Test FoldsASCII with only lowercase
TEST_F(CharClassBuilderTest_166, FoldsASCIIOnlyLowercase_166) {
  builder_->AddRange('a', 'z');
  // Without uppercase, FoldsASCII should return false
  EXPECT_FALSE(builder_->FoldsASCII());
}

// Test iterator begin/end on empty builder
TEST_F(CharClassBuilderTest_166, IteratorEmptyBuilder_166) {
  EXPECT_EQ(builder_->begin(), builder_->end());
}

// Test iterator begin/end on non-empty builder
TEST_F(CharClassBuilderTest_166, IteratorNonEmptyBuilder_166) {
  builder_->AddRange('a', 'z');
  EXPECT_NE(builder_->begin(), builder_->end());
}

// Test size after adding ranges
TEST_F(CharClassBuilderTest_166, SizeAfterAddingRanges_166) {
  EXPECT_EQ(0, builder_->size());
  builder_->AddRange('a', 'z');
  EXPECT_GT(builder_->size(), 0);
}

// Test GetCharClass returns non-null
TEST_F(CharClassBuilderTest_166, GetCharClassReturnsNonNull_166) {
  builder_->AddRange('a', 'z');
  CharClass* cc = builder_->GetCharClass();
  ASSERT_NE(cc, nullptr);
  cc->Delete();
}

// Test GetCharClass on empty builder
TEST_F(CharClassBuilderTest_166, GetCharClassOnEmptyBuilder_166) {
  CharClass* cc = builder_->GetCharClass();
  ASSERT_NE(cc, nullptr);
  cc->Delete();
}

// Test full after adding entire Unicode range
TEST_F(CharClassBuilderTest_166, FullAfterAddingAllRunes_166) {
  builder_->AddRange(0, 0x10FFFF);
  EXPECT_TRUE(builder_->full());
  EXPECT_FALSE(builder_->empty());
}

// Test AddRange where lo > hi (boundary condition)
TEST_F(CharClassBuilderTest_166, AddRangeLoGreaterThanHi_166) {
  // When lo > hi, AddRange should handle gracefully (likely no-op)
  bool result = builder_->AddRange('z', 'a');
  // The builder should still be empty since the range is invalid
  EXPECT_TRUE(builder_->empty());
}

// Test adding same range twice
TEST_F(CharClassBuilderTest_166, AddSameRangeTwice_166) {
  builder_->AddRange('a', 'z');
  int size_after_first = builder_->size();
  builder_->AddRange('a', 'z');
  // Size should remain the same
  EXPECT_EQ(size_after_first, builder_->size());
}

// Test AddRange with single Rune 0
TEST_F(CharClassBuilderTest_166, AddRangeWithRuneZero_166) {
  builder_->AddRange(0, 0);
  EXPECT_TRUE(builder_->Contains(0));
  EXPECT_FALSE(builder_->Contains(1));
}

// Test AddRange with max Unicode code point
TEST_F(CharClassBuilderTest_166, AddRangeMaxRune_166) {
  builder_->AddRange(0x10FFFF, 0x10FFFF);
  EXPECT_TRUE(builder_->Contains(0x10FFFF));
  EXPECT_FALSE(builder_->Contains(0x10FFFE));
}

// Test Copy of empty builder
TEST_F(CharClassBuilderTest_166, CopyEmptyBuilder_166) {
  CharClassBuilder* copy = builder_->Copy();
  ASSERT_NE(copy, nullptr);
  EXPECT_TRUE(copy->empty());
  EXPECT_EQ(0, copy->size());
  delete copy;
}

// Test AddCharClass with empty source
TEST_F(CharClassBuilderTest_166, AddEmptyCharClass_166) {
  builder_->AddRange('a', 'z');
  CharClassBuilder empty_builder;
  builder_->AddCharClass(&empty_builder);
  // Should still contain original range
  EXPECT_TRUE(builder_->Contains('a'));
  EXPECT_TRUE(builder_->Contains('z'));
}

// Test Negate on full builder makes it empty
TEST_F(CharClassBuilderTest_166, NegateFullBuilderMakesEmpty_166) {
  builder_->AddRange(0, 0x10FFFF);
  EXPECT_TRUE(builder_->full());
  builder_->Negate();
  EXPECT_TRUE(builder_->empty());
}

// Test RemoveAbove on empty builder
TEST_F(CharClassBuilderTest_166, RemoveAboveOnEmptyBuilder_166) {
  builder_->RemoveAbove('m');
  EXPECT_TRUE(builder_->empty());
}

// Test adjacent ranges are merged
TEST_F(CharClassBuilderTest_166, AdjacentRangesAreMerged_166) {
  builder_->AddRange('a', 'm');
  builder_->AddRange('n', 'z');
  EXPECT_TRUE(builder_->Contains('a'));
  EXPECT_TRUE(builder_->Contains('m'));
  EXPECT_TRUE(builder_->Contains('n'));
  EXPECT_TRUE(builder_->Contains('z'));
}

// Test iteration count matches expected ranges
TEST_F(CharClassBuilderTest_166, IterationCountMatchesRanges_166) {
  builder_->AddRange('a', 'c');
  builder_->AddRange('x', 'z');
  int count = 0;
  for (auto it = builder_->begin(); it != builder_->end(); ++it) {
    count++;
  }
  EXPECT_EQ(2, count);
}

// Test AddRangeFlags basic usage (no case folding)
TEST_F(CharClassBuilderTest_166, AddRangeFlagsBasic_166) {
  builder_->AddRangeFlags('a', 'z', Regexp::ParseFlags(0));
  EXPECT_TRUE(builder_->Contains('a'));
  EXPECT_TRUE(builder_->Contains('z'));
}

}  // namespace re2

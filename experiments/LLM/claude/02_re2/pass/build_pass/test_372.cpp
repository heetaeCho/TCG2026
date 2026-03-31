#include "gtest/gtest.h"
#include "re2/regexp.h"

namespace re2 {

class CharClassBuilderTest_372 : public ::testing::Test {
 protected:
  CharClassBuilder builder_;
};

// Test that a newly constructed CharClassBuilder is empty
TEST_F(CharClassBuilderTest_372, NewBuilderIsEmpty_372) {
  EXPECT_TRUE(builder_.empty());
  EXPECT_EQ(builder_.size(), 0);
}

// Test that a newly constructed CharClassBuilder is not full
TEST_F(CharClassBuilderTest_372, NewBuilderIsNotFull_372) {
  EXPECT_FALSE(builder_.full());
}

// Test Contains returns false for empty builder
TEST_F(CharClassBuilderTest_372, ContainsReturnsFalseWhenEmpty_372) {
  EXPECT_FALSE(builder_.Contains(0));
  EXPECT_FALSE(builder_.Contains('a'));
  EXPECT_FALSE(builder_.Contains('Z'));
}

// Test AddRange with a single character
TEST_F(CharClassBuilderTest_372, AddRangeSingleCharacter_372) {
  builder_.AddRange('a', 'a');
  EXPECT_TRUE(builder_.Contains('a'));
  EXPECT_FALSE(builder_.Contains('b'));
  EXPECT_FALSE(builder_.empty());
}

// Test AddRange with a range of characters
TEST_F(CharClassBuilderTest_372, AddRangeMultipleCharacters_372) {
  builder_.AddRange('a', 'z');
  EXPECT_TRUE(builder_.Contains('a'));
  EXPECT_TRUE(builder_.Contains('m'));
  EXPECT_TRUE(builder_.Contains('z'));
  EXPECT_FALSE(builder_.Contains('A'));
  EXPECT_FALSE(builder_.Contains('0'));
}

// Test AddRange returns true when range is new
TEST_F(CharClassBuilderTest_372, AddRangeReturnValue_372) {
  bool result = builder_.AddRange('a', 'z');
  // The return value indicates whether the range was added (changed the set)
  EXPECT_TRUE(result);
}

// Test AddRange with overlapping ranges
TEST_F(CharClassBuilderTest_372, AddRangeOverlapping_372) {
  builder_.AddRange('a', 'm');
  builder_.AddRange('h', 'z');
  EXPECT_TRUE(builder_.Contains('a'));
  EXPECT_TRUE(builder_.Contains('h'));
  EXPECT_TRUE(builder_.Contains('m'));
  EXPECT_TRUE(builder_.Contains('z'));
}

// Test size after adding ranges
TEST_F(CharClassBuilderTest_372, SizeAfterAddRange_372) {
  builder_.AddRange('a', 'z');
  EXPECT_GT(builder_.size(), 0);
}

// Test Contains boundary of range
TEST_F(CharClassBuilderTest_372, ContainsBoundaryOfRange_372) {
  builder_.AddRange('c', 'f');
  EXPECT_FALSE(builder_.Contains('b'));
  EXPECT_TRUE(builder_.Contains('c'));
  EXPECT_TRUE(builder_.Contains('f'));
  EXPECT_FALSE(builder_.Contains('g'));
}

// Test Negate on empty builder makes it full
TEST_F(CharClassBuilderTest_372, NegateEmptyBuilderMakesFull_372) {
  EXPECT_TRUE(builder_.empty());
  builder_.Negate();
  EXPECT_TRUE(builder_.full());
}

// Test Negate on full builder makes it empty
TEST_F(CharClassBuilderTest_372, NegateFullBuilderMakesEmpty_372) {
  builder_.Negate();  // now full
  builder_.Negate();  // now empty again
  EXPECT_TRUE(builder_.empty());
}

// Test Negate inverts containment
TEST_F(CharClassBuilderTest_372, NegateInvertsContainment_372) {
  builder_.AddRange('a', 'z');
  EXPECT_TRUE(builder_.Contains('a'));
  EXPECT_FALSE(builder_.Contains('A'));
  builder_.Negate();
  EXPECT_FALSE(builder_.Contains('a'));
  EXPECT_TRUE(builder_.Contains('A'));
}

// Test Copy creates an independent copy
TEST_F(CharClassBuilderTest_372, CopyCreatesIndependentCopy_372) {
  builder_.AddRange('a', 'z');
  CharClassBuilder* copy = builder_.Copy();
  ASSERT_NE(copy, nullptr);
  EXPECT_TRUE(copy->Contains('a'));
  EXPECT_TRUE(copy->Contains('z'));
  EXPECT_FALSE(copy->Contains('A'));
  
  // Modify original, copy should be unaffected
  builder_.AddRange('A', 'Z');
  EXPECT_FALSE(copy->Contains('A'));
  
  delete copy;
}

// Test AddCharClass merges another builder
TEST_F(CharClassBuilderTest_372, AddCharClassMergesRanges_372) {
  CharClassBuilder other;
  other.AddRange('A', 'Z');
  
  builder_.AddRange('a', 'z');
  builder_.AddCharClass(&other);
  
  EXPECT_TRUE(builder_.Contains('a'));
  EXPECT_TRUE(builder_.Contains('z'));
  EXPECT_TRUE(builder_.Contains('A'));
  EXPECT_TRUE(builder_.Contains('Z'));
}

// Test RemoveAbove removes characters above a threshold
TEST_F(CharClassBuilderTest_372, RemoveAboveRemovesHigherRunes_372) {
  builder_.AddRange('a', 'z');
  builder_.RemoveAbove('m');
  EXPECT_TRUE(builder_.Contains('a'));
  EXPECT_TRUE(builder_.Contains('m'));
  EXPECT_FALSE(builder_.Contains('n'));
  EXPECT_FALSE(builder_.Contains('z'));
}

// Test RemoveAbove with value below all ranges
TEST_F(CharClassBuilderTest_372, RemoveAboveBelowAllRanges_372) {
  builder_.AddRange('a', 'z');
  builder_.RemoveAbove('A');  // 'A' < 'a'
  EXPECT_FALSE(builder_.Contains('a'));
  EXPECT_FALSE(builder_.Contains('z'));
}

// Test RemoveAbove with value above all ranges (no-op)
TEST_F(CharClassBuilderTest_372, RemoveAboveAboveAllRanges_372) {
  builder_.AddRange('a', 'z');
  builder_.RemoveAbove(0x10FFFF);
  EXPECT_TRUE(builder_.Contains('a'));
  EXPECT_TRUE(builder_.Contains('z'));
}

// Test AddRange with Rune 0
TEST_F(CharClassBuilderTest_372, AddRangeWithRuneZero_372) {
  builder_.AddRange(0, 0);
  EXPECT_TRUE(builder_.Contains(0));
  EXPECT_FALSE(builder_.Contains(1));
}

// Test AddRange covering Unicode range
TEST_F(CharClassBuilderTest_372, AddRangeUnicode_372) {
  builder_.AddRange(0x4E00, 0x9FFF);  // CJK Unified Ideographs
  EXPECT_TRUE(builder_.Contains(0x4E00));
  EXPECT_TRUE(builder_.Contains(0x9FFF));
  EXPECT_TRUE(builder_.Contains(0x5000));
  EXPECT_FALSE(builder_.Contains(0x4DFF));
  EXPECT_FALSE(builder_.Contains(0xA000));
}

// Test GetCharClass returns non-null
TEST_F(CharClassBuilderTest_372, GetCharClassReturnsNonNull_372) {
  builder_.AddRange('a', 'z');
  CharClass* cc = builder_.GetCharClass();
  ASSERT_NE(cc, nullptr);
  cc->Delete();
}

// Test GetCharClass on empty builder
TEST_F(CharClassBuilderTest_372, GetCharClassOnEmptyBuilder_372) {
  CharClass* cc = builder_.GetCharClass();
  ASSERT_NE(cc, nullptr);
  cc->Delete();
}

// Test FoldsASCII
TEST_F(CharClassBuilderTest_372, FoldsASCIIDefaultEmpty_372) {
  EXPECT_FALSE(builder_.FoldsASCII());
}

// Test FoldsASCII with uppercase and lowercase
TEST_F(CharClassBuilderTest_372, FoldsASCIIWithBothCases_372) {
  builder_.AddRange('A', 'Z');
  builder_.AddRange('a', 'z');
  EXPECT_TRUE(builder_.FoldsASCII());
}

// Test iterator begin/end on empty builder
TEST_F(CharClassBuilderTest_372, IteratorEmptyBuilder_372) {
  EXPECT_EQ(builder_.begin(), builder_.end());
}

// Test iterator begin/end on non-empty builder
TEST_F(CharClassBuilderTest_372, IteratorNonEmptyBuilder_372) {
  builder_.AddRange('a', 'z');
  EXPECT_NE(builder_.begin(), builder_.end());
}

// Test multiple disjoint ranges
TEST_F(CharClassBuilderTest_372, MultipleDisjointRanges_372) {
  builder_.AddRange('a', 'c');
  builder_.AddRange('x', 'z');
  EXPECT_TRUE(builder_.Contains('a'));
  EXPECT_TRUE(builder_.Contains('b'));
  EXPECT_TRUE(builder_.Contains('c'));
  EXPECT_FALSE(builder_.Contains('d'));
  EXPECT_FALSE(builder_.Contains('w'));
  EXPECT_TRUE(builder_.Contains('x'));
  EXPECT_TRUE(builder_.Contains('y'));
  EXPECT_TRUE(builder_.Contains('z'));
}

// Test AddRange with adjacent ranges that should merge
TEST_F(CharClassBuilderTest_372, AddRangeAdjacentRanges_372) {
  builder_.AddRange('a', 'c');
  builder_.AddRange('d', 'f');
  EXPECT_TRUE(builder_.Contains('a'));
  EXPECT_TRUE(builder_.Contains('c'));
  EXPECT_TRUE(builder_.Contains('d'));
  EXPECT_TRUE(builder_.Contains('f'));
}

// Test AddRangeFlags (basic test with no special flags)
TEST_F(CharClassBuilderTest_372, AddRangeFlagsBasic_372) {
  builder_.AddRangeFlags('a', 'z', Regexp::NoParseFlags);
  EXPECT_TRUE(builder_.Contains('a'));
  EXPECT_TRUE(builder_.Contains('z'));
}

// Test AddRangeFlags with FoldCase
TEST_F(CharClassBuilderTest_372, AddRangeFlagsFoldCase_372) {
  builder_.AddRangeFlags('a', 'z', Regexp::FoldCase);
  // With FoldCase, uppercase should also be included
  EXPECT_TRUE(builder_.Contains('a'));
  EXPECT_TRUE(builder_.Contains('A'));
  EXPECT_TRUE(builder_.Contains('z'));
  EXPECT_TRUE(builder_.Contains('Z'));
}

// Test full() after adding the maximum range
TEST_F(CharClassBuilderTest_372, FullAfterMaxRange_372) {
  builder_.AddRange(0, 0x10FFFF);
  EXPECT_TRUE(builder_.full());
}

// Test Copy preserves negation
TEST_F(CharClassBuilderTest_372, CopyPreservesNegation_372) {
  builder_.AddRange('a', 'z');
  builder_.Negate();
  CharClassBuilder* copy = builder_.Copy();
  ASSERT_NE(copy, nullptr);
  EXPECT_FALSE(copy->Contains('a'));
  EXPECT_TRUE(copy->Contains('A'));
  delete copy;
}

// Test double AddRange is idempotent for containment
TEST_F(CharClassBuilderTest_372, DoubleAddRangeIdempotent_372) {
  builder_.AddRange('a', 'z');
  builder_.AddRange('a', 'z');
  EXPECT_TRUE(builder_.Contains('a'));
  EXPECT_TRUE(builder_.Contains('z'));
}

}  // namespace re2

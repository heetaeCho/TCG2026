#include "gtest/gtest.h"
#include "re2/regexp.h"

namespace re2 {

// Helper: Rune is typically int32_t; Unicode max is 0x10FFFF
static const Rune kMaxRune = 0x10FFFF;

// ============================================================
// Constructor Tests
// ============================================================

TEST(CharClassBuilderTest_600, DefaultConstructorCreatesEmptyClass_600) {
  CharClassBuilder ccb;
  EXPECT_TRUE(ccb.empty());
  EXPECT_EQ(0, ccb.size());
  EXPECT_FALSE(ccb.full());
}

// ============================================================
// AddRange Tests
// ============================================================

TEST(CharClassBuilderTest_600, AddSingleCharacterRange_600) {
  CharClassBuilder ccb;
  ccb.AddRange('a', 'a');
  EXPECT_FALSE(ccb.empty());
  EXPECT_TRUE(ccb.Contains('a'));
  EXPECT_FALSE(ccb.Contains('b'));
}

TEST(CharClassBuilderTest_600, AddMultiCharacterRange_600) {
  CharClassBuilder ccb;
  ccb.AddRange('a', 'z');
  EXPECT_TRUE(ccb.Contains('a'));
  EXPECT_TRUE(ccb.Contains('m'));
  EXPECT_TRUE(ccb.Contains('z'));
  EXPECT_FALSE(ccb.Contains('A'));
  EXPECT_FALSE(ccb.Contains('0'));
}

TEST(CharClassBuilderTest_600, AddRangeReturnValue_600) {
  CharClassBuilder ccb;
  // First add should return true (modified the set)
  bool result = ccb.AddRange('a', 'z');
  EXPECT_TRUE(result);
}

TEST(CharClassBuilderTest_600, AddOverlappingRanges_600) {
  CharClassBuilder ccb;
  ccb.AddRange('a', 'm');
  ccb.AddRange('g', 'z');
  EXPECT_TRUE(ccb.Contains('a'));
  EXPECT_TRUE(ccb.Contains('g'));
  EXPECT_TRUE(ccb.Contains('m'));
  EXPECT_TRUE(ccb.Contains('z'));
}

TEST(CharClassBuilderTest_600, AddAdjacentRanges_600) {
  CharClassBuilder ccb;
  ccb.AddRange('a', 'f');
  ccb.AddRange('g', 'z');
  EXPECT_TRUE(ccb.Contains('a'));
  EXPECT_TRUE(ccb.Contains('f'));
  EXPECT_TRUE(ccb.Contains('g'));
  EXPECT_TRUE(ccb.Contains('z'));
}

TEST(CharClassBuilderTest_600, AddFullRange_600) {
  CharClassBuilder ccb;
  ccb.AddRange(0, kMaxRune);
  EXPECT_TRUE(ccb.full());
  EXPECT_TRUE(ccb.Contains(0));
  EXPECT_TRUE(ccb.Contains('a'));
  EXPECT_TRUE(ccb.Contains(kMaxRune));
}

// ============================================================
// Contains Tests
// ============================================================

TEST(CharClassBuilderTest_600, ContainsOnEmptyClass_600) {
  CharClassBuilder ccb;
  EXPECT_FALSE(ccb.Contains('a'));
  EXPECT_FALSE(ccb.Contains(0));
  EXPECT_FALSE(ccb.Contains(kMaxRune));
}

TEST(CharClassBuilderTest_600, ContainsBoundaryValues_600) {
  CharClassBuilder ccb;
  ccb.AddRange('b', 'y');
  EXPECT_FALSE(ccb.Contains('a'));
  EXPECT_TRUE(ccb.Contains('b'));
  EXPECT_TRUE(ccb.Contains('y'));
  EXPECT_FALSE(ccb.Contains('z'));
}

// ============================================================
// Size and Empty/Full Tests
// ============================================================

TEST(CharClassBuilderTest_600, SizeAfterAddingRanges_600) {
  CharClassBuilder ccb;
  EXPECT_EQ(0, ccb.size());
  ccb.AddRange('a', 'z');
  EXPECT_GT(ccb.size(), 0);
}

TEST(CharClassBuilderTest_600, EmptyAfterConstruction_600) {
  CharClassBuilder ccb;
  EXPECT_TRUE(ccb.empty());
}

TEST(CharClassBuilderTest_600, NotEmptyAfterAddRange_600) {
  CharClassBuilder ccb;
  ccb.AddRange('x', 'x');
  EXPECT_FALSE(ccb.empty());
}

TEST(CharClassBuilderTest_600, FullAfterAddingAllRunes_600) {
  CharClassBuilder ccb;
  ccb.AddRange(0, kMaxRune);
  EXPECT_TRUE(ccb.full());
}

TEST(CharClassBuilderTest_600, NotFullWithPartialRange_600) {
  CharClassBuilder ccb;
  ccb.AddRange('a', 'z');
  EXPECT_FALSE(ccb.full());
}

// ============================================================
// Negate Tests
// ============================================================

TEST(CharClassBuilderTest_600, NegateEmptyBecomesFull_600) {
  CharClassBuilder ccb;
  EXPECT_TRUE(ccb.empty());
  ccb.Negate();
  EXPECT_TRUE(ccb.full());
}

TEST(CharClassBuilderTest_600, NegateFullBecomesEmpty_600) {
  CharClassBuilder ccb;
  ccb.AddRange(0, kMaxRune);
  EXPECT_TRUE(ccb.full());
  ccb.Negate();
  EXPECT_TRUE(ccb.empty());
}

TEST(CharClassBuilderTest_600, NegatePartialRange_600) {
  CharClassBuilder ccb;
  ccb.AddRange('a', 'z');
  ccb.Negate();
  // After negation, 'a'-'z' should NOT be contained
  EXPECT_FALSE(ccb.Contains('a'));
  EXPECT_FALSE(ccb.Contains('m'));
  EXPECT_FALSE(ccb.Contains('z'));
  // But characters outside the original range should be contained
  EXPECT_TRUE(ccb.Contains('A'));
  EXPECT_TRUE(ccb.Contains('0'));
  EXPECT_TRUE(ccb.Contains(0));
}

TEST(CharClassBuilderTest_600, DoubleNegateRestoresOriginal_600) {
  CharClassBuilder ccb;
  ccb.AddRange('a', 'z');
  ccb.Negate();
  ccb.Negate();
  EXPECT_TRUE(ccb.Contains('a'));
  EXPECT_TRUE(ccb.Contains('z'));
  EXPECT_FALSE(ccb.Contains('A'));
}

// ============================================================
// RemoveAbove Tests
// ============================================================

TEST(CharClassBuilderTest_600, RemoveAboveTruncatesRange_600) {
  CharClassBuilder ccb;
  ccb.AddRange('a', 'z');
  ccb.RemoveAbove('m');
  EXPECT_TRUE(ccb.Contains('a'));
  EXPECT_TRUE(ccb.Contains('m'));
  EXPECT_FALSE(ccb.Contains('n'));
  EXPECT_FALSE(ccb.Contains('z'));
}

TEST(CharClassBuilderTest_600, RemoveAboveWithHighValueNoEffect_600) {
  CharClassBuilder ccb;
  ccb.AddRange('a', 'z');
  ccb.RemoveAbove(kMaxRune);
  EXPECT_TRUE(ccb.Contains('a'));
  EXPECT_TRUE(ccb.Contains('z'));
}

TEST(CharClassBuilderTest_600, RemoveAboveZero_600) {
  CharClassBuilder ccb;
  ccb.AddRange(0, kMaxRune);
  ccb.RemoveAbove(0);
  EXPECT_TRUE(ccb.Contains(0));
  EXPECT_FALSE(ccb.Contains(1));
  EXPECT_FALSE(ccb.Contains('a'));
}

TEST(CharClassBuilderTest_600, RemoveAboveOnEmptyClass_600) {
  CharClassBuilder ccb;
  ccb.RemoveAbove('m');
  EXPECT_TRUE(ccb.empty());
}

// ============================================================
// Copy Tests
// ============================================================

TEST(CharClassBuilderTest_600, CopyCreatesIndependentCopy_600) {
  CharClassBuilder ccb;
  ccb.AddRange('a', 'z');
  CharClassBuilder* copy = ccb.Copy();
  ASSERT_NE(copy, nullptr);
  EXPECT_TRUE(copy->Contains('a'));
  EXPECT_TRUE(copy->Contains('z'));
  EXPECT_FALSE(copy->Contains('A'));

  // Modifying copy should not affect original
  copy->AddRange('A', 'Z');
  EXPECT_TRUE(copy->Contains('A'));
  EXPECT_FALSE(ccb.Contains('A'));

  delete copy;
}

TEST(CharClassBuilderTest_600, CopyOfEmptyClass_600) {
  CharClassBuilder ccb;
  CharClassBuilder* copy = ccb.Copy();
  ASSERT_NE(copy, nullptr);
  EXPECT_TRUE(copy->empty());
  delete copy;
}

// ============================================================
// AddCharClass Tests
// ============================================================

TEST(CharClassBuilderTest_600, AddCharClassMergesRanges_600) {
  CharClassBuilder ccb1;
  ccb1.AddRange('a', 'f');

  CharClassBuilder ccb2;
  ccb2.AddRange('g', 'z');

  ccb1.AddCharClass(&ccb2);
  EXPECT_TRUE(ccb1.Contains('a'));
  EXPECT_TRUE(ccb1.Contains('f'));
  EXPECT_TRUE(ccb1.Contains('g'));
  EXPECT_TRUE(ccb1.Contains('z'));
}

TEST(CharClassBuilderTest_600, AddCharClassWithOverlap_600) {
  CharClassBuilder ccb1;
  ccb1.AddRange('a', 'm');

  CharClassBuilder ccb2;
  ccb2.AddRange('g', 'z');

  ccb1.AddCharClass(&ccb2);
  EXPECT_TRUE(ccb1.Contains('a'));
  EXPECT_TRUE(ccb1.Contains('z'));
}

TEST(CharClassBuilderTest_600, AddEmptyCharClass_600) {
  CharClassBuilder ccb1;
  ccb1.AddRange('a', 'z');

  CharClassBuilder ccb2;  // empty

  ccb1.AddCharClass(&ccb2);
  EXPECT_TRUE(ccb1.Contains('a'));
  EXPECT_TRUE(ccb1.Contains('z'));
  EXPECT_FALSE(ccb1.Contains('A'));
}

// ============================================================
// FoldsASCII Tests
// ============================================================

TEST(CharClassBuilderTest_600, FoldsASCIIOnEmptyClass_600) {
  CharClassBuilder ccb;
  // Empty class should not fold ASCII
  EXPECT_FALSE(ccb.FoldsASCII());
}

TEST(CharClassBuilderTest_600, FoldsASCIIWithBothCases_600) {
  CharClassBuilder ccb;
  ccb.AddRange('A', 'Z');
  ccb.AddRange('a', 'z');
  // Contains both upper and lower ASCII letters
  EXPECT_TRUE(ccb.FoldsASCII());
}

TEST(CharClassBuilderTest_600, FoldsASCIIWithOnlyLower_600) {
  CharClassBuilder ccb;
  ccb.AddRange('a', 'z');
  // Only lowercase, may or may not fold depending on implementation
  // Just check it doesn't crash
  ccb.FoldsASCII();
}

// ============================================================
// Iterator Tests
// ============================================================

TEST(CharClassBuilderTest_600, IteratorOnEmptyClass_600) {
  CharClassBuilder ccb;
  EXPECT_EQ(ccb.begin(), ccb.end());
}

TEST(CharClassBuilderTest_600, IteratorOnNonEmptyClass_600) {
  CharClassBuilder ccb;
  ccb.AddRange('a', 'z');
  EXPECT_NE(ccb.begin(), ccb.end());
}

// ============================================================
// GetCharClass Tests
// ============================================================

TEST(CharClassBuilderTest_600, GetCharClassReturnsNonNull_600) {
  CharClassBuilder ccb;
  ccb.AddRange('a', 'z');
  CharClass* cc = ccb.GetCharClass();
  ASSERT_NE(cc, nullptr);
  cc->Delete();
}

TEST(CharClassBuilderTest_600, GetCharClassFromEmptyBuilder_600) {
  CharClassBuilder ccb;
  CharClass* cc = ccb.GetCharClass();
  ASSERT_NE(cc, nullptr);
  cc->Delete();
}

// ============================================================
// AddRangeFlags Tests
// ============================================================

TEST(CharClassBuilderTest_600, AddRangeFlagsNoFlags_600) {
  CharClassBuilder ccb;
  ccb.AddRangeFlags('a', 'z', Regexp::NoParseFlags);
  EXPECT_TRUE(ccb.Contains('a'));
  EXPECT_TRUE(ccb.Contains('z'));
}

TEST(CharClassBuilderTest_600, AddRangeFlagsFoldCase_600) {
  CharClassBuilder ccb;
  ccb.AddRangeFlags('a', 'z', Regexp::FoldCase);
  // With FoldCase, should also contain uppercase
  EXPECT_TRUE(ccb.Contains('a'));
  EXPECT_TRUE(ccb.Contains('z'));
  EXPECT_TRUE(ccb.Contains('A'));
  EXPECT_TRUE(ccb.Contains('Z'));
}

// ============================================================
// Complex Scenario Tests
// ============================================================

TEST(CharClassBuilderTest_600, ComplexScenarioAddNegateRemove_600) {
  CharClassBuilder ccb;
  ccb.AddRange('a', 'z');
  ccb.Negate();
  // Now contains everything except 'a'-'z'
  EXPECT_TRUE(ccb.Contains('A'));
  EXPECT_TRUE(ccb.Contains('0'));
  EXPECT_FALSE(ccb.Contains('a'));
  
  ccb.RemoveAbove(127);
  // Still should not contain 'a'-'z', should contain ASCII outside that
  EXPECT_FALSE(ccb.Contains('a'));
  EXPECT_TRUE(ccb.Contains('A'));
  EXPECT_FALSE(ccb.Contains(128));
}

TEST(CharClassBuilderTest_600, MultipleDisjointRanges_600) {
  CharClassBuilder ccb;
  ccb.AddRange('0', '9');
  ccb.AddRange('A', 'Z');
  ccb.AddRange('a', 'z');
  
  EXPECT_TRUE(ccb.Contains('0'));
  EXPECT_TRUE(ccb.Contains('9'));
  EXPECT_TRUE(ccb.Contains('A'));
  EXPECT_TRUE(ccb.Contains('Z'));
  EXPECT_TRUE(ccb.Contains('a'));
  EXPECT_TRUE(ccb.Contains('z'));
  
  EXPECT_FALSE(ccb.Contains(' '));
  EXPECT_FALSE(ccb.Contains('@'));
  EXPECT_FALSE(ccb.Contains('['));
  EXPECT_FALSE(ccb.Contains('`'));
  EXPECT_FALSE(ccb.Contains('{'));
}

TEST(CharClassBuilderTest_600, CopyThenNegate_600) {
  CharClassBuilder ccb;
  ccb.AddRange('a', 'z');
  CharClassBuilder* copy = ccb.Copy();
  copy->Negate();

  // Original should be unchanged
  EXPECT_TRUE(ccb.Contains('a'));
  EXPECT_FALSE(ccb.Contains('A'));

  // Copy should be negated
  EXPECT_FALSE(copy->Contains('a'));
  EXPECT_TRUE(copy->Contains('A'));

  delete copy;
}

}  // namespace re2

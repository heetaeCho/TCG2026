#include "gtest/gtest.h"
#include "re2/regexp.h"

namespace re2 {

// Test fixture for CharClassBuilder tests
class CharClassBuilderTest_380 : public ::testing::Test {
 protected:
  void TearDown() override {
    // CharClassBuilder is stack-allocated, no special teardown needed
  }
};

// Test that a newly constructed CharClassBuilder is empty
TEST_F(CharClassBuilderTest_380, NewBuilderIsEmpty_380) {
  CharClassBuilder builder;
  EXPECT_TRUE(builder.empty());
  EXPECT_EQ(builder.size(), 0);
}

// Test that a newly constructed CharClassBuilder is not full
TEST_F(CharClassBuilderTest_380, NewBuilderIsNotFull_380) {
  CharClassBuilder builder;
  EXPECT_FALSE(builder.full());
}

// Test adding a single range
TEST_F(CharClassBuilderTest_380, AddSingleRange_380) {
  CharClassBuilder builder;
  bool added = builder.AddRange('a', 'z');
  EXPECT_TRUE(added);
  EXPECT_FALSE(builder.empty());
  EXPECT_TRUE(builder.Contains('a'));
  EXPECT_TRUE(builder.Contains('m'));
  EXPECT_TRUE(builder.Contains('z'));
  EXPECT_FALSE(builder.Contains('A'));
}

// Test adding a single character (lo == hi)
TEST_F(CharClassBuilderTest_380, AddSingleCharacter_380) {
  CharClassBuilder builder;
  builder.AddRange('x', 'x');
  EXPECT_TRUE(builder.Contains('x'));
  EXPECT_FALSE(builder.Contains('w'));
  EXPECT_FALSE(builder.Contains('y'));
}

// Test Contains returns false for characters not added
TEST_F(CharClassBuilderTest_380, ContainsReturnsFalseForMissing_380) {
  CharClassBuilder builder;
  builder.AddRange('a', 'f');
  EXPECT_FALSE(builder.Contains('g'));
  EXPECT_FALSE(builder.Contains('0'));
  EXPECT_FALSE(builder.Contains('Z'));
}

// Test adding multiple non-overlapping ranges
TEST_F(CharClassBuilderTest_380, AddMultipleNonOverlappingRanges_380) {
  CharClassBuilder builder;
  builder.AddRange('a', 'c');
  builder.AddRange('x', 'z');
  EXPECT_TRUE(builder.Contains('a'));
  EXPECT_TRUE(builder.Contains('b'));
  EXPECT_TRUE(builder.Contains('c'));
  EXPECT_TRUE(builder.Contains('x'));
  EXPECT_TRUE(builder.Contains('y'));
  EXPECT_TRUE(builder.Contains('z'));
  EXPECT_FALSE(builder.Contains('d'));
  EXPECT_FALSE(builder.Contains('w'));
}

// Test adding overlapping ranges
TEST_F(CharClassBuilderTest_380, AddOverlappingRanges_380) {
  CharClassBuilder builder;
  builder.AddRange('a', 'm');
  builder.AddRange('g', 'z');
  EXPECT_TRUE(builder.Contains('a'));
  EXPECT_TRUE(builder.Contains('g'));
  EXPECT_TRUE(builder.Contains('m'));
  EXPECT_TRUE(builder.Contains('n'));
  EXPECT_TRUE(builder.Contains('z'));
}

// Test adding adjacent ranges that should merge
TEST_F(CharClassBuilderTest_380, AddAdjacentRanges_380) {
  CharClassBuilder builder;
  builder.AddRange('a', 'f');
  builder.AddRange('g', 'l');
  EXPECT_TRUE(builder.Contains('a'));
  EXPECT_TRUE(builder.Contains('f'));
  EXPECT_TRUE(builder.Contains('g'));
  EXPECT_TRUE(builder.Contains('l'));
}

// Test GetCharClass produces a valid CharClass
TEST_F(CharClassBuilderTest_380, GetCharClassBasic_380) {
  CharClassBuilder builder;
  builder.AddRange('a', 'z');
  CharClass* cc = builder.GetCharClass();
  ASSERT_NE(cc, nullptr);
  EXPECT_TRUE(cc->Contains('a'));
  EXPECT_TRUE(cc->Contains('m'));
  EXPECT_TRUE(cc->Contains('z'));
  EXPECT_FALSE(cc->Contains('A'));
  EXPECT_FALSE(cc->Contains('0'));
  cc->Delete();
}

// Test GetCharClass from empty builder
TEST_F(CharClassBuilderTest_380, GetCharClassEmpty_380) {
  CharClassBuilder builder;
  CharClass* cc = builder.GetCharClass();
  ASSERT_NE(cc, nullptr);
  EXPECT_TRUE(cc->empty());
  EXPECT_EQ(cc->size(), 0);
  EXPECT_FALSE(cc->Contains('a'));
  cc->Delete();
}

// Test GetCharClass with multiple ranges
TEST_F(CharClassBuilderTest_380, GetCharClassMultipleRanges_380) {
  CharClassBuilder builder;
  builder.AddRange('0', '9');
  builder.AddRange('A', 'Z');
  builder.AddRange('a', 'z');
  CharClass* cc = builder.GetCharClass();
  ASSERT_NE(cc, nullptr);
  EXPECT_TRUE(cc->Contains('0'));
  EXPECT_TRUE(cc->Contains('9'));
  EXPECT_TRUE(cc->Contains('A'));
  EXPECT_TRUE(cc->Contains('Z'));
  EXPECT_TRUE(cc->Contains('a'));
  EXPECT_TRUE(cc->Contains('z'));
  EXPECT_FALSE(cc->Contains(' '));
  EXPECT_FALSE(cc->Contains('!'));
  cc->Delete();
}

// Test Negate on CharClassBuilder
TEST_F(CharClassBuilderTest_380, NegateBuilder_380) {
  CharClassBuilder builder;
  builder.AddRange('a', 'z');
  builder.Negate();
  EXPECT_FALSE(builder.Contains('a'));
  EXPECT_FALSE(builder.Contains('z'));
  EXPECT_TRUE(builder.Contains('A'));
  EXPECT_TRUE(builder.Contains('0'));
  EXPECT_TRUE(builder.Contains(' '));
}

// Test Negate on empty builder makes it full
TEST_F(CharClassBuilderTest_380, NegateEmptyBuilderMakesFull_380) {
  CharClassBuilder builder;
  EXPECT_TRUE(builder.empty());
  builder.Negate();
  EXPECT_TRUE(builder.full());
}

// Test double Negate returns to original
TEST_F(CharClassBuilderTest_380, DoubleNegateRestoresOriginal_380) {
  CharClassBuilder builder;
  builder.AddRange('a', 'z');
  builder.Negate();
  builder.Negate();
  EXPECT_TRUE(builder.Contains('a'));
  EXPECT_TRUE(builder.Contains('z'));
  EXPECT_FALSE(builder.Contains('A'));
}

// Test RemoveAbove
TEST_F(CharClassBuilderTest_380, RemoveAbove_380) {
  CharClassBuilder builder;
  builder.AddRange('a', 'z');
  builder.RemoveAbove('m');
  EXPECT_TRUE(builder.Contains('a'));
  EXPECT_TRUE(builder.Contains('m'));
  EXPECT_FALSE(builder.Contains('n'));
  EXPECT_FALSE(builder.Contains('z'));
}

// Test RemoveAbove with value below all ranges
TEST_F(CharClassBuilderTest_380, RemoveAboveBelowAllRanges_380) {
  CharClassBuilder builder;
  builder.AddRange('m', 'z');
  builder.RemoveAbove('a');
  EXPECT_FALSE(builder.Contains('m'));
  EXPECT_FALSE(builder.Contains('z'));
}

// Test RemoveAbove with value above all ranges (no effect)
TEST_F(CharClassBuilderTest_380, RemoveAboveAboveAllRanges_380) {
  CharClassBuilder builder;
  builder.AddRange('a', 'f');
  builder.RemoveAbove('z');
  EXPECT_TRUE(builder.Contains('a'));
  EXPECT_TRUE(builder.Contains('f'));
}

// Test Copy produces independent copy
TEST_F(CharClassBuilderTest_380, CopyProducesIndependentCopy_380) {
  CharClassBuilder builder;
  builder.AddRange('a', 'z');
  CharClassBuilder* copy = builder.Copy();
  ASSERT_NE(copy, nullptr);
  EXPECT_TRUE(copy->Contains('a'));
  EXPECT_TRUE(copy->Contains('z'));
  EXPECT_FALSE(copy->Contains('A'));

  // Modify original, copy should be unaffected
  builder.AddRange('A', 'Z');
  EXPECT_FALSE(copy->Contains('A'));

  delete copy;
}

// Test AddCharClass merges another builder
TEST_F(CharClassBuilderTest_380, AddCharClassMergesBuilders_380) {
  CharClassBuilder builder1;
  builder1.AddRange('a', 'f');

  CharClassBuilder builder2;
  builder2.AddRange('x', 'z');

  builder1.AddCharClass(&builder2);
  EXPECT_TRUE(builder1.Contains('a'));
  EXPECT_TRUE(builder1.Contains('f'));
  EXPECT_TRUE(builder1.Contains('x'));
  EXPECT_TRUE(builder1.Contains('z'));
}

// Test size after adding ranges
TEST_F(CharClassBuilderTest_380, SizeAfterAddingRanges_380) {
  CharClassBuilder builder;
  EXPECT_EQ(builder.size(), 0);
  builder.AddRange('a', 'z');
  EXPECT_GT(builder.size(), 0);
}

// Test GetCharClass size matches builder
TEST_F(CharClassBuilderTest_380, GetCharClassSizeMatchesBuilder_380) {
  CharClassBuilder builder;
  builder.AddRange('a', 'c');
  builder.AddRange('x', 'z');
  int builderSize = builder.size();

  CharClass* cc = builder.GetCharClass();
  ASSERT_NE(cc, nullptr);
  EXPECT_EQ(cc->size(), builderSize);
  cc->Delete();
}

// Test CharClass Negate
TEST_F(CharClassBuilderTest_380, CharClassNegate_380) {
  CharClassBuilder builder;
  builder.AddRange('a', 'z');
  CharClass* cc = builder.GetCharClass();
  ASSERT_NE(cc, nullptr);

  CharClass* negated = cc->Negate();
  ASSERT_NE(negated, nullptr);
  EXPECT_FALSE(negated->Contains('a'));
  EXPECT_FALSE(negated->Contains('z'));
  EXPECT_TRUE(negated->Contains('A'));
  EXPECT_TRUE(negated->Contains('0'));

  cc->Delete();
  negated->Delete();
}

// Test CharClass iteration
TEST_F(CharClassBuilderTest_380, CharClassIteration_380) {
  CharClassBuilder builder;
  builder.AddRange('a', 'c');
  builder.AddRange('x', 'z');
  CharClass* cc = builder.GetCharClass();
  ASSERT_NE(cc, nullptr);

  int count = 0;
  for (CharClass::iterator it = cc->begin(); it != cc->end(); ++it) {
    count++;
    // Each range should have valid lo <= hi
    EXPECT_LE(it->lo, it->hi);
  }
  EXPECT_GT(count, 0);
  cc->Delete();
}

// Test FoldsASCII on CharClass from builder with ASCII case folding range
TEST_F(CharClassBuilderTest_380, FoldsASCII_380) {
  CharClassBuilder builder;
  // Just lowercase
  builder.AddRange('a', 'z');
  bool folds = builder.FoldsASCII();
  // This tests that FoldsASCII returns a value; we don't know the exact behavior
  // but can verify it's callable

  CharClass* cc = builder.GetCharClass();
  ASSERT_NE(cc, nullptr);
  EXPECT_EQ(cc->FoldsASCII(), folds);
  cc->Delete();
}

// Test CharClass empty and full
TEST_F(CharClassBuilderTest_380, CharClassEmptyAndFull_380) {
  CharClassBuilder builder;
  CharClass* cc = builder.GetCharClass();
  ASSERT_NE(cc, nullptr);
  EXPECT_TRUE(cc->empty());
  EXPECT_FALSE(cc->full());
  cc->Delete();
}

// Test builder begin/end iterators
TEST_F(CharClassBuilderTest_380, BuilderIteration_380) {
  CharClassBuilder builder;
  builder.AddRange('a', 'f');
  builder.AddRange('0', '9');

  int count = 0;
  for (CharClassBuilder::iterator it = builder.begin(); it != builder.end(); ++it) {
    count++;
    EXPECT_LE(it->lo, it->hi);
  }
  EXPECT_GT(count, 0);
}

// Test adding range with lo > hi (boundary case)
TEST_F(CharClassBuilderTest_380, AddRangeLoGreaterThanHi_380) {
  CharClassBuilder builder;
  // The behavior for lo > hi is implementation-defined, but we test it doesn't crash
  builder.AddRange('z', 'a');
  // We don't assert specific behavior, just that it doesn't crash
}

// Test with Unicode range
TEST_F(CharClassBuilderTest_380, UnicodeRange_380) {
  CharClassBuilder builder;
  builder.AddRange(0x0100, 0x01FF);
  EXPECT_TRUE(builder.Contains(0x0100));
  EXPECT_TRUE(builder.Contains(0x0150));
  EXPECT_TRUE(builder.Contains(0x01FF));
  EXPECT_FALSE(builder.Contains(0x00FF));
  EXPECT_FALSE(builder.Contains(0x0200));
}

// Test GetCharClass with Unicode ranges
TEST_F(CharClassBuilderTest_380, GetCharClassUnicode_380) {
  CharClassBuilder builder;
  builder.AddRange(0x4E00, 0x9FFF);  // CJK range
  CharClass* cc = builder.GetCharClass();
  ASSERT_NE(cc, nullptr);
  EXPECT_TRUE(cc->Contains(0x4E00));
  EXPECT_TRUE(cc->Contains(0x9FFF));
  EXPECT_FALSE(cc->Contains(0x4DFF));
  cc->Delete();
}

// Test RemoveAbove at exact boundary of a range
TEST_F(CharClassBuilderTest_380, RemoveAboveAtExactBoundary_380) {
  CharClassBuilder builder;
  builder.AddRange('a', 'z');
  builder.RemoveAbove('z');
  EXPECT_TRUE(builder.Contains('z'));
  EXPECT_TRUE(builder.Contains('a'));
}

// Test that negating a full builder makes it empty
TEST_F(CharClassBuilderTest_380, NegateFullBuilderMakesEmpty_380) {
  CharClassBuilder builder;
  builder.Negate();  // empty -> full
  EXPECT_TRUE(builder.full());
  builder.Negate();  // full -> empty
  EXPECT_TRUE(builder.empty());
}

// Test Copy of empty builder
TEST_F(CharClassBuilderTest_380, CopyEmptyBuilder_380) {
  CharClassBuilder builder;
  CharClassBuilder* copy = builder.Copy();
  ASSERT_NE(copy, nullptr);
  EXPECT_TRUE(copy->empty());
  EXPECT_EQ(copy->size(), 0);
  delete copy;
}

// Test AddCharClass with empty builder
TEST_F(CharClassBuilderTest_380, AddEmptyCharClass_380) {
  CharClassBuilder builder1;
  builder1.AddRange('a', 'z');

  CharClassBuilder builder2;  // empty

  builder1.AddCharClass(&builder2);
  EXPECT_TRUE(builder1.Contains('a'));
  EXPECT_TRUE(builder1.Contains('z'));
  // Should still have original ranges
}

// Test GetCharClass can be called multiple times
TEST_F(CharClassBuilderTest_380, GetCharClassMultipleCalls_380) {
  CharClassBuilder builder;
  builder.AddRange('a', 'f');

  CharClass* cc1 = builder.GetCharClass();
  CharClass* cc2 = builder.GetCharClass();
  ASSERT_NE(cc1, nullptr);
  ASSERT_NE(cc2, nullptr);

  EXPECT_TRUE(cc1->Contains('a'));
  EXPECT_TRUE(cc2->Contains('a'));

  cc1->Delete();
  cc2->Delete();
}

}  // namespace re2

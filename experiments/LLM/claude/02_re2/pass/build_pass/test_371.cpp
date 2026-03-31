#include "gtest/gtest.h"
#include "re2/regexp.h"

namespace re2 {

class CharClassBuilderTest_371 : public ::testing::Test {
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
TEST_F(CharClassBuilderTest_371, NewBuilderIsEmpty_371) {
  EXPECT_TRUE(builder_->empty());
  EXPECT_EQ(builder_->size(), 0);
  EXPECT_FALSE(builder_->full());
}

// Test adding a single range
TEST_F(CharClassBuilderTest_371, AddSingleRange_371) {
  builder_->AddRange('a', 'z');
  EXPECT_FALSE(builder_->empty());
  EXPECT_TRUE(builder_->Contains('a'));
  EXPECT_TRUE(builder_->Contains('m'));
  EXPECT_TRUE(builder_->Contains('z'));
  EXPECT_FALSE(builder_->Contains('A'));
  EXPECT_FALSE(builder_->Contains('0'));
}

// Test adding a single character range (lo == hi)
TEST_F(CharClassBuilderTest_371, AddSingleCharRange_371) {
  builder_->AddRange('x', 'x');
  EXPECT_TRUE(builder_->Contains('x'));
  EXPECT_FALSE(builder_->Contains('w'));
  EXPECT_FALSE(builder_->Contains('y'));
}

// Test Contains returns false for characters not in the builder
TEST_F(CharClassBuilderTest_371, ContainsReturnsFalseForMissing_371) {
  builder_->AddRange('a', 'f');
  EXPECT_FALSE(builder_->Contains('g'));
  EXPECT_FALSE(builder_->Contains('Z'));
  EXPECT_FALSE(builder_->Contains(0));
}

// Test adding multiple non-overlapping ranges
TEST_F(CharClassBuilderTest_371, AddMultipleNonOverlappingRanges_371) {
  builder_->AddRange('a', 'c');
  builder_->AddRange('x', 'z');
  EXPECT_TRUE(builder_->Contains('a'));
  EXPECT_TRUE(builder_->Contains('b'));
  EXPECT_TRUE(builder_->Contains('c'));
  EXPECT_TRUE(builder_->Contains('x'));
  EXPECT_TRUE(builder_->Contains('y'));
  EXPECT_TRUE(builder_->Contains('z'));
  EXPECT_FALSE(builder_->Contains('d'));
  EXPECT_FALSE(builder_->Contains('w'));
}

// Test adding overlapping ranges
TEST_F(CharClassBuilderTest_371, AddOverlappingRanges_371) {
  builder_->AddRange('a', 'm');
  builder_->AddRange('g', 'z');
  EXPECT_TRUE(builder_->Contains('a'));
  EXPECT_TRUE(builder_->Contains('g'));
  EXPECT_TRUE(builder_->Contains('m'));
  EXPECT_TRUE(builder_->Contains('n'));
  EXPECT_TRUE(builder_->Contains('z'));
}

// Test adding adjacent ranges
TEST_F(CharClassBuilderTest_371, AddAdjacentRanges_371) {
  builder_->AddRange('a', 'm');
  builder_->AddRange('n', 'z');
  EXPECT_TRUE(builder_->Contains('a'));
  EXPECT_TRUE(builder_->Contains('m'));
  EXPECT_TRUE(builder_->Contains('n'));
  EXPECT_TRUE(builder_->Contains('z'));
}

// Test AddCharClass copies ranges from another builder
TEST_F(CharClassBuilderTest_371, AddCharClassCopiesRanges_371) {
  CharClassBuilder other;
  other.AddRange('a', 'f');
  other.AddRange('0', '9');

  builder_->AddCharClass(&other);

  EXPECT_TRUE(builder_->Contains('a'));
  EXPECT_TRUE(builder_->Contains('f'));
  EXPECT_TRUE(builder_->Contains('0'));
  EXPECT_TRUE(builder_->Contains('9'));
  EXPECT_FALSE(builder_->Contains('g'));
}

// Test AddCharClass merges with existing ranges
TEST_F(CharClassBuilderTest_371, AddCharClassMergesWithExisting_371) {
  builder_->AddRange('a', 'f');

  CharClassBuilder other;
  other.AddRange('d', 'k');

  builder_->AddCharClass(&other);

  EXPECT_TRUE(builder_->Contains('a'));
  EXPECT_TRUE(builder_->Contains('f'));
  EXPECT_TRUE(builder_->Contains('g'));
  EXPECT_TRUE(builder_->Contains('k'));
  EXPECT_FALSE(builder_->Contains('l'));
}

// Test AddCharClass with empty source
TEST_F(CharClassBuilderTest_371, AddCharClassWithEmptySource_371) {
  builder_->AddRange('a', 'z');
  CharClassBuilder empty;
  builder_->AddCharClass(&empty);
  EXPECT_TRUE(builder_->Contains('a'));
  EXPECT_TRUE(builder_->Contains('z'));
}

// Test AddCharClass to empty destination
TEST_F(CharClassBuilderTest_371, AddCharClassToEmptyDest_371) {
  CharClassBuilder other;
  other.AddRange('a', 'z');
  builder_->AddCharClass(&other);
  EXPECT_TRUE(builder_->Contains('a'));
  EXPECT_TRUE(builder_->Contains('z'));
  EXPECT_FALSE(builder_->Contains('A'));
}

// Test Copy creates an independent copy
TEST_F(CharClassBuilderTest_371, CopyCreatesIndependentCopy_371) {
  builder_->AddRange('a', 'z');
  CharClassBuilder* copy = builder_->Copy();

  EXPECT_TRUE(copy->Contains('a'));
  EXPECT_TRUE(copy->Contains('z'));

  // Modify original, copy should be unaffected
  builder_->AddRange('0', '9');
  EXPECT_FALSE(copy->Contains('0'));

  delete copy;
}

// Test Copy of empty builder
TEST_F(CharClassBuilderTest_371, CopyOfEmptyBuilder_371) {
  CharClassBuilder* copy = builder_->Copy();
  EXPECT_TRUE(copy->empty());
  delete copy;
}

// Test Negate
TEST_F(CharClassBuilderTest_371, NegateInvertsRanges_371) {
  builder_->AddRange('a', 'z');
  EXPECT_TRUE(builder_->Contains('a'));
  EXPECT_FALSE(builder_->Contains('A'));

  builder_->Negate();

  EXPECT_FALSE(builder_->Contains('a'));
  EXPECT_FALSE(builder_->Contains('z'));
  EXPECT_TRUE(builder_->Contains('A'));
  EXPECT_TRUE(builder_->Contains('0'));
}

// Test double negate returns to original
TEST_F(CharClassBuilderTest_371, DoubleNegateRestoresOriginal_371) {
  builder_->AddRange('a', 'z');
  builder_->Negate();
  builder_->Negate();
  EXPECT_TRUE(builder_->Contains('a'));
  EXPECT_TRUE(builder_->Contains('z'));
  EXPECT_FALSE(builder_->Contains('A'));
}

// Test Negate on empty builder makes it full
TEST_F(CharClassBuilderTest_371, NegateEmptyMakesFull_371) {
  EXPECT_TRUE(builder_->empty());
  builder_->Negate();
  EXPECT_TRUE(builder_->full());
}

// Test Negate on full builder makes it empty
TEST_F(CharClassBuilderTest_371, NegateFullMakesEmpty_371) {
  builder_->Negate();  // empty -> full
  EXPECT_TRUE(builder_->full());
  builder_->Negate();  // full -> empty
  EXPECT_TRUE(builder_->empty());
}

// Test RemoveAbove removes characters above the threshold
TEST_F(CharClassBuilderTest_371, RemoveAbove_371) {
  builder_->AddRange(0, 0x10FFFF);  // Add all Unicode
  EXPECT_TRUE(builder_->Contains(0x10FFFF));
  EXPECT_TRUE(builder_->Contains(127));

  builder_->RemoveAbove(127);
  EXPECT_TRUE(builder_->Contains(0));
  EXPECT_TRUE(builder_->Contains(127));
  EXPECT_FALSE(builder_->Contains(128));
  EXPECT_FALSE(builder_->Contains(0x10FFFF));
}

// Test RemoveAbove with value larger than all ranges
TEST_F(CharClassBuilderTest_371, RemoveAboveWithLargeValue_371) {
  builder_->AddRange('a', 'z');
  builder_->RemoveAbove(0x10FFFF);
  EXPECT_TRUE(builder_->Contains('a'));
  EXPECT_TRUE(builder_->Contains('z'));
}

// Test RemoveAbove with zero
TEST_F(CharClassBuilderTest_371, RemoveAboveZero_371) {
  builder_->AddRange(0, 255);
  builder_->RemoveAbove(0);
  EXPECT_TRUE(builder_->Contains(0));
  EXPECT_FALSE(builder_->Contains(1));
}

// Test size reflects number of ranges
TEST_F(CharClassBuilderTest_371, SizeReflectsRangeCount_371) {
  EXPECT_EQ(builder_->size(), 0);
  builder_->AddRange('a', 'z');
  EXPECT_GE(builder_->size(), 1);
  builder_->AddRange('0', '9');
  EXPECT_GE(builder_->size(), 2);
}

// Test iterators
TEST_F(CharClassBuilderTest_371, IteratorsWork_371) {
  builder_->AddRange('a', 'c');
  builder_->AddRange('x', 'z');

  int count = 0;
  for (CharClassBuilder::iterator it = builder_->begin();
       it != builder_->end(); ++it) {
    count++;
    EXPECT_LE(it->lo, it->hi);
  }
  EXPECT_EQ(count, builder_->size());
}

// Test empty builder iterators
TEST_F(CharClassBuilderTest_371, EmptyBuilderIterators_371) {
  EXPECT_TRUE(builder_->begin() == builder_->end());
}

// Test full() after adding complete Unicode range
TEST_F(CharClassBuilderTest_371, FullAfterAddingAllUnicode_371) {
  builder_->AddRange(0, 0x10FFFF);
  EXPECT_TRUE(builder_->full());
  EXPECT_FALSE(builder_->empty());
}

// Test GetCharClass returns a valid CharClass
TEST_F(CharClassBuilderTest_371, GetCharClassReturnsNonNull_371) {
  builder_->AddRange('a', 'z');
  CharClass* cc = builder_->GetCharClass();
  EXPECT_NE(cc, nullptr);
  cc->Delete();
}

// Test GetCharClass on empty builder
TEST_F(CharClassBuilderTest_371, GetCharClassOnEmptyBuilder_371) {
  CharClass* cc = builder_->GetCharClass();
  EXPECT_NE(cc, nullptr);
  cc->Delete();
}

// Test FoldsASCII
TEST_F(CharClassBuilderTest_371, FoldsASCIIWithUpperAndLower_371) {
  builder_->AddRange('A', 'Z');
  builder_->AddRange('a', 'z');
  // When both upper and lower case ASCII letters are present, FoldsASCII should be true
  EXPECT_TRUE(builder_->FoldsASCII());
}

// Test FoldsASCII with only lowercase
TEST_F(CharClassBuilderTest_371, FoldsASCIIWithOnlyLower_371) {
  builder_->AddRange('a', 'z');
  // Only lowercase - doesn't fold ASCII
  EXPECT_FALSE(builder_->FoldsASCII());
}

// Test FoldsASCII with empty builder
TEST_F(CharClassBuilderTest_371, FoldsASCIIEmpty_371) {
  EXPECT_FALSE(builder_->FoldsASCII());
}

// Test AddRange returns bool
TEST_F(CharClassBuilderTest_371, AddRangeReturnValue_371) {
  bool result = builder_->AddRange('a', 'z');
  // First addition should return true (new range added)
  EXPECT_TRUE(result);
}

// Test adding a duplicate range
TEST_F(CharClassBuilderTest_371, AddDuplicateRange_371) {
  builder_->AddRange('a', 'z');
  bool result = builder_->AddRange('a', 'z');
  // Duplicate range - may return false since nothing new was added
  // We just verify Contains still works
  EXPECT_TRUE(builder_->Contains('a'));
  EXPECT_TRUE(builder_->Contains('z'));
}

// Test RemoveAbove on partially overlapping range
TEST_F(CharClassBuilderTest_371, RemoveAbovePartialOverlap_371) {
  builder_->AddRange('a', 'z');
  builder_->RemoveAbove('m');
  EXPECT_TRUE(builder_->Contains('a'));
  EXPECT_TRUE(builder_->Contains('m'));
  EXPECT_FALSE(builder_->Contains('n'));
  EXPECT_FALSE(builder_->Contains('z'));
}

// Test AddCharClass with self (same builder) - edge case
// This might be undefined behavior, but we test what happens
TEST_F(CharClassBuilderTest_371, AddCharClassSelfReference_371) {
  builder_->AddRange('a', 'z');
  // Adding self - should at least not crash; ranges should still be present
  builder_->AddCharClass(builder_);
  EXPECT_TRUE(builder_->Contains('a'));
  EXPECT_TRUE(builder_->Contains('z'));
}

// Test large Unicode ranges
TEST_F(CharClassBuilderTest_371, LargeUnicodeRange_371) {
  builder_->AddRange(0x4E00, 0x9FFF);  // CJK Unified Ideographs
  EXPECT_TRUE(builder_->Contains(0x4E00));
  EXPECT_TRUE(builder_->Contains(0x9FFF));
  EXPECT_TRUE(builder_->Contains(0x5000));
  EXPECT_FALSE(builder_->Contains(0x4DFF));
  EXPECT_FALSE(builder_->Contains(0xA000));
}

// Test boundary: Rune value 0
TEST_F(CharClassBuilderTest_371, BoundaryRuneZero_371) {
  builder_->AddRange(0, 0);
  EXPECT_TRUE(builder_->Contains(0));
  EXPECT_FALSE(builder_->Contains(1));
}

// Test boundary: Maximum Unicode code point
TEST_F(CharClassBuilderTest_371, BoundaryMaxUnicode_371) {
  builder_->AddRange(0x10FFFF, 0x10FFFF);
  EXPECT_TRUE(builder_->Contains(0x10FFFF));
  EXPECT_FALSE(builder_->Contains(0x10FFFE));
}

}  // namespace re2

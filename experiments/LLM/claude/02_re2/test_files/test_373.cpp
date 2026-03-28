#include "gtest/gtest.h"
#include "re2/regexp.h"

namespace re2 {

// Helper: Rune is typically int32_t / int
// AlphaMask and related constants are internal, but we test observable behavior.

class CharClassBuilderTest_373 : public ::testing::Test {
 protected:
  void SetUp() override {
    builder_ = new CharClassBuilder();
  }

  void TearDown() override {
    delete builder_;
  }

  CharClassBuilder* builder_;
};

// Test default construction results in empty builder
TEST_F(CharClassBuilderTest_373, DefaultConstructorEmpty_373) {
  EXPECT_TRUE(builder_->empty());
  EXPECT_EQ(builder_->size(), 0);
  EXPECT_FALSE(builder_->full());
}

// Test adding a single character range
TEST_F(CharClassBuilderTest_373, AddSingleCharRange_373) {
  EXPECT_TRUE(builder_->AddRange('a', 'a'));
  EXPECT_TRUE(builder_->Contains('a'));
  EXPECT_FALSE(builder_->Contains('b'));
  EXPECT_FALSE(builder_->empty());
}

// Test adding a range of characters
TEST_F(CharClassBuilderTest_373, AddRangeMultipleChars_373) {
  builder_->AddRange('a', 'z');
  for (Rune r = 'a'; r <= 'z'; r++) {
    EXPECT_TRUE(builder_->Contains(r));
  }
  EXPECT_FALSE(builder_->Contains('A'));
  EXPECT_FALSE(builder_->Contains('0'));
}

// Test Contains returns false for characters not added
TEST_F(CharClassBuilderTest_373, ContainsReturnsFalseForMissing_373) {
  builder_->AddRange('A', 'Z');
  EXPECT_FALSE(builder_->Contains('a'));
  EXPECT_FALSE(builder_->Contains('0'));
  EXPECT_TRUE(builder_->Contains('M'));
}

// Test FoldsASCII with matching upper and lower case ranges
TEST_F(CharClassBuilderTest_373, FoldsASCIIWithBothCases_373) {
  builder_->AddRange('a', 'z');
  builder_->AddRange('A', 'Z');
  EXPECT_TRUE(builder_->FoldsASCII());
}

// Test FoldsASCII with only lower case
TEST_F(CharClassBuilderTest_373, FoldsASCIIOnlyLower_373) {
  builder_->AddRange('a', 'z');
  // Without upper case, FoldsASCII may return false
  // This depends on implementation; we just verify it doesn't crash
  // and returns a boolean
  bool result = builder_->FoldsASCII();
  (void)result;  // Just ensure it's callable
}

// Test FoldsASCII with only upper case
TEST_F(CharClassBuilderTest_373, FoldsASCIIOnlyUpper_373) {
  builder_->AddRange('A', 'Z');
  bool result = builder_->FoldsASCII();
  (void)result;
}

// Test FoldsASCII on empty builder
TEST_F(CharClassBuilderTest_373, FoldsASCIIEmpty_373) {
  // Empty should fold trivially
  EXPECT_TRUE(builder_->FoldsASCII());
}

// Test Copy creates independent copy
TEST_F(CharClassBuilderTest_373, CopyCreatesIndependentCopy_373) {
  builder_->AddRange('a', 'f');
  CharClassBuilder* copy = builder_->Copy();
  ASSERT_NE(copy, nullptr);

  // Copy should contain same characters
  for (Rune r = 'a'; r <= 'f'; r++) {
    EXPECT_TRUE(copy->Contains(r));
  }

  // Modifying original shouldn't affect copy
  builder_->AddRange('g', 'z');
  EXPECT_FALSE(copy->Contains('g'));

  delete copy;
}

// Test Negate inverts the character class
TEST_F(CharClassBuilderTest_373, NegateInverts_373) {
  builder_->AddRange('a', 'a');
  EXPECT_TRUE(builder_->Contains('a'));

  builder_->Negate();

  // After negation, 'a' should not be contained
  EXPECT_FALSE(builder_->Contains('a'));
  // And other characters should be contained
  EXPECT_TRUE(builder_->Contains('b'));
  EXPECT_TRUE(builder_->Contains('A'));
  EXPECT_TRUE(builder_->Contains('0'));
}

// Test double negation restores original
TEST_F(CharClassBuilderTest_373, DoubleNegateRestores_373) {
  builder_->AddRange('x', 'z');
  builder_->Negate();
  builder_->Negate();

  EXPECT_TRUE(builder_->Contains('x'));
  EXPECT_TRUE(builder_->Contains('y'));
  EXPECT_TRUE(builder_->Contains('z'));
  EXPECT_FALSE(builder_->Contains('w'));
}

// Test RemoveAbove removes characters above threshold
TEST_F(CharClassBuilderTest_373, RemoveAbove_373) {
  builder_->AddRange(0, 0x10FFFF);  // Add all Unicode
  EXPECT_TRUE(builder_->Contains(0x10FFFF));
  EXPECT_TRUE(builder_->Contains(128));

  builder_->RemoveAbove(127);
  EXPECT_TRUE(builder_->Contains(127));
  EXPECT_FALSE(builder_->Contains(128));
  EXPECT_FALSE(builder_->Contains(0x10FFFF));
}

// Test RemoveAbove with 0
TEST_F(CharClassBuilderTest_373, RemoveAboveZero_373) {
  builder_->AddRange(0, 100);
  builder_->RemoveAbove(0);
  EXPECT_TRUE(builder_->Contains(0));
  EXPECT_FALSE(builder_->Contains(1));
}

// Test AddCharClass merges another builder
TEST_F(CharClassBuilderTest_373, AddCharClassMerges_373) {
  builder_->AddRange('a', 'f');

  CharClassBuilder other;
  other.AddRange('g', 'z');

  builder_->AddCharClass(&other);

  for (Rune r = 'a'; r <= 'z'; r++) {
    EXPECT_TRUE(builder_->Contains(r));
  }
}

// Test AddCharClass with overlapping ranges
TEST_F(CharClassBuilderTest_373, AddCharClassOverlapping_373) {
  builder_->AddRange('a', 'm');

  CharClassBuilder other;
  other.AddRange('h', 'z');

  builder_->AddCharClass(&other);

  for (Rune r = 'a'; r <= 'z'; r++) {
    EXPECT_TRUE(builder_->Contains(r));
  }
}

// Test size reflects number of ranges
TEST_F(CharClassBuilderTest_373, SizeReflectsRanges_373) {
  EXPECT_EQ(builder_->size(), 0);

  builder_->AddRange('a', 'z');
  EXPECT_GE(builder_->size(), 1);

  builder_->AddRange('A', 'Z');
  EXPECT_GE(builder_->size(), 1);
}

// Test full after adding entire Unicode range
TEST_F(CharClassBuilderTest_373, FullAfterAddingAll_373) {
  builder_->AddRange(0, Runemax);
  EXPECT_TRUE(builder_->full());
}

// Test empty after negating full
TEST_F(CharClassBuilderTest_373, EmptyAfterNegatingFull_373) {
  builder_->AddRange(0, Runemax);
  EXPECT_TRUE(builder_->full());
  builder_->Negate();
  EXPECT_TRUE(builder_->empty());
}

// Test full after negating empty
TEST_F(CharClassBuilderTest_373, FullAfterNegatingEmpty_373) {
  EXPECT_TRUE(builder_->empty());
  builder_->Negate();
  EXPECT_TRUE(builder_->full());
}

// Test GetCharClass returns non-null
TEST_F(CharClassBuilderTest_373, GetCharClassReturnsNonNull_373) {
  builder_->AddRange('a', 'z');
  CharClass* cc = builder_->GetCharClass();
  ASSERT_NE(cc, nullptr);
  cc->Delete();
}

// Test GetCharClass on empty builder
TEST_F(CharClassBuilderTest_373, GetCharClassEmpty_373) {
  CharClass* cc = builder_->GetCharClass();
  ASSERT_NE(cc, nullptr);
  cc->Delete();
}

// Test iterator begin/end
TEST_F(CharClassBuilderTest_373, IteratorBeginEnd_373) {
  builder_->AddRange('a', 'z');
  int count = 0;
  for (auto it = builder_->begin(); it != builder_->end(); ++it) {
    count++;
  }
  EXPECT_GT(count, 0);
}

// Test iterator on empty
TEST_F(CharClassBuilderTest_373, IteratorEmpty_373) {
  EXPECT_EQ(builder_->begin(), builder_->end());
}

// Test AddRange returns value (whether range was newly added)
TEST_F(CharClassBuilderTest_373, AddRangeReturnValue_373) {
  bool first = builder_->AddRange('a', 'z');
  // First add of a non-empty range should return true (added new ranges)
  EXPECT_TRUE(first);
}

// Test AddRange with lo > hi (invalid range)
TEST_F(CharClassBuilderTest_373, AddRangeInvalid_373) {
  bool result = builder_->AddRange('z', 'a');
  // With lo > hi, nothing should be added
  EXPECT_FALSE(result);
  EXPECT_TRUE(builder_->empty());
}

// Test AddRange with single Unicode codepoint
TEST_F(CharClassBuilderTest_373, AddRangeSingleUnicode_373) {
  Rune r = 0x4E00;  // CJK character
  builder_->AddRange(r, r);
  EXPECT_TRUE(builder_->Contains(r));
  EXPECT_FALSE(builder_->Contains(r - 1));
  EXPECT_FALSE(builder_->Contains(r + 1));
}

// Test AddRangeFlags with case-insensitive flag
TEST_F(CharClassBuilderTest_373, AddRangeFlagsFoldCase_373) {
  builder_->AddRangeFlags('a', 'z', Regexp::FoldCase);
  // With FoldCase, upper case should also be included
  EXPECT_TRUE(builder_->Contains('a'));
  EXPECT_TRUE(builder_->Contains('A'));
  EXPECT_TRUE(builder_->Contains('z'));
  EXPECT_TRUE(builder_->Contains('Z'));
}

// Test AddRangeFlags without fold case
TEST_F(CharClassBuilderTest_373, AddRangeFlagsNoFold_373) {
  builder_->AddRangeFlags('a', 'z', Regexp::NoParseFlags);
  EXPECT_TRUE(builder_->Contains('a'));
  EXPECT_TRUE(builder_->Contains('z'));
  // Without FoldCase, upper case may not be included
  EXPECT_FALSE(builder_->Contains('A'));
}

// Test RemoveAbove on empty builder doesn't crash
TEST_F(CharClassBuilderTest_373, RemoveAboveEmpty_373) {
  builder_->RemoveAbove(100);
  EXPECT_TRUE(builder_->empty());
}

// Test Copy of empty builder
TEST_F(CharClassBuilderTest_373, CopyEmpty_373) {
  CharClassBuilder* copy = builder_->Copy();
  ASSERT_NE(copy, nullptr);
  EXPECT_TRUE(copy->empty());
  delete copy;
}

// Test adjacent ranges merge
TEST_F(CharClassBuilderTest_373, AdjacentRangesMerge_373) {
  builder_->AddRange('a', 'm');
  builder_->AddRange('n', 'z');

  // All lowercase letters should be contained
  for (Rune r = 'a'; r <= 'z'; r++) {
    EXPECT_TRUE(builder_->Contains(r));
  }
}

// Test that negation of a single char produces complement
TEST_F(CharClassBuilderTest_373, NegationComplement_373) {
  builder_->AddRange('a', 'a');
  builder_->Negate();

  EXPECT_FALSE(builder_->Contains('a'));
  EXPECT_TRUE(builder_->Contains(0));
  EXPECT_TRUE(builder_->Contains('b'));
  EXPECT_TRUE(builder_->Contains(Runemax));
}

}  // namespace re2

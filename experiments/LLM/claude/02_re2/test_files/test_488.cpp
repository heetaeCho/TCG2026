#include "gtest/gtest.h"
#include "re2/regexp.h"
#include "re2/unicode_casefold.h"

namespace re2 {

// We need to access AddFoldedRange which is a static function in parse.cc.
// Since it's static, we can't call it directly. However, we can test it
// indirectly through the public interface of CharClassBuilder, specifically
// through AddRangeFlags with the FoldCase flag, which internally calls
// AddFoldedRange.

class AddFoldedRangeTest_488 : public ::testing::Test {
 protected:
  void SetUp() override {
    cc_ = new CharClassBuilder();
  }

  void TearDown() override {
    delete cc_;
  }

  CharClassBuilder* cc_;
};

// Test that adding a simple ASCII lowercase range with fold case includes uppercase
TEST_F(AddFoldedRangeTest_488, LowercaseAsciiRangeFoldsToUppercase_488) {
  // Adding 'a'-'z' with fold case should also include 'A'-'Z'
  cc_->AddRangeFlags('a', 'z', Regexp::FoldCase);
  
  for (Rune r = 'a'; r <= 'z'; r++) {
    EXPECT_TRUE(cc_->Contains(r)) << "Should contain lowercase " << (char)r;
  }
  for (Rune r = 'A'; r <= 'Z'; r++) {
    EXPECT_TRUE(cc_->Contains(r)) << "Should contain uppercase " << (char)r;
  }
}

// Test that adding a simple ASCII uppercase range with fold case includes lowercase
TEST_F(AddFoldedRangeTest_488, UppercaseAsciiRangeFoldsToLowercase_488) {
  cc_->AddRangeFlags('A', 'Z', Regexp::FoldCase);
  
  for (Rune r = 'a'; r <= 'z'; r++) {
    EXPECT_TRUE(cc_->Contains(r)) << "Should contain lowercase " << (char)r;
  }
  for (Rune r = 'A'; r <= 'Z'; r++) {
    EXPECT_TRUE(cc_->Contains(r)) << "Should contain uppercase " << (char)r;
  }
}

// Test single character fold
TEST_F(AddFoldedRangeTest_488, SingleCharacterFold_488) {
  cc_->AddRangeFlags('a', 'a', Regexp::FoldCase);
  
  EXPECT_TRUE(cc_->Contains('a'));
  EXPECT_TRUE(cc_->Contains('A'));
  EXPECT_FALSE(cc_->Contains('b'));
  EXPECT_FALSE(cc_->Contains('B'));
}

// Test that digits are not affected by case folding
TEST_F(AddFoldedRangeTest_488, DigitsNotAffectedByFold_488) {
  cc_->AddRangeFlags('0', '9', Regexp::FoldCase);
  
  for (Rune r = '0'; r <= '9'; r++) {
    EXPECT_TRUE(cc_->Contains(r));
  }
  // Should not include any letters
  EXPECT_FALSE(cc_->Contains('a'));
  EXPECT_FALSE(cc_->Contains('A'));
}

// Test range that doesn't have any case folds
TEST_F(AddFoldedRangeTest_488, NonAlphabeticRangeUnchanged_488) {
  cc_->AddRangeFlags('!', '/', Regexp::FoldCase);
  
  for (Rune r = '!'; r <= '/'; r++) {
    EXPECT_TRUE(cc_->Contains(r));
  }
}

// Test partial lowercase range
TEST_F(AddFoldedRangeTest_488, PartialLowercaseRange_488) {
  cc_->AddRangeFlags('a', 'c', Regexp::FoldCase);
  
  EXPECT_TRUE(cc_->Contains('a'));
  EXPECT_TRUE(cc_->Contains('b'));
  EXPECT_TRUE(cc_->Contains('c'));
  EXPECT_TRUE(cc_->Contains('A'));
  EXPECT_TRUE(cc_->Contains('B'));
  EXPECT_TRUE(cc_->Contains('C'));
  EXPECT_FALSE(cc_->Contains('d'));
  EXPECT_FALSE(cc_->Contains('D'));
}

// Test FoldsASCII on a folded ASCII range
TEST_F(AddFoldedRangeTest_488, FoldsASCIIAfterFold_488) {
  cc_->AddRangeFlags('a', 'z', Regexp::FoldCase);
  EXPECT_TRUE(cc_->FoldsASCII());
}

// Test without FoldCase flag - should NOT fold
TEST_F(AddFoldedRangeTest_488, WithoutFoldCaseNoFolding_488) {
  cc_->AddRangeFlags('a', 'z', Regexp::NoParseFlags);
  
  for (Rune r = 'a'; r <= 'z'; r++) {
    EXPECT_TRUE(cc_->Contains(r));
  }
  // Without fold, uppercase should NOT be included
  for (Rune r = 'A'; r <= 'Z'; r++) {
    EXPECT_FALSE(cc_->Contains(r));
  }
}

// Test Unicode case folding - Greek letters
TEST_F(AddFoldedRangeTest_488, GreekLettersFold_488) {
  // Greek capital letter Alpha = 0x0391, lowercase alpha = 0x03B1
  cc_->AddRangeFlags(0x0391, 0x0391, Regexp::FoldCase);
  
  EXPECT_TRUE(cc_->Contains(0x0391));  // Capital Alpha
  EXPECT_TRUE(cc_->Contains(0x03B1));  // Lowercase alpha
}

// Test empty range (lo > hi should be handled gracefully)
TEST_F(AddFoldedRangeTest_488, EmptyCharClassBuilder_488) {
  EXPECT_TRUE(cc_->empty());
  EXPECT_EQ(cc_->size(), 0);
}

// Test adding a range that spans across folding boundaries
TEST_F(AddFoldedRangeTest_488, RangeSpanningFoldBoundary_488) {
  // Range from 'Z' to 'a' includes '[', '\\', ']', '^', '_', '`'
  cc_->AddRangeFlags('Z', 'a', Regexp::FoldCase);
  
  EXPECT_TRUE(cc_->Contains('Z'));
  EXPECT_TRUE(cc_->Contains('a'));
  // 'Z' should fold to 'z' and 'a' should fold to 'A'
  EXPECT_TRUE(cc_->Contains('z'));
  EXPECT_TRUE(cc_->Contains('A'));
}

// Test that the class builder is not empty after adding a folded range
TEST_F(AddFoldedRangeTest_488, NotEmptyAfterAdd_488) {
  cc_->AddRangeFlags('a', 'a', Regexp::FoldCase);
  EXPECT_FALSE(cc_->empty());
}

// Test adding the same range twice (AddRange returns false on duplicate)
TEST_F(AddFoldedRangeTest_488, DuplicateRangeHandled_488) {
  cc_->AddRangeFlags('a', 'z', Regexp::FoldCase);
  int size1 = cc_->size();
  
  // Adding same range again
  cc_->AddRangeFlags('a', 'z', Regexp::FoldCase);
  int size2 = cc_->size();
  
  // Size should remain the same
  EXPECT_EQ(size1, size2);
}

// Test with Kelvin sign (U+212A) which folds to 'K' (U+004B) and 'k' (U+006B)
TEST_F(AddFoldedRangeTest_488, KelvinSignFold_488) {
  cc_->AddRangeFlags(0x212A, 0x212A, Regexp::FoldCase);
  
  EXPECT_TRUE(cc_->Contains(0x212A));  // Kelvin sign
  EXPECT_TRUE(cc_->Contains('K'));     // Latin capital K
  EXPECT_TRUE(cc_->Contains('k'));     // Latin small k
}

// Test single character 'K' fold includes Kelvin sign
TEST_F(AddFoldedRangeTest_488, LatinKFoldsToKelvin_488) {
  cc_->AddRangeFlags('K', 'K', Regexp::FoldCase);
  
  EXPECT_TRUE(cc_->Contains('K'));
  EXPECT_TRUE(cc_->Contains('k'));
  EXPECT_TRUE(cc_->Contains(0x212A));  // Kelvin sign
}

// Test long S (U+017F) which folds to 's'
TEST_F(AddFoldedRangeTest_488, LongSFold_488) {
  cc_->AddRangeFlags('s', 's', Regexp::FoldCase);
  
  EXPECT_TRUE(cc_->Contains('s'));
  EXPECT_TRUE(cc_->Contains('S'));
  EXPECT_TRUE(cc_->Contains(0x017F));  // Long S
}

// Test that a full range covers everything
TEST_F(AddFoldedRangeTest_488, FullRangeWithFold_488) {
  cc_->AddRangeFlags(0, 0x10FFFF, Regexp::FoldCase);
  EXPECT_TRUE(cc_->full());
}

// Test Copy preserves folded ranges
TEST_F(AddFoldedRangeTest_488, CopyPreservesFoldedRanges_488) {
  cc_->AddRangeFlags('a', 'z', Regexp::FoldCase);
  
  CharClassBuilder* copy = cc_->Copy();
  
  for (Rune r = 'a'; r <= 'z'; r++) {
    EXPECT_TRUE(copy->Contains(r));
  }
  for (Rune r = 'A'; r <= 'Z'; r++) {
    EXPECT_TRUE(copy->Contains(r));
  }
  
  delete copy;
}

// Test Negate after fold
TEST_F(AddFoldedRangeTest_488, NegateAfterFold_488) {
  cc_->AddRangeFlags('a', 'z', Regexp::FoldCase);
  cc_->Negate();
  
  // After negation, 'a'-'z' and 'A'-'Z' should NOT be contained
  EXPECT_FALSE(cc_->Contains('a'));
  EXPECT_FALSE(cc_->Contains('A'));
  // But other characters should be
  EXPECT_TRUE(cc_->Contains('0'));
  EXPECT_TRUE(cc_->Contains('!'));
}

// Test RemoveAbove after fold
TEST_F(AddFoldedRangeTest_488, RemoveAboveAfterFold_488) {
  cc_->AddRangeFlags('a', 'z', Regexp::FoldCase);
  cc_->RemoveAbove('Z');  // Remove everything above 'Z'
  
  // Uppercase letters should still be there (they are <= 'Z')
  for (Rune r = 'A'; r <= 'Z'; r++) {
    EXPECT_TRUE(cc_->Contains(r));
  }
  // Lowercase letters should be removed (they are > 'Z')
  for (Rune r = 'a'; r <= 'z'; r++) {
    EXPECT_FALSE(cc_->Contains(r));
  }
}

}  // namespace re2

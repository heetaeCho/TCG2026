#include "gtest/gtest.h"
#include "re2/regexp.h"

namespace re2 {

// We need to expose AddFoldedRangeLatin1 for testing since it's a static function
// in parse.cc. We'll test it indirectly through CharClassBuilder's AddRangeFlags
// or by recreating the expected behavior through the public interface.
// However, since AddFoldedRangeLatin1 is static (file-local), we cannot call it directly.
// We'll test the observable behavior through CharClassBuilder which is the collaborator.

// Since AddFoldedRangeLatin1 is static and not directly accessible, we test the
// CharClassBuilder behavior that would result from calling AddFoldedRangeLatin1.
// The function adds folded ranges for Latin1 characters - we can test this through
// AddRangeFlags with case-insensitive flags, which internally uses AddFoldedRangeLatin1.

class AddFoldedRangeLatin1Test_487 : public ::testing::Test {
 protected:
  void SetUp() override {
    cc_ = new CharClassBuilder();
  }

  void TearDown() override {
    delete cc_;
  }

  CharClassBuilder* cc_;
};

// Test that adding an uppercase letter range also adds the lowercase equivalent
TEST_F(AddFoldedRangeLatin1Test_487, UppercaseLetterFoldsToLowercase_487) {
  // Use AddRangeFlags with FoldCase to trigger AddFoldedRangeLatin1
  cc_->AddRangeFlags('A', 'A', Regexp::FoldCase);
  EXPECT_TRUE(cc_->Contains('A'));
  EXPECT_TRUE(cc_->Contains('a'));
}

// Test that adding a lowercase letter range also adds the uppercase equivalent
TEST_F(AddFoldedRangeLatin1Test_487, LowercaseLetterFoldsToUppercase_487) {
  cc_->AddRangeFlags('a', 'a', Regexp::FoldCase);
  EXPECT_TRUE(cc_->Contains('a'));
  EXPECT_TRUE(cc_->Contains('A'));
}

// Test folding for the full uppercase range A-Z
TEST_F(AddFoldedRangeLatin1Test_487, FullUppercaseRangeFolds_487) {
  cc_->AddRangeFlags('A', 'Z', Regexp::FoldCase);
  for (Rune r = 'A'; r <= 'Z'; r++) {
    EXPECT_TRUE(cc_->Contains(r)) << "Missing uppercase: " << (char)r;
  }
  for (Rune r = 'a'; r <= 'z'; r++) {
    EXPECT_TRUE(cc_->Contains(r)) << "Missing lowercase: " << (char)r;
  }
}

// Test folding for the full lowercase range a-z
TEST_F(AddFoldedRangeLatin1Test_487, FullLowercaseRangeFolds_487) {
  cc_->AddRangeFlags('a', 'z', Regexp::FoldCase);
  for (Rune r = 'A'; r <= 'Z'; r++) {
    EXPECT_TRUE(cc_->Contains(r)) << "Missing uppercase: " << (char)r;
  }
  for (Rune r = 'a'; r <= 'z'; r++) {
    EXPECT_TRUE(cc_->Contains(r)) << "Missing lowercase: " << (char)r;
  }
}

// Test that a digit does not fold to any letter
TEST_F(AddFoldedRangeLatin1Test_487, DigitDoesNotFold_487) {
  cc_->AddRangeFlags('0', '9', Regexp::FoldCase);
  for (Rune r = '0'; r <= '9'; r++) {
    EXPECT_TRUE(cc_->Contains(r));
  }
  // Digits should not cause any alphabetic characters to be added
  EXPECT_FALSE(cc_->Contains('A'));
  EXPECT_FALSE(cc_->Contains('a'));
}

// Test single character 'A' folds correctly
TEST_F(AddFoldedRangeLatin1Test_487, SingleCharA_487) {
  cc_->AddRangeFlags('A', 'A', Regexp::FoldCase);
  EXPECT_TRUE(cc_->Contains('A'));
  EXPECT_TRUE(cc_->Contains('a'));
  EXPECT_FALSE(cc_->Contains('B'));
  EXPECT_FALSE(cc_->Contains('b'));
}

// Test single character 'z' folds correctly
TEST_F(AddFoldedRangeLatin1Test_487, SingleCharZ_487) {
  cc_->AddRangeFlags('z', 'z', Regexp::FoldCase);
  EXPECT_TRUE(cc_->Contains('z'));
  EXPECT_TRUE(cc_->Contains('Z'));
  EXPECT_FALSE(cc_->Contains('y'));
  EXPECT_FALSE(cc_->Contains('Y'));
}

// Test boundary: character just before 'A' (which is '@')
TEST_F(AddFoldedRangeLatin1Test_487, CharBeforeUppercaseRange_487) {
  cc_->AddRangeFlags('@', '@', Regexp::FoldCase);
  EXPECT_TRUE(cc_->Contains('@'));
  EXPECT_FALSE(cc_->Contains('`'));  // '@' + 32 = '`', but '@' is not a letter
}

// Test boundary: character just after 'Z' (which is '[')
TEST_F(AddFoldedRangeLatin1Test_487, CharAfterUppercaseRange_487) {
  cc_->AddRangeFlags('[', '[', Regexp::FoldCase);
  EXPECT_TRUE(cc_->Contains('['));
  EXPECT_FALSE(cc_->Contains('{'));  // '[' is not a letter, should not fold
}

// Test boundary: character just before 'a' (which is '`')
TEST_F(AddFoldedRangeLatin1Test_487, CharBeforeLowercaseRange_487) {
  cc_->AddRangeFlags('`', '`', Regexp::FoldCase);
  EXPECT_TRUE(cc_->Contains('`'));
  EXPECT_FALSE(cc_->Contains('@'));
}

// Test boundary: character just after 'z' (which is '{')
TEST_F(AddFoldedRangeLatin1Test_487, CharAfterLowercaseRange_487) {
  cc_->AddRangeFlags('{', '{', Regexp::FoldCase);
  EXPECT_TRUE(cc_->Contains('{'));
  EXPECT_FALSE(cc_->Contains('['));
}

// Test range spanning non-letter and letter characters
TEST_F(AddFoldedRangeLatin1Test_487, MixedRangeWithLettersAndNonLetters_487) {
  // Range '9' to 'C' includes ':', ';', '<', '=', '>', '?', '@', 'A', 'B', 'C'
  cc_->AddRangeFlags('9', 'C', Regexp::FoldCase);
  EXPECT_TRUE(cc_->Contains('9'));
  EXPECT_TRUE(cc_->Contains(':'));
  EXPECT_TRUE(cc_->Contains('@'));
  EXPECT_TRUE(cc_->Contains('A'));
  EXPECT_TRUE(cc_->Contains('B'));
  EXPECT_TRUE(cc_->Contains('C'));
  // Folded lowercase equivalents
  EXPECT_TRUE(cc_->Contains('a'));
  EXPECT_TRUE(cc_->Contains('b'));
  EXPECT_TRUE(cc_->Contains('c'));
  // Should not contain 'd' or 'D'
  EXPECT_FALSE(cc_->Contains('D'));
  EXPECT_FALSE(cc_->Contains('d'));
}

// Test range spanning lowercase letters and non-letter characters after 'z'
TEST_F(AddFoldedRangeLatin1Test_487, LowercaseRangeWithTrailingNonLetters_487) {
  // Range 'x' to '~' includes 'x', 'y', 'z', '{', '|', '}', '~'
  cc_->AddRangeFlags('x', '~', Regexp::FoldCase);
  EXPECT_TRUE(cc_->Contains('x'));
  EXPECT_TRUE(cc_->Contains('y'));
  EXPECT_TRUE(cc_->Contains('z'));
  EXPECT_TRUE(cc_->Contains('{'));
  EXPECT_TRUE(cc_->Contains('~'));
  // Folded uppercase
  EXPECT_TRUE(cc_->Contains('X'));
  EXPECT_TRUE(cc_->Contains('Y'));
  EXPECT_TRUE(cc_->Contains('Z'));
}

// Test with a single non-alphabetic ASCII character (space)
TEST_F(AddFoldedRangeLatin1Test_487, SpaceCharacterNoFold_487) {
  cc_->AddRangeFlags(' ', ' ', Regexp::FoldCase);
  EXPECT_TRUE(cc_->Contains(' '));
  EXPECT_EQ(1, cc_->size());
}

// Test FoldsASCII after adding folded range
TEST_F(AddFoldedRangeLatin1Test_487, FoldsASCIIAfterFoldedRange_487) {
  cc_->AddRangeFlags('A', 'Z', Regexp::FoldCase);
  EXPECT_TRUE(cc_->FoldsASCII());
}

// Test that without FoldCase flag, no folding occurs
TEST_F(AddFoldedRangeLatin1Test_487, NoFoldWithoutFlag_487) {
  cc_->AddRangeFlags('A', 'A', Regexp::NoParseFlags);
  EXPECT_TRUE(cc_->Contains('A'));
  EXPECT_FALSE(cc_->Contains('a'));
}

// Test partial uppercase range
TEST_F(AddFoldedRangeLatin1Test_487, PartialUppercaseRange_487) {
  cc_->AddRangeFlags('M', 'P', Regexp::FoldCase);
  EXPECT_TRUE(cc_->Contains('M'));
  EXPECT_TRUE(cc_->Contains('N'));
  EXPECT_TRUE(cc_->Contains('O'));
  EXPECT_TRUE(cc_->Contains('P'));
  EXPECT_TRUE(cc_->Contains('m'));
  EXPECT_TRUE(cc_->Contains('n'));
  EXPECT_TRUE(cc_->Contains('o'));
  EXPECT_TRUE(cc_->Contains('p'));
  EXPECT_FALSE(cc_->Contains('L'));
  EXPECT_FALSE(cc_->Contains('l'));
  EXPECT_FALSE(cc_->Contains('Q'));
  EXPECT_FALSE(cc_->Contains('q'));
}

// Test with lo == hi for a single character
TEST_F(AddFoldedRangeLatin1Test_487, SingleCharacterRange_487) {
  cc_->AddRangeFlags('G', 'G', Regexp::FoldCase);
  EXPECT_TRUE(cc_->Contains('G'));
  EXPECT_TRUE(cc_->Contains('g'));
  EXPECT_FALSE(cc_->Contains('F'));
  EXPECT_FALSE(cc_->Contains('H'));
}

// Test empty CharClassBuilder initially
TEST_F(AddFoldedRangeLatin1Test_487, EmptyBuilderInitially_487) {
  EXPECT_TRUE(cc_->empty());
  EXPECT_EQ(0, cc_->size());
}

// Test that high Latin1 characters (above 127) are added but don't fold to ASCII
TEST_F(AddFoldedRangeLatin1Test_487, HighLatin1CharNoASCIIFold_487) {
  cc_->AddRangeFlags(0x80, 0x80, Regexp::FoldCase);
  EXPECT_TRUE(cc_->Contains(0x80));
  // Should not affect ASCII range
  EXPECT_FALSE(cc_->Contains('A'));
  EXPECT_FALSE(cc_->Contains('a'));
}

}  // namespace re2

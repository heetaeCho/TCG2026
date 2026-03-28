#include "gtest/gtest.h"
#include "re2/re2.h"

// We need access to CycleFoldRune and Rune type
// Based on the re2 codebase, these are in the re2 namespace
namespace re2 {
// Forward declaration
typedef int32_t Rune;
Rune CycleFoldRune(Rune r);
}

class CycleFoldRuneTest_486 : public ::testing::Test {
protected:
};

// Test that ASCII lowercase letters cycle to their uppercase equivalents
TEST_F(CycleFoldRuneTest_486, LowercaseAToUppercase_486) {
  re2::Rune result = re2::CycleFoldRune('a');
  EXPECT_EQ(result, 'A');
}

TEST_F(CycleFoldRuneTest_486, LowercaseZToUppercase_486) {
  re2::Rune result = re2::CycleFoldRune('z');
  EXPECT_EQ(result, 'Z');
}

// Test that ASCII uppercase letters cycle to their lowercase equivalents
TEST_F(CycleFoldRuneTest_486, UppercaseAToLowercase_486) {
  re2::Rune result = re2::CycleFoldRune('A');
  EXPECT_EQ(result, 'a');
}

TEST_F(CycleFoldRuneTest_486, UppercaseZToLowercase_486) {
  re2::Rune result = re2::CycleFoldRune('Z');
  EXPECT_EQ(result, 'z');
}

// Test that digits (no case folding) return themselves
TEST_F(CycleFoldRuneTest_486, DigitReturnsItself_486) {
  re2::Rune result = re2::CycleFoldRune('0');
  EXPECT_EQ(result, '0');
}

TEST_F(CycleFoldRuneTest_486, Digit9ReturnsItself_486) {
  re2::Rune result = re2::CycleFoldRune('9');
  EXPECT_EQ(result, '9');
}

// Test that space (no case folding) returns itself
TEST_F(CycleFoldRuneTest_486, SpaceReturnsItself_486) {
  re2::Rune result = re2::CycleFoldRune(' ');
  EXPECT_EQ(result, ' ');
}

// Test that null character returns itself
TEST_F(CycleFoldRuneTest_486, NullCharReturnsItself_486) {
  re2::Rune result = re2::CycleFoldRune(0);
  EXPECT_EQ(result, 0);
}

// Test cycling property: applying CycleFoldRune repeatedly should cycle back
TEST_F(CycleFoldRuneTest_486, CycleBackToOriginal_LowercaseA_486) {
  re2::Rune r = 'a';
  re2::Rune start = r;
  // Apply CycleFoldRune until we cycle back
  int count = 0;
  do {
    r = re2::CycleFoldRune(r);
    count++;
  } while (r != start && count < 100);
  EXPECT_EQ(r, start);
  EXPECT_LT(count, 100);
}

TEST_F(CycleFoldRuneTest_486, CycleBackToOriginal_UppercaseA_486) {
  re2::Rune r = 'A';
  re2::Rune start = r;
  int count = 0;
  do {
    r = re2::CycleFoldRune(r);
    count++;
  } while (r != start && count < 100);
  EXPECT_EQ(r, start);
  EXPECT_LT(count, 100);
}

// Test various ASCII letters
TEST_F(CycleFoldRuneTest_486, LowercaseMToUppercase_486) {
  re2::Rune result = re2::CycleFoldRune('m');
  EXPECT_EQ(result, 'M');
}

TEST_F(CycleFoldRuneTest_486, UppercaseMToLowercase_486) {
  re2::Rune result = re2::CycleFoldRune('M');
  EXPECT_EQ(result, 'm');
}

// Test punctuation characters return themselves
TEST_F(CycleFoldRuneTest_486, PunctuationReturnsItself_486) {
  EXPECT_EQ(re2::CycleFoldRune('!'), '!');
  EXPECT_EQ(re2::CycleFoldRune('@'), '@');
  EXPECT_EQ(re2::CycleFoldRune('#'), '#');
}

// Test Unicode character with case folding: German sharp s (ß = 0x00DF)
// ß case folds to a cycle involving other characters
TEST_F(CycleFoldRuneTest_486, GermanSharpS_486) {
  re2::Rune r = 0x00DF; // ß
  re2::Rune result = re2::CycleFoldRune(r);
  // Result should either be the same or a different code point in the cycle
  // We just verify it returns a valid rune
  EXPECT_GE(result, 0);
}

// Test Greek letters: α (0x03B1) and Α (0x0391)
TEST_F(CycleFoldRuneTest_486, GreekAlphaLowercase_486) {
  re2::Rune r = 0x03B1; // α
  re2::Rune result = re2::CycleFoldRune(r);
  EXPECT_EQ(result, 0x0391); // Α
}

TEST_F(CycleFoldRuneTest_486, GreekAlphaUppercase_486) {
  re2::Rune r = 0x0391; // Α
  re2::Rune result = re2::CycleFoldRune(r);
  EXPECT_EQ(result, 0x03B1); // α
}

// Test cycling property for a multi-character cycle
// 'k' (0x006B) -> 'K' (0x004B) -> 'K' (0x212A Kelvin sign) -> 'k'
TEST_F(CycleFoldRuneTest_486, KelvinSignCycle_486) {
  re2::Rune r = 'k';
  re2::Rune start = r;
  int count = 0;
  do {
    r = re2::CycleFoldRune(r);
    count++;
  } while (r != start && count < 100);
  EXPECT_EQ(r, start);
  // The cycle for 'k' should be length 3 (k -> K -> Kelvin -> k)
  EXPECT_EQ(count, 3);
}

// Test high Unicode code point that has no case fold
TEST_F(CycleFoldRuneTest_486, HighUnicodeNoCaseFold_486) {
  // A code point well beyond case folding ranges
  re2::Rune r = 0x10000;
  re2::Rune result = re2::CycleFoldRune(r);
  EXPECT_EQ(result, r);
}

// Test boundary: character just before 'A'
TEST_F(CycleFoldRuneTest_486, CharBeforeUpperA_486) {
  re2::Rune r = '@'; // 0x40, just before 'A' (0x41)
  re2::Rune result = re2::CycleFoldRune(r);
  EXPECT_EQ(result, '@');
}

// Test boundary: character just after 'z'
TEST_F(CycleFoldRuneTest_486, CharAfterLowerZ_486) {
  re2::Rune r = '{'; // 0x7B, just after 'z' (0x7A)
  re2::Rune result = re2::CycleFoldRune(r);
  EXPECT_EQ(result, '{');
}

// Test 's' which also has a multi-character cycle (s, S, ſ long s)
TEST_F(CycleFoldRuneTest_486, LowercaseSCycle_486) {
  re2::Rune r = 's';
  re2::Rune start = r;
  int count = 0;
  do {
    r = re2::CycleFoldRune(r);
    count++;
  } while (r != start && count < 100);
  EXPECT_EQ(r, start);
  EXPECT_EQ(count, 3); // s -> S -> ſ (0x017F) -> s
}

// Test negative rune (should return itself)
TEST_F(CycleFoldRuneTest_486, NegativeRuneReturnsItself_486) {
  re2::Rune r = -1;
  re2::Rune result = re2::CycleFoldRune(r);
  EXPECT_EQ(result, r);
}

// Test Cyrillic: а (0x0430) and А (0x0410)
TEST_F(CycleFoldRuneTest_486, CyrillicSmallA_486) {
  re2::Rune r = 0x0430; // а
  re2::Rune result = re2::CycleFoldRune(r);
  EXPECT_EQ(result, 0x0410); // А
}

TEST_F(CycleFoldRuneTest_486, CyrillicCapitalA_486) {
  re2::Rune r = 0x0410; // А
  re2::Rune result = re2::CycleFoldRune(r);
  EXPECT_EQ(result, 0x0430); // а
}

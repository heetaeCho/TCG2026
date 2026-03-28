#include "gtest/gtest.h"
#include "re2/parse.h"
#include "re2/unicode_casefold.h"

namespace re2 {

// Test normal delta application (positive delta)
TEST(ApplyFoldTest_485, PositiveDelta_485) {
  CaseFold f;
  f.lo = 0;
  f.hi = 100;
  f.delta = 5;
  Rune r = 10;
  Rune result = ApplyFold(&f, r);
  EXPECT_EQ(result, 15);
}

// Test normal delta application (negative delta)
TEST(ApplyFoldTest_485, NegativeDelta_485) {
  CaseFold f;
  f.lo = 0;
  f.hi = 100;
  f.delta = -3;
  Rune r = 10;
  Rune result = ApplyFold(&f, r);
  EXPECT_EQ(result, 7);
}

// Test zero delta
TEST(ApplyFoldTest_485, ZeroDelta_485) {
  CaseFold f;
  f.lo = 0;
  f.hi = 100;
  f.delta = 0;
  Rune r = 42;
  Rune result = ApplyFold(&f, r);
  EXPECT_EQ(result, 42);
}

// Test EvenOdd: even rune should return r+1
TEST(ApplyFoldTest_485, EvenOddWithEvenRune_485) {
  CaseFold f;
  f.lo = 0;
  f.hi = 100;
  f.delta = EvenOdd;
  Rune r = 10;  // even
  Rune result = ApplyFold(&f, r);
  EXPECT_EQ(result, 11);
}

// Test EvenOdd: odd rune should return r-1
TEST(ApplyFoldTest_485, EvenOddWithOddRune_485) {
  CaseFold f;
  f.lo = 0;
  f.hi = 100;
  f.delta = EvenOdd;
  Rune r = 11;  // odd
  Rune result = ApplyFold(&f, r);
  EXPECT_EQ(result, 10);
}

// Test OddEven: odd rune should return r+1
TEST(ApplyFoldTest_485, OddEvenWithOddRune_485) {
  CaseFold f;
  f.lo = 0;
  f.hi = 100;
  f.delta = OddEven;
  Rune r = 11;  // odd
  Rune result = ApplyFold(&f, r);
  EXPECT_EQ(result, 12);
}

// Test OddEven: even rune should return r-1
TEST(ApplyFoldTest_485, OddEvenWithEvenRune_485) {
  CaseFold f;
  f.lo = 0;
  f.hi = 100;
  f.delta = OddEven;
  Rune r = 10;  // even
  Rune result = ApplyFold(&f, r);
  EXPECT_EQ(result, 9);
}

// Test EvenOddSkip: when (r - lo) % 2 != 0, rune is unchanged
TEST(ApplyFoldTest_485, EvenOddSkipNoApply_485) {
  CaseFold f;
  f.lo = 0;
  f.hi = 100;
  f.delta = EvenOddSkip;
  Rune r = 1;  // (1 - 0) % 2 == 1, so skip
  Rune result = ApplyFold(&f, r);
  EXPECT_EQ(result, 1);
}

// Test EvenOddSkip: when (r - lo) % 2 == 0, falls through to EvenOdd with even rune
TEST(ApplyFoldTest_485, EvenOddSkipApplyEven_485) {
  CaseFold f;
  f.lo = 0;
  f.hi = 100;
  f.delta = EvenOddSkip;
  Rune r = 10;  // (10 - 0) % 2 == 0, even rune -> r+1
  Rune result = ApplyFold(&f, r);
  EXPECT_EQ(result, 11);
}

// Test EvenOddSkip: when (r - lo) % 2 == 0, falls through to EvenOdd with odd rune (r and lo both odd)
TEST(ApplyFoldTest_485, EvenOddSkipApplyOdd_485) {
  CaseFold f;
  f.lo = 1;
  f.hi = 100;
  f.delta = EvenOddSkip;
  Rune r = 3;  // (3 - 1) % 2 == 0, odd rune -> r-1
  Rune result = ApplyFold(&f, r);
  EXPECT_EQ(result, 2);
}

// Test OddEvenSkip: when (r - lo) % 2 != 0, rune is unchanged
TEST(ApplyFoldTest_485, OddEvenSkipNoApply_485) {
  CaseFold f;
  f.lo = 0;
  f.hi = 100;
  f.delta = OddEvenSkip;
  Rune r = 1;  // (1 - 0) % 2 == 1, so skip
  Rune result = ApplyFold(&f, r);
  EXPECT_EQ(result, 1);
}

// Test OddEvenSkip: when (r - lo) % 2 == 0, falls through to OddEven with odd rune
TEST(ApplyFoldTest_485, OddEvenSkipApplyOdd_485) {
  CaseFold f;
  f.lo = 1;
  f.hi = 100;
  f.delta = OddEvenSkip;
  Rune r = 11;  // (11 - 1) % 2 == 0, odd rune -> r+1
  Rune result = ApplyFold(&f, r);
  EXPECT_EQ(result, 12);
}

// Test OddEvenSkip: when (r - lo) % 2 == 0, falls through to OddEven with even rune
TEST(ApplyFoldTest_485, OddEvenSkipApplyEven_485) {
  CaseFold f;
  f.lo = 0;
  f.hi = 100;
  f.delta = OddEvenSkip;
  Rune r = 10;  // (10 - 0) % 2 == 0, even rune -> r-1
  Rune result = ApplyFold(&f, r);
  EXPECT_EQ(result, 9);
}

// Test with large delta
TEST(ApplyFoldTest_485, LargeDelta_485) {
  CaseFold f;
  f.lo = 0;
  f.hi = 100000;
  f.delta = 10000;
  Rune r = 5000;
  Rune result = ApplyFold(&f, r);
  EXPECT_EQ(result, 15000);
}

// Test boundary: rune equals lo for EvenOddSkip
TEST(ApplyFoldTest_485, EvenOddSkipRuneEqualsLo_485) {
  CaseFold f;
  f.lo = 10;
  f.hi = 100;
  f.delta = EvenOddSkip;
  Rune r = 10;  // (10 - 10) % 2 == 0, even rune -> r+1
  Rune result = ApplyFold(&f, r);
  EXPECT_EQ(result, 11);
}

// Test boundary: rune equals lo for OddEvenSkip
TEST(ApplyFoldTest_485, OddEvenSkipRuneEqualsLo_485) {
  CaseFold f;
  f.lo = 11;
  f.hi = 100;
  f.delta = OddEvenSkip;
  Rune r = 11;  // (11 - 11) % 2 == 0, odd rune -> r+1
  Rune result = ApplyFold(&f, r);
  EXPECT_EQ(result, 12);
}

// Test delta of 1
TEST(ApplyFoldTest_485, DeltaOne_485) {
  CaseFold f;
  f.lo = 0;
  f.hi = 100;
  f.delta = 1;
  Rune r = 65;  // 'A'
  Rune result = ApplyFold(&f, r);
  EXPECT_EQ(result, 66);
}

// Test delta of -1
TEST(ApplyFoldTest_485, DeltaNegativeOne_485) {
  CaseFold f;
  f.lo = 0;
  f.hi = 100;
  f.delta = -1;
  Rune r = 66;
  Rune result = ApplyFold(&f, r);
  EXPECT_EQ(result, 65);
}

// Test typical case folding delta (like 'a' - 'A' = 32)
TEST(ApplyFoldTest_485, TypicalCaseFoldDelta32_485) {
  CaseFold f;
  f.lo = 65;
  f.hi = 90;
  f.delta = 32;
  Rune r = 65;  // 'A' -> 'a'
  Rune result = ApplyFold(&f, r);
  EXPECT_EQ(result, 97);
}

// Test EvenOdd with rune = 0 (even)
TEST(ApplyFoldTest_485, EvenOddWithZero_485) {
  CaseFold f;
  f.lo = 0;
  f.hi = 100;
  f.delta = EvenOdd;
  Rune r = 0;
  Rune result = ApplyFold(&f, r);
  EXPECT_EQ(result, 1);
}

// Test OddEven with rune = 1 (odd)
TEST(ApplyFoldTest_485, OddEvenWithOne_485) {
  CaseFold f;
  f.lo = 0;
  f.hi = 100;
  f.delta = OddEven;
  Rune r = 1;
  Rune result = ApplyFold(&f, r);
  EXPECT_EQ(result, 2);
}

}  // namespace re2

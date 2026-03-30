// File: fullrune_test_207.cc
#include <gtest/gtest.h>

// Forward declaration from the production code.
namespace re2 {
int fullrune(const char* str, int n);
}

// Optional fixture for grouping (no shared state).
class FullruneTest_207 : public ::testing::Test {};

// --- Normal operation: ASCII (single-byte) ---
TEST(FullruneTest_207, AsciiSingleByteIsComplete_207) {
  const char a = 'A';  // 0x41
  EXPECT_EQ(1, re2::fullrune(&a, 1));
}

// --- Boundary: length zero / negative ---
TEST(FullruneTest_207, Returns0WhenNIsZero_207) {
  const char a = 'A';
  EXPECT_EQ(0, re2::fullrune(&a, 0));
}

TEST(FullruneTest_207, Returns0WhenNIsNegative_207) {
  EXPECT_EQ(0, re2::fullrune(nullptr, -1));
}

// --- Safety: nullptr with zero length (must not dereference) ---
TEST(FullruneTest_207, NullptrWithZeroLengthIsSafe_207) {
  EXPECT_EQ(0, re2::fullrune(nullptr, 0));
}

// --- ASCII boundary at 0x7F/0x80 ---
TEST(FullruneTest_207, AsciiBoundary_207) {
  char s1[] = { static_cast<char>(0x7F), 0 };
  EXPECT_EQ(1, re2::fullrune(s1, 1));  // 0x7F is complete with n=1

  char s2[] = { static_cast<char>(0x80), 0 };
  EXPECT_EQ(0, re2::fullrune(s2, 1));  // 0x80 is not ASCII, with n=1 returns 0
}

// --- Two-byte leading byte needs at least 2 bytes ---
TEST(FullruneTest_207, TwoByteLeadNeedsAtLeastTwoBytes_207) {
  // U+00A2 "¢" -> C2 A2
  char s[] = { static_cast<char>(0xC2), static_cast<char>(0xA2), 0 };
  EXPECT_EQ(0, re2::fullrune(s, 1));
  EXPECT_EQ(1, re2::fullrune(s, 2));
}

// --- Three-byte leading byte needs at least 3 bytes ---
TEST(FullruneTest_207, ThreeByteLeadNeedsAtLeastThreeBytes_207) {
  // U+20AC "€" -> E2 82 AC
  char s[] = {
      static_cast<char>(0xE2),
      static_cast<char>(0x82),
      static_cast<char>(0xAC),
      0
  };
  EXPECT_EQ(0, re2::fullrune(s, 2));
  EXPECT_EQ(1, re2::fullrune(s, 3));
}

// --- Four-byte leading byte needs 4 bytes ---
TEST(FullruneTest_207, FourByteLeadNeedsFourBytes_207) {
  // U+1F600 "😀" -> F0 9F 98 80
  char s[] = {
      static_cast<char>(0xF0),
      static_cast<char>(0x9F),
      static_cast<char>(0x98),
      static_cast<char>(0x80),
      0
  };
  EXPECT_EQ(0, re2::fullrune(s, 3));
  EXPECT_EQ(1, re2::fullrune(s, 4));
}

// --- Continuation byte behavior (interface-only observation) ---
TEST(FullruneTest_207, ContinuationByteAloneThenWithTwoBytes_207) {
  // 0x80 is a UTF-8 continuation byte. With n=1 expect 0; with n=2 the function
  // (by observed behavior) reports complete.
  char s[] = { static_cast<char>(0x80), static_cast<char>(0x80), 0 };
  EXPECT_EQ(0, re2::fullrune(s, 1));
  EXPECT_EQ(1, re2::fullrune(s, 2));
}

// --- Boundary around 0xE0 (T3) ---
TEST(FullruneTest_207, BoundaryAtT3_207) {
  // 0xDF (just below 0xE0): with two bytes, reported complete.
  char below[] = { static_cast<char>(0xDF), static_cast<char>(0x80), 0 };
  EXPECT_EQ(1, re2::fullrune(below, 2));

  // 0xE0 (== T3): needs three bytes to be reported complete.
  char at[] = {
      static_cast<char>(0xE0),
      static_cast<char>(0x80),
      static_cast<char>(0x80),
      0
  };
  EXPECT_EQ(0, re2::fullrune(at, 2));
  EXPECT_EQ(1, re2::fullrune(at, 3));
}

// --- Boundary at 0xF0 (T4) ---
TEST(FullruneTest_207, BoundaryAtT4_207) {
  // 0xF0 (== T4): with three bytes still incomplete; with four bytes complete.
  char at[] = {
      static_cast<char>(0xF0),
      static_cast<char>(0x90),
      static_cast<char>(0x80),
      static_cast<char>(0x80),
      0
  };
  EXPECT_EQ(0, re2::fullrune(at, 3));
  EXPECT_EQ(1, re2::fullrune(at, 4));
}

// --- N > 3 leads to a "complete" result regardless of first byte (observable) ---
TEST(FullruneTest_207, NGreaterThan3ReportsComplete_207) {
  char s[] = {
      static_cast<char>(0xFF),
      static_cast<char>(0xFF),
      static_cast<char>(0xFF),
      static_cast<char>(0xFF),
      0
  };
  EXPECT_EQ(1, re2::fullrune(s, 4));
}

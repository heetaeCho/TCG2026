// File: ./TestProjects/re2/re2/tests/maxrune_test.cc

#include <gtest/gtest.h>

// Include the implementation unit to make the internal static symbol visible
// in this translation unit without re-implementing it.
#include "re2/compile.cc"

using re2::MaxRune;

TEST(MaxRuneTest_302, OneByteAscii_302) {
  // Normal operation: 1-byte UTF-8 should cap at 0x7F (127)
  EXPECT_EQ(127, MaxRune(1));
}

TEST(MaxRuneTest_302, TwoBytes_302) {
  // Normal operation: 2-byte UTF-8 sequence -> 0x7FF (2047)
  EXPECT_EQ(2047, MaxRune(2));
}

TEST(MaxRuneTest_302, ThreeBytes_302) {
  // Normal operation: 3-byte UTF-8 sequence -> 0xFFFF (65535)
  EXPECT_EQ(65535, MaxRune(3));
}

TEST(MaxRuneTest_302, FourBytes_302) {
  // Normal operation: 4-byte UTF-8 sequence -> 0x1FFFFF (2,097,151)
  // Note: This is the function's observable return, not a statement about Unicode limits.
  EXPECT_EQ(2097151, MaxRune(4));
}

TEST(MaxRuneTest_302, ZeroLenBehavior_302) {
  // Boundary condition (len == 0). The function's observable behavior returns 1.
  // We do not assert on "correctness" of input domain; just verify the black-box output.
  EXPECT_EQ(1, MaxRune(0));
}

TEST(MaxRuneTest_302, FiveBytesBehavior_302) {
  // Boundary-ish / extension beyond common UTF-8 (len == 5) — still an observable output.
  // (1 << 26) - 1 = 67,108,863
  EXPECT_EQ(67108863, MaxRune(5));
}

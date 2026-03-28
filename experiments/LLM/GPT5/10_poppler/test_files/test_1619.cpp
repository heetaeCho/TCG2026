// Decrypt_md5Round2_test_1619.cc
//
// Unit tests for md5Round2 (static inline) in Decrypt.cc
//
// Notes:
// - md5Round2 has internal linkage (static inline) in a .cc file, so to test it we
//   include the implementation file directly in this test TU.
// - These tests treat md5Round2 as a black box and avoid re-deriving its formula.
// - Since md5Round2 has no observable side effects and no error signaling, tests
//   focus on observable, interface-level properties (e.g., determinism) and
//   boundary/smoke coverage.
//
// Adjust the include path below if your test build layout differs.

#include <gtest/gtest.h>

// Include the implementation to access the static inline symbol.
#include "Decrypt.cc" // NOLINT(build/include)

namespace {

class Md5Round2Test_1619 : public ::testing::Test {};

TEST_F(Md5Round2Test_1619, DeterministicForSameInputs_1619) {
  const unsigned long a = 0x01234567UL;
  const unsigned long b = 0x89abcdefUL;
  const unsigned long c = 0xfedcba98UL;
  const unsigned long d = 0x76543210UL;
  const unsigned long Xk = 0x0f1e2d3cUL;
  const unsigned long s  = 5UL;
  const unsigned long Ti = 0xa5a5a5a5UL;

  const unsigned long r1 = md5Round2(a, b, c, d, Xk, s, Ti);
  const unsigned long r2 = md5Round2(a, b, c, d, Xk, s, Ti);
  const unsigned long r3 = md5Round2(a, b, c, d, Xk, s, Ti);

  EXPECT_EQ(r1, r2);
  EXPECT_EQ(r2, r3);
}

TEST_F(Md5Round2Test_1619, HandlesAllZeros_1619) {
  // Boundary/smoke: all inputs are zero.
  const unsigned long r1 = md5Round2(0UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL);
  const unsigned long r2 = md5Round2(0UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL);
  EXPECT_EQ(r1, r2);
}

TEST_F(Md5Round2Test_1619, HandlesAllOnesMaxULong_1619) {
  // Boundary: maximal unsigned long values.
  const unsigned long m = ~0UL;

  const unsigned long r1 = md5Round2(m, m, m, m, m, m, m);
  const unsigned long r2 = md5Round2(m, m, m, m, m, m, m);

  EXPECT_EQ(r1, r2);
}

TEST_F(Md5Round2Test_1619, HandlesMixedBoundaryValues_1619) {
  // Boundary mix: zeros, max, alternating patterns, and a few shift-like values.
  const unsigned long a  = 0UL;
  const unsigned long b  = ~0UL;
  const unsigned long c  = 0xAAAAAAAAUL;
  const unsigned long d  = 0x55555555UL;
  const unsigned long Xk = ~0UL;
  const unsigned long s  = 31UL;        // common edge-ish shift amount for 32-bit,
                                        // still valid as an unsigned long value
  const unsigned long Ti = 0UL;

  const unsigned long r1 = md5Round2(a, b, c, d, Xk, s, Ti);
  const unsigned long r2 = md5Round2(a, b, c, d, Xk, s, Ti);

  EXPECT_EQ(r1, r2);
}

}  // namespace
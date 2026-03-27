// Decrypt_md5Round1_test_1618.cc
#include <gtest/gtest.h>

#include <cstdint>

// NOTE:
// md5Round1 is defined as `static inline` in Decrypt.cc, so it is not link-visible.
// The usual way to unit-test such a symbol is to include the implementation file
// into this test translation unit.
#include "Decrypt.cc"

namespace {

class Md5Round1Test_1618 : public ::testing::Test {};

TEST_F(Md5Round1Test_1618, MatchesKnownVector_1618) {
  const unsigned long a  = 0x67452301UL;
  const unsigned long b  = 0xefcdab89UL;
  const unsigned long c  = 0x98badcfeUL;
  const unsigned long d  = 0x10325476UL;
  const unsigned long Xk = 0x00000000UL;
  const unsigned long s  = 7UL;
  const unsigned long Ti = 0xd76aa478UL;

  const uint32_t out = static_cast<uint32_t>(md5Round1(a, b, c, d, Xk, s, Ti));
  EXPECT_EQ(out, 0xa51fe774u);
}

TEST_F(Md5Round1Test_1618, ZeroInputsProduceZero_1618) {
  const uint32_t out = static_cast<uint32_t>(md5Round1(0UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL));
  EXPECT_EQ(out, 0u);
}

TEST_F(Md5Round1Test_1618, AllOnesAndMaxShiftMatchesKnownVector_1618) {
  const unsigned long all = ~0UL;

  // Use values that remain meaningful even if unsigned long is wider than 32 bits:
  // the comparison is done on the low 32 bits of the function's return value.
  const uint32_t out = static_cast<uint32_t>(md5Round1(all, all, all, all, all, 31UL, all));
  EXPECT_EQ(out, 0x7ffffffdu);
}

TEST_F(Md5Round1Test_1618, DeterministicForSameInputs_1618) {
  const unsigned long a  = 0x01234567UL;
  const unsigned long b  = 0x89abcdefUL;
  const unsigned long c  = 0xfedcba98UL;
  const unsigned long d  = 0x76543210UL;
  const unsigned long Xk = 0x0f1e2d3cUL;
  const unsigned long s  = 12UL;
  const unsigned long Ti = 0x12345678UL;

  const uint32_t out1 = static_cast<uint32_t>(md5Round1(a, b, c, d, Xk, s, Ti));
  const uint32_t out2 = static_cast<uint32_t>(md5Round1(a, b, c, d, Xk, s, Ti));
  EXPECT_EQ(out1, out2);
  EXPECT_EQ(out1, 0xb1e70004u);  // Additional known-value check for the same inputs.
}

TEST_F(Md5Round1Test_1618, ChangingOneParameterChangesResult_1618) {
  const unsigned long a  = 0x01234567UL;
  const unsigned long b  = 0x89abcdefUL;
  const unsigned long c  = 0xfedcba98UL;
  const unsigned long d  = 0x76543210UL;
  const unsigned long Xk = 0x0f1e2d3cUL;
  const unsigned long s  = 12UL;

  const uint32_t out_base = static_cast<uint32_t>(md5Round1(a, b, c, d, Xk, s, 0x12345678UL));
  const uint32_t out_alt  = static_cast<uint32_t>(md5Round1(a, b, c, d, Xk, s, 0x12345679UL));

  EXPECT_NE(out_base, out_alt);
}

}  // namespace
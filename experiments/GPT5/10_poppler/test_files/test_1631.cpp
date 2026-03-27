// Decrypt_sha256Sigma1_test_1631.cc
#include <gtest/gtest.h>

#include <cstdint>
#include <type_traits>

// NOTE:
// sha256Sigma1() is declared `static inline` inside Decrypt.cc, so it has internal linkage.
// To test it directly without re-implementing it, we include the implementation file here.
// This test target should be built so that Decrypt.cc is NOT also separately compiled/linked
// into the same binary (otherwise you may get duplicate symbol link errors from other
// non-static definitions in Decrypt.cc).
#include "Decrypt.cc"

namespace {

class Sha256Sigma1Test_1631 : public ::testing::Test {};

TEST_F(Sha256Sigma1Test_1631, ReturnsExpectedForZero_1631) {
  EXPECT_EQ(sha256Sigma1(0u), 0u);
}

TEST_F(Sha256Sigma1Test_1631, ReturnsExpectedForOne_1631) {
  // Precomputed expected: rotr(1,6) ^ rotr(1,11) ^ rotr(1,25) == 0x04200080
  EXPECT_EQ(sha256Sigma1(1u), 0x04200080u);
}

TEST_F(Sha256Sigma1Test_1631, ReturnsExpectedForAllOnes_1631) {
  // For x = 0xFFFFFFFF, any rotate-right returns the same value, so XOR stays 0xFFFFFFFF.
  EXPECT_EQ(sha256Sigma1(0xFFFFFFFFu), 0xFFFFFFFFu);
}

TEST_F(Sha256Sigma1Test_1631, ReturnsExpectedForHighBitSet_1631) {
  // Precomputed expected for 0x80000000: 0x02100040
  EXPECT_EQ(sha256Sigma1(0x80000000u), 0x02100040u);
}

TEST_F(Sha256Sigma1Test_1631, ReturnsExpectedForTypicalPattern_1631) {
  // Precomputed expected for 0x12345678: 0x3561ABDA
  EXPECT_EQ(sha256Sigma1(0x12345678u), 0x3561ABDAu);
}

TEST_F(Sha256Sigma1Test_1631, ReturnsExpectedForDeadBeef_1631) {
  // Precomputed expected for 0xDEADBEEF: 0x345E14A3
  EXPECT_EQ(sha256Sigma1(0xDEADBEEFu), 0x345E14A3u);
}

TEST_F(Sha256Sigma1Test_1631, ReturnsExpectedForRepeatingNibblePatterns_1631) {
  // Precomputed expected:
  //   x = 0x0F0F0F0F => 0x5A5A5A5A
  //   x = 0xF0F0F0F0 => 0xA5A5A5A5
  EXPECT_EQ(sha256Sigma1(0x0F0F0F0Fu), 0x5A5A5A5Au);
  EXPECT_EQ(sha256Sigma1(0xF0F0F0F0u), 0xA5A5A5A5u);
}

TEST_F(Sha256Sigma1Test_1631, IsDeterministicForSameInput_1631) {
  const unsigned int x = 0xA1B2C3D4u;
  const unsigned int y1 = sha256Sigma1(x);
  const unsigned int y2 = sha256Sigma1(x);
  const unsigned int y3 = sha256Sigma1(x);
  EXPECT_EQ(y1, y2);
  EXPECT_EQ(y2, y3);
}

TEST_F(Sha256Sigma1Test_1631, ReturnTypeIsUnsignedInt_1631) {
  // Boundary/contract check on the declared interface.
  static_assert(std::is_same_v<decltype(sha256Sigma1(0u)), unsigned int>,
                "sha256Sigma1 must return unsigned int");
  SUCCEED();
}

}  // namespace
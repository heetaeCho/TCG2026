// Decrypt_rotr_test_1636.cc
#include <gtest/gtest.h>
#include <cstdint>
#include <vector>

// NOTE:
// `rotr` is declared `static inline` in Decrypt.cc (internal linkage).
// To test it without re-implementing it, include the implementation unit here.
// If your build already compiles Decrypt.cc separately into the test binary,
// do NOT include it here; instead, adjust your build to compile this test as
// the only TU that includes Decrypt.cc, or expose a test hook.
#include "Decrypt.cc"

namespace {

class RotrTest_1636 : public ::testing::Test {};

// Helper used only for *properties* (not re-implementing rotr):
// We avoid undefined behavior by never using n==0 or n>=64.
static inline uint64_t RotrTwiceShouldRoundTrip(uint64_t x, uint64_t n) {
  // rotr(rotr(x, n), 64-n) == x for 1<=n<=63
  return rotr(rotr(x, n), 64u - n);
}

TEST_F(RotrTest_1636, RotatesBy8BytesAsExpected_1636) {
  const uint64_t x = 0x0123456789ABCDEFULL;
  const uint64_t out = rotr(x, 8);
  EXPECT_EQ(out, 0xEF0123456789ABCDULL);
}

TEST_F(RotrTest_1636, RotateRightBy1MovesLsbToMsb_1636) {
  const uint64_t x = 0x0000000000000001ULL;
  const uint64_t out = rotr(x, 1);
  EXPECT_EQ(out, 0x8000000000000000ULL);
}

TEST_F(RotrTest_1636, RotateRightBy63MovesMsbToLsb_1636) {
  const uint64_t x = 0x8000000000000000ULL;
  const uint64_t out = rotr(x, 63);
  EXPECT_EQ(out, 0x0000000000000001ULL);
}

TEST_F(RotrTest_1636, ZeroStaysZeroForVariousRotations_1636) {
  const uint64_t x = 0ULL;
  for (uint64_t n : {1u, 2u, 7u, 8u, 31u, 32u, 63u}) {
    EXPECT_EQ(rotr(x, n), 0ULL) << "n=" << n;
  }
}

TEST_F(RotrTest_1636, AllOnesStaysAllOnesForVariousRotations_1636) {
  const uint64_t x = ~0ULL;
  for (uint64_t n : {1u, 5u, 16u, 32u, 63u}) {
    EXPECT_EQ(rotr(x, n), ~0ULL) << "n=" << n;
  }
}

TEST_F(RotrTest_1636, RoundTripPropertyHoldsForMultipleInputs_1636) {
  const std::vector<uint64_t> inputs = {
      0x0000000000000001ULL,
      0x8000000000000000ULL,
      0x0123456789ABCDEFULL,
      0xFEDCBA9876543210ULL,
      0x0F0F0F0F0F0F0F0FULL,
      0xF0F0F0F0F0F0F0F0ULL,
  };

  const std::vector<uint64_t> rotations = {1u, 2u, 7u, 8u, 13u, 31u, 32u, 33u, 63u};

  for (uint64_t x : inputs) {
    for (uint64_t n : rotations) {
      ASSERT_GE(n, 1u);
      ASSERT_LE(n, 63u);
      EXPECT_EQ(RotrTwiceShouldRoundTrip(x, n), x) << "x=0x" << std::hex << x << " n=" << std::dec
                                                   << n;
    }
  }
}

// Boundary / exceptional notes:
// n==0 or n>=64 would involve shifts by 64 (undefined behavior in C++) for this implementation.
// Since the interface provides no contract for those values, tests intentionally avoid them.

}  // namespace
// File: util/crc32c_unmask_test.cc
#include <cstdint>
#include "gtest/gtest.h"
#include "util/crc32c.h"

using leveldb::crc32c::Unmask;
using leveldb::crc32c::kMaskDelta;

// Basic correctness on a few representative values
TEST(Crc32cUnmaskTest_322, ReturnsExpectedForZero_322) {
  const uint32_t masked = 0u;
  // Precomputed expected: 0x8A942EBE
  EXPECT_EQ(static_cast<uint32_t>(0x8A942EBE), Unmask(masked));
}

TEST(Crc32cUnmaskTest_322, ReturnsExpectedForOne_322) {
  const uint32_t masked = 1u;
  // Precomputed expected: 0x8A94AEBE
  EXPECT_EQ(static_cast<uint32_t>(0x8A94AEBE), Unmask(masked));
}

// Boundary: when masked equals kMaskDelta
TEST(Crc32cUnmaskTest_322, ReturnsZeroWhenMaskedEqualsDelta_322) {
  const uint32_t masked = kMaskDelta;
  // Precomputed expected: 0x00000000
  EXPECT_EQ(static_cast<uint32_t>(0x00000000), Unmask(masked));
}

// Boundary: maximum 32-bit value
TEST(Crc32cUnmaskTest_322, ReturnsExpectedForMaxUint32_322) {
  const uint32_t masked = 0xFFFFFFFFu;
  // Precomputed expected: 0x8A93AEBE
  EXPECT_EQ(static_cast<uint32_t>(0x8A93AEBE), Unmask(masked));
}

// Typical/non-boundary input
TEST(Crc32cUnmaskTest_322, ReturnsExpectedForArbitraryValue_322) {
  const uint32_t masked = 0x12345678u;
  // Precomputed expected: 0xB5D037D8
  EXPECT_EQ(static_cast<uint32_t>(0xB5D037D8), Unmask(masked));
}

// Boundary around high bit set
TEST(Crc32cUnmaskTest_322, ReturnsExpectedForHighBitSet_322) {
  const uint32_t masked = 0x80000000u;
  // Precomputed expected: 0x8A946EBE
  EXPECT_EQ(static_cast<uint32_t>(0x8A946EBE), Unmask(masked));
}

// Small non-zero value to exercise wrap and rotation behavior (treated as black box)
TEST(Crc32cUnmaskTest_322, ReturnsExpectedForSmallNonZero_322) {
  const uint32_t masked = 0x00010000u;
  // Precomputed expected: 0x0A942EBF
  EXPECT_EQ(static_cast<uint32_t>(0x0A942EBF), Unmask(masked));
}

// Determinism: calling multiple times with same input yields the same output
TEST(Crc32cUnmaskTest_322, DeterministicForSameInput_322) {
  const uint32_t masked = 0xCAFEBABEu;
  const uint32_t first  = Unmask(masked);
  const uint32_t second = Unmask(masked);
  EXPECT_EQ(first, second);
}

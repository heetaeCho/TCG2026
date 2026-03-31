#include "util/crc32c.h"
#include <gtest/gtest.h>
#include <cstdint>

namespace leveldb {
namespace crc32c {

TEST(CRC32CMaskTest_321, MaskOfZero_321) {
  uint32_t crc = 0;
  uint32_t masked = Mask(crc);
  // Mask(0) = ((0 >> 15) | (0 << 17)) + kMaskDelta = 0 + kMaskDelta
  EXPECT_EQ(masked, kMaskDelta);
}

TEST(CRC32CMaskTest_321, MaskOfOne_321) {
  uint32_t crc = 1;
  uint32_t masked = Mask(crc);
  // ((1 >> 15) | (1 << 17)) + kMaskDelta = (0 | 131072) + kMaskDelta = 131072 + 2726488792
  uint32_t expected = ((crc >> 15) | (crc << 17)) + kMaskDelta;
  EXPECT_EQ(masked, expected);
}

TEST(CRC32CMaskTest_321, MaskOfMaxUint32_321) {
  uint32_t crc = 0xFFFFFFFF;
  uint32_t masked = Mask(crc);
  // ((0xFFFFFFFF >> 15) | (0xFFFFFFFF << 17)) + kMaskDelta
  // = (0x1FFFF | 0xFFFE0000) + kMaskDelta (both OR to 0xFFFFFFFF)
  // = 0xFFFFFFFF + kMaskDelta (with wrapping)
  uint32_t expected = ((crc >> 15) | (crc << 17)) + kMaskDelta;
  EXPECT_EQ(masked, expected);
}

TEST(CRC32CMaskTest_321, MaskOfKnownValue_321) {
  uint32_t crc = 0x12345678;
  uint32_t masked = Mask(crc);
  uint32_t expected = ((crc >> 15) | (crc << 17)) + kMaskDelta;
  EXPECT_EQ(masked, expected);
}

TEST(CRC32CMaskTest_321, MaskRotatesBitsCorrectly_321) {
  // Use a value where we can verify the rotation part independently
  uint32_t crc = 0x80000000; // only MSB set
  uint32_t rotated = (crc >> 15) | (crc << 17);
  // crc >> 15 = 0x00010000, crc << 17 = 0x00000000 (shifted out)
  EXPECT_EQ(rotated, 0x00010000u);
  uint32_t masked = Mask(crc);
  EXPECT_EQ(masked, rotated + kMaskDelta);
}

TEST(CRC32CMaskTest_321, MaskOfSmallValues_321) {
  for (uint32_t crc = 0; crc < 256; crc++) {
    uint32_t masked = Mask(crc);
    uint32_t expected = ((crc >> 15) | (crc << 17)) + kMaskDelta;
    EXPECT_EQ(masked, expected) << "Failed for crc=" << crc;
  }
}

TEST(CRC32CMaskTest_321, MaskOfPowerOfTwo_321) {
  for (int bit = 0; bit < 32; bit++) {
    uint32_t crc = 1u << bit;
    uint32_t masked = Mask(crc);
    uint32_t expected = ((crc >> 15) | (crc << 17)) + kMaskDelta;
    EXPECT_EQ(masked, expected) << "Failed for bit=" << bit;
  }
}

TEST(CRC32CMaskTest_321, MaskDifferentInputsProduceDifferentOutputsMostly_321) {
  // While not guaranteed for all pairs, for these specific values they should differ
  uint32_t m1 = Mask(0);
  uint32_t m2 = Mask(1);
  uint32_t m3 = Mask(2);
  EXPECT_NE(m1, m2);
  EXPECT_NE(m2, m3);
  EXPECT_NE(m1, m3);
}

TEST(CRC32CMaskTest_321, MaskIsConsistentForSameInput_321) {
  uint32_t crc = 0xDEADBEEF;
  uint32_t masked1 = Mask(crc);
  uint32_t masked2 = Mask(crc);
  EXPECT_EQ(masked1, masked2);
}

TEST(CRC32CMaskTest_321, KMaskDeltaValue_321) {
  EXPECT_EQ(kMaskDelta, 2726488792UL);
}

TEST(CRC32CMaskTest_321, MaskWrapsAroundOn32Bit_321) {
  // Choose a value such that rotation + kMaskDelta overflows 32 bits
  uint32_t crc = 0x7FFFFFFF;
  uint32_t masked = Mask(crc);
  uint32_t expected = ((crc >> 15) | (crc << 17)) + kMaskDelta;
  EXPECT_EQ(masked, expected);
}

}  // namespace crc32c
}  // namespace leveldb

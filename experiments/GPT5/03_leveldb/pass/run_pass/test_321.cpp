// File: util/crc32c_mask_test.cc
#include "gtest/gtest.h"
#include "util/crc32c.h"

namespace {

using leveldb::crc32c::Mask;

class CRC32C_MaskTest_321 : public ::testing::Test {};

TEST_F(CRC32C_MaskTest_321, ReturnsExpectedForZero_321) {
  // Precomputed expected value for input 0x00000000
  // Expected = 0xA282EAD8
  uint32_t input = 0x00000000u;
  uint32_t expected = 0xA282EAD8u;
  EXPECT_EQ(expected, Mask(input));
}

TEST_F(CRC32C_MaskTest_321, ReturnsExpectedForOne_321) {
  // Precomputed expected value for input 0x00000001
  // Expected = 0xA284EAD8
  uint32_t input = 0x00000001u;
  uint32_t expected = 0xA284EAD8u;
  EXPECT_EQ(expected, Mask(input));
}

TEST_F(CRC32C_MaskTest_321, ReturnsExpectedForMaxUint32_321) {
  // Precomputed expected value for input 0xFFFFFFFF
  // Expected = 0xA282EAD7
  uint32_t input = 0xFFFFFFFFu;
  uint32_t expected = 0xA282EAD7u;
  EXPECT_EQ(expected, Mask(input));
}

TEST_F(CRC32C_MaskTest_321, ReturnsExpectedForTypicalValue_321) {
  // Precomputed expected value for input 0x12345678
  // Expected = 0x4F730F40
  uint32_t input = 0x12345678u;
  uint32_t expected = 0x4F730F40u;
  EXPECT_EQ(expected, Mask(input));
}

TEST_F(CRC32C_MaskTest_321, ReturnsExpectedForAnotherTypicalValue_321) {
  // Precomputed expected value for input 0xDEADBEEF
  // Expected = 0x2062A833
  uint32_t input = 0xDEADBEEFu;
  uint32_t expected = 0x2062A833u;
  EXPECT_EQ(expected, Mask(input));
}

TEST_F(CRC32C_MaskTest_321, HandlesSignBoundaryValues_321) {
  // Precomputed values for 0x80000000 and 0x7FFFFFFF
  // Expected(0x80000000) = 0xA283EAD8
  // Expected(0x7FFFFFFF) = 0xA281EAD7
  EXPECT_EQ(0xA283EAD8u, Mask(0x80000000u));
  EXPECT_EQ(0xA281EAD7u, Mask(0x7FFFFFFFu));
}

TEST_F(CRC32C_MaskTest_321, DeterministicForSameInput_321) {
  uint32_t input = 0x12345678u;
  uint32_t first = Mask(input);
  uint32_t second = Mask(input);
  EXPECT_EQ(first, second);
}

}  // namespace

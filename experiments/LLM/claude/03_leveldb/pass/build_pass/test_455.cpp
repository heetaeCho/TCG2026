#include "gtest/gtest.h"
#include "util/crc32c.h"
#include <string>
#include <vector>
#include <cstring>

namespace leveldb {
namespace crc32c {

// Test CRC32C of empty data
TEST(CRC32CTest_455, EmptyData_455) {
  uint32_t crc = Value("", 0);
  // CRC of empty data should be 0
  EXPECT_EQ(0u, crc);
}

// Test CRC32C of a single byte
TEST(CRC32CTest_455, SingleByte_455) {
  char data = 'a';
  uint32_t crc = Value(&data, 1);
  EXPECT_NE(0u, crc);
}

// Test CRC32C of known string "hello world"
TEST(CRC32CTest_455, KnownString_455) {
  std::string data = "hello world";
  uint32_t crc = Value(data.data(), data.size());
  // The CRC should be deterministic
  uint32_t crc2 = Value(data.data(), data.size());
  EXPECT_EQ(crc, crc2);
}

// Test that different data produces different CRCs
TEST(CRC32CTest_455, DifferentDataDifferentCRC_455) {
  std::string data1 = "hello";
  std::string data2 = "world";
  uint32_t crc1 = Value(data1.data(), data1.size());
  uint32_t crc2 = Value(data2.data(), data2.size());
  EXPECT_NE(crc1, crc2);
}

// Test Extend with initial CRC of 0 equals Value
TEST(CRC32CTest_455, ExtendFromZeroEqualsValue_455) {
  std::string data = "test data for crc";
  uint32_t crc_value = Value(data.data(), data.size());
  uint32_t crc_extend = Extend(0, data.data(), data.size());
  EXPECT_EQ(crc_value, crc_extend);
}

// Test that Extend is composable: CRC(A+B) == Extend(CRC(A), B)
TEST(CRC32CTest_455, ExtendComposition_455) {
  std::string part1 = "hello ";
  std::string part2 = "world";
  std::string full = part1 + part2;

  uint32_t crc_full = Value(full.data(), full.size());
  uint32_t crc_part1 = Value(part1.data(), part1.size());
  uint32_t crc_composed = Extend(crc_part1, part2.data(), part2.size());

  EXPECT_EQ(crc_full, crc_composed);
}

// Test Extend with zero-length data returns the same CRC
TEST(CRC32CTest_455, ExtendZeroLength_455) {
  std::string data = "some data";
  uint32_t crc = Value(data.data(), data.size());
  uint32_t crc_extended = Extend(crc, "", 0);
  EXPECT_EQ(crc, crc_extended);
}

// Test CRC32C of all zeros
TEST(CRC32CTest_455, AllZeros_455) {
  char data[100];
  memset(data, 0, sizeof(data));
  uint32_t crc = Value(data, sizeof(data));
  EXPECT_NE(0u, crc);
}

// Test CRC32C of all 0xFF bytes
TEST(CRC32CTest_455, AllOnes_455) {
  char data[100];
  memset(data, 0xFF, sizeof(data));
  uint32_t crc = Value(data, sizeof(data));
  EXPECT_NE(0u, crc);
}

// Test CRC32C determinism
TEST(CRC32CTest_455, Deterministic_455) {
  std::string data = "The quick brown fox jumps over the lazy dog";
  uint32_t crc1 = Value(data.data(), data.size());
  uint32_t crc2 = Value(data.data(), data.size());
  uint32_t crc3 = Value(data.data(), data.size());
  EXPECT_EQ(crc1, crc2);
  EXPECT_EQ(crc2, crc3);
}

// Test with data that exercises the 16-byte stride path
TEST(CRC32CTest_455, LargeData_455) {
  std::string data(1024, 'x');
  uint32_t crc = Value(data.data(), data.size());
  EXPECT_NE(0u, crc);
  // Verify determinism for large data
  uint32_t crc2 = Value(data.data(), data.size());
  EXPECT_EQ(crc, crc2);
}

// Test with data size exactly 16 bytes (boundary for STEP16)
TEST(CRC32CTest_455, Exactly16Bytes_455) {
  std::string data = "0123456789abcdef";
  ASSERT_EQ(16u, data.size());
  uint32_t crc = Value(data.data(), data.size());
  EXPECT_NE(0u, crc);
}

// Test with data size 15 bytes (just under 16)
TEST(CRC32CTest_455, FifteenBytes_455) {
  std::string data = "0123456789abcde";
  ASSERT_EQ(15u, data.size());
  uint32_t crc = Value(data.data(), data.size());
  EXPECT_NE(0u, crc);
}

// Test with data size 17 bytes (just over 16)
TEST(CRC32CTest_455, SeventeenBytes_455) {
  std::string data = "0123456789abcdefg";
  ASSERT_EQ(17u, data.size());
  uint32_t crc = Value(data.data(), data.size());
  EXPECT_NE(0u, crc);
}

// Test with data sizes of 1 through 4 (boundary around alignment)
TEST(CRC32CTest_455, SmallSizes_455) {
  std::vector<uint32_t> crcs;
  for (size_t i = 1; i <= 4; i++) {
    std::string data(i, 'A');
    uint32_t crc = Value(data.data(), data.size());
    crcs.push_back(crc);
  }
  // Each should be unique
  for (size_t i = 0; i < crcs.size(); i++) {
    for (size_t j = i + 1; j < crcs.size(); j++) {
      EXPECT_NE(crcs[i], crcs[j]) << "CRC collision at sizes " << (i+1) << " and " << (j+1);
    }
  }
}

// Test Extend with multiple chunks matches single Value call
TEST(CRC32CTest_455, MultipleExtendChunks_455) {
  std::string full = "abcdefghijklmnopqrstuvwxyz0123456789";
  uint32_t crc_full = Value(full.data(), full.size());

  // Split into 3 parts
  std::string p1 = full.substr(0, 10);
  std::string p2 = full.substr(10, 15);
  std::string p3 = full.substr(25);

  uint32_t crc = Value(p1.data(), p1.size());
  crc = Extend(crc, p2.data(), p2.size());
  crc = Extend(crc, p3.data(), p3.size());

  EXPECT_EQ(crc_full, crc);
}

// Test with 32-byte data (exactly 2 x 16-byte strides)
TEST(CRC32CTest_455, ThirtyTwoBytes_455) {
  std::string data(32, 'B');
  uint32_t crc = Value(data.data(), data.size());
  EXPECT_NE(0u, crc);
}

// Test with very large data
TEST(CRC32CTest_455, VeryLargeData_455) {
  std::string data(65536, 'Z');
  uint32_t crc = Value(data.data(), data.size());
  EXPECT_NE(0u, crc);
  // Verify it's deterministic
  uint32_t crc2 = Value(data.data(), data.size());
  EXPECT_EQ(crc, crc2);
}

// Test Mask and Unmask round-trip
TEST(CRC32CTest_455, MaskUnmask_455) {
  std::string data = "foo";
  uint32_t crc = Value(data.data(), data.size());
  uint32_t masked = Mask(crc);
  // Masked should be different from original
  EXPECT_NE(crc, masked);
  // Unmasking should recover original
  uint32_t unmasked = Unmask(masked);
  EXPECT_EQ(crc, unmasked);
}

// Test that Mask produces different value than input
TEST(CRC32CTest_455, MaskDiffers_455) {
  uint32_t crc = Value("bar", 3);
  uint32_t masked = Mask(crc);
  EXPECT_NE(crc, masked);
}

// Test double masking
TEST(CRC32CTest_455, DoubleMask_455) {
  uint32_t crc = Value("baz", 3);
  uint32_t masked1 = Mask(crc);
  uint32_t masked2 = Mask(masked1);
  // Double masking should produce different result than single masking
  EXPECT_NE(masked1, masked2);
  // Unmasking twice should recover original
  uint32_t unmasked = Unmask(Unmask(masked2));
  EXPECT_EQ(crc, unmasked);
}

// Test Extend starting from a non-zero CRC with single byte
TEST(CRC32CTest_455, ExtendNonZeroCRC_455) {
  uint32_t initial_crc = Value("abc", 3);
  char byte = 'd';
  uint32_t extended = Extend(initial_crc, &byte, 1);
  uint32_t full_crc = Value("abcd", 4);
  EXPECT_EQ(full_crc, extended);
}

// Test with exactly 4 bytes (alignment boundary)
TEST(CRC32CTest_455, FourBytes_455) {
  std::string data = "abcd";
  ASSERT_EQ(4u, data.size());
  uint32_t crc = Value(data.data(), data.size());
  EXPECT_NE(0u, crc);
}

// Test with 8 bytes
TEST(CRC32CTest_455, EightBytes_455) {
  std::string data = "abcdefgh";
  ASSERT_EQ(8u, data.size());
  uint32_t crc = Value(data.data(), data.size());
  EXPECT_NE(0u, crc);
}

// Test Mask of zero
TEST(CRC32CTest_455, MaskZero_455) {
  uint32_t masked = Mask(0);
  uint32_t unmasked = Unmask(masked);
  EXPECT_EQ(0u, unmasked);
}

// Test Mask and Unmask with max uint32
TEST(CRC32CTest_455, MaskMaxUint32_455) {
  uint32_t val = 0xFFFFFFFFu;
  uint32_t masked = Mask(val);
  uint32_t unmasked = Unmask(masked);
  EXPECT_EQ(val, unmasked);
}

}  // namespace crc32c
}  // namespace leveldb

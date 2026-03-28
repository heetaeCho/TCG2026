#include "gtest/gtest.h"
#include "port/port_stdcxx.h"
#include <cstdint>
#include <cstring>
#include <string>
#include <vector>

namespace leveldb {
namespace port {

// Test with null buffer and zero size
TEST(AcceleratedCRC32CTest_43, NullBufferZeroSize_43) {
  uint32_t result = AcceleratedCRC32C(0, nullptr, 0);
  // With HAVE_CRC32C, extending CRC of empty data should return the initial CRC.
  // Without HAVE_CRC32C, result is always 0.
#if HAVE_CRC32C
  EXPECT_EQ(result, 0u);
#else
  EXPECT_EQ(result, 0u);
#endif
}

// Test with empty data (size = 0) but valid pointer
TEST(AcceleratedCRC32CTest_43, EmptyDataValidPointer_43) {
  const char buf[] = "hello";
  uint32_t result = AcceleratedCRC32C(0, buf, 0);
#if HAVE_CRC32C
  // CRC of zero bytes starting from 0 should be 0
  EXPECT_EQ(result, 0u);
#else
  EXPECT_EQ(result, 0u);
#endif
}

// Test with non-zero initial CRC and zero size
TEST(AcceleratedCRC32CTest_43, NonZeroInitialCRCZeroSize_43) {
  uint32_t initial_crc = 12345u;
  uint32_t result = AcceleratedCRC32C(initial_crc, nullptr, 0);
#if HAVE_CRC32C
  // Extending with zero bytes should return the initial CRC unchanged
  EXPECT_EQ(result, initial_crc);
#else
  EXPECT_EQ(result, 0u);
#endif
}

// Test with a simple known string
TEST(AcceleratedCRC32CTest_43, SimpleStringCRC_43) {
  const char* data = "hello";
  size_t len = 5;
  uint32_t result = AcceleratedCRC32C(0, data, len);
#if HAVE_CRC32C
  // The result should be a deterministic non-zero value for "hello"
  // We just verify it's consistent across calls
  uint32_t result2 = AcceleratedCRC32C(0, data, len);
  EXPECT_EQ(result, result2);
  // "hello" should produce a non-zero CRC32C
  EXPECT_NE(result, 0u);
#else
  EXPECT_EQ(result, 0u);
#endif
}

// Test that different data produces different CRCs (when CRC32C is available)
TEST(AcceleratedCRC32CTest_43, DifferentDataDifferentCRC_43) {
  const char* data1 = "hello";
  const char* data2 = "world";
  uint32_t crc1 = AcceleratedCRC32C(0, data1, 5);
  uint32_t crc2 = AcceleratedCRC32C(0, data2, 5);
#if HAVE_CRC32C
  EXPECT_NE(crc1, crc2);
#else
  EXPECT_EQ(crc1, 0u);
  EXPECT_EQ(crc2, 0u);
#endif
}

// Test determinism: same input always produces the same output
TEST(AcceleratedCRC32CTest_43, Deterministic_43) {
  const char* data = "test data for crc";
  size_t len = strlen(data);
  uint32_t result1 = AcceleratedCRC32C(0, data, len);
  uint32_t result2 = AcceleratedCRC32C(0, data, len);
  EXPECT_EQ(result1, result2);
}

// Test with single byte
TEST(AcceleratedCRC32CTest_43, SingleByte_43) {
  const char buf = 'A';
  uint32_t result = AcceleratedCRC32C(0, &buf, 1);
#if HAVE_CRC32C
  // Single byte CRC should be deterministic
  uint32_t result2 = AcceleratedCRC32C(0, &buf, 1);
  EXPECT_EQ(result, result2);
#else
  EXPECT_EQ(result, 0u);
#endif
}

// Test incremental CRC computation
TEST(AcceleratedCRC32CTest_43, IncrementalCRC_43) {
  const char* data = "helloworld";
  uint32_t full_crc = AcceleratedCRC32C(0, data, 10);

  uint32_t partial_crc = AcceleratedCRC32C(0, data, 5);
  uint32_t incremental_crc = AcceleratedCRC32C(partial_crc, data + 5, 5);

#if HAVE_CRC32C
  // CRC computed incrementally should match CRC computed in one shot
  EXPECT_EQ(full_crc, incremental_crc);
#else
  EXPECT_EQ(full_crc, 0u);
  EXPECT_EQ(incremental_crc, 0u);
#endif
}

// Test with a large buffer
TEST(AcceleratedCRC32CTest_43, LargeBuffer_43) {
  std::vector<char> buf(1024 * 64, 'x');  // 64KB buffer
  uint32_t result = AcceleratedCRC32C(0, buf.data(), buf.size());
#if HAVE_CRC32C
  // Should be deterministic
  uint32_t result2 = AcceleratedCRC32C(0, buf.data(), buf.size());
  EXPECT_EQ(result, result2);
  EXPECT_NE(result, 0u);
#else
  EXPECT_EQ(result, 0u);
#endif
}

// Test with all-zero buffer
TEST(AcceleratedCRC32CTest_43, AllZeroBuffer_43) {
  std::vector<char> buf(256, '\0');
  uint32_t result = AcceleratedCRC32C(0, buf.data(), buf.size());
#if HAVE_CRC32C
  uint32_t result2 = AcceleratedCRC32C(0, buf.data(), buf.size());
  EXPECT_EQ(result, result2);
#else
  EXPECT_EQ(result, 0u);
#endif
}

// Test with varying initial CRC values
TEST(AcceleratedCRC32CTest_43, VaryingInitialCRC_43) {
  const char* data = "test";
  size_t len = 4;
  uint32_t crc_a = AcceleratedCRC32C(0, data, len);
  uint32_t crc_b = AcceleratedCRC32C(1, data, len);
  uint32_t crc_c = AcceleratedCRC32C(0xFFFFFFFFu, data, len);

#if HAVE_CRC32C
  // Different initial CRC values should produce different results
  EXPECT_NE(crc_a, crc_b);
  EXPECT_NE(crc_a, crc_c);
  EXPECT_NE(crc_b, crc_c);
#else
  EXPECT_EQ(crc_a, 0u);
  EXPECT_EQ(crc_b, 0u);
  EXPECT_EQ(crc_c, 0u);
#endif
}

// Test that partial data gives different CRC than full data
TEST(AcceleratedCRC32CTest_43, PartialVsFullData_43) {
  const char* data = "abcdefgh";
  uint32_t crc_full = AcceleratedCRC32C(0, data, 8);
  uint32_t crc_partial = AcceleratedCRC32C(0, data, 4);

#if HAVE_CRC32C
  EXPECT_NE(crc_full, crc_partial);
#else
  EXPECT_EQ(crc_full, 0u);
  EXPECT_EQ(crc_partial, 0u);
#endif
}

}  // namespace port
}  // namespace leveldb

#include <string>
#include <cstdint>
#include <cstring>
#include "gtest/gtest.h"
#include "util/coding.h"

namespace leveldb {

// Test that PutFixed32 appends exactly 4 bytes to an empty string
TEST(PutFixed32Test_438, AppendsExactly4BytesToEmptyString_438) {
  std::string dst;
  PutFixed32(&dst, 0);
  EXPECT_EQ(dst.size(), 4u);
}

// Test that PutFixed32 encodes zero correctly
TEST(PutFixed32Test_438, EncodesZero_438) {
  std::string dst;
  PutFixed32(&dst, 0);
  ASSERT_EQ(dst.size(), 4u);
  uint32_t decoded = DecodeFixed32(dst.data());
  EXPECT_EQ(decoded, 0u);
}

// Test that PutFixed32 encodes a small value correctly
TEST(PutFixed32Test_438, EncodesSmallValue_438) {
  std::string dst;
  PutFixed32(&dst, 1);
  ASSERT_EQ(dst.size(), 4u);
  uint32_t decoded = DecodeFixed32(dst.data());
  EXPECT_EQ(decoded, 1u);
}

// Test that PutFixed32 encodes a typical value correctly
TEST(PutFixed32Test_438, EncodesTypicalValue_438) {
  std::string dst;
  PutFixed32(&dst, 12345678u);
  ASSERT_EQ(dst.size(), 4u);
  uint32_t decoded = DecodeFixed32(dst.data());
  EXPECT_EQ(decoded, 12345678u);
}

// Test that PutFixed32 encodes UINT32_MAX correctly
TEST(PutFixed32Test_438, EncodesMaxUint32_438) {
  std::string dst;
  PutFixed32(&dst, 0xFFFFFFFFu);
  ASSERT_EQ(dst.size(), 4u);
  uint32_t decoded = DecodeFixed32(dst.data());
  EXPECT_EQ(decoded, 0xFFFFFFFFu);
}

// Test that PutFixed32 encodes 0x80000000 (high bit set) correctly
TEST(PutFixed32Test_438, EncodesHighBitSet_438) {
  std::string dst;
  PutFixed32(&dst, 0x80000000u);
  ASSERT_EQ(dst.size(), 4u);
  uint32_t decoded = DecodeFixed32(dst.data());
  EXPECT_EQ(decoded, 0x80000000u);
}

// Test that PutFixed32 appends to existing data without overwriting
TEST(PutFixed32Test_438, AppendsToExistingData_438) {
  std::string dst = "hello";
  PutFixed32(&dst, 42u);
  EXPECT_EQ(dst.size(), 5u + 4u);
  // First 5 bytes should be preserved
  EXPECT_EQ(dst.substr(0, 5), "hello");
  // Remaining 4 bytes should decode to 42
  uint32_t decoded = DecodeFixed32(dst.data() + 5);
  EXPECT_EQ(decoded, 42u);
}

// Test multiple PutFixed32 calls accumulate correctly
TEST(PutFixed32Test_438, MultiplePutsAccumulate_438) {
  std::string dst;
  PutFixed32(&dst, 100u);
  PutFixed32(&dst, 200u);
  PutFixed32(&dst, 300u);
  EXPECT_EQ(dst.size(), 12u);

  uint32_t v1 = DecodeFixed32(dst.data());
  uint32_t v2 = DecodeFixed32(dst.data() + 4);
  uint32_t v3 = DecodeFixed32(dst.data() + 8);
  EXPECT_EQ(v1, 100u);
  EXPECT_EQ(v2, 200u);
  EXPECT_EQ(v3, 300u);
}

// Test encoding uses little-endian format (leveldb convention)
TEST(PutFixed32Test_438, LittleEndianEncoding_438) {
  std::string dst;
  PutFixed32(&dst, 0x04030201u);
  ASSERT_EQ(dst.size(), 4u);
  EXPECT_EQ(static_cast<unsigned char>(dst[0]), 0x01);
  EXPECT_EQ(static_cast<unsigned char>(dst[1]), 0x02);
  EXPECT_EQ(static_cast<unsigned char>(dst[2]), 0x03);
  EXPECT_EQ(static_cast<unsigned char>(dst[3]), 0x04);
}

// Test that PutFixed32 with value 0xFF encodes correctly
TEST(PutFixed32Test_438, EncodesSingleByteValue_438) {
  std::string dst;
  PutFixed32(&dst, 0xFFu);
  ASSERT_EQ(dst.size(), 4u);
  uint32_t decoded = DecodeFixed32(dst.data());
  EXPECT_EQ(decoded, 0xFFu);
}

// Test a power-of-two boundary value
TEST(PutFixed32Test_438, EncodesPowerOfTwo_438) {
  std::string dst;
  PutFixed32(&dst, 65536u); // 2^16
  ASSERT_EQ(dst.size(), 4u);
  uint32_t decoded = DecodeFixed32(dst.data());
  EXPECT_EQ(decoded, 65536u);
}

// Test encoding 0x01020304 for specific byte order verification
TEST(PutFixed32Test_438, ByteOrderVerification_438) {
  std::string dst;
  PutFixed32(&dst, 0x01020304u);
  ASSERT_EQ(dst.size(), 4u);
  // Little-endian: least significant byte first
  EXPECT_EQ(static_cast<unsigned char>(dst[0]), 0x04);
  EXPECT_EQ(static_cast<unsigned char>(dst[1]), 0x03);
  EXPECT_EQ(static_cast<unsigned char>(dst[2]), 0x02);
  EXPECT_EQ(static_cast<unsigned char>(dst[3]), 0x01);
}

}  // namespace leveldb

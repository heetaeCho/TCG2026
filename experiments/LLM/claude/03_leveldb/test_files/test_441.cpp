#include <string>
#include <cstdint>
#include "gtest/gtest.h"
#include "util/coding.h"

namespace leveldb {

// Helper to decode varint32 from a string for verification
// We use the existing DecodeVarint32 or GetVarint32 if available
// through the public interface in coding.h

class PutVarint32Test_441 : public ::testing::Test {
 protected:
  std::string dst_;
};

// Test encoding zero
TEST_F(PutVarint32Test_441, EncodesZero_441) {
  PutVarint32(&dst_, 0);
  ASSERT_FALSE(dst_.empty());
  // Zero should be encoded as a single byte 0x00
  ASSERT_EQ(dst_.size(), 1u);
  ASSERT_EQ(static_cast<unsigned char>(dst_[0]), 0x00);
}

// Test encoding value 1
TEST_F(PutVarint32Test_441, EncodesOne_441) {
  PutVarint32(&dst_, 1);
  ASSERT_EQ(dst_.size(), 1u);
  ASSERT_EQ(static_cast<unsigned char>(dst_[0]), 0x01);
}

// Test encoding small single-byte values (< 128)
TEST_F(PutVarint32Test_441, EncodesSingleByteValue_441) {
  PutVarint32(&dst_, 127);
  ASSERT_EQ(dst_.size(), 1u);
  ASSERT_EQ(static_cast<unsigned char>(dst_[0]), 127);
}

// Test encoding value that requires exactly 2 bytes (128)
TEST_F(PutVarint32Test_441, EncodesTwoByteValue_441) {
  PutVarint32(&dst_, 128);
  ASSERT_EQ(dst_.size(), 2u);
  // 128 in varint: 0x80 0x01
  ASSERT_EQ(static_cast<unsigned char>(dst_[0]), 0x80);
  ASSERT_EQ(static_cast<unsigned char>(dst_[1]), 0x01);
}

// Test encoding value 300 (requires 2 bytes)
TEST_F(PutVarint32Test_441, Encodes300_441) {
  PutVarint32(&dst_, 300);
  // 300 = 0x12C -> varint: 0xAC 0x02
  ASSERT_EQ(dst_.size(), 2u);
  ASSERT_EQ(static_cast<unsigned char>(dst_[0]), 0xAC);
  ASSERT_EQ(static_cast<unsigned char>(dst_[1]), 0x02);
}

// Test encoding value that requires 3 bytes
TEST_F(PutVarint32Test_441, EncodesThreeByteValue_441) {
  // 2^14 = 16384 requires 3 bytes in varint
  PutVarint32(&dst_, 16384);
  ASSERT_EQ(dst_.size(), 3u);
  // 16384 = 0x4000 -> varint: 0x80 0x80 0x01
  ASSERT_EQ(static_cast<unsigned char>(dst_[0]), 0x80);
  ASSERT_EQ(static_cast<unsigned char>(dst_[1]), 0x80);
  ASSERT_EQ(static_cast<unsigned char>(dst_[2]), 0x01);
}

// Test encoding value that requires 4 bytes
TEST_F(PutVarint32Test_441, EncodesFourByteValue_441) {
  // 2^21 = 2097152 requires 4 bytes in varint
  PutVarint32(&dst_, 2097152);
  ASSERT_EQ(dst_.size(), 4u);
}

// Test encoding max uint32 value (requires 5 bytes)
TEST_F(PutVarint32Test_441, EncodesMaxUint32_441) {
  PutVarint32(&dst_, 0xFFFFFFFF);
  ASSERT_EQ(dst_.size(), 5u);
  // Max uint32 varint: 0xFF 0xFF 0xFF 0xFF 0x0F
  ASSERT_EQ(static_cast<unsigned char>(dst_[0]), 0xFF);
  ASSERT_EQ(static_cast<unsigned char>(dst_[1]), 0xFF);
  ASSERT_EQ(static_cast<unsigned char>(dst_[2]), 0xFF);
  ASSERT_EQ(static_cast<unsigned char>(dst_[3]), 0xFF);
  ASSERT_EQ(static_cast<unsigned char>(dst_[4]), 0x0F);
}

// Test that PutVarint32 appends to existing string content
TEST_F(PutVarint32Test_441, AppendsToExistingContent_441) {
  dst_ = "prefix";
  PutVarint32(&dst_, 1);
  ASSERT_EQ(dst_.size(), 7u);  // "prefix" (6) + 1 byte varint
  ASSERT_EQ(dst_.substr(0, 6), "prefix");
  ASSERT_EQ(static_cast<unsigned char>(dst_[6]), 0x01);
}

// Test multiple appends produce concatenated varints
TEST_F(PutVarint32Test_441, MultipleAppends_441) {
  PutVarint32(&dst_, 1);
  PutVarint32(&dst_, 2);
  PutVarint32(&dst_, 3);
  ASSERT_EQ(dst_.size(), 3u);
  ASSERT_EQ(static_cast<unsigned char>(dst_[0]), 0x01);
  ASSERT_EQ(static_cast<unsigned char>(dst_[1]), 0x02);
  ASSERT_EQ(static_cast<unsigned char>(dst_[2]), 0x03);
}

// Test round-trip encoding and decoding with GetVarint32
TEST_F(PutVarint32Test_441, RoundTripSmallValue_441) {
  uint32_t original = 42;
  PutVarint32(&dst_, original);
  
  Slice input(dst_);
  uint32_t decoded;
  ASSERT_TRUE(GetVarint32(&input, &decoded));
  ASSERT_EQ(original, decoded);
}

// Test round-trip with large value
TEST_F(PutVarint32Test_441, RoundTripLargeValue_441) {
  uint32_t original = 123456789;
  PutVarint32(&dst_, original);
  
  Slice input(dst_);
  uint32_t decoded;
  ASSERT_TRUE(GetVarint32(&input, &decoded));
  ASSERT_EQ(original, decoded);
}

// Test round-trip with max value
TEST_F(PutVarint32Test_441, RoundTripMaxValue_441) {
  uint32_t original = 0xFFFFFFFF;
  PutVarint32(&dst_, original);
  
  Slice input(dst_);
  uint32_t decoded;
  ASSERT_TRUE(GetVarint32(&input, &decoded));
  ASSERT_EQ(original, decoded);
}

// Test round-trip with multiple values
TEST_F(PutVarint32Test_441, RoundTripMultipleValues_441) {
  std::vector<uint32_t> values = {0, 1, 127, 128, 16383, 16384, 2097151, 2097152, 0xFFFFFFFF};
  for (uint32_t v : values) {
    PutVarint32(&dst_, v);
  }
  
  Slice input(dst_);
  for (uint32_t expected : values) {
    uint32_t decoded;
    ASSERT_TRUE(GetVarint32(&input, &decoded));
    ASSERT_EQ(expected, decoded);
  }
  ASSERT_EQ(input.size(), 0u);
}

// Test encoding on empty string
TEST_F(PutVarint32Test_441, EncodesOnEmptyString_441) {
  ASSERT_TRUE(dst_.empty());
  PutVarint32(&dst_, 42);
  ASSERT_FALSE(dst_.empty());
  
  Slice input(dst_);
  uint32_t decoded;
  ASSERT_TRUE(GetVarint32(&input, &decoded));
  ASSERT_EQ(decoded, 42u);
}

// Test boundary values at byte boundaries
TEST_F(PutVarint32Test_441, BoundaryOneByteTwoBytes_441) {
  // 127 should be 1 byte, 128 should be 2 bytes
  std::string s1, s2;
  PutVarint32(&s1, 127);
  PutVarint32(&s2, 128);
  ASSERT_EQ(s1.size(), 1u);
  ASSERT_EQ(s2.size(), 2u);
}

TEST_F(PutVarint32Test_441, BoundaryTwoBytesThreeBytes_441) {
  // 2^14 - 1 = 16383 should be 2 bytes, 2^14 = 16384 should be 3 bytes
  std::string s1, s2;
  PutVarint32(&s1, 16383);
  PutVarint32(&s2, 16384);
  ASSERT_EQ(s1.size(), 2u);
  ASSERT_EQ(s2.size(), 3u);
}

TEST_F(PutVarint32Test_441, BoundaryThreeBytesFourBytes_441) {
  // 2^21 - 1 = 2097151 should be 3 bytes, 2^21 = 2097152 should be 4 bytes
  std::string s1, s2;
  PutVarint32(&s1, 2097151);
  PutVarint32(&s2, 2097152);
  ASSERT_EQ(s1.size(), 3u);
  ASSERT_EQ(s2.size(), 4u);
}

TEST_F(PutVarint32Test_441, BoundaryFourBytesFiveBytes_441) {
  // 2^28 - 1 = 268435455 should be 4 bytes, 2^28 = 268435456 should be 5 bytes
  std::string s1, s2;
  PutVarint32(&s1, 268435455);
  PutVarint32(&s2, 268435456);
  ASSERT_EQ(s1.size(), 4u);
  ASSERT_EQ(s2.size(), 5u);
}

}  // namespace leveldb

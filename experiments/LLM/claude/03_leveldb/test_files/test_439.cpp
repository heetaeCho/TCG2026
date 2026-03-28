#include <string>
#include <cstdint>
#include <cstring>
#include "gtest/gtest.h"
#include "util/coding.h"

namespace leveldb {

// Test normal operation: PutFixed64 appends 8 bytes to the string
TEST(PutFixed64Test_439, AppendsEightBytes_439) {
  std::string dst;
  PutFixed64(&dst, 0x0102030405060708ULL);
  EXPECT_EQ(dst.size(), 8u);
}

// Test that encoding zero produces 8 zero bytes
TEST(PutFixed64Test_439, EncodesZero_439) {
  std::string dst;
  PutFixed64(&dst, 0);
  EXPECT_EQ(dst.size(), 8u);
  for (size_t i = 0; i < 8; i++) {
    EXPECT_EQ(static_cast<unsigned char>(dst[i]), 0u);
  }
}

// Test that the value is encoded in little-endian format
TEST(PutFixed64Test_439, EncodesInLittleEndian_439) {
  std::string dst;
  uint64_t value = 0x0807060504030201ULL;
  PutFixed64(&dst, value);
  ASSERT_EQ(dst.size(), 8u);
  EXPECT_EQ(static_cast<unsigned char>(dst[0]), 0x01);
  EXPECT_EQ(static_cast<unsigned char>(dst[1]), 0x02);
  EXPECT_EQ(static_cast<unsigned char>(dst[2]), 0x03);
  EXPECT_EQ(static_cast<unsigned char>(dst[3]), 0x04);
  EXPECT_EQ(static_cast<unsigned char>(dst[4]), 0x05);
  EXPECT_EQ(static_cast<unsigned char>(dst[5]), 0x06);
  EXPECT_EQ(static_cast<unsigned char>(dst[6]), 0x07);
  EXPECT_EQ(static_cast<unsigned char>(dst[7]), 0x08);
}

// Test encoding UINT64_MAX (all bits set)
TEST(PutFixed64Test_439, EncodesMaxValue_439) {
  std::string dst;
  PutFixed64(&dst, UINT64_MAX);
  ASSERT_EQ(dst.size(), 8u);
  for (size_t i = 0; i < 8; i++) {
    EXPECT_EQ(static_cast<unsigned char>(dst[i]), 0xFF);
  }
}

// Test encoding value 1 (only least significant bit set)
TEST(PutFixed64Test_439, EncodesOne_439) {
  std::string dst;
  PutFixed64(&dst, 1ULL);
  ASSERT_EQ(dst.size(), 8u);
  EXPECT_EQ(static_cast<unsigned char>(dst[0]), 0x01);
  for (size_t i = 1; i < 8; i++) {
    EXPECT_EQ(static_cast<unsigned char>(dst[i]), 0x00);
  }
}

// Test that PutFixed64 appends to existing content without overwriting
TEST(PutFixed64Test_439, AppendsToExistingContent_439) {
  std::string dst = "hello";
  PutFixed64(&dst, 42);
  EXPECT_EQ(dst.size(), 5u + 8u);
  EXPECT_EQ(dst.substr(0, 5), "hello");
}

// Test multiple consecutive PutFixed64 calls
TEST(PutFixed64Test_439, MultipleAppends_439) {
  std::string dst;
  PutFixed64(&dst, 1);
  PutFixed64(&dst, 2);
  PutFixed64(&dst, 3);
  EXPECT_EQ(dst.size(), 24u);
}

// Test that the encoded value can be decoded back using DecodeFixed64
TEST(PutFixed64Test_439, RoundTripWithDecodeFixed64_439) {
  std::string dst;
  uint64_t original = 0xDEADBEEFCAFEBABEULL;
  PutFixed64(&dst, original);
  ASSERT_EQ(dst.size(), 8u);
  uint64_t decoded = DecodeFixed64(dst.data());
  EXPECT_EQ(decoded, original);
}

// Test encoding a value with only the high byte set
TEST(PutFixed64Test_439, HighByteOnly_439) {
  std::string dst;
  uint64_t value = 0xFF00000000000000ULL;
  PutFixed64(&dst, value);
  ASSERT_EQ(dst.size(), 8u);
  for (size_t i = 0; i < 7; i++) {
    EXPECT_EQ(static_cast<unsigned char>(dst[i]), 0x00);
  }
  EXPECT_EQ(static_cast<unsigned char>(dst[7]), 0xFF);
}

// Test encoding a power of 2
TEST(PutFixed64Test_439, PowerOfTwo_439) {
  std::string dst;
  uint64_t value = 1ULL << 32;  // 0x0000000100000000
  PutFixed64(&dst, value);
  ASSERT_EQ(dst.size(), 8u);
  EXPECT_EQ(static_cast<unsigned char>(dst[0]), 0x00);
  EXPECT_EQ(static_cast<unsigned char>(dst[1]), 0x00);
  EXPECT_EQ(static_cast<unsigned char>(dst[2]), 0x00);
  EXPECT_EQ(static_cast<unsigned char>(dst[3]), 0x00);
  EXPECT_EQ(static_cast<unsigned char>(dst[4]), 0x01);
  EXPECT_EQ(static_cast<unsigned char>(dst[5]), 0x00);
  EXPECT_EQ(static_cast<unsigned char>(dst[6]), 0x00);
  EXPECT_EQ(static_cast<unsigned char>(dst[7]), 0x00);
}

// Test round trip for multiple values
TEST(PutFixed64Test_439, MultipleRoundTrips_439) {
  std::string dst;
  uint64_t values[] = {0, 1, 255, 256, 65535, 0xFFFFFFFF, 0xFFFFFFFFFFFFFFFFULL, 0x123456789ABCDEF0ULL};
  for (uint64_t v : values) {
    dst.clear();
    PutFixed64(&dst, v);
    ASSERT_EQ(dst.size(), 8u);
    EXPECT_EQ(DecodeFixed64(dst.data()), v);
  }
}

}  // namespace leveldb

// File: util/coding_varint32_test.cc
#include <gtest/gtest.h>
#include <cstdint>
#include <algorithm>
#include <iterator>

namespace leveldb {
// Forward declaration of the function under test.
// The implementation is linked from the production code.
char* EncodeVarint32(char* dst, uint32_t v);
}

class EncodeVarint32Test_440 : public ::testing::Test {
protected:
  // Verifies: (1) exact bytes written, (2) returned pointer advances by
  // expected length, (3) no writes beyond the expected length.
  void ExpectEncoding(uint32_t value,
                      std::initializer_list<uint8_t> expected) {
    constexpr size_t kBufSize = 16;
    uint8_t buf[kBufSize];
    std::fill(std::begin(buf), std::end(buf), 0xAA); // sentinel

    char* start = reinterpret_cast<char*>(buf);
    char* end   = leveldb::EncodeVarint32(start, value);
    size_t written = static_cast<size_t>(end - start);

    ASSERT_EQ(expected.size(), written) << "Unexpected encoded length";
    size_t i = 0;
    for (uint8_t b : expected) {
      EXPECT_EQ(buf[i], b) << "Mismatch at byte index " << i;
      ++i;
    }
    for (; i < kBufSize; ++i) {
      EXPECT_EQ(buf[i], 0xAA) << "Buffer overrun at index " << i;
    }
  }
};

// ---- Single-byte encodings -------------------------------------------------

TEST_F(EncodeVarint32Test_440, EncodesZeroAsSingleByte_440) {
  // 0 -> [0x00]
  ExpectEncoding(0u, {0x00});
}

TEST_F(EncodeVarint32Test_440, Encodes127AsSingleByte_440) {
  // 127 -> [0x7F]
  ExpectEncoding(127u, {0x7F});
}

// ---- Two-byte boundaries ---------------------------------------------------

TEST_F(EncodeVarint32Test_440, BoundaryToTwoBytes_From128_440) {
  // 128 -> [0x80, 0x01]
  ExpectEncoding(128u, {0x80, 0x01});
}

TEST_F(EncodeVarint32Test_440, MaxTwoByte_16383_440) {
  // 16383 -> [0xFF, 0x7F]
  ExpectEncoding(16383u, {0xFF, 0x7F});
}

// ---- Three-byte boundaries -------------------------------------------------

TEST_F(EncodeVarint32Test_440, BoundaryToThreeBytes_From16384_440) {
  // 16384 -> [0x80, 0x80, 0x01]
  ExpectEncoding(16384u, {0x80, 0x80, 0x01});
}

TEST_F(EncodeVarint32Test_440, MaxThreeByte_2097151_440) {
  // 2^21 - 1 = 2097151 -> [0xFF, 0xFF, 0x7F]
  ExpectEncoding(2097151u, {0xFF, 0xFF, 0x7F});
}

// ---- Four-byte boundaries --------------------------------------------------

TEST_F(EncodeVarint32Test_440, BoundaryToFourBytes_From2097152_440) {
  // 2^21 = 2097152 -> [0x80, 0x80, 0x80, 0x01]
  ExpectEncoding(2097152u, {0x80, 0x80, 0x80, 0x01});
}

TEST_F(EncodeVarint32Test_440, MaxFourByte_268435455_440) {
  // 2^28 - 1 = 268435455 -> [0xFF, 0xFF, 0xFF, 0x7F]
  ExpectEncoding(268435455u, {0xFF, 0xFF, 0xFF, 0x7F});
}

// ---- Five-byte boundaries --------------------------------------------------

TEST_F(EncodeVarint32Test_440, BoundaryToFiveBytes_From268435456_440) {
  // 2^28 = 268435456 -> [0x80, 0x80, 0x80, 0x80, 0x01]
  ExpectEncoding(268435456u, {0x80, 0x80, 0x80, 0x80, 0x01});
}

TEST_F(EncodeVarint32Test_440, EncodesMaxUint32_AsFiveBytes_440) {
  // 0xFFFFFFFF -> [0xFF, 0xFF, 0xFF, 0xFF, 0x0F]
  ExpectEncoding(0xFFFFFFFFu, {0xFF, 0xFF, 0xFF, 0xFF, 0x0F});
}

// ---- Additional observable behavior ---------------------------------------

TEST_F(EncodeVarint32Test_440, ConsecutiveEncodingsAppendCorrectly_440) {
  // Encode two values back-to-back; verify layout and pointer advancement
  uint8_t buf[16];
  std::fill(std::begin(buf), std::end(buf), 0xAA);

  char* p = reinterpret_cast<char*>(buf);
  char* p1 = leveldb::EncodeVarint32(p, 127u);    // [0x7F]
  char* p2 = leveldb::EncodeVarint32(p1, 128u);   // [0x80, 0x01]

  EXPECT_EQ(p + 3, p2) << "Pointer should advance by total written length";

  // Expect concatenated bytes: 0x7F, 0x80, 0x01, then sentinels
  EXPECT_EQ(buf[0], 0x7F);
  EXPECT_EQ(buf[1], 0x80);
  EXPECT_EQ(buf[2], 0x01);
  for (size_t i = 3; i < std::size(buf); ++i) {
    EXPECT_EQ(buf[i], 0xAA) << "Unexpected write past combined encoding";
  }
}

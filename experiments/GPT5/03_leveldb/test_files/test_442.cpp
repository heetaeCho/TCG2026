// util/coding_encodevarint64_test.cc
#include <gtest/gtest.h>
#include <cstdint>
#include <vector>
#include <algorithm>

namespace leveldb {
// Forward declaration of the function under test.
char* EncodeVarint64(char* dst, uint64_t v);
}

static void ExpectEncoding(uint64_t value, const std::vector<uint8_t>& expected) {
  // Buffer large enough for any varint64 (max 10 bytes) + guard.
  char buf[32];
  std::fill(std::begin(buf), std::end(buf), static_cast<char>(0xAA)); // sentinel
  char* const start = buf;

  char* const end = leveldb::EncodeVarint64(buf, value);
  const size_t n = static_cast<size_t>(end - start);

  ASSERT_EQ(expected.size(), n) << "Unexpected encoded length";

  // Compare written bytes only.
  for (size_t i = 0; i < expected.size(); ++i) {
    uint8_t actual = static_cast<uint8_t>(buf[i]);
    EXPECT_EQ(expected[i], actual) << "Byte mismatch at index " << i;
  }

  // Ensure no overwrite beyond returned end (next byte remains sentinel).
  ASSERT_LT(n, sizeof(buf));
  EXPECT_EQ(0xAAu, static_cast<uint8_t>(buf[n])) << "Wrote past end pointer";
}

TEST(EncodeVarint64Test_442, EncodesZeroAsSingleByte_442) {
  ExpectEncoding(0u, {0x00});
}

TEST(EncodeVarint64Test_442, EncodesOneAsSingleByte_442) {
  ExpectEncoding(1u, {0x01});
}

TEST(EncodeVarint64Test_442, EncodesMaxOneByte127_442) {
  ExpectEncoding(127u, {0x7F});
}

TEST(EncodeVarint64Test_442, Encodes128AsTwoBytes_442) {
  // 128 = 0x80 0x01 in LEB128-style varint
  ExpectEncoding(128u, {0x80, 0x01});
}

TEST(EncodeVarint64Test_442, Encodes255AsTwoBytes_442) {
  // 255 = 0xFF 0x01
  ExpectEncoding(255u, {0xFF, 0x01});
}

TEST(EncodeVarint64Test_442, Encodes16383AsTwoBytesBoundaryMinusOne_442) {
  // 16383 = 0xFF 0x7F
  ExpectEncoding(16383u, {0xFF, 0x7F});
}

TEST(EncodeVarint64Test_442, Encodes16384AsThreeBytesBoundary_442) {
  // 16384 = 0x80 0x80 0x01
  ExpectEncoding(16384u, {0x80, 0x80, 0x01});
}

TEST(EncodeVarint64Test_442, EncodesMaxSigned63BitsAsNineBytes_442) {
  // (2^63 - 1) should take 9 bytes: 8 times 0xFF, then 0x7F
  const uint64_t v = (std::numeric_limits<uint64_t>::max() >> 1);
  ExpectEncoding(v, {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x7F});
}

TEST(EncodeVarint64Test_442, EncodesMaxUint64AsTenBytes_442) {
  // (2^64 - 1) should be 10 bytes: nine 0xFF, then 0x01
  ExpectEncoding(std::numeric_limits<uint64_t>::max(),
                 {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x01});
}

TEST(EncodeVarint64Test_442, ReturnPointerAdvancesByEncodedLength_442) {
  struct Case { uint64_t v; size_t len; };
  const Case cases[] = {
      {0u, 1}, {1u, 1}, {127u, 1},
      {128u, 2}, {255u, 2}, {16384u, 3},
      {(std::numeric_limits<uint64_t>::max() >> 1), 9},
      {std::numeric_limits<uint64_t>::max(), 10},
  };

  for (const auto& c : cases) {
    char buf[32];
    std::fill(std::begin(buf), std::end(buf), static_cast<char>(0xAA));
    char* const start = buf;
    char* const end = leveldb::EncodeVarint64(buf, c.v);
    size_t n = static_cast<size_t>(end - start);
    EXPECT_EQ(c.len, n) << "Length mismatch for value " << c.v;
    // Quick guard check to ensure no overwrite beyond n
    ASSERT_LT(n, sizeof(buf));
    EXPECT_EQ(0xAAu, static_cast<uint8_t>(buf[n]));
  }
}

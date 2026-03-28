// UnicodeMapFuncs_mapUTF16_test_1648.cc

#include <gtest/gtest.h>

#include <array>
#include <cstdint>
#include <cstring>

// Poppler typically defines Unicode in UnicodeType.h.
#include "UnicodeType.h"

// Function under test (implemented in UnicodeMapFuncs.cc)
int mapUTF16(Unicode u, char *buf, int bufSize);

namespace {

constexpr unsigned char kSentinel = 0xAA;

static void FillSentinel(char *buf, size_t n) {
  std::memset(buf, static_cast<int>(kSentinel), n);
}

static void ExpectBytesEq(const char *buf,
                          std::initializer_list<unsigned char> expected) {
  size_t i = 0;
  for (unsigned char v : expected) {
    EXPECT_EQ(static_cast<unsigned char>(buf[i]), v) << "at index " << i;
    ++i;
  }
}

}  // namespace

class MapUTF16Test_1648 : public ::testing::Test {};

TEST_F(MapUTF16Test_1648, EncodesBmpCodePointAsTwoBytes_1648) {
  std::array<char, 4> buf{};
  FillSentinel(buf.data(), buf.size());

  const Unicode u = static_cast<Unicode>(0x0041);  // 'A'
  const int written = mapUTF16(u, buf.data(), 2);

  EXPECT_EQ(written, 2);
  ExpectBytesEq(buf.data(), {0x00, 0x41});
  // Ensure no extra bytes were overwritten.
  EXPECT_EQ(static_cast<unsigned char>(buf[2]), kSentinel);
  EXPECT_EQ(static_cast<unsigned char>(buf[3]), kSentinel);
}

TEST_F(MapUTF16Test_1648, EncodesBmpUpperBoundaryFFFF_1648) {
  std::array<char, 4> buf{};
  FillSentinel(buf.data(), buf.size());

  const Unicode u = static_cast<Unicode>(0xFFFF);
  const int written = mapUTF16(u, buf.data(), 4);

  EXPECT_EQ(written, 2);
  ExpectBytesEq(buf.data(), {0xFF, 0xFF});
  EXPECT_EQ(static_cast<unsigned char>(buf[2]), kSentinel);
  EXPECT_EQ(static_cast<unsigned char>(buf[3]), kSentinel);
}

TEST_F(MapUTF16Test_1648, ReturnsZeroWhenBufferTooSmallForBmp_1648) {
  std::array<char, 2> buf{};
  FillSentinel(buf.data(), buf.size());

  const Unicode u = static_cast<Unicode>(0x1234);
  const int written = mapUTF16(u, buf.data(), 1);

  EXPECT_EQ(written, 0);
  // Buffer should remain untouched on failure.
  EXPECT_EQ(static_cast<unsigned char>(buf[0]), kSentinel);
  EXPECT_EQ(static_cast<unsigned char>(buf[1]), kSentinel);
}

TEST_F(MapUTF16Test_1648, EncodesNonBmpLowerBoundary10000AsSurrogatePair_1648) {
  std::array<char, 4> buf{};
  FillSentinel(buf.data(), buf.size());

  const Unicode u = static_cast<Unicode>(0x10000);
  const int written = mapUTF16(u, buf.data(), 4);

  EXPECT_EQ(written, 4);
  // Expected UTF-16 surrogate pair: D800 DC00 (big-endian bytes)
  ExpectBytesEq(buf.data(), {0xD8, 0x00, 0xDC, 0x00});
}

TEST_F(MapUTF16Test_1648, EncodesNonBmpUpperBoundary10FFFFAsSurrogatePair_1648) {
  std::array<char, 4> buf{};
  FillSentinel(buf.data(), buf.size());

  const Unicode u = static_cast<Unicode>(0x10FFFF);
  const int written = mapUTF16(u, buf.data(), 4);

  EXPECT_EQ(written, 4);
  // Expected UTF-16 surrogate pair: DBFF DFFF (big-endian bytes)
  ExpectBytesEq(buf.data(), {0xDB, 0xFF, 0xDF, 0xFF});
}

TEST_F(MapUTF16Test_1648, ReturnsZeroWhenBufferTooSmallForSurrogatePair_1648) {
  std::array<char, 4> buf{};
  FillSentinel(buf.data(), buf.size());

  const Unicode u = static_cast<Unicode>(0x10000);
  const int written = mapUTF16(u, buf.data(), 3);

  EXPECT_EQ(written, 0);
  // Ensure no partial write occurred (observable contract from interface usage).
  EXPECT_EQ(static_cast<unsigned char>(buf[0]), kSentinel);
  EXPECT_EQ(static_cast<unsigned char>(buf[1]), kSentinel);
  EXPECT_EQ(static_cast<unsigned char>(buf[2]), kSentinel);
  EXPECT_EQ(static_cast<unsigned char>(buf[3]), kSentinel);
}

TEST_F(MapUTF16Test_1648, ReturnsZeroForOutOfRangeCodePoint110000_1648) {
  std::array<char, 4> buf{};
  FillSentinel(buf.data(), buf.size());

  const Unicode u = static_cast<Unicode>(0x110000);
  const int written = mapUTF16(u, buf.data(), 4);

  EXPECT_EQ(written, 0);
  // Buffer should remain untouched on failure.
  EXPECT_EQ(static_cast<unsigned char>(buf[0]), kSentinel);
  EXPECT_EQ(static_cast<unsigned char>(buf[1]), kSentinel);
  EXPECT_EQ(static_cast<unsigned char>(buf[2]), kSentinel);
  EXPECT_EQ(static_cast<unsigned char>(buf[3]), kSentinel);
}

TEST_F(MapUTF16Test_1648, HandlesZeroCodePoint_1648) {
  std::array<char, 4> buf{};
  FillSentinel(buf.data(), buf.size());

  const Unicode u = static_cast<Unicode>(0x0000);
  const int written = mapUTF16(u, buf.data(), 2);

  EXPECT_EQ(written, 2);
  ExpectBytesEq(buf.data(), {0x00, 0x00});
  EXPECT_EQ(static_cast<unsigned char>(buf[2]), kSentinel);
  EXPECT_EQ(static_cast<unsigned char>(buf[3]), kSentinel);
}
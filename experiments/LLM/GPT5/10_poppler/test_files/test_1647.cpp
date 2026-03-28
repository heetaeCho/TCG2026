// mapUTF8_unittest_1647.cc
#include <gtest/gtest.h>

#include <array>
#include <cstdint>
#include <cstring>

// Poppler typically defines Unicode in goo/gtypes.h.
#include "goo/gtypes.h"

// Function under test (implemented in UnicodeMapFuncs.cc).
extern int mapUTF8(Unicode u, char *buf, int bufSize);

namespace {

class MapUTF8Test_1647 : public ::testing::Test {
protected:
  static std::array<char, 8> MakeSentinelBuf() {
    std::array<char, 8> b{};
    b.fill(static_cast<char>(0x5A)); // 'Z' sentinel
    return b;
  }

  static void ExpectBytesEq(const char *buf, const std::initializer_list<uint8_t> &bytes) {
    size_t i = 0;
    for (auto v : bytes) {
      EXPECT_EQ(static_cast<uint8_t>(static_cast<unsigned char>(buf[i])), v) << "at index " << i;
      ++i;
    }
  }

  static void ExpectNoOverwritePastN(const std::array<char, 8> &buf, int n) {
    for (int i = n; i < static_cast<int>(buf.size()); ++i) {
      EXPECT_EQ(buf[i], static_cast<char>(0x5A)) << "unexpected write past output length at index " << i;
    }
  }
};

} // namespace

TEST_F(MapUTF8Test_1647, EncodesAsciiBoundary7F_1647) {
  auto buf = MapUTF8Test_1647::MakeSentinelBuf();
  int n = mapUTF8(static_cast<Unicode>(0x7F), buf.data(), 1);
  ASSERT_EQ(n, 1);
  MapUTF8Test_1647::ExpectBytesEq(buf.data(), {0x7F});
  MapUTF8Test_1647::ExpectNoOverwritePastN(buf, n);
}

TEST_F(MapUTF8Test_1647, EncodesTwoByteLowerBoundary80_1647) {
  auto buf = MapUTF8Test_1647::MakeSentinelBuf();
  int n = mapUTF8(static_cast<Unicode>(0x80), buf.data(), 2);
  ASSERT_EQ(n, 2);
  MapUTF8Test_1647::ExpectBytesEq(buf.data(), {0xC2, 0x80});
  MapUTF8Test_1647::ExpectNoOverwritePastN(buf, n);
}

TEST_F(MapUTF8Test_1647, EncodesTwoByteUpperBoundary7FF_1647) {
  auto buf = MapUTF8Test_1647::MakeSentinelBuf();
  int n = mapUTF8(static_cast<Unicode>(0x7FF), buf.data(), 2);
  ASSERT_EQ(n, 2);
  MapUTF8Test_1647::ExpectBytesEq(buf.data(), {0xDF, 0xBF});
  MapUTF8Test_1647::ExpectNoOverwritePastN(buf, n);
}

TEST_F(MapUTF8Test_1647, EncodesThreeByteLowerBoundary800_1647) {
  auto buf = MapUTF8Test_1647::MakeSentinelBuf();
  int n = mapUTF8(static_cast<Unicode>(0x800), buf.data(), 3);
  ASSERT_EQ(n, 3);
  MapUTF8Test_1647::ExpectBytesEq(buf.data(), {0xE0, 0xA0, 0x80});
  MapUTF8Test_1647::ExpectNoOverwritePastN(buf, n);
}

TEST_F(MapUTF8Test_1647, EncodesThreeByteUpperBoundaryFFFF_1647) {
  auto buf = MapUTF8Test_1647::MakeSentinelBuf();
  int n = mapUTF8(static_cast<Unicode>(0xFFFF), buf.data(), 3);
  ASSERT_EQ(n, 3);
  MapUTF8Test_1647::ExpectBytesEq(buf.data(), {0xEF, 0xBF, 0xBF});
  MapUTF8Test_1647::ExpectNoOverwritePastN(buf, n);
}

TEST_F(MapUTF8Test_1647, EncodesFourByteLowerBoundary10000_1647) {
  auto buf = MapUTF8Test_1647::MakeSentinelBuf();
  int n = mapUTF8(static_cast<Unicode>(0x10000), buf.data(), 4);
  ASSERT_EQ(n, 4);
  MapUTF8Test_1647::ExpectBytesEq(buf.data(), {0xF0, 0x90, 0x80, 0x80});
  MapUTF8Test_1647::ExpectNoOverwritePastN(buf, n);
}

TEST_F(MapUTF8Test_1647, EncodesFourByteUpperBoundary10FFFF_1647) {
  auto buf = MapUTF8Test_1647::MakeSentinelBuf();
  int n = mapUTF8(static_cast<Unicode>(0x10FFFF), buf.data(), 4);
  ASSERT_EQ(n, 4);
  MapUTF8Test_1647::ExpectBytesEq(buf.data(), {0xF4, 0x8F, 0xBF, 0xBF});
  MapUTF8Test_1647::ExpectNoOverwritePastN(buf, n);
}

TEST_F(MapUTF8Test_1647, ReturnsZeroForOutOfRangeAboveUnicodeMax_1647) {
  auto buf = MapUTF8Test_1647::MakeSentinelBuf();
  int n = mapUTF8(static_cast<Unicode>(0x110000), buf.data(), 4);
  EXPECT_EQ(n, 0);
}

TEST_F(MapUTF8Test_1647, ReturnsZeroWhenBufferTooSmallForAscii_1647) {
  auto buf = MapUTF8Test_1647::MakeSentinelBuf();
  int n = mapUTF8(static_cast<Unicode>(0x41), buf.data(), 0);
  EXPECT_EQ(n, 0);
}

TEST_F(MapUTF8Test_1647, ReturnsZeroWhenBufferTooSmallForTwoByte_1647) {
  auto buf = MapUTF8Test_1647::MakeSentinelBuf();
  int n = mapUTF8(static_cast<Unicode>(0x80), buf.data(), 1);
  EXPECT_EQ(n, 0);
}

TEST_F(MapUTF8Test_1647, ReturnsZeroWhenBufferTooSmallForThreeByte_1647) {
  auto buf = MapUTF8Test_1647::MakeSentinelBuf();
  int n = mapUTF8(static_cast<Unicode>(0x800), buf.data(), 2);
  EXPECT_EQ(n, 0);
}

TEST_F(MapUTF8Test_1647, ReturnsZeroWhenBufferTooSmallForFourByte_1647) {
  auto buf = MapUTF8Test_1647::MakeSentinelBuf();
  int n = mapUTF8(static_cast<Unicode>(0x10000), buf.data(), 3);
  EXPECT_EQ(n, 0);
}
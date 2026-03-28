// TEST_ID 1139
// Unit tests for Exiv2::getURational(const byte* buf, ByteOrder byteOrder)
//
// File under test: ./TestProjects/exiv2/src/types.cpp

#include <gtest/gtest.h>

#include <array>
#include <cstdint>

#include "exiv2/types.hpp"

namespace {

class GetURationalTest_1139 : public ::testing::Test {
 protected:
  static std::array<Exiv2::byte, 8> MakeBufLittleEndian(uint32_t numerator, uint32_t denominator) {
    std::array<Exiv2::byte, 8> b{};
    // numerator
    b[0] = static_cast<Exiv2::byte>(numerator & 0xFFu);
    b[1] = static_cast<Exiv2::byte>((numerator >> 8) & 0xFFu);
    b[2] = static_cast<Exiv2::byte>((numerator >> 16) & 0xFFu);
    b[3] = static_cast<Exiv2::byte>((numerator >> 24) & 0xFFu);
    // denominator
    b[4] = static_cast<Exiv2::byte>(denominator & 0xFFu);
    b[5] = static_cast<Exiv2::byte>((denominator >> 8) & 0xFFu);
    b[6] = static_cast<Exiv2::byte>((denominator >> 16) & 0xFFu);
    b[7] = static_cast<Exiv2::byte>((denominator >> 24) & 0xFFu);
    return b;
  }

  static std::array<Exiv2::byte, 8> MakeBufBigEndian(uint32_t numerator, uint32_t denominator) {
    std::array<Exiv2::byte, 8> b{};
    // numerator
    b[0] = static_cast<Exiv2::byte>((numerator >> 24) & 0xFFu);
    b[1] = static_cast<Exiv2::byte>((numerator >> 16) & 0xFFu);
    b[2] = static_cast<Exiv2::byte>((numerator >> 8) & 0xFFu);
    b[3] = static_cast<Exiv2::byte>(numerator & 0xFFu);
    // denominator
    b[4] = static_cast<Exiv2::byte>((denominator >> 24) & 0xFFu);
    b[5] = static_cast<Exiv2::byte>((denominator >> 16) & 0xFFu);
    b[6] = static_cast<Exiv2::byte>((denominator >> 8) & 0xFFu);
    b[7] = static_cast<Exiv2::byte>(denominator & 0xFFu);
    return b;
  }
};

TEST_F(GetURationalTest_1139, ReadsLittleEndianNumeratorAndDenominator_1139) {
  const uint32_t kNum = 0x01020304u;
  const uint32_t kDen = 0xA0B0C0D0u;
  const auto buf = MakeBufLittleEndian(kNum, kDen);

  const Exiv2::URational r = Exiv2::getURational(buf.data(), Exiv2::littleEndian);

  EXPECT_EQ(r.first, kNum);
  EXPECT_EQ(r.second, kDen);
}

TEST_F(GetURationalTest_1139, ReadsBigEndianNumeratorAndDenominator_1139) {
  const uint32_t kNum = 0x01020304u;
  const uint32_t kDen = 0xA0B0C0D0u;
  const auto buf = MakeBufBigEndian(kNum, kDen);

  const Exiv2::URational r = Exiv2::getURational(buf.data(), Exiv2::bigEndian);

  EXPECT_EQ(r.first, kNum);
  EXPECT_EQ(r.second, kDen);
}

TEST_F(GetURationalTest_1139, PreservesZeroDenominator_1139) {
  const uint32_t kNum = 123456789u;
  const uint32_t kDen = 0u;

  const auto le = MakeBufLittleEndian(kNum, kDen);
  const auto be = MakeBufBigEndian(kNum, kDen);

  const Exiv2::URational r_le = Exiv2::getURational(le.data(), Exiv2::littleEndian);
  EXPECT_EQ(r_le.first, kNum);
  EXPECT_EQ(r_le.second, 0u);

  const Exiv2::URational r_be = Exiv2::getURational(be.data(), Exiv2::bigEndian);
  EXPECT_EQ(r_be.first, kNum);
  EXPECT_EQ(r_be.second, 0u);
}

TEST_F(GetURationalTest_1139, HandlesUint32BoundaryValues_1139) {
  const uint32_t kNum = 0u;
  const uint32_t kDen = 0xFFFFFFFFu;

  const auto le = MakeBufLittleEndian(kNum, kDen);
  const auto be = MakeBufBigEndian(kNum, kDen);

  const Exiv2::URational r_le = Exiv2::getURational(le.data(), Exiv2::littleEndian);
  EXPECT_EQ(r_le.first, 0u);
  EXPECT_EQ(r_le.second, 0xFFFFFFFFu);

  const Exiv2::URational r_be = Exiv2::getURational(be.data(), Exiv2::bigEndian);
  EXPECT_EQ(r_be.first, 0u);
  EXPECT_EQ(r_be.second, 0xFFFFFFFFu);
}

}  // namespace
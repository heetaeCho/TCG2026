// SPDX-License-Identifier: GPL-2.0-or-later
// Test for Exiv2::getFloat
// File: ./TestProjects/exiv2/src/types.cpp

#include <gtest/gtest.h>

#include <array>
#include <cstdint>
#include <cstring>
#include <limits>

#include "exiv2/types.hpp"

namespace {

using Exiv2::byte;
using Exiv2::ByteOrder;

static std::array<byte, 4> encodeU32(uint32_t v, ByteOrder order) {
  std::array<byte, 4> b{};
  if (order == Exiv2::littleEndian) {
    b[0] = static_cast<byte>((v >> 0) & 0xFF);
    b[1] = static_cast<byte>((v >> 8) & 0xFF);
    b[2] = static_cast<byte>((v >> 16) & 0xFF);
    b[3] = static_cast<byte>((v >> 24) & 0xFF);
  } else {  // big endian (and anything else treated as "not little" for input crafting)
    b[0] = static_cast<byte>((v >> 24) & 0xFF);
    b[1] = static_cast<byte>((v >> 16) & 0xFF);
    b[2] = static_cast<byte>((v >> 8) & 0xFF);
    b[3] = static_cast<byte>((v >> 0) & 0xFF);
  }
  return b;
}

static uint32_t floatBits(float f) {
  uint32_t u = 0;
  static_assert(sizeof(u) == sizeof(f), "float must be 32-bit for this test");
  std::memcpy(&u, &f, sizeof(u));
  return u;
}

}  // namespace

class GetFloatTest_1143 : public ::testing::Test {};

TEST_F(GetFloatTest_1143, ReadsLittleEndianBitPattern_1143) {
  const uint32_t bits = 0x3F800000u;  // 1.0f (IEEE-754)
  const auto buf = encodeU32(bits, Exiv2::littleEndian);

  const float f = Exiv2::getFloat(buf.data(), Exiv2::littleEndian);

  EXPECT_EQ(floatBits(f), bits);
  EXPECT_FLOAT_EQ(f, 1.0f);
}

TEST_F(GetFloatTest_1143, ReadsBigEndianBitPattern_1143) {
  const uint32_t bits = 0xBF800000u;  // -1.0f (IEEE-754)
  const auto buf = encodeU32(bits, Exiv2::bigEndian);

  const float f = Exiv2::getFloat(buf.data(), Exiv2::bigEndian);

  EXPECT_EQ(floatBits(f), bits);
  EXPECT_FLOAT_EQ(f, -1.0f);
}

TEST_F(GetFloatTest_1143, ByteOrderChangesInterpretation_1143) {
  // Same byte sequence; different byte order should typically produce different bit patterns.
  const uint32_t bitsLE = 0x3F800000u;  // 1.0f
  const auto buf = encodeU32(bitsLE, Exiv2::littleEndian);

  const float asLE = Exiv2::getFloat(buf.data(), Exiv2::littleEndian);
  const float asBE = Exiv2::getFloat(buf.data(), Exiv2::bigEndian);

  EXPECT_EQ(floatBits(asLE), bitsLE);
  EXPECT_NE(floatBits(asBE), bitsLE);
}

TEST_F(GetFloatTest_1143, PreservesSignedZero_1143) {
  const uint32_t posZeroBits = 0x00000000u;
  const uint32_t negZeroBits = 0x80000000u;

  const auto posBufLE = encodeU32(posZeroBits, Exiv2::littleEndian);
  const auto negBufLE = encodeU32(negZeroBits, Exiv2::littleEndian);

  const float posZero = Exiv2::getFloat(posBufLE.data(), Exiv2::littleEndian);
  const float negZero = Exiv2::getFloat(negBufLE.data(), Exiv2::littleEndian);

  EXPECT_EQ(floatBits(posZero), posZeroBits);
  EXPECT_EQ(floatBits(negZero), negZeroBits);
  EXPECT_EQ(posZero, 0.0f);
  EXPECT_EQ(negZero, 0.0f);
}

TEST_F(GetFloatTest_1143, HandlesInfinityBitPatterns_1143) {
  const uint32_t posInfBits = 0x7F800000u;
  const uint32_t negInfBits = 0xFF800000u;

  const auto posBufBE = encodeU32(posInfBits, Exiv2::bigEndian);
  const auto negBufBE = encodeU32(negInfBits, Exiv2::bigEndian);

  const float posInf = Exiv2::getFloat(posBufBE.data(), Exiv2::bigEndian);
  const float negInf = Exiv2::getFloat(negBufBE.data(), Exiv2::bigEndian);

  EXPECT_EQ(floatBits(posInf), posInfBits);
  EXPECT_EQ(floatBits(negInf), negInfBits);
  EXPECT_TRUE(std::isinf(posInf));
  EXPECT_TRUE(std::isinf(negInf));
  EXPECT_GT(posInf, 0.0f);
  EXPECT_LT(negInf, 0.0f);
}

TEST_F(GetFloatTest_1143, HandlesNaNBitPatternWithoutFloatEquality_1143) {
  // One quiet-NaN payload (IEEE-754 common pattern). Compare by bits, not by float equality.
  const uint32_t qnanBits = 0x7FC00001u;
  const auto bufLE = encodeU32(qnanBits, Exiv2::littleEndian);

  const float f = Exiv2::getFloat(bufLE.data(), Exiv2::littleEndian);

  EXPECT_EQ(floatBits(f), qnanBits);
  EXPECT_TRUE(std::isnan(f));
}

TEST_F(GetFloatTest_1143, BoundarySubnormalAndMaxFinite_1143) {
  const uint32_t minSubnormalBits = 0x00000001u;  // smallest positive subnormal
  const uint32_t maxFiniteBits = 0x7F7FFFFFu;     // largest finite float

  const auto subBufBE = encodeU32(minSubnormalBits, Exiv2::bigEndian);
  const auto maxBufBE = encodeU32(maxFiniteBits, Exiv2::bigEndian);

  const float sub = Exiv2::getFloat(subBufBE.data(), Exiv2::bigEndian);
  const float maxf = Exiv2::getFloat(maxBufBE.data(), Exiv2::bigEndian);

  EXPECT_EQ(floatBits(sub), minSubnormalBits);
  EXPECT_EQ(floatBits(maxf), maxFiniteBits);

  EXPECT_GT(sub, 0.0f);
  EXPECT_LT(sub, std::numeric_limits<float>::min());  // min() is smallest *normal*
  EXPECT_TRUE(std::isfinite(maxf));
  EXPECT_GT(maxf, 0.0f);
}
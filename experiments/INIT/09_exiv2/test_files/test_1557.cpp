// File: test_asfvideo_guidtag_1557.cpp
#include <gtest/gtest.h>

#include <array>
#include <cstdint>

#include "exiv2/asfvideo.hpp"

namespace {

// Convenience alias (matches the header's data4_ element type).
using Exiv2::byte;

static std::array<byte, 8> MakeData4(std::initializer_list<unsigned int> vals) {
  std::array<byte, 8> a{};
  size_t i = 0;
  for (auto v : vals) {
    if (i >= a.size()) break;
    a[i++] = static_cast<byte>(v & 0xFFu);
  }
  return a;
}

}  // namespace

namespace Exiv2 {

TEST(AsfGuidTagTest_1557, EqualityIsReflexive_1557) {
  const AsfVideo::GUIDTag tag(
      0x11223344u, 0x5566u, 0x7788u,
      MakeData4({0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77}));

  EXPECT_TRUE(tag == tag);
}

TEST(AsfGuidTagTest_1557, EqualityIsSymmetricForIdenticalValues_1557) {
  const AsfVideo::GUIDTag a(
      0xAABBCCDDu, 0xEEFFu, 0x0102u,
      MakeData4({0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70, 0x80}));
  const AsfVideo::GUIDTag b(
      0xAABBCCDDu, 0xEEFFu, 0x0102u,
      MakeData4({0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70, 0x80}));

  EXPECT_TRUE(a == b);
  EXPECT_TRUE(b == a);
}

TEST(AsfGuidTagTest_1557, InequalityWhenData1Differs_1557) {
  const AsfVideo::GUIDTag a(
      0x00000001u, 0x0002u, 0x0003u,
      MakeData4({0, 1, 2, 3, 4, 5, 6, 7}));
  const AsfVideo::GUIDTag b(
      0x00000002u, 0x0002u, 0x0003u,
      MakeData4({0, 1, 2, 3, 4, 5, 6, 7}));

  EXPECT_FALSE(a == b);
}

TEST(AsfGuidTagTest_1557, InequalityWhenData2OrData3Differs_1557) {
  const AsfVideo::GUIDTag base(
      0x12345678u, 0x1111u, 0x2222u,
      MakeData4({7, 6, 5, 4, 3, 2, 1, 0}));

  const AsfVideo::GUIDTag diff2(
      0x12345678u, 0x1112u, 0x2222u,
      MakeData4({7, 6, 5, 4, 3, 2, 1, 0}));
  const AsfVideo::GUIDTag diff3(
      0x12345678u, 0x1111u, 0x2223u,
      MakeData4({7, 6, 5, 4, 3, 2, 1, 0}));

  EXPECT_FALSE(base == diff2);
  EXPECT_FALSE(base == diff3);
}

TEST(AsfGuidTagTest_1557, InequalityWhenData4DiffersAtAnyPosition_1557) {
  const AsfVideo::GUIDTag a(
      0x0u, 0x0u, 0x0u,
      MakeData4({0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF, 0x11, 0x22}));
  const AsfVideo::GUIDTag b(
      0x0u, 0x0u, 0x0u,
      MakeData4({0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF, 0x11, 0x23}));  // last byte differs

  EXPECT_FALSE(a == b);
}

TEST(AsfGuidTagTest_1557, BoundaryValuesAllZeroVsAllOnes_1557) {
  const AsfVideo::GUIDTag allZero(
      0x00000000u, 0x0000u, 0x0000u,
      MakeData4({0, 0, 0, 0, 0, 0, 0, 0}));

  const AsfVideo::GUIDTag allOnes(
      0xFFFFFFFFu, 0xFFFFu, 0xFFFFu,
      MakeData4({0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}));

  EXPECT_TRUE(allZero == allZero);
  EXPECT_TRUE(allOnes == allOnes);
  EXPECT_FALSE(allZero == allOnes);
}

}  // namespace Exiv2
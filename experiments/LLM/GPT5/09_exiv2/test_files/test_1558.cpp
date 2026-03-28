// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_asfvideo_guidtag_1558.cpp

#include <gtest/gtest.h>

#include <array>
#include <string>

#include "exiv2/asfvideo.hpp"

namespace {

// TEST_ID: 1558
class AsfVideoGuidTagTest_1558 : public ::testing::Test {};

using Exiv2::AsfVideo;

TEST_F(AsfVideoGuidTagTest_1558, ToString_FormatsUppercaseHexAndHyphens_1558) {
  const AsfVideo::GUIDTag tag(
      0xA1B2C3D4u, 0xE5F6u, 0x0102u,
      std::array<Exiv2::byte, 8>{0x03, 0x04, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF});

  const std::string s = tag.to_string();

  EXPECT_EQ(s, "A1B2C3D4-E5F6-0102-0304-AABBCCDDEEFF");
  EXPECT_EQ(s.size(), 36u);
  EXPECT_EQ(s[8], '-');
  EXPECT_EQ(s[13], '-');
  EXPECT_EQ(s[18], '-');
  EXPECT_EQ(s[23], '-');
}

TEST_F(AsfVideoGuidTagTest_1558, ToString_ZeroPadsAllFields_1558) {
  const AsfVideo::GUIDTag tag(
      0x00000001u, 0x0002u, 0x0003u,
      std::array<Exiv2::byte, 8>{0x00, 0x09, 0x00, 0x0A, 0x00, 0x0B, 0x00, 0x0C});

  EXPECT_EQ(tag.to_string(), "00000001-0002-0003-0009-000A000B000C");
}

TEST_F(AsfVideoGuidTagTest_1558, ToString_IsStableAcrossCalls_1558) {
  const AsfVideo::GUIDTag tag(
      0xDEADBEEFu, 0x1234u, 0xABCDu,
      std::array<Exiv2::byte, 8>{0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70, 0x80});

  const std::string a = tag.to_string();
  const std::string b = tag.to_string();

  EXPECT_EQ(a, b);
}

TEST_F(AsfVideoGuidTagTest_1558, Equality_ReturnsTrueForSameComponents_1558) {
  const std::array<Exiv2::byte, 8> d4{0x01, 0x02, 0x03, 0x04, 0xAA, 0xBB, 0xCC, 0xDD};

  const AsfVideo::GUIDTag a(0x11223344u, 0x5566u, 0x7788u, d4);
  const AsfVideo::GUIDTag b(0x11223344u, 0x5566u, 0x7788u, d4);

  EXPECT_TRUE(a == b);
  EXPECT_TRUE(b == a);
}

TEST_F(AsfVideoGuidTagTest_1558, LessThan_IsFalseForEqualObjects_1558) {
  const std::array<Exiv2::byte, 8> d4{0, 1, 2, 3, 4, 5, 6, 7};

  const AsfVideo::GUIDTag a(0x01020304u, 0x0506u, 0x0708u, d4);
  const AsfVideo::GUIDTag b(0x01020304u, 0x0506u, 0x0708u, d4);

  EXPECT_FALSE(a < b);
  EXPECT_FALSE(b < a);
}

}  // namespace
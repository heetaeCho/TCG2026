// File: asfvideo_guidtag_test_2198.cpp
#include <gtest/gtest.h>

#include <array>
#include <cstdint>
#include <string>

#include <exiv2/asfvideo.hpp>

namespace {

using Exiv2::AsfVideo;

static uint32_t ReadU32LE(const uint8_t* p) {
  return (static_cast<uint32_t>(p[0]) << 0) |
         (static_cast<uint32_t>(p[1]) << 8) |
         (static_cast<uint32_t>(p[2]) << 16) |
         (static_cast<uint32_t>(p[3]) << 24);
}

static uint16_t ReadU16LE(const uint8_t* p) {
  return static_cast<uint16_t>((static_cast<uint16_t>(p[0]) << 0) |
                               (static_cast<uint16_t>(p[1]) << 8));
}

static std::array<uint8_t, 16> MakeGuidBytes(uint32_t d1, uint16_t d2, uint16_t d3,
                                             const std::array<Exiv2::byte, 8>& d4) {
  std::array<uint8_t, 16> b{};
  // data1 little-endian
  b[0] = static_cast<uint8_t>((d1 >> 0) & 0xFF);
  b[1] = static_cast<uint8_t>((d1 >> 8) & 0xFF);
  b[2] = static_cast<uint8_t>((d1 >> 16) & 0xFF);
  b[3] = static_cast<uint8_t>((d1 >> 24) & 0xFF);
  // data2 little-endian
  b[4] = static_cast<uint8_t>((d2 >> 0) & 0xFF);
  b[5] = static_cast<uint8_t>((d2 >> 8) & 0xFF);
  // data3 little-endian
  b[6] = static_cast<uint8_t>((d3 >> 0) & 0xFF);
  b[7] = static_cast<uint8_t>((d3 >> 8) & 0xFF);
  // data4 bytes as-is
  for (size_t i = 0; i < 8; ++i) {
    b[8 + i] = static_cast<uint8_t>(d4[i]);
  }
  return b;
}

class AsfVideoGuidTagTest_2198 : public ::testing::Test {};

}  // namespace

TEST_F(AsfVideoGuidTagTest_2198, ConstructFromBytesMatchesComponentCtor_2198) {
  const std::array<Exiv2::byte, 8> d4 = {
      static_cast<Exiv2::byte>(0x10), static_cast<Exiv2::byte>(0x20),
      static_cast<Exiv2::byte>(0x30), static_cast<Exiv2::byte>(0x40),
      static_cast<Exiv2::byte>(0x50), static_cast<Exiv2::byte>(0x60),
      static_cast<Exiv2::byte>(0x70), static_cast<Exiv2::byte>(0x80),
  };

  const uint32_t d1 = 0xA1B2C3D4u;
  const uint16_t d2 = 0x1122u;
  const uint16_t d3 = 0x3344u;

  const auto bytes = MakeGuidBytes(d1, d2, d3, d4);

  const AsfVideo::GUIDTag fromBytes(bytes.data());

  // Compute expected fields from the raw byte buffer in little-endian form.
  const uint32_t exp1 = ReadU32LE(bytes.data());
  const uint16_t exp2 = ReadU16LE(bytes.data() + 4);
  const uint16_t exp3 = ReadU16LE(bytes.data() + 6);
  std::array<Exiv2::byte, 8> exp4{};
  for (size_t i = 0; i < 8; ++i) exp4[i] = static_cast<Exiv2::byte>(bytes[8 + i]);

  const AsfVideo::GUIDTag fromParts(exp1, exp2, exp3, exp4);

  EXPECT_TRUE(fromBytes == fromParts);
  EXPECT_FALSE(fromBytes < fromParts);
  EXPECT_FALSE(fromParts < fromBytes);
}

TEST_F(AsfVideoGuidTagTest_2198, EqualGuidsHaveSameToString_2198) {
  const std::array<uint8_t, 16> bytes = {
      0xD4, 0xC3, 0xB2, 0xA1,  // data1 LE
      0x22, 0x11,              // data2 LE
      0x44, 0x33,              // data3 LE
      0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70, 0x80};

  const AsfVideo::GUIDTag a(bytes.data());
  const AsfVideo::GUIDTag b(bytes.data());

  ASSERT_TRUE(a == b);

  const std::string sa = a.to_string();
  const std::string sb = b.to_string();

  EXPECT_EQ(sa, sb);
  EXPECT_FALSE(sa.empty());
}

TEST_F(AsfVideoGuidTagTest_2198, DifferentGuidsNotEqualAndPreferDifferentToString_2198) {
  const std::array<uint8_t, 16> bytes1 = {
      0x00, 0x00, 0x00, 0x00,  //
      0x00, 0x00,              //
      0x00, 0x00,              //
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

  const std::array<uint8_t, 16> bytes2 = {
      0x01, 0x00, 0x00, 0x00,  //
      0x00, 0x00,              //
      0x00, 0x00,              //
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

  const AsfVideo::GUIDTag a(bytes1.data());
  const AsfVideo::GUIDTag b(bytes2.data());

  EXPECT_FALSE(a == b);

  // While exact formatting is unspecified, it should be stable and usually distinct for different GUIDs.
  const std::string sa = a.to_string();
  const std::string sb = b.to_string();
  EXPECT_FALSE(sa.empty());
  EXPECT_FALSE(sb.empty());
  EXPECT_NE(sa, sb);
}

TEST_F(AsfVideoGuidTagTest_2198, LessThanIsFalseForEqualObjects_2198) {
  const std::array<uint8_t, 16> bytes = {
      0xFF, 0xFF, 0xFF, 0xFF,  //
      0xEE, 0xEE,              //
      0xDD, 0xDD,              //
      0xCC, 0xCC, 0xCC, 0xCC, 0xBB, 0xBB, 0xBB, 0xBB};

  const AsfVideo::GUIDTag a(bytes.data());
  const AsfVideo::GUIDTag b(bytes.data());

  ASSERT_TRUE(a == b);
  EXPECT_FALSE(a < b);
  EXPECT_FALSE(b < a);
}

TEST_F(AsfVideoGuidTagTest_2198, LessThanIsNotMutuallyTrueForDifferentObjects_2198) {
  const std::array<uint8_t, 16> bytesA = {
      0x00, 0x00, 0x00, 0x00,  //
      0x00, 0x00,              //
      0x00, 0x00,              //
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

  const std::array<uint8_t, 16> bytesB = {
      0x00, 0x00, 0x00, 0x00,  //
      0x00, 0x00,              //
      0x00, 0x00,              //
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01};

  const AsfVideo::GUIDTag a(bytesA.data());
  const AsfVideo::GUIDTag b(bytesB.data());

  ASSERT_FALSE(a == b);

  const bool a_lt_b = (a < b);
  const bool b_lt_a = (b < a);

  // A strict ordering must not claim both directions at once.
  EXPECT_FALSE(a_lt_b && b_lt_a);
}

TEST_F(AsfVideoGuidTagTest_2198, CopyConstructionPreservesEqualityAndString_2198) {
  const std::array<uint8_t, 16> bytes = {
      0x12, 0x34, 0x56, 0x78,  //
      0x9A, 0xBC,              //
      0xDE, 0xF0,              //
      0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF};

  const AsfVideo::GUIDTag original(bytes.data());
  const AsfVideo::GUIDTag copy(original);

  EXPECT_TRUE(original == copy);
  EXPECT_FALSE(original < copy);
  EXPECT_FALSE(copy < original);
  EXPECT_EQ(original.to_string(), copy.to_string());
}
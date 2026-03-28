// TEST_ID 1560
// Unit tests for ASF GUID detection helper and GUIDTag observable behavior.
//
// Notes:
// - isASFType() has internal linkage (static in asfvideo.cpp). To test it as a black box,
//   we include the production .cpp into this test translation unit.
// - These tests do NOT access private state and only use public/observable behavior.

#include <gtest/gtest.h>

#include <array>
#include <cstdint>
#include <string>

#include "exiv2/asfvideo.hpp"
#include "exiv2/types.hpp"

// Include the implementation file to access the internal-linkage helper.
// Adjust include path if your test target doesn't already have src/ on include dirs.
#include "asfvideo.cpp"

namespace {

using Exiv2::byte;

constexpr std::array<byte, 16> kAsfHeaderGuidBytes = {
    // 75B22630-668E-11CF-A6D9-00AA0062CE6C
    // GUID binary layout in ASF is: data1 (LE, 4 bytes), data2 (LE, 2 bytes), data3 (LE, 2 bytes), data4 (8 bytes)
    static_cast<byte>(0x30), static_cast<byte>(0x26), static_cast<byte>(0xB2), static_cast<byte>(0x75),
    static_cast<byte>(0x8E), static_cast<byte>(0x66),
    static_cast<byte>(0xCF), static_cast<byte>(0x11),
    static_cast<byte>(0xA6), static_cast<byte>(0xD9), static_cast<byte>(0x00), static_cast<byte>(0xAA),
    static_cast<byte>(0x00), static_cast<byte>(0x62), static_cast<byte>(0xCE), static_cast<byte>(0x6C),
};

class AsfVideoTest_1560 : public ::testing::Test {
 protected:
  static const byte* HeaderBytes() { return kAsfHeaderGuidBytes.data(); }

  static std::array<byte, 16> MutatedBytes(std::size_t idx, byte new_value) {
    auto b = kAsfHeaderGuidBytes;
    b[idx] = new_value;
    return b;
  }
};

}  // namespace

TEST_F(AsfVideoTest_1560, IsASFType_ReturnsTrueForAsfHeaderGuidBytes_1560) {
  EXPECT_TRUE(Exiv2::isASFType(HeaderBytes()));
}

TEST_F(AsfVideoTest_1560, IsASFType_ReturnsFalseWhenOneByteDiffers_1560) {
  // Flip the last byte to ensure mismatch.
  const auto mutated = MutatedBytes(15, static_cast<byte>(kAsfHeaderGuidBytes[15] ^ 0xFF));
  EXPECT_FALSE(Exiv2::isASFType(mutated.data()));
}

TEST_F(AsfVideoTest_1560, IsASFType_ReturnsFalseForReorderedFirstFieldBytes_1560) {
  // Same GUID value components but with the first 4 bytes reversed relative to expected ASF GUID layout.
  auto reordered = kAsfHeaderGuidBytes;
  std::swap(reordered[0], reordered[3]);
  std::swap(reordered[1], reordered[2]);

  EXPECT_FALSE(Exiv2::isASFType(reordered.data()));
}

TEST_F(AsfVideoTest_1560, GUIDTag_ConstructedFromHeaderBytesEqualsHeaderConstant_1560) {
  const Exiv2::AsfVideo::GUIDTag fromBytes(HeaderBytes());
  EXPECT_TRUE(fromBytes == Exiv2::Header);
  EXPECT_TRUE(Exiv2::Header == fromBytes);
}

TEST_F(AsfVideoTest_1560, GUIDTag_ToString_IsNonEmptyAndStableAcrossCalls_1560) {
  const Exiv2::AsfVideo::GUIDTag tag(HeaderBytes());

  const std::string s1 = tag.to_string();
  const std::string s2 = tag.to_string();

  EXPECT_FALSE(s1.empty());
  EXPECT_EQ(s1, s2);
}

TEST_F(AsfVideoTest_1560, GUIDTag_Ordering_IsStrictForDifferentGuids_1560) {
  // Create two different GUIDs by mutating a single byte and verify ordering is strict
  // (i.e., not both a<b and b<a).
  const Exiv2::AsfVideo::GUIDTag a(HeaderBytes());

  const auto mutated = MutatedBytes(0, static_cast<byte>(kAsfHeaderGuidBytes[0] + 1));
  const Exiv2::AsfVideo::GUIDTag b(mutated.data());

  const bool a_lt_b = a < b;
  const bool b_lt_a = b < a;

  EXPECT_NE(a_lt_b, b_lt_a);  // exactly one should be true for distinct values (or both false only if equal)
  EXPECT_FALSE(a == b);
}
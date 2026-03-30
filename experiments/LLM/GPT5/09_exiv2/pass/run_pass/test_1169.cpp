// File: test_tiffheaderbase_read_1169.cpp
// Unit tests for Exiv2::Internal::TiffHeaderBase::read()
// TEST_ID: 1169

#include <gtest/gtest.h>

#include <cstdint>
#include <vector>

#include "tiffimage_int.hpp"
#include "exiv2/types.hpp"

namespace {

using Exiv2::ByteOrder;
using Exiv2::Internal::TiffHeaderBase;

using ByteVec = std::vector<unsigned char>;

static ByteVec makeHeaderBytes(ByteOrder bo, uint16_t tag, uint32_t offset) {
  ByteVec b(8, 0);

  if (bo == Exiv2::littleEndian) {
    b[0] = 'I';
    b[1] = 'I';
    // tag (uint16) little-endian
    b[2] = static_cast<unsigned char>(tag & 0xFFu);
    b[3] = static_cast<unsigned char>((tag >> 8) & 0xFFu);
    // offset (uint32) little-endian
    b[4] = static_cast<unsigned char>(offset & 0xFFu);
    b[5] = static_cast<unsigned char>((offset >> 8) & 0xFFu);
    b[6] = static_cast<unsigned char>((offset >> 16) & 0xFFu);
    b[7] = static_cast<unsigned char>((offset >> 24) & 0xFFu);
  } else {
    b[0] = 'M';
    b[1] = 'M';
    // tag (uint16) big-endian
    b[2] = static_cast<unsigned char>((tag >> 8) & 0xFFu);
    b[3] = static_cast<unsigned char>(tag & 0xFFu);
    // offset (uint32) big-endian
    b[4] = static_cast<unsigned char>((offset >> 24) & 0xFFu);
    b[5] = static_cast<unsigned char>((offset >> 16) & 0xFFu);
    b[6] = static_cast<unsigned char>((offset >> 8) & 0xFFu);
    b[7] = static_cast<unsigned char>(offset & 0xFFu);
  }

  return b;
}

class TiffHeaderBaseTest_1169 : public ::testing::Test {
 protected:
  // Pick values that are easy to recognize when verifying observable state.
  static constexpr uint16_t kCtorTag = 0x1234;
  static constexpr uint32_t kCtorSize = 8;
  static constexpr uint32_t kCtorOffset = 0xA1B2C3D4u;

  static TiffHeaderBase makeDefault() {
    return TiffHeaderBase(kCtorTag, kCtorSize, Exiv2::invalidByteOrder, kCtorOffset);
  }
};

}  // namespace

TEST_F(TiffHeaderBaseTest_1169, ReadReturnsFalseWhenDataNull_1169) {
  auto hdr = makeDefault();

  EXPECT_FALSE(hdr.read(nullptr, 8));
}

TEST_F(TiffHeaderBaseTest_1169, ReadReturnsFalseWhenSizeLessThan8_1169) {
  auto hdr = makeDefault();

  ByteVec bytes = makeHeaderBytes(Exiv2::littleEndian, kCtorTag, 0x01020304u);
  ASSERT_GE(bytes.size(), 8u);

  // Boundary: size == 0
  EXPECT_FALSE(hdr.read(reinterpret_cast<const Exiv2::byte*>(bytes.data()), 0));

  // Boundary: size == 7 (just below required 8)
  EXPECT_FALSE(hdr.read(reinterpret_cast<const Exiv2::byte*>(bytes.data()), 7));
}

TEST_F(TiffHeaderBaseTest_1169, ReadReturnsFalseForInvalidByteOrderMarkers_1169) {
  auto hdr = makeDefault();

  ByteVec bytes(8, 0);
  bytes[0] = 'I';
  bytes[1] = 'M';  // not "II" nor "MM"
  // rest doesn't matter for this test

  EXPECT_FALSE(hdr.read(reinterpret_cast<const Exiv2::byte*>(bytes.data()), bytes.size()));
}

TEST_F(TiffHeaderBaseTest_1169, ReadSucceedsForLittleEndianMatchingTag_1169) {
  auto hdr = makeDefault();

  const uint16_t tag = kCtorTag;  // matching tag should be accepted
  const uint32_t offset = 0x01020304u;

  ByteVec bytes = makeHeaderBytes(Exiv2::littleEndian, tag, offset);

  ASSERT_TRUE(hdr.read(reinterpret_cast<const Exiv2::byte*>(bytes.data()), bytes.size()));

  EXPECT_EQ(hdr.byteOrder(), Exiv2::littleEndian);
  EXPECT_EQ(hdr.tag(), tag);
  EXPECT_EQ(hdr.offset(), offset);
}

TEST_F(TiffHeaderBaseTest_1169, ReadSucceedsForBigEndianMatchingTag_1169) {
  auto hdr = makeDefault();

  const uint16_t tag = kCtorTag;  // matching tag should be accepted
  const uint32_t offset = 0x0A0B0C0Du;

  ByteVec bytes = makeHeaderBytes(Exiv2::bigEndian, tag, offset);

  ASSERT_TRUE(hdr.read(reinterpret_cast<const Exiv2::byte*>(bytes.data()), bytes.size()));

  EXPECT_EQ(hdr.byteOrder(), Exiv2::bigEndian);
  EXPECT_EQ(hdr.tag(), tag);
  EXPECT_EQ(hdr.offset(), offset);
}

TEST_F(TiffHeaderBaseTest_1169, ReadReturnsFalseWhenTagDoesNotMatchAndNotSpecial_1169) {
  auto hdr = makeDefault();

  const uint16_t differentTag = static_cast<uint16_t>(kCtorTag ^ 0x00FFu);
  ASSERT_NE(differentTag, kCtorTag);

  // Ensure it's not one of the explicitly-allowed special tags.
  ASSERT_NE(differentTag, static_cast<uint16_t>(444));
  ASSERT_NE(differentTag, static_cast<uint16_t>(17234));

  ByteVec bytes = makeHeaderBytes(Exiv2::littleEndian, differentTag, 0x11223344u);

  EXPECT_FALSE(hdr.read(reinterpret_cast<const Exiv2::byte*>(bytes.data()), bytes.size()));
}

TEST_F(TiffHeaderBaseTest_1169, ReadAcceptsSpecialTag444EvenIfConstructorTagDiffers_1169) {
  // Construct with a tag that is intentionally different from 444.
  TiffHeaderBase hdr(/*tag=*/0x1111, /*size=*/kCtorSize, Exiv2::invalidByteOrder, /*offset=*/0);

  const uint16_t specialTag = 444;
  const uint32_t offset = 0x55667788u;

  ByteVec bytes = makeHeaderBytes(Exiv2::littleEndian, specialTag, offset);

  ASSERT_TRUE(hdr.read(reinterpret_cast<const Exiv2::byte*>(bytes.data()), bytes.size()));

  EXPECT_EQ(hdr.tag(), specialTag);
  EXPECT_EQ(hdr.offset(), offset);
  EXPECT_EQ(hdr.byteOrder(), Exiv2::littleEndian);
}

TEST_F(TiffHeaderBaseTest_1169, ReadAcceptsSpecialTag17234EvenIfConstructorTagDiffers_1169) {
  // Construct with a tag that is intentionally different from 17234.
  TiffHeaderBase hdr(/*tag=*/0x2222, /*size=*/kCtorSize, Exiv2::invalidByteOrder, /*offset=*/0);

  const uint16_t specialTag = 17234;
  const uint32_t offset = 0x99AABBCCu;

  ByteVec bytes = makeHeaderBytes(Exiv2::bigEndian, specialTag, offset);

  ASSERT_TRUE(hdr.read(reinterpret_cast<const Exiv2::byte*>(bytes.data()), bytes.size()));

  EXPECT_EQ(hdr.tag(), specialTag);
  EXPECT_EQ(hdr.offset(), offset);
  EXPECT_EQ(hdr.byteOrder(), Exiv2::bigEndian);
}

TEST_F(TiffHeaderBaseTest_1169, ReadBoundaryAllowsExactly8Bytes_1169) {
  auto hdr = makeDefault();

  ByteVec bytes = makeHeaderBytes(Exiv2::littleEndian, kCtorTag, 0x00000000u);
  ASSERT_EQ(bytes.size(), 8u);

  EXPECT_TRUE(hdr.read(reinterpret_cast<const Exiv2::byte*>(bytes.data()), 8));
  EXPECT_EQ(hdr.tag(), kCtorTag);
  EXPECT_EQ(hdr.offset(), 0u);
  EXPECT_EQ(hdr.byteOrder(), Exiv2::littleEndian);
}
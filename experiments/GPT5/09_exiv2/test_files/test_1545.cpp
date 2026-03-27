// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_cr2header_int_1545.cpp

#include <gtest/gtest.h>

#include <algorithm>
#include <cstdint>

#include "cr2header_int.hpp"
#include "types.hpp"

namespace {

using Exiv2::ByteOrder;
using Exiv2::bigEndian;
using Exiv2::invalidByteOrder;
using Exiv2::littleEndian;
using Exiv2::DataBuf;
using Exiv2::Internal::Cr2Header;

static void ExpectCommonCr2HeaderFields(const DataBuf& buf, ByteOrder order) {
  ASSERT_EQ(buf.size(), 16u);

  // The 2-byte tag should decode to the header's tag (known to be 42 via ctor chain),
  // when interpreted using the header's byte order.
  EXPECT_EQ(buf.read_uint16(2, order), static_cast<uint16_t>(42));

  // The 4-byte offset at 4 should be 0x10 (16) using the header's byte order.
  EXPECT_EQ(buf.read_uint32(4, order), static_cast<uint32_t>(0x00000010));

  // The 4-byte value at 12 should be zero using the header's byte order.
  EXPECT_EQ(buf.read_uint32(12, order), static_cast<uint32_t>(0x00000000));
}

}  // namespace

TEST(Cr2HeaderTest_1545, WriteLittleEndianSetsIIAndCommonFields_1545) {
  Cr2Header hdr(littleEndian);
  const DataBuf buf = hdr.write();

  ASSERT_EQ(buf.size(), 16u);

  EXPECT_EQ(buf.read_uint8(0), static_cast<uint8_t>('I'));
  EXPECT_EQ(buf.read_uint8(1), static_cast<uint8_t>('I'));

  ExpectCommonCr2HeaderFields(buf, littleEndian);
}

TEST(Cr2HeaderTest_1545, WriteBigEndianSetsMMAndCommonFields_1545) {
  Cr2Header hdr(bigEndian);
  const DataBuf buf = hdr.write();

  ASSERT_EQ(buf.size(), 16u);

  EXPECT_EQ(buf.read_uint8(0), static_cast<uint8_t>('M'));
  EXPECT_EQ(buf.read_uint8(1), static_cast<uint8_t>('M'));

  ExpectCommonCr2HeaderFields(buf, bigEndian);
}

TEST(Cr2HeaderTest_1545, WriteCopiesByte0ToByte1ForBothEndian_1545) {
  {
    Cr2Header hdr(littleEndian);
    const DataBuf buf = hdr.write();
    ASSERT_EQ(buf.size(), 16u);
    EXPECT_EQ(buf.read_uint8(1), buf.read_uint8(0));
  }
  {
    Cr2Header hdr(bigEndian);
    const DataBuf buf = hdr.write();
    ASSERT_EQ(buf.size(), 16u);
    EXPECT_EQ(buf.read_uint8(1), buf.read_uint8(0));
  }
}

TEST(Cr2HeaderTest_1545, WriteCr2SignatureBytesAreConsistentAcrossByteOrders_1545) {
  // We do NOT assume what the signature bytes are, only that they are written
  // deterministically and independent of byte order.
  Cr2Header le(littleEndian);
  Cr2Header be(bigEndian);

  const DataBuf bufLe = le.write();
  const DataBuf bufBe = be.write();

  ASSERT_EQ(bufLe.size(), 16u);
  ASSERT_EQ(bufBe.size(), 16u);

  const auto leBegin = bufLe.begin();
  const auto beBegin = bufBe.begin();

  ASSERT_NE(leBegin, bufLe.end());
  ASSERT_NE(beBegin, bufBe.end());

  const bool sigEqual =
      std::equal(leBegin + 8, leBegin + 12, beBegin + 8, beBegin + 12);
  EXPECT_TRUE(sigEqual);
}

TEST(Cr2HeaderTest_1545, WriteWithInvalidByteOrderReturnsSizedBufferAndMirrorsByte0ToByte1_1545) {
  // Observable behavior we can safely assert without assuming how invalid byte order is handled:
  // - write() returns a 16-byte buffer
  // - byte(1) mirrors byte(0) due to the explicit copy
  Cr2Header hdr(invalidByteOrder);
  const DataBuf buf = hdr.write();

  ASSERT_EQ(buf.size(), 16u);
  EXPECT_EQ(buf.read_uint8(1), buf.read_uint8(0));
}
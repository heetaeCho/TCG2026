// =================================================================================================
// TEST_ID: 1170
// Unit tests for Exiv2::Internal::TiffHeaderBase::write()
// File: ./TestProjects/exiv2/src/tiffimage_int.cpp
// =================================================================================================

#include <gtest/gtest.h>

#include "tiffimage_int.hpp"
#include "types.hpp"

namespace {

using Exiv2::ByteOrder;
using Exiv2::bigEndian;
using Exiv2::invalidByteOrder;
using Exiv2::littleEndian;

using Exiv2::DataBuf;
using Exiv2::Internal::TiffHeaderBase;

class TiffHeaderBaseWriteTest_1170 : public ::testing::Test {};

TEST_F(TiffHeaderBaseWriteTest_1170, LittleEndianWritesIIAndTagAndFixedOffset_1170) {
  const uint16_t tag = 0x002A;
  const TiffHeaderBase header(tag, /*size=*/0u, littleEndian, /*offset=*/0u);

  const DataBuf buf = header.write();

  ASSERT_EQ(buf.size(), 8u);
  EXPECT_EQ(buf.read_uint8(0), static_cast<uint8_t>('I'));
  EXPECT_EQ(buf.read_uint8(1), static_cast<uint8_t>('I'));
  EXPECT_EQ(buf.read_uint16(2, littleEndian), tag);
  EXPECT_EQ(buf.read_uint32(4, littleEndian), 0x00000008u);
}

TEST_F(TiffHeaderBaseWriteTest_1170, BigEndianWritesMMAndTagAndFixedOffset_1170) {
  const uint16_t tag = 0x002A;
  const TiffHeaderBase header(tag, /*size=*/0u, bigEndian, /*offset=*/0u);

  const DataBuf buf = header.write();

  ASSERT_EQ(buf.size(), 8u);
  EXPECT_EQ(buf.read_uint8(0), static_cast<uint8_t>('M'));
  EXPECT_EQ(buf.read_uint8(1), static_cast<uint8_t>('M'));
  EXPECT_EQ(buf.read_uint16(2, bigEndian), tag);
  EXPECT_EQ(buf.read_uint32(4, bigEndian), 0x00000008u);
}

TEST_F(TiffHeaderBaseWriteTest_1170, TagBoundaryZeroLittleEndian_1170) {
  const uint16_t tag = 0x0000;
  const TiffHeaderBase header(tag, /*size=*/0u, littleEndian, /*offset=*/0u);

  const DataBuf buf = header.write();

  ASSERT_EQ(buf.size(), 8u);
  EXPECT_EQ(buf.read_uint8(0), static_cast<uint8_t>('I'));
  EXPECT_EQ(buf.read_uint8(1), static_cast<uint8_t>('I'));
  EXPECT_EQ(buf.read_uint16(2, littleEndian), tag);
  EXPECT_EQ(buf.read_uint32(4, littleEndian), 0x00000008u);
}

TEST_F(TiffHeaderBaseWriteTest_1170, TagBoundaryMaxBigEndian_1170) {
  const uint16_t tag = 0xFFFF;
  const TiffHeaderBase header(tag, /*size=*/0u, bigEndian, /*offset=*/0u);

  const DataBuf buf = header.write();

  ASSERT_EQ(buf.size(), 8u);
  EXPECT_EQ(buf.read_uint8(0), static_cast<uint8_t>('M'));
  EXPECT_EQ(buf.read_uint8(1), static_cast<uint8_t>('M'));
  EXPECT_EQ(buf.read_uint16(2, bigEndian), tag);
  EXPECT_EQ(buf.read_uint32(4, bigEndian), 0x00000008u);
}

TEST_F(TiffHeaderBaseWriteTest_1170, WrittenOffsetIsFixedTo8RegardlessOfConstructorOffset_1170) {
  const uint16_t tag = 0x1234;

  const TiffHeaderBase headerA(tag, /*size=*/1u, littleEndian, /*offset=*/0u);
  const TiffHeaderBase headerB(tag, /*size=*/999u, littleEndian, /*offset=*/0xDEADBEEFu);

  const DataBuf bufA = headerA.write();
  const DataBuf bufB = headerB.write();

  ASSERT_EQ(bufA.size(), 8u);
  ASSERT_EQ(bufB.size(), 8u);

  EXPECT_EQ(bufA.read_uint32(4, littleEndian), 0x00000008u);
  EXPECT_EQ(bufB.read_uint32(4, littleEndian), 0x00000008u);
}

TEST_F(TiffHeaderBaseWriteTest_1170, InvalidByteOrderStillDuplicatesFirstByteIntoSecondByte_1170) {
  const uint16_t tag = 0x002A;
  const TiffHeaderBase header(tag, /*size=*/0u, invalidByteOrder, /*offset=*/0u);

  const DataBuf buf = header.write();

  ASSERT_EQ(buf.size(), 8u);

  const uint8_t b0 = buf.read_uint8(0);
  const uint8_t b1 = buf.read_uint8(1);
  EXPECT_EQ(b1, b0);
}

}  // namespace
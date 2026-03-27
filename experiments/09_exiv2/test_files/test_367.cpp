#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/src/tiffcomposite_int.hpp"

#include "exiv2/error.hpp"



using namespace Exiv2;

using namespace Exiv2::Internal;



class TiffEntryBaseTest_367 : public ::testing::Test {

protected:

    byte buffer[4]; // Buffer to hold the data

};



TEST_F(TiffEntryBaseTest_367, WriteOffset_UnsignedShort_Normal_367) {

    size_t offset = 123;

    TiffType tiffType = ttUnsignedShort;

    ByteOrder byteOrder = littleEndian;



    size_t rc = TiffEntryBase::writeOffset(buffer, offset, tiffType, byteOrder);



    EXPECT_EQ(rc, 2);

    EXPECT_EQ(buffer[0], 0x7b); // 123 in little endian

    EXPECT_EQ(buffer[1], 0x00);

}



TEST_F(TiffEntryBaseTest_367, WriteOffset_SignedShort_Normal_367) {

    size_t offset = -1;

    TiffType tiffType = ttSignedShort;

    ByteOrder byteOrder = littleEndian;



    EXPECT_THROW(TiffEntryBase::writeOffset(buffer, offset, tiffType, byteOrder), Error);

}



TEST_F(TiffEntryBaseTest_367, WriteOffset_UnsignedLong_Normal_367) {

    size_t offset = 123456;

    TiffType tiffType = ttUnsignedLong;

    ByteOrder byteOrder = littleEndian;



    size_t rc = TiffEntryBase::writeOffset(buffer, offset, tiffType, byteOrder);



    EXPECT_EQ(rc, 4);

    EXPECT_EQ(buffer[0], 0x00); // 123456 in little endian

    EXPECT_EQ(buffer[1], 0xe2);

    EXPECT_EQ(buffer[2], 0x01);

    EXPECT_EQ(buffer[3], 0x00);

}



TEST_F(TiffEntryBaseTest_367, WriteOffset_SignedLong_Normal_367) {

    size_t offset = -1;

    TiffType tiffType = ttSignedLong;

    ByteOrder byteOrder = littleEndian;



    size_t rc = TiffEntryBase::writeOffset(buffer, offset, tiffType, byteOrder);



    EXPECT_EQ(rc, 4);

    EXPECT_EQ(buffer[0], 0xff); // -1 in little endian

    EXPECT_EQ(buffer[1], 0xff);

    EXPECT_EQ(buffer[2], 0xff);

    EXPECT_EQ(buffer[3], 0xff);

}



TEST_F(TiffEntryBaseTest_367, WriteOffset_UnsignedShort_BoundaryMax_367) {

    size_t offset = std::numeric_limits<uint16_t>::max();

    TiffType tiffType = ttUnsignedShort;

    ByteOrder byteOrder = littleEndian;



    size_t rc = TiffEntryBase::writeOffset(buffer, offset, tiffType, byteOrder);



    EXPECT_EQ(rc, 2);

    EXPECT_EQ(buffer[0], 0xff); // 65535 in little endian

    EXPECT_EQ(buffer[1], 0xff);

}



TEST_F(TiffEntryBaseTest_367, WriteOffset_UnsignedShort_BoundaryOverflow_367) {

    size_t offset = std::numeric_limits<uint16_t>::max() + 1;

    TiffType tiffType = ttUnsignedShort;

    ByteOrder byteOrder = littleEndian;



    EXPECT_THROW(TiffEntryBase::writeOffset(buffer, offset, tiffType, byteOrder), Error);

}



TEST_F(TiffEntryBaseTest_367, WriteOffset_UnsupportedTiffType_367) {

    size_t offset = 123;

    TiffType tiffType = static_cast<TiffType>(99); // Unsupported type

    ByteOrder byteOrder = littleEndian;



    EXPECT_THROW(TiffEntryBase::writeOffset(buffer, offset, tiffType, byteOrder), Error);

}

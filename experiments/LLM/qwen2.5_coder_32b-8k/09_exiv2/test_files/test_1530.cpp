#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "makernote_int.cpp"  // Assuming this file contains the implementation



using namespace Exiv2::Internal;



TEST_F(SonyMnTest_1530, InvalidSize_ReturnsNullptr_1530) {

    uint16_t tag = 0;

    IfdId group = IfdId::exifSubIfd;

    const byte* pData = reinterpret_cast<const byte*>("SONY DSC \0\0\0");

    size_t size = 11;  // Invalid size

    ByteOrder byteOrder = littleEndian;



    EXPECT_EQ(nullptr, newSonyMn(tag, group, IfdId::sony1Id, pData, size, byteOrder));

}



TEST_F(SonyMnTest_1530, ValidSignature_ReturnsNonNullptr_1530) {

    uint16_t tag = 0;

    IfdId group = IfdId::exifSubIfd;

    const byte* pData = reinterpret_cast<const byte*>("SONY DSC \0\0\0");

    size_t size = 12;  // Valid signature size

    ByteOrder byteOrder = littleEndian;



    EXPECT_NE(nullptr, newSonyMn(tag, group, IfdId::sony1Id, pData, size, byteOrder));

}



TEST_F(SonyMnTest_1530, InvalidSignature_ReturnsNullptr_1530) {

    uint16_t tag = 0;

    IfdId group = IfdId::exifSubIfd;

    const byte* pData = reinterpret_cast<const byte*>("INVALID SIG");

    size_t size = 12;  // Invalid signature

    ByteOrder byteOrder = littleEndian;



    EXPECT_EQ(nullptr, newSonyMn(tag, group, IfdId::sony1Id, pData, size, byteOrder));

}



TEST_F(SonyMnTest_1530, SizeLessThanHeader_ReturnsNullptr_1530) {

    uint16_t tag = 0;

    IfdId group = IfdId::exifSubIfd;

    const byte* pData = reinterpret_cast<const byte*>("SONY DSC \0\0\0");

    size_t size = SonyMnHeader::sizeOfSignature() + 13;  // Invalid size for header

    ByteOrder byteOrder = littleEndian;



    EXPECT_EQ(nullptr, newSonyMn(tag, group, IfdId::sony1Id, pData, size, byteOrder));

}



TEST_F(SonyMnTest_1530, ValidSizeAndSignature_ReturnsNonNullptr_1530) {

    uint16_t tag = 0;

    IfdId group = IfdId::exifSubIfd;

    const byte* pData = reinterpret_cast<const byte*>("SONY DSC \0\0\0");

    size_t size = SonyMnHeader::sizeOfSignature() + 14;  // Valid size and signature

    ByteOrder byteOrder = littleEndian;



    EXPECT_NE(nullptr, newSonyMn(tag, group, IfdId::sony1Id, pData, size, byteOrder));

}

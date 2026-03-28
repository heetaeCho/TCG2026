#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "makernote_int.cpp"



using namespace Exiv2::Internal;



class OMSystemMnHeaderTest_1451 : public ::testing::Test {

protected:

    OMSystemMnHeader header;

};



TEST_F(OMSystemMnHeaderTest_1451, ReadReturnsFalseWhenDataIsNull_1451) {

    const byte* pData = nullptr;

    size_t size = 10;

    ByteOrder byteOrder;



    EXPECT_FALSE(header.read(pData, size, byteOrder));

}



TEST_F(OMSystemMnHeaderTest_1451, ReadReturnsFalseWhenSizeIsLessThanSignatureSizeMinusTwo_1451) {

    const byte pData[] = { 0x00 };

    size_t size = header.sizeOfSignature() - 3; // Assuming signature size is at least 3

    ByteOrder byteOrder;



    EXPECT_FALSE(header.read(pData, size, byteOrder));

}



TEST_F(OMSystemMnHeaderTest_1451, ReadReturnsTrueWhenDataMatchesSignature_1451) {

    const byte pData[] = { 0x4F, 0x4D, 0x00 }; // Assuming signature is "OM"

    size_t size = sizeof(pData);

    ByteOrder byteOrder;



    EXPECT_TRUE(header.read(pData, size, byteOrder));

}



TEST_F(OMSystemMnHeaderTest_1451, ReadReturnsFalseWhenDataDoesNotMatchSignature_1451) {

    const byte pData[] = { 0x4F, 0x4D, 0xFF }; // Assuming signature is "OM"

    size_t size = sizeof(pData);

    ByteOrder byteOrder;



    EXPECT_FALSE(header.read(pData, size, byteOrder));

}



TEST_F(OMSystemMnHeaderTest_1451, ReadHandlesExactSignatureSize_1451) {

    const byte pData[] = { 0x4F, 0x4D }; // Assuming signature is "OM"

    size_t size = sizeof(pData);

    ByteOrder byteOrder;



    EXPECT_TRUE(header.read(pData, size, byteOrder));

}

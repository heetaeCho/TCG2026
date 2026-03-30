#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/src/makernote_int.cpp"



using namespace Exiv2::Internal;



class Nikon2MnHeaderTest : public ::testing::Test {

protected:

    Nikon2MnHeader header;

};



TEST_F(Nikon2MnHeaderTest, ReadWithNullPointer_1463) {

    const byte* pData = nullptr;

    size_t size = 10;

    ByteOrder byteOrder = littleEndian;



    EXPECT_FALSE(header.read(pData, size, byteOrder));

}



TEST_F(Nikon2MnHeaderTest, ReadWithSizeLessThanSignature_1463) {

    const byte data[5] = { 0x00, 0x01, 0x02, 0x03, 0x04 };

    size_t size = sizeof(data);

    ByteOrder byteOrder = littleEndian;



    EXPECT_FALSE(header.read(data, size, byteOrder));

}



TEST_F(Nikon2MnHeaderTest, ReadWithInvalidSignature_1463) {

    const byte data[7] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06 };

    size_t size = sizeof(data);

    ByteOrder byteOrder = littleEndian;



    EXPECT_FALSE(header.read(data, size, byteOrder));

}



TEST_F(Nikon2MnHeaderTest, ReadWithValidSignature_1463) {

    const byte data[7] = { 'N', 'i', 'k', 'o', 'n', 0x01, 0x02 };

    size_t size = sizeof(data);

    ByteOrder byteOrder = littleEndian;



    EXPECT_TRUE(header.read(data, size, byteOrder));

}



TEST_F(Nikon2MnHeaderTest, ReadWithExactSignatureSize_1463) {

    const byte data[6] = { 'N', 'i', 'k', 'o', 'n', 0x01 };

    size_t size = sizeof(data);

    ByteOrder byteOrder = littleEndian;



    EXPECT_TRUE(header.read(data, size, byteOrder));

}

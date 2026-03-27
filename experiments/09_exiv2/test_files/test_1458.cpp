#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "makernote_int.cpp" // Assuming the header file includes this cpp



using namespace Exiv2::Internal;



class FujiMnHeaderTest_1458 : public ::testing::Test {

protected:

    FujiMnHeader fuji_header;

    const byte testData[16] = {0x46, 0x55, 0x4a, 0x49, 0x4d, 0x47, 0x00, 0x10, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00};

    const byte invalidData[8] = {0x46, 0x55, 0x4a, 0x49, 0x00, 0x10, 0x00, 0x10};



    size_t validSize = sizeof(testData);

    size_t invalidSize = sizeof(invalidData);



    ByteOrder byteOrder_ = littleEndian; // Assuming a default byte order for testing

};



TEST_F(FujiMnHeaderTest_1458, ReadValidData_1458) {

    EXPECT_TRUE(fuji_header.read(testData, validSize, byteOrder_));

}



TEST_F(FujiMnHeaderTest_1458, ReadInvalidSignature_1458) {

    EXPECT_FALSE(fuji_header.read(invalidData, invalidSize, byteOrder_));

}



TEST_F(FujiMnHeaderTest_1458, ReadNullPointer_1458) {

    EXPECT_FALSE(fuji_header.read(nullptr, validSize, byteOrder_));

}



TEST_F(FujiMnHeaderTest_1458, ReadInsufficientData_1458) {

    EXPECT_FALSE(fuji_header.read(testData, 7, byteOrder_));

}



TEST_F(FujiMnHeaderTest_1458, ReadExactSignatureSize_1458) {

    EXPECT_TRUE(fuji_header.read(testData, 8, byteOrder_));

}

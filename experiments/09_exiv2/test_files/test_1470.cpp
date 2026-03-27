#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "makernote_int.cpp"



namespace Exiv2 { namespace Internal {



class Nikon3MnHeaderTest : public ::testing::Test {

protected:

    Nikon3MnHeader header;

    byte testData[100];

    ByteOrder bo;



    void SetUp() override {

        memset(testData, 0, sizeof(testData));

        memcpy(testData, "Nikon\0", 6); // Correct signature for testing

        bo = littleEndian; // Default byte order

    }

};



TEST_F(Nikon3MnHeaderTest_1470, ReadWithValidData_1470) {

    testData[10] = 0x49; testData[11] = 0x49; testData[12] = 0x2A; testData[13] = 0x00;

    testData[18] = 0x00; testData[19] = 0x00; // offset is 0

    EXPECT_TRUE(header.read(testData, sizeof(testData), bo));

}



TEST_F(Nikon3MnHeaderTest_1470, ReadWithInvalidSignature_1470) {

    memcpy(testData, "Wrong\0", 6); // Incorrect signature

    testData[10] = 0x49; testData[11] = 0x49; testData[12] = 0x2A; testData[13] = 0x00;

    testData[18] = 0x00; testData[19] = 0x00; // offset is 0

    EXPECT_FALSE(header.read(testData, sizeof(testData), bo));

}



TEST_F(Nikon3MnHeaderTest_1470, ReadWithInsufficientSize_1470) {

    memcpy(testData, "Nikon\0", 6); // Correct signature for testing

    testData[10] = 0x49; testData[11] = 0x49; testData[12] = 0x2A; testData[13] = 0x00;

    testData[18] = 0x00; testData[19] = 0x00; // offset is 0

    EXPECT_FALSE(header.read(testData, 5, bo)); // size < sizeOfSignature()

}



TEST_F(Nikon3MnHeaderTest_1470, ReadWithNullPointer_1470) {

    testData[10] = 0x49; testData[11] = 0x49; testData[12] = 0x2A; testData[13] = 0x00;

    testData[18] = 0x00; testData[19] = 0x00; // offset is 0

    EXPECT_FALSE(header.read(nullptr, sizeof(testData), bo));

}



TEST_F(Nikon3MnHeaderTest_1470, ReadWithInvalidTiffHeader_1470) {

    memcpy(testData, "Nikon\0", 6); // Correct signature for testing

    testData[10] = 0x49; testData[11] = 0x49; testData[12] = 0x2A; testData[13] = 0xFF;

    testData[18] = 0x00; testData[19] = 0x00; // offset is 0

    EXPECT_FALSE(header.read(testData, sizeof(testData), bo));

}



} } // namespace Exiv2::Internal

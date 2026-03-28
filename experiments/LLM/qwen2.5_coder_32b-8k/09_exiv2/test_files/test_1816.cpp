#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/crwimage.hpp"

#include "exiv2/exif.hpp"



using namespace Exiv2;



class CrwParserTest_1816 : public ::testing::Test {

protected:

    void SetUp() override {

        io = std::make_unique<BasicIo>();

        crwImage = new CrwImage(std::move(io), false);

    }



    void TearDown() override {

        delete crwImage;

    }



    BasicIo::UniquePtr io;

    CrwImage* crwImage;

};



TEST_F(CrwParserTest_1816, DecodeNormalOperation_1816) {

    const byte testData[] = {0x49, 0x49, 0x2A, 0x00, 0x08, 0x00, 0x00, 0x00, 0x0E, 0x00, 0x00, 0x00, 0x49, 0x20, 0x01, 0x00,

                            0x03, 0x00, 0x01, 0x00, 0x00, 0x00, 0x2A, 0x00, 0x00, 0x00};

    size_t testDataSize = sizeof(testData) / sizeof(byte);

    

    CrwParser::decode(crwImage, testData, testDataSize);



    EXPECT_EQ(crwImage->exifData()["Exif.Image2.JPEGInterchangeFormat"].toLong(), 42u);

    EXPECT_EQ(crwImage->exifData()["Exif.Image2.JPEGInterchangeFormatLength"].toLong(), 1u);

}



TEST_F(CrwParserTest_1816, DecodeNoPreviewComponent_1816) {

    const byte testData[] = {0x49, 0x49, 0x2A, 0x00, 0x08, 0x00, 0x00, 0x00, 0x0E, 0x00, 0x00, 0x00};

    size_t testDataSize = sizeof(testData) / sizeof(byte);

    

    CrwParser::decode(crwImage, testData, testDataSize);



    EXPECT_FALSE(crwImage->exifData().findKey(ExifKey("Exif.Image2.JPEGInterchangeFormat")));

    EXPECT_FALSE(crwImage->exifData().findKey(ExifKey("Exif.Image2.JPEGInterchangeFormatLength")));

}



TEST_F(CrwParserTest_1816, DecodeEmptyData_1816) {

    const byte testData[] = {};

    size_t testDataSize = sizeof(testData) / sizeof(byte);

    

    CrwParser::decode(crwImage, testData, testDataSize);



    EXPECT_FALSE(crwImage->exifData().findKey(ExifKey("Exif.Image2.JPEGInterchangeFormat")));

    EXPECT_FALSE(crwImage->exifData().findKey(ExifKey("Exif.Image2.JPEGInterchangeFormatLength")));

}



TEST_F(CrwParserTest_1816, DecodeInvalidSignature_1816) {

    const byte testData[] = {0x49, 0x49, 0x2B, 0x00}; // Invalid TIFF signature

    size_t testDataSize = sizeof(testData) / sizeof(byte);

    

    CrwParser::decode(crwImage, testData, testDataSize);



    EXPECT_FALSE(crwImage->exifData().findKey(ExifKey("Exif.Image2.JPEGInterchangeFormat")));

    EXPECT_FALSE(crwImage->exifData().findKey(ExifKey("Exif.Image2.JPEGInterchangeFormatLength")));

}



TEST_F(CrwParserTest_1816, DecodeBoundaryConditionMinSize_1816) {

    const byte testData[] = {0x49, 0x49, 0x2A, 0x00};

    size_t testDataSize = sizeof(testData) / sizeof(byte);

    

    CrwParser::decode(crwImage, testData, testDataSize);



    EXPECT_FALSE(crwImage->exifData().findKey(ExifKey("Exif.Image2.JPEGInterchangeFormat")));

    EXPECT_FALSE(crwImage->exifData().findKey(ExifKey("Exif.Image2.JPEGInterchangeFormatLength")));

}



TEST_F(CrwParserTest_1816, DecodeBoundaryConditionMaxSize_1816) {

    const byte testData[1024] = {}; // Max realistic data size

    for (int i = 0; i < 4; ++i) testData[i] = 0x49 + i; // Set a minimal valid header



    CrwParser::decode(crwImage, testData, sizeof(testData));



    EXPECT_FALSE(crwImage->exifData().findKey(ExifKey("Exif.Image2.JPEGInterchangeFormat")));

    EXPECT_FALSE(crwImage->exifData().findKey(ExifKey("Exif.Image2.JPEGInterchangeFormatLength")));

}

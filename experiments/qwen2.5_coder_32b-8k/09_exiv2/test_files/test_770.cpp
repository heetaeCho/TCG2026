#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/exif.hpp"

#include <string>



using namespace Exiv2;

using ::testing::_;

using ::testing::Eq;



class ExifThumbTest_770 : public ::testing::Test {

protected:

    class MockExifData : public ExifData {

    public:

        MOCK_METHOD(void, setJpegThumbnail, (const byte*, size_t, URational, URational, uint16_t), (override));

        MOCK_METHOD(void, erase, (), (override));

    };



    MockExifData mockExifData;

    ExifThumb exifThumb;



    ExifThumbTest_770() : exifThumb(mockExifData) {}

};



TEST_F(ExifThumbTest_770, SetJpegThumbnailWithFilePathNormalOperation_770) {

    std::string validPath = "valid/path/to/thumbnail.jpg";

    URational xres(1, 1);

    URational yres(1, 1);

    uint16_t unit = 1;



    EXPECT_CALL(mockExifData, setJpegThumbnail(_, _, Eq(xres), Eq(yres), Eq(unit))).Times(1);



    exifThumb.setJpegThumbnail(validPath, xres, yres, unit);

}



TEST_F(ExifThumbTest_770, SetJpegThumbnailWithFilePathBoundaryConditionEmptyPath_770) {

    std::string emptyPath = "";

    URational xres(1, 1);

    URational yres(1, 1);

    uint16_t unit = 1;



    EXPECT_THROW(exifThumb.setJpegThumbnail(emptyPath, xres, yres, unit), Exiv2::Error);

}



TEST_F(ExifThumbTest_770, SetJpegThumbnailWithFilePathBoundaryConditionNonexistentFile_770) {

    std::string nonExistentPath = "non/existent/path.jpg";

    URational xres(1, 1);

    URational yres(1, 1);

    uint16_t unit = 1;



    EXPECT_THROW(exifThumb.setJpegThumbnail(nonExistentPath, xres, yres, unit), Exiv2::Error);

}



TEST_F(ExifThumbTest_770, SetJpegThumbnailWithBufferNormalOperation_770) {

    const byte buffer[] = { 0xFF, 0xD8, 0xFF, 0xE0 };

    size_t bufferSize = sizeof(buffer) / sizeof(byte);

    URational xres(1, 1);

    URational yres(1, 1);

    uint16_t unit = 1;



    EXPECT_CALL(mockExifData, setJpegThumbnail(Eq(buffer), Eq(bufferSize), Eq(xres), Eq(yres), Eq(unit))).Times(1);



    exifThumb.setJpegThumbnail(buffer, bufferSize, xres, yres, unit);

}



TEST_F(ExifThumbTest_770, SetJpegThumbnailWithBufferBoundaryConditionZeroSize_770) {

    const byte buffer[] = { 0xFF, 0xD8, 0xFF, 0xE0 };

    size_t bufferSize = 0;

    URational xres(1, 1);

    URational yres(1, 1);

    uint16_t unit = 1;



    EXPECT_CALL(mockExifData, setJpegThumbnail(Eq(buffer), Eq(bufferSize), Eq(xres), Eq(yres), Eq(unit))).Times(1);



    exifThumb.setJpegThumbnail(buffer, bufferSize, xres, yres, unit);

}



TEST_F(ExifThumbTest_770, EraseNormalOperation_770) {

    EXPECT_CALL(mockExifData, erase()).Times(1);



    exifThumb.erase();

}

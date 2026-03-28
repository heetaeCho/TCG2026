#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/crwimage.hpp"

#include "exiv2/exifdata.hpp"



using namespace Exiv2;



class CrwImageTest : public ::testing::Test {

protected:

    BasicIo::UniquePtr io = std::make_unique<BasicIo>();

    bool create = false;

    CrwImage* crwImage = nullptr;



    void SetUp() override {

        crwImage = new CrwImage(std::move(io), create);

    }



    void TearDown() override {

        delete crwImage;

    }

};



TEST_F(CrwImageTest, PixelHeight_ReturnsZero_WhenKeyNotFound_1813) {

    EXPECT_EQ(crwImage->pixelHeight(), 0U);

}



TEST_F(CrwImageTest, PixelHeight_ReturnsCorrectValue_WhenKeyFound_1813) {

    ExifData& exifData = crwImage->exifData();

    uint32_t expectedHeight = 480;

    Exifdatum datum(ExifKey("Exif.Photo.PixelYDimension"), new Value::Uint32(expectedHeight));

    exifData.add(datum);



    EXPECT_EQ(crwImage->pixelHeight(), expectedHeight);

}



TEST_F(CrwImageTest, PixelHeight_ReturnsZero_WhenCountIsZero_1813) {

    ExifData& exifData = crwImage->exifData();

    Exifdatum datum(ExifKey("Exif.Photo.PixelYDimension"), new Value::Uint32(0));

    datum.setValue(static_cast<uint32_t>(0)); // Set count to 0

    exifData.add(datum);



    EXPECT_EQ(crwImage->pixelHeight(), 0U);

}



TEST_F(CrwImageTest, PixelHeight_ReturnsZero_WhenValueIsZero_1813) {

    ExifData& exifData = crwImage->exifData();

    uint32_t zeroHeight = 0;

    Exifdatum datum(ExifKey("Exif.Photo.PixelYDimension"), new Value::Uint32(zeroHeight));

    exifData.add(datum);



    EXPECT_EQ(crwImage->pixelHeight(), zeroHeight);

}

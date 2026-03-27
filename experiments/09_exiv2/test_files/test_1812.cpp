#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/crwimage.hpp"

#include "exiv2/exif.hpp"



using namespace Exiv2;



class MockExifData : public ExifData {

public:

    MOCK_METHOD1(findKey, iterator(const ExifKey& key));

};



class CrwImageTest_1812 : public ::testing::Test {

protected:

    std::unique_ptr<BasicIo> io_;

    MockExifData mockExifData;

    CrwImage* crwImage;



    void SetUp() override {

        io_ = BasicIo::createMemIo();

        crwImage = new CrwImage(std::move(io_), false);

        crwImage->exifData_ = mockExifData;

    }



    void TearDown() override {

        delete crwImage;

    }

};



TEST_F(CrwImageTest_1812, PixelWidth_ReturnsValueFromExifData_1812) {

    ExifKey pixelXDimensionKey("Exif.Photo.PixelXDimension");

    Exiv2::Exifdatum exifDatum(pixelXDimensionKey, new Value);

    exifDatum.setValue(3000u);



    EXPECT_CALL(mockExifData, findKey(testing::_))

        .WillOnce(testing::Return(&exifDatum));



    EXPECT_EQ(crwImage->pixelWidth(), 3000u);

}



TEST_F(CrwImageTest_1812, PixelWidth_ReturnsZeroWhenKeyNotFound_1812) {

    ExifKey pixelXDimensionKey("Exif.Photo.PixelXDimension");



    EXPECT_CALL(mockExifData, findKey(testing::_))

        .WillOnce(testing::Return(mockExifData.end()));



    EXPECT_EQ(crwImage->pixelWidth(), 0u);

}



TEST_F(CrwImageTest_1812, PixelWidth_ReturnsZeroWhenCountIsZero_1812) {

    ExifKey pixelXDimensionKey("Exif.Photo.PixelXDimension");

    Exiv2::Exifdatum exifDatum(pixelXDimensionKey, new Value);



    EXPECT_CALL(mockExifData, findKey(testing::_))

        .WillOnce(testing::Return(&exifDatum));



    EXPECT_CALL(exifDatum, count())

        .WillOnce(testing::Return(0u));



    EXPECT_EQ(crwImage->pixelWidth(), 0u);

}

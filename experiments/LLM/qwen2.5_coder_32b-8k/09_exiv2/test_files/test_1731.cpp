#include <gtest/gtest.h>

#include "exiv2/tiffimage.hpp"

#include "exiv2/exifdata.hpp"

#include "exiv2/metadata.hpp"



using namespace Exiv2;



class TiffImageTest_1731 : public ::testing::Test {

protected:

    BasicIo::UniquePtr io = std::make_unique<BasicIo>(nullptr);

    TiffImage image{std::move(io), false};

};



TEST_F(TiffImageTest_1731, PixelHeight_ReturnsPrimaryValue_WhenSet_1731) {

    image.pixelHeightPrimary_ = 4096;

    EXPECT_EQ(image.pixelHeight(), 4096);

}



TEST_F(TiffImageTest_1731, PixelHeight_ReadsFromExifData_WhenPrimaryNotSet_1731) {

    ExifKey key("Exif.Image.PrimaryGroup.ImageLength");

    Exifdatum exifDatum(key, nullptr);

    exifDatum.setValue(8192);

    image.exifData_.add(exifDatum);



    EXPECT_EQ(image.pixelHeight(), 8192);

}



TEST_F(TiffImageTest_1731, PixelHeight_ReturnsZero_WhenNeitherPrimaryNorExifDataAvailable_1731) {

    image.pixelHeightPrimary_ = 0;

    image.exifData_.clear();



    EXPECT_EQ(image.pixelHeight(), 0);

}



TEST_F(TiffImageTest_1731, PixelHeight_ReturnsCountValueFromExifData_WhenPrimaryNotSetAndMultipleCountsAvailable_1731) {

    ExifKey key("Exif.Image.PrimaryGroup.ImageLength");

    Exifdatum exifDatum(key, nullptr);

    exifDatum.setValue(8192);

    exifDatum.setValue(4096); // Simulate multiple counts

    image.exifData_.add(exifDatum);



    EXPECT_EQ(image.pixelHeight(), 8192); // Only the first count value is expected to be returned

}



TEST_F(TiffImageTest_1731, PixelHeight_ReturnsZero_WhenExifDataEntryHasNoCounts_1731) {

    ExifKey key("Exif.Image.PrimaryGroup.ImageLength");

    Exifdatum exifDatum(key, nullptr);

    image.exifData_.add(exifDatum);



    EXPECT_EQ(image.pixelHeight(), 0); // Since count() is 0, it should return 0

}

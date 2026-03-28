#include <gtest/gtest.h>

#include "exiv2/exif.hpp"

#include "./TestProjects/exiv2/src/easyaccess.cpp"



using namespace Exiv2;



class ImageQualityTest_517 : public ::testing::Test {

protected:

    ExifData exif_data_;

};



TEST_F(ImageQualityTest_517, FindExistingKey_517) {

    exif_data_.add(ExifKey("Exif.CanonCs.Quality"), new UShortValue(UShort(10)));

    EXPECT_NE(imageQuality(exif_data_), exif_data_.end());

}



TEST_F(ImageQualityTest_517, FindNonExistingKey_517) {

    EXPECT_EQ(imageQuality(exif_data_), exif_data_.end());

}



TEST_F(ImageQualityTest_517, MultipleKeysPresent_517) {

    exif_data_.add(ExifKey("Exif.CanonCs.Quality"), new UShortValue(UShort(10)));

    exif_data_.add(ExifKey("Exif.Fujifilm.Quality"), new UShortValue(UShort(20)));

    EXPECT_NE(imageQuality(exif_data_), exif_data_.end());

}



TEST_F(ImageQualityTest_517, EmptyExifData_517) {

    EXPECT_EQ(imageQuality(exif_data_), exif_data_.end());

}



TEST_F(ImageQualityTest_517, FindLastKey_517) {

    exif_data_.add(ExifKey("Exif.Casio2.Quality"), new UShortValue(UShort(30)));

    EXPECT_NE(imageQuality(exif_data_), exif_data_.end());

}

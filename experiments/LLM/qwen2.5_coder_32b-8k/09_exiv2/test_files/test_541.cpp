#include <gtest/gtest.h>

#include "exiv2/exif.hpp"



using namespace Exiv2;



class ExposureIndexTest : public ::testing::Test {

protected:

    ExifData exifData;

};



TEST_F(ExposureIndexTest_541, FindExifPhotoExposureIndex_541) {

    Exifdatum datum("Exif.Photo.ExposureIndex", 0);

    exifData.add(datum);



    auto it = exposureIndex(exifData);

    ASSERT_NE(it, exifData.end());

    EXPECT_EQ(it->key(), "Exif.Photo.ExposureIndex");

}



TEST_F(ExposureIndexTest_541, FindExifImageExposureIndex_541) {

    Exifdatum datum("Exif.Image.ExposureIndex", 0);

    exifData.add(datum);



    auto it = exposureIndex(exifData);

    ASSERT_NE(it, exifData.end());

    EXPECT_EQ(it->key(), "Exif.Image.ExposureIndex");

}



TEST_F(ExposureIndexTest_541, NoMatch_541) {

    Exifdatum datum("Exif.Some.OtherTag", 0);

    exifData.add(datum);



    auto it = exposureIndex(exifData);

    EXPECT_EQ(it, exifData.end());

}



TEST_F(ExposureIndexTest_541, MultipleMatchesPrioritizePhoto_541) {

    Exifdatum photoDatum("Exif.Photo.ExposureIndex", 0);

    Exifdatum imageDatum("Exif.Image.ExposureIndex", 0);

    exifData.add(photoDatum);

    exifData.add(imageDatum);



    auto it = exposureIndex(exifData);

    ASSERT_NE(it, exifData.end());

    EXPECT_EQ(it->key(), "Exif.Photo.ExposureIndex");

}



TEST_F(ExposureIndexTest_541, EmptyExifData_541) {

    auto it = exposureIndex(exifData);

    EXPECT_EQ(it, exifData.end());

}

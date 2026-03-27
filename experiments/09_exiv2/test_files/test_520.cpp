#include <gtest/gtest.h>

#include "exiv2/exif.hpp"



using namespace Exiv2;



TEST_F(SaturationTest_520, NormalOperationWithExistingKey_520) {

    ExifData exifData;

    exifData.add("Exif.Photo.Saturation", new UShort(1));

    auto it = saturation(exifData);

    EXPECT_NE(it, exifData.end());

}



TEST_F(SaturationTest_520, NormalOperationWithNonExistingKey_520) {

    ExifData exifData;

    auto it = saturation(exifData);

    EXPECT_EQ(it, exifData.end());

}



TEST_F(SaturationTest_520, BoundaryConditionEmptyExifData_520) {

    ExifData exifData;

    auto it = saturation(exifData);

    EXPECT_EQ(it, exifData.end());

}



TEST_F(SaturationTest_520, BoundaryConditionMultipleKeysPresent_520) {

    ExifData exifData;

    exifData.add("Exif.Photo.Saturation", new UShort(1));

    exifData.add("Exif.CanonCs.Saturation", new UShort(2));

    auto it = saturation(exifData);

    EXPECT_NE(it, exifData.end());

}



TEST_F(SaturationTest_520, BoundaryConditionMultipleKeysNotPresent_520) {

    ExifData exifData;

    exifData.add("Exif.Photo.ISOSpeed", new UShort(1));

    exifData.add("Exif.CanonCs.ISOSpeed", new UShort(2));

    auto it = saturation(exifData);

    EXPECT_EQ(it, exifData.end());

}

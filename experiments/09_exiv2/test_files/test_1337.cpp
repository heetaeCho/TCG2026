#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/tags.hpp"



namespace Exiv2 {



class ExifKeyTest : public ::testing::Test {

protected:

    ExifKey exifKey1;

    ExifKey exifKey2 = ExifKey("Exif.Image.Artist");

    ExifKey exifKey3 = ExifKey(0x112, "Exif.TIF");

};



TEST_F(ExifKeyTest_1337, DefaultConstructor_FamilyName_1337) {

    EXPECT_STREQ(exifKey1.familyName(), "Iptc");

}



TEST_F(ExifKeyTest_1337, StringConstructor_FamilyName_1337) {

    EXPECT_STREQ(exifKey2.familyName(), "Exif");

}



TEST_F(ExifKeyTest_1337, TagGroupConstructor_FamilyName_1337) {

    EXPECT_STREQ(exifKey3.familyName(), "Exif");

}



} // namespace Exiv2

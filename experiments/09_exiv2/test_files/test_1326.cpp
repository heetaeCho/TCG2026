#include <gtest/gtest.h>

#include <exiv2/tags.hpp>



using namespace Exiv2;



class ExifTagsTest_1326 : public ::testing::Test {

protected:

    ExifTags exifTags;

};



TEST_F(ExifTagsTest_1326, IsExifGroup_ReturnsTrueForValidExifGroupName_1326) {

    EXPECT_TRUE(exifTags.isExifGroup("IFD0"));

}



TEST_F(ExifTagsTest_1326, IsExifGroup_ReturnsFalseForInvalidExifGroupName_1326) {

    EXPECT_FALSE(exifTags.isExifGroup("NonExistentGroup"));

}



TEST_F(ExifTagsTest_1326, IsExifGroup_ReturnsTrueForAnotherValidExifGroupName_1326) {

    EXPECT_TRUE(exifTags.isExifGroup("EXIF"));

}



TEST_F(ExifTagsTest_1326, IsExifGroup_HandlesEmptyStringGracefully_1326) {

    EXPECT_FALSE(exifTags.isExifGroup(""));

}

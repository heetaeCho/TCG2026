#include <gtest/gtest.h>

#include "exiv2/tags.hpp"

#include "exiv2/tags_int.hpp"



namespace {



using namespace Exiv2;



class ExifTagsTest : public ::testing::Test {

protected:

    ExifTags exifTags;

};



TEST_F(ExifTagsTest_1322, SectionName_ReturnsKnownSectionNameForValidTag_1322) {

    // Arrange

    ExifKey key(0x9003, "Exif.Image");  // Example tag for DateTimeOriginal



    // Act

    const char* section = exifTags.sectionName(key);



    // Assert

    EXPECT_STREQ(section, "DateTime");

}



TEST_F(ExifTagsTest_1322, SectionName_ReturnsUnknownSectionNameForInvalidTag_1322) {

    // Arrange

    ExifKey key(65535, "UnknownGroup");  // Invalid tag



    // Act

    const char* section = exifTags.sectionName(key);



    // Assert

    EXPECT_STREQ(section, "(UnknownSection)");

}



TEST_F(ExifTagsTest_1322, SectionName_ReturnsKnownSectionNameForTagInSpecificIFD_1322) {

    // Arrange

    ExifKey key(0x9003, "Exif.SubIFD");  // Example tag for DateTimeOriginal in SubIFD



    // Act

    const char* section = exifTags.sectionName(key);



    // Assert

    EXPECT_STREQ(section, "DateTime");

}



TEST_F(ExifTagsTest_1322, SectionName_ReturnsKnownSectionNameForTagInSpecificGroup_1322) {

    // Arrange

    ExifKey key(0x9003);  // Example tag for DateTimeOriginal without specific group



    // Act

    const char* section = exifTags.sectionName(key);



    // Assert

    EXPECT_STREQ(section, "DateTime");

}



}  // namespace

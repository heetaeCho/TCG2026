#include <gtest/gtest.h>

#include "exiv2/tags.hpp"



namespace Exiv2 {

    class MockExifTags : public ExifTags {

    public:

        MOCK_METHOD(bool, isMakerGroup, (const std::string& groupName), (override));

    };

}



class ExifTagsTest_1325 : public ::testing::Test {};



TEST_F(ExifTagsTest_1325, IsMakerGroup_ReturnsTrueForKnownMakerGroup_1325) {

    Exiv2::ExifTags exifTags;

    EXPECT_EQ(exifTags.isMakerGroup("MakerNotes"), true);

}



TEST_F(ExifTagsTest_1325, IsMakerGroup_ReturnsFalseForUnknownGroup_1325) {

    Exiv2::ExifTags exifTags;

    EXPECT_EQ(exifTags.isMakerGroup("UnknownGroup"), false);

}



TEST_F(ExifTagsTest_1325, IsMakerGroup_BoundaryConditionEmptyString_1325) {

    Exiv2::ExifTags exifTags;

    EXPECT_EQ(exifTags.isMakerGroup(""), false);

}



TEST_F(ExifTagsTest_1325, IsMakerGroup_ExceptionalCaseNonAsciiGroupName_1325) {

    Exiv2::ExifTags exifTags;

    EXPECT_EQ(exifTags.isMakerGroup("Invalid\x80GroupName"), false);

}

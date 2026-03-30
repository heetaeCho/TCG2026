#include <gtest/gtest.h>

#include "exiv2/tags.hpp"



class ExifTagsTest_1327 : public ::testing::Test {

protected:

    Exiv2::ExifTags exifTags;

};



TEST_F(ExifTagsTest_1327, GroupList_ReturnsNonNullPointer_1327) {

    const Exiv2::GroupInfo* groupList = exifTags.groupList();

    EXPECT_NE(groupList, nullptr);

}



// Assuming boundary conditions for groupName in tagList

TEST_F(ExifTagsTest_1327, TagList_ValidGroupName_ReturnsNonNullPointer_1327) {

    const Exiv2::TagInfo* tagInfo = exifTags.tagList("IFD0");

    EXPECT_NE(tagInfo, nullptr);

}



TEST_F(ExifTagsTest_1327, TagList_InvalidGroupName_ReturnsNullPointer_1327) {

    const Exiv2::TagInfo* tagInfo = exifTags.tagList("INVALID_GROUP");

    EXPECT_EQ(tagInfo, nullptr);

}



// Assuming boundary conditions for groupName in ifdName

TEST_F(ExifTagsTest_1327, IfdName_ValidGroupName_ReturnsNonNullPointer_1327) {

    const char* ifdName = exifTags.ifdName("IFD0");

    EXPECT_STRNE(ifdName, "");

}



TEST_F(ExifTagsTest_1327, IfdName_InvalidGroupName_ReturnsEmptyString_1327) {

    const char* ifdName = exifTags.ifdName("INVALID_GROUP");

    EXPECT_STREQ(ifdName, "");

}



// Assuming boundary conditions for groupName in isMakerGroup

TEST_F(ExifTagsTest_1327, IsMakerGroup_ValidMakerGroupName_ReturnsTrue_1327) {

    bool isMaker = exifTags.isMakerGroup("MakerNote");

    EXPECT_TRUE(isMaker);

}



TEST_F(ExifTagsTest_1327, IsMakerGroup_NonMakerGroupName_ReturnsFalse_1327) {

    bool isMaker = exifTags.isMakerGroup("IFD0");

    EXPECT_FALSE(isMaker);

}



// Assuming boundary conditions for groupName in isExifGroup

TEST_F(ExifTagsTest_1327, IsExifGroup_ValidExifGroupName_ReturnsTrue_1327) {

    bool isExif = exifTags.isExifGroup("IFD0");

    EXPECT_TRUE(isExif);

}



TEST_F(ExifTagsTest_1327, IsExifGroup_NonExifGroupName_ReturnsFalse_1327) {

    bool isExif = exifTags.isExifGroup("MakerNote");

    EXPECT_FALSE(isExif);

}



// Assuming sectionName and defaultCount require valid ExifKey

TEST_F(ExifTagsTest_1327, SectionName_ValidExifKey_ReturnsNonNullPointer_1327) {

    Exiv2::ExifKey key("Exif.Image.Artist");

    const char* section = exifTags.sectionName(key);

    EXPECT_STRNE(section, "");

}



TEST_F(ExifTagsTest_1327, DefaultCount_ValidExifKey_ReturnsNonZeroValue_1327) {

    Exiv2::ExifKey key("Exif.Image.Artist");

    uint16_t count = exifTags.defaultCount(key);

    EXPECT_GE(count, 0);

}



// Assuming taglist to std::ostream requires valid groupName

TEST_F(ExifTagsTest_1327, Taglist_ValidGroupName_OutputsNonEmptyString_1327) {

    std::ostringstream os;

    exifTags.taglist(os, "IFD0");

    EXPECT_FALSE(os.str().empty());

}



TEST_F(ExifTagsTest_1327, Taglist_InvalidGroupName_OutputsEmptyString_1327) {

    std::ostringstream os;

    exifTags.taglist(os, "INVALID_GROUP");

    EXPECT_TRUE(os.str().empty());

}

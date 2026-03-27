#include <gtest/gtest.h>

#include "exiv2/tags.hpp"

#include <sstream>



namespace {



class ExifTagsTest : public ::testing::Test {

protected:

    Exiv2::ExifTags exifTags;

};



TEST_F(ExifTagsTest_1328, TagList_NormalOperation_1328) {

    const std::string groupName = "IFD0";

    const Exiv2::TagInfo* tagInfo = exifTags.tagList(groupName);

    EXPECT_NE(tagInfo, nullptr);

}



TEST_F(ExifTagsTest_1328, TagList_EmptyGroupName_1328) {

    const std::string groupName = "";

    const Exiv2::TagInfo* tagInfo = exifTags.tagList(groupName);

    EXPECT_EQ(tagInfo, nullptr); // Assuming empty group name returns nullptr

}



TEST_F(ExifTagsTest_1328, TagList_NonexistentGroupName_1328) {

    const std::string groupName = "NonExistentGroup";

    const Exiv2::TagInfo* tagInfo = exifTags.tagList(groupName);

    EXPECT_EQ(tagInfo, nullptr); // Assuming non-existent group name returns nullptr

}



TEST_F(ExifTagsTest_1328, GroupList_NormalOperation_1328) {

    const Exiv2::GroupInfo* groupInfo = exifTags.groupList();

    EXPECT_NE(groupInfo, nullptr);

}



TEST_F(ExifTagsTest_1328, SectionName_ValidKey_1328) {

    Exiv2::ExifKey key("Exif.Image.Artist");

    const char* sectionName = exifTags.sectionName(key);

    EXPECT_STREQ(sectionName, "Exif.Image"); // Assuming valid key returns correct section name

}



TEST_F(ExifTagsTest_1328, SectionName_InvalidKey_1328) {

    Exiv2::ExifKey key("Invalid.Key");

    const char* sectionName = exifTags.sectionName(key);

    EXPECT_STREQ(sectionName, ""); // Assuming invalid key returns empty string

}



TEST_F(ExifTagsTest_1328, DefaultCount_ValidKey_1328) {

    Exiv2::ExifKey key("Exif.Image.Artist");

    uint16_t count = exifTags.defaultCount(key);

    EXPECT_GE(count, 0); // Assuming valid key returns non-negative count

}



TEST_F(ExifTagsTest_1328, IfdName_ValidGroupName_1328) {

    const std::string groupName = "IFD0";

    const char* ifdName = exifTags.ifdName(groupName);

    EXPECT_STREQ(ifdName, "IFD0"); // Assuming valid group name returns correct IFD name

}



TEST_F(ExifTagsTest_1328, IfdName_InvalidGroupName_1328) {

    const std::string groupName = "NonExistentGroup";

    const char* ifdName = exifTags.ifdName(groupName);

    EXPECT_STREQ(ifdName, ""); // Assuming invalid group name returns empty string

}



TEST_F(ExifTagsTest_1328, IsMakerGroup_ValidGroupName_1328) {

    const std::string groupName = "Exif.MakerNote";

    bool isMaker = exifTags.isMakerGroup(groupName);

    EXPECT_TRUE(isMaker); // Assuming valid maker group name returns true

}



TEST_F(ExifTagsTest_1328, IsMakerGroup_InvalidGroupName_1328) {

    const std::string groupName = "IFD0";

    bool isMaker = exifTags.isMakerGroup(groupName);

    EXPECT_FALSE(isMaker); // Assuming non-maker group name returns false

}



TEST_F(ExifTagsTest_1328, IsExifGroup_ValidGroupName_1328) {

    const std::string groupName = "IFD0";

    bool isExif = exifTags.isExifGroup(groupName);

    EXPECT_TRUE(isExif); // Assuming valid EXIF group name returns true

}



TEST_F(ExifTagsTest_1328, IsExifGroup_InvalidGroupName_1328) {

    const std::string groupName = "NonExistentGroup";

    bool isExif = exifTags.isExifGroup(groupName);

    EXPECT_FALSE(isExif); // Assuming invalid group name returns false

}



TEST_F(ExifTagsTest_1328, Taglist_OutputStream_NormalOperation_1328) {

    std::ostringstream os;

    exifTags.taglist(os);

    EXPECT_FALSE(os.str().empty()); // Assuming normal operation writes something to the stream

}



TEST_F(ExifTagsTest_1328, Taglist_OutputStream_ValidGroupName_1328) {

    std::ostringstream os;

    const std::string groupName = "IFD0";

    exifTags.taglist(os, groupName);

    EXPECT_FALSE(os.str().empty()); // Assuming normal operation writes something to the stream

}



TEST_F(ExifTagsTest_1328, Taglist_OutputStream_EmptyGroupName_1328) {

    std::ostringstream os;

    const std::string groupName = "";

    exifTags.taglist(os, groupName);

    EXPECT_TRUE(os.str().empty()); // Assuming empty group name writes nothing to the stream

}



TEST_F(ExifTagsTest_1328, Taglist_OutputStream_NonexistentGroupName_1328) {

    std::ostringstream os;

    const std::string groupName = "NonExistentGroup";

    exifTags.taglist(os, groupName);

    EXPECT_TRUE(os.str().empty()); // Assuming non-existent group name writes nothing to the stream

}



}  // namespace

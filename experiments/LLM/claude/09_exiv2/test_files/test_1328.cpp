#include <gtest/gtest.h>
#include <sstream>
#include <string>

#include <exiv2/tags.hpp>
#include <exiv2/exif.hpp>

class ExifTagsTest_1328 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that groupList returns a non-null pointer
TEST_F(ExifTagsTest_1328, GroupListReturnsNonNull_1328) {
    const Exiv2::GroupInfo* groups = Exiv2::ExifTags::groupList();
    ASSERT_NE(groups, nullptr);
}

// Test that groupList contains at least one entry
TEST_F(ExifTagsTest_1328, GroupListHasEntries_1328) {
    const Exiv2::GroupInfo* groups = Exiv2::ExifTags::groupList();
    ASSERT_NE(groups, nullptr);
    // The first group should have a valid group name
    EXPECT_NE(groups[0].groupName_, nullptr);
}

// Test tagList with a known valid group name "Image"
TEST_F(ExifTagsTest_1328, TagListForImageGroupReturnsNonNull_1328) {
    const Exiv2::TagInfo* tags = Exiv2::ExifTags::tagList("Image");
    ASSERT_NE(tags, nullptr);
}

// Test tagList with a known valid group name "Photo"
TEST_F(ExifTagsTest_1328, TagListForPhotoGroupReturnsNonNull_1328) {
    const Exiv2::TagInfo* tags = Exiv2::ExifTags::tagList("Photo");
    ASSERT_NE(tags, nullptr);
}

// Test tagList with a known valid group name "GPSInfo"
TEST_F(ExifTagsTest_1328, TagListForGPSInfoGroupReturnsNonNull_1328) {
    const Exiv2::TagInfo* tags = Exiv2::ExifTags::tagList("GPSInfo");
    ASSERT_NE(tags, nullptr);
}

// Test tagList with a known valid group name "Iop"
TEST_F(ExifTagsTest_1328, TagListForIopGroupReturnsNonNull_1328) {
    const Exiv2::TagInfo* tags = Exiv2::ExifTags::tagList("Iop");
    ASSERT_NE(tags, nullptr);
}

// Test tagList with an invalid/unknown group name returns null
TEST_F(ExifTagsTest_1328, TagListForUnknownGroupReturnsNull_1328) {
    const Exiv2::TagInfo* tags = Exiv2::ExifTags::tagList("NonExistentGroupXYZ123");
    EXPECT_EQ(tags, nullptr);
}

// Test tagList with empty group name
TEST_F(ExifTagsTest_1328, TagListForEmptyGroupName_1328) {
    const Exiv2::TagInfo* tags = Exiv2::ExifTags::tagList("");
    EXPECT_EQ(tags, nullptr);
}

// Test taglist (ostream version) produces output
TEST_F(ExifTagsTest_1328, TaglistToStreamProducesOutput_1328) {
    std::ostringstream os;
    Exiv2::ExifTags::taglist(os);
    std::string output = os.str();
    EXPECT_FALSE(output.empty());
}

// Test taglist with group name to stream produces output for known group
TEST_F(ExifTagsTest_1328, TaglistWithGroupNameToStreamProducesOutput_1328) {
    std::ostringstream os;
    Exiv2::ExifTags::taglist(os, "Image");
    std::string output = os.str();
    EXPECT_FALSE(output.empty());
}

// Test taglist with group name "Photo" to stream
TEST_F(ExifTagsTest_1328, TaglistWithPhotoGroupToStream_1328) {
    std::ostringstream os;
    Exiv2::ExifTags::taglist(os, "Photo");
    std::string output = os.str();
    EXPECT_FALSE(output.empty());
}

// Test ifdName for a known group
TEST_F(ExifTagsTest_1328, IfdNameForImageGroup_1328) {
    const char* name = Exiv2::ExifTags::ifdName("Image");
    ASSERT_NE(name, nullptr);
    EXPECT_STRNE(name, "");
}

// Test ifdName for unknown group
TEST_F(ExifTagsTest_1328, IfdNameForUnknownGroup_1328) {
    const char* name = Exiv2::ExifTags::ifdName("NonExistentGroupXYZ");
    ASSERT_NE(name, nullptr);
}

// Test isExifGroup for known EXIF group
TEST_F(ExifTagsTest_1328, IsExifGroupForImageGroup_1328) {
    bool result = Exiv2::ExifTags::isExifGroup("Image");
    EXPECT_TRUE(result);
}

// Test isExifGroup for Photo group
TEST_F(ExifTagsTest_1328, IsExifGroupForPhotoGroup_1328) {
    bool result = Exiv2::ExifTags::isExifGroup("Photo");
    EXPECT_TRUE(result);
}

// Test isExifGroup for unknown group
TEST_F(ExifTagsTest_1328, IsExifGroupForUnknownGroup_1328) {
    bool result = Exiv2::ExifTags::isExifGroup("NonExistentGroupXYZ");
    EXPECT_FALSE(result);
}

// Test isMakerGroup for a known non-maker group
TEST_F(ExifTagsTest_1328, IsMakerGroupForImageGroup_1328) {
    bool result = Exiv2::ExifTags::isMakerGroup("Image");
    EXPECT_FALSE(result);
}

// Test isMakerGroup for unknown group
TEST_F(ExifTagsTest_1328, IsMakerGroupForUnknownGroup_1328) {
    bool result = Exiv2::ExifTags::isMakerGroup("NonExistentGroupXYZ");
    EXPECT_FALSE(result);
}

// Test sectionName with a valid ExifKey
TEST_F(ExifTagsTest_1328, SectionNameForValidKey_1328) {
    Exiv2::ExifKey key("Exif.Image.ImageWidth");
    const char* section = Exiv2::ExifTags::sectionName(key);
    ASSERT_NE(section, nullptr);
    EXPECT_STRNE(section, "");
}

// Test defaultCount with a valid ExifKey
TEST_F(ExifTagsTest_1328, DefaultCountForValidKey_1328) {
    Exiv2::ExifKey key("Exif.Image.ImageWidth");
    uint16_t count = Exiv2::ExifTags::defaultCount(key);
    // ImageWidth typically has a default count of 1
    EXPECT_GE(count, 0);
}

// Test sectionName with GPSInfo key
TEST_F(ExifTagsTest_1328, SectionNameForGPSKey_1328) {
    Exiv2::ExifKey key("Exif.GPSInfo.GPSLatitude");
    const char* section = Exiv2::ExifTags::sectionName(key);
    ASSERT_NE(section, nullptr);
}

// Test isExifGroup for empty string
TEST_F(ExifTagsTest_1328, IsExifGroupForEmptyString_1328) {
    bool result = Exiv2::ExifTags::isExifGroup("");
    EXPECT_FALSE(result);
}

// Test isMakerGroup for empty string
TEST_F(ExifTagsTest_1328, IsMakerGroupForEmptyString_1328) {
    bool result = Exiv2::ExifTags::isMakerGroup("");
    EXPECT_FALSE(result);
}

// Test that the first tag in "Image" tag list has valid fields
TEST_F(ExifTagsTest_1328, ImageTagListFirstEntryHasValidTag_1328) {
    const Exiv2::TagInfo* tags = Exiv2::ExifTags::tagList("Image");
    ASSERT_NE(tags, nullptr);
    // The first entry should have a tag value >= 0
    EXPECT_GE(tags[0].tag_, 0);
}

// Test taglist stream output for GPSInfo group
TEST_F(ExifTagsTest_1328, TaglistWithGPSInfoGroupToStream_1328) {
    std::ostringstream os;
    Exiv2::ExifTags::taglist(os, "GPSInfo");
    std::string output = os.str();
    EXPECT_FALSE(output.empty());
}

// Test ifdName for GPSInfo
TEST_F(ExifTagsTest_1328, IfdNameForGPSInfoGroup_1328) {
    const char* name = Exiv2::ExifTags::ifdName("GPSInfo");
    ASSERT_NE(name, nullptr);
    EXPECT_STRNE(name, "");
}

// Test ifdName for empty string
TEST_F(ExifTagsTest_1328, IfdNameForEmptyString_1328) {
    const char* name = Exiv2::ExifTags::ifdName("");
    ASSERT_NE(name, nullptr);
}

// Test multiple calls to groupList return consistent results
TEST_F(ExifTagsTest_1328, GroupListConsistentAcrossCalls_1328) {
    const Exiv2::GroupInfo* groups1 = Exiv2::ExifTags::groupList();
    const Exiv2::GroupInfo* groups2 = Exiv2::ExifTags::groupList();
    EXPECT_EQ(groups1, groups2);
}

// Test multiple calls to tagList return consistent results
TEST_F(ExifTagsTest_1328, TagListConsistentAcrossCalls_1328) {
    const Exiv2::TagInfo* tags1 = Exiv2::ExifTags::tagList("Image");
    const Exiv2::TagInfo* tags2 = Exiv2::ExifTags::tagList("Image");
    EXPECT_EQ(tags1, tags2);
}

// Test isExifGroup for GPSInfo
TEST_F(ExifTagsTest_1328, IsExifGroupForGPSInfo_1328) {
    bool result = Exiv2::ExifTags::isExifGroup("GPSInfo");
    EXPECT_TRUE(result);
}

// Test isExifGroup for Iop
TEST_F(ExifTagsTest_1328, IsExifGroupForIop_1328) {
    bool result = Exiv2::ExifTags::isExifGroup("Iop");
    EXPECT_TRUE(result);
}

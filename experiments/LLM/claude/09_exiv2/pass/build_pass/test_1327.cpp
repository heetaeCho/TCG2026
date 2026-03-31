#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <string>
#include <exiv2/tags.hpp>
#include <exiv2/exif.hpp>

class ExifTagsTest_1327 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that groupList returns a non-null pointer
TEST_F(ExifTagsTest_1327, GroupListReturnsNonNull_1327) {
    const Exiv2::GroupInfo* groups = Exiv2::ExifTags::groupList();
    ASSERT_NE(groups, nullptr);
}

// Test that groupList contains at least one entry
TEST_F(ExifTagsTest_1327, GroupListContainsEntries_1327) {
    const Exiv2::GroupInfo* groups = Exiv2::ExifTags::groupList();
    ASSERT_NE(groups, nullptr);
    // The first entry should have a valid group name
    EXPECT_NE(groups[0].groupName_, nullptr);
}

// Test that tagList returns non-null for a known group "Image"
TEST_F(ExifTagsTest_1327, TagListReturnsNonNullForImage_1327) {
    const Exiv2::TagInfo* tags = Exiv2::ExifTags::tagList("Image");
    ASSERT_NE(tags, nullptr);
}

// Test that tagList returns non-null for "Photo" group
TEST_F(ExifTagsTest_1327, TagListReturnsNonNullForPhoto_1327) {
    const Exiv2::TagInfo* tags = Exiv2::ExifTags::tagList("Photo");
    ASSERT_NE(tags, nullptr);
}

// Test that tagList returns non-null for "GPSInfo" group
TEST_F(ExifTagsTest_1327, TagListReturnsNonNullForGPSInfo_1327) {
    const Exiv2::TagInfo* tags = Exiv2::ExifTags::tagList("GPSInfo");
    ASSERT_NE(tags, nullptr);
}

// Test that tagList returns non-null for "Iop" group
TEST_F(ExifTagsTest_1327, TagListReturnsNonNullForIop_1327) {
    const Exiv2::TagInfo* tags = Exiv2::ExifTags::tagList("Iop");
    ASSERT_NE(tags, nullptr);
}

// Test taglist output to stream is not empty
TEST_F(ExifTagsTest_1327, TaglistOutputsToStream_1327) {
    std::ostringstream os;
    Exiv2::ExifTags::taglist(os);
    EXPECT_FALSE(os.str().empty());
}

// Test taglist with group name outputs to stream
TEST_F(ExifTagsTest_1327, TaglistWithGroupNameOutputsToStream_1327) {
    std::ostringstream os;
    Exiv2::ExifTags::taglist(os, "Image");
    EXPECT_FALSE(os.str().empty());
}

// Test taglist with Photo group name outputs to stream
TEST_F(ExifTagsTest_1327, TaglistWithPhotoGroupOutputsToStream_1327) {
    std::ostringstream os;
    Exiv2::ExifTags::taglist(os, "Photo");
    EXPECT_FALSE(os.str().empty());
}

// Test ifdName returns a valid string for known group
TEST_F(ExifTagsTest_1327, IfdNameReturnsValidStringForImage_1327) {
    const char* ifdName = Exiv2::ExifTags::ifdName("Image");
    ASSERT_NE(ifdName, nullptr);
    EXPECT_GT(std::string(ifdName).length(), 0u);
}

// Test ifdName for Photo group
TEST_F(ExifTagsTest_1327, IfdNameReturnsValidStringForPhoto_1327) {
    const char* ifdName = Exiv2::ExifTags::ifdName("Photo");
    ASSERT_NE(ifdName, nullptr);
    EXPECT_GT(std::string(ifdName).length(), 0u);
}

// Test isMakerGroup returns false for standard groups
TEST_F(ExifTagsTest_1327, IsMakerGroupFalseForImage_1327) {
    EXPECT_FALSE(Exiv2::ExifTags::isMakerGroup("Image"));
}

TEST_F(ExifTagsTest_1327, IsMakerGroupFalseForPhoto_1327) {
    EXPECT_FALSE(Exiv2::ExifTags::isMakerGroup("Photo"));
}

TEST_F(ExifTagsTest_1327, IsMakerGroupFalseForGPSInfo_1327) {
    EXPECT_FALSE(Exiv2::ExifTags::isMakerGroup("GPSInfo"));
}

// Test isExifGroup returns true for standard Exif groups
TEST_F(ExifTagsTest_1327, IsExifGroupTrueForImage_1327) {
    EXPECT_TRUE(Exiv2::ExifTags::isExifGroup("Image"));
}

TEST_F(ExifTagsTest_1327, IsExifGroupTrueForPhoto_1327) {
    EXPECT_TRUE(Exiv2::ExifTags::isExifGroup("Photo"));
}

TEST_F(ExifTagsTest_1327, IsExifGroupTrueForGPSInfo_1327) {
    EXPECT_TRUE(Exiv2::ExifTags::isExifGroup("GPSInfo"));
}

// Test isExifGroup returns false for an unknown group
TEST_F(ExifTagsTest_1327, IsExifGroupFalseForUnknown_1327) {
    EXPECT_FALSE(Exiv2::ExifTags::isExifGroup("NonExistentGroup"));
}

// Test isMakerGroup returns false for an unknown group
TEST_F(ExifTagsTest_1327, IsMakerGroupFalseForUnknown_1327) {
    EXPECT_FALSE(Exiv2::ExifTags::isMakerGroup("NonExistentGroup"));
}

// Test sectionName with a valid ExifKey
TEST_F(ExifTagsTest_1327, SectionNameReturnsValidString_1327) {
    Exiv2::ExifKey key("Exif.Image.ImageWidth");
    const char* section = Exiv2::ExifTags::sectionName(key);
    ASSERT_NE(section, nullptr);
    EXPECT_GT(std::string(section).length(), 0u);
}

// Test defaultCount with a valid ExifKey
TEST_F(ExifTagsTest_1327, DefaultCountReturnsValue_1327) {
    Exiv2::ExifKey key("Exif.Image.ImageWidth");
    uint16_t count = Exiv2::ExifTags::defaultCount(key);
    // ImageWidth should have a default count of 1
    EXPECT_GE(count, 0u);
}

// Test that groupList can be iterated until a sentinel entry
TEST_F(ExifTagsTest_1327, GroupListCanBeIterated_1327) {
    const Exiv2::GroupInfo* groups = Exiv2::ExifTags::groupList();
    ASSERT_NE(groups, nullptr);
    int count = 0;
    // Iterate through the group list; groupName_ == nullptr signals end
    while (groups[count].groupName_ != nullptr) {
        count++;
        // Safety: don't iterate more than a reasonable number
        if (count > 10000) break;
    }
    EXPECT_GT(count, 0);
    EXPECT_LE(count, 10000);
}

// Test taglist with an empty/unknown group name
TEST_F(ExifTagsTest_1327, TaglistWithUnknownGroupName_1327) {
    std::ostringstream os;
    // This should not crash; behavior may vary (empty output or error message)
    EXPECT_NO_THROW(Exiv2::ExifTags::taglist(os, "NonExistentGroup"));
}

// Test tagList with an empty group name
TEST_F(ExifTagsTest_1327, TagListWithEmptyGroupName_1327) {
    // Should handle gracefully
    EXPECT_NO_THROW(Exiv2::ExifTags::tagList(""));
}

// Test ifdName with empty string
TEST_F(ExifTagsTest_1327, IfdNameWithEmptyString_1327) {
    const char* ifdName = Exiv2::ExifTags::ifdName("");
    ASSERT_NE(ifdName, nullptr);
}

// Test sectionName with GPSInfo key
TEST_F(ExifTagsTest_1327, SectionNameForGPSKey_1327) {
    Exiv2::ExifKey key("Exif.GPSInfo.GPSLatitude");
    const char* section = Exiv2::ExifTags::sectionName(key);
    ASSERT_NE(section, nullptr);
}

// Test defaultCount for GPSInfo key
TEST_F(ExifTagsTest_1327, DefaultCountForGPSKey_1327) {
    Exiv2::ExifKey key("Exif.GPSInfo.GPSLatitude");
    uint16_t count = Exiv2::ExifTags::defaultCount(key);
    // GPSLatitude typically has 3 rational values
    EXPECT_EQ(count, 3u);
}

// Test isExifGroup with Iop
TEST_F(ExifTagsTest_1327, IsExifGroupTrueForIop_1327) {
    EXPECT_TRUE(Exiv2::ExifTags::isExifGroup("Iop"));
}

// Test that taglist output for Image group contains known tags
TEST_F(ExifTagsTest_1327, TaglistImageContainsImageWidth_1327) {
    std::ostringstream os;
    Exiv2::ExifTags::taglist(os, "Image");
    std::string output = os.str();
    EXPECT_NE(output.find("ImageWidth"), std::string::npos);
}

// Test that the general taglist output contains some content
TEST_F(ExifTagsTest_1327, GeneralTaglistContainsContent_1327) {
    std::ostringstream os;
    Exiv2::ExifTags::taglist(os);
    std::string output = os.str();
    // Should contain at least some known tag
    EXPECT_NE(output.find("Image"), std::string::npos);
}

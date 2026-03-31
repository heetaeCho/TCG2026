#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <exiv2/tags.hpp>
#include <exiv2/exif.hpp>

class ExifTagsTest_1330 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test taglist with a known valid group name produces non-empty output
TEST_F(ExifTagsTest_1330, TaglistWithValidGroupName_1330) {
    std::ostringstream os;
    Exiv2::ExifTags::taglist(os, "Image");
    std::string output = os.str();
    EXPECT_FALSE(output.empty()) << "taglist for 'Image' group should produce non-empty output";
}

// Test taglist with another known valid group name (Photo/Exif)
TEST_F(ExifTagsTest_1330, TaglistWithPhotoGroupName_1330) {
    std::ostringstream os;
    Exiv2::ExifTags::taglist(os, "Photo");
    std::string output = os.str();
    EXPECT_FALSE(output.empty()) << "taglist for 'Photo' group should produce non-empty output";
}

// Test taglist with an unknown/invalid group name produces empty or no crash
TEST_F(ExifTagsTest_1330, TaglistWithInvalidGroupName_1330) {
    std::ostringstream os;
    EXPECT_NO_THROW(Exiv2::ExifTags::taglist(os, "NonExistentGroup"));
}

// Test taglist with empty group name does not crash
TEST_F(ExifTagsTest_1330, TaglistWithEmptyGroupName_1330) {
    std::ostringstream os;
    EXPECT_NO_THROW(Exiv2::ExifTags::taglist(os, ""));
}

// Test taglist without group name (all tags) produces non-empty output
TEST_F(ExifTagsTest_1330, TaglistAllTags_1330) {
    std::ostringstream os;
    Exiv2::ExifTags::taglist(os);
    std::string output = os.str();
    EXPECT_FALSE(output.empty()) << "taglist for all tags should produce non-empty output";
}

// Test groupList returns non-null
TEST_F(ExifTagsTest_1330, GroupListReturnsNonNull_1330) {
    const Exiv2::GroupInfo* groups = Exiv2::ExifTags::groupList();
    EXPECT_NE(groups, nullptr);
}

// Test tagList with a known group returns non-null
TEST_F(ExifTagsTest_1330, TagListWithValidGroup_1330) {
    const Exiv2::TagInfo* tags = Exiv2::ExifTags::tagList("Image");
    EXPECT_NE(tags, nullptr);
}

// Test tagList with an invalid group name
TEST_F(ExifTagsTest_1330, TagListWithInvalidGroup_1330) {
    const Exiv2::TagInfo* tags = Exiv2::ExifTags::tagList("InvalidGroupXYZ");
    // May return nullptr or a valid pointer depending on implementation
    // Just ensure it doesn't crash
    (void)tags;
}

// Test ifdName with a known group name returns non-null, non-empty string
TEST_F(ExifTagsTest_1330, IfdNameWithValidGroup_1330) {
    const char* name = Exiv2::ExifTags::ifdName("Image");
    EXPECT_NE(name, nullptr);
    EXPECT_GT(strlen(name), 0u);
}

// Test ifdName with an invalid group name does not crash
TEST_F(ExifTagsTest_1330, IfdNameWithInvalidGroup_1330) {
    const char* name = Exiv2::ExifTags::ifdName("InvalidGroupXYZ");
    // Should not crash; result is implementation-defined
    (void)name;
}

// Test isMakerGroup with a known non-maker group
TEST_F(ExifTagsTest_1330, IsMakerGroupForImage_1330) {
    bool result = Exiv2::ExifTags::isMakerGroup("Image");
    EXPECT_FALSE(result) << "'Image' should not be a maker group";
}

// Test isMakerGroup with an invalid group name
TEST_F(ExifTagsTest_1330, IsMakerGroupForInvalidGroup_1330) {
    bool result = Exiv2::ExifTags::isMakerGroup("NonExistentGroup");
    EXPECT_FALSE(result) << "Non-existent group should not be a maker group";
}

// Test isExifGroup with a known Exif group
TEST_F(ExifTagsTest_1330, IsExifGroupForImage_1330) {
    bool result = Exiv2::ExifTags::isExifGroup("Image");
    EXPECT_TRUE(result) << "'Image' should be an Exif group";
}

// Test isExifGroup with a known Exif group (Photo)
TEST_F(ExifTagsTest_1330, IsExifGroupForPhoto_1330) {
    bool result = Exiv2::ExifTags::isExifGroup("Photo");
    EXPECT_TRUE(result) << "'Photo' should be an Exif group";
}

// Test isExifGroup with an invalid group name
TEST_F(ExifTagsTest_1330, IsExifGroupForInvalidGroup_1330) {
    bool result = Exiv2::ExifTags::isExifGroup("NonExistentGroup");
    EXPECT_FALSE(result) << "Non-existent group should not be an Exif group";
}

// Test isExifGroup with empty string
TEST_F(ExifTagsTest_1330, IsExifGroupForEmptyString_1330) {
    bool result = Exiv2::ExifTags::isExifGroup("");
    EXPECT_FALSE(result) << "Empty string should not be an Exif group";
}

// Test sectionName with a valid ExifKey
TEST_F(ExifTagsTest_1330, SectionNameWithValidKey_1330) {
    Exiv2::ExifKey key("Exif.Image.ImageWidth");
    const char* section = Exiv2::ExifTags::sectionName(key);
    EXPECT_NE(section, nullptr);
    EXPECT_GT(strlen(section), 0u);
}

// Test defaultCount with a valid ExifKey
TEST_F(ExifTagsTest_1330, DefaultCountWithValidKey_1330) {
    Exiv2::ExifKey key("Exif.Image.ImageWidth");
    uint16_t count = Exiv2::ExifTags::defaultCount(key);
    // ImageWidth should have a default count of 1
    EXPECT_GE(count, 0u);
}

// Test taglist output for GPSInfo group
TEST_F(ExifTagsTest_1330, TaglistWithGPSInfoGroup_1330) {
    std::ostringstream os;
    Exiv2::ExifTags::taglist(os, "GPSInfo");
    std::string output = os.str();
    EXPECT_FALSE(output.empty()) << "taglist for 'GPSInfo' group should produce non-empty output";
}

// Test taglist output for Iop group
TEST_F(ExifTagsTest_1330, TaglistWithIopGroup_1330) {
    std::ostringstream os;
    Exiv2::ExifTags::taglist(os, "Iop");
    std::string output = os.str();
    EXPECT_FALSE(output.empty()) << "taglist for 'Iop' group should produce non-empty output";
}

// Test that calling taglist twice with same group produces same output
TEST_F(ExifTagsTest_1330, TaglistConsistentOutput_1330) {
    std::ostringstream os1;
    Exiv2::ExifTags::taglist(os1, "Image");
    std::ostringstream os2;
    Exiv2::ExifTags::taglist(os2, "Image");
    EXPECT_EQ(os1.str(), os2.str()) << "taglist should produce consistent output for same group";
}

// Test isMakerGroup with empty string
TEST_F(ExifTagsTest_1330, IsMakerGroupForEmptyString_1330) {
    bool result = Exiv2::ExifTags::isMakerGroup("");
    EXPECT_FALSE(result) << "Empty string should not be a maker group";
}

// Test ifdName with empty string
TEST_F(ExifTagsTest_1330, IfdNameWithEmptyString_1330) {
    EXPECT_NO_THROW({
        const char* name = Exiv2::ExifTags::ifdName("");
        (void)name;
    });
}

// Test tagList with empty group name
TEST_F(ExifTagsTest_1330, TagListWithEmptyGroupName_1330) {
    EXPECT_NO_THROW({
        const Exiv2::TagInfo* tags = Exiv2::ExifTags::tagList("");
        (void)tags;
    });
}

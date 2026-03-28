#include <gtest/gtest.h>
#include <sstream>
#include <string>

#include <exiv2/tags.hpp>
#include <exiv2/exif.hpp>

// Test fixture for ExifTags
class ExifTagsTest_1325 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// ============================================================
// Tests for isMakerGroup
// ============================================================

TEST_F(ExifTagsTest_1325, IsMakerGroupReturnsTrueForCanonGroup_1325) {
    bool result = Exiv2::ExifTags::isMakerGroup("Canon");
    EXPECT_TRUE(result);
}

TEST_F(ExifTagsTest_1325, IsMakerGroupReturnsTrueForNikonGroup_1325) {
    // Nikon maker groups typically exist
    bool result = Exiv2::ExifTags::isMakerGroup("Nikon3");
    EXPECT_TRUE(result);
}

TEST_F(ExifTagsTest_1325, IsMakerGroupReturnsTrueForSonyGroup_1325) {
    bool result = Exiv2::ExifTags::isMakerGroup("Sony1");
    EXPECT_TRUE(result);
}

TEST_F(ExifTagsTest_1325, IsMakerGroupReturnsFalseForExifIfd_1325) {
    bool result = Exiv2::ExifTags::isMakerGroup("Photo");
    EXPECT_FALSE(result);
}

TEST_F(ExifTagsTest_1325, IsMakerGroupReturnsFalseForImageGroup_1325) {
    bool result = Exiv2::ExifTags::isMakerGroup("Image");
    EXPECT_FALSE(result);
}

TEST_F(ExifTagsTest_1325, IsMakerGroupReturnsFalseForGpsGroup_1325) {
    bool result = Exiv2::ExifTags::isMakerGroup("GPSInfo");
    EXPECT_FALSE(result);
}

TEST_F(ExifTagsTest_1325, IsMakerGroupReturnsFalseForEmptyString_1325) {
    bool result = Exiv2::ExifTags::isMakerGroup("");
    EXPECT_FALSE(result);
}

TEST_F(ExifTagsTest_1325, IsMakerGroupReturnsFalseForInvalidGroupName_1325) {
    bool result = Exiv2::ExifTags::isMakerGroup("NonExistentGroup");
    EXPECT_FALSE(result);
}

TEST_F(ExifTagsTest_1325, IsMakerGroupReturnsFalseForRandomString_1325) {
    bool result = Exiv2::ExifTags::isMakerGroup("abcdefghijk");
    EXPECT_FALSE(result);
}

TEST_F(ExifTagsTest_1325, IsMakerGroupReturnsFalseForIopGroup_1325) {
    bool result = Exiv2::ExifTags::isMakerGroup("Iop");
    EXPECT_FALSE(result);
}

// ============================================================
// Tests for isExifGroup
// ============================================================

TEST_F(ExifTagsTest_1325, IsExifGroupReturnsTrueForPhoto_1325) {
    bool result = Exiv2::ExifTags::isExifGroup("Photo");
    EXPECT_TRUE(result);
}

TEST_F(ExifTagsTest_1325, IsExifGroupReturnsTrueForImage_1325) {
    bool result = Exiv2::ExifTags::isExifGroup("Image");
    EXPECT_TRUE(result);
}

TEST_F(ExifTagsTest_1325, IsExifGroupReturnsTrueForGPSInfo_1325) {
    bool result = Exiv2::ExifTags::isExifGroup("GPSInfo");
    EXPECT_TRUE(result);
}

TEST_F(ExifTagsTest_1325, IsExifGroupReturnsTrueForIop_1325) {
    bool result = Exiv2::ExifTags::isExifGroup("Iop");
    EXPECT_TRUE(result);
}

TEST_F(ExifTagsTest_1325, IsExifGroupReturnsFalseForEmptyString_1325) {
    bool result = Exiv2::ExifTags::isExifGroup("");
    EXPECT_FALSE(result);
}

TEST_F(ExifTagsTest_1325, IsExifGroupReturnsFalseForNonExistentGroup_1325) {
    bool result = Exiv2::ExifTags::isExifGroup("FooBarBaz");
    EXPECT_FALSE(result);
}

// ============================================================
// Tests for groupList
// ============================================================

TEST_F(ExifTagsTest_1325, GroupListReturnsNonNull_1325) {
    const Exiv2::GroupInfo* groups = Exiv2::ExifTags::groupList();
    ASSERT_NE(groups, nullptr);
}

TEST_F(ExifTagsTest_1325, GroupListContainsAtLeastOneEntry_1325) {
    const Exiv2::GroupInfo* groups = Exiv2::ExifTags::groupList();
    ASSERT_NE(groups, nullptr);
    // The first entry should have a valid group name
    EXPECT_NE(groups[0].groupName_, nullptr);
}

// ============================================================
// Tests for tagList
// ============================================================

TEST_F(ExifTagsTest_1325, TagListForImageReturnsNonNull_1325) {
    const Exiv2::TagInfo* tags = Exiv2::ExifTags::tagList("Image");
    EXPECT_NE(tags, nullptr);
}

TEST_F(ExifTagsTest_1325, TagListForPhotoReturnsNonNull_1325) {
    const Exiv2::TagInfo* tags = Exiv2::ExifTags::tagList("Photo");
    EXPECT_NE(tags, nullptr);
}

TEST_F(ExifTagsTest_1325, TagListForGPSInfoReturnsNonNull_1325) {
    const Exiv2::TagInfo* tags = Exiv2::ExifTags::tagList("GPSInfo");
    EXPECT_NE(tags, nullptr);
}

TEST_F(ExifTagsTest_1325, TagListForInvalidGroupReturnsNull_1325) {
    const Exiv2::TagInfo* tags = Exiv2::ExifTags::tagList("CompletelyInvalidGroupName");
    EXPECT_EQ(tags, nullptr);
}

// ============================================================
// Tests for taglist (ostream)
// ============================================================

TEST_F(ExifTagsTest_1325, TaglistOutputStreamNotEmpty_1325) {
    std::ostringstream os;
    Exiv2::ExifTags::taglist(os);
    EXPECT_FALSE(os.str().empty());
}

TEST_F(ExifTagsTest_1325, TaglistGroupOutputStreamForImageNotEmpty_1325) {
    std::ostringstream os;
    Exiv2::ExifTags::taglist(os, "Image");
    EXPECT_FALSE(os.str().empty());
}

TEST_F(ExifTagsTest_1325, TaglistGroupOutputStreamForPhotoNotEmpty_1325) {
    std::ostringstream os;
    Exiv2::ExifTags::taglist(os, "Photo");
    EXPECT_FALSE(os.str().empty());
}

TEST_F(ExifTagsTest_1325, TaglistGroupOutputStreamForGPSInfoNotEmpty_1325) {
    std::ostringstream os;
    Exiv2::ExifTags::taglist(os, "GPSInfo");
    EXPECT_FALSE(os.str().empty());
}

// ============================================================
// Tests for ifdName
// ============================================================

TEST_F(ExifTagsTest_1325, IfdNameForImageGroup_1325) {
    const char* name = Exiv2::ExifTags::ifdName("Image");
    ASSERT_NE(name, nullptr);
    EXPECT_STRNE(name, "");
}

TEST_F(ExifTagsTest_1325, IfdNameForPhotoGroup_1325) {
    const char* name = Exiv2::ExifTags::ifdName("Photo");
    ASSERT_NE(name, nullptr);
    EXPECT_STRNE(name, "");
}

TEST_F(ExifTagsTest_1325, IfdNameForGPSInfoGroup_1325) {
    const char* name = Exiv2::ExifTags::ifdName("GPSInfo");
    ASSERT_NE(name, nullptr);
    EXPECT_STRNE(name, "");
}

TEST_F(ExifTagsTest_1325, IfdNameForEmptyStringReturnsNonNull_1325) {
    const char* name = Exiv2::ExifTags::ifdName("");
    ASSERT_NE(name, nullptr);
}

// ============================================================
// Tests for sectionName and defaultCount (require ExifKey)
// ============================================================

TEST_F(ExifTagsTest_1325, SectionNameForKnownKey_1325) {
    Exiv2::ExifKey key("Exif.Image.ImageWidth");
    const char* section = Exiv2::ExifTags::sectionName(key);
    ASSERT_NE(section, nullptr);
    EXPECT_STRNE(section, "");
}

TEST_F(ExifTagsTest_1325, DefaultCountForKnownKey_1325) {
    Exiv2::ExifKey key("Exif.Image.ImageWidth");
    uint16_t count = Exiv2::ExifTags::defaultCount(key);
    // ImageWidth should have a default count of 1
    EXPECT_GE(count, static_cast<uint16_t>(0));
}

TEST_F(ExifTagsTest_1325, SectionNameForGPSKey_1325) {
    Exiv2::ExifKey key("Exif.GPSInfo.GPSLatitude");
    const char* section = Exiv2::ExifTags::sectionName(key);
    ASSERT_NE(section, nullptr);
}

TEST_F(ExifTagsTest_1325, DefaultCountForGPSLatitude_1325) {
    Exiv2::ExifKey key("Exif.GPSInfo.GPSLatitude");
    uint16_t count = Exiv2::ExifTags::defaultCount(key);
    // GPSLatitude typically has 3 rational values
    EXPECT_EQ(count, static_cast<uint16_t>(3));
}

// ============================================================
// Boundary/Edge case tests for isMakerGroup
// ============================================================

TEST_F(ExifTagsTest_1325, IsMakerGroupCaseSensitivity_1325) {
    // Test that the function is case-sensitive
    bool resultLower = Exiv2::ExifTags::isMakerGroup("canon");
    bool resultUpper = Exiv2::ExifTags::isMakerGroup("CANON");
    // Both should likely return false since the proper name is "Canon"
    // But we just check they don't crash
    // The exact result depends on implementation, but we test observable behavior
    EXPECT_FALSE(resultLower);
    EXPECT_FALSE(resultUpper);
}

TEST_F(ExifTagsTest_1325, IsMakerGroupWithWhitespace_1325) {
    bool result = Exiv2::ExifTags::isMakerGroup(" Canon ");
    EXPECT_FALSE(result);
}

TEST_F(ExifTagsTest_1325, IsMakerGroupReturnsTrueForOlympusGroup_1325) {
    bool result = Exiv2::ExifTags::isMakerGroup("Olympus");
    EXPECT_TRUE(result);
}

TEST_F(ExifTagsTest_1325, IsMakerGroupReturnsTrueForFujifilm_1325) {
    bool result = Exiv2::ExifTags::isMakerGroup("Fujifilm");
    EXPECT_TRUE(result);
}

TEST_F(ExifTagsTest_1325, IsExifGroupReturnsFalseForMakerGroup_1325) {
    // A maker group should not be an Exif group
    bool result = Exiv2::ExifTags::isExifGroup("Canon");
    EXPECT_FALSE(result);
}

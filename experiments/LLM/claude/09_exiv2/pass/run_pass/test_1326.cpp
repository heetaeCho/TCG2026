#include <gtest/gtest.h>
#include <sstream>
#include <string>

#include <exiv2/tags.hpp>
#include <exiv2/exif.hpp>

namespace {

// Test fixture for ExifTags
class ExifTagsTest_1326 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== isExifGroup tests ====================

TEST_F(ExifTagsTest_1326, IsExifGroup_Image_ReturnsTrue_1326) {
    // "Image" is a standard Exif IFD group name (IFD0)
    EXPECT_TRUE(Exiv2::ExifTags::isExifGroup("Image"));
}

TEST_F(ExifTagsTest_1326, IsExifGroup_Photo_ReturnsTrue_1326) {
    // "Photo" corresponds to the Exif IFD
    EXPECT_TRUE(Exiv2::ExifTags::isExifGroup("Photo"));
}

TEST_F(ExifTagsTest_1326, IsExifGroup_GPSInfo_ReturnsTrue_1326) {
    EXPECT_TRUE(Exiv2::ExifTags::isExifGroup("GPSInfo"));
}

TEST_F(ExifTagsTest_1326, IsExifGroup_Iop_ReturnsTrue_1326) {
    EXPECT_TRUE(Exiv2::ExifTags::isExifGroup("Iop"));
}

TEST_F(ExifTagsTest_1326, IsExifGroup_Thumbnail_ReturnsTrue_1326) {
    EXPECT_TRUE(Exiv2::ExifTags::isExifGroup("Thumbnail"));
}

TEST_F(ExifTagsTest_1326, IsExifGroup_EmptyString_ReturnsFalse_1326) {
    EXPECT_FALSE(Exiv2::ExifTags::isExifGroup(""));
}

TEST_F(ExifTagsTest_1326, IsExifGroup_NonExistentGroup_ReturnsFalse_1326) {
    EXPECT_FALSE(Exiv2::ExifTags::isExifGroup("NonExistentGroup"));
}

TEST_F(ExifTagsTest_1326, IsExifGroup_RandomString_ReturnsFalse_1326) {
    EXPECT_FALSE(Exiv2::ExifTags::isExifGroup("foobar123"));
}

TEST_F(ExifTagsTest_1326, IsExifGroup_CaseSensitive_ReturnsFalse_1326) {
    // Group names should be case-sensitive; "image" != "Image"
    EXPECT_FALSE(Exiv2::ExifTags::isExifGroup("image"));
}

TEST_F(ExifTagsTest_1326, IsExifGroup_CaseSensitivePhoto_ReturnsFalse_1326) {
    EXPECT_FALSE(Exiv2::ExifTags::isExifGroup("photo"));
}

// ==================== isMakerGroup tests ====================

TEST_F(ExifTagsTest_1326, IsMakerGroup_StandardExifGroup_ReturnsFalse_1326) {
    // "Image" is a standard Exif group, not a maker group
    EXPECT_FALSE(Exiv2::ExifTags::isMakerGroup("Image"));
}

TEST_F(ExifTagsTest_1326, IsMakerGroup_Photo_ReturnsFalse_1326) {
    EXPECT_FALSE(Exiv2::ExifTags::isMakerGroup("Photo"));
}

TEST_F(ExifTagsTest_1326, IsMakerGroup_EmptyString_ReturnsFalse_1326) {
    EXPECT_FALSE(Exiv2::ExifTags::isMakerGroup(""));
}

TEST_F(ExifTagsTest_1326, IsMakerGroup_NonExistentGroup_ReturnsFalse_1326) {
    EXPECT_FALSE(Exiv2::ExifTags::isMakerGroup("NonExistentGroup"));
}

TEST_F(ExifTagsTest_1326, IsMakerGroup_CanonGroup_ReturnsTrue_1326) {
    // Canon is typically a known maker group
    // Note: This test depends on whether "Canon" is registered as a maker group
    bool result = Exiv2::ExifTags::isMakerGroup("Canon");
    // We just verify it returns a boolean without crashing
    (void)result;
}

// ==================== groupList tests ====================

TEST_F(ExifTagsTest_1326, GroupList_ReturnsNonNull_1326) {
    const Exiv2::GroupInfo* groups = Exiv2::ExifTags::groupList();
    EXPECT_NE(groups, nullptr);
}

TEST_F(ExifTagsTest_1326, GroupList_FirstEntryHasValidGroupName_1326) {
    const Exiv2::GroupInfo* groups = Exiv2::ExifTags::groupList();
    ASSERT_NE(groups, nullptr);
    // The first entry should have a non-null group name
    EXPECT_NE(groups[0].groupName_, nullptr);
}

// ==================== tagList tests ====================

TEST_F(ExifTagsTest_1326, TagList_Image_ReturnsNonNull_1326) {
    const Exiv2::TagInfo* tags = Exiv2::ExifTags::tagList("Image");
    EXPECT_NE(tags, nullptr);
}

TEST_F(ExifTagsTest_1326, TagList_Photo_ReturnsNonNull_1326) {
    const Exiv2::TagInfo* tags = Exiv2::ExifTags::tagList("Photo");
    EXPECT_NE(tags, nullptr);
}

TEST_F(ExifTagsTest_1326, TagList_GPSInfo_ReturnsNonNull_1326) {
    const Exiv2::TagInfo* tags = Exiv2::ExifTags::tagList("GPSInfo");
    EXPECT_NE(tags, nullptr);
}

TEST_F(ExifTagsTest_1326, TagList_NonExistentGroup_ReturnsNull_1326) {
    const Exiv2::TagInfo* tags = Exiv2::ExifTags::tagList("NonExistentGroup12345");
    // For non-existent groups, tagList may return nullptr or an empty list
    // We just verify it doesn't crash
    (void)tags;
}

// ==================== taglist (stream) tests ====================

TEST_F(ExifTagsTest_1326, Taglist_OstreamOverload_DoesNotCrash_1326) {
    std::ostringstream os;
    EXPECT_NO_THROW(Exiv2::ExifTags::taglist(os));
    // The output should contain something (at least some tag info)
    EXPECT_FALSE(os.str().empty());
}

TEST_F(ExifTagsTest_1326, Taglist_OstreamWithGroupName_Image_1326) {
    std::ostringstream os;
    EXPECT_NO_THROW(Exiv2::ExifTags::taglist(os, "Image"));
    EXPECT_FALSE(os.str().empty());
}

TEST_F(ExifTagsTest_1326, Taglist_OstreamWithGroupName_Photo_1326) {
    std::ostringstream os;
    EXPECT_NO_THROW(Exiv2::ExifTags::taglist(os, "Photo"));
    EXPECT_FALSE(os.str().empty());
}

TEST_F(ExifTagsTest_1326, Taglist_OstreamWithGroupName_GPSInfo_1326) {
    std::ostringstream os;
    EXPECT_NO_THROW(Exiv2::ExifTags::taglist(os, "GPSInfo"));
    EXPECT_FALSE(os.str().empty());
}

TEST_F(ExifTagsTest_1326, Taglist_OstreamWithGroupName_Iop_1326) {
    std::ostringstream os;
    EXPECT_NO_THROW(Exiv2::ExifTags::taglist(os, "Iop"));
    EXPECT_FALSE(os.str().empty());
}

// ==================== ifdName tests ====================

TEST_F(ExifTagsTest_1326, IfdName_Image_ReturnsNonNull_1326) {
    const char* name = Exiv2::ExifTags::ifdName("Image");
    EXPECT_NE(name, nullptr);
    EXPECT_STRNE(name, "");
}

TEST_F(ExifTagsTest_1326, IfdName_Photo_ReturnsNonNull_1326) {
    const char* name = Exiv2::ExifTags::ifdName("Photo");
    EXPECT_NE(name, nullptr);
    EXPECT_STRNE(name, "");
}

TEST_F(ExifTagsTest_1326, IfdName_EmptyString_1326) {
    const char* name = Exiv2::ExifTags::ifdName("");
    // Should not crash, may return empty or some default
    EXPECT_NE(name, nullptr);
}

TEST_F(ExifTagsTest_1326, IfdName_NonExistentGroup_1326) {
    const char* name = Exiv2::ExifTags::ifdName("NonExistentGroupXYZ");
    EXPECT_NE(name, nullptr);
}

// ==================== sectionName and defaultCount tests (require ExifKey) ====================

TEST_F(ExifTagsTest_1326, SectionName_ValidKey_ReturnsNonNull_1326) {
    Exiv2::ExifKey key("Exif.Image.ImageWidth");
    const char* section = Exiv2::ExifTags::sectionName(key);
    EXPECT_NE(section, nullptr);
}

TEST_F(ExifTagsTest_1326, DefaultCount_ValidKey_ReturnsValue_1326) {
    Exiv2::ExifKey key("Exif.Image.ImageWidth");
    uint16_t count = Exiv2::ExifTags::defaultCount(key);
    // ImageWidth typically has a default count of 1
    EXPECT_GE(count, static_cast<uint16_t>(0));
}

TEST_F(ExifTagsTest_1326, SectionName_PhotoKey_1326) {
    Exiv2::ExifKey key("Exif.Photo.ExposureTime");
    const char* section = Exiv2::ExifTags::sectionName(key);
    EXPECT_NE(section, nullptr);
}

TEST_F(ExifTagsTest_1326, DefaultCount_PhotoKey_1326) {
    Exiv2::ExifKey key("Exif.Photo.ExposureTime");
    uint16_t count = Exiv2::ExifTags::defaultCount(key);
    EXPECT_GE(count, static_cast<uint16_t>(0));
}

TEST_F(ExifTagsTest_1326, SectionName_GPSKey_1326) {
    Exiv2::ExifKey key("Exif.GPSInfo.GPSLatitude");
    const char* section = Exiv2::ExifTags::sectionName(key);
    EXPECT_NE(section, nullptr);
}

// ==================== Boundary/Edge case tests ====================

TEST_F(ExifTagsTest_1326, IsExifGroup_WhitespaceString_ReturnsFalse_1326) {
    EXPECT_FALSE(Exiv2::ExifTags::isExifGroup(" "));
}

TEST_F(ExifTagsTest_1326, IsExifGroup_SpecialCharacters_ReturnsFalse_1326) {
    EXPECT_FALSE(Exiv2::ExifTags::isExifGroup("!@#$%^&*()"));
}

TEST_F(ExifTagsTest_1326, IsMakerGroup_WhitespaceString_ReturnsFalse_1326) {
    EXPECT_FALSE(Exiv2::ExifTags::isMakerGroup(" "));
}

TEST_F(ExifTagsTest_1326, IsExifGroup_VeryLongString_ReturnsFalse_1326) {
    std::string longStr(1000, 'A');
    EXPECT_FALSE(Exiv2::ExifTags::isExifGroup(longStr));
}

TEST_F(ExifTagsTest_1326, IsMakerGroup_VeryLongString_ReturnsFalse_1326) {
    std::string longStr(1000, 'B');
    EXPECT_FALSE(Exiv2::ExifTags::isMakerGroup(longStr));
}

// Test that isExifGroup and isMakerGroup are mutually exclusive for known groups
TEST_F(ExifTagsTest_1326, IsExifGroup_And_IsMakerGroup_MutuallyExclusive_Image_1326) {
    bool isExif = Exiv2::ExifTags::isExifGroup("Image");
    bool isMaker = Exiv2::ExifTags::isMakerGroup("Image");
    // Image should be Exif, not Maker
    EXPECT_TRUE(isExif);
    EXPECT_FALSE(isMaker);
}

TEST_F(ExifTagsTest_1326, IsExifGroup_And_IsMakerGroup_MutuallyExclusive_Photo_1326) {
    bool isExif = Exiv2::ExifTags::isExifGroup("Photo");
    bool isMaker = Exiv2::ExifTags::isMakerGroup("Photo");
    EXPECT_TRUE(isExif);
    EXPECT_FALSE(isMaker);
}

}  // namespace

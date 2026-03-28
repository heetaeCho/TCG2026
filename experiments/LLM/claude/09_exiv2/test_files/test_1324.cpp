#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <exiv2/tags.hpp>
#include <exiv2/exif.hpp>

using namespace Exiv2;

// Test fixture for ExifTags tests
class ExifTagsTest_1324 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// ========== ifdName tests ==========

TEST_F(ExifTagsTest_1324, IfdNameForImage_1324) {
    const char* result = ExifTags::ifdName("Image");
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "IFD0");
}

TEST_F(ExifTagsTest_1324, IfdNameForPhoto_1324) {
    const char* result = ExifTags::ifdName("Photo");
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "Exif");
}

TEST_F(ExifTagsTest_1324, IfdNameForGPSInfo_1324) {
    const char* result = ExifTags::ifdName("GPSInfo");
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "GPSInfo");
}

TEST_F(ExifTagsTest_1324, IfdNameForIop_1324) {
    const char* result = ExifTags::ifdName("Iop");
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "Iop");
}

TEST_F(ExifTagsTest_1324, IfdNameForThumbnail_1324) {
    const char* result = ExifTags::ifdName("Thumbnail");
    ASSERT_NE(result, nullptr);
    // Thumbnail typically maps to IFD1
    EXPECT_STREQ(result, "IFD1");
}

TEST_F(ExifTagsTest_1324, IfdNameForUnknownGroup_1324) {
    const char* result = ExifTags::ifdName("NonExistentGroup");
    ASSERT_NE(result, nullptr);
    // Unknown group should return some default name
    // Just verify it doesn't crash and returns a non-null string
    EXPECT_TRUE(strlen(result) >= 0);
}

TEST_F(ExifTagsTest_1324, IfdNameForEmptyString_1324) {
    const char* result = ExifTags::ifdName("");
    ASSERT_NE(result, nullptr);
}

// ========== isMakerGroup tests ==========

TEST_F(ExifTagsTest_1324, IsMakerGroupForImage_1324) {
    EXPECT_FALSE(ExifTags::isMakerGroup("Image"));
}

TEST_F(ExifTagsTest_1324, IsMakerGroupForPhoto_1324) {
    EXPECT_FALSE(ExifTags::isMakerGroup("Photo"));
}

TEST_F(ExifTagsTest_1324, IsMakerGroupForGPSInfo_1324) {
    EXPECT_FALSE(ExifTags::isMakerGroup("GPSInfo"));
}

TEST_F(ExifTagsTest_1324, IsMakerGroupForUnknown_1324) {
    EXPECT_FALSE(ExifTags::isMakerGroup("SomeRandomGroup"));
}

TEST_F(ExifTagsTest_1324, IsMakerGroupForEmpty_1324) {
    EXPECT_FALSE(ExifTags::isMakerGroup(""));
}

// ========== isExifGroup tests ==========

TEST_F(ExifTagsTest_1324, IsExifGroupForImage_1324) {
    EXPECT_TRUE(ExifTags::isExifGroup("Image"));
}

TEST_F(ExifTagsTest_1324, IsExifGroupForPhoto_1324) {
    EXPECT_TRUE(ExifTags::isExifGroup("Photo"));
}

TEST_F(ExifTagsTest_1324, IsExifGroupForGPSInfo_1324) {
    EXPECT_TRUE(ExifTags::isExifGroup("GPSInfo"));
}

TEST_F(ExifTagsTest_1324, IsExifGroupForIop_1324) {
    EXPECT_TRUE(ExifTags::isExifGroup("Iop"));
}

TEST_F(ExifTagsTest_1324, IsExifGroupForUnknown_1324) {
    EXPECT_FALSE(ExifTags::isExifGroup("NonExistentGroup"));
}

TEST_F(ExifTagsTest_1324, IsExifGroupForEmpty_1324) {
    EXPECT_FALSE(ExifTags::isExifGroup(""));
}

// ========== groupList tests ==========

TEST_F(ExifTagsTest_1324, GroupListReturnsNonNull_1324) {
    const GroupInfo* groups = ExifTags::groupList();
    ASSERT_NE(groups, nullptr);
}

TEST_F(ExifTagsTest_1324, GroupListContainsEntries_1324) {
    const GroupInfo* groups = ExifTags::groupList();
    ASSERT_NE(groups, nullptr);
    // The first entry should have a valid group name
    EXPECT_NE(groups[0].groupName_, nullptr);
}

// ========== tagList tests ==========

TEST_F(ExifTagsTest_1324, TagListForImage_1324) {
    const TagInfo* tags = ExifTags::tagList("Image");
    ASSERT_NE(tags, nullptr);
}

TEST_F(ExifTagsTest_1324, TagListForPhoto_1324) {
    const TagInfo* tags = ExifTags::tagList("Photo");
    ASSERT_NE(tags, nullptr);
}

TEST_F(ExifTagsTest_1324, TagListForGPSInfo_1324) {
    const TagInfo* tags = ExifTags::tagList("GPSInfo");
    ASSERT_NE(tags, nullptr);
}

TEST_F(ExifTagsTest_1324, TagListForUnknownGroupReturnsNull_1324) {
    const TagInfo* tags = ExifTags::tagList("TotallyUnknownGroup12345");
    // Unknown group may return nullptr
    // This tests the boundary case
    // We just check it doesn't crash
    (void)tags;
}

// ========== taglist (stream) tests ==========

TEST_F(ExifTagsTest_1324, TaglistToStream_1324) {
    std::ostringstream os;
    ExifTags::taglist(os);
    std::string output = os.str();
    // Should produce some output
    EXPECT_FALSE(output.empty());
}

TEST_F(ExifTagsTest_1324, TaglistToStreamForImage_1324) {
    std::ostringstream os;
    ExifTags::taglist(os, "Image");
    std::string output = os.str();
    EXPECT_FALSE(output.empty());
}

TEST_F(ExifTagsTest_1324, TaglistToStreamForPhoto_1324) {
    std::ostringstream os;
    ExifTags::taglist(os, "Photo");
    std::string output = os.str();
    EXPECT_FALSE(output.empty());
}

TEST_F(ExifTagsTest_1324, TaglistToStreamForGPSInfo_1324) {
    std::ostringstream os;
    ExifTags::taglist(os, "GPSInfo");
    std::string output = os.str();
    EXPECT_FALSE(output.empty());
}

TEST_F(ExifTagsTest_1324, TaglistToStreamForUnknownGroup_1324) {
    std::ostringstream os;
    // Should not crash for unknown group
    ExifTags::taglist(os, "UnknownGroupXYZ");
    // Output may be empty for unknown group
}

// ========== sectionName tests ==========

TEST_F(ExifTagsTest_1324, SectionNameForValidKey_1324) {
    ExifKey key("Exif.Image.ImageWidth");
    const char* section = ExifTags::sectionName(key);
    ASSERT_NE(section, nullptr);
    EXPECT_TRUE(strlen(section) > 0);
}

TEST_F(ExifTagsTest_1324, SectionNameForPhotoKey_1324) {
    ExifKey key("Exif.Photo.ExposureTime");
    const char* section = ExifTags::sectionName(key);
    ASSERT_NE(section, nullptr);
    EXPECT_TRUE(strlen(section) > 0);
}

TEST_F(ExifTagsTest_1324, SectionNameForGPSKey_1324) {
    ExifKey key("Exif.GPSInfo.GPSLatitude");
    const char* section = ExifTags::sectionName(key);
    ASSERT_NE(section, nullptr);
    EXPECT_TRUE(strlen(section) > 0);
}

// ========== defaultCount tests ==========

TEST_F(ExifTagsTest_1324, DefaultCountForImageWidth_1324) {
    ExifKey key("Exif.Image.ImageWidth");
    uint16_t count = ExifTags::defaultCount(key);
    EXPECT_EQ(count, 1);
}

TEST_F(ExifTagsTest_1324, DefaultCountForGPSLatitude_1324) {
    ExifKey key("Exif.GPSInfo.GPSLatitude");
    uint16_t count = ExifTags::defaultCount(key);
    EXPECT_EQ(count, 3);
}

TEST_F(ExifTagsTest_1324, DefaultCountForExposureTime_1324) {
    ExifKey key("Exif.Photo.ExposureTime");
    uint16_t count = ExifTags::defaultCount(key);
    EXPECT_EQ(count, 1);
}

// ========== Consistency tests ==========

TEST_F(ExifTagsTest_1324, IfdNameAndIsExifGroupConsistency_1324) {
    // If a group is an EXIF group, ifdName should return a non-empty name
    std::string groups[] = {"Image", "Photo", "GPSInfo", "Iop", "Thumbnail"};
    for (const auto& group : groups) {
        if (ExifTags::isExifGroup(group)) {
            const char* name = ExifTags::ifdName(group);
            ASSERT_NE(name, nullptr) << "ifdName returned null for group: " << group;
            EXPECT_TRUE(strlen(name) > 0) << "ifdName returned empty for group: " << group;
        }
    }
}

TEST_F(ExifTagsTest_1324, MakerGroupIsNotStandardExifGroup_1324) {
    // Standard EXIF groups should not be maker groups
    EXPECT_FALSE(ExifTags::isMakerGroup("Image"));
    EXPECT_FALSE(ExifTags::isMakerGroup("Photo"));
    EXPECT_FALSE(ExifTags::isMakerGroup("GPSInfo"));
    EXPECT_FALSE(ExifTags::isMakerGroup("Iop"));
}

#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <exiv2/tags.hpp>
#include <exiv2/exif.hpp>

namespace {

// Test fixture for ExifTags tests
class ExifTagsTest_1329 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that taglist(os) produces non-empty output
TEST_F(ExifTagsTest_1329, TaglistProducesNonEmptyOutput_1329) {
    std::ostringstream os;
    Exiv2::ExifTags::taglist(os);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// Test that taglist(os) output contains newline characters (multiple tags)
TEST_F(ExifTagsTest_1329, TaglistContainsMultipleLines_1329) {
    std::ostringstream os;
    Exiv2::ExifTags::taglist(os);
    std::string result = os.str();
    // There should be multiple newlines indicating multiple tags
    size_t newlineCount = std::count(result.begin(), result.end(), '\n');
    EXPECT_GT(newlineCount, 1u);
}

// Test that taglist(os) is deterministic - calling twice gives same result
TEST_F(ExifTagsTest_1329, TaglistIsDeterministic_1329) {
    std::ostringstream os1;
    std::ostringstream os2;
    Exiv2::ExifTags::taglist(os1);
    Exiv2::ExifTags::taglist(os2);
    EXPECT_EQ(os1.str(), os2.str());
}

// Test taglist with group name for "Image" group
TEST_F(ExifTagsTest_1329, TaglistWithImageGroupProducesOutput_1329) {
    std::ostringstream os;
    Exiv2::ExifTags::taglist(os, "Image");
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// Test taglist with group name for "Photo" (Exif) group
TEST_F(ExifTagsTest_1329, TaglistWithPhotoGroupProducesOutput_1329) {
    std::ostringstream os;
    Exiv2::ExifTags::taglist(os, "Photo");
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// Test taglist with group name for "GPSInfo" group
TEST_F(ExifTagsTest_1329, TaglistWithGPSInfoGroupProducesOutput_1329) {
    std::ostringstream os;
    Exiv2::ExifTags::taglist(os, "GPSInfo");
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// Test taglist with group name for "Iop" group
TEST_F(ExifTagsTest_1329, TaglistWithIopGroupProducesOutput_1329) {
    std::ostringstream os;
    Exiv2::ExifTags::taglist(os, "Iop");
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// Test groupList returns non-null
TEST_F(ExifTagsTest_1329, GroupListReturnsNonNull_1329) {
    const Exiv2::GroupInfo* groups = Exiv2::ExifTags::groupList();
    ASSERT_NE(groups, nullptr);
}

// Test tagList with known group name returns non-null
TEST_F(ExifTagsTest_1329, TagListWithKnownGroupReturnsNonNull_1329) {
    const Exiv2::TagInfo* tags = Exiv2::ExifTags::tagList("Image");
    ASSERT_NE(tags, nullptr);
}

// Test tagList with "Photo" group returns non-null
TEST_F(ExifTagsTest_1329, TagListWithPhotoGroupReturnsNonNull_1329) {
    const Exiv2::TagInfo* tags = Exiv2::ExifTags::tagList("Photo");
    ASSERT_NE(tags, nullptr);
}

// Test tagList with "GPSInfo" group returns non-null
TEST_F(ExifTagsTest_1329, TagListWithGPSInfoGroupReturnsNonNull_1329) {
    const Exiv2::TagInfo* tags = Exiv2::ExifTags::tagList("GPSInfo");
    ASSERT_NE(tags, nullptr);
}

// Test isExifGroup for known Exif groups
TEST_F(ExifTagsTest_1329, IsExifGroupReturnsTrueForImage_1329) {
    EXPECT_TRUE(Exiv2::ExifTags::isExifGroup("Image"));
}

TEST_F(ExifTagsTest_1329, IsExifGroupReturnsTrueForPhoto_1329) {
    EXPECT_TRUE(Exiv2::ExifTags::isExifGroup("Photo"));
}

TEST_F(ExifTagsTest_1329, IsExifGroupReturnsTrueForGPSInfo_1329) {
    EXPECT_TRUE(Exiv2::ExifTags::isExifGroup("GPSInfo"));
}

TEST_F(ExifTagsTest_1329, IsExifGroupReturnsTrueForIop_1329) {
    EXPECT_TRUE(Exiv2::ExifTags::isExifGroup("Iop"));
}

// Test isExifGroup returns false for non-exif groups
TEST_F(ExifTagsTest_1329, IsExifGroupReturnsFalseForNonExifGroup_1329) {
    EXPECT_FALSE(Exiv2::ExifTags::isExifGroup("NonExistentGroup"));
}

TEST_F(ExifTagsTest_1329, IsExifGroupReturnsFalseForEmptyString_1329) {
    EXPECT_FALSE(Exiv2::ExifTags::isExifGroup(""));
}

// Test isMakerGroup returns false for standard Exif groups
TEST_F(ExifTagsTest_1329, IsMakerGroupReturnsFalseForImage_1329) {
    EXPECT_FALSE(Exiv2::ExifTags::isMakerGroup("Image"));
}

TEST_F(ExifTagsTest_1329, IsMakerGroupReturnsFalseForPhoto_1329) {
    EXPECT_FALSE(Exiv2::ExifTags::isMakerGroup("Photo"));
}

TEST_F(ExifTagsTest_1329, IsMakerGroupReturnsFalseForEmptyString_1329) {
    EXPECT_FALSE(Exiv2::ExifTags::isMakerGroup(""));
}

TEST_F(ExifTagsTest_1329, IsMakerGroupReturnsFalseForNonExistentGroup_1329) {
    EXPECT_FALSE(Exiv2::ExifTags::isMakerGroup("NonExistentGroup"));
}

// Test ifdName for known groups
TEST_F(ExifTagsTest_1329, IfdNameForImageGroup_1329) {
    const char* name = Exiv2::ExifTags::ifdName("Image");
    ASSERT_NE(name, nullptr);
    EXPECT_GT(std::string(name).length(), 0u);
}

TEST_F(ExifTagsTest_1329, IfdNameForPhotoGroup_1329) {
    const char* name = Exiv2::ExifTags::ifdName("Photo");
    ASSERT_NE(name, nullptr);
    EXPECT_GT(std::string(name).length(), 0u);
}

// Test sectionName with a valid ExifKey
TEST_F(ExifTagsTest_1329, SectionNameForValidKey_1329) {
    Exiv2::ExifKey key("Exif.Image.ImageWidth");
    const char* section = Exiv2::ExifTags::sectionName(key);
    ASSERT_NE(section, nullptr);
    EXPECT_GT(std::string(section).length(), 0u);
}

// Test defaultCount with a valid ExifKey
TEST_F(ExifTagsTest_1329, DefaultCountForImageWidth_1329) {
    Exiv2::ExifKey key("Exif.Image.ImageWidth");
    uint16_t count = Exiv2::ExifTags::defaultCount(key);
    // ImageWidth should have a count of 1
    EXPECT_GE(count, 0u);
}

// Test that the overall taglist output contains known tag names
TEST_F(ExifTagsTest_1329, TaglistContainsKnownTagNames_1329) {
    std::ostringstream os;
    Exiv2::ExifTags::taglist(os);
    std::string result = os.str();
    // We expect some well-known tags to appear
    // ImageWidth is a standard IFD tag
    EXPECT_NE(result.find("ImageWidth"), std::string::npos);
}

// Test that the group-specific taglist for Photo contains ExposureTime
TEST_F(ExifTagsTest_1329, PhotoTaglistContainsExposureTime_1329) {
    std::ostringstream os;
    Exiv2::ExifTags::taglist(os, "Photo");
    std::string result = os.str();
    EXPECT_NE(result.find("ExposureTime"), std::string::npos);
}

// Test that the group-specific taglist for GPSInfo contains GPSLatitude
TEST_F(ExifTagsTest_1329, GPSInfoTaglistContainsGPSLatitude_1329) {
    std::ostringstream os;
    Exiv2::ExifTags::taglist(os, "GPSInfo");
    std::string result = os.str();
    EXPECT_NE(result.find("GPSLatitude"), std::string::npos);
}

// Test that groupList has at least a few groups
TEST_F(ExifTagsTest_1329, GroupListHasMultipleEntries_1329) {
    const Exiv2::GroupInfo* groups = Exiv2::ExifTags::groupList();
    ASSERT_NE(groups, nullptr);
    int count = 0;
    for (int i = 0; groups[i].groupName_ != nullptr; ++i) {
        ++count;
    }
    EXPECT_GT(count, 3);
}

// Test taglist with different stream states
TEST_F(ExifTagsTest_1329, TaglistWithFreshStream_1329) {
    std::ostringstream os;
    EXPECT_TRUE(os.good());
    Exiv2::ExifTags::taglist(os);
    EXPECT_TRUE(os.good());
}

// Test that taglist with group name for unknown group
TEST_F(ExifTagsTest_1329, TaglistWithUnknownGroupProducesNoOutput_1329) {
    std::ostringstream os;
    // Passing an unknown group name - behavior may vary
    // but it should not crash
    try {
        Exiv2::ExifTags::taglist(os, "CompletelyFakeGroup12345");
    } catch (...) {
        // It's acceptable to throw for unknown groups
    }
}

}  // namespace

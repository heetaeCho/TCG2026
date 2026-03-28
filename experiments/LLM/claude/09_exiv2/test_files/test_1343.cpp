#include <gtest/gtest.h>
#include <exiv2/tags.hpp>
#include <exiv2/exif.hpp>
#include <string>

namespace {

// Test fixture for ExifKey tests
class ExifKeyTest_1343 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test construction from string key and basic accessors
TEST_F(ExifKeyTest_1343, ConstructFromString_ValidKey_1343) {
    Exiv2::ExifKey key("Exif.Image.Make");
    EXPECT_EQ("Exif.Image.Make", key.key());
    EXPECT_EQ("Exif", std::string(key.familyName()));
    EXPECT_EQ("Image", key.groupName());
    EXPECT_EQ("Make", key.tagName());
}

// Test construction from tag number and group name
TEST_F(ExifKeyTest_1343, ConstructFromTagAndGroup_1343) {
    Exiv2::ExifKey key(0x010f, "Image");
    EXPECT_EQ(0x010f, key.tag());
    EXPECT_EQ("Image", key.groupName());
    EXPECT_EQ("Exif", std::string(key.familyName()));
    EXPECT_EQ("Make", key.tagName());
}

// Test tag() returns correct tag value
TEST_F(ExifKeyTest_1343, TagReturnsCorrectValue_1343) {
    Exiv2::ExifKey key("Exif.Image.Model");
    EXPECT_EQ(0x0110, key.tag());
}

// Test key() returns full key string
TEST_F(ExifKeyTest_1343, KeyReturnsFullString_1343) {
    Exiv2::ExifKey key("Exif.Image.Model");
    EXPECT_EQ("Exif.Image.Model", key.key());
}

// Test familyName() always returns "Exif"
TEST_F(ExifKeyTest_1343, FamilyNameIsExif_1343) {
    Exiv2::ExifKey key("Exif.Image.Make");
    EXPECT_STREQ("Exif", key.familyName());
}

// Test groupName() returns the correct group
TEST_F(ExifKeyTest_1343, GroupNameReturnsCorrectGroup_1343) {
    Exiv2::ExifKey key("Exif.Photo.ExposureTime");
    EXPECT_EQ("Photo", key.groupName());
}

// Test tagName() returns correct tag name
TEST_F(ExifKeyTest_1343, TagNameReturnsCorrectName_1343) {
    Exiv2::ExifKey key("Exif.Photo.ExposureTime");
    EXPECT_EQ("ExposureTime", key.tagName());
}

// Test copy constructor
TEST_F(ExifKeyTest_1343, CopyConstructor_1343) {
    Exiv2::ExifKey original("Exif.Image.Make");
    Exiv2::ExifKey copy(original);
    EXPECT_EQ(original.key(), copy.key());
    EXPECT_EQ(original.tag(), copy.tag());
    EXPECT_EQ(original.groupName(), copy.groupName());
    EXPECT_EQ(original.tagName(), copy.tagName());
}

// Test assignment operator
TEST_F(ExifKeyTest_1343, AssignmentOperator_1343) {
    Exiv2::ExifKey key1("Exif.Image.Make");
    Exiv2::ExifKey key2("Exif.Image.Model");
    key2 = key1;
    EXPECT_EQ(key1.key(), key2.key());
    EXPECT_EQ(key1.tag(), key2.tag());
    EXPECT_EQ(key1.groupName(), key2.groupName());
}

// Test clone() creates an independent copy
TEST_F(ExifKeyTest_1343, CloneCreatesIndependentCopy_1343) {
    Exiv2::ExifKey key("Exif.Image.Make");
    auto cloned = key.clone();
    ASSERT_NE(nullptr, cloned.get());
    EXPECT_EQ(key.key(), cloned->key());
    EXPECT_EQ(key.tag(), cloned->tag());
    EXPECT_EQ(key.groupName(), cloned->groupName());
    EXPECT_EQ(key.tagName(), cloned->tagName());
}

// Test setIdx and idx
TEST_F(ExifKeyTest_1343, SetIdxAndIdx_1343) {
    Exiv2::ExifKey key("Exif.Image.Make");
    key.setIdx(42);
    EXPECT_EQ(42, key.idx());
}

// Test idx default value
TEST_F(ExifKeyTest_1343, IdxDefaultValue_1343) {
    Exiv2::ExifKey key("Exif.Image.Make");
    EXPECT_EQ(0, key.idx());
}

// Test tagLabel returns non-empty string for known tags
TEST_F(ExifKeyTest_1343, TagLabelForKnownTag_1343) {
    Exiv2::ExifKey key("Exif.Image.Make");
    std::string label = key.tagLabel();
    EXPECT_FALSE(label.empty());
}

// Test defaultTypeId for a known tag
TEST_F(ExifKeyTest_1343, DefaultTypeIdForKnownTag_1343) {
    Exiv2::ExifKey key("Exif.Image.Make");
    // Make is typically asciiString
    EXPECT_EQ(Exiv2::asciiString, key.defaultTypeId());
}

// Test ifdId returns a valid IfdId
TEST_F(ExifKeyTest_1343, IfdIdReturnsValidId_1343) {
    Exiv2::ExifKey key("Exif.Image.Make");
    EXPECT_NE(Exiv2::IfdId::ifdIdNotSet, key.ifdId());
}

// Test construction with invalid key string throws
TEST_F(ExifKeyTest_1343, ConstructFromInvalidString_Throws_1343) {
    EXPECT_THROW(Exiv2::ExifKey key("InvalidKey"), Exiv2::Error);
}

// Test construction with unknown group in string
TEST_F(ExifKeyTest_1343, ConstructFromUnknownGroup_Throws_1343) {
    EXPECT_THROW(Exiv2::ExifKey key("Exif.NonExistentGroup.SomeTag"), Exiv2::Error);
}

// Test ExposureTime tag from Photo group
TEST_F(ExifKeyTest_1343, PhotoGroupExposureTime_1343) {
    Exiv2::ExifKey key(0x829a, "Photo");
    EXPECT_EQ(0x829a, key.tag());
    EXPECT_EQ("Photo", key.groupName());
    EXPECT_EQ("ExposureTime", key.tagName());
}

// Test that different tags have different tag values
TEST_F(ExifKeyTest_1343, DifferentTagsHaveDifferentValues_1343) {
    Exiv2::ExifKey key1("Exif.Image.Make");
    Exiv2::ExifKey key2("Exif.Image.Model");
    EXPECT_NE(key1.tag(), key2.tag());
    EXPECT_NE(key1.key(), key2.key());
}

// Test tagDesc returns a description (may be empty for unknown tags, but non-null behavior)
TEST_F(ExifKeyTest_1343, TagDescForKnownTag_1343) {
    Exiv2::ExifKey key("Exif.Image.Make");
    // Just ensure it doesn't crash; description may or may not be empty
    std::string desc = key.tagDesc();
    // No assertion on content since it depends on localization/implementation
    (void)desc;
}

// Test self-assignment
TEST_F(ExifKeyTest_1343, SelfAssignment_1343) {
    Exiv2::ExifKey key("Exif.Image.Make");
    key = key;
    EXPECT_EQ("Exif.Image.Make", key.key());
    EXPECT_EQ(0x010f, key.tag());
}

// Test construction from tag and group for GPS tags
TEST_F(ExifKeyTest_1343, GPSGroupTag_1343) {
    Exiv2::ExifKey key("Exif.GPSInfo.GPSLatitude");
    EXPECT_EQ("GPSInfo", key.groupName());
    EXPECT_EQ("GPSLatitude", key.tagName());
}

// Test setIdx with negative value
TEST_F(ExifKeyTest_1343, SetIdxNegativeValue_1343) {
    Exiv2::ExifKey key("Exif.Image.Make");
    key.setIdx(-1);
    EXPECT_EQ(-1, key.idx());
}

// Test setIdx with zero
TEST_F(ExifKeyTest_1343, SetIdxZero_1343) {
    Exiv2::ExifKey key("Exif.Image.Make");
    key.setIdx(0);
    EXPECT_EQ(0, key.idx());
}

// Test clone preserves idx
TEST_F(ExifKeyTest_1343, ClonePreservesIdx_1343) {
    Exiv2::ExifKey key("Exif.Image.Make");
    key.setIdx(17);
    auto cloned = key.clone();
    EXPECT_EQ(17, cloned->idx());
}

// Test construction from tag number with ImageWidth
TEST_F(ExifKeyTest_1343, ConstructFromTagNumber_ImageWidth_1343) {
    Exiv2::ExifKey key(0x0100, "Image");
    EXPECT_EQ(0x0100, key.tag());
    EXPECT_EQ("ImageWidth", key.tagName());
}

} // namespace

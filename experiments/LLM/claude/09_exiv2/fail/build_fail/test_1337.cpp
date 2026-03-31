#include <gtest/gtest.h>
#include <exiv2/tags.hpp>
#include <exiv2/exif.hpp>
#include <string>

namespace {

// Test fixture for ExifKey tests
class ExifKeyTest_1337 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test: familyName returns "Exif"
TEST_F(ExifKeyTest_1337, FamilyNameReturnsExif_1337) {
    Exiv2::ExifKey key("Exif.Photo.DateTimeOriginal");
    EXPECT_STREQ(key.familyName(), "Exif");
}

// Test: Construction from string key
TEST_F(ExifKeyTest_1337, ConstructFromStringKey_1337) {
    Exiv2::ExifKey key("Exif.Photo.DateTimeOriginal");
    EXPECT_EQ(key.key(), "Exif.Photo.DateTimeOriginal");
}

// Test: groupName returns correct group
TEST_F(ExifKeyTest_1337, GroupNameReturnsCorrectGroup_1337) {
    Exiv2::ExifKey key("Exif.Photo.DateTimeOriginal");
    EXPECT_EQ(key.groupName(), "Photo");
}

// Test: tagName returns correct tag name
TEST_F(ExifKeyTest_1337, TagNameReturnsCorrectName_1337) {
    Exiv2::ExifKey key("Exif.Photo.DateTimeOriginal");
    EXPECT_EQ(key.tagName(), "DateTimeOriginal");
}

// Test: Construction from tag number and group name
TEST_F(ExifKeyTest_1337, ConstructFromTagAndGroup_1337) {
    // Tag 0x9003 is DateTimeOriginal in Photo group
    Exiv2::ExifKey key(0x9003, "Photo");
    EXPECT_EQ(key.key(), "Exif.Photo.DateTimeOriginal");
    EXPECT_EQ(key.tag(), 0x9003);
    EXPECT_EQ(key.groupName(), "Photo");
}

// Test: tag() returns correct tag number
TEST_F(ExifKeyTest_1337, TagReturnsCorrectNumber_1337) {
    Exiv2::ExifKey key("Exif.Photo.DateTimeOriginal");
    EXPECT_EQ(key.tag(), 0x9003);
}

// Test: Copy constructor
TEST_F(ExifKeyTest_1337, CopyConstructor_1337) {
    Exiv2::ExifKey original("Exif.Photo.DateTimeOriginal");
    Exiv2::ExifKey copy(original);
    EXPECT_EQ(copy.key(), original.key());
    EXPECT_EQ(copy.tag(), original.tag());
    EXPECT_EQ(copy.groupName(), original.groupName());
    EXPECT_EQ(copy.tagName(), original.tagName());
    EXPECT_STREQ(copy.familyName(), original.familyName());
}

// Test: Copy assignment operator
TEST_F(ExifKeyTest_1337, CopyAssignmentOperator_1337) {
    Exiv2::ExifKey key1("Exif.Photo.DateTimeOriginal");
    Exiv2::ExifKey key2("Exif.Image.ImageWidth");
    key2 = key1;
    EXPECT_EQ(key2.key(), key1.key());
    EXPECT_EQ(key2.tag(), key1.tag());
    EXPECT_EQ(key2.groupName(), key1.groupName());
}

// Test: clone() produces an equivalent key
TEST_F(ExifKeyTest_1337, CloneProducesEquivalentKey_1337) {
    Exiv2::ExifKey key("Exif.Photo.DateTimeOriginal");
    auto cloned = key.clone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->key(), key.key());
    EXPECT_EQ(cloned->tag(), key.tag());
    EXPECT_EQ(cloned->groupName(), key.groupName());
    EXPECT_STREQ(cloned->familyName(), key.familyName());
}

// Test: idx default value and setIdx
TEST_F(ExifKeyTest_1337, IdxDefaultAndSetIdx_1337) {
    Exiv2::ExifKey key("Exif.Photo.DateTimeOriginal");
    // Default idx should be 0
    EXPECT_EQ(key.idx(), 0);
    key.setIdx(42);
    EXPECT_EQ(key.idx(), 42);
}

// Test: tagLabel returns non-empty label for known tags
TEST_F(ExifKeyTest_1337, TagLabelForKnownTag_1337) {
    Exiv2::ExifKey key("Exif.Photo.DateTimeOriginal");
    std::string label = key.tagLabel();
    EXPECT_FALSE(label.empty());
}

// Test: Construction with Image group tags
TEST_F(ExifKeyTest_1337, ImageGroupTag_1337) {
    Exiv2::ExifKey key("Exif.Image.ImageWidth");
    EXPECT_EQ(key.groupName(), "Image");
    EXPECT_EQ(key.tagName(), "ImageWidth");
    EXPECT_STREQ(key.familyName(), "Exif");
    EXPECT_EQ(key.tag(), 0x0100);
}

// Test: Invalid key string should throw
TEST_F(ExifKeyTest_1337, InvalidKeyStringThrows_1337) {
    EXPECT_THROW(Exiv2::ExifKey("InvalidKeyString"), Exiv2::Error);
}

// Test: Key with wrong family prefix should throw
TEST_F(ExifKeyTest_1337, WrongFamilyPrefixThrows_1337) {
    EXPECT_THROW(Exiv2::ExifKey("Iptc.Photo.DateTimeOriginal"), Exiv2::Error);
}

// Test: defaultTypeId returns a valid TypeId
TEST_F(ExifKeyTest_1337, DefaultTypeIdForKnownTag_1337) {
    Exiv2::ExifKey key("Exif.Photo.DateTimeOriginal");
    Exiv2::TypeId typeId = key.defaultTypeId();
    // DateTimeOriginal should be asciiString type
    EXPECT_EQ(typeId, Exiv2::asciiString);
}

// Test: Construction from tag number with Image group
TEST_F(ExifKeyTest_1337, ConstructFromTagNumberImageGroup_1337) {
    // Tag 0x0100 is ImageWidth
    Exiv2::ExifKey key(0x0100, "Image");
    EXPECT_EQ(key.tag(), 0x0100);
    EXPECT_EQ(key.groupName(), "Image");
    EXPECT_EQ(key.key(), "Exif.Image.ImageWidth");
}

// Test: tagDesc returns description for known tag
TEST_F(ExifKeyTest_1337, TagDescForKnownTag_1337) {
    Exiv2::ExifKey key("Exif.Photo.DateTimeOriginal");
    std::string desc = key.tagDesc();
    // Known tags should have a non-empty description
    EXPECT_FALSE(desc.empty());
}

// Test: Different Exif groups
TEST_F(ExifKeyTest_1337, GPSInfoGroupTag_1337) {
    Exiv2::ExifKey key("Exif.GPSInfo.GPSLatitude");
    EXPECT_EQ(key.groupName(), "GPSInfo");
    EXPECT_EQ(key.tagName(), "GPSLatitude");
    EXPECT_STREQ(key.familyName(), "Exif");
}

// Test: Self-assignment should work
TEST_F(ExifKeyTest_1337, SelfAssignment_1337) {
    Exiv2::ExifKey key("Exif.Photo.DateTimeOriginal");
    const auto& ref = key;
    key = ref;
    EXPECT_EQ(key.key(), "Exif.Photo.DateTimeOriginal");
}

// Test: setIdx with negative value
TEST_F(ExifKeyTest_1337, SetIdxNegativeValue_1337) {
    Exiv2::ExifKey key("Exif.Photo.DateTimeOriginal");
    key.setIdx(-1);
    EXPECT_EQ(key.idx(), -1);
}

// Test: setIdx with zero
TEST_F(ExifKeyTest_1337, SetIdxZero_1337) {
    Exiv2::ExifKey key("Exif.Photo.DateTimeOriginal");
    key.setIdx(100);
    EXPECT_EQ(key.idx(), 100);
    key.setIdx(0);
    EXPECT_EQ(key.idx(), 0);
}

// Test: ifdId returns valid IfdId
TEST_F(ExifKeyTest_1337, IfdIdForPhotoGroup_1337) {
    Exiv2::ExifKey key("Exif.Photo.DateTimeOriginal");
    Exiv2::IfdId ifdId = key.ifdId();
    // Should return a valid non-zero IfdId for Photo group
    EXPECT_NE(ifdId, Exiv2::ifdIdNotSet);
}

// Test: Multiple clones are independent
TEST_F(ExifKeyTest_1337, MultipleClonesAreIndependent_1337) {
    Exiv2::ExifKey key("Exif.Photo.DateTimeOriginal");
    key.setIdx(5);
    auto clone1 = key.clone();
    auto clone2 = key.clone();
    EXPECT_EQ(clone1->key(), clone2->key());
    EXPECT_EQ(clone1->idx(), clone2->idx());
}

// Test: familyName is consistent across different keys
TEST_F(ExifKeyTest_1337, FamilyNameConsistentAcrossKeys_1337) {
    Exiv2::ExifKey key1("Exif.Photo.DateTimeOriginal");
    Exiv2::ExifKey key2("Exif.Image.ImageWidth");
    EXPECT_STREQ(key1.familyName(), key2.familyName());
    EXPECT_STREQ(key1.familyName(), "Exif");
}

// Test: Empty group/partial key string should throw
TEST_F(ExifKeyTest_1337, EmptyKeyStringThrows_1337) {
    EXPECT_THROW(Exiv2::ExifKey(""), Exiv2::Error);
}

// Test: Key with only family name should throw
TEST_F(ExifKeyTest_1337, OnlyFamilyNameThrows_1337) {
    EXPECT_THROW(Exiv2::ExifKey("Exif"), Exiv2::Error);
}

// Test: Key with family and group but no tag should throw
TEST_F(ExifKeyTest_1337, IncompleteKeyThrows_1337) {
    EXPECT_THROW(Exiv2::ExifKey("Exif.Photo"), Exiv2::Error);
}

}  // namespace

#include <gtest/gtest.h>
#include <exiv2/tags.hpp>
#include <exiv2/error.hpp>
#include <string>

namespace {

// Test fixture for ExifKey tests
class ExifKeyTest_1335 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test construction from a valid string key
TEST_F(ExifKeyTest_1335, ConstructFromValidStringKey_1335) {
    ASSERT_NO_THROW(Exiv2::ExifKey key("Exif.Photo.DateTimeOriginal"));
}

// Test construction from tag and group name
TEST_F(ExifKeyTest_1335, ConstructFromTagAndGroupName_1335) {
    ASSERT_NO_THROW(Exiv2::ExifKey key(0x9003, "Photo"));
}

// Test that key() returns the expected string representation
TEST_F(ExifKeyTest_1335, KeyReturnsCorrectString_1335) {
    Exiv2::ExifKey key("Exif.Photo.DateTimeOriginal");
    std::string result = key.key();
    EXPECT_EQ(result, "Exif.Photo.DateTimeOriginal");
}

// Test that familyName() returns "Exif"
TEST_F(ExifKeyTest_1335, FamilyNameReturnsExif_1335) {
    Exiv2::ExifKey key("Exif.Photo.DateTimeOriginal");
    EXPECT_STREQ(key.familyName(), "Exif");
}

// Test that groupName() returns the correct group
TEST_F(ExifKeyTest_1335, GroupNameReturnsCorrectGroup_1335) {
    Exiv2::ExifKey key("Exif.Photo.DateTimeOriginal");
    EXPECT_EQ(key.groupName(), "Photo");
}

// Test that tagName() returns the correct tag name
TEST_F(ExifKeyTest_1335, TagNameReturnsCorrectName_1335) {
    Exiv2::ExifKey key("Exif.Photo.DateTimeOriginal");
    EXPECT_EQ(key.tagName(), "DateTimeOriginal");
}

// Test that tag() returns the correct tag number
TEST_F(ExifKeyTest_1335, TagReturnsCorrectValue_1335) {
    Exiv2::ExifKey key("Exif.Photo.DateTimeOriginal");
    EXPECT_EQ(key.tag(), 0x9003);
}

// Test construction from tag number and group name matches string construction
TEST_F(ExifKeyTest_1335, ConstructFromTagNumberMatchesStringConstruction_1335) {
    Exiv2::ExifKey keyFromString("Exif.Photo.DateTimeOriginal");
    Exiv2::ExifKey keyFromTag(0x9003, "Photo");
    EXPECT_EQ(keyFromString.key(), keyFromTag.key());
    EXPECT_EQ(keyFromString.tag(), keyFromTag.tag());
    EXPECT_EQ(keyFromString.groupName(), keyFromTag.groupName());
    EXPECT_EQ(keyFromString.tagName(), keyFromTag.tagName());
}

// Test setIdx and idx
TEST_F(ExifKeyTest_1335, SetIdxAndGetIdx_1335) {
    Exiv2::ExifKey key("Exif.Photo.DateTimeOriginal");
    key.setIdx(42);
    EXPECT_EQ(key.idx(), 42);
}

// Test setIdx with zero
TEST_F(ExifKeyTest_1335, SetIdxToZero_1335) {
    Exiv2::ExifKey key("Exif.Photo.DateTimeOriginal");
    key.setIdx(0);
    EXPECT_EQ(key.idx(), 0);
}

// Test setIdx with negative value
TEST_F(ExifKeyTest_1335, SetIdxNegativeValue_1335) {
    Exiv2::ExifKey key("Exif.Photo.DateTimeOriginal");
    key.setIdx(-5);
    EXPECT_EQ(key.idx(), -5);
}

// Test default idx is 0
TEST_F(ExifKeyTest_1335, DefaultIdxIsZero_1335) {
    Exiv2::ExifKey key("Exif.Photo.DateTimeOriginal");
    EXPECT_EQ(key.idx(), 0);
}

// Test copy constructor
TEST_F(ExifKeyTest_1335, CopyConstructor_1335) {
    Exiv2::ExifKey original("Exif.Photo.DateTimeOriginal");
    original.setIdx(10);
    Exiv2::ExifKey copy(original);
    EXPECT_EQ(copy.key(), original.key());
    EXPECT_EQ(copy.tag(), original.tag());
    EXPECT_EQ(copy.groupName(), original.groupName());
    EXPECT_EQ(copy.tagName(), original.tagName());
    EXPECT_EQ(copy.idx(), original.idx());
}

// Test assignment operator
TEST_F(ExifKeyTest_1335, AssignmentOperator_1335) {
    Exiv2::ExifKey key1("Exif.Photo.DateTimeOriginal");
    Exiv2::ExifKey key2("Exif.Image.Make");
    key1.setIdx(7);
    key2 = key1;
    EXPECT_EQ(key2.key(), key1.key());
    EXPECT_EQ(key2.tag(), key1.tag());
    EXPECT_EQ(key2.groupName(), key1.groupName());
    EXPECT_EQ(key2.idx(), key1.idx());
}

// Test clone
TEST_F(ExifKeyTest_1335, CloneCreatesIndependentCopy_1335) {
    Exiv2::ExifKey key("Exif.Photo.DateTimeOriginal");
    key.setIdx(99);
    auto cloned = key.clone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->key(), key.key());
    EXPECT_EQ(cloned->tag(), key.tag());
    EXPECT_EQ(cloned->groupName(), key.groupName());
    EXPECT_EQ(cloned->idx(), key.idx());
}

// Test that clone is independent (modifying clone doesn't affect original)
TEST_F(ExifKeyTest_1335, CloneIsIndependent_1335) {
    Exiv2::ExifKey key("Exif.Photo.DateTimeOriginal");
    key.setIdx(5);
    auto cloned = key.clone();
    cloned->setIdx(100);
    EXPECT_EQ(key.idx(), 5);
    EXPECT_EQ(cloned->idx(), 100);
}

// Test tagLabel returns a non-empty string for known tags
TEST_F(ExifKeyTest_1335, TagLabelForKnownTag_1335) {
    Exiv2::ExifKey key("Exif.Photo.DateTimeOriginal");
    std::string label = key.tagLabel();
    EXPECT_FALSE(label.empty());
}

// Test tagDesc for a known tag
TEST_F(ExifKeyTest_1335, TagDescForKnownTag_1335) {
    Exiv2::ExifKey key("Exif.Photo.DateTimeOriginal");
    std::string desc = key.tagDesc();
    // Description should be available for well-known tags
    EXPECT_FALSE(desc.empty());
}

// Test defaultTypeId returns a valid type
TEST_F(ExifKeyTest_1335, DefaultTypeIdForKnownTag_1335) {
    Exiv2::ExifKey key("Exif.Photo.DateTimeOriginal");
    Exiv2::TypeId typeId = key.defaultTypeId();
    // DateTimeOriginal is ASCII type
    EXPECT_EQ(typeId, Exiv2::asciiString);
}

// Test with Image group tag
TEST_F(ExifKeyTest_1335, ImageGroupTag_1335) {
    Exiv2::ExifKey key("Exif.Image.Make");
    EXPECT_EQ(key.key(), "Exif.Image.Make");
    EXPECT_EQ(key.groupName(), "Image");
    EXPECT_EQ(key.tagName(), "Make");
    EXPECT_STREQ(key.familyName(), "Exif");
}

// Test with GPSInfo group tag
TEST_F(ExifKeyTest_1335, GPSInfoGroupTag_1335) {
    Exiv2::ExifKey key("Exif.GPSInfo.GPSLatitude");
    EXPECT_EQ(key.groupName(), "GPSInfo");
    EXPECT_EQ(key.tagName(), "GPSLatitude");
}

// Test invalid key string throws
TEST_F(ExifKeyTest_1335, InvalidKeyStringThrows_1335) {
    EXPECT_THROW(Exiv2::ExifKey key("Invalid.Key.String"), Exiv2::Error);
}

// Test empty key string throws
TEST_F(ExifKeyTest_1335, EmptyKeyStringThrows_1335) {
    EXPECT_THROW(Exiv2::ExifKey key(""), Exiv2::Error);
}

// Test key string with wrong family throws
TEST_F(ExifKeyTest_1335, WrongFamilyNameThrows_1335) {
    EXPECT_THROW(Exiv2::ExifKey key("Iptc.Photo.DateTimeOriginal"), Exiv2::Error);
}

// Test ifdId returns a valid IfdId
TEST_F(ExifKeyTest_1335, IfdIdReturnsValidValue_1335) {
    Exiv2::ExifKey key("Exif.Photo.DateTimeOriginal");
    Exiv2::IfdId ifdId = key.ifdId();
    EXPECT_NE(ifdId, Exiv2::IfdId::ifdIdNotSet);
}

// Test constructing from tag number with Image group
TEST_F(ExifKeyTest_1335, ConstructFromTagNumberImageGroup_1335) {
    // Make tag = 0x010f
    Exiv2::ExifKey key(0x010f, "Image");
    EXPECT_EQ(key.tagName(), "Make");
    EXPECT_EQ(key.groupName(), "Image");
}

// Test setIdx can be called multiple times
TEST_F(ExifKeyTest_1335, SetIdxMultipleTimes_1335) {
    Exiv2::ExifKey key("Exif.Photo.DateTimeOriginal");
    key.setIdx(1);
    EXPECT_EQ(key.idx(), 1);
    key.setIdx(2);
    EXPECT_EQ(key.idx(), 2);
    key.setIdx(1000);
    EXPECT_EQ(key.idx(), 1000);
}

// Test that copy doesn't affect original when modifying copy
TEST_F(ExifKeyTest_1335, CopyDoesNotAffectOriginal_1335) {
    Exiv2::ExifKey original("Exif.Photo.DateTimeOriginal");
    original.setIdx(10);
    Exiv2::ExifKey copy(original);
    copy.setIdx(20);
    EXPECT_EQ(original.idx(), 10);
    EXPECT_EQ(copy.idx(), 20);
}

// Test self-assignment
TEST_F(ExifKeyTest_1335, SelfAssignment_1335) {
    Exiv2::ExifKey key("Exif.Photo.DateTimeOriginal");
    key.setIdx(15);
    key = key;
    EXPECT_EQ(key.key(), "Exif.Photo.DateTimeOriginal");
    EXPECT_EQ(key.idx(), 15);
}

// Test with large idx value
TEST_F(ExifKeyTest_1335, LargeIdxValue_1335) {
    Exiv2::ExifKey key("Exif.Photo.DateTimeOriginal");
    key.setIdx(INT32_MAX);
    EXPECT_EQ(key.idx(), INT32_MAX);
}

// Test with minimum idx value
TEST_F(ExifKeyTest_1335, MinIdxValue_1335) {
    Exiv2::ExifKey key("Exif.Photo.DateTimeOriginal");
    key.setIdx(INT32_MIN);
    EXPECT_EQ(key.idx(), INT32_MIN);
}

}  // namespace

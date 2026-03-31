#include <gtest/gtest.h>
#include <exiv2/tags.hpp>
#include <exiv2/exif.hpp>
#include <string>

namespace {

// Test fixture for ExifKey tests
class ExifKeyTest_1346 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test construction from a string key
TEST_F(ExifKeyTest_1346, ConstructFromString_1346) {
    ASSERT_NO_THROW(Exiv2::ExifKey key("Exif.Image.Make"));
}

// Test construction from tag and group name
TEST_F(ExifKeyTest_1346, ConstructFromTagAndGroup_1346) {
    ASSERT_NO_THROW(Exiv2::ExifKey key(0x010f, "Image"));
}

// Test key() returns expected string
TEST_F(ExifKeyTest_1346, KeyReturnsCorrectString_1346) {
    Exiv2::ExifKey key("Exif.Image.Make");
    EXPECT_EQ(key.key(), "Exif.Image.Make");
}

// Test familyName() returns "Exif"
TEST_F(ExifKeyTest_1346, FamilyNameReturnsExif_1346) {
    Exiv2::ExifKey key("Exif.Image.Make");
    std::string familyName = key.familyName();
    EXPECT_EQ(familyName, "Exif");
}

// Test groupName() returns correct group
TEST_F(ExifKeyTest_1346, GroupNameReturnsImage_1346) {
    Exiv2::ExifKey key("Exif.Image.Make");
    EXPECT_EQ(key.groupName(), "Image");
}

// Test tagName() returns correct tag name
TEST_F(ExifKeyTest_1346, TagNameReturnsMake_1346) {
    Exiv2::ExifKey key("Exif.Image.Make");
    EXPECT_EQ(key.tagName(), "Make");
}

// Test tag() returns correct tag number
TEST_F(ExifKeyTest_1346, TagReturnsCorrectValue_1346) {
    Exiv2::ExifKey key("Exif.Image.Make");
    EXPECT_EQ(key.tag(), 0x010f);
}

// Test idx() default value
TEST_F(ExifKeyTest_1346, IdxDefaultIsZero_1346) {
    Exiv2::ExifKey key("Exif.Image.Make");
    EXPECT_EQ(key.idx(), 0);
}

// Test setIdx and idx
TEST_F(ExifKeyTest_1346, SetIdxAndGetIdx_1346) {
    Exiv2::ExifKey key("Exif.Image.Make");
    key.setIdx(42);
    EXPECT_EQ(key.idx(), 42);
}

// Test setIdx with negative value
TEST_F(ExifKeyTest_1346, SetIdxNegativeValue_1346) {
    Exiv2::ExifKey key("Exif.Image.Make");
    key.setIdx(-1);
    EXPECT_EQ(key.idx(), -1);
}

// Test setIdx with zero
TEST_F(ExifKeyTest_1346, SetIdxZero_1346) {
    Exiv2::ExifKey key("Exif.Image.Make");
    key.setIdx(100);
    EXPECT_EQ(key.idx(), 100);
    key.setIdx(0);
    EXPECT_EQ(key.idx(), 0);
}

// Test copy constructor
TEST_F(ExifKeyTest_1346, CopyConstructor_1346) {
    Exiv2::ExifKey key1("Exif.Image.Make");
    key1.setIdx(7);
    Exiv2::ExifKey key2(key1);
    EXPECT_EQ(key2.key(), key1.key());
    EXPECT_EQ(key2.tag(), key1.tag());
    EXPECT_EQ(key2.groupName(), key1.groupName());
    EXPECT_EQ(key2.idx(), 7);
}

// Test copy assignment
TEST_F(ExifKeyTest_1346, CopyAssignment_1346) {
    Exiv2::ExifKey key1("Exif.Image.Make");
    key1.setIdx(5);
    Exiv2::ExifKey key2("Exif.Image.Model");
    key2 = key1;
    EXPECT_EQ(key2.key(), "Exif.Image.Make");
    EXPECT_EQ(key2.idx(), 5);
}

// Test clone
TEST_F(ExifKeyTest_1346, CloneReturnsCorrectCopy_1346) {
    Exiv2::ExifKey key("Exif.Image.Make");
    key.setIdx(10);
    auto cloned = key.clone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->key(), "Exif.Image.Make");
    EXPECT_EQ(cloned->tag(), 0x010f);
    EXPECT_EQ(cloned->idx(), 10);
}

// Test tagLabel is not empty for known tags
TEST_F(ExifKeyTest_1346, TagLabelNotEmpty_1346) {
    Exiv2::ExifKey key("Exif.Image.Make");
    std::string label = key.tagLabel();
    EXPECT_FALSE(label.empty());
}

// Test construction from tag number and group
TEST_F(ExifKeyTest_1346, ConstructFromTagNumber_1346) {
    Exiv2::ExifKey key(0x0110, "Image");
    EXPECT_EQ(key.tag(), 0x0110);
    EXPECT_EQ(key.groupName(), "Image");
    EXPECT_EQ(key.tagName(), "Model");
}

// Test construction with invalid key string throws
TEST_F(ExifKeyTest_1346, InvalidKeyStringThrows_1346) {
    EXPECT_THROW(Exiv2::ExifKey key("InvalidKey"), Exiv2::Error);
}

// Test construction with wrong family name throws
TEST_F(ExifKeyTest_1346, WrongFamilyNameThrows_1346) {
    EXPECT_THROW(Exiv2::ExifKey key("Iptc.Image.Make"), Exiv2::Error);
}

// Test defaultTypeId returns a valid type
TEST_F(ExifKeyTest_1346, DefaultTypeIdForMake_1346) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::TypeId typeId = key.defaultTypeId();
    EXPECT_EQ(typeId, Exiv2::asciiString);
}

// Test ifdId returns a valid IfdId
TEST_F(ExifKeyTest_1346, IfdIdReturnsValid_1346) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::IfdId ifdId = key.ifdId();
    EXPECT_NE(ifdId, Exiv2::IfdId::ifdIdNotSet);
}

// Test key for Photo group
TEST_F(ExifKeyTest_1346, PhotoGroupKey_1346) {
    Exiv2::ExifKey key("Exif.Photo.ExposureTime");
    EXPECT_EQ(key.key(), "Exif.Photo.ExposureTime");
    EXPECT_EQ(key.familyName(), std::string("Exif"));
    EXPECT_EQ(key.groupName(), "Photo");
    EXPECT_EQ(key.tagName(), "ExposureTime");
}

// Test that copy does not share state (deep copy)
TEST_F(ExifKeyTest_1346, DeepCopyIndependence_1346) {
    Exiv2::ExifKey key1("Exif.Image.Make");
    key1.setIdx(3);
    Exiv2::ExifKey key2(key1);
    key2.setIdx(99);
    EXPECT_EQ(key1.idx(), 3);
    EXPECT_EQ(key2.idx(), 99);
}

// Test setIdx with large value
TEST_F(ExifKeyTest_1346, SetIdxLargeValue_1346) {
    Exiv2::ExifKey key("Exif.Image.Make");
    key.setIdx(999999);
    EXPECT_EQ(key.idx(), 999999);
}

// Test tagDesc returns something for a known tag
TEST_F(ExifKeyTest_1346, TagDescForKnownTag_1346) {
    Exiv2::ExifKey key("Exif.Image.Make");
    std::string desc = key.tagDesc();
    // Description should exist for a well-known tag
    EXPECT_FALSE(desc.empty());
}

// Test construction with GPSInfo group
TEST_F(ExifKeyTest_1346, GPSInfoGroup_1346) {
    ASSERT_NO_THROW(Exiv2::ExifKey key("Exif.GPSInfo.GPSLatitude"));
    Exiv2::ExifKey key("Exif.GPSInfo.GPSLatitude");
    EXPECT_EQ(key.groupName(), "GPSInfo");
}

// Test self-assignment
TEST_F(ExifKeyTest_1346, SelfAssignment_1346) {
    Exiv2::ExifKey key("Exif.Image.Make");
    key.setIdx(15);
    key = key;
    EXPECT_EQ(key.key(), "Exif.Image.Make");
    EXPECT_EQ(key.idx(), 15);
}

}  // namespace

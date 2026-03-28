#include <gtest/gtest.h>
#include <exiv2/tags.hpp>
#include <exiv2/exif.hpp>
#include <string>

namespace {

// Test fixture for ExifKey tests
class ExifKeyTest_1344 : public ::testing::Test {
protected:
    void SetUp() override {
    }
    void TearDown() override {
    }
};

// Test construction from string key
TEST_F(ExifKeyTest_1344, ConstructFromString_1344) {
    ASSERT_NO_THROW(Exiv2::ExifKey key("Exif.Image.Make"));
}

// Test construction from tag number and group name
TEST_F(ExifKeyTest_1344, ConstructFromTagAndGroup_1344) {
    ASSERT_NO_THROW(Exiv2::ExifKey key(0x010f, "Image"));
}

// Test key() returns correct string representation
TEST_F(ExifKeyTest_1344, KeyReturnsCorrectString_1344) {
    Exiv2::ExifKey key("Exif.Image.Make");
    EXPECT_EQ(key.key(), "Exif.Image.Make");
}

// Test familyName() returns "Exif"
TEST_F(ExifKeyTest_1344, FamilyNameReturnsExif_1344) {
    Exiv2::ExifKey key("Exif.Image.Make");
    EXPECT_STREQ(key.familyName(), "Exif");
}

// Test groupName() returns correct group
TEST_F(ExifKeyTest_1344, GroupNameReturnsCorrectGroup_1344) {
    Exiv2::ExifKey key("Exif.Image.Make");
    EXPECT_EQ(key.groupName(), "Image");
}

// Test tagName() returns correct tag name
TEST_F(ExifKeyTest_1344, TagNameReturnsCorrectName_1344) {
    Exiv2::ExifKey key("Exif.Image.Make");
    EXPECT_EQ(key.tagName(), "Make");
}

// Test tag() returns correct tag number
TEST_F(ExifKeyTest_1344, TagReturnsCorrectNumber_1344) {
    Exiv2::ExifKey key("Exif.Image.Make");
    EXPECT_EQ(key.tag(), 0x010f);
}

// Test construction from tag number and group yields correct key string
TEST_F(ExifKeyTest_1344, ConstructFromTagNumberYieldsCorrectKey_1344) {
    Exiv2::ExifKey key(0x010f, "Image");
    EXPECT_EQ(key.key(), "Exif.Image.Make");
    EXPECT_EQ(key.tag(), 0x010f);
    EXPECT_EQ(key.groupName(), "Image");
    EXPECT_EQ(key.tagName(), "Make");
}

// Test copy constructor
TEST_F(ExifKeyTest_1344, CopyConstructor_1344) {
    Exiv2::ExifKey original("Exif.Image.Make");
    Exiv2::ExifKey copy(original);
    EXPECT_EQ(copy.key(), original.key());
    EXPECT_EQ(copy.tag(), original.tag());
    EXPECT_EQ(copy.groupName(), original.groupName());
    EXPECT_EQ(copy.tagName(), original.tagName());
}

// Test assignment operator
TEST_F(ExifKeyTest_1344, AssignmentOperator_1344) {
    Exiv2::ExifKey key1("Exif.Image.Make");
    Exiv2::ExifKey key2("Exif.Image.Model");
    key2 = key1;
    EXPECT_EQ(key2.key(), "Exif.Image.Make");
    EXPECT_EQ(key2.tag(), key1.tag());
}

// Test clone() returns a valid copy
TEST_F(ExifKeyTest_1344, CloneReturnsValidCopy_1344) {
    Exiv2::ExifKey key("Exif.Image.Make");
    auto cloned = key.clone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->key(), key.key());
    EXPECT_EQ(cloned->tag(), key.tag());
    EXPECT_EQ(cloned->groupName(), key.groupName());
    EXPECT_EQ(cloned->tagName(), key.tagName());
    EXPECT_EQ(cloned->familyName(), std::string("Exif"));
}

// Test tagLabel() returns a non-empty string for known tags
TEST_F(ExifKeyTest_1344, TagLabelForKnownTag_1344) {
    Exiv2::ExifKey key("Exif.Image.Make");
    std::string label = key.tagLabel();
    EXPECT_FALSE(label.empty());
}

// Test defaultTypeId() for a known tag
TEST_F(ExifKeyTest_1344, DefaultTypeIdForMake_1344) {
    Exiv2::ExifKey key("Exif.Image.Make");
    // Make tag is ASCII type
    EXPECT_EQ(key.defaultTypeId(), Exiv2::asciiString);
}

// Test idx() and setIdx()
TEST_F(ExifKeyTest_1344, SetAndGetIdx_1344) {
    Exiv2::ExifKey key("Exif.Image.Make");
    key.setIdx(42);
    EXPECT_EQ(key.idx(), 42);
}

// Test idx() default value
TEST_F(ExifKeyTest_1344, DefaultIdxIsZero_1344) {
    Exiv2::ExifKey key("Exif.Image.Make");
    EXPECT_EQ(key.idx(), 0);
}

// Test construction with invalid key string throws
TEST_F(ExifKeyTest_1344, InvalidKeyStringThrows_1344) {
    EXPECT_THROW(Exiv2::ExifKey key("Invalid.Key.String"), Exiv2::Error);
}

// Test construction with empty string throws
TEST_F(ExifKeyTest_1344, EmptyStringThrows_1344) {
    EXPECT_THROW(Exiv2::ExifKey key(""), Exiv2::Error);
}

// Test different Exif groups - Photo group
TEST_F(ExifKeyTest_1344, PhotoGroupKey_1344) {
    Exiv2::ExifKey key("Exif.Photo.ExposureTime");
    EXPECT_EQ(key.key(), "Exif.Photo.ExposureTime");
    EXPECT_EQ(key.groupName(), "Photo");
    EXPECT_EQ(key.tagName(), "ExposureTime");
    EXPECT_STREQ(key.familyName(), "Exif");
}

// Test ifdId() returns a valid IFD identifier
TEST_F(ExifKeyTest_1344, IfdIdReturnsValidId_1344) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::IfdId ifdId = key.ifdId();
    EXPECT_NE(ifdId, Exiv2::IfdId::ifdIdNotSet);
}

// Test tagDesc() for known tag
TEST_F(ExifKeyTest_1344, TagDescForKnownTag_1344) {
    Exiv2::ExifKey key("Exif.Image.Make");
    std::string desc = key.tagDesc();
    // Description should exist for a known tag
    EXPECT_FALSE(desc.empty());
}

// Test that clone is independent from original
TEST_F(ExifKeyTest_1344, CloneIsIndependent_1344) {
    Exiv2::ExifKey key("Exif.Image.Make");
    key.setIdx(10);
    auto cloned = key.clone();
    EXPECT_EQ(cloned->idx(), 10);
    key.setIdx(20);
    EXPECT_EQ(cloned->idx(), 10);  // Clone should not be affected
    EXPECT_EQ(key.idx(), 20);
}

// Test self-assignment
TEST_F(ExifKeyTest_1344, SelfAssignment_1344) {
    Exiv2::ExifKey key("Exif.Image.Make");
    key = key;
    EXPECT_EQ(key.key(), "Exif.Image.Make");
}

// Test construction with Model tag
TEST_F(ExifKeyTest_1344, ModelTag_1344) {
    Exiv2::ExifKey key("Exif.Image.Model");
    EXPECT_EQ(key.tag(), 0x0110);
    EXPECT_EQ(key.tagName(), "Model");
    EXPECT_EQ(key.defaultTypeId(), Exiv2::asciiString);
}

// Test construction with numeric tag (ImageWidth)
TEST_F(ExifKeyTest_1344, ImageWidthTag_1344) {
    Exiv2::ExifKey key("Exif.Image.ImageWidth");
    EXPECT_EQ(key.tag(), 0x0100);
    EXPECT_EQ(key.tagName(), "ImageWidth");
}

// Test setIdx with negative value
TEST_F(ExifKeyTest_1344, SetIdxNegativeValue_1344) {
    Exiv2::ExifKey key("Exif.Image.Make");
    key.setIdx(-1);
    EXPECT_EQ(key.idx(), -1);
}

// Test GPS group
TEST_F(ExifKeyTest_1344, GPSGroupKey_1344) {
    Exiv2::ExifKey key("Exif.GPSInfo.GPSLatitude");
    EXPECT_EQ(key.groupName(), "GPSInfo");
    EXPECT_EQ(key.tagName(), "GPSLatitude");
    EXPECT_STREQ(key.familyName(), "Exif");
}

// Test that copy constructed object has same idx
TEST_F(ExifKeyTest_1344, CopyConstructorPreservesIdx_1344) {
    Exiv2::ExifKey original("Exif.Image.Make");
    original.setIdx(55);
    Exiv2::ExifKey copy(original);
    EXPECT_EQ(copy.idx(), 55);
}

// Test assignment preserves idx
TEST_F(ExifKeyTest_1344, AssignmentPreservesIdx_1344) {
    Exiv2::ExifKey key1("Exif.Image.Make");
    key1.setIdx(77);
    Exiv2::ExifKey key2("Exif.Image.Model");
    key2 = key1;
    EXPECT_EQ(key2.idx(), 77);
}

}  // namespace

#include <gtest/gtest.h>
#include <exiv2/tags.hpp>
#include <exiv2/error.hpp>
#include <string>
#include <memory>

namespace {

class ExifKeyTest_1334 : public ::testing::Test {
protected:
    void SetUp() override {
    }
    void TearDown() override {
    }
};

// Test construction from a valid string key
TEST_F(ExifKeyTest_1334, ConstructFromValidStringKey_1334) {
    EXPECT_NO_THROW(Exiv2::ExifKey key("Exif.Photo.DateTimeOriginal"));
}

// Test construction from tag number and group name
TEST_F(ExifKeyTest_1334, ConstructFromTagAndGroupName_1334) {
    EXPECT_NO_THROW(Exiv2::ExifKey key(0x9003, "Photo"));
}

// Test that key() returns the expected string representation
TEST_F(ExifKeyTest_1334, KeyReturnsCorrectString_1334) {
    Exiv2::ExifKey key("Exif.Photo.DateTimeOriginal");
    std::string result = key.key();
    EXPECT_EQ(result, "Exif.Photo.DateTimeOriginal");
}

// Test familyName returns "Exif"
TEST_F(ExifKeyTest_1334, FamilyNameReturnsExif_1334) {
    Exiv2::ExifKey key("Exif.Photo.DateTimeOriginal");
    EXPECT_STREQ(key.familyName(), "Exif");
}

// Test groupName returns the correct group
TEST_F(ExifKeyTest_1334, GroupNameReturnsCorrectGroup_1334) {
    Exiv2::ExifKey key("Exif.Photo.DateTimeOriginal");
    EXPECT_EQ(key.groupName(), "Photo");
}

// Test tagName returns the correct tag name
TEST_F(ExifKeyTest_1334, TagNameReturnsCorrectName_1334) {
    Exiv2::ExifKey key("Exif.Photo.DateTimeOriginal");
    EXPECT_EQ(key.tagName(), "DateTimeOriginal");
}

// Test tag() returns the correct tag number
TEST_F(ExifKeyTest_1334, TagReturnsCorrectNumber_1334) {
    Exiv2::ExifKey key("Exif.Photo.DateTimeOriginal");
    EXPECT_EQ(key.tag(), 0x9003);
}

// Test construction from tag and group, then verify key string
TEST_F(ExifKeyTest_1334, ConstructFromTagGroupVerifyKey_1334) {
    Exiv2::ExifKey key(0x010f, "Image");
    EXPECT_EQ(key.key(), "Exif.Image.Make");
    EXPECT_EQ(key.tag(), 0x010f);
    EXPECT_EQ(key.groupName(), "Image");
}

// Test copy constructor
TEST_F(ExifKeyTest_1334, CopyConstructor_1334) {
    Exiv2::ExifKey original("Exif.Photo.DateTimeOriginal");
    Exiv2::ExifKey copy(original);
    EXPECT_EQ(copy.key(), original.key());
    EXPECT_EQ(copy.tag(), original.tag());
    EXPECT_EQ(copy.groupName(), original.groupName());
    EXPECT_EQ(copy.tagName(), original.tagName());
}

// Test copy assignment operator
TEST_F(ExifKeyTest_1334, CopyAssignmentOperator_1334) {
    Exiv2::ExifKey key1("Exif.Photo.DateTimeOriginal");
    Exiv2::ExifKey key2("Exif.Image.Make");
    key2 = key1;
    EXPECT_EQ(key2.key(), key1.key());
    EXPECT_EQ(key2.tag(), key1.tag());
    EXPECT_EQ(key2.groupName(), key1.groupName());
    EXPECT_EQ(key2.tagName(), key1.tagName());
}

// Test self-assignment
TEST_F(ExifKeyTest_1334, SelfAssignment_1334) {
    Exiv2::ExifKey key("Exif.Photo.DateTimeOriginal");
    std::string originalKey = key.key();
    key = key;
    EXPECT_EQ(key.key(), originalKey);
}

// Test clone produces an independent copy
TEST_F(ExifKeyTest_1334, CloneProducesIndependentCopy_1334) {
    Exiv2::ExifKey key("Exif.Photo.DateTimeOriginal");
    auto cloned = key.clone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->key(), key.key());
    EXPECT_EQ(cloned->tag(), key.tag());
    EXPECT_EQ(cloned->groupName(), key.groupName());
}

// Test idx default value is 0
TEST_F(ExifKeyTest_1334, IdxDefaultIsZero_1334) {
    Exiv2::ExifKey key("Exif.Photo.DateTimeOriginal");
    EXPECT_EQ(key.idx(), 0);
}

// Test setIdx and idx
TEST_F(ExifKeyTest_1334, SetIdxAndGetIdx_1334) {
    Exiv2::ExifKey key("Exif.Photo.DateTimeOriginal");
    key.setIdx(42);
    EXPECT_EQ(key.idx(), 42);
}

// Test setIdx with negative value
TEST_F(ExifKeyTest_1334, SetIdxNegativeValue_1334) {
    Exiv2::ExifKey key("Exif.Photo.DateTimeOriginal");
    key.setIdx(-1);
    EXPECT_EQ(key.idx(), -1);
}

// Test tagLabel returns a non-empty string for known tags
TEST_F(ExifKeyTest_1334, TagLabelForKnownTag_1334) {
    Exiv2::ExifKey key("Exif.Photo.DateTimeOriginal");
    std::string label = key.tagLabel();
    EXPECT_FALSE(label.empty());
}

// Test construction with invalid key string throws
TEST_F(ExifKeyTest_1334, InvalidKeyStringThrows_1334) {
    EXPECT_THROW(Exiv2::ExifKey key("Invalid.Key.String"), Exiv2::Error);
}

// Test construction with empty key string throws
TEST_F(ExifKeyTest_1334, EmptyKeyStringThrows_1334) {
    EXPECT_THROW(Exiv2::ExifKey key(""), Exiv2::Error);
}

// Test construction with wrong family name throws
TEST_F(ExifKeyTest_1334, WrongFamilyNameThrows_1334) {
    EXPECT_THROW(Exiv2::ExifKey key("Iptc.Photo.DateTimeOriginal"), Exiv2::Error);
}

// Test ifdId returns a valid IfdId for known tags
TEST_F(ExifKeyTest_1334, IfdIdForKnownTag_1334) {
    Exiv2::ExifKey key("Exif.Photo.DateTimeOriginal");
    Exiv2::IfdId id = key.ifdId();
    EXPECT_NE(id, Exiv2::IfdId::ifdIdNotSet);
}

// Test defaultTypeId for a known tag
TEST_F(ExifKeyTest_1334, DefaultTypeIdForKnownTag_1334) {
    Exiv2::ExifKey key("Exif.Photo.DateTimeOriginal");
    Exiv2::TypeId typeId = key.defaultTypeId();
    EXPECT_EQ(typeId, Exiv2::asciiString);
}

// Test different groups
TEST_F(ExifKeyTest_1334, ImageGroupKey_1334) {
    Exiv2::ExifKey key("Exif.Image.ImageWidth");
    EXPECT_EQ(key.groupName(), "Image");
    EXPECT_EQ(key.tagName(), "ImageWidth");
    EXPECT_STREQ(key.familyName(), "Exif");
}

// Test GPS group
TEST_F(ExifKeyTest_1334, GPSGroupKey_1334) {
    Exiv2::ExifKey key("Exif.GPSInfo.GPSLatitude");
    EXPECT_EQ(key.groupName(), "GPSInfo");
    EXPECT_EQ(key.tagName(), "GPSLatitude");
}

// Test copy assignment changes all properties
TEST_F(ExifKeyTest_1334, AssignmentChangesAllProperties_1334) {
    Exiv2::ExifKey key1("Exif.Photo.DateTimeOriginal");
    Exiv2::ExifKey key2("Exif.Image.Make");
    key1.setIdx(10);

    key2 = key1;
    EXPECT_EQ(key2.key(), "Exif.Photo.DateTimeOriginal");
    EXPECT_EQ(key2.tag(), 0x9003);
    EXPECT_EQ(key2.idx(), 10);
}

// Test that tagDesc returns some description for known tags
TEST_F(ExifKeyTest_1334, TagDescForKnownTag_1334) {
    Exiv2::ExifKey key("Exif.Photo.DateTimeOriginal");
    std::string desc = key.tagDesc();
    // The description might be empty or not, but should not throw
    // Just verify it doesn't crash
    SUCCEED();
}

// Test construction using tag number and group, verifying tagName
TEST_F(ExifKeyTest_1334, ConstructFromTagNumberImageWidth_1334) {
    Exiv2::ExifKey key(0x0100, "Image");
    EXPECT_EQ(key.tagName(), "ImageWidth");
    EXPECT_EQ(key.tag(), 0x0100);
}

// Test multiple setIdx calls
TEST_F(ExifKeyTest_1334, MultipleSetIdxCalls_1334) {
    Exiv2::ExifKey key("Exif.Photo.DateTimeOriginal");
    key.setIdx(1);
    EXPECT_EQ(key.idx(), 1);
    key.setIdx(100);
    EXPECT_EQ(key.idx(), 100);
    key.setIdx(0);
    EXPECT_EQ(key.idx(), 0);
}

// Test that clone preserves idx
TEST_F(ExifKeyTest_1334, ClonePreservesIdx_1334) {
    Exiv2::ExifKey key("Exif.Photo.DateTimeOriginal");
    key.setIdx(55);
    auto cloned = key.clone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->idx(), 55);
}

// Test that modifying clone doesn't affect original
TEST_F(ExifKeyTest_1334, CloneIsIndependent_1334) {
    Exiv2::ExifKey key("Exif.Photo.DateTimeOriginal");
    key.setIdx(10);
    auto cloned = key.clone();
    cloned->setIdx(20);
    EXPECT_EQ(key.idx(), 10);
    EXPECT_EQ(cloned->idx(), 20);
}

// Test modifying assigned copy doesn't affect original
TEST_F(ExifKeyTest_1334, AssignedCopyIsIndependent_1334) {
    Exiv2::ExifKey key1("Exif.Photo.DateTimeOriginal");
    Exiv2::ExifKey key2("Exif.Image.Make");
    key2 = key1;
    key2.setIdx(99);
    EXPECT_EQ(key1.idx(), 0);
    EXPECT_EQ(key2.idx(), 99);
}

} // namespace

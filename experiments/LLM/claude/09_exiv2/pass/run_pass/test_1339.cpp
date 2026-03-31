#include <gtest/gtest.h>
#include <exiv2/tags.hpp>
#include <exiv2/error.hpp>
#include <string>

namespace {

class ExifKeyTest_1339 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test construction from a well-known string key
TEST_F(ExifKeyTest_1339, ConstructFromStringKey_1339) {
    ASSERT_NO_THROW(Exiv2::ExifKey key("Exif.Image.Make"));
}

// Test tagName returns expected value for a known tag
TEST_F(ExifKeyTest_1339, TagNameForKnownTag_1339) {
    Exiv2::ExifKey key("Exif.Image.Make");
    EXPECT_EQ(key.tagName(), "Make");
}

// Test key() returns the full key string
TEST_F(ExifKeyTest_1339, KeyReturnsFullString_1339) {
    Exiv2::ExifKey key("Exif.Image.Make");
    EXPECT_EQ(key.key(), "Exif.Image.Make");
}

// Test familyName returns "Exif"
TEST_F(ExifKeyTest_1339, FamilyNameIsExif_1339) {
    Exiv2::ExifKey key("Exif.Image.Make");
    EXPECT_STREQ(key.familyName(), "Exif");
}

// Test groupName returns the expected group
TEST_F(ExifKeyTest_1339, GroupNameReturnsCorrectGroup_1339) {
    Exiv2::ExifKey key("Exif.Image.Make");
    EXPECT_EQ(key.groupName(), "Image");
}

// Test tag() returns the correct tag number for Make (0x010f)
TEST_F(ExifKeyTest_1339, TagReturnsCorrectNumber_1339) {
    Exiv2::ExifKey key("Exif.Image.Make");
    EXPECT_EQ(key.tag(), 0x010f);
}

// Test tagLabel returns a non-empty label for known tags
TEST_F(ExifKeyTest_1339, TagLabelIsNonEmpty_1339) {
    Exiv2::ExifKey key("Exif.Image.Make");
    EXPECT_FALSE(key.tagLabel().empty());
}

// Test tagDesc returns a description (may or may not be empty, but shouldn't throw)
TEST_F(ExifKeyTest_1339, TagDescDoesNotThrow_1339) {
    Exiv2::ExifKey key("Exif.Image.Make");
    ASSERT_NO_THROW(key.tagDesc());
}

// Test construction from tag number and group name
TEST_F(ExifKeyTest_1339, ConstructFromTagAndGroup_1339) {
    ASSERT_NO_THROW(Exiv2::ExifKey key(0x010f, "Image"));
    Exiv2::ExifKey key(0x010f, "Image");
    EXPECT_EQ(key.tagName(), "Make");
    EXPECT_EQ(key.tag(), 0x010f);
    EXPECT_EQ(key.groupName(), "Image");
}

// Test copy constructor
TEST_F(ExifKeyTest_1339, CopyConstructor_1339) {
    Exiv2::ExifKey original("Exif.Image.Model");
    Exiv2::ExifKey copy(original);
    EXPECT_EQ(copy.key(), original.key());
    EXPECT_EQ(copy.tagName(), original.tagName());
    EXPECT_EQ(copy.tag(), original.tag());
    EXPECT_EQ(copy.groupName(), original.groupName());
}

// Test assignment operator
TEST_F(ExifKeyTest_1339, AssignmentOperator_1339) {
    Exiv2::ExifKey key1("Exif.Image.Make");
    Exiv2::ExifKey key2("Exif.Image.Model");
    key2 = key1;
    EXPECT_EQ(key2.key(), "Exif.Image.Make");
    EXPECT_EQ(key2.tagName(), "Make");
}

// Test clone
TEST_F(ExifKeyTest_1339, CloneProducesSameKey_1339) {
    Exiv2::ExifKey key("Exif.Image.Make");
    auto cloned = key.clone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->key(), key.key());
    EXPECT_EQ(cloned->tagName(), key.tagName());
    EXPECT_EQ(cloned->tag(), key.tag());
}

// Test idx default value and setIdx
TEST_F(ExifKeyTest_1339, IdxDefaultAndSet_1339) {
    Exiv2::ExifKey key("Exif.Image.Make");
    EXPECT_EQ(key.idx(), 0);
    key.setIdx(42);
    EXPECT_EQ(key.idx(), 42);
}

// Test setIdx with negative value
TEST_F(ExifKeyTest_1339, SetIdxNegativeValue_1339) {
    Exiv2::ExifKey key("Exif.Image.Make");
    key.setIdx(-5);
    EXPECT_EQ(key.idx(), -5);
}

// Test construction with invalid key string throws
TEST_F(ExifKeyTest_1339, InvalidKeyStringThrows_1339) {
    EXPECT_THROW(Exiv2::ExifKey key("InvalidKey"), Exiv2::Error);
}

// Test construction with wrong family name throws
TEST_F(ExifKeyTest_1339, WrongFamilyNameThrows_1339) {
    EXPECT_THROW(Exiv2::ExifKey key("Iptc.Image.Make"), Exiv2::Error);
}

// Test different Exif groups - Photo group
TEST_F(ExifKeyTest_1339, PhotoGroupTag_1339) {
    Exiv2::ExifKey key("Exif.Photo.ExposureTime");
    EXPECT_EQ(key.groupName(), "Photo");
    EXPECT_EQ(key.tagName(), "ExposureTime");
    EXPECT_STREQ(key.familyName(), "Exif");
}

// Test defaultTypeId returns a valid type
TEST_F(ExifKeyTest_1339, DefaultTypeIdForMake_1339) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::TypeId typeId = key.defaultTypeId();
    EXPECT_EQ(typeId, Exiv2::asciiString);
}

// Test ifdId returns a valid IfdId
TEST_F(ExifKeyTest_1339, IfdIdIsValid_1339) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::IfdId id = key.ifdId();
    EXPECT_NE(id, Exiv2::IfdId::ifdIdNotSet);
}

// Test construction with tag number and group for Photo
TEST_F(ExifKeyTest_1339, ConstructFromTagAndPhotoGroup_1339) {
    // ExposureTime tag = 0x829a
    Exiv2::ExifKey key(0x829a, "Photo");
    EXPECT_EQ(key.tagName(), "ExposureTime");
    EXPECT_EQ(key.groupName(), "Photo");
}

// Test Model tag
TEST_F(ExifKeyTest_1339, ModelTag_1339) {
    Exiv2::ExifKey key("Exif.Image.Model");
    EXPECT_EQ(key.tagName(), "Model");
    EXPECT_EQ(key.tag(), 0x0110);
}

// Test Orientation tag
TEST_F(ExifKeyTest_1339, OrientationTag_1339) {
    Exiv2::ExifKey key("Exif.Image.Orientation");
    EXPECT_EQ(key.tagName(), "Orientation");
    EXPECT_EQ(key.tag(), 0x0112);
}

// Test that clone is independent of original
TEST_F(ExifKeyTest_1339, CloneIsIndependent_1339) {
    Exiv2::ExifKey key("Exif.Image.Make");
    key.setIdx(10);
    auto cloned = key.clone();
    cloned->setIdx(20);
    EXPECT_EQ(key.idx(), 10);
    EXPECT_EQ(cloned->idx(), 20);
}

// Test copy constructor preserves idx
TEST_F(ExifKeyTest_1339, CopyConstructorPreservesIdx_1339) {
    Exiv2::ExifKey key("Exif.Image.Make");
    key.setIdx(77);
    Exiv2::ExifKey copy(key);
    EXPECT_EQ(copy.idx(), 77);
}

// Test assignment operator preserves idx
TEST_F(ExifKeyTest_1339, AssignmentPreservesIdx_1339) {
    Exiv2::ExifKey key1("Exif.Image.Make");
    key1.setIdx(33);
    Exiv2::ExifKey key2("Exif.Image.Model");
    key2 = key1;
    EXPECT_EQ(key2.idx(), 33);
}

// Test unknown tag by number
TEST_F(ExifKeyTest_1339, UnknownTagByNumber_1339) {
    // Use a tag number unlikely to be defined in Image group
    Exiv2::ExifKey key(0xffff, "Image");
    // Should still be constructable; tagName might be a hex representation
    EXPECT_FALSE(key.tagName().empty());
}

// Test empty key string throws
TEST_F(ExifKeyTest_1339, EmptyStringThrows_1339) {
    EXPECT_THROW(Exiv2::ExifKey key(""), Exiv2::Error);
}

// Test GPS group
TEST_F(ExifKeyTest_1339, GPSGroupTag_1339) {
    Exiv2::ExifKey key("Exif.GPSInfo.GPSLatitude");
    EXPECT_EQ(key.groupName(), "GPSInfo");
    EXPECT_EQ(key.tagName(), "GPSLatitude");
}

// Test self-assignment
TEST_F(ExifKeyTest_1339, SelfAssignment_1339) {
    Exiv2::ExifKey key("Exif.Image.Make");
    key.setIdx(55);
    key = key;
    EXPECT_EQ(key.key(), "Exif.Image.Make");
    EXPECT_EQ(key.idx(), 55);
}

}  // namespace

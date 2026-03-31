#include <gtest/gtest.h>
#include <exiv2/tags.hpp>
#include <exiv2/exif.hpp>
#include <string>

namespace {

class ExifKeyTest_1340 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test construction from a well-known string key
TEST_F(ExifKeyTest_1340, ConstructFromStringKey_1340) {
    EXPECT_NO_THROW(Exiv2::ExifKey key("Exif.Image.Make"));
}

// Test that key() returns the expected string for a known tag
TEST_F(ExifKeyTest_1340, KeyReturnsExpectedString_1340) {
    Exiv2::ExifKey key("Exif.Image.Make");
    EXPECT_EQ(key.key(), "Exif.Image.Make");
}

// Test familyName returns "Exif"
TEST_F(ExifKeyTest_1340, FamilyNameIsExif_1340) {
    Exiv2::ExifKey key("Exif.Image.Make");
    std::string familyName(key.familyName());
    EXPECT_EQ(familyName, "Exif");
}

// Test groupName returns expected group
TEST_F(ExifKeyTest_1340, GroupNameReturnsImage_1340) {
    Exiv2::ExifKey key("Exif.Image.Make");
    EXPECT_EQ(key.groupName(), "Image");
}

// Test tagName returns expected tag name
TEST_F(ExifKeyTest_1340, TagNameReturnsMake_1340) {
    Exiv2::ExifKey key("Exif.Image.Make");
    EXPECT_EQ(key.tagName(), "Make");
}

// Test tag() returns the expected tag number for Make (0x010f)
TEST_F(ExifKeyTest_1340, TagReturnsExpectedNumber_1340) {
    Exiv2::ExifKey key("Exif.Image.Make");
    EXPECT_EQ(key.tag(), 0x010f);
}

// Test tagLabel returns a non-empty label for a known tag
TEST_F(ExifKeyTest_1340, TagLabelIsNonEmptyForKnownTag_1340) {
    Exiv2::ExifKey key("Exif.Image.Make");
    std::string label = key.tagLabel();
    EXPECT_FALSE(label.empty());
}

// Test tagDesc returns a description (may or may not be empty depending on tag)
TEST_F(ExifKeyTest_1340, TagDescForKnownTag_1340) {
    Exiv2::ExifKey key("Exif.Image.Make");
    // Just ensure it doesn't throw
    std::string desc = key.tagDesc();
    // desc could be empty or non-empty, just verify no crash
    SUCCEED();
}

// Test construction from tag number and group name
TEST_F(ExifKeyTest_1340, ConstructFromTagAndGroup_1340) {
    Exiv2::ExifKey key(0x010f, "Image");
    EXPECT_EQ(key.key(), "Exif.Image.Make");
    EXPECT_EQ(key.tag(), 0x010f);
    EXPECT_EQ(key.tagName(), "Make");
}

// Test copy constructor
TEST_F(ExifKeyTest_1340, CopyConstructor_1340) {
    Exiv2::ExifKey key1("Exif.Image.Make");
    Exiv2::ExifKey key2(key1);
    EXPECT_EQ(key1.key(), key2.key());
    EXPECT_EQ(key1.tag(), key2.tag());
    EXPECT_EQ(key1.tagName(), key2.tagName());
    EXPECT_EQ(key1.groupName(), key2.groupName());
}

// Test assignment operator
TEST_F(ExifKeyTest_1340, AssignmentOperator_1340) {
    Exiv2::ExifKey key1("Exif.Image.Make");
    Exiv2::ExifKey key2("Exif.Image.Model");
    key2 = key1;
    EXPECT_EQ(key1.key(), key2.key());
    EXPECT_EQ(key1.tag(), key2.tag());
}

// Test clone
TEST_F(ExifKeyTest_1340, CloneProducesCopy_1340) {
    Exiv2::ExifKey key("Exif.Image.Make");
    auto cloned = key.clone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(key.key(), cloned->key());
    EXPECT_EQ(key.tag(), cloned->tag());
    EXPECT_EQ(key.tagName(), cloned->tagName());
}

// Test defaultTypeId for a known tag
TEST_F(ExifKeyTest_1340, DefaultTypeIdForMake_1340) {
    Exiv2::ExifKey key("Exif.Image.Make");
    // Make is an ASCII string type
    EXPECT_EQ(key.defaultTypeId(), Exiv2::asciiString);
}

// Test idx default and setIdx
TEST_F(ExifKeyTest_1340, IdxDefaultIsZero_1340) {
    Exiv2::ExifKey key("Exif.Image.Make");
    EXPECT_EQ(key.idx(), 0);
}

TEST_F(ExifKeyTest_1340, SetIdxChangesIdx_1340) {
    Exiv2::ExifKey key("Exif.Image.Make");
    key.setIdx(42);
    EXPECT_EQ(key.idx(), 42);
}

// Test construction with invalid key string throws
TEST_F(ExifKeyTest_1340, InvalidKeyStringThrows_1340) {
    EXPECT_THROW(Exiv2::ExifKey key("InvalidKey"), Exiv2::Error);
}

// Test construction with empty string throws
TEST_F(ExifKeyTest_1340, EmptyKeyStringThrows_1340) {
    EXPECT_THROW(Exiv2::ExifKey key(""), Exiv2::Error);
}

// Test another known tag: Exif.Photo.ExposureTime
TEST_F(ExifKeyTest_1340, ExposureTimeTag_1340) {
    Exiv2::ExifKey key("Exif.Photo.ExposureTime");
    EXPECT_EQ(key.key(), "Exif.Photo.ExposureTime");
    EXPECT_EQ(key.groupName(), "Photo");
    EXPECT_EQ(key.tagName(), "ExposureTime");
    EXPECT_EQ(key.tag(), 0x829a);
    EXPECT_FALSE(key.tagLabel().empty());
}

// Test tag from Exif.Image.Model
TEST_F(ExifKeyTest_1340, ModelTag_1340) {
    Exiv2::ExifKey key("Exif.Image.Model");
    EXPECT_EQ(key.tag(), 0x0110);
    EXPECT_EQ(key.tagName(), "Model");
    EXPECT_EQ(key.groupName(), "Image");
}

// Test construction from tag number and group for Photo group
TEST_F(ExifKeyTest_1340, ConstructFromTagNumberPhotoGroup_1340) {
    // ExposureTime tag = 0x829a in Photo group
    Exiv2::ExifKey key(0x829a, "Photo");
    EXPECT_EQ(key.tagName(), "ExposureTime");
    EXPECT_EQ(key.groupName(), "Photo");
}

// Test tagLabel for tag created from tag+group
TEST_F(ExifKeyTest_1340, TagLabelFromTagAndGroup_1340) {
    Exiv2::ExifKey key(0x010f, "Image");
    std::string label = key.tagLabel();
    EXPECT_FALSE(label.empty());
}

// Test ifdId returns a valid IfdId
TEST_F(ExifKeyTest_1340, IfdIdForImageGroup_1340) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::IfdId ifdId = key.ifdId();
    // Should not be ifdIdNotSet for a valid tag
    EXPECT_NE(ifdId, Exiv2::IfdId::ifdIdNotSet);
}

// Test with a partially-known key that has only group prefix
TEST_F(ExifKeyTest_1340, InvalidGroupThrows_1340) {
    EXPECT_THROW(Exiv2::ExifKey key("Exif.NonExistentGroup.SomeTag"), Exiv2::Error);
}

// Test multiple setIdx calls
TEST_F(ExifKeyTest_1340, MultipleSetIdx_1340) {
    Exiv2::ExifKey key("Exif.Image.Make");
    key.setIdx(10);
    EXPECT_EQ(key.idx(), 10);
    key.setIdx(99);
    EXPECT_EQ(key.idx(), 99);
    key.setIdx(0);
    EXPECT_EQ(key.idx(), 0);
}

// Test that cloned key has independent idx
TEST_F(ExifKeyTest_1340, ClonedKeyHasIndependentIdx_1340) {
    Exiv2::ExifKey key("Exif.Image.Make");
    key.setIdx(55);
    auto cloned = key.clone();
    EXPECT_EQ(cloned->idx(), 55);
    key.setIdx(100);
    EXPECT_EQ(cloned->idx(), 55);
}

// Test self-assignment
TEST_F(ExifKeyTest_1340, SelfAssignment_1340) {
    Exiv2::ExifKey key("Exif.Image.Make");
    key = key;
    EXPECT_EQ(key.key(), "Exif.Image.Make");
    EXPECT_EQ(key.tag(), 0x010f);
}

// Test GPS tags
TEST_F(ExifKeyTest_1340, GPSTag_1340) {
    Exiv2::ExifKey key("Exif.GPSInfo.GPSLatitude");
    EXPECT_EQ(key.groupName(), "GPSInfo");
    EXPECT_EQ(key.tagName(), "GPSLatitude");
    EXPECT_FALSE(key.tagLabel().empty());
}

// Test an unknown/hex tag in a known group
TEST_F(ExifKeyTest_1340, UnknownTagInKnownGroup_1340) {
    // Construct with a tag number that is unlikely to be defined
    Exiv2::ExifKey key(0xfffe, "Image");
    // Should still be constructable, tagName might be hex representation
    EXPECT_EQ(key.groupName(), "Image");
    EXPECT_EQ(key.tag(), 0xfffe);
}

// Test tagLabel for an unknown tag returns empty string (per the implementation shown: tag_ == 0xffff returns "")
TEST_F(ExifKeyTest_1340, TagLabelForUnknownTagMayBeEmpty_1340) {
    // 0xfffe is unknown but not 0xffff, behavior depends on tagInfo
    Exiv2::ExifKey key(0xfffe, "Image");
    // Just check it doesn't crash; label may or may not be empty
    std::string label = key.tagLabel();
    SUCCEED();
}

}  // namespace

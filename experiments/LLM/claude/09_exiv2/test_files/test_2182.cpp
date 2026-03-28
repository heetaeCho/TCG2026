#include <gtest/gtest.h>
#include <exiv2/tags.hpp>
#include <exiv2/error.hpp>
#include <exiv2/exif.hpp>

using namespace Exiv2;

class ExifKeyTest_2182 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test construction from a valid string key
TEST_F(ExifKeyTest_2182, ConstructFromValidStringKey_2182) {
    EXPECT_NO_THROW(ExifKey key("Exif.Image.Make"));
}

// Test construction from tag and group name
TEST_F(ExifKeyTest_2182, ConstructFromTagAndGroupName_2182) {
    EXPECT_NO_THROW(ExifKey key(0x010f, "Image"));
}

// Test key() returns correct string representation
TEST_F(ExifKeyTest_2182, KeyReturnsCorrectString_2182) {
    ExifKey key("Exif.Image.Make");
    EXPECT_EQ(key.key(), "Exif.Image.Make");
}

// Test familyName() returns "Exif"
TEST_F(ExifKeyTest_2182, FamilyNameReturnsExif_2182) {
    ExifKey key("Exif.Image.Make");
    EXPECT_STREQ(key.familyName(), "Exif");
}

// Test groupName() returns correct group
TEST_F(ExifKeyTest_2182, GroupNameReturnsCorrectGroup_2182) {
    ExifKey key("Exif.Image.Make");
    EXPECT_EQ(key.groupName(), "Image");
}

// Test tagName() returns correct tag name
TEST_F(ExifKeyTest_2182, TagNameReturnsCorrectName_2182) {
    ExifKey key("Exif.Image.Make");
    EXPECT_EQ(key.tagName(), "Make");
}

// Test tag() returns correct tag number
TEST_F(ExifKeyTest_2182, TagReturnsCorrectNumber_2182) {
    ExifKey key("Exif.Image.Make");
    EXPECT_EQ(key.tag(), 0x010f);
}

// Test construction from tag number and group
TEST_F(ExifKeyTest_2182, ConstructFromTagNumberAndGroup_2182) {
    ExifKey key(0x010f, "Image");
    EXPECT_EQ(key.key(), "Exif.Image.Make");
    EXPECT_EQ(key.tag(), 0x010f);
    EXPECT_EQ(key.groupName(), "Image");
    EXPECT_EQ(key.tagName(), "Make");
}

// Test copy constructor
TEST_F(ExifKeyTest_2182, CopyConstructor_2182) {
    ExifKey key1("Exif.Image.Make");
    ExifKey key2(key1);
    EXPECT_EQ(key1.key(), key2.key());
    EXPECT_EQ(key1.tag(), key2.tag());
    EXPECT_EQ(key1.groupName(), key2.groupName());
    EXPECT_EQ(key1.tagName(), key2.tagName());
}

// Test assignment operator
TEST_F(ExifKeyTest_2182, AssignmentOperator_2182) {
    ExifKey key1("Exif.Image.Make");
    ExifKey key2("Exif.Image.Model");
    key2 = key1;
    EXPECT_EQ(key1.key(), key2.key());
    EXPECT_EQ(key1.tag(), key2.tag());
}

// Test clone
TEST_F(ExifKeyTest_2182, CloneProducesSameKey_2182) {
    ExifKey key("Exif.Image.Make");
    auto cloned = key.clone();
    EXPECT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->key(), key.key());
    EXPECT_EQ(cloned->tag(), key.tag());
    EXPECT_EQ(cloned->groupName(), key.groupName());
}

// Test invalid key string throws exception
TEST_F(ExifKeyTest_2182, InvalidKeyStringThrows_2182) {
    EXPECT_THROW(ExifKey key("InvalidKey"), Error);
}

// Test empty key string throws exception
TEST_F(ExifKeyTest_2182, EmptyKeyStringThrows_2182) {
    EXPECT_THROW(ExifKey key(""), Error);
}

// Test key with wrong family name throws
TEST_F(ExifKeyTest_2182, WrongFamilyNameThrows_2182) {
    EXPECT_THROW(ExifKey key("Iptc.Image.Make"), Error);
}

// Test idx default value
TEST_F(ExifKeyTest_2182, IdxDefaultIsZero_2182) {
    ExifKey key("Exif.Image.Make");
    EXPECT_EQ(key.idx(), 0);
}

// Test setIdx and idx
TEST_F(ExifKeyTest_2182, SetIdxAndGetIdx_2182) {
    ExifKey key("Exif.Image.Make");
    key.setIdx(42);
    EXPECT_EQ(key.idx(), 42);
}

// Test tagLabel returns non-empty for known tag
TEST_F(ExifKeyTest_2182, TagLabelNonEmptyForKnownTag_2182) {
    ExifKey key("Exif.Image.Make");
    std::string label = key.tagLabel();
    EXPECT_FALSE(label.empty());
}

// Test construction with Photo group
TEST_F(ExifKeyTest_2182, ConstructPhotoGroup_2182) {
    ExifKey key("Exif.Photo.ExposureTime");
    EXPECT_EQ(key.groupName(), "Photo");
    EXPECT_STREQ(key.familyName(), "Exif");
}

// Test construction with GPSInfo group
TEST_F(ExifKeyTest_2182, ConstructGPSInfoGroup_2182) {
    ExifKey key("Exif.GPSInfo.GPSLatitude");
    EXPECT_EQ(key.groupName(), "GPSInfo");
}

// Test ifdId returns valid IFD for known tag
TEST_F(ExifKeyTest_2182, IfdIdReturnsValidIfd_2182) {
    ExifKey key("Exif.Image.Make");
    IfdId id = key.ifdId();
    EXPECT_NE(id, IfdId::ifdIdNotSet);
}

// Test defaultTypeId for a known tag
TEST_F(ExifKeyTest_2182, DefaultTypeIdForMake_2182) {
    ExifKey key("Exif.Image.Make");
    TypeId typeId = key.defaultTypeId();
    EXPECT_EQ(typeId, asciiString);
}

// Test construction from tag and group - Photo group
TEST_F(ExifKeyTest_2182, ConstructFromTagAndPhotoGroup_2182) {
    ExifKey key(0x829a, "Photo");  // ExposureTime
    EXPECT_EQ(key.groupName(), "Photo");
    EXPECT_EQ(key.tag(), 0x829a);
}

// Test that tagDesc returns something for known tags
TEST_F(ExifKeyTest_2182, TagDescForKnownTag_2182) {
    ExifKey key("Exif.Image.Make");
    // tagDesc may or may not be empty, but should not throw
    std::string desc = key.tagDesc();
    // Just verify it doesn't crash
}

// Test Model tag
TEST_F(ExifKeyTest_2182, ModelTag_2182) {
    ExifKey key("Exif.Image.Model");
    EXPECT_EQ(key.tagName(), "Model");
    EXPECT_EQ(key.tag(), 0x0110);
    EXPECT_EQ(key.groupName(), "Image");
}

// Test unknown tag in valid group
TEST_F(ExifKeyTest_2182, UnknownTagInValidGroup_2182) {
    // Tag 0xffff might be unknown but should still work in a valid group
    EXPECT_NO_THROW(ExifKey key(0xffff, "Image"));
}

// Test that two different keys are different
TEST_F(ExifKeyTest_2182, TwoDifferentKeysAreDifferent_2182) {
    ExifKey key1("Exif.Image.Make");
    ExifKey key2("Exif.Image.Model");
    EXPECT_NE(key1.key(), key2.key());
    EXPECT_NE(key1.tag(), key2.tag());
}

// Test construction with TagInfo for valid Exif IFD
TEST_F(ExifKeyTest_2182, ConstructFromTagInfoValidExifIfd_2182) {
    // Use ExifTags to find a known TagInfo
    ExifKey key("Exif.Image.Make");
    auto cloned = key.clone();
    EXPECT_EQ(cloned->key(), "Exif.Image.Make");
}

// Test setIdx with negative value
TEST_F(ExifKeyTest_2182, SetIdxNegativeValue_2182) {
    ExifKey key("Exif.Image.Make");
    key.setIdx(-1);
    EXPECT_EQ(key.idx(), -1);
}

// Test self-assignment
TEST_F(ExifKeyTest_2182, SelfAssignment_2182) {
    ExifKey key("Exif.Image.Make");
    key = key;
    EXPECT_EQ(key.key(), "Exif.Image.Make");
}

// Test Iop group
TEST_F(ExifKeyTest_2182, IopGroup_2182) {
    ExifKey key("Exif.Iop.InteroperabilityIndex");
    EXPECT_EQ(key.groupName(), "Iop");
}

// Test Thumbnail group (IFD1)
TEST_F(ExifKeyTest_2182, ThumbnailGroup_2182) {
    EXPECT_NO_THROW(ExifKey key("Exif.Thumbnail.ImageWidth"));
}

// Test that write doesn't crash
TEST_F(ExifKeyTest_2182, WriteToStream_2182) {
    ExifKey key("Exif.Image.Make");
    std::ostringstream os;
    EXPECT_NO_THROW(key.write(os));
    EXPECT_FALSE(os.str().empty());
}

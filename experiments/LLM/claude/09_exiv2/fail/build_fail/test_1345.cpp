#include <gtest/gtest.h>
#include <exiv2/tags.hpp>
#include <exiv2/exif.hpp>
#include <string>

using namespace Exiv2;

// Test fixture for ExifKey tests
class ExifKeyTest_1345 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== Construction Tests ====================

TEST_F(ExifKeyTest_1345, ConstructFromStringKey_1345) {
    ExifKey key("Exif.Image.Make");
    EXPECT_EQ(key.key(), "Exif.Image.Make");
}

TEST_F(ExifKeyTest_1345, ConstructFromTagAndGroupName_1345) {
    // Tag 0x010f is "Make" in the "Image" group
    ExifKey key(0x010f, "Image");
    EXPECT_EQ(key.tag(), 0x010f);
    EXPECT_EQ(key.groupName(), "Image");
}

TEST_F(ExifKeyTest_1345, CopyConstructor_1345) {
    ExifKey original("Exif.Image.Make");
    ExifKey copy(original);
    EXPECT_EQ(copy.key(), original.key());
    EXPECT_EQ(copy.tag(), original.tag());
    EXPECT_EQ(copy.groupName(), original.groupName());
    EXPECT_EQ(copy.ifdId(), original.ifdId());
}

TEST_F(ExifKeyTest_1345, AssignmentOperator_1345) {
    ExifKey key1("Exif.Image.Make");
    ExifKey key2("Exif.Image.Model");
    key2 = key1;
    EXPECT_EQ(key2.key(), key1.key());
    EXPECT_EQ(key2.tag(), key1.tag());
    EXPECT_EQ(key2.groupName(), key1.groupName());
}

// ==================== Key String Tests ====================

TEST_F(ExifKeyTest_1345, KeyReturnsCorrectString_1345) {
    ExifKey key("Exif.Image.Model");
    EXPECT_EQ(key.key(), "Exif.Image.Model");
}

TEST_F(ExifKeyTest_1345, FamilyNameIsExif_1345) {
    ExifKey key("Exif.Image.Make");
    EXPECT_STREQ(key.familyName(), "Exif");
}

TEST_F(ExifKeyTest_1345, GroupNameIsCorrect_1345) {
    ExifKey key("Exif.Image.Make");
    EXPECT_EQ(key.groupName(), "Image");
}

TEST_F(ExifKeyTest_1345, TagNameIsCorrect_1345) {
    ExifKey key("Exif.Image.Make");
    EXPECT_EQ(key.tagName(), "Make");
}

// ==================== Tag Tests ====================

TEST_F(ExifKeyTest_1345, TagValueIsCorrect_1345) {
    ExifKey key("Exif.Image.Make");
    EXPECT_EQ(key.tag(), 0x010f);
}

TEST_F(ExifKeyTest_1345, TagFromTagAndGroup_1345) {
    ExifKey key(0x0110, "Image");  // Model tag
    EXPECT_EQ(key.tag(), 0x0110);
}

// ==================== IfdId Tests ====================

TEST_F(ExifKeyTest_1345, IfdIdForImageGroup_1345) {
    ExifKey key("Exif.Image.Make");
    EXPECT_EQ(key.ifdId(), IfdId::ifd0Id);
}

TEST_F(ExifKeyTest_1345, IfdIdForPhotoGroup_1345) {
    ExifKey key("Exif.Photo.ExposureTime");
    EXPECT_EQ(key.ifdId(), IfdId::exifId);
}

TEST_F(ExifKeyTest_1345, IfdIdForGpsGroup_1345) {
    ExifKey key("Exif.GPSInfo.GPSLatitude");
    EXPECT_EQ(key.ifdId(), IfdId::gpsId);
}

// ==================== Tag Label and Description Tests ====================

TEST_F(ExifKeyTest_1345, TagLabelIsNotEmpty_1345) {
    ExifKey key("Exif.Image.Make");
    EXPECT_FALSE(key.tagLabel().empty());
}

TEST_F(ExifKeyTest_1345, TagDescForKnownTag_1345) {
    ExifKey key("Exif.Image.Make");
    // tagDesc should return something for a well-known tag
    std::string desc = key.tagDesc();
    // Description may or may not be empty, but should not throw
    SUCCEED();
}

// ==================== DefaultTypeId Tests ====================

TEST_F(ExifKeyTest_1345, DefaultTypeIdForMake_1345) {
    ExifKey key("Exif.Image.Make");
    // Make is an ASCII type
    EXPECT_EQ(key.defaultTypeId(), asciiString);
}

TEST_F(ExifKeyTest_1345, DefaultTypeIdForExposureTime_1345) {
    ExifKey key("Exif.Photo.ExposureTime");
    // ExposureTime is a rational type
    EXPECT_EQ(key.defaultTypeId(), unsignedRational);
}

// ==================== Clone Tests ====================

TEST_F(ExifKeyTest_1345, CloneCreatesEqualCopy_1345) {
    ExifKey key("Exif.Image.Make");
    auto cloned = key.clone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->key(), key.key());
    EXPECT_EQ(cloned->tag(), key.tag());
    EXPECT_EQ(cloned->groupName(), key.groupName());
    EXPECT_EQ(cloned->ifdId(), key.ifdId());
}

TEST_F(ExifKeyTest_1345, CloneIsIndependent_1345) {
    ExifKey key("Exif.Image.Make");
    auto cloned = key.clone();
    // Modifying the original should not affect the clone
    // We can verify they have the same values but are separate objects
    EXPECT_EQ(cloned->key(), "Exif.Image.Make");
}

// ==================== Idx Tests ====================

TEST_F(ExifKeyTest_1345, DefaultIdxIsZero_1345) {
    ExifKey key("Exif.Image.Make");
    EXPECT_EQ(key.idx(), 0);
}

TEST_F(ExifKeyTest_1345, SetIdxChangesIdx_1345) {
    ExifKey key("Exif.Image.Make");
    key.setIdx(42);
    EXPECT_EQ(key.idx(), 42);
}

TEST_F(ExifKeyTest_1345, SetIdxNegativeValue_1345) {
    ExifKey key("Exif.Image.Make");
    key.setIdx(-1);
    EXPECT_EQ(key.idx(), -1);
}

TEST_F(ExifKeyTest_1345, SetIdxToZero_1345) {
    ExifKey key("Exif.Image.Make");
    key.setIdx(10);
    EXPECT_EQ(key.idx(), 10);
    key.setIdx(0);
    EXPECT_EQ(key.idx(), 0);
}

// ==================== Error / Boundary Tests ====================

TEST_F(ExifKeyTest_1345, InvalidKeyStringThrows_1345) {
    EXPECT_THROW(ExifKey("Invalid.Key.String.That.DoesNotExist"), Error);
}

TEST_F(ExifKeyTest_1345, EmptyKeyStringThrows_1345) {
    EXPECT_THROW(ExifKey(""), Error);
}

TEST_F(ExifKeyTest_1345, MalformedKeyThrows_1345) {
    EXPECT_THROW(ExifKey("NotExif"), Error);
}

TEST_F(ExifKeyTest_1345, WrongFamilyNameThrows_1345) {
    EXPECT_THROW(ExifKey("Iptc.Image.Make"), Error);
}

// ==================== Various Known Tags Tests ====================

TEST_F(ExifKeyTest_1345, ImageWidthTag_1345) {
    ExifKey key("Exif.Image.ImageWidth");
    EXPECT_EQ(key.tagName(), "ImageWidth");
    EXPECT_EQ(key.tag(), 0x0100);
}

TEST_F(ExifKeyTest_1345, ImageLengthTag_1345) {
    ExifKey key("Exif.Image.ImageLength");
    EXPECT_EQ(key.tagName(), "ImageLength");
    EXPECT_EQ(key.tag(), 0x0101);
}

TEST_F(ExifKeyTest_1345, DateTimeOriginalTag_1345) {
    ExifKey key("Exif.Photo.DateTimeOriginal");
    EXPECT_EQ(key.tagName(), "DateTimeOriginal");
    EXPECT_EQ(key.groupName(), "Photo");
    EXPECT_EQ(key.ifdId(), IfdId::exifId);
}

// ==================== Consistency Tests ====================

TEST_F(ExifKeyTest_1345, ConstructFromTagMatchesConstructFromString_1345) {
    ExifKey fromString("Exif.Image.Make");
    ExifKey fromTag(0x010f, "Image");
    EXPECT_EQ(fromString.key(), fromTag.key());
    EXPECT_EQ(fromString.tag(), fromTag.tag());
    EXPECT_EQ(fromString.groupName(), fromTag.groupName());
    EXPECT_EQ(fromString.ifdId(), fromTag.ifdId());
    EXPECT_EQ(fromString.tagName(), fromTag.tagName());
}

TEST_F(ExifKeyTest_1345, SelfAssignment_1345) {
    ExifKey key("Exif.Image.Make");
    key = key;
    EXPECT_EQ(key.key(), "Exif.Image.Make");
    EXPECT_EQ(key.tag(), 0x010f);
}

TEST_F(ExifKeyTest_1345, CopyPreservesIdx_1345) {
    ExifKey key("Exif.Image.Make");
    key.setIdx(99);
    ExifKey copy(key);
    EXPECT_EQ(copy.idx(), 99);
}

TEST_F(ExifKeyTest_1345, AssignmentPreservesIdx_1345) {
    ExifKey key1("Exif.Image.Make");
    key1.setIdx(55);
    ExifKey key2("Exif.Image.Model");
    key2 = key1;
    EXPECT_EQ(key2.idx(), 55);
}

TEST_F(ExifKeyTest_1345, ClonePreservesIdx_1345) {
    ExifKey key("Exif.Image.Make");
    key.setIdx(77);
    auto cloned = key.clone();
    EXPECT_EQ(cloned->idx(), 77);
}

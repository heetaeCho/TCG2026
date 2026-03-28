#include <gtest/gtest.h>
#include <exiv2/tags.hpp>
#include <exiv2/error.hpp>
#include <string>
#include <memory>

namespace {

// Test fixture for ExifKey tests
class ExifKeyTest_1338 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// =====================================================
// Construction from string key
// =====================================================

TEST_F(ExifKeyTest_1338, ConstructFromStringKey_ValidKey_1338) {
    ASSERT_NO_THROW(Exiv2::ExifKey key("Exif.Photo.DateTimeOriginal"));
}

TEST_F(ExifKeyTest_1338, ConstructFromStringKey_FamilyNameIsExif_1338) {
    Exiv2::ExifKey key("Exif.Photo.DateTimeOriginal");
    EXPECT_STREQ(key.familyName(), "Exif");
}

TEST_F(ExifKeyTest_1338, ConstructFromStringKey_GroupName_1338) {
    Exiv2::ExifKey key("Exif.Photo.DateTimeOriginal");
    EXPECT_EQ(key.groupName(), "Photo");
}

TEST_F(ExifKeyTest_1338, ConstructFromStringKey_TagName_1338) {
    Exiv2::ExifKey key("Exif.Photo.DateTimeOriginal");
    EXPECT_EQ(key.tagName(), "DateTimeOriginal");
}

TEST_F(ExifKeyTest_1338, ConstructFromStringKey_KeyRoundTrip_1338) {
    Exiv2::ExifKey key("Exif.Photo.DateTimeOriginal");
    EXPECT_EQ(key.key(), "Exif.Photo.DateTimeOriginal");
}

TEST_F(ExifKeyTest_1338, ConstructFromStringKey_ImageGroup_1338) {
    Exiv2::ExifKey key("Exif.Image.Make");
    EXPECT_EQ(key.groupName(), "Image");
    EXPECT_EQ(key.tagName(), "Make");
}

TEST_F(ExifKeyTest_1338, ConstructFromStringKey_InvalidKey_Throws_1338) {
    EXPECT_THROW(Exiv2::ExifKey key("InvalidKey"), Exiv2::Error);
}

TEST_F(ExifKeyTest_1338, ConstructFromStringKey_EmptyString_Throws_1338) {
    EXPECT_THROW(Exiv2::ExifKey key(""), Exiv2::Error);
}

TEST_F(ExifKeyTest_1338, ConstructFromStringKey_WrongFamily_Throws_1338) {
    EXPECT_THROW(Exiv2::ExifKey key("Iptc.Application2.Headline"), Exiv2::Error);
}

// =====================================================
// Construction from tag and group name
// =====================================================

TEST_F(ExifKeyTest_1338, ConstructFromTagAndGroup_ValidTag_1338) {
    ASSERT_NO_THROW(Exiv2::ExifKey key(0x010f, "Image"));
}

TEST_F(ExifKeyTest_1338, ConstructFromTagAndGroup_GroupName_1338) {
    Exiv2::ExifKey key(0x010f, "Image");
    EXPECT_EQ(key.groupName(), "Image");
}

TEST_F(ExifKeyTest_1338, ConstructFromTagAndGroup_Tag_1338) {
    Exiv2::ExifKey key(0x010f, "Image");
    EXPECT_EQ(key.tag(), 0x010f);
}

TEST_F(ExifKeyTest_1338, ConstructFromTagAndGroup_FamilyName_1338) {
    Exiv2::ExifKey key(0x010f, "Image");
    EXPECT_STREQ(key.familyName(), "Exif");
}

TEST_F(ExifKeyTest_1338, ConstructFromTagAndGroup_KeyString_1338) {
    Exiv2::ExifKey key(0x010f, "Image");
    EXPECT_EQ(key.key(), "Exif.Image.Make");
}

// =====================================================
// Copy constructor
// =====================================================

TEST_F(ExifKeyTest_1338, CopyConstructor_CopiesCorrectly_1338) {
    Exiv2::ExifKey original("Exif.Photo.DateTimeOriginal");
    Exiv2::ExifKey copy(original);
    EXPECT_EQ(copy.key(), original.key());
    EXPECT_EQ(copy.groupName(), original.groupName());
    EXPECT_EQ(copy.tagName(), original.tagName());
    EXPECT_EQ(copy.tag(), original.tag());
}

TEST_F(ExifKeyTest_1338, CopyConstructor_IndependentOfOriginal_1338) {
    Exiv2::ExifKey original("Exif.Photo.DateTimeOriginal");
    Exiv2::ExifKey copy(original);
    // Both should have same values but be independent objects
    EXPECT_EQ(copy.key(), "Exif.Photo.DateTimeOriginal");
    EXPECT_STREQ(copy.familyName(), "Exif");
}

// =====================================================
// Assignment operator
// =====================================================

TEST_F(ExifKeyTest_1338, AssignmentOperator_AssignsCorrectly_1338) {
    Exiv2::ExifKey key1("Exif.Photo.DateTimeOriginal");
    Exiv2::ExifKey key2("Exif.Image.Make");
    key2 = key1;
    EXPECT_EQ(key2.key(), key1.key());
    EXPECT_EQ(key2.groupName(), key1.groupName());
    EXPECT_EQ(key2.tagName(), key1.tagName());
}

// =====================================================
// Clone
// =====================================================

TEST_F(ExifKeyTest_1338, Clone_CreatesIndependentCopy_1338) {
    Exiv2::ExifKey original("Exif.Photo.DateTimeOriginal");
    auto cloned = original.clone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->key(), original.key());
    EXPECT_EQ(cloned->groupName(), original.groupName());
    EXPECT_EQ(cloned->tagName(), original.tagName());
    EXPECT_EQ(cloned->tag(), original.tag());
}

// =====================================================
// idx / setIdx
// =====================================================

TEST_F(ExifKeyTest_1338, Idx_DefaultIsZero_1338) {
    Exiv2::ExifKey key("Exif.Photo.DateTimeOriginal");
    EXPECT_EQ(key.idx(), 0);
}

TEST_F(ExifKeyTest_1338, SetIdx_ChangesIdx_1338) {
    Exiv2::ExifKey key("Exif.Photo.DateTimeOriginal");
    key.setIdx(42);
    EXPECT_EQ(key.idx(), 42);
}

TEST_F(ExifKeyTest_1338, SetIdx_NegativeValue_1338) {
    Exiv2::ExifKey key("Exif.Photo.DateTimeOriginal");
    key.setIdx(-1);
    EXPECT_EQ(key.idx(), -1);
}

// =====================================================
// tagLabel and tagDesc
// =====================================================

TEST_F(ExifKeyTest_1338, TagLabel_KnownTag_NonEmpty_1338) {
    Exiv2::ExifKey key("Exif.Image.Make");
    std::string label = key.tagLabel();
    // Known tags should have a non-empty label
    EXPECT_FALSE(label.empty());
}

TEST_F(ExifKeyTest_1338, TagDesc_KnownTag_NonEmpty_1338) {
    Exiv2::ExifKey key("Exif.Image.Make");
    std::string desc = key.tagDesc();
    // Known tags should have a non-empty description
    EXPECT_FALSE(desc.empty());
}

// =====================================================
// defaultTypeId
// =====================================================

TEST_F(ExifKeyTest_1338, DefaultTypeId_MakeTag_1338) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::TypeId typeId = key.defaultTypeId();
    // Make is an ASCII string tag
    EXPECT_EQ(typeId, Exiv2::asciiString);
}

// =====================================================
// ifdId
// =====================================================

TEST_F(ExifKeyTest_1338, IfdId_PhotoGroup_1338) {
    Exiv2::ExifKey key("Exif.Photo.DateTimeOriginal");
    Exiv2::IfdId id = key.ifdId();
    EXPECT_NE(id, Exiv2::IfdId::ifdIdNotSet);
}

TEST_F(ExifKeyTest_1338, IfdId_ImageGroup_1338) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::IfdId id = key.ifdId();
    EXPECT_NE(id, Exiv2::IfdId::ifdIdNotSet);
}

// =====================================================
// Various known tags
// =====================================================

TEST_F(ExifKeyTest_1338, KnownTag_ExposureTime_1338) {
    Exiv2::ExifKey key("Exif.Photo.ExposureTime");
    EXPECT_EQ(key.groupName(), "Photo");
    EXPECT_EQ(key.tagName(), "ExposureTime");
    EXPECT_EQ(key.key(), "Exif.Photo.ExposureTime");
}

TEST_F(ExifKeyTest_1338, KnownTag_Model_1338) {
    Exiv2::ExifKey key("Exif.Image.Model");
    EXPECT_EQ(key.groupName(), "Image");
    EXPECT_EQ(key.tagName(), "Model");
    EXPECT_EQ(key.tag(), 0x0110);
}

TEST_F(ExifKeyTest_1338, KnownTag_ISOSpeedRatings_1338) {
    Exiv2::ExifKey key("Exif.Photo.ISOSpeedRatings");
    EXPECT_EQ(key.groupName(), "Photo");
    EXPECT_EQ(key.tagName(), "ISOSpeedRatings");
}

// =====================================================
// Tag number with unknown tag in valid group
// =====================================================

TEST_F(ExifKeyTest_1338, UnknownTagNumber_InValidGroup_1338) {
    // Use a tag number that is unlikely to be defined
    Exiv2::ExifKey key(0xffff, "Image");
    EXPECT_EQ(key.tag(), 0xffff);
    EXPECT_EQ(key.groupName(), "Image");
    // Should still produce a valid key string
    EXPECT_FALSE(key.key().empty());
}

// =====================================================
// GPS group
// =====================================================

TEST_F(ExifKeyTest_1338, GPSTag_GPSLatitude_1338) {
    Exiv2::ExifKey key("Exif.GPSInfo.GPSLatitude");
    EXPECT_EQ(key.groupName(), "GPSInfo");
    EXPECT_EQ(key.tagName(), "GPSLatitude");
    EXPECT_STREQ(key.familyName(), "Exif");
}

// =====================================================
// Thumbnail / IFD1
// =====================================================

TEST_F(ExifKeyTest_1338, Thumbnail_ImageWidth_1338) {
    ASSERT_NO_THROW(Exiv2::ExifKey key("Exif.Thumbnail.ImageWidth"));
    Exiv2::ExifKey key("Exif.Thumbnail.ImageWidth");
    EXPECT_EQ(key.groupName(), "Thumbnail");
}

// =====================================================
// Multiple constructions yield consistent results
// =====================================================

TEST_F(ExifKeyTest_1338, ConsistentConstruction_StringVsTagGroup_1338) {
    Exiv2::ExifKey keyFromString("Exif.Image.Make");
    Exiv2::ExifKey keyFromTag(0x010f, "Image");
    
    EXPECT_EQ(keyFromString.key(), keyFromTag.key());
    EXPECT_EQ(keyFromString.groupName(), keyFromTag.groupName());
    EXPECT_EQ(keyFromString.tagName(), keyFromTag.tagName());
    EXPECT_EQ(keyFromString.tag(), keyFromTag.tag());
    EXPECT_EQ(keyFromString.ifdId(), keyFromTag.ifdId());
}

}  // namespace

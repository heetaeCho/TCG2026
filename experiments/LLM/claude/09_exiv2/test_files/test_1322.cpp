#include <gtest/gtest.h>
#include <sstream>
#include <string>

#include "exiv2/tags.hpp"
#include "exiv2/exif.hpp"

namespace {

// Test fixture for ExifTags tests
class ExifTagsTest_1322 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test sectionName with a known standard Exif tag
TEST_F(ExifTagsTest_1322, SectionNameForKnownTag_1322) {
  // Exif.Image.ImageWidth is a well-known tag in the Image group
  Exiv2::ExifKey key("Exif.Image.ImageWidth");
  const char* section = Exiv2::ExifTags::sectionName(key);
  ASSERT_NE(section, nullptr);
  // ImageWidth should be in ImageStructure section
  EXPECT_STREQ(section, "ImageStructure");
}

// Test sectionName for an unknown/invalid tag returns the unknown section
TEST_F(ExifTagsTest_1322, SectionNameForUnknownTag_1322) {
  // Tag 0xFFFF in Image group is unlikely to be defined, should return unknown section
  Exiv2::ExifKey key(0xFFFF, "Image");
  const char* section = Exiv2::ExifTags::sectionName(key);
  ASSERT_NE(section, nullptr);
  EXPECT_STREQ(section, "(UnknownSection)");
}

// Test sectionName for Exif.Photo tags (capture conditions)
TEST_F(ExifTagsTest_1322, SectionNameForExposureTime_1322) {
  Exiv2::ExifKey key("Exif.Photo.ExposureTime");
  const char* section = Exiv2::ExifTags::sectionName(key);
  ASSERT_NE(section, nullptr);
  EXPECT_STREQ(section, "CaptureConditions");
}

// Test sectionName for GPS tags
TEST_F(ExifTagsTest_1322, SectionNameForGPSTag_1322) {
  Exiv2::ExifKey key("Exif.GPSInfo.GPSLatitude");
  const char* section = Exiv2::ExifTags::sectionName(key);
  ASSERT_NE(section, nullptr);
  EXPECT_STREQ(section, "GPS");
}

// Test sectionName for Interoperability tags
TEST_F(ExifTagsTest_1322, SectionNameForIopTag_1322) {
  Exiv2::ExifKey key("Exif.Iop.InteroperabilityIndex");
  const char* section = Exiv2::ExifTags::sectionName(key);
  ASSERT_NE(section, nullptr);
  EXPECT_STREQ(section, "Interoperability");
}

// Test sectionName for DateTime related tags
TEST_F(ExifTagsTest_1322, SectionNameForDateTimeTag_1322) {
  Exiv2::ExifKey key("Exif.Photo.DateTimeOriginal");
  const char* section = Exiv2::ExifTags::sectionName(key);
  ASSERT_NE(section, nullptr);
  EXPECT_STREQ(section, "DateTime");
}

// Test sectionName for ExifVersion tag (exifVersion section)
TEST_F(ExifTagsTest_1322, SectionNameForExifVersion_1322) {
  Exiv2::ExifKey key("Exif.Photo.ExifVersion");
  const char* section = Exiv2::ExifTags::sectionName(key);
  ASSERT_NE(section, nullptr);
  EXPECT_STREQ(section, "ExifVersion");
}

// Test sectionName for ImageConfig section
TEST_F(ExifTagsTest_1322, SectionNameForImageConfig_1322) {
  Exiv2::ExifKey key("Exif.Photo.PixelXDimension");
  const char* section = Exiv2::ExifTags::sectionName(key);
  ASSERT_NE(section, nullptr);
  EXPECT_STREQ(section, "ImageConfig");
}

// Test sectionName for UserComment (UserInfo section)
TEST_F(ExifTagsTest_1322, SectionNameForUserComment_1322) {
  Exiv2::ExifKey key("Exif.Photo.UserComment");
  const char* section = Exiv2::ExifTags::sectionName(key);
  ASSERT_NE(section, nullptr);
  EXPECT_STREQ(section, "UserInfo");
}

// Test defaultCount for a known tag
TEST_F(ExifTagsTest_1322, DefaultCountForKnownTag_1322) {
  Exiv2::ExifKey key("Exif.Image.ImageWidth");
  uint16_t count = Exiv2::ExifTags::defaultCount(key);
  EXPECT_EQ(count, 1);
}

// Test defaultCount for an unknown tag
TEST_F(ExifTagsTest_1322, DefaultCountForUnknownTag_1322) {
  Exiv2::ExifKey key(0xFFFF, "Image");
  uint16_t count = Exiv2::ExifTags::defaultCount(key);
  // Unknown tag should have count from unknownTag which is -1 cast to uint16_t
  // but the actual behavior depends on implementation
  // We just verify it doesn't crash and returns some value
  (void)count;
}

// Test ifdName for a known group
TEST_F(ExifTagsTest_1322, IfdNameForImageGroup_1322) {
  const char* name = Exiv2::ExifTags::ifdName("Image");
  ASSERT_NE(name, nullptr);
  EXPECT_STREQ(name, "IFD0");
}

// Test ifdName for Photo group
TEST_F(ExifTagsTest_1322, IfdNameForPhotoGroup_1322) {
  const char* name = Exiv2::ExifTags::ifdName("Photo");
  ASSERT_NE(name, nullptr);
  EXPECT_STREQ(name, "Exif");
}

// Test isMakerGroup for standard groups (should be false)
TEST_F(ExifTagsTest_1322, IsMakerGroupForStandardGroup_1322) {
  EXPECT_FALSE(Exiv2::ExifTags::isMakerGroup("Image"));
  EXPECT_FALSE(Exiv2::ExifTags::isMakerGroup("Photo"));
  EXPECT_FALSE(Exiv2::ExifTags::isMakerGroup("GPSInfo"));
}

// Test isExifGroup for known Exif groups
TEST_F(ExifTagsTest_1322, IsExifGroupForKnownGroups_1322) {
  EXPECT_TRUE(Exiv2::ExifTags::isExifGroup("Image"));
  EXPECT_TRUE(Exiv2::ExifTags::isExifGroup("Photo"));
}

// Test isExifGroup for non-Exif group
TEST_F(ExifTagsTest_1322, IsExifGroupForNonExifGroup_1322) {
  EXPECT_FALSE(Exiv2::ExifTags::isExifGroup("NonExistentGroup"));
}

// Test groupList returns non-null
TEST_F(ExifTagsTest_1322, GroupListReturnsNonNull_1322) {
  const Exiv2::GroupInfo* groups = Exiv2::ExifTags::groupList();
  ASSERT_NE(groups, nullptr);
}

// Test tagList for Image group returns non-null
TEST_F(ExifTagsTest_1322, TagListForImageGroupReturnsNonNull_1322) {
  const Exiv2::TagInfo* tags = Exiv2::ExifTags::tagList("Image");
  ASSERT_NE(tags, nullptr);
}

// Test tagList for Photo group returns non-null
TEST_F(ExifTagsTest_1322, TagListForPhotoGroupReturnsNonNull_1322) {
  const Exiv2::TagInfo* tags = Exiv2::ExifTags::tagList("Photo");
  ASSERT_NE(tags, nullptr);
}

// Test taglist output to stream (no group specified)
TEST_F(ExifTagsTest_1322, TaglistOutputToStream_1322) {
  std::ostringstream os;
  Exiv2::ExifTags::taglist(os);
  std::string output = os.str();
  // Should produce some output
  EXPECT_FALSE(output.empty());
}

// Test taglist output for a specific group
TEST_F(ExifTagsTest_1322, TaglistOutputForSpecificGroup_1322) {
  std::ostringstream os;
  Exiv2::ExifTags::taglist(os, "Image");
  std::string output = os.str();
  EXPECT_FALSE(output.empty());
}

// Test ExifKey construction from string
TEST_F(ExifTagsTest_1322, ExifKeyConstructionFromString_1322) {
  Exiv2::ExifKey key("Exif.Image.ImageWidth");
  EXPECT_EQ(key.familyName(), std::string("Exif"));
  EXPECT_EQ(key.groupName(), std::string("Image"));
  EXPECT_EQ(key.tagName(), std::string("ImageWidth"));
}

// Test ExifKey construction from tag number and group
TEST_F(ExifTagsTest_1322, ExifKeyConstructionFromTagAndGroup_1322) {
  Exiv2::ExifKey key(0x0100, "Image");
  EXPECT_EQ(key.tag(), 0x0100);
  EXPECT_EQ(key.groupName(), std::string("Image"));
}

// Test ExifKey copy constructor
TEST_F(ExifTagsTest_1322, ExifKeyCopyConstructor_1322) {
  Exiv2::ExifKey key1("Exif.Image.ImageWidth");
  Exiv2::ExifKey key2(key1);
  EXPECT_EQ(key1.key(), key2.key());
  EXPECT_EQ(key1.tag(), key2.tag());
  EXPECT_EQ(key1.groupName(), key2.groupName());
}

// Test ExifKey assignment operator
TEST_F(ExifTagsTest_1322, ExifKeyAssignmentOperator_1322) {
  Exiv2::ExifKey key1("Exif.Image.ImageWidth");
  Exiv2::ExifKey key2("Exif.Image.ImageLength");
  key2 = key1;
  EXPECT_EQ(key1.key(), key2.key());
  EXPECT_EQ(key1.tag(), key2.tag());
}

// Test ExifKey clone
TEST_F(ExifTagsTest_1322, ExifKeyClone_1322) {
  Exiv2::ExifKey key("Exif.Image.ImageWidth");
  auto cloned = key.clone();
  ASSERT_NE(cloned, nullptr);
  EXPECT_EQ(key.key(), cloned->key());
  EXPECT_EQ(key.tag(), cloned->tag());
}

// Test ExifKey key() returns full key string
TEST_F(ExifTagsTest_1322, ExifKeyFullKeyString_1322) {
  Exiv2::ExifKey key("Exif.Image.ImageWidth");
  EXPECT_EQ(key.key(), "Exif.Image.ImageWidth");
}

// Test ExifKey tagLabel for a known tag
TEST_F(ExifTagsTest_1322, ExifKeyTagLabel_1322) {
  Exiv2::ExifKey key("Exif.Image.ImageWidth");
  std::string label = key.tagLabel();
  EXPECT_FALSE(label.empty());
}

// Test ExifKey tagDesc for a known tag
TEST_F(ExifTagsTest_1322, ExifKeyTagDesc_1322) {
  Exiv2::ExifKey key("Exif.Image.ImageWidth");
  std::string desc = key.tagDesc();
  // Known tags should have a description
  EXPECT_FALSE(desc.empty());
}

// Test ExifKey idx default
TEST_F(ExifTagsTest_1322, ExifKeyIdxDefault_1322) {
  Exiv2::ExifKey key("Exif.Image.ImageWidth");
  int idx = key.idx();
  EXPECT_EQ(idx, 0);
}

// Test ExifKey setIdx and idx
TEST_F(ExifTagsTest_1322, ExifKeySetIdx_1322) {
  Exiv2::ExifKey key("Exif.Image.ImageWidth");
  key.setIdx(42);
  EXPECT_EQ(key.idx(), 42);
}

// Test ExifKey defaultTypeId for a known tag
TEST_F(ExifTagsTest_1322, ExifKeyDefaultTypeId_1322) {
  Exiv2::ExifKey key("Exif.Image.ImageWidth");
  Exiv2::TypeId typeId = key.defaultTypeId();
  // ImageWidth can be LONG or SHORT
  EXPECT_TRUE(typeId == Exiv2::unsignedLong || typeId == Exiv2::unsignedShort);
}

// Test ExifKey ifdId
TEST_F(ExifTagsTest_1322, ExifKeyIfdId_1322) {
  Exiv2::ExifKey key("Exif.Image.ImageWidth");
  Exiv2::IfdId ifdId = key.ifdId();
  EXPECT_EQ(ifdId, Exiv2::IfdId::ifd0Id);
}

// Test ExifKey for Photo group ifdId
TEST_F(ExifTagsTest_1322, ExifKeyPhotoIfdId_1322) {
  Exiv2::ExifKey key("Exif.Photo.ExposureTime");
  Exiv2::IfdId ifdId = key.ifdId();
  EXPECT_EQ(ifdId, Exiv2::IfdId::exifId);
}

// Test sectionName for OtherTags section
TEST_F(ExifTagsTest_1322, SectionNameForOtherTags_1322) {
  // Exif.Image.DocumentName might be in OtherTags
  Exiv2::ExifKey key("Exif.Image.DocumentName");
  const char* section = Exiv2::ExifTags::sectionName(key);
  ASSERT_NE(section, nullptr);
  // Just verify it returns a valid string (not null), section may vary
  EXPECT_GT(std::string(section).size(), 0u);
}

// Test ExifKey construction with invalid key string throws
TEST_F(ExifTagsTest_1322, ExifKeyInvalidStringThrows_1322) {
  EXPECT_THROW(Exiv2::ExifKey key("InvalidKeyString"), Exiv2::Error);
}

// Test that multiple sectionName calls are consistent
TEST_F(ExifTagsTest_1322, SectionNameConsistency_1322) {
  Exiv2::ExifKey key1("Exif.Image.ImageWidth");
  Exiv2::ExifKey key2("Exif.Image.ImageWidth");
  const char* s1 = Exiv2::ExifTags::sectionName(key1);
  const char* s2 = Exiv2::ExifTags::sectionName(key2);
  EXPECT_STREQ(s1, s2);
}

// Test sectionName for Makernote group
TEST_F(ExifTagsTest_1322, SectionNameForMakernoteTag_1322) {
  // Try to create a key for a maker note group, if available
  try {
    Exiv2::ExifKey key(0x0001, "Canon");
    const char* section = Exiv2::ExifTags::sectionName(key);
    ASSERT_NE(section, nullptr);
    EXPECT_STREQ(section, "Makernote");
  } catch (const Exiv2::Error&) {
    // If Canon group doesn't exist, that's ok - skip
    GTEST_SKIP() << "Canon maker group not available";
  }
}

// Test isMakerGroup for a known maker group
TEST_F(ExifTagsTest_1322, IsMakerGroupForCanon_1322) {
  // Canon should be a maker group if it exists
  bool result = Exiv2::ExifTags::isMakerGroup("Canon");
  EXPECT_TRUE(result);
}

// Test tagList for an unknown group name
TEST_F(ExifTagsTest_1322, TagListForUnknownGroup_1322) {
  const Exiv2::TagInfo* tags = Exiv2::ExifTags::tagList("NonExistentGroupXYZ123");
  // Should return nullptr for unknown groups
  EXPECT_EQ(tags, nullptr);
}

// Test sectionName for RecordingOffset section (StripOffsets tag)
TEST_F(ExifTagsTest_1322, SectionNameForStripOffsets_1322) {
  Exiv2::ExifKey key("Exif.Image.StripOffsets");
  const char* section = Exiv2::ExifTags::sectionName(key);
  ASSERT_NE(section, nullptr);
  EXPECT_STREQ(section, "RecordingOffset");
}

}  // namespace

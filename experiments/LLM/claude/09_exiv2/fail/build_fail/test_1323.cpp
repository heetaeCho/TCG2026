#include <gtest/gtest.h>
#include <sstream>
#include <string>

#include "exiv2/tags.hpp"
#include "exiv2/exif.hpp"

namespace {

// Test fixture for ExifTags tests
class ExifTagsTest_1323 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// ==================== defaultCount tests ====================

TEST_F(ExifTagsTest_1323, DefaultCountForKnownTag_1323) {
  // Exif.Image.ImageWidth is a well-known tag (tag 0x0100 in IFD0)
  Exiv2::ExifKey key("Exif.Image.ImageWidth");
  uint16_t count = Exiv2::ExifTags::defaultCount(key);
  // ImageWidth typically has count 1
  EXPECT_GT(count, 0);
}

TEST_F(ExifTagsTest_1323, DefaultCountForUnknownTag_1323) {
  // Use a tag number that is unlikely to be defined in IFD0
  Exiv2::ExifKey key(0xFFFF, "Image");
  uint16_t count = Exiv2::ExifTags::defaultCount(key);
  // For unknown tags, the count should come from unknownTag which has count -1
  // interpreted as uint16_t
  EXPECT_EQ(count, static_cast<uint16_t>(-1));
}

TEST_F(ExifTagsTest_1323, DefaultCountForPhotoTag_1323) {
  // Exif.Photo.ExposureTime (tag 0x829A)
  Exiv2::ExifKey key("Exif.Photo.ExposureTime");
  uint16_t count = Exiv2::ExifTags::defaultCount(key);
  // ExposureTime has a defined count
  EXPECT_GT(count, 0);
}

// ==================== sectionName tests ====================

TEST_F(ExifTagsTest_1323, SectionNameForKnownTag_1323) {
  Exiv2::ExifKey key("Exif.Image.ImageWidth");
  const char* section = Exiv2::ExifTags::sectionName(key);
  ASSERT_NE(section, nullptr);
  EXPECT_GT(strlen(section), 0u);
}

TEST_F(ExifTagsTest_1323, SectionNameForUnknownTag_1323) {
  Exiv2::ExifKey key(0xFFFF, "Image");
  const char* section = Exiv2::ExifTags::sectionName(key);
  ASSERT_NE(section, nullptr);
}

// ==================== groupList tests ====================

TEST_F(ExifTagsTest_1323, GroupListIsNotNull_1323) {
  const Exiv2::GroupInfo* groups = Exiv2::ExifTags::groupList();
  ASSERT_NE(groups, nullptr);
}

TEST_F(ExifTagsTest_1323, GroupListContainsEntries_1323) {
  const Exiv2::GroupInfo* groups = Exiv2::ExifTags::groupList();
  ASSERT_NE(groups, nullptr);
  // There should be at least one group (e.g., Image, Photo, etc.)
  // The list is terminated by a sentinel with ifdId_ == ifdIdNotSet
  int count = 0;
  for (auto gi = groups; gi->ifdId_ != Exiv2::IfdId::ifdIdNotSet; ++gi) {
    ++count;
  }
  EXPECT_GT(count, 0);
}

// ==================== tagList tests ====================

TEST_F(ExifTagsTest_1323, TagListForImageGroup_1323) {
  const Exiv2::TagInfo* tags = Exiv2::ExifTags::tagList("Image");
  ASSERT_NE(tags, nullptr);
}

TEST_F(ExifTagsTest_1323, TagListForPhotoGroup_1323) {
  const Exiv2::TagInfo* tags = Exiv2::ExifTags::tagList("Photo");
  ASSERT_NE(tags, nullptr);
}

TEST_F(ExifTagsTest_1323, TagListForUnknownGroupReturnsNull_1323) {
  const Exiv2::TagInfo* tags = Exiv2::ExifTags::tagList("NonExistentGroup12345");
  EXPECT_EQ(tags, nullptr);
}

// ==================== taglist (stream) tests ====================

TEST_F(ExifTagsTest_1323, TaglistOutputsToStream_1323) {
  std::ostringstream os;
  Exiv2::ExifTags::taglist(os);
  std::string output = os.str();
  // Should produce non-empty output listing all known tags
  EXPECT_FALSE(output.empty());
}

TEST_F(ExifTagsTest_1323, TaglistForGroupOutputsToStream_1323) {
  std::ostringstream os;
  Exiv2::ExifTags::taglist(os, "Image");
  std::string output = os.str();
  EXPECT_FALSE(output.empty());
}

TEST_F(ExifTagsTest_1323, TaglistForUnknownGroupOutputsEmpty_1323) {
  std::ostringstream os;
  // Unknown group should produce no output or handle gracefully
  EXPECT_NO_THROW(Exiv2::ExifTags::taglist(os, "NonExistentGroup12345"));
}

// ==================== ifdName tests ====================

TEST_F(ExifTagsTest_1323, IfdNameForImageGroup_1323) {
  const char* name = Exiv2::ExifTags::ifdName("Image");
  ASSERT_NE(name, nullptr);
  EXPECT_GT(strlen(name), 0u);
}

TEST_F(ExifTagsTest_1323, IfdNameForPhotoGroup_1323) {
  const char* name = Exiv2::ExifTags::ifdName("Photo");
  ASSERT_NE(name, nullptr);
  EXPECT_GT(strlen(name), 0u);
}

TEST_F(ExifTagsTest_1323, IfdNameForUnknownGroup_1323) {
  const char* name = Exiv2::ExifTags::ifdName("NonExistentGroup12345");
  ASSERT_NE(name, nullptr);
}

// ==================== isMakerGroup tests ====================

TEST_F(ExifTagsTest_1323, IsMakerGroupForStandardGroup_1323) {
  // "Image" is not a maker group
  EXPECT_FALSE(Exiv2::ExifTags::isMakerGroup("Image"));
}

TEST_F(ExifTagsTest_1323, IsMakerGroupForPhotoGroup_1323) {
  EXPECT_FALSE(Exiv2::ExifTags::isMakerGroup("Photo"));
}

TEST_F(ExifTagsTest_1323, IsMakerGroupForUnknownGroup_1323) {
  EXPECT_FALSE(Exiv2::ExifTags::isMakerGroup("NonExistentGroup12345"));
}

TEST_F(ExifTagsTest_1323, IsMakerGroupForCanonGroup_1323) {
  // Canon is typically a maker group
  bool result = Exiv2::ExifTags::isMakerGroup("Canon");
  // Just verify it doesn't crash; actual value depends on implementation
  (void)result;
}

// ==================== isExifGroup tests ====================

TEST_F(ExifTagsTest_1323, IsExifGroupForImageGroup_1323) {
  EXPECT_TRUE(Exiv2::ExifTags::isExifGroup("Image"));
}

TEST_F(ExifTagsTest_1323, IsExifGroupForPhotoGroup_1323) {
  EXPECT_TRUE(Exiv2::ExifTags::isExifGroup("Photo"));
}

TEST_F(ExifTagsTest_1323, IsExifGroupForUnknownGroup_1323) {
  EXPECT_FALSE(Exiv2::ExifTags::isExifGroup("NonExistentGroup12345"));
}

// ==================== ExifKey tests ====================

class ExifKeyTest_1323 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

TEST_F(ExifKeyTest_1323, ConstructFromString_1323) {
  Exiv2::ExifKey key("Exif.Image.ImageWidth");
  EXPECT_EQ(key.key(), "Exif.Image.ImageWidth");
}

TEST_F(ExifKeyTest_1323, ConstructFromTagAndGroup_1323) {
  // Tag 0x0100 is ImageWidth in Image group
  Exiv2::ExifKey key(0x0100, "Image");
  EXPECT_EQ(key.tag(), 0x0100);
  EXPECT_EQ(key.groupName(), "Image");
}

TEST_F(ExifKeyTest_1323, FamilyNameIsExif_1323) {
  Exiv2::ExifKey key("Exif.Image.ImageWidth");
  EXPECT_STREQ(key.familyName(), "Exif");
}

TEST_F(ExifKeyTest_1323, GroupNameReturnsCorrectGroup_1323) {
  Exiv2::ExifKey key("Exif.Photo.ExposureTime");
  EXPECT_EQ(key.groupName(), "Photo");
}

TEST_F(ExifKeyTest_1323, TagNameReturnsCorrectName_1323) {
  Exiv2::ExifKey key("Exif.Image.ImageWidth");
  EXPECT_EQ(key.tagName(), "ImageWidth");
}

TEST_F(ExifKeyTest_1323, TagReturnsCorrectValue_1323) {
  Exiv2::ExifKey key("Exif.Image.ImageWidth");
  EXPECT_EQ(key.tag(), 0x0100);
}

TEST_F(ExifKeyTest_1323, CopyConstructor_1323) {
  Exiv2::ExifKey key1("Exif.Image.ImageWidth");
  Exiv2::ExifKey key2(key1);
  EXPECT_EQ(key1.key(), key2.key());
  EXPECT_EQ(key1.tag(), key2.tag());
  EXPECT_EQ(key1.groupName(), key2.groupName());
}

TEST_F(ExifKeyTest_1323, AssignmentOperator_1323) {
  Exiv2::ExifKey key1("Exif.Image.ImageWidth");
  Exiv2::ExifKey key2("Exif.Photo.ExposureTime");
  key2 = key1;
  EXPECT_EQ(key1.key(), key2.key());
  EXPECT_EQ(key1.tag(), key2.tag());
}

TEST_F(ExifKeyTest_1323, Clone_1323) {
  Exiv2::ExifKey key("Exif.Image.ImageWidth");
  auto cloned = key.clone();
  ASSERT_NE(cloned, nullptr);
  EXPECT_EQ(key.key(), cloned->key());
  EXPECT_EQ(key.tag(), cloned->tag());
}

TEST_F(ExifKeyTest_1323, TagLabel_1323) {
  Exiv2::ExifKey key("Exif.Image.ImageWidth");
  std::string label = key.tagLabel();
  // Should have a non-empty label for a well-known tag
  EXPECT_FALSE(label.empty());
}

TEST_F(ExifKeyTest_1323, TagDesc_1323) {
  Exiv2::ExifKey key("Exif.Image.ImageWidth");
  std::string desc = key.tagDesc();
  // Should have a non-empty description for a well-known tag
  EXPECT_FALSE(desc.empty());
}

TEST_F(ExifKeyTest_1323, DefaultTypeId_1323) {
  Exiv2::ExifKey key("Exif.Image.ImageWidth");
  Exiv2::TypeId typeId = key.defaultTypeId();
  // ImageWidth is typically SHORT or LONG
  EXPECT_NE(typeId, Exiv2::invalidTypeId);
}

TEST_F(ExifKeyTest_1323, SetAndGetIdx_1323) {
  Exiv2::ExifKey key("Exif.Image.ImageWidth");
  key.setIdx(42);
  EXPECT_EQ(key.idx(), 42);
}

TEST_F(ExifKeyTest_1323, DefaultIdx_1323) {
  Exiv2::ExifKey key("Exif.Image.ImageWidth");
  // Default idx should be 0
  EXPECT_EQ(key.idx(), 0);
}

TEST_F(ExifKeyTest_1323, IfdIdForImageGroup_1323) {
  Exiv2::ExifKey key("Exif.Image.ImageWidth");
  Exiv2::IfdId ifdId = key.ifdId();
  EXPECT_NE(ifdId, Exiv2::IfdId::ifdIdNotSet);
}

TEST_F(ExifKeyTest_1323, ConstructFromInvalidStringThrows_1323) {
  EXPECT_THROW(Exiv2::ExifKey key("InvalidKeyFormat"), Exiv2::Error);
}

TEST_F(ExifKeyTest_1323, ConstructFromUnknownTagByNumber_1323) {
  // Tag number that doesn't exist in Image group
  Exiv2::ExifKey key(0xBEEF, "Image");
  EXPECT_EQ(key.tag(), 0xBEEF);
  EXPECT_EQ(key.groupName(), "Image");
}

// ==================== defaultCount with various known tags ====================

TEST_F(ExifTagsTest_1323, DefaultCountForOrientation_1323) {
  Exiv2::ExifKey key("Exif.Image.Orientation");
  uint16_t count = Exiv2::ExifTags::defaultCount(key);
  // Orientation has count 1
  EXPECT_EQ(count, 1);
}

TEST_F(ExifTagsTest_1323, DefaultCountForGPSVersionID_1323) {
  Exiv2::ExifKey key("Exif.GPSInfo.GPSVersionID");
  uint16_t count = Exiv2::ExifTags::defaultCount(key);
  // GPSVersionID has count 4
  EXPECT_EQ(count, 4);
}

}  // namespace

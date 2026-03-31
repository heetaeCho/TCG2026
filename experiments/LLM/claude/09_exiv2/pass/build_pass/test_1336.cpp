#include <gtest/gtest.h>
#include <exiv2/tags.hpp>
#include <exiv2/error.hpp>
#include <string>

using namespace Exiv2;

// Test creating ExifKey from a valid string key
TEST(ExifKeyTest_1336, ConstructFromValidStringKey_1336) {
  ExifKey key("Exif.Photo.DateTimeOriginal");
  EXPECT_EQ(key.key(), "Exif.Photo.DateTimeOriginal");
}

// Test familyName returns "Exif"
TEST(ExifKeyTest_1336, FamilyNameIsExif_1336) {
  ExifKey key("Exif.Photo.DateTimeOriginal");
  EXPECT_STREQ(key.familyName(), "Exif");
}

// Test groupName returns correct group
TEST(ExifKeyTest_1336, GroupNameReturnsCorrectGroup_1336) {
  ExifKey key("Exif.Photo.DateTimeOriginal");
  EXPECT_EQ(key.groupName(), "Photo");
}

// Test tagName returns correct tag name
TEST(ExifKeyTest_1336, TagNameReturnsCorrectName_1336) {
  ExifKey key("Exif.Photo.DateTimeOriginal");
  EXPECT_EQ(key.tagName(), "DateTimeOriginal");
}

// Test tag returns correct tag number
TEST(ExifKeyTest_1336, TagReturnsCorrectNumber_1336) {
  ExifKey key("Exif.Photo.DateTimeOriginal");
  // DateTimeOriginal is tag 0x9003
  EXPECT_EQ(key.tag(), 0x9003);
}

// Test constructing from tag number and group name
TEST(ExifKeyTest_1336, ConstructFromTagAndGroupName_1336) {
  ExifKey key(0x9003, "Photo");
  EXPECT_EQ(key.key(), "Exif.Photo.DateTimeOriginal");
  EXPECT_EQ(key.tag(), 0x9003);
  EXPECT_EQ(key.groupName(), "Photo");
}

// Test copy constructor
TEST(ExifKeyTest_1336, CopyConstructor_1336) {
  ExifKey original("Exif.Photo.DateTimeOriginal");
  ExifKey copy(original);
  EXPECT_EQ(copy.key(), original.key());
  EXPECT_EQ(copy.tag(), original.tag());
  EXPECT_EQ(copy.groupName(), original.groupName());
  EXPECT_EQ(copy.tagName(), original.tagName());
}

// Test assignment operator
TEST(ExifKeyTest_1336, AssignmentOperator_1336) {
  ExifKey key1("Exif.Photo.DateTimeOriginal");
  ExifKey key2("Exif.Image.Make");
  key2 = key1;
  EXPECT_EQ(key2.key(), key1.key());
  EXPECT_EQ(key2.tag(), key1.tag());
  EXPECT_EQ(key2.groupName(), key1.groupName());
}

// Test clone
TEST(ExifKeyTest_1336, CloneProducesCopy_1336) {
  ExifKey key("Exif.Photo.DateTimeOriginal");
  auto cloned = key.clone();
  ASSERT_NE(cloned, nullptr);
  EXPECT_EQ(cloned->key(), key.key());
  EXPECT_EQ(cloned->tag(), key.tag());
  EXPECT_EQ(cloned->groupName(), key.groupName());
}

// Test ExifKey with Image group
TEST(ExifKeyTest_1336, ImageGroupKey_1336) {
  ExifKey key("Exif.Image.Make");
  EXPECT_EQ(key.key(), "Exif.Image.Make");
  EXPECT_EQ(key.groupName(), "Image");
  EXPECT_EQ(key.tagName(), "Make");
  EXPECT_STREQ(key.familyName(), "Exif");
}

// Test tagLabel returns non-empty for known tags
TEST(ExifKeyTest_1336, TagLabelForKnownTag_1336) {
  ExifKey key("Exif.Photo.DateTimeOriginal");
  std::string label = key.tagLabel();
  EXPECT_FALSE(label.empty());
}

// Test idx default value and setIdx
TEST(ExifKeyTest_1336, IdxDefaultAndSet_1336) {
  ExifKey key("Exif.Photo.DateTimeOriginal");
  EXPECT_EQ(key.idx(), 0);
  key.setIdx(5);
  EXPECT_EQ(key.idx(), 5);
}

// Test constructing from invalid key string throws
TEST(ExifKeyTest_1336, ConstructFromInvalidKeyThrows_1336) {
  EXPECT_THROW(ExifKey("InvalidKey"), Error);
}

// Test constructing from key with wrong family throws
TEST(ExifKeyTest_1336, ConstructFromWrongFamilyThrows_1336) {
  EXPECT_THROW(ExifKey("Iptc.Photo.DateTimeOriginal"), Error);
}

// Test ifdId returns valid IfdId
TEST(ExifKeyTest_1336, IfdIdReturnsValid_1336) {
  ExifKey key("Exif.Photo.DateTimeOriginal");
  IfdId id = key.ifdId();
  EXPECT_NE(id, IfdId::ifdIdNotSet);
}

// Test defaultTypeId returns a valid type
TEST(ExifKeyTest_1336, DefaultTypeIdForKnownTag_1336) {
  ExifKey key("Exif.Photo.DateTimeOriginal");
  TypeId typeId = key.defaultTypeId();
  EXPECT_NE(typeId, invalidTypeId);
}

// Test constructing ExifKey with tag number and group for Image
TEST(ExifKeyTest_1336, ConstructFromTagNumberImageGroup_1336) {
  // Make tag is 0x010f
  ExifKey key(0x010f, "Image");
  EXPECT_EQ(key.tagName(), "Make");
  EXPECT_EQ(key.groupName(), "Image");
  EXPECT_EQ(key.tag(), 0x010f);
}

// Test ExifKey with GPSInfo group
TEST(ExifKeyTest_1336, GPSInfoGroupKey_1336) {
  ExifKey key("Exif.GPSInfo.GPSLatitude");
  EXPECT_EQ(key.key(), "Exif.GPSInfo.GPSLatitude");
  EXPECT_EQ(key.groupName(), "GPSInfo");
  EXPECT_EQ(key.tagName(), "GPSLatitude");
}

// Test tagDesc returns something for known tags
TEST(ExifKeyTest_1336, TagDescForKnownTag_1336) {
  ExifKey key("Exif.Image.Make");
  std::string desc = key.tagDesc();
  // Description may or may not be empty, but the call should not crash
  // For well-known tags it's typically non-empty
  EXPECT_FALSE(desc.empty());
}

// Test self-assignment
TEST(ExifKeyTest_1336, SelfAssignment_1336) {
  ExifKey key("Exif.Photo.DateTimeOriginal");
  key = key;
  EXPECT_EQ(key.key(), "Exif.Photo.DateTimeOriginal");
}

// Test constructing with unknown tag in a valid group
TEST(ExifKeyTest_1336, UnknownTagInValidGroup_1336) {
  // Tag 0xFFFF is unlikely to be defined in Photo
  ExifKey key(0xFFFF, "Photo");
  EXPECT_EQ(key.tag(), 0xFFFF);
  EXPECT_EQ(key.groupName(), "Photo");
  // tagName should return something (likely hex representation)
  EXPECT_FALSE(key.tagName().empty());
}

// Test key string format consistency
TEST(ExifKeyTest_1336, KeyStringFormatConsistency_1336) {
  ExifKey key(0x010f, "Image");
  std::string keyStr = key.key();
  // Key should start with "Exif."
  EXPECT_EQ(keyStr.substr(0, 5), "Exif.");
  // Key should contain the group name
  EXPECT_NE(keyStr.find("Image"), std::string::npos);
}

// Test ExifKey with Iop group
TEST(ExifKeyTest_1336, IopGroupKey_1336) {
  ExifKey key("Exif.Iop.InteroperabilityIndex");
  EXPECT_EQ(key.groupName(), "Iop");
  EXPECT_EQ(key.tagName(), "InteroperabilityIndex");
}

// Test multiple setIdx calls
TEST(ExifKeyTest_1336, MultipleSetIdx_1336) {
  ExifKey key("Exif.Image.Make");
  key.setIdx(10);
  EXPECT_EQ(key.idx(), 10);
  key.setIdx(20);
  EXPECT_EQ(key.idx(), 20);
  key.setIdx(0);
  EXPECT_EQ(key.idx(), 0);
}

// Test that cloned object is independent
TEST(ExifKeyTest_1336, ClonedObjectIsIndependent_1336) {
  ExifKey key("Exif.Image.Make");
  key.setIdx(42);
  auto cloned = key.clone();
  EXPECT_EQ(cloned->idx(), 42);
  key.setIdx(99);
  EXPECT_EQ(cloned->idx(), 42);
}

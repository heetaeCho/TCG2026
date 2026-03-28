#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <string>
#include <memory>
#include <exiv2/exiv2.hpp>

// Since Key is abstract, we need a concrete implementation to test.
// We'll use Exiv2's built-in concrete key types (ExifKey, IptcKey, XmpKey).

class KeyWriteTest_36 : public ::testing::Test {
protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test that ExifKey::write outputs the key string to the stream
TEST_F(KeyWriteTest_36, ExifKeyWriteOutputsKey_36) {
  Exiv2::ExifKey key("Exif.Photo.DateTimeOriginal");
  std::ostringstream os;
  key.write(os);
  EXPECT_EQ(os.str(), key.key());
}

// Test that ExifKey::key returns the expected key string
TEST_F(KeyWriteTest_36, ExifKeyReturnsCorrectKey_36) {
  Exiv2::ExifKey key("Exif.Photo.DateTimeOriginal");
  EXPECT_EQ(key.key(), "Exif.Photo.DateTimeOriginal");
}

// Test that ExifKey::familyName returns "Exif"
TEST_F(KeyWriteTest_36, ExifKeyFamilyName_36) {
  Exiv2::ExifKey key("Exif.Photo.DateTimeOriginal");
  EXPECT_STREQ(key.familyName(), "Exif");
}

// Test that ExifKey::groupName returns the group
TEST_F(KeyWriteTest_36, ExifKeyGroupName_36) {
  Exiv2::ExifKey key("Exif.Photo.DateTimeOriginal");
  EXPECT_EQ(key.groupName(), "Photo");
}

// Test that ExifKey::tagName returns the tag name
TEST_F(KeyWriteTest_36, ExifKeyTagName_36) {
  Exiv2::ExifKey key("Exif.Photo.DateTimeOriginal");
  EXPECT_EQ(key.tagName(), "DateTimeOriginal");
}

// Test that ExifKey::tag returns a non-zero tag number for a known tag
TEST_F(KeyWriteTest_36, ExifKeyTagNumber_36) {
  Exiv2::ExifKey key("Exif.Photo.DateTimeOriginal");
  // DateTimeOriginal tag is 0x9003 = 36867
  EXPECT_EQ(key.tag(), 0x9003);
}

// Test that ExifKey::tagLabel returns a non-empty label
TEST_F(KeyWriteTest_36, ExifKeyTagLabel_36) {
  Exiv2::ExifKey key("Exif.Photo.DateTimeOriginal");
  EXPECT_FALSE(key.tagLabel().empty());
}

// Test clone produces a valid copy
TEST_F(KeyWriteTest_36, ExifKeyClone_36) {
  Exiv2::ExifKey key("Exif.Photo.DateTimeOriginal");
  auto cloned = key.clone();
  ASSERT_NE(cloned, nullptr);
  EXPECT_EQ(cloned->key(), key.key());
  EXPECT_EQ(cloned->tag(), key.tag());
  EXPECT_STREQ(cloned->familyName(), key.familyName());
  EXPECT_EQ(cloned->groupName(), key.groupName());
  EXPECT_EQ(cloned->tagName(), key.tagName());
}

// Test write on cloned key produces the same output
TEST_F(KeyWriteTest_36, ClonedKeyWriteMatchesOriginal_36) {
  Exiv2::ExifKey key("Exif.Image.ImageWidth");
  auto cloned = key.clone();
  
  std::ostringstream os1, os2;
  key.write(os1);
  cloned->write(os2);
  EXPECT_EQ(os1.str(), os2.str());
}

// Test IptcKey
TEST_F(KeyWriteTest_36, IptcKeyWriteOutputsKey_36) {
  Exiv2::IptcKey key("Iptc.Application2.Headline");
  std::ostringstream os;
  key.write(os);
  EXPECT_EQ(os.str(), key.key());
}

TEST_F(KeyWriteTest_36, IptcKeyFamilyName_36) {
  Exiv2::IptcKey key("Iptc.Application2.Headline");
  EXPECT_STREQ(key.familyName(), "Iptc");
}

TEST_F(KeyWriteTest_36, IptcKeyGroupName_36) {
  Exiv2::IptcKey key("Iptc.Application2.Headline");
  EXPECT_EQ(key.groupName(), "Application2");
}

TEST_F(KeyWriteTest_36, IptcKeyTagName_36) {
  Exiv2::IptcKey key("Iptc.Application2.Headline");
  EXPECT_EQ(key.tagName(), "Headline");
}

TEST_F(KeyWriteTest_36, IptcKeyClone_36) {
  Exiv2::IptcKey key("Iptc.Application2.Headline");
  auto cloned = key.clone();
  ASSERT_NE(cloned, nullptr);
  EXPECT_EQ(cloned->key(), key.key());
}

// Test XmpKey
TEST_F(KeyWriteTest_36, XmpKeyWriteOutputsKey_36) {
  Exiv2::XmpKey key("Xmp.dc.title");
  std::ostringstream os;
  key.write(os);
  EXPECT_EQ(os.str(), key.key());
}

TEST_F(KeyWriteTest_36, XmpKeyFamilyName_36) {
  Exiv2::XmpKey key("Xmp.dc.title");
  EXPECT_STREQ(key.familyName(), "Xmp");
}

TEST_F(KeyWriteTest_36, XmpKeyGroupName_36) {
  Exiv2::XmpKey key("Xmp.dc.title");
  EXPECT_EQ(key.groupName(), "dc");
}

TEST_F(KeyWriteTest_36, XmpKeyTagName_36) {
  Exiv2::XmpKey key("Xmp.dc.title");
  EXPECT_EQ(key.tagName(), "title");
}

TEST_F(KeyWriteTest_36, XmpKeyClone_36) {
  Exiv2::XmpKey key("Xmp.dc.title");
  auto cloned = key.clone();
  ASSERT_NE(cloned, nullptr);
  EXPECT_EQ(cloned->key(), key.key());
}

// Test write to an already populated stream appends correctly
TEST_F(KeyWriteTest_36, WriteAppendsToStream_36) {
  Exiv2::ExifKey key("Exif.Photo.DateTimeOriginal");
  std::ostringstream os;
  os << "prefix:";
  key.write(os);
  EXPECT_EQ(os.str(), "prefix:" + key.key());
}

// Test write returns a reference to the same stream
TEST_F(KeyWriteTest_36, WriteReturnsStreamReference_36) {
  Exiv2::ExifKey key("Exif.Photo.DateTimeOriginal");
  std::ostringstream os;
  std::ostream& result = key.write(os);
  EXPECT_EQ(&result, &os);
}

// Test different ExifKey groups
TEST_F(KeyWriteTest_36, ExifKeyImageGroup_36) {
  Exiv2::ExifKey key("Exif.Image.Make");
  EXPECT_EQ(key.key(), "Exif.Image.Make");
  EXPECT_EQ(key.groupName(), "Image");
  EXPECT_EQ(key.tagName(), "Make");
  EXPECT_STREQ(key.familyName(), "Exif");
}

// Test that tagDesc returns a string (may be empty for some tags but should not throw)
TEST_F(KeyWriteTest_36, ExifKeyTagDesc_36) {
  Exiv2::ExifKey key("Exif.Photo.DateTimeOriginal");
  // Should not throw, result is a string
  std::string desc = key.tagDesc();
  // Just verify it's callable; the description can be empty or non-empty
  SUCCEED();
}

// Test constructing ExifKey with tag number
TEST_F(KeyWriteTest_36, ExifKeyFromTagNumber_36) {
  // Tag 0x010f is "Make" in IFD0/Image
  Exiv2::ExifKey key(0x010f, "Image");
  EXPECT_EQ(key.tag(), 0x010f);
  EXPECT_EQ(key.tagName(), "Make");
}

// Error case: invalid key string should throw
TEST_F(KeyWriteTest_36, InvalidExifKeyThrows_36) {
  EXPECT_THROW(Exiv2::ExifKey key("InvalidKeyString"), Exiv2::Error);
}

TEST_F(KeyWriteTest_36, InvalidIptcKeyThrows_36) {
  EXPECT_THROW(Exiv2::IptcKey key("InvalidKeyString"), Exiv2::Error);
}

TEST_F(KeyWriteTest_36, InvalidXmpKeyThrows_36) {
  EXPECT_THROW(Exiv2::XmpKey key("InvalidKeyString"), Exiv2::Error);
}

// Test writing empty stream
TEST_F(KeyWriteTest_36, WriteToEmptyStream_36) {
  Exiv2::ExifKey key("Exif.Image.ImageWidth");
  std::ostringstream os;
  key.write(os);
  EXPECT_FALSE(os.str().empty());
  EXPECT_EQ(os.str(), "Exif.Image.ImageWidth");
}

// Test copy construction via clone preserves all properties
TEST_F(KeyWriteTest_36, ClonePreservesAllProperties_36) {
  Exiv2::ExifKey key("Exif.Photo.ISOSpeedRatings");
  auto cloned = key.clone();
  
  EXPECT_EQ(cloned->key(), key.key());
  EXPECT_STREQ(cloned->familyName(), key.familyName());
  EXPECT_EQ(cloned->groupName(), key.groupName());
  EXPECT_EQ(cloned->tagName(), key.tagName());
  EXPECT_EQ(cloned->tag(), key.tag());
  EXPECT_EQ(cloned->tagLabel(), key.tagLabel());
  EXPECT_EQ(cloned->tagDesc(), key.tagDesc());
}

// Test multiple writes to the same stream
TEST_F(KeyWriteTest_36, MultipleWritesToSameStream_36) {
  Exiv2::ExifKey key1("Exif.Image.Make");
  Exiv2::ExifKey key2("Exif.Image.Model");
  std::ostringstream os;
  key1.write(os);
  os << ",";
  key2.write(os);
  EXPECT_EQ(os.str(), "Exif.Image.Make,Exif.Image.Model");
}

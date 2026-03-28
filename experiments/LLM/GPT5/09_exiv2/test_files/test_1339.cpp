// File: test_exifkey_tagname_1339.cpp
#include <gtest/gtest.h>

#include <exiv2/tags.hpp>
#include <exiv2/error.hpp>

#include <cstdint>
#include <memory>
#include <string>

namespace {

using Exiv2::ExifKey;

// NOTE: These tests treat ExifKey as a black box and only validate observable behavior
// via the public interface (constructors/copy/assignment/setIdx/clone/tagName).

TEST(ExifKeyTagNameTest_1339, TagNameFromWellFormedKeyString_ImageMake_1339) {
  ExifKey key("Exif.Image.Make");
  EXPECT_EQ(key.tagName(), "Make");
}

TEST(ExifKeyTagNameTest_1339, TagNameFromWellFormedKeyString_PhotoDateTimeOriginal_1339) {
  ExifKey key("Exif.Photo.DateTimeOriginal");
  EXPECT_EQ(key.tagName(), "DateTimeOriginal");
}

TEST(ExifKeyTagNameTest_1339, TagNameFromTagAndGroupName_KnownTag_1339) {
  // 0x010F is a widely-used Exif tag for "Make" in the Image (IFD0) group.
  ExifKey key(static_cast<uint16_t>(0x010F), std::string("Image"));
  EXPECT_EQ(key.tagName(), "Make");
}

TEST(ExifKeyTagNameTest_1339, SetIdxDoesNotChangeTagName_1339) {
  ExifKey key("Exif.Photo.DateTimeOriginal");
  const std::string before = key.tagName();

  key.setIdx(0);
  EXPECT_EQ(key.tagName(), before);

  key.setIdx(3);
  EXPECT_EQ(key.tagName(), before);

  key.setIdx(-1);
  EXPECT_EQ(key.tagName(), before);
}

TEST(ExifKeyTagNameTest_1339, CopyConstructorPreservesTagName_1339) {
  ExifKey original("Exif.Image.Make");
  ExifKey copy(original);
  EXPECT_EQ(copy.tagName(), original.tagName());
}

TEST(ExifKeyTagNameTest_1339, CopyAssignmentPreservesTagName_1339) {
  ExifKey lhs("Exif.Photo.DateTimeOriginal");
  ExifKey rhs("Exif.Image.Make");

  const std::string rhsName = rhs.tagName();
  lhs = rhs;

  EXPECT_EQ(lhs.tagName(), rhsName);
  EXPECT_EQ(lhs.tagName(), rhs.tagName());
}

TEST(ExifKeyTagNameTest_1339, ClonePreservesTagName_1339) {
  ExifKey key("Exif.Image.Make");
  const std::string name = key.tagName();

  auto cloned = key.clone();
  ASSERT_TRUE(static_cast<bool>(cloned));
  EXPECT_EQ(cloned->tagName(), name);
}

TEST(ExifKeyTagNameTest_1339, InvalidKeyStringThrows_1339) {
  // Observable error case: invalid key formatting should be rejected.
  // We only assert the exception type, not the message.
  EXPECT_THROW({ ExifKey bad("NotAValid.ExifKey"); }, Exiv2::Error);
}

TEST(ExifKeyTagNameTest_1339, UnknownTagInKnownGroupProducesNonEmptyTagName_1339) {
  // Boundary-ish case: a tag value that may not exist in the group.
  // We only require that calling tagName() is safe and yields some representation.
  ExifKey key(static_cast<uint16_t>(0xFFFF), std::string("Image"));
  const std::string name = key.tagName();
  EXPECT_FALSE(name.empty());
}

}  // namespace
// TEST_ID 2183
// Unit tests for Exiv2::ExifKey (black-box tests based on public interface only)

#include <gtest/gtest.h>

#include <cstdint>
#include <memory>
#include <string>

#include "exiv2/tags.hpp"

namespace {

void ExpectExifKeyObservablesEqual(const Exiv2::ExifKey& a, const Exiv2::ExifKey& b) {
  // Compare only via public, observable API.
  EXPECT_EQ(a.key(), b.key());
  EXPECT_STREQ(a.familyName(), b.familyName());
  EXPECT_EQ(a.groupName(), b.groupName());
  EXPECT_EQ(a.tagName(), b.tagName());
  EXPECT_EQ(a.tagLabel(), b.tagLabel());
  EXPECT_EQ(a.tagDesc(), b.tagDesc());
  EXPECT_EQ(a.tag(), b.tag());
  EXPECT_EQ(a.defaultTypeId(), b.defaultTypeId());
  EXPECT_EQ(a.ifdId(), b.ifdId());
  EXPECT_EQ(a.idx(), b.idx());
}

}  // namespace

// Use a valid, commonly-used Exiv2 Exif key string format for construction.
// (We do not assert any specific parsing details beyond that the object is usable.)
TEST(ExifKeyTest_2183, ConstructFromString_AllowsCallingPublicAccessors_2183) {
  const std::string kKey = "Exif.Image.Make";

  Exiv2::ExifKey key(kKey);

  EXPECT_NO_THROW({
    (void)key.key();
    (void)key.familyName();
    (void)key.groupName();
    (void)key.tagName();
    (void)key.tagLabel();
    (void)key.tagDesc();
    (void)key.tag();
    (void)key.defaultTypeId();
    (void)key.ifdId();
    (void)key.idx();
  });
}

TEST(ExifKeyTest_2183, CopyConstructor_PreservesObservableProperties_2183) {
  Exiv2::ExifKey original("Exif.Image.Make");
  original.setIdx(7);

  Exiv2::ExifKey copy(original);

  ExpectExifKeyObservablesEqual(original, copy);
}

TEST(ExifKeyTest_2183, CopyAssignment_PreservesObservableProperties_2183) {
  Exiv2::ExifKey source("Exif.Image.Make");
  source.setIdx(3);

  Exiv2::ExifKey dest("Exif.Photo.DateTimeOriginal");
  dest.setIdx(99);

  dest = source;

  ExpectExifKeyObservablesEqual(source, dest);
}

TEST(ExifKeyTest_2183, SelfAssignment_IsSafeAndPreservesObservableProperties_2183) {
  Exiv2::ExifKey key("Exif.Image.Make");
  key.setIdx(11);

  // Snapshot through public API before self-assignment.
  const std::string before_key = key.key();
  const std::string before_group = key.groupName();
  const std::string before_tagName = key.tagName();
  const std::string before_tagLabel = key.tagLabel();
  const std::string before_tagDesc = key.tagDesc();
  const uint16_t before_tag = key.tag();
  const auto before_type = key.defaultTypeId();
  const auto before_ifd = key.ifdId();
  const int before_idx = key.idx();
  const char* before_family = key.familyName();

  key = key;

  EXPECT_EQ(before_key, key.key());
  EXPECT_EQ(before_group, key.groupName());
  EXPECT_EQ(before_tagName, key.tagName());
  EXPECT_EQ(before_tagLabel, key.tagLabel());
  EXPECT_EQ(before_tagDesc, key.tagDesc());
  EXPECT_EQ(before_tag, key.tag());
  EXPECT_EQ(before_type, key.defaultTypeId());
  EXPECT_EQ(before_ifd, key.ifdId());
  EXPECT_EQ(before_idx, key.idx());
  EXPECT_STREQ(before_family, key.familyName());
}

TEST(ExifKeyTest_2183, Clone_ReturnsEquivalentKeyObject_2183) {
  Exiv2::ExifKey original("Exif.Image.Make");
  original.setIdx(5);

  Exiv2::ExifKey::UniquePtr cloned = original.clone();
  ASSERT_NE(cloned.get(), nullptr);

  // clone() returns a Key::UniquePtr-like type; treat it as ExifKey via the API we have.
  // We only compare observables using the virtual/public interface on ExifKey.
  const auto* cloned_exif = dynamic_cast<const Exiv2::ExifKey*>(cloned.get());
  ASSERT_NE(cloned_exif, nullptr);

  ExpectExifKeyObservablesEqual(original, *cloned_exif);
}

TEST(ExifKeyTest_2183, SetIdx_UpdatesIdxObservable_2183) {
  Exiv2::ExifKey key("Exif.Image.Make");

  key.setIdx(0);
  EXPECT_EQ(key.idx(), 0);

  key.setIdx(1);
  EXPECT_EQ(key.idx(), 1);

  key.setIdx(12345);
  EXPECT_EQ(key.idx(), 12345);

  // Boundary-ish values for int (without assuming internal constraints).
  key.setIdx(-1);
  EXPECT_EQ(key.idx(), -1);
}

TEST(ExifKeyTest_2183, ConstructFromTagAndGroupName_ObjectIsUsable_2183) {
  // We avoid asserting any specific mapping/formatting; only that the object can be used via public API.
  const uint16_t tag = static_cast<uint16_t>(0x010F);  // Common EXIF tag id for "Make" in many contexts.
  const std::string group = "Image";

  Exiv2::ExifKey key(tag, group);

  EXPECT_NO_THROW({
    (void)key.key();
    (void)key.familyName();
    (void)key.groupName();
    (void)key.tagName();
    (void)key.tagLabel();
    (void)key.tagDesc();
    (void)key.tag();
    (void)key.defaultTypeId();
    (void)key.ifdId();
    (void)key.idx();
  });
}
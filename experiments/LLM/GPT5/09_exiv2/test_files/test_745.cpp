// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_exifdatum_tagname_745.cpp
//
// Unit tests for Exiv2::Exifdatum::tagName()
// Interface under test (black-box): Exiv2::Exifdatum::tagName()

#include <gtest/gtest.h>

#include <exiv2/exif.hpp>
#include <exiv2/tags.hpp>

namespace {

// TEST_ID = 745
class ExifdatumTest_745 : public ::testing::Test {};

TEST_F(ExifdatumTest_745, TagNameMatchesUnderlyingExifKey_FromStringKey_745) {
  const Exiv2::ExifKey key("Exif.Image.Make");
  const Exiv2::Exifdatum datum(key, nullptr);

  // Observable contract from the implementation snippet:
  // tagName() should return key_->tagName() when a key exists.
  EXPECT_EQ(datum.tagName(), key.tagName());
}

TEST_F(ExifdatumTest_745, TagNameMatchesUnderlyingExifKey_FromTagAndGroupCtor_745) {
  // Use the (tag, groupName) constructor; avoid assuming any specific tagName text.
  const Exiv2::ExifKey key(static_cast<uint16_t>(0x010F), std::string("Image"));  // 0x010F commonly "Make"
  const Exiv2::Exifdatum datum(key, nullptr);

  EXPECT_EQ(datum.tagName(), key.tagName());
}

TEST_F(ExifdatumTest_745, TagNameStableAcrossCopyConstruction_745) {
  const Exiv2::ExifKey key("Exif.Photo.FNumber");
  const Exiv2::Exifdatum original(key, nullptr);

  const Exiv2::Exifdatum copy(original);

  EXPECT_EQ(copy.tagName(), original.tagName());
  EXPECT_EQ(copy.tagName(), key.tagName());
}

TEST_F(ExifdatumTest_745, TagNameStableAcrossCopyAssignment_745) {
  const Exiv2::ExifKey keyA("Exif.Image.Model");
  const Exiv2::ExifKey keyB("Exif.Photo.ExposureTime");

  const Exiv2::Exifdatum src(keyB, nullptr);
  Exiv2::Exifdatum dst(keyA, nullptr);

  // Copy-assign and verify observable behavior via tagName().
  dst = src;

  EXPECT_EQ(dst.tagName(), src.tagName());
  EXPECT_EQ(dst.tagName(), keyB.tagName());
}

TEST_F(ExifdatumTest_745, TagNameMatchesUnderlyingExifKey_ForEmptyKeyStringBoundary_745) {
  // Boundary: an empty key string. We do not assume what ExifKey::tagName() returns,
  // only that Exifdatum forwards to its underlying key.
  const Exiv2::ExifKey key(std::string{});
  const Exiv2::Exifdatum datum(key, nullptr);

  EXPECT_EQ(datum.tagName(), key.tagName());
}

}  // namespace
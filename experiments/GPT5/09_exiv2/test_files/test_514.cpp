// SPDX-License-Identifier: GPL-2.0-or-later
// ----------------------------------------------------------------------------
// Test file for Exiv2::exposureMode (easyaccess.cpp)
//
// The TEST_ID is 514
// ----------------------------------------------------------------------------

#include <gtest/gtest.h>

#include <exiv2/easyaccess.hpp>
#include <exiv2/exif.hpp>
#include <exiv2/value.hpp>

#include <cstdint>
#include <string>
#include <vector>

namespace {

class ExposureModeTest_514 : public ::testing::Test {
 protected:
  static void addUShort(Exiv2::ExifData& ed, const std::string& key, uint16_t v) {
    Exiv2::ExifKey exifKey(key);
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::unsignedShort);
    ASSERT_TRUE(value.get() != nullptr);
    value->read(std::to_string(v));
    ed.add(exifKey, value.get());  // ExifData clones the value internally.
  }

  static bool isOneOfKeys(const std::string& actual, const std::vector<std::string>& keys) {
    for (const auto& k : keys) {
      if (actual == k) return true;
    }
    return false;
  }
};

TEST_F(ExposureModeTest_514, ReturnsEndWhenExifDataEmpty_514) {
  Exiv2::ExifData ed;
  const Exiv2::ExifData& ced = ed;

  const auto it = Exiv2::exposureMode(ced);

  EXPECT_EQ(it, ced.end());
}

TEST_F(ExposureModeTest_514, ReturnsEndWhenNoMatchingKeysPresent_514) {
  Exiv2::ExifData ed;
  addUShort(ed, "Exif.Photo.FNumber", 28);  // unrelated key
  addUShort(ed, "Exif.Image.Make", 1);      // also unrelated (type here doesn't matter for lookup)
  const Exiv2::ExifData& ced = ed;

  const auto it = Exiv2::exposureMode(ced);

  EXPECT_EQ(it, ced.end());
}

TEST_F(ExposureModeTest_514, FindsExifPhotoExposureProgramWhenPresent_514) {
  Exiv2::ExifData ed;
  addUShort(ed, "Exif.Photo.ExposureProgram", 3);
  const Exiv2::ExifData& ced = ed;

  const auto it = Exiv2::exposureMode(ced);

  ASSERT_NE(it, ced.end());
  EXPECT_EQ(it->key(), std::string("Exif.Photo.ExposureProgram"));
}

TEST_F(ExposureModeTest_514, FindsExifImageExposureProgramWhenPresent_514) {
  Exiv2::ExifData ed;
  addUShort(ed, "Exif.Image.ExposureProgram", 2);
  const Exiv2::ExifData& ced = ed;

  const auto it = Exiv2::exposureMode(ced);

  ASSERT_NE(it, ced.end());
  EXPECT_EQ(it->key(), std::string("Exif.Image.ExposureProgram"));
}

TEST_F(ExposureModeTest_514, FindsOneOfMatchingKeysWhenMultiplePresent_514) {
  // The function searches across a fixed set of keys. When multiple are present,
  // the observable contract we test is: it returns an iterator to *one* of those
  // present matching keys (not end, and not an unrelated key).
  Exiv2::ExifData ed;
  addUShort(ed, "Exif.Sony1.ExposureMode", 1);
  addUShort(ed, "Exif.CanonCs.ExposureProgram", 4);
  addUShort(ed, "Exif.Photo.FNumber", 10);  // unrelated
  const Exiv2::ExifData& ced = ed;

  const auto it = Exiv2::exposureMode(ced);

  ASSERT_NE(it, ced.end());

  const std::vector<std::string> expectedAnyOf = {
      "Exif.CanonCs.ExposureProgram",
      "Exif.Sony1.ExposureMode",
  };
  EXPECT_TRUE(isOneOfKeys(it->key(), expectedAnyOf));
}

TEST_F(ExposureModeTest_514, StillReturnsEndAfterClear_514) {
  Exiv2::ExifData ed;
  addUShort(ed, "Exif.Photo.ExposureProgram", 3);
  ed.clear();
  const Exiv2::ExifData& ced = ed;

  const auto it = Exiv2::exposureMode(ced);

  EXPECT_EQ(it, ced.end());
}

}  // namespace
// SPDX-License-Identifier: (GPL-2.0 OR BSD-3-Clause)
// Tests for Exiv2::exposureIndex (easyaccess.cpp)

#include <gtest/gtest.h>

#include <exiv2/exif.hpp>
#include <exiv2/value.hpp>

#include <memory>
#include <string>

namespace Exiv2 {
// Function under test (defined in easyaccess.cpp)
ExifData::const_iterator exposureIndex(const ExifData& ed);
}  // namespace Exiv2

namespace {

class ExposureIndexTest_541 : public ::testing::Test {
 protected:
  static void addUShort(Exiv2::ExifData& ed, const std::string& keyStr, uint16_t v) {
    Exiv2::ExifKey key(keyStr);
    std::unique_ptr<Exiv2::Value> val(Exiv2::Value::create(Exiv2::unsignedShort));
    ASSERT_TRUE(val.get() != nullptr);
    val->read(std::to_string(v));
    ed.add(key, val.get());  // ExifData::add clones the value internally
  }
};

TEST_F(ExposureIndexTest_541, ReturnsEndWhenExifDataEmpty_541) {
  Exiv2::ExifData ed;

  const auto it = Exiv2::exposureIndex(ed);

  EXPECT_EQ(it, ed.end());
}

TEST_F(ExposureIndexTest_541, ReturnsEndWhenNeitherKeyPresent_541) {
  Exiv2::ExifData ed;
  addUShort(ed, "Exif.Photo.FocalLength", 50);
  addUShort(ed, "Exif.Image.ISOSpeedRatings", 200);

  const auto it = Exiv2::exposureIndex(ed);

  EXPECT_EQ(it, ed.end());
}

TEST_F(ExposureIndexTest_541, FindsExifPhotoExposureIndexWhenPresent_541) {
  Exiv2::ExifData ed;
  addUShort(ed, "Exif.Photo.ExposureIndex", 123);

  const auto it = Exiv2::exposureIndex(ed);

  EXPECT_NE(it, ed.end());
  EXPECT_EQ(it, ed.findKey(Exiv2::ExifKey("Exif.Photo.ExposureIndex")));
}

TEST_F(ExposureIndexTest_541, FindsExifImageExposureIndexWhenPhotoKeyAbsent_541) {
  Exiv2::ExifData ed;
  addUShort(ed, "Exif.Image.ExposureIndex", 77);

  const auto it = Exiv2::exposureIndex(ed);

  EXPECT_NE(it, ed.end());
  EXPECT_EQ(it, ed.findKey(Exiv2::ExifKey("Exif.Image.ExposureIndex")));
}

TEST_F(ExposureIndexTest_541, PrefersExifPhotoExposureIndexWhenBothPresent_541) {
  Exiv2::ExifData ed;
  addUShort(ed, "Exif.Image.ExposureIndex", 77);
  addUShort(ed, "Exif.Photo.ExposureIndex", 123);

  const auto it = Exiv2::exposureIndex(ed);

  EXPECT_NE(it, ed.end());
  EXPECT_EQ(it, ed.findKey(Exiv2::ExifKey("Exif.Photo.ExposureIndex")));
}

}  // namespace
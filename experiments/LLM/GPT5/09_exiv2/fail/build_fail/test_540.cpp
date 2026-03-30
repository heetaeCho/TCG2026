// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_easyaccess_flashEnergy_540.cpp

#include <gtest/gtest.h>

#include <exiv2/easyaccess.hpp>
#include <exiv2/exif.hpp>

namespace {

class FlashEnergyTest_540 : public ::testing::Test {
 protected:
  static void addExif(Exiv2::ExifData& ed, const char* keyStr, const char* valueStr = "1") {
    Exiv2::ExifKey key(keyStr);
    Exiv2::Exifdatum datum(key);
    datum.setValue(valueStr);  // uses public interface; value content is not important for lookup
    ed.add(datum);
  }
};

TEST_F(FlashEnergyTest_540, ReturnsEndWhenEmpty_540) {
  Exiv2::ExifData ed;

  const auto it = Exiv2::flashEnergy(static_cast<const Exiv2::ExifData&>(ed));
  EXPECT_EQ(it, static_cast<const Exiv2::ExifData&>(ed).end());
}

TEST_F(FlashEnergyTest_540, ReturnsEndWhenNeitherKeyPresent_540) {
  Exiv2::ExifData ed;
  addExif(ed, "Exif.Photo.SomeOtherTag", "123");

  const auto it = Exiv2::flashEnergy(static_cast<const Exiv2::ExifData&>(ed));
  EXPECT_EQ(it, static_cast<const Exiv2::ExifData&>(ed).end());
}

TEST_F(FlashEnergyTest_540, ReturnsPhotoFlashEnergyWhenPresent_540) {
  Exiv2::ExifData ed;
  addExif(ed, "Exif.Photo.FlashEnergy", "10");

  const auto it = Exiv2::flashEnergy(static_cast<const Exiv2::ExifData&>(ed));
  ASSERT_NE(it, static_cast<const Exiv2::ExifData&>(ed).end());
  EXPECT_EQ(it->key(), std::string("Exif.Photo.FlashEnergy"));
}

TEST_F(FlashEnergyTest_540, ReturnsImageFlashEnergyWhenOnlyImagePresent_540) {
  Exiv2::ExifData ed;
  addExif(ed, "Exif.Image.FlashEnergy", "20");

  const auto it = Exiv2::flashEnergy(static_cast<const Exiv2::ExifData&>(ed));
  ASSERT_NE(it, static_cast<const Exiv2::ExifData&>(ed).end());
  EXPECT_EQ(it->key(), std::string("Exif.Image.FlashEnergy"));
}

TEST_F(FlashEnergyTest_540, PrefersPhotoKeyWhenBothPresent_540) {
  Exiv2::ExifData ed;
  addExif(ed, "Exif.Image.FlashEnergy", "20");
  addExif(ed, "Exif.Photo.FlashEnergy", "10");

  const auto it = Exiv2::flashEnergy(static_cast<const Exiv2::ExifData&>(ed));
  ASSERT_NE(it, static_cast<const Exiv2::ExifData&>(ed).end());
  EXPECT_EQ(it->key(), std::string("Exif.Photo.FlashEnergy"));
}

TEST_F(FlashEnergyTest_540, ReturnedIteratorMatchesFindKeyForResolvedKey_540) {
  Exiv2::ExifData ed;
  addExif(ed, "Exif.Image.FlashEnergy", "20");

  const auto& ced = static_cast<const Exiv2::ExifData&>(ed);
  const auto it = Exiv2::flashEnergy(ced);

  ASSERT_NE(it, ced.end());
  EXPECT_EQ(it, ced.findKey(Exiv2::ExifKey("Exif.Image.FlashEnergy")));
}

}  // namespace
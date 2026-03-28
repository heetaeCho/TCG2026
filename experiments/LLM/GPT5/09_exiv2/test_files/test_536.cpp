// File: test_easyaccess_flash_536.cpp
// Unit tests for Exiv2::flash(const ExifData&)
//
// Constraints:
// - Treat implementation as black box.
// - Validate only observable behavior via public interface.

#include <gtest/gtest.h>

#include <exiv2/exiv2.hpp>  // Exiv2::ExifData, Exiv2::ExifKey, Exiv2::flash

namespace {

using Exiv2::ExifData;

TEST(FlashEasyAccessTest_536, ReturnsEndWhenExifDataIsEmpty_536) {
  const ExifData ed;
  const auto it = Exiv2::flash(ed);
  EXPECT_EQ(it, ed.end());
}

TEST(FlashEasyAccessTest_536, ReturnsEndWhenNoCandidateKeysExist_536) {
  ExifData ed;
  // Add some unrelated tags.
  ed["Exif.Image.Make"] = "DummyMake";
  ed["Exif.Image.Model"] = "DummyModel";

  const ExifData& ced = ed;
  const auto it = Exiv2::flash(ced);
  EXPECT_EQ(it, ced.end());
}

TEST(FlashEasyAccessTest_536, FindsExifPhotoFlashWhenPresent_536) {
  ExifData ed;
  ed["Exif.Photo.Flash"] = "1";

  const ExifData& ced = ed;
  const auto it = Exiv2::flash(ced);

  ASSERT_NE(it, ced.end());
  EXPECT_EQ(it->key(), std::string("Exif.Photo.Flash"));

  // Cross-check using the public findKey API.
  const auto fk = ced.findKey(Exiv2::ExifKey("Exif.Photo.Flash"));
  EXPECT_NE(fk, ced.end());
  EXPECT_EQ(it, fk);
}

TEST(FlashEasyAccessTest_536, FindsLaterKeyWhenEarlierKeysAbsent_536) {
  ExifData ed;
  ed["Exif.Sony2.FlashAction"] = "0";

  const ExifData& ced = ed;
  const auto it = Exiv2::flash(ced);

  ASSERT_NE(it, ced.end());
  EXPECT_EQ(it->key(), std::string("Exif.Sony2.FlashAction"));

  const auto fk = ced.findKey(Exiv2::ExifKey("Exif.Sony2.FlashAction"));
  EXPECT_NE(fk, ced.end());
  EXPECT_EQ(it, fk);
}

TEST(FlashEasyAccessTest_536, PrefersFirstMatchByKeyPriorityOrder_536) {
  // The implementation checks keys in this order:
  // "Exif.Photo.Flash", "Exif.Image.Flash", "Exif.Pentax.Flash", "Exif.PentaxDng.Flash",
  // "Exif.Sony1.FlashAction", "Exif.Sony2.FlashAction"
  ExifData ed;

  // Add multiple candidates; the function should return the first match in the priority list.
  ed["Exif.Sony2.FlashAction"] = "0";
  ed["Exif.Image.Flash"] = "1";
  ed["Exif.Photo.Flash"] = "1";  // Highest priority among these.

  const ExifData& ced = ed;
  const auto it = Exiv2::flash(ced);

  ASSERT_NE(it, ced.end());
  EXPECT_EQ(it->key(), std::string("Exif.Photo.Flash"));
}

TEST(FlashEasyAccessTest_536, PrefersExifImageFlashOverPentaxWhenPhotoAbsent_536) {
  ExifData ed;

  // No "Exif.Photo.Flash"
  ed["Exif.Pentax.Flash"] = "2";
  ed["Exif.Image.Flash"] = "1";

  const ExifData& ced = ed;
  const auto it = Exiv2::flash(ced);

  ASSERT_NE(it, ced.end());
  EXPECT_EQ(it->key(), std::string("Exif.Image.Flash"));
}

}  // namespace
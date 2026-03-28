// File: test_easyaccess_fnumber_528.cpp
#include <gtest/gtest.h>

#include <exiv2/easyaccess.hpp>
#include <exiv2/exif.hpp>
#include <exiv2/value.hpp>

#include <memory>
#include <string>

namespace {

using Exiv2::ExifData;
using Exiv2::ExifKey;

// Helper: add a rational-like value to ExifData under `keyStr`.
// We only rely on public Exiv2 interfaces; we don't assume how values are stored internally.
static void addRationalLike(ExifData& ed, const std::string& keyStr, const std::string& valueStr) {
  // FNumber is typically a rational; Exiv2 supports multiple rational-ish types.
  // Use a common one; ExifData::add clones/copies the Value internally.
  std::unique_ptr<Exiv2::Value> v(Exiv2::Value::create(Exiv2::unsignedRational));
  ASSERT_TRUE(v != nullptr);
  ASSERT_NO_THROW(v->read(valueStr));
  ASSERT_NO_THROW(ed.add(ExifKey(keyStr), v.get()));
}

class EasyAccessFNumberTest_528 : public ::testing::Test {
 protected:
  static constexpr const char* kPhoto = "Exif.Photo.FNumber";
  static constexpr const char* kImage = "Exif.Image.FNumber";
  static constexpr const char* kPentax = "Exif.Pentax.FNumber";
  static constexpr const char* kPentaxDng = "Exif.PentaxDng.FNumber";
  static constexpr const char* kSamsung2 = "Exif.Samsung2.FNumber";
};

TEST_F(EasyAccessFNumberTest_528, ReturnsEndWhenEmpty_528) {
  ExifData ed;
  auto it = Exiv2::fNumber(ed);
  EXPECT_EQ(it, ed.end());
}

TEST_F(EasyAccessFNumberTest_528, ReturnsEndWhenNoMatchingKeysPresent_528) {
  ExifData ed;
  addRationalLike(ed, "Exif.Photo.ExposureTime", "1/125");
  addRationalLike(ed, "Exif.Photo.FocalLength", "50/1");

  auto it = Exiv2::fNumber(ed);
  EXPECT_EQ(it, ed.end());
}

TEST_F(EasyAccessFNumberTest_528, FindsExifPhotoFNumberWhenPresent_528) {
  ExifData ed;
  addRationalLike(ed, kPhoto, "28/10");  // f/2.8

  auto it = Exiv2::fNumber(ed);
  ASSERT_NE(it, ed.end());
  EXPECT_EQ(it->key(), std::string(kPhoto));
}

TEST_F(EasyAccessFNumberTest_528, FindsLaterKeyWhenEarlierOnesMissing_528) {
  ExifData ed;
  addRationalLike(ed, kPentaxDng, "4/1");  // f/4

  auto it = Exiv2::fNumber(ed);
  ASSERT_NE(it, ed.end());
  EXPECT_EQ(it->key(), std::string(kPentaxDng));
}

TEST_F(EasyAccessFNumberTest_528, RespectsPriorityOrderWhenMultipleCandidatesExist_528) {
  // Priority (per implementation): Photo, Image, Pentax, PentaxDng, Samsung2
  ExifData ed;
  addRationalLike(ed, kSamsung2, "56/10");   // f/5.6
  addRationalLike(ed, kPentaxDng, "4/1");    // f/4
  addRationalLike(ed, kImage, "22/10");      // f/2.2
  addRationalLike(ed, kPhoto, "18/10");      // f/1.8

  auto it = Exiv2::fNumber(ed);
  ASSERT_NE(it, ed.end());
  EXPECT_EQ(it->key(), std::string(kPhoto));  // highest priority
}

TEST_F(EasyAccessFNumberTest_528, StillFindsAfterSorting_528) {
  ExifData ed;
  addRationalLike(ed, kPentax, "2/1");  // f/2
  addRationalLike(ed, "Exif.Photo.ExposureTime", "1/60");

  // Sorting should not affect whether a matching metadatum can be found via the public API.
  ASSERT_NO_THROW(ed.sortByKey());

  auto it = Exiv2::fNumber(ed);
  ASSERT_NE(it, ed.end());
  EXPECT_EQ(it->key(), std::string(kPentax));
}

}  // namespace
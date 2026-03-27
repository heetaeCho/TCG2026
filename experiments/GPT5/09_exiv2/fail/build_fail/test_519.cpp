// TEST_ID 519
// Unit tests for Exiv2::lensName (easyaccess.cpp)
// Focus: observable selection of lens-related Exif keys via returned const_iterator.

#include <gtest/gtest.h>

#include <exiv2/easyaccess.hpp>
#include <exiv2/exif.hpp>
#include <exiv2/value.hpp>

#include <memory>
#include <string>

namespace {

using Exiv2::ExifData;
using Exiv2::ExifKey;
using Exiv2::Value;

static void AddAscii(ExifData& ed, const std::string& key, const std::string& text) {
  std::unique_ptr<Value> v(Value::create(Exiv2::asciiString));
  ASSERT_TRUE(v.get() != nullptr);
  // Value::read parses from string representation.
  ASSERT_NO_THROW(v->read(text));
  ASSERT_NO_THROW(ed.add(ExifKey(key), v.get()));
}

static void AddUShort(ExifData& ed, const std::string& key, uint16_t n) {
  std::unique_ptr<Value> v(Value::create(Exiv2::unsignedShort));
  ASSERT_TRUE(v.get() != nullptr);
  ASSERT_NO_THROW(v->read(std::to_string(n)));
  ASSERT_NO_THROW(ed.add(ExifKey(key), v.get()));
}

class LensNameTest_519 : public ::testing::Test {};

}  // namespace

TEST_F(LensNameTest_519, EmptyExifDataReturnsEnd_519) {
  ExifData ed;
  const auto it = Exiv2::lensName(ed);
  EXPECT_EQ(it, ed.end());
}

TEST_F(LensNameTest_519, NoMatchingKeysReturnsEnd_519) {
  ExifData ed;
  AddAscii(ed, "Exif.Photo.DateTimeOriginal", "2020:01:01 00:00:00");
  AddAscii(ed, "Exif.Image.Make", "TestMake");
  const auto it = Exiv2::lensName(ed);
  EXPECT_EQ(it, ed.end());
}

TEST_F(LensNameTest_519, FindsSingleSupportedKey_LensModel_519) {
  ExifData ed;
  AddAscii(ed, "Exif.Photo.LensModel", "UnitTest Lens 50mm");
  const auto it = Exiv2::lensName(ed);

  ASSERT_NE(it, ed.end());
  EXPECT_EQ(it->key(), std::string("Exif.Photo.LensModel"));
  EXPECT_EQ(it->toString(), std::string("UnitTest Lens 50mm"));
}

TEST_F(LensNameTest_519, PrefersEarlierKeyWhenMultipleArePresent_CanonCsVsPhotoLensModel_519) {
  ExifData ed;
  AddAscii(ed, "Exif.Photo.LensModel", "Photo LensModel");
  AddAscii(ed, "Exif.CanonCs.LensType", "CanonCs LensType");  // listed earlier than Exif.Photo.LensModel

  const auto it = Exiv2::lensName(ed);

  ASSERT_NE(it, ed.end());
  EXPECT_EQ(it->key(), std::string("Exif.CanonCs.LensType"));
  EXPECT_EQ(it->toString(), std::string("CanonCs LensType"));
}

TEST_F(LensNameTest_519, PrefersExifPhotoLensModelOverExifCanonLensModel_519) {
  ExifData ed;
  AddAscii(ed, "Exif.Canon.LensModel", "Canon LensModel");
  AddAscii(ed, "Exif.Photo.LensModel", "Photo LensModel");  // listed earlier than Exif.Canon.LensModel

  const auto it = Exiv2::lensName(ed);

  ASSERT_NE(it, ed.end());
  EXPECT_EQ(it->key(), std::string("Exif.Photo.LensModel"));
  EXPECT_EQ(it->toString(), std::string("Photo LensModel"));
}

TEST_F(LensNameTest_519, NikonLd4ZeroValueIsSkippedInFavorOfAnotherAvailableLensKey_519) {
  ExifData ed;

  // NikonLd4 keys are present in the search list; helper name indicates zero should be skipped.
  AddUShort(ed, "Exif.NikonLd4.LensIDNumber", 0);
  AddAscii(ed, "Exif.Photo.LensModel", "Fallback LensModel");

  const auto it = Exiv2::lensName(ed);

  ASSERT_NE(it, ed.end());
  EXPECT_EQ(it->key(), std::string("Exif.Photo.LensModel"));
  EXPECT_EQ(it->toString(), std::string("Fallback LensModel"));
}

TEST_F(LensNameTest_519, NikonLd4NonZeroValueIsReturnedWhenPresent_519) {
  ExifData ed;

  AddUShort(ed, "Exif.NikonLd4.LensIDNumber", 123);
  AddAscii(ed, "Exif.Photo.LensModel", "Also Present");

  const auto it = Exiv2::lensName(ed);

  ASSERT_NE(it, ed.end());
  EXPECT_EQ(it->key(), std::string("Exif.NikonLd4.LensIDNumber"));
  // We only require it's not "0" and is stable as a string representation.
  EXPECT_NE(it->toString(), std::string("0"));
}

TEST_F(LensNameTest_519, Boundary_MatchingKeyAtEndOfList_ExifNikon3Lens_519) {
  ExifData ed;

  // Last key in the hardcoded list in lensName():
  // "Exif.Nikon3.Lens"
  AddAscii(ed, "Exif.Nikon3.Lens", "Nikon3 Lens Value");

  const auto it = Exiv2::lensName(ed);

  ASSERT_NE(it, ed.end());
  EXPECT_EQ(it->key(), std::string("Exif.Nikon3.Lens"));
  EXPECT_EQ(it->toString(), std::string("Nikon3 Lens Value"));
}
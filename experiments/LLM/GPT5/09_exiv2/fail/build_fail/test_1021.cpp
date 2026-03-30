// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_minoltamn_int_resolveLens0x34_1021.cpp
//
// TEST_ID is 1021
//
// These tests exercise Exiv2::Internal::resolveLens0x34 via observable stream output.
// The function has internal linkage in minoltamn_int.cpp, so we include the .cpp here
// to compile the tests in the same translation unit.

#include <gtest/gtest.h>

#include <exiv2/exif.hpp>
#include <exiv2/value.hpp>

#include <sstream>
#include <string>

// Include the implementation to access the TU-local static function under test.
#include "minoltamn_int.cpp"

namespace {

// Helper to create a Value that can be added into ExifData.
static Exiv2::Value::UniquePtr makeValueFromString(Exiv2::TypeId type, const std::string& s) {
  auto v = Exiv2::Value::create(type);
  // read(std::string) is part of the public interface.
  v->read(s);
  return v;
}

static void addExifAscii(Exiv2::ExifData& exif, const char* key, const std::string& val) {
  Exiv2::ExifKey exifKey(key);
  auto v = makeValueFromString(Exiv2::asciiString, val);
  exif.add(exifKey, v.get());
}

static void addExifLong(Exiv2::ExifData& exif, const char* key, long val) {
  Exiv2::ExifKey exifKey(key);
  auto v = makeValueFromString(Exiv2::unsignedLong, std::to_string(val));
  exif.add(exifKey, v.get());
}

class ResolveLens0x34Test_1021 : public ::testing::Test {
 protected:
  // A Value instance to pass through to printers (used in fallback path).
  Exiv2::Value::UniquePtr value_ = makeValueFromString(Exiv2::unsignedShort, "3");
};

}  // namespace

TEST_F(ResolveLens0x34Test_1021, ResolvesIndex4WhenModelA77VAndMaxApertureMatches_1021) {
  Exiv2::ExifData exif;
  addExifAscii(exif, "Exif.Image.Model", "SLT-A77V");
  addExifAscii(exif, "Exif.Photo.MaxApertureValue", "760/256");
  // Keep focal length outside the [70,300] range so the second condition does not override.
  addExifLong(exif, "Exif.Photo.FocalLength", 50);

  std::ostringstream os_actual;
  const Exiv2::ExifData* md = &exif;

  // Call the function under test.
  Exiv2::Internal::resolveLens0x34(os_actual, *value_, md);

  // Compare to the observable behavior of resolvedLens for the same lensID/index.
  std::ostringstream os_expected;
  Exiv2::Internal::resolvedLens(os_expected, 0x34, 4);

  EXPECT_EQ(os_expected.str(), os_actual.str());
}

TEST_F(ResolveLens0x34Test_1021, ResolvesIndex3WhenModelA77VAndFocalLengthInRange_1021) {
  Exiv2::ExifData exif;
  addExifAscii(exif, "Exif.Image.Model", "SLT-A77V");
  addExifAscii(exif, "Exif.Photo.MaxApertureValue", "123/256");  // non-matching
  addExifLong(exif, "Exif.Photo.FocalLength", 100);              // in range

  std::ostringstream os_actual;
  const Exiv2::ExifData* md = &exif;

  Exiv2::Internal::resolveLens0x34(os_actual, *value_, md);

  std::ostringstream os_expected;
  Exiv2::Internal::resolvedLens(os_expected, 0x34, 3);

  EXPECT_EQ(os_expected.str(), os_actual.str());
}

TEST_F(ResolveLens0x34Test_1021, Index3OverridesIndex4WhenBothConditionsMatch_1021) {
  Exiv2::ExifData exif;
  addExifAscii(exif, "Exif.Image.Model", "SLT-A77V");
  addExifAscii(exif, "Exif.Photo.MaxApertureValue", "760/256");  // would select index 4
  addExifLong(exif, "Exif.Photo.FocalLength", 70);               // in range, should override to 3

  std::ostringstream os_actual;
  const Exiv2::ExifData* md = &exif;

  Exiv2::Internal::resolveLens0x34(os_actual, *value_, md);

  std::ostringstream os_expected;
  Exiv2::Internal::resolvedLens(os_expected, 0x34, 3);

  EXPECT_EQ(os_expected.str(), os_actual.str());
}

TEST_F(ResolveLens0x34Test_1021, FocalLengthRangeBoundaryLowInclusiveResolvesIndex3_1021) {
  Exiv2::ExifData exif;
  addExifAscii(exif, "Exif.Image.Model", "SLT-A77V");
  addExifAscii(exif, "Exif.Photo.MaxApertureValue", "0/1");  // non-matching
  addExifLong(exif, "Exif.Photo.FocalLength", 70);           // boundary

  std::ostringstream os_actual;
  Exiv2::Internal::resolveLens0x34(os_actual, *value_, &exif);

  std::ostringstream os_expected;
  Exiv2::Internal::resolvedLens(os_expected, 0x34, 3);

  EXPECT_EQ(os_expected.str(), os_actual.str());
}

TEST_F(ResolveLens0x34Test_1021, FocalLengthRangeBoundaryHighInclusiveResolvesIndex3_1021) {
  Exiv2::ExifData exif;
  addExifAscii(exif, "Exif.Image.Model", "SLT-A77V");
  addExifAscii(exif, "Exif.Photo.MaxApertureValue", "0/1");  // non-matching
  addExifLong(exif, "Exif.Photo.FocalLength", 300);          // boundary

  std::ostringstream os_actual;
  Exiv2::Internal::resolveLens0x34(os_actual, *value_, &exif);

  std::ostringstream os_expected;
  Exiv2::Internal::resolvedLens(os_expected, 0x34, 3);

  EXPECT_EQ(os_expected.str(), os_actual.str());
}

TEST_F(ResolveLens0x34Test_1021, FallsBackToPrintTagWhenMetadataIsNull_1021) {
  std::ostringstream os_actual;
  Exiv2::Internal::resolveLens0x34(os_actual, *value_, nullptr);

  // Expected: the same as directly invoking the fallback printer.
  std::ostringstream os_expected;
  Exiv2::Internal::EXV_PRINT_TAG(Exiv2::Internal::minoltaSonyLensID)(os_expected, *value_, nullptr);

  EXPECT_EQ(os_expected.str(), os_actual.str());
}

TEST_F(ResolveLens0x34Test_1021, FallsBackToPrintTagWhenRequiredKeysMissing_1021) {
  Exiv2::ExifData exif;
  // Intentionally do not add Exif.Image.Model / Exif.Photo.MaxApertureValue / Exif.Photo.FocalLength
  // so lookups (if they throw) are caught and the function falls back.

  std::ostringstream os_actual;
  Exiv2::Internal::resolveLens0x34(os_actual, *value_, &exif);

  std::ostringstream os_expected;
  Exiv2::Internal::EXV_PRINT_TAG(Exiv2::Internal::minoltaSonyLensID)(os_expected, *value_, &exif);

  EXPECT_EQ(os_expected.str(), os_actual.str());
}

TEST_F(ResolveLens0x34Test_1021, FallsBackToPrintTagWhenModelDoesNotMatch_1021) {
  Exiv2::ExifData exif;
  addExifAscii(exif, "Exif.Image.Model", "SomeOtherModel");
  addExifAscii(exif, "Exif.Photo.MaxApertureValue", "760/256");
  addExifLong(exif, "Exif.Photo.FocalLength", 100);

  std::ostringstream os_actual;
  Exiv2::Internal::resolveLens0x34(os_actual, *value_, &exif);

  std::ostringstream os_expected;
  Exiv2::Internal::EXV_PRINT_TAG(Exiv2::Internal::minoltaSonyLensID)(os_expected, *value_, &exif);

  EXPECT_EQ(os_expected.str(), os_actual.str());
}
// -----------------------------------------------------------------------------
// Test file for Exiv2::isoSpeed (easyaccess.cpp)
// TEST_ID: 511
// -----------------------------------------------------------------------------

#include <gtest/gtest.h>

#include <exiv2/easyaccess.hpp>
#include <exiv2/exif.hpp>

namespace {

using Exiv2::ExifData;

class IsoSpeedTest_511 : public ::testing::Test {
 protected:
  static std::string KeyOf(const ExifData::const_iterator& it) { return it->key(); }
};

TEST_F(IsoSpeedTest_511, EmptyExifDataReturnsEnd_511) {
  ExifData ed;

  const auto it = Exiv2::isoSpeed(ed);
  EXPECT_EQ(it, ed.end());
}

TEST_F(IsoSpeedTest_511, ReturnsFirstKeyWhenPresentAndValid_511) {
  ExifData ed;
  ed["Exif.Photo.ISOSpeedRatings"] = "100";

  const auto it = Exiv2::isoSpeed(ed);
  ASSERT_NE(it, ed.end());
  EXPECT_EQ(KeyOf(it), "Exif.Photo.ISOSpeedRatings");
}

TEST_F(IsoSpeedTest_511, PrefersEarlierKeyOverLaterWhenBothValid_511) {
  ExifData ed;
  ed["Exif.Photo.ISOSpeedRatings"] = "100";
  ed["Exif.Image.ISOSpeedRatings"] = "200";

  const auto it = Exiv2::isoSpeed(ed);
  ASSERT_NE(it, ed.end());
  EXPECT_EQ(KeyOf(it), "Exif.Photo.ISOSpeedRatings");
}

TEST_F(IsoSpeedTest_511, SkipsNonPositiveOrInvalidAndFindsNextValid_511) {
  ExifData ed;
  // Earlier key present but not usable
  ed["Exif.Photo.ISOSpeedRatings"] = "0";
  // Next key in the search list (per interface-visible keys) is set to a valid value
  ed["Exif.Image.ISOSpeedRatings"] = "200";

  const auto it = Exiv2::isoSpeed(ed);
  ASSERT_NE(it, ed.end());
  EXPECT_EQ(KeyOf(it), "Exif.Image.ISOSpeedRatings");
}

TEST_F(IsoSpeedTest_511, SkipsNonNumericAndFindsNextValid_511) {
  ExifData ed;
  ed["Exif.Photo.ISOSpeedRatings"] = "abc";
  ed["Exif.Image.ISOSpeedRatings"] = "250";

  const auto it = Exiv2::isoSpeed(ed);
  ASSERT_NE(it, ed.end());
  EXPECT_EQ(KeyOf(it), "Exif.Image.ISOSpeedRatings");
}

TEST_F(IsoSpeedTest_511, ReturnsIteratorToTagEvenIfValueContainsInf_511) {
  ExifData ed;
  ed["Exif.Photo.ISOSpeedRatings"] = "inf";

  const auto it = Exiv2::isoSpeed(ed);
  ASSERT_NE(it, ed.end());
  EXPECT_EQ(KeyOf(it), "Exif.Photo.ISOSpeedRatings");
}

TEST_F(IsoSpeedTest_511, WhenIsoIs65535AndNoSensitivityTypeReturnsIsoTag_511) {
  ExifData ed;
  ed["Exif.Photo.ISOSpeedRatings"] = "65535";
  // No Exif.Photo.SensitivityType provided

  const auto it = Exiv2::isoSpeed(ed);
  ASSERT_NE(it, ed.end());
  EXPECT_EQ(KeyOf(it), "Exif.Photo.ISOSpeedRatings");
}

TEST_F(IsoSpeedTest_511, WhenIsoIs65535UsesSensitivityFallbackIfAvailable_511) {
  ExifData ed;
  ed["Exif.Photo.ISOSpeedRatings"] = "65535";
  ed["Exif.Photo.SensitivityType"] = "1";
  ed["Exif.Photo.StandardOutputSensitivity"] = "400";

  const auto it = Exiv2::isoSpeed(ed);
  ASSERT_NE(it, ed.end());
  EXPECT_EQ(KeyOf(it), "Exif.Photo.StandardOutputSensitivity");
}

TEST_F(IsoSpeedTest_511, WhenNoPrimaryIsoKeyUsesSensitivityTypePath_511) {
  ExifData ed;
  ed["Exif.Photo.SensitivityType"] = "3";
  ed["Exif.Photo.ISOSpeed"] = "800";

  const auto it = Exiv2::isoSpeed(ed);
  ASSERT_NE(it, ed.end());
  EXPECT_EQ(KeyOf(it), "Exif.Photo.ISOSpeed");
}

TEST_F(IsoSpeedTest_511, SensitivityTypeOutOfRangeDoesNotSelectFallback_511) {
  ExifData ed;
  ed["Exif.Photo.ISOSpeedRatings"] = "65535";
  ed["Exif.Photo.SensitivityType"] = "99";
  ed["Exif.Photo.StandardOutputSensitivity"] = "400";  // Should not be used for out-of-range type

  const auto it = Exiv2::isoSpeed(ed);
  ASSERT_NE(it, ed.end());
  EXPECT_EQ(KeyOf(it), "Exif.Photo.ISOSpeedRatings");
}

}  // namespace
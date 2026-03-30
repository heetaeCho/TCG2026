// =================================================================================================
//  TEST_ID: 537
//  File: test_easyaccess_serialnumber_537.cpp
//  Unit tests for: Exiv2::serialNumber(const Exiv2::ExifData&)
//  From: ./TestProjects/exiv2/src/easyaccess.cpp
// =================================================================================================

#include <gtest/gtest.h>

#include <exiv2/exif.hpp>

// The function under test is implemented in easyaccess.cpp within namespace Exiv2.
// Depending on your build, you may already have a public header that declares it.
// If not, this forward declaration matches the provided signature.
namespace Exiv2 {
ExifData::const_iterator serialNumber(const ExifData& ed);
}  // namespace Exiv2

namespace {

class SerialNumberEasyAccessTest_537 : public ::testing::Test {
 protected:
  Exiv2::ExifData ed_;

  // Helper: set a value using the public operator[] interface.
  // Exiv2 commonly supports string assignment to Exifdatum.
  void SetKey(const char* key, const char* value) { ed_[key] = value; }
};

TEST_F(SerialNumberEasyAccessTest_537, ReturnsEndWhenExifDataEmpty_537) {
  ASSERT_TRUE(ed_.empty());

  const auto it = Exiv2::serialNumber(ed_);
  EXPECT_EQ(it, ed_.end());
}

TEST_F(SerialNumberEasyAccessTest_537, ReturnsIteratorToMatchingKeyWhenPresent_537) {
  SetKey("Exif.Nikon3.SerialNumber", "12345");

  const auto it = Exiv2::serialNumber(ed_);
  ASSERT_NE(it, ed_.end());
  EXPECT_EQ(it->key(), std::string("Exif.Nikon3.SerialNumber"));
}

TEST_F(SerialNumberEasyAccessTest_537, ReturnsEndWhenNoKnownSerialKeyIsPresent_537) {
  SetKey("Exif.Image.Make", "NIKON");
  SetKey("Exif.Image.Model", "D850");
  SetKey("Exif.Photo.FNumber", "28/10");  // some unrelated tag

  const auto it = Exiv2::serialNumber(ed_);
  EXPECT_EQ(it, ed_.end());
}

TEST_F(SerialNumberEasyAccessTest_537, FindsSerialNumberEvenWithManyUnrelatedKeys_537) {
  // Add unrelated keys first
  SetKey("Exif.Image.Make", "Canon");
  SetKey("Exif.Image.Model", "EOS");
  SetKey("Exif.Photo.ExposureTime", "1/125");
  SetKey("Exif.Photo.ISOSpeedRatings", "100");

  // Add a known serial key from the list
  SetKey("Exif.Sony2.SerialNumber", "SONY-777");

  const auto it = Exiv2::serialNumber(ed_);
  ASSERT_NE(it, ed_.end());
  EXPECT_EQ(it->key(), std::string("Exif.Sony2.SerialNumber"));
}

TEST_F(SerialNumberEasyAccessTest_537, PrefersEarlierKeyInSearchOrderWhenMultiplePresent_537) {
  // The provided implementation passes an ordered key list to findMetadatum.
  // This test verifies the observable preference implied by that ordering.
  SetKey("Exif.Sony2.SerialNumber", "SONY-222");
  SetKey("Exif.Nikon3.SerialNumber", "NIKON-333");
  SetKey("Exif.Canon.SerialNumber", "CANON-111");  // first in list per provided code

  const auto it = Exiv2::serialNumber(ed_);
  ASSERT_NE(it, ed_.end());
  EXPECT_EQ(it->key(), std::string("Exif.Canon.SerialNumber"));
}

TEST_F(SerialNumberEasyAccessTest_537, ReturnsEndAfterClearEvenIfPreviouslyPresent_537) {
  SetKey("Exif.Pentax.SerialNumber", "PENTAX-999");
  ASSERT_NE(Exiv2::serialNumber(ed_), ed_.end());

  ed_.clear();
  ASSERT_TRUE(ed_.empty());

  const auto it = Exiv2::serialNumber(ed_);
  EXPECT_EQ(it, ed_.end());
}

}  // namespace
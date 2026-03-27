// File: test_easyaccess_flashBias_513.cpp

#include <gtest/gtest.h>

#include <exiv2/easyaccess.hpp>
#include <exiv2/exif.hpp>
#include <exiv2/value.hpp>

#include <string>

namespace {

using Exiv2::ExifData;
using Exiv2::ExifKey;
using Exiv2::Value;

// Helper: add a simple value for a given Exif key without depending on internal behavior.
static void addUShortValue(ExifData& ed, const std::string& key, uint16_t v) {
  auto value = Value::create(Exiv2::unsignedShort);
  ASSERT_NE(value.get(), nullptr);
  ASSERT_NO_THROW(value->read(std::to_string(v)));
  ASSERT_NO_THROW(ed.add(ExifKey(key), value.get()));
}

class FlashBiasTest_513 : public ::testing::Test {
 protected:
  ExifData ed_;
};

TEST_F(FlashBiasTest_513, ReturnsEndWhenEmpty_513) {
  ASSERT_TRUE(ed_.empty());

  ExifData::const_iterator it;
  ASSERT_NO_THROW(it = Exiv2::flashBias(ed_));
  EXPECT_EQ(it, ed_.end());
}

TEST_F(FlashBiasTest_513, ReturnsEndWhenNoMatchingKeys_513) {
  addUShortValue(ed_, "Exif.Image.ImageWidth", 123);
  addUShortValue(ed_, "Exif.Photo.ISOSpeedRatings", 200);

  ExifData::const_iterator it;
  ASSERT_NO_THROW(it = Exiv2::flashBias(ed_));
  EXPECT_EQ(it, ed_.end());
}

TEST_F(FlashBiasTest_513, ReturnsIteratorWhenFirstKeyPresent_513) {
  addUShortValue(ed_, "Exif.CanonSi.FlashBias", 7);

  ExifData::const_iterator it = Exiv2::flashBias(ed_);
  ASSERT_NE(it, ed_.end());
  EXPECT_EQ(it->key(), "Exif.CanonSi.FlashBias");
}

TEST_F(FlashBiasTest_513, ReturnsIteratorWhenLaterKeyPresent_513) {
  addUShortValue(ed_, "Exif.Sony2.FlashExposureComp", 9);

  ExifData::const_iterator it = Exiv2::flashBias(ed_);
  ASSERT_NE(it, ed_.end());
  EXPECT_EQ(it->key(), "Exif.Sony2.FlashExposureComp");
}

TEST_F(FlashBiasTest_513, ReturnsFirstInPriorityOrderWhenMultiplePresent_513) {
  // Add a later-listed key first, then an earlier-listed key.
  addUShortValue(ed_, "Exif.Sony2.FlashExposureComp", 9);
  addUShortValue(ed_, "Exif.Panasonic.FlashBias", 3);

  // If multiple candidates exist, the observable contract implied by the API is:
  // it returns the first match among the known keys list.
  ExifData::const_iterator it = Exiv2::flashBias(ed_);
  ASSERT_NE(it, ed_.end());
  EXPECT_EQ(it->key(), "Exif.Panasonic.FlashBias");
}

TEST_F(FlashBiasTest_513, IgnoresUnrelatedKeysWhenMatchingExists_513) {
  addUShortValue(ed_, "Exif.Image.ImageWidth", 123);
  addUShortValue(ed_, "Exif.OlympusCs.FlashExposureComp", 5);
  addUShortValue(ed_, "Exif.Photo.ISOSpeedRatings", 400);

  ExifData::const_iterator it = Exiv2::flashBias(ed_);
  ASSERT_NE(it, ed_.end());
  EXPECT_EQ(it->key(), "Exif.OlympusCs.FlashExposureComp");
}

TEST_F(FlashBiasTest_513, DoesNotThrowWithPopulatedExifData_513) {
  addUShortValue(ed_, "Exif.Image.ImageWidth", 123);
  addUShortValue(ed_, "Exif.Sony1.FlashExposureComp", 1);

  EXPECT_NO_THROW((void)Exiv2::flashBias(ed_));
}

}  // namespace
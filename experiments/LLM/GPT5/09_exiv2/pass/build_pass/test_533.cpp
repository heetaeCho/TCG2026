// File: test_easyaccess_maxApertureValue_533.cpp
#include <gtest/gtest.h>

#include <exiv2/easyaccess.hpp>
#include <exiv2/exif.hpp>

#include <string>

namespace {

class MaxApertureValueTest_533 : public ::testing::Test {
 protected:
  static void setDummyValue(Exiv2::ExifData& ed, const std::string& key) {
    // Use only public interface. Exifdatum typically supports assignment from string.
    ed[key] = "1";
  }
};

TEST_F(MaxApertureValueTest_533, EmptyExifDataReturnsEnd_533) {
  Exiv2::ExifData ed;

  auto it = Exiv2::maxApertureValue(ed);
  EXPECT_EQ(it, ed.end());
}

TEST_F(MaxApertureValueTest_533, FindsExifPhotoMaxApertureValue_533) {
  Exiv2::ExifData ed;
  setDummyValue(ed, "Exif.Photo.MaxApertureValue");

  auto it = Exiv2::maxApertureValue(ed);
  ASSERT_NE(it, ed.end());
  EXPECT_EQ(it->key(), "Exif.Photo.MaxApertureValue");
}

TEST_F(MaxApertureValueTest_533, FindsExifImageMaxApertureValueWhenPhotoMissing_533) {
  Exiv2::ExifData ed;
  setDummyValue(ed, "Exif.Image.MaxApertureValue");

  auto it = Exiv2::maxApertureValue(ed);
  ASSERT_NE(it, ed.end());
  EXPECT_EQ(it->key(), "Exif.Image.MaxApertureValue");
}

TEST_F(MaxApertureValueTest_533, FindsCanonCsMaxApertureWhenHigherPriorityMissing_533) {
  Exiv2::ExifData ed;
  setDummyValue(ed, "Exif.CanonCs.MaxAperture");

  auto it = Exiv2::maxApertureValue(ed);
  ASSERT_NE(it, ed.end());
  EXPECT_EQ(it->key(), "Exif.CanonCs.MaxAperture");
}

TEST_F(MaxApertureValueTest_533, FindsNikonLd4MaxApertureWhenOthersMissing_533) {
  Exiv2::ExifData ed;
  setDummyValue(ed, "Exif.NikonLd4.MaxAperture");

  auto it = Exiv2::maxApertureValue(ed);
  ASSERT_NE(it, ed.end());
  EXPECT_EQ(it->key(), "Exif.NikonLd4.MaxAperture");
}

TEST_F(MaxApertureValueTest_533, ReturnsHighestPriorityKeyWhenMultiplePresent_533) {
  Exiv2::ExifData ed;

  // Add several candidate keys; expectation is that the first key in the documented
  // priority list is returned if present.
  setDummyValue(ed, "Exif.NikonLd4.MaxAperture");
  setDummyValue(ed, "Exif.CanonCs.MaxAperture");
  setDummyValue(ed, "Exif.Image.MaxApertureValue");
  setDummyValue(ed, "Exif.Photo.MaxApertureValue");

  auto it = Exiv2::maxApertureValue(ed);
  ASSERT_NE(it, ed.end());
  EXPECT_EQ(it->key(), "Exif.Photo.MaxApertureValue");
}

TEST_F(MaxApertureValueTest_533, ReturnsFirstMatchingKeyByPriorityNotInsertionOrder_533) {
  Exiv2::ExifData ed;

  // Insert a lower-priority key first, then a higher-priority key.
  setDummyValue(ed, "Exif.CanonCs.MaxAperture");
  setDummyValue(ed, "Exif.Photo.MaxApertureValue");

  auto it = Exiv2::maxApertureValue(ed);
  ASSERT_NE(it, ed.end());
  EXPECT_EQ(it->key(), "Exif.Photo.MaxApertureValue");
}

TEST_F(MaxApertureValueTest_533, IgnoresNonCandidateKeys_533) {
  Exiv2::ExifData ed;

  // Add some unrelated keys; function should return end() if no candidates exist.
  setDummyValue(ed, "Exif.Photo.FNumber");
  setDummyValue(ed, "Exif.Image.Make");

  auto it = Exiv2::maxApertureValue(ed);
  EXPECT_EQ(it, ed.end());
}

TEST_F(MaxApertureValueTest_533, ReturnedIteratorIsUsableAsConstIterator_533) {
  Exiv2::ExifData ed;
  setDummyValue(ed, "Exif.Image.MaxApertureValue");

  const Exiv2::ExifData& ced = ed;
  Exiv2::ExifData::const_iterator it = Exiv2::maxApertureValue(ced);

  ASSERT_NE(it, ced.end());
  EXPECT_EQ(it->key(), "Exif.Image.MaxApertureValue");
}

}  // namespace
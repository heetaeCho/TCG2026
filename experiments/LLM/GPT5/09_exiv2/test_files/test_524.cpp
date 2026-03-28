// File: test_easyaccess_meteringMode_524.cpp
#include <gtest/gtest.h>

#include <exiv2/easyaccess.hpp>
#include <exiv2/exif.hpp>

#include <string>
#include <vector>

namespace {

// Helper: add an Exif datum using only public API.
static void addExifKeyValue(Exiv2::ExifData& ed, const std::string& key, const std::string& value = "1") {
  // Exiv2 supports assignment via operator[] for common test usage.
  ed[key] = value;
}

// The exact key list used by Exiv2::meteringMode (from easyaccess.cpp).
static const std::vector<std::string> kMeteringKeys = {
    "Exif.Photo.MeteringMode",
    "Exif.Image.MeteringMode",
    "Exif.CanonCs.MeteringMode",
    "Exif.MinoltaCs5D.MeteringMode",
    "Exif.MinoltaCsOld.MeteringMode",
    "Exif.OlympusCs.MeteringMode",
    "Exif.Pentax.MeteringMode",
    "Exif.PentaxDng.MeteringMode",
    "Exif.Sigma.MeteringMode",
    "Exif.Sony1.MeteringMode2",
    "Exif.Sony1Cs.MeteringMode",
    "Exif.Sony1Cs2.MeteringMode",
    "Exif.Sony2.MeteringMode2",
    "Exif.Sony2Cs.MeteringMode",
    "Exif.Sony1MltCsA100.MeteringMode",
};

class MeteringModeTest_524 : public ::testing::Test {
 protected:
  Exiv2::ExifData ed_;
};

}  // namespace

TEST_F(MeteringModeTest_524, EmptyExifDataReturnsEnd_524) {
  const auto it = Exiv2::meteringMode(ed_);
  EXPECT_EQ(it, ed_.end());
}

TEST_F(MeteringModeTest_524, FindsWhenFirstPreferredKeyExists_524) {
  addExifKeyValue(ed_, "Exif.Photo.MeteringMode", "3");

  const auto it = Exiv2::meteringMode(ed_);
  ASSERT_NE(it, ed_.end());
  EXPECT_EQ(it->key(), "Exif.Photo.MeteringMode");
}

TEST_F(MeteringModeTest_524, FindsWhenOnlyNonFirstKeyExists_524) {
  addExifKeyValue(ed_, "Exif.Sony2Cs.MeteringMode", "5");

  const auto it = Exiv2::meteringMode(ed_);
  ASSERT_NE(it, ed_.end());
  EXPECT_EQ(it->key(), "Exif.Sony2Cs.MeteringMode");
}

TEST_F(MeteringModeTest_524, ReturnsEndWhenNoneOfKnownKeysExist_524) {
  addExifKeyValue(ed_, "Exif.Image.Make", "SomeMake");
  addExifKeyValue(ed_, "Exif.Photo.ExposureTime", "1/125");

  const auto it = Exiv2::meteringMode(ed_);
  EXPECT_EQ(it, ed_.end());
}

TEST_F(MeteringModeTest_524, WhenMultipleKnownKeysExistReturnedKeyIsFromKnownSet_524) {
  // Add multiple candidate keys (not assuming ordering behavior here).
  addExifKeyValue(ed_, "Exif.Sigma.MeteringMode", "1");
  addExifKeyValue(ed_, "Exif.Image.MeteringMode", "2");
  addExifKeyValue(ed_, "Exif.Sony1Cs.MeteringMode", "3");

  const auto it = Exiv2::meteringMode(ed_);
  ASSERT_NE(it, ed_.end());

  const std::string foundKey = it->key();
  const bool inKnownSet =
      std::find(kMeteringKeys.begin(), kMeteringKeys.end(), foundKey) != kMeteringKeys.end();
  EXPECT_TRUE(inKnownSet);
}

TEST_F(MeteringModeTest_524, PrefersEarlierKeyWhenTwoCandidatesExist_524) {
  // This test verifies observable prioritization implied by the key list order.
  // If implementation changes priority, this test will catch it.
  addExifKeyValue(ed_, "Exif.Sony2Cs.MeteringMode", "7");   // later in list
  addExifKeyValue(ed_, "Exif.Image.MeteringMode", "2");     // earlier in list

  const auto it = Exiv2::meteringMode(ed_);
  ASSERT_NE(it, ed_.end());
  EXPECT_EQ(it->key(), "Exif.Image.MeteringMode");
}
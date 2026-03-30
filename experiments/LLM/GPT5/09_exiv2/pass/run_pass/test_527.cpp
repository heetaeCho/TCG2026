// SPDX-License-Identifier: GPL-2.0-or-later

#include <gtest/gtest.h>

#include <exiv2/easyaccess.hpp>
#include <exiv2/exif.hpp>

#include <string>
#include <vector>

namespace {

class ExposureTimeTest_527 : public ::testing::Test {
 protected:
  static constexpr const char* k1 = "Exif.Photo.ExposureTime";
  static constexpr const char* k2 = "Exif.Image.ExposureTime";
  static constexpr const char* k3 = "Exif.Pentax.ExposureTime";
  static constexpr const char* k4 = "Exif.PentaxDng.ExposureTime";
  static constexpr const char* k5 = "Exif.Samsung2.ExposureTime";

  static void setExposure(Exiv2::ExifData& ed, const std::string& key, const std::string& value = "1/125") {
    // Rely only on public interface; Exifdatum::setValue(std::string) is part of Exiv2's public API.
    ed[key].setValue(value);
  }
};

TEST_F(ExposureTimeTest_527, ReturnsEndWhenEmpty_527) {
  Exiv2::ExifData ed;

  const auto it = Exiv2::exposureTime(ed);

  EXPECT_EQ(it, ed.end());
}

TEST_F(ExposureTimeTest_527, ReturnsEndWhenNoMatchingKeysPresent_527) {
  Exiv2::ExifData ed;
  setExposure(ed, "Exif.Photo.FNumber", "8");  // unrelated key
  setExposure(ed, "Exif.Image.Make", "UnitTestCam");

  const auto it = Exiv2::exposureTime(ed);

  EXPECT_EQ(it, ed.end());
}

TEST_F(ExposureTimeTest_527, ReturnsIteratorToTheOnlySupportedKeyPresent_527) {
  const std::vector<std::string> supportedKeys = {k1, k2, k3, k4, k5};

  for (const auto& key : supportedKeys) {
    Exiv2::ExifData ed;
    setExposure(ed, key, "1/60");

    const auto it = Exiv2::exposureTime(ed);

    ASSERT_NE(it, ed.end()) << "Expected non-end iterator for key: " << key;
    EXPECT_EQ(it->key(), key);
  }
}

TEST_F(ExposureTimeTest_527, PrefersExifPhotoExposureTimeOverOtherCandidates_527) {
  Exiv2::ExifData ed;

  // Add a "later" candidate first, then the first-priority candidate.
  setExposure(ed, k5, "1/10");
  setExposure(ed, k1, "1/200");

  const auto it = Exiv2::exposureTime(ed);

  ASSERT_NE(it, ed.end());
  EXPECT_EQ(it->key(), std::string(k1));
}

TEST_F(ExposureTimeTest_527, PrefersEarlierKeyInDocumentedSearchOrder_527) {
  Exiv2::ExifData ed;

  // Both are in the list; k2 appears before k3 in the function's key list.
  setExposure(ed, k3, "1/30");
  setExposure(ed, k2, "1/500");

  const auto it = Exiv2::exposureTime(ed);

  ASSERT_NE(it, ed.end());
  EXPECT_EQ(it->key(), std::string(k2));
}

}  // namespace
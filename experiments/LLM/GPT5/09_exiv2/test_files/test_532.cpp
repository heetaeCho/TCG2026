// SPDX-License-Identifier: GPL-2.0-or-later

#include <gtest/gtest.h>

#include <exiv2/easyaccess.hpp>
#include <exiv2/exif.hpp>

namespace {

using Exiv2::ExifData;

class ExposureBiasValueTest_532 : public ::testing::Test {
 protected:
  static void EnsureKeyExists(ExifData& ed, const char* key) {
    // ExifData::operator[] is part of the public interface and is expected to
    // create/return the datum for the given key.
    (void)ed[key];
  }
};

TEST_F(ExposureBiasValueTest_532, ReturnsEndWhenNoKnownKeyPresent_532) {
  ExifData ed;
  const auto it = Exiv2::exposureBiasValue(ed);
  EXPECT_EQ(it, ed.end());
}

TEST_F(ExposureBiasValueTest_532, ReturnsMatchingIteratorWhenEachKnownKeyPresent_532) {
  static constexpr const char* kKeys[] = {
      "Exif.Photo.ExposureBiasValue",
      "Exif.Image.ExposureBiasValue",
      "Exif.MinoltaCs5D.ExposureManualBias",
      "Exif.OlympusRd.ExposureBiasValue",
      "Exif.OlympusRd2.ExposureBiasValue",
  };

  for (const char* key : kKeys) {
    ExifData ed;
    EnsureKeyExists(ed, key);

    SCOPED_TRACE(key);

    const auto it = Exiv2::exposureBiasValue(ed);
    EXPECT_NE(it, ed.end());

    // Verify it points to the same datum found via the public ExifData API.
    const auto expected = ed.findKey(Exiv2::ExifKey(key));
    EXPECT_NE(expected, ed.end());
    EXPECT_EQ(it, expected);
  }
}

TEST_F(ExposureBiasValueTest_532, RespectsPriorityOrderWhenMultipleKeysPresent_532) {
  // The implementation searches multiple keys; verify it returns the first match
  // in the documented order (not insertion order).
  ExifData ed;

  // Insert a lower-priority key first.
  EnsureKeyExists(ed, "Exif.Image.ExposureBiasValue");
  // Insert a higher-priority key second.
  EnsureKeyExists(ed, "Exif.Photo.ExposureBiasValue");

  const auto beforeCount = ed.count();
  const auto it = Exiv2::exposureBiasValue(ed);
  const auto afterCount = ed.count();

  // Function takes const ExifData&, so it must not mutate observable state.
  EXPECT_EQ(beforeCount, afterCount);

  const auto expected = ed.findKey(Exiv2::ExifKey("Exif.Photo.ExposureBiasValue"));
  EXPECT_NE(expected, ed.end());
  EXPECT_EQ(it, expected);
}

TEST_F(ExposureBiasValueTest_532, ReturnsFirstInListEvenIfAllKeysPresent_532) {
  ExifData ed;

  EnsureKeyExists(ed, "Exif.OlympusRd2.ExposureBiasValue");
  EnsureKeyExists(ed, "Exif.OlympusRd.ExposureBiasValue");
  EnsureKeyExists(ed, "Exif.MinoltaCs5D.ExposureManualBias");
  EnsureKeyExists(ed, "Exif.Image.ExposureBiasValue");
  EnsureKeyExists(ed, "Exif.Photo.ExposureBiasValue");

  const auto it = Exiv2::exposureBiasValue(ed);
  const auto expected = ed.findKey(Exiv2::ExifKey("Exif.Photo.ExposureBiasValue"));

  EXPECT_NE(it, ed.end());
  EXPECT_NE(expected, ed.end());
  EXPECT_EQ(it, expected);
}

}  // namespace
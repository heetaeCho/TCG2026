// File: test_subjectdistance_534.cpp
#include <gtest/gtest.h>

#include <exiv2/easyaccess.hpp>
#include <exiv2/exif.hpp>
#include <exiv2/exifkey.hpp>

namespace {

// Keep the fixture name + TEST names suffixed with the TEST_ID (534).
class SubjectDistanceTest_534 : public ::testing::Test {
 protected:
  static void SetInt(Exiv2::ExifData& ed, const char* key, long v) {
    // Exiv2 supports assigning numeric values through Exifdatum's operator=.
    ed[key] = v;
  }

  static void SetString(Exiv2::ExifData& ed, const char* key, const char* v) {
    ed[key] = v;
  }
};

TEST_F(SubjectDistanceTest_534, EmptyExifDataReturnsEnd_534) {
  Exiv2::ExifData ed;

  const auto it = Exiv2::subjectDistance(ed);
  EXPECT_EQ(it, ed.end());
}

TEST_F(SubjectDistanceTest_534, FindsFirstKeyWhenPresent_534) {
  Exiv2::ExifData ed;
  SetInt(ed, "Exif.Photo.SubjectDistance", 123);

  const auto it = Exiv2::subjectDistance(ed);

  ASSERT_NE(it, ed.end());
  EXPECT_EQ(it->key(), std::string("Exif.Photo.SubjectDistance"));
}

TEST_F(SubjectDistanceTest_534, PrefersEarlierKeyInListWhenMultiplePresent_534) {
  Exiv2::ExifData ed;

  // Two keys from the hard-coded list in easyaccess.cpp.
  SetInt(ed, "Exif.Olympus.FocusDistance", 111);
  SetInt(ed, "Exif.Image.SubjectDistance", 222);

  // "Exif.Image.SubjectDistance" appears earlier than "Exif.Olympus.FocusDistance".
  const auto it = Exiv2::subjectDistance(ed);

  ASSERT_NE(it, ed.end());
  EXPECT_EQ(it->key(), std::string("Exif.Image.SubjectDistance"));
}

TEST_F(SubjectDistanceTest_534, ReturnsLastKeyInListWhenOnlyThatExists_534) {
  Exiv2::ExifData ed;
  SetInt(ed, "Exif.Casio2.ObjectDistance", 77);

  const auto it = Exiv2::subjectDistance(ed);

  ASSERT_NE(it, ed.end());
  EXPECT_EQ(it->key(), std::string("Exif.Casio2.ObjectDistance"));
}

TEST_F(SubjectDistanceTest_534, SkipsZeroValueForNikonLd4AndFindsNext_534) {
  Exiv2::ExifData ed;

  // The implementation calls findMetadatumSkip0inNikonLd4(...), so a 0 value for
  // NikonLd4 focus distance is expected to be treated specially (skipped).
  SetInt(ed, "Exif.NikonLd4.FocusDistance", 0);
  SetInt(ed, "Exif.OlympusFi.FocusDistance", 555);

  const auto it = Exiv2::subjectDistance(ed);

  ASSERT_NE(it, ed.end());
  EXPECT_EQ(it->key(), std::string("Exif.OlympusFi.FocusDistance"));
}

}  // namespace
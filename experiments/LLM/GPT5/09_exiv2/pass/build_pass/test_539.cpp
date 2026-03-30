// File: test_subjectarea_539.cpp
#include <gtest/gtest.h>

#include <exiv2/easyaccess.hpp>
#include <exiv2/exif.hpp>

namespace {

class SubjectAreaTest_539 : public ::testing::Test {
 protected:
  static void AddAsciiLikeValue(Exiv2::ExifData& ed, const std::string& key, const std::string& value) {
    // Exiv2 commonly supports assignment from string via Exifdatum::operator=(std::string)
    ed[key] = value;
  }
};

TEST_F(SubjectAreaTest_539, ReturnsEndWhenEmpty_539) {
  Exiv2::ExifData ed;
  const Exiv2::ExifData& ced = ed;

  auto it = Exiv2::subjectArea(ced);
  EXPECT_EQ(it, ced.end());
}

TEST_F(SubjectAreaTest_539, ReturnsEndWhenNeitherKeyExists_539) {
  Exiv2::ExifData ed;
  AddAsciiLikeValue(ed, "Exif.Image.Make", "NIKON");
  AddAsciiLikeValue(ed, "Exif.Photo.FNumber", "2.8");
  const Exiv2::ExifData& ced = ed;

  auto it = Exiv2::subjectArea(ced);
  EXPECT_EQ(it, ced.end());
}

TEST_F(SubjectAreaTest_539, FindsExifPhotoSubjectAreaWhenPresent_539) {
  Exiv2::ExifData ed;
  AddAsciiLikeValue(ed, "Exif.Photo.SubjectArea", "1 2 3 4");
  const Exiv2::ExifData& ced = ed;

  auto it = Exiv2::subjectArea(ced);

  ASSERT_NE(it, ced.end());
  EXPECT_EQ(it->key(), "Exif.Photo.SubjectArea");
}

TEST_F(SubjectAreaTest_539, FindsExifImageSubjectLocationWhenSubjectAreaMissing_539) {
  Exiv2::ExifData ed;
  AddAsciiLikeValue(ed, "Exif.Image.SubjectLocation", "42");
  const Exiv2::ExifData& ced = ed;

  auto it = Exiv2::subjectArea(ced);

  ASSERT_NE(it, ced.end());
  EXPECT_EQ(it->key(), "Exif.Image.SubjectLocation");
}

TEST_F(SubjectAreaTest_539, PrefersSubjectAreaOverSubjectLocationWhenBothPresent_539) {
  Exiv2::ExifData ed;
  AddAsciiLikeValue(ed, "Exif.Image.SubjectLocation", "42");
  AddAsciiLikeValue(ed, "Exif.Photo.SubjectArea", "10 20 30 40");
  const Exiv2::ExifData& ced = ed;

  auto it = Exiv2::subjectArea(ced);

  ASSERT_NE(it, ced.end());
  // Observable preference based on key order used by subjectArea().
  EXPECT_EQ(it->key(), "Exif.Photo.SubjectArea");
}

}  // namespace
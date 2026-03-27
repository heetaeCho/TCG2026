// =================================================================================================
// TEST_ID: 512
// File: test_easyaccess_dateTimeOriginal_512.cpp
// =================================================================================================

#include <gtest/gtest.h>

#include <exiv2/easyaccess.hpp>
#include <exiv2/exif.hpp>
#include <exiv2/value.hpp>

#include <string>

namespace {

Exiv2::Value::UniquePtr makeAsciiValue(const std::string& s) {
  auto v = Exiv2::Value::create(Exiv2::asciiString);
  v->read(s);
  return v;
}

}  // namespace

namespace Exiv2 {

class DateTimeOriginalTest_512 : public ::testing::Test {
 protected:
  static constexpr const char* kKeyPhoto = "Exif.Photo.DateTimeOriginal";
  static constexpr const char* kKeyImage = "Exif.Image.DateTimeOriginal";
};

TEST_F(DateTimeOriginalTest_512, ReturnsEndWhenExifDataIsEmpty_512) {
  ExifData ed;
  const ExifData& ced = ed;

  auto it = dateTimeOriginal(ced);

  EXPECT_TRUE(ced.empty());
  EXPECT_EQ(it, ced.end());
}

TEST_F(DateTimeOriginalTest_512, ReturnsEndWhenNoMatchingKeyExists_512) {
  ExifData ed;
  // Add an unrelated tag.
  {
    auto v = makeAsciiValue("2026:02:05 08:00:00");
    ed.add(ExifKey("Exif.Image.DateTime"), v.get());
  }
  const auto beforeCount = ed.count();
  const ExifData& ced = ed;

  auto it = dateTimeOriginal(ced);

  EXPECT_EQ(it, ced.end());
  EXPECT_EQ(ced.count(), beforeCount);  // Should not mutate observable container size.
}

TEST_F(DateTimeOriginalTest_512, ReturnsPhotoDateTimeOriginalWhenPresent_512) {
  ExifData ed;
  {
    auto v = makeAsciiValue("2026:02:05 08:00:00");
    ed.add(ExifKey(kKeyPhoto), v.get());
  }
  const ExifData& ced = ed;

  auto it = dateTimeOriginal(ced);

  ASSERT_NE(it, ced.end());
  EXPECT_EQ(it->key(), std::string(kKeyPhoto));
  // Cross-check against ExifData lookup (observable, public API).
  EXPECT_EQ(it, ced.findKey(ExifKey(kKeyPhoto)));
}

TEST_F(DateTimeOriginalTest_512, ReturnsImageDateTimeOriginalWhenPhotoIsAbsent_512) {
  ExifData ed;
  {
    auto v = makeAsciiValue("2026:02:05 08:00:01");
    ed.add(ExifKey(kKeyImage), v.get());
  }
  const ExifData& ced = ed;

  auto it = dateTimeOriginal(ced);

  ASSERT_NE(it, ced.end());
  EXPECT_EQ(it->key(), std::string(kKeyImage));
  EXPECT_EQ(it, ced.findKey(ExifKey(kKeyImage)));
}

TEST_F(DateTimeOriginalTest_512, PrefersPhotoOverImageWhenBothArePresent_512) {
  ExifData ed;
  {
    auto v1 = makeAsciiValue("2026:02:05 08:00:02");
    ed.add(ExifKey(kKeyImage), v1.get());
  }
  {
    auto v2 = makeAsciiValue("2026:02:05 08:00:03");
    ed.add(ExifKey(kKeyPhoto), v2.get());
  }
  const ExifData& ced = ed;

  auto it = dateTimeOriginal(ced);

  ASSERT_NE(it, ced.end());
  // Observable preference is based on which key the iterator points to.
  EXPECT_EQ(it->key(), std::string(kKeyPhoto));
  EXPECT_EQ(it, ced.findKey(ExifKey(kKeyPhoto)));
  EXPECT_NE(it, ced.findKey(ExifKey(kKeyImage)));
}

TEST_F(DateTimeOriginalTest_512, RemainsValidWithAdditionalUnrelatedMetadata_512) {
  ExifData ed;
  {
    auto v = makeAsciiValue("foo");
    ed.add(ExifKey("Exif.Photo.UserComment"), v.get());
  }
  {
    auto v = makeAsciiValue("2026:02:05 08:00:04");
    ed.add(ExifKey(kKeyPhoto), v.get());
  }
  {
    auto v = makeAsciiValue("bar");
    ed.add(ExifKey("Exif.Image.Make"), v.get());
  }

  const auto beforeCount = ed.count();
  const ExifData& ced = ed;

  auto it = dateTimeOriginal(ced);

  ASSERT_NE(it, ced.end());
  EXPECT_EQ(it->key(), std::string(kKeyPhoto));
  EXPECT_EQ(ced.count(), beforeCount);  // No observable mutation of ExifData size.
}

}  // namespace Exiv2
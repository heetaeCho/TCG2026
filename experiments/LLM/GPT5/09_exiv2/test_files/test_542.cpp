// File: test_easyaccess_sensingMethod_542.cpp

#include <gtest/gtest.h>

#include <exiv2/easyaccess.hpp>
#include <exiv2/exif.hpp>
#include <exiv2/value.hpp>

namespace {

class SensingMethodEasyAccessTest_542 : public ::testing::Test {
 protected:
  static Exiv2::Value::UniquePtr makeUShortValue(const char* txt) {
    Exiv2::Value::UniquePtr v = Exiv2::Value::create(Exiv2::unsignedShort);
    // If read() fails for some reason, we still return the value object; the
    // easyaccess function under test only needs the key to exist.
    (void)v->read(txt);
    return v;
  }
};

TEST_F(SensingMethodEasyAccessTest_542, ReturnsEndWhenExifDataEmpty_542) {
  Exiv2::ExifData ed;
  const auto it = Exiv2::sensingMethod(ed);
  EXPECT_EQ(it, ed.end());
}

TEST_F(SensingMethodEasyAccessTest_542, FindsExifPhotoSensingMethodWhenPresent_542) {
  Exiv2::ExifData ed;

  Exiv2::ExifKey key("Exif.Photo.SensingMethod");
  auto v = makeUShortValue("2");
  ed.add(key, v.get());

  const auto it = Exiv2::sensingMethod(ed);
  ASSERT_NE(it, ed.end());
  EXPECT_EQ(it->key(), std::string("Exif.Photo.SensingMethod"));
}

TEST_F(SensingMethodEasyAccessTest_542, FallsBackToExifImageSensingMethodWhenPhotoMissing_542) {
  Exiv2::ExifData ed;

  Exiv2::ExifKey key("Exif.Image.SensingMethod");
  auto v = makeUShortValue("3");
  ed.add(key, v.get());

  const auto it = Exiv2::sensingMethod(ed);
  ASSERT_NE(it, ed.end());
  EXPECT_EQ(it->key(), std::string("Exif.Image.SensingMethod"));
}

TEST_F(SensingMethodEasyAccessTest_542, PrefersExifPhotoOverExifImageWhenBothPresent_542) {
  Exiv2::ExifData ed;

  // Add both keys; function should prefer "Exif.Photo.SensingMethod".
  {
    Exiv2::ExifKey key("Exif.Image.SensingMethod");
    auto v = makeUShortValue("3");
    ed.add(key, v.get());
  }
  {
    Exiv2::ExifKey key("Exif.Photo.SensingMethod");
    auto v = makeUShortValue("2");
    ed.add(key, v.get());
  }

  const auto it = Exiv2::sensingMethod(ed);
  ASSERT_NE(it, ed.end());
  EXPECT_EQ(it->key(), std::string("Exif.Photo.SensingMethod"));
}

TEST_F(SensingMethodEasyAccessTest_542, IgnoresUnrelatedKeysAndReturnsEnd_542) {
  Exiv2::ExifData ed;

  Exiv2::ExifKey otherKey("Exif.Photo.FNumber");
  Exiv2::Value::UniquePtr v = Exiv2::Value::create(Exiv2::rational);
  (void)v->read("56/10");
  ed.add(otherKey, v.get());

  const auto it = Exiv2::sensingMethod(ed);
  EXPECT_EQ(it, ed.end());
}

}  // namespace
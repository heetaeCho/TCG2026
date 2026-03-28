// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_exifdatum_key_742.cpp
//
// Unit tests for Exiv2::Exifdatum::key() based strictly on public interface.
//
// TEST_ID: 742

#include <gtest/gtest.h>

#include <exiv2/exif.hpp>
#include <exiv2/tags.hpp>
#include <exiv2/value.hpp>

namespace {

class ExifdatumKeyTest_742 : public ::testing::Test {
 protected:
  static Exiv2::Value::UniquePtr MakeAsciiValue(const std::string& s) {
    auto v = Exiv2::Value::create(Exiv2::asciiString);
    // Use only public Value API. If setValue fails for some types, tests still focus on key().
    (void)v->read(s);
    return v;
  }
};

TEST_F(ExifdatumKeyTest_742, KeyReturnsSameAsExifKey_742) {
  const std::string k = "Exif.Image.Make";
  Exiv2::ExifKey exifKey(k);

  auto v = MakeAsciiValue("dummy");
  Exiv2::Exifdatum d(exifKey, v.get());

  EXPECT_EQ(d.key(), exifKey.key());
}

TEST_F(ExifdatumKeyTest_742, KeyPersistsAfterCopyConstruction_742) {
  const std::string k = "Exif.Photo.FNumber";
  Exiv2::ExifKey exifKey(k);

  auto v = MakeAsciiValue("dummy");
  Exiv2::Exifdatum original(exifKey, v.get());

  Exiv2::Exifdatum copy(original);

  EXPECT_EQ(copy.key(), original.key());
  EXPECT_EQ(copy.key(), exifKey.key());
}

TEST_F(ExifdatumKeyTest_742, KeyPersistsAfterCopyAssignment_742) {
  Exiv2::ExifKey keyA("Exif.Image.Model");
  Exiv2::ExifKey keyB("Exif.Photo.ExposureTime");

  auto v1 = MakeAsciiValue("a");
  auto v2 = MakeAsciiValue("b");

  Exiv2::Exifdatum a(keyA, v1.get());
  Exiv2::Exifdatum b(keyB, v2.get());

  // Sanity: different keys before assignment (observable through key()).
  EXPECT_NE(a.key(), b.key());

  b = a;

  EXPECT_EQ(b.key(), a.key());
  EXPECT_EQ(b.key(), keyA.key());
}

TEST_F(ExifdatumKeyTest_742, KeyHandlesEmptyExifKeyString_742) {
  // Boundary condition: empty key string (behavior is observable via key()).
  Exiv2::ExifKey emptyKey(std::string{});

  auto v = MakeAsciiValue("dummy");
  Exiv2::Exifdatum d(emptyKey, v.get());

  EXPECT_EQ(d.key(), emptyKey.key());
}

}  // namespace
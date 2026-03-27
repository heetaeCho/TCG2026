// SPDX-License-Identifier: GPL-2.0-or-later
// Tests for Exiv2::ExifData::clear()
// File: exifdata_clear_test_779.cpp

#include <gtest/gtest.h>

#include <exiv2/exif.hpp>
#include <exiv2/value.hpp>

#include <string>

namespace {

class ExifDataTest_779 : public ::testing::Test {
 protected:
  static Exiv2::ExifKey MakeKey() { return Exiv2::ExifKey("Exif.Image.Make"); }
  static Exiv2::ExifKey ModelKey() { return Exiv2::ExifKey("Exif.Image.Model"); }

  static Exiv2::Value::UniquePtr AsciiValue(const std::string& s) {
    auto v = Exiv2::Value::create(Exiv2::asciiString);
    v->read(s);
    return v;
  }
};

TEST_F(ExifDataTest_779, ClearOnEmpty_NoThrowAndStaysEmpty_779) {
  Exiv2::ExifData exif;

  EXPECT_TRUE(exif.empty());
  EXPECT_EQ(exif.count(), 0u);
  EXPECT_EQ(exif.begin(), exif.end());

  EXPECT_NO_THROW(exif.clear());

  EXPECT_TRUE(exif.empty());
  EXPECT_EQ(exif.count(), 0u);
  EXPECT_EQ(exif.begin(), exif.end());
}

TEST_F(ExifDataTest_779, ClearAfterOperatorBracketInsert_779) {
  Exiv2::ExifData exif;

  ASSERT_TRUE(exif.empty());
  ASSERT_EQ(exif.count(), 0u);

  // Insert/create a datum through operator[] (observable effect: container non-empty).
  EXPECT_NO_THROW((void)exif["Exif.Image.Make"]);

  EXPECT_FALSE(exif.empty());
  EXPECT_GE(exif.count(), 1u);
  EXPECT_NE(exif.begin(), exif.end());

  EXPECT_NO_THROW(exif.clear());

  EXPECT_TRUE(exif.empty());
  EXPECT_EQ(exif.count(), 0u);
  EXPECT_EQ(exif.begin(), exif.end());
}

TEST_F(ExifDataTest_779, ClearAfterAddWithValue_MakesEmpty_779) {
  Exiv2::ExifData exif;

  auto key = MakeKey();
  auto v = AsciiValue("Canon");

  EXPECT_NO_THROW(exif.add(key, v.get()));

  EXPECT_FALSE(exif.empty());
  EXPECT_GE(exif.count(), 1u);

  EXPECT_NO_THROW(exif.clear());

  EXPECT_TRUE(exif.empty());
  EXPECT_EQ(exif.count(), 0u);
}

TEST_F(ExifDataTest_779, ClearRemovesKeySoFindKeyReturnsEnd_779) {
  Exiv2::ExifData exif;

  const auto key = MakeKey();
  auto v = AsciiValue("Nikon");

  ASSERT_NO_THROW(exif.add(key, v.get()));
  ASSERT_FALSE(exif.empty());

  // Use findKey (observable through returned iterator).
  auto it_before = exif.findKey(key);
  EXPECT_NE(it_before, exif.end());

  ASSERT_NO_THROW(exif.clear());

  EXPECT_TRUE(exif.empty());
  EXPECT_EQ(exif.count(), 0u);

  auto it_after = exif.findKey(key);
  EXPECT_EQ(it_after, exif.end());
}

TEST_F(ExifDataTest_779, ClearAfterMultipleAdds_ResetsBeginEndAndCount_779) {
  Exiv2::ExifData exif;

  auto v1 = AsciiValue("Sony");
  auto v2 = AsciiValue("A7");

  ASSERT_NO_THROW(exif.add(MakeKey(), v1.get()));
  ASSERT_NO_THROW(exif.add(ModelKey(), v2.get()));

  EXPECT_FALSE(exif.empty());
  EXPECT_GE(exif.count(), 2u);
  EXPECT_NE(exif.begin(), exif.end());

  EXPECT_NO_THROW(exif.clear());

  EXPECT_TRUE(exif.empty());
  EXPECT_EQ(exif.count(), 0u);
  EXPECT_EQ(exif.begin(), exif.end());
}

TEST_F(ExifDataTest_779, ClearIsIdempotent_CallingTwiceKeepsEmpty_779) {
  Exiv2::ExifData exif;

  auto v = AsciiValue("Fujifilm");
  ASSERT_NO_THROW(exif.add(MakeKey(), v.get()));
  ASSERT_FALSE(exif.empty());

  ASSERT_NO_THROW(exif.clear());
  EXPECT_TRUE(exif.empty());
  EXPECT_EQ(exif.count(), 0u);

  // Boundary: clear again on already-empty container.
  EXPECT_NO_THROW(exif.clear());
  EXPECT_TRUE(exif.empty());
  EXPECT_EQ(exif.count(), 0u);
  EXPECT_EQ(exif.begin(), exif.end());
}

}  // namespace
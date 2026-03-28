// File: test_exifdata_sortbykey_780.cpp
// Unit tests for Exiv2::ExifData::sortByKey()
// TEST_ID: 780

#include <gtest/gtest.h>

#include <exiv2/exif.hpp>

#include <algorithm>
#include <string>
#include <vector>

namespace {

class ExifDataSortByKeyTest_780 : public ::testing::Test {
 protected:
  static std::vector<std::string> KeysOf(Exiv2::ExifData& data) {
    std::vector<std::string> keys;
    for (auto it = data.begin(); it != data.end(); ++it) {
      // Exiv2::Exifdatum is a public type; key() is part of its public API in Exiv2.
      keys.push_back(it->key());
    }
    return keys;
  }

  static bool IsNonDecreasing(const std::vector<std::string>& v) {
    return std::is_sorted(v.begin(), v.end());
  }
};

TEST_F(ExifDataSortByKeyTest_780, SortByKeyOnEmptyDoesNotChangeCount_780) {
  Exiv2::ExifData data;
  ASSERT_TRUE(data.empty());
  ASSERT_EQ(data.count(), 0u);

  EXPECT_NO_THROW(data.sortByKey());

  EXPECT_TRUE(data.empty());
  EXPECT_EQ(data.count(), 0u);
  EXPECT_EQ(KeysOf(data).size(), 0u);
}

TEST_F(ExifDataSortByKeyTest_780, SortByKeyOnSingleElementKeepsSameSingleKey_780) {
  Exiv2::ExifData data;

  data["Exif.Image.Make"];  // Use operator[] to ensure insertion without relying on Value creation.
  ASSERT_FALSE(data.empty());
  ASSERT_EQ(data.count(), 1u);

  const auto before = KeysOf(data);
  ASSERT_EQ(before.size(), 1u);
  ASSERT_EQ(before[0], "Exif.Image.Make");

  EXPECT_NO_THROW(data.sortByKey());

  const auto after = KeysOf(data);
  ASSERT_EQ(after.size(), 1u);
  EXPECT_EQ(after[0], "Exif.Image.Make");
  EXPECT_EQ(data.count(), 1u);
}

TEST_F(ExifDataSortByKeyTest_780, SortByKeyReordersKeysIntoLexicographicOrder_780) {
  Exiv2::ExifData data;

  // Insert out of order.
  data["Exif.Photo.DateTimeOriginal"];
  data["Exif.Image.Make"];
  data["Exif.Image.Model"];
  data["Exif.Photo.FNumber"];
  data["Exif.Image.Software"];

  ASSERT_EQ(data.count(), 5u);

  EXPECT_NO_THROW(data.sortByKey());

  const auto keys = KeysOf(data);
  ASSERT_EQ(keys.size(), 5u);
  EXPECT_TRUE(IsNonDecreasing(keys));

  // Verify all inserted keys are still present (content preserved).
  const std::vector<std::string> expected = {
      "Exif.Photo.DateTimeOriginal",
      "Exif.Image.Make",
      "Exif.Image.Model",
      "Exif.Photo.FNumber",
      "Exif.Image.Software",
  };
  for (const auto& k : expected) {
    EXPECT_NE(std::find(keys.begin(), keys.end(), k), keys.end()) << "Missing key: " << k;
  }
}

TEST_F(ExifDataSortByKeyTest_780, SortByKeyDoesNotChangeCountOrEmptiness_780) {
  Exiv2::ExifData data;

  data["Exif.Image.Model"];
  data["Exif.Image.Make"];
  data["Exif.Photo.ISOSpeedRatings"];
  ASSERT_EQ(data.count(), 3u);
  ASSERT_FALSE(data.empty());

  EXPECT_NO_THROW(data.sortByKey());

  EXPECT_EQ(data.count(), 3u);
  EXPECT_FALSE(data.empty());
}

TEST_F(ExifDataSortByKeyTest_780, SortByKeyIsIdempotentCallingTwiceKeepsSortedOrder_780) {
  Exiv2::ExifData data;

  data["Exif.Image.Model"];
  data["Exif.Image.Make"];
  data["Exif.Photo.FocalLength"];
  data["Exif.Photo.ExposureTime"];

  data.sortByKey();
  const auto once = KeysOf(data);
  ASSERT_TRUE(IsNonDecreasing(once));

  EXPECT_NO_THROW(data.sortByKey());
  const auto twice = KeysOf(data);

  EXPECT_EQ(once, twice);
  EXPECT_TRUE(IsNonDecreasing(twice));
}

TEST_F(ExifDataSortByKeyTest_780, SortByKeyWithAlreadySortedInputRemainsSortedAndStableAsSet_780) {
  Exiv2::ExifData data;

  // Insert already in lexicographic order by key string.
  data["Exif.Image.Make"];
  data["Exif.Image.Model"];
  data["Exif.Image.Software"];
  data["Exif.Photo.DateTimeOriginal"];

  const auto before = KeysOf(data);
  ASSERT_TRUE(IsNonDecreasing(before));
  ASSERT_EQ(data.count(), before.size());

  EXPECT_NO_THROW(data.sortByKey());

  const auto after = KeysOf(data);
  EXPECT_TRUE(IsNonDecreasing(after));
  EXPECT_EQ(after.size(), before.size());
  // We only assert the set of keys is preserved (ordering may or may not remain identical depending on implementation).
  for (const auto& k : before) {
    EXPECT_NE(std::find(after.begin(), after.end(), k), after.end()) << "Missing key: " << k;
  }
}

}  // namespace
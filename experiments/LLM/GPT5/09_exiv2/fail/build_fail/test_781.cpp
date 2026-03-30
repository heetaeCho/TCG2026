// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_exifdata_sortbytag_781.cpp

#include <gtest/gtest.h>

#include <exiv2/exif.hpp>
#include <exiv2/value.hpp>

#include <algorithm>
#include <cstdint>
#include <memory>
#include <set>
#include <string>
#include <vector>

namespace {

class ExifDataTest_781 : public ::testing::Test {
 protected:
  static std::unique_ptr<Exiv2::Value> MakeAsciiValue(const std::string& s) {
    // Use a public factory; do not assume internal representation.
    std::unique_ptr<Exiv2::Value> v(Exiv2::Value::create(Exiv2::asciiString));
    v->read(s);
    return v;
  }

  static Exiv2::ExifKey K(const char* key) { return Exiv2::ExifKey(key); }

  static std::set<std::string> KeysOf(const Exiv2::ExifData& exif) {
    std::set<std::string> keys;
    for (auto it = exif.begin(); it != exif.end(); ++it) {
      keys.insert(it->key());
    }
    return keys;
  }

  static std::vector<uint32_t> TagsInIterationOrder(const Exiv2::ExifData& exif) {
    std::vector<uint32_t> tags;
    for (auto it = exif.begin(); it != exif.end(); ++it) {
      // Exifdatum::tag() is part of the public Exiv2 interface.
      tags.push_back(static_cast<uint32_t>(it->tag()));
    }
    return tags;
  }
};

TEST_F(ExifDataTest_781, SortByTag_OnEmptyIsNoOp_781) {
  Exiv2::ExifData exif;
  EXPECT_TRUE(exif.empty());
  EXPECT_EQ(exif.count(), 0u);

  exif.sortByTag();

  EXPECT_TRUE(exif.empty());
  EXPECT_EQ(exif.count(), 0u);
  EXPECT_EQ(exif.begin(), exif.end());
}

TEST_F(ExifDataTest_781, SortByTag_SingleElementKeepsSameElement_781) {
  Exiv2::ExifData exif;

  exif.add(K("Exif.Image.Make"), MakeAsciiValue("ACME").get());
  ASSERT_FALSE(exif.empty());
  ASSERT_EQ(exif.count(), 1u);

  const auto keys_before = KeysOf(exif);

  exif.sortByTag();

  EXPECT_EQ(exif.count(), 1u);
  const auto keys_after = KeysOf(exif);
  EXPECT_EQ(keys_after, keys_before);

  // Also verify it is still findable via the public findKey interface.
  auto it = exif.findKey(K("Exif.Image.Make"));
  EXPECT_NE(it, exif.end());
  if (it != exif.end()) {
    EXPECT_EQ(it->key(), std::string("Exif.Image.Make"));
  }
}

TEST_F(ExifDataTest_781, SortByTag_MultipleElementsBecomeNondecreasingByTag_781) {
  Exiv2::ExifData exif;

  // Pick well-known Exif keys with widely separated tag IDs.
  exif.add(K("Exif.Image.ImageDescription"), MakeAsciiValue("desc").get());
  exif.add(K("Exif.Image.Make"), MakeAsciiValue("make").get());
  exif.add(K("Exif.Photo.ExposureTime"), MakeAsciiValue("1/125").get());
  exif.add(K("Exif.Photo.FNumber"), MakeAsciiValue("5.6").get());

  ASSERT_EQ(exif.count(), 4u);

  exif.sortByTag();

  const auto tags = TagsInIterationOrder(exif);
  ASSERT_EQ(tags.size(), 4u);
  EXPECT_TRUE(std::is_sorted(tags.begin(), tags.end()))
      << "Expected iteration order to be nondecreasing by Exifdatum::tag() after sortByTag().";
}

TEST_F(ExifDataTest_781, SortByTag_DoesNotAddRemoveOrLoseElements_781) {
  Exiv2::ExifData exif;

  exif.add(K("Exif.Image.Make"), MakeAsciiValue("make").get());
  exif.add(K("Exif.Image.Model"), MakeAsciiValue("model").get());
  exif.add(K("Exif.Photo.DateTimeOriginal"), MakeAsciiValue("2026:02:05 21:00:00").get());

  ASSERT_EQ(exif.count(), 3u);

  const auto keys_before = KeysOf(exif);

  exif.sortByTag();

  EXPECT_EQ(exif.count(), 3u);
  const auto keys_after = KeysOf(exif);
  EXPECT_EQ(keys_after, keys_before);

  // Each key should still be locatable.
  for (const auto& k : keys_before) {
    auto it = exif.findKey(ExifDataTest_781::K(k.c_str()));
    EXPECT_NE(it, exif.end()) << "Missing key after sortByTag(): " << k;
  }
}

TEST_F(ExifDataTest_781, SortByTag_IsIdempotent_781) {
  Exiv2::ExifData exif;

  exif.add(K("Exif.Photo.ExposureTime"), MakeAsciiValue("1/60").get());
  exif.add(K("Exif.Image.Make"), MakeAsciiValue("make").get());
  exif.add(K("Exif.Photo.FNumber"), MakeAsciiValue("8.0").get());
  exif.add(K("Exif.Image.ImageDescription"), MakeAsciiValue("desc").get());

  ASSERT_EQ(exif.count(), 4u);

  exif.sortByTag();
  const auto tags_once = TagsInIterationOrder(exif);
  const auto keys_once = KeysOf(exif);

  exif.sortByTag();
  const auto tags_twice = TagsInIterationOrder(exif);
  const auto keys_twice = KeysOf(exif);

  EXPECT_EQ(keys_twice, keys_once);
  EXPECT_EQ(tags_twice, tags_once);
  EXPECT_TRUE(std::is_sorted(tags_twice.begin(), tags_twice.end()));
}

TEST_F(ExifDataTest_781, SortByTag_AfterEraseRangeMaintainsOrdering_781) {
  Exiv2::ExifData exif;

  exif.add(K("Exif.Image.Make"), MakeAsciiValue("make").get());
  exif.add(K("Exif.Image.Model"), MakeAsciiValue("model").get());
  exif.add(K("Exif.Photo.ExposureTime"), MakeAsciiValue("1/250").get());
  exif.add(K("Exif.Photo.FNumber"), MakeAsciiValue("4.0").get());

  ASSERT_EQ(exif.count(), 4u);

  // Erase a middle range using only public iterators.
  auto beg = exif.begin();
  auto end = exif.begin();
  ASSERT_NE(beg, exif.end());
  ++end;
  if (end != exif.end()) {
    ++end;  // try to erase up to (but not including) the 3rd element
  }
  exif.erase(beg, end);

  // Count should have decreased (exact amount depends on available elements),
  // but must remain consistent with begin/end traversal.
  size_t iter_count = 0;
  for (auto it = exif.begin(); it != exif.end(); ++it) ++iter_count;
  EXPECT_EQ(exif.count(), iter_count);

  exif.sortByTag();

  const auto tags = TagsInIterationOrder(exif);
  EXPECT_TRUE(std::is_sorted(tags.begin(), tags.end()));
}

}  // namespace
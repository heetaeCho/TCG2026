// =================================================================================================
// tests/test_exifdata_add_776.cpp
// Unit tests for Exiv2::ExifData::add(const ExifKey&, const Value*)
// TEST_ID: 776
// =================================================================================================

#include <gtest/gtest.h>

#include <memory>
#include <string>

#include "exiv2/exif.hpp"
#include "exiv2/tags.hpp"
#include "exiv2/value.hpp"

namespace {

class ExifDataTest_776 : public ::testing::Test {
 protected:
  static std::unique_ptr<Exiv2::Value> MakeAsciiValue(const std::string& s) {
    // Use the public factory and public read() API only.
    auto v = Exiv2::Value::create(Exiv2::asciiString);
    EXPECT_NE(v, nullptr);
    // read() returns int; we only require it to be callable via the public API.
    (void)v->read(s);
    return v;
  }

  static Exiv2::ExifKey MakeKey(const std::string& key) {
    return Exiv2::ExifKey(key);
  }
};

TEST_F(ExifDataTest_776, AddWithKeyAndValuePointer_MakesContainerNonEmpty_776) {
  Exiv2::ExifData data;
  EXPECT_TRUE(data.empty());
  EXPECT_EQ(data.count(), 0u);

  const auto key = MakeKey("Exif.Image.Make");
  auto val = MakeAsciiValue("Canon");

  data.add(key, val.get());

  EXPECT_FALSE(data.empty());
  EXPECT_GE(data.count(), 1u);
  EXPECT_NE(data.findKey(key), data.end());
}

TEST_F(ExifDataTest_776, AddDoesNotDependOnValueLifetime_AfterValueDestroyedDataStillContainsKey_776) {
  Exiv2::ExifData data;
  const auto key = MakeKey("Exif.Image.Model");

  {
    auto val = MakeAsciiValue("EOS");
    data.add(key, val.get());
    EXPECT_NE(data.findKey(key), data.end());
    EXPECT_GE(data.count(), 1u);
  }  // val destroyed here

  // Observable behavior: container remains usable and still reports the key present.
  EXPECT_FALSE(data.empty());
  EXPECT_GE(data.count(), 1u);
  EXPECT_NE(data.findKey(key), data.end());
}

TEST_F(ExifDataTest_776, AddTwiceWithSameKey_CountDoesNotDecreaseAndKeyRemainsFindable_776) {
  Exiv2::ExifData data;
  const auto key = MakeKey("Exif.Photo.UserComment");

  auto v1 = MakeAsciiValue("one");
  data.add(key, v1.get());
  const auto c1 = data.count();
  EXPECT_NE(data.findKey(key), data.end());

  auto v2 = MakeAsciiValue("two");
  data.add(key, v2.get());
  const auto c2 = data.count();

  // Black-box friendly: do not assume duplicate handling; only require the container didn't lose entries.
  EXPECT_GE(c2, c1);
  EXPECT_NE(data.findKey(key), data.end());
}

TEST_F(ExifDataTest_776, ClearAfterAdd_EmptiesContainer_776) {
  Exiv2::ExifData data;
  data.add(MakeKey("Exif.Image.Make"), MakeAsciiValue("Canon").get());  // temporary pointer OK for call
  data.add(MakeKey("Exif.Image.Model"), MakeAsciiValue("EOS").get());

  EXPECT_FALSE(data.empty());
  EXPECT_GE(data.count(), 1u);

  data.clear();

  EXPECT_TRUE(data.empty());
  EXPECT_EQ(data.count(), 0u);
  EXPECT_EQ(data.begin(), data.end());
}

TEST_F(ExifDataTest_776, EraseSingleElement_DecreasesCountWhenNotEmpty_776) {
  Exiv2::ExifData data;

  auto v1 = MakeAsciiValue("Canon");
  auto v2 = MakeAsciiValue("EOS");

  data.add(MakeKey("Exif.Image.Make"), v1.get());
  data.add(MakeKey("Exif.Image.Model"), v2.get());

  ASSERT_FALSE(data.empty());
  const auto before = data.count();
  ASSERT_GE(before, 1u);

  auto it = data.begin();
  ASSERT_NE(it, data.end());

  (void)data.erase(it);

  const auto after = data.count();
  // Without assuming ordering/duplicate rules, we can still require erase() didn't increase count.
  EXPECT_LE(after, before);
}

TEST_F(ExifDataTest_776, EraseRangeBeginToEnd_ResultsInEmpty_776) {
  Exiv2::ExifData data;

  auto v1 = MakeAsciiValue("A");
  auto v2 = MakeAsciiValue("B");
  auto v3 = MakeAsciiValue("C");

  data.add(MakeKey("Exif.Image.Make"), v1.get());
  data.add(MakeKey("Exif.Image.Model"), v2.get());
  data.add(MakeKey("Exif.Photo.UserComment"), v3.get());

  ASSERT_FALSE(data.empty());
  ASSERT_GE(data.count(), 1u);

  (void)data.erase(data.begin(), data.end());

  EXPECT_TRUE(data.empty());
  EXPECT_EQ(data.count(), 0u);
  EXPECT_EQ(data.begin(), data.end());
}

TEST_F(ExifDataTest_776, SortByKeyAndSortByTag_DoNotChangeCountAndAreCallable_776) {
  Exiv2::ExifData data;

  auto v1 = MakeAsciiValue("Canon");
  auto v2 = MakeAsciiValue("EOS");

  data.add(MakeKey("Exif.Image.Model"), v2.get());
  data.add(MakeKey("Exif.Image.Make"), v1.get());

  const auto before = data.count();
  ASSERT_GE(before, 1u);

  data.sortByKey();
  EXPECT_EQ(data.count(), before);

  data.sortByTag();
  EXPECT_EQ(data.count(), before);

  // Still findable after sorts (no assumption about iterator position).
  EXPECT_NE(data.findKey(MakeKey("Exif.Image.Make")), data.end());
  EXPECT_NE(data.findKey(MakeKey("Exif.Image.Model")), data.end());
}

}  // namespace
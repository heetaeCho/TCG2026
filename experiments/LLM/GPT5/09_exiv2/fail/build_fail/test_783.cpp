// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_exifdata_erase_pos_783.cpp

#include <gtest/gtest.h>

#include <exiv2/exif.hpp>
#include <exiv2/value.hpp>

#include <string>

namespace {

class ExifDataErasePosTest_783 : public ::testing::Test {
 protected:
  static Exiv2::ExifKey Key(const std::string& k) { return Exiv2::ExifKey(k); }

  static void AddAscii(Exiv2::ExifData& data, const std::string& key, const std::string& value) {
    Exiv2::Value::UniquePtr v = Exiv2::Value::create(Exiv2::asciiString);
    ASSERT_NE(v.get(), nullptr);
    ASSERT_NO_THROW(v->read(value));
    EXPECT_NO_THROW(data.add(Key(key), v.get()));
  }
};

TEST_F(ExifDataErasePosTest_783, EraseMiddleElementRemovesAndReturnsNext_783) {
  Exiv2::ExifData data;

  const std::string k1 = "Exif.Image.Make";
  const std::string k2 = "Exif.Image.Model";
  const std::string k3 = "Exif.Photo.DateTimeOriginal";

  ASSERT_NO_FATAL_FAILURE(AddAscii(data, k1, "Canon"));
  ASSERT_NO_FATAL_FAILURE(AddAscii(data, k2, "EOS"));
  ASSERT_NO_FATAL_FAILURE(AddAscii(data, k3, "2020:01:01 00:00:00"));

  ASSERT_FALSE(data.empty());
  ASSERT_GE(data.count(), static_cast<size_t>(3));

  auto it2 = data.findKey(Key(k2));
  ASSERT_NE(it2, data.end());

  const size_t before = data.count();
  auto ret = data.erase(it2);

  EXPECT_EQ(data.count(), before - 1);
  EXPECT_EQ(data.findKey(Key(k2)), data.end()) << "Erased key should no longer be found";

  // The returned iterator should be either end() or a valid iterator to the next element.
  if (ret != data.end()) {
    // Must not be the erased element anymore.
    EXPECT_NE(ret->key(), k2);
  }
}

TEST_F(ExifDataErasePosTest_783, EraseBeginRemovesFirstAndReturnsNewBeginOrEnd_783) {
  Exiv2::ExifData data;

  ASSERT_NO_FATAL_FAILURE(AddAscii(data, "Exif.Image.Make", "Canon"));
  ASSERT_NO_FATAL_FAILURE(AddAscii(data, "Exif.Image.Model", "EOS"));

  ASSERT_GE(data.count(), static_cast<size_t>(2));
  auto beg = data.begin();
  ASSERT_NE(beg, data.end());
  const std::string erasedKey = beg->key();

  const size_t before = data.count();
  auto ret = data.erase(beg);

  EXPECT_EQ(data.count(), before - 1);
  EXPECT_EQ(data.findKey(Key(erasedKey)), data.end());

  // After erasing begin(), returned iterator is typically the next element (or end()).
  if (!data.empty()) {
    EXPECT_NE(ret, data.end());
    EXPECT_EQ(ret, data.begin());
  } else {
    EXPECT_EQ(ret, data.end());
  }
}

TEST_F(ExifDataErasePosTest_783, EraseLastElementReturnsEnd_783) {
  Exiv2::ExifData data;

  ASSERT_NO_FATAL_FAILURE(AddAscii(data, "Exif.Image.Make", "Canon"));
  ASSERT_NO_FATAL_FAILURE(AddAscii(data, "Exif.Image.Model", "EOS"));
  ASSERT_NO_FATAL_FAILURE(AddAscii(data, "Exif.Photo.ExposureTime", "1/125"));

  ASSERT_GE(data.count(), static_cast<size_t>(3));

  // Get an iterator to the last element by walking from begin().
  auto last = data.begin();
  ASSERT_NE(last, data.end());
  auto next = last;
  ++next;
  while (next != data.end()) {
    last = next;
    ++next;
  }
  const std::string lastKey = last->key();

  const size_t before = data.count();
  auto ret = data.erase(last);

  EXPECT_EQ(data.count(), before - 1);
  EXPECT_EQ(data.findKey(Key(lastKey)), data.end());
  EXPECT_EQ(ret, data.end());
}

TEST_F(ExifDataErasePosTest_783, EraseOnlyElementMakesEmptyAndReturnsEnd_783) {
  Exiv2::ExifData data;

  ASSERT_NO_FATAL_FAILURE(AddAscii(data, "Exif.Image.Make", "Canon"));
  ASSERT_EQ(data.count(), static_cast<size_t>(1));
  ASSERT_FALSE(data.empty());

  auto it = data.begin();
  ASSERT_NE(it, data.end());

  auto ret = data.erase(it);

  EXPECT_TRUE(data.empty());
  EXPECT_EQ(data.count(), static_cast<size_t>(0));
  EXPECT_EQ(ret, data.end());
}

TEST_F(ExifDataErasePosTest_783, EraseThenEraseAgainOnRemainingElement_783) {
  Exiv2::ExifData data;

  ASSERT_NO_FATAL_FAILURE(AddAscii(data, "Exif.Image.Make", "Canon"));
  ASSERT_NO_FATAL_FAILURE(AddAscii(data, "Exif.Image.Model", "EOS"));
  ASSERT_EQ(data.count(), static_cast<size_t>(2));

  // Erase one element by key (via iterator), then erase the remaining begin().
  auto it = data.findKey(Key("Exif.Image.Model"));
  ASSERT_NE(it, data.end());

  auto ret1 = data.erase(it);
  (void)ret1;  // ret1 may be end() depending on ordering.
  ASSERT_EQ(data.count(), static_cast<size_t>(1));
  ASSERT_FALSE(data.empty());

  auto ret2 = data.erase(data.begin());
  EXPECT_TRUE(data.empty());
  EXPECT_EQ(data.count(), static_cast<size_t>(0));
  EXPECT_EQ(ret2, data.end());
}

}  // namespace
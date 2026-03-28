// File: test_exifdata_erase_range_782.cpp
#include <gtest/gtest.h>

#include <exiv2/exif.hpp>

#include <iterator>
#include <string>
#include <vector>

namespace {

class ExifDataEraseRangeTest_782 : public ::testing::Test {
 protected:
  static void TouchKeys(Exiv2::ExifData& data, const std::vector<std::string>& keys) {
    for (const auto& k : keys) {
      // operator[] is part of the public interface; treat as black-box insertion/access.
      (void)data[k];
    }
  }

  static std::vector<std::string> MakeNKeys(size_t n) {
    std::vector<std::string> out;
    out.reserve(n);
    for (size_t i = 0; i < n; ++i) {
      out.push_back("Exif.Image.ProcessingSoftware." + std::to_string(i));
    }
    return out;
  }
};

TEST_F(ExifDataEraseRangeTest_782, EraseOnEmptyBeginToEndDoesNotThrowAndReturnsEnd_782) {
  Exiv2::ExifData data;
  ASSERT_TRUE(data.empty());
  ASSERT_EQ(data.count(), 0u);

  Exiv2::ExifData::iterator ret{};
  EXPECT_NO_THROW(ret = data.erase(data.begin(), data.end()));

  EXPECT_EQ(ret, data.end());
  EXPECT_TRUE(data.empty());
  EXPECT_EQ(data.count(), 0u);
}

TEST_F(ExifDataEraseRangeTest_782, EraseRangeBeginToBeginIsNoOpAndReturnsBegin_782) {
  Exiv2::ExifData data;
  TouchKeys(data, MakeNKeys(3));
  ASSERT_GE(data.count(), 1u);

  const auto beforeCount = data.count();
  auto b = data.begin();

  Exiv2::ExifData::iterator ret{};
  EXPECT_NO_THROW(ret = data.erase(b, b));

  EXPECT_EQ(ret, data.begin());   // begin should remain the same position after no-op
  EXPECT_EQ(data.count(), beforeCount);
  EXPECT_EQ(data.empty(), beforeCount == 0u);
}

TEST_F(ExifDataEraseRangeTest_782, EraseFirstElementReturnsNewBeginAndDecreasesCount_782) {
  Exiv2::ExifData data;
  TouchKeys(data, MakeNKeys(5));
  ASSERT_EQ(data.count(), 5u);

  auto b = data.begin();
  auto b_next = std::next(b);

  Exiv2::ExifData::iterator ret{};
  EXPECT_NO_THROW(ret = data.erase(b, b_next));

  EXPECT_EQ(data.count(), 4u);
  // For standard erase semantics, returned iterator should point to the element that
  // is now at the erased position; that is exactly data.begin() after erasing first.
  EXPECT_EQ(ret, data.begin());
}

TEST_F(ExifDataEraseRangeTest_782, EraseTailFromMiddleToEndReturnsEndAndLeavesPrefix_782) {
  Exiv2::ExifData data;
  TouchKeys(data, MakeNKeys(5));
  ASSERT_EQ(data.count(), 5u);

  auto it_mid = std::next(data.begin(), 2);

  Exiv2::ExifData::iterator ret{};
  EXPECT_NO_THROW(ret = data.erase(it_mid, data.end()));

  EXPECT_EQ(ret, data.end());
  EXPECT_EQ(data.count(), 2u);
  EXPECT_FALSE(data.empty());
}

TEST_F(ExifDataEraseRangeTest_782, EraseAllElementsBeginToEndEmptiesContainerAndReturnsEnd_782) {
  Exiv2::ExifData data;
  TouchKeys(data, MakeNKeys(4));
  ASSERT_EQ(data.count(), 4u);

  Exiv2::ExifData::iterator ret{};
  EXPECT_NO_THROW(ret = data.erase(data.begin(), data.end()));

  EXPECT_EQ(ret, data.end());
  EXPECT_TRUE(data.empty());
  EXPECT_EQ(data.count(), 0u);
}

}  // namespace
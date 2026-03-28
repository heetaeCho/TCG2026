#include <gtest/gtest.h>
#include <vector>
#include <string>

// Include the header under test
#include "exiv2/slice.hpp"

// Test fixture for MutableSliceBase tests via Slice
class MutableSliceBaseTest_9 : public ::testing::Test {
 protected:
  void SetUp() override {
    vec_ = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
  }

  std::vector<int> vec_;
};

// Test that end() returns an iterator pointing past the last element of the slice
TEST_F(MutableSliceBaseTest_9, EndIteratorPointsPastLastElement_9) {
  auto slice = Exiv2::Slice<std::vector<int>>(vec_, 0, vec_.size());
  auto it = slice.end();
  // end() should be one past the last element; decrementing should give last element
  --it;
  EXPECT_EQ(*it, 100);
}

// Test that end() for a sub-slice is correct
TEST_F(MutableSliceBaseTest_9, EndIteratorForSubSlice_9) {
  auto slice = Exiv2::Slice<std::vector<int>>(vec_, 2, 5);
  // Slice covers indices 2..4 -> values 30, 40, 50
  auto it = slice.end();
  --it;
  EXPECT_EQ(*it, 50);
}

// Test that begin() to end() range covers all elements in the slice
TEST_F(MutableSliceBaseTest_9, BeginToEndCoversAllElements_9) {
  auto slice = Exiv2::Slice<std::vector<int>>(vec_, 1, 4);
  std::vector<int> result;
  for (auto it = slice.begin(); it != slice.end(); ++it) {
    result.push_back(*it);
  }
  EXPECT_EQ(result.size(), 3u);
  EXPECT_EQ(result[0], 20);
  EXPECT_EQ(result[1], 30);
  EXPECT_EQ(result[2], 40);
}

// Test that end() - begin() equals slice size
TEST_F(MutableSliceBaseTest_9, EndMinusBeginEqualsSize_9) {
  auto slice = Exiv2::Slice<std::vector<int>>(vec_, 3, 7);
  auto dist = std::distance(slice.begin(), slice.end());
  EXPECT_EQ(dist, 4);
}

// Test end() on a single-element slice
TEST_F(MutableSliceBaseTest_9, SingleElementSliceEnd_9) {
  auto slice = Exiv2::Slice<std::vector<int>>(vec_, 5, 6);
  auto it = slice.begin();
  ++it;
  EXPECT_EQ(it, slice.end());
}

// Test end() on an empty slice (begin == end)
TEST_F(MutableSliceBaseTest_9, EmptySliceEndEqualsBegin_9) {
  auto slice = Exiv2::Slice<std::vector<int>>(vec_, 3, 3);
  EXPECT_EQ(slice.begin(), slice.end());
}

// Test that elements can be modified through iterators from begin() to end()
TEST_F(MutableSliceBaseTest_9, MutableIteratorModifiesElements_9) {
  auto slice = Exiv2::Slice<std::vector<int>>(vec_, 0, 3);
  for (auto it = slice.begin(); it != slice.end(); ++it) {
    *it = *it * 2;
  }
  EXPECT_EQ(vec_[0], 20);
  EXPECT_EQ(vec_[1], 40);
  EXPECT_EQ(vec_[2], 60);
  // Elements outside the slice should be unchanged
  EXPECT_EQ(vec_[3], 40);
}

// Test at() for valid index
TEST_F(MutableSliceBaseTest_9, AtValidIndex_9) {
  auto slice = Exiv2::Slice<std::vector<int>>(vec_, 2, 6);
  EXPECT_EQ(slice.at(0), 30);
  EXPECT_EQ(slice.at(1), 40);
  EXPECT_EQ(slice.at(2), 50);
  EXPECT_EQ(slice.at(3), 60);
}

// Test at() for out-of-range index throws
TEST_F(MutableSliceBaseTest_9, AtOutOfRangeThrows_9) {
  auto slice = Exiv2::Slice<std::vector<int>>(vec_, 2, 5);
  EXPECT_THROW(slice.at(3), std::out_of_range);
}

// Test at() modification reflects in original container
TEST_F(MutableSliceBaseTest_9, AtModifiesOriginal_9) {
  auto slice = Exiv2::Slice<std::vector<int>>(vec_, 0, 5);
  slice.at(2) = 999;
  EXPECT_EQ(vec_[2], 999);
}

// Test subSlice creation and its end()
TEST_F(MutableSliceBaseTest_9, SubSliceEndIsCorrect_9) {
  auto slice = Exiv2::Slice<std::vector<int>>(vec_, 1, 8);
  auto sub = slice.subSlice(1, 4);
  // sub covers original indices 2..4 -> values 30, 40, 50
  std::vector<int> result;
  for (auto it = sub.begin(); it != sub.end(); ++it) {
    result.push_back(*it);
  }
  EXPECT_EQ(result.size(), 3u);
  EXPECT_EQ(result[0], 30);
  EXPECT_EQ(result[1], 40);
  EXPECT_EQ(result[2], 50);
}

// Test that creating a slice with invalid range throws
TEST_F(MutableSliceBaseTest_9, InvalidRangeThrows_9) {
  EXPECT_THROW(
      (Exiv2::Slice<std::vector<int>>(vec_, 5, 3)),
      std::out_of_range);
}

// Test that creating a slice beyond container size throws
TEST_F(MutableSliceBaseTest_9, BeyondContainerSizeThrows_9) {
  EXPECT_THROW(
      (Exiv2::Slice<std::vector<int>>(vec_, 0, vec_.size() + 1)),
      std::out_of_range);
}

// Test full-range slice covers entire vector
TEST_F(MutableSliceBaseTest_9, FullRangeSlice_9) {
  auto slice = Exiv2::Slice<std::vector<int>>(vec_, 0, vec_.size());
  auto dist = std::distance(slice.begin(), slice.end());
  EXPECT_EQ(static_cast<size_t>(dist), vec_.size());
}

// Test with byte data (uint8_t vector)
TEST(MutableSliceBaseByteTest_9, ByteVectorSlice_9) {
  std::vector<uint8_t> data = {0x00, 0x01, 0x02, 0x03, 0x04, 0xFF};
  auto slice = Exiv2::Slice<std::vector<uint8_t>>(data, 1, 5);

  auto it = slice.end();
  --it;
  EXPECT_EQ(*it, 0x04);

  EXPECT_EQ(slice.at(0), 0x01);
  EXPECT_EQ(slice.at(3), 0x04);
}

// Test subSlice with invalid range throws
TEST_F(MutableSliceBaseTest_9, SubSliceInvalidRangeThrows_9) {
  auto slice = Exiv2::Slice<std::vector<int>>(vec_, 0, 5);
  EXPECT_THROW(slice.subSlice(3, 1), std::out_of_range);
}

// Test subSlice beyond parent slice size throws
TEST_F(MutableSliceBaseTest_9, SubSliceBeyondParentThrows_9) {
  auto slice = Exiv2::Slice<std::vector<int>>(vec_, 0, 5);
  EXPECT_THROW(slice.subSlice(0, 6), std::out_of_range);
}

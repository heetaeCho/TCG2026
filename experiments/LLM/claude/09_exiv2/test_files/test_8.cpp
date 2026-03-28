#include <gtest/gtest.h>
#include <vector>
#include <string>

// Include the header under test
#include "exiv2/slice.hpp"

using namespace Exiv2;

// Test fixture for MutableSlice tests using vector<uint8_t>
class MutableSliceTest_8 : public ::testing::Test {
 protected:
  void SetUp() override {
    data_ = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  }

  std::vector<uint8_t> data_;
};

// Test that begin() returns an iterator pointing to the correct element
TEST_F(MutableSliceTest_8, BeginPointsToFirstElement_8) {
  auto slice = Slice<uint8_t>(data_, 0, data_.size());
  auto it = slice.begin();
  EXPECT_EQ(*it, 0);
}

// Test that begin() on a slice with non-zero start offset points to the correct element
TEST_F(MutableSliceTest_8, BeginWithOffsetPointsToCorrectElement_8) {
  auto slice = Slice<uint8_t>(data_, 3, 7);
  auto it = slice.begin();
  EXPECT_EQ(*it, 3);
}

// Test that end() returns an iterator past the last element
TEST_F(MutableSliceTest_8, EndIteratorIsCorrect_8) {
  auto slice = Slice<uint8_t>(data_, 2, 5);
  auto it = slice.end();
  --it;
  EXPECT_EQ(*it, 4);
}

// Test that iterating from begin to end covers the correct number of elements
TEST_F(MutableSliceTest_8, BeginToEndDistance_8) {
  auto slice = Slice<uint8_t>(data_, 1, 6);
  size_t count = 0;
  for (auto it = slice.begin(); it != slice.end(); ++it) {
    ++count;
  }
  EXPECT_EQ(count, 5u);
}

// Test that elements accessed via begin iterator can be modified
TEST_F(MutableSliceTest_8, BeginIteratorAllowsMutation_8) {
  auto slice = Slice<uint8_t>(data_, 0, data_.size());
  auto it = slice.begin();
  *it = 42;
  EXPECT_EQ(data_[0], 42);
}

// Test at() for valid index
TEST_F(MutableSliceTest_8, AtReturnsCorrectElement_8) {
  auto slice = Slice<uint8_t>(data_, 2, 8);
  EXPECT_EQ(slice.at(0), 2);
  EXPECT_EQ(slice.at(3), 5);
  EXPECT_EQ(slice.at(5), 7);
}

// Test at() for mutation
TEST_F(MutableSliceTest_8, AtAllowsMutation_8) {
  auto slice = Slice<uint8_t>(data_, 0, data_.size());
  slice.at(5) = 99;
  EXPECT_EQ(data_[5], 99);
}

// Test at() throws for out of range index
TEST_F(MutableSliceTest_8, AtThrowsOnOutOfRange_8) {
  auto slice = Slice<uint8_t>(data_, 2, 5);
  EXPECT_THROW(slice.at(3), std::out_of_range);
  EXPECT_THROW(slice.at(100), std::out_of_range);
}

// Test that a slice of size 1 works correctly
TEST_F(MutableSliceTest_8, SingleElementSlice_8) {
  auto slice = Slice<uint8_t>(data_, 4, 5);
  EXPECT_EQ(slice.at(0), 4);
  EXPECT_EQ(std::distance(slice.begin(), slice.end()), 1);
}

// Test that a full-range slice covers all elements
TEST_F(MutableSliceTest_8, FullRangeSlice_8) {
  auto slice = Slice<uint8_t>(data_, 0, data_.size());
  size_t i = 0;
  for (auto it = slice.begin(); it != slice.end(); ++it, ++i) {
    EXPECT_EQ(*it, data_[i]);
  }
  EXPECT_EQ(i, data_.size());
}

// Test subSlice returns correct sub-range
TEST_F(MutableSliceTest_8, SubSliceReturnsCorrectRange_8) {
  auto slice = Slice<uint8_t>(data_, 1, 9);
  auto sub = slice.subSlice(2, 5);
  // sub should cover data_[3], data_[4], data_[5]
  EXPECT_EQ(sub.at(0), 3);
  EXPECT_EQ(sub.at(1), 4);
  EXPECT_EQ(sub.at(2), 5);
}

// Test subSlice boundary: subSlice(0, size) returns equivalent slice
TEST_F(MutableSliceTest_8, SubSliceFullRange_8) {
  auto slice = Slice<uint8_t>(data_, 2, 7);
  auto sub = slice.subSlice(0, 5);
  for (size_t i = 0; i < 5; ++i) {
    EXPECT_EQ(sub.at(i), slice.at(i));
  }
}

// Test subSlice with invalid range throws
TEST_F(MutableSliceTest_8, SubSliceInvalidRangeThrows_8) {
  auto slice = Slice<uint8_t>(data_, 0, 5);
  EXPECT_THROW(slice.subSlice(3, 6), std::out_of_range);
}

// Test creating slice with begin == end (empty slice)
TEST_F(MutableSliceTest_8, EmptySlice_8) {
  auto slice = Slice<uint8_t>(data_, 3, 3);
  EXPECT_EQ(slice.begin(), slice.end());
  EXPECT_EQ(std::distance(slice.begin(), slice.end()), 0);
}

// Test creating slice with begin > end throws
TEST_F(MutableSliceTest_8, InvalidRangeThrows_8) {
  EXPECT_THROW(Slice<uint8_t>(data_, 5, 3), std::out_of_range);
}

// Test creating slice with end > container size throws
TEST_F(MutableSliceTest_8, EndBeyondSizeThrows_8) {
  EXPECT_THROW(Slice<uint8_t>(data_, 0, data_.size() + 1), std::out_of_range);
}

// Test modification through iterator is reflected in underlying data
TEST_F(MutableSliceTest_8, ModificationThroughIteratorReflected_8) {
  auto slice = Slice<uint8_t>(data_, 2, 6);
  size_t idx = 0;
  for (auto it = slice.begin(); it != slice.end(); ++it, ++idx) {
    *it = static_cast<uint8_t>(100 + idx);
  }
  EXPECT_EQ(data_[2], 100);
  EXPECT_EQ(data_[3], 101);
  EXPECT_EQ(data_[4], 102);
  EXPECT_EQ(data_[5], 103);
}

// Test with vector<int> data type
class MutableSliceIntTest_8 : public ::testing::Test {
 protected:
  void SetUp() override {
    data_ = {10, 20, 30, 40, 50};
  }
  std::vector<int> data_;
};

TEST_F(MutableSliceIntTest_8, BeginPointsCorrectly_8) {
  auto slice = Slice<int>(data_, 1, 4);
  EXPECT_EQ(*slice.begin(), 20);
}

TEST_F(MutableSliceIntTest_8, AtAccessCorrect_8) {
  auto slice = Slice<int>(data_, 0, 5);
  EXPECT_EQ(slice.at(2), 30);
  slice.at(2) = 300;
  EXPECT_EQ(data_[2], 300);
}

TEST_F(MutableSliceIntTest_8, IteratorDistance_8) {
  auto slice = Slice<int>(data_, 0, 5);
  EXPECT_EQ(std::distance(slice.begin(), slice.end()), 5);
}

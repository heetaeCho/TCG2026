#include <gtest/gtest.h>
#include <vector>
#include <array>
#include <stdexcept>

// Include the slice header
#include "exiv2/slice.hpp"

using namespace Exiv2;

class SliceSubSliceTest_11 : public ::testing::Test {
 protected:
  void SetUp() override {
    vec_ = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  }

  std::vector<int> vec_;
};

// Test that creating a subSlice of the full range works
TEST_F(SliceSubSliceTest_11, SubSliceFullRange_11) {
  auto slice = Slice<std::vector<int>>(vec_, 0, vec_.size());
  auto sub = slice.subSlice(0, vec_.size());
  EXPECT_EQ(sub.size(), vec_.size());
  for (size_t i = 0; i < sub.size(); ++i) {
    EXPECT_EQ(sub.at(i), static_cast<int>(i));
  }
}

// Test subSlice with a subset in the middle
TEST_F(SliceSubSliceTest_11, SubSliceMiddleRange_11) {
  auto slice = Slice<std::vector<int>>(vec_, 0, vec_.size());
  auto sub = slice.subSlice(2, 5);
  EXPECT_EQ(sub.size(), 3u);
  EXPECT_EQ(sub.at(0), 2);
  EXPECT_EQ(sub.at(1), 3);
  EXPECT_EQ(sub.at(2), 4);
}

// Test subSlice from beginning
TEST_F(SliceSubSliceTest_11, SubSliceFromBeginning_11) {
  auto slice = Slice<std::vector<int>>(vec_, 0, vec_.size());
  auto sub = slice.subSlice(0, 3);
  EXPECT_EQ(sub.size(), 3u);
  EXPECT_EQ(sub.at(0), 0);
  EXPECT_EQ(sub.at(1), 1);
  EXPECT_EQ(sub.at(2), 2);
}

// Test subSlice to end
TEST_F(SliceSubSliceTest_11, SubSliceToEnd_11) {
  auto slice = Slice<std::vector<int>>(vec_, 0, vec_.size());
  auto sub = slice.subSlice(7, 10);
  EXPECT_EQ(sub.size(), 3u);
  EXPECT_EQ(sub.at(0), 7);
  EXPECT_EQ(sub.at(1), 8);
  EXPECT_EQ(sub.at(2), 9);
}

// Test subSlice of size 1
TEST_F(SliceSubSliceTest_11, SubSliceSingleElement_11) {
  auto slice = Slice<std::vector<int>>(vec_, 0, vec_.size());
  auto sub = slice.subSlice(5, 6);
  EXPECT_EQ(sub.size(), 1u);
  EXPECT_EQ(sub.at(0), 5);
}

// Test subSlice with end exceeding parent slice range throws
TEST_F(SliceSubSliceTest_11, SubSliceEndExceedsRange_11) {
  auto slice = Slice<std::vector<int>>(vec_, 0, 5);
  EXPECT_THROW(slice.subSlice(0, 6), std::out_of_range);
}

// Test subSlice with begin out of range throws
TEST_F(SliceSubSliceTest_11, SubSliceBeginOutOfRange_11) {
  auto slice = Slice<std::vector<int>>(vec_, 0, 5);
  EXPECT_THROW(slice.subSlice(6, 7), std::out_of_range);
}

// Test subSlice on a slice that is itself offset
TEST_F(SliceSubSliceTest_11, SubSliceOfOffsetSlice_11) {
  auto slice = Slice<std::vector<int>>(vec_, 3, 8);
  // slice contains elements {3, 4, 5, 6, 7}
  auto sub = slice.subSlice(1, 4);
  // sub should contain {4, 5, 6}
  EXPECT_EQ(sub.size(), 3u);
  EXPECT_EQ(sub.at(0), 4);
  EXPECT_EQ(sub.at(1), 5);
  EXPECT_EQ(sub.at(2), 6);
}

// Test that subSlice with begin == end throws (empty range, end-1 would underflow or be out of range)
TEST_F(SliceSubSliceTest_11, SubSliceEmptyRangeBeginEqualsEnd_11) {
  auto slice = Slice<std::vector<int>>(vec_, 0, vec_.size());
  // begin == end means size 0, but end-1 == begin-1 which could be problematic
  // When begin=5, end=5, end-1=4 which is valid, but new_end == new_begin
  // This depends on implementation - let's test it
  // Actually with begin=0, end=0, end-1 wraps around for size_t
  EXPECT_THROW(slice.subSlice(0, 0), std::out_of_range);
}

// Test mutability: modifications through subSlice reflect in original
TEST_F(SliceSubSliceTest_11, SubSliceMutationsReflectInOriginal_11) {
  auto slice = Slice<std::vector<int>>(vec_, 0, vec_.size());
  auto sub = slice.subSlice(2, 5);
  sub.at(0) = 42;
  EXPECT_EQ(vec_[2], 42);
  EXPECT_EQ(slice.at(2), 42);
}

// Test nested subSlice
TEST_F(SliceSubSliceTest_11, NestedSubSlice_11) {
  auto slice = Slice<std::vector<int>>(vec_, 0, vec_.size());
  auto sub1 = slice.subSlice(2, 8);   // {2,3,4,5,6,7}
  auto sub2 = sub1.subSlice(1, 4);    // {3,4,5}
  EXPECT_EQ(sub2.size(), 3u);
  EXPECT_EQ(sub2.at(0), 3);
  EXPECT_EQ(sub2.at(1), 4);
  EXPECT_EQ(sub2.at(2), 5);
}

// Test subSlice where begin > end (invalid)
TEST_F(SliceSubSliceTest_11, SubSliceBeginGreaterThanEnd_11) {
  auto slice = Slice<std::vector<int>>(vec_, 0, vec_.size());
  EXPECT_THROW(slice.subSlice(5, 3), std::out_of_range);
}

// Test subSlice at boundary of parent slice
TEST_F(SliceSubSliceTest_11, SubSliceAtExactBoundary_11) {
  auto slice = Slice<std::vector<int>>(vec_, 2, 7);
  // slice has indices 0..4 (elements 2,3,4,5,6)
  auto sub = slice.subSlice(0, 5);
  EXPECT_EQ(sub.size(), 5u);
  EXPECT_EQ(sub.at(0), 2);
  EXPECT_EQ(sub.at(4), 6);
}

// Test subSlice iterator access
TEST_F(SliceSubSliceTest_11, SubSliceIteratorAccess_11) {
  auto slice = Slice<std::vector<int>>(vec_, 0, vec_.size());
  auto sub = slice.subSlice(3, 6);
  std::vector<int> result(sub.begin(), sub.end());
  ASSERT_EQ(result.size(), 3u);
  EXPECT_EQ(result[0], 3);
  EXPECT_EQ(result[1], 4);
  EXPECT_EQ(result[2], 5);
}

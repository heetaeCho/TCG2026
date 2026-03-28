#include <gtest/gtest.h>
#include <vector>
#include <string>
#include <stdexcept>

#include "exiv2/slice.hpp"

// Test fixture for Slice tests
class SliceTest_4 : public ::testing::Test {
 protected:
  void SetUp() override {
    testVec_ = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
  }

  std::vector<int> testVec_;
};

// ==================== SliceBase tests ====================

TEST_F(SliceTest_4, SizeReturnsCorrectValue_4) {
  auto slice = Exiv2::Slice<const std::vector<int>>(testVec_, 2, 5);
  EXPECT_EQ(slice.size(), 3u);
}

TEST_F(SliceTest_4, SizeOfEmptySliceIsZero_4) {
  auto slice = Exiv2::Slice<const std::vector<int>>(testVec_, 3, 3);
  EXPECT_EQ(slice.size(), 0u);
}

TEST_F(SliceTest_4, SizeOfFullSlice_4) {
  auto slice = Exiv2::Slice<const std::vector<int>>(testVec_, 0, 10);
  EXPECT_EQ(slice.size(), 10u);
}

// ==================== Construction tests ====================

TEST_F(SliceTest_4, ConstructionWithValidRange_4) {
  EXPECT_NO_THROW((Exiv2::Slice<const std::vector<int>>(testVec_, 0, 5)));
}

TEST_F(SliceTest_4, ConstructionWithBeginGreaterThanEndThrows_4) {
  EXPECT_THROW((Exiv2::Slice<const std::vector<int>>(testVec_, 5, 2)), std::out_of_range);
}

TEST_F(SliceTest_4, ConstructionWithEndBeyondSizeThrows_4) {
  EXPECT_THROW((Exiv2::Slice<const std::vector<int>>(testVec_, 0, 20)), std::out_of_range);
}

TEST_F(SliceTest_4, ConstructionWithBeginEqualsEnd_4) {
  EXPECT_NO_THROW((Exiv2::Slice<const std::vector<int>>(testVec_, 5, 5)));
}

TEST_F(SliceTest_4, ConstructionAtBoundary_4) {
  EXPECT_NO_THROW((Exiv2::Slice<const std::vector<int>>(testVec_, 0, 10)));
}

// ==================== at() tests ====================

TEST_F(SliceTest_4, AtReturnsCorrectElement_4) {
  auto slice = Exiv2::Slice<const std::vector<int>>(testVec_, 2, 7);
  EXPECT_EQ(slice.at(0), 30);
  EXPECT_EQ(slice.at(1), 40);
  EXPECT_EQ(slice.at(2), 50);
  EXPECT_EQ(slice.at(3), 60);
  EXPECT_EQ(slice.at(4), 70);
}

TEST_F(SliceTest_4, AtFirstElement_4) {
  auto slice = Exiv2::Slice<const std::vector<int>>(testVec_, 0, 5);
  EXPECT_EQ(slice.at(0), 10);
}

TEST_F(SliceTest_4, AtLastElement_4) {
  auto slice = Exiv2::Slice<const std::vector<int>>(testVec_, 0, 5);
  EXPECT_EQ(slice.at(4), 50);
}

TEST_F(SliceTest_4, AtOutOfRangeThrows_4) {
  auto slice = Exiv2::Slice<const std::vector<int>>(testVec_, 2, 5);
  EXPECT_THROW(slice.at(3), std::out_of_range);
}

TEST_F(SliceTest_4, AtOnEmptySliceThrows_4) {
  auto slice = Exiv2::Slice<const std::vector<int>>(testVec_, 3, 3);
  EXPECT_THROW(slice.at(0), std::out_of_range);
}

// ==================== cbegin/cend iterator tests ====================

TEST_F(SliceTest_4, CbeginPointsToFirstElement_4) {
  auto slice = Exiv2::Slice<const std::vector<int>>(testVec_, 3, 7);
  auto it = slice.cbegin();
  EXPECT_EQ(*it, 40);
}

TEST_F(SliceTest_4, CendMinusCbeginEqualsSize_4) {
  auto slice = Exiv2::Slice<const std::vector<int>>(testVec_, 2, 8);
  auto dist = std::distance(slice.cbegin(), slice.cend());
  EXPECT_EQ(static_cast<size_t>(dist), slice.size());
}

TEST_F(SliceTest_4, IteratorTraversalMatchesAt_4) {
  auto slice = Exiv2::Slice<const std::vector<int>>(testVec_, 1, 6);
  size_t idx = 0;
  for (auto it = slice.cbegin(); it != slice.cend(); ++it, ++idx) {
    EXPECT_EQ(*it, slice.at(idx));
  }
  EXPECT_EQ(idx, slice.size());
}

TEST_F(SliceTest_4, EmptySliceIteratorsAreEqual_4) {
  auto slice = Exiv2::Slice<const std::vector<int>>(testVec_, 4, 4);
  EXPECT_EQ(slice.cbegin(), slice.cend());
}

// ==================== subSlice tests ====================

TEST_F(SliceTest_4, SubSliceReturnsCorrectElements_4) {
  auto slice = Exiv2::Slice<const std::vector<int>>(testVec_, 2, 8);
  // subSlice indices are relative to the parent slice
  auto sub = slice.subSlice(1, 4);
  EXPECT_EQ(sub.size(), 3u);
  EXPECT_EQ(sub.at(0), 40);
  EXPECT_EQ(sub.at(1), 50);
  EXPECT_EQ(sub.at(2), 60);
}

TEST_F(SliceTest_4, SubSliceEmptySlice_4) {
  auto slice = Exiv2::Slice<const std::vector<int>>(testVec_, 2, 8);
  auto sub = slice.subSlice(3, 3);
  EXPECT_EQ(sub.size(), 0u);
}

TEST_F(SliceTest_4, SubSliceFullRange_4) {
  auto slice = Exiv2::Slice<const std::vector<int>>(testVec_, 2, 8);
  auto sub = slice.subSlice(0, 6);
  EXPECT_EQ(sub.size(), 6u);
  EXPECT_EQ(sub.at(0), 30);
  EXPECT_EQ(sub.at(5), 80);
}

TEST_F(SliceTest_4, SubSliceOutOfRangeThrows_4) {
  auto slice = Exiv2::Slice<const std::vector<int>>(testVec_, 2, 5);
  EXPECT_THROW(slice.subSlice(0, 4), std::out_of_range);
}

TEST_F(SliceTest_4, SubSliceBeginGreaterThanEndThrows_4) {
  auto slice = Exiv2::Slice<const std::vector<int>>(testVec_, 2, 8);
  EXPECT_THROW(slice.subSlice(4, 2), std::out_of_range);
}

// ==================== Mutable slice tests ====================

TEST_F(SliceTest_4, MutableSliceAtReturnsCorrectElement_4) {
  auto slice = Exiv2::Slice<std::vector<int>>(testVec_, 1, 5);
  EXPECT_EQ(slice.at(0), 20);
  EXPECT_EQ(slice.at(3), 50);
}

TEST_F(SliceTest_4, MutableSliceAtAllowsModification_4) {
  auto slice = Exiv2::Slice<std::vector<int>>(testVec_, 1, 5);
  slice.at(0) = 999;
  EXPECT_EQ(slice.at(0), 999);
  EXPECT_EQ(testVec_[1], 999);
}

TEST_F(SliceTest_4, MutableSliceBeginIterator_4) {
  auto slice = Exiv2::Slice<std::vector<int>>(testVec_, 3, 7);
  auto it = slice.begin();
  EXPECT_EQ(*it, 40);
  *it = 42;
  EXPECT_EQ(testVec_[3], 42);
}

TEST_F(SliceTest_4, MutableSliceEndMinusBeginEqualsSize_4) {
  auto slice = Exiv2::Slice<std::vector<int>>(testVec_, 2, 9);
  auto dist = std::distance(slice.begin(), slice.end());
  EXPECT_EQ(static_cast<size_t>(dist), slice.size());
}

TEST_F(SliceTest_4, MutableSliceAtOutOfRangeThrows_4) {
  auto slice = Exiv2::Slice<std::vector<int>>(testVec_, 2, 5);
  EXPECT_THROW(slice.at(3), std::out_of_range);
}

// ==================== Slice from begin/end at boundaries ====================

TEST_F(SliceTest_4, SliceFromBeginning_4) {
  auto slice = Exiv2::Slice<const std::vector<int>>(testVec_, 0, 3);
  EXPECT_EQ(slice.at(0), 10);
  EXPECT_EQ(slice.at(2), 30);
  EXPECT_EQ(slice.size(), 3u);
}

TEST_F(SliceTest_4, SliceToEnd_4) {
  auto slice = Exiv2::Slice<const std::vector<int>>(testVec_, 7, 10);
  EXPECT_EQ(slice.at(0), 80);
  EXPECT_EQ(slice.at(2), 100);
  EXPECT_EQ(slice.size(), 3u);
}

TEST_F(SliceTest_4, SingleElementSlice_4) {
  auto slice = Exiv2::Slice<const std::vector<int>>(testVec_, 5, 6);
  EXPECT_EQ(slice.size(), 1u);
  EXPECT_EQ(slice.at(0), 60);
}

// ==================== Range-based for loop test ====================

TEST_F(SliceTest_4, RangeBasedForLoopOnConstSlice_4) {
  auto slice = Exiv2::Slice<const std::vector<int>>(testVec_, 0, 5);
  std::vector<int> collected;
  for (const auto& val : slice) {
    collected.push_back(val);
  }
  ASSERT_EQ(collected.size(), 5u);
  EXPECT_EQ(collected[0], 10);
  EXPECT_EQ(collected[4], 50);
}

TEST_F(SliceTest_4, RangeBasedForLoopOnMutableSlice_4) {
  auto slice = Exiv2::Slice<std::vector<int>>(testVec_, 2, 6);
  for (auto& val : slice) {
    val *= 2;
  }
  EXPECT_EQ(testVec_[2], 60);
  EXPECT_EQ(testVec_[3], 80);
  EXPECT_EQ(testVec_[4], 100);
  EXPECT_EQ(testVec_[5], 120);
  // Verify elements outside slice are unchanged
  EXPECT_EQ(testVec_[0], 10);
  EXPECT_EQ(testVec_[1], 20);
  EXPECT_EQ(testVec_[6], 70);
}

// ==================== MutableSlice subSlice tests ====================

TEST_F(SliceTest_4, MutableSubSliceReturnsCorrectElements_4) {
  auto slice = Exiv2::Slice<std::vector<int>>(testVec_, 1, 8);
  auto sub = slice.subSlice(2, 5);
  EXPECT_EQ(sub.size(), 3u);
  EXPECT_EQ(sub.at(0), 40);
  EXPECT_EQ(sub.at(1), 50);
  EXPECT_EQ(sub.at(2), 60);
}

TEST_F(SliceTest_4, MutableSubSliceAllowsModification_4) {
  auto slice = Exiv2::Slice<std::vector<int>>(testVec_, 1, 8);
  auto sub = slice.subSlice(0, 3);
  sub.at(0) = 111;
  EXPECT_EQ(testVec_[1], 111);
}

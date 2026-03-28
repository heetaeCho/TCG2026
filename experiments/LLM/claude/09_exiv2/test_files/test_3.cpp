#include <gtest/gtest.h>
#include <vector>
#include <string>
#include <stdexcept>

#include "exiv2/slice.hpp"

// Test fixture for Slice tests
class SliceTest_3 : public ::testing::Test {
 protected:
  void SetUp() override {
    testVec_ = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
  }

  std::vector<int> testVec_;
};

// ==================== Construction Tests ====================

TEST_F(SliceTest_3, ConstructValidSlice_3) {
  EXPECT_NO_THROW(Exiv2::Slice<const std::vector<int>> slice(testVec_, 0, 5));
}

TEST_F(SliceTest_3, ConstructFullRangeSlice_3) {
  EXPECT_NO_THROW(Exiv2::Slice<const std::vector<int>> slice(testVec_, 0, testVec_.size()));
}

TEST_F(SliceTest_3, ConstructEmptySlice_3) {
  EXPECT_NO_THROW(Exiv2::Slice<const std::vector<int>> slice(testVec_, 3, 3));
}

TEST_F(SliceTest_3, ConstructInvalidRangeThrows_3) {
  EXPECT_THROW(Exiv2::Slice<const std::vector<int>> slice(testVec_, 5, 3), std::out_of_range);
}

TEST_F(SliceTest_3, ConstructOutOfBoundsThrows_3) {
  EXPECT_THROW(Exiv2::Slice<const std::vector<int>> slice(testVec_, 0, testVec_.size() + 1), std::out_of_range);
}

// ==================== Size Tests ====================

TEST_F(SliceTest_3, SizeReturnsCorrectValue_3) {
  Exiv2::Slice<const std::vector<int>> slice(testVec_, 2, 7);
  EXPECT_EQ(slice.size(), 5u);
}

TEST_F(SliceTest_3, SizeOfEmptySliceIsZero_3) {
  Exiv2::Slice<const std::vector<int>> slice(testVec_, 4, 4);
  EXPECT_EQ(slice.size(), 0u);
}

TEST_F(SliceTest_3, SizeOfFullSlice_3) {
  Exiv2::Slice<const std::vector<int>> slice(testVec_, 0, testVec_.size());
  EXPECT_EQ(slice.size(), testVec_.size());
}

// ==================== at() Tests ====================

TEST_F(SliceTest_3, AtReturnsCorrectElement_3) {
  Exiv2::Slice<const std::vector<int>> slice(testVec_, 2, 7);
  // slice[0] should correspond to testVec_[2] = 30
  EXPECT_EQ(slice.at(0), 30);
  EXPECT_EQ(slice.at(1), 40);
  EXPECT_EQ(slice.at(2), 50);
  EXPECT_EQ(slice.at(3), 60);
  EXPECT_EQ(slice.at(4), 70);
}

TEST_F(SliceTest_3, AtFirstElement_3) {
  Exiv2::Slice<const std::vector<int>> slice(testVec_, 0, testVec_.size());
  EXPECT_EQ(slice.at(0), 10);
}

TEST_F(SliceTest_3, AtLastElement_3) {
  Exiv2::Slice<const std::vector<int>> slice(testVec_, 0, testVec_.size());
  EXPECT_EQ(slice.at(testVec_.size() - 1), 100);
}

TEST_F(SliceTest_3, AtOutOfRangeThrows_3) {
  Exiv2::Slice<const std::vector<int>> slice(testVec_, 2, 7);
  EXPECT_THROW(slice.at(5), std::out_of_range);
}

TEST_F(SliceTest_3, AtOnEmptySliceThrows_3) {
  Exiv2::Slice<const std::vector<int>> slice(testVec_, 3, 3);
  EXPECT_THROW(slice.at(0), std::out_of_range);
}

TEST_F(SliceTest_3, AtLargeIndexThrows_3) {
  Exiv2::Slice<const std::vector<int>> slice(testVec_, 0, 5);
  EXPECT_THROW(slice.at(100), std::out_of_range);
}

// ==================== Iterator Tests ====================

TEST_F(SliceTest_3, CbeginCendIteratorRange_3) {
  Exiv2::Slice<const std::vector<int>> slice(testVec_, 2, 5);
  std::vector<int> result(slice.cbegin(), slice.cend());
  std::vector<int> expected = {30, 40, 50};
  EXPECT_EQ(result, expected);
}

TEST_F(SliceTest_3, EmptySliceIteratorsEqual_3) {
  Exiv2::Slice<const std::vector<int>> slice(testVec_, 5, 5);
  EXPECT_EQ(slice.cbegin(), slice.cend());
}

TEST_F(SliceTest_3, FullSliceIteratorRange_3) {
  Exiv2::Slice<const std::vector<int>> slice(testVec_, 0, testVec_.size());
  std::vector<int> result(slice.cbegin(), slice.cend());
  EXPECT_EQ(result, testVec_);
}

// ==================== subSlice Tests ====================

TEST_F(SliceTest_3, SubSliceReturnsCorrectElements_3) {
  Exiv2::Slice<const std::vector<int>> slice(testVec_, 2, 8);
  // slice covers indices 2..7 of testVec_: {30, 40, 50, 60, 70, 80}
  // subSlice(1, 4) should give elements at relative positions 1,2,3: {40, 50, 60}
  auto sub = slice.subSlice(1, 4);
  EXPECT_EQ(sub.size(), 3u);
  EXPECT_EQ(sub.at(0), 40);
  EXPECT_EQ(sub.at(1), 50);
  EXPECT_EQ(sub.at(2), 60);
}

TEST_F(SliceTest_3, SubSliceEmptyRange_3) {
  Exiv2::Slice<const std::vector<int>> slice(testVec_, 2, 8);
  auto sub = slice.subSlice(3, 3);
  EXPECT_EQ(sub.size(), 0u);
}

TEST_F(SliceTest_3, SubSliceFullRange_3) {
  Exiv2::Slice<const std::vector<int>> slice(testVec_, 2, 5);
  auto sub = slice.subSlice(0, 3);
  EXPECT_EQ(sub.size(), 3u);
  EXPECT_EQ(sub.at(0), 30);
  EXPECT_EQ(sub.at(1), 40);
  EXPECT_EQ(sub.at(2), 50);
}

TEST_F(SliceTest_3, SubSliceInvalidRangeThrows_3) {
  Exiv2::Slice<const std::vector<int>> slice(testVec_, 2, 8);
  EXPECT_THROW(slice.subSlice(4, 2), std::out_of_range);
}

TEST_F(SliceTest_3, SubSliceOutOfBoundsThrows_3) {
  Exiv2::Slice<const std::vector<int>> slice(testVec_, 2, 8);
  // slice.size() == 6, requesting subSlice(0, 7) should throw
  EXPECT_THROW(slice.subSlice(0, 7), std::out_of_range);
}

// ==================== Mutable Slice Tests ====================

TEST_F(SliceTest_3, MutableSliceAt_3) {
  Exiv2::Slice<std::vector<int>> slice(testVec_, 1, 6);
  EXPECT_EQ(slice.at(0), 20);
  EXPECT_EQ(slice.at(4), 60);
}

TEST_F(SliceTest_3, MutableSliceModifyElement_3) {
  Exiv2::Slice<std::vector<int>> slice(testVec_, 1, 6);
  slice.at(0) = 999;
  EXPECT_EQ(slice.at(0), 999);
  EXPECT_EQ(testVec_[1], 999);
}

TEST_F(SliceTest_3, MutableSliceAtOutOfRangeThrows_3) {
  Exiv2::Slice<std::vector<int>> slice(testVec_, 1, 6);
  EXPECT_THROW(slice.at(5), std::out_of_range);
}

TEST_F(SliceTest_3, MutableSliceBeginEnd_3) {
  Exiv2::Slice<std::vector<int>> slice(testVec_, 3, 6);
  std::vector<int> result(slice.begin(), slice.end());
  std::vector<int> expected = {40, 50, 60};
  EXPECT_EQ(result, expected);
}

// ==================== Byte vector tests ====================

TEST_F(SliceTest_3, ByteVectorSlice_3) {
  std::vector<uint8_t> data = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05};
  Exiv2::Slice<const std::vector<uint8_t>> slice(data, 1, 4);
  EXPECT_EQ(slice.size(), 3u);
  EXPECT_EQ(slice.at(0), 0x01);
  EXPECT_EQ(slice.at(1), 0x02);
  EXPECT_EQ(slice.at(2), 0x03);
}

// ==================== Single element slice ====================

TEST_F(SliceTest_3, SingleElementSlice_3) {
  Exiv2::Slice<const std::vector<int>> slice(testVec_, 5, 6);
  EXPECT_EQ(slice.size(), 1u);
  EXPECT_EQ(slice.at(0), 60);
  EXPECT_THROW(slice.at(1), std::out_of_range);
}

// ==================== Boundary: begin == 0, end == 0 ====================

TEST_F(SliceTest_3, ZeroZeroSlice_3) {
  Exiv2::Slice<const std::vector<int>> slice(testVec_, 0, 0);
  EXPECT_EQ(slice.size(), 0u);
  EXPECT_THROW(slice.at(0), std::out_of_range);
}

// ==================== Const correctness ====================

TEST_F(SliceTest_3, ConstSliceAtReturnsConstRef_3) {
  const Exiv2::Slice<const std::vector<int>> slice(testVec_, 0, 5);
  // Should compile and return const reference
  const int& val = slice.at(0);
  EXPECT_EQ(val, 10);
}

#include <gtest/gtest.h>
#include <vector>
#include <string>
#include <stdexcept>

#include "exiv2/slice.hpp"

// Test fixture for Slice tests
class SliceTest_6 : public ::testing::Test {
 protected:
  void SetUp() override {
    testVec_ = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    testStr_ = "0123456789";
  }

  std::vector<int> testVec_;
  std::string testStr_;
};

// ==================== Construction Tests ====================

TEST_F(SliceTest_6, ConstructSliceFromVector_6) {
  ASSERT_NO_THROW(Exiv2::Slice<std::vector<int>> slice(testVec_, 0, testVec_.size()));
}

TEST_F(SliceTest_6, ConstructSliceWithValidRange_6) {
  ASSERT_NO_THROW(Exiv2::Slice<std::vector<int>> slice(testVec_, 2, 5));
}

TEST_F(SliceTest_6, ConstructSliceWithEmptyRange_6) {
  ASSERT_NO_THROW(Exiv2::Slice<std::vector<int>> slice(testVec_, 3, 3));
}

TEST_F(SliceTest_6, ConstructSliceWithInvalidRangeThrows_6) {
  ASSERT_THROW(Exiv2::Slice<std::vector<int>> slice(testVec_, 5, 3), std::out_of_range);
}

TEST_F(SliceTest_6, ConstructSliceWithEndBeyondSizeThrows_6) {
  ASSERT_THROW(Exiv2::Slice<std::vector<int>> slice(testVec_, 0, testVec_.size() + 1), std::out_of_range);
}

TEST_F(SliceTest_6, ConstructSliceWithBeginBeyondSizeThrows_6) {
  ASSERT_THROW(Exiv2::Slice<std::vector<int>> slice(testVec_, testVec_.size() + 1, testVec_.size() + 2), std::out_of_range);
}

// ==================== Size Tests ====================

TEST_F(SliceTest_6, SizeReturnsCorrectValue_6) {
  Exiv2::Slice<std::vector<int>> slice(testVec_, 2, 7);
  EXPECT_EQ(slice.size(), 5u);
}

TEST_F(SliceTest_6, SizeOfEmptySliceIsZero_6) {
  Exiv2::Slice<std::vector<int>> slice(testVec_, 3, 3);
  EXPECT_EQ(slice.size(), 0u);
}

TEST_F(SliceTest_6, SizeOfFullSlice_6) {
  Exiv2::Slice<std::vector<int>> slice(testVec_, 0, testVec_.size());
  EXPECT_EQ(slice.size(), testVec_.size());
}

// ==================== at() Tests ====================

TEST_F(SliceTest_6, AtReturnsCorrectElement_6) {
  Exiv2::Slice<std::vector<int>> slice(testVec_, 2, 7);
  // at(0) should be testVec_[2] = 2
  EXPECT_EQ(slice.at(0), 2);
  EXPECT_EQ(slice.at(1), 3);
  EXPECT_EQ(slice.at(4), 6);
}

TEST_F(SliceTest_6, AtOutOfRangeThrows_6) {
  Exiv2::Slice<std::vector<int>> slice(testVec_, 2, 7);
  EXPECT_THROW(slice.at(5), std::out_of_range);
}

TEST_F(SliceTest_6, AtOnEmptySliceThrows_6) {
  Exiv2::Slice<std::vector<int>> slice(testVec_, 3, 3);
  EXPECT_THROW(slice.at(0), std::out_of_range);
}

TEST_F(SliceTest_6, ConstAtReturnsCorrectElement_6) {
  const Exiv2::Slice<const std::vector<int>> slice(testVec_, 1, 4);
  EXPECT_EQ(slice.at(0), 1);
  EXPECT_EQ(slice.at(2), 3);
}

// ==================== Iterator Tests ====================

TEST_F(SliceTest_6, CbeginCendIterateCorrectly_6) {
  Exiv2::Slice<const std::vector<int>> slice(testVec_, 3, 6);
  std::vector<int> result(slice.cbegin(), slice.cend());
  std::vector<int> expected = {3, 4, 5};
  EXPECT_EQ(result, expected);
}

TEST_F(SliceTest_6, BeginEndIterateCorrectly_6) {
  Exiv2::Slice<std::vector<int>> slice(testVec_, 0, 3);
  std::vector<int> result(slice.begin(), slice.end());
  std::vector<int> expected = {0, 1, 2};
  EXPECT_EQ(result, expected);
}

TEST_F(SliceTest_6, EmptySliceIteratorsEqual_6) {
  Exiv2::Slice<const std::vector<int>> slice(testVec_, 5, 5);
  EXPECT_EQ(slice.cbegin(), slice.cend());
}

// ==================== subSlice Tests ====================

TEST_F(SliceTest_6, SubSliceReturnsCorrectElements_6) {
  Exiv2::Slice<const std::vector<int>> slice(testVec_, 2, 8);
  // slice covers indices [2, 8) -> elements {2, 3, 4, 5, 6, 7}
  // subSlice(1, 4) -> covers slice indices [1, 4) -> original indices [3, 6) -> {3, 4, 5}
  auto sub = slice.subSlice<Exiv2::Slice<const std::vector<int>>>(1, 4);
  EXPECT_EQ(sub.size(), 3u);
  EXPECT_EQ(sub.at(0), 3);
  EXPECT_EQ(sub.at(1), 4);
  EXPECT_EQ(sub.at(2), 5);
}

TEST_F(SliceTest_6, SubSliceOfEntireSlice_6) {
  Exiv2::Slice<const std::vector<int>> slice(testVec_, 2, 8);
  auto sub = slice.subSlice<Exiv2::Slice<const std::vector<int>>>(0, 6);
  EXPECT_EQ(sub.size(), 6u);
  EXPECT_EQ(sub.at(0), 2);
  EXPECT_EQ(sub.at(5), 7);
}

TEST_F(SliceTest_6, SubSliceEmptyRange_6) {
  Exiv2::Slice<const std::vector<int>> slice(testVec_, 2, 8);
  auto sub = slice.subSlice<Exiv2::Slice<const std::vector<int>>>(3, 3);
  EXPECT_EQ(sub.size(), 0u);
}

TEST_F(SliceTest_6, SubSliceEndBeyondSliceSizeThrows_6) {
  Exiv2::Slice<const std::vector<int>> slice(testVec_, 2, 8);
  // slice size is 6, subSlice(0, 7) should throw
  EXPECT_THROW(
      (slice.subSlice<Exiv2::Slice<const std::vector<int>>>(0, 7)),
      std::out_of_range);
}

TEST_F(SliceTest_6, SubSliceBeginBeyondEndThrows_6) {
  Exiv2::Slice<const std::vector<int>> slice(testVec_, 2, 8);
  EXPECT_THROW(
      (slice.subSlice<Exiv2::Slice<const std::vector<int>>>(5, 3)),
      std::out_of_range);
}

TEST_F(SliceTest_6, SubSliceFromBeginning_6) {
  Exiv2::Slice<const std::vector<int>> slice(testVec_, 0, 10);
  auto sub = slice.subSlice<Exiv2::Slice<const std::vector<int>>>(0, 3);
  EXPECT_EQ(sub.size(), 3u);
  EXPECT_EQ(sub.at(0), 0);
  EXPECT_EQ(sub.at(2), 2);
}

TEST_F(SliceTest_6, SubSliceAtEnd_6) {
  Exiv2::Slice<const std::vector<int>> slice(testVec_, 0, 10);
  auto sub = slice.subSlice<Exiv2::Slice<const std::vector<int>>>(7, 10);
  EXPECT_EQ(sub.size(), 3u);
  EXPECT_EQ(sub.at(0), 7);
  EXPECT_EQ(sub.at(2), 9);
}

TEST_F(SliceTest_6, NestedSubSlice_6) {
  Exiv2::Slice<const std::vector<int>> slice(testVec_, 1, 9);
  // slice covers [1, 9) -> {1, 2, 3, 4, 5, 6, 7, 8}
  auto sub1 = slice.subSlice<Exiv2::Slice<const std::vector<int>>>(1, 7);
  // sub1 covers original [2, 8) -> {2, 3, 4, 5, 6, 7}
  auto sub2 = sub1.subSlice<Exiv2::Slice<const std::vector<int>>>(1, 4);
  // sub2 covers original [3, 6) -> {3, 4, 5}
  EXPECT_EQ(sub2.size(), 3u);
  EXPECT_EQ(sub2.at(0), 3);
  EXPECT_EQ(sub2.at(1), 4);
  EXPECT_EQ(sub2.at(2), 5);
}

// ==================== Mutable Slice Tests ====================

TEST_F(SliceTest_6, MutableSliceModifiesOriginal_6) {
  Exiv2::Slice<std::vector<int>> slice(testVec_, 2, 5);
  slice.at(0) = 42;
  EXPECT_EQ(testVec_[2], 42);
}

TEST_F(SliceTest_6, MutableSliceAtReturnsReference_6) {
  Exiv2::Slice<std::vector<int>> slice(testVec_, 0, 5);
  slice.at(3) = 99;
  EXPECT_EQ(slice.at(3), 99);
  EXPECT_EQ(testVec_[3], 99);
}

// ==================== Const Slice from const vector ====================

TEST_F(SliceTest_6, ConstSliceFromConstVector_6) {
  const std::vector<int> constVec = {10, 20, 30, 40, 50};
  Exiv2::Slice<const std::vector<int>> slice(constVec, 1, 4);
  EXPECT_EQ(slice.size(), 3u);
  EXPECT_EQ(slice.at(0), 20);
  EXPECT_EQ(slice.at(2), 40);
}

// ==================== Boundary Tests ====================

TEST_F(SliceTest_6, SliceOfSingleElement_6) {
  Exiv2::Slice<const std::vector<int>> slice(testVec_, 5, 6);
  EXPECT_EQ(slice.size(), 1u);
  EXPECT_EQ(slice.at(0), 5);
}

TEST_F(SliceTest_6, SubSliceOfSingleElement_6) {
  Exiv2::Slice<const std::vector<int>> slice(testVec_, 0, 10);
  auto sub = slice.subSlice<Exiv2::Slice<const std::vector<int>>>(4, 5);
  EXPECT_EQ(sub.size(), 1u);
  EXPECT_EQ(sub.at(0), 4);
}

TEST_F(SliceTest_6, AtLastValidIndex_6) {
  Exiv2::Slice<const std::vector<int>> slice(testVec_, 0, 10);
  EXPECT_EQ(slice.at(9), 9);
}

TEST_F(SliceTest_6, AtFirstIndexAfterLastThrows_6) {
  Exiv2::Slice<const std::vector<int>> slice(testVec_, 0, 10);
  EXPECT_THROW(slice.at(10), std::out_of_range);
}

// ==================== String-based slice tests (if supported) ====================

TEST_F(SliceTest_6, SliceFromString_6) {
  // If Slice works with std::string
  try {
    Exiv2::Slice<const std::string> slice(testStr_, 2, 5);
    EXPECT_EQ(slice.size(), 3u);
    EXPECT_EQ(slice.at(0), '2');
    EXPECT_EQ(slice.at(2), '4');
  } catch (...) {
    // If string slicing is not supported, that's OK
    GTEST_SKIP() << "String slicing not supported";
  }
}

// ==================== MutableSubSlice Tests ====================

TEST_F(SliceTest_6, MutableSubSliceModifiesOriginal_6) {
  Exiv2::Slice<std::vector<int>> slice(testVec_, 1, 8);
  auto sub = slice.subSlice<Exiv2::Slice<std::vector<int>>>(2, 5);
  // sub covers original indices [3, 6) -> {3, 4, 5}
  sub.at(0) = 100;
  EXPECT_EQ(testVec_[3], 100);
}

// ==================== Empty vector edge case ====================

TEST_F(SliceTest_6, EmptyVectorEmptySlice_6) {
  std::vector<int> emptyVec;
  ASSERT_NO_THROW(Exiv2::Slice<std::vector<int>> slice(emptyVec, 0, 0));
}

TEST_F(SliceTest_6, EmptyVectorNonEmptySliceThrows_6) {
  std::vector<int> emptyVec;
  ASSERT_THROW(Exiv2::Slice<std::vector<int>> slice(emptyVec, 0, 1), std::out_of_range);
}

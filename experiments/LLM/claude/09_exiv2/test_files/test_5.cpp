#include <gtest/gtest.h>
#include <vector>
#include <string>
#include <stdexcept>

#include "exiv2/slice.hpp"

// Test fixture for Slice tests
class SliceTest_5 : public ::testing::Test {
 protected:
  void SetUp() override {
    testVec = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
  }

  std::vector<int> testVec;
};

// ==================== SliceBase Tests ====================

TEST_F(SliceTest_5, SizeReturnsCorrectValue_5) {
  Exiv2::Slice<std::vector<int>> slice(testVec, 2, 7);
  EXPECT_EQ(slice.size(), 5u);
}

TEST_F(SliceTest_5, SizeOfEmptySliceIsZero_5) {
  Exiv2::Slice<std::vector<int>> slice(testVec, 3, 3);
  EXPECT_EQ(slice.size(), 0u);
}

TEST_F(SliceTest_5, SizeOfFullSlice_5) {
  Exiv2::Slice<std::vector<int>> slice(testVec, 0, 10);
  EXPECT_EQ(slice.size(), 10u);
}

TEST_F(SliceTest_5, ConstructionWithBeginGreaterThanEndThrows_5) {
  EXPECT_THROW(Exiv2::Slice<std::vector<int>>(testVec, 5, 3), std::out_of_range);
}

TEST_F(SliceTest_5, ConstructionWithEndBeyondContainerThrows_5) {
  EXPECT_THROW(Exiv2::Slice<std::vector<int>>(testVec, 0, 11), std::out_of_range);
}

// ==================== ConstSliceBase / Slice<const> Tests ====================

TEST_F(SliceTest_5, ConstSliceAtReturnsCorrectElement_5) {
  const std::vector<int>& constVec = testVec;
  Exiv2::Slice<const std::vector<int>> slice(constVec, 2, 7);
  EXPECT_EQ(slice.at(0), 30);
  EXPECT_EQ(slice.at(1), 40);
  EXPECT_EQ(slice.at(4), 70);
}

TEST_F(SliceTest_5, ConstSliceAtOutOfRangeThrows_5) {
  const std::vector<int>& constVec = testVec;
  Exiv2::Slice<const std::vector<int>> slice(constVec, 2, 7);
  EXPECT_THROW(slice.at(5), std::out_of_range);
}

TEST_F(SliceTest_5, ConstSliceCbeginCendIterateCorrectly_5) {
  const std::vector<int>& constVec = testVec;
  Exiv2::Slice<const std::vector<int>> slice(constVec, 3, 6);
  std::vector<int> result(slice.cbegin(), slice.cend());
  std::vector<int> expected = {40, 50, 60};
  EXPECT_EQ(result, expected);
}

TEST_F(SliceTest_5, ConstSliceEmptyIteratorRange_5) {
  const std::vector<int>& constVec = testVec;
  Exiv2::Slice<const std::vector<int>> slice(constVec, 5, 5);
  EXPECT_EQ(slice.cbegin(), slice.cend());
}

// ==================== Mutable Slice Tests ====================

TEST_F(SliceTest_5, MutableSliceAtReturnsCorrectElement_5) {
  Exiv2::Slice<std::vector<int>> slice(testVec, 0, 5);
  EXPECT_EQ(slice.at(0), 10);
  EXPECT_EQ(slice.at(4), 50);
}

TEST_F(SliceTest_5, MutableSliceAtAllowsModification_5) {
  Exiv2::Slice<std::vector<int>> slice(testVec, 1, 4);
  slice.at(0) = 999;
  EXPECT_EQ(testVec[1], 999);
}

TEST_F(SliceTest_5, MutableSliceAtOutOfRangeThrows_5) {
  Exiv2::Slice<std::vector<int>> slice(testVec, 1, 4);
  EXPECT_THROW(slice.at(3), std::out_of_range);
}

TEST_F(SliceTest_5, MutableSliceBeginEndIterateCorrectly_5) {
  Exiv2::Slice<std::vector<int>> slice(testVec, 2, 5);
  std::vector<int> result(slice.begin(), slice.end());
  std::vector<int> expected = {30, 40, 50};
  EXPECT_EQ(result, expected);
}

TEST_F(SliceTest_5, MutableSliceCbeginCendWork_5) {
  Exiv2::Slice<std::vector<int>> slice(testVec, 0, 3);
  std::vector<int> result(slice.cbegin(), slice.cend());
  std::vector<int> expected = {10, 20, 30};
  EXPECT_EQ(result, expected);
}

// ==================== SubSlice Tests ====================

TEST_F(SliceTest_5, SubSliceReturnsCorrectElements_5) {
  Exiv2::Slice<std::vector<int>> slice(testVec, 2, 8);
  auto sub = slice.subSlice(1, 4);
  EXPECT_EQ(sub.size(), 3u);
  EXPECT_EQ(sub.at(0), 40);
  EXPECT_EQ(sub.at(1), 50);
  EXPECT_EQ(sub.at(2), 60);
}

TEST_F(SliceTest_5, SubSliceOfConstSlice_5) {
  const std::vector<int>& constVec = testVec;
  Exiv2::Slice<const std::vector<int>> slice(constVec, 1, 9);
  auto sub = slice.subSlice(2, 5);
  EXPECT_EQ(sub.size(), 3u);
  EXPECT_EQ(sub.at(0), 40);
  EXPECT_EQ(sub.at(1), 50);
  EXPECT_EQ(sub.at(2), 60);
}

TEST_F(SliceTest_5, SubSliceEmptySubSlice_5) {
  Exiv2::Slice<std::vector<int>> slice(testVec, 0, 10);
  auto sub = slice.subSlice(5, 5);
  EXPECT_EQ(sub.size(), 0u);
}

TEST_F(SliceTest_5, SubSliceWithBeginGreaterThanEndThrows_5) {
  Exiv2::Slice<std::vector<int>> slice(testVec, 0, 10);
  EXPECT_THROW(slice.subSlice(5, 3), std::out_of_range);
}

TEST_F(SliceTest_5, SubSliceWithEndBeyondSliceSizeThrows_5) {
  Exiv2::Slice<std::vector<int>> slice(testVec, 0, 5);
  EXPECT_THROW(slice.subSlice(0, 6), std::out_of_range);
}

// ==================== Boundary Tests ====================

TEST_F(SliceTest_5, SliceAtFirstElement_5) {
  Exiv2::Slice<std::vector<int>> slice(testVec, 0, 10);
  EXPECT_EQ(slice.at(0), 10);
}

TEST_F(SliceTest_5, SliceAtLastElement_5) {
  Exiv2::Slice<std::vector<int>> slice(testVec, 0, 10);
  EXPECT_EQ(slice.at(9), 100);
}

TEST_F(SliceTest_5, SliceAtNegativeBoundaryCheck_5) {
  Exiv2::Slice<std::vector<int>> slice(testVec, 0, 10);
  // size_t is unsigned, so a large value should trigger out_of_range
  EXPECT_THROW(slice.at(static_cast<size_t>(-1)), std::out_of_range);
}

// ==================== Tests with different container types ====================

TEST_F(SliceTest_5, SliceFromStringVector_5) {
  std::vector<std::string> strVec = {"hello", "world", "foo", "bar"};
  Exiv2::Slice<std::vector<std::string>> slice(strVec, 1, 3);
  EXPECT_EQ(slice.size(), 2u);
  EXPECT_EQ(slice.at(0), "world");
  EXPECT_EQ(slice.at(1), "foo");
}

TEST_F(SliceTest_5, MutableSliceModificationReflectsInOriginal_5) {
  Exiv2::Slice<std::vector<int>> slice(testVec, 0, 5);
  for (size_t i = 0; i < slice.size(); ++i) {
    slice.at(i) = static_cast<int>(i * 100);
  }
  EXPECT_EQ(testVec[0], 0);
  EXPECT_EQ(testVec[1], 100);
  EXPECT_EQ(testVec[2], 200);
  EXPECT_EQ(testVec[3], 300);
  EXPECT_EQ(testVec[4], 400);
  // Elements beyond the slice should be unchanged
  EXPECT_EQ(testVec[5], 60);
}

TEST_F(SliceTest_5, ConstSliceFromMutableVector_5) {
  // Creating a const slice from a mutable vector
  const auto& cref = testVec;
  Exiv2::Slice<const std::vector<int>> cslice(cref, 0, 5);
  EXPECT_EQ(cslice.at(0), 10);
  EXPECT_EQ(cslice.size(), 5u);
}

// ==================== Iterator modification through mutable slice ====================

TEST_F(SliceTest_5, ModifyThroughIterator_5) {
  Exiv2::Slice<std::vector<int>> slice(testVec, 2, 5);
  for (auto it = slice.begin(); it != slice.end(); ++it) {
    *it = 0;
  }
  EXPECT_EQ(testVec[2], 0);
  EXPECT_EQ(testVec[3], 0);
  EXPECT_EQ(testVec[4], 0);
  // Untouched elements
  EXPECT_EQ(testVec[0], 10);
  EXPECT_EQ(testVec[1], 20);
  EXPECT_EQ(testVec[5], 60);
}

// ==================== SubSlice chaining ====================

TEST_F(SliceTest_5, SubSliceOfSubSlice_5) {
  Exiv2::Slice<std::vector<int>> slice(testVec, 0, 10);
  auto sub1 = slice.subSlice(2, 8);  // {30, 40, 50, 60, 70, 80}
  auto sub2 = sub1.subSlice(1, 4);   // {40, 50, 60}
  EXPECT_EQ(sub2.size(), 3u);
  EXPECT_EQ(sub2.at(0), 40);
  EXPECT_EQ(sub2.at(1), 50);
  EXPECT_EQ(sub2.at(2), 60);
}

// ==================== Construction edge cases ====================

TEST_F(SliceTest_5, ConstructSliceAtVectorBoundary_5) {
  Exiv2::Slice<std::vector<int>> slice(testVec, 9, 10);
  EXPECT_EQ(slice.size(), 1u);
  EXPECT_EQ(slice.at(0), 100);
}

TEST_F(SliceTest_5, ConstructSliceBeginEqualsEnd_5) {
  Exiv2::Slice<std::vector<int>> slice(testVec, 0, 0);
  EXPECT_EQ(slice.size(), 0u);
  EXPECT_THROW(slice.at(0), std::out_of_range);
}

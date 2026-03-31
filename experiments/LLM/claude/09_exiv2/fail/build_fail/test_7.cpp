#include <gtest/gtest.h>
#include <vector>
#include <string>

// Include the slice header
#include "exiv2/slice.hpp"

// Test fixture for MutableSlice tests using vector
class MutableSliceTest_7 : public ::testing::Test {
 protected:
  void SetUp() override {
    vec_ = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
  }

  std::vector<int> vec_;
};

// Test that at() returns the correct element for valid indices
TEST_F(MutableSliceTest_7, AtReturnsCorrectElement_7) {
  auto slice = Exiv2::slice(vec_, 0, vec_.size());
  EXPECT_EQ(slice.at(0), 10);
  EXPECT_EQ(slice.at(1), 20);
  EXPECT_EQ(slice.at(9), 100);
}

// Test that at() returns a mutable reference that can modify the underlying data
TEST_F(MutableSliceTest_7, AtReturnsMutableReference_7) {
  auto slice = Exiv2::slice(vec_, 0, vec_.size());
  slice.at(0) = 999;
  EXPECT_EQ(vec_[0], 999);
  EXPECT_EQ(slice.at(0), 999);
}

// Test that at() with a subslice returns the correct element relative to the subslice
TEST_F(MutableSliceTest_7, AtWithSubsliceOffset_7) {
  auto slice = Exiv2::slice(vec_, 2, 7);
  // slice represents elements {30, 40, 50, 60, 70}
  EXPECT_EQ(slice.at(0), 30);
  EXPECT_EQ(slice.at(4), 70);
}

// Test that at() throws on out-of-range index
TEST_F(MutableSliceTest_7, AtThrowsOnOutOfRange_7) {
  auto slice = Exiv2::slice(vec_, 0, 5);
  EXPECT_THROW(slice.at(5), std::out_of_range);
  EXPECT_THROW(slice.at(100), std::out_of_range);
}

// Test that at() throws on out-of-range for subslice
TEST_F(MutableSliceTest_7, AtThrowsOnOutOfRangeSubslice_7) {
  auto slice = Exiv2::slice(vec_, 3, 6);
  // Valid indices: 0, 1, 2
  EXPECT_NO_THROW(slice.at(0));
  EXPECT_NO_THROW(slice.at(2));
  EXPECT_THROW(slice.at(3), std::out_of_range);
}

// Test slice of size 1
TEST_F(MutableSliceTest_7, SliceOfSizeOne_7) {
  auto slice = Exiv2::slice(vec_, 5, 6);
  EXPECT_EQ(slice.at(0), 60);
  EXPECT_THROW(slice.at(1), std::out_of_range);
}

// Test modification through subslice reflects in original vector
TEST_F(MutableSliceTest_7, SubsliceModificationReflectsInOriginal_7) {
  auto slice = Exiv2::slice(vec_, 2, 8);
  slice.at(0) = 333;
  EXPECT_EQ(vec_[2], 333);
}

// Test that creating a slice with invalid range throws
TEST_F(MutableSliceTest_7, InvalidRangeThrows_7) {
  EXPECT_THROW(Exiv2::slice(vec_, 5, 3), std::out_of_range);
}

// Test that creating a slice exceeding container size throws
TEST_F(MutableSliceTest_7, SliceExceedingContainerSizeThrows_7) {
  EXPECT_THROW(Exiv2::slice(vec_, 0, vec_.size() + 1), std::out_of_range);
}

// Test empty slice (begin == end)
TEST_F(MutableSliceTest_7, EmptySliceThrowsOnAccess_7) {
  auto slice = Exiv2::slice(vec_, 3, 3);
  EXPECT_THROW(slice.at(0), std::out_of_range);
}

// Test size of slice
TEST_F(MutableSliceTest_7, SliceSizeIsCorrect_7) {
  auto slice = Exiv2::slice(vec_, 2, 7);
  EXPECT_EQ(slice.size(), 5u);
}

// Test subSlice creation and access
TEST_F(MutableSliceTest_7, SubSliceCreationAndAccess_7) {
  auto slice = Exiv2::slice(vec_, 1, 9);
  auto sub = slice.subSlice(2, 5);
  // Original indices: 1+2=3 to 1+5=6 -> {40, 50, 60}
  EXPECT_EQ(sub.at(0), 40);
  EXPECT_EQ(sub.at(1), 50);
  EXPECT_EQ(sub.at(2), 60);
  EXPECT_THROW(sub.at(3), std::out_of_range);
}

// Test subSlice with invalid range throws
TEST_F(MutableSliceTest_7, SubSliceInvalidRangeThrows_7) {
  auto slice = Exiv2::slice(vec_, 0, 10);
  EXPECT_THROW(slice.subSlice(5, 3), std::out_of_range);
}

// Test subSlice exceeding parent slice size throws
TEST_F(MutableSliceTest_7, SubSliceExceedingParentThrows_7) {
  auto slice = Exiv2::slice(vec_, 0, 5);
  EXPECT_THROW(slice.subSlice(0, 6), std::out_of_range);
}

// Test begin() and end() iterators
TEST_F(MutableSliceTest_7, BeginEndIterators_7) {
  auto slice = Exiv2::slice(vec_, 2, 5);
  auto it = slice.begin();
  EXPECT_EQ(*it, 30);
  ++it;
  EXPECT_EQ(*it, 40);
  ++it;
  EXPECT_EQ(*it, 50);
  ++it;
  EXPECT_EQ(it, slice.end());
}

// Test that iterators allow modification
TEST_F(MutableSliceTest_7, IteratorsAllowModification_7) {
  auto slice = Exiv2::slice(vec_, 0, 5);
  for (auto it = slice.begin(); it != slice.end(); ++it) {
    *it = 0;
  }
  for (size_t i = 0; i < 5; ++i) {
    EXPECT_EQ(vec_[i], 0);
  }
}

// Test with different data type (unsigned char / byte)
TEST(MutableSliceByteTest_7, ByteVectorSlice_7) {
  std::vector<uint8_t> data = {0x00, 0x01, 0x02, 0xFF, 0xFE};
  auto slice = Exiv2::slice(data, 1, 4);
  EXPECT_EQ(slice.at(0), 0x01);
  EXPECT_EQ(slice.at(2), 0xFF);
  slice.at(1) = 0xAB;
  EXPECT_EQ(data[2], 0xAB);
}

// Test that at() with maximum valid index works
TEST_F(MutableSliceTest_7, AtMaxValidIndex_7) {
  auto slice = Exiv2::slice(vec_, 0, vec_.size());
  EXPECT_NO_THROW(slice.at(vec_.size() - 1));
  EXPECT_THROW(slice.at(vec_.size()), std::out_of_range);
}

// Test that slice of full container matches original
TEST_F(MutableSliceTest_7, FullContainerSlice_7) {
  auto slice = Exiv2::slice(vec_, 0, vec_.size());
  for (size_t i = 0; i < vec_.size(); ++i) {
    EXPECT_EQ(slice.at(i), vec_[i]);
  }
}

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <exiv2/slice.hpp>
#include <vector>
#include <array>
#include <stdexcept>

namespace {

class MutableSliceBaseTest_10 : public ::testing::Test {
 protected:
  void SetUp() override {
    vec_ = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  }

  std::vector<int> vec_;
};

// Test that creating a mutable slice from a vector works for normal range
TEST_F(MutableSliceBaseTest_10, CreateSliceFromVector_10) {
  auto slice = Exiv2::Slice<std::vector<int>>(vec_, 0, vec_.size());
  EXPECT_EQ(slice.size(), vec_.size());
}

// Test at() returns correct values for valid indices
TEST_F(MutableSliceBaseTest_10, AtReturnsCorrectValues_10) {
  auto slice = Exiv2::Slice<std::vector<int>>(vec_, 0, vec_.size());
  for (size_t i = 0; i < vec_.size(); ++i) {
    EXPECT_EQ(slice.at(i), static_cast<int>(i));
  }
}

// Test at() allows mutation of elements
TEST_F(MutableSliceBaseTest_10, AtAllowsMutation_10) {
  auto slice = Exiv2::Slice<std::vector<int>>(vec_, 0, vec_.size());
  slice.at(3) = 42;
  EXPECT_EQ(slice.at(3), 42);
  EXPECT_EQ(vec_[3], 42);
}

// Test at() throws on out-of-bounds access
TEST_F(MutableSliceBaseTest_10, AtThrowsOnOutOfBounds_10) {
  auto slice = Exiv2::Slice<std::vector<int>>(vec_, 0, vec_.size());
  EXPECT_THROW(slice.at(vec_.size()), std::out_of_range);
  EXPECT_THROW(slice.at(vec_.size() + 100), std::out_of_range);
}

// Test begin and end iterators allow iteration
TEST_F(MutableSliceBaseTest_10, BeginEndIteration_10) {
  auto slice = Exiv2::Slice<std::vector<int>>(vec_, 0, vec_.size());
  int expected = 0;
  for (auto it = slice.begin(); it != slice.end(); ++it) {
    EXPECT_EQ(*it, expected);
    ++expected;
  }
  EXPECT_EQ(expected, 10);
}

// Test begin/end iterators allow mutation
TEST_F(MutableSliceBaseTest_10, IteratorsMutable_10) {
  auto slice = Exiv2::Slice<std::vector<int>>(vec_, 0, vec_.size());
  for (auto it = slice.begin(); it != slice.end(); ++it) {
    *it = 99;
  }
  for (size_t i = 0; i < vec_.size(); ++i) {
    EXPECT_EQ(vec_[i], 99);
  }
}

// Test creating a slice with a sub-range of the vector
TEST_F(MutableSliceBaseTest_10, SubRangeSlice_10) {
  auto slice = Exiv2::Slice<std::vector<int>>(vec_, 2, 5);
  EXPECT_EQ(slice.size(), 3u);
  EXPECT_EQ(slice.at(0), 2);
  EXPECT_EQ(slice.at(1), 3);
  EXPECT_EQ(slice.at(2), 4);
}

// Test subSlice creates a correct sub-slice
TEST_F(MutableSliceBaseTest_10, SubSliceCreation_10) {
  auto slice = Exiv2::Slice<std::vector<int>>(vec_, 0, vec_.size());
  auto sub = slice.subSlice(2, 5);
  EXPECT_EQ(sub.size(), 3u);
  EXPECT_EQ(sub.at(0), 2);
  EXPECT_EQ(sub.at(1), 3);
  EXPECT_EQ(sub.at(2), 4);
}

// Test subSlice mutation reflects in original
TEST_F(MutableSliceBaseTest_10, SubSliceMutationReflectsInOriginal_10) {
  auto slice = Exiv2::Slice<std::vector<int>>(vec_, 0, vec_.size());
  auto sub = slice.subSlice(2, 5);
  sub.at(0) = 100;
  EXPECT_EQ(vec_[2], 100);
  EXPECT_EQ(slice.at(2), 100);
}

// Test subSlice with invalid range throws
TEST_F(MutableSliceBaseTest_10, SubSliceInvalidRangeThrows_10) {
  auto slice = Exiv2::Slice<std::vector<int>>(vec_, 0, vec_.size());
  EXPECT_THROW(slice.subSlice(5, 3), std::out_of_range);
}

// Test subSlice out of bounds throws
TEST_F(MutableSliceBaseTest_10, SubSliceOutOfBoundsThrows_10) {
  auto slice = Exiv2::Slice<std::vector<int>>(vec_, 0, vec_.size());
  EXPECT_THROW(slice.subSlice(0, vec_.size() + 1), std::out_of_range);
}

// Test to_const_base via creating const slice - empty slice
TEST_F(MutableSliceBaseTest_10, EmptySlice_10) {
  auto slice = Exiv2::Slice<std::vector<int>>(vec_, 3, 3);
  EXPECT_EQ(slice.size(), 0u);
  EXPECT_EQ(slice.begin(), slice.end());
}

// Test at() on empty slice throws
TEST_F(MutableSliceBaseTest_10, EmptySliceAtThrows_10) {
  auto slice = Exiv2::Slice<std::vector<int>>(vec_, 3, 3);
  EXPECT_THROW(slice.at(0), std::out_of_range);
}

// Test creating a slice with begin > end throws
TEST_F(MutableSliceBaseTest_10, InvalidRangeConstructionThrows_10) {
  EXPECT_THROW((Exiv2::Slice<std::vector<int>>(vec_, 5, 3)), std::out_of_range);
}

// Test creating a slice exceeding container size throws
TEST_F(MutableSliceBaseTest_10, ExceedingContainerSizeThrows_10) {
  EXPECT_THROW((Exiv2::Slice<std::vector<int>>(vec_, 0, vec_.size() + 1)), std::out_of_range);
}

// Test single element slice
TEST_F(MutableSliceBaseTest_10, SingleElementSlice_10) {
  auto slice = Exiv2::Slice<std::vector<int>>(vec_, 5, 6);
  EXPECT_EQ(slice.size(), 1u);
  EXPECT_EQ(slice.at(0), 5);
  slice.at(0) = 55;
  EXPECT_EQ(vec_[5], 55);
}

// Test subSlice of subSlice
TEST_F(MutableSliceBaseTest_10, NestedSubSlice_10) {
  auto slice = Exiv2::Slice<std::vector<int>>(vec_, 0, vec_.size());
  auto sub1 = slice.subSlice(2, 8);
  auto sub2 = sub1.subSlice(1, 4);
  EXPECT_EQ(sub2.size(), 3u);
  EXPECT_EQ(sub2.at(0), 3);
  EXPECT_EQ(sub2.at(1), 4);
  EXPECT_EQ(sub2.at(2), 5);
}

// Test boundary: slice spanning entire vector
TEST_F(MutableSliceBaseTest_10, FullVectorSliceBoundary_10) {
  auto slice = Exiv2::Slice<std::vector<int>>(vec_, 0, 10);
  EXPECT_EQ(slice.size(), 10u);
  EXPECT_EQ(slice.at(0), 0);
  EXPECT_EQ(slice.at(9), 9);
}

// Test at() at exact boundary index (last valid)
TEST_F(MutableSliceBaseTest_10, AtBoundaryLastValid_10) {
  auto slice = Exiv2::Slice<std::vector<int>>(vec_, 0, vec_.size());
  EXPECT_NO_THROW(slice.at(vec_.size() - 1));
  EXPECT_THROW(slice.at(vec_.size()), std::out_of_range);
}

// Test with byte data (uint8_t vector)
TEST(MutableSliceBaseByteTest_10, ByteVectorSlice_10) {
  std::vector<uint8_t> data = {0x00, 0x01, 0x02, 0x03, 0xFF};
  auto slice = Exiv2::Slice<std::vector<uint8_t>>(data, 1, 4);
  EXPECT_EQ(slice.size(), 3u);
  EXPECT_EQ(slice.at(0), 0x01);
  EXPECT_EQ(slice.at(2), 0x03);
  slice.at(1) = 0xAB;
  EXPECT_EQ(data[2], 0xAB);
}

// Test subSlice empty from subSlice
TEST_F(MutableSliceBaseTest_10, SubSliceEmptyRange_10) {
  auto slice = Exiv2::Slice<std::vector<int>>(vec_, 0, vec_.size());
  auto sub = slice.subSlice(5, 5);
  EXPECT_EQ(sub.size(), 0u);
}

}  // namespace

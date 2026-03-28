#include <gtest/gtest.h>
#include <vector>
#include <string>
#include "exiv2/slice.hpp"

// Test fixture for Slice tests with vectors
class SliceTest_17 : public ::testing::Test {
 protected:
  void SetUp() override {
    vec_ = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  }

  std::vector<int> vec_;
};

// Test basic construction of a Slice from a vector
TEST_F(SliceTest_17, ConstructFromVector_17) {
  ASSERT_NO_THROW(Exiv2::Slice<std::vector<int>> slice(vec_, 0, vec_.size()));
}

// Test element access through a slice
TEST_F(SliceTest_17, ElementAccess_17) {
  Exiv2::Slice<std::vector<int>> slice(vec_, 0, vec_.size());
  for (size_t i = 0; i < vec_.size(); ++i) {
    EXPECT_EQ(slice.at(i), static_cast<int>(i));
  }
}

// Test subSlice on a mutable slice returns correct elements
TEST_F(SliceTest_17, MutableSubSlice_17) {
  Exiv2::Slice<std::vector<int>> slice(vec_, 0, vec_.size());
  auto sub = slice.subSlice(2, 5);
  EXPECT_EQ(sub.size(), 3u);
  EXPECT_EQ(sub.at(0), 2);
  EXPECT_EQ(sub.at(1), 3);
  EXPECT_EQ(sub.at(2), 4);
}

// Test const subSlice from a mutable slice
TEST_F(SliceTest_17, ConstSubSliceFromMutable_17) {
  Exiv2::Slice<std::vector<int>> slice(vec_, 0, vec_.size());
  const auto& constSlice = slice;
  auto sub = constSlice.subSlice(3, 7);
  EXPECT_EQ(sub.size(), 4u);
  EXPECT_EQ(sub.at(0), 3);
  EXPECT_EQ(sub.at(1), 4);
  EXPECT_EQ(sub.at(2), 5);
  EXPECT_EQ(sub.at(3), 6);
}

// Test subSlice with begin == end yields empty slice
TEST_F(SliceTest_17, SubSliceEmptyRange_17) {
  Exiv2::Slice<std::vector<int>> slice(vec_, 0, vec_.size());
  auto sub = slice.subSlice(3, 3);
  EXPECT_EQ(sub.size(), 0u);
}

// Test subSlice at the very beginning
TEST_F(SliceTest_17, SubSliceFromBeginning_17) {
  Exiv2::Slice<std::vector<int>> slice(vec_, 0, vec_.size());
  auto sub = slice.subSlice(0, 3);
  EXPECT_EQ(sub.size(), 3u);
  EXPECT_EQ(sub.at(0), 0);
  EXPECT_EQ(sub.at(1), 1);
  EXPECT_EQ(sub.at(2), 2);
}

// Test subSlice at the very end
TEST_F(SliceTest_17, SubSliceToEnd_17) {
  Exiv2::Slice<std::vector<int>> slice(vec_, 0, vec_.size());
  auto sub = slice.subSlice(7, 10);
  EXPECT_EQ(sub.size(), 3u);
  EXPECT_EQ(sub.at(0), 7);
  EXPECT_EQ(sub.at(1), 8);
  EXPECT_EQ(sub.at(2), 9);
}

// Test subSlice covering entire range
TEST_F(SliceTest_17, SubSliceEntireRange_17) {
  Exiv2::Slice<std::vector<int>> slice(vec_, 0, vec_.size());
  auto sub = slice.subSlice(0, 10);
  EXPECT_EQ(sub.size(), 10u);
  for (size_t i = 0; i < 10; ++i) {
    EXPECT_EQ(sub.at(i), static_cast<int>(i));
  }
}

// Test that subSlice with begin > end throws
TEST_F(SliceTest_17, SubSliceBeginGreaterThanEndThrows_17) {
  Exiv2::Slice<std::vector<int>> slice(vec_, 0, vec_.size());
  EXPECT_THROW(slice.subSlice(5, 3), std::out_of_range);
}

// Test that subSlice with end > size throws
TEST_F(SliceTest_17, SubSliceEndExceedsSizeThrows_17) {
  Exiv2::Slice<std::vector<int>> slice(vec_, 0, vec_.size());
  EXPECT_THROW(slice.subSlice(0, 11), std::out_of_range);
}

// Test construction with begin > end throws
TEST_F(SliceTest_17, ConstructionBeginGreaterThanEndThrows_17) {
  EXPECT_THROW(Exiv2::Slice<std::vector<int>>(vec_, 5, 3), std::out_of_range);
}

// Test construction with end > container size throws
TEST_F(SliceTest_17, ConstructionEndExceedsContainerSizeThrows_17) {
  EXPECT_THROW(Exiv2::Slice<std::vector<int>>(vec_, 0, 11), std::out_of_range);
}

// Test subSlice of a subSlice (chained)
TEST_F(SliceTest_17, ChainedSubSlice_17) {
  Exiv2::Slice<std::vector<int>> slice(vec_, 0, vec_.size());
  auto sub1 = slice.subSlice(2, 8);
  auto sub2 = sub1.subSlice(1, 4);
  EXPECT_EQ(sub2.size(), 3u);
  EXPECT_EQ(sub2.at(0), 3);
  EXPECT_EQ(sub2.at(1), 4);
  EXPECT_EQ(sub2.at(2), 5);
}

// Test const subSlice of a const subSlice (chained)
TEST_F(SliceTest_17, ChainedConstSubSlice_17) {
  Exiv2::Slice<std::vector<int>> slice(vec_, 0, vec_.size());
  const auto& constSlice = slice;
  auto sub1 = constSlice.subSlice(1, 9);
  auto sub2 = sub1.subSlice(2, 5);
  EXPECT_EQ(sub2.size(), 3u);
  EXPECT_EQ(sub2.at(0), 3);
  EXPECT_EQ(sub2.at(1), 4);
  EXPECT_EQ(sub2.at(2), 5);
}

// Test slice size method
TEST_F(SliceTest_17, SliceSize_17) {
  Exiv2::Slice<std::vector<int>> slice(vec_, 2, 7);
  EXPECT_EQ(slice.size(), 5u);
}

// Test modification through mutable slice
TEST_F(SliceTest_17, MutableSliceModification_17) {
  Exiv2::Slice<std::vector<int>> slice(vec_, 0, vec_.size());
  slice.at(3) = 42;
  EXPECT_EQ(vec_[3], 42);
}

// Test modification through mutable subSlice
TEST_F(SliceTest_17, MutableSubSliceModification_17) {
  Exiv2::Slice<std::vector<int>> slice(vec_, 0, vec_.size());
  auto sub = slice.subSlice(2, 6);
  sub.at(1) = 99;
  EXPECT_EQ(vec_[3], 99);
}

// Test at() out of range throws
TEST_F(SliceTest_17, AtOutOfRangeThrows_17) {
  Exiv2::Slice<std::vector<int>> slice(vec_, 0, 5);
  EXPECT_THROW(slice.at(5), std::out_of_range);
}

// Pointer-based slice tests
class PtrSliceTest_17 : public ::testing::Test {
 protected:
  void SetUp() override {
    for (int i = 0; i < 10; ++i) {
      arr_[i] = i * 10;
    }
  }

  int arr_[10];
};

// Test construction from a mutable pointer
TEST_F(PtrSliceTest_17, ConstructFromMutablePtr_17) {
  ASSERT_NO_THROW(Exiv2::Slice<int*> slice(arr_, 0, 10));
}

// Test element access from pointer slice
TEST_F(PtrSliceTest_17, PtrSliceElementAccess_17) {
  Exiv2::Slice<int*> slice(arr_, 0, 10);
  for (size_t i = 0; i < 10; ++i) {
    EXPECT_EQ(slice.at(i), static_cast<int>(i * 10));
  }
}

// Test mutable subSlice from pointer slice
TEST_F(PtrSliceTest_17, PtrSliceMutableSubSlice_17) {
  Exiv2::Slice<int*> slice(arr_, 0, 10);
  auto sub = slice.subSlice(3, 7);
  EXPECT_EQ(sub.size(), 4u);
  EXPECT_EQ(sub.at(0), 30);
  EXPECT_EQ(sub.at(3), 60);
}

// Test const subSlice from pointer slice
TEST_F(PtrSliceTest_17, PtrSliceConstSubSlice_17) {
  Exiv2::Slice<int*> slice(arr_, 0, 10);
  const auto& constSlice = slice;
  auto sub = constSlice.subSlice(1, 4);
  EXPECT_EQ(sub.size(), 3u);
  EXPECT_EQ(sub.at(0), 10);
  EXPECT_EQ(sub.at(2), 30);
}

// Test construction from a const pointer
TEST_F(PtrSliceTest_17, ConstructFromConstPtr_17) {
  const int* cptr = arr_;
  ASSERT_NO_THROW(Exiv2::Slice<const int*> slice(cptr, 0, 10));
}

// Test const pointer slice element access
TEST_F(PtrSliceTest_17, ConstPtrSliceElementAccess_17) {
  const int* cptr = arr_;
  Exiv2::Slice<const int*> slice(cptr, 0, 10);
  EXPECT_EQ(slice.at(0), 0);
  EXPECT_EQ(slice.at(9), 90);
}

// Test const pointer slice subSlice
TEST_F(PtrSliceTest_17, ConstPtrSubSlice_17) {
  const int* cptr = arr_;
  Exiv2::Slice<const int*> slice(cptr, 0, 10);
  auto sub = slice.subSlice(2, 5);
  EXPECT_EQ(sub.size(), 3u);
  EXPECT_EQ(sub.at(0), 20);
  EXPECT_EQ(sub.at(1), 30);
  EXPECT_EQ(sub.at(2), 40);
}

// Test modification through mutable pointer slice
TEST_F(PtrSliceTest_17, MutablePtrSliceModification_17) {
  Exiv2::Slice<int*> slice(arr_, 0, 10);
  slice.at(5) = 555;
  EXPECT_EQ(arr_[5], 555);
}

// Test modification through mutable pointer subSlice
TEST_F(PtrSliceTest_17, MutablePtrSubSliceModification_17) {
  Exiv2::Slice<int*> slice(arr_, 0, 10);
  auto sub = slice.subSlice(3, 8);
  sub.at(2) = 777;
  EXPECT_EQ(arr_[5], 777);
}

// Test pointer slice with begin == end (empty)
TEST_F(PtrSliceTest_17, PtrSliceEmpty_17) {
  Exiv2::Slice<int*> slice(arr_, 5, 5);
  EXPECT_EQ(slice.size(), 0u);
}

// Test pointer slice subSlice out of range
TEST_F(PtrSliceTest_17, PtrSubSliceOutOfRange_17) {
  Exiv2::Slice<int*> slice(arr_, 0, 10);
  EXPECT_THROW(slice.subSlice(0, 11), std::out_of_range);
}

// Test that a slice created with an offset works correctly
TEST_F(SliceTest_17, SliceWithOffset_17) {
  Exiv2::Slice<std::vector<int>> slice(vec_, 3, 8);
  EXPECT_EQ(slice.size(), 5u);
  EXPECT_EQ(slice.at(0), 3);
  EXPECT_EQ(slice.at(4), 7);
}

// Test subSlice from an already-offset slice
TEST_F(SliceTest_17, SubSliceFromOffsetSlice_17) {
  Exiv2::Slice<std::vector<int>> slice(vec_, 3, 8);
  auto sub = slice.subSlice(1, 3);
  EXPECT_EQ(sub.size(), 2u);
  EXPECT_EQ(sub.at(0), 4);
  EXPECT_EQ(sub.at(1), 5);
}

// Test that subSlice on empty slice with 0,0 is valid
TEST_F(SliceTest_17, SubSliceOnEmptySlice_17) {
  Exiv2::Slice<std::vector<int>> slice(vec_, 5, 5);
  EXPECT_EQ(slice.size(), 0u);
  auto sub = slice.subSlice(0, 0);
  EXPECT_EQ(sub.size(), 0u);
}

// Test single element slice
TEST_F(SliceTest_17, SingleElementSlice_17) {
  Exiv2::Slice<std::vector<int>> slice(vec_, 4, 5);
  EXPECT_EQ(slice.size(), 1u);
  EXPECT_EQ(slice.at(0), 4);
}

// Test single element subSlice
TEST_F(SliceTest_17, SingleElementSubSlice_17) {
  Exiv2::Slice<std::vector<int>> slice(vec_, 0, 10);
  auto sub = slice.subSlice(7, 8);
  EXPECT_EQ(sub.size(), 1u);
  EXPECT_EQ(sub.at(0), 7);
}

#include <gtest/gtest.h>
#include <vector>
#include <string>
#include "exiv2/slice.hpp"

// Test fixture for Slice tests with vectors
class SliceTest_16 : public ::testing::Test {
 protected:
  void SetUp() override {
    vec_ = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    const_vec_ = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
  }

  std::vector<int> vec_;
  std::vector<int> const_vec_;
};

// ==================== Vector Slice Tests ====================

TEST_F(SliceTest_16, ConstructSliceFromVector_16) {
  Exiv2::Slice<std::vector<int>> slice(vec_, 0, vec_.size());
  EXPECT_EQ(slice.size(), vec_.size());
}

TEST_F(SliceTest_16, ConstructSliceFromVectorSubrange_16) {
  Exiv2::Slice<std::vector<int>> slice(vec_, 2, 5);
  EXPECT_EQ(slice.size(), 3u);
}

TEST_F(SliceTest_16, AccessElementsViaAt_16) {
  Exiv2::Slice<std::vector<int>> slice(vec_, 0, vec_.size());
  for (size_t i = 0; i < vec_.size(); ++i) {
    EXPECT_EQ(slice.at(i), vec_[i]);
  }
}

TEST_F(SliceTest_16, AccessElementsViaAtWithOffset_16) {
  Exiv2::Slice<std::vector<int>> slice(vec_, 3, 7);
  EXPECT_EQ(slice.at(0), 3);
  EXPECT_EQ(slice.at(1), 4);
  EXPECT_EQ(slice.at(2), 5);
  EXPECT_EQ(slice.at(3), 6);
}

TEST_F(SliceTest_16, AtThrowsOnOutOfBounds_16) {
  Exiv2::Slice<std::vector<int>> slice(vec_, 0, 5);
  EXPECT_THROW(slice.at(5), std::out_of_range);
  EXPECT_THROW(slice.at(100), std::out_of_range);
}

TEST_F(SliceTest_16, MutableSliceModifiesUnderlyingData_16) {
  Exiv2::Slice<std::vector<int>> slice(vec_, 2, 5);
  slice.at(0) = 99;
  EXPECT_EQ(vec_[2], 99);
}

TEST_F(SliceTest_16, EmptySlice_16) {
  Exiv2::Slice<std::vector<int>> slice(vec_, 3, 3);
  EXPECT_EQ(slice.size(), 0u);
}

TEST_F(SliceTest_16, ConstructWithBeginGreaterThanEndThrows_16) {
  EXPECT_THROW(Exiv2::Slice<std::vector<int>>(vec_, 5, 3), std::out_of_range);
}

TEST_F(SliceTest_16, ConstructWithEndBeyondContainerSizeThrows_16) {
  EXPECT_THROW(Exiv2::Slice<std::vector<int>>(vec_, 0, vec_.size() + 1), std::out_of_range);
}

// ==================== SubSlice Tests ====================

TEST_F(SliceTest_16, SubSliceFromMutableSlice_16) {
  Exiv2::Slice<std::vector<int>> slice(vec_, 0, 10);
  auto sub = slice.subSlice(2, 5);
  EXPECT_EQ(sub.size(), 3u);
  EXPECT_EQ(sub.at(0), 2);
  EXPECT_EQ(sub.at(1), 3);
  EXPECT_EQ(sub.at(2), 4);
}

TEST_F(SliceTest_16, SubSliceModifiesOriginalData_16) {
  Exiv2::Slice<std::vector<int>> slice(vec_, 0, 10);
  auto sub = slice.subSlice(2, 5);
  sub.at(0) = 42;
  EXPECT_EQ(vec_[2], 42);
}

TEST_F(SliceTest_16, SubSliceOfSubSlice_16) {
  Exiv2::Slice<std::vector<int>> slice(vec_, 1, 9);
  auto sub1 = slice.subSlice(1, 6);  // maps to vec_[2..7]
  auto sub2 = sub1.subSlice(1, 3);   // maps to vec_[3..5]
  EXPECT_EQ(sub2.size(), 2u);
  EXPECT_EQ(sub2.at(0), 3);
  EXPECT_EQ(sub2.at(1), 4);
}

TEST_F(SliceTest_16, SubSliceWithInvalidRangeThrows_16) {
  Exiv2::Slice<std::vector<int>> slice(vec_, 0, 10);
  EXPECT_THROW(slice.subSlice(5, 3), std::out_of_range);
}

TEST_F(SliceTest_16, SubSliceExceedingParentSizeThrows_16) {
  Exiv2::Slice<std::vector<int>> slice(vec_, 0, 5);
  EXPECT_THROW(slice.subSlice(0, 6), std::out_of_range);
}

TEST_F(SliceTest_16, SubSliceEmptyRange_16) {
  Exiv2::Slice<std::vector<int>> slice(vec_, 0, 10);
  auto sub = slice.subSlice(3, 3);
  EXPECT_EQ(sub.size(), 0u);
}

// ==================== Const SubSlice from Mutable Slice ====================

TEST_F(SliceTest_16, ConstSubSliceFromMutableSlice_16) {
  Exiv2::Slice<std::vector<int>> slice(vec_, 0, 10);
  // Get a const subslice
  Exiv2::Slice<const std::vector<int>> constSub = slice.subSlice(2, 5);
  EXPECT_EQ(constSub.size(), 3u);
  EXPECT_EQ(constSub.at(0), 2);
  EXPECT_EQ(constSub.at(1), 3);
  EXPECT_EQ(constSub.at(2), 4);
}

// ==================== Const Vector Slice Tests ====================

TEST_F(SliceTest_16, ConstVectorSlice_16) {
  const std::vector<int>& cref = const_vec_;
  Exiv2::Slice<const std::vector<int>> slice(cref, 0, cref.size());
  EXPECT_EQ(slice.size(), cref.size());
  for (size_t i = 0; i < cref.size(); ++i) {
    EXPECT_EQ(slice.at(i), cref[i]);
  }
}

TEST_F(SliceTest_16, ConstVectorSliceSubSlice_16) {
  const std::vector<int>& cref = const_vec_;
  Exiv2::Slice<const std::vector<int>> slice(cref, 2, 7);
  auto sub = slice.subSlice(1, 3);
  EXPECT_EQ(sub.size(), 2u);
  EXPECT_EQ(sub.at(0), 40);
  EXPECT_EQ(sub.at(1), 50);
}

// ==================== Pointer Slice Tests ====================

class PtrSliceTest_16 : public ::testing::Test {
 protected:
  void SetUp() override {
    for (int i = 0; i < 10; ++i) {
      data_[i] = i * 10;
    }
  }

  int data_[10];
};

TEST_F(PtrSliceTest_16, ConstructMutablePtrSlice_16) {
  Exiv2::Slice<int*> slice(data_, 0, 10);
  EXPECT_EQ(slice.size(), 10u);
  for (size_t i = 0; i < 10; ++i) {
    EXPECT_EQ(slice.at(i), static_cast<int>(i * 10));
  }
}

TEST_F(PtrSliceTest_16, MutablePtrSliceModifiesData_16) {
  Exiv2::Slice<int*> slice(data_, 2, 5);
  slice.at(0) = 999;
  EXPECT_EQ(data_[2], 999);
}

TEST_F(PtrSliceTest_16, ConstPtrSlice_16) {
  const int* cdata = data_;
  Exiv2::Slice<const int*> slice(cdata, 0, 10);
  EXPECT_EQ(slice.size(), 10u);
  for (size_t i = 0; i < 10; ++i) {
    EXPECT_EQ(slice.at(i), static_cast<int>(i * 10));
  }
}

TEST_F(PtrSliceTest_16, PtrSliceSubSlice_16) {
  Exiv2::Slice<int*> slice(data_, 0, 10);
  auto sub = slice.subSlice(3, 7);
  EXPECT_EQ(sub.size(), 4u);
  EXPECT_EQ(sub.at(0), 30);
  EXPECT_EQ(sub.at(1), 40);
  EXPECT_EQ(sub.at(2), 50);
  EXPECT_EQ(sub.at(3), 60);
}

TEST_F(PtrSliceTest_16, PtrSliceAtOutOfBoundsThrows_16) {
  Exiv2::Slice<int*> slice(data_, 0, 5);
  EXPECT_THROW(slice.at(5), std::out_of_range);
}

TEST_F(PtrSliceTest_16, PtrSliceSubSliceInvalidRangeThrows_16) {
  Exiv2::Slice<int*> slice(data_, 0, 10);
  EXPECT_THROW(slice.subSlice(7, 3), std::out_of_range);
}

TEST_F(PtrSliceTest_16, PtrSliceSubSliceBeyondSizeThrows_16) {
  Exiv2::Slice<int*> slice(data_, 0, 5);
  EXPECT_THROW(slice.subSlice(0, 6), std::out_of_range);
}

TEST_F(PtrSliceTest_16, ConstPtrSubSlice_16) {
  const int* cdata = data_;
  Exiv2::Slice<const int*> slice(cdata, 1, 8);
  auto sub = slice.subSlice(2, 5);
  EXPECT_EQ(sub.size(), 3u);
  EXPECT_EQ(sub.at(0), 30);
  EXPECT_EQ(sub.at(1), 40);
  EXPECT_EQ(sub.at(2), 50);
}

TEST_F(PtrSliceTest_16, MutablePtrSliceConstSubSlice_16) {
  Exiv2::Slice<int*> slice(data_, 0, 10);
  Exiv2::Slice<const int*> constSub = slice.subSlice(2, 5);
  EXPECT_EQ(constSub.size(), 3u);
  EXPECT_EQ(constSub.at(0), 20);
}

// ==================== Iterator Tests ====================

TEST_F(SliceTest_16, IteratorBeginEnd_16) {
  Exiv2::Slice<std::vector<int>> slice(vec_, 0, vec_.size());
  auto it = slice.begin();
  auto end = slice.end();
  int count = 0;
  for (; it != end; ++it) {
    EXPECT_EQ(*it, vec_[count]);
    ++count;
  }
  EXPECT_EQ(count, static_cast<int>(vec_.size()));
}

TEST_F(SliceTest_16, IteratorOnSubrange_16) {
  Exiv2::Slice<std::vector<int>> slice(vec_, 3, 7);
  std::vector<int> result(slice.begin(), slice.end());
  ASSERT_EQ(result.size(), 4u);
  EXPECT_EQ(result[0], 3);
  EXPECT_EQ(result[1], 4);
  EXPECT_EQ(result[2], 5);
  EXPECT_EQ(result[3], 6);
}

// ==================== Size Tests ====================

TEST_F(SliceTest_16, SizeReflectsRange_16) {
  Exiv2::Slice<std::vector<int>> slice1(vec_, 0, 10);
  EXPECT_EQ(slice1.size(), 10u);

  Exiv2::Slice<std::vector<int>> slice2(vec_, 0, 0);
  EXPECT_EQ(slice2.size(), 0u);

  Exiv2::Slice<std::vector<int>> slice3(vec_, 5, 5);
  EXPECT_EQ(slice3.size(), 0u);

  Exiv2::Slice<std::vector<int>> slice4(vec_, 2, 8);
  EXPECT_EQ(slice4.size(), 6u);
}

// ==================== Byte data tests ====================

class ByteSliceTest_16 : public ::testing::Test {
 protected:
  void SetUp() override {
    for (size_t i = 0; i < sizeof(data_); ++i) {
      data_[i] = static_cast<uint8_t>(i);
    }
  }

  uint8_t data_[256];
};

TEST_F(ByteSliceTest_16, BytePtrSlice_16) {
  Exiv2::Slice<uint8_t*> slice(data_, 0, 256);
  EXPECT_EQ(slice.size(), 256u);
  EXPECT_EQ(slice.at(0), 0);
  EXPECT_EQ(slice.at(255), 255);
}

TEST_F(ByteSliceTest_16, BytePtrSliceSubSlice_16) {
  Exiv2::Slice<uint8_t*> slice(data_, 100, 200);
  auto sub = slice.subSlice(10, 20);
  EXPECT_EQ(sub.size(), 10u);
  EXPECT_EQ(sub.at(0), 110);
  EXPECT_EQ(sub.at(9), 119);
}

// ==================== Edge case: single element ====================

TEST_F(SliceTest_16, SingleElementSlice_16) {
  Exiv2::Slice<std::vector<int>> slice(vec_, 5, 6);
  EXPECT_EQ(slice.size(), 1u);
  EXPECT_EQ(slice.at(0), 5);
  EXPECT_THROW(slice.at(1), std::out_of_range);
}

TEST_F(SliceTest_16, SingleElementSubSlice_16) {
  Exiv2::Slice<std::vector<int>> slice(vec_, 0, 10);
  auto sub = slice.subSlice(9, 10);
  EXPECT_EQ(sub.size(), 1u);
  EXPECT_EQ(sub.at(0), 9);
}

// ==================== Full range subslice ====================

TEST_F(SliceTest_16, FullRangeSubSlice_16) {
  Exiv2::Slice<std::vector<int>> slice(vec_, 2, 8);
  auto sub = slice.subSlice(0, slice.size());
  EXPECT_EQ(sub.size(), slice.size());
  for (size_t i = 0; i < sub.size(); ++i) {
    EXPECT_EQ(sub.at(i), slice.at(i));
  }
}

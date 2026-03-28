#include <gtest/gtest.h>
#include <vector>
#include <string>
#include <stdexcept>

#include "exiv2/slice.hpp"

// Test fixture for Slice tests with raw pointers
class SliceTest_19 : public ::testing::Test {
 protected:
  void SetUp() override {
    for (int i = 0; i < 10; ++i) {
      data_[i] = i * 10;
    }
    vec_ = {0, 10, 20, 30, 40, 50, 60, 70, 80, 90};
  }

  int data_[10];
  std::vector<int> vec_;
};

// ===================== Mutable Pointer Slice Tests =====================

TEST_F(SliceTest_19, MutablePtrSliceConstructionNormal_19) {
  ASSERT_NO_THROW(Exiv2::Slice<int*> slice(data_, 0, 10));
}

TEST_F(SliceTest_19, MutablePtrSliceAccessElements_19) {
  Exiv2::Slice<int*> slice(data_, 0, 10);
  for (size_t i = 0; i < 10; ++i) {
    EXPECT_EQ(slice.at(i), static_cast<int>(i * 10));
  }
}

TEST_F(SliceTest_19, MutablePtrSliceModifyElements_19) {
  Exiv2::Slice<int*> slice(data_, 0, 10);
  slice.at(3) = 999;
  EXPECT_EQ(data_[3], 999);
}

TEST_F(SliceTest_19, MutablePtrSliceSubSliceBeginEnd_19) {
  Exiv2::Slice<int*> slice(data_, 0, 10);
  Exiv2::Slice<int*> sub = slice.subSlice(2, 5);
  EXPECT_EQ(sub.size(), 3u);
  EXPECT_EQ(sub.at(0), 20);
  EXPECT_EQ(sub.at(1), 30);
  EXPECT_EQ(sub.at(2), 40);
}

TEST_F(SliceTest_19, MutablePtrSliceSubSliceModifiesOriginal_19) {
  Exiv2::Slice<int*> slice(data_, 0, 10);
  Exiv2::Slice<int*> sub = slice.subSlice(2, 5);
  sub.at(0) = 777;
  EXPECT_EQ(data_[2], 777);
  EXPECT_EQ(slice.at(2), 777);
}

TEST_F(SliceTest_19, MutablePtrSliceSubSliceEmptyRange_19) {
  Exiv2::Slice<int*> slice(data_, 0, 10);
  Exiv2::Slice<int*> sub = slice.subSlice(3, 3);
  EXPECT_EQ(sub.size(), 0u);
}

TEST_F(SliceTest_19, MutablePtrSliceSubSliceInvalidRangeThrows_19) {
  Exiv2::Slice<int*> slice(data_, 0, 10);
  EXPECT_THROW(slice.subSlice(5, 3), std::out_of_range);
}

TEST_F(SliceTest_19, MutablePtrSliceSubSliceOutOfBoundsThrows_19) {
  Exiv2::Slice<int*> slice(data_, 0, 10);
  EXPECT_THROW(slice.subSlice(0, 11), std::out_of_range);
}

TEST_F(SliceTest_19, MutablePtrSliceAccessOutOfBoundsThrows_19) {
  Exiv2::Slice<int*> slice(data_, 0, 5);
  EXPECT_THROW(slice.at(5), std::out_of_range);
}

TEST_F(SliceTest_19, MutablePtrSliceSize_19) {
  Exiv2::Slice<int*> slice(data_, 2, 7);
  EXPECT_EQ(slice.size(), 5u);
}

TEST_F(SliceTest_19, MutablePtrSliceConstructionBeginEqualsEnd_19) {
  Exiv2::Slice<int*> slice(data_, 5, 5);
  EXPECT_EQ(slice.size(), 0u);
}

TEST_F(SliceTest_19, MutablePtrSliceConstructionInvalidRangeThrows_19) {
  EXPECT_THROW(Exiv2::Slice<int*>(data_, 7, 3), std::out_of_range);
}

// ===================== Const Pointer Slice Tests =====================

TEST_F(SliceTest_19, ConstPtrSliceConstructionNormal_19) {
  const int* cdata = data_;
  ASSERT_NO_THROW(Exiv2::Slice<const int*> slice(cdata, 0, 10));
}

TEST_F(SliceTest_19, ConstPtrSliceAccessElements_19) {
  const int* cdata = data_;
  Exiv2::Slice<const int*> slice(cdata, 0, 10);
  for (size_t i = 0; i < 10; ++i) {
    EXPECT_EQ(slice.at(i), static_cast<int>(i * 10));
  }
}

TEST_F(SliceTest_19, ConstPtrSliceSubSlice_19) {
  const int* cdata = data_;
  Exiv2::Slice<const int*> slice(cdata, 0, 10);
  Exiv2::Slice<const int*> sub = slice.subSlice(1, 4);
  EXPECT_EQ(sub.size(), 3u);
  EXPECT_EQ(sub.at(0), 10);
  EXPECT_EQ(sub.at(1), 20);
  EXPECT_EQ(sub.at(2), 30);
}

TEST_F(SliceTest_19, ConstPtrSliceAccessOutOfBoundsThrows_19) {
  const int* cdata = data_;
  Exiv2::Slice<const int*> slice(cdata, 0, 5);
  EXPECT_THROW(slice.at(5), std::out_of_range);
}

TEST_F(SliceTest_19, ConstPtrSliceSubSliceInvalidRange_19) {
  const int* cdata = data_;
  Exiv2::Slice<const int*> slice(cdata, 0, 10);
  EXPECT_THROW(slice.subSlice(6, 2), std::out_of_range);
}

// ===================== Vector Slice Tests =====================

TEST_F(SliceTest_19, VectorSliceConstructionNormal_19) {
  ASSERT_NO_THROW(Exiv2::Slice<std::vector<int>> slice(vec_, 0, vec_.size()));
}

TEST_F(SliceTest_19, VectorSliceAccessElements_19) {
  Exiv2::Slice<std::vector<int>> slice(vec_, 0, vec_.size());
  for (size_t i = 0; i < vec_.size(); ++i) {
    EXPECT_EQ(slice.at(i), vec_[i]);
  }
}

TEST_F(SliceTest_19, VectorSliceModifyElements_19) {
  Exiv2::Slice<std::vector<int>> slice(vec_, 0, vec_.size());
  slice.at(0) = 123;
  EXPECT_EQ(vec_[0], 123);
}

TEST_F(SliceTest_19, VectorSliceSubSlice_19) {
  Exiv2::Slice<std::vector<int>> slice(vec_, 0, vec_.size());
  auto sub = slice.subSlice(3, 7);
  EXPECT_EQ(sub.size(), 4u);
  EXPECT_EQ(sub.at(0), 30);
  EXPECT_EQ(sub.at(3), 60);
}

TEST_F(SliceTest_19, VectorSliceSubSliceModifiesOriginal_19) {
  Exiv2::Slice<std::vector<int>> slice(vec_, 0, vec_.size());
  auto sub = slice.subSlice(3, 7);
  sub.at(0) = 555;
  EXPECT_EQ(vec_[3], 555);
}

TEST_F(SliceTest_19, VectorSliceSize_19) {
  Exiv2::Slice<std::vector<int>> slice(vec_, 2, 8);
  EXPECT_EQ(slice.size(), 6u);
}

TEST_F(SliceTest_19, VectorSliceOutOfBoundsAccessThrows_19) {
  Exiv2::Slice<std::vector<int>> slice(vec_, 0, 5);
  EXPECT_THROW(slice.at(5), std::out_of_range);
}

TEST_F(SliceTest_19, VectorSliceConstructionOutOfBoundsThrows_19) {
  EXPECT_THROW(Exiv2::Slice<std::vector<int>>(vec_, 0, 20), std::out_of_range);
}

TEST_F(SliceTest_19, VectorSliceConstructionInvalidRangeThrows_19) {
  EXPECT_THROW(Exiv2::Slice<std::vector<int>>(vec_, 8, 3), std::out_of_range);
}

TEST_F(SliceTest_19, VectorSliceSubSliceOutOfBoundsThrows_19) {
  Exiv2::Slice<std::vector<int>> slice(vec_, 0, 5);
  EXPECT_THROW(slice.subSlice(0, 6), std::out_of_range);
}

// ===================== Nested SubSlice Tests =====================

TEST_F(SliceTest_19, NestedSubSlice_19) {
  Exiv2::Slice<int*> slice(data_, 0, 10);
  auto sub1 = slice.subSlice(2, 8);  // elements: 20, 30, 40, 50, 60, 70
  auto sub2 = sub1.subSlice(1, 4);   // elements: 30, 40, 50
  EXPECT_EQ(sub2.size(), 3u);
  EXPECT_EQ(sub2.at(0), 30);
  EXPECT_EQ(sub2.at(1), 40);
  EXPECT_EQ(sub2.at(2), 50);
}

TEST_F(SliceTest_19, NestedSubSliceModifiesOriginal_19) {
  Exiv2::Slice<int*> slice(data_, 0, 10);
  auto sub1 = slice.subSlice(2, 8);
  auto sub2 = sub1.subSlice(1, 4);
  sub2.at(0) = 333;
  EXPECT_EQ(data_[3], 333);
}

// ===================== Boundary Tests =====================

TEST_F(SliceTest_19, SingleElementSlice_19) {
  Exiv2::Slice<int*> slice(data_, 4, 5);
  EXPECT_EQ(slice.size(), 1u);
  EXPECT_EQ(slice.at(0), 40);
}

TEST_F(SliceTest_19, FullRangeSlice_19) {
  Exiv2::Slice<int*> slice(data_, 0, 10);
  EXPECT_EQ(slice.size(), 10u);
}

TEST_F(SliceTest_19, SubSliceOfEntireRange_19) {
  Exiv2::Slice<int*> slice(data_, 0, 10);
  auto sub = slice.subSlice(0, 10);
  EXPECT_EQ(sub.size(), 10u);
  for (size_t i = 0; i < 10; ++i) {
    EXPECT_EQ(sub.at(i), slice.at(i));
  }
}

TEST_F(SliceTest_19, SubSliceAtBoundaryEnd_19) {
  Exiv2::Slice<int*> slice(data_, 0, 10);
  auto sub = slice.subSlice(9, 10);
  EXPECT_EQ(sub.size(), 1u);
  EXPECT_EQ(sub.at(0), 90);
}

// ===================== Const SubSlice from Mutable =====================

TEST_F(SliceTest_19, ConstSubSliceFromMutablePtrSlice_19) {
  Exiv2::Slice<int*> slice(data_, 0, 10);
  const auto& constSlice = slice;
  // Getting a const subSlice from const reference
  auto sub = constSlice.subSlice(2, 5);
  EXPECT_EQ(sub.size(), 3u);
  EXPECT_EQ(sub.at(0), 20);
}

// ===================== Different data types =====================

TEST_F(SliceTest_19, CharPtrSlice_19) {
  char buf[] = "Hello World";
  Exiv2::Slice<char*> slice(buf, 0, 11);
  EXPECT_EQ(slice.at(0), 'H');
  EXPECT_EQ(slice.at(5), ' ');
  EXPECT_EQ(slice.at(6), 'W');
  slice.at(0) = 'h';
  EXPECT_EQ(buf[0], 'h');
}

TEST_F(SliceTest_19, CharPtrSubSlice_19) {
  char buf[] = "Hello World";
  Exiv2::Slice<char*> slice(buf, 0, 11);
  auto sub = slice.subSlice(6, 11);
  EXPECT_EQ(sub.size(), 5u);
  EXPECT_EQ(sub.at(0), 'W');
  EXPECT_EQ(sub.at(4), 'd');
}

// ===================== Unsigned char (byte) Slice =====================

TEST_F(SliceTest_19, UnsignedCharPtrSlice_19) {
  unsigned char bytes[] = {0x00, 0xFF, 0x80, 0x7F, 0x01};
  Exiv2::Slice<unsigned char*> slice(bytes, 0, 5);
  EXPECT_EQ(slice.at(0), 0x00);
  EXPECT_EQ(slice.at(1), 0xFF);
  EXPECT_EQ(slice.at(2), 0x80);

  auto sub = slice.subSlice(1, 4);
  EXPECT_EQ(sub.size(), 3u);
  EXPECT_EQ(sub.at(0), 0xFF);
  sub.at(0) = 0xAA;
  EXPECT_EQ(bytes[1], 0xAA);
}

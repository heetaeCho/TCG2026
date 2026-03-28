#include <gtest/gtest.h>
#include <vector>
#include <array>
#include <string>
#include <stdexcept>

// Include the header under test
#include "exiv2/slice.hpp"

// ============================================================================
// Tests for makeSlice function and Slice class
// ============================================================================

class MakeSliceTest_21 : public ::testing::Test {
 protected:
  void SetUp() override {
    for (int i = 0; i < 10; ++i) {
      intArray[i] = i * 10;
    }
  }

  int intArray[10];
};

// --- Normal Operation Tests ---

TEST_F(MakeSliceTest_21, CreateSliceFromIntArray_21) {
  auto slice = Exiv2::makeSlice(intArray, 0, 10);
  EXPECT_EQ(slice.size(), 10u);
}

TEST_F(MakeSliceTest_21, AccessElementsViaSlice_21) {
  auto slice = Exiv2::makeSlice(intArray, 0, 10);
  for (size_t i = 0; i < 10; ++i) {
    EXPECT_EQ(slice.at(i), static_cast<int>(i * 10));
  }
}

TEST_F(MakeSliceTest_21, SliceWithOffset_21) {
  auto slice = Exiv2::makeSlice(intArray, 2, 5);
  EXPECT_EQ(slice.size(), 3u);
  EXPECT_EQ(slice.at(0), 20);
  EXPECT_EQ(slice.at(1), 30);
  EXPECT_EQ(slice.at(2), 40);
}

TEST_F(MakeSliceTest_21, ModifyThroughSlice_21) {
  auto slice = Exiv2::makeSlice(intArray, 0, 10);
  slice.at(3) = 999;
  EXPECT_EQ(intArray[3], 999);
}

TEST_F(MakeSliceTest_21, SliceSizeIsCorrect_21) {
  auto slice = Exiv2::makeSlice(intArray, 3, 7);
  EXPECT_EQ(slice.size(), 4u);
}

// --- Boundary Condition Tests ---

TEST_F(MakeSliceTest_21, EmptySlice_21) {
  auto slice = Exiv2::makeSlice(intArray, 5, 5);
  EXPECT_EQ(slice.size(), 0u);
}

TEST_F(MakeSliceTest_21, SingleElementSlice_21) {
  auto slice = Exiv2::makeSlice(intArray, 0, 1);
  EXPECT_EQ(slice.size(), 1u);
  EXPECT_EQ(slice.at(0), 0);
}

TEST_F(MakeSliceTest_21, SliceAtEnd_21) {
  auto slice = Exiv2::makeSlice(intArray, 9, 10);
  EXPECT_EQ(slice.size(), 1u);
  EXPECT_EQ(slice.at(0), 90);
}

TEST_F(MakeSliceTest_21, SliceFromBeginning_21) {
  auto slice = Exiv2::makeSlice(intArray, 0, 3);
  EXPECT_EQ(slice.size(), 3u);
  EXPECT_EQ(slice.at(0), 0);
  EXPECT_EQ(slice.at(1), 10);
  EXPECT_EQ(slice.at(2), 20);
}

// --- Error / Exception Tests ---

TEST_F(MakeSliceTest_21, BeginGreaterThanEndThrows_21) {
  EXPECT_THROW(Exiv2::makeSlice(intArray, 5, 3), std::out_of_range);
}

TEST_F(MakeSliceTest_21, AccessOutOfBoundsThrows_21) {
  auto slice = Exiv2::makeSlice(intArray, 0, 5);
  EXPECT_THROW(slice.at(5), std::out_of_range);
}

TEST_F(MakeSliceTest_21, AccessOutOfBoundsOnEmptySliceThrows_21) {
  auto slice = Exiv2::makeSlice(intArray, 3, 3);
  EXPECT_THROW(slice.at(0), std::out_of_range);
}

// --- Tests with different types ---

TEST_F(MakeSliceTest_21, SliceOfCharArray_21) {
  char charArray[] = "Hello World";
  auto slice = Exiv2::makeSlice(charArray, 0, 5);
  EXPECT_EQ(slice.size(), 5u);
  EXPECT_EQ(slice.at(0), 'H');
  EXPECT_EQ(slice.at(4), 'o');
}

TEST_F(MakeSliceTest_21, SliceOfDoubleArray_21) {
  double dblArray[] = {1.1, 2.2, 3.3, 4.4, 5.5};
  auto slice = Exiv2::makeSlice(dblArray, 1, 4);
  EXPECT_EQ(slice.size(), 3u);
  EXPECT_DOUBLE_EQ(slice.at(0), 2.2);
  EXPECT_DOUBLE_EQ(slice.at(1), 3.3);
  EXPECT_DOUBLE_EQ(slice.at(2), 4.4);
}

TEST_F(MakeSliceTest_21, ConstSliceFromConstArray_21) {
  const int constArray[] = {100, 200, 300, 400, 500};
  auto slice = Exiv2::makeSlice(constArray, 1, 4);
  EXPECT_EQ(slice.size(), 3u);
  EXPECT_EQ(slice.at(0), 200);
  EXPECT_EQ(slice.at(1), 300);
  EXPECT_EQ(slice.at(2), 400);
}

// --- Subslice Tests ---

TEST_F(MakeSliceTest_21, SubsliceFromSlice_21) {
  auto slice = Exiv2::makeSlice(intArray, 0, 10);
  auto subslice = slice.subSlice(2, 5);
  EXPECT_EQ(subslice.size(), 3u);
  EXPECT_EQ(subslice.at(0), 20);
  EXPECT_EQ(subslice.at(1), 30);
  EXPECT_EQ(subslice.at(2), 40);
}

TEST_F(MakeSliceTest_21, SubsliceEmptyFromSlice_21) {
  auto slice = Exiv2::makeSlice(intArray, 0, 10);
  auto subslice = slice.subSlice(5, 5);
  EXPECT_EQ(subslice.size(), 0u);
}

TEST_F(MakeSliceTest_21, SubsliceOutOfRangeThrows_21) {
  auto slice = Exiv2::makeSlice(intArray, 0, 5);
  EXPECT_THROW(slice.subSlice(0, 6), std::out_of_range);
}

TEST_F(MakeSliceTest_21, SubsliceBeginGreaterThanEndThrows_21) {
  auto slice = Exiv2::makeSlice(intArray, 0, 10);
  EXPECT_THROW(slice.subSlice(5, 3), std::out_of_range);
}

// --- Modification via subslice reflects in original ---

TEST_F(MakeSliceTest_21, ModifySubsliceReflectsInOriginal_21) {
  auto slice = Exiv2::makeSlice(intArray, 0, 10);
  auto subslice = slice.subSlice(2, 5);
  subslice.at(0) = 777;
  EXPECT_EQ(intArray[2], 777);
  EXPECT_EQ(slice.at(2), 777);
}

// --- Tests with unsigned char (byte-like data) ---

TEST_F(MakeSliceTest_21, SliceOfUnsignedChar_21) {
  unsigned char bytes[] = {0x00, 0xFF, 0xAB, 0xCD, 0xEF};
  auto slice = Exiv2::makeSlice(bytes, 1, 4);
  EXPECT_EQ(slice.size(), 3u);
  EXPECT_EQ(slice.at(0), 0xFF);
  EXPECT_EQ(slice.at(1), 0xAB);
  EXPECT_EQ(slice.at(2), 0xCD);
}

// --- Large negative index tests (size_t wrapping) ---

TEST_F(MakeSliceTest_21, AccessLargeIndexThrows_21) {
  auto slice = Exiv2::makeSlice(intArray, 0, 10);
  EXPECT_THROW(slice.at(100), std::out_of_range);
}

// --- Full array slice ---

TEST_F(MakeSliceTest_21, FullArraySlice_21) {
  auto slice = Exiv2::makeSlice(intArray, 0, 10);
  EXPECT_EQ(slice.size(), 10u);
  for (size_t i = 0; i < 10; ++i) {
    EXPECT_EQ(slice.at(i), static_cast<int>(i * 10));
  }
}

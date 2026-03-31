#include <gtest/gtest.h>
#include <vector>
#include <string>
#include <array>
#include <stdexcept>

// Include the header under test
#include "exiv2/slice.hpp"

// ============================================================================
// Tests for makeSlice and Slice functionality
// ============================================================================

// Test fixture for Slice tests with vectors
class SliceTest_20 : public ::testing::Test {
 protected:
  void SetUp() override {
    vec_int = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    vec_char = {'a', 'b', 'c', 'd', 'e'};
    vec_empty = {};
  }

  std::vector<int> vec_int;
  std::vector<char> vec_char;
  std::vector<int> vec_empty;
};

// --- Normal operation tests ---

TEST_F(SliceTest_20, MakeSliceFromVector_NormalRange_20) {
  auto slice = Exiv2::makeSlice(vec_int, 2, 5);
  EXPECT_EQ(slice.size(), 3u);
}

TEST_F(SliceTest_20, MakeSliceFromVector_AccessElements_20) {
  auto slice = Exiv2::makeSlice(vec_int, 2, 5);
  EXPECT_EQ(slice.at(0), 2);
  EXPECT_EQ(slice.at(1), 3);
  EXPECT_EQ(slice.at(2), 4);
}

TEST_F(SliceTest_20, MakeSliceFromVector_EntireRange_20) {
  auto slice = Exiv2::makeSlice(vec_int, 0, 10);
  EXPECT_EQ(slice.size(), 10u);
  for (size_t i = 0; i < 10; ++i) {
    EXPECT_EQ(slice.at(i), static_cast<int>(i));
  }
}

TEST_F(SliceTest_20, MakeSliceFromVector_SingleElement_20) {
  auto slice = Exiv2::makeSlice(vec_int, 3, 4);
  EXPECT_EQ(slice.size(), 1u);
  EXPECT_EQ(slice.at(0), 3);
}

TEST_F(SliceTest_20, MakeSliceFromCharVector_20) {
  auto slice = Exiv2::makeSlice(vec_char, 1, 4);
  EXPECT_EQ(slice.size(), 3u);
  EXPECT_EQ(slice.at(0), 'b');
  EXPECT_EQ(slice.at(1), 'c');
  EXPECT_EQ(slice.at(2), 'd');
}

// --- Boundary condition tests ---

TEST_F(SliceTest_20, MakeSliceFromVector_EmptySlice_BeginEqualsEnd_20) {
  auto slice = Exiv2::makeSlice(vec_int, 3, 3);
  EXPECT_EQ(slice.size(), 0u);
}

TEST_F(SliceTest_20, MakeSliceFromVector_EmptySlice_AtBeginning_20) {
  auto slice = Exiv2::makeSlice(vec_int, 0, 0);
  EXPECT_EQ(slice.size(), 0u);
}

TEST_F(SliceTest_20, MakeSliceFromVector_EmptySlice_AtEnd_20) {
  auto slice = Exiv2::makeSlice(vec_int, 10, 10);
  EXPECT_EQ(slice.size(), 0u);
}

TEST_F(SliceTest_20, MakeSliceFromVector_FirstElement_20) {
  auto slice = Exiv2::makeSlice(vec_int, 0, 1);
  EXPECT_EQ(slice.size(), 1u);
  EXPECT_EQ(slice.at(0), 0);
}

TEST_F(SliceTest_20, MakeSliceFromVector_LastElement_20) {
  auto slice = Exiv2::makeSlice(vec_int, 9, 10);
  EXPECT_EQ(slice.size(), 1u);
  EXPECT_EQ(slice.at(0), 9);
}

// --- Error / exceptional case tests ---

TEST_F(SliceTest_20, MakeSliceFromVector_BeginGreaterThanEnd_Throws_20) {
  EXPECT_THROW(Exiv2::makeSlice(vec_int, 5, 2), std::out_of_range);
}

TEST_F(SliceTest_20, MakeSliceFromVector_EndOutOfRange_Throws_20) {
  EXPECT_THROW(Exiv2::makeSlice(vec_int, 0, 11), std::out_of_range);
}

TEST_F(SliceTest_20, MakeSliceFromVector_BothOutOfRange_Throws_20) {
  EXPECT_THROW(Exiv2::makeSlice(vec_int, 11, 15), std::out_of_range);
}

TEST_F(SliceTest_20, MakeSliceFromEmptyVector_NonZeroRange_Throws_20) {
  EXPECT_THROW(Exiv2::makeSlice(vec_empty, 0, 1), std::out_of_range);
}

TEST_F(SliceTest_20, MakeSliceFromEmptyVector_ZeroRange_20) {
  auto slice = Exiv2::makeSlice(vec_empty, 0, 0);
  EXPECT_EQ(slice.size(), 0u);
}

TEST_F(SliceTest_20, SliceAccessOutOfBounds_Throws_20) {
  auto slice = Exiv2::makeSlice(vec_int, 2, 5);
  EXPECT_THROW(slice.at(3), std::out_of_range);
}

TEST_F(SliceTest_20, SliceAccessOutOfBounds_LargeIndex_Throws_20) {
  auto slice = Exiv2::makeSlice(vec_int, 2, 5);
  EXPECT_THROW(slice.at(100), std::out_of_range);
}

// --- Modification through slice ---

TEST_F(SliceTest_20, MakeSlice_ModifyThroughSlice_ReflectsInOriginal_20) {
  auto slice = Exiv2::makeSlice(vec_int, 2, 5);
  slice.at(0) = 42;
  EXPECT_EQ(vec_int[2], 42);
}

TEST_F(SliceTest_20, MakeSlice_ModifyOriginal_ReflectsInSlice_20) {
  auto slice = Exiv2::makeSlice(vec_int, 2, 5);
  vec_int[3] = 99;
  EXPECT_EQ(slice.at(1), 99);
}

// --- Const vector tests ---

TEST_F(SliceTest_20, MakeSliceFromConstVector_20) {
  const std::vector<int>& const_ref = vec_int;
  auto slice = Exiv2::makeSlice(const_ref, 1, 4);
  EXPECT_EQ(slice.size(), 3u);
  EXPECT_EQ(slice.at(0), 1);
  EXPECT_EQ(slice.at(1), 2);
  EXPECT_EQ(slice.at(2), 3);
}

// --- Subslice tests ---

TEST_F(SliceTest_20, SubSlice_FromSlice_20) {
  auto slice = Exiv2::makeSlice(vec_int, 2, 8);
  // slice represents elements [2,3,4,5,6,7]
  auto subslice = slice.subSlice(1, 4);
  // subslice should represent elements [3,4,5]
  EXPECT_EQ(subslice.size(), 3u);
  EXPECT_EQ(subslice.at(0), 3);
  EXPECT_EQ(subslice.at(1), 4);
  EXPECT_EQ(subslice.at(2), 5);
}

TEST_F(SliceTest_20, SubSlice_EmptySubSlice_20) {
  auto slice = Exiv2::makeSlice(vec_int, 2, 8);
  auto subslice = slice.subSlice(3, 3);
  EXPECT_EQ(subslice.size(), 0u);
}

TEST_F(SliceTest_20, SubSlice_BeginGreaterThanEnd_Throws_20) {
  auto slice = Exiv2::makeSlice(vec_int, 2, 8);
  EXPECT_THROW(slice.subSlice(4, 2), std::out_of_range);
}

TEST_F(SliceTest_20, SubSlice_EndOutOfRange_Throws_20) {
  auto slice = Exiv2::makeSlice(vec_int, 2, 8);
  // slice size is 6, so end=7 is out of range
  EXPECT_THROW(slice.subSlice(0, 7), std::out_of_range);
}

// --- Iterator tests ---

TEST_F(SliceTest_20, SliceIterator_BeginEnd_20) {
  auto slice = Exiv2::makeSlice(vec_int, 3, 7);
  std::vector<int> result(slice.begin(), slice.end());
  ASSERT_EQ(result.size(), 4u);
  EXPECT_EQ(result[0], 3);
  EXPECT_EQ(result[1], 4);
  EXPECT_EQ(result[2], 5);
  EXPECT_EQ(result[3], 6);
}

TEST_F(SliceTest_20, SliceIterator_EmptySlice_20) {
  auto slice = Exiv2::makeSlice(vec_int, 5, 5);
  EXPECT_EQ(slice.begin(), slice.end());
}

// --- Test with different container: std::string ---

TEST(SliceStringTest_20, MakeSliceFromString_20) {
  std::string str = "Hello, World!";
  auto slice = Exiv2::makeSlice(str, 7, 12);
  EXPECT_EQ(slice.size(), 5u);
  EXPECT_EQ(slice.at(0), 'W');
  EXPECT_EQ(slice.at(1), 'o');
  EXPECT_EQ(slice.at(2), 'r');
  EXPECT_EQ(slice.at(3), 'l');
  EXPECT_EQ(slice.at(4), 'd');
}

TEST(SliceStringTest_20, MakeSliceFromString_ModifyThrough_20) {
  std::string str = "Hello";
  auto slice = Exiv2::makeSlice(str, 0, 5);
  slice.at(0) = 'J';
  EXPECT_EQ(str, "Jello");
}

TEST(SliceStringTest_20, MakeSliceFromString_OutOfRange_20) {
  std::string str = "Hi";
  EXPECT_THROW(Exiv2::makeSlice(str, 0, 3), std::out_of_range);
}

// --- Test with const container ---

TEST(SliceConstTest_20, MakeSliceFromConstString_20) {
  const std::string str = "Hello";
  auto slice = Exiv2::makeSlice(str, 1, 3);
  EXPECT_EQ(slice.size(), 2u);
  EXPECT_EQ(slice.at(0), 'e');
  EXPECT_EQ(slice.at(1), 'l');
}

// --- Size consistency ---

TEST_F(SliceTest_20, SliceSizeConsistency_20) {
  for (size_t begin = 0; begin <= vec_int.size(); ++begin) {
    for (size_t end = begin; end <= vec_int.size(); ++end) {
      auto slice = Exiv2::makeSlice(vec_int, begin, end);
      EXPECT_EQ(slice.size(), end - begin)
          << "begin=" << begin << " end=" << end;
    }
  }
}

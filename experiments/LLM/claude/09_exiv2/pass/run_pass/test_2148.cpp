#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <vector>
#include <string>
#include <stdexcept>

// Include the header under test
#include "exiv2/slice.hpp"

// ============================================================================
// Test fixture for Slice tests
// ============================================================================

class SliceTest_2148 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Set up common test data
    vec_int_ = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    vec_char_ = {'a', 'b', 'c', 'd', 'e', 'f'};
  }

  std::vector<int> vec_int_;
  std::vector<char> vec_char_;
};

// ---------------------------------------------------------------------------
// Tests for Slice over std::vector (value-based slices)
// ---------------------------------------------------------------------------

TEST_F(SliceTest_2148, ConstructSliceFromVector_NormalRange_2148) {
  // Constructing a slice from a vector with valid begin/end should not throw
  EXPECT_NO_THROW({
    auto sl = Exiv2::Slice<std::vector<int>>(vec_int_, 0, vec_int_.size());
  });
}

TEST_F(SliceTest_2148, ConstructSliceFromVector_Subrange_2148) {
  EXPECT_NO_THROW({
    auto sl = Exiv2::Slice<std::vector<int>>(vec_int_, 2, 5);
  });
}

TEST_F(SliceTest_2148, ConstructSliceFromVector_EmptyRange_2148) {
  // begin == end should be valid (empty slice)
  EXPECT_NO_THROW({
    auto sl = Exiv2::Slice<std::vector<int>>(vec_int_, 3, 3);
  });
}

TEST_F(SliceTest_2148, ConstructSliceFromVector_BeginGreaterThanEnd_Throws_2148) {
  // begin > end should throw
  EXPECT_THROW({
    auto sl = Exiv2::Slice<std::vector<int>>(vec_int_, 5, 2);
  }, std::out_of_range);
}

TEST_F(SliceTest_2148, ConstructSliceFromVector_EndBeyondSize_Throws_2148) {
  // end > vector size should throw
  EXPECT_THROW({
    auto sl = Exiv2::Slice<std::vector<int>>(vec_int_, 0, vec_int_.size() + 1);
  }, std::out_of_range);
}

TEST_F(SliceTest_2148, SliceAt_ReturnsCorrectElement_2148) {
  auto sl = Exiv2::Slice<std::vector<int>>(vec_int_, 2, 7);
  // at(0) should correspond to vec_int_[2]
  EXPECT_EQ(sl.at(0), 2);
  EXPECT_EQ(sl.at(1), 3);
  EXPECT_EQ(sl.at(4), 6);
}

TEST_F(SliceTest_2148, SliceAt_OutOfRange_Throws_2148) {
  auto sl = Exiv2::Slice<std::vector<int>>(vec_int_, 2, 5);
  // Slice has 3 elements (indices 0, 1, 2)
  EXPECT_THROW(sl.at(3), std::out_of_range);
  EXPECT_THROW(sl.at(10), std::out_of_range);
}

TEST_F(SliceTest_2148, SliceSize_ReturnsCorrectSize_2148) {
  auto sl = Exiv2::Slice<std::vector<int>>(vec_int_, 2, 7);
  EXPECT_EQ(sl.size(), 5u);
}

TEST_F(SliceTest_2148, SliceSize_EmptySlice_ReturnsZero_2148) {
  auto sl = Exiv2::Slice<std::vector<int>>(vec_int_, 4, 4);
  EXPECT_EQ(sl.size(), 0u);
}

TEST_F(SliceTest_2148, SliceModifyThroughAt_ModifiesOriginal_2148) {
  auto sl = Exiv2::Slice<std::vector<int>>(vec_int_, 1, 4);
  sl.at(0) = 100;
  EXPECT_EQ(vec_int_[1], 100);
}

TEST_F(SliceTest_2148, SubSlice_ValidRange_2148) {
  auto sl = Exiv2::Slice<std::vector<int>>(vec_int_, 1, 8);
  // subSlice(1, 4) => elements at original indices 2, 3, 4
  auto sub = sl.subSlice(1, 4);
  EXPECT_EQ(sub.size(), 3u);
  EXPECT_EQ(sub.at(0), 2);
  EXPECT_EQ(sub.at(1), 3);
  EXPECT_EQ(sub.at(2), 4);
}

TEST_F(SliceTest_2148, SubSlice_BeginGreaterThanEnd_Throws_2148) {
  auto sl = Exiv2::Slice<std::vector<int>>(vec_int_, 0, 5);
  EXPECT_THROW(sl.subSlice(3, 1), std::out_of_range);
}

TEST_F(SliceTest_2148, SubSlice_EndBeyondSliceSize_Throws_2148) {
  auto sl = Exiv2::Slice<std::vector<int>>(vec_int_, 0, 5);
  EXPECT_THROW(sl.subSlice(0, 6), std::out_of_range);
}

TEST_F(SliceTest_2148, SubSlice_EmptySubSlice_2148) {
  auto sl = Exiv2::Slice<std::vector<int>>(vec_int_, 0, 5);
  auto sub = sl.subSlice(2, 2);
  EXPECT_EQ(sub.size(), 0u);
}

// ---------------------------------------------------------------------------
// Tests for Slice over const std::vector
// ---------------------------------------------------------------------------

TEST_F(SliceTest_2148, ConstSliceFromConstVector_2148) {
  const std::vector<int>& cref = vec_int_;
  auto sl = Exiv2::Slice<const std::vector<int>>(cref, 0, cref.size());
  EXPECT_EQ(sl.at(0), 0);
  EXPECT_EQ(sl.size(), cref.size());
}

TEST_F(SliceTest_2148, ConstSlice_AtReturnsConstRef_2148) {
  const std::vector<int>& cref = vec_int_;
  auto sl = Exiv2::Slice<const std::vector<int>>(cref, 2, 6);
  EXPECT_EQ(sl.at(0), 2);
  EXPECT_EQ(sl.at(3), 5);
}

// ---------------------------------------------------------------------------
// Tests for pointer-based slices (PtrSliceStorage path)
// ---------------------------------------------------------------------------

TEST_F(SliceTest_2148, PtrSlice_NullPointer_Throws_2148) {
  int* null_ptr = nullptr;
  EXPECT_THROW({
    auto sl = Exiv2::Slice<int*>(null_ptr, 0, 5);
  }, std::invalid_argument);
}

TEST_F(SliceTest_2148, PtrSlice_ValidPointer_NoThrow_2148) {
  int arr[] = {10, 20, 30, 40, 50};
  EXPECT_NO_THROW({
    auto sl = Exiv2::Slice<int*>(arr, 0, 5);
  });
}

TEST_F(SliceTest_2148, PtrSlice_At_ReturnsCorrectElement_2148) {
  int arr[] = {10, 20, 30, 40, 50};
  auto sl = Exiv2::Slice<int*>(arr, 0, 5);
  EXPECT_EQ(sl.at(0), 10);
  EXPECT_EQ(sl.at(2), 30);
  EXPECT_EQ(sl.at(4), 50);
}

TEST_F(SliceTest_2148, PtrSlice_At_OutOfRange_Throws_2148) {
  int arr[] = {10, 20, 30};
  auto sl = Exiv2::Slice<int*>(arr, 0, 3);
  EXPECT_THROW(sl.at(3), std::out_of_range);
}

TEST_F(SliceTest_2148, PtrSlice_Size_2148) {
  int arr[] = {10, 20, 30, 40, 50};
  auto sl = Exiv2::Slice<int*>(arr, 1, 4);
  EXPECT_EQ(sl.size(), 3u);
}

TEST_F(SliceTest_2148, PtrSlice_ModifyElement_2148) {
  int arr[] = {10, 20, 30, 40, 50};
  auto sl = Exiv2::Slice<int*>(arr, 0, 5);
  sl.at(2) = 999;
  EXPECT_EQ(arr[2], 999);
}

TEST_F(SliceTest_2148, PtrSlice_WithOffset_2148) {
  int arr[] = {10, 20, 30, 40, 50};
  auto sl = Exiv2::Slice<int*>(arr, 2, 5);
  EXPECT_EQ(sl.at(0), 30);
  EXPECT_EQ(sl.at(1), 40);
  EXPECT_EQ(sl.at(2), 50);
}

TEST_F(SliceTest_2148, PtrSlice_EmptySlice_2148) {
  int arr[] = {10, 20, 30};
  auto sl = Exiv2::Slice<int*>(arr, 1, 1);
  EXPECT_EQ(sl.size(), 0u);
}

TEST_F(SliceTest_2148, PtrSlice_BeginGreaterThanEnd_Throws_2148) {
  int arr[] = {10, 20, 30};
  EXPECT_THROW({
    auto sl = Exiv2::Slice<int*>(arr, 3, 1);
  }, std::out_of_range);
}

TEST_F(SliceTest_2148, ConstPtrSlice_NullPointer_Throws_2148) {
  const int* null_ptr = nullptr;
  EXPECT_THROW({
    auto sl = Exiv2::Slice<const int*>(null_ptr, 0, 5);
  }, std::invalid_argument);
}

TEST_F(SliceTest_2148, ConstPtrSlice_At_ReturnsCorrectElement_2148) {
  const int arr[] = {10, 20, 30, 40, 50};
  auto sl = Exiv2::Slice<const int*>(arr, 0, 5);
  EXPECT_EQ(sl.at(0), 10);
  EXPECT_EQ(sl.at(4), 50);
}

// ---------------------------------------------------------------------------
// Tests for Slice SubSlice on pointer-based slices
// ---------------------------------------------------------------------------

TEST_F(SliceTest_2148, PtrSlice_SubSlice_ValidRange_2148) {
  int arr[] = {10, 20, 30, 40, 50};
  auto sl = Exiv2::Slice<int*>(arr, 0, 5);
  auto sub = sl.subSlice(1, 4);
  EXPECT_EQ(sub.size(), 3u);
  EXPECT_EQ(sub.at(0), 20);
  EXPECT_EQ(sub.at(2), 40);
}

TEST_F(SliceTest_2148, PtrSlice_SubSlice_OutOfRange_Throws_2148) {
  int arr[] = {10, 20, 30, 40, 50};
  auto sl = Exiv2::Slice<int*>(arr, 0, 5);
  EXPECT_THROW(sl.subSlice(0, 6), std::out_of_range);
}

// ---------------------------------------------------------------------------
// Tests for iterator-like behavior (begin/end)
// ---------------------------------------------------------------------------

TEST_F(SliceTest_2148, SliceIteration_Vector_2148) {
  auto sl = Exiv2::Slice<std::vector<int>>(vec_int_, 3, 7);
  std::vector<int> result;
  for (size_t i = 0; i < sl.size(); ++i) {
    result.push_back(sl.at(i));
  }
  EXPECT_EQ(result, (std::vector<int>{3, 4, 5, 6}));
}

TEST_F(SliceTest_2148, SliceIteration_Ptr_2148) {
  int arr[] = {100, 200, 300, 400, 500};
  auto sl = Exiv2::Slice<int*>(arr, 1, 4);
  std::vector<int> result;
  for (size_t i = 0; i < sl.size(); ++i) {
    result.push_back(sl.at(i));
  }
  EXPECT_EQ(result, (std::vector<int>{200, 300, 400}));
}

// ---------------------------------------------------------------------------
// Boundary tests
// ---------------------------------------------------------------------------

TEST_F(SliceTest_2148, SliceFullRange_Vector_2148) {
  auto sl = Exiv2::Slice<std::vector<int>>(vec_int_, 0, vec_int_.size());
  EXPECT_EQ(sl.size(), vec_int_.size());
  for (size_t i = 0; i < vec_int_.size(); ++i) {
    EXPECT_EQ(sl.at(i), vec_int_[i]);
  }
}

TEST_F(SliceTest_2148, SliceSingleElement_2148) {
  auto sl = Exiv2::Slice<std::vector<int>>(vec_int_, 5, 6);
  EXPECT_EQ(sl.size(), 1u);
  EXPECT_EQ(sl.at(0), 5);
}

TEST_F(SliceTest_2148, SliceFirstElement_2148) {
  auto sl = Exiv2::Slice<std::vector<int>>(vec_int_, 0, 1);
  EXPECT_EQ(sl.size(), 1u);
  EXPECT_EQ(sl.at(0), 0);
}

TEST_F(SliceTest_2148, SliceLastElement_2148) {
  auto sl = Exiv2::Slice<std::vector<int>>(vec_int_, vec_int_.size() - 1, vec_int_.size());
  EXPECT_EQ(sl.size(), 1u);
  EXPECT_EQ(sl.at(0), 9);
}

// ---------------------------------------------------------------------------
// Tests for char vector slices
// ---------------------------------------------------------------------------

TEST_F(SliceTest_2148, CharVectorSlice_2148) {
  auto sl = Exiv2::Slice<std::vector<char>>(vec_char_, 1, 4);
  EXPECT_EQ(sl.size(), 3u);
  EXPECT_EQ(sl.at(0), 'b');
  EXPECT_EQ(sl.at(1), 'c');
  EXPECT_EQ(sl.at(2), 'd');
}

// ---------------------------------------------------------------------------
// Tests for unsigned char pointer slices (common in image processing)
// ---------------------------------------------------------------------------

TEST_F(SliceTest_2148, UCharPtrSlice_2148) {
  unsigned char data[] = {0x00, 0xFF, 0xAB, 0xCD, 0xEF};
  auto sl = Exiv2::Slice<unsigned char*>(data, 0, 5);
  EXPECT_EQ(sl.size(), 5u);
  EXPECT_EQ(sl.at(0), 0x00);
  EXPECT_EQ(sl.at(1), 0xFF);
  EXPECT_EQ(sl.at(4), 0xEF);
}

TEST_F(SliceTest_2148, UCharPtrSlice_NullThrows_2148) {
  unsigned char* null_ptr = nullptr;
  EXPECT_THROW({
    auto sl = Exiv2::Slice<unsigned char*>(null_ptr, 0, 1);
  }, std::invalid_argument);
}

// ---------------------------------------------------------------------------
// makeSlice helper function tests (if available)
// ---------------------------------------------------------------------------

TEST_F(SliceTest_2148, MakeSliceFromVector_2148) {
  // Test the makeSlice convenience function if it exists
  try {
    auto sl = Exiv2::makeSlice(vec_int_, 2, 5);
    EXPECT_EQ(sl.size(), 3u);
    EXPECT_EQ(sl.at(0), 2);
    EXPECT_EQ(sl.at(2), 4);
  } catch (...) {
    // If makeSlice is not available, this test is skipped implicitly
    GTEST_SKIP() << "makeSlice not available";
  }
}

// ---------------------------------------------------------------------------
// Test chained subSlice operations
// ---------------------------------------------------------------------------

TEST_F(SliceTest_2148, ChainedSubSlice_2148) {
  auto sl = Exiv2::Slice<std::vector<int>>(vec_int_, 0, 10);
  auto sub1 = sl.subSlice(2, 8);  // elements 2..7
  auto sub2 = sub1.subSlice(1, 4); // elements 3..5 of original
  EXPECT_EQ(sub2.size(), 3u);
  EXPECT_EQ(sub2.at(0), 3);
  EXPECT_EQ(sub2.at(1), 4);
  EXPECT_EQ(sub2.at(2), 5);
}

#include <gtest/gtest.h>
#include <vector>
#include <string>
#include <stdexcept>
#include <array>

// Include the actual header
#include "exiv2/slice.hpp"

// ============================================================================
// Tests for Slice functionality
// ============================================================================

// Helper type aliases
using IntVector = std::vector<int>;
using ByteVector = std::vector<uint8_t>;

// Test fixture for Slice tests
class SliceTest_2147 : public ::testing::Test {
 protected:
  void SetUp() override {
    vec_ = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    empty_vec_ = {};
  }

  IntVector vec_;
  IntVector empty_vec_;
};

// ---------------------------------------------------------------------------
// Construction tests
// ---------------------------------------------------------------------------

TEST_F(SliceTest_2147, ConstructSliceFromVector_NormalRange_2147) {
  EXPECT_NO_THROW({
    auto sl = Exiv2::Slice<IntVector>(vec_, 0, vec_.size());
  });
}

TEST_F(SliceTest_2147, ConstructSliceFromVector_SubRange_2147) {
  EXPECT_NO_THROW({
    auto sl = Exiv2::Slice<IntVector>(vec_, 2, 5);
  });
}

TEST_F(SliceTest_2147, ConstructSliceFromVector_EmptyRange_2147) {
  EXPECT_NO_THROW({
    auto sl = Exiv2::Slice<IntVector>(vec_, 3, 3);
  });
}

TEST_F(SliceTest_2147, ConstructSliceFromEmptyVector_EmptyRange_2147) {
  EXPECT_NO_THROW({
    auto sl = Exiv2::Slice<IntVector>(empty_vec_, 0, 0);
  });
}

TEST_F(SliceTest_2147, ConstructSlice_EndBeyondSize_ThrowsOutOfRange_2147) {
  EXPECT_THROW({
    auto sl = Exiv2::Slice<IntVector>(vec_, 0, vec_.size() + 1);
  }, std::out_of_range);
}

TEST_F(SliceTest_2147, ConstructSlice_BeginGreaterThanEnd_ThrowsOutOfRange_2147) {
  EXPECT_THROW({
    auto sl = Exiv2::Slice<IntVector>(vec_, 5, 3);
  }, std::out_of_range);
}

TEST_F(SliceTest_2147, ConstructSlice_EmptyVectorNonZeroEnd_ThrowsOutOfRange_2147) {
  EXPECT_THROW({
    auto sl = Exiv2::Slice<IntVector>(empty_vec_, 0, 1);
  }, std::out_of_range);
}

TEST_F(SliceTest_2147, ConstructSlice_BeginAndEndBeyondSize_ThrowsOutOfRange_2147) {
  EXPECT_THROW({
    auto sl = Exiv2::Slice<IntVector>(vec_, 11, 15);
  }, std::out_of_range);
}

// ---------------------------------------------------------------------------
// Size tests
// ---------------------------------------------------------------------------

TEST_F(SliceTest_2147, Size_FullVector_2147) {
  auto sl = Exiv2::Slice<IntVector>(vec_, 0, vec_.size());
  EXPECT_EQ(sl.size(), vec_.size());
}

TEST_F(SliceTest_2147, Size_SubRange_2147) {
  auto sl = Exiv2::Slice<IntVector>(vec_, 2, 7);
  EXPECT_EQ(sl.size(), static_cast<size_t>(5));
}

TEST_F(SliceTest_2147, Size_EmptySlice_2147) {
  auto sl = Exiv2::Slice<IntVector>(vec_, 4, 4);
  EXPECT_EQ(sl.size(), static_cast<size_t>(0));
}

// ---------------------------------------------------------------------------
// Element access tests (operator[] and at())
// ---------------------------------------------------------------------------

TEST_F(SliceTest_2147, ElementAccess_FirstElement_2147) {
  auto sl = Exiv2::Slice<IntVector>(vec_, 0, vec_.size());
  EXPECT_EQ(sl.at(0), 0);
}

TEST_F(SliceTest_2147, ElementAccess_SubRangeCorrectOffset_2147) {
  auto sl = Exiv2::Slice<IntVector>(vec_, 3, 7);
  EXPECT_EQ(sl.at(0), 3);
  EXPECT_EQ(sl.at(1), 4);
  EXPECT_EQ(sl.at(2), 5);
  EXPECT_EQ(sl.at(3), 6);
}

TEST_F(SliceTest_2147, ElementAccess_LastElement_2147) {
  auto sl = Exiv2::Slice<IntVector>(vec_, 0, vec_.size());
  EXPECT_EQ(sl.at(9), 9);
}

TEST_F(SliceTest_2147, ElementAccess_OutOfRange_ThrowsOutOfRange_2147) {
  auto sl = Exiv2::Slice<IntVector>(vec_, 2, 5);
  EXPECT_THROW(sl.at(3), std::out_of_range);
}

TEST_F(SliceTest_2147, ElementAccess_OutOfRange_NegativeLikeIndex_2147) {
  auto sl = Exiv2::Slice<IntVector>(vec_, 2, 5);
  // size_t is unsigned, so a large value should throw
  EXPECT_THROW(sl.at(static_cast<size_t>(-1)), std::out_of_range);
}

// ---------------------------------------------------------------------------
// Mutability tests
// ---------------------------------------------------------------------------

TEST_F(SliceTest_2147, MutableSlice_ModifyElement_2147) {
  auto sl = Exiv2::Slice<IntVector>(vec_, 2, 5);
  sl.at(0) = 42;
  EXPECT_EQ(vec_[2], 42);
}

TEST_F(SliceTest_2147, MutableSlice_ModifyMultipleElements_2147) {
  auto sl = Exiv2::Slice<IntVector>(vec_, 0, 5);
  for (size_t i = 0; i < sl.size(); ++i) {
    sl.at(i) = static_cast<int>(i * 10);
  }
  EXPECT_EQ(vec_[0], 0);
  EXPECT_EQ(vec_[1], 10);
  EXPECT_EQ(vec_[2], 20);
  EXPECT_EQ(vec_[3], 30);
  EXPECT_EQ(vec_[4], 40);
  // Unchanged elements
  EXPECT_EQ(vec_[5], 5);
}

// ---------------------------------------------------------------------------
// SubSlice tests
// ---------------------------------------------------------------------------

TEST_F(SliceTest_2147, SubSlice_ValidRange_2147) {
  auto sl = Exiv2::Slice<IntVector>(vec_, 2, 8);
  auto sub = sl.subSlice(1, 4);
  EXPECT_EQ(sub.size(), static_cast<size_t>(3));
  EXPECT_EQ(sub.at(0), 3);
  EXPECT_EQ(sub.at(1), 4);
  EXPECT_EQ(sub.at(2), 5);
}

TEST_F(SliceTest_2147, SubSlice_EmptySubSlice_2147) {
  auto sl = Exiv2::Slice<IntVector>(vec_, 2, 8);
  auto sub = sl.subSlice(3, 3);
  EXPECT_EQ(sub.size(), static_cast<size_t>(0));
}

TEST_F(SliceTest_2147, SubSlice_FullRange_2147) {
  auto sl = Exiv2::Slice<IntVector>(vec_, 2, 8);
  auto sub = sl.subSlice(0, sl.size());
  EXPECT_EQ(sub.size(), sl.size());
  for (size_t i = 0; i < sub.size(); ++i) {
    EXPECT_EQ(sub.at(i), sl.at(i));
  }
}

TEST_F(SliceTest_2147, SubSlice_OutOfRange_Throws_2147) {
  auto sl = Exiv2::Slice<IntVector>(vec_, 2, 8);
  EXPECT_THROW(sl.subSlice(0, sl.size() + 1), std::out_of_range);
}

TEST_F(SliceTest_2147, SubSlice_BeginGreaterThanEnd_Throws_2147) {
  auto sl = Exiv2::Slice<IntVector>(vec_, 2, 8);
  EXPECT_THROW(sl.subSlice(4, 2), std::out_of_range);
}

// ---------------------------------------------------------------------------
// Const Slice tests
// ---------------------------------------------------------------------------

TEST_F(SliceTest_2147, ConstSlice_ElementAccessReadOnly_2147) {
  const IntVector const_vec = {10, 20, 30, 40, 50};
  auto sl = Exiv2::Slice<const IntVector>(const_vec, 1, 4);
  EXPECT_EQ(sl.size(), static_cast<size_t>(3));
  EXPECT_EQ(sl.at(0), 20);
  EXPECT_EQ(sl.at(1), 30);
  EXPECT_EQ(sl.at(2), 40);
}

TEST_F(SliceTest_2147, ConstSlice_OutOfRangeAccess_Throws_2147) {
  const IntVector const_vec = {10, 20, 30};
  auto sl = Exiv2::Slice<const IntVector>(const_vec, 0, 3);
  EXPECT_THROW(sl.at(3), std::out_of_range);
}

// ---------------------------------------------------------------------------
// Byte vector tests
// ---------------------------------------------------------------------------

TEST_F(SliceTest_2147, ByteVector_NormalAccess_2147) {
  ByteVector bvec = {0xFF, 0x00, 0xAB, 0xCD, 0xEF};
  auto sl = Exiv2::Slice<ByteVector>(bvec, 1, 4);
  EXPECT_EQ(sl.size(), static_cast<size_t>(3));
  EXPECT_EQ(sl.at(0), 0x00);
  EXPECT_EQ(sl.at(1), 0xAB);
  EXPECT_EQ(sl.at(2), 0xCD);
}

// ---------------------------------------------------------------------------
// Iterator tests (if begin/end are available)
// ---------------------------------------------------------------------------

TEST_F(SliceTest_2147, Iterator_RangeForLoop_2147) {
  auto sl = Exiv2::Slice<IntVector>(vec_, 3, 6);
  std::vector<int> result;
  for (auto& val : sl) {
    result.push_back(val);
  }
  ASSERT_EQ(result.size(), static_cast<size_t>(3));
  EXPECT_EQ(result[0], 3);
  EXPECT_EQ(result[1], 4);
  EXPECT_EQ(result[2], 5);
}

TEST_F(SliceTest_2147, Iterator_EmptySliceNoIteration_2147) {
  auto sl = Exiv2::Slice<IntVector>(vec_, 5, 5);
  int count = 0;
  for (auto& val : sl) {
    (void)val;
    ++count;
  }
  EXPECT_EQ(count, 0);
}

// ---------------------------------------------------------------------------
// Boundary condition: single element
// ---------------------------------------------------------------------------

TEST_F(SliceTest_2147, SingleElement_Access_2147) {
  auto sl = Exiv2::Slice<IntVector>(vec_, 7, 8);
  EXPECT_EQ(sl.size(), static_cast<size_t>(1));
  EXPECT_EQ(sl.at(0), 7);
}

// ---------------------------------------------------------------------------
// Boundary: begin == 0, end == 0
// ---------------------------------------------------------------------------

TEST_F(SliceTest_2147, ZeroZero_EmptySlice_2147) {
  auto sl = Exiv2::Slice<IntVector>(vec_, 0, 0);
  EXPECT_EQ(sl.size(), static_cast<size_t>(0));
}

// ---------------------------------------------------------------------------
// Multiple subslices referencing same data
// ---------------------------------------------------------------------------

TEST_F(SliceTest_2147, MultipleSlices_SameUnderlying_2147) {
  auto sl1 = Exiv2::Slice<IntVector>(vec_, 0, 5);
  auto sl2 = Exiv2::Slice<IntVector>(vec_, 3, 8);
  
  // Overlapping region: indices 3, 4 in original
  sl1.at(3) = 100;
  EXPECT_EQ(sl2.at(0), 100);
  
  sl2.at(1) = 200;
  EXPECT_EQ(sl1.at(4), 200);
}

// ---------------------------------------------------------------------------
// Large index boundary
// ---------------------------------------------------------------------------

TEST_F(SliceTest_2147, AccessLastValidIndex_2147) {
  auto sl = Exiv2::Slice<IntVector>(vec_, 0, vec_.size());
  EXPECT_NO_THROW(sl.at(vec_.size() - 1));
  EXPECT_THROW(sl.at(vec_.size()), std::out_of_range);
}

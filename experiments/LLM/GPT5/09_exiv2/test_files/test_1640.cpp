// =================================================================================================
// TEST_ID: 1640
// File: test_tiff_finder_visit_binary_element_1640.cpp
// =================================================================================================

#include <gtest/gtest.h>

#include "tiffvisitor_int.hpp"  // Exiv2::Internal::TiffFinder
#include "tiffcomposite_int.hpp" // Exiv2::Internal::TiffBinaryElement (type for pointer)

namespace {

// NOTE:
// These tests treat Exiv2::Internal::TiffFinder as a black box.
// With only the provided interface and without assuming constructor availability for TiffBinaryElement,
// the observable, interface-level behavior we can safely assert is focused on null-handling and
// stability of result() across calls.

class TiffFinderTest_1640 : public ::testing::Test {
protected:
  using Finder = Exiv2::Internal::TiffFinder;

  // Chosen arbitrary values; tests do not assume matching logic.
  static constexpr uint16_t kTag = 0x1234;
  static constexpr Exiv2::Internal::IfdId kGroup = static_cast<Exiv2::Internal::IfdId>(0);

  Finder makeFinder() { return Finder(kTag, kGroup); }
};

TEST_F(TiffFinderTest_1640, ConstructorInitialResultIsNull_1640) {
  auto finder = makeFinder();
  EXPECT_EQ(nullptr, finder.result());
}

TEST_F(TiffFinderTest_1640, VisitBinaryElementWithNullDoesNotCrash_1640) {
  auto finder = makeFinder();

  // Boundary / robustness: nullptr input.
  EXPECT_NO_THROW(finder.visitBinaryElement(nullptr));
}

TEST_F(TiffFinderTest_1640, VisitBinaryElementWithNullDoesNotChangeResult_1640) {
  auto finder = makeFinder();
  ASSERT_EQ(nullptr, finder.result());

  finder.visitBinaryElement(nullptr);

  // Observable behavior through public API: result() remains unchanged (still nullptr).
  EXPECT_EQ(nullptr, finder.result());
}

TEST_F(TiffFinderTest_1640, MultipleNullVisitsAreIdempotent_1640) {
  auto finder = makeFinder();
  ASSERT_EQ(nullptr, finder.result());

  EXPECT_NO_THROW(finder.visitBinaryElement(nullptr));
  EXPECT_EQ(nullptr, finder.result());

  EXPECT_NO_THROW(finder.visitBinaryElement(nullptr));
  EXPECT_EQ(nullptr, finder.result());
}

}  // namespace
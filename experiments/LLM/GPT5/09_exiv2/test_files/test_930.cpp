// ============================================================================
// tests_canonmn_int_tagListAfMiAdj_930.cpp
// Unit tests for Exiv2::Internal::CanonMakerNote::tagListAfMiAdj()
// ============================================================================

#include <gtest/gtest.h>

#include "canonmn_int.hpp"

namespace {

// NOTE: The snippet provided exposes only:
//   static constexpr auto tagListAfMiAdj() { return tagInfoAfMiAdj_; }
// Since the actual TagInfo type/structure is not provided here, these tests
// only validate *observable* properties that do not depend on internal layout.

class CanonMakerNoteTagListAfMiAdjTest_930 : public ::testing::Test {};

TEST_F(CanonMakerNoteTagListAfMiAdjTest_930, ReturnsSamePointerOnMultipleCalls_930) {
  const auto p1 = Exiv2::Internal::CanonMakerNote::tagListAfMiAdj();
  const auto p2 = Exiv2::Internal::CanonMakerNote::tagListAfMiAdj();

  // For a tag list accessor backed by a static array, returning the same address
  // across calls is an observable and stable property.
  EXPECT_EQ(p1, p2);
}

TEST_F(CanonMakerNoteTagListAfMiAdjTest_930, ReturnedPointerIsNotNull_930) {
  const auto p = Exiv2::Internal::CanonMakerNote::tagListAfMiAdj();

  // A tag list accessor is expected to return a usable pointer.
  // This checks a basic boundary/validity condition without relying on internals.
  EXPECT_NE(p, nullptr);
}

TEST_F(CanonMakerNoteTagListAfMiAdjTest_930, CanTakeAddressAndCompareStability_930) {
  // Boundary-ish: ensure the returned value is a stable addressable entity.
  const auto p1 = Exiv2::Internal::CanonMakerNote::tagListAfMiAdj();
  const auto p2 = Exiv2::Internal::CanonMakerNote::tagListAfMiAdj();
  const auto p3 = Exiv2::Internal::CanonMakerNote::tagListAfMiAdj();

  EXPECT_EQ(p1, p2);
  EXPECT_EQ(p2, p3);
}

}  // namespace
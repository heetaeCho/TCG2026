// File: test_canonmn_int_taglistcs_909.cpp
// Unit tests for Exiv2::Internal::CanonMakerNote::tagListCs()
// TEST_ID: 909

#include <gtest/gtest.h>

#include "canonmn_int.hpp"  // Exiv2::Internal::CanonMakerNote

namespace {

// Fixture name must include TEST_ID per requirements.
class CanonMakerNoteTest_909 : public ::testing::Test {};

TEST_F(CanonMakerNoteTest_909, TagListCs_ReturnsStableValueAcrossCalls_909) {
  const auto first = Exiv2::Internal::CanonMakerNote::tagListCs();
  const auto second = Exiv2::Internal::CanonMakerNote::tagListCs();

  // Observable behavior: repeated calls should yield the same tag list handle/value.
  EXPECT_EQ(first, second);
}

TEST_F(CanonMakerNoteTest_909, TagListCs_ReturnIsNotNullWhenPointerLike_909) {
  const auto list = Exiv2::Internal::CanonMakerNote::tagListCs();

  // The public API returns "auto"; in Exiv2 this is typically pointer-like for tag lists.
  // If it is pointer-like, it should not be null.
  EXPECT_NE(list, nullptr);
}

TEST_F(CanonMakerNoteTest_909, TagListCs_IsUsableAsConstexpr_909) {
  // This validates the "static constexpr" contract in the interface without relying on internals.
  constexpr auto list = Exiv2::Internal::CanonMakerNote::tagListCs();

  // If pointer-like, it should be a valid constexpr value.
  static_assert(list != nullptr, "tagListCs() should yield a non-null constexpr value");
  (void)list;
}

}  // namespace
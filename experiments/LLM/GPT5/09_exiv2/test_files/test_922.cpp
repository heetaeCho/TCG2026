// =================================================================================================
// TEST_ID: 922
// File: test_canonmn_int_taglistfcd2_922.cpp
// =================================================================================================

#include <gtest/gtest.h>

#include <type_traits>
#include <utility>

#include "canonmn_int.hpp"

namespace {

using Exiv2::Internal::CanonMakerNote;

class CanonMakerNoteTest_922 : public ::testing::Test {};

TEST_F(CanonMakerNoteTest_922, TagListFcd2_ReturnTypeIsPointerLike_922) {
  // Black-box: only verify observable type properties from the public signature/return value.
  using RetT = decltype(CanonMakerNote::tagListFcd2());
  EXPECT_TRUE(std::is_pointer_v<RetT> || std::is_array_v<std::remove_reference_t<RetT>>)
      << "Expected tagListFcd2() to return a pointer-like (or array-like) type.";
}

TEST_F(CanonMakerNoteTest_922, TagListFcd2_ReturnsStableAddressAcrossCalls_922) {
  // Boundary/consistency check: repeated calls should refer to the same static tag list object.
  const auto p1 = CanonMakerNote::tagListFcd2();
  const auto p2 = CanonMakerNote::tagListFcd2();
  EXPECT_EQ(p1, p2);
}

TEST_F(CanonMakerNoteTest_922, TagListFcd2_CanBeUsedInConstexprContext_922) {
  // The interface advertises constexpr; verify it can be initialized as constexpr.
  constexpr auto p = CanonMakerNote::tagListFcd2();
  (void)p;

  // Also validate the resulting value can be compared / used without runtime side effects.
  EXPECT_EQ(p, CanonMakerNote::tagListFcd2());
}

TEST_F(CanonMakerNoteTest_922, TagListFcd2_NonNullWhenAvailable_922) {
  // Defensive: many Exiv2 tag lists are backed by a static array and should be non-null.
  // If upstream ever changes this to allow null, this test will catch it.
  const auto p = CanonMakerNote::tagListFcd2();
  ASSERT_NE(p, nullptr);
}

}  // namespace
// SPDX-License-Identifier: GPL-2.0-or-later
// Test file for Exiv2::Internal::CanonMakerNote::tagListLiOp()
// The TEST_ID is 933

#include <gtest/gtest.h>

#include <type_traits>

#include "canonmn_int.hpp"

namespace {

using Exiv2::Internal::CanonMakerNote;

class CanonMakerNoteTest_933 : public ::testing::Test {};

TEST_F(CanonMakerNoteTest_933, TagListLiOp_ReturnTypeIsNotVoid_933) {
  using RetT = decltype(CanonMakerNote::tagListLiOp());
  static_assert(!std::is_void_v<RetT>, "tagListLiOp() must not return void");
  SUCCEED();
}

TEST_F(CanonMakerNoteTest_933, TagListLiOp_ReturnsStableHandleAcrossCalls_933) {
  const auto a = CanonMakerNote::tagListLiOp();
  const auto b = CanonMakerNote::tagListLiOp();
  EXPECT_EQ(a, b);
}

TEST_F(CanonMakerNoteTest_933, TagListLiOp_ReturnIsNonNullIfPointer_933) {
  using RetT = decltype(CanonMakerNote::tagListLiOp());
  const auto v = CanonMakerNote::tagListLiOp();

  if constexpr (std::is_pointer_v<RetT>) {
    EXPECT_NE(v, nullptr);
  } else {
    // No additional observable guarantees for non-pointer return types.
    SUCCEED();
  }
}

TEST_F(CanonMakerNoteTest_933, TagListLiOp_CanBeUsedAsConstexpr_933) {
  // The interface advertises constexpr; this verifies it is usable in a constant-expression context.
  constexpr auto v = CanonMakerNote::tagListLiOp();
  (void)v;
  SUCCEED();
}

}  // namespace
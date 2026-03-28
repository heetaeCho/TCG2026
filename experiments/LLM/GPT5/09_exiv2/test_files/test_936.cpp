// SPDX-License-Identifier: GPL-2.0-or-later

#include <gtest/gtest.h>

#include <type_traits>

#include "canonmn_int.hpp"

namespace {

class CanonMakerNoteTest_936 : public ::testing::Test {};

static_assert(!std::is_void_v<decltype(Exiv2::Internal::CanonMakerNote::tagListMe())>,
              "tagListMe() must return a non-void type");

// Ensure tagListMe() is usable in a constant-expression context (as declared constexpr).
constexpr auto kCanonMeTagList_936 = Exiv2::Internal::CanonMakerNote::tagListMe();
static_assert(kCanonMeTagList_936 == Exiv2::Internal::CanonMakerNote::tagListMe(),
              "tagListMe() should be stable in constexpr evaluation");

TEST_F(CanonMakerNoteTest_936, TagListMe_IsCallable_936) {
  // Primary observable behavior: the function exists and can be called.
  (void)Exiv2::Internal::CanonMakerNote::tagListMe();
  SUCCEED();
}

TEST_F(CanonMakerNoteTest_936, TagListMe_ReturnTypeIsPointerLike_936) {
  // We don't assume what it points to, only that the returned object is pointer-like
  // (typical for tag list accessors).
  using RetT = decltype(Exiv2::Internal::CanonMakerNote::tagListMe());
  EXPECT_TRUE(std::is_pointer_v<RetT>);
}

TEST_F(CanonMakerNoteTest_936, TagListMe_ReturnValueIsStableAcrossCalls_936) {
  // Boundary/consistency check: repeated calls return the same value (no observable mutation).
  const auto p1 = Exiv2::Internal::CanonMakerNote::tagListMe();
  const auto p2 = Exiv2::Internal::CanonMakerNote::tagListMe();
  EXPECT_EQ(p1, p2);
}

TEST_F(CanonMakerNoteTest_936, TagListMe_ReturnValueIsNonNull_936) {
  // Basic sanity: tag list accessor should yield a usable pointer.
  const auto p = Exiv2::Internal::CanonMakerNote::tagListMe();
  EXPECT_NE(p, nullptr);
}

}  // namespace
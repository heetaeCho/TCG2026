// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_nikon3makernote_taglistii_423.cpp

#include <gtest/gtest.h>

#include "nikonmn_int.hpp"

namespace {

// Compile-time sanity: tagListIi() is constexpr-callable and returns a stable value type.
constexpr auto kIiTagListA_423 = Exiv2::Internal::Nikon3MakerNote::tagListIi();
constexpr auto kIiTagListB_423 = Exiv2::Internal::Nikon3MakerNote::tagListIi();
static_assert(kIiTagListA_423 == kIiTagListB_423,
              "Nikon3MakerNote::tagListIi() should be stable across calls in constexpr context");

class Nikon3MakerNoteTest_423 : public ::testing::Test {};

TEST_F(Nikon3MakerNoteTest_423, TagListIi_ReturnsSameValueAcrossCalls_423) {
  const auto a = Exiv2::Internal::Nikon3MakerNote::tagListIi();
  const auto b = Exiv2::Internal::Nikon3MakerNote::tagListIi();
  EXPECT_EQ(a, b);
}

TEST_F(Nikon3MakerNoteTest_423, TagListIi_IsNotNullWhenPointerLike_423) {
  // The interface returns "auto" (likely a pointer to a TagInfo array). We only assert
  // non-null when the returned type supports comparison with nullptr.
  const auto v = Exiv2::Internal::Nikon3MakerNote::tagListIi();

  if constexpr (requires { v == nullptr; }) {
    EXPECT_NE(v, nullptr);
  } else {
    SUCCEED() << "tagListIi() return type is not nullptr-comparable; non-null check skipped.";
  }
}

TEST_F(Nikon3MakerNoteTest_423, TagListIi_CanBeUsedAtRuntime_423) {
  // Minimal runtime usage: ensure it can be called without throwing/crashing.
  (void)Exiv2::Internal::Nikon3MakerNote::tagListIi();
  SUCCEED();
}

}  // namespace
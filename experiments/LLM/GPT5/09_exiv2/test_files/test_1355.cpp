// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_samsung2makernote_taglistpw_1355.cpp
//
// Unit tests for Exiv2::Internal::Samsung2MakerNote::tagListPw()
// Constraints: treat implementation as black box; test only observable interface behavior.

#include <gtest/gtest.h>

#include <type_traits>
#include <utility>

#include "samsungmn_int.hpp"

namespace {

using Exiv2::Internal::Samsung2MakerNote;

// Helper: obtain a comparable "data pointer" from whatever tagList* returns.
// This avoids assuming whether the return type is a pointer, array reference, std::array, etc.
template <typename T>
constexpr auto dataPtr(T&& v) {
  using U = std::remove_reference_t<T>;
  if constexpr (std::is_pointer_v<U>) {
    return v;
  } else if constexpr (std::is_array_v<U>) {
    return &v[0];
  } else {
    // For containers like std::array that have .data()
    return v.data();
  }
}

// Helper: checks whether a "data pointer" is non-null when that notion applies.
template <typename PtrT>
constexpr bool isNonNullDataPtr(PtrT p) {
  if constexpr (std::is_pointer_v<PtrT>) {
    return p != nullptr;
  } else {
    // If it's not a pointer, "null" doesn't apply (e.g., some iterators).
    return true;
  }
}

class Samsung2MakerNoteTest_1355 : public ::testing::Test {};

TEST_F(Samsung2MakerNoteTest_1355, TagListPw_IsCallable_1355) {
  // If this compiles and runs, the callable interface is present.
  auto list = Samsung2MakerNote::tagListPw();
  (void)list;
}

TEST_F(Samsung2MakerNoteTest_1355, TagListPw_DataPointerIsStableAcrossCalls_1355) {
  auto list1 = Samsung2MakerNote::tagListPw();
  auto list2 = Samsung2MakerNote::tagListPw();

  const auto p1 = dataPtr(list1);
  const auto p2 = dataPtr(list2);

  // Observable contract we can safely assert: repeated calls yield the same underlying storage.
  EXPECT_EQ(p1, p2);
}

TEST_F(Samsung2MakerNoteTest_1355, TagListPw_DataPointerIsNonNullWhenPointerLike_1355) {
  auto list = Samsung2MakerNote::tagListPw();
  const auto p = dataPtr(list);

  // If the return is pointer-like, it should not be null.
  // If it's not pointer-like (e.g., std::array ref), "null" doesn't apply and this passes by design.
  EXPECT_TRUE(isNonNullDataPtr(p));
}

// Compile-time checks: only about the public signature properties (no internal assumptions).
TEST_F(Samsung2MakerNoteTest_1355, TagListPw_CanBeUsedInConstantExpression_1355) {
  constexpr auto list = Samsung2MakerNote::tagListPw();
  (void)list;

  // Also ensure taking a stable "data pointer" is constexpr-capable if the type allows.
  constexpr auto p = dataPtr(list);
  (void)p;
}

TEST_F(Samsung2MakerNoteTest_1355, TagListAndTagListPw_AreBothCallable_1355) {
  // The header indicates both exist. We don't assume they differ or are equal.
  auto listDefault = Samsung2MakerNote::tagList();
  auto listPw = Samsung2MakerNote::tagListPw();

  (void)listDefault;
  (void)listPw;

  const auto pDefault = dataPtr(listDefault);
  const auto pPw = dataPtr(listPw);

  EXPECT_TRUE(isNonNullDataPtr(pDefault));
  EXPECT_TRUE(isNonNullDataPtr(pPw));
}

}  // namespace
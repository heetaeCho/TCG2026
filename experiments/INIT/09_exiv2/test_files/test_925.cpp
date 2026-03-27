// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_canonmn_int_tagListCbi_925.cpp

#include <gtest/gtest.h>

#include <type_traits>
#include <utility>

#include "canonmn_int.hpp"

namespace {

// Helper that extracts a comparable “base address” from whatever tagListCbi() returns.
// It supports:
//  - pointer types (returns the pointer itself)
//  - array references (returns &arr[0])
//  - other lvalue references that support operator[] (best-effort: &ref[0])
template <typename T>
constexpr const void* baseAddressOf(T&& v) {
  using R = std::remove_reference_t<T>;

  if constexpr (std::is_pointer_v<R>) {
    return static_cast<const void*>(v);
  } else if constexpr (std::is_array_v<R>) {
    return static_cast<const void*>(std::addressof(v[0]));
  } else if constexpr (std::is_lvalue_reference_v<T> && requires { v[0]; }) {
    return static_cast<const void*>(std::addressof(v[0]));
  } else {
    // Fallback: address of the object itself (still allows “stable identity” checks).
    return static_cast<const void*>(std::addressof(v));
  }
}

}  // namespace

namespace Exiv2::Internal {

class CanonMakerNoteTest_925 : public ::testing::Test {};

TEST_F(CanonMakerNoteTest_925, TagListCbi_IsCallable_925) {
  // Should compile and be callable.
  (void)CanonMakerNote::tagListCbi();
  SUCCEED();
}

TEST_F(CanonMakerNoteTest_925, TagListCbi_IsConstexprUsable_925) {
  // The interface declares this function constexpr; ensure it can be evaluated in a constant expression.
  constexpr auto v = CanonMakerNote::tagListCbi();
  (void)v;
  SUCCEED();
}

TEST_F(CanonMakerNoteTest_925, TagListCbi_AddressIsStableAcrossCalls_925) {
  // Black-box observable behavior: repeated calls should refer to the same underlying tag list object.
  // (This is consistent with returning a static tag info table.)
  const auto a = CanonMakerNote::tagListCbi();
  const auto b = CanonMakerNote::tagListCbi();

  const void* addrA = baseAddressOf(a);
  const void* addrB = baseAddressOf(b);

  EXPECT_EQ(addrA, addrB);
}

TEST_F(CanonMakerNoteTest_925, TagListCbi_IfPointerThenNotNull_925) {
  // Only assert non-null when the return type is a pointer (avoid guessing otherwise).
  auto v = CanonMakerNote::tagListCbi();
  using R = std::remove_reference_t<decltype(v)>;

  if constexpr (std::is_pointer_v<R>) {
    EXPECT_NE(v, nullptr);
  } else {
    SUCCEED();
  }
}

}  // namespace Exiv2::Internal
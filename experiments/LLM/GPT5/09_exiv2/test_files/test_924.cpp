// SPDX-License-Identifier: GPL-2.0-or-later
// The TEST_ID is 924
//
// Unit tests for Exiv2::Internal::CanonMakerNote::tagListAs()
// File: ./TestProjects/exiv2/src/canonmn_int.hpp

#include <gtest/gtest.h>

#include <type_traits>
#include <utility>

#include "canonmn_int.hpp"

namespace {

using Exiv2::Internal::CanonMakerNote;

template <typename T>
constexpr bool IsPointerLike() {
  return std::is_pointer_v<std::remove_reference_t<T>>;
}

template <typename T>
bool SameIdentityOrValue(T&& a, T&& b) {
  using U = std::remove_reference_t<T>;
  if constexpr (std::is_pointer_v<U>) {
    // If returned by value as a pointer, identity == pointer value.
    return a == b;
  } else {
    // If returned as a reference (e.g., array reference), compare object identity.
    return std::addressof(a) == std::addressof(b);
  }
}

}  // namespace

class CanonMakerNoteTagListAsTest_924 : public ::testing::Test {};

TEST_F(CanonMakerNoteTagListAsTest_924, CallableAndStableAcrossCalls_924) {
  // Just verify observable stability: repeated calls yield the same identity/value.
  decltype(auto) a = CanonMakerNote::tagListAs();
  decltype(auto) b = CanonMakerNote::tagListAs();

  EXPECT_TRUE(SameIdentityOrValue(a, b));
}

TEST_F(CanonMakerNoteTagListAsTest_924, UsableInConstexprContext_924) {
  // The interface says this is constexpr; ensure it can be used in a constant expression.
  constexpr auto v = CanonMakerNote::tagListAs();
  (void)v;

  SUCCEED();
}

TEST_F(CanonMakerNoteTagListAsTest_924, NotNullWhenPointer_924) {
  // If the returned type is a pointer, it's reasonable/observable to require non-null
  // (at least in a functioning codebase). If it's not a pointer, we skip this check.
  decltype(auto) v = CanonMakerNote::tagListAs();

  using Ret = decltype(v);
  if constexpr (IsPointerLike<Ret>()) {
    EXPECT_NE(v, nullptr);
  } else {
    GTEST_SKIP() << "tagListAs() does not return a pointer type; null-check not applicable.";
  }
}
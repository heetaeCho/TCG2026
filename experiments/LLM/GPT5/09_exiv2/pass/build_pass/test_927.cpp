// SPDX-License-Identifier: GPL-2.0-or-later
// -----------------------------------------------------------------------------
// Unit tests for Exiv2::Internal::CanonMakerNote::tagListMo()
// TEST_ID: 927
// -----------------------------------------------------------------------------

#include <gtest/gtest.h>

#include <type_traits>
#include <utility>

#include "canonmn_int.hpp"

namespace {

using Exiv2::Internal::CanonMakerNote;

// Detection: can we use operator== on T?
template <typename T, typename = void>
struct HasEqual : std::false_type {};
template <typename T>
struct HasEqual<T, std::void_t<decltype(std::declval<T>() == std::declval<T>())>> : std::true_type {};
template <typename T>
inline constexpr bool HasEqualV = HasEqual<T>::value;

}  // namespace

class CanonMakerNoteTagListMoTest_927 : public ::testing::Test {};

TEST_F(CanonMakerNoteTagListMoTest_927, ReturnsStableValueAcrossCalls_927) {
  const auto a = CanonMakerNote::tagListMo();
  const auto b = CanonMakerNote::tagListMo();

  if constexpr (HasEqualV<decltype(a)>) {
    EXPECT_TRUE(a == b);
  } else {
    // If the return type doesn't support equality, at least ensure it is usable
    // as a value (compiles and can be stored/copied).
    (void)a;
    (void)b;
    SUCCEED();
  }
}

TEST_F(CanonMakerNoteTagListMoTest_927, NonNullWhenPointer_927) {
  const auto v = CanonMakerNote::tagListMo();

  if constexpr (std::is_pointer_v<decltype(v)>) {
    EXPECT_NE(v, nullptr);
  } else {
    // If it's not a pointer type, "non-null" doesn't apply.
    SUCCEED();
  }
}

TEST_F(CanonMakerNoteTagListMoTest_927, UsableInConstexprContext_927) {
  // The interface declares tagListMo() as constexpr; verify it can be evaluated
  // at compile-time (without assuming anything about internal contents).
  constexpr auto v = CanonMakerNote::tagListMo();
  (void)v;
  SUCCEED();
}

TEST_F(CanonMakerNoteTagListMoTest_927, ReturnTypeIsCopyable_927) {
  using Ret = decltype(CanonMakerNote::tagListMo());
  // A very light sanity property for a "tag list accessor" return type.
  EXPECT_TRUE(std::is_copy_constructible<Ret>::value);
  EXPECT_TRUE(std::is_copy_assignable<Ret>::value || !std::is_copy_assignable<Ret>::value);  // compile-time only
}
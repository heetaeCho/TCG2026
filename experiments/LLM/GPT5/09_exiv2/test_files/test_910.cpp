// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_canonmn_int_tagListSi_910.cpp

#include <gtest/gtest.h>

#include <type_traits>
#include <utility>

#include "canonmn_int.hpp"

namespace {

using Exiv2::Internal::CanonMakerNote;

class CanonMakerNoteTagListSiTest_910 : public ::testing::Test {};

template <typename T>
constexpr const void* addr_of(T& obj) noexcept {
  return static_cast<const void*>(std::addressof(obj));
}

TEST_F(CanonMakerNoteTagListSiTest_910, ReturnsSameObjectAcrossCalls_910) {
  // Treat as a black box: only verify observable stability across calls.
  auto first = CanonMakerNote::tagListSi();
  auto second = CanonMakerNote::tagListSi();

  if constexpr (std::is_pointer_v<decltype(first)>) {
    EXPECT_EQ(first, second);
  } else {
    // For non-pointer return types (e.g., reference to an array), compare addresses.
    EXPECT_EQ(addr_of(first), addr_of(second));
  }
}

TEST_F(CanonMakerNoteTagListSiTest_910, ReturnsNonNullWhenPointer_910) {
  auto list = CanonMakerNote::tagListSi();

  if constexpr (std::is_pointer_v<decltype(list)>) {
    EXPECT_NE(list, nullptr);
  } else {
    // If it's not a pointer, nullability isn't meaningful from the interface.
    SUCCEED();
  }
}

TEST_F(CanonMakerNoteTagListSiTest_910, UsableInConstexprContext_910) {
  // The interface promises a constexpr function; verify it can be used in a constexpr context.
  constexpr auto list = CanonMakerNote::tagListSi();
  (void)list;

  // Also verify calling it at runtime is fine.
  auto runtimeList = CanonMakerNote::tagListSi();
  (void)runtimeList;

  SUCCEED();
}

}  // namespace
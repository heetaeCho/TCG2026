// SPDX-License-Identifier: GPL-2.0-or-later

#include <gtest/gtest.h>

#include <type_traits>
#include <utility>

#include "panasonicmn_int.hpp"

namespace {

using Exiv2::Internal::PanasonicMakerNote;

// Convert PanasonicMakerNote::tagList() return value into a pointer to the first element,
// whether it returns a pointer or a reference to an array.
template <typename T>
constexpr auto tagListToPtr(T&& t) {
  using U = std::remove_reference_t<T>;
  if constexpr (std::is_pointer_v<U>) {
    return t;
  } else {
    // Assume it's an array-like object supporting operator[] (e.g. reference to array).
    return &t[0];
  }
}

class PanasonicMakerNoteTest_705 : public ::testing::Test {};

TEST_F(PanasonicMakerNoteTest_705, TagList_IsUsableInConstantExpression_705) {
  // Compile-time check that tagList() is constexpr-usable and addressable.
  constexpr auto tl = PanasonicMakerNote::tagList();
  constexpr auto p = tagListToPtr(tl);

  static_assert(p != nullptr, "tagList() must provide an addressable tag list");
  (void)p;

  SUCCEED();
}

TEST_F(PanasonicMakerNoteTest_705, TagList_ReturnsStableAddressAcrossCalls_705) {
  const auto tl1 = PanasonicMakerNote::tagList();
  const auto tl2 = PanasonicMakerNote::tagList();

  const auto p1 = tagListToPtr(tl1);
  const auto p2 = tagListToPtr(tl2);

  // As a statically-backed tag list, repeated calls should provide the same address.
  ASSERT_NE(p1, nullptr);
  ASSERT_NE(p2, nullptr);
  EXPECT_EQ(p1, p2);
}

TEST_F(PanasonicMakerNoteTest_705, TagList_PointerTypeOrArrayReferenceIsAccepted_705) {
  // Boundary-style check on the *shape* of the return type without assuming internal contents.
  using Ret = decltype(PanasonicMakerNote::tagList());
  constexpr bool kOk =
      std::is_pointer_v<std::remove_reference_t<Ret>> ||
      std::is_array_v<std::remove_reference_t<Ret>>;

  EXPECT_TRUE(kOk);
}

}  // namespace
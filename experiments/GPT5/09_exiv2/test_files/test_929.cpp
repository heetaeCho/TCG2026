// SPDX-License-Identifier: GPL-2.0-or-later

#include <gtest/gtest.h>

#include <type_traits>

#include "canonmn_int.hpp"

namespace {

using Exiv2::Internal::CanonMakerNote;

template <typename T>
void ExpectNotNullIfPointer(const T& v) {
  if constexpr (std::is_pointer_v<T>) {
    EXPECT_NE(v, nullptr);
  } else {
    (void)v;  // Non-pointer: nothing sensible to assert without knowing the type.
  }
}

class CanonMakerNoteTest_929 : public ::testing::Test {};

TEST_F(CanonMakerNoteTest_929, TagListCi_IsUsableInConstexprContext_929) {
  // This test primarily ensures the function can be ODR-used in a constexpr context.
  // If tagListCi() is not constexpr as declared, this will fail to compile.
  constexpr auto list = CanonMakerNote::tagListCi();
  (void)list;
}

TEST_F(CanonMakerNoteTest_929, TagListCi_ReturnsStableValueAcrossCalls_929) {
  const auto a = CanonMakerNote::tagListCi();
  const auto b = CanonMakerNote::tagListCi();

  // Observable behavior: repeated calls should return an identical value (e.g., same pointer).
  EXPECT_EQ(a, b);

  // If the return type is a pointer, it should be non-null.
  ExpectNotNullIfPointer(a);
}

TEST_F(CanonMakerNoteTest_929, TagListCi_MultipleCallsRemainConsistent_929) {
  const auto first = CanonMakerNote::tagListCi();
  ExpectNotNullIfPointer(first);

  for (int i = 0; i < 100; ++i) {
    const auto cur = CanonMakerNote::tagListCi();
    EXPECT_EQ(cur, first);
  }
}

}  // namespace
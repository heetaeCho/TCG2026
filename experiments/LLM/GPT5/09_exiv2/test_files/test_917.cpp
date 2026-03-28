// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_canonmn_int_taglistmv_917.cpp

#include <gtest/gtest.h>

#include <type_traits>

#include "canonmn_int.hpp"

namespace {

using Exiv2::Internal::CanonMakerNote;

class CanonMakerNoteTagListMvTest_917 : public ::testing::Test {};

TEST_F(CanonMakerNoteTagListMvTest_917, ReturnsPointerLikeType_917) {
  // We don't assume the exact pointee type; just verify the API returns a pointer-like type.
  using Ret = decltype(CanonMakerNote::tagListMv());
  EXPECT_TRUE((std::is_pointer_v<Ret>)) << "tagListMv() should return a pointer type";
}

TEST_F(CanonMakerNoteTagListMvTest_917, ReturnsNonNull_917) {
  const auto ptr = CanonMakerNote::tagListMv();
  EXPECT_NE(ptr, nullptr);
}

TEST_F(CanonMakerNoteTagListMvTest_917, ReturnsStableAddressAcrossCalls_917) {
  const auto p1 = CanonMakerNote::tagListMv();
  const auto p2 = CanonMakerNote::tagListMv();
  EXPECT_EQ(p1, p2);
}

TEST_F(CanonMakerNoteTagListMvTest_917, UsableInConstexprContext_917) {
  // If the function is truly constexpr (as declared), it should be usable in a constexpr variable.
  constexpr auto p = CanonMakerNote::tagListMv();
  (void)p;

  // Also confirm the constexpr value matches the runtime call result.
  EXPECT_EQ(p, CanonMakerNote::tagListMv());
}

}  // namespace
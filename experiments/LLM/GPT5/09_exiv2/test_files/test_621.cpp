// SPDX-License-Identifier: GPL-2.0-or-later
// The TEST_ID is 621
//
// Unit tests for:
//   Exiv2::Internal::FujiMakerNote::tagList()
//
// Constraints honored:
// - Treat implementation as a black box (no assumptions about contents of tag list).
// - Only observable behavior: compile-time / linkage and return-type usability.
// - No private-state access.

#include <gtest/gtest.h>

#include "fujimn_int.hpp"

namespace {

using Exiv2::Internal::FujiMakerNote;

class FujiMakerNoteTest_621 : public ::testing::Test {};

TEST_F(FujiMakerNoteTest_621, TagList_IsCallable_621) {
  // If tagList() is not present/accessible, this test won't compile.
  (void)FujiMakerNote::tagList();
}

TEST_F(FujiMakerNoteTest_621, TagList_CanBeCalledMultipleTimes_621) {
  // We don't assume anything about identity/value stability; we only verify
  // it is callable repeatedly without requiring any external state.
  (void)FujiMakerNote::tagList();
  (void)FujiMakerNote::tagList();
}

TEST_F(FujiMakerNoteTest_621, TagList_ReturnType_IsUsableInDecltype_621) {
  // Boundary-ish: ensure the return type is a valid, complete type for usage
  // in decltype context without inspecting it.
  using RetT = decltype(FujiMakerNote::tagList());
  (void)sizeof(RetT);  // forces RetT to be a valid type
}

TEST_F(FujiMakerNoteTest_621, TagList_ReturnsSameTypeAcrossCalls_621) {
  // Observable at compile time: multiple invocations should yield the same type.
  using T1 = decltype(FujiMakerNote::tagList());
  using T2 = decltype(FujiMakerNote::tagList());
  EXPECT_TRUE((std::is_same<T1, T2>::value));
}

}  // namespace
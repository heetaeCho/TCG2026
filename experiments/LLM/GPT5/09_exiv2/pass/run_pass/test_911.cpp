// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_canonmn_int_taglistpa_911.cpp

#include <gtest/gtest.h>

#include <type_traits>

#include "canonmn_int.hpp"

namespace {

using Exiv2::Internal::CanonMakerNote;

class CanonMakerNoteTest_911 : public ::testing::Test {};

// Compile-time sanity checks (no assumptions about contents).
namespace compile_time_checks_911 {
constexpr auto p = CanonMakerNote::tagListPa();
static_assert(std::is_pointer_v<decltype(p)>,
              "CanonMakerNote::tagListPa() is expected to decay to a pointer type.");
}  // namespace compile_time_checks_911

// Normal operation: callable and returns a stable pointer-like value.
TEST_F(CanonMakerNoteTest_911, TagListPa_ReturnsNonNull_911) {
  const auto p = CanonMakerNote::tagListPa();
  ASSERT_NE(p, nullptr);
}

// Boundary-ish: repeated calls should be consistent (same underlying table).
TEST_F(CanonMakerNoteTest_911, TagListPa_RepeatedCallsReturnSameAddress_911) {
  const auto p1 = CanonMakerNote::tagListPa();
  const auto p2 = CanonMakerNote::tagListPa();
  ASSERT_NE(p1, nullptr);
  ASSERT_NE(p2, nullptr);
  EXPECT_EQ(p1, p2);
}

// Usability: can be used in a constexpr context (interface promise).
TEST_F(CanonMakerNoteTest_911, TagListPa_IsConstexprUsable_911) {
  constexpr auto p = CanonMakerNote::tagListPa();
  // We don’t inspect the pointed-to data (black-box). Just ensure it is a valid constant expression.
  (void)p;
  SUCCEED();
}

}  // namespace
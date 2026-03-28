// File: test_canonmn_int_taglistfi_915.cpp
// TEST_ID: 915

#include <gtest/gtest.h>

#include <type_traits>

// Include the interface under test
#include "canonmn_int.hpp"

namespace {

using Exiv2::Internal::CanonMakerNote;

TEST(CanonMakerNoteTagListFiTest_915, ReturnsSameAddressOnRepeatedCalls_915) {
  const auto* p1 = CanonMakerNote::tagListFi();
  const auto* p2 = CanonMakerNote::tagListFi();

  // Observable behavior: returned handle is stable across calls.
  EXPECT_EQ(p1, p2);
}

TEST(CanonMakerNoteTagListFiTest_915, ReturnValueIsPointerAndNonNull_915) {
  const auto* p = CanonMakerNote::tagListFi();

  // We don't assume what the pointee type is; only that the interface returns a pointer-like handle.
  static_assert(std::is_pointer_v<decltype(p)>, "tagListFi() must return a pointer type");

  // Basic safety: a tag list should be a valid address.
  EXPECT_NE(p, nullptr);
}

TEST(CanonMakerNoteTagListFiTest_915, CallableInConstexprContext_915) {
  // The interface declares tagListFi() as constexpr; verify it is usable in a constant-evaluated context.
  constexpr auto p = CanonMakerNote::tagListFi();
  static_assert(p != nullptr, "constexpr tagListFi() should not evaluate to nullptr");

  // Also verify runtime view matches constexpr result.
  EXPECT_EQ(p, CanonMakerNote::tagListFi());
}

}  // namespace
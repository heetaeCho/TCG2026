// SPDX-License-Identifier: GPL-2.0-or-later
// File: page_getStructParents_test.cpp
//
// Unit tests for Page::getStructParents() (black-box, interface-only).
//
// TEST_ID: 730

#include <gtest/gtest.h>

#include <type_traits>
#include <utility>

#include "poppler/Page.h"

namespace {

// Helper aliases for compile-time signature checks.
using ExpectedGetterPtr = int (Page::*)() const;

} // namespace

TEST(PageTest_730, GetStructParentsHasExpectedMemberFunctionType_730) {
  // Verify the member function pointer type matches: int (Page::*)() const
  static_assert(std::is_same_v<decltype(&Page::getStructParents), ExpectedGetterPtr>,
                "Page::getStructParents must have signature: int getStructParents() const");
  SUCCEED();
}

TEST(PageTest_730, GetStructParentsReturnTypeIsInt_730) {
  // Verify return type through expression SFINAE (no instance required).
  using Ret = decltype(std::declval<const Page&>().getStructParents());
  static_assert(std::is_same_v<Ret, int>, "getStructParents() must return int");
  SUCCEED();
}

TEST(PageTest_730, GetStructParentsCallableOnConstObject_730) {
  // Boundary-ish: ensure callable on const reference (const-correctness).
  using Expr = decltype(std::declval<const Page&>().getStructParents());
  (void)sizeof(Expr); // keep it ODR-safe, no runtime dependency
  SUCCEED();
}

TEST(PageTest_730, GetStructParentsCanBeInvokedIfDefaultConstructible_730) {
  // If Page happens to be default-constructible in this build, do a minimal runtime call.
  // This avoids guessing constructors while still providing a "normal operation" invocation
  // when possible.
  if constexpr (std::is_default_constructible_v<Page>) {
    const Page p{};
    const int v1 = p.getStructParents();
    const int v2 = p.getStructParents();

    // Observable behavior we can assert without assuming meaning:
    // repeated calls on the same const object should be stable.
    EXPECT_EQ(v1, v2);
  } else {
    SUCCEED();
  }
}
// SPDX-License-Identifier: GPL-2.0-or-later
//
// Unit tests for LinkDest::getKind()
// File under test: ./TestProjects/poppler/poppler/Link.h

#include <gtest/gtest.h>

#include <type_traits>
#include <utility>

#include "poppler/Link.h"

namespace {

class LinkDestTest_270 : public ::testing::Test {};

TEST_F(LinkDestTest_270, GetKind_AddressableAsConstMemberFunction_270) {
  // Verifies the method exists, is public, and is const-qualified.
  using ExpectedPtrType = LinkDestKind (LinkDest::*)() const;
  ExpectedPtrType ptr = &LinkDest::getKind;
  (void)ptr;
  SUCCEED();
}

TEST_F(LinkDestTest_270, GetKind_ReturnTypeIsLinkDestKind_270) {
  // Verifies the return type via an unevaluated expression (no object needed).
  using Ret = decltype(std::declval<const LinkDest&>().getKind());
  static_assert(std::is_same<Ret, LinkDestKind>::value,
                "LinkDest::getKind() must return LinkDestKind");
  SUCCEED();
}

TEST_F(LinkDestTest_270, GetKind_InvocableOnConstReference_270) {
  // Ensures getKind() can be called on a const LinkDest& (const correctness).
  static_assert(std::is_same<decltype(std::declval<const LinkDest&>().getKind()), LinkDestKind>::value,
                "getKind() should be callable on const LinkDest& and return LinkDestKind");
  SUCCEED();
}

TEST_F(LinkDestTest_270, GetKind_InvocableOnNonConstObject_270) {
  // Non-const objects should also be able to call the const-qualified method.
  static_assert(std::is_same<decltype(std::declval<LinkDest&>().getKind()), LinkDestKind>::value,
                "getKind() should be callable on LinkDest& and return LinkDestKind");
  SUCCEED();
}

}  // namespace
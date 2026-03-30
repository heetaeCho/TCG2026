// SPDX-License-Identifier: GPL-2.0-or-later
// File: LinkOCGState_test_327.cc

#include <gtest/gtest.h>

#include <type_traits>
#include <utility>   // std::declval
#include <vector>

#include "poppler/Link.h"
#include "poppler/Object.h"

namespace {

// Helper: create an Object that is at least safely constructible.
// In Poppler, default-constructed Object is typically a null object.
static Object MakeDefaultObjectForLinkAction_327() {
  Object obj;
  return obj;
}

} // namespace

// Compile-time interface contract test (no runtime assumptions).
TEST(LinkOCGStateTest_327, GetStateList_ReturnTypeIsConstVectorRef_327) {
  using RetT = decltype(std::declval<const LinkOCGState&>().getStateList());
  static_assert(std::is_same_v<RetT, const std::vector<StateList>&>,
                "getStateList() must return 'const std::vector<StateList>&'");
  SUCCEED();
}

TEST(LinkOCGStateTest_327, GetStateList_ReturnsSameReferenceOnRepeatedCalls_327) {
  Object obj = MakeDefaultObjectForLinkAction_327();
  LinkOCGState action(&obj);

  const auto* p1 = &action.getStateList();
  const auto* p2 = &action.getStateList();

  EXPECT_EQ(p1, p2); // same reference object on repeated calls
}

TEST(LinkOCGStateTest_327, GetStateList_CanBeCalledThroughConstReference_327) {
  Object obj = MakeDefaultObjectForLinkAction_327();
  LinkOCGState action(&obj);

  const LinkOCGState& cref = action;

  const auto* p_nonconst = &action.getStateList();
  const auto* p_const = &cref.getStateList();

  EXPECT_EQ(p_nonconst, p_const);
}

TEST(LinkOCGStateTest_327, GetStateList_ReferenceIsPerInstance_327) {
  Object obj1 = MakeDefaultObjectForLinkAction_327();
  Object obj2 = MakeDefaultObjectForLinkAction_327();

  LinkOCGState a(&obj1);
  LinkOCGState b(&obj2);

  // Observable, interface-level expectation: each instance owns its own state list.
  EXPECT_NE(&a.getStateList(), &b.getStateList());
}
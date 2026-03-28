// SPDX-License-Identifier: GPL-2.0-or-later
// File: LinkSubmitForm_getFlags_342_test.cpp
//
// Unit tests for LinkSubmitForm::getFlags() (black-box).
//
// Constraints honored:
// - No reliance on private state
// - No re-implementation / inference of internal parsing logic
// - Only observable behavior through the public interface

#include <gtest/gtest.h>

#include <cstdint>
#include <type_traits>

// Poppler headers
#include "poppler/Link.h"
#include "poppler/Object.h"

class LinkSubmitFormTest_342 : public ::testing::Test {
protected:
  // Create a minimal "empty" Object that should be safe to pass as submitObj.
  // We intentionally do not attempt to craft dictionaries/arrays/etc., to avoid
  // inferring constructor logic.
  static Object MakeEmptyObject() {
    Object obj;
    return obj;
  }
};

TEST_F(LinkSubmitFormTest_342, GetFlags_ReturnTypeIsUint32_342) {
  Object obj = MakeEmptyObject();
  LinkSubmitForm action(&obj);

  using RetT = decltype(action.getFlags());
  static_assert(std::is_same_v<RetT, uint32_t>,
                "LinkSubmitForm::getFlags() must return uint32_t");
}

TEST_F(LinkSubmitFormTest_342, GetFlags_IsStableAcrossRepeatedCalls_342) {
  Object obj = MakeEmptyObject();
  LinkSubmitForm action(&obj);

  const uint32_t first = action.getFlags();
  // Repeated calls should be stable for the same instance (pure getter behavior).
  EXPECT_EQ(action.getFlags(), first);
  EXPECT_EQ(action.getFlags(), first);
}

TEST_F(LinkSubmitFormTest_342, GetFlags_TwoInstancesFromSameObjectMatch_342) {
  Object obj = MakeEmptyObject();

  LinkSubmitForm a(&obj);
  LinkSubmitForm b(&obj);

  // We don't assume any specific numeric value, only consistency given identical input.
  EXPECT_EQ(a.getFlags(), b.getFlags());
}

TEST_F(LinkSubmitFormTest_342, GetFlags_CanBeCalledEvenIfActionNotOk_342) {
  Object obj = MakeEmptyObject();
  LinkSubmitForm action(&obj);

  // We don't assume whether isOk() is true/false for an empty object.
  // We only verify that calling getFlags() is safe and deterministic regardless.
  (void)action.isOk();

  const uint32_t f1 = action.getFlags();
  const uint32_t f2 = action.getFlags();
  EXPECT_EQ(f1, f2);
}
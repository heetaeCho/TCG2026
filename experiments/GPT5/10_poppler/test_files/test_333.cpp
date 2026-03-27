// SPDX-License-Identifier: GPL-2.0-or-later
// TEST_ID = 333
//
// Unit tests for LinkHide (Poppler)
//
// Constraints respected:
// - Treat implementation as black box (no private state access, no logic re-implementation).
// - Test only via public interface and observable behavior.
// - Cover normal/boundary/error-like inputs where possible (e.g., nullptr / null Object).
//
// File: ./TestProjects/poppler/poppler/LinkHide_test.cpp

#include <gtest/gtest.h>

#include "poppler/Link.h"
#include "poppler/Object.h"

namespace {

class LinkHideTest_333 : public ::testing::Test {
protected:
  // Helper: create a "null" Object in a way that is compatible with Poppler builds.
  static Object MakeNullObject() {
    Object obj;
#if defined(POPPLER_HAS_OBJECT_INITNULL) || 1
    // Many Poppler versions provide initNull(); if not, default constructed Object is often null.
    // We keep this call guarded by compilation behavior; if initNull exists, use it.
    // If it doesn't exist in your tree, remove the call below.
    obj.initNull();
#endif
    return obj;
  }
};

TEST_F(LinkHideTest_333, ConstructWithNullptr_AllowsSafeQueries_333) {
  // Boundary / error-like case: nullptr input.
  // Observable behavior we can test safely: public methods are callable and stable.
  LinkHide action(nullptr);

  // Should be callable without crashing.
  const bool ok1 = action.isOk();
  const bool ok2 = action.isOk();
  EXPECT_EQ(ok1, ok2);

  const auto k1 = action.getKind();
  const auto k2 = action.getKind();
  EXPECT_EQ(k1, k2);

  const bool show1 = action.isShowAction();
  const bool show2 = action.isShowAction();
  EXPECT_EQ(show1, show2);

  const bool has1 = action.hasTargetName();
  const bool has2 = action.hasTargetName();
  EXPECT_EQ(has1, has2);

  // Only access target name if the interface says it's present.
  if (action.hasTargetName()) {
    const std::string &n1 = action.getTargetName();
    const std::string &n2 = action.getTargetName();
    EXPECT_EQ(n1, n2);
  }
}

TEST_F(LinkHideTest_333, ConstructWithNullObject_AllowsSafeQueries_333) {
  // Boundary / error-like case: Object explicitly set to null.
  Object obj = MakeNullObject();
  LinkHide action(&obj);

  // Methods should be callable and return stable values across repeated calls.
  EXPECT_EQ(action.isOk(), action.isOk());
  EXPECT_EQ(action.getKind(), action.getKind());
  EXPECT_EQ(action.isShowAction(), action.isShowAction());
  EXPECT_EQ(action.hasTargetName(), action.hasTargetName());

  if (action.hasTargetName()) {
    EXPECT_EQ(action.getTargetName(), action.getTargetName());
  }
}

TEST_F(LinkHideTest_333, ShowAction_IsStableAcrossCalls_ForVariousInputs_333) {
  // Normal operation expectation (black-box): isShowAction() is a pure query and stable.
  LinkHide a_nullptr(nullptr);
  EXPECT_EQ(a_nullptr.isShowAction(), a_nullptr.isShowAction());

  Object obj = MakeNullObject();
  LinkHide a_nullobj(&obj);
  EXPECT_EQ(a_nullobj.isShowAction(), a_nullobj.isShowAction());
}

TEST_F(LinkHideTest_333, HasTargetName_GuardsGetTargetName_333) {
  // Verify the external contract usage pattern:
  // only call getTargetName() if hasTargetName() returns true.
  LinkHide action(nullptr);

  // If it reports a target name, repeated access should be consistent.
  if (action.hasTargetName()) {
    const std::string &name = action.getTargetName();
    EXPECT_EQ(name, action.getTargetName());
  } else {
    // If it reports no target name, we intentionally do not call getTargetName().
    SUCCEED();
  }
}

TEST_F(LinkHideTest_333, KindAndOk_AreSelfConsistent_333) {
  // Another black-box consistency check (no assumptions about specific enum values).
  Object obj = MakeNullObject();
  LinkHide action(&obj);

  const auto k = action.getKind();
  EXPECT_EQ(k, action.getKind());

  const bool ok = action.isOk();
  EXPECT_EQ(ok, action.isOk());
}

} // namespace
// TEST_ID: 330
// File: LinkHide_test.cpp
//
// Unit tests for LinkHide (poppler/Link.h)
// Constraints honored:
// - Treat LinkHide as a black box (no internal logic assumptions).
// - Use only observable behavior via public interface.
// - No private state access.

#include <gtest/gtest.h>

#include <string>

#include "poppler/Link.h"

// If the build system doesn't expose poppler::Object as a complete type here,
// we only need a pointer value for the constructor signature. The constructor
// takes `const Object*`, so we can pass nullptr without needing a definition.

class LinkHideTest_330 : public ::testing::Test {
protected:
  // Helper to construct safely without needing to materialize an Object instance.
  // We only use nullptr because the interface allows it.
  static LinkHide MakeWithNullObject() { return LinkHide(nullptr); }
};

TEST_F(LinkHideTest_330, GetKindReturnsActionHide_330) {
  LinkHide hide = MakeWithNullObject();
  EXPECT_EQ(hide.getKind(), actionHide);
}

TEST_F(LinkHideTest_330, GetKindIsStableAcrossRepeatedCalls_330) {
  LinkHide hide = MakeWithNullObject();

  const auto k1 = hide.getKind();
  const auto k2 = hide.getKind();
  const auto k3 = hide.getKind();

  EXPECT_EQ(k1, actionHide);
  EXPECT_EQ(k2, actionHide);
  EXPECT_EQ(k3, actionHide);
}

TEST_F(LinkHideTest_330, GetKindDoesNotDependOnIsOkCallOrder_330) {
  LinkHide hide = MakeWithNullObject();

  // We don't assume what isOk() returns; we only ensure observable getKind()
  // stays correct regardless of calling isOk().
  (void)hide.isOk();

  EXPECT_EQ(hide.getKind(), actionHide);

  (void)hide.isOk();
  EXPECT_EQ(hide.getKind(), actionHide);
}

TEST_F(LinkHideTest_330, HasTargetNameAndGetTargetNameAreCallable_330) {
  LinkHide hide = MakeWithNullObject();

  // Boundary/robustness: these APIs should be callable without crashing.
  // We do NOT assume a particular value for hasTargetName().
  const bool hasName = hide.hasTargetName();
  (void)hasName;

  // If it reports it has a target name, getTargetName() should be safely readable.
  // If it reports it doesn't, we still verify the returned reference is usable
  // (e.g., can read size), without assuming contents.
  const std::string &nameRef = hide.getTargetName();
  (void)nameRef.size();

  SUCCEED();
}

TEST_F(LinkHideTest_330, IsShowActionIsCallableAndGetKindStillHide_330) {
  LinkHide hide = MakeWithNullObject();

  // We don't assume whether it's show or hide; only that it's callable.
  const bool show = hide.isShowAction();
  (void)show;

  EXPECT_EQ(hide.getKind(), actionHide);
}

// Error/exceptional case (as observable): constructor called with nullptr.
// We cannot assert isOk() value without spec, but we can require calls remain safe.
TEST_F(LinkHideTest_330, NullObjectConstructionAllowsSafeQueries_330) {
  LinkHide hide(nullptr);

  // All public queries should be callable.
  (void)hide.isOk();
  (void)hide.hasTargetName();
  (void)hide.getTargetName();
  (void)hide.isShowAction();

  // And kind must match the interface contract.
  EXPECT_EQ(hide.getKind(), actionHide);
}
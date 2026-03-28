// LinkResetForm_test_335.cpp
#include <gtest/gtest.h>

#include "poppler/Link.h"
#include "poppler/Object.h"

namespace {

// Helper: create a benign Object for constructor input without assuming internal behavior.
static Object MakeNullObject() {
  Object obj;
  // Poppler's Object commonly supports initNull(). If the local Poppler fork differs,
  // adjust this helper to create a valid/benign Object without changing test intent.
  obj.initNull();
  return obj;
}

} // namespace

// The TEST_ID is 335

TEST(LinkResetFormTest_335, GetKindReturnsActionResetFormWithNullptr_335) {
  // Boundary: nullptr input (if supported by implementation).
  // We only assert observable behavior: getKind() value.
  LinkResetForm action(nullptr);
  EXPECT_EQ(action.getKind(), actionResetForm);
}

TEST(LinkResetFormTest_335, GetKindReturnsActionResetFormWithNullObject_335) {
  // Normal-ish: pass a well-defined "null" Object.
  const Object nameObj = MakeNullObject();
  LinkResetForm action(&nameObj);

  EXPECT_EQ(action.getKind(), actionResetForm);
}

TEST(LinkResetFormTest_335, GetKindIsStableRegardlessOfIsOk_335) {
  // We do not assume what isOk() returns for a given Object.
  // We only verify that calling isOk() does not affect getKind().
  const Object nameObj = MakeNullObject();
  LinkResetForm action(&nameObj);

  (void)action.isOk(); // observable call; result intentionally not asserted
  EXPECT_EQ(action.getKind(), actionResetForm);

  (void)action.isOk();
  EXPECT_EQ(action.getKind(), actionResetForm);
}

TEST(LinkResetFormTest_335, GetKindDoesNotThrow_335) {
  // Exceptional/robustness: observable via "no throw" + correct kind.
  EXPECT_NO_THROW({
    const Object nameObj = MakeNullObject();
    LinkResetForm action(&nameObj);
    EXPECT_EQ(action.getKind(), actionResetForm);
  });
}
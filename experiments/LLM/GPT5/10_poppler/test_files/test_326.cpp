// LinkOCGState_getKind_tests_326.cpp

#include <gtest/gtest.h>

#include "Link.h"
#include "Object.h"

namespace {

// Helper that builds an Object in a safe, minimal state.
// We intentionally avoid guessing any required dictionary structure for LinkOCGState.
static Object MakeNullObject() {
  Object obj;
  obj.initNull();
  return obj;
}

class LinkOCGStateTest_326 : public ::testing::Test {
protected:
  Object obj_ = MakeNullObject();
};

} // namespace

TEST_F(LinkOCGStateTest_326, GetKindReturnsActionOCGState_326) {
  LinkOCGState action(&obj_);
  EXPECT_EQ(action.getKind(), actionOCGState);
}

TEST_F(LinkOCGStateTest_326, GetKindIsStableAcrossCalls_326) {
  LinkOCGState action(&obj_);
  const auto k1 = action.getKind();
  const auto k2 = action.getKind();
  EXPECT_EQ(k1, k2);
  EXPECT_EQ(k1, actionOCGState);
}

TEST_F(LinkOCGStateTest_326, IsOkIsCallableAndStableAcrossCalls_326) {
  LinkOCGState action(&obj_);

  const bool ok1 = action.isOk();
  const bool ok2 = action.isOk();

  // Black-box: we don't assume true/false, only that repeated calls are consistent.
  EXPECT_EQ(ok1, ok2);
}

TEST_F(LinkOCGStateTest_326, GetStateListReturnsStableReference_326) {
  LinkOCGState action(&obj_);

  const auto &list1 = action.getStateList();
  const auto *ptr1 = &list1;

  const auto &list2 = action.getStateList();
  const auto *ptr2 = &list2;

  EXPECT_EQ(ptr1, ptr2);

  // Also ensure it is safe to query basic properties.
  const auto size1 = list1.size();
  const auto size2 = list2.size();
  EXPECT_EQ(size1, size2);
}

TEST_F(LinkOCGStateTest_326, GetPreserveRBIsCallableAndStable_326) {
  LinkOCGState action(&obj_);

  const bool v1 = action.getPreserveRB();
  const bool v2 = action.getPreserveRB();

  // Black-box: do not assume default; only require consistency for repeated reads.
  EXPECT_EQ(v1, v2);
}
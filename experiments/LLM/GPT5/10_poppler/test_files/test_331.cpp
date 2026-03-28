// File: test_linkhide_331.cpp
// Unit tests for LinkHide::hasTargetName()
// The TEST_ID is 331

#include <gtest/gtest.h>

#include "poppler/Link.h"
#include "poppler/Object.h"

namespace {

class LinkHideTest_331 : public ::testing::Test {
protected:
  // Helper: exercise the API in a purely black-box way (no assumptions about semantics),
  // asserting only that it is callable and stable (idempotent) for a given instance.
  static void ExpectHasTargetNameIsStable(LinkHide &lh) {
    const bool first = lh.hasTargetName();
    const bool second = lh.hasTargetName();
    const bool third = lh.hasTargetName();
    EXPECT_EQ(first, second);
    EXPECT_EQ(second, third);
  }
};

} // namespace

TEST_F(LinkHideTest_331, ConstructWithNullObject_AllowsCallingHasTargetName_331) {
  Object obj;
  obj.initNull();

  ASSERT_NO_THROW({
    LinkHide lh(&obj);
    // No semantic expectations; only observable stability of the return value.
    ExpectHasTargetNameIsStable(lh);
  });
}

TEST_F(LinkHideTest_331, ConstructWithBoolObject_AllowsCallingHasTargetName_331) {
  Object obj;
  obj.initBool(true);

  ASSERT_NO_THROW({
    LinkHide lh(&obj);
    ExpectHasTargetNameIsStable(lh);
  });
}

TEST_F(LinkHideTest_331, ConstructWithIntObject_AllowsCallingHasTargetName_331) {
  Object obj;
  obj.initInt(0);

  ASSERT_NO_THROW({
    LinkHide lh(&obj);
    ExpectHasTargetNameIsStable(lh);
  });
}

TEST_F(LinkHideTest_331, ConstructWithNameObject_AllowsCallingHasTargetName_331) {
  Object obj;
  obj.initName("AnyName");

  ASSERT_NO_THROW({
    LinkHide lh(&obj);
    ExpectHasTargetNameIsStable(lh);
  });
}

TEST_F(LinkHideTest_331, MultipleInstancesFromSameInput_ProduceConsistentPerInstanceResults_331) {
  Object obj;
  obj.initNull();

  ASSERT_NO_THROW({
    LinkHide lh1(&obj);
    LinkHide lh2(&obj);

    // Per-instance stability.
    const bool a1 = lh1.hasTargetName();
    const bool a2 = lh1.hasTargetName();
    EXPECT_EQ(a1, a2);

    const bool b1 = lh2.hasTargetName();
    const bool b2 = lh2.hasTargetName();
    EXPECT_EQ(b1, b2);

    // Cross-instance consistency for identical construction input is a reasonable
    // observable check without assuming the "meaning" of the value.
    EXPECT_EQ(a1, b1);
  });
}
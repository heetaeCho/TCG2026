// LinkRendition_getOperation_tests_312.cc
// Unit tests for LinkRendition::getOperation (black-box interface tests)
//
// TEST_ID: 312

#include <gtest/gtest.h>

#include "poppler/Link.h" // Adjust include path if needed in your build

namespace {

class LinkRenditionTest_312 : public ::testing::Test {};

TEST_F(LinkRenditionTest_312, GetOperation_DoesNotCrash_WithNullObjectPtr_312) {
  // Boundary: constructor called with nullptr (if supported by implementation).
  // We only verify observable behavior: no crash and stable return value.
  LinkRendition lr(nullptr);

  const auto op1 = lr.getOperation();
  const auto op2 = lr.getOperation();

  EXPECT_EQ(op1, op2);
}

TEST_F(LinkRenditionTest_312, GetOperation_IsStable_ForDefaultConstructedObject_312) {
  // Boundary/robustness: pass a default-constructed Object (whatever "default" means in this build).
  // We avoid asserting "validity" because that would require inferring parsing rules.
  Object obj;
  LinkRendition lr(&obj);

  const auto op1 = lr.getOperation();
  const auto op2 = lr.getOperation();

  EXPECT_EQ(op1, op2);
}

TEST_F(LinkRenditionTest_312, GetOperation_CanBeCalled_Repeatedly_OnSameInstance_312) {
  // Normal usage pattern (observable): repeated calls are consistent and do not throw/crash.
  Object obj;
  LinkRendition lr(&obj);

  const auto baseline = lr.getOperation();
  for (int i = 0; i < 10; ++i) {
    EXPECT_EQ(lr.getOperation(), baseline);
  }
}

}  // namespace
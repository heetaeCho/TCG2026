// File: test_xref_getrootnum_263.cpp
// Unit tests for XRef::getRootNum()
// TEST_ID: 263

#include <gtest/gtest.h>

#include "poppler/XRef.h"

class XRefTest_263 : public ::testing::Test {
protected:
  XRef xref_;
};

TEST_F(XRefTest_263, GetRootNum_DoesNotThrow_263) {
  EXPECT_NO_THROW({
    (void)xref_.getRootNum();
  });
}

TEST_F(XRefTest_263, GetRootNum_IsStableAcrossMultipleCalls_263) {
  const int first = xref_.getRootNum();
  const int second = xref_.getRootNum();
  EXPECT_EQ(first, second);
}

TEST_F(XRefTest_263, GetRootNum_WorksThroughConstReference_263) {
  const XRef& cxref = xref_;
  const int a = cxref.getRootNum();
  const int b = cxref.getRootNum();
  EXPECT_EQ(a, b);
}

TEST_F(XRefTest_263, GetRootNum_DefaultConstructedObjectIsUsable_263) {
  XRef local;
  EXPECT_NO_THROW({
    (void)local.getRootNum();
  });
}
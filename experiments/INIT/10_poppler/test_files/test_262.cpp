// File: test_xref_262.cpp
// Unit tests for poppler::XRef (or ::XRef) getNumObjects()
// TEST_ID: 262

#include <gtest/gtest.h>

#include <type_traits>

// Adjust include path as needed by your build system.
#include "XRef.h"

namespace {

class XRefTest_262 : public ::testing::Test {};

TEST_F(XRefTest_262, DefaultConstruction_ReturnsNonNegative_262) {
  ::XRef xref;
  const int n = xref.getNumObjects();
  EXPECT_GE(n, 0);
}

TEST_F(XRefTest_262, DefaultConstruction_IsStableAcrossMultipleCalls_262) {
  ::XRef xref;

  const int first = xref.getNumObjects();
  const int second = xref.getNumObjects();
  const int third = xref.getNumObjects();

  EXPECT_EQ(first, second);
  EXPECT_EQ(second, third);
}

TEST_F(XRefTest_262, ConstObject_AllowsGetNumObjects_262) {
  const ::XRef xref;
  const int n = xref.getNumObjects();
  EXPECT_GE(n, 0);
}

TEST_F(XRefTest_262, NotCopyableOrAssignable_TypeTraits_262) {
  // Observable API contract from the header: copy/assignment are deleted.
  EXPECT_FALSE((std::is_copy_constructible_v<::XRef>));
  EXPECT_FALSE((std::is_copy_assignable_v<::XRef>));
  EXPECT_FALSE((std::is_move_constructible_v<::XRef>));
  EXPECT_FALSE((std::is_move_assignable_v<::XRef>));
}

TEST_F(XRefTest_262, GetNumObjects_ReturnTypeIsInt_262) {
  ::XRef xref;
  static_assert(std::is_same_v<decltype(xref.getNumObjects()), int>,
                "XRef::getNumObjects() must return int");
  (void)xref;
}

}  // namespace
// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_xref_getrootgen_264.cpp
//
// Unit tests for poppler::XRef::getRootGen() based strictly on the provided interface.
// Constraints honored:
// - Treat XRef as a black box (no private access, no inferred internal logic).
// - Only use observable behavior via public API.
// - No mocks needed (no external interactions exposed by getRootGen()).

#include <gtest/gtest.h>

// Include the header under test.
#include "./TestProjects/poppler/poppler/XRef.h"

namespace {

class XRefTest_264 : public ::testing::Test {
protected:
  XRefTest_264() = default;
  ~XRefTest_264() override = default;
};

TEST_F(XRefTest_264, GetRootGen_IsDeterministicAcrossRepeatedCalls_264) {
  XRef xref;

  const int first = xref.getRootGen();
  const int second = xref.getRootGen();
  const int third = xref.getRootGen();

  EXPECT_EQ(first, second);
  EXPECT_EQ(second, third);
}

TEST_F(XRefTest_264, GetRootGen_DoesNotChangeWhenCalledOnConstRef_264) {
  XRef xref;
  const XRef& cxref = xref;

  const int a = cxref.getRootGen();
  const int b = cxref.getRootGen();

  EXPECT_EQ(a, b);
}

TEST_F(XRefTest_264, GetRootGen_ReturnValueIsStableBetweenIndependentInstances_264) {
  // Boundary-ish: ensure no cross-instance interference is observable via this getter.
  XRef xref1;
  XRef xref2;

  const int v1a = xref1.getRootGen();
  const int v1b = xref1.getRootGen();
  const int v2a = xref2.getRootGen();
  const int v2b = xref2.getRootGen();

  EXPECT_EQ(v1a, v1b);
  EXPECT_EQ(v2a, v2b);
}

TEST_F(XRefTest_264, GetRootGen_CanBeCalledOnTemporaryWithoutCrashing_264) {
  // Boundary: calling getter on a temporary object should be safe and return an int.
  // We only assert it does not crash and the returned value is consistent within this expression.
  const int v = XRef{}.getRootGen();
  (void)v;
  SUCCEED();
}

}  // namespace
// SPDX-License-Identifier: GPL-2.0-or-later
// Unit tests for XRef::isXRefStream()
// TEST_ID: 258

#include <gtest/gtest.h>

#include <memory>
#include <vector>

#include "poppler/XRef.h"

namespace {

class XRefTest_258 : public ::testing::Test {};

TEST_F(XRefTest_258, DefaultConstructed_CallDoesNotThrow_258) {
  XRef xref;
  EXPECT_NO_THROW({
    volatile bool v = xref.isXRefStream();
    (void)v;
  });
}

TEST_F(XRefTest_258, DefaultConstructed_RepeatedCallsAreStable_258) {
  XRef xref;

  const bool first = xref.isXRefStream();
  for (int i = 0; i < 10; ++i) {
    EXPECT_EQ(first, xref.isXRefStream());
  }
}

TEST_F(XRefTest_258, ConstObject_CanCallAndIsStable_258) {
  XRef xref;
  const XRef& cref = xref;

  const bool first = cref.isXRefStream();
  for (int i = 0; i < 10; ++i) {
    EXPECT_EQ(first, cref.isXRefStream());
  }
}

TEST_F(XRefTest_258, MultipleInstances_EachInstanceIsSelfConsistent_258) {
  XRef a;
  XRef b;

  const bool a0 = a.isXRefStream();
  const bool b0 = b.isXRefStream();

  // We do NOT assume a0 != b0 (that would infer internal state).
  for (int i = 0; i < 10; ++i) {
    EXPECT_EQ(a0, a.isXRefStream());
    EXPECT_EQ(b0, b.isXRefStream());
  }
}

TEST_F(XRefTest_258, HeapAllocated_ObjectUsableViaPointer_258) {
  auto xref = std::make_unique<XRef>();

  const bool first = xref->isXRefStream();
  EXPECT_EQ(first, xref->isXRefStream());
  EXPECT_EQ(first, xref->isXRefStream());
}

TEST_F(XRefTest_258, WorksInContainer_258) {
  std::vector<XRef> v;
  v.emplace_back();
  v.emplace_back();
  v.emplace_back();

  for (auto& x : v) {
    const bool first = x.isXRefStream();
    EXPECT_EQ(first, x.isXRefStream());
  }
}

}  // namespace
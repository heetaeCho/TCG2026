// SPDX-License-Identifier: GPL-2.0-or-later
// Unit tests for GfxPath::getSubpath
//
// File: test_gfxpath_getsubpath_555.cpp

#include <gtest/gtest.h>

#include "GfxState.h" // GfxPath, GfxSubpath

namespace {

class GfxPathTest_555 : public ::testing::Test {
protected:
  static GfxPath MakePathWithNSubpaths(int n) {
    GfxPath p;
    for (int i = 0; i < n; ++i) {
      const double base = static_cast<double>(i) * 10.0;
      p.moveTo(base, base);
      p.lineTo(base + 1.0, base + 2.0);
      // close() is part of the public API; calling it helps ensure each subpath
      // is "completed" as a typical usage pattern, but we do not assume internals.
      p.close();
    }
    return p;
  }
};

TEST_F(GfxPathTest_555, GetSubpath_ReturnsNonNullForEachValidIndex_555) {
  GfxPath p = MakePathWithNSubpaths(3);

  const int n = p.getNumSubpaths();
  ASSERT_GE(n, 1);

  for (int i = 0; i < n; ++i) {
    GfxSubpath *sp = p.getSubpath(i);
    EXPECT_NE(sp, nullptr) << "Expected non-null subpath pointer for index " << i;
  }
}

TEST_F(GfxPathTest_555, GetSubpath_WorksForFirstAndLastIndex_555) {
  GfxPath p = MakePathWithNSubpaths(4);

  const int n = p.getNumSubpaths();
  ASSERT_GE(n, 1);

  GfxSubpath *first = p.getSubpath(0);
  EXPECT_NE(first, nullptr);

  GfxSubpath *last = p.getSubpath(n - 1);
  EXPECT_NE(last, nullptr);
}

TEST_F(GfxPathTest_555, GetSubpath_RepeatedCallsReturnSamePointerForSameIndex_555) {
  GfxPath p = MakePathWithNSubpaths(2);

  const int n = p.getNumSubpaths();
  ASSERT_GE(n, 2);

  GfxSubpath *sp1 = p.getSubpath(0);
  ASSERT_NE(sp1, nullptr);

  GfxSubpath *sp2 = p.getSubpath(0);
  EXPECT_EQ(sp1, sp2) << "Expected stable pointer identity for the same index";
}

TEST_F(GfxPathTest_555, GetSubpath_AfterAppend_AllValidIndicesAccessible_555) {
  GfxPath a = MakePathWithNSubpaths(2);
  GfxPath b = MakePathWithNSubpaths(3);

  const int na = a.getNumSubpaths();
  const int nb = b.getNumSubpaths();
  ASSERT_GE(na, 1);
  ASSERT_GE(nb, 1);

  a.append(&b);

  const int n = a.getNumSubpaths();
  ASSERT_GE(n, na + nb);

  for (int i = 0; i < n; ++i) {
    EXPECT_NE(a.getSubpath(i), nullptr) << "Subpath should be accessible at index " << i;
  }
}

TEST_F(GfxPathTest_555, GetSubpath_FromCopy_AllValidIndicesAccessible_555) {
  GfxPath p = MakePathWithNSubpaths(3);
  const int n = p.getNumSubpaths();
  ASSERT_GE(n, 1);

  GfxPath *cpy = p.copy();
  ASSERT_NE(cpy, nullptr);

  EXPECT_EQ(cpy->getNumSubpaths(), n);

  for (int i = 0; i < cpy->getNumSubpaths(); ++i) {
    EXPECT_NE(cpy->getSubpath(i), nullptr) << "Copy should provide accessible subpath at index " << i;
  }

  delete cpy;
}

} // namespace
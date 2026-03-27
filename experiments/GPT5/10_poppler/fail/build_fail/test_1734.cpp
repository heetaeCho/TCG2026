//===----------------------------------------------------------------------===//
// CairoOutputDev_hasType3GlyphBBox_1734_test.cc
// Unit tests for CairoOutputDev::hasType3GlyphBBox()
//===----------------------------------------------------------------------===//

#include <gtest/gtest.h>

#include "poppler/CairoOutputDev.h"

namespace {

class CairoOutputDevHasType3GlyphBBoxTest_1734 : public ::testing::Test {
protected:
  CairoOutputDev dev_;
};

TEST_F(CairoOutputDevHasType3GlyphBBoxTest_1734, ReturnsStableValueAcrossRepeatedCalls_1734) {
  const bool first = dev_.hasType3GlyphBBox();

  // Black-box stability: repeated calls without other interactions should be consistent.
  EXPECT_EQ(first, dev_.hasType3GlyphBBox());
  EXPECT_EQ(first, dev_.hasType3GlyphBBox());
  EXPECT_EQ(first, dev_.hasType3GlyphBBox());
}

TEST_F(CairoOutputDevHasType3GlyphBBoxTest_1734, CallableOnConstInstance_1734) {
  const CairoOutputDev &cdev = dev_;

  const bool v1 = cdev.hasType3GlyphBBox();
  const bool v2 = cdev.hasType3GlyphBBox();

  EXPECT_EQ(v1, v2);
}

TEST_F(CairoOutputDevHasType3GlyphBBoxTest_1734, SeparateInstancesEachProvideStableResult_1734) {
  CairoOutputDev a;
  CairoOutputDev b;

  const bool a_first = a.hasType3GlyphBBox();
  const bool b_first = b.hasType3GlyphBBox();

  EXPECT_EQ(a_first, a.hasType3GlyphBBox());
  EXPECT_EQ(b_first, b.hasType3GlyphBBox());

  // Also verify stability through const access paths.
  const CairoOutputDev &ca = a;
  const CairoOutputDev &cb = b;
  EXPECT_EQ(a_first, ca.hasType3GlyphBBox());
  EXPECT_EQ(b_first, cb.hasType3GlyphBBox());
}

} // namespace
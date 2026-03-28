// CairoOutputDev_getType3GlyphBBox_1735_test.cc
#include <gtest/gtest.h>

#include "CairoOutputDev.h"

namespace {

class CairoOutputDevTest_1735 : public ::testing::Test {
protected:
  CairoOutputDev dev;
};

TEST_F(CairoOutputDevTest_1735, GetType3GlyphBBox_ReturnsNonNullPointer_1735) {
  double *bbox = dev.getType3GlyphBBox();
  ASSERT_NE(bbox, nullptr);
}

TEST_F(CairoOutputDevTest_1735, GetType3GlyphBBox_ReturnsStablePointerAcrossCalls_1735) {
  double *bbox1 = dev.getType3GlyphBBox();
  double *bbox2 = dev.getType3GlyphBBox();

  ASSERT_NE(bbox1, nullptr);
  ASSERT_NE(bbox2, nullptr);
  EXPECT_EQ(bbox1, bbox2);
}

TEST_F(CairoOutputDevTest_1735, GetType3GlyphBBox_AllowsReadWriteThroughReturnedPointer_1735) {
  double *bbox1 = dev.getType3GlyphBBox();
  ASSERT_NE(bbox1, nullptr);

  // Boundary-ish values (including negatives and a large magnitude), written through the API-provided pointer.
  const double llx = -123.5;
  const double lly = 0.0;
  const double urx = 987654.25;
  const double ury = 42.75;

  bbox1[0] = llx;
  bbox1[1] = lly;
  bbox1[2] = urx;
  bbox1[3] = ury;

  // Verify the same memory is observed on subsequent calls (black-box observable behavior via the returned pointer).
  double *bbox2 = dev.getType3GlyphBBox();
  ASSERT_NE(bbox2, nullptr);

  EXPECT_EQ(bbox2[0], llx);
  EXPECT_EQ(bbox2[1], lly);
  EXPECT_EQ(bbox2[2], urx);
  EXPECT_EQ(bbox2[3], ury);
}

}  // namespace
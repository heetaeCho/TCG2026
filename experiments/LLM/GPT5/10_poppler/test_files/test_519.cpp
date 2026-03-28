// Test file for GfxRadialShading::getCoords
// Focus: observable behavior via public interface only.
//
// File: gfx_radial_shading_getcoords_test_519.cpp

#include <gtest/gtest.h>

#include "poppler/GfxState.h"

namespace {

class GfxRadialShadingTest_519 : public ::testing::Test {
protected:
  // Prefer the ctor overload that avoids needing Function objects.
  static GfxRadialShading Make(double x0, double y0, double r0,
                               double x1, double y1, double r1,
                               double t0, double t1,
                               bool extend0, bool extend1) {
    int dummyFuncs = 0;
    return GfxRadialShading(x0, y0, r0, x1, y1, r1, t0, t1, std::move(dummyFuncs), extend0, extend1);
  }
};

TEST_F(GfxRadialShadingTest_519, GetCoordsReturnsConstructorValues_519) {
  auto shading = Make(1.25, -2.5, 3.75, 10.0, 20.0, 30.0, /*t0=*/0.0, /*t1=*/1.0, false, true);

  double x0 = 0, y0 = 0, r0 = 0, x1 = 0, y1 = 0, r1 = 0;
  shading.getCoords(&x0, &y0, &r0, &x1, &y1, &r1);

  EXPECT_DOUBLE_EQ(x0, 1.25);
  EXPECT_DOUBLE_EQ(y0, -2.5);
  EXPECT_DOUBLE_EQ(r0, 3.75);
  EXPECT_DOUBLE_EQ(x1, 10.0);
  EXPECT_DOUBLE_EQ(y1, 20.0);
  EXPECT_DOUBLE_EQ(r1, 30.0);
}

TEST_F(GfxRadialShadingTest_519, GetCoordsHandlesZerosAndNegatives_519) {
  auto shading = Make(0.0, 0.0, 0.0, -0.0, -0.0, -5.0, /*t0=*/-1.0, /*t1=*/-1.0, true, false);

  double x0 = 123, y0 = 123, r0 = 123, x1 = 123, y1 = 123, r1 = 123;
  shading.getCoords(&x0, &y0, &r0, &x1, &y1, &r1);

  EXPECT_DOUBLE_EQ(x0, 0.0);
  EXPECT_DOUBLE_EQ(y0, 0.0);
  EXPECT_DOUBLE_EQ(r0, 0.0);
  EXPECT_DOUBLE_EQ(x1, -0.0);
  EXPECT_DOUBLE_EQ(y1, -0.0);
  EXPECT_DOUBLE_EQ(r1, -5.0);
}

TEST_F(GfxRadialShadingTest_519, GetCoordsHandlesLargeMagnitudes_519) {
  const double big = 1e300;
  auto shading = Make(big, -big, big / 2.0, -big / 3.0, big / 4.0, -big / 5.0,
                      /*t0=*/0.0, /*t1=*/2.0, false, false);

  double x0 = 0, y0 = 0, r0 = 0, x1 = 0, y1 = 0, r1 = 0;
  shading.getCoords(&x0, &y0, &r0, &x1, &y1, &r1);

  EXPECT_DOUBLE_EQ(x0, big);
  EXPECT_DOUBLE_EQ(y0, -big);
  EXPECT_DOUBLE_EQ(r0, big / 2.0);
  EXPECT_DOUBLE_EQ(x1, -big / 3.0);
  EXPECT_DOUBLE_EQ(y1, big / 4.0);
  EXPECT_DOUBLE_EQ(r1, -big / 5.0);
}

TEST_F(GfxRadialShadingTest_519, GetCoordsWorksWithAliasedOutputPointers_519) {
  auto shading = Make(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, /*t0=*/0.0, /*t1=*/1.0, false, false);

  // All outputs alias the same storage. Observable behavior: sequential writes.
  double v = 0.0;
  shading.getCoords(&v, &v, &v, &v, &v, &v);

  // The last assignment in getCoords is *r1A = r1; therefore v should end up as r1.
  EXPECT_DOUBLE_EQ(v, 6.0);
}

TEST_F(GfxRadialShadingTest_519, CopyConstructorPreservesCoords_519) {
  auto original = Make(7.0, 8.0, 9.0, -1.0, -2.0, -3.0, /*t0=*/0.25, /*t1=*/0.75, true, true);

  GfxRadialShading copied(&original);

  double ox0 = 0, oy0 = 0, or0 = 0, ox1 = 0, oy1 = 0, or1 = 0;
  double cx0 = 0, cy0 = 0, cr0 = 0, cx1 = 0, cy1 = 0, cr1 = 0;

  original.getCoords(&ox0, &oy0, &or0, &ox1, &oy1, &or1);
  copied.getCoords(&cx0, &cy0, &cr0, &cx1, &cy1, &cr1);

  EXPECT_DOUBLE_EQ(cx0, ox0);
  EXPECT_DOUBLE_EQ(cy0, oy0);
  EXPECT_DOUBLE_EQ(cr0, or0);
  EXPECT_DOUBLE_EQ(cx1, ox1);
  EXPECT_DOUBLE_EQ(cy1, oy1);
  EXPECT_DOUBLE_EQ(cr1, or1);
}

#if GTEST_HAS_DEATH_TEST
TEST_F(GfxRadialShadingTest_519, GetCoordsDiesOnNullOutputPointer_519) {
  auto shading = Make(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, /*t0=*/0.0, /*t1=*/1.0, false, false);

  double x0 = 0, y0 = 0, r0 = 0, x1 = 0, y1 = 0, r1 = 0;

  // Error case (observable): dereferencing a null output pointer should crash/abort.
  // Use a death test so this remains contained.
  EXPECT_DEATH(shading.getCoords(nullptr, &y0, &r0, &x1, &y1, &r1), ".*");
}
#endif

} // namespace
// TEST_ID: 518
#include <gtest/gtest.h>

#include "poppler/GfxState.h"

namespace {

class GfxAxialShadingTest_518 : public ::testing::Test {
protected:
  static GfxAxialShading MakeShading(double x0, double y0, double x1, double y1) {
    // Use the ctor overload that avoids needing Function objects.
    // Treat implementation as a black box; we only rely on the public interface.
    int funcs = 0;
    return GfxAxialShading(x0, y0, x1, y1,
                           /*t0A=*/0.0, /*t1A=*/1.0,
                           std::move(funcs),
                           /*extend0A=*/false, /*extend1A=*/false);
  }
};

TEST_F(GfxAxialShadingTest_518, GetCoordsReturnsConstructionCoords_518) {
  auto shading = MakeShading(1.25, -2.5, 10.0, 20.0);

  double x0 = 0, y0 = 0, x1 = 0, y1 = 0;
  shading.getCoords(&x0, &y0, &x1, &y1);

  EXPECT_DOUBLE_EQ(x0, 1.25);
  EXPECT_DOUBLE_EQ(y0, -2.5);
  EXPECT_DOUBLE_EQ(x1, 10.0);
  EXPECT_DOUBLE_EQ(y1, 20.0);
}

TEST_F(GfxAxialShadingTest_518, GetCoordsIsStableAcrossMultipleCalls_518) {
  auto shading = MakeShading(-0.0, 0.0, 3.14159, -1234.0);

  double x0a = 0, y0a = 0, x1a = 0, y1a = 0;
  shading.getCoords(&x0a, &y0a, &x1a, &y1a);

  double x0b = 0, y0b = 0, x1b = 0, y1b = 0;
  shading.getCoords(&x0b, &y0b, &x1b, &y1b);

  EXPECT_DOUBLE_EQ(x0a, x0b);
  EXPECT_DOUBLE_EQ(y0a, y0b);
  EXPECT_DOUBLE_EQ(x1a, x1b);
  EXPECT_DOUBLE_EQ(y1a, y1b);
}

TEST_F(GfxAxialShadingTest_518, GetCoordsHandlesBoundaryValues_518) {
  // Boundary-ish values: zeros, negatives, and large magnitudes.
  auto shading = MakeShading(0.0, -0.0, 1e308, -1e308);

  double x0 = 123, y0 = 456, x1 = 789, y1 = 101112;
  shading.getCoords(&x0, &y0, &x1, &y1);

  EXPECT_DOUBLE_EQ(x0, 0.0);
  EXPECT_DOUBLE_EQ(y0, -0.0);
  EXPECT_DOUBLE_EQ(x1, 1e308);
  EXPECT_DOUBLE_EQ(y1, -1e308);
}

#if GTEST_HAS_DEATH_TEST
TEST_F(GfxAxialShadingTest_518, GetCoordsWithNullOutputPointerDies_518) {
  auto shading = MakeShading(1.0, 2.0, 3.0, 4.0);

  double y0 = 0, x1 = 0, y1 = 0;
  // The interface accepts raw pointers; passing nullptr is an invalid usage.
  // We verify the observable behavior (process death) without relying on internals.
  EXPECT_DEATH(shading.getCoords(nullptr, &y0, &x1, &y1), "");
}

TEST_F(GfxAxialShadingTest_518, GetCoordsWithAllNullptrDies_518) {
  auto shading = MakeShading(1.0, 2.0, 3.0, 4.0);
  EXPECT_DEATH(shading.getCoords(nullptr, nullptr, nullptr, nullptr), "");
}
#endif  // GTEST_HAS_DEATH_TEST

}  // namespace
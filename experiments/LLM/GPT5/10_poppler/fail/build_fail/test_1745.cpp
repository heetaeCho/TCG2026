// CairoImageOutputDev_tilingPatternFill_1745_test.cc
#include <gtest/gtest.h>

#include <array>
#include <cmath>
#include <limits>

#include "CairoOutputDev.h"

// Forward-declare types used only as pointers (we don't need definitions for these tests).
class GfxState;
class Gfx;
class Catalog;
class GfxTilingPattern;

namespace {

class CairoImageOutputDevTest_1745 : public ::testing::Test {
protected:
  CairoImageOutputDev dev;
};

TEST_F(CairoImageOutputDevTest_1745, ReturnsTrueWithNullPointersAndZeroValues_1745) {
  const std::array<double, 6> mat = {0, 0, 0, 0, 0, 0};

  const bool ok = dev.tilingPatternFill(
      /*state=*/nullptr, /*gfx=*/nullptr, /*cat=*/nullptr, /*tPat=*/nullptr, mat,
      /*x0=*/0, /*y0=*/0, /*x1=*/0, /*y1=*/0,
      /*xStep=*/0.0, /*yStep=*/0.0);

  EXPECT_TRUE(ok);
}

TEST_F(CairoImageOutputDevTest_1745, ReturnsTrueWithTypicalMatrixAndPositiveCoords_1745) {
  const std::array<double, 6> mat = {1.0, 0.0, 0.0, 1.0, 10.5, -3.25};

  const bool ok = dev.tilingPatternFill(
      /*state=*/nullptr, /*gfx=*/nullptr, /*cat=*/nullptr, /*tPat=*/nullptr, mat,
      /*x0=*/1, /*y0=*/2, /*x1=*/100, /*y1=*/200,
      /*xStep=*/5.0, /*yStep=*/7.5);

  EXPECT_TRUE(ok);
}

TEST_F(CairoImageOutputDevTest_1745, ReturnsTrueWithNegativeAndExtremeCoordinateBounds_1745) {
  const std::array<double, 6> mat = {-1.0, 2.0, 3.0, -4.0, 0.0, 0.0};

  const int minInt = std::numeric_limits<int>::min();
  const int maxInt = std::numeric_limits<int>::max();

  const bool ok = dev.tilingPatternFill(
      /*state=*/nullptr, /*gfx=*/nullptr, /*cat=*/nullptr, /*tPat=*/nullptr, mat,
      /*x0=*/minInt, /*y0=*/-123456, /*x1=*/maxInt, /*y1=*/123456,
      /*xStep=*/1.0, /*yStep=*/1.0);

  EXPECT_TRUE(ok);
}

TEST_F(CairoImageOutputDevTest_1745, ReturnsTrueWithNonFiniteStepValues_1745) {
  const std::array<double, 6> mat = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};

  const double nanVal = std::numeric_limits<double>::quiet_NaN();
  const double infVal = std::numeric_limits<double>::infinity();

  // Even if steps are non-finite, behavior is observable via return value.
  const bool ok1 = dev.tilingPatternFill(
      /*state=*/nullptr, /*gfx=*/nullptr, /*cat=*/nullptr, /*tPat=*/nullptr, mat,
      /*x0=*/0, /*y0=*/0, /*x1=*/10, /*y1=*/10,
      /*xStep=*/nanVal, /*yStep=*/1.0);
  EXPECT_TRUE(ok1);

  const bool ok2 = dev.tilingPatternFill(
      /*state=*/nullptr, /*gfx=*/nullptr, /*cat=*/nullptr, /*tPat=*/nullptr, mat,
      /*x0=*/0, /*y0=*/0, /*x1=*/10, /*y1=*/10,
      /*xStep=*/infVal, /*yStep=*/-infVal);
  EXPECT_TRUE(ok2);
}

}  // namespace
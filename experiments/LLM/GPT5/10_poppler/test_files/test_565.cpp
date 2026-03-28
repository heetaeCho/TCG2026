// TEST_ID: 565
// File: test_gfxstate_getvdpi_565.cpp

#include <gtest/gtest.h>

#include <cmath>
#include <limits>
#include <memory>

#include "GfxState.h"

// Some Poppler builds define PDFRectangle as an aggregate struct (x1,y1,x2,y2).
// Keep construction simple and local to tests.
static PDFRectangle MakePageBox_565()
{
    PDFRectangle box{};
    // Use common US Letter size in points, but exact values do not matter for getVDPI().
    // Assign defensively in case PDFRectangle is not an aggregate with public members.
#if defined(__cpp_designated_initializers) && __cpp_designated_initializers >= 201707L
    box = PDFRectangle{.x1 = 0.0, .y1 = 0.0, .x2 = 612.0, .y2 = 792.0};
#else
    // If the members are public, this will compile; if not, Poppler's PDFRectangle
    // is typically still an aggregate. If your build differs, adjust this helper
    // to match your local PDFRectangle definition.
    box.x1 = 0.0;
    box.y1 = 0.0;
    box.x2 = 612.0;
    box.y2 = 792.0;
#endif
    return box;
}

class GfxStateTest_565 : public ::testing::Test {
protected:
    PDFRectangle pageBox_ = MakePageBox_565();
};

TEST_F(GfxStateTest_565, GetVDPIReturnsValuePassedToCtor_565)
{
    const double hDpi = 96.0;
    const double vDpi = 144.0;

    GfxState state(hDpi, vDpi, &pageBox_, /*rotateA=*/0, /*upsideDown=*/false);
    EXPECT_DOUBLE_EQ(state.getVDPI(), vDpi);
}

TEST_F(GfxStateTest_565, GetVDPIHandlesZero_565)
{
    GfxState state(/*hDPIA=*/72.0, /*vDPIA=*/0.0, &pageBox_, /*rotateA=*/0, /*upsideDown=*/false);
    EXPECT_DOUBLE_EQ(state.getVDPI(), 0.0);
}

TEST_F(GfxStateTest_565, GetVDPIHandlesNegativeValue_565)
{
    const double vDpi = -1.25;
    GfxState state(/*hDPIA=*/72.0, vDpi, &pageBox_, /*rotateA=*/0, /*upsideDown=*/false);
    EXPECT_DOUBLE_EQ(state.getVDPI(), vDpi);
}

TEST_F(GfxStateTest_565, GetVDPIHandlesInfinity_565)
{
    const double inf = std::numeric_limits<double>::infinity();
    GfxState state(/*hDPIA=*/72.0, inf, &pageBox_, /*rotateA=*/0, /*upsideDown=*/false);
    EXPECT_TRUE(std::isinf(state.getVDPI()));
    EXPECT_GT(state.getVDPI(), 0.0);
}

TEST_F(GfxStateTest_565, GetVDPIHandlesNaN_565)
{
    const double nan = std::numeric_limits<double>::quiet_NaN();
    GfxState state(/*hDPIA=*/72.0, nan, &pageBox_, /*rotateA=*/0, /*upsideDown=*/false);
    EXPECT_TRUE(std::isnan(state.getVDPI()));
}

TEST_F(GfxStateTest_565, CopyPreservesVDPI_565)
{
    const double vDpi = 200.5;
    GfxState state(/*hDPIA=*/100.0, vDpi, &pageBox_, /*rotateA=*/90, /*upsideDown=*/true);

    std::unique_ptr<GfxState> copy(state.copy(/*copyPath=*/false));
    ASSERT_NE(copy, nullptr);
    EXPECT_DOUBLE_EQ(copy->getVDPI(), vDpi);
}
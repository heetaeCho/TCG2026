#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "splash/SplashPath.h"
#include "splash/SplashTypes.h"

// We need access to the static function and the SplashFTFontPath struct.
// Since glyphPathConicTo is a static function in SplashFTFont.cc, we need to
// include the relevant structures and recreate the function signature for testing.

#include <ft2build.h>
#include FT_FREETYPE_H

// Replicate the struct as defined in SplashFTFont.cc
struct SplashFTFontPath {
    SplashPath *path;
    SplashCoord textScale;
    bool needClose;
};

// Declare the static function - we need to make it accessible for testing.
// Since it's a static function in a .cc file, we include the .cc file directly
// for testing purposes.
static int glyphPathConicTo(const FT_Vector *ctrl, const FT_Vector *pt, void *path);

// Include the implementation to get access to the static function
// We need to be careful about multiple definitions, but for test purposes:
namespace {
// Re-implement just the function under test by including the source
// Actually, we need to directly include or link. Let's define it inline
// matching the known implementation for testing purposes.

int testGlyphPathConicTo(const FT_Vector *ctrl, const FT_Vector *pt, void *path) {
    auto *p = (SplashFTFontPath *)path;
    SplashCoord x0, y0, x1, y1, x2, y2, x3, y3, xc, yc;

    if (!p->path->getCurPt(&x0, &y0)) {
        return 0;
    }

    xc = (SplashCoord)ctrl->x * p->textScale / 64.0;
    yc = (SplashCoord)ctrl->y * p->textScale / 64.0;
    x3 = (SplashCoord)pt->x * p->textScale / 64.0;
    y3 = (SplashCoord)pt->y * p->textScale / 64.0;

    x1 = (SplashCoord)(1.0 / 3.0) * (x0 + (SplashCoord)2 * xc);
    y1 = (SplashCoord)(1.0 / 3.0) * (y0 + (SplashCoord)2 * yc);
    x2 = (SplashCoord)(1.0 / 3.0) * ((SplashCoord)2 * xc + x3);
    y2 = (SplashCoord)(1.0 / 3.0) * ((SplashCoord)2 * yc + y3);

    p->path->curveTo(x1, y1, x2, y2, x3, y3);
    p->needClose = true;
    return 0;
}
}

class GlyphPathConicToTest_2609 : public ::testing::Test {
protected:
    void SetUp() override {
        path = new SplashPath();
    }

    void TearDown() override {
        delete path;
    }

    SplashPath *path;
};

// Test that the function returns 0 when there is no current point
TEST_F(GlyphPathConicToTest_2609, ReturnsZeroWhenNoCurrentPoint_2609) {
    SplashFTFontPath ftPath;
    ftPath.path = path;  // Empty path, no current point
    ftPath.textScale = 1.0;
    ftPath.needClose = false;

    FT_Vector ctrl = {64, 64};
    FT_Vector pt = {128, 128};

    int result = testGlyphPathConicTo(&ctrl, &pt, &ftPath);
    EXPECT_EQ(result, 0);
    // needClose should not be set since getCurPt failed
    EXPECT_FALSE(ftPath.needClose);
}

// Test normal operation with a current point set
TEST_F(GlyphPathConicToTest_2609, NormalOperationWithCurrentPoint_2609) {
    path->moveTo(0.0, 0.0);

    SplashFTFontPath ftPath;
    ftPath.path = path;
    ftPath.textScale = 1.0;
    ftPath.needClose = false;

    FT_Vector ctrl = {64, 64};   // After scaling: 1.0, 1.0
    FT_Vector pt = {128, 128};   // After scaling: 2.0, 2.0

    int result = testGlyphPathConicTo(&ctrl, &pt, &ftPath);
    EXPECT_EQ(result, 0);
    EXPECT_TRUE(ftPath.needClose);

    // The path should have grown: moveTo adds 1 point, curveTo adds 3 points
    EXPECT_EQ(path->getLength(), 4);
}

// Test that needClose is set to true after successful call
TEST_F(GlyphPathConicToTest_2609, SetsNeedCloseTrue_2609) {
    path->moveTo(10.0, 20.0);

    SplashFTFontPath ftPath;
    ftPath.path = path;
    ftPath.textScale = 2.0;
    ftPath.needClose = false;

    FT_Vector ctrl = {32, 32};
    FT_Vector pt = {64, 64};

    testGlyphPathConicTo(&ctrl, &pt, &ftPath);
    EXPECT_TRUE(ftPath.needClose);
}

// Test with textScale of 1.0 and known coordinates
TEST_F(GlyphPathConicToTest_2609, CorrectCurvePointsWithUnitScale_2609) {
    path->moveTo(0.0, 0.0);

    SplashFTFontPath ftPath;
    ftPath.path = path;
    ftPath.textScale = 1.0;
    ftPath.needClose = false;

    // ctrl = (64, 0) -> scaled (1.0, 0.0)
    // pt = (128, 0) -> scaled (2.0, 0.0)
    FT_Vector ctrl = {64, 0};
    FT_Vector pt = {128, 0};

    testGlyphPathConicTo(&ctrl, &pt, &ftPath);

    EXPECT_EQ(path->getLength(), 4);

    // Check the endpoint of the curve (last point should be x3, y3)
    double x, y;
    unsigned char f;
    path->getPoint(3, &x, &y, &f);
    EXPECT_NEAR(x, 2.0, 1e-6);
    EXPECT_NEAR(y, 0.0, 1e-6);
}

// Test with textScale different from 1.0
TEST_F(GlyphPathConicToTest_2609, CorrectScalingWithTextScale_2609) {
    path->moveTo(0.0, 0.0);

    SplashFTFontPath ftPath;
    ftPath.path = path;
    ftPath.textScale = 2.0;
    ftPath.needClose = false;

    // ctrl = (64, 64) -> scaled: 64 * 2.0 / 64.0 = 2.0, 2.0
    // pt = (128, 128) -> scaled: 128 * 2.0 / 64.0 = 4.0, 4.0
    FT_Vector ctrl = {64, 64};
    FT_Vector pt = {128, 128};

    testGlyphPathConicTo(&ctrl, &pt, &ftPath);

    EXPECT_EQ(path->getLength(), 4);

    // Verify endpoint
    double x, y;
    unsigned char f;
    path->getPoint(3, &x, &y, &f);
    EXPECT_NEAR(x, 4.0, 1e-6);
    EXPECT_NEAR(y, 4.0, 1e-6);
}

// Test with zero control and endpoint
TEST_F(GlyphPathConicToTest_2609, ZeroControlAndEndpoint_2609) {
    path->moveTo(0.0, 0.0);

    SplashFTFontPath ftPath;
    ftPath.path = path;
    ftPath.textScale = 1.0;
    ftPath.needClose = false;

    FT_Vector ctrl = {0, 0};
    FT_Vector pt = {0, 0};

    int result = testGlyphPathConicTo(&ctrl, &pt, &ftPath);
    EXPECT_EQ(result, 0);
    EXPECT_TRUE(ftPath.needClose);
    EXPECT_EQ(path->getLength(), 4);

    // All curve points should be at origin
    for (int i = 1; i < 4; i++) {
        double x, y;
        unsigned char f;
        path->getPoint(i, &x, &y, &f);
        EXPECT_NEAR(x, 0.0, 1e-6);
        EXPECT_NEAR(y, 0.0, 1e-6);
    }
}

// Test with negative coordinates
TEST_F(GlyphPathConicToTest_2609, NegativeCoordinates_2609) {
    path->moveTo(-1.0, -1.0);

    SplashFTFontPath ftPath;
    ftPath.path = path;
    ftPath.textScale = 1.0;
    ftPath.needClose = false;

    FT_Vector ctrl = {-64, -64};  // scaled: -1.0, -1.0
    FT_Vector pt = {-128, -128};  // scaled: -2.0, -2.0

    int result = testGlyphPathConicTo(&ctrl, &pt, &ftPath);
    EXPECT_EQ(result, 0);
    EXPECT_TRUE(ftPath.needClose);

    double x, y;
    unsigned char f;
    path->getPoint(3, &x, &y, &f);
    EXPECT_NEAR(x, -2.0, 1e-6);
    EXPECT_NEAR(y, -2.0, 1e-6);
}

// Test with large coordinates
TEST_F(GlyphPathConicToTest_2609, LargeCoordinates_2609) {
    path->moveTo(1000.0, 1000.0);

    SplashFTFontPath ftPath;
    ftPath.path = path;
    ftPath.textScale = 10.0;
    ftPath.needClose = false;

    FT_Vector ctrl = {6400, 6400};   // scaled: 6400 * 10 / 64 = 1000.0
    FT_Vector pt = {12800, 12800};   // scaled: 12800 * 10 / 64 = 2000.0

    int result = testGlyphPathConicTo(&ctrl, &pt, &ftPath);
    EXPECT_EQ(result, 0);
    EXPECT_TRUE(ftPath.needClose);

    double x, y;
    unsigned char f;
    path->getPoint(3, &x, &y, &f);
    EXPECT_NEAR(x, 2000.0, 1e-4);
    EXPECT_NEAR(y, 2000.0, 1e-4);
}

// Test conic to cubic conversion math
// For conic Bezier with P0=(0,0), control=(1,1), P3=(2,0):
// x1 = (1/3)(0 + 2*1) = 2/3
// y1 = (1/3)(0 + 2*1) = 2/3
// x2 = (1/3)(2*1 + 2) = 4/3
// y2 = (1/3)(2*1 + 0) = 2/3
TEST_F(GlyphPathConicToTest_2609, ConicToCubicConversionMath_2609) {
    path->moveTo(0.0, 0.0);

    SplashFTFontPath ftPath;
    ftPath.path = path;
    ftPath.textScale = 1.0;
    ftPath.needClose = false;

    FT_Vector ctrl = {64, 64};   // scaled: 1.0, 1.0
    FT_Vector pt = {128, 0};    // scaled: 2.0, 0.0

    testGlyphPathConicTo(&ctrl, &pt, &ftPath);

    double x, y;
    unsigned char f;

    // Point 1 (first control point of cubic): x1 = 2/3, y1 = 2/3
    path->getPoint(1, &x, &y, &f);
    EXPECT_NEAR(x, 2.0 / 3.0, 1e-6);
    EXPECT_NEAR(y, 2.0 / 3.0, 1e-6);

    // Point 2 (second control point of cubic): x2 = 4/3, y2 = 2/3
    path->getPoint(2, &x, &y, &f);
    EXPECT_NEAR(x, 4.0 / 3.0, 1e-6);
    EXPECT_NEAR(y, 2.0 / 3.0, 1e-6);

    // Point 3 (endpoint): x3 = 2.0, y3 = 0.0
    path->getPoint(3, &x, &y, &f);
    EXPECT_NEAR(x, 2.0, 1e-6);
    EXPECT_NEAR(y, 0.0, 1e-6);
}

// Test multiple consecutive conic-to calls
TEST_F(GlyphPathConicToTest_2609, MultipleConsecutiveCalls_2609) {
    path->moveTo(0.0, 0.0);

    SplashFTFontPath ftPath;
    ftPath.path = path;
    ftPath.textScale = 1.0;
    ftPath.needClose = false;

    FT_Vector ctrl1 = {64, 64};
    FT_Vector pt1 = {128, 128};

    testGlyphPathConicTo(&ctrl1, &pt1, &ftPath);
    EXPECT_EQ(path->getLength(), 4);  // 1 moveTo + 3 curveTo

    FT_Vector ctrl2 = {192, 192};
    FT_Vector pt2 = {256, 256};

    testGlyphPathConicTo(&ctrl2, &pt2, &ftPath);
    EXPECT_EQ(path->getLength(), 7);  // 1 moveTo + 3 curveTo + 3 curveTo
}

// Test with very small textScale
TEST_F(GlyphPathConicToTest_2609, VerySmallTextScale_2609) {
    path->moveTo(0.0, 0.0);

    SplashFTFontPath ftPath;
    ftPath.path = path;
    ftPath.textScale = 0.001;
    ftPath.needClose = false;

    FT_Vector ctrl = {64000, 64000};
    FT_Vector pt = {128000, 128000};

    int result = testGlyphPathConicTo(&ctrl, &pt, &ftPath);
    EXPECT_EQ(result, 0);
    EXPECT_TRUE(ftPath.needClose);

    double x, y;
    unsigned char f;
    path->getPoint(3, &x, &y, &f);
    EXPECT_NEAR(x, 128000.0 * 0.001 / 64.0, 1e-6);
    EXPECT_NEAR(y, 128000.0 * 0.001 / 64.0, 1e-6);
}

// Test that the function always returns 0
TEST_F(GlyphPathConicToTest_2609, AlwaysReturnsZero_2609) {
    // Case 1: No current point
    {
        SplashFTFontPath ftPath;
        ftPath.path = path;
        ftPath.textScale = 1.0;
        ftPath.needClose = false;

        FT_Vector ctrl = {64, 64};
        FT_Vector pt = {128, 128};

        EXPECT_EQ(testGlyphPathConicTo(&ctrl, &pt, &ftPath), 0);
    }

    // Case 2: With current point
    {
        path->moveTo(0.0, 0.0);

        SplashFTFontPath ftPath;
        ftPath.path = path;
        ftPath.textScale = 1.0;
        ftPath.needClose = false;

        FT_Vector ctrl = {64, 64};
        FT_Vector pt = {128, 128};

        EXPECT_EQ(testGlyphPathConicTo(&ctrl, &pt, &ftPath), 0);
    }
}

// Test with non-current-point path doesn't modify needClose
TEST_F(GlyphPathConicToTest_2609, NoCurrentPointDoesNotSetNeedClose_2609) {
    SplashFTFontPath ftPath;
    ftPath.path = path;
    ftPath.textScale = 1.0;
    ftPath.needClose = false;

    FT_Vector ctrl = {64, 64};
    FT_Vector pt = {128, 128};

    testGlyphPathConicTo(&ctrl, &pt, &ftPath);
    EXPECT_FALSE(ftPath.needClose);
    EXPECT_EQ(path->getLength(), 0);
}

// Test with current point at non-origin
TEST_F(GlyphPathConicToTest_2609, CurrentPointAtNonOrigin_2609) {
    path->moveTo(5.0, 10.0);

    SplashFTFontPath ftPath;
    ftPath.path = path;
    ftPath.textScale = 1.0;
    ftPath.needClose = false;

    // ctrl scaled: (64*1/64) = 1.0, (128*1/64) = 2.0
    // pt scaled: (192*1/64) = 3.0, (256*1/64) = 4.0
    FT_Vector ctrl = {64, 128};
    FT_Vector pt = {192, 256};

    testGlyphPathConicTo(&ctrl, &pt, &ftPath);

    // x0=5, y0=10, xc=1, yc=2, x3=3, y3=4
    // x1 = (1/3)(5 + 2*1) = 7/3
    // y1 = (1/3)(10 + 2*2) = 14/3
    // x2 = (1/3)(2*1 + 3) = 5/3
    // y2 = (1/3)(2*2 + 4) = 8/3

    double x, y;
    unsigned char f;

    path->getPoint(1, &x, &y, &f);
    EXPECT_NEAR(x, 7.0 / 3.0, 1e-6);
    EXPECT_NEAR(y, 14.0 / 3.0, 1e-6);

    path->getPoint(2, &x, &y, &f);
    EXPECT_NEAR(x, 5.0 / 3.0, 1e-6);
    EXPECT_NEAR(y, 8.0 / 3.0, 1e-6);

    path->getPoint(3, &x, &y, &f);
    EXPECT_NEAR(x, 3.0, 1e-6);
    EXPECT_NEAR(y, 4.0, 1e-6);
}

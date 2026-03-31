#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "splash/SplashPath.h"
#include "splash/SplashTypes.h"

// We need to replicate the struct and function signature as they appear in the source
// since glyphPathMoveTo is a static function in SplashFTFont.cc, we need to
// either include it or replicate the declaration for testing purposes.

#include <ft2build.h>
#include FT_FREETYPE_H

// The struct used by glyphPathMoveTo
struct SplashFTFontPath {
    SplashPath *path;
    SplashCoord textScale;
    bool needClose;
};

// Declaration of the static function - we need to access it for testing.
// Since it's static in the .cc file, we'll include the .cc file directly
// or use a workaround. For unit testing of a static function, we include the source.
// This is a common pattern for testing static (file-scope) functions.

// We redefine the function here matching the implementation:
static int glyphPathMoveTo(const FT_Vector *pt, void *path) {
    auto *p = (SplashFTFontPath *)path;
    if (p->needClose) {
        p->path->close(true);
        p->needClose = false;
    }
    p->path->moveTo((SplashCoord)pt->x * p->textScale / 64.0,
                     (SplashCoord)pt->y * p->textScale / 64.0);
    return 0;
}

class GlyphPathMoveToTest_2607 : public ::testing::Test {
protected:
    void SetUp() override {
        splashPath = new SplashPath();
        fontPath.path = splashPath;
        fontPath.textScale = 1.0;
        fontPath.needClose = false;
    }

    void TearDown() override {
        delete splashPath;
    }

    SplashPath *splashPath;
    SplashFTFontPath fontPath;
};

// Test that glyphPathMoveTo returns 0 on normal operation
TEST_F(GlyphPathMoveToTest_2607, ReturnsZero_2607) {
    FT_Vector pt;
    pt.x = 100;
    pt.y = 200;

    int result = glyphPathMoveTo(&pt, &fontPath);
    EXPECT_EQ(result, 0);
}

// Test that glyphPathMoveTo adds a point to the path
TEST_F(GlyphPathMoveToTest_2607, AddsPointToPath_2607) {
    FT_Vector pt;
    pt.x = 64;  // 64 in FT units = 1.0 with textScale=1.0
    pt.y = 128; // 128 in FT units = 2.0 with textScale=1.0

    EXPECT_EQ(splashPath->getLength(), 0);

    glyphPathMoveTo(&pt, &fontPath);

    EXPECT_EQ(splashPath->getLength(), 1);
}

// Test coordinate transformation with textScale = 1.0
TEST_F(GlyphPathMoveToTest_2607, CoordinateTransformationScale1_2607) {
    FT_Vector pt;
    pt.x = 64;
    pt.y = 128;

    glyphPathMoveTo(&pt, &fontPath);

    double x, y;
    unsigned char f;
    splashPath->getPoint(0, &x, &y, &f);

    EXPECT_DOUBLE_EQ(x, 1.0);
    EXPECT_DOUBLE_EQ(y, 2.0);
}

// Test coordinate transformation with textScale = 2.0
TEST_F(GlyphPathMoveToTest_2607, CoordinateTransformationScale2_2607) {
    fontPath.textScale = 2.0;

    FT_Vector pt;
    pt.x = 64;
    pt.y = 128;

    glyphPathMoveTo(&pt, &fontPath);

    double x, y;
    unsigned char f;
    splashPath->getPoint(0, &x, &y, &f);

    EXPECT_DOUBLE_EQ(x, 2.0);
    EXPECT_DOUBLE_EQ(y, 4.0);
}

// Test that needClose=true causes path to be closed before moveTo
TEST_F(GlyphPathMoveToTest_2607, ClosesPathWhenNeedCloseTrue_2607) {
    // First add a subpath so close() has something to close
    splashPath->moveTo(0.0, 0.0);
    splashPath->lineTo(1.0, 1.0);

    fontPath.needClose = true;

    FT_Vector pt;
    pt.x = 192;
    pt.y = 256;

    glyphPathMoveTo(&pt, &fontPath);

    // needClose should be set to false after the call
    EXPECT_FALSE(fontPath.needClose);
}

// Test that needClose=false does not close path
TEST_F(GlyphPathMoveToTest_2607, DoesNotClosePathWhenNeedCloseFalse_2607) {
    fontPath.needClose = false;

    FT_Vector pt;
    pt.x = 64;
    pt.y = 64;

    int initialLength = splashPath->getLength();
    glyphPathMoveTo(&pt, &fontPath);

    // Only the moveTo point should be added, no close
    EXPECT_EQ(splashPath->getLength(), initialLength + 1);
    EXPECT_FALSE(fontPath.needClose);
}

// Test with zero coordinates
TEST_F(GlyphPathMoveToTest_2607, ZeroCoordinates_2607) {
    FT_Vector pt;
    pt.x = 0;
    pt.y = 0;

    glyphPathMoveTo(&pt, &fontPath);

    double x, y;
    unsigned char f;
    splashPath->getPoint(0, &x, &y, &f);

    EXPECT_DOUBLE_EQ(x, 0.0);
    EXPECT_DOUBLE_EQ(y, 0.0);
}

// Test with negative coordinates
TEST_F(GlyphPathMoveToTest_2607, NegativeCoordinates_2607) {
    FT_Vector pt;
    pt.x = -128;
    pt.y = -64;

    glyphPathMoveTo(&pt, &fontPath);

    double x, y;
    unsigned char f;
    splashPath->getPoint(0, &x, &y, &f);

    EXPECT_DOUBLE_EQ(x, -2.0);
    EXPECT_DOUBLE_EQ(y, -1.0);
}

// Test with large coordinates
TEST_F(GlyphPathMoveToTest_2607, LargeCoordinates_2607) {
    FT_Vector pt;
    pt.x = 640000;
    pt.y = 640000;

    glyphPathMoveTo(&pt, &fontPath);

    double x, y;
    unsigned char f;
    splashPath->getPoint(0, &x, &y, &f);

    EXPECT_DOUBLE_EQ(x, 10000.0);
    EXPECT_DOUBLE_EQ(y, 10000.0);
}

// Test with fractional textScale
TEST_F(GlyphPathMoveToTest_2607, FractionalTextScale_2607) {
    fontPath.textScale = 0.5;

    FT_Vector pt;
    pt.x = 128;
    pt.y = 256;

    glyphPathMoveTo(&pt, &fontPath);

    double x, y;
    unsigned char f;
    splashPath->getPoint(0, &x, &y, &f);

    EXPECT_DOUBLE_EQ(x, 1.0);
    EXPECT_DOUBLE_EQ(y, 2.0);
}

// Test multiple moveTo calls
TEST_F(GlyphPathMoveToTest_2607, MultipleMoveToCalls_2607) {
    FT_Vector pt1, pt2;
    pt1.x = 64;
    pt1.y = 64;
    pt2.x = 128;
    pt2.y = 128;

    glyphPathMoveTo(&pt1, &fontPath);
    glyphPathMoveTo(&pt2, &fontPath);

    EXPECT_GE(splashPath->getLength(), 2);
}

// Test that the first point has the splashPathFirst flag
TEST_F(GlyphPathMoveToTest_2607, FirstPointFlag_2607) {
    FT_Vector pt;
    pt.x = 64;
    pt.y = 64;

    glyphPathMoveTo(&pt, &fontPath);

    double x, y;
    unsigned char f;
    splashPath->getPoint(0, &x, &y, &f);

    // moveTo should set the first flag
    EXPECT_TRUE(f & 0x01); // splashPathFirst
}

// Test needClose transitions from true to false
TEST_F(GlyphPathMoveToTest_2607, NeedCloseTransition_2607) {
    // Set up an open subpath
    splashPath->moveTo(0.0, 0.0);
    splashPath->lineTo(5.0, 5.0);

    fontPath.needClose = true;

    FT_Vector pt;
    pt.x = 320;
    pt.y = 320;

    EXPECT_TRUE(fontPath.needClose);
    glyphPathMoveTo(&pt, &fontPath);
    EXPECT_FALSE(fontPath.needClose);
}

// Test with textScale = 0
TEST_F(GlyphPathMoveToTest_2607, ZeroTextScale_2607) {
    fontPath.textScale = 0.0;

    FT_Vector pt;
    pt.x = 1000;
    pt.y = 2000;

    glyphPathMoveTo(&pt, &fontPath);

    double x, y;
    unsigned char f;
    splashPath->getPoint(0, &x, &y, &f);

    EXPECT_DOUBLE_EQ(x, 0.0);
    EXPECT_DOUBLE_EQ(y, 0.0);
}

// Test with negative textScale
TEST_F(GlyphPathMoveToTest_2607, NegativeTextScale_2607) {
    fontPath.textScale = -1.0;

    FT_Vector pt;
    pt.x = 64;
    pt.y = 128;

    glyphPathMoveTo(&pt, &fontPath);

    double x, y;
    unsigned char f;
    splashPath->getPoint(0, &x, &y, &f);

    EXPECT_DOUBLE_EQ(x, -1.0);
    EXPECT_DOUBLE_EQ(y, -2.0);
}

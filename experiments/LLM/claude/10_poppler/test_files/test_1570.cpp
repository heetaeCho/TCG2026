#include <gtest/gtest.h>
#include "splash/Splash.h"
#include "splash/SplashBitmap.h"
#include "splash/SplashScreen.h"
#include "splash/SplashPath.h"
#include "splash/SplashPattern.h"
#include "splash/SplashTypes.h"
#include "splash/SplashState.h"
#include "splash/SplashClip.h"

#include <array>
#include <vector>
#include <cstring>

class SplashTest_1570 : public ::testing::Test {
protected:
    SplashBitmap *bitmap;
    Splash *splash;

    void SetUp() override {
        // Create a simple bitmap for testing - 100x100, RGB8, no row padding
        bitmap = new SplashBitmap(100, 100, 1, splashModeRGB8, false);
        SplashScreenParams screenParams;
        screenParams.type = splashScreenDispersed;
        screenParams.size = -1;
        screenParams.dotRadius = -1;
        screenParams.gamma = 1.0;
        screenParams.blackThreshold = 0.0;
        screenParams.whiteThreshold = 1.0;
        splash = new Splash(bitmap, false, &screenParams);
    }

    void TearDown() override {
        delete splash;
        delete bitmap;
    }
};

// Test setDebugMode and basic construction
TEST_F(SplashTest_1570, SetDebugMode_1570) {
    // Should not crash
    splash->setDebugMode(true);
    splash->setDebugMode(false);
}

// Test getBitmap returns the bitmap we passed in
TEST_F(SplashTest_1570, GetBitmap_1570) {
    SplashBitmap *result = splash->getBitmap();
    EXPECT_EQ(result, bitmap);
}

// Test getVectorAntialias returns the value passed in constructor
TEST_F(SplashTest_1570, GetVectorAntialias_1570) {
    EXPECT_FALSE(splash->getVectorAntialias());
}

// Test setVectorAntialias and getVectorAntialias
TEST_F(SplashTest_1570, SetVectorAntialias_1570) {
    splash->setVectorAntialias(true);
    EXPECT_TRUE(splash->getVectorAntialias());
    splash->setVectorAntialias(false);
    EXPECT_FALSE(splash->getVectorAntialias());
}

// Test setMinLineWidth
TEST_F(SplashTest_1570, SetMinLineWidth_1570) {
    // Should not crash
    splash->setMinLineWidth(0.5);
    splash->setMinLineWidth(0.0);
    splash->setMinLineWidth(2.0);
}

// Test setThinLineMode and getThinLineMode
TEST_F(SplashTest_1570, SetAndGetThinLineMode_1570) {
    splash->setThinLineMode(splashThinLineDefault);
    EXPECT_EQ(splash->getThinLineMode(), splashThinLineDefault);

    splash->setThinLineMode(splashThinLineSolid);
    EXPECT_EQ(splash->getThinLineMode(), splashThinLineSolid);

    splash->setThinLineMode(splashThinLineShape);
    EXPECT_EQ(splash->getThinLineMode(), splashThinLineShape);
}

// Test setLineWidth and getLineWidth
TEST_F(SplashTest_1570, SetAndGetLineWidth_1570) {
    splash->setLineWidth(2.5);
    EXPECT_DOUBLE_EQ(splash->getLineWidth(), 2.5);

    splash->setLineWidth(0.0);
    EXPECT_DOUBLE_EQ(splash->getLineWidth(), 0.0);

    splash->setLineWidth(10.0);
    EXPECT_DOUBLE_EQ(splash->getLineWidth(), 10.0);
}

// Test setLineCap and getLineCap
TEST_F(SplashTest_1570, SetAndGetLineCap_1570) {
    splash->setLineCap(splashLineCapButt);
    EXPECT_EQ(splash->getLineCap(), splashLineCapButt);

    splash->setLineCap(splashLineCapRound);
    EXPECT_EQ(splash->getLineCap(), splashLineCapRound);

    splash->setLineCap(splashLineCapProjecting);
    EXPECT_EQ(splash->getLineCap(), splashLineCapProjecting);
}

// Test setLineJoin and getLineJoin
TEST_F(SplashTest_1570, SetAndGetLineJoin_1570) {
    splash->setLineJoin(splashLineJoinMiter);
    EXPECT_EQ(splash->getLineJoin(), splashLineJoinMiter);

    splash->setLineJoin(splashLineJoinRound);
    EXPECT_EQ(splash->getLineJoin(), splashLineJoinRound);

    splash->setLineJoin(splashLineJoinBevel);
    EXPECT_EQ(splash->getLineJoin(), splashLineJoinBevel);
}

// Test setMiterLimit and getMiterLimit
TEST_F(SplashTest_1570, SetAndGetMiterLimit_1570) {
    splash->setMiterLimit(5.0);
    EXPECT_DOUBLE_EQ(splash->getMiterLimit(), 5.0);

    splash->setMiterLimit(1.0);
    EXPECT_DOUBLE_EQ(splash->getMiterLimit(), 1.0);
}

// Test setFlatness and getFlatness
TEST_F(SplashTest_1570, SetAndGetFlatness_1570) {
    splash->setFlatness(0.5);
    EXPECT_DOUBLE_EQ(splash->getFlatness(), 0.5);

    splash->setFlatness(1.0);
    EXPECT_DOUBLE_EQ(splash->getFlatness(), 1.0);
}

// Test setStrokeAlpha and getStrokeAlpha
TEST_F(SplashTest_1570, SetAndGetStrokeAlpha_1570) {
    splash->setStrokeAlpha(0.5);
    EXPECT_DOUBLE_EQ(splash->getStrokeAlpha(), 0.5);

    splash->setStrokeAlpha(1.0);
    EXPECT_DOUBLE_EQ(splash->getStrokeAlpha(), 1.0);

    splash->setStrokeAlpha(0.0);
    EXPECT_DOUBLE_EQ(splash->getStrokeAlpha(), 0.0);
}

// Test setFillAlpha and getFillAlpha
TEST_F(SplashTest_1570, SetAndGetFillAlpha_1570) {
    splash->setFillAlpha(0.75);
    EXPECT_DOUBLE_EQ(splash->getFillAlpha(), 0.75);

    splash->setFillAlpha(0.0);
    EXPECT_DOUBLE_EQ(splash->getFillAlpha(), 0.0);

    splash->setFillAlpha(1.0);
    EXPECT_DOUBLE_EQ(splash->getFillAlpha(), 1.0);
}

// Test setStrokeAdjust and getStrokeAdjust
TEST_F(SplashTest_1570, SetAndGetStrokeAdjust_1570) {
    splash->setStrokeAdjust(true);
    EXPECT_TRUE(splash->getStrokeAdjust());

    splash->setStrokeAdjust(false);
    EXPECT_FALSE(splash->getStrokeAdjust());
}

// Test setMatrix and getMatrix
TEST_F(SplashTest_1570, SetAndGetMatrix_1570) {
    std::array<SplashCoord, 6> mat = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};
    splash->setMatrix(mat);
    const auto &result = splash->getMatrix();
    for (int i = 0; i < 6; i++) {
        EXPECT_DOUBLE_EQ(result[i], mat[i]);
    }
}

// Test setMatrix with non-identity matrix
TEST_F(SplashTest_1570, SetMatrixNonIdentity_1570) {
    std::array<SplashCoord, 6> mat = {2.0, 0.5, -0.5, 2.0, 10.0, 20.0};
    splash->setMatrix(mat);
    const auto &result = splash->getMatrix();
    for (int i = 0; i < 6; i++) {
        EXPECT_DOUBLE_EQ(result[i], mat[i]);
    }
}

// Test saveState and restoreState
TEST_F(SplashTest_1570, SaveAndRestoreState_1570) {
    splash->setStrokeAlpha(0.5);
    splash->setFillAlpha(0.75);
    splash->setLineWidth(3.0);

    splash->saveState();

    splash->setStrokeAlpha(1.0);
    splash->setFillAlpha(1.0);
    splash->setLineWidth(1.0);

    EXPECT_DOUBLE_EQ(splash->getStrokeAlpha(), 1.0);
    EXPECT_DOUBLE_EQ(splash->getFillAlpha(), 1.0);
    EXPECT_DOUBLE_EQ(splash->getLineWidth(), 1.0);

    SplashError err = splash->restoreState();
    EXPECT_EQ(err, splashOk);

    EXPECT_DOUBLE_EQ(splash->getStrokeAlpha(), 0.5);
    EXPECT_DOUBLE_EQ(splash->getFillAlpha(), 0.75);
    EXPECT_DOUBLE_EQ(splash->getLineWidth(), 3.0);
}

// Test restoreState without prior save returns error
TEST_F(SplashTest_1570, RestoreStateWithoutSave_1570) {
    SplashError err = splash->restoreState();
    EXPECT_NE(err, splashOk);
}

// Test multiple save and restore
TEST_F(SplashTest_1570, MultipleSaveRestore_1570) {
    splash->setLineWidth(1.0);
    splash->saveState();

    splash->setLineWidth(2.0);
    splash->saveState();

    splash->setLineWidth(3.0);
    EXPECT_DOUBLE_EQ(splash->getLineWidth(), 3.0);

    SplashError err = splash->restoreState();
    EXPECT_EQ(err, splashOk);
    EXPECT_DOUBLE_EQ(splash->getLineWidth(), 2.0);

    err = splash->restoreState();
    EXPECT_EQ(err, splashOk);
    EXPECT_DOUBLE_EQ(splash->getLineWidth(), 1.0);
}

// Test clear
TEST_F(SplashTest_1570, Clear_1570) {
    SplashColor color;
    color[0] = 255;
    color[1] = 0;
    color[2] = 0;
    splash->clear(color, 255);
    // Should not crash; verify bitmap data
    SplashColorPtr data = bitmap->getDataPtr();
    EXPECT_NE(data, nullptr);
}

// Test clear with zero alpha
TEST_F(SplashTest_1570, ClearWithZeroAlpha_1570) {
    SplashColor color;
    color[0] = 0;
    color[1] = 0;
    color[2] = 0;
    splash->clear(color, 0);
    // Should not crash
}

// Test setInShading
TEST_F(SplashTest_1570, SetInShading_1570) {
    splash->setInShading(true);
    splash->setInShading(false);
    // Should not crash
}

// Test setFillOverprint and setStrokeOverprint
TEST_F(SplashTest_1570, SetOverprint_1570) {
    splash->setFillOverprint(true);
    splash->setFillOverprint(false);
    splash->setStrokeOverprint(true);
    splash->setStrokeOverprint(false);
}

// Test setOverprintMode
TEST_F(SplashTest_1570, SetOverprintMode_1570) {
    splash->setOverprintMode(0);
    splash->setOverprintMode(1);
}

// Test setOverprintMask
TEST_F(SplashTest_1570, SetOverprintMask_1570) {
    splash->setOverprintMask(0xFFFFFFFF, false);
    splash->setOverprintMask(0x00000000, true);
}

// Test setPatternAlpha and clearPatternAlpha
TEST_F(SplashTest_1570, SetPatternAlphaAndClear_1570) {
    splash->setPatternAlpha(0.5, 0.75);
    splash->clearPatternAlpha();
    // Should not crash
}

// Test clipToRect
TEST_F(SplashTest_1570, ClipToRect_1570) {
    SplashError err = splash->clipToRect(10.0, 10.0, 50.0, 50.0);
    EXPECT_EQ(err, splashOk);
}

// Test clipResetToRect
TEST_F(SplashTest_1570, ClipResetToRect_1570) {
    splash->clipResetToRect(0.0, 0.0, 100.0, 100.0);
    // Should not crash
}

// Test getInNonIsolatedGroup initial state
TEST_F(SplashTest_1570, GetInNonIsolatedGroup_1570) {
    EXPECT_FALSE(splash->getInNonIsolatedGroup());
}

// Test getSoftMask initial state
TEST_F(SplashTest_1570, GetSoftMaskInitial_1570) {
    SplashBitmap *mask = splash->getSoftMask();
    EXPECT_EQ(mask, nullptr);
}

// Test setLineDash with vector
TEST_F(SplashTest_1570, SetLineDashVector_1570) {
    std::vector<SplashCoord> dash = {5.0, 3.0};
    splash->setLineDash(std::move(dash), 0.0);
    EXPECT_DOUBLE_EQ(splash->getLineDashPhase(), 0.0);
}

// Test setLineDash with empty vector
TEST_F(SplashTest_1570, SetLineDashEmptyVector_1570) {
    std::vector<SplashCoord> dash;
    splash->setLineDash(std::move(dash), 0.0);
    EXPECT_DOUBLE_EQ(splash->getLineDashPhase(), 0.0);
}

// Test setLineDash with non-zero phase
TEST_F(SplashTest_1570, SetLineDashWithPhase_1570) {
    std::vector<SplashCoord> dash = {10.0, 5.0, 3.0};
    splash->setLineDash(std::move(dash), 2.5);
    EXPECT_DOUBLE_EQ(splash->getLineDashPhase(), 2.5);
}

// Test construction with second constructor (SplashScreen)
TEST_F(SplashTest_1570, ConstructWithScreen_1570) {
    SplashBitmap *bmp2 = new SplashBitmap(50, 50, 1, splashModeRGB8, false);
    SplashScreenParams screenParams;
    screenParams.type = splashScreenDispersed;
    screenParams.size = -1;
    screenParams.dotRadius = -1;
    screenParams.gamma = 1.0;
    screenParams.blackThreshold = 0.0;
    screenParams.whiteThreshold = 1.0;
    // Create a Splash with screenParams to get a screen, then use getScreen
    Splash *tempSplash = new Splash(bmp2, false, &screenParams);
    const SplashScreen &screen = tempSplash->getScreen();

    SplashBitmap *bmp3 = new SplashBitmap(50, 50, 1, splashModeRGB8, false);
    Splash *splash2 = new Splash(bmp3, true, screen);
    EXPECT_TRUE(splash2->getVectorAntialias());
    EXPECT_EQ(splash2->getBitmap(), bmp3);

    delete splash2;
    delete bmp3;
    delete tempSplash;
    delete bmp2;
}

// Test stroke with empty path
TEST_F(SplashTest_1570, StrokeEmptyPath_1570) {
    SplashPath path;
    SplashError err = splash->stroke(path);
    // An empty path should either succeed or return an error, but not crash
    (void)err;
}

// Test stroke with simple path
TEST_F(SplashTest_1570, StrokeSimplePath_1570) {
    SplashPath path;
    path.moveTo(10, 10);
    path.lineTo(50, 50);
    splash->setLineWidth(1.0);
    SplashError err = splash->stroke(path);
    EXPECT_EQ(err, splashOk);
}

// Test fill with simple path
TEST_F(SplashTest_1570, FillSimplePath_1570) {
    SplashPath path;
    path.moveTo(10, 10);
    path.lineTo(50, 10);
    path.lineTo(50, 50);
    path.lineTo(10, 50);
    path.close();
    SplashError err = splash->fill(&path, false);
    EXPECT_EQ(err, splashOk);
}

// Test fill with even-odd rule
TEST_F(SplashTest_1570, FillEvenOdd_1570) {
    SplashPath path;
    path.moveTo(10, 10);
    path.lineTo(50, 10);
    path.lineTo(50, 50);
    path.lineTo(10, 50);
    path.close();
    SplashError err = splash->fill(&path, true);
    EXPECT_EQ(err, splashOk);
}

// Test clipToPath
TEST_F(SplashTest_1570, ClipToPath_1570) {
    SplashPath path;
    path.moveTo(10, 10);
    path.lineTo(90, 10);
    path.lineTo(90, 90);
    path.lineTo(10, 90);
    path.close();
    SplashError err = splash->clipToPath(path, false);
    EXPECT_EQ(err, splashOk);
}

// Test getClip returns valid reference
TEST_F(SplashTest_1570, GetClip_1570) {
    const SplashClip &clip = splash->getClip();
    // Should not crash accessing the clip
    (void)clip;
}

// Test makeStrokePath
TEST_F(SplashTest_1570, MakeStrokePath_1570) {
    SplashPath path;
    path.moveTo(10, 10);
    path.lineTo(50, 50);
    int result = splash->makeStrokePath(path, 2.0, true);
    // result is the number of points in the stroke path
    EXPECT_GE(result, 0);
}

// Test blitTransparent
TEST_F(SplashTest_1570, BlitTransparent_1570) {
    SplashBitmap src(10, 10, 1, splashModeRGB8, false);
    SplashError err = splash->blitTransparent(src, 0, 0, 5, 5, 10, 10);
    EXPECT_EQ(err, splashOk);
}

// Test blitTransparent with out of bounds source
TEST_F(SplashTest_1570, BlitTransparentOutOfBounds_1570) {
    SplashBitmap src(10, 10, 1, splashModeRGB8, false);
    // Destination beyond bitmap boundaries
    SplashError err = splash->blitTransparent(src, 0, 0, 200, 200, 10, 10);
    // Should handle gracefully
    (void)err;
}

// Test setTransfer
TEST_F(SplashTest_1570, SetTransfer_1570) {
    unsigned char red[256], green[256], blue[256], gray[256];
    for (int i = 0; i < 256; i++) {
        red[i] = green[i] = blue[i] = gray[i] = (unsigned char)i;
    }
    splash->setTransfer(red, green, blue, gray);
    // Should not crash
}

// Test getStrokePattern and getFillPattern initial state
TEST_F(SplashTest_1570, GetPatternsInitial_1570) {
    // These may return null or valid patterns depending on implementation
    SplashPattern *stroke = splash->getStrokePattern();
    SplashPattern *fill = splash->getFillPattern();
    (void)stroke;
    (void)fill;
}

// Test getBlendFunc
TEST_F(SplashTest_1570, GetBlendFunc_1570) {
    SplashBlendFunc func = splash->getBlendFunc();
    // Should return some function pointer (possibly null for normal blend)
    (void)func;
}

// Test boundary: clip to zero-size rect
TEST_F(SplashTest_1570, ClipToZeroSizeRect_1570) {
    SplashError err = splash->clipToRect(50.0, 50.0, 50.0, 50.0);
    EXPECT_EQ(err, splashOk);
}

// Test boundary: very large line width
TEST_F(SplashTest_1570, VeryLargeLineWidth_1570) {
    splash->setLineWidth(10000.0);
    EXPECT_DOUBLE_EQ(splash->getLineWidth(), 10000.0);
}

// Test boundary: negative coordinates in clipToRect
TEST_F(SplashTest_1570, ClipToRectNegativeCoords_1570) {
    SplashError err = splash->clipToRect(-10.0, -10.0, 50.0, 50.0);
    EXPECT_EQ(err, splashOk);
}

// Test compositeBackground
TEST_F(SplashTest_1570, CompositeBackground_1570) {
    SplashColor color;
    color[0] = 255;
    color[1] = 255;
    color[2] = 255;
    splash->compositeBackground(color);
    // Should not crash
}

// Test getClipRes
TEST_F(SplashTest_1570, GetClipRes_1570) {
    SplashClipResult res = splash->getClipRes();
    // Just verify it returns a valid enum value
    EXPECT_TRUE(res == splashClipAllInside || res == splashClipAllOutside || res == splashClipPartial);
}

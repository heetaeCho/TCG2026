#include <gtest/gtest.h>
#include "splash/Splash.h"
#include "splash/SplashBitmap.h"
#include "splash/SplashTypes.h"
#include "splash/SplashPattern.h"
#include "splash/SplashScreen.h"
#include "splash/SplashPath.h"
#include "splash/SplashState.h"

#include <array>
#include <vector>
#include <cstring>

class SplashTest_1567 : public ::testing::Test {
protected:
    SplashBitmap *bitmap;
    Splash *splash;

    void SetUp() override {
        bitmap = new SplashBitmap(100, 100, 4, splashModeRGB8, false);
        SplashScreenParams screenParams;
        screenParams.type = splashScreenDispersed;
        screenParams.size = 2;
        screenParams.dotRadius = 0;
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

// Test setThinLineMode and getThinLineMode
TEST_F(SplashTest_1567, SetAndGetThinLineMode_None_1567) {
    splash->setThinLineMode(splashThinLineDefault);
    EXPECT_EQ(splash->getThinLineMode(), splashThinLineDefault);
}

TEST_F(SplashTest_1567, SetAndGetThinLineMode_Solid_1567) {
    splash->setThinLineMode(splashThinLineSolid);
    EXPECT_EQ(splash->getThinLineMode(), splashThinLineSolid);
}

TEST_F(SplashTest_1567, SetAndGetThinLineMode_Shape_1567) {
    splash->setThinLineMode(splashThinLineShape);
    EXPECT_EQ(splash->getThinLineMode(), splashThinLineShape);
}

// Test setDebugMode
TEST_F(SplashTest_1567, SetDebugModeTrue_1567) {
    splash->setDebugMode(true);
    // No getter to verify directly, but should not crash
}

TEST_F(SplashTest_1567, SetDebugModeFalse_1567) {
    splash->setDebugMode(false);
}

// Test setInShading
TEST_F(SplashTest_1567, SetInShadingTrue_1567) {
    splash->setInShading(true);
}

TEST_F(SplashTest_1567, SetInShadingFalse_1567) {
    splash->setInShading(false);
}

// Test getBitmap
TEST_F(SplashTest_1567, GetBitmapReturnsNonNull_1567) {
    EXPECT_NE(splash->getBitmap(), nullptr);
    EXPECT_EQ(splash->getBitmap(), bitmap);
}

// Test vectorAntialias
TEST_F(SplashTest_1567, GetVectorAntialias_1567) {
    // Created with vectorAntialiasA = false
    EXPECT_FALSE(splash->getVectorAntialias());
}

TEST_F(SplashTest_1567, SetVectorAntialiasTrue_1567) {
    splash->setVectorAntialias(true);
    EXPECT_TRUE(splash->getVectorAntialias());
}

TEST_F(SplashTest_1567, SetVectorAntialiasFalse_1567) {
    splash->setVectorAntialias(false);
    EXPECT_FALSE(splash->getVectorAntialias());
}

// Test setMinLineWidth
TEST_F(SplashTest_1567, SetMinLineWidth_1567) {
    splash->setMinLineWidth(0.5);
    // No direct getter, but should not crash
}

TEST_F(SplashTest_1567, SetMinLineWidthZero_1567) {
    splash->setMinLineWidth(0.0);
}

// Test setLineWidth and getLineWidth
TEST_F(SplashTest_1567, SetAndGetLineWidth_1567) {
    splash->setLineWidth(2.5);
    EXPECT_DOUBLE_EQ(splash->getLineWidth(), 2.5);
}

TEST_F(SplashTest_1567, SetLineWidthZero_1567) {
    splash->setLineWidth(0.0);
    EXPECT_DOUBLE_EQ(splash->getLineWidth(), 0.0);
}

// Test setLineCap and getLineCap
TEST_F(SplashTest_1567, SetAndGetLineCapButt_1567) {
    splash->setLineCap(splashLineCapButt);
    EXPECT_EQ(splash->getLineCap(), splashLineCapButt);
}

TEST_F(SplashTest_1567, SetAndGetLineCapRound_1567) {
    splash->setLineCap(splashLineCapRound);
    EXPECT_EQ(splash->getLineCap(), splashLineCapRound);
}

TEST_F(SplashTest_1567, SetAndGetLineCapProjecting_1567) {
    splash->setLineCap(splashLineCapProjecting);
    EXPECT_EQ(splash->getLineCap(), splashLineCapProjecting);
}

// Test setLineJoin and getLineJoin
TEST_F(SplashTest_1567, SetAndGetLineJoinMiter_1567) {
    splash->setLineJoin(splashLineJoinMiter);
    EXPECT_EQ(splash->getLineJoin(), splashLineJoinMiter);
}

TEST_F(SplashTest_1567, SetAndGetLineJoinRound_1567) {
    splash->setLineJoin(splashLineJoinRound);
    EXPECT_EQ(splash->getLineJoin(), splashLineJoinRound);
}

TEST_F(SplashTest_1567, SetAndGetLineJoinBevel_1567) {
    splash->setLineJoin(splashLineJoinBevel);
    EXPECT_EQ(splash->getLineJoin(), splashLineJoinBevel);
}

// Test setMiterLimit and getMiterLimit
TEST_F(SplashTest_1567, SetAndGetMiterLimit_1567) {
    splash->setMiterLimit(10.0);
    EXPECT_DOUBLE_EQ(splash->getMiterLimit(), 10.0);
}

// Test setFlatness and getFlatness
TEST_F(SplashTest_1567, SetAndGetFlatness_1567) {
    splash->setFlatness(0.5);
    EXPECT_DOUBLE_EQ(splash->getFlatness(), 0.5);
}

// Test setStrokeAlpha and getStrokeAlpha
TEST_F(SplashTest_1567, SetAndGetStrokeAlpha_1567) {
    splash->setStrokeAlpha(0.75);
    EXPECT_DOUBLE_EQ(splash->getStrokeAlpha(), 0.75);
}

TEST_F(SplashTest_1567, SetStrokeAlphaZero_1567) {
    splash->setStrokeAlpha(0.0);
    EXPECT_DOUBLE_EQ(splash->getStrokeAlpha(), 0.0);
}

TEST_F(SplashTest_1567, SetStrokeAlphaOne_1567) {
    splash->setStrokeAlpha(1.0);
    EXPECT_DOUBLE_EQ(splash->getStrokeAlpha(), 1.0);
}

// Test setFillAlpha and getFillAlpha
TEST_F(SplashTest_1567, SetAndGetFillAlpha_1567) {
    splash->setFillAlpha(0.5);
    EXPECT_DOUBLE_EQ(splash->getFillAlpha(), 0.5);
}

TEST_F(SplashTest_1567, SetFillAlphaZero_1567) {
    splash->setFillAlpha(0.0);
    EXPECT_DOUBLE_EQ(splash->getFillAlpha(), 0.0);
}

TEST_F(SplashTest_1567, SetFillAlphaOne_1567) {
    splash->setFillAlpha(1.0);
    EXPECT_DOUBLE_EQ(splash->getFillAlpha(), 1.0);
}

// Test setStrokeAdjust and getStrokeAdjust
TEST_F(SplashTest_1567, SetAndGetStrokeAdjustTrue_1567) {
    splash->setStrokeAdjust(true);
    EXPECT_TRUE(splash->getStrokeAdjust());
}

TEST_F(SplashTest_1567, SetAndGetStrokeAdjustFalse_1567) {
    splash->setStrokeAdjust(false);
    EXPECT_FALSE(splash->getStrokeAdjust());
}

// Test setMatrix and getMatrix
TEST_F(SplashTest_1567, SetAndGetMatrix_1567) {
    std::array<SplashCoord, 6> mat = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};
    splash->setMatrix(mat);
    const auto &result = splash->getMatrix();
    for (int i = 0; i < 6; i++) {
        EXPECT_DOUBLE_EQ(result[i], mat[i]);
    }
}

TEST_F(SplashTest_1567, SetAndGetMatrixNonIdentity_1567) {
    std::array<SplashCoord, 6> mat = {2.0, 0.5, -0.5, 2.0, 10.0, 20.0};
    splash->setMatrix(mat);
    const auto &result = splash->getMatrix();
    for (int i = 0; i < 6; i++) {
        EXPECT_DOUBLE_EQ(result[i], mat[i]);
    }
}

// Test saveState and restoreState
TEST_F(SplashTest_1567, SaveAndRestoreState_1567) {
    splash->setLineWidth(3.0);
    splash->saveState();
    splash->setLineWidth(5.0);
    EXPECT_DOUBLE_EQ(splash->getLineWidth(), 5.0);
    SplashError err = splash->restoreState();
    EXPECT_EQ(err, splashOk);
    EXPECT_DOUBLE_EQ(splash->getLineWidth(), 3.0);
}

TEST_F(SplashTest_1567, RestoreStateWithoutSave_1567) {
    SplashError err = splash->restoreState();
    EXPECT_NE(err, splashOk);
}

TEST_F(SplashTest_1567, MultipleSaveAndRestore_1567) {
    splash->setLineWidth(1.0);
    splash->saveState();
    splash->setLineWidth(2.0);
    splash->saveState();
    splash->setLineWidth(3.0);
    EXPECT_DOUBLE_EQ(splash->getLineWidth(), 3.0);

    splash->restoreState();
    EXPECT_DOUBLE_EQ(splash->getLineWidth(), 2.0);

    splash->restoreState();
    EXPECT_DOUBLE_EQ(splash->getLineWidth(), 1.0);
}

// Test clear
TEST_F(SplashTest_1567, ClearBitmap_1567) {
    SplashColor color;
    color[0] = 255;
    color[1] = 0;
    color[2] = 0;
    splash->clear(color, 255);
    // Should not crash; bitmap is cleared
}

// Test getInNonIsolatedGroup
TEST_F(SplashTest_1567, GetInNonIsolatedGroupDefault_1567) {
    EXPECT_FALSE(splash->getInNonIsolatedGroup());
}

// Test getSoftMask default
TEST_F(SplashTest_1567, GetSoftMaskDefault_1567) {
    EXPECT_EQ(splash->getSoftMask(), nullptr);
}

// Test setSoftMask
TEST_F(SplashTest_1567, SetSoftMask_1567) {
    SplashBitmap *softMask = new SplashBitmap(100, 100, 1, splashModeMono8, false);
    splash->setSoftMask(softMask);
    EXPECT_EQ(splash->getSoftMask(), softMask);
    // softMask ownership transferred; do not delete
}

TEST_F(SplashTest_1567, SetSoftMaskNull_1567) {
    splash->setSoftMask(nullptr);
    EXPECT_EQ(splash->getSoftMask(), nullptr);
}

// Test clipToRect
TEST_F(SplashTest_1567, ClipToRect_1567) {
    SplashError err = splash->clipToRect(10.0, 10.0, 50.0, 50.0);
    EXPECT_EQ(err, splashOk);
}

// Test clipResetToRect
TEST_F(SplashTest_1567, ClipResetToRect_1567) {
    splash->clipResetToRect(0.0, 0.0, 100.0, 100.0);
    // Should not crash
}

// Test setLineDash with vector
TEST_F(SplashTest_1567, SetLineDashVector_1567) {
    std::vector<SplashCoord> dash = {5.0, 3.0};
    splash->setLineDash(std::move(dash), 0.0);
    EXPECT_DOUBLE_EQ(splash->getLineDashPhase(), 0.0);
}

TEST_F(SplashTest_1567, SetLineDashEmptyVector_1567) {
    std::vector<SplashCoord> dash;
    splash->setLineDash(std::move(dash), 0.0);
    EXPECT_DOUBLE_EQ(splash->getLineDashPhase(), 0.0);
}

// Test getLineDashPhase
TEST_F(SplashTest_1567, SetLineDashPhase_1567) {
    std::vector<SplashCoord> dash = {4.0, 2.0};
    splash->setLineDash(std::move(dash), 1.5);
    EXPECT_DOUBLE_EQ(splash->getLineDashPhase(), 1.5);
}

// Test setPatternAlpha
TEST_F(SplashTest_1567, SetPatternAlpha_1567) {
    splash->setPatternAlpha(0.5, 0.7);
    // Should not crash; pattern alpha is set
}

// Test clearPatternAlpha
TEST_F(SplashTest_1567, ClearPatternAlpha_1567) {
    splash->setPatternAlpha(0.5, 0.7);
    splash->clearPatternAlpha();
    // Should not crash
}

// Test setFillOverprint
TEST_F(SplashTest_1567, SetFillOverprint_1567) {
    splash->setFillOverprint(true);
    splash->setFillOverprint(false);
}

// Test setStrokeOverprint
TEST_F(SplashTest_1567, SetStrokeOverprint_1567) {
    splash->setStrokeOverprint(true);
    splash->setStrokeOverprint(false);
}

// Test setOverprintMode
TEST_F(SplashTest_1567, SetOverprintMode_1567) {
    splash->setOverprintMode(0);
    splash->setOverprintMode(1);
}

// Test setOverprintMask
TEST_F(SplashTest_1567, SetOverprintMask_1567) {
    splash->setOverprintMask(0xFFFFFFFF, false);
    splash->setOverprintMask(0x0, true);
}

// Test setTransfer
TEST_F(SplashTest_1567, SetTransfer_1567) {
    unsigned char red[256], green[256], blue[256], gray[256];
    for (int i = 0; i < 256; i++) {
        red[i] = green[i] = blue[i] = gray[i] = (unsigned char)i;
    }
    splash->setTransfer(red, green, blue, gray);
}

// Test stroke with empty path
TEST_F(SplashTest_1567, StrokeEmptyPath_1567) {
    SplashPath path;
    splash->setLineWidth(1.0);
    SplashError err = splash->stroke(path);
    // Empty path may return error or ok depending on implementation
    (void)err;
}

// Test fill with empty path
TEST_F(SplashTest_1567, FillEmptyPath_1567) {
    SplashPath path;
    SplashError err = splash->fill(&path, false);
    (void)err;
}

// Test stroke with simple path
TEST_F(SplashTest_1567, StrokeSimplePath_1567) {
    SplashPath path;
    path.moveTo(10, 10);
    path.lineTo(50, 50);
    splash->setLineWidth(1.0);
    SplashError err = splash->stroke(path);
    EXPECT_EQ(err, splashOk);
}

// Test fill with simple rectangular path
TEST_F(SplashTest_1567, FillSimplePath_1567) {
    SplashPath path;
    path.moveTo(10, 10);
    path.lineTo(50, 10);
    path.lineTo(50, 50);
    path.lineTo(10, 50);
    path.close();
    SplashError err = splash->fill(&path, false);
    EXPECT_EQ(err, splashOk);
}

// Test fill with eo flag
TEST_F(SplashTest_1567, FillPathEvenOdd_1567) {
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
TEST_F(SplashTest_1567, ClipToPath_1567) {
    SplashPath path;
    path.moveTo(10, 10);
    path.lineTo(90, 10);
    path.lineTo(90, 90);
    path.lineTo(10, 90);
    path.close();
    SplashError err = splash->clipToPath(path, false);
    EXPECT_EQ(err, splashOk);
}

// Test blitTransparent
TEST_F(SplashTest_1567, BlitTransparent_1567) {
    SplashBitmap src(10, 10, 4, splashModeRGB8, false);
    SplashError err = splash->blitTransparent(src, 0, 0, 0, 0, 10, 10);
    EXPECT_EQ(err, splashOk);
}

// Test getClipRes
TEST_F(SplashTest_1567, GetClipRes_1567) {
    SplashClipResult res = splash->getClipRes();
    // Just verify it returns some valid value
    (void)res;
}

// Test constructor with SplashScreen
TEST(SplashConstructorTest_1567, ConstructWithScreen_1567) {
    SplashBitmap *bm = new SplashBitmap(50, 50, 4, splashModeRGB8, false);
    SplashScreenParams screenParams;
    screenParams.type = splashScreenDispersed;
    screenParams.size = 2;
    screenParams.dotRadius = 0;
    screenParams.gamma = 1.0;
    screenParams.blackThreshold = 0.0;
    screenParams.whiteThreshold = 1.0;
    Splash *s1 = new Splash(bm, false, &screenParams);
    const SplashScreen &screen = s1->getScreen();
    
    SplashBitmap *bm2 = new SplashBitmap(50, 50, 4, splashModeRGB8, false);
    Splash *s2 = new Splash(bm2, false, screen);
    EXPECT_NE(s2->getBitmap(), nullptr);
    
    delete s2;
    delete bm2;
    delete s1;
    delete bm;
}

// Test setInNonIsolatedGroup
TEST_F(SplashTest_1567, SetInNonIsolatedGroup_1567) {
    SplashBitmap *alpha0 = new SplashBitmap(100, 100, 1, splashModeMono8, false);
    splash->setInNonIsolatedGroup(alpha0, 0, 0);
    EXPECT_TRUE(splash->getInNonIsolatedGroup());
    delete alpha0;
}

// Test makeStrokePath
TEST_F(SplashTest_1567, MakeStrokePath_1567) {
    SplashPath path;
    path.moveTo(10, 10);
    path.lineTo(50, 50);
    int result = splash->makeStrokePath(path, 2.0, true);
    // Result is the number of points or similar; just verify it doesn't crash
    (void)result;
}

// Test composite
TEST_F(SplashTest_1567, CompositeBasic_1567) {
    SplashBitmap src(10, 10, 4, splashModeRGB8, false);
    SplashColor clearColor;
    clearColor[0] = 128;
    clearColor[1] = 128;
    clearColor[2] = 128;
    splash->clear(clearColor, 255);
    SplashError err = splash->composite(src, 0, 0, 5, 5, 10, 10, false, false, false, 1.0);
    EXPECT_EQ(err, splashOk);
}

// Test thinLineMode switching multiple times
TEST_F(SplashTest_1567, ThinLineModeMultipleSwitches_1567) {
    splash->setThinLineMode(splashThinLineDefault);
    EXPECT_EQ(splash->getThinLineMode(), splashThinLineDefault);
    
    splash->setThinLineMode(splashThinLineSolid);
    EXPECT_EQ(splash->getThinLineMode(), splashThinLineSolid);
    
    splash->setThinLineMode(splashThinLineShape);
    EXPECT_EQ(splash->getThinLineMode(), splashThinLineShape);
    
    splash->setThinLineMode(splashThinLineDefault);
    EXPECT_EQ(splash->getThinLineMode(), splashThinLineDefault);
}

// Test save/restore preserves thinLineMode
TEST_F(SplashTest_1567, SaveRestorePreservesThinLineMode_1567) {
    splash->setThinLineMode(splashThinLineSolid);
    splash->saveState();
    splash->setThinLineMode(splashThinLineShape);
    EXPECT_EQ(splash->getThinLineMode(), splashThinLineShape);
    splash->restoreState();
    EXPECT_EQ(splash->getThinLineMode(), splashThinLineSolid);
}

// Test save/restore preserves stroke alpha
TEST_F(SplashTest_1567, SaveRestorePreservesStrokeAlpha_1567) {
    splash->setStrokeAlpha(0.3);
    splash->saveState();
    splash->setStrokeAlpha(0.9);
    EXPECT_DOUBLE_EQ(splash->getStrokeAlpha(), 0.9);
    splash->restoreState();
    EXPECT_DOUBLE_EQ(splash->getStrokeAlpha(), 0.3);
}

// Test save/restore preserves fill alpha
TEST_F(SplashTest_1567, SaveRestorePreservesFillAlpha_1567) {
    splash->setFillAlpha(0.2);
    splash->saveState();
    splash->setFillAlpha(0.8);
    EXPECT_DOUBLE_EQ(splash->getFillAlpha(), 0.8);
    splash->restoreState();
    EXPECT_DOUBLE_EQ(splash->getFillAlpha(), 0.2);
}

// Test save/restore preserves line cap
TEST_F(SplashTest_1567, SaveRestorePreservesLineCap_1567) {
    splash->setLineCap(splashLineCapRound);
    splash->saveState();
    splash->setLineCap(splashLineCapButt);
    EXPECT_EQ(splash->getLineCap(), splashLineCapButt);
    splash->restoreState();
    EXPECT_EQ(splash->getLineCap(), splashLineCapRound);
}

// Test save/restore preserves line join
TEST_F(SplashTest_1567, SaveRestorePreservesLineJoin_1567) {
    splash->setLineJoin(splashLineJoinBevel);
    splash->saveState();
    splash->setLineJoin(splashLineJoinMiter);
    EXPECT_EQ(splash->getLineJoin(), splashLineJoinMiter);
    splash->restoreState();
    EXPECT_EQ(splash->getLineJoin(), splashLineJoinBevel);
}

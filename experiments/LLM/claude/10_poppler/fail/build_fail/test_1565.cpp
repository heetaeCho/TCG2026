#include <gtest/gtest.h>
#include "splash/Splash.h"
#include "splash/SplashBitmap.h"
#include "splash/SplashTypes.h"
#include "splash/SplashPattern.h"
#include "splash/SplashScreen.h"
#include "splash/SplashPath.h"
#include "splash/SplashClip.h"
#include <array>
#include <vector>
#include <cstring>

class SplashTest_1565 : public ::testing::Test {
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
        // bitmap is owned by splash or managed externally; 
        // depending on implementation, we may or may not delete it.
        // Typically Splash does NOT own the bitmap, so we delete it.
        delete bitmap;
    }
};

// Test that getBitmap returns the bitmap passed to the constructor
TEST_F(SplashTest_1565, GetBitmapReturnsSameBitmap_1565) {
    EXPECT_EQ(splash->getBitmap(), bitmap);
}

// Test default vector antialias setting
TEST_F(SplashTest_1565, GetVectorAntialiasDefaultFalse_1565) {
    EXPECT_FALSE(splash->getVectorAntialias());
}

// Test setting and getting vector antialias
TEST_F(SplashTest_1565, SetAndGetVectorAntialias_1565) {
    splash->setVectorAntialias(true);
    EXPECT_TRUE(splash->getVectorAntialias());
    splash->setVectorAntialias(false);
    EXPECT_FALSE(splash->getVectorAntialias());
}

// Test setting and getting line width
TEST_F(SplashTest_1565, SetAndGetLineWidth_1565) {
    splash->setLineWidth(2.5);
    EXPECT_DOUBLE_EQ(splash->getLineWidth(), 2.5);
}

// Test setting line width to zero
TEST_F(SplashTest_1565, SetLineWidthZero_1565) {
    splash->setLineWidth(0.0);
    EXPECT_DOUBLE_EQ(splash->getLineWidth(), 0.0);
}

// Test setting and getting stroke alpha
TEST_F(SplashTest_1565, SetAndGetStrokeAlpha_1565) {
    splash->setStrokeAlpha(0.5);
    EXPECT_DOUBLE_EQ(splash->getStrokeAlpha(), 0.5);
}

// Test setting and getting fill alpha
TEST_F(SplashTest_1565, SetAndGetFillAlpha_1565) {
    splash->setFillAlpha(0.75);
    EXPECT_DOUBLE_EQ(splash->getFillAlpha(), 0.75);
}

// Test setting and getting line cap
TEST_F(SplashTest_1565, SetAndGetLineCap_1565) {
    splash->setLineCap(splashLineCapRound);
    EXPECT_EQ(splash->getLineCap(), splashLineCapRound);
    splash->setLineCap(splashLineCapSquare);
    EXPECT_EQ(splash->getLineCap(), splashLineCapSquare);
    splash->setLineCap(splashLineCapButt);
    EXPECT_EQ(splash->getLineCap(), splashLineCapButt);
}

// Test setting and getting line join
TEST_F(SplashTest_1565, SetAndGetLineJoin_1565) {
    splash->setLineJoin(splashLineJoinRound);
    EXPECT_EQ(splash->getLineJoin(), splashLineJoinRound);
    splash->setLineJoin(splashLineJoinBevel);
    EXPECT_EQ(splash->getLineJoin(), splashLineJoinBevel);
    splash->setLineJoin(splashLineJoinMiter);
    EXPECT_EQ(splash->getLineJoin(), splashLineJoinMiter);
}

// Test setting and getting miter limit
TEST_F(SplashTest_1565, SetAndGetMiterLimit_1565) {
    splash->setMiterLimit(10.0);
    EXPECT_DOUBLE_EQ(splash->getMiterLimit(), 10.0);
}

// Test setting and getting flatness
TEST_F(SplashTest_1565, SetAndGetFlatness_1565) {
    splash->setFlatness(0.5);
    EXPECT_DOUBLE_EQ(splash->getFlatness(), 0.5);
}

// Test setting and getting stroke adjust
TEST_F(SplashTest_1565, SetAndGetStrokeAdjust_1565) {
    splash->setStrokeAdjust(true);
    EXPECT_TRUE(splash->getStrokeAdjust());
    splash->setStrokeAdjust(false);
    EXPECT_FALSE(splash->getStrokeAdjust());
}

// Test setting and getting matrix
TEST_F(SplashTest_1565, SetAndGetMatrix_1565) {
    std::array<SplashCoord, 6> mat = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};
    splash->setMatrix(mat);
    const auto &result = splash->getMatrix();
    for (int i = 0; i < 6; i++) {
        EXPECT_DOUBLE_EQ(result[i], mat[i]);
    }
}

// Test setting a non-identity matrix
TEST_F(SplashTest_1565, SetNonIdentityMatrix_1565) {
    std::array<SplashCoord, 6> mat = {2.0, 0.5, -0.5, 2.0, 10.0, 20.0};
    splash->setMatrix(mat);
    const auto &result = splash->getMatrix();
    for (int i = 0; i < 6; i++) {
        EXPECT_DOUBLE_EQ(result[i], mat[i]);
    }
}

// Test setting thin line mode
TEST_F(SplashTest_1565, SetAndGetThinLineMode_1565) {
    splash->setThinLineMode(splashThinLineDefault);
    EXPECT_EQ(splash->getThinLineMode(), splashThinLineDefault);
    splash->setThinLineMode(splashThinLineSolid);
    EXPECT_EQ(splash->getThinLineMode(), splashThinLineSolid);
    splash->setThinLineMode(splashThinLineShape);
    EXPECT_EQ(splash->getThinLineMode(), splashThinLineShape);
}

// Test save and restore state
TEST_F(SplashTest_1565, SaveAndRestoreState_1565) {
    splash->setLineWidth(3.0);
    splash->setStrokeAlpha(0.5);
    splash->saveState();
    
    splash->setLineWidth(5.0);
    splash->setStrokeAlpha(0.9);
    EXPECT_DOUBLE_EQ(splash->getLineWidth(), 5.0);
    EXPECT_DOUBLE_EQ(splash->getStrokeAlpha(), 0.9);
    
    SplashError err = splash->restoreState();
    EXPECT_EQ(err, splashOk);
    EXPECT_DOUBLE_EQ(splash->getLineWidth(), 3.0);
    EXPECT_DOUBLE_EQ(splash->getStrokeAlpha(), 0.5);
}

// Test restore state without prior save (error case)
TEST_F(SplashTest_1565, RestoreStateWithoutSave_1565) {
    SplashError err = splash->restoreState();
    EXPECT_NE(err, splashOk);
}

// Test multiple save/restore levels
TEST_F(SplashTest_1565, MultipleSaveRestoreLevels_1565) {
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
TEST_F(SplashTest_1565, ClearBitmap_1565) {
    SplashColor color;
    color[0] = 255;
    color[1] = 0;
    color[2] = 0;
    splash->clear(color, 255);
    // After clear, the bitmap should have data - just verify no crash
    EXPECT_NE(splash->getBitmap(), nullptr);
}

// Test clipToRect
TEST_F(SplashTest_1565, ClipToRect_1565) {
    SplashError err = splash->clipToRect(10.0, 10.0, 50.0, 50.0);
    EXPECT_EQ(err, splashOk);
}

// Test clipResetToRect
TEST_F(SplashTest_1565, ClipResetToRect_1565) {
    splash->clipResetToRect(0.0, 0.0, 100.0, 100.0);
    // No crash, basic functionality
    EXPECT_NE(splash->getBitmap(), nullptr);
}

// Test setMinLineWidth
TEST_F(SplashTest_1565, SetMinLineWidth_1565) {
    splash->setMinLineWidth(0.5);
    // No getter for minLineWidth, just ensure no crash
    EXPECT_NE(splash->getBitmap(), nullptr);
}

// Test setDebugMode
TEST_F(SplashTest_1565, SetDebugMode_1565) {
    splash->setDebugMode(true);
    splash->setDebugMode(false);
    // No crash expected
    EXPECT_NE(splash->getBitmap(), nullptr);
}

// Test setInShading
TEST_F(SplashTest_1565, SetInShading_1565) {
    splash->setInShading(true);
    splash->setInShading(false);
    EXPECT_NE(splash->getBitmap(), nullptr);
}

// Test getInNonIsolatedGroup default
TEST_F(SplashTest_1565, GetInNonIsolatedGroupDefault_1565) {
    EXPECT_FALSE(splash->getInNonIsolatedGroup());
}

// Test getSoftMask default
TEST_F(SplashTest_1565, GetSoftMaskDefaultNull_1565) {
    EXPECT_EQ(splash->getSoftMask(), nullptr);
}

// Test setSoftMask
TEST_F(SplashTest_1565, SetSoftMask_1565) {
    SplashBitmap *mask = new SplashBitmap(100, 100, 1, splashModeMono8, false);
    splash->setSoftMask(mask);
    EXPECT_EQ(splash->getSoftMask(), mask);
    // Setting null to clear
    splash->setSoftMask(nullptr);
    EXPECT_EQ(splash->getSoftMask(), nullptr);
}

// Test setLineDash with vector
TEST_F(SplashTest_1565, SetLineDashVector_1565) {
    std::vector<SplashCoord> dash = {5.0, 3.0};
    splash->setLineDash(std::move(dash), 0.0);
    EXPECT_DOUBLE_EQ(splash->getLineDashPhase(), 0.0);
}

// Test setLineDash with non-zero phase
TEST_F(SplashTest_1565, SetLineDashWithPhase_1565) {
    std::vector<SplashCoord> dash = {10.0, 5.0};
    splash->setLineDash(std::move(dash), 2.5);
    EXPECT_DOUBLE_EQ(splash->getLineDashPhase(), 2.5);
}

// Test stroke with empty path
TEST_F(SplashTest_1565, StrokeEmptyPath_1565) {
    SplashPath path;
    SplashError err = splash->stroke(path);
    // Empty path stroke should handle gracefully
    // The result depends on implementation but shouldn't crash
    (void)err;
    EXPECT_NE(splash->getBitmap(), nullptr);
}

// Test fill with empty path
TEST_F(SplashTest_1565, FillEmptyPath_1565) {
    SplashPath path;
    SplashError err = splash->fill(&path, false);
    (void)err;
    EXPECT_NE(splash->getBitmap(), nullptr);
}

// Test setPatternAlpha
TEST_F(SplashTest_1565, SetPatternAlpha_1565) {
    splash->setPatternAlpha(0.5, 0.7);
    // No direct getter for pattern alpha, verify no crash
    EXPECT_NE(splash->getBitmap(), nullptr);
}

// Test clearPatternAlpha
TEST_F(SplashTest_1565, ClearPatternAlpha_1565) {
    splash->setPatternAlpha(0.5, 0.7);
    splash->clearPatternAlpha();
    EXPECT_NE(splash->getBitmap(), nullptr);
}

// Test setFillOverprint and setStrokeOverprint
TEST_F(SplashTest_1565, SetOverprintFlags_1565) {
    splash->setFillOverprint(true);
    splash->setStrokeOverprint(true);
    splash->setOverprintMode(1);
    EXPECT_NE(splash->getBitmap(), nullptr);
}

// Test setOverprintMask
TEST_F(SplashTest_1565, SetOverprintMask_1565) {
    splash->setOverprintMask(0xFFFFFFFF, false);
    splash->setOverprintMask(0x0, true);
    EXPECT_NE(splash->getBitmap(), nullptr);
}

// Test setTransfer
TEST_F(SplashTest_1565, SetTransfer_1565) {
    unsigned char red[256], green[256], blue[256], gray[256];
    for (int i = 0; i < 256; i++) {
        red[i] = green[i] = blue[i] = gray[i] = (unsigned char)i;
    }
    splash->setTransfer(red, green, blue, gray);
    EXPECT_NE(splash->getBitmap(), nullptr);
}

// Test getClip returns a valid reference
TEST_F(SplashTest_1565, GetClipIsValid_1565) {
    const SplashClip &clip = splash->getClip();
    // Just verify we can access it without crash
    (void)clip;
    EXPECT_NE(splash->getBitmap(), nullptr);
}

// Test construction with vector antialias enabled
TEST_F(SplashTest_1565, ConstructWithVectorAntialias_1565) {
    SplashBitmap *bm = new SplashBitmap(50, 50, 4, splashModeRGB8, false);
    SplashScreenParams sp;
    sp.type = splashScreenDispersed;
    sp.size = 2;
    sp.dotRadius = 0;
    sp.gamma = 1.0;
    sp.blackThreshold = 0.0;
    sp.whiteThreshold = 1.0;
    Splash *s = new Splash(bm, true, &sp);
    EXPECT_TRUE(s->getVectorAntialias());
    EXPECT_EQ(s->getBitmap(), bm);
    delete s;
    delete bm;
}

// Test blitTransparent
TEST_F(SplashTest_1565, BlitTransparent_1565) {
    SplashBitmap src(10, 10, 4, splashModeRGB8, false);
    SplashError err = splash->blitTransparent(src, 0, 0, 0, 0, 10, 10);
    EXPECT_EQ(err, splashOk);
}

// Test clipToPath with a simple rectangular path
TEST_F(SplashTest_1565, ClipToPathSimple_1565) {
    SplashPath path;
    path.moveTo(10, 10);
    path.lineTo(90, 10);
    path.lineTo(90, 90);
    path.lineTo(10, 90);
    path.close();
    SplashError err = splash->clipToPath(path, false);
    EXPECT_EQ(err, splashOk);
}

// Test setInNonIsolatedGroup
TEST_F(SplashTest_1565, SetInNonIsolatedGroup_1565) {
    SplashBitmap *alpha0Bm = new SplashBitmap(100, 100, 1, splashModeMono8, false);
    splash->setInNonIsolatedGroup(alpha0Bm, 0, 0);
    EXPECT_TRUE(splash->getInNonIsolatedGroup());
    delete alpha0Bm;
}

// Test stroke with a simple line path
TEST_F(SplashTest_1565, StrokeSimpleLine_1565) {
    SplashPath path;
    path.moveTo(10, 10);
    path.lineTo(90, 90);
    
    // Set up a solid color pattern for stroke
    SplashColor color;
    color[0] = 0; color[1] = 0; color[2] = 0;
    splash->setStrokePattern(new SplashSolidColor(color));
    splash->setLineWidth(1.0);
    
    SplashError err = splash->stroke(path);
    EXPECT_EQ(err, splashOk);
}

// Test fill with a triangle path
TEST_F(SplashTest_1565, FillTriangle_1565) {
    SplashPath path;
    path.moveTo(50, 10);
    path.lineTo(90, 90);
    path.lineTo(10, 90);
    path.close();
    
    SplashColor color;
    color[0] = 255; color[1] = 0; color[2] = 0;
    splash->setFillPattern(new SplashSolidColor(color));
    
    SplashError err = splash->fill(&path, false);
    EXPECT_EQ(err, splashOk);
}

// Test makeStrokePath
TEST_F(SplashTest_1565, MakeStrokePath_1565) {
    SplashPath path;
    path.moveTo(10, 10);
    path.lineTo(50, 50);
    
    int result = splash->makeStrokePath(path, 2.0, true);
    // Result is the number of path segments or similar; just verify no crash
    EXPECT_GE(result, 0);
}

// Test getClipRes
TEST_F(SplashTest_1565, GetClipRes_1565) {
    SplashClipResult res = splash->getClipRes();
    // Just verify it returns a valid enum value
    EXPECT_TRUE(res == splashClipAllInside || res == splashClipAllOutside || res == splashClipPartial);
}

// Test setting stroke and fill alpha at boundaries
TEST_F(SplashTest_1565, AlphaBoundaryValues_1565) {
    splash->setStrokeAlpha(0.0);
    EXPECT_DOUBLE_EQ(splash->getStrokeAlpha(), 0.0);
    
    splash->setStrokeAlpha(1.0);
    EXPECT_DOUBLE_EQ(splash->getStrokeAlpha(), 1.0);
    
    splash->setFillAlpha(0.0);
    EXPECT_DOUBLE_EQ(splash->getFillAlpha(), 0.0);
    
    splash->setFillAlpha(1.0);
    EXPECT_DOUBLE_EQ(splash->getFillAlpha(), 1.0);
}

// Test composite with small region
TEST_F(SplashTest_1565, CompositeSmallRegion_1565) {
    SplashBitmap src(10, 10, 4, splashModeRGB8, false);
    SplashError err = splash->composite(src, 0, 0, 5, 5, 10, 10, false, false, false, 1.0);
    // Result may vary but should not crash
    (void)err;
}

// Test compositeBackground
TEST_F(SplashTest_1565, CompositeBackground_1565) {
    SplashColor color;
    color[0] = 255; color[1] = 255; color[2] = 255;
    splash->compositeBackground(color);
    EXPECT_NE(splash->getBitmap(), nullptr);
}

// Test blitImage
TEST_F(SplashTest_1565, BlitImage_1565) {
    SplashBitmap src(10, 10, 4, splashModeRGB8, false);
    splash->blitImage(src, false, 0, 0);
    EXPECT_NE(splash->getBitmap(), nullptr);
}

// Test save state preserves fill alpha
TEST_F(SplashTest_1565, SaveStatePreservesFillAlpha_1565) {
    splash->setFillAlpha(0.3);
    splash->saveState();
    splash->setFillAlpha(0.8);
    EXPECT_DOUBLE_EQ(splash->getFillAlpha(), 0.8);
    splash->restoreState();
    EXPECT_DOUBLE_EQ(splash->getFillAlpha(), 0.3);
}

// Test save state preserves line cap
TEST_F(SplashTest_1565, SaveStatePreservesLineCap_1565) {
    splash->setLineCap(splashLineCapRound);
    splash->saveState();
    splash->setLineCap(splashLineCapSquare);
    EXPECT_EQ(splash->getLineCap(), splashLineCapSquare);
    splash->restoreState();
    EXPECT_EQ(splash->getLineCap(), splashLineCapRound);
}

// Test save state preserves stroke adjust
TEST_F(SplashTest_1565, SaveStatePreservesStrokeAdjust_1565) {
    splash->setStrokeAdjust(true);
    splash->saveState();
    splash->setStrokeAdjust(false);
    EXPECT_FALSE(splash->getStrokeAdjust());
    splash->restoreState();
    EXPECT_TRUE(splash->getStrokeAdjust());
}

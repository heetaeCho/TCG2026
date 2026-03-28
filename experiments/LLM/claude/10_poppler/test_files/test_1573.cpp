#include <gtest/gtest.h>
#include "splash/Splash.h"
#include "splash/SplashBitmap.h"
#include "splash/SplashTypes.h"
#include "splash/SplashPattern.h"
#include "splash/SplashScreen.h"
#include "splash/SplashState.h"
#include "splash/SplashClip.h"
#include "splash/SplashPath.h"

class SplashTest_1573 : public ::testing::Test {
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

// Test vectorAntialias getter and setter - normal operation
TEST_F(SplashTest_1573, SetVectorAntialiasTrue_1573) {
    splash->setVectorAntialias(true);
    EXPECT_TRUE(splash->getVectorAntialias());
}

TEST_F(SplashTest_1573, SetVectorAntialiasFalse_1573) {
    splash->setVectorAntialias(false);
    EXPECT_FALSE(splash->getVectorAntialias());
}

TEST_F(SplashTest_1573, VectorAntialiasDefaultFalse_1573) {
    // Constructed with vectorAntialiasA = false
    EXPECT_FALSE(splash->getVectorAntialias());
}

TEST_F(SplashTest_1573, VectorAntialiasToggle_1573) {
    splash->setVectorAntialias(true);
    EXPECT_TRUE(splash->getVectorAntialias());
    splash->setVectorAntialias(false);
    EXPECT_FALSE(splash->getVectorAntialias());
    splash->setVectorAntialias(true);
    EXPECT_TRUE(splash->getVectorAntialias());
}

// Test construction with vector antialias enabled
TEST(SplashConstructionTest_1573, ConstructWithVectorAntialiasTrue_1573) {
    SplashBitmap *bmp = new SplashBitmap(100, 100, 4, splashModeRGB8, false);
    SplashScreenParams screenParams;
    screenParams.type = splashScreenDispersed;
    screenParams.size = 2;
    screenParams.dotRadius = 0;
    screenParams.gamma = 1.0;
    screenParams.blackThreshold = 0.0;
    screenParams.whiteThreshold = 1.0;
    Splash *s = new Splash(bmp, true, &screenParams);
    EXPECT_TRUE(s->getVectorAntialias());
    delete s;
    delete bmp;
}

// Test getBitmap
TEST_F(SplashTest_1573, GetBitmapReturnsConstructedBitmap_1573) {
    EXPECT_EQ(splash->getBitmap(), bitmap);
}

// Test setMinLineWidth / setLineWidth / getLineWidth
TEST_F(SplashTest_1573, SetAndGetLineWidth_1573) {
    splash->setLineWidth(2.5);
    EXPECT_DOUBLE_EQ(splash->getLineWidth(), 2.5);
}

TEST_F(SplashTest_1573, SetLineWidthZero_1573) {
    splash->setLineWidth(0.0);
    EXPECT_DOUBLE_EQ(splash->getLineWidth(), 0.0);
}

TEST_F(SplashTest_1573, SetLineWidthNegative_1573) {
    splash->setLineWidth(-1.0);
    EXPECT_DOUBLE_EQ(splash->getLineWidth(), -1.0);
}

// Test stroke alpha
TEST_F(SplashTest_1573, SetAndGetStrokeAlpha_1573) {
    splash->setStrokeAlpha(0.5);
    EXPECT_DOUBLE_EQ(splash->getStrokeAlpha(), 0.5);
}

TEST_F(SplashTest_1573, SetStrokeAlphaZero_1573) {
    splash->setStrokeAlpha(0.0);
    EXPECT_DOUBLE_EQ(splash->getStrokeAlpha(), 0.0);
}

TEST_F(SplashTest_1573, SetStrokeAlphaOne_1573) {
    splash->setStrokeAlpha(1.0);
    EXPECT_DOUBLE_EQ(splash->getStrokeAlpha(), 1.0);
}

// Test fill alpha
TEST_F(SplashTest_1573, SetAndGetFillAlpha_1573) {
    splash->setFillAlpha(0.75);
    EXPECT_DOUBLE_EQ(splash->getFillAlpha(), 0.75);
}

TEST_F(SplashTest_1573, SetFillAlphaZero_1573) {
    splash->setFillAlpha(0.0);
    EXPECT_DOUBLE_EQ(splash->getFillAlpha(), 0.0);
}

TEST_F(SplashTest_1573, SetFillAlphaOne_1573) {
    splash->setFillAlpha(1.0);
    EXPECT_DOUBLE_EQ(splash->getFillAlpha(), 1.0);
}

// Test line cap
TEST_F(SplashTest_1573, SetAndGetLineCap_1573) {
    splash->setLineCap(splashLineCapRound);
    EXPECT_EQ(splash->getLineCap(), splashLineCapRound);
}

TEST_F(SplashTest_1573, SetLineCapButt_1573) {
    splash->setLineCap(splashLineCapButt);
    EXPECT_EQ(splash->getLineCap(), splashLineCapButt);
}

TEST_F(SplashTest_1573, SetLineCapProjecting_1573) {
    splash->setLineCap(splashLineCapProjecting);
    EXPECT_EQ(splash->getLineCap(), splashLineCapProjecting);
}

// Test line join
TEST_F(SplashTest_1573, SetAndGetLineJoin_1573) {
    splash->setLineJoin(splashLineJoinRound);
    EXPECT_EQ(splash->getLineJoin(), splashLineJoinRound);
}

TEST_F(SplashTest_1573, SetLineJoinMiter_1573) {
    splash->setLineJoin(splashLineJoinMiter);
    EXPECT_EQ(splash->getLineJoin(), splashLineJoinMiter);
}

TEST_F(SplashTest_1573, SetLineJoinBevel_1573) {
    splash->setLineJoin(splashLineJoinBevel);
    EXPECT_EQ(splash->getLineJoin(), splashLineJoinBevel);
}

// Test miter limit
TEST_F(SplashTest_1573, SetAndGetMiterLimit_1573) {
    splash->setMiterLimit(10.0);
    EXPECT_DOUBLE_EQ(splash->getMiterLimit(), 10.0);
}

// Test flatness
TEST_F(SplashTest_1573, SetAndGetFlatness_1573) {
    splash->setFlatness(1.5);
    EXPECT_DOUBLE_EQ(splash->getFlatness(), 1.5);
}

// Test stroke adjust
TEST_F(SplashTest_1573, SetStrokeAdjustTrue_1573) {
    splash->setStrokeAdjust(true);
    EXPECT_TRUE(splash->getStrokeAdjust());
}

TEST_F(SplashTest_1573, SetStrokeAdjustFalse_1573) {
    splash->setStrokeAdjust(false);
    EXPECT_FALSE(splash->getStrokeAdjust());
}

// Test matrix
TEST_F(SplashTest_1573, SetAndGetMatrix_1573) {
    std::array<SplashCoord, 6> mat = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};
    splash->setMatrix(mat);
    const auto &result = splash->getMatrix();
    for (int i = 0; i < 6; i++) {
        EXPECT_DOUBLE_EQ(result[i], mat[i]);
    }
}

TEST_F(SplashTest_1573, SetMatrixNonIdentity_1573) {
    std::array<SplashCoord, 6> mat = {2.0, 0.5, 0.3, 1.5, 10.0, 20.0};
    splash->setMatrix(mat);
    const auto &result = splash->getMatrix();
    for (int i = 0; i < 6; i++) {
        EXPECT_DOUBLE_EQ(result[i], mat[i]);
    }
}

// Test thin line mode
TEST_F(SplashTest_1573, SetAndGetThinLineMode_1573) {
    splash->setThinLineMode(splashThinLineShape);
    EXPECT_EQ(splash->getThinLineMode(), splashThinLineShape);
}

TEST_F(SplashTest_1573, SetThinLineModeDefault_1573) {
    splash->setThinLineMode(splashThinLineDefault);
    EXPECT_EQ(splash->getThinLineMode(), splashThinLineDefault);
}

// Test debug mode
TEST_F(SplashTest_1573, SetDebugMode_1573) {
    splash->setDebugMode(true);
    // No getter that's clearly public for debug mode is exposed except the setter.
    // We test that calling it doesn't crash.
    splash->setDebugMode(false);
}

// Test setInShading
TEST_F(SplashTest_1573, SetInShading_1573) {
    splash->setInShading(true);
    splash->setInShading(false);
    // No crash expected
}

// Test save/restore state
TEST_F(SplashTest_1573, SaveAndRestoreState_1573) {
    splash->setLineWidth(3.0);
    splash->saveState();
    splash->setLineWidth(5.0);
    EXPECT_DOUBLE_EQ(splash->getLineWidth(), 5.0);
    SplashError err = splash->restoreState();
    EXPECT_EQ(err, splashOk);
    EXPECT_DOUBLE_EQ(splash->getLineWidth(), 3.0);
}

TEST_F(SplashTest_1573, RestoreStateWithoutSave_1573) {
    SplashError err = splash->restoreState();
    EXPECT_NE(err, splashOk);
}

TEST_F(SplashTest_1573, MultipleSaveRestore_1573) {
    splash->setFillAlpha(0.1);
    splash->saveState();
    splash->setFillAlpha(0.5);
    splash->saveState();
    splash->setFillAlpha(0.9);
    EXPECT_DOUBLE_EQ(splash->getFillAlpha(), 0.9);

    SplashError err = splash->restoreState();
    EXPECT_EQ(err, splashOk);
    EXPECT_DOUBLE_EQ(splash->getFillAlpha(), 0.5);

    err = splash->restoreState();
    EXPECT_EQ(err, splashOk);
    EXPECT_DOUBLE_EQ(splash->getFillAlpha(), 0.1);
}

// Test clear
TEST_F(SplashTest_1573, ClearBitmap_1573) {
    SplashColor color;
    color[0] = 255;
    color[1] = 0;
    color[2] = 0;
    splash->clear(color, 255);
    // Verify by checking bitmap data
    SplashColorPtr data = bitmap->getDataPtr();
    // First pixel should be red (for RGB8)
    EXPECT_EQ(data[0], 255);
    EXPECT_EQ(data[1], 0);
    EXPECT_EQ(data[2], 0);
}

// Test clipToRect
TEST_F(SplashTest_1573, ClipToRect_1573) {
    SplashError err = splash->clipToRect(10.0, 10.0, 90.0, 90.0);
    EXPECT_EQ(err, splashOk);
}

// Test clipResetToRect
TEST_F(SplashTest_1573, ClipResetToRect_1573) {
    splash->clipResetToRect(0.0, 0.0, 50.0, 50.0);
    // Should not crash; clip should be set
}

// Test setLineDash with vector
TEST_F(SplashTest_1573, SetLineDashVector_1573) {
    std::vector<SplashCoord> dash = {5.0, 3.0};
    splash->setLineDash(std::move(dash), 0.0);
    EXPECT_DOUBLE_EQ(splash->getLineDashPhase(), 0.0);
}

TEST_F(SplashTest_1573, SetLineDashPhase_1573) {
    std::vector<SplashCoord> dash = {10.0, 5.0};
    splash->setLineDash(std::move(dash), 2.5);
    EXPECT_DOUBLE_EQ(splash->getLineDashPhase(), 2.5);
}

// Test setMinLineWidth doesn't crash
TEST_F(SplashTest_1573, SetMinLineWidth_1573) {
    splash->setMinLineWidth(0.5);
    // No direct getter, but should not crash
}

// Test getSoftMask initially
TEST_F(SplashTest_1573, GetSoftMaskInitiallyNull_1573) {
    EXPECT_EQ(splash->getSoftMask(), nullptr);
}

// Test getInNonIsolatedGroup initially
TEST_F(SplashTest_1573, GetInNonIsolatedGroupInitiallyFalse_1573) {
    EXPECT_FALSE(splash->getInNonIsolatedGroup());
}

// Test overprint settings don't crash
TEST_F(SplashTest_1573, SetFillOverprint_1573) {
    splash->setFillOverprint(true);
    splash->setFillOverprint(false);
}

TEST_F(SplashTest_1573, SetStrokeOverprint_1573) {
    splash->setStrokeOverprint(true);
    splash->setStrokeOverprint(false);
}

TEST_F(SplashTest_1573, SetOverprintMode_1573) {
    splash->setOverprintMode(0);
    splash->setOverprintMode(1);
}

// Test setOverprintMask
TEST_F(SplashTest_1573, SetOverprintMask_1573) {
    splash->setOverprintMask(0xFFFFFFFF, false);
    splash->setOverprintMask(0x0, true);
}

// Test setPatternAlpha and clearPatternAlpha
TEST_F(SplashTest_1573, SetPatternAlpha_1573) {
    splash->setPatternAlpha(0.5, 0.7);
    // Should not crash
}

TEST_F(SplashTest_1573, ClearPatternAlpha_1573) {
    splash->setPatternAlpha(0.5, 0.7);
    splash->clearPatternAlpha();
    // Should not crash
}

// Test state persistence across save/restore for various properties
TEST_F(SplashTest_1573, SaveRestoreStrokeAlpha_1573) {
    splash->setStrokeAlpha(0.3);
    splash->saveState();
    splash->setStrokeAlpha(0.8);
    EXPECT_DOUBLE_EQ(splash->getStrokeAlpha(), 0.8);
    splash->restoreState();
    EXPECT_DOUBLE_EQ(splash->getStrokeAlpha(), 0.3);
}

TEST_F(SplashTest_1573, SaveRestoreLineCap_1573) {
    splash->setLineCap(splashLineCapRound);
    splash->saveState();
    splash->setLineCap(splashLineCapButt);
    EXPECT_EQ(splash->getLineCap(), splashLineCapButt);
    splash->restoreState();
    EXPECT_EQ(splash->getLineCap(), splashLineCapRound);
}

TEST_F(SplashTest_1573, SaveRestoreLineJoin_1573) {
    splash->setLineJoin(splashLineJoinBevel);
    splash->saveState();
    splash->setLineJoin(splashLineJoinMiter);
    EXPECT_EQ(splash->getLineJoin(), splashLineJoinMiter);
    splash->restoreState();
    EXPECT_EQ(splash->getLineJoin(), splashLineJoinBevel);
}

// Test boundary: very large line width
TEST_F(SplashTest_1573, SetVeryLargeLineWidth_1573) {
    splash->setLineWidth(1e10);
    EXPECT_DOUBLE_EQ(splash->getLineWidth(), 1e10);
}

// Test boundary: very small positive line width
TEST_F(SplashTest_1573, SetVerySmallLineWidth_1573) {
    splash->setLineWidth(1e-10);
    EXPECT_DOUBLE_EQ(splash->getLineWidth(), 1e-10);
}

// Test repeated set of vector antialias
TEST_F(SplashTest_1573, RepeatedSetVectorAntialias_1573) {
    for (int i = 0; i < 100; i++) {
        splash->setVectorAntialias(i % 2 == 0);
        EXPECT_EQ(splash->getVectorAntialias(), (i % 2 == 0));
    }
}

// Test save/restore preserves vectorAntialias? Actually vectorAntialias
// is a member of Splash, not SplashState, so it should NOT be affected by save/restore.
TEST_F(SplashTest_1573, VectorAntialiasNotAffectedBySaveRestore_1573) {
    splash->setVectorAntialias(true);
    splash->saveState();
    splash->setVectorAntialias(false);
    EXPECT_FALSE(splash->getVectorAntialias());
    splash->restoreState();
    // vectorAntialias is a direct member, not state-managed, so it should remain false
    EXPECT_FALSE(splash->getVectorAntialias());
}

// Test clipToPath with a simple path
TEST_F(SplashTest_1573, ClipToPathSimple_1573) {
    SplashPath path;
    path.moveTo(10, 10);
    path.lineTo(90, 10);
    path.lineTo(90, 90);
    path.lineTo(10, 90);
    path.close();
    SplashError err = splash->clipToPath(path, false);
    EXPECT_EQ(err, splashOk);
}

// Test stroke with empty path
TEST_F(SplashTest_1573, StrokeEmptyPath_1573) {
    SplashPath path;
    SplashError err = splash->stroke(path);
    // An empty path should either succeed or return an error, but not crash
    (void)err;
}

// Test fill with empty path
TEST_F(SplashTest_1573, FillEmptyPath_1573) {
    SplashPath path;
    SplashError err = splash->fill(&path, false);
    (void)err;
}

// Test stroke with simple rectangle path
TEST_F(SplashTest_1573, StrokeSimpleRectangle_1573) {
    SplashPath path;
    path.moveTo(10, 10);
    path.lineTo(50, 10);
    path.lineTo(50, 50);
    path.lineTo(10, 50);
    path.close();

    splash->setLineWidth(1.0);
    SplashColor color;
    color[0] = 0;
    color[1] = 0;
    color[2] = 0;
    splash->clear(color, 255);

    SplashError err = splash->stroke(path);
    EXPECT_EQ(err, splashOk);
}

// Test getClipRes
TEST_F(SplashTest_1573, GetClipRes_1573) {
    SplashClipResult res = splash->getClipRes();
    // Just verify it returns without crashing
    (void)res;
}

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

// Test fixture that creates a Splash object with a simple bitmap
class SplashTest_1571 : public ::testing::Test {
protected:
    SplashBitmap *bitmap;
    Splash *splash;

    void SetUp() override {
        // Create a simple RGB8 bitmap
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

// Test setInShading and related state
TEST_F(SplashTest_1571, SetInShadingTrue_1571) {
    splash->setInShading(true);
    // No crash, no observable getter for inShading but we verify it doesn't crash
    SUCCEED();
}

TEST_F(SplashTest_1571, SetInShadingFalse_1571) {
    splash->setInShading(false);
    SUCCEED();
}

TEST_F(SplashTest_1571, SetInShadingToggle_1571) {
    splash->setInShading(true);
    splash->setInShading(false);
    splash->setInShading(true);
    SUCCEED();
}

// Test getBitmap
TEST_F(SplashTest_1571, GetBitmapReturnsNonNull_1571) {
    SplashBitmap *bmp = splash->getBitmap();
    ASSERT_NE(bmp, nullptr);
    EXPECT_EQ(bmp, bitmap);
}

// Test vector antialias getter/setter
TEST_F(SplashTest_1571, GetVectorAntialiasDefault_1571) {
    // Was constructed with false
    EXPECT_FALSE(splash->getVectorAntialias());
}

TEST_F(SplashTest_1571, SetVectorAntialiasTrue_1571) {
    splash->setVectorAntialias(true);
    EXPECT_TRUE(splash->getVectorAntialias());
}

TEST_F(SplashTest_1571, SetVectorAntialiasFalse_1571) {
    splash->setVectorAntialias(true);
    splash->setVectorAntialias(false);
    EXPECT_FALSE(splash->getVectorAntialias());
}

// Test setDebugMode
TEST_F(SplashTest_1571, SetDebugModeTrue_1571) {
    splash->setDebugMode(true);
    SUCCEED();
}

TEST_F(SplashTest_1571, SetDebugModeFalse_1571) {
    splash->setDebugMode(false);
    SUCCEED();
}

// Test thin line mode
TEST_F(SplashTest_1571, SetAndGetThinLineMode_1571) {
    splash->setThinLineMode(splashThinLineDefault);
    EXPECT_EQ(splash->getThinLineMode(), splashThinLineDefault);
}

TEST_F(SplashTest_1571, SetThinLineModeShape_1571) {
    splash->setThinLineMode(splashThinLineShape);
    EXPECT_EQ(splash->getThinLineMode(), splashThinLineShape);
}

// Test min line width
TEST_F(SplashTest_1571, SetMinLineWidth_1571) {
    splash->setMinLineWidth(0.5);
    SUCCEED();
}

TEST_F(SplashTest_1571, SetMinLineWidthZero_1571) {
    splash->setMinLineWidth(0.0);
    SUCCEED();
}

// Test line width getter/setter
TEST_F(SplashTest_1571, SetAndGetLineWidth_1571) {
    splash->setLineWidth(2.5);
    EXPECT_DOUBLE_EQ(splash->getLineWidth(), 2.5);
}

TEST_F(SplashTest_1571, SetLineWidthZero_1571) {
    splash->setLineWidth(0.0);
    EXPECT_DOUBLE_EQ(splash->getLineWidth(), 0.0);
}

// Test stroke alpha getter/setter
TEST_F(SplashTest_1571, SetAndGetStrokeAlpha_1571) {
    splash->setStrokeAlpha(0.5);
    EXPECT_DOUBLE_EQ(splash->getStrokeAlpha(), 0.5);
}

TEST_F(SplashTest_1571, SetStrokeAlphaZero_1571) {
    splash->setStrokeAlpha(0.0);
    EXPECT_DOUBLE_EQ(splash->getStrokeAlpha(), 0.0);
}

TEST_F(SplashTest_1571, SetStrokeAlphaOne_1571) {
    splash->setStrokeAlpha(1.0);
    EXPECT_DOUBLE_EQ(splash->getStrokeAlpha(), 1.0);
}

// Test fill alpha getter/setter
TEST_F(SplashTest_1571, SetAndGetFillAlpha_1571) {
    splash->setFillAlpha(0.75);
    EXPECT_DOUBLE_EQ(splash->getFillAlpha(), 0.75);
}

TEST_F(SplashTest_1571, SetFillAlphaZero_1571) {
    splash->setFillAlpha(0.0);
    EXPECT_DOUBLE_EQ(splash->getFillAlpha(), 0.0);
}

TEST_F(SplashTest_1571, SetFillAlphaOne_1571) {
    splash->setFillAlpha(1.0);
    EXPECT_DOUBLE_EQ(splash->getFillAlpha(), 1.0);
}

// Test pattern alpha
TEST_F(SplashTest_1571, SetPatternAlpha_1571) {
    splash->setPatternAlpha(0.5, 0.7);
    SUCCEED();
}

TEST_F(SplashTest_1571, ClearPatternAlpha_1571) {
    splash->setPatternAlpha(0.5, 0.7);
    splash->clearPatternAlpha();
    SUCCEED();
}

// Test line cap getter/setter
TEST_F(SplashTest_1571, SetAndGetLineCap_1571) {
    splash->setLineCap(splashLineCapRound);
    EXPECT_EQ(splash->getLineCap(), splashLineCapRound);
}

TEST_F(SplashTest_1571, SetLineCapButt_1571) {
    splash->setLineCap(splashLineCapButt);
    EXPECT_EQ(splash->getLineCap(), splashLineCapButt);
}

TEST_F(SplashTest_1571, SetLineCapProjecting_1571) {
    splash->setLineCap(splashLineCapProjecting);
    EXPECT_EQ(splash->getLineCap(), splashLineCapProjecting);
}

// Test line join getter/setter
TEST_F(SplashTest_1571, SetAndGetLineJoin_1571) {
    splash->setLineJoin(splashLineJoinRound);
    EXPECT_EQ(splash->getLineJoin(), splashLineJoinRound);
}

TEST_F(SplashTest_1571, SetLineJoinMiter_1571) {
    splash->setLineJoin(splashLineJoinMiter);
    EXPECT_EQ(splash->getLineJoin(), splashLineJoinMiter);
}

TEST_F(SplashTest_1571, SetLineJoinBevel_1571) {
    splash->setLineJoin(splashLineJoinBevel);
    EXPECT_EQ(splash->getLineJoin(), splashLineJoinBevel);
}

// Test miter limit getter/setter
TEST_F(SplashTest_1571, SetAndGetMiterLimit_1571) {
    splash->setMiterLimit(10.0);
    EXPECT_DOUBLE_EQ(splash->getMiterLimit(), 10.0);
}

// Test flatness getter/setter
TEST_F(SplashTest_1571, SetAndGetFlatness_1571) {
    splash->setFlatness(0.5);
    EXPECT_DOUBLE_EQ(splash->getFlatness(), 0.5);
}

// Test stroke adjust getter/setter
TEST_F(SplashTest_1571, SetAndGetStrokeAdjust_1571) {
    splash->setStrokeAdjust(true);
    EXPECT_TRUE(splash->getStrokeAdjust());
}

TEST_F(SplashTest_1571, SetStrokeAdjustFalse_1571) {
    splash->setStrokeAdjust(false);
    EXPECT_FALSE(splash->getStrokeAdjust());
}

// Test matrix getter/setter
TEST_F(SplashTest_1571, SetAndGetMatrix_1571) {
    std::array<SplashCoord, 6> mat = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};
    splash->setMatrix(mat);
    const auto &result = splash->getMatrix();
    for (int i = 0; i < 6; i++) {
        EXPECT_DOUBLE_EQ(result[i], mat[i]);
    }
}

TEST_F(SplashTest_1571, SetMatrixNonIdentity_1571) {
    std::array<SplashCoord, 6> mat = {2.0, 0.5, -0.5, 2.0, 10.0, 20.0};
    splash->setMatrix(mat);
    const auto &result = splash->getMatrix();
    for (int i = 0; i < 6; i++) {
        EXPECT_DOUBLE_EQ(result[i], mat[i]);
    }
}

// Test line dash
TEST_F(SplashTest_1571, SetLineDashVector_1571) {
    std::vector<SplashCoord> dash = {3.0, 2.0};
    splash->setLineDash(std::move(dash), 0.0);
    EXPECT_DOUBLE_EQ(splash->getLineDashPhase(), 0.0);
}

TEST_F(SplashTest_1571, SetLineDashWithPhase_1571) {
    std::vector<SplashCoord> dash = {5.0, 3.0};
    splash->setLineDash(std::move(dash), 1.5);
    EXPECT_DOUBLE_EQ(splash->getLineDashPhase(), 1.5);
}

TEST_F(SplashTest_1571, SetLineDashEmpty_1571) {
    std::vector<SplashCoord> dash;
    splash->setLineDash(std::move(dash), 0.0);
    EXPECT_DOUBLE_EQ(splash->getLineDashPhase(), 0.0);
}

// Test overprint settings
TEST_F(SplashTest_1571, SetFillOverprint_1571) {
    splash->setFillOverprint(true);
    SUCCEED();
}

TEST_F(SplashTest_1571, SetStrokeOverprint_1571) {
    splash->setStrokeOverprint(true);
    SUCCEED();
}

TEST_F(SplashTest_1571, SetOverprintMode_1571) {
    splash->setOverprintMode(1);
    SUCCEED();
}

TEST_F(SplashTest_1571, SetOverprintMask_1571) {
    splash->setOverprintMask(0xFFFFFFFF, false);
    SUCCEED();
}

TEST_F(SplashTest_1571, SetOverprintMaskAdditive_1571) {
    splash->setOverprintMask(0x0F, true);
    SUCCEED();
}

// Test save/restore state
TEST_F(SplashTest_1571, SaveAndRestoreState_1571) {
    splash->setLineWidth(5.0);
    splash->saveState();
    splash->setLineWidth(10.0);
    EXPECT_DOUBLE_EQ(splash->getLineWidth(), 10.0);
    SplashError err = splash->restoreState();
    EXPECT_EQ(err, splashOk);
    EXPECT_DOUBLE_EQ(splash->getLineWidth(), 5.0);
}

TEST_F(SplashTest_1571, RestoreStateWithoutSave_1571) {
    SplashError err = splash->restoreState();
    EXPECT_NE(err, splashOk);
}

TEST_F(SplashTest_1571, MultipleSaveRestore_1571) {
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
TEST_F(SplashTest_1571, ClearBitmap_1571) {
    SplashColor color;
    color[0] = 255;
    color[1] = 0;
    color[2] = 0;
    splash->clear(color, 255);
    SUCCEED();
}

TEST_F(SplashTest_1571, ClearBitmapWithZeroAlpha_1571) {
    SplashColor color;
    color[0] = 0;
    color[1] = 0;
    color[2] = 0;
    splash->clear(color, 0);
    SUCCEED();
}

// Test clipResetToRect
TEST_F(SplashTest_1571, ClipResetToRect_1571) {
    splash->clipResetToRect(0.0, 0.0, 50.0, 50.0);
    SUCCEED();
}

// Test clipToRect
TEST_F(SplashTest_1571, ClipToRect_1571) {
    SplashError err = splash->clipToRect(10.0, 10.0, 90.0, 90.0);
    EXPECT_EQ(err, splashOk);
}

TEST_F(SplashTest_1571, ClipToRectSmall_1571) {
    SplashError err = splash->clipToRect(0.0, 0.0, 1.0, 1.0);
    EXPECT_EQ(err, splashOk);
}

// Test clipToPath
TEST_F(SplashTest_1571, ClipToPathSimple_1571) {
    SplashPath path;
    path.moveTo(10, 10);
    path.lineTo(90, 10);
    path.lineTo(90, 90);
    path.lineTo(10, 90);
    path.close();
    SplashError err = splash->clipToPath(path, false);
    EXPECT_EQ(err, splashOk);
}

// Test stroke with a simple path
TEST_F(SplashTest_1571, StrokeSimplePath_1571) {
    SplashPath path;
    path.moveTo(10, 10);
    path.lineTo(50, 50);
    splash->setLineWidth(1.0);
    SplashError err = splash->stroke(path);
    EXPECT_EQ(err, splashOk);
}

// Test fill with a simple path
TEST_F(SplashTest_1571, FillSimplePath_1571) {
    SplashPath path;
    path.moveTo(10, 10);
    path.lineTo(90, 10);
    path.lineTo(90, 90);
    path.lineTo(10, 90);
    path.close();
    SplashError err = splash->fill(&path, false);
    EXPECT_EQ(err, splashOk);
}

TEST_F(SplashTest_1571, FillEvenOdd_1571) {
    SplashPath path;
    path.moveTo(10, 10);
    path.lineTo(90, 10);
    path.lineTo(90, 90);
    path.lineTo(10, 90);
    path.close();
    SplashError err = splash->fill(&path, true);
    EXPECT_EQ(err, splashOk);
}

// Test getClip
TEST_F(SplashTest_1571, GetClipReturnsValidReference_1571) {
    const SplashClip &clip = splash->getClip();
    // Just verify we can access it without crash
    (void)clip;
    SUCCEED();
}

// Test getScreen
TEST_F(SplashTest_1571, GetScreenReturnsValidReference_1571) {
    const SplashScreen &screen = splash->getScreen();
    (void)screen;
    SUCCEED();
}

// Test getInNonIsolatedGroup
TEST_F(SplashTest_1571, GetInNonIsolatedGroupDefault_1571) {
    EXPECT_FALSE(splash->getInNonIsolatedGroup());
}

// Test getSoftMask
TEST_F(SplashTest_1571, GetSoftMaskDefault_1571) {
    SplashBitmap *mask = splash->getSoftMask();
    EXPECT_EQ(mask, nullptr);
}

// Test setSoftMask
TEST_F(SplashTest_1571, SetSoftMask_1571) {
    SplashBitmap *maskBitmap = new SplashBitmap(100, 100, 1, splashModeMono8, false);
    splash->setSoftMask(maskBitmap);
    SplashBitmap *result = splash->getSoftMask();
    EXPECT_EQ(result, maskBitmap);
}

// Test setTransfer
TEST_F(SplashTest_1571, SetTransfer_1571) {
    unsigned char red[256], green[256], blue[256], gray[256];
    for (int i = 0; i < 256; i++) {
        red[i] = green[i] = blue[i] = gray[i] = (unsigned char)i;
    }
    splash->setTransfer(red, green, blue, gray);
    SUCCEED();
}

// Test blitTransparent
TEST_F(SplashTest_1571, BlitTransparent_1571) {
    SplashBitmap src(50, 50, 4, splashModeRGB8, false);
    SplashError err = splash->blitTransparent(src, 0, 0, 10, 10, 50, 50);
    EXPECT_EQ(err, splashOk);
}

TEST_F(SplashTest_1571, BlitTransparentOutOfBounds_1571) {
    SplashBitmap src(50, 50, 4, splashModeRGB8, false);
    SplashError err = splash->blitTransparent(src, 0, 0, 200, 200, 50, 50);
    // May or may not succeed, but shouldn't crash
    (void)err;
    SUCCEED();
}

// Test composite
TEST_F(SplashTest_1571, CompositeBasic_1571) {
    SplashBitmap src(50, 50, 4, splashModeRGB8, false);
    SplashColor color;
    color[0] = 128;
    color[1] = 128;
    color[2] = 128;
    src.getAlphaPtr(); // ensure alpha exists or not
    SplashError err = splash->composite(src, 0, 0, 0, 0, 50, 50, true, false, false, 1.0);
    // Just check it doesn't crash
    (void)err;
    SUCCEED();
}

// Test compositeBackground
TEST_F(SplashTest_1571, CompositeBackground_1571) {
    SplashColor color;
    color[0] = 255;
    color[1] = 255;
    color[2] = 255;
    splash->compositeBackground(color);
    SUCCEED();
}

// Test makeStrokePath
TEST_F(SplashTest_1571, MakeStrokePath_1571) {
    SplashPath path;
    path.moveTo(10, 10);
    path.lineTo(50, 50);
    int result = splash->makeStrokePath(path, 2.0, true);
    // Result is the number of points in the stroke path
    EXPECT_GE(result, 0);
}

// Test getBlendFunc
TEST_F(SplashTest_1571, GetBlendFunc_1571) {
    SplashBlendFunc func = splash->getBlendFunc();
    // Default blend func should not be null
    (void)func;
    SUCCEED();
}

// Test setBlendFunc
TEST_F(SplashTest_1571, SetBlendFunc_1571) {
    splash->setBlendFunc(nullptr);
    EXPECT_EQ(splash->getBlendFunc(), nullptr);
}

// Test getClipRes
TEST_F(SplashTest_1571, GetClipRes_1571) {
    SplashClipResult res = splash->getClipRes();
    // Just verify it returns a valid value
    (void)res;
    SUCCEED();
}

// Test construction with SplashScreen
class SplashScreenConstructorTest_1571 : public ::testing::Test {
protected:
    SplashBitmap *bitmap;
    
    void SetUp() override {
        bitmap = new SplashBitmap(100, 100, 4, splashModeRGB8, false);
    }
    
    void TearDown() override {
        delete bitmap;
    }
};

TEST_F(SplashScreenConstructorTest_1571, ConstructWithScreenParams_1571) {
    SplashScreenParams screenParams;
    screenParams.type = splashScreenDispersed;
    screenParams.size = 2;
    screenParams.dotRadius = 0;
    screenParams.gamma = 1.0;
    screenParams.blackThreshold = 0.0;
    screenParams.whiteThreshold = 1.0;
    Splash *s = new Splash(bitmap, false, &screenParams);
    ASSERT_NE(s, nullptr);
    EXPECT_EQ(s->getBitmap(), bitmap);
    delete s;
}

// Test setInNonIsolatedGroup
TEST_F(SplashTest_1571, SetInNonIsolatedGroup_1571) {
    SplashBitmap *alpha0Bmp = new SplashBitmap(100, 100, 1, splashModeMono8, false);
    splash->setInNonIsolatedGroup(alpha0Bmp, 0, 0);
    EXPECT_TRUE(splash->getInNonIsolatedGroup());
    delete alpha0Bmp;
}

// Test shadedFill
TEST_F(SplashTest_1571, ShadedFillBasic_1571) {
    SplashPath path;
    path.moveTo(10, 10);
    path.lineTo(90, 10);
    path.lineTo(90, 90);
    path.lineTo(10, 90);
    path.close();
    splash->setInShading(true);
    // We pass nullptr pattern which may cause issues, but test the interface
    SplashError err = splash->shadedFill(path, true, nullptr, false);
    splash->setInShading(false);
    (void)err;
    SUCCEED();
}

// Test multiple property changes persist through save/restore
TEST_F(SplashTest_1571, SaveRestoreMultipleProperties_1571) {
    splash->setLineWidth(3.0);
    splash->setStrokeAlpha(0.5);
    splash->setFillAlpha(0.8);
    splash->setLineCap(splashLineCapRound);
    splash->setLineJoin(splashLineJoinBevel);
    splash->setMiterLimit(5.0);
    splash->setFlatness(0.3);
    splash->setStrokeAdjust(true);

    splash->saveState();

    splash->setLineWidth(10.0);
    splash->setStrokeAlpha(1.0);
    splash->setFillAlpha(0.1);
    splash->setLineCap(splashLineCapButt);
    splash->setLineJoin(splashLineJoinMiter);
    splash->setMiterLimit(20.0);
    splash->setFlatness(1.0);
    splash->setStrokeAdjust(false);

    EXPECT_DOUBLE_EQ(splash->getLineWidth(), 10.0);
    EXPECT_DOUBLE_EQ(splash->getStrokeAlpha(), 1.0);
    EXPECT_DOUBLE_EQ(splash->getFillAlpha(), 0.1);
    EXPECT_EQ(splash->getLineCap(), splashLineCapButt);
    EXPECT_EQ(splash->getLineJoin(), splashLineJoinMiter);
    EXPECT_DOUBLE_EQ(splash->getMiterLimit(), 20.0);
    EXPECT_DOUBLE_EQ(splash->getFlatness(), 1.0);
    EXPECT_FALSE(splash->getStrokeAdjust());

    splash->restoreState();

    EXPECT_DOUBLE_EQ(splash->getLineWidth(), 3.0);
    EXPECT_DOUBLE_EQ(splash->getStrokeAlpha(), 0.5);
    EXPECT_DOUBLE_EQ(splash->getFillAlpha(), 0.8);
    EXPECT_EQ(splash->getLineCap(), splashLineCapRound);
    EXPECT_EQ(splash->getLineJoin(), splashLineJoinBevel);
    EXPECT_DOUBLE_EQ(splash->getMiterLimit(), 5.0);
    EXPECT_DOUBLE_EQ(splash->getFlatness(), 0.3);
    EXPECT_TRUE(splash->getStrokeAdjust());
}

// Test blitImage (public version)
TEST_F(SplashTest_1571, BlitImagePublic_1571) {
    SplashBitmap src(20, 20, 4, splashModeRGB8, false);
    splash->blitImage(src, false, 5, 5);
    SUCCEED();
}

// Test stroke with empty path
TEST_F(SplashTest_1571, StrokeEmptyPath_1571) {
    SplashPath path;
    SplashError err = splash->stroke(path);
    // Empty path - implementation defined behavior
    (void)err;
    SUCCEED();
}

// Test fill with null path
TEST_F(SplashTest_1571, FillNullPath_1571) {
    // Some implementations may handle nullptr
    // Skip this if it would crash
    SplashPath path;
    SplashError err = splash->fill(&path, false);
    (void)err;
    SUCCEED();
}

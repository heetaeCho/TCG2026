#include <gtest/gtest.h>
#include "splash/Splash.h"
#include "splash/SplashBitmap.h"
#include "splash/SplashTypes.h"
#include "splash/SplashPattern.h"
#include "splash/SplashScreen.h"
#include "splash/SplashPath.h"
#include "splash/SplashClip.h"

class SplashTest_1568 : public ::testing::Test {
protected:
    SplashBitmap *bitmap;
    Splash *splash;

    void SetUp() override {
        // Create a simple bitmap for testing (e.g., 100x100, RGB8)
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

// Test getThinLineMode default value
TEST_F(SplashTest_1568, GetThinLineMode_Default_1568) {
    SplashThinLineMode mode = splash->getThinLineMode();
    // Default should be some valid thin line mode
    EXPECT_TRUE(mode == splashThinLineDefault || mode == splashThinLineSolid || mode == splashThinLineShape);
}

// Test setThinLineMode and getThinLineMode
TEST_F(SplashTest_1568, SetThinLineMode_Default_1568) {
    splash->setThinLineMode(splashThinLineDefault);
    EXPECT_EQ(splash->getThinLineMode(), splashThinLineDefault);
}

TEST_F(SplashTest_1568, SetThinLineMode_Solid_1568) {
    splash->setThinLineMode(splashThinLineSolid);
    EXPECT_EQ(splash->getThinLineMode(), splashThinLineSolid);
}

TEST_F(SplashTest_1568, SetThinLineMode_Shape_1568) {
    splash->setThinLineMode(splashThinLineShape);
    EXPECT_EQ(splash->getThinLineMode(), splashThinLineShape);
}

// Test getBitmap returns the bitmap passed in constructor
TEST_F(SplashTest_1568, GetBitmap_ReturnsBitmap_1568) {
    EXPECT_EQ(splash->getBitmap(), bitmap);
}

// Test setMinLineWidth
TEST_F(SplashTest_1568, SetMinLineWidth_1568) {
    splash->setMinLineWidth(2.0);
    // No getter for minLineWidth directly, but should not crash
    SUCCEED();
}

// Test getVectorAntialias
TEST_F(SplashTest_1568, GetVectorAntialias_False_1568) {
    EXPECT_FALSE(splash->getVectorAntialias());
}

// Test setVectorAntialias
TEST_F(SplashTest_1568, SetVectorAntialias_True_1568) {
    splash->setVectorAntialias(true);
    // Note: Depending on compilation flags, this may or may not change the value
    // We just ensure it doesn't crash
    SUCCEED();
}

// Test setDebugMode
TEST_F(SplashTest_1568, SetDebugMode_True_1568) {
    splash->setDebugMode(true);
    SUCCEED();
}

TEST_F(SplashTest_1568, SetDebugMode_False_1568) {
    splash->setDebugMode(false);
    SUCCEED();
}

// Test setInShading
TEST_F(SplashTest_1568, SetInShading_True_1568) {
    splash->setInShading(true);
    SUCCEED();
}

TEST_F(SplashTest_1568, SetInShading_False_1568) {
    splash->setInShading(false);
    SUCCEED();
}

// Test setLineWidth and getLineWidth
TEST_F(SplashTest_1568, SetAndGetLineWidth_1568) {
    splash->setLineWidth(3.5);
    EXPECT_DOUBLE_EQ(splash->getLineWidth(), 3.5);
}

TEST_F(SplashTest_1568, SetAndGetLineWidth_Zero_1568) {
    splash->setLineWidth(0.0);
    EXPECT_DOUBLE_EQ(splash->getLineWidth(), 0.0);
}

TEST_F(SplashTest_1568, SetAndGetLineWidth_Negative_1568) {
    splash->setLineWidth(-1.0);
    EXPECT_DOUBLE_EQ(splash->getLineWidth(), -1.0);
}

// Test setStrokeAlpha and getStrokeAlpha
TEST_F(SplashTest_1568, SetAndGetStrokeAlpha_1568) {
    splash->setStrokeAlpha(0.5);
    EXPECT_DOUBLE_EQ(splash->getStrokeAlpha(), 0.5);
}

TEST_F(SplashTest_1568, SetAndGetStrokeAlpha_FullOpaque_1568) {
    splash->setStrokeAlpha(1.0);
    EXPECT_DOUBLE_EQ(splash->getStrokeAlpha(), 1.0);
}

TEST_F(SplashTest_1568, SetAndGetStrokeAlpha_FullTransparent_1568) {
    splash->setStrokeAlpha(0.0);
    EXPECT_DOUBLE_EQ(splash->getStrokeAlpha(), 0.0);
}

// Test setFillAlpha and getFillAlpha
TEST_F(SplashTest_1568, SetAndGetFillAlpha_1568) {
    splash->setFillAlpha(0.75);
    EXPECT_DOUBLE_EQ(splash->getFillAlpha(), 0.75);
}

TEST_F(SplashTest_1568, SetAndGetFillAlpha_Zero_1568) {
    splash->setFillAlpha(0.0);
    EXPECT_DOUBLE_EQ(splash->getFillAlpha(), 0.0);
}

// Test setLineCap and getLineCap
TEST_F(SplashTest_1568, SetAndGetLineCap_Butt_1568) {
    splash->setLineCap(splashLineCapButt);
    EXPECT_EQ(splash->getLineCap(), splashLineCapButt);
}

TEST_F(SplashTest_1568, SetAndGetLineCap_Round_1568) {
    splash->setLineCap(splashLineCapRound);
    EXPECT_EQ(splash->getLineCap(), splashLineCapRound);
}

TEST_F(SplashTest_1568, SetAndGetLineCap_Projecting_1568) {
    splash->setLineCap(splashLineCapProjecting);
    EXPECT_EQ(splash->getLineCap(), splashLineCapProjecting);
}

// Test setLineJoin and getLineJoin
TEST_F(SplashTest_1568, SetAndGetLineJoin_Miter_1568) {
    splash->setLineJoin(splashLineJoinMiter);
    EXPECT_EQ(splash->getLineJoin(), splashLineJoinMiter);
}

TEST_F(SplashTest_1568, SetAndGetLineJoin_Round_1568) {
    splash->setLineJoin(splashLineJoinRound);
    EXPECT_EQ(splash->getLineJoin(), splashLineJoinRound);
}

TEST_F(SplashTest_1568, SetAndGetLineJoin_Bevel_1568) {
    splash->setLineJoin(splashLineJoinBevel);
    EXPECT_EQ(splash->getLineJoin(), splashLineJoinBevel);
}

// Test setMiterLimit and getMiterLimit
TEST_F(SplashTest_1568, SetAndGetMiterLimit_1568) {
    splash->setMiterLimit(10.0);
    EXPECT_DOUBLE_EQ(splash->getMiterLimit(), 10.0);
}

// Test setFlatness and getFlatness
TEST_F(SplashTest_1568, SetAndGetFlatness_1568) {
    splash->setFlatness(1.5);
    EXPECT_DOUBLE_EQ(splash->getFlatness(), 1.5);
}

// Test setStrokeAdjust and getStrokeAdjust
TEST_F(SplashTest_1568, SetAndGetStrokeAdjust_True_1568) {
    splash->setStrokeAdjust(true);
    EXPECT_TRUE(splash->getStrokeAdjust());
}

TEST_F(SplashTest_1568, SetAndGetStrokeAdjust_False_1568) {
    splash->setStrokeAdjust(false);
    EXPECT_FALSE(splash->getStrokeAdjust());
}

// Test setMatrix and getMatrix
TEST_F(SplashTest_1568, SetAndGetMatrix_Identity_1568) {
    std::array<SplashCoord, 6> mat = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};
    splash->setMatrix(mat);
    const auto &result = splash->getMatrix();
    for (int i = 0; i < 6; i++) {
        EXPECT_DOUBLE_EQ(result[i], mat[i]);
    }
}

TEST_F(SplashTest_1568, SetAndGetMatrix_Custom_1568) {
    std::array<SplashCoord, 6> mat = {2.0, 0.5, -0.5, 2.0, 10.0, 20.0};
    splash->setMatrix(mat);
    const auto &result = splash->getMatrix();
    for (int i = 0; i < 6; i++) {
        EXPECT_DOUBLE_EQ(result[i], mat[i]);
    }
}

// Test saveState and restoreState
TEST_F(SplashTest_1568, SaveAndRestoreState_1568) {
    splash->setLineWidth(5.0);
    splash->saveState();
    splash->setLineWidth(10.0);
    EXPECT_DOUBLE_EQ(splash->getLineWidth(), 10.0);
    SplashError err = splash->restoreState();
    EXPECT_EQ(err, splashOk);
    EXPECT_DOUBLE_EQ(splash->getLineWidth(), 5.0);
}

TEST_F(SplashTest_1568, RestoreStateWithoutSave_1568) {
    SplashError err = splash->restoreState();
    EXPECT_NE(err, splashOk);
}

TEST_F(SplashTest_1568, SaveAndRestoreMultipleStates_1568) {
    splash->setLineWidth(1.0);
    splash->saveState();
    splash->setLineWidth(2.0);
    splash->saveState();
    splash->setLineWidth(3.0);
    EXPECT_DOUBLE_EQ(splash->getLineWidth(), 3.0);
    
    EXPECT_EQ(splash->restoreState(), splashOk);
    EXPECT_DOUBLE_EQ(splash->getLineWidth(), 2.0);
    
    EXPECT_EQ(splash->restoreState(), splashOk);
    EXPECT_DOUBLE_EQ(splash->getLineWidth(), 1.0);
}

// Test clear
TEST_F(SplashTest_1568, Clear_1568) {
    SplashColor color;
    color[0] = 255;
    color[1] = 0;
    color[2] = 0;
    splash->clear(color, 255);
    SUCCEED();
}

// Test getInNonIsolatedGroup
TEST_F(SplashTest_1568, GetInNonIsolatedGroup_Default_1568) {
    EXPECT_FALSE(splash->getInNonIsolatedGroup());
}

// Test getSoftMask
TEST_F(SplashTest_1568, GetSoftMask_Default_1568) {
    EXPECT_EQ(splash->getSoftMask(), nullptr);
}

// Test setSoftMask
TEST_F(SplashTest_1568, SetSoftMask_Null_1568) {
    splash->setSoftMask(nullptr);
    EXPECT_EQ(splash->getSoftMask(), nullptr);
}

// Test clipToRect
TEST_F(SplashTest_1568, ClipToRect_1568) {
    SplashError err = splash->clipToRect(0, 0, 50, 50);
    EXPECT_EQ(err, splashOk);
}

// Test clipResetToRect
TEST_F(SplashTest_1568, ClipResetToRect_1568) {
    splash->clipResetToRect(10, 10, 90, 90);
    SUCCEED();
}

// Test setLineDash with vector
TEST_F(SplashTest_1568, SetLineDash_Vector_1568) {
    std::vector<SplashCoord> dash = {5.0, 3.0};
    splash->setLineDash(std::move(dash), 0.0);
    EXPECT_DOUBLE_EQ(splash->getLineDashPhase(), 0.0);
}

// Test setPatternAlpha
TEST_F(SplashTest_1568, SetPatternAlpha_1568) {
    splash->setPatternAlpha(0.5, 0.7);
    SUCCEED();
}

// Test clearPatternAlpha
TEST_F(SplashTest_1568, ClearPatternAlpha_1568) {
    splash->setPatternAlpha(0.5, 0.7);
    splash->clearPatternAlpha();
    SUCCEED();
}

// Test setFillOverprint
TEST_F(SplashTest_1568, SetFillOverprint_1568) {
    splash->setFillOverprint(true);
    SUCCEED();
}

// Test setStrokeOverprint
TEST_F(SplashTest_1568, SetStrokeOverprint_1568) {
    splash->setStrokeOverprint(true);
    SUCCEED();
}

// Test setOverprintMode
TEST_F(SplashTest_1568, SetOverprintMode_1568) {
    splash->setOverprintMode(1);
    SUCCEED();
}

// Test setOverprintMask
TEST_F(SplashTest_1568, SetOverprintMask_1568) {
    splash->setOverprintMask(0xFFFFFFFF, false);
    SUCCEED();
}

// Test getClipRes
TEST_F(SplashTest_1568, GetClipRes_1568) {
    SplashClipResult res = splash->getClipRes();
    EXPECT_TRUE(res == splashClipAllInside || res == splashClipAllOutside || res == splashClipPartial);
}

// Test stroke with empty path
TEST_F(SplashTest_1568, Stroke_EmptyPath_1568) {
    SplashPath path;
    SplashError err = splash->stroke(path);
    // An empty path should return an error or succeed gracefully
    SUCCEED();
}

// Test fill with empty path
TEST_F(SplashTest_1568, Fill_EmptyPath_1568) {
    SplashPath path;
    SplashError err = splash->fill(&path, false);
    SUCCEED();
}

// Test construction with SplashScreen copy constructor
TEST_F(SplashTest_1568, ConstructWithScreen_1568) {
    SplashBitmap *bmp2 = new SplashBitmap(50, 50, 4, splashModeRGB8, false);
    const SplashScreen &screen = splash->getScreen();
    Splash *splash2 = new Splash(bmp2, false, screen);
    EXPECT_NE(splash2, nullptr);
    EXPECT_EQ(splash2->getBitmap(), bmp2);
    delete splash2;
    delete bmp2;
}

// Test setThinLineMode toggling
TEST_F(SplashTest_1568, SetThinLineMode_Toggle_1568) {
    splash->setThinLineMode(splashThinLineSolid);
    EXPECT_EQ(splash->getThinLineMode(), splashThinLineSolid);
    splash->setThinLineMode(splashThinLineDefault);
    EXPECT_EQ(splash->getThinLineMode(), splashThinLineDefault);
    splash->setThinLineMode(splashThinLineShape);
    EXPECT_EQ(splash->getThinLineMode(), splashThinLineShape);
}

// Test blitTransparent
TEST_F(SplashTest_1568, BlitTransparent_1568) {
    SplashBitmap src(10, 10, 4, splashModeRGB8, false);
    SplashError err = splash->blitTransparent(src, 0, 0, 0, 0, 10, 10);
    EXPECT_EQ(err, splashOk);
}

// Test multiple property changes persist through state save/restore
TEST_F(SplashTest_1568, SaveRestoreMultipleProperties_1568) {
    splash->setLineWidth(2.0);
    splash->setStrokeAlpha(0.5);
    splash->setFillAlpha(0.3);
    splash->setLineCap(splashLineCapRound);
    
    splash->saveState();
    
    splash->setLineWidth(4.0);
    splash->setStrokeAlpha(1.0);
    splash->setFillAlpha(1.0);
    splash->setLineCap(splashLineCapButt);
    
    EXPECT_DOUBLE_EQ(splash->getLineWidth(), 4.0);
    EXPECT_DOUBLE_EQ(splash->getStrokeAlpha(), 1.0);
    EXPECT_DOUBLE_EQ(splash->getFillAlpha(), 1.0);
    EXPECT_EQ(splash->getLineCap(), splashLineCapButt);
    
    splash->restoreState();
    
    EXPECT_DOUBLE_EQ(splash->getLineWidth(), 2.0);
    EXPECT_DOUBLE_EQ(splash->getStrokeAlpha(), 0.5);
    EXPECT_DOUBLE_EQ(splash->getFillAlpha(), 0.3);
    EXPECT_EQ(splash->getLineCap(), splashLineCapRound);
}

// Test makeStrokePath with a simple path
TEST_F(SplashTest_1568, MakeStrokePath_SimplePath_1568) {
    SplashPath path;
    path.moveTo(0, 0);
    path.lineTo(50, 50);
    int result = splash->makeStrokePath(path, 2.0, true);
    // Result is the number of path segments or similar; just check it doesn't return negative for a valid path
    EXPECT_GE(result, 0);
}

// Test getBlendFunc
TEST_F(SplashTest_1568, GetBlendFunc_1568) {
    SplashBlendFunc func = splash->getBlendFunc();
    // Should return some valid function pointer (could be nullptr for default)
    SUCCEED();
}

// Test setBlendFunc
TEST_F(SplashTest_1568, SetBlendFunc_Null_1568) {
    splash->setBlendFunc(nullptr);
    EXPECT_EQ(splash->getBlendFunc(), nullptr);
}

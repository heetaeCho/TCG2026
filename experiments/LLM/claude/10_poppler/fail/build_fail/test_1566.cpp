#include <gtest/gtest.h>
#include "splash/Splash.h"
#include "splash/SplashBitmap.h"
#include "splash/SplashTypes.h"
#include "splash/SplashPattern.h"
#include "splash/SplashScreen.h"
#include "splash/SplashPath.h"
#include "splash/SplashState.h"

class SplashTest_1566 : public ::testing::Test {
protected:
    SplashBitmap *bitmap;
    Splash *splash;

    void SetUp() override {
        // Create a simple bitmap for testing - RGB8, 100x100
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

// Test setMinLineWidth and verify it doesn't crash
TEST_F(SplashTest_1566, SetMinLineWidth_Normal_1566) {
    splash->setMinLineWidth(1.0);
    // No crash means success - minLineWidth is private, can't directly verify
}

TEST_F(SplashTest_1566, SetMinLineWidth_Zero_1566) {
    splash->setMinLineWidth(0.0);
}

TEST_F(SplashTest_1566, SetMinLineWidth_Negative_1566) {
    splash->setMinLineWidth(-1.0);
}

TEST_F(SplashTest_1566, SetMinLineWidth_Large_1566) {
    splash->setMinLineWidth(1000.0);
}

TEST_F(SplashTest_1566, SetMinLineWidth_VerySmall_1566) {
    splash->setMinLineWidth(0.001);
}

// Test setThinLineMode / getThinLineMode
TEST_F(SplashTest_1566, SetAndGetThinLineMode_None_1566) {
    splash->setThinLineMode(splashThinLineDefault);
    EXPECT_EQ(splashThinLineDefault, splash->getThinLineMode());
}

TEST_F(SplashTest_1566, SetAndGetThinLineMode_Solid_1566) {
    splash->setThinLineMode(splashThinLineSolid);
    EXPECT_EQ(splashThinLineSolid, splash->getThinLineMode());
}

TEST_F(SplashTest_1566, SetAndGetThinLineMode_Shape_1566) {
    splash->setThinLineMode(splashThinLineShape);
    EXPECT_EQ(splashThinLineShape, splash->getThinLineMode());
}

// Test setDebugMode
TEST_F(SplashTest_1566, SetDebugMode_True_1566) {
    splash->setDebugMode(true);
    // No crash means success - debugMode is private
}

TEST_F(SplashTest_1566, SetDebugMode_False_1566) {
    splash->setDebugMode(false);
}

// Test setInShading
TEST_F(SplashTest_1566, SetInShading_True_1566) {
    splash->setInShading(true);
}

TEST_F(SplashTest_1566, SetInShading_False_1566) {
    splash->setInShading(false);
}

// Test getBitmap
TEST_F(SplashTest_1566, GetBitmap_ReturnsSameBitmap_1566) {
    SplashBitmap *result = splash->getBitmap();
    EXPECT_EQ(bitmap, result);
}

// Test getVectorAntialias / setVectorAntialias
TEST_F(SplashTest_1566, GetVectorAntialias_InitialValue_1566) {
    // Created with vectorAntialiasA = false
    EXPECT_FALSE(splash->getVectorAntialias());
}

TEST_F(SplashTest_1566, SetVectorAntialias_True_1566) {
    splash->setVectorAntialias(true);
    EXPECT_TRUE(splash->getVectorAntialias());
}

TEST_F(SplashTest_1566, SetVectorAntialias_False_1566) {
    splash->setVectorAntialias(false);
    EXPECT_FALSE(splash->getVectorAntialias());
}

TEST_F(SplashTest_1566, SetVectorAntialias_Toggle_1566) {
    splash->setVectorAntialias(true);
    EXPECT_TRUE(splash->getVectorAntialias());
    splash->setVectorAntialias(false);
    EXPECT_FALSE(splash->getVectorAntialias());
}

// Test setLineWidth / getLineWidth
TEST_F(SplashTest_1566, SetAndGetLineWidth_1566) {
    splash->setLineWidth(2.5);
    EXPECT_DOUBLE_EQ(2.5, splash->getLineWidth());
}

TEST_F(SplashTest_1566, SetAndGetLineWidth_Zero_1566) {
    splash->setLineWidth(0.0);
    EXPECT_DOUBLE_EQ(0.0, splash->getLineWidth());
}

// Test setStrokeAlpha / getStrokeAlpha
TEST_F(SplashTest_1566, SetAndGetStrokeAlpha_1566) {
    splash->setStrokeAlpha(0.5);
    EXPECT_DOUBLE_EQ(0.5, splash->getStrokeAlpha());
}

TEST_F(SplashTest_1566, SetAndGetStrokeAlpha_Full_1566) {
    splash->setStrokeAlpha(1.0);
    EXPECT_DOUBLE_EQ(1.0, splash->getStrokeAlpha());
}

TEST_F(SplashTest_1566, SetAndGetStrokeAlpha_Zero_1566) {
    splash->setStrokeAlpha(0.0);
    EXPECT_DOUBLE_EQ(0.0, splash->getStrokeAlpha());
}

// Test setFillAlpha / getFillAlpha
TEST_F(SplashTest_1566, SetAndGetFillAlpha_1566) {
    splash->setFillAlpha(0.75);
    EXPECT_DOUBLE_EQ(0.75, splash->getFillAlpha());
}

TEST_F(SplashTest_1566, SetAndGetFillAlpha_Zero_1566) {
    splash->setFillAlpha(0.0);
    EXPECT_DOUBLE_EQ(0.0, splash->getFillAlpha());
}

// Test setLineCap / getLineCap
TEST_F(SplashTest_1566, SetAndGetLineCap_Butt_1566) {
    splash->setLineCap(splashLineCapButt);
    EXPECT_EQ(splashLineCapButt, splash->getLineCap());
}

TEST_F(SplashTest_1566, SetAndGetLineCap_Round_1566) {
    splash->setLineCap(splashLineCapRound);
    EXPECT_EQ(splashLineCapRound, splash->getLineCap());
}

TEST_F(SplashTest_1566, SetAndGetLineCap_Projecting_1566) {
    splash->setLineCap(splashLineCapProjecting);
    EXPECT_EQ(splashLineCapProjecting, splash->getLineCap());
}

// Test setLineJoin / getLineJoin
TEST_F(SplashTest_1566, SetAndGetLineJoin_Miter_1566) {
    splash->setLineJoin(splashLineJoinMiter);
    EXPECT_EQ(splashLineJoinMiter, splash->getLineJoin());
}

TEST_F(SplashTest_1566, SetAndGetLineJoin_Round_1566) {
    splash->setLineJoin(splashLineJoinRound);
    EXPECT_EQ(splashLineJoinRound, splash->getLineJoin());
}

TEST_F(SplashTest_1566, SetAndGetLineJoin_Bevel_1566) {
    splash->setLineJoin(splashLineJoinBevel);
    EXPECT_EQ(splashLineJoinBevel, splash->getLineJoin());
}

// Test setMiterLimit / getMiterLimit
TEST_F(SplashTest_1566, SetAndGetMiterLimit_1566) {
    splash->setMiterLimit(10.0);
    EXPECT_DOUBLE_EQ(10.0, splash->getMiterLimit());
}

// Test setFlatness / getFlatness
TEST_F(SplashTest_1566, SetAndGetFlatness_1566) {
    splash->setFlatness(1.5);
    EXPECT_DOUBLE_EQ(1.5, splash->getFlatness());
}

// Test setStrokeAdjust / getStrokeAdjust
TEST_F(SplashTest_1566, SetAndGetStrokeAdjust_True_1566) {
    splash->setStrokeAdjust(true);
    EXPECT_TRUE(splash->getStrokeAdjust());
}

TEST_F(SplashTest_1566, SetAndGetStrokeAdjust_False_1566) {
    splash->setStrokeAdjust(false);
    EXPECT_FALSE(splash->getStrokeAdjust());
}

// Test setMatrix / getMatrix
TEST_F(SplashTest_1566, SetAndGetMatrix_1566) {
    std::array<SplashCoord, 6> mat = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};
    splash->setMatrix(mat);
    const auto &result = splash->getMatrix();
    for (int i = 0; i < 6; i++) {
        EXPECT_DOUBLE_EQ(mat[i], result[i]);
    }
}

TEST_F(SplashTest_1566, SetAndGetMatrix_NonIdentity_1566) {
    std::array<SplashCoord, 6> mat = {2.0, 0.5, -0.5, 2.0, 10.0, 20.0};
    splash->setMatrix(mat);
    const auto &result = splash->getMatrix();
    for (int i = 0; i < 6; i++) {
        EXPECT_DOUBLE_EQ(mat[i], result[i]);
    }
}

// Test saveState / restoreState
TEST_F(SplashTest_1566, SaveAndRestoreState_1566) {
    splash->setLineWidth(5.0);
    splash->saveState();
    splash->setLineWidth(10.0);
    EXPECT_DOUBLE_EQ(10.0, splash->getLineWidth());
    SplashError err = splash->restoreState();
    EXPECT_EQ(splashOk, err);
    EXPECT_DOUBLE_EQ(5.0, splash->getLineWidth());
}

TEST_F(SplashTest_1566, RestoreStateWithoutSave_1566) {
    SplashError err = splash->restoreState();
    EXPECT_NE(splashOk, err);
}

TEST_F(SplashTest_1566, SaveAndRestoreState_Multiple_1566) {
    splash->setLineWidth(1.0);
    splash->saveState();
    splash->setLineWidth(2.0);
    splash->saveState();
    splash->setLineWidth(3.0);
    EXPECT_DOUBLE_EQ(3.0, splash->getLineWidth());
    
    splash->restoreState();
    EXPECT_DOUBLE_EQ(2.0, splash->getLineWidth());
    
    splash->restoreState();
    EXPECT_DOUBLE_EQ(1.0, splash->getLineWidth());
}

// Test clear
TEST_F(SplashTest_1566, Clear_1566) {
    SplashColor color;
    color[0] = 255;
    color[1] = 0;
    color[2] = 0;
    splash->clear(color, 255);
    // Verify through bitmap
    SplashBitmap *bmp = splash->getBitmap();
    EXPECT_NE(nullptr, bmp);
}

// Test getInNonIsolatedGroup
TEST_F(SplashTest_1566, GetInNonIsolatedGroup_Initial_1566) {
    EXPECT_FALSE(splash->getInNonIsolatedGroup());
}

// Test getSoftMask
TEST_F(SplashTest_1566, GetSoftMask_Initial_1566) {
    SplashBitmap *mask = splash->getSoftMask();
    EXPECT_EQ(nullptr, mask);
}

// Test clipToRect
TEST_F(SplashTest_1566, ClipToRect_ValidRect_1566) {
    SplashError err = splash->clipToRect(10.0, 10.0, 90.0, 90.0);
    EXPECT_EQ(splashOk, err);
}

// Test clipResetToRect
TEST_F(SplashTest_1566, ClipResetToRect_1566) {
    splash->clipResetToRect(0.0, 0.0, 100.0, 100.0);
    // No crash means success
}

// Test setOverprintMask
TEST_F(SplashTest_1566, SetOverprintMask_1566) {
    splash->setOverprintMask(0xFFFFFFFF, false);
}

TEST_F(SplashTest_1566, SetOverprintMask_Additive_1566) {
    splash->setOverprintMask(0x0F, true);
}

// Test setFillOverprint / setStrokeOverprint
TEST_F(SplashTest_1566, SetFillOverprint_1566) {
    splash->setFillOverprint(true);
    splash->setFillOverprint(false);
}

TEST_F(SplashTest_1566, SetStrokeOverprint_1566) {
    splash->setStrokeOverprint(true);
    splash->setStrokeOverprint(false);
}

// Test setOverprintMode
TEST_F(SplashTest_1566, SetOverprintMode_1566) {
    splash->setOverprintMode(0);
    splash->setOverprintMode(1);
}

// Test setPatternAlpha / clearPatternAlpha
TEST_F(SplashTest_1566, SetAndClearPatternAlpha_1566) {
    splash->setPatternAlpha(0.5, 0.7);
    splash->clearPatternAlpha();
}

// Test getClipRes
TEST_F(SplashTest_1566, GetClipRes_1566) {
    SplashClipResult res = splash->getClipRes();
    // Just verify it returns a valid value
    EXPECT_TRUE(res == splashClipAllInside || res == splashClipAllOutside || res == splashClipPartial);
}

// Test setLineDash with vector
TEST_F(SplashTest_1566, SetLineDash_Vector_1566) {
    std::vector<SplashCoord> dash = {5.0, 3.0};
    splash->setLineDash(std::move(dash), 0.0);
    EXPECT_DOUBLE_EQ(0.0, splash->getLineDashPhase());
}

TEST_F(SplashTest_1566, SetLineDash_EmptyVector_1566) {
    std::vector<SplashCoord> dash;
    splash->setLineDash(std::move(dash), 0.0);
}

// Test stroke with empty path
TEST_F(SplashTest_1566, Stroke_EmptyPath_1566) {
    SplashPath path;
    splash->setLineWidth(1.0);
    SplashError err = splash->stroke(path);
    // Empty path - behavior depends on implementation
    // Just check it doesn't crash
    (void)err;
}

// Test that bitmap width/height are consistent
TEST_F(SplashTest_1566, BitmapConsistency_1566) {
    SplashBitmap *bmp = splash->getBitmap();
    ASSERT_NE(nullptr, bmp);
    EXPECT_EQ(100, bmp->getWidth());
    EXPECT_EQ(100, bmp->getHeight());
}

// Test with vectorAntialias enabled
class SplashAATest_1566 : public ::testing::Test {
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
        splash = new Splash(bitmap, true, &screenParams);
    }

    void TearDown() override {
        delete splash;
        delete bitmap;
    }
};

TEST_F(SplashAATest_1566, VectorAntialias_Enabled_1566) {
    EXPECT_TRUE(splash->getVectorAntialias());
}

TEST_F(SplashAATest_1566, SetMinLineWidth_WithAA_1566) {
    splash->setMinLineWidth(0.5);
    // No crash
}

// Test multiple state properties persist through save/restore
TEST_F(SplashTest_1566, SaveRestoreMultipleProperties_1566) {
    splash->setLineWidth(3.0);
    splash->setStrokeAlpha(0.8);
    splash->setFillAlpha(0.6);
    splash->setLineCap(splashLineCapRound);
    splash->setLineJoin(splashLineJoinBevel);

    splash->saveState();

    splash->setLineWidth(7.0);
    splash->setStrokeAlpha(0.3);
    splash->setFillAlpha(0.2);
    splash->setLineCap(splashLineCapProjecting);
    splash->setLineJoin(splashLineJoinMiter);

    EXPECT_DOUBLE_EQ(7.0, splash->getLineWidth());
    EXPECT_DOUBLE_EQ(0.3, splash->getStrokeAlpha());

    SplashError err = splash->restoreState();
    EXPECT_EQ(splashOk, err);

    EXPECT_DOUBLE_EQ(3.0, splash->getLineWidth());
    EXPECT_DOUBLE_EQ(0.8, splash->getStrokeAlpha());
    EXPECT_DOUBLE_EQ(0.6, splash->getFillAlpha());
    EXPECT_EQ(splashLineCapRound, splash->getLineCap());
    EXPECT_EQ(splashLineJoinBevel, splash->getLineJoin());
}

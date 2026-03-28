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

class SplashTest_1569 : public ::testing::Test {
protected:
    SplashBitmap *bitmap;
    Splash *splash;

    void SetUp() override {
        // Create a simple bitmap for testing - 100x100, RGB8
        bitmap = new SplashBitmap(100, 100, 4, splashModeRGB8, false);
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
        // Note: Splash may or may not own the bitmap; typically it does not delete it
        delete bitmap;
    }
};

// Test getClipRes returns a valid SplashClipResult
TEST_F(SplashTest_1569, GetClipRes_DefaultValue_1569) {
    SplashClipResult res = splash->getClipRes();
    // The result should be one of the valid enum values
    EXPECT_TRUE(res == splashClipAllInside || 
                res == splashClipAllOutside || 
                res == splashClipPartial);
}

// Test getBitmap returns the bitmap passed to the constructor
TEST_F(SplashTest_1569, GetBitmap_ReturnsBitmapPassedToConstructor_1569) {
    SplashBitmap *result = splash->getBitmap();
    EXPECT_EQ(result, bitmap);
}

// Test getVectorAntialias returns false when constructed with false
TEST_F(SplashTest_1569, GetVectorAntialias_InitialFalse_1569) {
    bool vaa = splash->getVectorAntialias();
    EXPECT_FALSE(vaa);
}

// Test setVectorAntialias and getVectorAntialias
TEST_F(SplashTest_1569, SetGetVectorAntialias_1569) {
    splash->setVectorAntialias(true);
    EXPECT_TRUE(splash->getVectorAntialias());
    splash->setVectorAntialias(false);
    EXPECT_FALSE(splash->getVectorAntialias());
}

// Test setLineWidth and getLineWidth
TEST_F(SplashTest_1569, SetGetLineWidth_1569) {
    splash->setLineWidth(2.5);
    EXPECT_DOUBLE_EQ(splash->getLineWidth(), 2.5);
}

// Test setLineWidth with zero
TEST_F(SplashTest_1569, SetGetLineWidth_Zero_1569) {
    splash->setLineWidth(0.0);
    EXPECT_DOUBLE_EQ(splash->getLineWidth(), 0.0);
}

// Test setLineWidth with negative value
TEST_F(SplashTest_1569, SetGetLineWidth_Negative_1569) {
    splash->setLineWidth(-1.0);
    EXPECT_DOUBLE_EQ(splash->getLineWidth(), -1.0);
}

// Test setLineCap and getLineCap
TEST_F(SplashTest_1569, SetGetLineCap_Butt_1569) {
    splash->setLineCap(splashLineCapButt);
    EXPECT_EQ(splash->getLineCap(), splashLineCapButt);
}

TEST_F(SplashTest_1569, SetGetLineCap_Round_1569) {
    splash->setLineCap(splashLineCapRound);
    EXPECT_EQ(splash->getLineCap(), splashLineCapRound);
}

TEST_F(SplashTest_1569, SetGetLineCap_Projecting_1569) {
    splash->setLineCap(splashLineCapProjecting);
    EXPECT_EQ(splash->getLineCap(), splashLineCapProjecting);
}

// Test setLineJoin and getLineJoin
TEST_F(SplashTest_1569, SetGetLineJoin_Miter_1569) {
    splash->setLineJoin(splashLineJoinMiter);
    EXPECT_EQ(splash->getLineJoin(), splashLineJoinMiter);
}

TEST_F(SplashTest_1569, SetGetLineJoin_Round_1569) {
    splash->setLineJoin(splashLineJoinRound);
    EXPECT_EQ(splash->getLineJoin(), splashLineJoinRound);
}

TEST_F(SplashTest_1569, SetGetLineJoin_Bevel_1569) {
    splash->setLineJoin(splashLineJoinBevel);
    EXPECT_EQ(splash->getLineJoin(), splashLineJoinBevel);
}

// Test setMiterLimit and getMiterLimit
TEST_F(SplashTest_1569, SetGetMiterLimit_1569) {
    splash->setMiterLimit(10.0);
    EXPECT_DOUBLE_EQ(splash->getMiterLimit(), 10.0);
}

// Test setFlatness and getFlatness
TEST_F(SplashTest_1569, SetGetFlatness_1569) {
    splash->setFlatness(0.5);
    EXPECT_DOUBLE_EQ(splash->getFlatness(), 0.5);
}

// Test setStrokeAlpha and getStrokeAlpha
TEST_F(SplashTest_1569, SetGetStrokeAlpha_1569) {
    splash->setStrokeAlpha(0.75);
    EXPECT_DOUBLE_EQ(splash->getStrokeAlpha(), 0.75);
}

// Test setFillAlpha and getFillAlpha
TEST_F(SplashTest_1569, SetGetFillAlpha_1569) {
    splash->setFillAlpha(0.5);
    EXPECT_DOUBLE_EQ(splash->getFillAlpha(), 0.5);
}

// Test setStrokeAlpha boundary - full opacity
TEST_F(SplashTest_1569, SetStrokeAlpha_FullOpacity_1569) {
    splash->setStrokeAlpha(1.0);
    EXPECT_DOUBLE_EQ(splash->getStrokeAlpha(), 1.0);
}

// Test setStrokeAlpha boundary - zero opacity
TEST_F(SplashTest_1569, SetStrokeAlpha_ZeroOpacity_1569) {
    splash->setStrokeAlpha(0.0);
    EXPECT_DOUBLE_EQ(splash->getStrokeAlpha(), 0.0);
}

// Test setFillAlpha boundary - full opacity
TEST_F(SplashTest_1569, SetFillAlpha_FullOpacity_1569) {
    splash->setFillAlpha(1.0);
    EXPECT_DOUBLE_EQ(splash->getFillAlpha(), 1.0);
}

// Test setFillAlpha boundary - zero opacity
TEST_F(SplashTest_1569, SetFillAlpha_ZeroOpacity_1569) {
    splash->setFillAlpha(0.0);
    EXPECT_DOUBLE_EQ(splash->getFillAlpha(), 0.0);
}

// Test setStrokeAdjust and getStrokeAdjust
TEST_F(SplashTest_1569, SetGetStrokeAdjust_True_1569) {
    splash->setStrokeAdjust(true);
    EXPECT_TRUE(splash->getStrokeAdjust());
}

TEST_F(SplashTest_1569, SetGetStrokeAdjust_False_1569) {
    splash->setStrokeAdjust(false);
    EXPECT_FALSE(splash->getStrokeAdjust());
}

// Test setMatrix and getMatrix
TEST_F(SplashTest_1569, SetGetMatrix_Identity_1569) {
    std::array<SplashCoord, 6> mat = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};
    splash->setMatrix(mat);
    const auto &result = splash->getMatrix();
    for (int i = 0; i < 6; i++) {
        EXPECT_DOUBLE_EQ(result[i], mat[i]);
    }
}

TEST_F(SplashTest_1569, SetGetMatrix_CustomValues_1569) {
    std::array<SplashCoord, 6> mat = {2.0, 0.5, -0.5, 2.0, 10.0, 20.0};
    splash->setMatrix(mat);
    const auto &result = splash->getMatrix();
    for (int i = 0; i < 6; i++) {
        EXPECT_DOUBLE_EQ(result[i], mat[i]);
    }
}

// Test setThinLineMode and getThinLineMode
TEST_F(SplashTest_1569, SetGetThinLineMode_1569) {
    splash->setThinLineMode(splashThinLineDefault);
    EXPECT_EQ(splash->getThinLineMode(), splashThinLineDefault);
}

TEST_F(SplashTest_1569, SetGetThinLineMode_Shape_1569) {
    splash->setThinLineMode(splashThinLineShape);
    EXPECT_EQ(splash->getThinLineMode(), splashThinLineShape);
}

// Test getInNonIsolatedGroup - default should be false
TEST_F(SplashTest_1569, GetInNonIsolatedGroup_Default_1569) {
    EXPECT_FALSE(splash->getInNonIsolatedGroup());
}

// Test getSoftMask - default should be nullptr
TEST_F(SplashTest_1569, GetSoftMask_Default_1569) {
    SplashBitmap *mask = splash->getSoftMask();
    EXPECT_EQ(mask, nullptr);
}

// Test saveState and restoreState
TEST_F(SplashTest_1569, SaveAndRestoreState_1569) {
    splash->setLineWidth(5.0);
    splash->saveState();
    splash->setLineWidth(10.0);
    EXPECT_DOUBLE_EQ(splash->getLineWidth(), 10.0);
    SplashError err = splash->restoreState();
    EXPECT_EQ(err, splashOk);
    EXPECT_DOUBLE_EQ(splash->getLineWidth(), 5.0);
}

// Test restoreState without matching saveState should return error
TEST_F(SplashTest_1569, RestoreState_WithoutSave_1569) {
    SplashError err = splash->restoreState();
    EXPECT_NE(err, splashOk);
}

// Test multiple saveState / restoreState pairs
TEST_F(SplashTest_1569, MultipleSaveRestore_1569) {
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
TEST_F(SplashTest_1569, Clear_1569) {
    SplashColor color;
    color[0] = 255;
    color[1] = 0;
    color[2] = 0;
    splash->clear(color, 255);
    // Verify bitmap has been cleared - check a pixel
    SplashColorPtr data = bitmap->getDataPtr();
    EXPECT_NE(data, nullptr);
}

// Test clipToRect
TEST_F(SplashTest_1569, ClipToRect_ValidRect_1569) {
    SplashError err = splash->clipToRect(10.0, 10.0, 50.0, 50.0);
    EXPECT_EQ(err, splashOk);
}

// Test clipResetToRect
TEST_F(SplashTest_1569, ClipResetToRect_1569) {
    splash->clipResetToRect(0.0, 0.0, 100.0, 100.0);
    // Should not crash and clip should be set
    const SplashClip &clip = splash->getClip();
    (void)clip; // Just verify we can access the clip
}

// Test setLineDash with vector
TEST_F(SplashTest_1569, SetLineDash_Vector_1569) {
    std::vector<SplashCoord> dash = {5.0, 3.0};
    splash->setLineDash(std::move(dash), 0.0);
    EXPECT_DOUBLE_EQ(splash->getLineDashPhase(), 0.0);
}

// Test setLineDash with non-zero phase
TEST_F(SplashTest_1569, SetLineDash_NonZeroPhase_1569) {
    std::vector<SplashCoord> dash = {10.0, 5.0};
    splash->setLineDash(std::move(dash), 2.5);
    EXPECT_DOUBLE_EQ(splash->getLineDashPhase(), 2.5);
}

// Test setMinLineWidth
TEST_F(SplashTest_1569, SetMinLineWidth_1569) {
    splash->setMinLineWidth(0.5);
    // No getter for minLineWidth, but it should not crash
}

// Test setDebugMode
TEST_F(SplashTest_1569, SetDebugMode_1569) {
    splash->setDebugMode(true);
    splash->setDebugMode(false);
    // No getter for debugMode, but it should not crash
}

// Test setInShading
TEST_F(SplashTest_1569, SetInShading_1569) {
    splash->setInShading(true);
    splash->setInShading(false);
    // No getter for inShading, but it should not crash
}

// Test setFillOverprint and setStrokeOverprint
TEST_F(SplashTest_1569, SetFillOverprint_1569) {
    splash->setFillOverprint(true);
    splash->setFillOverprint(false);
}

TEST_F(SplashTest_1569, SetStrokeOverprint_1569) {
    splash->setStrokeOverprint(true);
    splash->setStrokeOverprint(false);
}

// Test setOverprintMode
TEST_F(SplashTest_1569, SetOverprintMode_1569) {
    splash->setOverprintMode(0);
    splash->setOverprintMode(1);
}

// Test setPatternAlpha
TEST_F(SplashTest_1569, SetPatternAlpha_1569) {
    splash->setPatternAlpha(0.5, 0.8);
    // The pattern alpha affects stroke and fill alpha
}

// Test clearPatternAlpha
TEST_F(SplashTest_1569, ClearPatternAlpha_1569) {
    splash->setPatternAlpha(0.5, 0.8);
    splash->clearPatternAlpha();
}

// Test setOverprintMask
TEST_F(SplashTest_1569, SetOverprintMask_1569) {
    splash->setOverprintMask(0xFFFFFFFF, false);
    splash->setOverprintMask(0x0, true);
}

// Test setInNonIsolatedGroup
TEST_F(SplashTest_1569, SetInNonIsolatedGroup_1569) {
    SplashBitmap *alpha0Bmp = new SplashBitmap(100, 100, 4, splashModeRGB8, false);
    splash->setInNonIsolatedGroup(alpha0Bmp, 0, 0);
    EXPECT_TRUE(splash->getInNonIsolatedGroup());
    delete alpha0Bmp;
}

// Test stroke with empty path
TEST_F(SplashTest_1569, Stroke_EmptyPath_1569) {
    SplashPath path;
    SplashError err = splash->stroke(path);
    // Stroking an empty path might return an error or succeed with no effect
    (void)err;
}

// Test stroke with simple line
TEST_F(SplashTest_1569, Stroke_SimpleLine_1569) {
    SplashPath path;
    path.moveTo(10.0, 10.0);
    path.lineTo(50.0, 50.0);
    splash->setLineWidth(1.0);
    SplashError err = splash->stroke(path);
    EXPECT_EQ(err, splashOk);
}

// Test fill with simple rectangle path
TEST_F(SplashTest_1569, Fill_SimpleRect_1569) {
    SplashPath *path = new SplashPath();
    path->moveTo(10.0, 10.0);
    path->lineTo(50.0, 10.0);
    path->lineTo(50.0, 50.0);
    path->lineTo(10.0, 50.0);
    path->close();
    SplashError err = splash->fill(path, false);
    EXPECT_EQ(err, splashOk);
    delete path;
}

// Test blitTransparent
TEST_F(SplashTest_1569, BlitTransparent_1569) {
    SplashBitmap src(50, 50, 4, splashModeRGB8, false);
    SplashError err = splash->blitTransparent(src, 0, 0, 10, 10, 50, 50);
    EXPECT_EQ(err, splashOk);
}

// Test composite
TEST_F(SplashTest_1569, Composite_1569) {
    SplashBitmap src(50, 50, 4, splashModeRGB8, false);
    SplashError err = splash->composite(src, 0, 0, 0, 0, 50, 50, false, false, false, 1.0);
    EXPECT_EQ(err, splashOk);
}

// Test makeStrokePath with simple path
TEST_F(SplashTest_1569, MakeStrokePath_1569) {
    SplashPath path;
    path.moveTo(10.0, 10.0);
    path.lineTo(50.0, 50.0);
    int result = splash->makeStrokePath(path, 2.0, true);
    // Result indicates the number of points or similar; just verify it doesn't crash
    (void)result;
}

// Test with vector antialias enabled
class SplashWithAATest_1569 : public ::testing::Test {
protected:
    SplashBitmap *bitmap;
    Splash *splash;

    void SetUp() override {
        bitmap = new SplashBitmap(100, 100, 4, splashModeRGB8, false);
        SplashScreenParams screenParams;
        screenParams.type = splashScreenDispersed;
        screenParams.size = -1;
        screenParams.dotRadius = -1;
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

TEST_F(SplashWithAATest_1569, VectorAntialiasEnabled_1569) {
    EXPECT_TRUE(splash->getVectorAntialias());
}

TEST_F(SplashWithAATest_1569, StrokeWithAA_1569) {
    SplashPath path;
    path.moveTo(10.0, 10.0);
    path.lineTo(90.0, 90.0);
    splash->setLineWidth(1.0);
    SplashError err = splash->stroke(path);
    EXPECT_EQ(err, splashOk);
}

// Test with Mono8 mode
class SplashMono8Test_1569 : public ::testing::Test {
protected:
    SplashBitmap *bitmap;
    Splash *splash;

    void SetUp() override {
        bitmap = new SplashBitmap(100, 100, 1, splashModeMono8, false);
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

TEST_F(SplashMono8Test_1569, ClearMono8_1569) {
    SplashColor color;
    color[0] = 128;
    splash->clear(color, 255);
    SplashColorPtr data = bitmap->getDataPtr();
    EXPECT_NE(data, nullptr);
}

// Test saveState preserves fill alpha
TEST_F(SplashTest_1569, SaveStatePreservesFillAlpha_1569) {
    splash->setFillAlpha(0.3);
    splash->saveState();
    splash->setFillAlpha(0.9);
    EXPECT_DOUBLE_EQ(splash->getFillAlpha(), 0.9);
    splash->restoreState();
    EXPECT_DOUBLE_EQ(splash->getFillAlpha(), 0.3);
}

// Test saveState preserves stroke alpha
TEST_F(SplashTest_1569, SaveStatePreservesStrokeAlpha_1569) {
    splash->setStrokeAlpha(0.2);
    splash->saveState();
    splash->setStrokeAlpha(0.8);
    EXPECT_DOUBLE_EQ(splash->getStrokeAlpha(), 0.8);
    splash->restoreState();
    EXPECT_DOUBLE_EQ(splash->getStrokeAlpha(), 0.2);
}

// Test saveState preserves line cap
TEST_F(SplashTest_1569, SaveStatePreservesLineCap_1569) {
    splash->setLineCap(splashLineCapRound);
    splash->saveState();
    splash->setLineCap(splashLineCapButt);
    EXPECT_EQ(splash->getLineCap(), splashLineCapButt);
    splash->restoreState();
    EXPECT_EQ(splash->getLineCap(), splashLineCapRound);
}

// Test saveState preserves line join
TEST_F(SplashTest_1569, SaveStatePreservesLineJoin_1569) {
    splash->setLineJoin(splashLineJoinRound);
    splash->saveState();
    splash->setLineJoin(splashLineJoinBevel);
    EXPECT_EQ(splash->getLineJoin(), splashLineJoinBevel);
    splash->restoreState();
    EXPECT_EQ(splash->getLineJoin(), splashLineJoinRound);
}

// Test saveState preserves miter limit
TEST_F(SplashTest_1569, SaveStatePreservesMiterLimit_1569) {
    splash->setMiterLimit(5.0);
    splash->saveState();
    splash->setMiterLimit(15.0);
    EXPECT_DOUBLE_EQ(splash->getMiterLimit(), 15.0);
    splash->restoreState();
    EXPECT_DOUBLE_EQ(splash->getMiterLimit(), 5.0);
}

// Test saveState preserves flatness
TEST_F(SplashTest_1569, SaveStatePreservesFlatness_1569) {
    splash->setFlatness(1.5);
    splash->saveState();
    splash->setFlatness(3.0);
    EXPECT_DOUBLE_EQ(splash->getFlatness(), 3.0);
    splash->restoreState();
    EXPECT_DOUBLE_EQ(splash->getFlatness(), 1.5);
}

// Test clipToRect with inverted coordinates
TEST_F(SplashTest_1569, ClipToRect_InvertedCoords_1569) {
    SplashError err = splash->clipToRect(50.0, 50.0, 10.0, 10.0);
    // Should handle gracefully
    (void)err;
}

// Test setSoftMask and getSoftMask
TEST_F(SplashTest_1569, SetGetSoftMask_1569) {
    SplashBitmap *mask = new SplashBitmap(100, 100, 1, splashModeMono8, false);
    splash->setSoftMask(mask);
    EXPECT_EQ(splash->getSoftMask(), mask);
    // Set to null to clean up
    splash->setSoftMask(nullptr);
}

// Test setTransfer
TEST_F(SplashTest_1569, SetTransfer_1569) {
    unsigned char red[256], green[256], blue[256], gray[256];
    for (int i = 0; i < 256; i++) {
        red[i] = green[i] = blue[i] = gray[i] = (unsigned char)i;
    }
    splash->setTransfer(red, green, blue, gray);
    // Should not crash
}

// Test blitImage (public version)
TEST_F(SplashTest_1569, BlitImage_Public_1569) {
    SplashBitmap src(50, 50, 4, splashModeRGB8, false);
    splash->blitImage(src, false, 10, 10);
    // Should not crash
}

// Test compositeBackground
TEST_F(SplashTest_1569, CompositeBackground_1569) {
    SplashColor color;
    color[0] = 255;
    color[1] = 255;
    color[2] = 255;
    splash->compositeBackground(color);
    // Should not crash
}

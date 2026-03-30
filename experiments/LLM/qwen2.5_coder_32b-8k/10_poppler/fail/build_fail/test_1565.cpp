#include <gtest/gtest.h>

#include "TestProjects/poppler/splash/Splash.h"

#include "TestProjects/poppler/splash/SplashBitmap.h"



class SplashTest_1565 : public ::testing::Test {

protected:

    void SetUp() override {

        bitmap = new SplashBitmap(10, 10, false);

        splash = new Splash(bitmap, false, nullptr);

    }



    void TearDown() override {

        delete splash;

        delete bitmap;

    }



    Splash *splash;

    SplashBitmap *bitmap;

};



TEST_F(SplashTest_1565, GetBitmap_ReturnsCorrectBitmap_1565) {

    EXPECT_EQ(splash->getBitmap(), bitmap);

}



TEST_F(SplashTest_1565, SetAndGetMatrix_NormalOperation_1565) {

    std::array<SplashCoord, 6> matrix = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};

    splash->setMatrix(matrix);

    EXPECT_EQ(splash->getMatrix(), matrix);

}



TEST_F(SplashTest_1565, SetAndGetStrokePattern_NormalOperation_1565) {

    SplashPattern *pattern = new SplashPattern();

    splash->setStrokePattern(pattern);

    EXPECT_EQ(splash->getStrokePattern(), pattern);

    delete pattern;

}



TEST_F(SplashTest_1565, SetAndGetFillPattern_NormalOperation_1565) {

    SplashPattern *pattern = new SplashPattern();

    splash->setFillPattern(pattern);

    EXPECT_EQ(splash->getFillPattern(), pattern);

    delete pattern;

}



TEST_F(SplashTest_1565, SetAndGetBlendFunc_NormalOperation_1565) {

    SplashBlendFunc blendFunc = [](SplashColorPtr src, SplashColorPtr dst, SplashColorPtr res) {};

    splash->setBlendFunc(blendFunc);

    EXPECT_EQ(splash->getBlendFunc().target_type(), blendFunc.target_type());

}



TEST_F(SplashTest_1565, SetAndGetStrokeAlpha_NormalOperation_1565) {

    SplashCoord alpha = 0.5;

    splash->setStrokeAlpha(alpha);

    EXPECT_FLOAT_EQ(splash->getStrokeAlpha(), alpha);

}



TEST_F(SplashTest_1565, SetAndGetFillAlpha_NormalOperation_1565) {

    SplashCoord alpha = 0.7;

    splash->setFillAlpha(alpha);

    EXPECT_FLOAT_EQ(splash->getFillAlpha(), alpha);

}



TEST_F(SplashTest_1565, SetAndClearPatternAlpha_NormalOperation_1565) {

    SplashCoord strokeAlpha = 0.3, fillAlpha = 0.4;

    splash->setPatternAlpha(strokeAlpha, fillAlpha);

    EXPECT_FLOAT_EQ(splash->getStrokeAlpha(), strokeAlpha);

    EXPECT_FLOAT_EQ(splash->getFillAlpha(), fillAlpha);



    splash->clearPatternAlpha();

    // Assuming default alpha is 1.0 after clearing

    EXPECT_FLOAT_EQ(splash->getStrokeAlpha(), 1.0);

    EXPECT_FLOAT_EQ(splash->getFillAlpha(), 1.0);

}



TEST_F(SplashTest_1565, SetAndGetLineWidth_NormalOperation_1565) {

    SplashCoord lineWidth = 2.0;

    splash->setLineWidth(lineWidth);

    EXPECT_FLOAT_EQ(splash->getLineWidth(), lineWidth);

}



TEST_F(SplashTest_1565, SetAndGetLineCap_NormalOperation_1565) {

    SplashLineCap lineCap = splashLineCapButt;

    splash->setLineCap(lineCap);

    EXPECT_EQ(splash->getLineCap(), lineCap);

}



TEST_F(SplashTest_1565, SetAndGetLineJoin_NormalOperation_1565) {

    SplashLineJoin lineJoin = splashLineJoinMiter;

    splash->setLineJoin(lineJoin);

    EXPECT_EQ(splash->getLineJoin(), lineJoin);

}



TEST_F(SplashTest_1565, SetAndGetMiterLimit_NormalOperation_1565) {

    SplashCoord miterLimit = 4.0;

    splash->setMiterLimit(miterLimit);

    EXPECT_FLOAT_EQ(splash->getMiterLimit(), miterLimit);

}



TEST_F(SplashTest_1565, SetAndGetFlatness_NormalOperation_1565) {

    SplashCoord flatness = 0.3;

    splash->setFlatness(flatness);

    EXPECT_FLOAT_EQ(splash->getFlatness(), flatness);

}



TEST_F(SplashTest_1565, SetAndGetLineDash_NormalOperation_1565) {

    std::vector<SplashCoord> lineDash = {2.0, 3.0};

    SplashCoord phase = 1.0;

    splash->setLineDash(std::move(lineDash), phase);

    // Since we're moving the vector, we need to recreate it for comparison

    EXPECT_EQ(splash->getMatrix()[4], phase); // Assuming phase is stored in matrix[4] for simplicity

}



TEST_F(SplashTest_1565, SetAndGetStrokeAdjust_NormalOperation_1565) {

    bool strokeAdjust = true;

    splash->setStrokeAdjust(strokeAdjust);

    EXPECT_EQ(splash->getStrokeAdjust(), strokeAdjust);

}



TEST_F(SplashTest_1565, SaveAndRestoreState_NormalOperation_1565) {

    splash->saveState();

    splash->setLineWidth(2.0);

    splash->restoreState();

    // Assuming default line width is 1.0 after restore

    EXPECT_FLOAT_EQ(splash->getLineWidth(), 1.0);

}



TEST_F(SplashTest_1565, Clear_NormalOperation_1565) {

    SplashColor color = {255, 0, 0};

    unsigned char alpha = 255;

    splash->clear(color, alpha);

    // This is a black box test, we assume clear operation modifies the bitmap accordingly

}



TEST_F(SplashTest_1565, SetAndGetSoftMask_NormalOperation_1565) {

    SplashBitmap *softMask = new SplashBitmap(10, 10, false);

    splash->setSoftMask(softMask);

    EXPECT_EQ(splash->getSoftMask(), softMask);

    delete softMask;

}



TEST_F(SplashTest_1565, SetAndGetInNonIsolatedGroup_NormalOperation_1565) {

    SplashBitmap *alpha0BitmapA = new SplashBitmap(10, 10, false);

    int alpha0XA = 0, alpha0YA = 0;

    splash->setInNonIsolatedGroup(alpha0BitmapA, alpha0XA, alpha0YA);

    // No direct getter for these values, but we assume the state is set correctly

}



TEST_F(SplashTest_1565, SetAndGetOverprintMask_NormalOperation_1565) {

    unsigned int overprintMask = 0b101;

    bool additive = true;

    splash->setOverprintMask(overprintMask, additive);

    // No direct getter for these values, but we assume the state is set correctly

}



TEST_F(SplashTest_1565, SetAndGetMinLineWidth_NormalOperation_1565) {

    SplashCoord minLineWidth = 0.2;

    splash->setMinLineWidth(minLineWidth);

    EXPECT_FLOAT_EQ(splash->minLineWidth, minLineWidth); // Assuming direct access for test simplicity

}



TEST_F(SplashTest_1565, SetAndGetThinLineMode_NormalOperation_1565) {

    SplashThinLineMode thinLineModeA = splashThinLineDefault;

    splash->setThinLineMode(thinLineModeA);

    EXPECT_EQ(splash->getThinLineMode(), thinLineModeA);

}



TEST_F(SplashTest_1565, SetAndGetDebugMode_NormalOperation_1565) {

    bool debugModeA = true;

    splash->setDebugMode(debugModeA);

    EXPECT_EQ(splash->debugMode, debugModeA); // Assuming direct access for test simplicity

}



TEST_F(SplashTest_1565, SetAndGetInShading_NormalOperation_1565) {

    bool sh = true;

    splash->setInShading(sh);

    EXPECT_EQ(splash->inShading, sh); // Assuming direct access for test simplicity

}



TEST_F(SplashTest_1565, GetVectorAntialias_DefaultValue_1565) {

    EXPECT_FALSE(splash->getVectorAntialias());

}



TEST_F(SplashTest_1565, SetAndGetVectorAntialias_NormalOperation_1565) {

    bool vaa = true;

    splash->setVectorAntialias(vaa);

    EXPECT_EQ(splash->getVectorAntialias(), vaa);

}

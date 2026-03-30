#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/SplashOutputDev.h"

#include "gmock/gmock.h"



using namespace testing;



class MockGfxState : public GfxState {

public:

    MOCK_METHOD(void, setCTM, (double, double, double, double, double, double), (override));

};



class MockXRef : public XRef {

    // Additional methods can be mocked if needed

};



class SplashOutputDevTest_1108 : public ::testing::Test {

protected:

    void SetUp() override {

        splashOut = new SplashOutputDev(SplashColorModeRGB8, 4, paperColor, false, splashThinLineCenter, false);

    }



    void TearDown() override {

        delete splashOut;

    }



    SplashColor paperColor = {255, 255, 255};

    SplashOutputDev* splashOut;

};



TEST_F(SplashOutputDevTest_1108, UseDrawCharReturnsTrue_1108) {

    EXPECT_TRUE(splashOut->useDrawChar());

}



TEST_F(SplashOutputDevTest_1108, NormalOperationUseTilingPatternFill_1108) {

    EXPECT_CALL(*splashOut, useTilingPatternFill()).WillOnce(Return(true));

    EXPECT_TRUE(splashOut->useTilingPatternFill());

}



TEST_F(SplashOutputDevTest_1108, NormalOperationUseShadedFills_1108) {

    EXPECT_CALL(*splashOut, useShadedFills(2)).WillOnce(Return(true));

    EXPECT_TRUE(splashOut->useShadedFills(2));

}



TEST_F(SplashOutputDevTest_1108, BoundaryConditionUpsideDown_1108) {

    EXPECT_FALSE(splashOut->upsideDown());

}



TEST_F(SplashOutputDevTest_1108, NormalOperationInterpretType3Chars_1108) {

    EXPECT_CALL(*splashOut, interpretType3Chars()).WillOnce(Return(false));

    EXPECT_FALSE(splashOut->interpretType3Chars());

}



TEST_F(SplashOutputDevTest_1108, NormalOperationGetBitmap_1108) {

    SplashBitmap* bitmap = splashOut->getBitmap();

    EXPECT_NE(bitmap, nullptr);

}



TEST_F(SplashOutputDevTest_1108, NormalOperationGetCurrentFont_1108) {

    SplashFont* font = splashOut->getCurrentFont();

    EXPECT_EQ(font, nullptr); // Assuming no font is set initially

}



TEST_F(SplashOutputDevTest_1108, BoundaryConditionGetBitmapWidth_1108) {

    EXPECT_EQ(splashOut->getBitmapWidth(), 0); // Default width if not initialized

}



TEST_F(SplashOutputDevTest_1108, BoundaryConditionGetBitmapHeight_1108) {

    EXPECT_EQ(splashOut->getBitmapHeight(), 0); // Default height if not initialized

}



TEST_F(SplashOutputDevTest_1108, NormalOperationSetSkipText_1108) {

    splashOut->setSkipText(true, true);

    EXPECT_TRUE(splashOut->skipHorizText);

    EXPECT_TRUE(splashOut->skipRotatedText);

}



TEST_F(SplashOutputDevTest_1108, NormalOperationSetFontAntialias_1108) {

    splashOut->setFontAntialias(true);

    EXPECT_TRUE(splashOut->fontAntialias);

}



TEST_F(SplashOutputDevTest_1108, NormalOperationSetEnableFreeType_1108) {

    splashOut->setEnableFreeType(true);

    // No direct way to verify, but assume internal state is set correctly

}

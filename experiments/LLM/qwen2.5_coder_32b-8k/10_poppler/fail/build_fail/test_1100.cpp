#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/SplashOutputDev.h"

#include "TestProjects/poppler/poppler/GfxState.h"



using namespace testing;



class SplashGouraudPatternTest : public ::testing::Test {

protected:

    GfxGouraudTriangleShading mockShading;

    bool bDirectColorTranslation = true;



    std::unique_ptr<SplashGouraudPattern> pattern;



    void SetUp() override {

        pattern = std::make_unique<SplashGouraudPattern>(bDirectColorTranslation, &mockShading);

    }

};



TEST_F(SplashGouraudPatternTest_1100, IsCMYK_ReturnsTrueForCMYKMode_1100) {

    pattern->gfxMode = csDeviceCMYK;

    EXPECT_TRUE(pattern->isCMYK());

}



TEST_F(SplashGouraudPatternTest_1100, IsCMYK_ReturnsFalseForNonCMYKMode_1100) {

    pattern->gfxMode = csDeviceRGB;

    EXPECT_FALSE(pattern->isCMYK());

}

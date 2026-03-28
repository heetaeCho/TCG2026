#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/SplashOutputDev.h"



class SplashOutputDevTest : public ::testing::Test {

protected:

    void SetUp() override {

        splashOutputDev = new SplashOutputDev(SplashColorModeRGB8, 1, nullptr, false, splashThinLineDefault, false);

    }



    void TearDown() override {

        delete splashOutputDev;

    }



    SplashOutputDev* splashOutputDev;

};



TEST_F(SplashOutputDevTest_1114, GetFontAntialias_DefaultValue_1114) {

    EXPECT_FALSE(splashOutputDev->getFontAntialias());

}



TEST_F(SplashOutputDevTest_1114, SetAndGetFontAntialias_True_1114) {

    splashOutputDev->setFontAntialias(true);

    EXPECT_TRUE(splashOutputDev->getFontAntialias());

}



TEST_F(SplashOutputDevTest_1114, SetAndGetFontAntialias_False_1114) {

    splashOutputDev->setFontAntialias(false);

    EXPECT_FALSE(splashOutputDev->getFontAntialias());

}

#include <gtest/gtest.h>

#include "SplashOutputDev.h"



class SplashOutputDevTest_1115 : public ::testing::Test {

protected:

    void SetUp() override {

        splashOutputDev = new SplashOutputDev(SplashColorModeMono, 0, nullptr, false, splashThinLineDefault, false);

    }



    void TearDown() override {

        delete splashOutputDev;

    }



    SplashOutputDev* splashOutputDev;

};



TEST_F(SplashOutputDevTest_1115, SetFontAntialias_DefaultValue_1115) {

    EXPECT_EQ(splashOutputDev->getFontAntialias(), false);

}



TEST_F(SplashOutputDevTest_1115, SetFontAntialias_Enable_1115) {

    splashOutputDev->setFontAntialias(true);

    EXPECT_EQ(splashOutputDev->getFontAntialias(), true);

}



TEST_F(SplashOutputDevTest_1115, SetFontAntialias_Disable_1115) {

    splashOutputDev->setFontAntialias(false);

    EXPECT_EQ(splashOutputDev->getFontAntialias(), false);

}



TEST_F(SplashOutputDevTest_1115, SetFontAntialias_Toggle_1115) {

    splashOutputDev->setFontAntialias(true);

    EXPECT_EQ(splashOutputDev->getFontAntialias(), true);



    splashOutputDev->setFontAntialias(false);

    EXPECT_EQ(splashOutputDev->getFontAntialias(), false);

}

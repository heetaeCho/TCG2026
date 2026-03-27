#include <gtest/gtest.h>

#include "Splash.h"



class SplashTest : public ::testing::Test {

protected:

    void SetUp() override {

        bitmap = new SplashBitmap();

        screenParams = new SplashScreenParams();

        splash = new Splash(bitmap, false, screenParams);

    }



    void TearDown() override {

        delete splash;

        delete screenParams;

        delete bitmap;

    }



    SplashBitmap* bitmap;

    SplashScreenParams* screenParams;

    Splash* splash;

};



TEST_F(SplashTest_1572, GetVectorAntialias_DefaultValueFalse_1572) {

    EXPECT_FALSE(splash->getVectorAntialias());

}



TEST_F(SplashTest_1572, SetAndGetVectorAntialias_True_1572) {

    splash->setVectorAntialias(true);

    EXPECT_TRUE(splash->getVectorAntialias());

}



TEST_F(SplashTest_1572, SetAndGetVectorAntialias_False_1572) {

    splash->setVectorAntialias(false);

    EXPECT_FALSE(splash->getVectorAntialias());

}

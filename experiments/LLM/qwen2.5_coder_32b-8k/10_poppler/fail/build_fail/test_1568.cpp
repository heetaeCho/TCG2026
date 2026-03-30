#include <gtest/gtest.h>

#include "Splash.h"

#include <array>



class SplashTest : public ::testing::Test {

protected:

    void SetUp() override {

        // Assuming a default constructor or mock setup if needed.

        splash = new Splash(nullptr, false, nullptr);

    }



    void TearDown() override {

        delete splash;

    }



    Splash* splash;

};



TEST_F(SplashTest_1568, GetThinLineMode_DefaultValue_1568) {

    // Assuming default value is something specific, we check for that.

    EXPECT_EQ(splash->getThinLineMode(), SplashThinLineMode::thinLineDefault);

}



TEST_F(SplashTest_1568, SetAndGetThinLineMode_NormalOperation_1568) {

    splash->setThinLineMode(SplashThinLineMode::thinLineRoundCap);

    EXPECT_EQ(splash->getThinLineMode(), SplashThinLineMode::thinLineRoundCap);



    splash->setThinLineMode(SplashThinLineMode::thinLineButtCap);

    EXPECT_EQ(splash->getThinLineMode(), SplashThinLineMode::thinLineButtCap);

}



TEST_F(SplashTest_1568, SetAndGetMinLineWidth_NormalOperation_1568) {

    splash->setMinLineWidth(0.5);

    EXPECT_FLOAT_EQ(splash->getLineWidth(), 0.5);



    splash->setMinLineWidth(2.0);

    EXPECT_FLOAT_EQ(splash->getLineWidth(), 2.0);

}



TEST_F(SplashTest_1568, GetVectorAntialias_DefaultValue_1568) {

    // Assuming default value is false.

    EXPECT_FALSE(splash->getVectorAntialias());

}



TEST_F(SplashTest_1568, SetAndGetVectorAntialias_NormalOperation_1568) {

    splash->setVectorAntialias(true);

    EXPECT_TRUE(splash->getVectorAntialias());



    splash->setVectorAntialias(false);

    EXPECT_FALSE(splash->getVectorAntialias());

}



TEST_F(SplashTest_1568, SetAndGetClipRes_NormalOperation_1568) {

    // Assuming we can set and get clip result.

    splash->clipResetToRect(0, 0, 100, 100);

    EXPECT_EQ(splash->getClipRes(), SplashClipResult::clipAllInside);



    splash->clipToRect(-100, -100, -50, -50); // Should be all outside

    EXPECT_EQ(splash->getClipRes(), SplashClipResult::clipAllOutside);

}



TEST_F(SplashTest_1568, GetDebugMode_DefaultValue_1568) {

    // Assuming default value is false.

    EXPECT_FALSE(splash->getDebugMode());

}



TEST_F(SplashTest_1568, SetAndGetDebugMode_NormalOperation_1568) {

    splash->setDebugMode(true);

    EXPECT_TRUE(splash->getDebugMode());



    splash->setDebugMode(false);

    EXPECT_FALSE(splash->getDebugMode());

}

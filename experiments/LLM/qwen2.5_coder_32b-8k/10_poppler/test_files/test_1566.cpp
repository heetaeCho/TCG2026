#include <gtest/gtest.h>

#include "TestProjects/poppler/splash/Splash.h"



class SplashTest : public ::testing::Test {

protected:

    void SetUp() override {

        // Assuming a default constructor for simplicity, if not available create an appropriate mock or stub.

        splash = new Splash(nullptr, false, nullptr);

    }



    void TearDown() override {

        delete splash;

    }



    Splash* splash;

};



TEST_F(SplashTest_1566, SetMinLineWidth_ValidValue_1566) {

    SplashCoord lineWidth = 2.5;

    splash->setMinLineWidth(lineWidth);

}



TEST_F(SplashTest_1566, SetMinLineWidth_Zero_1566) {

    SplashCoord lineWidth = 0;

    splash->setMinLineWidth(lineWidth);

}



TEST_F(SplashTest_1566, SetMinLineWidth_NegativeValue_1566) {

    SplashCoord lineWidth = -1.5;

    splash->setMinLineWidth(lineWidth);

}

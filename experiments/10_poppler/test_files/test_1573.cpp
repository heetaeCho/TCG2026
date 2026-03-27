#include <gtest/gtest.h>

#include "Splash.h"



class SplashTest_1573 : public ::testing::Test {

protected:

    void SetUp() override {

        // Assuming there's a way to create a valid SplashBitmap and SplashScreenParams/SplashScreen for this test.

        // For the purpose of this example, we'll mock these dependencies.

        splash = new Splash(nullptr, false, nullptr); // Using nullptr for simplicity

    }



    void TearDown() override {

        delete splash;

    }



    Splash* splash;

};



TEST_F(SplashTest_1573, SetVectorAntialias_Enable_1573) {

    splash->setVectorAntialias(true);

    EXPECT_TRUE(splash->getVectorAntialias());

}



TEST_F(SplashTest_1573, SetVectorAntialias_Disable_1573) {

    splash->setVectorAntialias(false);

    EXPECT_FALSE(splash->getVectorAntialias());

}



TEST_F(SplashTest_1573, SetVectorAntialias_BoundaryCondition_1573) {

    splash->setVectorAntialias(true);

    EXPECT_TRUE(splash->getVectorAntialias());



    splash->setVectorAntialias(false);

    EXPECT_FALSE(splash->getVectorAntialias());

}



TEST_F(SplashTest_1573, GetVectorAntialias_DefaultValue_1573) {

    // Assuming the default value of vectorAntialias is false as no constructor sets it to true.

    EXPECT_FALSE(splash->getVectorAntialias());

}

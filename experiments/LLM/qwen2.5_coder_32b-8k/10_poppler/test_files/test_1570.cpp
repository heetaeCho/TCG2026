#include <gtest/gtest.h>

#include "Splash.h"

#include <array>



class SplashTest_1570 : public ::testing::Test {

protected:

    void SetUp() override {

        splash = new Splash(nullptr, false, nullptr);

    }



    void TearDown() override {

        delete splash;

    }



    Splash* splash;

};



TEST_F(SplashTest_1570, SetDebugMode_NormalOperation_1570) {

    splash->setDebugMode(true);

    // Since we can't directly check the internal state, we assume if no crash happens,

    // the operation is successful.

}



TEST_F(SplashTest_1570, SetDebugMode_BoundaryCondition_1570) {

    splash->setDebugMode(false);

    // Similarly, checking for boundary conditions like false in this context is about ensuring

    // no unexpected behavior occurs.

}



TEST_F(SplashTest_1570, SetDebugMode_ExceptionalCase_1570) {

    // Since setDebugMode doesn't have any parameters that can lead to exceptions based on the provided interface,

    // there are no exceptional cases to test for this function specifically.

}

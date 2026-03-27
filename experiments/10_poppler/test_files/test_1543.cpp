#include <gtest/gtest.h>

#include "SplashState.h"



class SplashStateTest : public ::testing::Test {

protected:

    SplashState *splashState;



    void SetUp() override {

        splashState = new SplashState(100, 100, false, nullptr);

    }



    void TearDown() override {

        delete splashState;

    }

};



TEST_F(SplashStateTest_1543, SetOverprintMode_DefaultValue_1543) {

    // No initial value is set, so we assume it's zero-initialized

    int initialValue = 0;

    EXPECT_EQ(splashState->copy()->getOverprintMode(), initialValue);

}



TEST_F(SplashStateTest_1543, SetOverprintMode_ValidValue_1543) {

    splashState->setOverprintMode(1);

    EXPECT_EQ(splashState->copy()->getOverprintMode(), 1);

}



TEST_F(SplashStateTest_1543, SetOverprintMode_BoundaryValue_Zero_1543) {

    splashState->setOverprintMode(0);

    EXPECT_EQ(splashState->copy()->getOverprintMode(), 0);

}



TEST_F(SplashStateTest_1543, SetOverprintMode_NegativeValue_1543) {

    splashState->setOverprintMode(-1);

    EXPECT_EQ(splashState->copy()->getOverprintMode(), -1);

}



TEST_F(SplashStateTest_1543, SetOverprintMode_LargePositiveValue_1543) {

    splashState->setOverprintMode(2147483647); // INT_MAX

    EXPECT_EQ(splashState->copy()->getOverprintMode(), 2147483647);

}

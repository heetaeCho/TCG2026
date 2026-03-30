#include <gtest/gtest.h>

#include "TestProjects/poppler/splash/SplashState.h"



class SplashStateTest : public ::testing::Test {

protected:

    SplashState* state;



    void SetUp() override {

        state = new SplashState(100, 100, false, nullptr);

    }



    void TearDown() override {

        delete state;

    }

};



TEST_F(SplashStateTest_1542, SetStrokeOverprint_DefaultValue_1542) {

    // Default value is not specified, but we can test if setting it to false works as expected

    state->setStrokeOverprint(false);

    // No observable behavior to assert directly, so this is more of a setup for future tests

}



TEST_F(SplashStateTest_1542, SetStrokeOverprint_ToTrue_1542) {

    state->setStrokeOverprint(true);

    // No observable behavior to assert directly, so this is more of a setup for future tests

}



TEST_F(SplashStateTest_1542, SetStrokeOverprint_ToFalse_1542) {

    state->setStrokeOverprint(false);

    // No observable behavior to assert directly, so this is more of a setup for future tests

}

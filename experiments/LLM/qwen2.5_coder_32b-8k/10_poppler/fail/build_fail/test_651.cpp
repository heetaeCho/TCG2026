#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/GfxState.h"



class GfxStateTest : public ::testing::Test {

protected:

    GfxState state{72.0, 72.0, nullptr, 0, false};



    void SetUp() override {

        // Setup code if needed

    }



    void TearDown() override {

        // Teardown code if needed

    }

};



TEST_F(GfxStateTest_651, SetRiseAndGetRise_NormalOperation_651) {

    double testValue = 10.5;

    state.setRise(testValue);

    EXPECT_EQ(state.getRise(), testValue);

}



TEST_F(GfxStateTest_651, SetRiseAndGetRise_BoundaryConditionZero_651) {

    double testValue = 0.0;

    state.setRise(testValue);

    EXPECT_EQ(state.getRise(), testValue);

}



TEST_F(GfxStateTest_651, SetRiseAndGetRise_NegativeValue_651) {

    double testValue = -5.25;

    state.setRise(testValue);

    EXPECT_EQ(state.getRise(), testValue);

}

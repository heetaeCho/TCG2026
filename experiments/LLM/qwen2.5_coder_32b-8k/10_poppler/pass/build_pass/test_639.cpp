#include <gtest/gtest.h>

#include "GfxState.h"



class GfxStateTest_639 : public ::testing::Test {

protected:

    GfxState* state;



    void SetUp() override {

        // Assuming a constructor exists that initializes necessary members

        // Since the constructor is not provided, we will mock this with default values

        state = new GfxState(72.0, 72.0, nullptr, 0, false);

    }



    void TearDown() override {

        delete state;

    }

};



TEST_F(GfxStateTest_639, SetFlatness_NormalOperation_639) {

    int flatnessValue = 10;

    state->setFlatness(flatnessValue);

    EXPECT_EQ(state->getFlatness(), flatnessValue);

}



TEST_F(GfxStateTest_639, SetFlatness_BoundaryConditionZero_639) {

    state->setFlatness(0);

    EXPECT_EQ(state->getFlatness(), 0);

}



TEST_F(GfxStateTest_639, SetFlatness_BoundaryConditionMaxInt_639) {

    int maxInt = std::numeric_limits<int>::max();

    state->setFlatness(maxInt);

    EXPECT_EQ(state->getFlatness(), maxInt);

}



TEST_F(GfxStateTest_639, SetFlatness_ExceptionalCaseNegativeValue_639) {

    // Assuming the class can handle negative values without crashing

    int negativeValue = -5;

    state->setFlatness(negativeValue);

    EXPECT_EQ(state->getFlatness(), negativeValue);

}

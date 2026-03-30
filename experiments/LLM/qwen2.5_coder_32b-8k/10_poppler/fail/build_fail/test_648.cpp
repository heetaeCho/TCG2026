#include <gtest/gtest.h>

#include "GfxState.h"



class GfxStateTest_648 : public ::testing::Test {

protected:

    GfxState* state;



    void SetUp() override {

        // Assuming default constructor exists or a mock setup is possible.

        // Here, we use placeholders for parameters as the actual constructor is not provided.

        state = new GfxState(72.0, 72.0, nullptr, 0, false);

    }



    void TearDown() override {

        delete state;

    }

};



TEST_F(GfxStateTest_648, SetWordSpace_DefaultValue_648) {

    double wordSpace = 0.0;

    state->getWordSpace(&wordSpace);

    EXPECT_DOUBLE_EQ(wordSpace, 0.0); // Assuming default value is 0.0

}



TEST_F(GfxStateTest_648, SetWordSpace_PositiveValue_648) {

    double expected = 10.5;

    state->setWordSpace(expected);

    double actual = state->getWordSpace();

    EXPECT_DOUBLE_EQ(actual, expected);

}



TEST_F(GfxStateTest_648, SetWordSpace_NegativeValue_648) {

    double expected = -5.25;

    state->setWordSpace(expected);

    double actual = state->getWordSpace();

    EXPECT_DOUBLE_EQ(actual, expected);

}



TEST_F(GfxStateTest_648, SetWordSpace_ZeroValue_648) {

    double expected = 0.0;

    state->setWordSpace(expected);

    double actual = state->getWordSpace();

    EXPECT_DOUBLE_EQ(actual, expected);

}

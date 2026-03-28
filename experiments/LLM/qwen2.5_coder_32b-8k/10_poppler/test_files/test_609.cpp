#include <gtest/gtest.h>

#include "GfxState.h"



class GfxStateTest : public ::testing::Test {

protected:

    GfxState* state;



    void SetUp() override {

        // Assuming a default constructor or mock parameters for the actual constructor

        state = new GfxState(300.0, 300.0, nullptr, 0, false);

    }



    void TearDown() override {

        delete state;

    }

};



TEST_F(GfxStateTest_609, GetWordSpace_DefaultValue_609) {

    double wordSpace = state->getWordSpace();

    EXPECT_DOUBLE_EQ(wordSpace, 0.0); // Assuming default value for wordSpace is 0.0

}



TEST_F(GfxStateTest_609, SetAndGetWordSpace_NormalOperation_609) {

    state->setWordSpace(5.0);

    double wordSpace = state->getWordSpace();

    EXPECT_DOUBLE_EQ(wordSpace, 5.0);

}



TEST_F(GfxStateTest_609, SetAndGetWordSpace_BoundaryCondition_609) {

    state->setWordSpace(-1.0);

    double wordSpace = state->getWordSpace();

    EXPECT_DOUBLE_EQ(wordSpace, -1.0);



    state->setWordSpace(1e6);

    wordSpace = state->getWordSpace();

    EXPECT_DOUBLE_EQ(wordSpace, 1e6);

}



TEST_F(GfxStateTest_609, SetAndGetWordSpace_ZeroValue_609) {

    state->setWordSpace(0.0);

    double wordSpace = state->getWordSpace();

    EXPECT_DOUBLE_EQ(wordSpace, 0.0);

}

#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/GfxState.h"



class GfxStateTest : public ::testing::Test {

protected:

    GfxState* gfxState;



    void SetUp() override {

        gfxState = new GfxState(300.0, 300.0, nullptr, 0, false);

    }



    void TearDown() override {

        delete gfxState;

    }

};



TEST_F(GfxStateTest_647, SetCharSpace_DefaultValue_647) {

    double charSpace = 0.0;

    EXPECT_EQ(gfxState->getCharSpace(), charSpace);

}



TEST_F(GfxStateTest_647, SetCharSpace_PositiveValue_647) {

    double newCharSpace = 1.2;

    gfxState->setCharSpace(newCharSpace);

    EXPECT_EQ(gfxState->getCharSpace(), newCharSpace);

}



TEST_F(GfxStateTest_647, SetCharSpace_NegativeValue_647) {

    double newCharSpace = -0.5;

    gfxState->setCharSpace(newCharSpace);

    EXPECT_EQ(gfxState->getCharSpace(), newCharSpace);

}



TEST_F(GfxStateTest_647, SetCharSpace_ZeroValue_647) {

    double newCharSpace = 0.0;

    gfxState->setCharSpace(newCharSpace);

    EXPECT_EQ(gfxState->getCharSpace(), newCharSpace);

}

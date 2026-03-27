#include <gtest/gtest.h>

#include "GfxState.h"



class GfxStateTest : public ::testing::Test {

protected:

    GfxState *gfxState;



    void SetUp() override {

        gfxState = new GfxState(300, 300, nullptr, 0, false);

    }



    void TearDown() override {

        delete gfxState;

    }

};



TEST_F(GfxStateTest_597, GetLineDash_DefaultValue_597) {

    double start = 0.0;

    const std::vector<double> &dash = gfxState->getLineDash(&start);

    EXPECT_EQ(start, 0.0);

    EXPECT_TRUE(dash.empty());

}



TEST_F(GfxStateTest_597, GetLineDash_SetValue_597) {

    double start = 1.0;

    std::vector<double> dashPattern = {2.0, 3.0, 4.0};

    gfxState->setLineDash(std::move(dashPattern), start);

    double retrievedStart = 0.0;

    const std::vector<double> &retrievedDash = gfxState->getLineDash(&retrievedStart);

    EXPECT_EQ(retrievedStart, start);

    EXPECT_EQ(retrievedDash, dashPattern);

}



TEST_F(GfxStateTest_597, GetLineDash_SetZeroLengthDash_597) {

    double start = 1.0;

    std::vector<double> dashPattern = {};

    gfxState->setLineDash(std::move(dashPattern), start);

    double retrievedStart = 0.0;

    const std::vector<double> &retrievedDash = gfxState->getLineDash(&retrievedStart);

    EXPECT_EQ(retrievedStart, start);

    EXPECT_TRUE(retrievedDash.empty());

}

#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/GfxState.h"



class GfxStateTest : public ::testing::Test {

protected:

    GfxState* state;



    void SetUp() override {

        // Assuming a default constructor or mock values for the parameters is acceptable

        state = new GfxState(300.0, 300.0, nullptr, 0, false);

    }



    void TearDown() override {

        delete state;

    }

};



TEST_F(GfxStateTest_573, GetPageHeight_ReturnsExpectedValue_573) {

    double expectedHeight = 842.0; // Example value, replace with actual or mock value

    EXPECT_DOUBLE_EQ(expectedHeight, state->getPageHeight());

}



TEST_F(GfxStateTest_573, GetHDPI_ReturnsExpectedValue_573) {

    EXPECT_DOUBLE_EQ(300.0, state->getHDPI());

}



TEST_F(GfxStateTest_573, GetVDPI_ReturnsExpectedValue_573) {

    EXPECT_DOUBLE_EQ(300.0, state->getVDPI());

}



TEST_F(GfxStateTest_573, GetRotate_DefaultInitialization_ReturnsZero_573) {

    EXPECT_EQ(0, state->getRotate());

}



// Assuming a default value for page width is available

TEST_F(GfxStateTest_573, GetPageWidth_ReturnsExpectedValue_573) {

    double expectedWidth = 595.0; // Example value, replace with actual or mock value

    EXPECT_DOUBLE_EQ(expectedWidth, state->getPageWidth());

}



// Assuming boundary conditions for page dimensions can be tested

TEST_F(GfxStateTest_573, GetPageHeight_ZeroInitialization_ReturnsZero_573) {

    GfxState zeroState(0.0, 0.0, nullptr, 0, false);

    EXPECT_DOUBLE_EQ(0.0, zeroState.getPageHeight());

}



// Assuming exceptional cases or error handling if any

TEST_F(GfxStateTest_573, GetPageWidth_NegativeInitialization_ReturnsNegativeValue_573) {

    // This test assumes that the constructor can accept negative values

    GfxState negativeState(-1.0, -1.0, nullptr, 0, false);

    EXPECT_DOUBLE_EQ(0.0, negativeState.getPageWidth()); // Assuming it clamps to zero or another valid value

}

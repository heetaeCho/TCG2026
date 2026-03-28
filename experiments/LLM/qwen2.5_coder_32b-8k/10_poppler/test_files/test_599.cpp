#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/GfxState.h"



// Test fixture for GfxState tests.

class GfxStateTest_599 : public ::testing::Test {

protected:

    // Create an instance of GfxState with some initial values.

    GfxState state{72.0, 72.0, nullptr, 0, false};



    void SetUp() override {

        // Initialize any necessary state before each test.

    }



    void TearDown() override {

        // Clean up any resources after each test.

    }

};



// Test the normal operation of getLineJoin().

TEST_F(GfxStateTest_599, GetLineJoin_NormalOperation_599) {

    LineJoinStyle expectedLineJoin = LineJoinStyle::miterJoin;

    state.setLineJoin(expectedLineJoin);

    EXPECT_EQ(state.getLineJoin(), expectedLineJoin);

}



// Test the boundary condition where LineJoinStyle is set to a valid value.

TEST_F(GfxStateTest_599, GetLineJoin_BoundaryCondition_ValidValue_599) {

    LineJoinStyle expectedLineJoin = LineJoinStyle::bevelJoin;

    state.setLineJoin(expectedLineJoin);

    EXPECT_EQ(state.getLineJoin(), expectedLineJoin);

}



// Test the boundary condition where LineJoinStyle is set to another valid value.

TEST_F(GfxStateTest_599, GetLineJoin_BoundaryCondition_AnotherValidValue_599) {

    LineJoinStyle expectedLineJoin = LineJoinStyle::roundJoin;

    state.setLineJoin(expectedLineJoin);

    EXPECT_EQ(state.getLineJoin(), expectedLineJoin);

}



// Test the exceptional case where LineJoinStyle is set to an invalid value (if applicable).

// Since LineJoinStyle is an enum, setting it out of range would not be possible directly.

// This test assumes that the setter method handles any invalid values gracefully.

TEST_F(GfxStateTest_599, GetLineJoin_ExceptionalCase_SetInvalidValue_599) {

    // If there's a way to simulate this scenario, include it here.

    // For now, we assume setLineJoin does not accept out-of-range values directly.

    LineJoinStyle expectedLineJoin = static_cast<LineJoinStyle>(-1); // Invalid value

    state.setLineJoin(expectedLineJoin);

    EXPECT_NE(state.getLineJoin(), expectedLineJoin); // Should not reflect the invalid value

}

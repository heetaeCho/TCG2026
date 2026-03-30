#include <gtest/gtest.h>

#include "GfxState.h"



class GfxStateTest : public ::testing::Test {

protected:

    GfxState state{72.0, 72.0, nullptr, 0, false};

    GfxColor color;

};



TEST_F(GfxStateTest_631, SetStrokeColor_NormalOperation_631) {

    // Arrange

    color.c[0] = 0.5;

    color.c[1] = 0.7;

    color.c[2] = 0.9;



    // Act

    state.setStrokeColor(&color);



    // Assert

    const GfxColor* strokeColor = state.getStrokeColor();

    EXPECT_EQ(strokeColor->c[0], 0.5);

    EXPECT_EQ(strokeColor->c[1], 0.7);

    EXPECT_EQ(strokeColor->c[2], 0.9);

}



TEST_F(GfxStateTest_631, SetStrokeColor_BoundaryConditions_631) {

    // Arrange

    color.c[0] = 0.0;

    color.c[1] = 1.0;

    color.c[2] = 0.5;



    // Act

    state.setStrokeColor(&color);



    // Assert

    const GfxColor* strokeColor = state.getStrokeColor();

    EXPECT_EQ(strokeColor->c[0], 0.0);

    EXPECT_EQ(strokeColor->c[1], 1.0);

    EXPECT_EQ(strokeColor->c[2], 0.5);

}



TEST_F(GfxStateTest_631, SetStrokeColor_ExceptionalCase_NullPointer_631) {

    // Arrange & Act & Assert

    EXPECT_NO_THROW(state.setStrokeColor(nullptr));

}

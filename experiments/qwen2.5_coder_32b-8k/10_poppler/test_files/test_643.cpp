#include <gtest/gtest.h>

#include "GfxState.h"



class GfxStateTest : public ::testing::Test {

protected:

    GfxState* state;



    void SetUp() override {

        // Assuming a valid PDFRectangle object and other necessary parameters are available

        PDFRectangle pageBox(0, 0, 100, 100);

        state = new GfxState(300.0, 300.0, &pageBox, 0, false);

    }



    void TearDown() override {

        delete state;

    }

};



TEST_F(GfxStateTest_643, SetStrokeAdjustAndGetStrokeAdjust_643) {

    // Test normal operation

    state->setStrokeAdjust(true);

    EXPECT_TRUE(state->getStrokeAdjust());



    state->setStrokeAdjust(false);

    EXPECT_FALSE(state->getStrokeAdjust());

}



TEST_F(GfxStateTest_643, GetStrokeAdjust_DefaultValue_643) {

    // Test boundary condition: default value

    GfxState* newState = new GfxState(300.0, 300.0, &PDFRectangle(0, 0, 100, 100), 0, false);

    EXPECT_FALSE(newState->getStrokeAdjust());

    delete newState;

}



// No exceptional or error cases are observable through the given interface for this function.

```



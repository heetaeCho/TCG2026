#include <gtest/gtest.h>

#include "GfxState.h"



class GfxStateTest : public ::testing::Test {

protected:

    GfxState* state;



    void SetUp() override {

        state = new GfxState(72.0, 72.0, nullptr, 0, false);

    }



    void TearDown() override {

        delete state;

    }

};



TEST_F(GfxStateTest_576, GetStrokeColor_ReturnsNonNullPointer_576) {

    EXPECT_NE(state->getStrokeColor(), nullptr);

}



// Boundary condition: No specific boundary conditions for getStrokeColor as it always returns a pointer to a member.

// Exceptional case: No observable exceptional cases through the provided interface for getStrokeColor.



```



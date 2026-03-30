#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-page.h"



class PopplerColorTest_2480 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup can be used to initialize any common objects or states if needed.

    }



    void TearDown() override {

        // Cleanup can be done here if necessary.

    }

};



TEST_F(PopplerColorTest_2480, NewPopplerColor_ReturnsNonNullPointer_2480) {

    PopplerColor* color = poppler_color_new();

    EXPECT_NE(color, nullptr);

}



TEST_F(PopplerColorTest_2480, NewPopplerColor_MemoryIsZeroed_2480) {

    PopplerColor* color = poppler_color_new();

    EXPECT_EQ(color->red, 0);

    EXPECT_EQ(color->green, 0);

    EXPECT_EQ(color->blue, 0);

    EXPECT_EQ(color->alpha, 0);

}



TEST_F(PopplerColorTest_2480, NewPopplerColor_MultipleCallsReturnDifferentInstances_2480) {

    PopplerColor* color1 = poppler_color_new();

    PopplerColor* color2 = poppler_color_new();

    EXPECT_NE(color1, color2);

}



// Assuming there are no exceptional or boundary conditions for this simple function.

```



These tests cover:

- Normal operation: `NewPopplerColor_ReturnsNonNullPointer_2480` checks if the returned pointer is not null.

- Observable behavior: `NewPopplerColor_MemoryIsZeroed_2480` verifies that the memory allocated is zero-initialized.

- Boundary conditions: `NewPopplerColor_MultipleCallsReturnDifferentInstances_2480` ensures multiple calls to the function return different instances, which might be a boundary condition in terms of memory allocation.



#include <gtest/gtest.h>



// Since div255 is a static inline function, we need to create a way to test it.

// We can wrap it in a class or a struct for testing purposes.



struct Div255Wrapper {

    unsigned char callDiv255(int x) {

        return div255(x);

    }

};



TEST_F(Div255Test_1576, NormalOperation_PositiveInput_1576) {

    Div255Wrapper wrapper;

    EXPECT_EQ(wrapper.callDiv255(255), 255);

    EXPECT_EQ(wrapper.callDiv255(128), 128);

    EXPECT_EQ(wrapper.callDiv255(64), 64);

}



TEST_F(Div255Test_1576, NormalOperation_ZeroInput_1576) {

    Div255Wrapper wrapper;

    EXPECT_EQ(wrapper.callDiv255(0), 0);

}



TEST_F(Div255Test_1576, BoundaryCondition_MaxInt_1576) {

    Div255Wrapper wrapper;

    EXPECT_EQ(wrapper.callDiv255(INT_MAX), 255);

}



TEST_F(Div255Test_1576, BoundaryCondition_MinInt_1576) {

    Div255Wrapper wrapper;

    EXPECT_EQ(wrapper.callDiv255(INT_MIN), 0); // Due to overflow, the result is clamped to 0

}



TEST_F(Div255Test_1576, BoundaryCondition_LargeInput_1576) {

    Div255Wrapper wrapper;

    EXPECT_EQ(wrapper.callDiv255(65535), 255);

}



TEST_F(Div255Test_1576, BoundaryCondition_SmallInput_1576) {

    Div255Wrapper wrapper;

    EXPECT_EQ(wrapper.callDiv255(1), 0); // Result is rounded down

}

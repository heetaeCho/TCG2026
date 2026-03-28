#include <gtest/gtest.h>



// Since clip255 is a static inline function, we need to provide it in the test file.

static inline unsigned char clip255(int x) { return x < 0 ? 0 : x > 255 ? 255 : x; }



TEST(Clip255Test_1598, NormalOperation_PositiveValues_1598) {

    EXPECT_EQ(clip255(10), 10);

    EXPECT_EQ(clip255(128), 128);

    EXPECT_EQ(clip255(200), 200);

}



TEST(Clip255Test_1598, NormalOperation_NegativeValues_1598) {

    EXPECT_EQ(clip255(-10), 0);

    EXPECT_EQ(clip255(-128), 0);

    EXPECT_EQ(clip255(-200), 0);

}



TEST(Clip255Test_1598, BoundaryCondition_LowerBound_1598) {

    EXPECT_EQ(clip255(0), 0);

}



TEST(Clip255Test_1598, BoundaryCondition_UpperBound_1598) {

    EXPECT_EQ(clip255(255), 255);

}



TEST(Clip255Test_1598, ExceptionalCase_AboveUpperBound_1598) {

    EXPECT_EQ(clip255(256), 255);

    EXPECT_EQ(clip255(300), 255);

}



TEST(Clip255Test_1598, ExceptionalCase_BelowLowerBound_1598) {

    EXPECT_EQ(clip255(-1), 0);

    EXPECT_EQ(clip255(-100), 0);

}

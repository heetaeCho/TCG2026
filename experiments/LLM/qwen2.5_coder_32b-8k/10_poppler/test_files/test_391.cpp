#include <gtest/gtest.h>

#include "GfxState.h"



class ByteToDblTest : public ::testing::Test {

protected:

    // No additional setup needed for this simple function

};



TEST_F(ByteToDblTest_391, NormalOperation_391) {

    EXPECT_DOUBLE_EQ(byteToDbl(0), 0.0);

    EXPECT_DOUBLE_EQ(byteToDbl(128), 0.5);

    EXPECT_DOUBLE_EQ(byteToDbl(255), 1.0);

}



TEST_F(ByteToDblTest_391, BoundaryConditions_391) {

    EXPECT_DOUBLE_EQ(byteToDbl(std::numeric_limits<unsigned char>::min()), 0.0);

    EXPECT_DOUBLE_EQ(byteToDbl(std::numeric_limits<unsigned char>::max()), 1.0);

}

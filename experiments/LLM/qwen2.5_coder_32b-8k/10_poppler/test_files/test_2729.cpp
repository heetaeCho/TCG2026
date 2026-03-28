#include <gtest/gtest.h>

#include <cmath>



// Assuming IS_CLOSER function is in a header file that we include

// For the sake of this example, let's assume it's included from "HtmlOutputDev.h"

#include "HtmlOutputDev.h"



TEST(IS_CLOSER_Test_2729, NormalOperation_2729) {

    EXPECT_TRUE(IS_CLOSER(1.0, 1.1, 1.5));

    EXPECT_FALSE(IS_CLOSER(1.0, 1.1, 0.8));

}



TEST(IS_CLOSER_Test_2729, BoundaryConditions_2729) {

    EXPECT_TRUE(IS_CLOSER(1.0, 1.0, 1.5)); // x == y

    EXPECT_FALSE(IS_CLOSER(1.0, 1.5, 1.0)); // z == x

    EXPECT_TRUE(IS_CLOSER(1.0, 1.5, 1.6)); // z > y and z > x

}



TEST(IS_CLOSER_Test_2729, NegativeValues_2729) {

    EXPECT_TRUE(IS_CLOSER(-1.0, -1.1, -1.5));

    EXPECT_FALSE(IS_CLOSER(-1.0, -1.1, -0.8));

}



TEST(IS_CLOSER_Test_2729, ZeroValues_2729) {

    EXPECT_TRUE(IS_CLOSER(0.0, 0.1, 0.5));

    EXPECT_FALSE(IS_CLOSER(0.0, 0.1, -0.1));

}



TEST(IS_CLOSER_Test_2729, LargeNumbers_2729) {

    EXPECT_TRUE(IS_CLOSER(1e10, 1.1e10, 1.5e10));

    EXPECT_FALSE(IS_CLOSER(1e10, 1.1e10, 8e9));

}



TEST(IS_CLOSER_Test_2729, SmallNumbers_2729) {

    EXPECT_TRUE(IS_CLOSER(1e-10, 1.1e-10, 1.5e-10));

    EXPECT_FALSE(IS_CLOSER(1e-10, 1.1e-10, 8e-11));

}

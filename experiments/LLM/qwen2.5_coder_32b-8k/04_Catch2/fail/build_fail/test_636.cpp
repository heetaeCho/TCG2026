#include <gtest/gtest.h>

#include <cmath>

#include "./TestProjects/Catch2/src/catch2/internal/catch_polyfills.cpp"



using namespace Catch;



class IsnanTest : public ::testing::Test {

protected:

    // No additional setup or teardown required for this simple function test

};



TEST_F(IsnanTest_636, NormalOperation_NaNValue_636) {

    EXPECT_TRUE(isnan(std::numeric_limits<double>::quiet_NaN()));

}



TEST_F(IsnanTest_636, NormalOperation_NormalNumber_636) {

    EXPECT_FALSE(isnan(42.0));

}



TEST_F(IsnanTest_636, BoundaryCondition_MaxDouble_636) {

    EXPECT_FALSE(isnan(std::numeric_limits<double>::max()));

}



TEST_F(IsnanTest_636, BoundaryCondition_MinDouble_636) {

    EXPECT_FALSE(isnan(std::numeric_limits<double>::min()));

}



TEST_F(IsnanTest_636, BoundaryCondition_Zero_636) {

    EXPECT_FALSE(isnan(0.0));

}

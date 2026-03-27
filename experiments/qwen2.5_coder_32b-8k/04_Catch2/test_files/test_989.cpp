#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/extras/catch_amalgamated.cpp"



using namespace Catch::Benchmark::Detail;



// Test fixture for normal_quantile function

class NormalQuantileTest_989 : public ::testing::Test {

protected:

    void SetUp() override {}

    void TearDown() override {}

};



TEST_F(NormalQuantileTest_989, NormalOperation_989) {

    EXPECT_DOUBLE_EQ(normal_quantile(0.5), 0.0);

    EXPECT_NEAR(normal_quantile(0.975), 1.959963984540054, 1e-9); // Approximate value for z-score of 0.975

    EXPECT_NEAR(normal_quantile(0.025), -1.959963984540054, 1e-9); // Approximate value for z-score of 0.025

}



TEST_F(NormalQuantileTest_989, BoundaryConditions_989) {

    EXPECT_DOUBLE_EQ(normal_quantile(0.0), -std::numeric_limits<double>::infinity());

    EXPECT_DOUBLE_EQ(normal_quantile(1.0), std::numeric_limits<double>::infinity());

}



TEST_F(NormalQuantileTest_989, ExceptionalCases_989) {

    // Since the function uses assert for invalid inputs and returns 0.0 in such cases,

    // we expect it to return 0.0 for out-of-bound values.

    EXPECT_DOUBLE_EQ(normal_quantile(-1.0), 0.0);

    EXPECT_DOUBLE_EQ(normal_quantile(2.0), 0.0);

}



TEST_F(NormalQuantileTest_989, ExtremeValues_989) {

    // Test extreme values within valid range

    EXPECT_NEAR(normal_quantile(0.999999999), 6.734146752148236, 1e-9); // Approximate value for very high p

    EXPECT_NEAR(normal_quantile(0.000000001), -6.734146752148236, 1e-9); // Approximate value for very low p

}

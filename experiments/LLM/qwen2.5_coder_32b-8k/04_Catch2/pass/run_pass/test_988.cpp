#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/extras/catch_amalgamated.cpp"



using namespace Catch::Benchmark::Detail;



// Test fixture for erfc_inv function

class ErfcInvTest_988 : public ::testing::Test {

protected:

    // Setup and teardown can be added here if needed

};



TEST_F(ErfcInvTest_988, NormalOperation_988) {

    double result = erfc_inv(0.5);

    EXPECT_DOUBLE_EQ(result, erf_inv(0.5));

}



TEST_F(ErfcInvTest_988, BoundaryConditionLower_988) {

    double result = erfc_inv(0.0);

    EXPECT_DOUBLE_EQ(result, erf_inv(1.0));

}



TEST_F(ErfcInvTest_988, BoundaryConditionUpper_988) {

    double result = erfc_inv(1.0);

    EXPECT_DOUBLE_EQ(result, erf_inv(0.0));

}



TEST_F(ErfcInvTest_988, ValueInRange_988) {

    double result = erfc_inv(0.25);

    EXPECT_DOUBLE_EQ(result, erf_inv(0.75));

}

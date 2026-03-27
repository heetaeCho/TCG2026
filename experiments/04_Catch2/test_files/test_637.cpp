#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/internal/catch_polyfills.cpp"



using namespace Catch;



TEST(nextafterFunctionTest_637, NormalOperation_PositiveNumbers_637) {

    EXPECT_FLOAT_EQ(nextafter(1.0f, 2.0f), nextafterf(1.0f, 2.0f));

}



TEST(nextafterFunctionTest_637, NormalOperation_NegativeNumbers_637) {

    EXPECT_FLOAT_EQ(nextafter(-1.0f, -2.0f), nextafterf(-1.0f, -2.0f));

}



TEST(nextafterFunctionTest_637, BoundaryCondition_ZeroToPositive_637) {

    EXPECT_FLOAT_EQ(nextafter(0.0f, 1.0f), nextafterf(0.0f, 1.0f));

}



TEST(nextafterFunctionTest_637, BoundaryCondition_ZeroToNegative_637) {

    EXPECT_FLOAT_EQ(nextafter(0.0f, -1.0f), nextafterf(0.0f, -1.0f));

}



TEST(nextafterFunctionTest_637, BoundaryCondition_MaxFloat_637) {

    EXPECT_FLOAT_EQ(nextafter(std::numeric_limits<float>::max(), std::numeric_limits<float>::infinity()), 

                    nextafterf(std::numeric_limits<float>::max(), std::numeric_limits<float>::infinity()));

}



TEST(nextafterFunctionTest_637, BoundaryCondition_MinFloat_637) {

    EXPECT_FLOAT_EQ(nextafter(-std::numeric_limits<float>::max(), -std::numeric_limits<float>::infinity()), 

                    nextafterf(-std::numeric_limits<float>::max(), -std::numeric_limits<float>::infinity()));

}



TEST(nextafterFunctionTest_637, ExceptionalCase_NaNInput_637) {

    EXPECT_FLOAT_EQ(nextafter(std::numeric_limits<float>::quiet_NaN(), 1.0f), 

                    nextafterf(std::numeric_limits<float>::quiet_NaN(), 1.0f));

}



TEST(nextafterFunctionTest_637, ExceptionalCase_InfinityInput_637) {

    EXPECT_FLOAT_EQ(nextafter(std::numeric_limits<float>::infinity(), std::numeric_limits<float>::max()), 

                    nextafterf(std::numeric_limits<float>::infinity(), std::numeric_limits<float>::max()));

}

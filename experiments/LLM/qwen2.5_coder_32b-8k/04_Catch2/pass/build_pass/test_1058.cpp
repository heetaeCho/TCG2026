#include <gtest/gtest.h>

#include "catch2/internal/catch_uniform_floating_point_distribution.hpp"



using Catch::uniform_floating_point_distribution;

using FloatType = double; // Assuming FloatType is double for these tests



class UniformFloatingPointDistributionTest_1058 : public ::testing::Test {

protected:

    uniform_floating_point_distribution<FloatType> dist;



    UniformFloatingPointDistributionTest_1058()

        : dist(-1.0, 1.0) {} // Example range

};



TEST_F(UniformFloatingPointDistributionTest_1058, ConstructorValidRange_1058) {

    EXPECT_NO_THROW(uniform_floating_point_distribution<FloatType>(-1.0, 1.0));

}



TEST_F(UniformFloatingPointDistributionTest_1058, ConstructorSameValues_1058) {

    EXPECT_NO_THROW(uniform_floating_point_distribution<FloatType>(0.0, 0.0));

}



TEST_F(UniformFloatingPointDistributionTest_1058, ConstructorInvalidRange_1058) {

    EXPECT_THROW(uniform_floating_point_distribution<FloatType>(1.0, -1.0), std::exception);

}



TEST_F(UniformFloatingPointDistributionTest_1058, AReturnsCorrectValue_1058) {

    EXPECT_EQ(dist.a(), -1.0);

}



TEST_F(UniformFloatingPointDistributionTest_1058, BReturnsCorrectValue_1058) {

    EXPECT_EQ(dist.b(), 1.0);

}

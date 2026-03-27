#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/internal/catch_uniform_floating_point_distribution.hpp"



using namespace Catch;



class UniformFloatingPointDistributionTest : public ::testing::Test {

protected:

    using FloatType = double;

    uniform_floating_point_distribution<FloatType> distribution;



    UniformFloatingPointDistributionTest() 

        : distribution(1.0, 2.0) {} // Example range

};



// Test to verify the normal operation of the b() function

TEST_F(UniformFloatingPointDistributionTest_345, BReturnsCorrectValue_345) {

    EXPECT_EQ(distribution.b(), 2.0);

}



// Test to verify the boundary condition when a and b are equal

TEST_F(UniformFloatingPointDistributionTest_345, AEqualsB_ReturnsA_345) {

    uniform_floating_point_distribution<FloatType> distEqual(1.0, 1.0);

    EXPECT_EQ(distEqual.b(), 1.0);

}



// Test to verify the boundary condition when a is greater than b

TEST_F(UniformFloatingPointDistributionTest_345, AGreaterThanB_ReturnsAAsB_345) {

    uniform_floating_point_distribution<FloatType> distInverted(2.0, 1.0);

    EXPECT_EQ(distInverted.b(), 2.0);

}



// Test to verify the normal operation of the a() function

TEST_F(UniformFloatingPointDistributionTest_345, AReturnsCorrectValue_345) {

    EXPECT_EQ(distribution.a(), 1.0);

}



// Test to verify the boundary condition when a and b are equal for a()

TEST_F(UniformFloatingPointDistributionTest_345, AEqualsB_ReturnsAForA_345) {

    uniform_floating_point_distribution<FloatType> distEqual(1.0, 1.0);

    EXPECT_EQ(distEqual.a(), 1.0);

}



// Test to verify the boundary condition when a is greater than b for a()

TEST_F(UniformFloatingPointDistributionTest_345, AGreaterThanB_ReturnsAAsA_345) {

    uniform_floating_point_distribution<FloatType> distInverted(2.0, 1.0);

    EXPECT_EQ(distInverted.a(), 1.0);

}

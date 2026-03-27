#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/internal/catch_uniform_floating_point_distribution.hpp"



using namespace Catch;



TEST_F(UniformFloatingPointDistributionTest_344, ConstructorInitializesAAndB_344) {

    uniform_floating_point_distribution<double> dist(1.0, 2.0);

    EXPECT_DOUBLE_EQ(dist.a(), 1.0);

    EXPECT_DOUBLE_EQ(dist.b(), 2.0);

}



TEST_F(UniformFloatingPointDistributionTest_344, ConstructorHandlesSameAAndB_344) {

    uniform_floating_point_distribution<double> dist(1.5, 1.5);

    EXPECT_DOUBLE_EQ(dist.a(), 1.5);

    EXPECT_DOUBLE_EQ(dist.b(), 1.5);

}



TEST_F(UniformFloatingPointDistributionTest_344, AReturnsCorrectValueAfterConstruction_344) {

    uniform_floating_point_distribution<double> dist(-5.0, 5.0);

    EXPECT_DOUBLE_EQ(dist.a(), -5.0);

}



TEST_F(UniformFloatingPointDistributionTest_344, BReturnsCorrectValueAfterConstruction_344) {

    uniform_floating_point_distribution<double> dist(-5.0, 5.0);

    EXPECT_DOUBLE_EQ(dist.b(), 5.0);

}



TEST_F(UniformFloatingPointDistributionTest_344, AIsLessThanOrEqualToB_344) {

    uniform_floating_point_distribution<double> dist(1.0, 2.0);

    EXPECT_LE(dist.a(), dist.b());

}



TEST_F(UniformFloatingPointDistributionTest_344, ConstructorHandlesNegativeRange_344) {

    uniform_floating_point_distribution<double> dist(-2.0, -1.0);

    EXPECT_DOUBLE_EQ(dist.a(), -2.0);

    EXPECT_DOUBLE_EQ(dist.b(), -1.0);

}



TEST_F(UniformFloatingPointDistributionTest_344, ConstructorHandlesLargeRange_344) {

    uniform_floating_point_distribution<double> dist(-1e9, 1e9);

    EXPECT_DOUBLE_EQ(dist.a(), -1e9);

    EXPECT_DOUBLE_EQ(dist.b(), 1e9);

}

#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/internal/catch_uniform_floating_point_distribution.hpp"

#include <cmath>



using namespace Catch;

using namespace ::testing;



// Mock Generator for testing

class MockGenerator {

public:

    MOCK_METHOD0(generate, uint32_t());

};



TEST_F(UniformFloatingPointDistributionTest_343, ConstructorWithValidRange_343) {

    uniform_floating_point_distribution<double> dist(1.0, 2.0);

    EXPECT_DOUBLE_EQ(dist.a(), 1.0);

    EXPECT_DOUBLE_EQ(dist.b(), 2.0);

}



TEST_F(UniformFloatingPointDistributionTest_343, ConstructorWithNegativeRange_343) {

    uniform_floating_point_distribution<double> dist(-2.0, -1.0);

    EXPECT_DOUBLE_EQ(dist.a(), -2.0);

    EXPECT_DOUBLE_EQ(dist.b(), -1.0);

}



TEST_F(UniformFloatingPointDistributionTest_343, ConstructorWithSameEndpoints_343) {

    uniform_floating_point_distribution<double> dist(1.0, 1.0);

    EXPECT_DOUBLE_EQ(dist.a(), 1.0);

    EXPECT_DOUBLE_EQ(dist.b(), 1.0);

}



TEST_F(UniformFloatingPointDistributionTest_343, OperatorCallWithZeroSteps_343) {

    uniform_floating_point_distribution<double> dist(1.0, 2.0);

    MockGenerator mockGen;

    EXPECT_CALL(mockGen, generate()).WillOnce(Return(0u));

    double result = dist(mockGen);

    EXPECT_DOUBLE_EQ(result, 1.0);

}



TEST_F(UniformFloatingPointDistributionTest_343, OperatorCallWithMaxSteps_343) {

    uniform_floating_point_distribution<double> dist(1.0, 2.0);

    MockGenerator mockGen;

    uint32_t max_steps = dist.m_floats_in_range;

    EXPECT_CALL(mockGen, generate()).WillOnce(Return(max_steps));

    double result = dist(mockGen);

    EXPECT_DOUBLE_EQ(result, 2.0);

}



TEST_F(UniformFloatingPointDistributionTest_343, OperatorCallWithIntermediateSteps_343) {

    uniform_floating_point_distribution<double> dist(1.0, 2.0);

    MockGenerator mockGen;

    uint32_t intermediate_steps = dist.m_floats_in_range / 2;

    EXPECT_CALL(mockGen, generate()).WillOnce(Return(intermediate_steps));

    double result = dist(mockGen);

    EXPECT_DOUBLE_EQ(result, 1.5);

}



TEST_F(UniformFloatingPointDistributionTest_343, OperatorCallWithLargeRange_343) {

    uniform_floating_point_distribution<double> dist(-1e6, 1e6);

    MockGenerator mockGen;

    uint32_t intermediate_steps = dist.m_floats_in_range / 2;

    EXPECT_CALL(mockGen, generate()).WillOnce(Return(intermediate_steps));

    double result = dist(mockGen);

    EXPECT_DOUBLE_EQ(result, 0.0);

}



TEST_F(UniformFloatingPointDistributionTest_343, OperatorCallWithNegativeRangeIntermediateSteps_343) {

    uniform_floating_point_distribution<double> dist(-2.0, -1.0);

    MockGenerator mockGen;

    uint32_t intermediate_steps = dist.m_floats_in_range / 2;

    EXPECT_CALL(mockGen, generate()).WillOnce(Return(intermediate_steps));

    double result = dist(mockGen);

    EXPECT_DOUBLE_EQ(result, -1.5);

}

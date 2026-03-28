#include <gtest/gtest.h>

#include "catch2/internal/catch_uniform_integer_distribution.hpp"



using namespace Catch;



class UniformIntegerDistributionTest_338 : public ::testing::Test {

protected:

    using IntegerType = int;

    uniform_integer_distribution<IntegerType> dist;



    UniformIntegerDistributionTest_338() : dist(1, 10) {}

};



TEST_F(UniformIntegerDistributionTest_338, BReturnsUpperBound_338) {

    EXPECT_EQ(dist.b(), 10);

}



TEST_F(UniformIntegerDistributionTest_338, BMatchesConstructorParameter_338) {

    uniform_integer_distribution<IntegerType> customDist(5, 15);

    EXPECT_EQ(customDist.b(), 15);

}



TEST_F(UniformIntegerDistributionTest_338, AAndBDefineRangeCorrectly_338) {

    uniform_integer_distribution<IntegerType> customDist(20, 30);

    EXPECT_EQ(customDist.a() + customDist.m_ab_distance - 1, customDist.b());

}



TEST_F(UniformIntegerDistributionTest_338, BHandlesMinimumValues_338) {

    uniform_integer_distribution<IntegerType> minDist(std::numeric_limits<int>::min(), std::numeric_limits<int>::min() + 1);

    EXPECT_EQ(minDist.b(), std::numeric_limits<int>::min() + 1);

}



TEST_F(UniformIntegerDistributionTest_338, BHandlesMaximumValues_338) {

    uniform_integer_distribution<IntegerType> maxDist(std::numeric_limits<int>::max() - 1, std::numeric_limits<int>::max());

    EXPECT_EQ(maxDist.b(), std::numeric_limits<int>::max());

}



TEST_F(UniformIntegerDistributionTest_338, BThrowsOnInvalidRange_338) {

    try {

        uniform_integer_distribution<IntegerType> invalidDist(10, 9);

        FAIL() << "Expected exception for invalid range";

    } catch (const std::exception& e) {

        SUCCEED();

    }

}

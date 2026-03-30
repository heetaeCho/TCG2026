#include <gtest/gtest.h>

#include "./TestProjects/Catch2/src/catch2/internal/catch_uniform_integer_distribution.hpp"



using namespace Catch;



class UniformIntegerDistributionTest_337 : public ::testing::Test {

protected:

    uniform_integer_distribution<int> distribution;

    

    UniformIntegerDistributionTest_337() : distribution(1, 10) {}

};



TEST_F(UniformIntegerDistributionTest_337, ConstructorInitializesA_337) {

    EXPECT_EQ(distribution.a(), 1);

}



TEST_F(UniformIntegerDistributionTest_337, ConstructorInitializesB_337) {

    EXPECT_EQ(distribution.b(), 10);

}



TEST_F(UniformIntegerDistributionTest_337, BoundaryConditionAEqualsB_337) {

    uniform_integer_distribution<int> single_point_distribution(5, 5);

    EXPECT_EQ(single_point_distribution.a(), 5);

    EXPECT_EQ(single_point_distribution.b(), 5);

}



// Assuming operator() generates a value within the range [a, b]

TEST_F(UniformIntegerDistributionTest_337, OperatorGeneratesValueInRange_337) {

    struct MockGenerator {

        unsigned int operator()() { return 42; } // Arbitrary value

    };

    MockGenerator generator;

    auto result = distribution(generator);

    EXPECT_GE(result, 1);

    EXPECT_LE(result, 10);

}



// Assuming no observable exception for normal operation

TEST_F(UniformIntegerDistributionTest_337, NoExceptionOnValidRange_337) {

    struct MockGenerator {

        unsigned int operator()() { return 42; } // Arbitrary value

    };

    MockGenerator generator;

    EXPECT_NO_THROW(distribution(generator));

}

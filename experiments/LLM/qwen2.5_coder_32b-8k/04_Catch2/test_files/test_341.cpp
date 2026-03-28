#include <gtest/gtest.h>

#include "catch2/internal/catch_uniform_floating_point_distribution.hpp"



class CatchUniformFloatingPointDistributionTest_341 : public ::testing::Test {

protected:

    // No setup or teardown required for this test case

};



TEST_F(CatchUniformFloatingPointDistributionTest_341, NormalOperationWithSpecificGamma_341) {

    double gamma = 1.99584030953472e+292;

    std::uint64_t expected_max_steps = 9007199254740991;

    EXPECT_EQ(Catch::Detail::calculate_max_steps_in_one_go(gamma), expected_max_steps);

}



TEST_F(CatchUniformFloatingPointDistributionTest_341, NormalOperationWithDifferentGamma_341) {

    double gamma = 1.0;

    std::uint64_t expected_max_steps = static_cast<std::uint64_t>(-1);

    EXPECT_EQ(Catch::Detail::calculate_max_steps_in_one_go(gamma), expected_max_steps);

}



TEST_F(CatchUniformFloatingPointDistributionTest_341, BoundaryConditionWithMaxDoubleGamma_341) {

    double gamma = std::numeric_limits<double>::max();

    std::uint64_t expected_max_steps = static_cast<std::uint64_t>(-1);

    EXPECT_EQ(Catch::Detail::calculate_max_steps_in_one_go(gamma), expected_max_steps);

}



TEST_F(CatchUniformFloatingPointDistributionTest_341, BoundaryConditionWithMinDoubleGamma_341) {

    double gamma = std::numeric_limits<double>::min();

    std::uint64_t expected_max_steps = static_cast<std::uint64_t>(-1);

    EXPECT_EQ(Catch::Detail::calculate_max_steps_in_one_go(gamma), expected_max_steps);

}



TEST_F(CatchUniformFloatingPointDistributionTest_341, BoundaryConditionWithZeroGamma_341) {

    double gamma = 0.0;

    std::uint64_t expected_max_steps = static_cast<std::uint64_t>(-1);

    EXPECT_EQ(Catch::Detail::calculate_max_steps_in_one_go(gamma), expected_max_steps);

}



TEST_F(CatchUniformFloatingPointDistributionTest_341, BoundaryConditionWithNegativeGamma_341) {

    double gamma = -1.0;

    std::uint64_t expected_max_steps = static_cast<std::uint64_t>(-1);

    EXPECT_EQ(Catch::Detail::calculate_max_steps_in_one_go(gamma), expected_max_steps);

}

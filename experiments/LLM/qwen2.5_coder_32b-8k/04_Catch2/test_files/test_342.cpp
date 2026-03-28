#include <gtest/gtest.h>

#include "catch2/internal/catch_uniform_floating_point_distribution.hpp"



class CalculateMaxStepsInOneGoTest_342 : public ::testing::Test {

protected:

    using namespace Catch::Detail;

};



TEST_F(CalculateMaxStepsInOneGoTest_342, NormalOperation_GammaNotSpecial_342) {

    float gamma = 1.0f; // Any value other than the special case

    std::uint32_t result = Catch::Detail::calculate_max_steps_in_one_go(gamma);

    EXPECT_EQ(result, static_cast<std::uint32_t>(-1));

}



TEST_F(CalculateMaxStepsInOneGoTest_342, NormalOperation_GammaSpecialCase_342) {

    float gamma = 2.028241e+31f; // The special case

    std::uint32_t result = Catch::Detail::calculate_max_steps_in_one_go(gamma);

    EXPECT_EQ(result, 16777215u);

}



TEST_F(CalculateMaxStepsInOneGoTest_342, BoundaryCondition_ZeroGamma_342) {

    float gamma = 0.0f;

    std::uint32_t result = Catch::Detail::calculate_max_steps_in_one_go(gamma);

    EXPECT_EQ(result, static_cast<std::uint32_t>(-1));

}



TEST_F(CalculateMaxStepsInOneGoTest_342, BoundaryCondition_MaxFloatGamma_342) {

    float gamma = std::numeric_limits<float>::max();

    std::uint32_t result = Catch::Detail::calculate_max_steps_in_one_go(gamma);

    EXPECT_EQ(result, static_cast<std::uint32_t>(-1));

}



TEST_F(CalculateMaxStepsInOneGoTest_342, BoundaryCondition_NegativeGamma_342) {

    float gamma = -1.0f;

    std::uint32_t result = Catch::Detail::calculate_max_steps_in_one_go(gamma);

    EXPECT_EQ(result, static_cast<std::uint32_t>(-1));

}

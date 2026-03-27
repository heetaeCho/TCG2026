#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/yaml-cpp/src/contrib/dragonbox.h"



using namespace YAML::jkj::dragonbox::policy::decimal_to_binary_rounding;



TEST_F(DragonboxNearestTowardZeroPolicyTest_368, NormalIntervalReturnsEmptyInterval_368) {

    // Test normal operation where the function is expected to return an empty interval.

    auto result = nearest_toward_zero_t::normal_interval<int>(0);

    EXPECT_TRUE(result.empty());

}



TEST_F(DragonboxNearestTowardZeroPolicyTest_368, NormalIntervalWithPositiveSignificandBitsReturnsEmptyInterval_368) {

    // Test boundary condition with a positive significand bits.

    auto result = nearest_toward_zero_t::normal_interval<int>(1);

    EXPECT_TRUE(result.empty());

}



TEST_F(DragonboxNearestTowardZeroPolicyTest_368, NormalIntervalWithNegativeSignificandBitsReturnsEmptyInterval_368) {

    // Test boundary condition with a negative significand bits.

    auto result = nearest_toward_zero_t::normal_interval<int>(-1);

    EXPECT_TRUE(result.empty());

}



TEST_F(DragonboxNearestTowardZeroPolicyTest_368, NormalIntervalWithMaxIntSignificandBitsReturnsEmptyInterval_368) {

    // Test boundary condition with the maximum int value for significand bits.

    auto result = nearest_toward_zero_t::normal_interval<int>(std::numeric_limits<int>::max());

    EXPECT_TRUE(result.empty());

}



TEST_F(DragonboxNearestTowardZeroPolicyTest_368, NormalIntervalWithMinIntSignificandBitsReturnsEmptyInterval_368) {

    // Test boundary condition with the minimum int value for significand bits.

    auto result = nearest_toward_zero_t::normal_interval<int>(std::numeric_limits<int>::min());

    EXPECT_TRUE(result.empty());

}

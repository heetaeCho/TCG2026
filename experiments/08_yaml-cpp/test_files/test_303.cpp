#include <gtest/gtest.h>

#include "TestProjects/yaml-cpp/src/contrib/dragonbox.h"



using namespace YAML::jkj::dragonbox::detail::wuint;



TEST_F(uint128Test_303, DefaultConstructorInitializesToZero_303) {

    uint128 num;

    EXPECT_EQ(num.high(), 0);

    EXPECT_EQ(num.low(), 0);

}



TEST_F(uint128Test_303, ParameterizedConstructorSetsValues_303) {

    std::uint_least64_t high_value = 123456789;

    std::uint_least64_t low_value = 987654321;

    uint128 num(high_value, low_value);

    EXPECT_EQ(num.high(), high_value);

    EXPECT_EQ(num.low(), low_value);

}



TEST_F(uint128Test_303, HighReturnsCorrectValue_303) {

    std::uint_least64_t expected_high = 987654321;

    uint128 num(expected_high, 0);

    EXPECT_EQ(num.high(), expected_high);

}



TEST_F(uint128Test_303, LowReturnsCorrectValue_303) {

    std::uint_least64_t expected_low = 123456789;

    uint128 num(0, expected_low);

    EXPECT_EQ(num.low(), expected_low);

}



TEST_F(uint128Test_303, OperatorPlusEqualsUpdatesLow_303) {

    std::uint_least64_t initial_low = 10;

    std::uint_least64_t increment = 5;

    uint128 num(0, initial_low);

    num += increment;

    EXPECT_EQ(num.high(), 0);

    EXPECT_EQ(num.low(), initial_low + increment);

}



TEST_F(uint128Test_303, OperatorPlusEqualsHandlesCarry_303) {

    std::uint_least64_t initial_low = UINT64_MAX - 5;

    std::uint_least64_t increment = 10;

    uint128 num(0, initial_low);

    num += increment;

    EXPECT_EQ(num.high(), 1);

    EXPECT_EQ(num.low(), 5);

}



TEST_F(uint128Test_303, OperatorPlusEqualsBoundaryCondition_303) {

    std::uint_least64_t initial_low = UINT64_MAX;

    std::uint_least64_t increment = 0;

    uint128 num(0, initial_low);

    num += increment;

    EXPECT_EQ(num.high(), 0);

    EXPECT_EQ(num.low(), initial_low + increment);

}



TEST_F(uint128Test_303, OperatorPlusEqualsLargeIncrement_303) {

    std::uint_least64_t initial_low = UINT64_MAX - 100;

    std::uint_least64_t increment = 200;

    uint128 num(0, initial_low);

    num += increment;

    EXPECT_EQ(num.high(), 1);

    EXPECT_EQ(num.low(), 100);

}

#include <gtest/gtest.h>
#include "contrib/dragonbox.h"

namespace detail = YAML::jkj::dragonbox::detail;

// Since we're testing template metaprogramming utilities that are deeply internal
// to the dragonbox implementation, we need to work with the types defined in the header.
// The check_policy_list_validity function is a constexpr function used at compile time.

// We test it through the higher-level to_decimal API which uses these policy checks internally.

class DragonboxPolicyTest_414 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that to_decimal works with float (default policies go through check_policy_list_validity)
TEST_F(DragonboxPolicyTest_414, FloatToDecimalDefaultPolicies_414) {
    float value = 1.0f;
    auto result = YAML::jkj::dragonbox::to_decimal(value);
    EXPECT_EQ(result.significand, 1u);
    EXPECT_EQ(result.exponent, 0);
    EXPECT_FALSE(result.is_negative);
}

// Test that to_decimal works with double (default policies)
TEST_F(DragonboxPolicyTest_414, DoubleToDecimalDefaultPolicies_414) {
    double value = 1.0;
    auto result = YAML::jkj::dragonbox::to_decimal(value);
    EXPECT_EQ(result.significand, 1u);
    EXPECT_EQ(result.exponent, 0);
    EXPECT_FALSE(result.is_negative);
}

// Test negative float
TEST_F(DragonboxPolicyTest_414, NegativeFloatToDecimal_414) {
    float value = -1.0f;
    auto result = YAML::jkj::dragonbox::to_decimal(value);
    EXPECT_EQ(result.significand, 1u);
    EXPECT_EQ(result.exponent, 0);
    EXPECT_TRUE(result.is_negative);
}

// Test negative double
TEST_F(DragonboxPolicyTest_414, NegativeDoubleToDecimal_414) {
    double value = -1.0;
    auto result = YAML::jkj::dragonbox::to_decimal(value);
    EXPECT_EQ(result.significand, 1u);
    EXPECT_EQ(result.exponent, 0);
    EXPECT_TRUE(result.is_negative);
}

// Test small float value
TEST_F(DragonboxPolicyTest_414, SmallFloatToDecimal_414) {
    float value = 0.1f;
    auto result = YAML::jkj::dragonbox::to_decimal(value);
    EXPECT_GT(result.significand, 0u);
}

// Test small double value
TEST_F(DragonboxPolicyTest_414, SmallDoubleToDecimal_414) {
    double value = 0.1;
    auto result = YAML::jkj::dragonbox::to_decimal(value);
    EXPECT_GT(result.significand, 0u);
}

// Test large float value
TEST_F(DragonboxPolicyTest_414, LargeFloatToDecimal_414) {
    float value = 1.0e30f;
    auto result = YAML::jkj::dragonbox::to_decimal(value);
    EXPECT_GT(result.significand, 0u);
    EXPECT_GT(result.exponent, 0);
}

// Test large double value
TEST_F(DragonboxPolicyTest_414, LargeDoubleToDecimal_414) {
    double value = 1.0e100;
    auto result = YAML::jkj::dragonbox::to_decimal(value);
    EXPECT_GT(result.significand, 0u);
    EXPECT_GT(result.exponent, 0);
}

// Test boundary: smallest positive float
TEST_F(DragonboxPolicyTest_414, SmallestPositiveFloat_414) {
    float value = std::numeric_limits<float>::min();
    auto result = YAML::jkj::dragonbox::to_decimal(value);
    EXPECT_GT(result.significand, 0u);
    EXPECT_FALSE(result.is_negative);
}

// Test boundary: largest finite double
TEST_F(DragonboxPolicyTest_414, LargestFiniteDouble_414) {
    double value = std::numeric_limits<double>::max();
    auto result = YAML::jkj::dragonbox::to_decimal(value);
    EXPECT_GT(result.significand, 0u);
    EXPECT_FALSE(result.is_negative);
}

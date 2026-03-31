#include "gtest/gtest.h"
#include "contrib/dragonbox.h"

namespace {

using namespace YAML::jkj::dragonbox;

// Mock/helper types that satisfy the template requirements
struct MockSignedSignificandBits_Negative {
    constexpr bool is_negative() const noexcept { return true; }
};

struct MockSignedSignificandBits_Positive {
    constexpr bool is_negative() const noexcept { return false; }
};

// We need to use the actual dragonbox types if possible, but since we're testing
// the policy in isolation, we'll try to use the real float/double carrier types.

class ReturnSignTest_334 : public ::testing::Test {
protected:
    using sign_policy = policy::sign::return_sign_t;
};

// Test with actual dragonbox float types if available
TEST_F(ReturnSignTest_334, HandleSignPositiveFloat_334) {
    // Use the actual dragonbox to_decimal to get real types, then test handle_sign
    // For float
    float positive_val = 3.14f;
    auto result = to_decimal(positive_val, policy::sign::return_sign{});
    // A positive float should have is_negative == false
    EXPECT_FALSE(result.is_negative);
    EXPECT_GT(result.significand, 0u);
}

TEST_F(ReturnSignTest_334, HandleSignNegativeFloat_334) {
    float negative_val = -3.14f;
    auto result = to_decimal(negative_val, policy::sign::return_sign{});
    EXPECT_TRUE(result.is_negative);
    EXPECT_GT(result.significand, 0u);
}

TEST_F(ReturnSignTest_334, HandleSignPositiveDouble_334) {
    double positive_val = 2.718281828;
    auto result = to_decimal(positive_val, policy::sign::return_sign{});
    EXPECT_FALSE(result.is_negative);
    EXPECT_GT(result.significand, 0u);
}

TEST_F(ReturnSignTest_334, HandleSignNegativeDouble_334) {
    double negative_val = -2.718281828;
    auto result = to_decimal(negative_val, policy::sign::return_sign{});
    EXPECT_TRUE(result.is_negative);
    EXPECT_GT(result.significand, 0u);
}

TEST_F(ReturnSignTest_334, HandleSignPositiveZeroFloat_334) {
    float pos_zero = 0.0f;
    auto result = to_decimal(pos_zero, policy::sign::return_sign{});
    EXPECT_FALSE(result.is_negative);
    EXPECT_EQ(result.significand, 0u);
}

TEST_F(ReturnSignTest_334, HandleSignNegativeZeroFloat_334) {
    float neg_zero = -0.0f;
    auto result = to_decimal(neg_zero, policy::sign::return_sign{});
    EXPECT_TRUE(result.is_negative);
    EXPECT_EQ(result.significand, 0u);
}

TEST_F(ReturnSignTest_334, HandleSignPositiveZeroDouble_334) {
    double pos_zero = 0.0;
    auto result = to_decimal(pos_zero, policy::sign::return_sign{});
    EXPECT_FALSE(result.is_negative);
    EXPECT_EQ(result.significand, 0u);
}

TEST_F(ReturnSignTest_334, HandleSignNegativeZeroDouble_334) {
    double neg_zero = -0.0;
    auto result = to_decimal(neg_zero, policy::sign::return_sign{});
    EXPECT_TRUE(result.is_negative);
    EXPECT_EQ(result.significand, 0u);
}

TEST_F(ReturnSignTest_334, HandleSignOneFloat_334) {
    float val = 1.0f;
    auto result = to_decimal(val, policy::sign::return_sign{});
    EXPECT_FALSE(result.is_negative);
    EXPECT_EQ(result.significand, 1u);
    EXPECT_EQ(result.exponent, 0);
}

TEST_F(ReturnSignTest_334, HandleSignNegativeOneFloat_334) {
    float val = -1.0f;
    auto result = to_decimal(val, policy::sign::return_sign{});
    EXPECT_TRUE(result.is_negative);
    EXPECT_EQ(result.significand, 1u);
    EXPECT_EQ(result.exponent, 0);
}

TEST_F(ReturnSignTest_334, HandleSignSmallPositiveDouble_334) {
    double val = 1e-300;
    auto result = to_decimal(val, policy::sign::return_sign{});
    EXPECT_FALSE(result.is_negative);
    EXPECT_GT(result.significand, 0u);
}

TEST_F(ReturnSignTest_334, HandleSignSmallNegativeDouble_334) {
    double val = -1e-300;
    auto result = to_decimal(val, policy::sign::return_sign{});
    EXPECT_TRUE(result.is_negative);
    EXPECT_GT(result.significand, 0u);
}

} // namespace

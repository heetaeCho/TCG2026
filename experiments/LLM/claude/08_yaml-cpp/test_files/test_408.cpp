#include "gtest/gtest.h"
#include <cstdint>
#include <cmath>
#include <limits>
#include <cstring>

// Include the dragonbox header
#include "contrib/dragonbox.h"

namespace {

using namespace YAML::jkj::dragonbox;

// We need to use the actual policy types and format traits from dragonbox
// For float (ieee754_binary32) and double (ieee754_binary64)

// Helper to get the bits of a float
uint32_t float_to_bits(float f) {
    uint32_t bits;
    std::memcpy(&bits, &f, sizeof(bits));
    return bits;
}

uint64_t double_to_bits(double d) {
    uint64_t bits;
    std::memcpy(&bits, &d, sizeof(bits));
    return bits;
}

// Helper: extract exponent bits from float
int float_exponent_bits(float f) {
    uint32_t bits = float_to_bits(f);
    return static_cast<int>((bits >> 23) & 0xFF);
}

// Helper: extract exponent bits from double
int double_exponent_bits(double d) {
    uint64_t bits = double_to_bits(d);
    return static_cast<int>((bits >> 52) & 0x7FF);
}

class ComputeRightClosedDirectedFloat_408 : public ::testing::Test {
protected:
    using format_traits = detail::ieee754_binary_traits<detail::ieee754_binary32, uint32_t>;
    using impl_type = detail::impl<format_traits>;
    
    // Use default policies similar to what to_decimal would use
    using sign_policy = detail::policy_impl::sign::return_sign_t;
    using trailing_zero_policy = detail::policy_impl::trailing_zero::ignore_t;
    using cache_policy = detail::policy_impl::cache::full_t;
    using preferred_integer_types_policy = detail::policy_impl::preferred_integer_types::match_t;
    
    auto compute(float f) {
        uint32_t bits = float_to_bits(f);
        auto s = detail::signed_significand_bits<format_traits>(bits);
        int exp_bits = float_exponent_bits(f);
        return impl_type::compute_right_closed_directed<
            sign_policy, trailing_zero_policy, cache_policy, preferred_integer_types_policy>(
            s, static_cast<detail::exponent_int>(exp_bits));
    }
};

class ComputeRightClosedDirectedDouble_408 : public ::testing::Test {
protected:
    using format_traits = detail::ieee754_binary_traits<detail::ieee754_binary64, uint64_t>;
    using impl_type = detail::impl<format_traits>;
    
    using sign_policy = detail::policy_impl::sign::return_sign_t;
    using trailing_zero_policy = detail::policy_impl::trailing_zero::ignore_t;
    using cache_policy = detail::policy_impl::cache::full_t;
    using preferred_integer_types_policy = detail::policy_impl::preferred_integer_types::match_t;
    
    auto compute(double d) {
        uint64_t bits = double_to_bits(d);
        auto s = detail::signed_significand_bits<format_traits>(bits);
        int exp_bits = double_exponent_bits(d);
        return impl_type::compute_right_closed_directed<
            sign_policy, trailing_zero_policy, cache_policy, preferred_integer_types_policy>(
            s, static_cast<detail::exponent_int>(exp_bits));
    }
};

// ===================== Float Tests =====================

TEST_F(ComputeRightClosedDirectedFloat_408, PositiveOne_408) {
    auto result = compute(1.0f);
    EXPECT_FALSE(result.is_negative);
    EXPECT_EQ(result.significand, 1u);
    EXPECT_EQ(result.exponent, 0);
}

TEST_F(ComputeRightClosedDirectedFloat_408, PositiveTwo_408) {
    auto result = compute(2.0f);
    EXPECT_FALSE(result.is_negative);
    EXPECT_EQ(result.significand, 2u);
    EXPECT_EQ(result.exponent, 0);
}

TEST_F(ComputeRightClosedDirectedFloat_408, PositiveTen_408) {
    auto result = compute(10.0f);
    EXPECT_FALSE(result.is_negative);
    EXPECT_EQ(result.significand, 1u);
    EXPECT_EQ(result.exponent, 1);
}

TEST_F(ComputeRightClosedDirectedFloat_408, PositiveHalf_408) {
    auto result = compute(0.5f);
    EXPECT_FALSE(result.is_negative);
    EXPECT_EQ(result.significand, 5u);
    EXPECT_EQ(result.exponent, -1);
}

TEST_F(ComputeRightClosedDirectedFloat_408, NegativeOne_408) {
    auto result = compute(-1.0f);
    EXPECT_TRUE(result.is_negative);
    EXPECT_EQ(result.significand, 1u);
    EXPECT_EQ(result.exponent, 0);
}

TEST_F(ComputeRightClosedDirectedFloat_408, NegativeHalf_408) {
    auto result = compute(-0.5f);
    EXPECT_TRUE(result.is_negative);
    EXPECT_EQ(result.significand, 5u);
    EXPECT_EQ(result.exponent, -1);
}

TEST_F(ComputeRightClosedDirectedFloat_408, SmallPositiveFloat_408) {
    auto result = compute(0.1f);
    EXPECT_FALSE(result.is_negative);
    // 0.1f is not exactly representable; just check significand and exponent reconstruct properly
    double reconstructed = result.significand * std::pow(10.0, result.exponent);
    EXPECT_NEAR(reconstructed, 0.1, 1e-7);
}

TEST_F(ComputeRightClosedDirectedFloat_408, SmallestNormalFloat_408) {
    float f = std::numeric_limits<float>::min(); // smallest normal
    auto result = compute(f);
    EXPECT_FALSE(result.is_negative);
    double reconstructed = result.significand * std::pow(10.0, result.exponent);
    EXPECT_NEAR(reconstructed, static_cast<double>(f), static_cast<double>(f) * 1e-6);
}

TEST_F(ComputeRightClosedDirectedFloat_408, SmallestSubnormalFloat_408) {
    float f = std::numeric_limits<float>::denorm_min();
    auto result = compute(f);
    EXPECT_FALSE(result.is_negative);
    double reconstructed = result.significand * std::pow(10.0, result.exponent);
    EXPECT_NEAR(reconstructed, static_cast<double>(f), static_cast<double>(f) * 1e-3);
}

TEST_F(ComputeRightClosedDirectedFloat_408, LargestFloat_408) {
    float f = std::numeric_limits<float>::max();
    auto result = compute(f);
    EXPECT_FALSE(result.is_negative);
    EXPECT_GT(result.significand, 0u);
}

TEST_F(ComputeRightClosedDirectedFloat_408, PowerOfTwo_408) {
    // Powers of two trigger shorter_interval logic
    auto result = compute(4.0f);
    EXPECT_FALSE(result.is_negative);
    EXPECT_EQ(result.significand, 4u);
    EXPECT_EQ(result.exponent, 0);
}

TEST_F(ComputeRightClosedDirectedFloat_408, PointTwoFive_408) {
    auto result = compute(0.25f);
    EXPECT_FALSE(result.is_negative);
    EXPECT_EQ(result.significand, 25u);
    EXPECT_EQ(result.exponent, -2);
}

TEST_F(ComputeRightClosedDirectedFloat_408, OneHundred_408) {
    auto result = compute(100.0f);
    EXPECT_FALSE(result.is_negative);
    EXPECT_EQ(result.significand, 1u);
    EXPECT_EQ(result.exponent, 2);
}

TEST_F(ComputeRightClosedDirectedFloat_408, PointOneTwoFive_408) {
    auto result = compute(0.125f);
    EXPECT_FALSE(result.is_negative);
    EXPECT_EQ(result.significand, 125u);
    EXPECT_EQ(result.exponent, -3);
}

// ===================== Double Tests =====================

TEST_F(ComputeRightClosedDirectedDouble_408, PositiveOne_408) {
    auto result = compute(1.0);
    EXPECT_FALSE(result.is_negative);
    EXPECT_EQ(result.significand, 1ull);
    EXPECT_EQ(result.exponent, 0);
}

TEST_F(ComputeRightClosedDirectedDouble_408, PositiveTwo_408) {
    auto result = compute(2.0);
    EXPECT_FALSE(result.is_negative);
    EXPECT_EQ(result.significand, 2ull);
    EXPECT_EQ(result.exponent, 0);
}

TEST_F(ComputeRightClosedDirectedDouble_408, PositiveTen_408) {
    auto result = compute(10.0);
    EXPECT_FALSE(result.is_negative);
    EXPECT_EQ(result.significand, 1ull);
    EXPECT_EQ(result.exponent, 1);
}

TEST_F(ComputeRightClosedDirectedDouble_408, NegativeOne_408) {
    auto result = compute(-1.0);
    EXPECT_TRUE(result.is_negative);
    EXPECT_EQ(result.significand, 1ull);
    EXPECT_EQ(result.exponent, 0);
}

TEST_F(ComputeRightClosedDirectedDouble_408, PositiveHalf_408) {
    auto result = compute(0.5);
    EXPECT_FALSE(result.is_negative);
    EXPECT_EQ(result.significand, 5ull);
    EXPECT_EQ(result.exponent, -1);
}

TEST_F(ComputeRightClosedDirectedDouble_408, SmallPositiveDouble_408) {
    auto result = compute(0.1);
    EXPECT_FALSE(result.is_negative);
    double reconstructed = result.significand * std::pow(10.0, result.exponent);
    EXPECT_NEAR(reconstructed, 0.1, 1e-15);
}

TEST_F(ComputeRightClosedDirectedDouble_408, SmallestNormalDouble_408) {
    double d = std::numeric_limits<double>::min();
    auto result = compute(d);
    EXPECT_FALSE(result.is_negative);
    EXPECT_GT(result.significand, 0ull);
}

TEST_F(ComputeRightClosedDirectedDouble_408, SmallestSubnormalDouble_408) {
    double d = std::numeric_limits<double>::denorm_min();
    auto result = compute(d);
    EXPECT_FALSE(result.is_negative);
    EXPECT_GT(result.significand, 0ull);
}

TEST_F(ComputeRightClosedDirectedDouble_408, LargestDouble_408) {
    double d = std::numeric_limits<double>::max();
    auto result = compute(d);
    EXPECT_FALSE(result.is_negative);
    EXPECT_GT(result.significand, 0ull);
}

TEST_F(ComputeRightClosedDirectedDouble_408, PowerOfTwoDouble_408) {
    // Powers of two with exponent != 1 trigger shorter_interval
    auto result = compute(8.0);
    EXPECT_FALSE(result.is_negative);
    EXPECT_EQ(result.significand, 8ull);
    EXPECT_EQ(result.exponent, 0);
}

TEST_F(ComputeRightClosedDirectedDouble_408, NegativePowerOfTwo_408) {
    auto result = compute(-8.0);
    EXPECT_TRUE(result.is_negative);
    EXPECT_EQ(result.significand, 8ull);
    EXPECT_EQ(result.exponent, 0);
}

TEST_F(ComputeRightClosedDirectedDouble_408, OneThousand_408) {
    auto result = compute(1000.0);
    EXPECT_FALSE(result.is_negative);
    EXPECT_EQ(result.significand, 1ull);
    EXPECT_EQ(result.exponent, 3);
}

TEST_F(ComputeRightClosedDirectedDouble_408, PointZeroOne_408) {
    auto result = compute(0.01);
    EXPECT_FALSE(result.is_negative);
    double reconstructed = result.significand * std::pow(10.0, result.exponent);
    EXPECT_NEAR(reconstructed, 0.01, 1e-15);
}

TEST_F(ComputeRightClosedDirectedDouble_408, Pi_408) {
    auto result = compute(3.141592653589793);
    EXPECT_FALSE(result.is_negative);
    double reconstructed = result.significand * std::pow(10.0, result.exponent);
    EXPECT_NEAR(reconstructed, 3.141592653589793, 1e-14);
}

TEST_F(ComputeRightClosedDirectedDouble_408, NegativePi_408) {
    auto result = compute(-3.141592653589793);
    EXPECT_TRUE(result.is_negative);
    double reconstructed = result.significand * std::pow(10.0, result.exponent);
    EXPECT_NEAR(reconstructed, 3.141592653589793, 1e-14);
}

TEST_F(ComputeRightClosedDirectedDouble_408, ExponentBitsOne_408) {
    // Test with exponent_bits == 1 (binary_exponent != 0, but exponent == 1)
    // For double, exponent_bits=1 means biased exponent=1, so actual exponent = 1 - 1023 = -1022
    // significand = 0 means two_fc = 0, but since exponent_bits == 1, shorter_interval is false
    // This is 2^-1022 which is the smallest normal double
    double d = std::numeric_limits<double>::min();
    auto result = compute(d);
    EXPECT_FALSE(result.is_negative);
    double reconstructed = result.significand * std::pow(10.0, result.exponent);
    EXPECT_NEAR(reconstructed, d, d * 1e-10);
}

// Test reconstruction consistency: the decimal representation should 
// round-trip back to approximately the original value
TEST_F(ComputeRightClosedDirectedDouble_408, ReconstructionConsistency_408) {
    double values[] = {1.0, 2.5, 0.3, 123.456, 1e10, 1e-10, 999.999};
    for (double v : values) {
        auto result = compute(v);
        double reconstructed = result.significand * std::pow(10.0, result.exponent);
        EXPECT_NEAR(reconstructed, v, std::abs(v) * 1e-14) 
            << "Failed for value: " << v;
    }
}

TEST_F(ComputeRightClosedDirectedFloat_408, ReconstructionConsistencyFloat_408) {
    float values[] = {1.0f, 2.5f, 0.3f, 123.456f, 1e5f, 1e-5f, 999.999f};
    for (float v : values) {
        auto result = compute(v);
        double reconstructed = result.significand * std::pow(10.0, result.exponent);
        EXPECT_NEAR(reconstructed, static_cast<double>(v), std::abs(v) * 1e-6) 
            << "Failed for value: " << v;
    }
}

} // namespace

#include <gtest/gtest.h>
#include "contrib/dragonbox.h"

// We need to work with the actual types from the dragonbox header.
// Create a simple mock for SignedSignificandBits that provides is_negative()

namespace {

struct MockSignedSignificandBitsPositive {
    constexpr bool is_negative() const noexcept { return false; }
};

struct MockSignedSignificandBitsNegative {
    constexpr bool is_negative() const noexcept { return true; }
};

using namespace YAML::jkj::dragonbox::policy::decimal_to_binary_rounding;

class NearestTowardMinusInfinityTest_365 : public ::testing::Test {
protected:
    nearest_toward_minus_infinity_t policy;
};

// Test normal_interval with a positive (non-negative) value
TEST_F(NearestTowardMinusInfinityTest_365, NormalIntervalPositiveValue_365) {
    MockSignedSignificandBitsPositive positive_bits;
    auto result = nearest_toward_minus_infinity_t::normal_interval(positive_bits);
    // When is_negative() returns false, the asymmetric_boundary should reflect that
    // The boundary is constructed with is_negative() == false
    EXPECT_FALSE(result.is_closed);
}

// Test normal_interval with a negative value
TEST_F(NearestTowardMinusInfinityTest_365, NormalIntervalNegativeValue_365) {
    MockSignedSignificandBitsNegative negative_bits;
    auto result = nearest_toward_minus_infinity_t::normal_interval(negative_bits);
    // When is_negative() returns true, the asymmetric_boundary should reflect that
    // The boundary is constructed with is_negative() == true
    EXPECT_TRUE(result.is_closed);
}

// Test shorter_interval with a positive (non-negative) value
TEST_F(NearestTowardMinusInfinityTest_365, ShorterIntervalPositiveValue_365) {
    MockSignedSignificandBitsPositive positive_bits;
    auto result = nearest_toward_minus_infinity_t::shorter_interval(positive_bits);
    EXPECT_FALSE(result.is_closed);
}

// Test shorter_interval with a negative value
TEST_F(NearestTowardMinusInfinityTest_365, ShorterIntervalNegativeValue_365) {
    MockSignedSignificandBitsNegative negative_bits;
    auto result = nearest_toward_minus_infinity_t::shorter_interval(negative_bits);
    EXPECT_TRUE(result.is_closed);
}

// Test constexpr capability of normal_interval
TEST_F(NearestTowardMinusInfinityTest_365, NormalIntervalIsConstexpr_365) {
    constexpr MockSignedSignificandBitsPositive positive_bits{};
    constexpr auto result = nearest_toward_minus_infinity_t::normal_interval(positive_bits);
    EXPECT_FALSE(result.is_closed);
}

// Test constexpr capability of normal_interval with negative
TEST_F(NearestTowardMinusInfinityTest_365, NormalIntervalNegativeIsConstexpr_365) {
    constexpr MockSignedSignificandBitsNegative negative_bits{};
    constexpr auto result = nearest_toward_minus_infinity_t::normal_interval(negative_bits);
    EXPECT_TRUE(result.is_closed);
}

// Test that the function is noexcept for normal_interval
TEST_F(NearestTowardMinusInfinityTest_365, NormalIntervalIsNoexcept_365) {
    MockSignedSignificandBitsPositive positive_bits;
    EXPECT_TRUE(noexcept(nearest_toward_minus_infinity_t::normal_interval(positive_bits)));
}

// Test that shorter_interval is noexcept
TEST_F(NearestTowardMinusInfinityTest_365, ShorterIntervalIsNoexcept_365) {
    MockSignedSignificandBitsPositive positive_bits;
    EXPECT_TRUE(noexcept(nearest_toward_minus_infinity_t::shorter_interval(positive_bits)));
}

// Boundary: both positive and negative yield different results
TEST_F(NearestTowardMinusInfinityTest_365, PositiveAndNegativeYieldDifferentResults_365) {
    MockSignedSignificandBitsPositive positive_bits;
    MockSignedSignificandBitsNegative negative_bits;
    auto result_pos = nearest_toward_minus_infinity_t::normal_interval(positive_bits);
    auto result_neg = nearest_toward_minus_infinity_t::normal_interval(negative_bits);
    EXPECT_NE(result_pos.is_closed, result_neg.is_closed);
}

} // anonymous namespace

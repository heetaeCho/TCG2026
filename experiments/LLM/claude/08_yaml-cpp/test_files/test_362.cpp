#include <gtest/gtest.h>

// Include the header under test
#include "./TestProjects/yaml-cpp/src/contrib/dragonbox.h"

namespace {

// Mock SignedSignificandBits for testing
struct MockSignedSignificandBitsNegative {
    constexpr bool is_negative() const noexcept { return true; }
};

struct MockSignedSignificandBitsPositive {
    constexpr bool is_negative() const noexcept { return false; }
};

using NearestTowardPlusInfinity = YAML::jkj::dragonbox::policy::decimal_to_binary_rounding::nearest_toward_plus_infinity_t;

// Test fixture
class NearestTowardPlusInfinityTest_362 : public ::testing::Test {
protected:
    NearestTowardPlusInfinity policy_;
};

// Test normal_interval with negative sign bit
TEST_F(NearestTowardPlusInfinityTest_362, NormalIntervalNegativeReturnsFalseIncludeLeftEndpoint_362) {
    MockSignedSignificandBitsNegative negative_bits;
    auto result = NearestTowardPlusInfinity::normal_interval(negative_bits);
    // When is_negative() returns true, !true = false
    // asymmetric_boundary constructed with false means include_left_endpoint is false
    EXPECT_FALSE(result.include_left_endpoint);
}

// Test normal_interval with positive sign bit
TEST_F(NearestTowardPlusInfinityTest_362, NormalIntervalPositiveReturnsTrueIncludeLeftEndpoint_362) {
    MockSignedSignificandBitsPositive positive_bits;
    auto result = NearestTowardPlusInfinity::normal_interval(positive_bits);
    // When is_negative() returns false, !false = true
    // asymmetric_boundary constructed with true means include_left_endpoint is true
    EXPECT_TRUE(result.include_left_endpoint);
}

// Test shorter_interval with negative sign bit
TEST_F(NearestTowardPlusInfinityTest_362, ShorterIntervalNegativeReturnsFalseIncludeLeftEndpoint_362) {
    MockSignedSignificandBitsNegative negative_bits;
    auto result = NearestTowardPlusInfinity::shorter_interval(negative_bits);
    // Same logic as normal_interval for nearest_toward_plus_infinity
    EXPECT_FALSE(result.include_left_endpoint);
}

// Test shorter_interval with positive sign bit
TEST_F(NearestTowardPlusInfinityTest_362, ShorterIntervalPositiveReturnsTrueIncludeLeftEndpoint_362) {
    MockSignedSignificandBitsPositive positive_bits;
    auto result = NearestTowardPlusInfinity::shorter_interval(positive_bits);
    EXPECT_TRUE(result.include_left_endpoint);
}

// Test constexpr evaluation of normal_interval with negative
TEST_F(NearestTowardPlusInfinityTest_362, NormalIntervalIsConstexprNegative_362) {
    constexpr MockSignedSignificandBitsNegative negative_bits{};
    constexpr auto result = NearestTowardPlusInfinity::normal_interval(negative_bits);
    EXPECT_FALSE(result.include_left_endpoint);
}

// Test constexpr evaluation of normal_interval with positive
TEST_F(NearestTowardPlusInfinityTest_362, NormalIntervalIsConstexprPositive_362) {
    constexpr MockSignedSignificandBitsPositive positive_bits{};
    constexpr auto result = NearestTowardPlusInfinity::normal_interval(positive_bits);
    EXPECT_TRUE(result.include_left_endpoint);
}

// Test noexcept specification for normal_interval
TEST_F(NearestTowardPlusInfinityTest_362, NormalIntervalIsNoexcept_362) {
    MockSignedSignificandBitsNegative negative_bits;
    EXPECT_TRUE(noexcept(NearestTowardPlusInfinity::normal_interval(negative_bits)));
}

// Test noexcept specification for shorter_interval
TEST_F(NearestTowardPlusInfinityTest_362, ShorterIntervalIsNoexcept_362) {
    MockSignedSignificandBitsPositive positive_bits;
    EXPECT_TRUE(noexcept(NearestTowardPlusInfinity::shorter_interval(positive_bits)));
}

} // namespace

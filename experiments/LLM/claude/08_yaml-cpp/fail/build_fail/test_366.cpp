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

using NearestTowardMinusInfinity = YAML::jkj::dragonbox::policy::decimal_to_binary_rounding::nearest_toward_minus_infinity_t;

// Test fixture
class NearestTowardMinusInfinityTest_366 : public ::testing::Test {
protected:
    NearestTowardMinusInfinity policy_;
};

// Test shorter_interval with negative signed significand bits
TEST_F(NearestTowardMinusInfinityTest_366, ShorterIntervalNegativeReturnsTrue_366) {
    MockSignedSignificandBitsNegative neg_bits;
    auto result = NearestTowardMinusInfinity::shorter_interval(neg_bits);
    // When is_negative() returns true, the asymmetric_boundary should reflect that
    // The interval_type::asymmetric_boundary is constructed with is_negative() result
    EXPECT_TRUE(result.is_closed);
}

// Test shorter_interval with positive signed significand bits
TEST_F(NearestTowardMinusInfinityTest_366, ShorterIntervalPositiveReturnsFalse_366) {
    MockSignedSignificandBitsPositive pos_bits;
    auto result = NearestTowardMinusInfinity::shorter_interval(pos_bits);
    // When is_negative() returns false, the asymmetric_boundary should reflect that
    EXPECT_FALSE(result.is_closed);
}

// Test that shorter_interval is constexpr with negative bits
TEST_F(NearestTowardMinusInfinityTest_366, ShorterIntervalIsConstexprNegative_366) {
    constexpr auto result = NearestTowardMinusInfinity::shorter_interval(MockSignedSignificandBitsNegative{});
    EXPECT_TRUE(result.is_closed);
}

// Test that shorter_interval is constexpr with positive bits
TEST_F(NearestTowardMinusInfinityTest_366, ShorterIntervalIsConstexprPositive_366) {
    constexpr auto result = NearestTowardMinusInfinity::shorter_interval(MockSignedSignificandBitsPositive{});
    EXPECT_FALSE(result.is_closed);
}

// Test normal_interval with negative signed significand bits
TEST_F(NearestTowardMinusInfinityTest_366, NormalIntervalNegativeReturnsTrue_366) {
    MockSignedSignificandBitsNegative neg_bits;
    auto result = NearestTowardMinusInfinity::normal_interval(neg_bits);
    EXPECT_TRUE(result.is_closed);
}

// Test normal_interval with positive signed significand bits
TEST_F(NearestTowardMinusInfinityTest_366, NormalIntervalPositiveReturnsFalse_366) {
    MockSignedSignificandBitsPositive pos_bits;
    auto result = NearestTowardMinusInfinity::normal_interval(pos_bits);
    EXPECT_FALSE(result.is_closed);
}

// Test that normal_interval is constexpr with negative bits
TEST_F(NearestTowardMinusInfinityTest_366, NormalIntervalIsConstexprNegative_366) {
    constexpr auto result = NearestTowardMinusInfinity::normal_interval(MockSignedSignificandBitsNegative{});
    EXPECT_TRUE(result.is_closed);
}

// Test that normal_interval is constexpr with positive bits
TEST_F(NearestTowardMinusInfinityTest_366, NormalIntervalIsConstexprPositive_366) {
    constexpr auto result = NearestTowardMinusInfinity::normal_interval(MockSignedSignificandBitsPositive{});
    EXPECT_FALSE(result.is_closed);
}

// Test that the struct is default constructible
TEST_F(NearestTowardMinusInfinityTest_366, IsDefaultConstructible_366) {
    EXPECT_TRUE(std::is_default_constructible<NearestTowardMinusInfinity>::value);
}

// Boundary: Test that shorter_interval and normal_interval return consistent results for the same input
TEST_F(NearestTowardMinusInfinityTest_366, ShorterAndNormalConsistentForNegative_366) {
    MockSignedSignificandBitsNegative neg_bits;
    auto shorter_result = NearestTowardMinusInfinity::shorter_interval(neg_bits);
    auto normal_result = NearestTowardMinusInfinity::normal_interval(neg_bits);
    EXPECT_EQ(shorter_result.is_closed, normal_result.is_closed);
}

TEST_F(NearestTowardMinusInfinityTest_366, ShorterAndNormalConsistentForPositive_366) {
    MockSignedSignificandBitsPositive pos_bits;
    auto shorter_result = NearestTowardMinusInfinity::shorter_interval(pos_bits);
    auto normal_result = NearestTowardMinusInfinity::normal_interval(pos_bits);
    EXPECT_EQ(shorter_result.is_closed, normal_result.is_closed);
}

}  // namespace

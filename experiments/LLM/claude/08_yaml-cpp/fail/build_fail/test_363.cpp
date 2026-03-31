#include <gtest/gtest.h>

// Include the header under test
#include "./TestProjects/yaml-cpp/src/contrib/dragonbox.h"

namespace {

// Mock SignedSignificandBits class for testing
struct MockSignedSignificandBitsNegative {
    constexpr bool is_negative() const noexcept { return true; }
};

struct MockSignedSignificandBitsPositive {
    constexpr bool is_negative() const noexcept { return false; }
};

using nearest_toward_plus_infinity_t = 
    YAML::jkj::dragonbox::policy::decimal_to_binary_rounding::nearest_toward_plus_infinity_t;

// Test fixture
class NearestTowardPlusInfinityTest_363 : public ::testing::Test {
protected:
    nearest_toward_plus_infinity_t policy;
};

// Test shorter_interval with negative signed significand bits
// When is_negative() returns true, the result should be !true = false
TEST_F(NearestTowardPlusInfinityTest_363, ShorterIntervalWithNegativeSign_363) {
    MockSignedSignificandBitsNegative negative_bits;
    auto result = nearest_toward_plus_infinity_t::shorter_interval(negative_bits);
    // !s.is_negative() where is_negative() == true => false
    EXPECT_FALSE(result.is_closed);
}

// Test shorter_interval with positive signed significand bits
// When is_negative() returns false, the result should be !false = true
TEST_F(NearestTowardPlusInfinityTest_363, ShorterIntervalWithPositiveSign_363) {
    MockSignedSignificandBitsPositive positive_bits;
    auto result = nearest_toward_plus_infinity_t::shorter_interval(positive_bits);
    // !s.is_negative() where is_negative() == false => true
    EXPECT_TRUE(result.is_closed);
}

// Test that shorter_interval is constexpr with negative bits
TEST_F(NearestTowardPlusInfinityTest_363, ShorterIntervalConstexprNegative_363) {
    constexpr MockSignedSignificandBitsNegative negative_bits{};
    constexpr auto result = nearest_toward_plus_infinity_t::shorter_interval(negative_bits);
    EXPECT_FALSE(result.is_closed);
}

// Test that shorter_interval is constexpr with positive bits
TEST_F(NearestTowardPlusInfinityTest_363, ShorterIntervalConstexprPositive_363) {
    constexpr MockSignedSignificandBitsPositive positive_bits{};
    constexpr auto result = nearest_toward_plus_infinity_t::shorter_interval(positive_bits);
    EXPECT_TRUE(result.is_closed);
}

// Boundary: Test that the function is noexcept
TEST_F(NearestTowardPlusInfinityTest_363, ShorterIntervalIsNoexcept_363) {
    MockSignedSignificandBitsNegative negative_bits;
    MockSignedSignificandBitsPositive positive_bits;
    EXPECT_TRUE(noexcept(nearest_toward_plus_infinity_t::shorter_interval(negative_bits)));
    EXPECT_TRUE(noexcept(nearest_toward_plus_infinity_t::shorter_interval(positive_bits)));
}

// Test normal_interval with negative signed significand bits
TEST_F(NearestTowardPlusInfinityTest_363, NormalIntervalWithNegativeSign_363) {
    MockSignedSignificandBitsNegative negative_bits;
    auto result = nearest_toward_plus_infinity_t::normal_interval(negative_bits);
    // For nearest_toward_plus_infinity, normal_interval with negative: !is_negative() = false
    EXPECT_FALSE(result.is_closed);
}

// Test normal_interval with positive signed significand bits
TEST_F(NearestTowardPlusInfinityTest_363, NormalIntervalWithPositiveSign_363) {
    MockSignedSignificandBitsPositive positive_bits;
    auto result = nearest_toward_plus_infinity_t::normal_interval(positive_bits);
    // For nearest_toward_plus_infinity, normal_interval with positive: !is_negative() = true
    EXPECT_TRUE(result.is_closed);
}

} // namespace

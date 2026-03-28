#include <gtest/gtest.h>
#include <type_traits>

// Include the header under test
#include "./TestProjects/yaml-cpp/src/contrib/dragonbox.h"

namespace {

// Mock SignedSignificandBits that returns true for has_even_significand_bits
struct EvenSignificandBits {
    constexpr bool has_even_significand_bits() const noexcept { return true; }
};

// Mock SignedSignificandBits that returns false for has_even_significand_bits
struct OddSignificandBits {
    constexpr bool has_even_significand_bits() const noexcept { return false; }
};

using NearestToEven = YAML::jkj::dragonbox::policy::decimal_to_binary_rounding::nearest_to_even_t;

// Test fixture
class NearestToEvenTest_356 : public ::testing::Test {
protected:
    NearestToEven policy;
};

// Test that normal_interval returns symmetric_boundary with include_left_endpoint = true
// when significand bits are even
TEST_F(NearestToEvenTest_356, NormalIntervalEvenSignificandReturnsTrue_356) {
    EvenSignificandBits even_bits;
    auto result = NearestToEven::normal_interval(even_bits);
    // When significand bits are even, the boundary should include the endpoint
    EXPECT_TRUE(result.is_closed);
}

// Test that normal_interval returns symmetric_boundary with include_left_endpoint = false
// when significand bits are odd
TEST_F(NearestToEvenTest_356, NormalIntervalOddSignificandReturnsFalse_356) {
    OddSignificandBits odd_bits;
    auto result = NearestToEven::normal_interval(odd_bits);
    // When significand bits are odd, the boundary should not include the endpoint
    EXPECT_FALSE(result.is_closed);
}

// Test that normal_interval is constexpr with even bits
TEST_F(NearestToEvenTest_356, NormalIntervalIsConstexprEven_356) {
    constexpr EvenSignificandBits even_bits{};
    constexpr auto result = NearestToEven::normal_interval(even_bits);
    EXPECT_TRUE(result.is_closed);
}

// Test that normal_interval is constexpr with odd bits
TEST_F(NearestToEvenTest_356, NormalIntervalIsConstexprOdd_356) {
    constexpr OddSignificandBits odd_bits{};
    constexpr auto result = NearestToEven::normal_interval(odd_bits);
    EXPECT_FALSE(result.is_closed);
}

// Test that normal_interval is noexcept
TEST_F(NearestToEvenTest_356, NormalIntervalIsNoexcept_356) {
    EvenSignificandBits even_bits;
    EXPECT_TRUE(noexcept(NearestToEven::normal_interval(even_bits)));
}

// Test shorter_interval returns closed interval
TEST_F(NearestToEvenTest_356, ShorterIntervalReturnsClosed_356) {
    EvenSignificandBits even_bits;
    auto result = NearestToEven::shorter_interval(even_bits);
    // shorter_interval should return a closed interval type
    // Both endpoints should be closed
    EXPECT_TRUE(result.include_left_endpoint);
    EXPECT_TRUE(result.include_right_endpoint);
}

// Test shorter_interval with odd bits still returns closed
TEST_F(NearestToEvenTest_356, ShorterIntervalOddBitsReturnsClosed_356) {
    OddSignificandBits odd_bits;
    auto result = NearestToEven::shorter_interval(odd_bits);
    EXPECT_TRUE(result.include_left_endpoint);
    EXPECT_TRUE(result.include_right_endpoint);
}

// Test shorter_interval is noexcept
TEST_F(NearestToEvenTest_356, ShorterIntervalIsNoexcept_356) {
    EvenSignificandBits even_bits;
    EXPECT_TRUE(noexcept(NearestToEven::shorter_interval(even_bits)));
}

// Test that the type is default constructible
TEST_F(NearestToEvenTest_356, IsDefaultConstructible_356) {
    EXPECT_TRUE(std::is_default_constructible<NearestToEven>::value);
}

} // anonymous namespace

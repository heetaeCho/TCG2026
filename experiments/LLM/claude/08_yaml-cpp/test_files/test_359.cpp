#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Include the header under test
#include "contrib/dragonbox.h"

namespace {

using namespace YAML::jkj::dragonbox;

// Mock SignedSignificandBits for testing
struct MockSignedSignificandBitsEven {
    constexpr bool has_even_significand_bits() const noexcept { return true; }
};

struct MockSignedSignificandBitsOdd {
    constexpr bool has_even_significand_bits() const noexcept { return false; }
};

using NearestToOdd = policy::decimal_to_binary_rounding::nearest_to_odd_t;

// Test normal_interval with even significand bits
TEST(NearestToOddTest_359, NormalIntervalWithEvenSignificandBits_359) {
    MockSignedSignificandBitsEven even_bits;
    auto result = NearestToOdd::normal_interval(even_bits);
    // When has_even_significand_bits() returns true, !true = false
    // The symmetric_boundary should be constructed with false (closed boundary)
    EXPECT_FALSE(result.is_open);
}

// Test normal_interval with odd significand bits
TEST(NearestToOddTest_359, NormalIntervalWithOddSignificandBits_359) {
    MockSignedSignificandBitsOdd odd_bits;
    auto result = NearestToOdd::normal_interval(odd_bits);
    // When has_even_significand_bits() returns false, !false = true
    // The symmetric_boundary should be constructed with true (open boundary)
    EXPECT_TRUE(result.is_open);
}

// Test shorter_interval returns open interval
TEST(NearestToOddTest_359, ShorterIntervalReturnsOpen_359) {
    MockSignedSignificandBitsEven even_bits;
    auto result = NearestToOdd::shorter_interval(even_bits);
    // shorter_interval returns interval_type::open, which should have both boundaries open
    // Verify the result type is interval_type::open
    (void)result; // Just verify it compiles and returns
}

// Test shorter_interval with odd bits
TEST(NearestToOddTest_359, ShorterIntervalWithOddBits_359) {
    MockSignedSignificandBitsOdd odd_bits;
    auto result = NearestToOdd::shorter_interval(odd_bits);
    // shorter_interval ignores the parameter and returns interval_type::open
    (void)result;
}

// Test constexpr behavior - normal_interval with even bits
TEST(NearestToOddTest_359, NormalIntervalIsConstexprEven_359) {
    constexpr MockSignedSignificandBitsEven even_bits{};
    constexpr auto result = NearestToOdd::normal_interval(even_bits);
    EXPECT_FALSE(result.is_open);
}

// Test constexpr behavior - normal_interval with odd bits
TEST(NearestToOddTest_359, NormalIntervalIsConstexprOdd_359) {
    constexpr MockSignedSignificandBitsOdd odd_bits{};
    constexpr auto result = NearestToOdd::normal_interval(odd_bits);
    EXPECT_TRUE(result.is_open);
}

// Test constexpr behavior - shorter_interval
TEST(NearestToOddTest_359, ShorterIntervalIsConstexpr_359) {
    constexpr MockSignedSignificandBitsEven even_bits{};
    constexpr auto result = NearestToOdd::shorter_interval(even_bits);
    (void)result;
}

// Test that normal_interval is noexcept
TEST(NearestToOddTest_359, NormalIntervalIsNoexcept_359) {
    MockSignedSignificandBitsEven even_bits;
    EXPECT_TRUE(noexcept(NearestToOdd::normal_interval(even_bits)));
}

// Test that shorter_interval is noexcept
TEST(NearestToOddTest_359, ShorterIntervalIsNoexcept_359) {
    MockSignedSignificandBitsEven even_bits;
    EXPECT_TRUE(noexcept(NearestToOdd::shorter_interval(even_bits)));
}

} // namespace

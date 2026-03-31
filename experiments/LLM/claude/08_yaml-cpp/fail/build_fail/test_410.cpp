#include <gtest/gtest.h>
#include "contrib/dragonbox.h"

// We need to use the actual FormatTraits types from the dragonbox implementation.
// Typically these are ieee754_binary32 and ieee754_binary64.

namespace {

using namespace YAML::jkj::dragonbox;

// Type aliases for the impl specializations
using impl_float = detail::impl<detail::ieee754_binary_traits<detail::ieee754_binary32, uint32_t>>;
using impl_double = detail::impl<detail::ieee754_binary_traits<detail::ieee754_binary64, uint64_t>>;

// ============================================================
// Tests for float (binary32) format
// ============================================================

class ImplFloatIsLeftEndpointIntegerShorterIntervalTest_410 : public ::testing::Test {};

TEST_F(ImplFloatIsLeftEndpointIntegerShorterIntervalTest_410, AtLowerThresholdReturnsTrue_410) {
    // The lower threshold for float's shorter interval left endpoint check.
    // For binary32, the significand bits = 23, so thresholds are derived from that.
    // We test at the boundary: exponent = 2 (typical lower threshold for float)
    // Since we treat this as black box, we probe known values.
    // binary32: lower threshold is 2, upper threshold is 3
    constexpr bool result = impl_float::is_left_endpoint_integer_shorter_interval(2);
    EXPECT_TRUE(result);
}

TEST_F(ImplFloatIsLeftEndpointIntegerShorterIntervalTest_410, AtUpperThresholdReturnsTrue_410) {
    constexpr bool result = impl_float::is_left_endpoint_integer_shorter_interval(3);
    EXPECT_TRUE(result);
}

TEST_F(ImplFloatIsLeftEndpointIntegerShorterIntervalTest_410, BelowLowerThresholdReturnsFalse_410) {
    constexpr bool result = impl_float::is_left_endpoint_integer_shorter_interval(1);
    EXPECT_FALSE(result);
}

TEST_F(ImplFloatIsLeftEndpointIntegerShorterIntervalTest_410, AboveUpperThresholdReturnsFalse_410) {
    constexpr bool result = impl_float::is_left_endpoint_integer_shorter_interval(4);
    EXPECT_FALSE(result);
}

TEST_F(ImplFloatIsLeftEndpointIntegerShorterIntervalTest_410, NegativeExponentReturnsFalse_410) {
    constexpr bool result = impl_float::is_left_endpoint_integer_shorter_interval(-1);
    EXPECT_FALSE(result);
}

TEST_F(ImplFloatIsLeftEndpointIntegerShorterIntervalTest_410, ZeroExponentReturnsFalse_410) {
    constexpr bool result = impl_float::is_left_endpoint_integer_shorter_interval(0);
    EXPECT_FALSE(result);
}

TEST_F(ImplFloatIsLeftEndpointIntegerShorterIntervalTest_410, LargePositiveExponentReturnsFalse_410) {
    constexpr bool result = impl_float::is_left_endpoint_integer_shorter_interval(100);
    EXPECT_FALSE(result);
}

TEST_F(ImplFloatIsLeftEndpointIntegerShorterIntervalTest_410, LargeNegativeExponentReturnsFalse_410) {
    constexpr bool result = impl_float::is_left_endpoint_integer_shorter_interval(-100);
    EXPECT_FALSE(result);
}

// ============================================================
// Tests for double (binary64) format
// ============================================================

class ImplDoubleIsLeftEndpointIntegerShorterIntervalTest_410 : public ::testing::Test {};

TEST_F(ImplDoubleIsLeftEndpointIntegerShorterIntervalTest_410, AtLowerThresholdReturnsTrue_410) {
    // For binary64 (double), the lower threshold is 2
    constexpr bool result = impl_double::is_left_endpoint_integer_shorter_interval(2);
    EXPECT_TRUE(result);
}

TEST_F(ImplDoubleIsLeftEndpointIntegerShorterIntervalTest_410, AtUpperThresholdReturnsTrue_410) {
    // For binary64, upper threshold is 3
    constexpr bool result = impl_double::is_left_endpoint_integer_shorter_interval(3);
    EXPECT_TRUE(result);
}

TEST_F(ImplDoubleIsLeftEndpointIntegerShorterIntervalTest_410, BelowLowerThresholdReturnsFalse_410) {
    constexpr bool result = impl_double::is_left_endpoint_integer_shorter_interval(1);
    EXPECT_FALSE(result);
}

TEST_F(ImplDoubleIsLeftEndpointIntegerShorterIntervalTest_410, AboveUpperThresholdReturnsFalse_410) {
    constexpr bool result = impl_double::is_left_endpoint_integer_shorter_interval(4);
    EXPECT_FALSE(result);
}

TEST_F(ImplDoubleIsLeftEndpointIntegerShorterIntervalTest_410, NegativeExponentReturnsFalse_410) {
    constexpr bool result = impl_double::is_left_endpoint_integer_shorter_interval(-5);
    EXPECT_FALSE(result);
}

TEST_F(ImplDoubleIsLeftEndpointIntegerShorterIntervalTest_410, ZeroExponentReturnsFalse_410) {
    constexpr bool result = impl_double::is_left_endpoint_integer_shorter_interval(0);
    EXPECT_FALSE(result);
}

TEST_F(ImplDoubleIsLeftEndpointIntegerShorterIntervalTest_410, LargePositiveExponentReturnsFalse_410) {
    constexpr bool result = impl_double::is_left_endpoint_integer_shorter_interval(500);
    EXPECT_FALSE(result);
}

TEST_F(ImplDoubleIsLeftEndpointIntegerShorterIntervalTest_410, LargeNegativeExponentReturnsFalse_410) {
    constexpr bool result = impl_double::is_left_endpoint_integer_shorter_interval(-500);
    EXPECT_FALSE(result);
}

// ============================================================
// Constexpr verification tests
// ============================================================

TEST(ImplConstexprTest_410, IsLeftEndpointIsConstexprFloat_410) {
    // Verify the function is usable in constexpr context
    static_assert(impl_float::is_left_endpoint_integer_shorter_interval(2) == true ||
                  impl_float::is_left_endpoint_integer_shorter_interval(2) == false,
                  "Function must be constexpr");
    SUCCEED();
}

TEST(ImplConstexprTest_410, IsLeftEndpointIsConstexprDouble_410) {
    static_assert(impl_double::is_left_endpoint_integer_shorter_interval(2) == true ||
                  impl_double::is_left_endpoint_integer_shorter_interval(2) == false,
                  "Function must be constexpr");
    SUCCEED();
}

} // anonymous namespace

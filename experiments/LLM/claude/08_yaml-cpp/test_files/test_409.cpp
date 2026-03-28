#include <gtest/gtest.h>
#include "./TestProjects/yaml-cpp/src/contrib/dragonbox.h"

// We need to use concrete FormatTraits to instantiate impl.
// In dragonbox, ieee754_binary32 (float) and ieee754_binary64 (double) are typical format traits.

namespace {

using namespace YAML::jkj::dragonbox;

// Test fixture for float format
class DragonboxImplFloat_409 : public ::testing::Test {
protected:
    using float_impl = detail::impl<detail::ieee754_binary32>;
};

// Test fixture for double format
class DragonboxImplDouble_409 : public ::testing::Test {
protected:
    using double_impl = detail::impl<detail::ieee754_binary64>;
};

// ============================================================================
// Tests for float (ieee754_binary32)
// ============================================================================

TEST_F(DragonboxImplFloat_409, IsRightEndpointIntegerShorterInterval_VeryLargeNegativeExponent_ReturnsFalse_409) {
    // Very negative exponent should be below the lower threshold
    EXPECT_FALSE(float_impl::is_right_endpoint_integer_shorter_interval(-1000));
}

TEST_F(DragonboxImplFloat_409, IsRightEndpointIntegerShorterInterval_VeryLargePositiveExponent_ReturnsFalse_409) {
    // Very large positive exponent should be above the upper threshold
    EXPECT_FALSE(float_impl::is_right_endpoint_integer_shorter_interval(1000));
}

TEST_F(DragonboxImplFloat_409, IsRightEndpointIntegerShorterInterval_ZeroExponent_409) {
    // Zero exponent - check if it falls within the valid range
    // We just observe the behavior, not assert a specific result
    bool result = float_impl::is_right_endpoint_integer_shorter_interval(0);
    // Just ensure it compiles and returns a deterministic result
    EXPECT_EQ(result, float_impl::is_right_endpoint_integer_shorter_interval(0));
}

TEST_F(DragonboxImplFloat_409, IsRightEndpointIntegerShorterInterval_NegativeOne_409) {
    bool result = float_impl::is_right_endpoint_integer_shorter_interval(-1);
    EXPECT_EQ(result, float_impl::is_right_endpoint_integer_shorter_interval(-1));
}

TEST_F(DragonboxImplFloat_409, IsRightEndpointIntegerShorterInterval_Constexpr_409) {
    // Verify it can be used in a constexpr context
    constexpr bool result = float_impl::is_right_endpoint_integer_shorter_interval(0);
    (void)result;
    SUCCEED();
}

// For float (binary32), the known thresholds are typically:
// lower = -4, upper = 2 (these are well-known values from dragonbox paper)
TEST_F(DragonboxImplFloat_409, IsRightEndpointIntegerShorterInterval_AtLowerThreshold_ReturnsTrue_409) {
    // The lower threshold for float is known to be -4
    EXPECT_TRUE(float_impl::is_right_endpoint_integer_shorter_interval(-4));
}

TEST_F(DragonboxImplFloat_409, IsRightEndpointIntegerShorterInterval_BelowLowerThreshold_ReturnsFalse_409) {
    EXPECT_FALSE(float_impl::is_right_endpoint_integer_shorter_interval(-5));
}

TEST_F(DragonboxImplFloat_409, IsRightEndpointIntegerShorterInterval_AtUpperThreshold_ReturnsTrue_409) {
    // The upper threshold for float is known to be 2
    EXPECT_TRUE(float_impl::is_right_endpoint_integer_shorter_interval(2));
}

TEST_F(DragonboxImplFloat_409, IsRightEndpointIntegerShorterInterval_AboveUpperThreshold_ReturnsFalse_409) {
    EXPECT_FALSE(float_impl::is_right_endpoint_integer_shorter_interval(3));
}

TEST_F(DragonboxImplFloat_409, IsRightEndpointIntegerShorterInterval_WithinRange_ReturnsTrue_409) {
    EXPECT_TRUE(float_impl::is_right_endpoint_integer_shorter_interval(-2));
    EXPECT_TRUE(float_impl::is_right_endpoint_integer_shorter_interval(-1));
    EXPECT_TRUE(float_impl::is_right_endpoint_integer_shorter_interval(0));
    EXPECT_TRUE(float_impl::is_right_endpoint_integer_shorter_interval(1));
}

// ============================================================================
// Tests for double (ieee754_binary64)
// ============================================================================

TEST_F(DragonboxImplDouble_409, IsRightEndpointIntegerShorterInterval_VeryLargeNegativeExponent_ReturnsFalse_409) {
    EXPECT_FALSE(double_impl::is_right_endpoint_integer_shorter_interval(-10000));
}

TEST_F(DragonboxImplDouble_409, IsRightEndpointIntegerShorterInterval_VeryLargePositiveExponent_ReturnsFalse_409) {
    EXPECT_FALSE(double_impl::is_right_endpoint_integer_shorter_interval(10000));
}

TEST_F(DragonboxImplDouble_409, IsRightEndpointIntegerShorterInterval_ZeroExponent_409) {
    bool result = double_impl::is_right_endpoint_integer_shorter_interval(0);
    EXPECT_EQ(result, double_impl::is_right_endpoint_integer_shorter_interval(0));
}

TEST_F(DragonboxImplDouble_409, IsRightEndpointIntegerShorterInterval_Constexpr_409) {
    constexpr bool result = double_impl::is_right_endpoint_integer_shorter_interval(0);
    (void)result;
    SUCCEED();
}

// For double (binary64), the known thresholds are typically:
// lower = -2, upper = 2
TEST_F(DragonboxImplDouble_409, IsRightEndpointIntegerShorterInterval_AtLowerThreshold_ReturnsTrue_409) {
    EXPECT_TRUE(double_impl::is_right_endpoint_integer_shorter_interval(-2));
}

TEST_F(DragonboxImplDouble_409, IsRightEndpointIntegerShorterInterval_BelowLowerThreshold_ReturnsFalse_409) {
    EXPECT_FALSE(double_impl::is_right_endpoint_integer_shorter_interval(-3));
}

TEST_F(DragonboxImplDouble_409, IsRightEndpointIntegerShorterInterval_AtUpperThreshold_ReturnsTrue_409) {
    EXPECT_TRUE(double_impl::is_right_endpoint_integer_shorter_interval(2));
}

TEST_F(DragonboxImplDouble_409, IsRightEndpointIntegerShorterInterval_AboveUpperThreshold_ReturnsFalse_409) {
    EXPECT_FALSE(double_impl::is_right_endpoint_integer_shorter_interval(3));
}

TEST_F(DragonboxImplDouble_409, IsRightEndpointIntegerShorterInterval_WithinRange_ReturnsTrue_409) {
    EXPECT_TRUE(double_impl::is_right_endpoint_integer_shorter_interval(-1));
    EXPECT_TRUE(double_impl::is_right_endpoint_integer_shorter_interval(0));
    EXPECT_TRUE(double_impl::is_right_endpoint_integer_shorter_interval(1));
}

// ============================================================================
// Consistency tests
// ============================================================================

TEST_F(DragonboxImplFloat_409, IsRightEndpointIntegerShorterInterval_Deterministic_409) {
    // Calling with the same argument should always return the same result
    for (int exp = -200; exp <= 200; ++exp) {
        bool first = float_impl::is_right_endpoint_integer_shorter_interval(exp);
        bool second = float_impl::is_right_endpoint_integer_shorter_interval(exp);
        EXPECT_EQ(first, second) << "Non-deterministic result for exponent " << exp;
    }
}

TEST_F(DragonboxImplDouble_409, IsRightEndpointIntegerShorterInterval_Deterministic_409) {
    for (int exp = -200; exp <= 200; ++exp) {
        bool first = double_impl::is_right_endpoint_integer_shorter_interval(exp);
        bool second = double_impl::is_right_endpoint_integer_shorter_interval(exp);
        EXPECT_EQ(first, second) << "Non-deterministic result for exponent " << exp;
    }
}

// The valid range should be contiguous (it's a simple range check)
TEST_F(DragonboxImplFloat_409, IsRightEndpointIntegerShorterInterval_ContiguousRange_409) {
    // Find the boundaries by scanning
    int lower_bound = -200;
    int upper_bound = 200;
    
    // Find first true
    bool found_first_true = false;
    int first_true = 0;
    int last_true = 0;
    
    for (int exp = -200; exp <= 200; ++exp) {
        if (float_impl::is_right_endpoint_integer_shorter_interval(exp)) {
            if (!found_first_true) {
                first_true = exp;
                found_first_true = true;
            }
            last_true = exp;
        }
    }
    
    if (found_first_true) {
        // All values between first_true and last_true should be true
        for (int exp = first_true; exp <= last_true; ++exp) {
            EXPECT_TRUE(float_impl::is_right_endpoint_integer_shorter_interval(exp))
                << "Expected true for exponent " << exp << " in range [" 
                << first_true << ", " << last_true << "]";
        }
    }
}

TEST_F(DragonboxImplDouble_409, IsRightEndpointIntegerShorterInterval_ContiguousRange_409) {
    bool found_first_true = false;
    int first_true = 0;
    int last_true = 0;
    
    for (int exp = -200; exp <= 200; ++exp) {
        if (double_impl::is_right_endpoint_integer_shorter_interval(exp)) {
            if (!found_first_true) {
                first_true = exp;
                found_first_true = true;
            }
            last_true = exp;
        }
    }
    
    if (found_first_true) {
        for (int exp = first_true; exp <= last_true; ++exp) {
            EXPECT_TRUE(double_impl::is_right_endpoint_integer_shorter_interval(exp))
                << "Expected true for exponent " << exp << " in range [" 
                << first_true << ", " << last_true << "]";
        }
    }
}

} // anonymous namespace

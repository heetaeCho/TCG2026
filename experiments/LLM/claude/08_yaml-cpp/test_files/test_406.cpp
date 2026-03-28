#include <gtest/gtest.h>
#include <cstdint>
#include <cstring>
#include <cmath>
#include <limits>

// Include the dragonbox header
#include "contrib/dragonbox.h"

using namespace YAML::jkj::dragonbox;

// Helper to get the IEEE754 bit representation
static uint32_t float_to_bits(float f) {
    uint32_t bits;
    std::memcpy(&bits, &f, sizeof(bits));
    return bits;
}

static uint64_t double_to_bits(double d) {
    uint64_t bits;
    std::memcpy(&bits, &d, sizeof(bits));
    return bits;
}

// Type aliases for convenience
using float_format_traits = detail::float_format_traits;
using double_format_traits = detail::double_format_traits;
using float_impl = detail::impl<float_format_traits>;
using double_impl = detail::impl<double_format_traits>;

// Policy types
using sign_policy = policy::sign::return_sign_t;
using trailing_zero_policy = policy::trailing_zero::remove_t;
using interval_type_provider = policy::decimal_to_binary_rounding::nearest_to_even_t;
using binary_to_decimal_rounding = policy::binary_to_decimal_rounding::to_even_t;
using cache_policy = policy::cache::full_t;
using preferred_integer_types = policy::preferred_integer_types::default_t;

// Helper to extract sign, significand, and exponent from float bits
struct FloatComponents {
    bool sign;
    int exponent_bits;
    uint32_t significand_bits;
};

static FloatComponents decompose_float(float f) {
    uint32_t bits = float_to_bits(f);
    FloatComponents c;
    c.sign = (bits >> 31) != 0;
    c.exponent_bits = (bits >> 23) & 0xFF;
    c.significand_bits = bits & 0x7FFFFF;
    return c;
}

struct DoubleComponents {
    bool sign;
    int exponent_bits;
    uint64_t significand_bits;
};

static DoubleComponents decompose_double(double d) {
    uint64_t bits = double_to_bits(d);
    DoubleComponents c;
    c.sign = (bits >> 63) != 0;
    c.exponent_bits = (bits >> 52) & 0x7FF;
    c.significand_bits = bits & 0x000FFFFFFFFFFFFFULL;
    return c;
}

// We test through the top-level to_decimal function which calls compute_nearest
class DragonboxFloat32Test_406 : public ::testing::Test {
protected:
    // Use the top-level conversion function
    auto convert(float f) {
        return to_decimal(f,
            policy::sign::return_sign,
            policy::trailing_zero::remove,
            policy::decimal_to_binary_rounding::nearest_to_even,
            policy::binary_to_decimal_rounding::to_even,
            policy::cache::full,
            policy::preferred_integer_types::default_);
    }
};

class DragonboxFloat64Test_406 : public ::testing::Test {
protected:
    auto convert(double d) {
        return to_decimal(d,
            policy::sign::return_sign,
            policy::trailing_zero::remove,
            policy::decimal_to_binary_rounding::nearest_to_even,
            policy::binary_to_decimal_rounding::to_even,
            policy::cache::full,
            policy::preferred_integer_types::default_);
    }
};

// ==================== Float32 Tests ====================

TEST_F(DragonboxFloat32Test_406, PositiveOne_406) {
    auto result = convert(1.0f);
    EXPECT_FALSE(result.is_negative);
    EXPECT_EQ(result.significand, 1u);
    EXPECT_EQ(result.exponent, 0);
}

TEST_F(DragonboxFloat32Test_406, NegativeOne_406) {
    auto result = convert(-1.0f);
    EXPECT_TRUE(result.is_negative);
    EXPECT_EQ(result.significand, 1u);
    EXPECT_EQ(result.exponent, 0);
}

TEST_F(DragonboxFloat32Test_406, PositiveZero_406) {
    auto result = convert(0.0f);
    EXPECT_FALSE(result.is_negative);
    EXPECT_EQ(result.significand, 0u);
    EXPECT_EQ(result.exponent, 0);
}

TEST_F(DragonboxFloat32Test_406, NegativeZero_406) {
    auto result = convert(-0.0f);
    EXPECT_TRUE(result.is_negative);
    EXPECT_EQ(result.significand, 0u);
    EXPECT_EQ(result.exponent, 0);
}

TEST_F(DragonboxFloat32Test_406, PointFive_406) {
    auto result = convert(0.5f);
    EXPECT_FALSE(result.is_negative);
    EXPECT_EQ(result.significand, 5u);
    EXPECT_EQ(result.exponent, -1);
}

TEST_F(DragonboxFloat32Test_406, Ten_406) {
    auto result = convert(10.0f);
    EXPECT_FALSE(result.is_negative);
    EXPECT_EQ(result.significand, 1u);
    EXPECT_EQ(result.exponent, 1);
}

TEST_F(DragonboxFloat32Test_406, Hundred_406) {
    auto result = convert(100.0f);
    EXPECT_FALSE(result.is_negative);
    EXPECT_EQ(result.significand, 1u);
    EXPECT_EQ(result.exponent, 2);
}

TEST_F(DragonboxFloat32Test_406, SmallFloat_406) {
    auto result = convert(1.5f);
    EXPECT_FALSE(result.is_negative);
    EXPECT_EQ(result.significand, 15u);
    EXPECT_EQ(result.exponent, -1);
}

TEST_F(DragonboxFloat32Test_406, LargeFloat_406) {
    auto result = convert(1.0e10f);
    EXPECT_FALSE(result.is_negative);
    EXPECT_EQ(result.significand, 1u);
    EXPECT_EQ(result.exponent, 10);
}

TEST_F(DragonboxFloat32Test_406, SmallPositiveFloat_406) {
    auto result = convert(1.0e-10f);
    EXPECT_FALSE(result.is_negative);
    // Just verify significand > 0 and exponent is negative
    EXPECT_GT(result.significand, 0u);
    EXPECT_LT(result.exponent, 0);
}

TEST_F(DragonboxFloat32Test_406, FloatMinNormal_406) {
    float min_normal = std::numeric_limits<float>::min();
    auto result = convert(min_normal);
    EXPECT_FALSE(result.is_negative);
    EXPECT_GT(result.significand, 0u);
}

TEST_F(DragonboxFloat32Test_406, FloatMaxValue_406) {
    float max_val = std::numeric_limits<float>::max();
    auto result = convert(max_val);
    EXPECT_FALSE(result.is_negative);
    EXPECT_GT(result.significand, 0u);
}

TEST_F(DragonboxFloat32Test_406, FloatMinDenorm_406) {
    float min_denorm = std::numeric_limits<float>::denorm_min();
    auto result = convert(min_denorm);
    EXPECT_FALSE(result.is_negative);
    EXPECT_GT(result.significand, 0u);
}

TEST_F(DragonboxFloat32Test_406, NegativeFloat_406) {
    auto result = convert(-3.14f);
    EXPECT_TRUE(result.is_negative);
    EXPECT_GT(result.significand, 0u);
}

TEST_F(DragonboxFloat32Test_406, FloatTwoPointFive_406) {
    auto result = convert(2.5f);
    EXPECT_FALSE(result.is_negative);
    EXPECT_EQ(result.significand, 25u);
    EXPECT_EQ(result.exponent, -1);
}

TEST_F(DragonboxFloat32Test_406, FloatThousand_406) {
    auto result = convert(1000.0f);
    EXPECT_FALSE(result.is_negative);
    EXPECT_EQ(result.significand, 1u);
    EXPECT_EQ(result.exponent, 3);
}

TEST_F(DragonboxFloat32Test_406, FloatPointOne_406) {
    auto result = convert(0.1f);
    EXPECT_FALSE(result.is_negative);
    EXPECT_EQ(result.significand, 1u);
    EXPECT_EQ(result.exponent, -1);
}

TEST_F(DragonboxFloat32Test_406, FloatPointThree_406) {
    auto result = convert(0.3f);
    EXPECT_FALSE(result.is_negative);
    EXPECT_EQ(result.significand, 3u);
    EXPECT_EQ(result.exponent, -1);
}

TEST_F(DragonboxFloat32Test_406, FloatSevenPointFive_406) {
    auto result = convert(7.5f);
    EXPECT_FALSE(result.is_negative);
    EXPECT_EQ(result.significand, 75u);
    EXPECT_EQ(result.exponent, -1);
}

TEST_F(DragonboxFloat32Test_406, FloatRoundTripConsistency_406) {
    // The significand * 10^exponent should reconstruct the original value
    float original = 123.456f;
    auto result = convert(original);
    EXPECT_FALSE(result.is_negative);
    double reconstructed = result.significand * std::pow(10.0, result.exponent);
    EXPECT_FLOAT_EQ(original, static_cast<float>(reconstructed));
}

// ==================== Float64 Tests ====================

TEST_F(DragonboxFloat64Test_406, PositiveOne_406) {
    auto result = convert(1.0);
    EXPECT_FALSE(result.is_negative);
    EXPECT_EQ(result.significand, 1u);
    EXPECT_EQ(result.exponent, 0);
}

TEST_F(DragonboxFloat64Test_406, NegativeOne_406) {
    auto result = convert(-1.0);
    EXPECT_TRUE(result.is_negative);
    EXPECT_EQ(result.significand, 1u);
    EXPECT_EQ(result.exponent, 0);
}

TEST_F(DragonboxFloat64Test_406, PositiveZero_406) {
    auto result = convert(0.0);
    EXPECT_FALSE(result.is_negative);
    EXPECT_EQ(result.significand, 0u);
    EXPECT_EQ(result.exponent, 0);
}

TEST_F(DragonboxFloat64Test_406, NegativeZero_406) {
    auto result = convert(-0.0);
    EXPECT_TRUE(result.is_negative);
    EXPECT_EQ(result.significand, 0u);
    EXPECT_EQ(result.exponent, 0);
}

TEST_F(DragonboxFloat64Test_406, PointFive_406) {
    auto result = convert(0.5);
    EXPECT_FALSE(result.is_negative);
    EXPECT_EQ(result.significand, 5u);
    EXPECT_EQ(result.exponent, -1);
}

TEST_F(DragonboxFloat64Test_406, Ten_406) {
    auto result = convert(10.0);
    EXPECT_FALSE(result.is_negative);
    EXPECT_EQ(result.significand, 1u);
    EXPECT_EQ(result.exponent, 1);
}

TEST_F(DragonboxFloat64Test_406, Hundred_406) {
    auto result = convert(100.0);
    EXPECT_FALSE(result.is_negative);
    EXPECT_EQ(result.significand, 1u);
    EXPECT_EQ(result.exponent, 2);
}

TEST_F(DragonboxFloat64Test_406, DoubleMinNormal_406) {
    double min_normal = std::numeric_limits<double>::min();
    auto result = convert(min_normal);
    EXPECT_FALSE(result.is_negative);
    EXPECT_GT(result.significand, 0u);
}

TEST_F(DragonboxFloat64Test_406, DoubleMaxValue_406) {
    double max_val = std::numeric_limits<double>::max();
    auto result = convert(max_val);
    EXPECT_FALSE(result.is_negative);
    EXPECT_GT(result.significand, 0u);
}

TEST_F(DragonboxFloat64Test_406, DoubleMinDenorm_406) {
    double min_denorm = std::numeric_limits<double>::denorm_min();
    auto result = convert(min_denorm);
    EXPECT_FALSE(result.is_negative);
    EXPECT_GT(result.significand, 0u);
}

TEST_F(DragonboxFloat64Test_406, NegativeDouble_406) {
    auto result = convert(-3.14);
    EXPECT_TRUE(result.is_negative);
    EXPECT_GT(result.significand, 0u);
}

TEST_F(DragonboxFloat64Test_406, DoubleLargeValue_406) {
    auto result = convert(1.0e100);
    EXPECT_FALSE(result.is_negative);
    EXPECT_EQ(result.significand, 1u);
    EXPECT_EQ(result.exponent, 100);
}

TEST_F(DragonboxFloat64Test_406, DoubleSmallValue_406) {
    auto result = convert(1.0e-100);
    EXPECT_FALSE(result.is_negative);
    EXPECT_EQ(result.significand, 1u);
    EXPECT_EQ(result.exponent, -100);
}

TEST_F(DragonboxFloat64Test_406, DoublePointOne_406) {
    auto result = convert(0.1);
    EXPECT_FALSE(result.is_negative);
    EXPECT_EQ(result.significand, 1u);
    EXPECT_EQ(result.exponent, -1);
}

TEST_F(DragonboxFloat64Test_406, DoublePointThree_406) {
    auto result = convert(0.3);
    EXPECT_FALSE(result.is_negative);
    EXPECT_EQ(result.significand, 3u);
    EXPECT_EQ(result.exponent, -1);
}

TEST_F(DragonboxFloat64Test_406, DoublePi_406) {
    auto result = convert(3.141592653589793);
    EXPECT_FALSE(result.is_negative);
    EXPECT_GT(result.significand, 0u);
}

TEST_F(DragonboxFloat64Test_406, DoubleRoundTripConsistency_406) {
    double original = 123456.789012345;
    auto result = convert(original);
    EXPECT_FALSE(result.is_negative);
    double reconstructed = result.significand * std::pow(10.0, result.exponent);
    EXPECT_DOUBLE_EQ(original, reconstructed);
}

TEST_F(DragonboxFloat64Test_406, DoubleVerySmallDenorm_406) {
    // A very small denormalized double
    double tiny = 5e-324;
    auto result = convert(tiny);
    EXPECT_FALSE(result.is_negative);
    EXPECT_GT(result.significand, 0u);
}

TEST_F(DragonboxFloat64Test_406, DoubleNegativeLarge_406) {
    auto result = convert(-1.0e300);
    EXPECT_TRUE(result.is_negative);
    EXPECT_EQ(result.significand, 1u);
    EXPECT_EQ(result.exponent, 300);
}

TEST_F(DragonboxFloat64Test_406, DoubleTwoPointFive_406) {
    auto result = convert(2.5);
    EXPECT_FALSE(result.is_negative);
    EXPECT_EQ(result.significand, 25u);
    EXPECT_EQ(result.exponent, -1);
}

TEST_F(DragonboxFloat64Test_406, DoubleThousand_406) {
    auto result = convert(1000.0);
    EXPECT_FALSE(result.is_negative);
    EXPECT_EQ(result.significand, 1u);
    EXPECT_EQ(result.exponent, 3);
}

// ==================== Static Helper Tests ====================

class DragonboxImplHelperTest_406 : public ::testing::Test {};

TEST_F(DragonboxImplHelperTest_406, MinFunction_406) {
    EXPECT_EQ(float_impl::min(3, 5), 3);
    EXPECT_EQ(float_impl::min(5, 3), 3);
    EXPECT_EQ(float_impl::min(3, 3), 3);
    EXPECT_EQ(float_impl::min(-1, 1), -1);
    EXPECT_EQ(float_impl::min(0, 0), 0);
}

TEST_F(DragonboxImplHelperTest_406, MaxFunction_406) {
    EXPECT_EQ(float_impl::max(3, 5), 5);
    EXPECT_EQ(float_impl::max(5, 3), 5);
    EXPECT_EQ(float_impl::max(3, 3), 3);
    EXPECT_EQ(float_impl::max(-1, 1), 1);
    EXPECT_EQ(float_impl::max(0, 0), 0);
}

TEST_F(DragonboxImplHelperTest_406, IsRightEndpointIntegerShorterInterval_406) {
    // Just test that the function is callable and returns a bool
    bool result_float = float_impl::is_right_endpoint_integer_shorter_interval(2);
    (void)result_float; // suppress unused warning
    bool result_double = double_impl::is_right_endpoint_integer_shorter_interval(2);
    (void)result_double;
}

TEST_F(DragonboxImplHelperTest_406, IsLeftEndpointIntegerShorterInterval_406) {
    bool result_float = float_impl::is_left_endpoint_integer_shorter_interval(2);
    (void)result_float;
    bool result_double = double_impl::is_left_endpoint_integer_shorter_interval(2);
    (void)result_double;
}

// ==================== Subnormal boundary tests ====================

TEST_F(DragonboxFloat32Test_406, SmallestSubnormal_406) {
    // Smallest positive subnormal float
    uint32_t bits = 1;
    float f;
    std::memcpy(&f, &bits, sizeof(f));
    auto result = convert(f);
    EXPECT_FALSE(result.is_negative);
    EXPECT_GT(result.significand, 0u);
}

TEST_F(DragonboxFloat32Test_406, LargestSubnormal_406) {
    // Largest positive subnormal float: exponent = 0, significand = all 1s
    uint32_t bits = 0x007FFFFF;
    float f;
    std::memcpy(&f, &bits, sizeof(f));
    auto result = convert(f);
    EXPECT_FALSE(result.is_negative);
    EXPECT_GT(result.significand, 0u);
}

TEST_F(DragonboxFloat32Test_406, SmallestNormal_406) {
    // Smallest positive normal float: exponent = 1, significand = 0
    uint32_t bits = 0x00800000;
    float f;
    std::memcpy(&f, &bits, sizeof(f));
    auto result = convert(f);
    EXPECT_FALSE(result.is_negative);
    EXPECT_GT(result.significand, 0u);
}

TEST_F(DragonboxFloat64Test_406, SmallestSubnormal_406) {
    uint64_t bits = 1;
    double d;
    std::memcpy(&d, &bits, sizeof(d));
    auto result = convert(d);
    EXPECT_FALSE(result.is_negative);
    EXPECT_GT(result.significand, 0u);
}

TEST_F(DragonboxFloat64Test_406, LargestSubnormal_406) {
    uint64_t bits = 0x000FFFFFFFFFFFFFULL;
    double d;
    std::memcpy(&d, &bits, sizeof(d));
    auto result = convert(d);
    EXPECT_FALSE(result.is_negative);
    EXPECT_GT(result.significand, 0u);
}

TEST_F(DragonboxFloat64Test_406, SmallestNormal_406) {
    uint64_t bits = 0x0010000000000000ULL;
    double d;
    std::memcpy(&d, &bits, sizeof(d));
    auto result = convert(d);
    EXPECT_FALSE(result.is_negative);
    EXPECT_GT(result.significand, 0u);
}

// ==================== Power-of-two boundary tests ====================

TEST_F(DragonboxFloat32Test_406, PowerOfTwo_Two_406) {
    auto result = convert(2.0f);
    EXPECT_FALSE(result.is_negative);
    EXPECT_EQ(result.significand, 2u);
    EXPECT_EQ(result.exponent, 0);
}

TEST_F(DragonboxFloat32Test_406, PowerOfTwo_Four_406) {
    auto result = convert(4.0f);
    EXPECT_FALSE(result.is_negative);
    EXPECT_EQ(result.significand, 4u);
    EXPECT_EQ(result.exponent, 0);
}

TEST_F(DragonboxFloat32Test_406, PowerOfTwo_Eight_406) {
    auto result = convert(8.0f);
    EXPECT_FALSE(result.is_negative);
    EXPECT_EQ(result.significand, 8u);
    EXPECT_EQ(result.exponent, 0);
}

TEST_F(DragonboxFloat64Test_406, PowerOfTwo_Two_406) {
    auto result = convert(2.0);
    EXPECT_FALSE(result.is_negative);
    EXPECT_EQ(result.significand, 2u);
    EXPECT_EQ(result.exponent, 0);
}

TEST_F(DragonboxFloat64Test_406, PowerOfTwo_1024_406) {
    auto result = convert(1024.0);
    EXPECT_FALSE(result.is_negative);
    EXPECT_EQ(result.significand, 1024u);
    EXPECT_EQ(result.exponent, 0);
}

// ==================== Trailing zeros tests ====================

TEST_F(DragonboxFloat32Test_406, ValueWithTrailingZeros_406) {
    // 1.0e5 = 100000 => significand=1, exponent=5
    auto result = convert(1.0e5f);
    EXPECT_FALSE(result.is_negative);
    EXPECT_EQ(result.significand, 1u);
    EXPECT_EQ(result.exponent, 5);
}

TEST_F(DragonboxFloat64Test_406, ValueWithTrailingZeros_406) {
    auto result = convert(1.0e15);
    EXPECT_FALSE(result.is_negative);
    EXPECT_EQ(result.significand, 1u);
    EXPECT_EQ(result.exponent, 15);
}

// ==================== Sign consistency tests ====================

TEST_F(DragonboxFloat32Test_406, SignConsistencyPositive_406) {
    float values[] = {0.1f, 1.0f, 10.0f, 100.0f, 0.001f};
    for (float v : values) {
        auto result = convert(v);
        EXPECT_FALSE(result.is_negative) << "Failed for value: " << v;
    }
}

TEST_F(DragonboxFloat32Test_406, SignConsistencyNegative_406) {
    float values[] = {-0.1f, -1.0f, -10.0f, -100.0f, -0.001f};
    for (float v : values) {
        auto result = convert(v);
        EXPECT_TRUE(result.is_negative) << "Failed for value: " << v;
    }
}

TEST_F(DragonboxFloat64Test_406, SignConsistencyPositive_406) {
    double values[] = {0.1, 1.0, 10.0, 100.0, 0.001};
    for (double v : values) {
        auto result = convert(v);
        EXPECT_FALSE(result.is_negative) << "Failed for value: " << v;
    }
}

TEST_F(DragonboxFloat64Test_406, SignConsistencyNegative_406) {
    double values[] = {-0.1, -1.0, -10.0, -100.0, -0.001};
    for (double v : values) {
        auto result = convert(v);
        EXPECT_TRUE(result.is_negative) << "Failed for value: " << v;
    }
}

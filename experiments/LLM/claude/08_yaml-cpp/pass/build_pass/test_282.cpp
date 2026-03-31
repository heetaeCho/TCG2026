#include <gtest/gtest.h>
#include <cstdint>
#include <cmath>
#include <limits>

// Include the header under test
#include "contrib/dragonbox.h"

namespace {

// Test fixture for default_float_bit_carrier_conversion_traits<float>
class DefaultFloatBitCarrierConversionTraitsFloatTest_282 : public ::testing::Test {
protected:
    using Traits = YAML::jkj::dragonbox::default_float_bit_carrier_conversion_traits<float>;
};

// Test fixture for default_float_bit_carrier_conversion_traits<double>
class DefaultFloatBitCarrierConversionTraitsDoubleTest_282 : public ::testing::Test {
protected:
    using Traits = YAML::jkj::dragonbox::default_float_bit_carrier_conversion_traits<double>;
};

// ==================== Float (32-bit) Tests ====================

TEST_F(DefaultFloatBitCarrierConversionTraitsFloatTest_282, CarrierToFloatZero_282) {
    // IEEE 754: +0.0f has bit pattern 0x00000000
    float result = Traits::carrier_to_float(0x00000000u);
    EXPECT_EQ(result, 0.0f);
    EXPECT_FALSE(std::signbit(result));
}

TEST_F(DefaultFloatBitCarrierConversionTraitsFloatTest_282, CarrierToFloatNegativeZero_282) {
    // IEEE 754: -0.0f has bit pattern 0x80000000
    float result = Traits::carrier_to_float(0x80000000u);
    EXPECT_EQ(result, -0.0f);
    EXPECT_TRUE(std::signbit(result));
}

TEST_F(DefaultFloatBitCarrierConversionTraitsFloatTest_282, CarrierToFloatOne_282) {
    // IEEE 754: 1.0f has bit pattern 0x3F800000
    float result = Traits::carrier_to_float(0x3F800000u);
    EXPECT_EQ(result, 1.0f);
}

TEST_F(DefaultFloatBitCarrierConversionTraitsFloatTest_282, CarrierToFloatNegativeOne_282) {
    // IEEE 754: -1.0f has bit pattern 0xBF800000
    float result = Traits::carrier_to_float(0xBF800000u);
    EXPECT_EQ(result, -1.0f);
}

TEST_F(DefaultFloatBitCarrierConversionTraitsFloatTest_282, CarrierToFloatInfinity_282) {
    // IEEE 754: +infinity has bit pattern 0x7F800000
    float result = Traits::carrier_to_float(0x7F800000u);
    EXPECT_TRUE(std::isinf(result));
    EXPECT_GT(result, 0.0f);
}

TEST_F(DefaultFloatBitCarrierConversionTraitsFloatTest_282, CarrierToFloatNegativeInfinity_282) {
    // IEEE 754: -infinity has bit pattern 0xFF800000
    float result = Traits::carrier_to_float(0xFF800000u);
    EXPECT_TRUE(std::isinf(result));
    EXPECT_LT(result, 0.0f);
}

TEST_F(DefaultFloatBitCarrierConversionTraitsFloatTest_282, CarrierToFloatNaN_282) {
    // IEEE 754: A NaN has bit pattern 0x7FC00000 (quiet NaN)
    float result = Traits::carrier_to_float(0x7FC00000u);
    EXPECT_TRUE(std::isnan(result));
}

TEST_F(DefaultFloatBitCarrierConversionTraitsFloatTest_282, CarrierToFloatMaxFloat_282) {
    // IEEE 754: max float has bit pattern 0x7F7FFFFF
    float result = Traits::carrier_to_float(0x7F7FFFFFu);
    EXPECT_EQ(result, std::numeric_limits<float>::max());
}

TEST_F(DefaultFloatBitCarrierConversionTraitsFloatTest_282, CarrierToFloatMinPositiveNormal_282) {
    // IEEE 754: min positive normal float has bit pattern 0x00800000
    float result = Traits::carrier_to_float(0x00800000u);
    EXPECT_EQ(result, std::numeric_limits<float>::min());
}

TEST_F(DefaultFloatBitCarrierConversionTraitsFloatTest_282, CarrierToFloatSmallestDenormalized_282) {
    // IEEE 754: smallest denormalized float has bit pattern 0x00000001
    float result = Traits::carrier_to_float(0x00000001u);
    EXPECT_EQ(result, std::numeric_limits<float>::denorm_min());
}

TEST_F(DefaultFloatBitCarrierConversionTraitsFloatTest_282, FloatToCarrierZero_282) {
    auto result = Traits::float_to_carrier(0.0f);
    EXPECT_EQ(result, 0x00000000u);
}

TEST_F(DefaultFloatBitCarrierConversionTraitsFloatTest_282, FloatToCarrierNegativeZero_282) {
    auto result = Traits::float_to_carrier(-0.0f);
    EXPECT_EQ(result, 0x80000000u);
}

TEST_F(DefaultFloatBitCarrierConversionTraitsFloatTest_282, FloatToCarrierOne_282) {
    auto result = Traits::float_to_carrier(1.0f);
    EXPECT_EQ(result, 0x3F800000u);
}

TEST_F(DefaultFloatBitCarrierConversionTraitsFloatTest_282, FloatToCarrierNegativeOne_282) {
    auto result = Traits::float_to_carrier(-1.0f);
    EXPECT_EQ(result, 0xBF800000u);
}

TEST_F(DefaultFloatBitCarrierConversionTraitsFloatTest_282, FloatToCarrierInfinity_282) {
    auto result = Traits::float_to_carrier(std::numeric_limits<float>::infinity());
    EXPECT_EQ(result, 0x7F800000u);
}

TEST_F(DefaultFloatBitCarrierConversionTraitsFloatTest_282, FloatToCarrierNegativeInfinity_282) {
    auto result = Traits::float_to_carrier(-std::numeric_limits<float>::infinity());
    EXPECT_EQ(result, 0xFF800000u);
}

TEST_F(DefaultFloatBitCarrierConversionTraitsFloatTest_282, FloatToCarrierMaxFloat_282) {
    auto result = Traits::float_to_carrier(std::numeric_limits<float>::max());
    EXPECT_EQ(result, 0x7F7FFFFFu);
}

TEST_F(DefaultFloatBitCarrierConversionTraitsFloatTest_282, RoundTripFloatToCarrierAndBack_282) {
    float original = 3.14f;
    auto carrier = Traits::float_to_carrier(original);
    float round_tripped = Traits::carrier_to_float(carrier);
    EXPECT_EQ(original, round_tripped);
}

TEST_F(DefaultFloatBitCarrierConversionTraitsFloatTest_282, RoundTripCarrierToFloatAndBack_282) {
    uint32_t original = 0x40490FDBu; // approximately pi
    float f = Traits::carrier_to_float(original);
    auto round_tripped = Traits::float_to_carrier(f);
    EXPECT_EQ(original, round_tripped);
}

TEST_F(DefaultFloatBitCarrierConversionTraitsFloatTest_282, RoundTripMultipleValues_282) {
    float values[] = {0.0f, -0.0f, 1.0f, -1.0f, 0.5f, -0.5f, 
                      100.0f, -100.0f, 1e-30f, 1e30f,
                      std::numeric_limits<float>::min(),
                      std::numeric_limits<float>::max(),
                      std::numeric_limits<float>::denorm_min(),
                      std::numeric_limits<float>::epsilon()};
    for (float val : values) {
        auto carrier = Traits::float_to_carrier(val);
        float result = Traits::carrier_to_float(carrier);
        EXPECT_EQ(val, result) << "Round trip failed for value: " << val;
    }
}

// ==================== Double (64-bit) Tests ====================

TEST_F(DefaultFloatBitCarrierConversionTraitsDoubleTest_282, CarrierToDoubleZero_282) {
    // IEEE 754: +0.0 has bit pattern 0x0000000000000000
    double result = Traits::carrier_to_float(0x0000000000000000ull);
    EXPECT_EQ(result, 0.0);
    EXPECT_FALSE(std::signbit(result));
}

TEST_F(DefaultFloatBitCarrierConversionTraitsDoubleTest_282, CarrierToDoubleNegativeZero_282) {
    // IEEE 754: -0.0 has bit pattern 0x8000000000000000
    double result = Traits::carrier_to_float(0x8000000000000000ull);
    EXPECT_EQ(result, -0.0);
    EXPECT_TRUE(std::signbit(result));
}

TEST_F(DefaultFloatBitCarrierConversionTraitsDoubleTest_282, CarrierToDoubleOne_282) {
    // IEEE 754: 1.0 has bit pattern 0x3FF0000000000000
    double result = Traits::carrier_to_float(0x3FF0000000000000ull);
    EXPECT_EQ(result, 1.0);
}

TEST_F(DefaultFloatBitCarrierConversionTraitsDoubleTest_282, CarrierToDoubleNegativeOne_282) {
    double result = Traits::carrier_to_float(0xBFF0000000000000ull);
    EXPECT_EQ(result, -1.0);
}

TEST_F(DefaultFloatBitCarrierConversionTraitsDoubleTest_282, CarrierToDoubleInfinity_282) {
    double result = Traits::carrier_to_float(0x7FF0000000000000ull);
    EXPECT_TRUE(std::isinf(result));
    EXPECT_GT(result, 0.0);
}

TEST_F(DefaultFloatBitCarrierConversionTraitsDoubleTest_282, CarrierToDoubleNegativeInfinity_282) {
    double result = Traits::carrier_to_float(0xFFF0000000000000ull);
    EXPECT_TRUE(std::isinf(result));
    EXPECT_LT(result, 0.0);
}

TEST_F(DefaultFloatBitCarrierConversionTraitsDoubleTest_282, CarrierToDoubleNaN_282) {
    double result = Traits::carrier_to_float(0x7FF8000000000000ull);
    EXPECT_TRUE(std::isnan(result));
}

TEST_F(DefaultFloatBitCarrierConversionTraitsDoubleTest_282, CarrierToDoubleMaxDouble_282) {
    double result = Traits::carrier_to_float(0x7FEFFFFFFFFFFFFFull);
    EXPECT_EQ(result, std::numeric_limits<double>::max());
}

TEST_F(DefaultFloatBitCarrierConversionTraitsDoubleTest_282, CarrierToDoubleMinPositiveNormal_282) {
    double result = Traits::carrier_to_float(0x0010000000000000ull);
    EXPECT_EQ(result, std::numeric_limits<double>::min());
}

TEST_F(DefaultFloatBitCarrierConversionTraitsDoubleTest_282, CarrierToDoubleSmallestDenormalized_282) {
    double result = Traits::carrier_to_float(0x0000000000000001ull);
    EXPECT_EQ(result, std::numeric_limits<double>::denorm_min());
}

TEST_F(DefaultFloatBitCarrierConversionTraitsDoubleTest_282, DoubleToCarrierZero_282) {
    auto result = Traits::float_to_carrier(0.0);
    EXPECT_EQ(result, 0x0000000000000000ull);
}

TEST_F(DefaultFloatBitCarrierConversionTraitsDoubleTest_282, DoubleToCarrierNegativeZero_282) {
    auto result = Traits::float_to_carrier(-0.0);
    EXPECT_EQ(result, 0x8000000000000000ull);
}

TEST_F(DefaultFloatBitCarrierConversionTraitsDoubleTest_282, DoubleToCarrierOne_282) {
    auto result = Traits::float_to_carrier(1.0);
    EXPECT_EQ(result, 0x3FF0000000000000ull);
}

TEST_F(DefaultFloatBitCarrierConversionTraitsDoubleTest_282, DoubleToCarrierInfinity_282) {
    auto result = Traits::float_to_carrier(std::numeric_limits<double>::infinity());
    EXPECT_EQ(result, 0x7FF0000000000000ull);
}

TEST_F(DefaultFloatBitCarrierConversionTraitsDoubleTest_282, RoundTripDoubleToCarrierAndBack_282) {
    double original = 3.141592653589793;
    auto carrier = Traits::float_to_carrier(original);
    double round_tripped = Traits::carrier_to_float(carrier);
    EXPECT_EQ(original, round_tripped);
}

TEST_F(DefaultFloatBitCarrierConversionTraitsDoubleTest_282, RoundTripCarrierToDoubleAndBack_282) {
    uint64_t original = 0x400921FB54442D18ull; // approximately pi
    double d = Traits::carrier_to_float(original);
    auto round_tripped = Traits::float_to_carrier(d);
    EXPECT_EQ(original, round_tripped);
}

TEST_F(DefaultFloatBitCarrierConversionTraitsDoubleTest_282, RoundTripMultipleDoubleValues_282) {
    double values[] = {0.0, -0.0, 1.0, -1.0, 0.5, -0.5,
                       100.0, -100.0, 1e-300, 1e300,
                       std::numeric_limits<double>::min(),
                       std::numeric_limits<double>::max(),
                       std::numeric_limits<double>::denorm_min(),
                       std::numeric_limits<double>::epsilon()};
    for (double val : values) {
        auto carrier = Traits::float_to_carrier(val);
        double result = Traits::carrier_to_float(carrier);
        EXPECT_EQ(val, result) << "Round trip failed for value: " << val;
    }
}

// Test that carrier_to_float for float type with a known value (2.0f)
TEST_F(DefaultFloatBitCarrierConversionTraitsFloatTest_282, CarrierToFloatTwo_282) {
    // IEEE 754: 2.0f has bit pattern 0x40000000
    float result = Traits::carrier_to_float(0x40000000u);
    EXPECT_EQ(result, 2.0f);
}

// Test that carrier_to_float for double type with a known value (2.0)
TEST_F(DefaultFloatBitCarrierConversionTraitsDoubleTest_282, CarrierToDoubleTwo_282) {
    // IEEE 754: 2.0 has bit pattern 0x4000000000000000
    double result = Traits::carrier_to_float(0x4000000000000000ull);
    EXPECT_EQ(result, 2.0);
}

// Test float_to_carrier with NaN for float
TEST_F(DefaultFloatBitCarrierConversionTraitsFloatTest_282, FloatToCarrierNaN_282) {
    auto result = Traits::float_to_carrier(std::numeric_limits<float>::quiet_NaN());
    // The carrier should represent a NaN - check that converting back gives NaN
    float back = Traits::carrier_to_float(result);
    EXPECT_TRUE(std::isnan(back));
}

// Test float_to_carrier with NaN for double
TEST_F(DefaultFloatBitCarrierConversionTraitsDoubleTest_282, DoubleToCarrierNaN_282) {
    auto result = Traits::float_to_carrier(std::numeric_limits<double>::quiet_NaN());
    double back = Traits::carrier_to_float(result);
    EXPECT_TRUE(std::isnan(back));
}

// Test epsilon values
TEST_F(DefaultFloatBitCarrierConversionTraitsFloatTest_282, FloatToCarrierEpsilon_282) {
    float epsilon = std::numeric_limits<float>::epsilon();
    auto carrier = Traits::float_to_carrier(epsilon);
    float result = Traits::carrier_to_float(carrier);
    EXPECT_EQ(result, epsilon);
}

TEST_F(DefaultFloatBitCarrierConversionTraitsDoubleTest_282, DoubleToCarrierEpsilon_282) {
    double epsilon = std::numeric_limits<double>::epsilon();
    auto carrier = Traits::float_to_carrier(epsilon);
    double result = Traits::carrier_to_float(carrier);
    EXPECT_EQ(result, epsilon);
}

// Test that different carrier values produce different floats (for non-NaN values)
TEST_F(DefaultFloatBitCarrierConversionTraitsFloatTest_282, DifferentCarriersDifferentFloats_282) {
    float f1 = Traits::carrier_to_float(0x3F800000u); // 1.0f
    float f2 = Traits::carrier_to_float(0x40000000u); // 2.0f
    EXPECT_NE(f1, f2);
}

TEST_F(DefaultFloatBitCarrierConversionTraitsDoubleTest_282, DifferentCarriersDifferentDoubles_282) {
    double d1 = Traits::carrier_to_float(0x3FF0000000000000ull); // 1.0
    double d2 = Traits::carrier_to_float(0x4000000000000000ull); // 2.0
    EXPECT_NE(d1, d2);
}

} // namespace

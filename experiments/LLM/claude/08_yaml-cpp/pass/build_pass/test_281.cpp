#include <gtest/gtest.h>
#include <cmath>
#include <cstring>
#include <limits>

// Include the header under test
#include "./TestProjects/yaml-cpp/src/contrib/dragonbox.h"

namespace {

using float_traits = YAML::jkj::dragonbox::default_float_bit_carrier_conversion_traits<float>;
using double_traits = YAML::jkj::dragonbox::default_float_bit_carrier_conversion_traits<double>;

// ============================================================
// Tests for float (32-bit)
// ============================================================

class DefaultFloatBitCarrierConversionTraitsFloatTest_281 : public ::testing::Test {};

TEST_F(DefaultFloatBitCarrierConversionTraitsFloatTest_281, FloatToCarrierZero_281) {
    float val = 0.0f;
    auto carrier = float_traits::float_to_carrier(val);
    // Positive zero should have all bits zero
    EXPECT_EQ(carrier, 0u);
}

TEST_F(DefaultFloatBitCarrierConversionTraitsFloatTest_281, FloatToCarrierNegativeZero_281) {
    float val = -0.0f;
    auto carrier = float_traits::float_to_carrier(val);
    // Negative zero has sign bit set: 0x80000000
    EXPECT_EQ(carrier, 0x80000000u);
}

TEST_F(DefaultFloatBitCarrierConversionTraitsFloatTest_281, FloatToCarrierOne_281) {
    float val = 1.0f;
    auto carrier = float_traits::float_to_carrier(val);
    // IEEE 754: 1.0f = 0x3F800000
    EXPECT_EQ(carrier, 0x3F800000u);
}

TEST_F(DefaultFloatBitCarrierConversionTraitsFloatTest_281, FloatToCarrierNegativeOne_281) {
    float val = -1.0f;
    auto carrier = float_traits::float_to_carrier(val);
    // IEEE 754: -1.0f = 0xBF800000
    EXPECT_EQ(carrier, 0xBF800000u);
}

TEST_F(DefaultFloatBitCarrierConversionTraitsFloatTest_281, FloatToCarrierInfinity_281) {
    float val = std::numeric_limits<float>::infinity();
    auto carrier = float_traits::float_to_carrier(val);
    // +inf = 0x7F800000
    EXPECT_EQ(carrier, 0x7F800000u);
}

TEST_F(DefaultFloatBitCarrierConversionTraitsFloatTest_281, FloatToCarrierNegativeInfinity_281) {
    float val = -std::numeric_limits<float>::infinity();
    auto carrier = float_traits::float_to_carrier(val);
    // -inf = 0xFF800000
    EXPECT_EQ(carrier, 0xFF800000u);
}

TEST_F(DefaultFloatBitCarrierConversionTraitsFloatTest_281, FloatToCarrierNaN_281) {
    float val = std::numeric_limits<float>::quiet_NaN();
    auto carrier = float_traits::float_to_carrier(val);
    // NaN has exponent all ones and non-zero mantissa
    // Check exponent bits are all set
    EXPECT_EQ(carrier & 0x7F800000u, 0x7F800000u);
    // Check mantissa is non-zero (it's a NaN)
    EXPECT_NE(carrier & 0x007FFFFFu, 0u);
}

TEST_F(DefaultFloatBitCarrierConversionTraitsFloatTest_281, FloatToCarrierSmallestDenorm_281) {
    float val = std::numeric_limits<float>::denorm_min();
    auto carrier = float_traits::float_to_carrier(val);
    // Smallest denormalized float: 0x00000001
    EXPECT_EQ(carrier, 0x00000001u);
}

TEST_F(DefaultFloatBitCarrierConversionTraitsFloatTest_281, FloatToCarrierMaxFloat_281) {
    float val = std::numeric_limits<float>::max();
    auto carrier = float_traits::float_to_carrier(val);
    // max float = 0x7F7FFFFF
    EXPECT_EQ(carrier, 0x7F7FFFFFu);
}

TEST_F(DefaultFloatBitCarrierConversionTraitsFloatTest_281, FloatToCarrierMinNormalized_281) {
    float val = std::numeric_limits<float>::min();
    auto carrier = float_traits::float_to_carrier(val);
    // Smallest normalized float: 0x00800000
    EXPECT_EQ(carrier, 0x00800000u);
}

TEST_F(DefaultFloatBitCarrierConversionTraitsFloatTest_281, CarrierToFloatZero_281) {
    auto result = float_traits::carrier_to_float(0u);
    EXPECT_EQ(result, 0.0f);
    // Verify it's positive zero
    EXPECT_FALSE(std::signbit(result));
}

TEST_F(DefaultFloatBitCarrierConversionTraitsFloatTest_281, CarrierToFloatNegativeZero_281) {
    auto result = float_traits::carrier_to_float(0x80000000u);
    EXPECT_EQ(result, -0.0f);
    EXPECT_TRUE(std::signbit(result));
}

TEST_F(DefaultFloatBitCarrierConversionTraitsFloatTest_281, CarrierToFloatOne_281) {
    auto result = float_traits::carrier_to_float(0x3F800000u);
    EXPECT_EQ(result, 1.0f);
}

TEST_F(DefaultFloatBitCarrierConversionTraitsFloatTest_281, CarrierToFloatInfinity_281) {
    auto result = float_traits::carrier_to_float(0x7F800000u);
    EXPECT_TRUE(std::isinf(result));
    EXPECT_GT(result, 0.0f);
}

TEST_F(DefaultFloatBitCarrierConversionTraitsFloatTest_281, CarrierToFloatNaN_281) {
    auto result = float_traits::carrier_to_float(0x7FC00000u);
    EXPECT_TRUE(std::isnan(result));
}

TEST_F(DefaultFloatBitCarrierConversionTraitsFloatTest_281, RoundTripFloat_281) {
    float values[] = {0.0f, -0.0f, 1.0f, -1.0f, 0.5f, 3.14f, -2.718f,
                      std::numeric_limits<float>::min(),
                      std::numeric_limits<float>::max(),
                      std::numeric_limits<float>::denorm_min(),
                      std::numeric_limits<float>::epsilon()};
    for (float val : values) {
        auto carrier = float_traits::float_to_carrier(val);
        auto result = float_traits::carrier_to_float(carrier);
        // Bit-exact comparison using memcmp to handle NaN and signed zeros
        EXPECT_EQ(std::memcmp(&val, &result, sizeof(float)), 0)
            << "Round-trip failed for value with carrier: " << carrier;
    }
}

TEST_F(DefaultFloatBitCarrierConversionTraitsFloatTest_281, RoundTripCarrierFloat_281) {
    uint32_t carriers[] = {0u, 0x80000000u, 0x3F800000u, 0x7F800000u,
                           0x00000001u, 0x7F7FFFFFu, 0x00800000u,
                           0x42280000u /* 42.0f */};
    for (auto c : carriers) {
        auto f = float_traits::carrier_to_float(c);
        auto result = float_traits::float_to_carrier(f);
        EXPECT_EQ(result, c) << "Round-trip failed for carrier: " << c;
    }
}

// ============================================================
// Tests for double (64-bit)
// ============================================================

class DefaultFloatBitCarrierConversionTraitsDoubleTest_281 : public ::testing::Test {};

TEST_F(DefaultFloatBitCarrierConversionTraitsDoubleTest_281, DoubleToCarrierZero_281) {
    double val = 0.0;
    auto carrier = double_traits::float_to_carrier(val);
    EXPECT_EQ(carrier, 0ull);
}

TEST_F(DefaultFloatBitCarrierConversionTraitsDoubleTest_281, DoubleToCarrierNegativeZero_281) {
    double val = -0.0;
    auto carrier = double_traits::float_to_carrier(val);
    EXPECT_EQ(carrier, 0x8000000000000000ull);
}

TEST_F(DefaultFloatBitCarrierConversionTraitsDoubleTest_281, DoubleToCarrierOne_281) {
    double val = 1.0;
    auto carrier = double_traits::float_to_carrier(val);
    // IEEE 754: 1.0 = 0x3FF0000000000000
    EXPECT_EQ(carrier, 0x3FF0000000000000ull);
}

TEST_F(DefaultFloatBitCarrierConversionTraitsDoubleTest_281, DoubleToCarrierNegativeOne_281) {
    double val = -1.0;
    auto carrier = double_traits::float_to_carrier(val);
    EXPECT_EQ(carrier, 0xBFF0000000000000ull);
}

TEST_F(DefaultFloatBitCarrierConversionTraitsDoubleTest_281, DoubleToCarrierInfinity_281) {
    double val = std::numeric_limits<double>::infinity();
    auto carrier = double_traits::float_to_carrier(val);
    EXPECT_EQ(carrier, 0x7FF0000000000000ull);
}

TEST_F(DefaultFloatBitCarrierConversionTraitsDoubleTest_281, DoubleToCarrierNegativeInfinity_281) {
    double val = -std::numeric_limits<double>::infinity();
    auto carrier = double_traits::float_to_carrier(val);
    EXPECT_EQ(carrier, 0xFFF0000000000000ull);
}

TEST_F(DefaultFloatBitCarrierConversionTraitsDoubleTest_281, DoubleToCarrierNaN_281) {
    double val = std::numeric_limits<double>::quiet_NaN();
    auto carrier = double_traits::float_to_carrier(val);
    // Exponent all ones
    EXPECT_EQ(carrier & 0x7FF0000000000000ull, 0x7FF0000000000000ull);
    // Mantissa non-zero
    EXPECT_NE(carrier & 0x000FFFFFFFFFFFFFull, 0ull);
}

TEST_F(DefaultFloatBitCarrierConversionTraitsDoubleTest_281, DoubleToCarrierSmallestDenorm_281) {
    double val = std::numeric_limits<double>::denorm_min();
    auto carrier = double_traits::float_to_carrier(val);
    EXPECT_EQ(carrier, 0x0000000000000001ull);
}

TEST_F(DefaultFloatBitCarrierConversionTraitsDoubleTest_281, DoubleToCarrierMaxDouble_281) {
    double val = std::numeric_limits<double>::max();
    auto carrier = double_traits::float_to_carrier(val);
    EXPECT_EQ(carrier, 0x7FEFFFFFFFFFFFFFull);
}

TEST_F(DefaultFloatBitCarrierConversionTraitsDoubleTest_281, DoubleToCarrierMinNormalized_281) {
    double val = std::numeric_limits<double>::min();
    auto carrier = double_traits::float_to_carrier(val);
    EXPECT_EQ(carrier, 0x0010000000000000ull);
}

TEST_F(DefaultFloatBitCarrierConversionTraitsDoubleTest_281, CarrierToDoubleZero_281) {
    auto result = double_traits::carrier_to_float(0ull);
    EXPECT_EQ(result, 0.0);
    EXPECT_FALSE(std::signbit(result));
}

TEST_F(DefaultFloatBitCarrierConversionTraitsDoubleTest_281, CarrierToDoubleNegativeZero_281) {
    auto result = double_traits::carrier_to_float(0x8000000000000000ull);
    EXPECT_EQ(result, -0.0);
    EXPECT_TRUE(std::signbit(result));
}

TEST_F(DefaultFloatBitCarrierConversionTraitsDoubleTest_281, CarrierToDoubleOne_281) {
    auto result = double_traits::carrier_to_float(0x3FF0000000000000ull);
    EXPECT_EQ(result, 1.0);
}

TEST_F(DefaultFloatBitCarrierConversionTraitsDoubleTest_281, CarrierToDoubleInfinity_281) {
    auto result = double_traits::carrier_to_float(0x7FF0000000000000ull);
    EXPECT_TRUE(std::isinf(result));
    EXPECT_GT(result, 0.0);
}

TEST_F(DefaultFloatBitCarrierConversionTraitsDoubleTest_281, CarrierToDoubleNaN_281) {
    auto result = double_traits::carrier_to_float(0x7FF8000000000000ull);
    EXPECT_TRUE(std::isnan(result));
}

TEST_F(DefaultFloatBitCarrierConversionTraitsDoubleTest_281, RoundTripDouble_281) {
    double values[] = {0.0, -0.0, 1.0, -1.0, 0.5, 3.141592653589793, -2.718281828459045,
                       std::numeric_limits<double>::min(),
                       std::numeric_limits<double>::max(),
                       std::numeric_limits<double>::denorm_min(),
                       std::numeric_limits<double>::epsilon()};
    for (double val : values) {
        auto carrier = double_traits::float_to_carrier(val);
        auto result = double_traits::carrier_to_float(carrier);
        EXPECT_EQ(std::memcmp(&val, &result, sizeof(double)), 0)
            << "Round-trip failed for double value with carrier: " << carrier;
    }
}

TEST_F(DefaultFloatBitCarrierConversionTraitsDoubleTest_281, RoundTripCarrierDouble_281) {
    uint64_t carriers[] = {0ull, 0x8000000000000000ull, 0x3FF0000000000000ull,
                           0x7FF0000000000000ull, 0x0000000000000001ull,
                           0x7FEFFFFFFFFFFFFFull, 0x0010000000000000ull,
                           0x4045000000000000ull /* 42.0 */};
    for (auto c : carriers) {
        auto d = double_traits::carrier_to_float(c);
        auto result = double_traits::float_to_carrier(d);
        EXPECT_EQ(result, c) << "Round-trip failed for carrier: " << c;
    }
}

// ============================================================
// Additional edge case tests
// ============================================================

TEST_F(DefaultFloatBitCarrierConversionTraitsFloatTest_281, FloatToCarrierPi_281) {
    float val = 3.14159265f;
    auto carrier = float_traits::float_to_carrier(val);
    auto roundtrip = float_traits::carrier_to_float(carrier);
    EXPECT_EQ(val, roundtrip);
}

TEST_F(DefaultFloatBitCarrierConversionTraitsFloatTest_281, FloatToCarrierEpsilon_281) {
    float val = std::numeric_limits<float>::epsilon();
    auto carrier = float_traits::float_to_carrier(val);
    // epsilon = 0x34000000
    EXPECT_EQ(carrier, 0x34000000u);
}

TEST_F(DefaultFloatBitCarrierConversionTraitsDoubleTest_281, DoubleToCarrierEpsilon_281) {
    double val = std::numeric_limits<double>::epsilon();
    auto carrier = double_traits::float_to_carrier(val);
    // double epsilon = 0x3CB0000000000000
    EXPECT_EQ(carrier, 0x3CB0000000000000ull);
}

TEST_F(DefaultFloatBitCarrierConversionTraitsFloatTest_281, FloatToCarrierTwo_281) {
    float val = 2.0f;
    auto carrier = float_traits::float_to_carrier(val);
    // 2.0f = 0x40000000
    EXPECT_EQ(carrier, 0x40000000u);
}

TEST_F(DefaultFloatBitCarrierConversionTraitsDoubleTest_281, DoubleToCarrierTwo_281) {
    double val = 2.0;
    auto carrier = double_traits::float_to_carrier(val);
    // 2.0 = 0x4000000000000000
    EXPECT_EQ(carrier, 0x4000000000000000ull);
}

TEST_F(DefaultFloatBitCarrierConversionTraitsFloatTest_281, FloatToCarrierHalf_281) {
    float val = 0.5f;
    auto carrier = float_traits::float_to_carrier(val);
    // 0.5f = 0x3F000000
    EXPECT_EQ(carrier, 0x3F000000u);
}

TEST_F(DefaultFloatBitCarrierConversionTraitsDoubleTest_281, DoubleToCarrierHalf_281) {
    double val = 0.5;
    auto carrier = double_traits::float_to_carrier(val);
    // 0.5 = 0x3FE0000000000000
    EXPECT_EQ(carrier, 0x3FE0000000000000ull);
}

} // anonymous namespace

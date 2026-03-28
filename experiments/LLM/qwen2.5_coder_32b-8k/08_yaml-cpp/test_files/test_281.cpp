#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "dragonbox.h"



namespace YAML { namespace jkj { namespace dragonbox {



using namespace ::testing;



TEST(default_float_bit_carrier_conversion_traits_281, FloatToCarrier_RoundTripConversion_281) {

    float original_value = 3.14159f;

    auto carrier = default_float_bit_carrier_conversion_traits<float>::float_to_carrier(original_value);

    auto converted_back = default_float_bit_carrier_conversion_traits<float>::carrier_to_float(carrier);

    EXPECT_FLOAT_EQ(original_value, converted_back);

}



TEST(default_float_bit_carrier_conversion_traits_281, FloatToCarrier_ZeroValue_281) {

    float zero_value = 0.0f;

    auto carrier = default_float_bit_carrier_conversion_traits<float>::float_to_carrier(zero_value);

    EXPECT_EQ(carrier, 0u); // Assuming carrier_uint is unsigned

}



TEST(default_float_bit_carrier_conversion_traits_281, FloatToCarrier_MaxValue_281) {

    float max_value = std::numeric_limits<float>::max();

    auto carrier = default_float_bit_carrier_conversion_traits<float>::float_to_carrier(max_value);

    EXPECT_NE(carrier, 0u); // Carrier should not be zero for max value

}



TEST(default_float_bit_carrier_conversion_traits_281, FloatToCarrier_MinValue_281) {

    float min_value = std::numeric_limits<float>::min();

    auto carrier = default_float_bit_carrier_conversion_traits<float>::float_to_carrier(min_value);

    EXPECT_NE(carrier, 0u); // Carrier should not be zero for min value

}



TEST(default_float_bit_carrier_conversion_traits_281, FloatToCarrier_NegativeValue_281) {

    float negative_value = -2.718f;

    auto carrier = default_float_bit_carrier_conversion_traits<float>::float_to_carrier(negative_value);

    auto converted_back = default_float_bit_carrier_conversion_traits<float>::carrier_to_float(carrier);

    EXPECT_FLOAT_EQ(negative_value, converted_back);

}



TEST(default_float_bit_carrier_conversion_traits_281, CarrierToFloat_RoundTripConversion_281) {

    carrier_uint original_carrier = 0x40490fdb; // Bit representation of 3.14159f

    auto value = default_float_bit_carrier_conversion_traits<float>::carrier_to_float(original_carrier);

    auto converted_back = default_float_bit_carrier_conversion_traits<float>::float_to_carrier(value);

    EXPECT_EQ(original_carrier, converted_back);

}



TEST(default_float_bit_carrier_conversion_traits_281, CarrierToFloat_ZeroCarrier_281) {

    carrier_uint zero_carrier = 0u;

    auto value = default_float_bit_carrier_conversion_traits<float>::carrier_to_float(zero_carrier);

    EXPECT_FLOAT_EQ(value, 0.0f);

}



TEST(default_float_bit_carrier_conversion_traits_281, CarrierToFloat_MaxCarrier_281) {

    carrier_uint max_carrier = std::numeric_limits<carrier_uint>::max();

    auto value = default_float_bit_carrier_conversion_traits<float>::carrier_to_float(max_carrier);

    EXPECT_EQ(std::signbit(value), 0); // Positive infinity or NaN

}



TEST(default_float_bit_carrier_conversion_traits_281, CarrierToFloat_MinCarrier_281) {

    carrier_uint min_carrier = std::numeric_limits<carrier_uint>::min();

    auto value = default_float_bit_carrier_conversion_traits<float>::carrier_to_float(min_carrier);

    EXPECT_EQ(std::signbit(value), 0); // Zero or positive subnormal

}



}}} // namespace YAML::jkj::dragonbox

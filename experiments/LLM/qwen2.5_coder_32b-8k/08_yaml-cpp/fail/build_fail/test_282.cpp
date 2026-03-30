#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/yaml-cpp/src/contrib/dragonbox.h"



using namespace YAML::jkj::dragonbox;



template <>

struct default_float_bit_carrier_conversion_traits<float> {

    using carrier_uint = uint32_t;

    static JKJ_CONSTEXPR20 carrier_uint float_to_carrier(float x) noexcept;

    static JKJ_CONSTEXPR20 float carrier_to_float(carrier_uint x) noexcept;

};



TEST_F(DragonboxTest_282, CarrierToFloat_Conversion_NormalOperation_282) {

    default_float_bit_carrier_conversion_traits<float> traits;

    uint32_t carrier_value = 0x40490fdb; // Represents 3.14f in IEEE 754

    float expected_result = 3.14f;

    EXPECT_FLOAT_EQ(traits.carrier_to_float(carrier_value), expected_result);

}



TEST_F(DragonboxTest_282, CarrierToFloat_Conversion_BoundaryCondition_Zero_282) {

    default_float_bit_carrier_conversion_traits<float> traits;

    uint32_t carrier_value = 0x00000000; // Represents 0.0f in IEEE 754

    float expected_result = 0.0f;

    EXPECT_FLOAT_EQ(traits.carrier_to_float(carrier_value), expected_result);

}



TEST_F(DragonboxTest_282, CarrierToFloat_Conversion_BoundaryCondition_Max_282) {

    default_float_bit_carrier_conversion_traits<float> traits;

    uint32_t carrier_value = 0x7f7fffff; // Represents positive infinity in IEEE 754

    float expected_result = std::numeric_limits<float>::infinity();

    EXPECT_FLOAT_EQ(traits.carrier_to_float(carrier_value), expected_result);

}



TEST_F(DragonboxTest_282, CarrierToFloat_Conversion_BoundaryCondition_Min_282) {

    default_float_bit_carrier_conversion_traits<float> traits;

    uint32_t carrier_value = 0xff7fffff; // Represents negative infinity in IEEE 754

    float expected_result = -std::numeric_limits<float>::infinity();

    EXPECT_FLOAT_EQ(traits.carrier_to_float(carrier_value), expected_result);

}



TEST_F(DragonboxTest_282, CarrierToFloat_Conversion_Exceptional_NaN_282) {

    default_float_bit_carrier_conversion_traits<float> traits;

    uint32_t carrier_value = 0x7fc00001; // Represents NaN in IEEE 754

    float result = traits.carrier_to_float(carrier_value);

    EXPECT_TRUE(std::isnan(result));

}

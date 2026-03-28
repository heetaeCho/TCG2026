#include <gtest/gtest.h>

#include "dragonbox.h"



using namespace YAML::jkj::dragonbox;



TEST_F(DragonboxFloatBitsTest_298, IsFinite_ValidExponent_298) {

    float_bits<float> fb(0x40490fdb); // Example bit pattern for 3.14

    EXPECT_TRUE(fb.is_finite(fb.extract_exponent_bits()));

}



TEST_F(DragonboxFloatBitsTest_298, IsFinite_ZeroExponent_298) {

    float_bits<float> fb(0x00000000); // Zero

    EXPECT_TRUE(fb.is_finite(fb.extract_exponent_bits()));

}



TEST_F(DragonboxFloatBitsTest_298, IsFinite_MaxExponent_298) {

    float_bits<float> fb(0x7f800000); // Infinity

    EXPECT_FALSE(fb.is_finite(fb.extract_exponent_bits()));

}



TEST_F(DragonboxFloatBitsTest_298, IsFinite_DenormalExponent_298) {

    float_bits<float> fb(0x00400000); // Denormal number

    EXPECT_TRUE(fb.is_finite(fb.extract_exponent_bits()));

}



TEST_F(DragonboxFloatBitsTest_298, IsFinite_NaNExponent_298) {

    float_bits<float> fb(0x7fc00000); // NaN

    EXPECT_FALSE(fb.is_finite(fb.extract_exponent_bits()));

}



TEST_F(DragonboxFloatBitsTest_298, IsFinite_ValidExponent_DefaultFunction_298) {

    float_bits<float> fb(0x40490fdb); // Example bit pattern for 3.14

    EXPECT_TRUE(fb.is_finite());

}



TEST_F(DragonboxFloatBitsTest_298, IsFinite_ZeroExponent_DefaultFunction_298) {

    float_bits<float> fb(0x00000000); // Zero

    EXPECT_TRUE(fb.is_finite());

}



TEST_F(DragonboxFloatBitsTest_298, IsFinite_MaxExponent_DefaultFunction_298) {

    float_bits<float> fb(0x7f800000); // Infinity

    EXPECT_FALSE(fb.is_finite());

}



TEST_F(DragonboxFloatBitsTest_298, IsFinite_DenormalExponent_DefaultFunction_298) {

    float_bits<float> fb(0x00400000); // Denormal number

    EXPECT_TRUE(fb.is_finite());

}



TEST_F(DragonboxFloatBitsTest_298, IsFinite_NaNExponent_DefaultFunction_298) {

    float_bits<float> fb(0x7fc00000); // NaN

    EXPECT_FALSE(fb.is_finite());

}

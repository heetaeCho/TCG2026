#include <gtest/gtest.h>

#include "./TestProjects/yaml-cpp/src/contrib/dragonbox.h"



using namespace YAML::jkj::dragonbox;



// Mocking a FormatTraits struct for testing purposes

struct MockFormatTraits {

    using exponent_int = int;

    using carrier_uint = unsigned int;

    static constexpr exponent_int extract_exponent_bits(carrier_uint bit_pattern) noexcept {

        // Simplified mock implementation for testing

        return (bit_pattern >> 23) & 0xFF;

    }

};



using TestFloatBits = float_bits<MockFormatTraits>;



class FloatBitsTest_288 : public ::testing::Test {

protected:

    TestFloatBits fb;



    void SetUp() override {

        // Initialize with a default bit pattern

        fb = TestFloatBits(0x41700000); // Represents the float number 15.0 in IEEE 754 format

    }

};



TEST_F(FloatBitsTest_288, ExtractExponentBits_NormalOperation_288) {

    EXPECT_EQ(fb.extract_exponent_bits(), 126);

}



TEST_F(FloatBitsTest_288, ExtractExponentBits_ZeroExponent_288) {

    TestFloatBits fb_zero(0x00000000); // Represents the float number 0.0 in IEEE 754 format

    EXPECT_EQ(fb_zero.extract_exponent_bits(), 0);

}



TEST_F(FloatBitsTest_288, ExtractExponentBits_MaxExponent_288) {

    TestFloatBits fb_max(0x7F800000); // Represents the float number positive infinity in IEEE 754 format

    EXPECT_EQ(fb_max.extract_exponent_bits(), 255);

}



TEST_F(FloatBitsTest_288, ExtractExponentBits_MinNormalizedExponent_288) {

    TestFloatBits fb_min_normalized(0x00800000); // Represents the float number 1.175494e-38 in IEEE 754 format

    EXPECT_EQ(fb_min_normalized.extract_exponent_bits(), 1);

}



TEST_F(FloatBitsTest_288, BinaryExponent_NormalOperation_288) {

    EXPECT_EQ(TestFloatBits::binary_exponent(126), 126 - 127); // Bias for single precision is 127

}



TEST_F(FloatBitsTest_288, BinaryExponent_ZeroExponent_288) {

    EXPECT_EQ(TestFloatBits::binary_exponent(0), -127);

}



TEST_F(FloatBitsTest_288, BinaryExponent_MaxExponent_288) {

    EXPECT_EQ(TestFloatBits::binary_exponent(255), 255 - 127);

}

#include <gtest/gtest.h>

#include "dragonbox.h"



using namespace YAML::jkj::dragonbox;



// Assuming carrier_uint and exponent_int are defined somewhere in the actual implementation

using carrier_uint = uint32_t;

using exponent_int = int;



class FloatBitsTest_289 : public ::testing::Test {

protected:

    float_bits<> fb_zero;

    float_bits<> fb_positive;

    float_bits<> fb_negative;



    void SetUp() override {

        // Assuming bit patterns for zero, positive, and negative numbers

        fb_zero = float_bits<>(0x00000000); // Zero

        fb_positive = float_bits<>(0x40490fdb); // 3.14 in IEEE 754 single-precision

        fb_negative = float_bits<>(0xc0490fdb); // -3.14 in IEEE 754 single-precision

    }

};



TEST_F(FloatBitsTest_289, ExtractSignificandBits_Zero_289) {

    EXPECT_EQ(fb_zero.extract_significand_bits(), 0);

}



TEST_F(FloatBitsTest_289, ExtractSignificandBits_Positive_289) {

    EXPECT_EQ(fb_positive.extract_significand_bits(), 1253727);

}



TEST_F(FloatBitsTest_289, ExtractSignificandBits_Negative_289) {

    EXPECT_EQ(fb_negative.extract_significand_bits(), 1253727);

}



TEST_F(FloatBitsTest_289, IsNonzero_Zero_289) {

    EXPECT_FALSE(fb_zero.is_nonzero());

}



TEST_F(FloatBitsTest_289, IsNonzero_Positive_289) {

    EXPECT_TRUE(fb_positive.is_nonzero());

}



TEST_F(FloatBitsTest_289, IsNonzero_Negative_289) {

    EXPECT_TRUE(fb_negative.is_nonzero());

}



TEST_F(FloatBitsTest_289, IsPositive_Zero_289) {

    EXPECT_FALSE(fb_zero.is_positive());

}



TEST_F(FloatBitsTest_289, IsPositive_Positive_289) {

    EXPECT_TRUE(fb_positive.is_positive());

}



TEST_F(FloatBitsTest_289, IsPositive_Negative_289) {

    EXPECT_FALSE(fb_negative.is_positive());

}



TEST_F(FloatBitsTest_289, IsNegative_Zero_289) {

    EXPECT_FALSE(fb_zero.is_negative());

}



TEST_F(FloatBitsTest_289, IsNegative_Positive_289) {

    EXPECT_FALSE(fb_positive.is_negative());

}



TEST_F(FloatBitsTest_289, IsNegative_Negative_289) {

    EXPECT_TRUE(fb_negative.is_negative());

}

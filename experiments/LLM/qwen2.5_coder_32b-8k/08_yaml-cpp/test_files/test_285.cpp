#include <gtest/gtest.h>

#include "TestProjects/yaml-cpp/src/contrib/dragonbox.h"



using namespace YAML::jkj::dragonbox;



// Mocking FormatTraits to use with signed_significand_bits

struct MockFormatTraits {

    static constexpr bool is_negative(carrier_uint u) noexcept {

        return u & (1ull << 63); // Assuming carrier_uint is a 64-bit unsigned integer for this example

    }

};



class SignedSignificandBitsTest_285 : public ::testing::Test {

protected:

    signed_significand_bits<MockFormatTraits> s;

};



TEST_F(SignedSignificandBitsTest_285, DefaultConstructorSetsZero_285) {

    EXPECT_EQ(s.u, 0);

}



TEST_F(SignedSignificandBitsTest_285, ExplicitConstructorSetsBitPattern_285) {

    carrier_uint bit_pattern = 123456789;

    signed_significand_bits<MockFormatTraits> s(bit_pattern);

    EXPECT_EQ(s.u, bit_pattern);

}



TEST_F(SignedSignificandBitsTest_285, IsNegative_ReturnsTrueForNegativePattern_285) {

    carrier_uint negative_bit_pattern = 1ull << 63; // Set the sign bit

    signed_significand_bits<MockFormatTraits> s(negative_bit_pattern);

    EXPECT_TRUE(s.is_negative());

}



TEST_F(SignedSignificandBitsTest_285, IsNegative_ReturnsFalseForPositivePattern_285) {

    carrier_uint positive_bit_pattern = 123456789;

    signed_significand_bits<MockFormatTraits> s(positive_bit_pattern);

    EXPECT_FALSE(s.is_negative());

}



TEST_F(SignedSignificandBitsTest_285, IsPositive_ReturnsTrueForPositivePattern_285) {

    carrier_uint positive_bit_pattern = 123456789;

    signed_significand_bits<MockFormatTraits> s(positive_bit_pattern);

    EXPECT_TRUE(s.is_positive());

}



TEST_F(SignedSignificandBitsTest_285, IsPositive_ReturnsFalseForNegativePattern_285) {

    carrier_uint negative_bit_pattern = 1ull << 63; // Set the sign bit

    signed_significand_bits<MockFormatTraits> s(negative_bit_pattern);

    EXPECT_FALSE(s.is_positive());

}



TEST_F(SignedSignificandBitsTest_285, HasAllZeroSignificandBits_ReturnsTrueForZeroPattern_285) {

    carrier_uint zero_bit_pattern = 0;

    signed_significand_bits<MockFormatTraits> s(zero_bit_pattern);

    EXPECT_TRUE(s.has_all_zero_significand_bits());

}



TEST_F(SignedSignificandBitsTest_285, HasAllZeroSignificandBits_ReturnsFalseForNonZeroPattern_285) {

    carrier_uint non_zero_bit_pattern = 123456789;

    signed_significand_bits<MockFormatTraits> s(non_zero_bit_pattern);

    EXPECT_FALSE(s.has_all_zero_significand_bits());

}



TEST_F(SignedSignificandBitsTest_285, HasEvenSignificandBits_ReturnsTrueForEvenPattern_285) {

    carrier_uint even_bit_pattern = 2; // Binary: 10

    signed_significand_bits<MockFormatTraits> s(even_bit_pattern);

    EXPECT_TRUE(s.has_even_significand_bits());

}



TEST_F(SignedSignificandBitsTest_285, HasEvenSignificandBits_ReturnsFalseForOddPattern_285) {

    carrier_uint odd_bit_pattern = 1; // Binary: 1

    signed_significand_bits<MockFormatTraits> s(odd_bit_pattern);

    EXPECT_FALSE(s.has_even_significand_bits());

}

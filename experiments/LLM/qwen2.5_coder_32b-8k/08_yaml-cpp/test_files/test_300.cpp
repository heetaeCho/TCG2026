#include <gtest/gtest.h>

#include "dragonbox.h"



namespace YAML { namespace jkj { namespace dragonbox {



using namespace ::testing;



// Test fixture for float_bits class

class FloatBitsTest_300 : public Test {

protected:

    using FormatTraits = /* specify appropriate format traits here */;

    using FloatBitsType = float_bits<FormatTraits>;

    FloatBitsType fb;

};



TEST_F(FloatBitsTest_300, HasEvenSignificandBits_ReturnsTrueForEven_300) {

    // Arrange

    uint32_t bit_pattern_with_even_significand = 0x12345678; // Example pattern with even significand bits

    FloatBitsType fb(bit_pattern_with_even_significand);



    // Act & Assert

    EXPECT_TRUE(fb.has_even_significand_bits());

}



TEST_F(FloatBitsTest_300, HasEvenSignificandBits_ReturnsFalseForOdd_300) {

    // Arrange

    uint32_t bit_pattern_with_odd_significand = 0x12345679; // Example pattern with odd significand bits

    FloatBitsType fb(bit_pattern_with_odd_significand);



    // Act & Assert

    EXPECT_FALSE(fb.has_even_significand_bits());

}



TEST_F(FloatBitsTest_300, ExtractExponentBits_ReturnsCorrectValue_300) {

    // Arrange

    uint32_t bit_pattern = 0x12345678; // Example pattern

    FloatBitsType fb(bit_pattern);

    exponent_int expected_exponent_bits = /* calculate expected value based on bit_pattern */;



    // Act & Assert

    EXPECT_EQ(fb.extract_exponent_bits(), expected_exponent_bits);

}



TEST_F(FloatBitsTest_300, ExtractSignificandBits_ReturnsCorrectValue_300) {

    // Arrange

    uint32_t bit_pattern = 0x12345678; // Example pattern

    FloatBitsType fb(bit_pattern);

    carrier_uint expected_significand_bits = /* calculate expected value based on bit_pattern */;



    // Act & Assert

    EXPECT_EQ(fb.extract_significand_bits(), expected_significand_bits);

}



TEST_F(FloatBitsTest_300, IsNonzero_ReturnsTrueForNonzeroPattern_300) {

    // Arrange

    uint32_t nonzero_bit_pattern = 0x12345678; // Example pattern

    FloatBitsType fb(nonzero_bit_pattern);



    // Act & Assert

    EXPECT_TRUE(fb.is_nonzero());

}



TEST_F(FloatBitsTest_300, IsNonzero_ReturnsFalseForZeroPattern_300) {

    // Arrange

    uint32_t zero_bit_pattern = 0x0; // Zero pattern

    FloatBitsType fb(zero_bit_pattern);



    // Act & Assert

    EXPECT_FALSE(fb.is_nonzero());

}



TEST_F(FloatBitsTest_300, IsPositive_ReturnsTrueForPositivePattern_300) {

    // Arrange

    uint32_t positive_bit_pattern = 0x12345678; // Example pattern with positive sign bit

    FloatBitsType fb(positive_bit_pattern);



    // Act & Assert

    EXPECT_TRUE(fb.is_positive());

}



TEST_F(FloatBitsTest_300, IsPositive_ReturnsFalseForNegativePattern_300) {

    // Arrange

    uint32_t negative_bit_pattern = 0x82345678; // Example pattern with negative sign bit

    FloatBitsType fb(negative_bit_pattern);



    // Act & Assert

    EXPECT_FALSE(fb.is_positive());

}



TEST_F(FloatBitsTest_300, IsNegative_ReturnsTrueForNegativePattern_300) {

    // Arrange

    uint32_t negative_bit_pattern = 0x82345678; // Example pattern with negative sign bit

    FloatBitsType fb(negative_bit_pattern);



    // Act & Assert

    EXPECT_TRUE(fb.is_negative());

}



TEST_F(FloatBitsTest_300, IsNegative_ReturnsFalseForPositivePattern_300) {

    // Arrange

    uint32_t positive_bit_pattern = 0x12345678; // Example pattern with positive sign bit

    FloatBitsType fb(positive_bit_pattern);



    // Act & Assert

    EXPECT_FALSE(fb.is_negative());

}



TEST_F(FloatBitsTest_300, IsFinite_ReturnsTrueForNormalValue_300) {

    // Arrange

    uint32_t normal_value_bit_pattern = 0x12345678; // Example pattern for a normal value

    FloatBitsType fb(normal_value_bit_pattern);



    // Act & Assert

    EXPECT_TRUE(fb.is_finite());

}



TEST_F(FloatBitsTest_300, IsFinite_ReturnsFalseForInfinity_300) {

    // Arrange

    uint32_t infinity_bit_pattern = 0x7F800000; // Example pattern for positive infinity

    FloatBitsType fb(infinity_bit_pattern);



    // Act & Assert

    EXPECT_FALSE(fb.is_finite());

}



TEST_F(FloatBitsTest_300, IsFinite_ReturnsFalseForNegativeInfinity_300) {

    // Arrange

    uint32_t negative_infinity_bit_pattern = 0xFF800000; // Example pattern for negative infinity

    FloatBitsType fb(negative_infinity_bit_pattern);



    // Act & Assert

    EXPECT_FALSE(fb.is_finite());

}



TEST_F(FloatBitsTest_300, IsFinite_ReturnsFalseForNaN_300) {

    // Arrange

    uint32_t nan_bit_pattern = 0x7FC00001; // Example pattern for NaN (Not a Number)

    FloatBitsType fb(nan_bit_pattern);



    // Act & Assert

    EXPECT_FALSE(fb.is_finite());

}



TEST_F(FloatBitsTest_300, BinaryExponent_ReturnsCorrectValue_300) {

    // Arrange

    uint32_t bit_pattern = 0x12345678; // Example pattern

    FloatBitsType fb(bit_pattern);

    exponent_int expected_binary_exponent = /* calculate expected value based on bit_pattern */;



    // Act & Assert

    EXPECT_EQ(fb.binary_exponent(), expected_binary_exponent);

}



TEST_F(FloatBitsTest_300, BinarySignificand_ReturnsCorrectValue_300) {

    // Arrange

    uint32_t bit_pattern = 0x12345678; // Example pattern

    FloatBitsType fb(bit_pattern);

    carrier_uint expected_binary_significand = /* calculate expected value based on bit_pattern */;



    // Act & Assert

    EXPECT_EQ(fb.binary_significand(), expected_binary_significand);

}



}}} // namespace YAML::jkj::dragonbox

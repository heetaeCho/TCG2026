#include <gtest/gtest.h>

#include "./TestProjects/yaml-cpp/src/contrib/dragonbox.h"



using namespace YAML::jkj::dragonbox;



struct MockFormatTraits {

    static constexpr bool is_positive(carrier_uint u) noexcept {

        return (u & (carrier_uint(1) << (sizeof(carrier_uint) * 8 - 1))) == 0;

    }

};



template struct signed_significand_bits<MockFormatTraits>;



class SignedSignificandBitsTest_284 : public ::testing::Test {

protected:

    using SSB = signed_significand_bits<MockFormatTraits>;

    carrier_uint positive_value = 0b010101;

    carrier_uint negative_value = 0b110101;

};



TEST_F(SignedSignificandBitsTest_284, IsPositive_PositiveValue_ReturnsTrue_284) {

    SSB ssb(positive_value);

    EXPECT_TRUE(ssb.is_positive());

}



TEST_F(SignedSignificandBitsTest_284, IsPositive_NegativeValue_ReturnsFalse_284) {

    SSB ssb(negative_value);

    EXPECT_FALSE(ssb.is_positive());

}



TEST_F(SignedSignificandBitsTest_284, IsNegative_PositiveValue_ReturnsFalse_284) {

    SSB ssb(positive_value);

    EXPECT_FALSE(ssb.is_negative());

}



TEST_F(SignedSignificandBitsTest_284, IsNegative_NegativeValue_ReturnsTrue_284) {

    SSB ssb(negative_value);

    EXPECT_TRUE(ssb.is_negative());

}



TEST_F(SignedSignificandBitsTest_284, HasAllZeroSignificandBits_ZeroSignificand_ReturnsTrue_284) {

    carrier_uint zero_significand = 0;

    SSB ssb(zero_significand);

    EXPECT_TRUE(ssb.has_all_zero_significand_bits());

}



TEST_F(SignedSignificandBitsTest_284, HasAllZeroSignificandBits_NonZeroSignificand_ReturnsFalse_284) {

    SSB ssb(positive_value);

    EXPECT_FALSE(ssb.has_all_zero_significand_bits());

}



TEST_F(SignedSignificandBitsTest_284, HasEvenSignificandBits_EvenSignificand_ReturnsTrue_284) {

    carrier_uint even_significand = 0b010100;

    SSB ssb(even_significand);

    EXPECT_TRUE(ssb.has_even_significand_bits());

}



TEST_F(SignedSignificandBitsTest_284, HasEvenSignificandBits_OddSignificand_ReturnsFalse_284) {

    carrier_uint odd_significand = 0b010101;

    SSB ssb(odd_significand);

    EXPECT_FALSE(ssb.has_even_significand_bits());

}



TEST_F(SignedSignificandBitsTest_284, RemoveSignBitAndShift_PositiveValue_ReturnsCorrectValue_284) {

    SSB ssb(positive_value);

    carrier_uint expected = positive_value << 1;

    EXPECT_EQ(ssb.remove_sign_bit_and_shift(), expected);

}



TEST_F(SignedSignificandBitsTest_284, RemoveSignBitAndShift_NegativeValue_ReturnsCorrectValue_284) {

    SSB ssb(negative_value);

    carrier_uint expected = (negative_value & ((carrier_uint(1) << (sizeof(carrier_uint) * 8 - 1)) - 1)) << 1;

    EXPECT_EQ(ssb.remove_sign_bit_and_shift(), expected);

}

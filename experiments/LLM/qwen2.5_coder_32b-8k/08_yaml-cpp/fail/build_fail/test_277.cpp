#include <gtest/gtest.h>

#include "dragonbox.h"



using namespace YAML::jkj::dragonbox;



template<typename Format, typename CarrierUInt, typename ExponentInt>

class DragonboxTraitsTest : public ::testing::Test {

protected:

    using Traits = ieee754_binary_traits<Format, CarrierUInt, ExponentInt>;

};



typedef testing::Types<

    /* Define the actual types you want to test here */

    std::tuple<float, uint32_t, int>

> DragonboxTraitsTypes;



TYPED_TEST_SUITE(DragonboxTraitsTest, DragonboxTraitsTypes);



TYPED_TEST(DragonboxTraitsTest, IsNegative_PositiveValue_277) {

    using CarrierUInt = typename TypeParam::second_type;

    CarrierUInt positive_value = 1u; // Assuming the sign bit is the highest bit

    EXPECT_FALSE(Traits::is_negative(positive_value));

}



TYPED_TEST(DragonboxTraitsTest, IsNegative_NegativeValue_277) {

    using CarrierUInt = typename TypeParam::second_type;

    CarrierUInt negative_value = 0x80000000u; // Assuming the sign bit is the highest bit

    EXPECT_TRUE(Traits::is_negative(negative_value));

}



TYPED_TEST(DragonboxTraitsTest, IsNonzero_ZeroValue_277) {

    using CarrierUInt = typename TypeParam::second_type;

    CarrierUInt zero_value = 0u;

    EXPECT_FALSE(Traits::is_nonzero(zero_value));

}



TYPED_TEST(DragonboxTraitsTest, IsNonzero_NonzeroValue_277) {

    using CarrierUInt = typename TypeParam::second_type;

    CarrierUInt nonzero_value = 1u;

    EXPECT_TRUE(Traits::is_nonzero(nonzero_value));

}



TYPED_TEST(DragonboxTraitsTest, IsPositive_PositiveValue_277) {

    using CarrierUInt = typename TypeParam::second_type;

    CarrierUInt positive_value = 1u; // Assuming the sign bit is the highest bit

    EXPECT_TRUE(Traits::is_positive(positive_value));

}



TYPED_TEST(DragonboxTraitsTest, IsPositive_NegativeValue_277) {

    using CarrierUInt = typename TypeParam::second_type;

    CarrierUInt negative_value = 0x80000000u; // Assuming the sign bit is the highest bit

    EXPECT_FALSE(Traits::is_positive(negative_value));

}



TYPED_TEST(DragonboxTraitsTest, IsFinite_FiniteValue_277) {

    using ExponentInt = typename TypeParam::third_type;

    ExponentInt finite_exponent_bits = 10; // Assuming a valid exponent bit pattern for finite numbers

    EXPECT_TRUE(Traits::is_finite(finite_exponent_bits));

}



TYPED_TEST(DragonboxTraitsTest, IsFinite_InfValue_277) {

    using ExponentInt = typename TypeParam::third_type;

    ExponentInt inf_exponent_bits = 0xFF; // Assuming a valid exponent bit pattern for infinity

    EXPECT_FALSE(Traits::is_finite(inf_exponent_bits));

}



TYPED_TEST(DragonboxTraitsTest, HasAllZeroSignificandBits_ZeroSignificand_277) {

    using CarrierUInt = typename TypeParam::second_type;

    CarrierUInt zero_significand = 0u; // Assuming the significand bits are all zeros

    EXPECT_TRUE(Traits::has_all_zero_significand_bits(zero_significand));

}



TYPED_TEST(DragonboxTraitsTest, HasAllZeroSignificandBits_NonzeroSignificand_277) {

    using CarrierUInt = typename TypeParam::second_type;

    CarrierUInt nonzero_significand = 1u; // Assuming the significand bits are not all zeros

    EXPECT_FALSE(Traits::has_all_zero_significand_bits(nonzero_significand));

}



TYPED_TEST(DragonboxTraitsTest, HasEvenSignificandBits_EvenSignificand_277) {

    using CarrierUInt = typename TypeParam::second_type;

    CarrierUInt even_significand = 0xAAAAAAAu; // Assuming the significand bits are even

    EXPECT_TRUE(Traits::has_even_significand_bits(even_significand));

}



TYPED_TEST(DragonboxTraitsTest, HasEvenSignificandBits_OddSignificand_277) {

    using CarrierUInt = typename TypeParam::second_type;

    CarrierUInt odd_significand = 0x5555555u; // Assuming the significand bits are odd

    EXPECT_FALSE(Traits::has_even_significand_bits(odd_significand));

}

```



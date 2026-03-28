#include <gtest/gtest.h>

#include "dragonbox.h"



namespace YAML { namespace jkj { namespace dragonbox {



class Ieee754BinaryTraitsTest : public ::testing::Test {

protected:

    using Format = /* some_format_type */;

    using CarrierUInt = /* some_carrier_uint_type */;

    using ExponentInt = /* some_exponent_int_type */;

    using Traits = ieee754_binary_traits<Format, CarrierUInt, ExponentInt>;

};



TEST_F(Ieee754BinaryTraitsTest_278, IsFinite_NormalExponent_278) {

    ExponentInt exponent_bits = 10; // Example normal exponent

    EXPECT_TRUE(Traits::is_finite(exponent_bits));

}



TEST_F(Ieee754BinaryTraitsTest_278, IsFinite_MaxExponentMinusOne_278) {

    ExponentInt max_exponent = (ExponentInt(1) << Format::exponent_bits) - 2;

    EXPECT_TRUE(Traits::is_finite(max_exponent));

}



TEST_F(Ieee754BinaryTraitsTest_278, IsFinite_MaxExponent_278) {

    ExponentInt max_exponent = (ExponentInt(1) << Format::exponent_bits) - 1;

    EXPECT_FALSE(Traits::is_finite(max_exponent));

}



TEST_F(Ieee754BinaryTraitsTest_278, IsFinite_AllOnesExponent_278) {

    ExponentInt all_ones_exponent = ~ExponentInt(0);

    EXPECT_FALSE(Traits::is_finite(all_ones_exponent));

}



TEST_F(Ieee754BinaryTraitsTest_278, IsFinite_ZeroExponent_278) {

    ExponentInt zero_exponent = 0;

    EXPECT_TRUE(Traits::is_finite(zero_exponent));

}



}}} // namespace YAML::jkj::dragonbox

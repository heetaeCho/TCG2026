#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/yaml-cpp/src/contrib/dragonbox.h"



namespace YAML { namespace jkj { namespace dragonbox {



class DragonboxTest_273 : public ::testing::Test {

protected:

    using Format = /* specify appropriate format type */;

    using CarrierUInt = /* specify appropriate carrier uint type */;

    using ExponentInt = /* specify appropriate exponent int type */;

    using Traits = ieee754_binary_traits<Format, CarrierUInt, ExponentInt>;

};



TEST_F(DragonboxTest_273, BinaryExponent_ZeroExponentBits_ReturnsMinExponent_273) {

    ExponentInt result = Traits::binary_exponent(0);

    EXPECT_EQ(result, Format::min_exponent);

}



TEST_F(DragonboxTest_273, BinaryExponent_NonZeroExponentBits_ReturnsCorrectValue_273) {

    ExponentInt exponent_bits = 10;

    ExponentInt expected_result = exponent_bits + Format::exponent_bias;

    ExponentInt result = Traits::binary_exponent(exponent_bits);

    EXPECT_EQ(result, expected_result);

}



TEST_F(DragonboxTest_273, BinaryExponent_MaxExponentBits_ReturnsCorrectValue_273) {

    ExponentInt exponent_bits = std::numeric_limits<ExponentInt>::max();

    ExponentInt expected_result = exponent_bits + Format::exponent_bias;

    ExponentInt result = Traits::binary_exponent(exponent_bits);

    EXPECT_EQ(result, expected_result);

}



TEST_F(DragonboxTest_273, BinaryExponent_BoundaryConditionMin_ReturnsCorrectValue_273) {

    ExponentInt exponent_bits = Format::min_exponent - Format::exponent_bias;

    ExponentInt result = Traits::binary_exponent(exponent_bits);

    EXPECT_EQ(result, Format::min_exponent);

}



TEST_F(DragonboxTest_273, BinaryExponent_BoundaryConditionMax_ReturnsCorrectValue_273) {

    ExponentInt exponent_bits = Format::max_exponent - Format::exponent_bias;

    ExponentInt expected_result = Format::max_exponent;

    ExponentInt result = Traits::binary_exponent(exponent_bits);

    EXPECT_EQ(result, expected_result);

}



}}}  // namespace YAML::jkj::dragonbox

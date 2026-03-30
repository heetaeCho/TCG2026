#include <gtest/gtest.h>

#include "./TestProjects/yaml-cpp/src/contrib/dragonbox.h"



using namespace YAML::jkj::dragonbox::policy::binary_to_decimal_rounding;



TEST_F(DragonBoxPolicyTests_386, PreferRoundDown_OddSignificand_ReturnsTrue_386) {

    EXPECT_TRUE(to_even_t::prefer_round_down<uint32_t>(1));

}



TEST_F(DragonBoxPolicyTests_386, PreferRoundDown_EvenSignificand_ReturnsFalse_386) {

    EXPECT_FALSE(to_even_t::prefer_round_down<uint32_t>(2));

}



TEST_F(DragonBoxPolicyTests_386, PreferRoundDown_ZeroSignificand_ReturnsFalse_386) {

    EXPECT_FALSE(to_even_t::prefer_round_down<uint32_t>(0));

}



TEST_F(DragonBoxPolicyTests_386, PreferRoundDown_MaxOddSignificand_ReturnsTrue_386) {

    EXPECT_TRUE(to_even_t::prefer_round_down<uint32_t>(std::numeric_limits<uint32_t>::max() - 1));

}



TEST_F(DragonBoxPolicyTests_386, PreferRoundDown_MaxEvenSignificand_ReturnsFalse_386) {

    EXPECT_FALSE(to_even_t::prefer_round_down<uint32_t>(std::numeric_limits<uint32_t>::max()));

}

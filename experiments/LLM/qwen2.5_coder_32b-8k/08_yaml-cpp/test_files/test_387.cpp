#include <gtest/gtest.h>

#include "dragonbox.h"



namespace YAML { namespace jkj { namespace dragonbox { namespace policy { namespace binary_to_decimal_rounding {



class ToOddTTest_387 : public ::testing::Test {

protected:

    using CarrierUInt = uint64_t;

    to_odd_t policy;

};



TEST_F(ToOddTTest_387, PreferRoundDown_EvenSignificand_387) {

    CarrierUInt significand = 2; // Even number

    EXPECT_FALSE(policy.prefer_round_down(significand));

}



TEST_F(ToOddTTest_387, PreferRoundDown_OddSignificand_387) {

    CarrierUInt significand = 1; // Odd number

    EXPECT_TRUE(policy.prefer_round_down(significand));

}



TEST_F(ToOddTTest_387, PreferRoundDown_ZeroSignificand_387) {

    CarrierUInt significand = 0; // Edge case: zero is considered even

    EXPECT_FALSE(policy.prefer_round_down(significand));

}



TEST_F(ToOddTTest_387, PreferRoundDown_MaxEvenSignificand_387) {

    CarrierUInt significand = std::numeric_limits<CarrierUInt>::max() & ~CarrierUInt{1}; // Max even number

    EXPECT_FALSE(policy.prefer_round_down(significand));

}



TEST_F(ToOddTTest_387, PreferRoundDown_MaxOddSignificand_387) {

    CarrierUInt significand = std::numeric_limits<CarrierUInt>::max(); // Max odd number

    EXPECT_TRUE(policy.prefer_round_down(significand));

}



}}}}} // namespace YAML::jkj::dragonbox::policy::binary_to_decimal_rounding

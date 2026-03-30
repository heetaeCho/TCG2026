#include <gtest/gtest.h>

#include "dragonbox.h"



using namespace YAML::jkj::dragonbox;



class FloatBitsTest_299 : public ::testing::Test {

protected:

    using FormatTraits = /* specify appropriate format traits type */;

    using FloatBits = float_bits<FormatTraits>;



    FloatBits finite_positive;

    FloatBits finite_negative;

    FloatBits zero;

    FloatBits inf;

    FloatBits nan;



    void SetUp() override {

        // Initialize with appropriate bit patterns for different cases

        // This is a placeholder, replace with actual bit patterns

        finite_positive = FloatBits(/* bit pattern for a positive finite number */);

        finite_negative = FloatBits(/* bit pattern for a negative finite number */);

        zero = FloatBits(/* bit pattern for zero */);

        inf = FloatBits(/* bit pattern for infinity */);

        nan = FloatBits(/* bit pattern for NaN */);

    }

};



TEST_F(FloatBitsTest_299, IsFinite_PositiveFiniteNumber_299) {

    EXPECT_TRUE(finite_positive.is_finite());

}



TEST_F(FloatBitsTest_299, IsFinite_NegativeFiniteNumber_299) {

    EXPECT_TRUE(finite_negative.is_finite());

}



TEST_F(FloatBitsTest_299, IsFinite_Zero_299) {

    EXPECT_TRUE(zero.is_finite());

}



TEST_F(FloatBitsTest_299, IsFinite_Infinity_299) {

    EXPECT_FALSE(inf.is_finite());

}



TEST_F(FloatBitsTest_299, IsFinite_NaN_299) {

    EXPECT_FALSE(nan.is_finite());

}

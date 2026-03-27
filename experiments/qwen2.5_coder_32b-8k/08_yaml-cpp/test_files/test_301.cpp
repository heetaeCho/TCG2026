#include <gtest/gtest.h>

#include "dragonbox.h"



namespace YAML { namespace jkj { namespace dragonbox {



class DragonboxTest_301 : public ::testing::Test {

protected:

    // Add any necessary setup or teardown here if needed.

};



// Test normal operation with a positive float value

TEST_F(DragonboxTest_301, MakeFloatBits_PositiveValue_301) {

    auto result = make_float_bits<float>(42.5f);

    EXPECT_EQ(result.carrier, 0x42280000); // Known bit representation for 42.5f

}



// Test normal operation with a negative float value

TEST_F(DragonboxTest_301, MakeFloatBits_NegativeValue_301) {

    auto result = make_float_bits<float>(-42.5f);

    EXPECT_EQ(result.carrier, 0xC2280000); // Known bit representation for -42.5f

}



// Test normal operation with zero value

TEST_F(DragonboxTest_301, MakeFloatBits_ZeroValue_301) {

    auto result = make_float_bits<float>(0.0f);

    EXPECT_EQ(result.carrier, 0x00000000); // Known bit representation for 0.0f

}



// Test boundary condition with the smallest positive normalized float value

TEST_F(DragonboxTest_301, MakeFloatBits_SmallestPositiveNormalized_301) {

    auto result = make_float_bits<float>(std::numeric_limits<float>::min());

    EXPECT_EQ(result.carrier, 0x00800000); // Known bit representation for the smallest positive normalized float

}



// Test boundary condition with the largest finite float value

TEST_F(DragonboxTest_301, MakeFloatBits_LargestFiniteValue_301) {

    auto result = make_float_bits<float>(std::numeric_limits<float>::max());

    EXPECT_EQ(result.carrier, 0x7F7FFFFF); // Known bit representation for the largest finite float

}



// Test boundary condition with infinity

TEST_F(DragonboxTest_301, MakeFloatBits_InfinityValue_301) {

    auto result = make_float_bits<float>(std::numeric_limits<float>::infinity());

    EXPECT_EQ(result.carrier, 0x7F800000); // Known bit representation for positive infinity

}



// Test boundary condition with negative infinity

TEST_F(DragonboxTest_301, MakeFloatBits_NegativeInfinityValue_301) {

    auto result = make_float_bits<float>(-std::numeric_limits<float>::infinity());

    EXPECT_EQ(result.carrier, 0xFF800000); // Known bit representation for negative infinity

}



// Test boundary condition with NaN (Not a Number)

TEST_F(DragonboxTest_301, MakeFloatBits_NaNValue_301) {

    auto result = make_float_bits<float>(std::numeric_limits<float>::quiet_NaN());

    EXPECT_NE(result.carrier, 0x7F800000); // NaN has a specific pattern but can vary

    EXPECT_NE(result.carrier, 0xFF800000);

}



} } }

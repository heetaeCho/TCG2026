#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "dragonbox.h"



using namespace YAML::jkj::dragonbox;



// Mocking Format and CarrierUInt for demonstration purposes

struct MockFormat {

    static constexpr int significand_bits = 52;

};



using carrier_uint = uint64_t;

using exponent_int = int16_t;



TEST_F(DragonboxTest_270, ExtractSignificandBits_NormalOperation_270) {

    ieee754_binary_traits<MockFormat, carrier_uint, exponent_int> traits;

    carrier_uint input = 0x123456789ABCDEF0;

    carrier_uint expected_output = 0x9ABCDEF0; // Lower 52 bits of the input

    EXPECT_EQ(traits.extract_significand_bits(input), expected_output);

}



TEST_F(DragonboxTest_270, ExtractSignificandBits_BoundaryCondition_AllOnes_270) {

    ieee754_binary_traits<MockFormat, carrier_uint, exponent_int> traits;

    carrier_uint input = 0xFFFFFFFFFFFFFFFF;

    carrier_uint expected_output = (1ULL << MockFormat::significand_bits) - 1; // All ones in lower 52 bits

    EXPECT_EQ(traits.extract_significand_bits(input), expected_output);

}



TEST_F(DragonboxTest_270, ExtractSignificandBits_BoundaryCondition_AllZeros_270) {

    ieee754_binary_traits<MockFormat, carrier_uint, exponent_int> traits;

    carrier_uint input = 0x0;

    carrier_uint expected_output = 0x0; // All zeros

    EXPECT_EQ(traits.extract_significand_bits(input), expected_output);

}



TEST_F(DragonboxTest_270, ExtractSignificandBits_BoundaryCondition_TopBitSet_270) {

    ieee754_binary_traits<MockFormat, carrier_uint, exponent_int> traits;

    carrier_uint input = 0x8000000000000000; // Top bit set

    carrier_uint expected_output = 0x0; // Lower 52 bits are zero

    EXPECT_EQ(traits.extract_significand_bits(input), expected_output);

}

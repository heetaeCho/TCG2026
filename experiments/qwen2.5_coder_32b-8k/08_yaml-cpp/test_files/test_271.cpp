#include <gtest/gtest.h>

#include "dragonbox.h"



using namespace YAML::jkj::dragonbox;



// Mocking template parameters for testing

struct MockFormat {

    static constexpr int exponent_bits = 8;

    static constexpr int significand_bits = 23;

};



using TestTraits = ieee754_binary_traits<MockFormat, uint32_t, int>;



TEST_F(DragonBoxTest_271, RemoveExponentBits_NormalOperation_271) {

    uint32_t input = 0x12345678; // Example value

    uint32_t expected_output = 0x10000078; // Expected result after removing exponent bits

    EXPECT_EQ(TestTraits::remove_exponent_bits(input), expected_output);

}



TEST_F(DragonBoxTest_271, RemoveExponentBits_BoundaryCondition_MaxValue_271) {

    uint32_t input = 0xFFFFFFFF; // Maximum value for uint32_t

    uint32_t expected_output = 0x807FFFFF; // Expected result after removing exponent bits

    EXPECT_EQ(TestTraits::remove_exponent_bits(input), expected_output);

}



TEST_F(DragonBoxTest_271, RemoveExponentBits_BoundaryCondition_Zero_271) {

    uint32_t input = 0x0; // Zero value

    uint32_t expected_output = 0x0; // Expected result after removing exponent bits

    EXPECT_EQ(TestTraits::remove_exponent_bits(input), expected_output);

}



TEST_F(DragonBoxTest_271, RemoveExponentBits_ExceptionalCase_AllOnesInExponent_271) {

    uint32_t input = 0xFF800000; // All ones in exponent bits

    uint32_t expected_output = 0x80000000; // Expected result after removing exponent bits

    EXPECT_EQ(TestTraits::remove_exponent_bits(input), expected_output);

}

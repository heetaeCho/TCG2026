#include <gtest/gtest.h>



using namespace YAML::jkj::dragonbox;



// Assuming Format and CarrierUInt are defined somewhere in the actual implementation

// For testing purposes, we will mock these types

struct MockFormat {

    static constexpr int total_bits = 32; // Example value

};



using MockCarrierUInt = uint32_t;

using MockExponentInt = int32_t;



using TestTraits = ieee754_binary_traits<MockFormat, MockCarrierUInt, MockExponentInt>;



TEST_F(DragonboxTest_279, HasAllZeroSignificandBits_ZeroInput_279) {

    MockCarrierUInt input = 0;

    EXPECT_TRUE(TestTraits::has_all_zero_significand_bits(input));

}



TEST_F(DragonboxTest_279, HasAllZeroSignificandBits_NonZeroSignificand_279) {

    MockCarrierUInt input = 1; // Example non-zero significand

    EXPECT_FALSE(TestTraits::has_all_zero_significand_bits(input));

}



TEST_F(DragonboxTest_279, HasAllZeroSignificandBits_MaxExponent_279) {

    MockCarrierUInt input = (MockCarrierUInt(1) << (MockFormat::total_bits - 1)) - 1;

    EXPECT_TRUE(TestTraits::has_all_zero_significand_bits(input));

}



TEST_F(DragonboxTest_279, HasAllZeroSignificandBits_MaxExponentWithSign_279) {

    MockCarrierUInt input = (MockCarrierUInt(1) << (MockFormat::total_bits - 1)) - 1 | (MockCarrierUInt(1) << (MockFormat::total_bits - 1));

    EXPECT_TRUE(TestTraits::has_all_zero_significand_bits(input));

}



TEST_F(DragonboxTest_279, HasAllZeroSignificandBits_SignBitOnly_279) {

    MockCarrierUInt input = MockCarrierUInt(1) << (MockFormat::total_bits - 1);

    EXPECT_TRUE(TestTraits::has_all_zero_significand_bits(input));

}



TEST_F(DragonboxTest_279, HasAllZeroSignificandBits_MaxValue_279) {

    MockCarrierUInt input = ~MockCarrierUInt(0); // All bits set

    EXPECT_FALSE(TestTraits::has_all_zero_significand_bits(input));

}

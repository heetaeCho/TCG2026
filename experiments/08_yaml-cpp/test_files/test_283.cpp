#include <gtest/gtest.h>

#include "dragonbox.h"



namespace YAML { namespace jkj { namespace dragonbox {



class SignedSignificandBitsTest_283 : public ::testing::Test {

protected:

    using FormatTraits = /* specify appropriate format traits if needed */;

    using SSB = signed_significand_bits<FormatTraits>;

    carrier_uint testBitPattern;



    void SetUp() override {

        // Initialize with a default bit pattern for testing

        testBitPattern = 0b10101010101010101010101010101010;

    }

};



TEST_F(SignedSignificandBitsTest_283, RemoveSignBitAndShift_Positive_283) {

    SSB ssb(testBitPattern);

    carrier_uint result = ssb.remove_sign_bit_and_shift();

    EXPECT_EQ(result, 0b0101010101010101010101010101010);

}



TEST_F(SignedSignificandBitsTest_283, RemoveSignBitAndShift_Negative_283) {

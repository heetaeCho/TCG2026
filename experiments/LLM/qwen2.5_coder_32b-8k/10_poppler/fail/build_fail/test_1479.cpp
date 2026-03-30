#include <gtest/gtest.h>

#include "JArithmeticDecoder.h"



class JArithmeticDecoderTest_1479 : public ::testing::Test {

protected:

    JArithmeticDecoder decoder;

};



TEST_F(JArithmeticDecoderTest_1479, InitialByteCounterIsZero_1479) {

    EXPECT_EQ(decoder.getByteCounter(), 0U);

}



TEST_F(JArithmeticDecoderTest_1479, ResetByteCounterSetsToZero_1479) {

    decoder.resetByteCounter();

    EXPECT_EQ(decoder.getByteCounter(), 0U);

}



TEST_F(JArithmeticDecoderTest_1479, GetReadPastEndOfStreamInitiallyFalse_1479) {

    EXPECT_FALSE(decoder.getReadPastEndOfStream());

}

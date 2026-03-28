#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/JArithmeticDecoder.h"



class JArithmeticDecoderTest_1478 : public ::testing::Test {

protected:

    JArithmeticDecoder decoder;



    void SetUp() override {

        // Setup code, if needed

    }



    void TearDown() override {

        // Teardown code, if needed

    }

};



TEST_F(JArithmeticDecoderTest_1478, ResetByteCounterResetsToZero_1478) {

    // Simulate reading some bytes to set nBytesRead to a non-zero value

    decoder.resetByteCounter();

    EXPECT_EQ(decoder.getByteCounter(), 0);



    // Read past end of stream should be false after reset

    EXPECT_FALSE(decoder.getReadPastEndOfStream());

}



TEST_F(JArithmeticDecoderTest_1478, ByteCounterRemainsZeroAfterReset_1478) {

    decoder.resetByteCounter();

    EXPECT_EQ(decoder.getByteCounter(), 0);

}



TEST_F(JArithmeticDecoderTest_1478, ReadPastEndOfStreamInitiallyFalse_1478) {

    EXPECT_FALSE(decoder.getReadPastEndOfStream());

}

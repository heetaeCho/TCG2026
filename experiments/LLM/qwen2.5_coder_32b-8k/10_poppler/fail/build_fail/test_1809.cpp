#include <gtest/gtest.h>

#include "JBIG2Stream.h"

#include <gmock/gmock.h>



class JBIG2MMRDecoderTest_1809 : public ::testing::Test {

protected:

    JBIG2MMRDecoder* decoder;



    void SetUp() override {

        decoder = new JBIG2MMRDecoder();

    }



    void TearDown() override {

        delete decoder;

    }

};



TEST_F(JBIG2MMRDecoderTest_1809, ResetByteCounter_SetsCounterToZero_1809) {

    decoder->resetByteCounter();

    EXPECT_EQ(decoder->getByteCounter(), 0);

}



TEST_F(JBIG2MMRDecoderTest_1809, GetByteCounter_ReturnsCorrectCountAfterReset_1809) {

    decoder->resetByteCounter();

    unsigned int initialCount = decoder->getByteCounter();

    EXPECT_EQ(initialCount, 0);

}

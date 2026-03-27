#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "Stream.h"



using namespace testing;



class BaseSeekInputStreamTest : public Test {

protected:

    Goffset start = 0;

    bool limited = false;

    Goffset length = 16384;

    Object dict;

    std::unique_ptr<BaseSeekInputStream> stream;



    void SetUp() override {

        stream.reset(new BaseSeekInputStream(start, limited, length, std::move(dict)));

    }

};



TEST_F(BaseSeekInputStreamTest_134, LookChar_ReturnsEOF_AtEndOfBuffer_134) {

    // Assuming bufPtr is at the end of the buffer and fillBuf() returns false

    EXPECT_CALL(*stream, fillBuf()).WillOnce(Return(false));

    int result = stream->lookChar();

    EXPECT_EQ(result, EOF);

}



TEST_F(BaseSeekInputStreamTest_134, LookChar_ReturnsCorrectValue_AtStartOfBuffer_134) {

    // Assuming bufPtr is at the start of the buffer and fillBuf() returns true

    char testByte = 0x42;

    stream->bufPtr = &testByte;

    EXPECT_CALL(*stream, fillBuf()).WillOnce(Return(true));

    int result = stream->lookChar();

    EXPECT_EQ(result, static_cast<int>(static_cast<unsigned char>(testByte)));

}



TEST_F(BaseSeekInputStreamTest_134, LookChar_CallsFillBuf_WhenBufferIsEmpty_134) {

    // Assuming bufPtr is at the end of the buffer

    stream->bufPtr = stream->bufEnd;

    EXPECT_CALL(*stream, fillBuf()).WillOnce(Return(false));

    int result = stream->lookChar();

    EXPECT_EQ(result, EOF);

}



TEST_F(BaseSeekInputStreamTest_134, LookChar_ReturnsSameValue_OnSubsequentCallsWithinBuffer_134) {

    char testByte = 0x2A;

    stream->bufPtr = &testByte;

    EXPECT_CALL(*stream, fillBuf()).WillOnce(Return(true));

    int firstCall = stream->lookChar();

    int secondCall = stream->lookChar();

    EXPECT_EQ(firstCall, secondCall);

}



TEST_F(BaseSeekInputStreamTest_134, LookChar_DoesNotAdvanceBufferPointer_134) {

    char testByte = 0x2A;

    stream->bufPtr = &testByte;

    char* initialPtr = stream->bufPtr;

    EXPECT_CALL(*stream, fillBuf()).WillOnce(Return(true));

    int result = stream->lookChar();

    EXPECT_EQ(result, static_cast<int>(static_cast<unsigned char>(testByte)));

    EXPECT_EQ(stream->bufPtr, initialPtr);

}

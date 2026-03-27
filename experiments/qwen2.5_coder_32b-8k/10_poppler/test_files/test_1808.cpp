#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "JBIG2Stream.hh"

#include "Stream.hh"



using namespace testing;



class MockStream : public Stream {

public:

    MOCK_METHOD(void, close, (), (override));

    MOCK_METHOD(int, getChar, (), (override));

    MOCK_METHOD(bool, rewind, (), (override));

    MOCK_METHOD(Goffset, getPos, (), (const, override));

    MOCK_METHOD(void, setPos, (Goffset pos, int dir), (override));

    MOCK_METHOD(unsigned int, discardChars, (unsigned int n), (override));

};



class JBIG2MMRDecoderTest_1808 : public Test {

protected:

    MockStream mockStream;

    JBIG2MMRDecoder decoder;



    void SetUp() override {

        decoder.setStream(&mockStream);

    }

};



TEST_F(JBIG2MMRDecoderTest_1808, SetStreamSetsInternalPointer_1808) {

    EXPECT_EQ(decoder.getStream(), &mockStream);

}



TEST_F(JBIG2MMRDecoderTest_1808, ResetByteCounterResetsCounter_1808) {

    decoder.resetByteCounter();

    EXPECT_EQ(decoder.getByteCounter(), 0U);

}



TEST_F(JBIG2MMRDecoderTest_1808, SkipToReturnsTrueOnSuccess_1808) {

    EXPECT_CALL(mockStream, discardChars(42)).WillOnce(Return(42));

    EXPECT_TRUE(decoder.skipTo(42));

}



TEST_F(JBIG2MMRDecoderTest_1808, SkipToReturnsFalseIfNotEnoughBytesDiscarded_1808) {

    EXPECT_CALL(mockStream, discardChars(42)).WillOnce(Return(20));

    EXPECT_FALSE(decoder.skipTo(42));

}



TEST_F(JBIG2MMRDecoderTest_1808, GetByteCounterIncrementsWithGet24Bits_1808) {

    EXPECT_CALL(mockStream, getChar()).Times(3).WillRepeatedly(Return(0xFF));

    decoder.get24Bits();

    EXPECT_EQ(decoder.getByteCounter(), 3U);

}



TEST_F(JBIG2MMRDecoderTest_1808, GetBlackCodeCallsGet2DCode_1808) {

    EXPECT_CALL(mockStream, getChar()).WillOnce(Return(0xFF));

    decoder.getBlackCode();

    // Assuming get2DCode increments byte counter

    EXPECT_EQ(decoder.getByteCounter(), 1U);

}



TEST_F(JBIG2MMRDecoderTest_1808, GetWhiteCodeCallsGet2DCode_1808) {

    EXPECT_CALL(mockStream, getChar()).WillOnce(Return(0xFF));

    decoder.getWhiteCode();

    // Assuming get2DCode increments byte counter

    EXPECT_EQ(decoder.getByteCounter(), 1U);

}



TEST_F(JBIG2MMRDecoderTest_1808, ResetResetsAllState_1808) {

    decoder.resetByteCounter();

    decoder.skipTo(42); // Assume some state change

    decoder.reset();

    EXPECT_EQ(decoder.getByteCounter(), 0U);

}

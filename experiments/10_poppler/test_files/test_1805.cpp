#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "JBIG2Stream.cc"

#include "Stream.h"



using namespace testing;



class MockStream : public Stream {

public:

    MOCK_METHOD(void, setPos, (Goffset pos, int dir), (override));

    MOCK_METHOD(int, getChar, (), (override));

    MOCK_METHOD(bool, rewind, (), (override));

    MOCK_METHOD(void, close, (), (override));

};



class JBIG2HuffmanDecoderTest_1805 : public Test {

protected:

    std::unique_ptr<MockStream> mockStream;

    JBIG2HuffmanDecoder decoder;



    void SetUp() override {

        mockStream = std::make_unique<MockStream>();

        decoder.setStream(mockStream.get());

    }

};



TEST_F(JBIG2HuffmanDecoderTest_1805, SetStreamSetsInternalStreamPointer_1805) {

    EXPECT_NE(decoder.getByteCounter(), 0); // Assuming getByteCounter changes state when stream is set

    decoder.resetByteCounter();

    EXPECT_EQ(decoder.getByteCounter(), 0);

}



TEST_F(JBIG2HuffmanDecoderTest_1805, ResetResetsState_1805) {

    decoder.resetByteCounter();

    EXPECT_EQ(decoder.getByteCounter(), 0);

    // Assuming some state is changed after setting stream and calling readBits

    mockStream->setPos(0, 0);

    mockStream->getChar();

    EXPECT_CALL(*mockStream, getChar()).WillOnce(Return(1));

    unsigned int result = decoder.readBit();

    EXPECT_EQ(result, 1);

    decoder.reset();

    EXPECT_EQ(decoder.getByteCounter(), 0); // Assuming byte counter resets

}



TEST_F(JBIG2HuffmanDecoderTest_1805, ReadBitsReadsCorrectNumberOfBits_1805) {

    mockStream->setPos(0, 0);

    EXPECT_CALL(*mockStream, getChar()).WillOnce(Return(0b11001100)).WillOnce(Return(0b10101010));

    unsigned int result = decoder.readBits(8, nullptr);

    EXPECT_EQ(result, 0b11001100);

    result = decoder.readBits(4, nullptr);

    EXPECT_EQ(result, 0b1010);

}



TEST_F(JBIG2HuffmanDecoderTest_1805, ReadBitReadsSingleBit_1805) {

    mockStream->setPos(0, 0);

    EXPECT_CALL(*mockStream, getChar()).WillOnce(Return(0b11001100));

    unsigned int result = decoder.readBit();

    EXPECT_EQ(result, 1);

    result = decoder.readBit();

    EXPECT_EQ(result, 1);

}



TEST_F(JBIG2HuffmanDecoderTest_1805, RewindResetsStreamPosition_1805) {

    mockStream->setPos(0, 0);

    EXPECT_CALL(*mockStream, rewind()).WillOnce(Return(true));

    bool success = decoder.rewind();

    EXPECT_TRUE(success);

}



TEST_F(JBIG2HuffmanDecoderTest_1805, CloseClosesStream_1805) {

    mockStream->setPos(0, 0);

    EXPECT_CALL(*mockStream, close());

    decoder.close();

}

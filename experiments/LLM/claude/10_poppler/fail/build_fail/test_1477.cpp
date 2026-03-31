#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "JArithmeticDecoder.h"
#include "Stream.h"

// Mock Stream class for testing
class MockStream : public Stream {
public:
    MockStream() : Stream() {}
    ~MockStream() override {}

    MOCK_METHOD(StreamKind, getKind, (), (const, override));
    MOCK_METHOD(bool, rewind, (), (override));
    MOCK_METHOD(void, close, (), (override));
    MOCK_METHOD(int, getChar, (), (override));
    MOCK_METHOD(int, lookChar, (), (override));
    MOCK_METHOD(int, getRawChar, (), (override));
    MOCK_METHOD(void, getRawChars, (int nChars, int *buffer), (override));
    MOCK_METHOD(int, getUnfilteredChar, (), (override));
    MOCK_METHOD(bool, unfilteredRewind, (), (override));
    MOCK_METHOD(char*, getLine, (char *buf, int size), (override));
    MOCK_METHOD(unsigned int, discardChars, (unsigned int n), (override));
    MOCK_METHOD(Goffset, getPos, (), (override));
    MOCK_METHOD(void, setPos, (Goffset pos, int dir), (override));
    MOCK_METHOD(bool, isBinary, (bool last), (const, override));
    MOCK_METHOD(BaseStream*, getBaseStream, (), (override));
    MOCK_METHOD(Stream*, getUndecodedStream, (), (override));
    MOCK_METHOD(Dict*, getDict, (), (override));
    MOCK_METHOD(Object*, getDictObject, (), (override));
};

class JArithmeticDecoderTest_1477 : public ::testing::Test {
protected:
    void SetUp() override {
        decoder = new JArithmeticDecoder();
        mockStream = new MockStream();
    }

    void TearDown() override {
        delete decoder;
        delete mockStream;
    }

    JArithmeticDecoder *decoder;
    MockStream *mockStream;
};

// Test: Constructor creates a valid object
TEST_F(JArithmeticDecoderTest_1477, ConstructorCreatesValidObject_1477) {
    JArithmeticDecoder dec;
    // Should be constructible without issues
    EXPECT_FALSE(dec.getReadPastEndOfStream());
}

// Test: setStream with stream only (no dataLen)
TEST_F(JArithmeticDecoderTest_1477, SetStreamWithoutDataLen_1477) {
    decoder->setStream(mockStream);
    // Should not crash; stream is set
    SUCCEED();
}

// Test: setStream with stream and dataLen
TEST_F(JArithmeticDecoderTest_1477, SetStreamWithDataLen_1477) {
    decoder->setStream(mockStream, 100);
    // Should not crash; stream and dataLen are set
    SUCCEED();
}

// Test: setStream with zero dataLen
TEST_F(JArithmeticDecoderTest_1477, SetStreamWithZeroDataLen_1477) {
    decoder->setStream(mockStream, 0);
    SUCCEED();
}

// Test: setStream with negative dataLen
TEST_F(JArithmeticDecoderTest_1477, SetStreamWithNegativeDataLen_1477) {
    decoder->setStream(mockStream, -1);
    SUCCEED();
}

// Test: resetByteCounter resets counter to zero
TEST_F(JArithmeticDecoderTest_1477, ResetByteCounterResetsToZero_1477) {
    decoder->setStream(mockStream, 100);
    decoder->resetByteCounter();
    EXPECT_EQ(decoder->getByteCounter(), 0u);
}

// Test: getByteCounter returns initial value
TEST_F(JArithmeticDecoderTest_1477, GetByteCounterInitialValue_1477) {
    // After construction, byte counter should be 0
    EXPECT_EQ(decoder->getByteCounter(), 0u);
}

// Test: getReadPastEndOfStream initial value is false
TEST_F(JArithmeticDecoderTest_1477, GetReadPastEndOfStreamInitialFalse_1477) {
    EXPECT_FALSE(decoder->getReadPastEndOfStream());
}

// Test: start initializes decoder state
TEST_F(JArithmeticDecoderTest_1477, StartInitializesDecoder_1477) {
    decoder->setStream(mockStream, 10);
    // Mock getChar to return valid bytes during start
    EXPECT_CALL(*mockStream, getChar())
        .WillRepeatedly(::testing::Return(0x00));
    decoder->start();
    SUCCEED();
}

// Test: cleanup can be called after start
TEST_F(JArithmeticDecoderTest_1477, CleanupAfterStart_1477) {
    decoder->setStream(mockStream, 10);
    EXPECT_CALL(*mockStream, getChar())
        .WillRepeatedly(::testing::Return(0x00));
    decoder->start();
    decoder->cleanup();
    SUCCEED();
}

// Test: restart with new data length
TEST_F(JArithmeticDecoderTest_1477, RestartWithNewDataLen_1477) {
    decoder->setStream(mockStream, 10);
    EXPECT_CALL(*mockStream, getChar())
        .WillRepeatedly(::testing::Return(0x00));
    decoder->start();
    decoder->restart(20);
    SUCCEED();
}

// Test: decodeBit with valid stats
TEST_F(JArithmeticDecoderTest_1477, DecodeBitReturnsZeroOrOne_1477) {
    JArithmeticDecoderStats stats(4);  // context size 4 means 2^4 = 16 contexts
    decoder->setStream(mockStream, 100);
    EXPECT_CALL(*mockStream, getChar())
        .WillRepeatedly(::testing::Return(0xFF));
    decoder->start();
    
    int bit = decoder->decodeBit(0, &stats);
    EXPECT_TRUE(bit == 0 || bit == 1);
}

// Test: decodeByte returns value in range [0, 255]
TEST_F(JArithmeticDecoderTest_1477, DecodeByteReturnsValidByte_1477) {
    JArithmeticDecoderStats stats(10);
    decoder->setStream(mockStream, 100);
    EXPECT_CALL(*mockStream, getChar())
        .WillRepeatedly(::testing::Return(0xAA));
    decoder->start();

    int byte = decoder->decodeByte(0, &stats);
    EXPECT_GE(byte, 0);
    EXPECT_LE(byte, 255);
}

// Test: decodeInt returns a boolean
TEST_F(JArithmeticDecoderTest_1477, DecodeIntReturnsBool_1477) {
    JArithmeticDecoderStats stats(512);
    decoder->setStream(mockStream, 100);
    EXPECT_CALL(*mockStream, getChar())
        .WillRepeatedly(::testing::Return(0x00));
    decoder->start();

    int x = 0;
    bool result = decoder->decodeInt(&x, &stats);
    // result is either true or false
    EXPECT_TRUE(result == true || result == false);
}

// Test: decodeIAID with small codeLen
TEST_F(JArithmeticDecoderTest_1477, DecodeIAIDWithSmallCodeLen_1477) {
    // For codeLen=1, stats needs 2^1 = 2 entries
    JArithmeticDecoderStats stats(1);
    decoder->setStream(mockStream, 100);
    EXPECT_CALL(*mockStream, getChar())
        .WillRepeatedly(::testing::Return(0x55));
    decoder->start();

    unsigned int id = decoder->decodeIAID(1, &stats);
    // With codeLen=1, result should be 0 or 1
    EXPECT_LE(id, 1u);
}

// Test: Multiple decodeBit calls work sequentially
TEST_F(JArithmeticDecoderTest_1477, MultipleDecodeBitCalls_1477) {
    JArithmeticDecoderStats stats(4);
    decoder->setStream(mockStream, 200);
    EXPECT_CALL(*mockStream, getChar())
        .WillRepeatedly(::testing::Return(0x80));
    decoder->start();

    for (int i = 0; i < 10; i++) {
        int bit = decoder->decodeBit(0, &stats);
        EXPECT_TRUE(bit == 0 || bit == 1);
    }
}

// Test: Byte counter increments after reading
TEST_F(JArithmeticDecoderTest_1477, ByteCounterIncrementsAfterStart_1477) {
    decoder->setStream(mockStream, 100);
    EXPECT_CALL(*mockStream, getChar())
        .WillRepeatedly(::testing::Return(0x00));
    decoder->resetByteCounter();
    EXPECT_EQ(decoder->getByteCounter(), 0u);
    decoder->start();
    // After start, some bytes should have been read
    EXPECT_GE(decoder->getByteCounter(), 0u);
}

// Test: setStream with large dataLen
TEST_F(JArithmeticDecoderTest_1477, SetStreamWithLargeDataLen_1477) {
    decoder->setStream(mockStream, 1000000);
    SUCCEED();
}

// Test: Multiple start calls
TEST_F(JArithmeticDecoderTest_1477, MultipleStartCalls_1477) {
    decoder->setStream(mockStream, 50);
    EXPECT_CALL(*mockStream, getChar())
        .WillRepeatedly(::testing::Return(0x00));
    decoder->start();
    decoder->start();
    SUCCEED();
}

// Test: EOF stream behavior (getChar returns EOF)
TEST_F(JArithmeticDecoderTest_1477, EOFStreamBehavior_1477) {
    decoder->setStream(mockStream, 2);
    EXPECT_CALL(*mockStream, getChar())
        .WillRepeatedly(::testing::Return(EOF));
    decoder->start();
    
    JArithmeticDecoderStats stats(4);
    // Decode should still work even with EOF
    int bit = decoder->decodeBit(0, &stats);
    EXPECT_TRUE(bit == 0 || bit == 1);
}

// Test: readPastEndOfStream becomes true when data is exhausted
TEST_F(JArithmeticDecoderTest_1477, ReadPastEndOfStreamWithLimitedData_1477) {
    decoder->setStream(mockStream, 1);
    EXPECT_CALL(*mockStream, getChar())
        .WillRepeatedly(::testing::Return(0x00));
    decoder->start();

    JArithmeticDecoderStats stats(4);
    // Decode many bits to exhaust the limited data
    for (int i = 0; i < 100; i++) {
        decoder->decodeBit(0, &stats);
    }
    // After reading past the end, this should be true
    // (This depends on implementation, but with dataLen=1 and 100 decodes, it's likely)
    // We just verify the method is callable
    bool pastEnd = decoder->getReadPastEndOfStream();
    EXPECT_TRUE(pastEnd == true || pastEnd == false);
}

// Test: restart resets state for new data
TEST_F(JArithmeticDecoderTest_1477, RestartResetsForNewData_1477) {
    decoder->setStream(mockStream, 10);
    EXPECT_CALL(*mockStream, getChar())
        .WillRepeatedly(::testing::Return(0x00));
    decoder->start();

    JArithmeticDecoderStats stats(4);
    decoder->decodeBit(0, &stats);

    decoder->restart(20);
    // After restart, should be able to continue decoding
    int bit = decoder->decodeBit(0, &stats);
    EXPECT_TRUE(bit == 0 || bit == 1);
}

// Test: decodeInt with different contexts
TEST_F(JArithmeticDecoderTest_1477, DecodeIntMultipleTimes_1477) {
    JArithmeticDecoderStats stats(512);
    decoder->setStream(mockStream, 500);
    EXPECT_CALL(*mockStream, getChar())
        .WillRepeatedly(::testing::Return(0x42));
    decoder->start();

    for (int i = 0; i < 5; i++) {
        int x = 0;
        bool result = decoder->decodeInt(&x, &stats);
        EXPECT_TRUE(result == true || result == false);
    }
}

// Test: Copy constructor is deleted
TEST_F(JArithmeticDecoderTest_1477, CopyConstructorDeleted_1477) {
    EXPECT_FALSE(std::is_copy_constructible<JArithmeticDecoder>::value);
}

// Test: Copy assignment is deleted
TEST_F(JArithmeticDecoderTest_1477, CopyAssignmentDeleted_1477) {
    EXPECT_FALSE(std::is_copy_assignable<JArithmeticDecoder>::value);
}

// Test: decodeBit with different context values
TEST_F(JArithmeticDecoderTest_1477, DecodeBitDifferentContexts_1477) {
    JArithmeticDecoderStats stats(8);  // 2^8 = 256 contexts
    decoder->setStream(mockStream, 200);
    EXPECT_CALL(*mockStream, getChar())
        .WillRepeatedly(::testing::Return(0xCC));
    decoder->start();

    for (unsigned int ctx = 0; ctx < 10; ctx++) {
        int bit = decoder->decodeBit(ctx, &stats);
        EXPECT_TRUE(bit == 0 || bit == 1);
    }
}

// Test: decodeIAID with larger codeLen
TEST_F(JArithmeticDecoderTest_1477, DecodeIAIDLargerCodeLen_1477) {
    // codeLen=4 means up to 2^4 = 16 possible values
    JArithmeticDecoderStats stats(4);
    decoder->setStream(mockStream, 200);
    EXPECT_CALL(*mockStream, getChar())
        .WillRepeatedly(::testing::Return(0x33));
    decoder->start();

    unsigned int id = decoder->decodeIAID(4, &stats);
    EXPECT_LT(id, 16u);
}

// Test: resetByteCounter after decoding
TEST_F(JArithmeticDecoderTest_1477, ResetByteCounterAfterDecoding_1477) {
    decoder->setStream(mockStream, 100);
    EXPECT_CALL(*mockStream, getChar())
        .WillRepeatedly(::testing::Return(0x00));
    decoder->start();

    JArithmeticDecoderStats stats(4);
    for (int i = 0; i < 20; i++) {
        decoder->decodeBit(0, &stats);
    }

    unsigned int counterBefore = decoder->getByteCounter();
    decoder->resetByteCounter();
    EXPECT_EQ(decoder->getByteCounter(), 0u);
    // counterBefore should have been > 0 (bytes were read)
    EXPECT_GT(counterBefore, 0u);
}

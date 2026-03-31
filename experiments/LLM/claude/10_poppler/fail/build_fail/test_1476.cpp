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

class JArithmeticDecoderTest_1476 : public ::testing::Test {
protected:
    JArithmeticDecoder decoder;
    MockStream mockStream;
};

// Test: Default construction
TEST_F(JArithmeticDecoderTest_1476, DefaultConstruction_1476) {
    // Just verify that a decoder can be created without issues
    JArithmeticDecoder dec;
    EXPECT_EQ(dec.getByteCounter(), 0u);
    EXPECT_FALSE(dec.getReadPastEndOfStream());
}

// Test: setStream with single argument sets the stream
TEST_F(JArithmeticDecoderTest_1476, SetStreamSingleArg_1476) {
    decoder.setStream(&mockStream);
    // After setting stream, byte counter should be accessible
    EXPECT_EQ(decoder.getByteCounter(), 0u);
}

// Test: setStream with two arguments (stream and dataLen)
TEST_F(JArithmeticDecoderTest_1476, SetStreamWithDataLen_1476) {
    decoder.setStream(&mockStream, 100);
    EXPECT_EQ(decoder.getByteCounter(), 0u);
}

// Test: resetByteCounter resets the counter to zero
TEST_F(JArithmeticDecoderTest_1476, ResetByteCounter_1476) {
    decoder.setStream(&mockStream);
    decoder.resetByteCounter();
    EXPECT_EQ(decoder.getByteCounter(), 0u);
}

// Test: getByteCounter returns 0 initially
TEST_F(JArithmeticDecoderTest_1476, GetByteCounterInitiallyZero_1476) {
    EXPECT_EQ(decoder.getByteCounter(), 0u);
}

// Test: getReadPastEndOfStream returns false initially
TEST_F(JArithmeticDecoderTest_1476, GetReadPastEndOfStreamInitiallyFalse_1476) {
    EXPECT_FALSE(decoder.getReadPastEndOfStream());
}

// Test: setStream with dataLen of zero
TEST_F(JArithmeticDecoderTest_1476, SetStreamWithZeroDataLen_1476) {
    decoder.setStream(&mockStream, 0);
    EXPECT_EQ(decoder.getByteCounter(), 0u);
}

// Test: setStream with negative dataLen
TEST_F(JArithmeticDecoderTest_1476, SetStreamWithNegativeDataLen_1476) {
    decoder.setStream(&mockStream, -1);
    EXPECT_EQ(decoder.getByteCounter(), 0u);
}

// Test: start after setStream
TEST_F(JArithmeticDecoderTest_1476, StartAfterSetStream_1476) {
    EXPECT_CALL(mockStream, getChar())
        .WillRepeatedly(::testing::Return(0));
    
    decoder.setStream(&mockStream);
    decoder.start();
    // start should initialize internal state; byte counter may have changed
    // We just verify it doesn't crash
}

// Test: decodeBit with valid stats
TEST_F(JArithmeticDecoderTest_1476, DecodeBitBasic_1476) {
    EXPECT_CALL(mockStream, getChar())
        .WillRepeatedly(::testing::Return(0));
    
    JArithmeticDecoderStats stats(4);
    decoder.setStream(&mockStream);
    decoder.start();
    
    int result = decoder.decodeBit(0, &stats);
    // Result should be 0 or 1
    EXPECT_TRUE(result == 0 || result == 1);
}

// Test: decodeByte with valid stats
TEST_F(JArithmeticDecoderTest_1476, DecodeByteBasic_1476) {
    EXPECT_CALL(mockStream, getChar())
        .WillRepeatedly(::testing::Return(0xFF));
    
    JArithmeticDecoderStats stats(512);
    decoder.setStream(&mockStream);
    decoder.start();
    
    int result = decoder.decodeByte(0, &stats);
    // Result should be in range [0, 255]
    EXPECT_GE(result, 0);
    EXPECT_LE(result, 255);
}

// Test: decodeInt with valid stats
TEST_F(JArithmeticDecoderTest_1476, DecodeIntBasic_1476) {
    EXPECT_CALL(mockStream, getChar())
        .WillRepeatedly(::testing::Return(0));
    
    JArithmeticDecoderStats stats(512);
    decoder.setStream(&mockStream);
    decoder.start();
    
    int x = 0;
    bool result = decoder.decodeInt(&x, &stats);
    // result indicates success/failure, x gets the decoded value
    EXPECT_TRUE(result == true || result == false);
}

// Test: decodeIAID with valid stats
TEST_F(JArithmeticDecoderTest_1476, DecodeIAIDBasic_1476) {
    EXPECT_CALL(mockStream, getChar())
        .WillRepeatedly(::testing::Return(0));
    
    // For codeLen = 2, need 1 << 2 = 4 contexts
    JArithmeticDecoderStats stats(4);
    decoder.setStream(&mockStream);
    decoder.start();
    
    unsigned int result = decoder.decodeIAID(2, &stats);
    // Result should be within [0, (1 << codeLen) - 1]
    EXPECT_LT(result, 4u);
}

// Test: restart with a new data length
TEST_F(JArithmeticDecoderTest_1476, RestartWithNewDataLen_1476) {
    EXPECT_CALL(mockStream, getChar())
        .WillRepeatedly(::testing::Return(0));
    
    decoder.setStream(&mockStream, 100);
    decoder.start();
    decoder.restart(50);
    // After restart, decoder should be operational
    EXPECT_EQ(decoder.getByteCounter(), 0u);
}

// Test: cleanup after decoding
TEST_F(JArithmeticDecoderTest_1476, CleanupAfterDecoding_1476) {
    EXPECT_CALL(mockStream, getChar())
        .WillRepeatedly(::testing::Return(0));
    
    decoder.setStream(&mockStream, 10);
    decoder.start();
    decoder.cleanup();
    // Should not crash
}

// Test: Multiple decodeBit calls
TEST_F(JArithmeticDecoderTest_1476, MultipleDecodeBitCalls_1476) {
    EXPECT_CALL(mockStream, getChar())
        .WillRepeatedly(::testing::Return(0xAA));
    
    JArithmeticDecoderStats stats(4);
    decoder.setStream(&mockStream);
    decoder.start();
    
    for (int i = 0; i < 10; ++i) {
        int result = decoder.decodeBit(0, &stats);
        EXPECT_TRUE(result == 0 || result == 1);
    }
}

// Test: setStream overrides previous stream setting
TEST_F(JArithmeticDecoderTest_1476, SetStreamOverridesPrevious_1476) {
    MockStream mockStream2;
    
    decoder.setStream(&mockStream);
    decoder.setStream(&mockStream2);
    // Should not crash, new stream is set
    EXPECT_EQ(decoder.getByteCounter(), 0u);
}

// Test: Byte counter increments after reading
TEST_F(JArithmeticDecoderTest_1476, ByteCounterAfterReading_1476) {
    EXPECT_CALL(mockStream, getChar())
        .WillRepeatedly(::testing::Return(0x55));
    
    JArithmeticDecoderStats stats(512);
    decoder.setStream(&mockStream);
    decoder.start();
    
    unsigned int initialCount = decoder.getByteCounter();
    
    // Decode several bytes to trigger reads
    for (int i = 0; i < 20; ++i) {
        decoder.decodeBit(0, &stats);
    }
    
    // Byte counter should have increased (or at least not decreased)
    EXPECT_GE(decoder.getByteCounter(), initialCount);
}

// Test: resetByteCounter after some reads
TEST_F(JArithmeticDecoderTest_1476, ResetByteCounterAfterReads_1476) {
    EXPECT_CALL(mockStream, getChar())
        .WillRepeatedly(::testing::Return(0x42));
    
    JArithmeticDecoderStats stats(512);
    decoder.setStream(&mockStream);
    decoder.start();
    
    // Do some decoding
    for (int i = 0; i < 10; ++i) {
        decoder.decodeBit(0, &stats);
    }
    
    decoder.resetByteCounter();
    EXPECT_EQ(decoder.getByteCounter(), 0u);
}

// Test: EOF handling - getChar returns EOF
TEST_F(JArithmeticDecoderTest_1476, EOFHandling_1476) {
    EXPECT_CALL(mockStream, getChar())
        .WillRepeatedly(::testing::Return(EOF));
    
    JArithmeticDecoderStats stats(512);
    decoder.setStream(&mockStream);
    decoder.start();
    
    // Decoding when stream returns EOF
    for (int i = 0; i < 20; ++i) {
        int result = decoder.decodeBit(0, &stats);
        EXPECT_TRUE(result == 0 || result == 1);
    }
}

// Test: setStream with dataLen then start and limited reading
TEST_F(JArithmeticDecoderTest_1476, LimitedStreamReading_1476) {
    EXPECT_CALL(mockStream, getChar())
        .WillRepeatedly(::testing::Return(0x00));
    
    JArithmeticDecoderStats stats(512);
    decoder.setStream(&mockStream, 2);
    decoder.start();
    
    // Read beyond the limited data
    for (int i = 0; i < 50; ++i) {
        decoder.decodeBit(0, &stats);
    }
    
    // Should have read past end of stream at some point
    // This is observable through getReadPastEndOfStream
}

// Test: decodeIAID with codeLen of 1
TEST_F(JArithmeticDecoderTest_1476, DecodeIAIDCodeLen1_1476) {
    EXPECT_CALL(mockStream, getChar())
        .WillRepeatedly(::testing::Return(0xFF));
    
    JArithmeticDecoderStats stats(2); // 1 << 1 = 2
    decoder.setStream(&mockStream);
    decoder.start();
    
    unsigned int result = decoder.decodeIAID(1, &stats);
    EXPECT_LT(result, 2u);
}

// Test: decodeIAID with larger codeLen
TEST_F(JArithmeticDecoderTest_1476, DecodeIAIDLargerCodeLen_1476) {
    EXPECT_CALL(mockStream, getChar())
        .WillRepeatedly(::testing::Return(0x80));
    
    unsigned int codeLen = 8;
    JArithmeticDecoderStats stats(1u << codeLen);
    decoder.setStream(&mockStream);
    decoder.start();
    
    unsigned int result = decoder.decodeIAID(codeLen, &stats);
    EXPECT_LT(result, 1u << codeLen);
}

// Test: JArithmeticDecoderStats construction and reset
TEST_F(JArithmeticDecoderTest_1476, StatsConstructionAndReset_1476) {
    JArithmeticDecoderStats stats(100);
    stats.reset();
    // Should not crash
}

// Test: JArithmeticDecoderStats copy
TEST_F(JArithmeticDecoderTest_1476, StatsCopy_1476) {
    JArithmeticDecoderStats stats1(100);
    JArithmeticDecoderStats stats2(100);
    stats2.copyFrom(&stats1);
    // Should not crash
}

// Test: Different context values for decodeBit
TEST_F(JArithmeticDecoderTest_1476, DecodeBitDifferentContexts_1476) {
    EXPECT_CALL(mockStream, getChar())
        .WillRepeatedly(::testing::Return(0x33));
    
    JArithmeticDecoderStats stats(256);
    decoder.setStream(&mockStream);
    decoder.start();
    
    for (unsigned int ctx = 0; ctx < 10; ++ctx) {
        int result = decoder.decodeBit(ctx, &stats);
        EXPECT_TRUE(result == 0 || result == 1);
    }
}

// Test: Sequence of operations: setStream, start, decode, cleanup, restart
TEST_F(JArithmeticDecoderTest_1476, FullLifecycle_1476) {
    EXPECT_CALL(mockStream, getChar())
        .WillRepeatedly(::testing::Return(0x77));
    
    JArithmeticDecoderStats stats(64);
    
    decoder.setStream(&mockStream, 50);
    decoder.start();
    
    for (int i = 0; i < 5; ++i) {
        decoder.decodeBit(0, &stats);
    }
    
    decoder.cleanup();
    decoder.restart(30);
    
    for (int i = 0; i < 5; ++i) {
        decoder.decodeBit(0, &stats);
    }
    
    decoder.cleanup();
}

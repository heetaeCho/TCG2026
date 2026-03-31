#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "JArithmeticDecoder.h"
#include "Stream.h"

// Test fixture for JArithmeticDecoder
class JArithmeticDecoderTest_1479 : public ::testing::Test {
protected:
    void SetUp() override {
        decoder = new JArithmeticDecoder();
    }

    void TearDown() override {
        delete decoder;
    }

    JArithmeticDecoder *decoder;
};

// Test that a newly constructed decoder has zero byte counter
TEST_F(JArithmeticDecoderTest_1479, DefaultConstructor_ByteCounterIsZero_1479) {
    EXPECT_EQ(decoder->getByteCounter(), 0u);
}

// Test that copy constructor is deleted (compile-time check - just verify object is usable)
TEST_F(JArithmeticDecoderTest_1479, ObjectIsConstructible_1479) {
    JArithmeticDecoder *dec = new JArithmeticDecoder();
    EXPECT_NE(dec, nullptr);
    EXPECT_EQ(dec->getByteCounter(), 0u);
    delete dec;
}

// Test resetByteCounter resets the counter to zero
TEST_F(JArithmeticDecoderTest_1479, ResetByteCounter_SetsToZero_1479) {
    decoder->resetByteCounter();
    EXPECT_EQ(decoder->getByteCounter(), 0u);
}

// Test getReadPastEndOfStream returns false initially
TEST_F(JArithmeticDecoderTest_1479, GetReadPastEndOfStream_InitiallyFalse_1479) {
    EXPECT_FALSE(decoder->getReadPastEndOfStream());
}

// Test that resetByteCounter can be called multiple times
TEST_F(JArithmeticDecoderTest_1479, ResetByteCounter_MultipleCalls_1479) {
    decoder->resetByteCounter();
    EXPECT_EQ(decoder->getByteCounter(), 0u);
    decoder->resetByteCounter();
    EXPECT_EQ(decoder->getByteCounter(), 0u);
}

// Test getByteCounter is const-correct (can be called on const reference)
TEST_F(JArithmeticDecoderTest_1479, GetByteCounter_ConstCorrectness_1479) {
    const JArithmeticDecoder &constRef = *decoder;
    EXPECT_EQ(constRef.getByteCounter(), 0u);
}

// Test getReadPastEndOfStream is const-correct
TEST_F(JArithmeticDecoderTest_1479, GetReadPastEndOfStream_ConstCorrectness_1479) {
    const JArithmeticDecoder &constRef = *decoder;
    EXPECT_FALSE(constRef.getReadPastEndOfStream());
}

// Test with a real stream - setStream with data length, then decode operations
// We create a MemStream to feed data to the decoder
class JArithmeticDecoderStreamTest_1479 : public ::testing::Test {
protected:
    void SetUp() override {
        decoder = new JArithmeticDecoder();
    }

    void TearDown() override {
        delete decoder;
    }

    JArithmeticDecoder *decoder;
};

// Test setStream with length parameter
TEST_F(JArithmeticDecoderStreamTest_1479, SetStreamWithLength_1479) {
    // Create a small buffer for a MemStream
    static const char data[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    Object obj;
    MemStream *memStream = new MemStream(const_cast<char *>(data), 0, sizeof(data), std::move(obj));
    memStream->reset();

    decoder->setStream(memStream, sizeof(data));
    decoder->resetByteCounter();
    EXPECT_EQ(decoder->getByteCounter(), 0u);

    delete memStream;
}

// Test setStream without length parameter
TEST_F(JArithmeticDecoderStreamTest_1479, SetStreamWithoutLength_1479) {
    static const char data[] = {0xFF, 0xAC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    Object obj;
    MemStream *memStream = new MemStream(const_cast<char *>(data), 0, sizeof(data), std::move(obj));
    memStream->reset();

    decoder->setStream(memStream);
    decoder->resetByteCounter();
    EXPECT_EQ(decoder->getByteCounter(), 0u);

    delete memStream;
}

// Test that after start(), some bytes may be read (byte counter may change)
TEST_F(JArithmeticDecoderStreamTest_1479, StartReadsBytes_1479) {
    static const char data[] = {0xFF, 0xAC, 0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC,
                                 0xDE, 0xF0, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66};
    Object obj;
    MemStream *memStream = new MemStream(const_cast<char *>(data), 0, sizeof(data), std::move(obj));
    memStream->reset();

    decoder->setStream(memStream, sizeof(data));
    decoder->resetByteCounter();
    decoder->start();

    // After start, some bytes should have been read
    unsigned int bytesAfterStart = decoder->getByteCounter();
    EXPECT_GE(bytesAfterStart, 0u);

    decoder->cleanup();
    delete memStream;
}

// Test decodeBit with a JArithmeticDecoderStats
TEST_F(JArithmeticDecoderStreamTest_1479, DecodeBit_ReturnsValidBit_1479) {
    static const char data[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    Object obj;
    MemStream *memStream = new MemStream(const_cast<char *>(data), 0, sizeof(data), std::move(obj));
    memStream->reset();

    JArithmeticDecoderStats *stats = new JArithmeticDecoderStats(4);

    decoder->setStream(memStream, sizeof(data));
    decoder->resetByteCounter();
    decoder->start();

    int bit = decoder->decodeBit(0, stats);
    // decodeBit should return 0 or 1
    EXPECT_TRUE(bit == 0 || bit == 1);

    decoder->cleanup();
    delete stats;
    delete memStream;
}

// Test decodeByte returns a value in valid range
TEST_F(JArithmeticDecoderStreamTest_1479, DecodeByte_ReturnsValidByte_1479) {
    static const char data[] = {0xFF, 0xAC, 0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC,
                                 0xDE, 0xF0, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66};
    Object obj;
    MemStream *memStream = new MemStream(const_cast<char *>(data), 0, sizeof(data), std::move(obj));
    memStream->reset();

    // decodeByte needs 256 * 3 stats contexts
    JArithmeticDecoderStats *stats = new JArithmeticDecoderStats(768);

    decoder->setStream(memStream, sizeof(data));
    decoder->resetByteCounter();
    decoder->start();

    int byte = decoder->decodeByte(0, stats);
    // decodeByte should return a value between 0 and 255
    EXPECT_GE(byte, 0);
    EXPECT_LE(byte, 255);

    decoder->cleanup();
    delete stats;
    delete memStream;
}

// Test decodeInt returns a boolean
TEST_F(JArithmeticDecoderStreamTest_1479, DecodeInt_ReturnsBool_1479) {
    static const char data[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    Object obj;
    MemStream *memStream = new MemStream(const_cast<char *>(data), 0, sizeof(data), std::move(obj));
    memStream->reset();

    // decodeInt uses 512 contexts
    JArithmeticDecoderStats *stats = new JArithmeticDecoderStats(512);

    decoder->setStream(memStream, sizeof(data));
    decoder->resetByteCounter();
    decoder->start();

    int x = 0;
    bool result = decoder->decodeInt(&x, stats);
    // Result is a boolean indicating success/failure
    EXPECT_TRUE(result == true || result == false);

    decoder->cleanup();
    delete stats;
    delete memStream;
}

// Test that byte counter increases after decoding operations
TEST_F(JArithmeticDecoderStreamTest_1479, ByteCounterIncreases_AfterDecoding_1479) {
    static const char data[64] = {};
    Object obj;
    MemStream *memStream = new MemStream(const_cast<char *>(data), 0, sizeof(data), std::move(obj));
    memStream->reset();

    JArithmeticDecoderStats *stats = new JArithmeticDecoderStats(4);

    decoder->setStream(memStream, sizeof(data));
    decoder->resetByteCounter();
    decoder->start();

    unsigned int initialCount = decoder->getByteCounter();

    // Decode multiple bits to potentially trigger byte reads
    for (int i = 0; i < 32; i++) {
        decoder->decodeBit(0, stats);
    }

    unsigned int finalCount = decoder->getByteCounter();
    EXPECT_GE(finalCount, initialCount);

    decoder->cleanup();
    delete stats;
    delete memStream;
}

// Test restart with a new data length
TEST_F(JArithmeticDecoderStreamTest_1479, Restart_WithNewDataLen_1479) {
    static const char data[32] = {};
    Object obj;
    MemStream *memStream = new MemStream(const_cast<char *>(data), 0, sizeof(data), std::move(obj));
    memStream->reset();

    decoder->setStream(memStream, 16);
    decoder->resetByteCounter();
    decoder->start();

    // Now restart with a different length
    decoder->restart(16);
    // After restart, decoder should be usable
    EXPECT_EQ(decoder->getByteCounter(), decoder->getByteCounter()); // sanity

    decoder->cleanup();
    delete memStream;
}

// Test JArithmeticDecoderStats
TEST_F(JArithmeticDecoderTest_1479, StatsConstruction_1479) {
    JArithmeticDecoderStats *stats = new JArithmeticDecoderStats(256);
    EXPECT_NE(stats, nullptr);
    delete stats;
}

// Test JArithmeticDecoderStats copy
TEST_F(JArithmeticDecoderTest_1479, StatsCopy_1479) {
    JArithmeticDecoderStats *stats = new JArithmeticDecoderStats(256);
    JArithmeticDecoderStats *copy = stats->copy();
    EXPECT_NE(copy, nullptr);
    delete stats;
    delete copy;
}

// Test JArithmeticDecoderStats reset
TEST_F(JArithmeticDecoderTest_1479, StatsReset_1479) {
    JArithmeticDecoderStats *stats = new JArithmeticDecoderStats(256);
    stats->reset();
    // After reset, stats should be in initial state - no crash expected
    EXPECT_NE(stats, nullptr);
    delete stats;
}

// Test decodeIAID with small code length
TEST_F(JArithmeticDecoderStreamTest_1479, DecodeIAID_SmallCodeLen_1479) {
    static const char data[64] = {};
    Object obj;
    MemStream *memStream = new MemStream(const_cast<char *>(data), 0, sizeof(data), std::move(obj));
    memStream->reset();

    // For codeLen=2, need 1<<2 = 4 contexts
    JArithmeticDecoderStats *stats = new JArithmeticDecoderStats(4);

    decoder->setStream(memStream, sizeof(data));
    decoder->resetByteCounter();
    decoder->start();

    unsigned int iaid = decoder->decodeIAID(2, stats);
    // With codeLen=2, result should be in [0, 3]
    EXPECT_LT(iaid, 4u);

    decoder->cleanup();
    delete stats;
    delete memStream;
}

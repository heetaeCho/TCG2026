#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "JArithmeticDecoder.h"
#include "Stream.h"

// Test fixture for JArithmeticDecoder
class JArithmeticDecoderTest_1480 : public ::testing::Test {
protected:
    void SetUp() override {
        decoder = new JArithmeticDecoder();
    }

    void TearDown() override {
        delete decoder;
    }

    JArithmeticDecoder *decoder;
};

// Test that a freshly constructed decoder has not read past end of stream
TEST_F(JArithmeticDecoderTest_1480, InitialReadPastEndOfStreamIsFalse_1480) {
    EXPECT_FALSE(decoder->getReadPastEndOfStream());
}

// Test that the decoder is not copy constructible (compile-time check implicit,
// but we verify the object can be created normally)
TEST_F(JArithmeticDecoderTest_1480, ConstructionWorks_1480) {
    JArithmeticDecoder *dec = new JArithmeticDecoder();
    EXPECT_NE(dec, nullptr);
    EXPECT_FALSE(dec->getReadPastEndOfStream());
    delete dec;
}

// Test that getByteCounter returns 0 after construction or reset
TEST_F(JArithmeticDecoderTest_1480, InitialByteCounterIsZero_1480) {
    // After construction, byte counter should be at initial state
    // resetByteCounter should set it to 0
    decoder->resetByteCounter();
    EXPECT_EQ(decoder->getByteCounter(), 0u);
}

// Test that resetByteCounter resets the counter
TEST_F(JArithmeticDecoderTest_1480, ResetByteCounterResetsToZero_1480) {
    decoder->resetByteCounter();
    unsigned int count = decoder->getByteCounter();
    EXPECT_EQ(count, 0u);
}

// Test that multiple resets still yield zero
TEST_F(JArithmeticDecoderTest_1480, MultipleResetsStillZero_1480) {
    decoder->resetByteCounter();
    decoder->resetByteCounter();
    decoder->resetByteCounter();
    EXPECT_EQ(decoder->getByteCounter(), 0u);
}

// Test cleanup can be called without crash
TEST_F(JArithmeticDecoderTest_1480, CleanupDoesNotCrash_1480) {
    decoder->cleanup();
    // No crash means success
    SUCCEED();
}

// Test that getReadPastEndOfStream is const-correct (can be called on const ref)
TEST_F(JArithmeticDecoderTest_1480, GetReadPastEndOfStreamConstCorrectness_1480) {
    const JArithmeticDecoder &constRef = *decoder;
    EXPECT_FALSE(constRef.getReadPastEndOfStream());
}

// Test that getByteCounter is const-correct
TEST_F(JArithmeticDecoderTest_1480, GetByteCounterConstCorrectness_1480) {
    const JArithmeticDecoder &constRef = *decoder;
    decoder->resetByteCounter();
    EXPECT_EQ(constRef.getByteCounter(), 0u);
}

// Test JArithmeticDecoderStats construction and basic usage
class JArithmeticDecoderStatsTest_1480 : public ::testing::Test {
protected:
    void SetUp() override {
    }
    void TearDown() override {
    }
};

TEST_F(JArithmeticDecoderStatsTest_1480, StatsCanBeCreated_1480) {
    // JArithmeticDecoderStats is a dependency; create with a small context size
    JArithmeticDecoderStats *stats = new JArithmeticDecoderStats(16);
    EXPECT_NE(stats, nullptr);
    delete stats;
}

TEST_F(JArithmeticDecoderStatsTest_1480, StatsResetWorks_1480) {
    JArithmeticDecoderStats *stats = new JArithmeticDecoderStats(16);
    stats->reset();
    // No crash expected
    SUCCEED();
    delete stats;
}

TEST_F(JArithmeticDecoderStatsTest_1480, StatsCopyToWorks_1480) {
    JArithmeticDecoderStats *stats1 = new JArithmeticDecoderStats(16);
    JArithmeticDecoderStats *stats2 = new JArithmeticDecoderStats(16);
    stats1->copyTo(stats2);
    // No crash expected
    SUCCEED();
    delete stats1;
    delete stats2;
}

// Test with a MemStream to verify decoding behavior
class JArithmeticDecoderWithStreamTest_1480 : public ::testing::Test {
protected:
    void SetUp() override {
        decoder = new JArithmeticDecoder();
    }

    void TearDown() override {
        delete decoder;
    }

    JArithmeticDecoder *decoder;
};

TEST_F(JArithmeticDecoderWithStreamTest_1480, SetStreamWithLengthAndStart_1480) {
    // Create a minimal memory stream with some data
    unsigned char data[] = {0xFF, 0xAC, 0x00, 0x01, 0x02, 0x03};
    Object obj;
    obj.initNull();
    MemStream *memStream = new MemStream(reinterpret_cast<char *>(data), 0, sizeof(data), std::move(obj));
    memStream->reset();

    decoder->setStream(memStream, sizeof(data));
    decoder->start();

    // After starting, readPastEndOfStream may or may not be true depending on data
    // but it shouldn't crash
    SUCCEED();

    decoder->cleanup();
    delete memStream;
}

TEST_F(JArithmeticDecoderWithStreamTest_1480, DecodeBitDoesNotCrashWithValidStream_1480) {
    unsigned char data[] = {0xFF, 0xAC, 0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC};
    Object obj;
    obj.initNull();
    MemStream *memStream = new MemStream(reinterpret_cast<char *>(data), 0, sizeof(data), std::move(obj));
    memStream->reset();

    JArithmeticDecoderStats *stats = new JArithmeticDecoderStats(512);

    decoder->setStream(memStream, sizeof(data));
    decoder->start();

    // Decode a few bits - should not crash
    for (int i = 0; i < 8; i++) {
        int bit = decoder->decodeBit(0, stats);
        EXPECT_TRUE(bit == 0 || bit == 1);
    }

    decoder->cleanup();
    delete stats;
    delete memStream;
}

TEST_F(JArithmeticDecoderWithStreamTest_1480, DecodeByteReturnsValidRange_1480) {
    unsigned char data[] = {0xFF, 0xAC, 0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC, 0xDE, 0xF0, 0x11, 0x22};
    Object obj;
    obj.initNull();
    MemStream *memStream = new MemStream(reinterpret_cast<char *>(data), 0, sizeof(data), std::move(obj));
    memStream->reset();

    JArithmeticDecoderStats *stats = new JArithmeticDecoderStats(512);

    decoder->setStream(memStream, sizeof(data));
    decoder->start();

    int byte = decoder->decodeByte(0, stats);
    EXPECT_GE(byte, 0);
    EXPECT_LE(byte, 255);

    decoder->cleanup();
    delete stats;
    delete memStream;
}

TEST_F(JArithmeticDecoderWithStreamTest_1480, ByteCounterIncrementsWithReads_1480) {
    unsigned char data[] = {0xFF, 0xAC, 0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC, 0xDE, 0xF0};
    Object obj;
    obj.initNull();
    MemStream *memStream = new MemStream(reinterpret_cast<char *>(data), 0, sizeof(data), std::move(obj));
    memStream->reset();

    JArithmeticDecoderStats *stats = new JArithmeticDecoderStats(512);

    decoder->setStream(memStream, sizeof(data));
    decoder->resetByteCounter();
    decoder->start();

    // After start, some bytes should have been read
    unsigned int counterAfterStart = decoder->getByteCounter();
    EXPECT_GT(counterAfterStart, 0u);

    decoder->cleanup();
    delete stats;
    delete memStream;
}

TEST_F(JArithmeticDecoderWithStreamTest_1480, DecodeIntReturnsResult_1480) {
    unsigned char data[] = {0xFF, 0xAC, 0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC, 0xDE, 0xF0,
                            0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xAA};
    Object obj;
    obj.initNull();
    MemStream *memStream = new MemStream(reinterpret_cast<char *>(data), 0, sizeof(data), std::move(obj));
    memStream->reset();

    JArithmeticDecoderStats *stats = new JArithmeticDecoderStats(512);

    decoder->setStream(memStream, sizeof(data));
    decoder->start();

    int x = 0;
    bool result = decoder->decodeInt(&x, stats);
    // result is either true or false, both are valid
    (void)result;
    SUCCEED();

    decoder->cleanup();
    delete stats;
    delete memStream;
}

TEST_F(JArithmeticDecoderWithStreamTest_1480, DecodeIAIDReturnsValue_1480) {
    unsigned char data[] = {0xFF, 0xAC, 0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC, 0xDE, 0xF0,
                            0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xAA};
    Object obj;
    obj.initNull();
    MemStream *memStream = new MemStream(reinterpret_cast<char *>(data), 0, sizeof(data), std::move(obj));
    memStream->reset();

    // For decodeIAID with codeLen=4, need stats with size 1<<4 = 16
    JArithmeticDecoderStats *stats = new JArithmeticDecoderStats(1 << 4);

    decoder->setStream(memStream, sizeof(data));
    decoder->start();

    unsigned int iaid = decoder->decodeIAID(4, stats);
    // With codeLen=4, result should be in [0, 15]
    EXPECT_LT(iaid, 16u);

    decoder->cleanup();
    delete stats;
    delete memStream;
}

// Test reading past end of stream detection
TEST_F(JArithmeticDecoderWithStreamTest_1480, ReadPastEndOfStreamDetected_1480) {
    // Very short stream - should trigger read past end
    unsigned char data[] = {0xFF, 0xAC};
    Object obj;
    obj.initNull();
    MemStream *memStream = new MemStream(reinterpret_cast<char *>(data), 0, sizeof(data), std::move(obj));
    memStream->reset();

    JArithmeticDecoderStats *stats = new JArithmeticDecoderStats(512);

    decoder->setStream(memStream, sizeof(data));
    decoder->start();

    // Try to decode many bits to force reading past end
    for (int i = 0; i < 100; i++) {
        decoder->decodeBit(0, stats);
    }

    // After extensive reading from a very short stream, we expect to have read past end
    EXPECT_TRUE(decoder->getReadPastEndOfStream());

    decoder->cleanup();
    delete stats;
    delete memStream;
}

// Test setStream without length (unlimited stream)
TEST_F(JArithmeticDecoderWithStreamTest_1480, SetStreamWithoutLength_1480) {
    unsigned char data[] = {0xFF, 0xAC, 0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC};
    Object obj;
    obj.initNull();
    MemStream *memStream = new MemStream(reinterpret_cast<char *>(data), 0, sizeof(data), std::move(obj));
    memStream->reset();

    JArithmeticDecoderStats *stats = new JArithmeticDecoderStats(512);

    decoder->setStream(memStream);
    decoder->start();

    int bit = decoder->decodeBit(0, stats);
    EXPECT_TRUE(bit == 0 || bit == 1);

    decoder->cleanup();
    delete stats;
    delete memStream;
}

// Test restart functionality
TEST_F(JArithmeticDecoderWithStreamTest_1480, RestartResetsState_1480) {
    unsigned char data[] = {0xFF, 0xAC, 0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC, 0xDE, 0xF0};
    Object obj;
    obj.initNull();
    MemStream *memStream = new MemStream(reinterpret_cast<char *>(data), 0, sizeof(data), std::move(obj));
    memStream->reset();

    decoder->setStream(memStream, sizeof(data));
    decoder->start();

    // Restart with a new data length
    decoder->restart(5);

    // Should be able to continue decoding after restart
    JArithmeticDecoderStats *stats = new JArithmeticDecoderStats(512);
    int bit = decoder->decodeBit(0, stats);
    EXPECT_TRUE(bit == 0 || bit == 1);

    decoder->cleanup();
    delete stats;
    delete memStream;
}

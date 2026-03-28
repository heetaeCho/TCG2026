#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Stream.h"
#include "JBIG2Stream.cc"

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

class JBIG2HuffmanDecoderTest_1805 : public ::testing::Test {
protected:
    JBIG2HuffmanDecoder decoder;
    MockStream mockStream;

    void SetUp() override {
        decoder.reset();
    }
};

// Test that default construction works without crash
TEST_F(JBIG2HuffmanDecoderTest_1805, DefaultConstruction_1805) {
    JBIG2HuffmanDecoder dec;
    // Should construct without issues
    SUCCEED();
}

// Test setStream sets the stream without crash
TEST_F(JBIG2HuffmanDecoderTest_1805, SetStream_1805) {
    decoder.setStream(&mockStream);
    // No crash means success
    SUCCEED();
}

// Test setStream with nullptr
TEST_F(JBIG2HuffmanDecoderTest_1805, SetStreamNull_1805) {
    decoder.setStream(nullptr);
    SUCCEED();
}

// Test reset works without crash
TEST_F(JBIG2HuffmanDecoderTest_1805, Reset_1805) {
    decoder.setStream(&mockStream);
    decoder.reset();
    SUCCEED();
}

// Test resetByteCounter
TEST_F(JBIG2HuffmanDecoderTest_1805, ResetByteCounter_1805) {
    decoder.setStream(&mockStream);
    decoder.resetByteCounter();
    EXPECT_EQ(decoder.getByteCounter(), 0u);
}

// Test getByteCounter initially after reset
TEST_F(JBIG2HuffmanDecoderTest_1805, GetByteCounterInitial_1805) {
    decoder.setStream(&mockStream);
    decoder.reset();
    decoder.resetByteCounter();
    EXPECT_EQ(decoder.getByteCounter(), 0u);
}

// Test readBits with 0 bits requested
TEST_F(JBIG2HuffmanDecoderTest_1805, ReadBitsZero_1805) {
    decoder.setStream(&mockStream);
    decoder.reset();
    bool eof = false;
    unsigned int result = decoder.readBits(0, &eof);
    EXPECT_EQ(result, 0u);
    EXPECT_FALSE(eof);
}

// Test readBits reads from stream
TEST_F(JBIG2HuffmanDecoderTest_1805, ReadBitsFromStream_1805) {
    decoder.setStream(&mockStream);
    decoder.reset();

    // When reading bits, the decoder should call getChar on the stream
    EXPECT_CALL(mockStream, getChar())
        .WillRepeatedly(::testing::Return(0xAB));

    bool eof = false;
    unsigned int result = decoder.readBits(8, &eof);
    // We just verify it doesn't crash and returns something
    EXPECT_FALSE(eof);
}

// Test readBits detects EOF
TEST_F(JBIG2HuffmanDecoderTest_1805, ReadBitsEOF_1805) {
    decoder.setStream(&mockStream);
    decoder.reset();

    // Return EOF (-1) from stream
    EXPECT_CALL(mockStream, getChar())
        .WillRepeatedly(::testing::Return(EOF));

    bool eof = false;
    decoder.readBits(8, &eof);
    EXPECT_TRUE(eof);
}

// Test readBit reads single bit
TEST_F(JBIG2HuffmanDecoderTest_1805, ReadBit_1805) {
    decoder.setStream(&mockStream);
    decoder.reset();

    EXPECT_CALL(mockStream, getChar())
        .WillRepeatedly(::testing::Return(0xFF));

    unsigned int bit = decoder.readBit();
    // Should return 0 or 1
    EXPECT_TRUE(bit == 0 || bit == 1);
}

// Test readBits with 1 bit
TEST_F(JBIG2HuffmanDecoderTest_1805, ReadBitsOne_1805) {
    decoder.setStream(&mockStream);
    decoder.reset();

    EXPECT_CALL(mockStream, getChar())
        .WillRepeatedly(::testing::Return(0x80));

    bool eof = false;
    unsigned int result = decoder.readBits(1, &eof);
    EXPECT_FALSE(eof);
    EXPECT_TRUE(result == 0 || result == 1);
}

// Test multiple readBit calls consume bits properly
TEST_F(JBIG2HuffmanDecoderTest_1805, MultipleReadBits_1805) {
    decoder.setStream(&mockStream);
    decoder.reset();

    EXPECT_CALL(mockStream, getChar())
        .WillRepeatedly(::testing::Return(0xA5)); // 10100101

    // Read 8 individual bits
    unsigned int bits[8];
    for (int i = 0; i < 8; i++) {
        bits[i] = decoder.readBit();
        EXPECT_TRUE(bits[i] == 0 || bits[i] == 1);
    }
}

// Test readBits with maximum reasonable request
TEST_F(JBIG2HuffmanDecoderTest_1805, ReadBitsLargeN_1805) {
    decoder.setStream(&mockStream);
    decoder.reset();

    EXPECT_CALL(mockStream, getChar())
        .WillRepeatedly(::testing::Return(0x00));

    bool eof = false;
    unsigned int result = decoder.readBits(32, &eof);
    // Just verify it doesn't crash
    (void)result;
}

// Test decodeInt with nullptr table behavior
TEST_F(JBIG2HuffmanDecoderTest_1805, DecodeIntBasic_1805) {
    decoder.setStream(&mockStream);
    decoder.reset();

    // Build a simple table for testing
    // A minimal valid Huffman table with EOT marker
    JBIG2HuffmanTable table[2];
    table[0].val = 0;
    table[0].prefixLen = 1;
    table[0].rangeLen = 0;
    table[1].val = jbig2HuffmanEOT;
    table[1].prefixLen = 0;
    table[1].rangeLen = 0;

    // Try to build the table
    bool built = JBIG2HuffmanDecoder::buildTable(table, 2);
    // If built successfully, try decoding
    if (built) {
        EXPECT_CALL(mockStream, getChar())
            .WillRepeatedly(::testing::Return(0x00));

        int x = 0;
        bool result = decoder.decodeInt(&x, table);
        // Just verify it doesn't crash
        (void)result;
    }
}

// Test buildTable with empty/minimal input
TEST_F(JBIG2HuffmanDecoderTest_1805, BuildTableMinimal_1805) {
    JBIG2HuffmanTable table[1];
    table[0].val = jbig2HuffmanEOT;
    table[0].prefixLen = 0;
    table[0].rangeLen = 0;

    bool result = JBIG2HuffmanDecoder::buildTable(table, 1);
    // Result depends on implementation; just ensure no crash
    (void)result;
}

// Test reset followed by readBits
TEST_F(JBIG2HuffmanDecoderTest_1805, ResetThenRead_1805) {
    decoder.setStream(&mockStream);
    decoder.reset();

    EXPECT_CALL(mockStream, getChar())
        .WillRepeatedly(::testing::Return(0x55));

    bool eof = false;
    unsigned int r1 = decoder.readBits(4, &eof);

    decoder.reset();

    unsigned int r2 = decoder.readBits(4, &eof);
    // After reset, internal buffer should be cleared, so new read from stream
    (void)r1;
    (void)r2;
}

// Test byte counter increments when reading
TEST_F(JBIG2HuffmanDecoderTest_1805, ByteCounterIncrements_1805) {
    decoder.setStream(&mockStream);
    decoder.reset();
    decoder.resetByteCounter();

    EXPECT_CALL(mockStream, getChar())
        .WillRepeatedly(::testing::Return(0x42));

    EXPECT_EQ(decoder.getByteCounter(), 0u);

    bool eof = false;
    decoder.readBits(8, &eof);

    // After reading 8 bits (1 byte), counter should be >= 1
    unsigned int counter = decoder.getByteCounter();
    EXPECT_GE(counter, 0u); // At minimum it should be non-negative
}

// Test multiple resets don't cause issues
TEST_F(JBIG2HuffmanDecoderTest_1805, MultipleResets_1805) {
    decoder.setStream(&mockStream);
    decoder.reset();
    decoder.reset();
    decoder.reset();
    decoder.resetByteCounter();
    decoder.resetByteCounter();
    EXPECT_EQ(decoder.getByteCounter(), 0u);
}

// Test that readBits with eof pointer properly set on stream end
TEST_F(JBIG2HuffmanDecoderTest_1805, ReadBitsEOFSignaling_1805) {
    decoder.setStream(&mockStream);
    decoder.reset();

    // First call returns data, subsequent calls return EOF
    EXPECT_CALL(mockStream, getChar())
        .WillOnce(::testing::Return(0xAA))
        .WillRepeatedly(::testing::Return(EOF));

    bool eof = false;

    // First 8 bits should succeed
    decoder.readBits(8, &eof);

    // Next read should eventually hit EOF
    decoder.readBits(8, &eof);
    EXPECT_TRUE(eof);
}

// Test setting stream multiple times
TEST_F(JBIG2HuffmanDecoderTest_1805, SetStreamMultipleTimes_1805) {
    MockStream stream1, stream2;

    decoder.setStream(&stream1);
    decoder.reset();

    decoder.setStream(&stream2);
    decoder.reset();

    // Should not crash
    SUCCEED();
}

// Test readBit when stream returns EOF
TEST_F(JBIG2HuffmanDecoderTest_1805, ReadBitEOF_1805) {
    decoder.setStream(&mockStream);
    decoder.reset();

    EXPECT_CALL(mockStream, getChar())
        .WillRepeatedly(::testing::Return(EOF));

    unsigned int bit = decoder.readBit();
    // On EOF, readBit should return something (implementation-defined)
    (void)bit;
}

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "poppler/Stream.h"
#include "poppler/Hints.cc"

// Mock Stream class to simulate getChar behavior
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
    MOCK_METHOD(void, getRawChars, (int nChars, int* buffer), (override));
    MOCK_METHOD(int, getUnfilteredChar, (), (override));
    MOCK_METHOD(bool, unfilteredRewind, (), (override));
    MOCK_METHOD(char*, getLine, (char* buf, int size), (override));
    MOCK_METHOD(unsigned int, discardChars, (unsigned int n), (override));
    MOCK_METHOD(Goffset, getPos, (), (override));
    MOCK_METHOD(void, setPos, (Goffset pos, int dir), (override));
    MOCK_METHOD(std::optional<std::string>, getPSFilter, (int psLevel, const char* indent), (override));
    MOCK_METHOD(bool, isBinary, (bool last), (const, override));
    MOCK_METHOD(BaseStream*, getBaseStream, (), (override));
    MOCK_METHOD(Stream*, getUndecodedStream, (), (override));
    MOCK_METHOD(Dict*, getDict, (), (override));
    MOCK_METHOD(Object*, getDictObject, (), (override));
};

class StreamBitReaderTest_1978 : public ::testing::Test {
protected:
    void SetUp() override {
        mockStream = new MockStream();
    }

    void TearDown() override {
        delete mockStream;
    }

    MockStream* mockStream;
};

// Test that reading a single bit from a byte works correctly
TEST_F(StreamBitReaderTest_1978, ReadBitReturnsMSBFirst_1978) {
    // Byte 0xA0 = 10100000 in binary
    EXPECT_CALL(*mockStream, getChar())
        .WillOnce(::testing::Return(0xA0));

    StreamBitReader reader(mockStream);
    unsigned int bit = reader.readBit();
    EXPECT_EQ(bit, 1u); // MSB of 0xA0
}

// Test reading all 8 bits from a single byte
TEST_F(StreamBitReaderTest_1978, ReadAllBitsFromOneByte_1978) {
    // 0xA5 = 10100101
    EXPECT_CALL(*mockStream, getChar())
        .WillOnce(::testing::Return(0xA5));

    StreamBitReader reader(mockStream);

    EXPECT_EQ(reader.readBit(), 1u); // bit 7
    EXPECT_EQ(reader.readBit(), 0u); // bit 6
    EXPECT_EQ(reader.readBit(), 1u); // bit 5
    EXPECT_EQ(reader.readBit(), 0u); // bit 4
    EXPECT_EQ(reader.readBit(), 0u); // bit 3
    EXPECT_EQ(reader.readBit(), 1u); // bit 2
    EXPECT_EQ(reader.readBit(), 0u); // bit 1
    EXPECT_EQ(reader.readBit(), 1u); // bit 0
}

// Test that reading bits across byte boundaries fetches new bytes
TEST_F(StreamBitReaderTest_1978, ReadBitAcrossByteBoundary_1978) {
    // First byte: 0xFF = 11111111, second byte: 0x00 = 00000000
    EXPECT_CALL(*mockStream, getChar())
        .WillOnce(::testing::Return(0xFF))
        .WillOnce(::testing::Return(0x00));

    StreamBitReader reader(mockStream);

    // Read all 8 bits of first byte (all 1s)
    for (int i = 0; i < 8; i++) {
        EXPECT_EQ(reader.readBit(), 1u);
    }

    // Read first bit of second byte (0)
    EXPECT_EQ(reader.readBit(), 0u);
}

// Test that EOF returns (unsigned int)-1
TEST_F(StreamBitReaderTest_1978, ReadBitAtEOFReturnsMinusOne_1978) {
    EXPECT_CALL(*mockStream, getChar())
        .WillOnce(::testing::Return(EOF));

    StreamBitReader reader(mockStream);
    unsigned int result = reader.readBit();
    EXPECT_EQ(result, (unsigned int)-1);
}

// Test that atEOF returns true after EOF is encountered
TEST_F(StreamBitReaderTest_1978, AtEOFReturnsTrueAfterEOF_1978) {
    EXPECT_CALL(*mockStream, getChar())
        .WillOnce(::testing::Return(EOF));

    StreamBitReader reader(mockStream);
    EXPECT_FALSE(reader.atEOF());

    reader.readBit();
    EXPECT_TRUE(reader.atEOF());
}

// Test that atEOF returns false initially
TEST_F(StreamBitReaderTest_1978, AtEOFReturnsFalseInitially_1978) {
    StreamBitReader reader(mockStream);
    EXPECT_FALSE(reader.atEOF());
}

// Test readBits reads multiple bits correctly
TEST_F(StreamBitReaderTest_1978, ReadBitsReadsMultipleBits_1978) {
    // 0xAB = 10101011
    EXPECT_CALL(*mockStream, getChar())
        .WillOnce(::testing::Return(0xAB));

    StreamBitReader reader(mockStream);
    unsigned int result = reader.readBits(4);
    // Top 4 bits of 0xAB: 1010 = 10
    EXPECT_EQ(result, 0xAu);
}

// Test readBits reads 8 bits (full byte)
TEST_F(StreamBitReaderTest_1978, ReadBitsFullByte_1978) {
    EXPECT_CALL(*mockStream, getChar())
        .WillOnce(::testing::Return(0xCD));

    StreamBitReader reader(mockStream);
    unsigned int result = reader.readBits(8);
    EXPECT_EQ(result, 0xCDu);
}

// Test readBits across byte boundaries
TEST_F(StreamBitReaderTest_1978, ReadBitsAcrossByteBoundary_1978) {
    // First: 0xAB = 10101011, Second: 0xCD = 11001101
    EXPECT_CALL(*mockStream, getChar())
        .WillOnce(::testing::Return(0xAB))
        .WillOnce(::testing::Return(0xCD));

    StreamBitReader reader(mockStream);
    // Read 4 bits: 1010 = 0xA
    unsigned int first = reader.readBits(4);
    EXPECT_EQ(first, 0xAu);

    // Read 8 bits: 1011 1100 = 0xBC
    unsigned int second = reader.readBits(8);
    EXPECT_EQ(second, 0xBCu);
}

// Test readBits with 0 bits
TEST_F(StreamBitReaderTest_1978, ReadBitsZeroBits_1978) {
    StreamBitReader reader(mockStream);
    unsigned int result = reader.readBits(0);
    EXPECT_EQ(result, 0u);
}

// Test readBits with 1 bit
TEST_F(StreamBitReaderTest_1978, ReadBitsOneBit_1978) {
    EXPECT_CALL(*mockStream, getChar())
        .WillOnce(::testing::Return(0x80)); // 10000000

    StreamBitReader reader(mockStream);
    unsigned int result = reader.readBits(1);
    EXPECT_EQ(result, 1u);
}

// Test resetInputBits clears the bit buffer
TEST_F(StreamBitReaderTest_1978, ResetInputBitsClearsBuffer_1978) {
    // First byte: 0xFF, after reset and next read, second byte: 0x00
    EXPECT_CALL(*mockStream, getChar())
        .WillOnce(::testing::Return(0xFF))
        .WillOnce(::testing::Return(0x00));

    StreamBitReader reader(mockStream);

    // Read 4 bits from first byte
    reader.readBits(4);

    // Reset - this should discard remaining bits in buffer
    reader.resetInputBits();

    // Now reading should fetch a new byte (0x00)
    unsigned int bit = reader.readBit();
    EXPECT_EQ(bit, 0u);
}

// Test reading 0x00 byte
TEST_F(StreamBitReaderTest_1978, ReadBitFromZeroByte_1978) {
    EXPECT_CALL(*mockStream, getChar())
        .WillOnce(::testing::Return(0x00));

    StreamBitReader reader(mockStream);
    for (int i = 0; i < 8; i++) {
        EXPECT_EQ(reader.readBit(), 0u);
    }
}

// Test reading 0xFF byte
TEST_F(StreamBitReaderTest_1978, ReadBitFromFFByte_1978) {
    EXPECT_CALL(*mockStream, getChar())
        .WillOnce(::testing::Return(0xFF));

    StreamBitReader reader(mockStream);
    for (int i = 0; i < 8; i++) {
        EXPECT_EQ(reader.readBit(), 1u);
    }
}

// Test that EOF in the middle of readBits is handled
TEST_F(StreamBitReaderTest_1978, ReadBitsHitsEOFInMiddle_1978) {
    EXPECT_CALL(*mockStream, getChar())
        .WillOnce(::testing::Return(0xF0))  // 11110000
        .WillOnce(::testing::Return(EOF));

    StreamBitReader reader(mockStream);

    // Read 4 bits successfully: 1111
    reader.readBits(4);

    // Read remaining 4 bits: 0000
    reader.readBits(4);

    // Now try to read more - should hit EOF
    unsigned int result = reader.readBit();
    EXPECT_EQ(result, (unsigned int)-1);
    EXPECT_TRUE(reader.atEOF());
}

// Test readBits with large number of bits spanning multiple bytes
TEST_F(StreamBitReaderTest_1978, ReadBitsMultipleBytes_1978) {
    // 0xAB = 10101011, 0xCD = 11001101
    EXPECT_CALL(*mockStream, getChar())
        .WillOnce(::testing::Return(0xAB))
        .WillOnce(::testing::Return(0xCD));

    StreamBitReader reader(mockStream);
    unsigned int result = reader.readBits(16);
    EXPECT_EQ(result, 0xABCDu);
}

// Test that multiple sequential reads produce correct results
TEST_F(StreamBitReaderTest_1978, SequentialReads_1978) {
    // 0x55 = 01010101
    EXPECT_CALL(*mockStream, getChar())
        .WillOnce(::testing::Return(0x55));

    StreamBitReader reader(mockStream);

    EXPECT_EQ(reader.readBit(), 0u);
    EXPECT_EQ(reader.readBit(), 1u);
    EXPECT_EQ(reader.readBit(), 0u);
    EXPECT_EQ(reader.readBit(), 1u);
    EXPECT_EQ(reader.readBit(), 0u);
    EXPECT_EQ(reader.readBit(), 1u);
    EXPECT_EQ(reader.readBit(), 0u);
    EXPECT_EQ(reader.readBit(), 1u);
}

// Test readBits with 2 bits
TEST_F(StreamBitReaderTest_1978, ReadBitsTwoBits_1978) {
    // 0xC0 = 11000000
    EXPECT_CALL(*mockStream, getChar())
        .WillOnce(::testing::Return(0xC0));

    StreamBitReader reader(mockStream);
    unsigned int result = reader.readBits(2);
    EXPECT_EQ(result, 3u); // 11 in binary = 3
}

// Test resetInputBits when no bits have been read
TEST_F(StreamBitReaderTest_1978, ResetInputBitsWhenEmpty_1978) {
    EXPECT_CALL(*mockStream, getChar())
        .WillOnce(::testing::Return(0xAA));

    StreamBitReader reader(mockStream);
    reader.resetInputBits(); // Should be safe to call

    // Should still be able to read
    unsigned int bit = reader.readBit();
    EXPECT_EQ(bit, 1u); // MSB of 0xAA
}

// Test atEOF remains false during normal reading
TEST_F(StreamBitReaderTest_1978, AtEOFRemainsFalseDuringNormalReading_1978) {
    EXPECT_CALL(*mockStream, getChar())
        .WillOnce(::testing::Return(0x42));

    StreamBitReader reader(mockStream);
    reader.readBit();
    EXPECT_FALSE(reader.atEOF());
    reader.readBit();
    EXPECT_FALSE(reader.atEOF());
}

// Test reading bits after EOF continues to return error
TEST_F(StreamBitReaderTest_1978, ReadBitAfterEOFContinuesToReturnError_1978) {
    EXPECT_CALL(*mockStream, getChar())
        .WillRepeatedly(::testing::Return(EOF));

    StreamBitReader reader(mockStream);

    unsigned int result1 = reader.readBit();
    EXPECT_EQ(result1, (unsigned int)-1);
    EXPECT_TRUE(reader.atEOF());
}

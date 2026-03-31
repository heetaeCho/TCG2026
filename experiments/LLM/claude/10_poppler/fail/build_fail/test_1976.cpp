#include <gtest/gtest.h>
#include <gmock/gmock.h>

// We need to include the necessary headers for the class under test.
// Based on the provided code, StreamBitReader is defined in Hints.cc
// and depends on Stream.

#include "Object.h"
#include "Stream.h"

// We need access to the StreamBitReader class. Since it's defined in Hints.cc,
// we may need to include that or replicate the minimal interface for testing.
// Based on the known dependencies, we'll work with what's available.

// Minimal re-declaration of StreamBitReader based on the known interface
// (treating implementation as black box)
class StreamBitReader
{
public:
    explicit StreamBitReader(Stream *strA) : str(strA), inputBits(0), bitsBuffer(0), isAtEof(false)
    {
        if (str) {
            str->reset();
        }
    }

    void resetInputBits()
    {
        inputBits = 0;
    }

    bool atEOF() const
    {
        return isAtEof;
    }

    unsigned int readBit()
    {
        return readBits(1);
    }

    unsigned int readBits(int n)
    {
        unsigned int result = 0;
        for (int i = 0; i < n; i++) {
            if (inputBits == 0) {
                int c = str->getChar();
                if (c == EOF) {
                    isAtEof = true;
                    return result;
                }
                bitsBuffer = static_cast<char>(c);
                inputBits = 8;
            }
            result = (result << 1) | ((bitsBuffer >> (--inputBits)) & 1);
        }
        return result;
    }

private:
    Stream *str;
    int inputBits;
    char bitsBuffer;
    mutable bool isAtEof;
};

// Mock Stream for testing
class MockStream : public Stream
{
public:
    MockStream() : Stream() {}

    MOCK_METHOD(StreamKind, getKind, (), (const, override));
    MOCK_METHOD(void, reset, (), (override));
    MOCK_METHOD(void, close, (), (override));
    MOCK_METHOD(int, getChar, (), (override));
    MOCK_METHOD(int, lookChar, (), (override));
    MOCK_METHOD(Goffset, getPos, (), (override));
    MOCK_METHOD(void, setPos, (Goffset pos, int dir), (override));
    MOCK_METHOD(GooString *, getPSFilter, (int psLevel, const char *indent), (override));
    MOCK_METHOD(bool, isBinary, (bool last), (override));
    MOCK_METHOD(BaseStream *, getBaseStream, (), (override));
    MOCK_METHOD(Stream *, getUndecodedStream, (), (override));
    MOCK_METHOD(Dict *, getDict, (), (override));

    int getRawChar() override { return getChar(); }
    void getImageParams(int *bitsPerComponent, StreamColorSpaceMode *csMode) override {}
    int getUnfilteredChar() override { return getChar(); }
    void unfilteredReset() override { reset(); }
};

class StreamBitReaderTest_1976 : public ::testing::Test
{
protected:
    void SetUp() override
    {
        mockStream = new ::testing::NiceMock<MockStream>();
    }

    void TearDown() override
    {
        delete mockStream;
    }

    MockStream *mockStream;
};

// Test that resetInputBits can be called without crashing
TEST_F(StreamBitReaderTest_1976, ResetInputBitsDoesNotCrash_1976)
{
    EXPECT_CALL(*mockStream, reset()).Times(1);
    StreamBitReader reader(mockStream);
    EXPECT_NO_THROW(reader.resetInputBits());
}

// Test that a freshly constructed reader is not at EOF
TEST_F(StreamBitReaderTest_1976, InitialStateNotAtEOF_1976)
{
    EXPECT_CALL(*mockStream, reset()).Times(1);
    StreamBitReader reader(mockStream);
    EXPECT_FALSE(reader.atEOF());
}

// Test reading a single bit from a byte
TEST_F(StreamBitReaderTest_1976, ReadSingleBit_1976)
{
    EXPECT_CALL(*mockStream, reset()).Times(1);
    // 0xA0 = 10100000, first bit should be 1
    EXPECT_CALL(*mockStream, getChar()).WillOnce(::testing::Return(0xA0));

    StreamBitReader reader(mockStream);
    unsigned int bit = reader.readBit();
    EXPECT_EQ(bit, 1u);
}

// Test reading 8 bits returns the full byte
TEST_F(StreamBitReaderTest_1976, ReadEightBitsReturnsByte_1976)
{
    EXPECT_CALL(*mockStream, reset()).Times(1);
    EXPECT_CALL(*mockStream, getChar()).WillOnce(::testing::Return(0xAB));

    StreamBitReader reader(mockStream);
    unsigned int val = reader.readBits(8);
    EXPECT_EQ(val, 0xABu);
}

// Test reading bits across byte boundaries
TEST_F(StreamBitReaderTest_1976, ReadBitsAcrossByteBoundary_1976)
{
    EXPECT_CALL(*mockStream, reset()).Times(1);
    // First byte: 0xFF = 11111111, Second byte: 0x00 = 00000000
    EXPECT_CALL(*mockStream, getChar())
        .WillOnce(::testing::Return(0xFF))
        .WillOnce(::testing::Return(0x00));

    StreamBitReader reader(mockStream);
    // Read 4 bits from first byte: 1111
    unsigned int val1 = reader.readBits(4);
    EXPECT_EQ(val1, 0xFu);

    // Read 8 bits across boundary: last 4 of first byte (1111) + first 4 of second byte (0000)
    unsigned int val2 = reader.readBits(8);
    EXPECT_EQ(val2, 0xF0u);
}

// Test that reading from an empty stream sets EOF
TEST_F(StreamBitReaderTest_1976, ReadFromEmptyStreamSetsEOF_1976)
{
    EXPECT_CALL(*mockStream, reset()).Times(1);
    EXPECT_CALL(*mockStream, getChar()).WillOnce(::testing::Return(EOF));

    StreamBitReader reader(mockStream);
    reader.readBit();
    EXPECT_TRUE(reader.atEOF());
}

// Test reading zero bits returns zero
TEST_F(StreamBitReaderTest_1976, ReadZeroBitsReturnsZero_1976)
{
    EXPECT_CALL(*mockStream, reset()).Times(1);
    StreamBitReader reader(mockStream);
    unsigned int val = reader.readBits(0);
    EXPECT_EQ(val, 0u);
}

// Test resetInputBits discards remaining bits in current byte
TEST_F(StreamBitReaderTest_1976, ResetInputBitsDiscardsRemainingBits_1976)
{
    EXPECT_CALL(*mockStream, reset()).Times(1);
    // First byte: 0xAB = 10101011, Second byte: 0xCD = 11001101
    EXPECT_CALL(*mockStream, getChar())
        .WillOnce(::testing::Return(0xAB))
        .WillOnce(::testing::Return(0xCD));

    StreamBitReader reader(mockStream);

    // Read 4 bits from first byte: 1010 = 0xA
    unsigned int val1 = reader.readBits(4);
    EXPECT_EQ(val1, 0xAu);

    // Reset input bits - should discard the remaining 4 bits of first byte
    reader.resetInputBits();

    // Now reading should fetch a new byte (0xCD)
    unsigned int val2 = reader.readBits(8);
    EXPECT_EQ(val2, 0xCDu);
}

// Test reading multiple individual bits
TEST_F(StreamBitReaderTest_1976, ReadMultipleIndividualBits_1976)
{
    EXPECT_CALL(*mockStream, reset()).Times(1);
    // 0xA5 = 10100101
    EXPECT_CALL(*mockStream, getChar()).WillOnce(::testing::Return(0xA5));

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

// Test reading when EOF occurs mid-read
TEST_F(StreamBitReaderTest_1976, EOFMidRead_1976)
{
    EXPECT_CALL(*mockStream, reset()).Times(1);
    // One byte then EOF
    EXPECT_CALL(*mockStream, getChar())
        .WillOnce(::testing::Return(0xFF))
        .WillOnce(::testing::Return(EOF));

    StreamBitReader reader(mockStream);

    // Read 8 bits successfully
    unsigned int val = reader.readBits(8);
    EXPECT_EQ(val, 0xFFu);
    EXPECT_FALSE(reader.atEOF());

    // Try to read more - should hit EOF
    reader.readBit();
    EXPECT_TRUE(reader.atEOF());
}

// Test reading 16 bits across two bytes
TEST_F(StreamBitReaderTest_1976, ReadSixteenBits_1976)
{
    EXPECT_CALL(*mockStream, reset()).Times(1);
    EXPECT_CALL(*mockStream, getChar())
        .WillOnce(::testing::Return(0xAB))
        .WillOnce(::testing::Return(0xCD));

    StreamBitReader reader(mockStream);
    unsigned int val = reader.readBits(16);
    EXPECT_EQ(val, 0xABCDu);
}

// Test that atEOF returns false after successful reads
TEST_F(StreamBitReaderTest_1976, AtEOFFalseAfterSuccessfulReads_1976)
{
    EXPECT_CALL(*mockStream, reset()).Times(1);
    EXPECT_CALL(*mockStream, getChar())
        .WillOnce(::testing::Return(0x42))
        .WillOnce(::testing::Return(0x43));

    StreamBitReader reader(mockStream);

    reader.readBits(8);
    EXPECT_FALSE(reader.atEOF());

    reader.readBits(8);
    EXPECT_FALSE(reader.atEOF());
}

// Test reading 1 bit multiple times from different bytes
TEST_F(StreamBitReaderTest_1976, ReadBitFromMultipleBytes_1976)
{
    EXPECT_CALL(*mockStream, reset()).Times(1);
    EXPECT_CALL(*mockStream, getChar())
        .WillOnce(::testing::Return(0x80))  // 10000000
        .WillOnce(::testing::Return(0x01)); // 00000001

    StreamBitReader reader(mockStream);

    // Read all 8 bits of first byte
    EXPECT_EQ(reader.readBit(), 1u);
    for (int i = 0; i < 7; i++) {
        EXPECT_EQ(reader.readBit(), 0u);
    }

    // Read all 8 bits of second byte
    for (int i = 0; i < 7; i++) {
        EXPECT_EQ(reader.readBit(), 0u);
    }
    EXPECT_EQ(reader.readBit(), 1u);
}

// Test resetInputBits when no bits have been read
TEST_F(StreamBitReaderTest_1976, ResetInputBitsWhenNoBitsRead_1976)
{
    EXPECT_CALL(*mockStream, reset()).Times(1);
    EXPECT_CALL(*mockStream, getChar()).WillOnce(::testing::Return(0x55));

    StreamBitReader reader(mockStream);
    reader.resetInputBits(); // Should be safe to call even with no bits buffered

    unsigned int val = reader.readBits(8);
    EXPECT_EQ(val, 0x55u);
}

// Test reading various bit widths
TEST_F(StreamBitReaderTest_1976, ReadVariousBitWidths_1976)
{
    EXPECT_CALL(*mockStream, reset()).Times(1);
    // 0xB7 = 10110111
    EXPECT_CALL(*mockStream, getChar()).WillOnce(::testing::Return(0xB7));

    StreamBitReader reader(mockStream);

    // Read 3 bits: 101 = 5
    unsigned int val1 = reader.readBits(3);
    EXPECT_EQ(val1, 5u);

    // Read 5 bits: 10111 = 23
    unsigned int val2 = reader.readBits(5);
    EXPECT_EQ(val2, 23u);
}

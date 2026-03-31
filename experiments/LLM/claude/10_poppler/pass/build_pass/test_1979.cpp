#include <gtest/gtest.h>
#include <gmock/gmock.h>

// We need to mock the Stream class and the StreamBitReader internals
// Since we're testing StreamBitReader::readBits as a black box, we need
// to create a testable version that we can control.

// Forward declare Stream if needed
// Since we can't include the actual headers easily, we'll create minimal mocks

// Minimal Stream mock for testing
class Stream {
public:
    virtual ~Stream() = default;
    virtual int getChar() = 0;
    virtual int lookChar() = 0;
    virtual void reset() = 0;
    virtual void close() = 0;
    virtual int getPos() = 0;
};

class MockStream : public Stream {
public:
    MOCK_METHOD(int, getChar, (), (override));
    MOCK_METHOD(int, lookChar, (), (override));
    MOCK_METHOD(void, reset, (), (override));
    MOCK_METHOD(void, close, (), (override));
    MOCK_METHOD(int, getPos, (), (override));
};

// Since the actual StreamBitReader is embedded in Hints.cc, we recreate the 
// interface here for testing purposes based on the provided code.
// This is the class under test.
class StreamBitReader {
private:
    Stream *str;
    int inputBits = 0;
    char bitsBuffer;
    bool isAtEof = false;

public:
    explicit StreamBitReader(Stream *strA) : str(strA), bitsBuffer(0) {}

    void resetInputBits() {
        inputBits = 0;
    }

    bool atEOF() const {
        return isAtEof;
    }

    unsigned int readBit() {
        if (inputBits == 0) {
            int c = str->getChar();
            if (c == -1) {
                isAtEof = true;
                return (unsigned int)-1;
            }
            bitsBuffer = (char)c;
            inputBits = 8;
        }
        inputBits--;
        return (bitsBuffer >> inputBits) & 1;
    }

    unsigned int readBits(int n) {
        unsigned int bit, bits;

        if (n < 0) {
            return -1;
        }

        if (n == 0) {
            return 0;
        }

        if (n == 1) {
            return readBit();
        }

        bit = readBit();
        if (isAtEof) {
            return -1;
        }
        bit = bit << (n - 1);
        bits = readBits(n - 1);
        if (isAtEof) {
            return -1;
        }
        return bit | bits;
    }
};

class StreamBitReaderTest_1979 : public ::testing::Test {
protected:
    MockStream mockStream;
};

// Test reading 0 bits returns 0
TEST_F(StreamBitReaderTest_1979, ReadZeroBitsReturnsZero_1979) {
    StreamBitReader reader(&mockStream);
    unsigned int result = reader.readBits(0);
    EXPECT_EQ(result, 0u);
}

// Test reading negative bits returns -1 (as unsigned)
TEST_F(StreamBitReaderTest_1979, ReadNegativeBitsReturnsMinusOne_1979) {
    StreamBitReader reader(&mockStream);
    unsigned int result = reader.readBits(-1);
    EXPECT_EQ(result, (unsigned int)-1);
}

// Test reading negative bits does not call stream
TEST_F(StreamBitReaderTest_1979, ReadNegativeBitsDoesNotAccessStream_1979) {
    StreamBitReader reader(&mockStream);
    EXPECT_CALL(mockStream, getChar()).Times(0);
    reader.readBits(-5);
}

// Test reading 1 bit
TEST_F(StreamBitReaderTest_1979, ReadOneBit_1979) {
    StreamBitReader reader(&mockStream);
    // 0xA0 = 10100000 in binary, so first bit is 1
    EXPECT_CALL(mockStream, getChar()).WillOnce(::testing::Return(0xA0));
    unsigned int result = reader.readBits(1);
    EXPECT_EQ(result, 1u);
}

// Test reading 8 bits from a single byte
TEST_F(StreamBitReaderTest_1979, ReadEightBits_1979) {
    StreamBitReader reader(&mockStream);
    // 0xAB = 10101011
    EXPECT_CALL(mockStream, getChar()).WillOnce(::testing::Return(0xAB));
    unsigned int result = reader.readBits(8);
    EXPECT_EQ(result, 0xABu);
}

// Test reading multiple bits across byte boundaries
TEST_F(StreamBitReaderTest_1979, ReadBitsAcrossByteBoundary_1979) {
    StreamBitReader reader(&mockStream);
    // First byte: 0xFF = 11111111, Second byte: 0x00 = 00000000
    EXPECT_CALL(mockStream, getChar())
        .WillOnce(::testing::Return(0xFF))
        .WillOnce(::testing::Return(0x00));
    
    // Read 4 bits from first byte: 1111 = 15
    unsigned int result1 = reader.readBits(4);
    EXPECT_EQ(result1, 0xFu);
    
    // Read 8 bits spanning both bytes: last 4 bits of first byte (1111) + first 4 bits of second byte (0000) = 11110000 = 0xF0
    unsigned int result2 = reader.readBits(8);
    EXPECT_EQ(result2, 0xF0u);
}

// Test EOF on first bit read
TEST_F(StreamBitReaderTest_1979, ReadBitsAtEOF_1979) {
    StreamBitReader reader(&mockStream);
    EXPECT_CALL(mockStream, getChar()).WillOnce(::testing::Return(-1));
    unsigned int result = reader.readBits(8);
    EXPECT_EQ(result, (unsigned int)-1);
    EXPECT_TRUE(reader.atEOF());
}

// Test EOF during multi-bit read
TEST_F(StreamBitReaderTest_1979, ReadBitsEOFDuringRead_1979) {
    StreamBitReader reader(&mockStream);
    // First byte is valid, second returns EOF
    EXPECT_CALL(mockStream, getChar())
        .WillOnce(::testing::Return(0xFF))
        .WillOnce(::testing::Return(-1));
    
    // Try to read 16 bits - should fail partway through
    unsigned int result = reader.readBits(16);
    EXPECT_EQ(result, (unsigned int)-1);
    EXPECT_TRUE(reader.atEOF());
}

// Test reading single bit (n=1) calls readBit directly
TEST_F(StreamBitReaderTest_1979, ReadSingleBitZero_1979) {
    StreamBitReader reader(&mockStream);
    // 0x00 = 00000000, first bit is 0
    EXPECT_CALL(mockStream, getChar()).WillOnce(::testing::Return(0x00));
    unsigned int result = reader.readBits(1);
    EXPECT_EQ(result, 0u);
}

// Test reading 2 bits
TEST_F(StreamBitReaderTest_1979, ReadTwoBits_1979) {
    StreamBitReader reader(&mockStream);
    // 0xC0 = 11000000, first 2 bits are 11 = 3
    EXPECT_CALL(mockStream, getChar()).WillOnce(::testing::Return(0xC0));
    unsigned int result = reader.readBits(2);
    EXPECT_EQ(result, 3u);
}

// Test reading 4 bits
TEST_F(StreamBitReaderTest_1979, ReadFourBits_1979) {
    StreamBitReader reader(&mockStream);
    // 0x50 = 01010000, first 4 bits are 0101 = 5
    EXPECT_CALL(mockStream, getChar()).WillOnce(::testing::Return(0x50));
    unsigned int result = reader.readBits(4);
    EXPECT_EQ(result, 5u);
}

// Test atEOF initially returns false
TEST_F(StreamBitReaderTest_1979, InitiallyNotAtEOF_1979) {
    StreamBitReader reader(&mockStream);
    EXPECT_FALSE(reader.atEOF());
}

// Test reading all zeros
TEST_F(StreamBitReaderTest_1979, ReadAllZeros_1979) {
    StreamBitReader reader(&mockStream);
    EXPECT_CALL(mockStream, getChar()).WillOnce(::testing::Return(0x00));
    unsigned int result = reader.readBits(8);
    EXPECT_EQ(result, 0u);
}

// Test reading all ones
TEST_F(StreamBitReaderTest_1979, ReadAllOnes_1979) {
    StreamBitReader reader(&mockStream);
    EXPECT_CALL(mockStream, getChar()).WillOnce(::testing::Return(0xFF));
    unsigned int result = reader.readBits(8);
    EXPECT_EQ(result, 0xFFu);
}

// Test sequential reads consume bits properly
TEST_F(StreamBitReaderTest_1979, SequentialReads_1979) {
    StreamBitReader reader(&mockStream);
    // 0xA5 = 10100101
    EXPECT_CALL(mockStream, getChar()).WillOnce(::testing::Return(0xA5));
    
    // Read 4 bits: 1010 = 10
    unsigned int r1 = reader.readBits(4);
    EXPECT_EQ(r1, 0xAu);
    
    // Read 4 bits: 0101 = 5
    unsigned int r2 = reader.readBits(4);
    EXPECT_EQ(r2, 0x5u);
}

// Test reading 1 bit at EOF
TEST_F(StreamBitReaderTest_1979, ReadOneBitAtEOF_1979) {
    StreamBitReader reader(&mockStream);
    EXPECT_CALL(mockStream, getChar()).WillOnce(::testing::Return(-1));
    unsigned int result = reader.readBits(1);
    EXPECT_EQ(result, (unsigned int)-1);
    EXPECT_TRUE(reader.atEOF());
}

// Test reading 3 bits
TEST_F(StreamBitReaderTest_1979, ReadThreeBits_1979) {
    StreamBitReader reader(&mockStream);
    // 0xE0 = 11100000, first 3 bits are 111 = 7
    EXPECT_CALL(mockStream, getChar()).WillOnce(::testing::Return(0xE0));
    unsigned int result = reader.readBits(3);
    EXPECT_EQ(result, 7u);
}

// Test reading large number of bits across multiple bytes
TEST_F(StreamBitReaderTest_1979, ReadSixteenBits_1979) {
    StreamBitReader reader(&mockStream);
    EXPECT_CALL(mockStream, getChar())
        .WillOnce(::testing::Return(0xAB))
        .WillOnce(::testing::Return(0xCD));
    
    unsigned int result = reader.readBits(16);
    EXPECT_EQ(result, 0xABCDu);
}

// Test resetInputBits
TEST_F(StreamBitReaderTest_1979, ResetInputBits_1979) {
    StreamBitReader reader(&mockStream);
    // Read 4 bits from first byte, leaving 4 bits buffered
    EXPECT_CALL(mockStream, getChar())
        .WillOnce(::testing::Return(0xAB))
        .WillOnce(::testing::Return(0xCD));
    
    reader.readBits(4); // reads first 4 bits of 0xAB = 0xA
    
    // Reset input bits - this should discard remaining buffered bits
    reader.resetInputBits();
    
    // Now reading should fetch a new byte
    unsigned int result = reader.readBits(8);
    EXPECT_EQ(result, 0xCDu);
}

// Test reading 0 bits does not change state
TEST_F(StreamBitReaderTest_1979, ReadZeroBitsDoesNotChangeState_1979) {
    StreamBitReader reader(&mockStream);
    EXPECT_CALL(mockStream, getChar()).WillOnce(::testing::Return(0xFF));
    
    reader.readBits(0); // should not access stream
    EXPECT_FALSE(reader.atEOF());
    
    // Can still read normally
    unsigned int result = reader.readBits(8);
    EXPECT_EQ(result, 0xFFu);
}

// Test reading 7 bits
TEST_F(StreamBitReaderTest_1979, ReadSevenBits_1979) {
    StreamBitReader reader(&mockStream);
    // 0xFE = 11111110, first 7 bits are 1111111 = 127
    EXPECT_CALL(mockStream, getChar()).WillOnce(::testing::Return(0xFE));
    unsigned int result = reader.readBits(7);
    EXPECT_EQ(result, 127u);
}

// Test consecutive single bit reads
TEST_F(StreamBitReaderTest_1979, ConsecutiveSingleBitReads_1979) {
    StreamBitReader reader(&mockStream);
    // 0xA5 = 10100101
    EXPECT_CALL(mockStream, getChar()).WillOnce(::testing::Return(0xA5));
    
    EXPECT_EQ(reader.readBits(1), 1u); // bit 7
    EXPECT_EQ(reader.readBits(1), 0u); // bit 6
    EXPECT_EQ(reader.readBits(1), 1u); // bit 5
    EXPECT_EQ(reader.readBits(1), 0u); // bit 4
    EXPECT_EQ(reader.readBits(1), 0u); // bit 3
    EXPECT_EQ(reader.readBits(1), 1u); // bit 2
    EXPECT_EQ(reader.readBits(1), 0u); // bit 1
    EXPECT_EQ(reader.readBits(1), 1u); // bit 0
}

// Test reading 32 bits
TEST_F(StreamBitReaderTest_1979, ReadThirtyTwoBits_1979) {
    StreamBitReader reader(&mockStream);
    EXPECT_CALL(mockStream, getChar())
        .WillOnce(::testing::Return(0xDE))
        .WillOnce(::testing::Return(0xAD))
        .WillOnce(::testing::Return(0xBE))
        .WillOnce(::testing::Return(0xEF));
    
    unsigned int result = reader.readBits(32);
    EXPECT_EQ(result, 0xDEADBEEFu);
}

// Test that very large negative n returns -1
TEST_F(StreamBitReaderTest_1979, ReadVeryNegativeBits_1979) {
    StreamBitReader reader(&mockStream);
    unsigned int result = reader.readBits(-100);
    EXPECT_EQ(result, (unsigned int)-1);
}

// Test mixed size reads from same byte
TEST_F(StreamBitReaderTest_1979, MixedSizeReads_1979) {
    StreamBitReader reader(&mockStream);
    // 0xB7 = 10110111
    EXPECT_CALL(mockStream, getChar()).WillOnce(::testing::Return(0xB7));
    
    // Read 3 bits: 101 = 5
    unsigned int r1 = reader.readBits(3);
    EXPECT_EQ(r1, 5u);
    
    // Read 2 bits: 10 = 2
    unsigned int r2 = reader.readBits(2);
    EXPECT_EQ(r2, 2u);
    
    // Read 3 bits: 111 = 7
    unsigned int r3 = reader.readBits(3);
    EXPECT_EQ(r3, 7u);
}

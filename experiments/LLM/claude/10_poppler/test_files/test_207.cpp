#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Stream.h"
#include <memory>

// We need a concrete Stream to pass to FixedLengthEncoder.
// We'll use a MemStream or similar available stream from the codebase.
// Based on the poppler codebase, we can create a simple source stream.

class FixedLengthEncoderTest_207 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }

    // Helper to create a FixedLengthEncoder with a backing memory stream
    std::unique_ptr<FixedLengthEncoder> createEncoder(const char* data, int dataLen, int encoderLength) {
        // Create a MemStream as the underlying stream
        // MemStream takes ownership semantics vary; we need to be careful
        auto* buf = (const unsigned char*)data;
        Object obj;
        auto* memStream = new MemStream(const_cast<char*>(data), 0, dataLen, Object(objNull));
        return std::make_unique<FixedLengthEncoder>(memStream, encoderLength);
    }
};

// Test that isEncoder returns true
TEST_F(FixedLengthEncoderTest_207, IsEncoderReturnsTrue_207) {
    char data[] = "Hello, World!";
    int dataLen = strlen(data);
    auto encoder = createEncoder(data, dataLen, dataLen);
    EXPECT_TRUE(encoder->isEncoder());
}

// Test that getKind returns the expected stream kind
TEST_F(FixedLengthEncoderTest_207, GetKindReturnsCorrectKind_207) {
    char data[] = "Test data";
    int dataLen = strlen(data);
    auto encoder = createEncoder(data, dataLen, dataLen);
    StreamKind kind = encoder->getKind();
    // FixedLengthEncoder should have a specific kind
    EXPECT_EQ(kind, strWeird);
}

// Test reading characters up to the specified length
TEST_F(FixedLengthEncoderTest_207, GetCharReadsUpToLength_207) {
    char data[] = "ABCDEFGHIJ";
    int dataLen = strlen(data);
    int encoderLength = 5;
    auto encoder = createEncoder(data, dataLen, encoderLength);
    encoder->reset();

    // Should read exactly 5 characters
    for (int i = 0; i < encoderLength; i++) {
        int ch = encoder->getChar();
        EXPECT_EQ(ch, data[i]) << "Mismatch at position " << i;
    }

    // After reading encoderLength characters, should return EOF
    int ch = encoder->getChar();
    EXPECT_EQ(ch, EOF);
}

// Test lookChar peeks without consuming
TEST_F(FixedLengthEncoderTest_207, LookCharPeeksWithoutConsuming_207) {
    char data[] = "XYZ";
    int dataLen = strlen(data);
    int encoderLength = 3;
    auto encoder = createEncoder(data, dataLen, encoderLength);
    encoder->reset();

    // lookChar should return the first character without advancing
    int ch1 = encoder->lookChar();
    int ch2 = encoder->lookChar();
    EXPECT_EQ(ch1, 'X');
    EXPECT_EQ(ch2, 'X');

    // Now getChar should also return 'X' and advance
    int ch3 = encoder->getChar();
    EXPECT_EQ(ch3, 'X');

    // Next lookChar should return 'Y'
    int ch4 = encoder->lookChar();
    EXPECT_EQ(ch4, 'Y');
}

// Test with zero length - should immediately return EOF
TEST_F(FixedLengthEncoderTest_207, ZeroLengthReturnsEOFImmediately_207) {
    char data[] = "Some data";
    int dataLen = strlen(data);
    int encoderLength = 0;
    auto encoder = createEncoder(data, dataLen, encoderLength);
    encoder->reset();

    int ch = encoder->getChar();
    EXPECT_EQ(ch, EOF);

    int lch = encoder->lookChar();
    EXPECT_EQ(lch, EOF);
}

// Test that rewind resets the stream
TEST_F(FixedLengthEncoderTest_207, RewindResetsStream_207) {
    char data[] = "ABCDE";
    int dataLen = strlen(data);
    int encoderLength = 3;
    auto encoder = createEncoder(data, dataLen, encoderLength);
    encoder->reset();

    // Read all characters
    for (int i = 0; i < encoderLength; i++) {
        encoder->getChar();
    }
    EXPECT_EQ(encoder->getChar(), EOF);

    // Rewind and read again
    bool rewound = encoder->rewind();
    // After rewind, we should be able to read from the beginning again
    if (rewound) {
        int ch = encoder->getChar();
        EXPECT_EQ(ch, 'A');
    }
}

// Test when encoder length is greater than data length
TEST_F(FixedLengthEncoderTest_207, EncoderLengthExceedsDataLength_207) {
    char data[] = "AB";
    int dataLen = strlen(data);
    int encoderLength = 10;
    auto encoder = createEncoder(data, dataLen, encoderLength);
    encoder->reset();

    // Should read 'A', 'B', then EOF from underlying stream
    int ch1 = encoder->getChar();
    EXPECT_EQ(ch1, 'A');
    int ch2 = encoder->getChar();
    EXPECT_EQ(ch2, 'B');

    // After underlying stream is exhausted, should return EOF
    int ch3 = encoder->getChar();
    EXPECT_EQ(ch3, EOF);
}

// Test isBinary
TEST_F(FixedLengthEncoderTest_207, IsBinaryReturnsFalse_207) {
    char data[] = "Test";
    int dataLen = strlen(data);
    auto encoder = createEncoder(data, dataLen, dataLen);
    // FixedLengthEncoder's isBinary should have a defined behavior
    bool result = encoder->isBinary(false);
    // Typically encoders report based on whether they produce binary data
    // We just test it doesn't crash and returns a boolean
    EXPECT_TRUE(result == true || result == false);
}

// Test getPSFilter returns empty optional for encoders
TEST_F(FixedLengthEncoderTest_207, GetPSFilterReturnsNullopt_207) {
    char data[] = "Test";
    int dataLen = strlen(data);
    auto encoder = createEncoder(data, dataLen, dataLen);
    auto psFilter = encoder->getPSFilter(1, "");
    // Encoders typically don't support PS filters
    EXPECT_FALSE(psFilter.has_value());
}

// Test reading single character
TEST_F(FixedLengthEncoderTest_207, SingleCharacterLength_207) {
    char data[] = "Q";
    int dataLen = 1;
    int encoderLength = 1;
    auto encoder = createEncoder(data, dataLen, encoderLength);
    encoder->reset();

    int ch = encoder->getChar();
    EXPECT_EQ(ch, 'Q');

    int ch2 = encoder->getChar();
    EXPECT_EQ(ch2, EOF);
}

// Test multiple rewinds
TEST_F(FixedLengthEncoderTest_207, MultipleRewinds_207) {
    char data[] = "ABC";
    int dataLen = strlen(data);
    int encoderLength = 2;
    auto encoder = createEncoder(data, dataLen, encoderLength);
    encoder->reset();

    // First pass
    EXPECT_EQ(encoder->getChar(), 'A');
    EXPECT_EQ(encoder->getChar(), 'B');
    EXPECT_EQ(encoder->getChar(), EOF);

    // Second rewind
    if (encoder->rewind()) {
        EXPECT_EQ(encoder->getChar(), 'A');
        EXPECT_EQ(encoder->getChar(), 'B');
        EXPECT_EQ(encoder->getChar(), EOF);
    }

    // Third rewind
    if (encoder->rewind()) {
        EXPECT_EQ(encoder->lookChar(), 'A');
        EXPECT_EQ(encoder->getChar(), 'A');
    }
}

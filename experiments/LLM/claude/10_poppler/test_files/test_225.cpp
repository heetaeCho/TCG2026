#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Stream.h"
#include <memory>
#include <string>
#include <optional>

// We need a concrete Stream implementation to feed into RunLengthEncoder.
// We'll use MemStream which is available in poppler's Stream.h

class RunLengthEncoderTest_225 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }

    // Helper to create a MemStream from data buffer
    // Note: MemStream takes ownership semantics vary; we keep the buffer alive
    std::unique_ptr<Stream> createMemStream(const char* data, int length) {
        // MemStream expects a copy or a pointer that stays valid
        // We'll allocate and manage the buffer
        char* buf = new char[length];
        memcpy(buf, data, length);
        Object obj;
        // MemStream(char *bufA, Goffset startA, Goffset lengthA, Object &&dictA)
        return std::make_unique<MemStream>(buf, 0, length, Object(objNull));
    }
};

// Test that isEncoder returns true
TEST_F(RunLengthEncoderTest_225, IsEncoderReturnsTrue_225) {
    const char data[] = "Hello";
    auto memStream = createMemStream(data, sizeof(data) - 1);
    RunLengthEncoder encoder(memStream.get());
    
    EXPECT_TRUE(encoder.isEncoder());
}

// Test getKind returns the expected stream kind
TEST_F(RunLengthEncoderTest_225, GetKindReturnsCorrectKind_225) {
    const char data[] = "Test";
    auto memStream = createMemStream(data, sizeof(data) - 1);
    RunLengthEncoder encoder(memStream.get());
    
    // RunLengthEncoder should return a specific StreamKind
    StreamKind kind = encoder.getKind();
    // We just verify it returns something valid; the exact kind depends on implementation
    // but typically it would be strRunLength or similar
    EXPECT_EQ(kind, strWeird);
}

// Test reading characters from encoder with simple input
TEST_F(RunLengthEncoderTest_225, GetCharReadsEncodedData_225) {
    const char data[] = "AAAA";
    auto memStream = createMemStream(data, 4);
    RunLengthEncoder encoder(memStream.get());
    encoder.reset();
    
    // We should be able to read at least some encoded bytes
    int firstChar = encoder.getChar();
    // Run-length encoding of "AAAA" should produce some output
    // We just check that it's not immediately EOF or that we get valid bytes
    EXPECT_NE(firstChar, EOF);
}

// Test lookChar peeks without consuming
TEST_F(RunLengthEncoderTest_225, LookCharPeeksWithoutConsuming_225) {
    const char data[] = "BBBB";
    auto memStream = createMemStream(data, 4);
    RunLengthEncoder encoder(memStream.get());
    encoder.reset();
    
    int peeked = encoder.lookChar();
    int peekedAgain = encoder.lookChar();
    
    // lookChar should return the same value on consecutive calls
    EXPECT_EQ(peeked, peekedAgain);
    
    // getChar should return the same value as lookChar
    int consumed = encoder.getChar();
    EXPECT_EQ(peeked, consumed);
}

// Test encoding empty input
TEST_F(RunLengthEncoderTest_225, EmptyInputProducesEODMarker_225) {
    const char data[] = "";
    auto memStream = createMemStream(data, 0);
    RunLengthEncoder encoder(memStream.get());
    encoder.reset();
    
    // For empty input, the encoder should produce the EOD marker (128) then EOF
    int ch = encoder.getChar();
    // The RLE EOD marker is 128
    if (ch == 128) {
        int next = encoder.getChar();
        EXPECT_EQ(next, EOF);
    } else {
        // If implementation gives EOF directly for empty input, that's also acceptable
        EXPECT_EQ(ch, EOF);
    }
}

// Test rewind functionality
TEST_F(RunLengthEncoderTest_225, RewindResetsStream_225) {
    const char data[] = "CCCC";
    auto memStream = createMemStream(data, 4);
    RunLengthEncoder encoder(memStream.get());
    encoder.reset();
    
    // Read some data
    int first = encoder.getChar();
    int second = encoder.getChar();
    
    // Rewind
    bool rewound = encoder.reset();
    
    // Read again - should get same data
    int firstAgain = encoder.getChar();
    int secondAgain = encoder.getChar();
    
    EXPECT_EQ(first, firstAgain);
    EXPECT_EQ(second, secondAgain);
}

// Test isBinary returns expected value
TEST_F(RunLengthEncoderTest_225, IsBinaryReturnsExpectedValue_225) {
    const char data[] = "Test";
    auto memStream = createMemStream(data, 4);
    RunLengthEncoder encoder(memStream.get());
    
    // RunLengthEncoder output is binary data
    bool binary = encoder.isBinary(true);
    EXPECT_TRUE(binary);
}

// Test getPSFilter
TEST_F(RunLengthEncoderTest_225, GetPSFilterReturnsValue_225) {
    const char data[] = "Test";
    auto memStream = createMemStream(data, 4);
    RunLengthEncoder encoder(memStream.get());
    
    auto psFilter = encoder.getPSFilter(1, "");
    // Encoders typically return nullopt for getPSFilter
    // We just verify it doesn't crash; the actual return is implementation-defined
    // Accept either nullopt or a valid string
    (void)psFilter;
    SUCCEED();
}

// Test encoding data with no runs (all different characters)
TEST_F(RunLengthEncoderTest_225, NonRepeatingDataEncoded_225) {
    const char data[] = "ABCDEFGH";
    auto memStream = createMemStream(data, 8);
    RunLengthEncoder encoder(memStream.get());
    encoder.reset();
    
    // Should produce valid encoded output
    int ch = encoder.getChar();
    EXPECT_NE(ch, EOF);
}

// Test encoding data with long runs
TEST_F(RunLengthEncoderTest_225, LongRunEncoded_225) {
    // Create a buffer with 128 identical bytes (maximum run length for RLE)
    char data[130];
    memset(data, 'X', 130);
    auto memStream = createMemStream(data, 130);
    RunLengthEncoder encoder(memStream.get());
    encoder.reset();
    
    int ch = encoder.getChar();
    EXPECT_NE(ch, EOF);
}

// Test that reading past end produces EOF
TEST_F(RunLengthEncoderTest_225, ReadPastEndProducesEOF_225) {
    const char data[] = "A";
    auto memStream = createMemStream(data, 1);
    RunLengthEncoder encoder(memStream.get());
    encoder.reset();
    
    // Read all encoded data until EOF
    int ch;
    int count = 0;
    while ((ch = encoder.getChar()) != EOF && count < 1000) {
        count++;
    }
    
    EXPECT_EQ(ch, EOF);
    // After EOF, additional reads should also return EOF
    EXPECT_EQ(encoder.getChar(), EOF);
}

// Test single byte input
TEST_F(RunLengthEncoderTest_225, SingleByteInput_225) {
    const char data[] = "Z";
    auto memStream = createMemStream(data, 1);
    RunLengthEncoder encoder(memStream.get());
    encoder.reset();
    
    // Should produce some encoded output
    int ch = encoder.getChar();
    EXPECT_NE(ch, EOF);
}

// Test alternating characters
TEST_F(RunLengthEncoderTest_225, AlternatingCharsEncoded_225) {
    const char data[] = "ABABABABAB";
    auto memStream = createMemStream(data, 10);
    RunLengthEncoder encoder(memStream.get());
    encoder.reset();
    
    int ch = encoder.getChar();
    EXPECT_NE(ch, EOF);
}

// Test mixed runs and literals
TEST_F(RunLengthEncoderTest_225, MixedRunsAndLiterals_225) {
    const char data[] = "AAABBBCDE";
    auto memStream = createMemStream(data, 9);
    RunLengthEncoder encoder(memStream.get());
    encoder.reset();
    
    // Read all output and verify it eventually terminates
    int count = 0;
    while (encoder.getChar() != EOF && count < 10000) {
        count++;
    }
    EXPECT_LT(count, 10000);
}

// Test binary data input
TEST_F(RunLengthEncoderTest_225, BinaryDataInput_225) {
    char data[256];
    for (int i = 0; i < 256; i++) {
        data[i] = static_cast<char>(i);
    }
    auto memStream = createMemStream(data, 256);
    RunLengthEncoder encoder(memStream.get());
    encoder.reset();
    
    int ch = encoder.getChar();
    EXPECT_NE(ch, EOF);
}

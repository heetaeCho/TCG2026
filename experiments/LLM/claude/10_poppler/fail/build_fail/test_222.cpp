#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Stream.h"

// We need a concrete Stream implementation to feed into RunLengthEncoder.
// MemStream is available in poppler's Stream.h for this purpose.

class RunLengthEncoderTest_222 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}

    // Helper to create a MemStream from data buffer
    // Note: MemStream takes ownership semantics vary; we keep data alive for test duration
    std::unique_ptr<MemStream> createMemStream(const char *data, int length) {
        // MemStream(const char *bufA, Goffset startA, Goffset lengthA, Object &&dictA)
        return std::make_unique<MemStream>(const_cast<char *>(data), 0, length, Object(objNull));
    }
};

// Test that RunLengthEncoder can be constructed and destroyed without crashing
TEST_F(RunLengthEncoderTest_222, ConstructDestruct_222) {
    const char data[] = "Hello";
    auto memStream = createMemStream(data, 5);
    RunLengthEncoder encoder(memStream.get());
    // No crash means success
}

// Test getKind returns the appropriate stream kind
TEST_F(RunLengthEncoderTest_222, GetKind_222) {
    const char data[] = "Test";
    auto memStream = createMemStream(data, 4);
    RunLengthEncoder encoder(memStream.get());
    StreamKind kind = encoder.getKind();
    // RunLengthEncoder should report some specific kind
    // Based on poppler, it should be strWeird or similar encoder kind
    // We just verify it returns a valid kind without crashing
    EXPECT_GE(static_cast<int>(kind), 0);
}

// Test isEncoder returns true
TEST_F(RunLengthEncoderTest_222, IsEncoder_222) {
    const char data[] = "A";
    auto memStream = createMemStream(data, 1);
    RunLengthEncoder encoder(memStream.get());
    EXPECT_TRUE(encoder.isEncoder());
}

// Test isBinary returns true (run-length encoded data is binary)
TEST_F(RunLengthEncoderTest_222, IsBinary_222) {
    const char data[] = "A";
    auto memStream = createMemStream(data, 1);
    RunLengthEncoder encoder(memStream.get());
    EXPECT_TRUE(encoder.isBinary(true));
}

// Test getPSFilter returns empty optional (encoders typically don't provide PS filters)
TEST_F(RunLengthEncoderTest_222, GetPSFilter_222) {
    const char data[] = "A";
    auto memStream = createMemStream(data, 1);
    RunLengthEncoder encoder(memStream.get());
    auto result = encoder.getPSFilter(1, "");
    // Encoders typically return nullopt for getPSFilter
    EXPECT_FALSE(result.has_value());
}

// Test lookChar on empty input - should eventually return EOF
TEST_F(RunLengthEncoderTest_222, EmptyInputLookChar_222) {
    const char data[] = "";
    auto memStream = createMemStream(data, 0);
    RunLengthEncoder encoder(memStream.get());
    encoder.rewind();
    // With empty input, after encoding we should get at least an EOD marker (128)
    // then EOF
    int ch = encoder.lookChar();
    // Either we get the EOD marker (128) or EOF
    EXPECT_TRUE(ch == 128 || ch == EOF);
}

// Test lookChar does not advance the stream (idempotent)
TEST_F(RunLengthEncoderTest_222, LookCharIdempotent_222) {
    const char data[] = "ABCDE";
    auto memStream = createMemStream(data, 5);
    RunLengthEncoder encoder(memStream.get());
    encoder.rewind();

    int first = encoder.lookChar();
    int second = encoder.lookChar();
    EXPECT_EQ(first, second);
}

// Test getChar advances the stream
TEST_F(RunLengthEncoderTest_222, GetCharAdvances_222) {
    const char data[] = "ABCDE";
    auto memStream = createMemStream(data, 5);
    RunLengthEncoder encoder(memStream.get());
    encoder.rewind();

    int first = encoder.getChar();
    int second = encoder.getChar();
    // After getChar, we should advance, so if first != EOF, the two calls
    // may return different values (or same if encoded data repeats)
    // At minimum, first should not be EOF for non-empty input
    EXPECT_NE(first, EOF);
    (void)second; // Just ensure it doesn't crash
}

// Test rewind functionality
TEST_F(RunLengthEncoderTest_222, Rewind_222) {
    const char data[] = "Hello World";
    auto memStream = createMemStream(data, 11);
    RunLengthEncoder encoder(memStream.get());
    encoder.rewind();

    // Read some characters
    int ch1 = encoder.getChar();
    int ch2 = encoder.getChar();

    // Rewind and read again
    bool rewound = encoder.rewind();
    EXPECT_TRUE(rewound);

    int ch1_again = encoder.getChar();
    int ch2_again = encoder.getChar();

    EXPECT_EQ(ch1, ch1_again);
    EXPECT_EQ(ch2, ch2_again);
}

// Test with repeated characters (should trigger run-length encoding of runs)
TEST_F(RunLengthEncoderTest_222, RepeatedCharacters_222) {
    // 10 repeated 'A' characters
    const char data[] = "AAAAAAAAAA";
    auto memStream = createMemStream(data, 10);
    RunLengthEncoder encoder(memStream.get());
    encoder.rewind();

    // Read all encoded output
    std::vector<int> output;
    int ch;
    while ((ch = encoder.getChar()) != EOF) {
        output.push_back(ch);
    }

    // Output should be non-empty (encoded data + EOD marker 128)
    EXPECT_FALSE(output.empty());

    // The last meaningful byte before EOF should be 128 (EOD)
    // Find the EOD marker
    bool foundEOD = false;
    for (int val : output) {
        if (val == 128) {
            foundEOD = true;
        }
    }
    EXPECT_TRUE(foundEOD);
}

// Test with all different characters (literal run)
TEST_F(RunLengthEncoderTest_222, AllDifferentCharacters_222) {
    const char data[] = "ABCDEFGHIJ";
    auto memStream = createMemStream(data, 10);
    RunLengthEncoder encoder(memStream.get());
    encoder.rewind();

    std::vector<int> output;
    int ch;
    while ((ch = encoder.getChar()) != EOF) {
        output.push_back(ch);
    }

    EXPECT_FALSE(output.empty());
}

// Test with single byte input
TEST_F(RunLengthEncoderTest_222, SingleByteInput_222) {
    const char data[] = "X";
    auto memStream = createMemStream(data, 1);
    RunLengthEncoder encoder(memStream.get());
    encoder.rewind();

    std::vector<int> output;
    int ch;
    while ((ch = encoder.getChar()) != EOF) {
        output.push_back(ch);
    }

    // Should produce some encoded output
    EXPECT_FALSE(output.empty());
}

// Test with binary data including zero bytes
TEST_F(RunLengthEncoderTest_222, BinaryDataWithZeros_222) {
    char data[8] = {0, 0, 0, 0, 1, 2, 3, 4};
    auto memStream = createMemStream(data, 8);
    RunLengthEncoder encoder(memStream.get());
    encoder.rewind();

    std::vector<int> output;
    int ch;
    while ((ch = encoder.getChar()) != EOF) {
        output.push_back(ch);
        if (output.size() > 200) break; // Safety guard
    }

    EXPECT_FALSE(output.empty());
}

// Test with large input (128 bytes of same character)
TEST_F(RunLengthEncoderTest_222, LargeRepeatedRun_222) {
    char data[128];
    memset(data, 'Z', 128);
    auto memStream = createMemStream(data, 128);
    RunLengthEncoder encoder(memStream.get());
    encoder.rewind();

    std::vector<int> output;
    int ch;
    while ((ch = encoder.getChar()) != EOF) {
        output.push_back(ch);
        if (output.size() > 500) break; // Safety guard
    }

    EXPECT_FALSE(output.empty());
}

// Test lookChar after reading everything returns EOF
TEST_F(RunLengthEncoderTest_222, LookCharAfterEOF_222) {
    const char data[] = "AB";
    auto memStream = createMemStream(data, 2);
    RunLengthEncoder encoder(memStream.get());
    encoder.rewind();

    // Consume all output
    int ch;
    while ((ch = encoder.getChar()) != EOF) {
        // consume
    }

    // Now lookChar should return EOF
    EXPECT_EQ(encoder.lookChar(), EOF);
}

// Test getChar after EOF returns EOF repeatedly
TEST_F(RunLengthEncoderTest_222, GetCharAfterEOFRepeated_222) {
    const char data[] = "A";
    auto memStream = createMemStream(data, 1);
    RunLengthEncoder encoder(memStream.get());
    encoder.rewind();

    // Consume all
    while (encoder.getChar() != EOF) {}

    EXPECT_EQ(encoder.getChar(), EOF);
    EXPECT_EQ(encoder.getChar(), EOF);
}

// Test mixed runs - alternating repeated and non-repeated
TEST_F(RunLengthEncoderTest_222, MixedRuns_222) {
    const char data[] = "AAABBBCDE";
    auto memStream = createMemStream(data, 9);
    RunLengthEncoder encoder(memStream.get());
    encoder.rewind();

    std::vector<int> output;
    int ch;
    while ((ch = encoder.getChar()) != EOF) {
        output.push_back(ch);
        if (output.size() > 200) break;
    }

    EXPECT_FALSE(output.empty());
}

// Test that lookChar followed by getChar returns the same value
TEST_F(RunLengthEncoderTest_222, LookCharThenGetChar_222) {
    const char data[] = "Test data for encoding";
    auto memStream = createMemStream(data, 22);
    RunLengthEncoder encoder(memStream.get());
    encoder.rewind();

    for (int i = 0; i < 5; i++) {
        int looked = encoder.lookChar();
        int got = encoder.getChar();
        EXPECT_EQ(looked, got);
        if (looked == EOF) break;
    }
}

// Test with data at exactly 128 bytes (max run length for RLE)
TEST_F(RunLengthEncoderTest_222, ExactMaxRunLength_222) {
    char data[128];
    for (int i = 0; i < 128; i++) {
        data[i] = static_cast<char>(i % 256);
    }
    auto memStream = createMemStream(data, 128);
    RunLengthEncoder encoder(memStream.get());
    encoder.rewind();

    std::vector<int> output;
    int ch;
    while ((ch = encoder.getChar()) != EOF) {
        output.push_back(ch);
        if (output.size() > 500) break;
    }

    EXPECT_FALSE(output.empty());
}

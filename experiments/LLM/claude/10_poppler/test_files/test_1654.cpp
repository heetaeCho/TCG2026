#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "FlateEncoder.h"
#include "Stream.h"
#include <memory>
#include <string>
#include <optional>

// We need a concrete Stream to pass to FlateEncoder.
// MemStream is a concrete Stream class available in poppler.

class FlateEncoderTest_1654 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }

    std::unique_ptr<FlateEncoder> createEncoder(const char *data, int len) {
        // Create a MemStream from the data. MemStream takes ownership semantics vary,
        // so we use a persistent buffer.
        buf_.assign(data, data + len);
        Object dictObj;
        auto *memStream = new MemStream(buf_.data(), 0, len, std::move(dictObj));
        memStream->reset();
        return std::make_unique<FlateEncoder>(memStream);
    }

    std::vector<char> buf_;
};

// Test that isEncoder returns true
TEST_F(FlateEncoderTest_1654, IsEncoderReturnsTrue_1654) {
    auto encoder = createEncoder("hello", 5);
    EXPECT_TRUE(encoder->isEncoder());
}

// Test that getKind returns the expected stream kind for FlateEncoder
TEST_F(FlateEncoderTest_1654, GetKindReturnsCorrectKind_1654) {
    auto encoder = createEncoder("hello", 5);
    EXPECT_EQ(encoder->getKind(), streamFlate);
}

// Test that isBinary returns true (compressed data is binary)
TEST_F(FlateEncoderTest_1654, IsBinaryReturnsTrue_1654) {
    auto encoder = createEncoder("hello", 5);
    EXPECT_TRUE(encoder->isBinary());
    EXPECT_TRUE(encoder->isBinary(true));
    EXPECT_TRUE(encoder->isBinary(false));
}

// Test that getPSFilter returns nullopt (FlateEncoder typically doesn't support PS filter)
TEST_F(FlateEncoderTest_1654, GetPSFilterReturnsNullopt_1654) {
    auto encoder = createEncoder("hello", 5);
    auto result = encoder->getPSFilter(1, "");
    EXPECT_FALSE(result.has_value());
}

// Test that getChar returns valid data after encoding
TEST_F(FlateEncoderTest_1654, GetCharReturnsEncodedData_1654) {
    const char *input = "Hello, World!";
    int len = strlen(input);
    auto encoder = createEncoder(input, len);
    encoder->reset();

    int firstByte = encoder->getChar();
    // The first byte should not be EOF since we have input data
    EXPECT_NE(firstByte, EOF);
}

// Test that lookChar returns same value as subsequent getChar
TEST_F(FlateEncoderTest_1654, LookCharPeeksWithoutConsuming_1654) {
    const char *input = "Test data for encoding";
    int len = strlen(input);
    auto encoder = createEncoder(input, len);
    encoder->reset();

    int peeked = encoder->lookChar();
    int got = encoder->getChar();
    EXPECT_EQ(peeked, got);
}

// Test that encoding empty data eventually returns EOF
TEST_F(FlateEncoderTest_1654, EmptyInputEventuallyReturnsEOF_1654) {
    auto encoder = createEncoder("", 0);
    encoder->reset();

    // Even with empty input, zlib produces some header/trailer bytes
    // Eventually we must reach EOF
    int count = 0;
    int ch;
    while ((ch = encoder->getChar()) != EOF && count < 100000) {
        count++;
    }
    EXPECT_EQ(ch, EOF);
}

// Test that rewind/reset allows re-reading the encoded data
TEST_F(FlateEncoderTest_1654, RewindAllowsReReading_1654) {
    const char *input = "Rewind test data";
    int len = strlen(input);
    auto encoder = createEncoder(input, len);
    encoder->reset();

    // Read some bytes
    std::vector<int> firstRead;
    for (int i = 0; i < 5; i++) {
        int ch = encoder->getChar();
        firstRead.push_back(ch);
    }

    // Reset and read again
    encoder->reset();
    std::vector<int> secondRead;
    for (int i = 0; i < 5; i++) {
        int ch = encoder->getChar();
        secondRead.push_back(ch);
    }

    EXPECT_EQ(firstRead, secondRead);
}

// Test that encoding produces valid deflate output (starts with proper zlib header)
TEST_F(FlateEncoderTest_1654, OutputStartsWithZlibHeader_1654) {
    const char *input = "Some test data to encode with flate";
    int len = strlen(input);
    auto encoder = createEncoder(input, len);
    encoder->reset();

    int byte1 = encoder->getChar();
    int byte2 = encoder->getChar();

    // zlib header: first byte is typically 0x78 for deflate
    // CMF byte: CM=8 (deflate), CINFO varies
    EXPECT_NE(byte1, EOF);
    EXPECT_NE(byte2, EOF);
    // Check that the compression method nibble is 8 (deflate)
    EXPECT_EQ(byte1 & 0x0F, 8);
}

// Test reading all encoded data until EOF
TEST_F(FlateEncoderTest_1654, ReadAllEncodedDataUntilEOF_1654) {
    const char *input = "Complete read test";
    int len = strlen(input);
    auto encoder = createEncoder(input, len);
    encoder->reset();

    std::vector<unsigned char> encoded;
    int ch;
    while ((ch = encoder->getChar()) != EOF) {
        encoded.push_back(static_cast<unsigned char>(ch));
    }

    // Encoded data should be non-empty
    EXPECT_FALSE(encoded.empty());
    // Encoded output should have some reasonable size
    EXPECT_GT(encoded.size(), 0u);
}

// Test that after EOF, getChar continues to return EOF
TEST_F(FlateEncoderTest_1654, GetCharReturnsEOFRepeatedly_1654) {
    const char *input = "x";
    int len = 1;
    auto encoder = createEncoder(input, len);
    encoder->reset();

    // Read until EOF
    int ch;
    while ((ch = encoder->getChar()) != EOF) {
        // consume
    }

    // Subsequent calls should also return EOF
    EXPECT_EQ(encoder->getChar(), EOF);
    EXPECT_EQ(encoder->getChar(), EOF);
}

// Test that after EOF, lookChar also returns EOF
TEST_F(FlateEncoderTest_1654, LookCharReturnsEOFAfterEnd_1654) {
    const char *input = "y";
    int len = 1;
    auto encoder = createEncoder(input, len);
    encoder->reset();

    // Read until EOF
    while (encoder->getChar() != EOF) {
        // consume
    }

    EXPECT_EQ(encoder->lookChar(), EOF);
}

// Test with larger input data
TEST_F(FlateEncoderTest_1654, LargerInputProducesEncodedOutput_1654) {
    std::string largeInput(10000, 'A');
    auto encoder = createEncoder(largeInput.c_str(), largeInput.size());
    encoder->reset();

    std::vector<unsigned char> encoded;
    int ch;
    while ((ch = encoder->getChar()) != EOF) {
        encoded.push_back(static_cast<unsigned char>(ch));
    }

    // Compressed repeated data should be significantly smaller
    EXPECT_FALSE(encoded.empty());
    EXPECT_LT(encoded.size(), largeInput.size());
}

// Test with binary input data
TEST_F(FlateEncoderTest_1654, BinaryInputProducesOutput_1654) {
    char binaryData[256];
    for (int i = 0; i < 256; i++) {
        binaryData[i] = static_cast<char>(i);
    }
    auto encoder = createEncoder(binaryData, 256);
    encoder->reset();

    int firstByte = encoder->getChar();
    EXPECT_NE(firstByte, EOF);
}

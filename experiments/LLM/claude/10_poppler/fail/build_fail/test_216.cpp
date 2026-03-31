#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Stream.h"
#include <cstring>
#include <memory>

// A simple MemStream-based test helper to create ASCII85Encoder instances
// We need a concrete Stream to pass to ASCII85Encoder

class ASCII85EncoderTest_216 : public ::testing::Test {
protected:
    std::unique_ptr<ASCII85Encoder> createEncoder(const char* data, int len) {
        // Create a MemStream from data. MemStream takes ownership semantics vary;
        // we need to ensure the buffer outlives the stream.
        char* buf = new char[len];
        memcpy(buf, data, len);
        Object dictObj;
        auto memStream = new MemStream(buf, 0, len, std::move(dictObj));
        memStream->reset();
        auto encoder = std::make_unique<ASCII85Encoder>(memStream);
        encoder->reset();
        return encoder;
    }

    std::string readAll(ASCII85Encoder* encoder) {
        std::string result;
        int ch;
        while ((ch = encoder->getChar()) != EOF) {
            result += static_cast<char>(ch);
        }
        return result;
    }
};

TEST_F(ASCII85EncoderTest_216, EmptyInput_216) {
    auto encoder = createEncoder("", 0);
    // For empty input, ASCII85 should at minimum produce the end-of-data marker "~>"
    std::string output = readAll(encoder.get());
    // The output should end with "~>"
    ASSERT_GE(output.size(), 2u);
    EXPECT_EQ(output.substr(output.size() - 2), "~>");
}

TEST_F(ASCII85EncoderTest_216, LookCharDoesNotConsume_216) {
    auto encoder = createEncoder("A", 1);
    int first = encoder->lookChar();
    int second = encoder->lookChar();
    EXPECT_EQ(first, second);
    // Now getChar should return the same character
    int third = encoder->getChar();
    EXPECT_EQ(first, third);
}

TEST_F(ASCII85EncoderTest_216, GetCharConsumesCharacter_216) {
    auto encoder = createEncoder("AB", 2);
    int first = encoder->getChar();
    int second = encoder->getChar();
    // They might or might not be the same, but after consuming all, we should get EOF eventually
    EXPECT_NE(first, EOF);
    // Continue reading until EOF
    std::string remaining;
    remaining += static_cast<char>(first);
    remaining += static_cast<char>(second);
    int ch;
    while ((ch = encoder->getChar()) != EOF) {
        remaining += static_cast<char>(ch);
    }
    // Should end with ~>
    ASSERT_GE(remaining.size(), 2u);
    EXPECT_EQ(remaining.substr(remaining.size() - 2), "~>");
}

TEST_F(ASCII85EncoderTest_216, SingleByteInput_216) {
    auto encoder = createEncoder("X", 1);
    std::string output = readAll(encoder.get());
    // Output should be valid ASCII85 ending with ~>
    EXPECT_GE(output.size(), 2u);
    EXPECT_EQ(output.substr(output.size() - 2), "~>");
    // All characters should be printable ASCII or within ASCII85 range
    for (size_t i = 0; i < output.size() - 2; i++) {
        unsigned char c = output[i];
        // ASCII85 uses characters '!' (33) to 'u' (117), plus 'z' for all-zero groups
        EXPECT_TRUE((c >= '!' && c <= 'u') || c == 'z' || c == '~' || c == '>');
    }
}

TEST_F(ASCII85EncoderTest_216, FourByteAlignedInput_216) {
    // 4 bytes should encode to exactly 5 ASCII85 characters + "~>"
    auto encoder = createEncoder("Test", 4);
    std::string output = readAll(encoder.get());
    EXPECT_EQ(output.substr(output.size() - 2), "~>");
}

TEST_F(ASCII85EncoderTest_216, AllZeroBytes_216) {
    // Four zero bytes should encode to 'z' in ASCII85
    char zeros[4] = {0, 0, 0, 0};
    auto encoder = createEncoder(zeros, 4);
    std::string output = readAll(encoder.get());
    // Should contain 'z' followed by "~>"
    EXPECT_EQ(output, "z~>");
}

TEST_F(ASCII85EncoderTest_216, LargerInput_216) {
    const char* data = "Hello, World! This is a test of ASCII85 encoding.";
    int len = strlen(data);
    auto encoder = createEncoder(data, len);
    std::string output = readAll(encoder.get());
    EXPECT_GE(output.size(), 2u);
    EXPECT_EQ(output.substr(output.size() - 2), "~>");
}

TEST_F(ASCII85EncoderTest_216, LookCharReturnsEOFWhenExhausted_216) {
    auto encoder = createEncoder("A", 1);
    // Consume all
    while (encoder->getChar() != EOF) {
    }
    // Now lookChar should return EOF
    EXPECT_EQ(encoder->lookChar(), EOF);
}

TEST_F(ASCII85EncoderTest_216, GetCharReturnsEOFWhenExhausted_216) {
    auto encoder = createEncoder("B", 1);
    while (encoder->getChar() != EOF) {
    }
    // Subsequent getChar should also return EOF
    EXPECT_EQ(encoder->getChar(), EOF);
    EXPECT_EQ(encoder->getChar(), EOF);
}

TEST_F(ASCII85EncoderTest_216, GetKind_216) {
    auto encoder = createEncoder("x", 1);
    // ASCII85Encoder should report its kind
    StreamKind kind = encoder->getKind();
    EXPECT_EQ(kind, strASCII85);
}

TEST_F(ASCII85EncoderTest_216, IsEncoder_216) {
    auto encoder = createEncoder("x", 1);
    EXPECT_TRUE(encoder->isEncoder());
}

TEST_F(ASCII85EncoderTest_216, IsBinary_216) {
    auto encoder = createEncoder("x", 1);
    // ASCII85 encoder produces text output, so isBinary should be false
    EXPECT_FALSE(encoder->isBinary());
}

TEST_F(ASCII85EncoderTest_216, RewindAndReread_216) {
    const char* data = "ABCD";
    auto encoder = createEncoder(data, 4);
    std::string firstRead = readAll(encoder.get());

    // Rewind and read again
    bool rewound = encoder->reset();
    std::string secondRead = readAll(encoder.get());

    EXPECT_EQ(firstRead, secondRead);
}

TEST_F(ASCII85EncoderTest_216, ThreeByteInput_216) {
    // 3 bytes (not aligned to 4) should produce 4 ASCII85 chars + "~>"
    auto encoder = createEncoder("ABC", 3);
    std::string output = readAll(encoder.get());
    EXPECT_EQ(output.substr(output.size() - 2), "~>");
}

TEST_F(ASCII85EncoderTest_216, TwoByteInput_216) {
    auto encoder = createEncoder("AB", 2);
    std::string output = readAll(encoder.get());
    EXPECT_EQ(output.substr(output.size() - 2), "~>");
}

TEST_F(ASCII85EncoderTest_216, FiveByteInput_216) {
    // 5 bytes = 4 + 1, testing boundary between groups
    auto encoder = createEncoder("ABCDE", 5);
    std::string output = readAll(encoder.get());
    EXPECT_EQ(output.substr(output.size() - 2), "~>");
}

TEST_F(ASCII85EncoderTest_216, AllOnesInput_216) {
    // Four 0xFF bytes
    char data[4] = {(char)0xFF, (char)0xFF, (char)0xFF, (char)0xFF};
    auto encoder = createEncoder(data, 4);
    std::string output = readAll(encoder.get());
    // Should encode to "s8W-!" followed by "~>"
    EXPECT_EQ(output.substr(output.size() - 2), "~>");
    // 'z' should NOT appear since it's not all zeros
    EXPECT_EQ(output.find('z'), std::string::npos);
}

TEST_F(ASCII85EncoderTest_216, EightZeroBytes_216) {
    // Two groups of four zeros should give "zz~>"
    char data[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    auto encoder = createEncoder(data, 8);
    std::string output = readAll(encoder.get());
    EXPECT_EQ(output, "zz~>");
}

TEST_F(ASCII85EncoderTest_216, OutputCharactersInValidRange_216) {
    const char* data = "The quick brown fox jumps over the lazy dog";
    int len = strlen(data);
    auto encoder = createEncoder(data, len);
    std::string output = readAll(encoder.get());

    // All characters before "~>" should be in valid ASCII85 range
    for (size_t i = 0; i < output.size() - 2; i++) {
        unsigned char c = output[i];
        bool valid = (c >= '!' && c <= 'u') || c == 'z';
        EXPECT_TRUE(valid) << "Invalid character at position " << i << ": " << (int)c;
    }
}

TEST_F(ASCII85EncoderTest_216, GetPSFilter_216) {
    auto encoder = createEncoder("x", 1);
    auto result = encoder->getPSFilter(1, "");
    // getPSFilter for encoder may return nullopt or a value; just test it doesn't crash
    // Based on typical encoder behavior, it likely returns nullopt
}

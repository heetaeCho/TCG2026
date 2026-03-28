#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Stream.h"

// We need a concrete Stream to pass to ASCII85Encoder.
// Using MemStream which is typically available in poppler.

class ASCII85EncoderTest_219 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}

    // Helper to create an ASCII85Encoder from raw data
    std::unique_ptr<ASCII85Encoder> createEncoder(const char* data, int len) {
        // MemStream takes ownership-like semantics; we need to keep the buffer alive
        auto* buf = new char[len];
        memcpy(buf, data, len);
        Object obj;
        auto* memStream = new MemStream(buf, 0, len, std::move(obj));
        memStream->reset();
        return std::make_unique<ASCII85Encoder>(memStream);
    }

    std::string readAll(ASCII85Encoder* encoder) {
        std::string result;
        encoder->reset();
        int c;
        while ((c = encoder->getChar()) != EOF) {
            result.push_back(static_cast<char>(c));
        }
        return result;
    }
};

// Test that isEncoder returns true
TEST_F(ASCII85EncoderTest_219, IsEncoderReturnsTrue_219) {
    auto encoder = createEncoder("", 0);
    EXPECT_TRUE(encoder->isEncoder());
}

// Test that getKind returns the expected stream kind
TEST_F(ASCII85EncoderTest_219, GetKindReturnsCorrectKind_219) {
    auto encoder = createEncoder("test", 4);
    StreamKind kind = encoder->getKind();
    EXPECT_EQ(kind, strWeird);
}

// Test encoding of empty input
TEST_F(ASCII85EncoderTest_219, EmptyInputProducesEOD_219) {
    auto encoder = createEncoder("", 0);
    std::string output = readAll(encoder.get());
    // ASCII85 encoding of empty input should produce end-of-data marker "~>"
    EXPECT_EQ(output, "~>");
}

// Test encoding of a single byte
TEST_F(ASCII85EncoderTest_219, SingleByteEncoding_219) {
    const char data[] = {0x00};
    auto encoder = createEncoder(data, 1);
    std::string output = readAll(encoder.get());
    // Should end with "~>"
    EXPECT_GE(output.size(), 2u);
    EXPECT_EQ(output.substr(output.size() - 2), "~>");
}

// Test encoding of four zero bytes (special 'z' encoding in ASCII85)
TEST_F(ASCII85EncoderTest_219, FourZeroBytesEncoding_219) {
    const char data[] = {0x00, 0x00, 0x00, 0x00};
    auto encoder = createEncoder(data, 4);
    std::string output = readAll(encoder.get());
    // Four zero bytes in ASCII85 are typically encoded as 'z'
    // Output should contain 'z' and end with "~>"
    EXPECT_NE(output.find('z'), std::string::npos);
    EXPECT_EQ(output.substr(output.size() - 2), "~>");
}

// Test encoding of known input "Man "
TEST_F(ASCII85EncoderTest_219, KnownInputEncoding_219) {
    // "Man " in ASCII85 is "9jqo^"
    const char data[] = "Man ";
    auto encoder = createEncoder(data, 4);
    std::string output = readAll(encoder.get());
    // The output should start with the ASCII85 encoding and end with "~>"
    EXPECT_EQ(output.substr(output.size() - 2), "~>");
    EXPECT_GE(output.size(), 7u); // At least 5 encoded chars + "~>"
}

// Test lookChar does not consume the character
TEST_F(ASCII85EncoderTest_219, LookCharDoesNotConsume_219) {
    const char data[] = "Hello";
    auto encoder = createEncoder(data, 5);
    encoder->reset();

    int first = encoder->lookChar();
    int second = encoder->lookChar();
    EXPECT_EQ(first, second);

    // getChar should return the same character
    int third = encoder->getChar();
    EXPECT_EQ(first, third);
}

// Test isBinary returns false (ASCII85 is text encoding)
TEST_F(ASCII85EncoderTest_219, IsBinaryReturnsFalse_219) {
    auto encoder = createEncoder("test", 4);
    EXPECT_FALSE(encoder->isBinary(true));
    EXPECT_FALSE(encoder->isBinary(false));
}

// Test getPSFilter returns nullopt for ASCII85Encoder (encoders typically return nullopt)
TEST_F(ASCII85EncoderTest_219, GetPSFilterReturnsNullopt_219) {
    auto encoder = createEncoder("test", 4);
    auto result = encoder->getPSFilter(1, "");
    // Encoders typically don't support PS filters
    EXPECT_FALSE(result.has_value());
}

// Test rewind functionality
TEST_F(ASCII85EncoderTest_219, RewindAllowsReReading_219) {
    const char data[] = "Test";
    auto encoder = createEncoder(data, 4);

    std::string output1 = readAll(encoder.get());

    encoder->reset();
    std::string output2 = readAll(encoder.get());

    EXPECT_EQ(output1, output2);
}

// Test encoding of longer input
TEST_F(ASCII85EncoderTest_219, LongerInputEncoding_219) {
    const char data[] = "The quick brown fox jumps over the lazy dog";
    auto encoder = createEncoder(data, strlen(data));
    std::string output = readAll(encoder.get());

    // Output should end with "~>"
    EXPECT_EQ(output.substr(output.size() - 2), "~>");
    // Output should be longer than input (ASCII85 has ~25% overhead)
    EXPECT_GT(output.size(), strlen(data));
}

// Test encoding of all 0xFF bytes
TEST_F(ASCII85EncoderTest_219, AllFFBytesEncoding_219) {
    const char data[] = {(char)0xFF, (char)0xFF, (char)0xFF, (char)0xFF};
    auto encoder = createEncoder(data, 4);
    std::string output = readAll(encoder.get());

    // Four 0xFF bytes encode to "s8W-!" in ASCII85
    EXPECT_EQ(output.substr(output.size() - 2), "~>");
    EXPECT_GE(output.size(), 7u);
}

// Test that output characters are in valid ASCII85 range
TEST_F(ASCII85EncoderTest_219, OutputCharsInValidRange_219) {
    const char data[] = "Hello, World!";
    auto encoder = createEncoder(data, strlen(data));
    encoder->reset();

    int c;
    while ((c = encoder->getChar()) != EOF) {
        // Valid ASCII85 chars: '!' (33) to 'u' (117), 'z' (122), '~' (126), '>' (62)
        bool valid = (c >= '!' && c <= 'u') || c == 'z' || c == '~' || c == '>';
        EXPECT_TRUE(valid) << "Invalid character: " << c << " '" << (char)c << "'";
    }
}

// Test encoding of two bytes (partial group)
TEST_F(ASCII85EncoderTest_219, TwoBytesEncoding_219) {
    const char data[] = {0x41, 0x42}; // "AB"
    auto encoder = createEncoder(data, 2);
    std::string output = readAll(encoder.get());

    EXPECT_EQ(output.substr(output.size() - 2), "~>");
    // Partial group of 2 bytes should produce 3 encoded chars + "~>"
    EXPECT_GE(output.size(), 5u);
}

// Test encoding of three bytes (partial group)
TEST_F(ASCII85EncoderTest_219, ThreeBytesEncoding_219) {
    const char data[] = {0x41, 0x42, 0x43}; // "ABC"
    auto encoder = createEncoder(data, 3);
    std::string output = readAll(encoder.get());

    EXPECT_EQ(output.substr(output.size() - 2), "~>");
}

// Test getChar returns EOF after all data consumed
TEST_F(ASCII85EncoderTest_219, GetCharReturnsEOFAfterAllData_219) {
    const char data[] = "A";
    auto encoder = createEncoder(data, 1);
    encoder->reset();

    // Read until EOF
    while (encoder->getChar() != EOF) {}

    // Further reads should still return EOF
    EXPECT_EQ(encoder->getChar(), EOF);
    EXPECT_EQ(encoder->getChar(), EOF);
}

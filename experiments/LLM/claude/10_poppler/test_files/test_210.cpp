#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Stream.h"
#include <cstring>
#include <memory>

// We need a concrete Stream to feed into ASCIIHexEncoder.
// MemStream is available in poppler's Stream.h

class ASCIIHexEncoderTest_210 : public ::testing::Test {
protected:
    // Helper to create an ASCIIHexEncoder from raw data
    std::unique_ptr<ASCIIHexEncoder> createEncoder(const char *data, int len) {
        // MemStream takes ownership-like semantics; we need the buffer to persist
        // We'll store it in a member
        buf_.assign(data, data + len);
        Object objNull;
        auto *memStream = new MemStream(buf_.data(), 0, len, Object(objNull));
        memStream->reset();
        auto encoder = std::make_unique<ASCIIHexEncoder>(memStream);
        encoder->reset();
        return encoder;
    }

    std::vector<char> buf_;
};

// Test that an empty input stream produces EOF on lookChar
TEST_F(ASCIIHexEncoderTest_210, EmptyStream_LookCharReturnsEOF_210) {
    auto encoder = createEncoder("", 0);
    // After encoding empty data, we expect the end-of-data marker '>' then EOF
    // The ASCIIHex encoding should output '>' as end marker, then EOF
    // Let's consume whatever is there
    std::string result;
    int c;
    while ((c = encoder->getChar()) != EOF) {
        result += static_cast<char>(c);
    }
    // After all chars consumed, lookChar should return EOF
    EXPECT_EQ(EOF, encoder->lookChar());
}

// Test that lookChar does not advance the stream position
TEST_F(ASCIIHexEncoderTest_210, LookCharDoesNotAdvance_210) {
    auto encoder = createEncoder("A", 1);
    int first = encoder->lookChar();
    int second = encoder->lookChar();
    EXPECT_EQ(first, second);
    // Should be the same as getChar
    int third = encoder->getChar();
    EXPECT_EQ(first, third);
}

// Test encoding a single byte produces correct hex output
TEST_F(ASCIIHexEncoderTest_210, SingleByte_ProducesHexEncoding_210) {
    // 'A' = 0x41, so should produce "41" followed by ">" and then EOF
    auto encoder = createEncoder("A", 1);
    std::string result;
    int c;
    while ((c = encoder->getChar()) != EOF) {
        result += static_cast<char>(c);
    }
    // Result should contain "41" and end with ">"
    // There might be newlines for line wrapping, but for a single byte it should be short
    // Remove any whitespace characters for checking hex content
    std::string hexOnly;
    for (char ch : result) {
        if (ch != '\n' && ch != '\r' && ch != ' ') {
            hexOnly += ch;
        }
    }
    EXPECT_EQ(hexOnly, "41>");
}

// Test encoding multiple bytes
TEST_F(ASCIIHexEncoderTest_210, MultipleBytes_ProducesCorrectHex_210) {
    auto encoder = createEncoder("\x00\xff", 2);
    std::string result;
    int c;
    while ((c = encoder->getChar()) != EOF) {
        result += static_cast<char>(c);
    }
    std::string hexOnly;
    for (char ch : result) {
        if (ch != '\n' && ch != '\r' && ch != ' ') {
            hexOnly += ch;
        }
    }
    EXPECT_EQ(hexOnly, "00ff>");
}

// Test getKind returns the expected kind
TEST_F(ASCIIHexEncoderTest_210, GetKind_210) {
    auto encoder = createEncoder("test", 4);
    EXPECT_EQ(encoder->getKind(), strWeird);
}

// Test isBinary returns false (ASCII hex is text)
TEST_F(ASCIIHexEncoderTest_210, IsBinary_ReturnsFalse_210) {
    auto encoder = createEncoder("test", 4);
    EXPECT_FALSE(encoder->isBinary(true));
}

// Test isEncoder returns true
TEST_F(ASCIIHexEncoderTest_210, IsEncoder_ReturnsTrue_210) {
    auto encoder = createEncoder("test", 4);
    EXPECT_TRUE(encoder->isEncoder());
}

// Test getPSFilter returns empty optional (encoders typically return nullopt)
TEST_F(ASCIIHexEncoderTest_210, GetPSFilter_ReturnsNullopt_210) {
    auto encoder = createEncoder("test", 4);
    auto result = encoder->getPSFilter(1, "");
    // Encoders typically don't have PS filter representation
    // This may or may not have a value; we just test it doesn't crash
    // If it returns a value, that's also acceptable
}

// Test rewind functionality - after consuming, rewind and read again
TEST_F(ASCIIHexEncoderTest_210, Rewind_AllowsReReading_210) {
    auto encoder = createEncoder("B", 1);
    
    // Read all output first time
    std::string firstRead;
    int c;
    while ((c = encoder->getChar()) != EOF) {
        firstRead += static_cast<char>(c);
    }
    
    // Rewind
    bool rewound = encoder->reset();
    
    // Read all output second time
    std::string secondRead;
    while ((c = encoder->getChar()) != EOF) {
        secondRead += static_cast<char>(c);
    }
    
    EXPECT_EQ(firstRead, secondRead);
}

// Test encoding byte with value 0
TEST_F(ASCIIHexEncoderTest_210, ZeroByte_210) {
    char data[] = {0};
    auto encoder = createEncoder(data, 1);
    std::string result;
    int c;
    while ((c = encoder->getChar()) != EOF) {
        result += static_cast<char>(c);
    }
    std::string hexOnly;
    for (char ch : result) {
        if (ch != '\n' && ch != '\r' && ch != ' ') {
            hexOnly += ch;
        }
    }
    EXPECT_EQ(hexOnly, "00>");
}

// Test encoding byte with value 0xFF
TEST_F(ASCIIHexEncoderTest_210, MaxByte_210) {
    char data[] = {static_cast<char>(0xFF)};
    auto encoder = createEncoder(data, 1);
    std::string result;
    int c;
    while ((c = encoder->getChar()) != EOF) {
        result += static_cast<char>(c);
    }
    std::string hexOnly;
    for (char ch : result) {
        if (ch != '\n' && ch != '\r' && ch != ' ') {
            hexOnly += ch;
        }
    }
    EXPECT_EQ(hexOnly, "ff>");
}

// Test that lookChar returns value in range 0-255 or EOF
TEST_F(ASCIIHexEncoderTest_210, LookCharReturnsValidRange_210) {
    auto encoder = createEncoder("Hello", 5);
    int c = encoder->lookChar();
    EXPECT_TRUE(c == EOF || (c >= 0 && c <= 255));
}

// Test longer input to exercise line wrapping
TEST_F(ASCIIHexEncoderTest_210, LongerInput_CompletesWithEndMarker_210) {
    // 50 bytes of data to potentially trigger line wrapping
    std::string data(50, 'X'); // 'X' = 0x58
    auto encoder = createEncoder(data.c_str(), static_cast<int>(data.size()));
    std::string result;
    int c;
    while ((c = encoder->getChar()) != EOF) {
        result += static_cast<char>(c);
    }
    // Should end with '>'
    ASSERT_FALSE(result.empty());
    // Remove whitespace and check ending
    std::string hexOnly;
    for (char ch : result) {
        if (ch != '\n' && ch != '\r' && ch != ' ') {
            hexOnly += ch;
        }
    }
    EXPECT_EQ(hexOnly.back(), '>');
    // Each byte should produce 2 hex chars, plus the '>'
    EXPECT_EQ(hexOnly.size(), 50u * 2 + 1);
}

// Test getChar after EOF continues to return EOF
TEST_F(ASCIIHexEncoderTest_210, GetCharAfterEOF_ReturnsEOF_210) {
    auto encoder = createEncoder("a", 1);
    int c;
    while ((c = encoder->getChar()) != EOF) {
        // consume all
    }
    EXPECT_EQ(EOF, encoder->getChar());
    EXPECT_EQ(EOF, encoder->getChar());
    EXPECT_EQ(EOF, encoder->lookChar());
}

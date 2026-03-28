#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Stream.h"
#include <cstring>
#include <vector>
#include <memory>

// We need a concrete Stream implementation to feed data into ASCIIHexEncoder.
// MemStream is available in poppler's Stream.h

class ASCIIHexEncoderTest_209 : public ::testing::Test {
protected:
    std::unique_ptr<ASCIIHexEncoder> createEncoder(const char* data, int len) {
        // We need to create a MemStream. MemStream takes ownership-like semantics
        // but we need to keep the buffer alive.
        char* buf = new char[len];
        memcpy(buf, data, len);
        buffers_.push_back(buf);

        Object objNull;
        auto memStream = new MemStream(buf, 0, len, Object(objNull));
        auto encoder = std::make_unique<ASCIIHexEncoder>(memStream);
        return encoder;
    }

    void TearDown() override {
        for (auto* b : buffers_) {
            delete[] b;
        }
        buffers_.clear();
    }

    std::vector<char*> buffers_;
};

// Test that ASCIIHexEncoder encodes empty input properly (should return '>' then EOF)
TEST_F(ASCIIHexEncoderTest_209, EmptyInput_209) {
    auto encoder = createEncoder("", 0);
    encoder->reset();

    // For empty input, we expect the end-of-data marker '>' followed by EOF
    std::string result;
    int c;
    while ((c = encoder->getChar()) != EOF) {
        result += static_cast<char>(c);
    }
    // The result should end with '>'
    ASSERT_FALSE(result.empty());
    EXPECT_EQ(result.back(), '>');
}

// Test encoding a single byte
TEST_F(ASCIIHexEncoderTest_209, SingleByte_209) {
    const char data[] = {'\x0a'};
    auto encoder = createEncoder(data, 1);
    encoder->reset();

    std::string result;
    int c;
    while ((c = encoder->getChar()) != EOF) {
        result += static_cast<char>(c);
    }

    // 0x0a should encode to "0a" followed by ">"
    // Check that result contains "0a" and ends with '>'
    EXPECT_NE(result.find("0a"), std::string::npos);
    EXPECT_EQ(result.back(), '>');
}

// Test encoding known bytes and verifying hex output
TEST_F(ASCIIHexEncoderTest_209, KnownBytes_209) {
    const char data[] = {'\xff', '\x00', '\xab'};
    auto encoder = createEncoder(data, 3);
    encoder->reset();

    std::string result;
    int c;
    while ((c = encoder->getChar()) != EOF) {
        result += static_cast<char>(c);
    }

    // Should contain hex representations
    // ff, 00, ab followed by >
    // Remove any whitespace/newlines for checking
    std::string cleaned;
    for (char ch : result) {
        if (ch != '\n' && ch != '\r' && ch != ' ') {
            cleaned += ch;
        }
    }
    EXPECT_EQ(cleaned.back(), '>');
    // Check the hex content
    EXPECT_NE(cleaned.find("ff"), std::string::npos);
    EXPECT_NE(cleaned.find("00"), std::string::npos);
    EXPECT_NE(cleaned.find("ab"), std::string::npos);
}

// Test that getChar returns EOF after all data is consumed
TEST_F(ASCIIHexEncoderTest_209, ReturnsEOFAfterEnd_209) {
    const char data[] = {'A'};
    auto encoder = createEncoder(data, 1);
    encoder->reset();

    int c;
    while ((c = encoder->getChar()) != EOF) {
        // consume all
    }
    // Subsequent calls should also return EOF
    EXPECT_EQ(encoder->getChar(), EOF);
    EXPECT_EQ(encoder->getChar(), EOF);
}

// Test lookChar doesn't advance the stream
TEST_F(ASCIIHexEncoderTest_209, LookCharDoesNotAdvance_209) {
    const char data[] = {'X'};
    auto encoder = createEncoder(data, 1);
    encoder->reset();

    int first = encoder->lookChar();
    int second = encoder->lookChar();
    EXPECT_EQ(first, second);

    // Now getChar should return the same
    int third = encoder->getChar();
    EXPECT_EQ(first, third);
}

// Test getKind returns the expected stream kind
TEST_F(ASCIIHexEncoderTest_209, GetKind_209) {
    const char data[] = {'A'};
    auto encoder = createEncoder(data, 1);
    StreamKind kind = encoder->getKind();
    // ASCIIHexEncoder should report its kind
    EXPECT_EQ(kind, strASCIIHex);
}

// Test isEncoder returns true
TEST_F(ASCIIHexEncoderTest_209, IsEncoder_209) {
    const char data[] = {'A'};
    auto encoder = createEncoder(data, 1);
    EXPECT_TRUE(encoder->isEncoder());
}

// Test isBinary returns false (hex encoding produces ASCII)
TEST_F(ASCIIHexEncoderTest_209, IsBinary_209) {
    const char data[] = {'A'};
    auto encoder = createEncoder(data, 1);
    EXPECT_FALSE(encoder->isBinary(true));
    EXPECT_FALSE(encoder->isBinary(false));
}

// Test that rewind works and we can re-read the same data
TEST_F(ASCIIHexEncoderTest_209, Rewind_209) {
    const char data[] = {'H', 'i'};
    auto encoder = createEncoder(data, 2);
    encoder->reset();

    std::string firstPass;
    int c;
    while ((c = encoder->getChar()) != EOF) {
        firstPass += static_cast<char>(c);
    }

    // Rewind and read again
    bool rewound = encoder->rewind();
    if (rewound) {
        std::string secondPass;
        while ((c = encoder->getChar()) != EOF) {
            secondPass += static_cast<char>(c);
        }
        EXPECT_EQ(firstPass, secondPass);
    }
}

// Test encoding printable ASCII characters
TEST_F(ASCIIHexEncoderTest_209, PrintableASCII_209) {
    const char data[] = "Hello";
    auto encoder = createEncoder(data, 5);  // exclude null terminator
    encoder->reset();

    std::string result;
    int c;
    while ((c = encoder->getChar()) != EOF) {
        result += static_cast<char>(c);
    }

    // 'H' = 0x48, 'e' = 0x65, 'l' = 0x6c, 'l' = 0x6c, 'o' = 0x6f
    std::string cleaned;
    for (char ch : result) {
        if (ch != '\n' && ch != '\r' && ch != ' ') {
            cleaned += ch;
        }
    }
    // Should end with >
    EXPECT_EQ(cleaned.back(), '>');
    // Remove trailing >
    std::string hex = cleaned.substr(0, cleaned.size() - 1);
    EXPECT_EQ(hex, "48656c6c6f");
}

// Test that all output characters are valid hex digits, newlines, or '>'
TEST_F(ASCIIHexEncoderTest_209, OutputContainsOnlyValidChars_209) {
    // Use all byte values 0-255
    char data[256];
    for (int i = 0; i < 256; i++) {
        data[i] = static_cast<char>(i);
    }
    auto encoder = createEncoder(data, 256);
    encoder->reset();

    int c;
    while ((c = encoder->getChar()) != EOF) {
        char ch = static_cast<char>(c & 0xff);
        bool validHexChar = (ch >= '0' && ch <= '9') || (ch >= 'a' && ch <= 'f') || (ch >= 'A' && ch <= 'F');
        bool isNewline = (ch == '\n' || ch == '\r');
        bool isEndMarker = (ch == '>');
        EXPECT_TRUE(validHexChar || isNewline || isEndMarker)
            << "Unexpected character: " << (int)ch << " '" << ch << "'";
    }
}

// Test getPSFilter returns nullopt or empty (encoders typically don't support PS filters)
TEST_F(ASCIIHexEncoderTest_209, GetPSFilter_209) {
    const char data[] = {'A'};
    auto encoder = createEncoder(data, 1);
    auto result = encoder->getPSFilter(1, "");
    // Encoders typically return nullopt for getPSFilter
    EXPECT_FALSE(result.has_value());
}

// Test encoding larger data to verify line breaking behavior
TEST_F(ASCIIHexEncoderTest_209, LargerData_209) {
    // Create a larger buffer
    const int size = 1000;
    char data[size];
    for (int i = 0; i < size; i++) {
        data[i] = static_cast<char>(i % 256);
    }
    auto encoder = createEncoder(data, size);
    encoder->reset();

    int charCount = 0;
    int c;
    while ((c = encoder->getChar()) != EOF) {
        charCount++;
    }
    // Each byte produces 2 hex chars, plus possible newlines, plus final '>'
    // At minimum we should have 2*size + 1 characters (without newlines)
    EXPECT_GE(charCount, 2 * size + 1);
}

// Test that getChar returns values in 0-255 range (& 0xff) before EOF
TEST_F(ASCIIHexEncoderTest_209, GetCharReturnsValidRange_209) {
    const char data[] = {'\x00', '\x7f', '\x80', '\xff'};
    auto encoder = createEncoder(data, 4);
    encoder->reset();

    int c;
    while ((c = encoder->getChar()) != EOF) {
        EXPECT_GE(c, 0);
        EXPECT_LE(c, 255);
    }
}

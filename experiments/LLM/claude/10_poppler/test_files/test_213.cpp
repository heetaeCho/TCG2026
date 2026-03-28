#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Stream.h"
#include <cstring>
#include <memory>

// We need a concrete Stream to feed into ASCIIHexEncoder.
// MemStream is available in poppler's Stream.h

class ASCIIHexEncoderTest_213 : public ::testing::Test {
protected:
    // Helper to create an ASCIIHexEncoder from raw data
    std::unique_ptr<ASCIIHexEncoder> createEncoder(const char *data, int len) {
        // MemStream takes ownership-like semantics; we need to keep the buffer alive
        // MemStream(const char *bufA, Goffset startA, Goffset lengthA, Object &&dictA)
        buf_.assign(data, data + len);
        Object dictObj;
        auto memStream = new MemStream(buf_.data(), 0, len, std::move(dictObj));
        auto encoder = std::make_unique<ASCIIHexEncoder>(memStream);
        return encoder;
    }

    std::vector<char> buf_;
};

TEST_F(ASCIIHexEncoderTest_213, IsEncoderReturnsTrue_213) {
    auto encoder = createEncoder("A", 1);
    EXPECT_TRUE(encoder->isEncoder());
}

TEST_F(ASCIIHexEncoderTest_213, GetKindReturnsCorrectKind_213) {
    auto encoder = createEncoder("A", 1);
    // ASCIIHexEncoder should report its kind
    StreamKind kind = encoder->getKind();
    EXPECT_EQ(kind, strASCIIHex);
}

TEST_F(ASCIIHexEncoderTest_213, IsBinaryReturnsFalse_213) {
    auto encoder = createEncoder("A", 1);
    // ASCII hex encoding produces ASCII text, not binary
    EXPECT_FALSE(encoder->isBinary(true));
    EXPECT_FALSE(encoder->isBinary(false));
}

TEST_F(ASCIIHexEncoderTest_213, GetPSFilterReturnsNullopt_213) {
    auto encoder = createEncoder("A", 1);
    // Encoders typically return nullopt for getPSFilter
    auto result = encoder->getPSFilter(1, "");
    EXPECT_FALSE(result.has_value());
}

TEST_F(ASCIIHexEncoderTest_213, EmptyInputProducesEndMarker_213) {
    auto encoder = createEncoder("", 0);
    encoder->reset();
    
    // For empty input, should get '>' as end-of-data marker then EOF
    int ch = encoder->getChar();
    EXPECT_EQ(ch, '>');
    
    ch = encoder->getChar();
    EXPECT_EQ(ch, EOF);
}

TEST_F(ASCIIHexEncoderTest_213, SingleByteEncoding_213) {
    // 'A' = 0x41, so should produce "41" then ">"
    auto encoder = createEncoder("A", 1);
    encoder->reset();
    
    std::string result;
    int ch;
    while ((ch = encoder->getChar()) != EOF) {
        result += static_cast<char>(ch);
    }
    
    // Should contain hex encoding of 'A' (41) followed by '>'
    EXPECT_NE(result.find("41"), std::string::npos);
    EXPECT_EQ(result.back(), '>');
}

TEST_F(ASCIIHexEncoderTest_213, MultiByteEncoding_213) {
    // "AB" = 0x41 0x42
    auto encoder = createEncoder("AB", 2);
    encoder->reset();
    
    std::string result;
    int ch;
    while ((ch = encoder->getChar()) != EOF) {
        result += static_cast<char>(ch);
    }
    
    // Should contain "4142" somewhere, ending with '>'
    EXPECT_NE(result.find("41"), std::string::npos);
    EXPECT_NE(result.find("42"), std::string::npos);
    EXPECT_EQ(result.back(), '>');
}

TEST_F(ASCIIHexEncoderTest_213, LookCharDoesNotConsume_213) {
    auto encoder = createEncoder("A", 1);
    encoder->reset();
    
    int first_look = encoder->lookChar();
    int second_look = encoder->lookChar();
    EXPECT_EQ(first_look, second_look);
    
    int get_ch = encoder->getChar();
    EXPECT_EQ(first_look, get_ch);
}

TEST_F(ASCIIHexEncoderTest_213, RewindResetsStream_213) {
    auto encoder = createEncoder("A", 1);
    encoder->reset();
    
    // Read all characters
    std::string first_pass;
    int ch;
    while ((ch = encoder->getChar()) != EOF) {
        first_pass += static_cast<char>(ch);
    }
    
    // Rewind and read again
    bool rewound = encoder->rewind();
    
    if (rewound) {
        std::string second_pass;
        while ((ch = encoder->getChar()) != EOF) {
            second_pass += static_cast<char>(ch);
        }
        EXPECT_EQ(first_pass, second_pass);
    }
}

TEST_F(ASCIIHexEncoderTest_213, NullByteEncoding_213) {
    // '\0' = 0x00
    const char data[] = {'\0'};
    auto encoder = createEncoder(data, 1);
    encoder->reset();
    
    std::string result;
    int ch;
    while ((ch = encoder->getChar()) != EOF) {
        result += static_cast<char>(ch);
    }
    
    // Should contain "00" followed by '>'
    EXPECT_NE(result.find("00"), std::string::npos);
    EXPECT_EQ(result.back(), '>');
}

TEST_F(ASCIIHexEncoderTest_213, HighByteEncoding_213) {
    // 0xFF
    const char data[] = {static_cast<char>(0xFF)};
    auto encoder = createEncoder(data, 1);
    encoder->reset();
    
    std::string result;
    int ch;
    while ((ch = encoder->getChar()) != EOF) {
        result += static_cast<char>(ch);
    }
    
    // Should contain "ff" or "FF" followed by '>'
    // Convert to lowercase for comparison
    std::string lower_result;
    for (char c : result) {
        lower_result += static_cast<char>(tolower(c));
    }
    EXPECT_NE(lower_result.find("ff"), std::string::npos);
    EXPECT_EQ(result.back(), '>');
}

TEST_F(ASCIIHexEncoderTest_213, AllHexDigitsPresent_213) {
    // Encode bytes that use all hex digits: 0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF
    const char data[] = {0x01, 0x23, 0x45, 0x67, 
                         static_cast<char>(0x89), static_cast<char>(0xAB), 
                         static_cast<char>(0xCD), static_cast<char>(0xEF)};
    auto encoder = createEncoder(data, 8);
    encoder->reset();
    
    std::string result;
    int ch;
    while ((ch = encoder->getChar()) != EOF) {
        result += static_cast<char>(ch);
    }
    
    EXPECT_EQ(result.back(), '>');
    // Each character in the output (except '>' and possible newlines) should be a hex digit
    for (size_t i = 0; i < result.size() - 1; i++) {
        char c = result[i];
        bool is_hex = isxdigit(c) || c == '\n' || c == '\r';
        EXPECT_TRUE(is_hex) << "Unexpected character: " << c << " at position " << i;
    }
}

TEST_F(ASCIIHexEncoderTest_213, OutputOnlyContainsValidChars_213) {
    const char data[] = "Hello, World!";
    auto encoder = createEncoder(data, 13);
    encoder->reset();
    
    std::string result;
    int ch;
    while ((ch = encoder->getChar()) != EOF) {
        result += static_cast<char>(ch);
    }
    
    // Output should only contain hex digits [0-9a-fA-F], '>', and possibly newlines
    for (char c : result) {
        bool valid = isxdigit(c) || c == '>' || c == '\n' || c == '\r';
        EXPECT_TRUE(valid) << "Invalid character in output: " << static_cast<int>(c);
    }
}

TEST_F(ASCIIHexEncoderTest_213, EOFAfterFullRead_213) {
    auto encoder = createEncoder("X", 1);
    encoder->reset();
    
    // Read until EOF
    int ch;
    while ((ch = encoder->getChar()) != EOF) {
        // consume
    }
    
    // Subsequent reads should still return EOF
    EXPECT_EQ(encoder->getChar(), EOF);
    EXPECT_EQ(encoder->getChar(), EOF);
}

TEST_F(ASCIIHexEncoderTest_213, LookCharAfterEOF_213) {
    auto encoder = createEncoder("", 0);
    encoder->reset();
    
    // Read the '>' marker
    encoder->getChar();
    
    // Now should be at EOF
    EXPECT_EQ(encoder->lookChar(), EOF);
    EXPECT_EQ(encoder->getChar(), EOF);
}

TEST_F(ASCIIHexEncoderTest_213, LongerDataLineWrapping_213) {
    // Create a longer input to test potential line wrapping behavior
    std::string longData(100, 'A');
    auto encoder = createEncoder(longData.c_str(), static_cast<int>(longData.size()));
    encoder->reset();
    
    std::string result;
    int ch;
    while ((ch = encoder->getChar()) != EOF) {
        result += static_cast<char>(ch);
    }
    
    // Should end with '>'
    EXPECT_EQ(result.back(), '>');
    
    // Count hex digits (excluding newlines and '>')
    int hexCount = 0;
    for (char c : result) {
        if (isxdigit(c)) {
            hexCount++;
        }
    }
    // Each input byte produces 2 hex digits
    EXPECT_EQ(hexCount, 200);
}

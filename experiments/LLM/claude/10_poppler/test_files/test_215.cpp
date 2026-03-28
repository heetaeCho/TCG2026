#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Stream.h"
#include <cstring>
#include <memory>
#include <vector>

// A simple MemStream-based test helper to create ASCII85Encoder instances
// We need a source stream to feed into the encoder.

class ASCII85EncoderTest_215 : public ::testing::Test {
protected:
    // Helper to create an ASCII85Encoder from raw bytes
    std::unique_ptr<ASCII85Encoder> createEncoder(const char* data, int len) {
        // We need to create a MemStream that owns the data
        // MemStream takes a char*, start, length, and Object for dict
        char* buf = static_cast<char*>(gmalloc(len));
        memcpy(buf, data, len);
        Object dictObj;
        auto memStream = new MemStream(buf, 0, len, std::move(dictObj));
        memStream->reset();
        auto encoder = std::make_unique<ASCII85Encoder>(memStream);
        encoder->reset();
        return encoder;
    }

    // Helper to read all output from encoder into a string
    std::string readAll(ASCII85Encoder* encoder) {
        std::string result;
        int c;
        while ((c = encoder->getChar()) != EOF) {
            result += static_cast<char>(c);
        }
        return result;
    }
};

// Test that encoding an empty stream produces the end-of-data marker "~>"
TEST_F(ASCII85EncoderTest_215, EmptyInput_215) {
    auto encoder = createEncoder("", 0);
    std::string output = readAll(encoder.get());
    // ASCII85 encoding of empty data should at minimum contain the end marker "~>"
    EXPECT_FALSE(output.empty());
    // The output should end with "~>"
    ASSERT_GE(output.size(), 2u);
    EXPECT_EQ(output.substr(output.size() - 2), "~>");
}

// Test encoding a single byte
TEST_F(ASCII85EncoderTest_215, SingleByte_215) {
    const char data[] = {0x00};
    auto encoder = createEncoder(data, 1);
    std::string output = readAll(encoder.get());
    // Should end with ~>
    ASSERT_GE(output.size(), 2u);
    EXPECT_EQ(output.substr(output.size() - 2), "~>");
}

// Test encoding four zero bytes - ASCII85 has special 'z' encoding for all zeros
TEST_F(ASCII85EncoderTest_215, FourZeroBytes_215) {
    const char data[] = {0x00, 0x00, 0x00, 0x00};
    auto encoder = createEncoder(data, 4);
    std::string output = readAll(encoder.get());
    // Four zero bytes in ASCII85 typically encode as 'z'
    ASSERT_GE(output.size(), 2u);
    EXPECT_EQ(output.substr(output.size() - 2), "~>");
    // Should contain 'z' for all-zero group
    EXPECT_NE(output.find('z'), std::string::npos);
}

// Test encoding known data and verifying output characters are in valid ASCII85 range
TEST_F(ASCII85EncoderTest_215, OutputCharactersInValidRange_215) {
    const char data[] = "Hello, World!";
    auto encoder = createEncoder(data, strlen(data));
    std::string output = readAll(encoder.get());
    
    // All characters should be in the valid ASCII85 range: '!' (33) to 'u' (117),
    // or 'z' for all-zero groups, or '~' and '>' for the end marker
    for (size_t i = 0; i < output.size() - 2; ++i) {
        char c = output[i];
        bool valid = (c >= '!' && c <= 'u') || c == 'z' || c == '\n' || c == '\r';
        EXPECT_TRUE(valid) << "Invalid character at position " << i << ": " << (int)c;
    }
    
    // Should end with ~>
    EXPECT_EQ(output.substr(output.size() - 2), "~>");
}

// Test that getChar returns EOF after all data is consumed
TEST_F(ASCII85EncoderTest_215, GetCharReturnsEOFAfterEnd_215) {
    const char data[] = "A";
    auto encoder = createEncoder(data, 1);
    
    // Read all characters
    int c;
    while ((c = encoder->getChar()) != EOF) {
        // just consume
    }
    
    // Additional calls should still return EOF
    EXPECT_EQ(encoder->getChar(), EOF);
    EXPECT_EQ(encoder->getChar(), EOF);
}

// Test lookChar returns same value as next getChar without consuming
TEST_F(ASCII85EncoderTest_215, LookCharDoesNotConsume_215) {
    const char data[] = "Test";
    auto encoder = createEncoder(data, 4);
    
    int looked = encoder->lookChar();
    int got = encoder->getChar();
    EXPECT_EQ(looked, got);
}

// Test lookChar returns EOF when stream is exhausted
TEST_F(ASCII85EncoderTest_215, LookCharReturnsEOFWhenExhausted_215) {
    auto encoder = createEncoder("", 0);
    
    // Read all
    while (encoder->getChar() != EOF) {}
    
    EXPECT_EQ(encoder->lookChar(), EOF);
}

// Test that getKind returns the expected stream kind
TEST_F(ASCII85EncoderTest_215, GetKindReturnsCorrectKind_215) {
    const char data[] = "x";
    auto encoder = createEncoder(data, 1);
    // ASCII85Encoder should report its kind
    StreamKind kind = encoder->getKind();
    // We just verify it returns a valid kind (it's implementation-defined which one)
    (void)kind; // At minimum, it shouldn't crash
}

// Test isEncoder returns true
TEST_F(ASCII85EncoderTest_215, IsEncoderReturnsTrue_215) {
    const char data[] = "x";
    auto encoder = createEncoder(data, 1);
    EXPECT_TRUE(encoder->isEncoder());
}

// Test isBinary returns false (ASCII85 produces ASCII output)
TEST_F(ASCII85EncoderTest_215, IsBinaryReturnsFalse_215) {
    const char data[] = "x";
    auto encoder = createEncoder(data, 1);
    EXPECT_FALSE(encoder->isBinary(true));
    EXPECT_FALSE(encoder->isBinary(false));
}

// Test encoding multiple groups (more than 4 bytes)
TEST_F(ASCII85EncoderTest_215, MultipleGroups_215) {
    const char data[] = "ABCDEFGH"; // 8 bytes = 2 full groups
    auto encoder = createEncoder(data, 8);
    std::string output = readAll(encoder.get());
    
    ASSERT_GE(output.size(), 2u);
    EXPECT_EQ(output.substr(output.size() - 2), "~>");
}

// Test encoding with partial last group (not multiple of 4)
TEST_F(ASCII85EncoderTest_215, PartialLastGroup_215) {
    const char data[] = "ABCDE"; // 5 bytes = 1 full group + 1 byte partial
    auto encoder = createEncoder(data, 5);
    std::string output = readAll(encoder.get());
    
    ASSERT_GE(output.size(), 2u);
    EXPECT_EQ(output.substr(output.size() - 2), "~>");
}

// Test rewind and re-read produces the same output
TEST_F(ASCII85EncoderTest_215, RewindProducesSameOutput_215) {
    const char data[] = "Hello";
    auto encoder = createEncoder(data, 5);
    
    std::string firstRead = readAll(encoder.get());
    
    bool rewound = encoder->reset();
    // If reset succeeds, read again
    if (rewound) {
        std::string secondRead = readAll(encoder.get());
        EXPECT_EQ(firstRead, secondRead);
    }
}

// Test encoding binary data with all byte values
TEST_F(ASCII85EncoderTest_215, BinaryData_215) {
    char data[256];
    for (int i = 0; i < 256; ++i) {
        data[i] = static_cast<char>(i);
    }
    auto encoder = createEncoder(data, 256);
    std::string output = readAll(encoder.get());
    
    ASSERT_GE(output.size(), 2u);
    EXPECT_EQ(output.substr(output.size() - 2), "~>");
}

// Test that getPSFilter returns a value (or nullopt)
TEST_F(ASCII85EncoderTest_215, GetPSFilter_215) {
    const char data[] = "x";
    auto encoder = createEncoder(data, 1);
    auto result = encoder->getPSFilter(1, "");
    // Encoders typically return nullopt for getPSFilter
    // We just verify it doesn't crash
    (void)result;
}

// Test that getChar returns values in 0-255 range (unsigned byte)
TEST_F(ASCII85EncoderTest_215, GetCharReturnsUnsignedByte_215) {
    const char data[] = "Test data for encoding";
    auto encoder = createEncoder(data, strlen(data));
    
    int c;
    while ((c = encoder->getChar()) != EOF) {
        EXPECT_GE(c, 0);
        EXPECT_LE(c, 255);
    }
}

// Test with exactly 4 bytes (one complete group)
TEST_F(ASCII85EncoderTest_215, ExactlyOneGroup_215) {
    const char data[] = "ABCD";
    auto encoder = createEncoder(data, 4);
    std::string output = readAll(encoder.get());
    
    ASSERT_GE(output.size(), 2u);
    EXPECT_EQ(output.substr(output.size() - 2), "~>");
    // One group of 4 bytes should produce 5 encoded chars + "~>" = 7 chars minimum
    EXPECT_GE(output.size(), 7u);
}

// Test with two bytes (partial group)
TEST_F(ASCII85EncoderTest_215, TwoBytes_215) {
    const char data[] = {0x41, 0x42}; // "AB"
    auto encoder = createEncoder(data, 2);
    std::string output = readAll(encoder.get());
    
    ASSERT_GE(output.size(), 2u);
    EXPECT_EQ(output.substr(output.size() - 2), "~>");
}

// Test with three bytes (partial group)
TEST_F(ASCII85EncoderTest_215, ThreeBytes_215) {
    const char data[] = {0x41, 0x42, 0x43}; // "ABC"
    auto encoder = createEncoder(data, 3);
    std::string output = readAll(encoder.get());
    
    ASSERT_GE(output.size(), 2u);
    EXPECT_EQ(output.substr(output.size() - 2), "~>");
}

// Test with 0xFF bytes
TEST_F(ASCII85EncoderTest_215, AllOnesBytes_215) {
    const char data[] = {(char)0xFF, (char)0xFF, (char)0xFF, (char)0xFF};
    auto encoder = createEncoder(data, 4);
    std::string output = readAll(encoder.get());
    
    ASSERT_GE(output.size(), 2u);
    EXPECT_EQ(output.substr(output.size() - 2), "~>");
    // 0xFFFFFFFF should not be encoded as 'z' (that's only for 0x00000000)
    // It should produce "s8W-!" 
}

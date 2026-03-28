#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Stream.h"

// We need a concrete Stream to pass to ASCII85Encoder's constructor.
// We'll use a minimal MemStream or similar approach.
// Based on the poppler codebase, we can use a MemStream as the underlying stream.

class ASCII85EncoderTest_214 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that getKind returns strWeird
TEST_F(ASCII85EncoderTest_214, GetKindReturnsStrWeird_214) {
    // Create a minimal underlying stream - use a MemStream with empty data
    const char data[] = "Hello, World!";
    auto obj = Object(objNull);
    MemStream *memStr = new MemStream(const_cast<char*>(data), 0, sizeof(data) - 1, std::move(obj));
    
    ASCII85Encoder encoder(memStr);
    
    EXPECT_EQ(encoder.getKind(), strWeird);
}

// Test that isEncoder returns true
TEST_F(ASCII85EncoderTest_214, IsEncoderReturnsTrue_214) {
    const char data[] = "Test";
    auto obj = Object(objNull);
    MemStream *memStr = new MemStream(const_cast<char*>(data), 0, sizeof(data) - 1, std::move(obj));
    
    ASCII85Encoder encoder(memStr);
    
    EXPECT_TRUE(encoder.isEncoder());
}

// Test that isBinary returns false (ASCII85 is text-based encoding)
TEST_F(ASCII85EncoderTest_214, IsBinaryReturnsFalse_214) {
    const char data[] = "Test";
    auto obj = Object(objNull);
    MemStream *memStr = new MemStream(const_cast<char*>(data), 0, sizeof(data) - 1, std::move(obj));
    
    ASCII85Encoder encoder(memStr);
    
    EXPECT_FALSE(encoder.isBinary(true));
    EXPECT_FALSE(encoder.isBinary(false));
}

// Test that getPSFilter returns empty optional (encoders typically don't have PS filters)
TEST_F(ASCII85EncoderTest_214, GetPSFilterReturnsNullopt_214) {
    const char data[] = "Test";
    auto obj = Object(objNull);
    MemStream *memStr = new MemStream(const_cast<char*>(data), 0, sizeof(data) - 1, std::move(obj));
    
    ASCII85Encoder encoder(memStr);
    
    auto result = encoder.getPSFilter(1, "");
    // Encoders typically don't support PS filters
    EXPECT_FALSE(result.has_value());
}

// Test encoding of empty input - should just produce end-of-data marker
TEST_F(ASCII85EncoderTest_214, EmptyInputProducesEOD_214) {
    const char data[] = "";
    auto obj = Object(objNull);
    MemStream *memStr = new MemStream(const_cast<char*>(data), 0, 0, std::move(obj));
    
    ASCII85Encoder encoder(memStr);
    encoder.rewind();
    
    // For empty input, we should get the end-of-data marker "~>" then EOF
    std::string output;
    int c;
    while ((c = encoder.getChar()) != EOF) {
        output += static_cast<char>(c);
    }
    
    // The output should end with "~>"
    ASSERT_GE(output.size(), 2u);
    EXPECT_EQ(output.substr(output.size() - 2), "~>");
}

// Test encoding of known input data
TEST_F(ASCII85EncoderTest_214, EncodesKnownData_214) {
    // ASCII85 encoding of "Man " should be "9jqo^"
    const char data[] = "Man ";
    auto obj = Object(objNull);
    MemStream *memStr = new MemStream(const_cast<char*>(data), 0, 4, std::move(obj));
    
    ASCII85Encoder encoder(memStr);
    encoder.rewind();
    
    std::string output;
    int c;
    while ((c = encoder.getChar()) != EOF) {
        output += static_cast<char>(c);
    }
    
    // Should end with ~>
    EXPECT_TRUE(output.size() >= 2);
    EXPECT_EQ(output.substr(output.size() - 2), "~>");
    
    // The encoded portion (before ~>) should be a valid ASCII85 string
    std::string encoded = output.substr(0, output.size() - 2);
    // All characters should be in the valid ASCII85 range (! to u, or z)
    for (char ch : encoded) {
        bool valid = (ch >= '!' && ch <= 'u') || ch == 'z' || ch == '\n' || ch == '\r';
        EXPECT_TRUE(valid) << "Invalid ASCII85 character: " << static_cast<int>(ch);
    }
}

// Test encoding of all zeros (should use 'z' shortcut in standard ASCII85)
TEST_F(ASCII85EncoderTest_214, EncodesAllZeros_214) {
    const char data[] = {0, 0, 0, 0};
    auto obj = Object(objNull);
    MemStream *memStr = new MemStream(const_cast<char*>(data), 0, 4, std::move(obj));
    
    ASCII85Encoder encoder(memStr);
    encoder.rewind();
    
    std::string output;
    int c;
    while ((c = encoder.getChar()) != EOF) {
        output += static_cast<char>(c);
    }
    
    // Should end with ~>
    EXPECT_TRUE(output.size() >= 2);
    EXPECT_EQ(output.substr(output.size() - 2), "~>");
    
    // Four zero bytes should encode to 'z' in ASCII85
    std::string encoded = output.substr(0, output.size() - 2);
    EXPECT_EQ(encoded, "z");
}

// Test lookChar does not consume the character
TEST_F(ASCII85EncoderTest_214, LookCharDoesNotConsume_214) {
    const char data[] = "A";
    auto obj = Object(objNull);
    MemStream *memStr = new MemStream(const_cast<char*>(data), 0, 1, std::move(obj));
    
    ASCII85Encoder encoder(memStr);
    encoder.rewind();
    
    int first_look = encoder.lookChar();
    int second_look = encoder.lookChar();
    
    // lookChar should return the same character without consuming it
    EXPECT_EQ(first_look, second_look);
    
    // getChar should return the same character
    int get = encoder.getChar();
    EXPECT_EQ(first_look, get);
}

// Test rewind resets the encoder
TEST_F(ASCII85EncoderTest_214, RewindResetsEncoder_214) {
    const char data[] = "Test";
    auto obj = Object(objNull);
    MemStream *memStr = new MemStream(const_cast<char*>(data), 0, 4, std::move(obj));
    
    ASCII85Encoder encoder(memStr);
    encoder.rewind();
    
    // Read all output
    std::string output1;
    int c;
    while ((c = encoder.getChar()) != EOF) {
        output1 += static_cast<char>(c);
    }
    
    // Rewind and read again
    encoder.rewind();
    std::string output2;
    while ((c = encoder.getChar()) != EOF) {
        output2 += static_cast<char>(c);
    }
    
    EXPECT_EQ(output1, output2);
}

// Test that rewind returns true on success
TEST_F(ASCII85EncoderTest_214, RewindReturnsTrue_214) {
    const char data[] = "Test";
    auto obj = Object(objNull);
    MemStream *memStr = new MemStream(const_cast<char*>(data), 0, 4, std::move(obj));
    
    ASCII85Encoder encoder(memStr);
    
    EXPECT_TRUE(encoder.rewind());
}

// Test single byte input
TEST_F(ASCII85EncoderTest_214, SingleByteInput_214) {
    const char data[] = "A";
    auto obj = Object(objNull);
    MemStream *memStr = new MemStream(const_cast<char*>(data), 0, 1, std::move(obj));
    
    ASCII85Encoder encoder(memStr);
    encoder.rewind();
    
    std::string output;
    int c;
    while ((c = encoder.getChar()) != EOF) {
        output += static_cast<char>(c);
    }
    
    // Should have some encoded output plus ~>
    EXPECT_GE(output.size(), 2u);
    EXPECT_EQ(output.substr(output.size() - 2), "~>");
}

// Test that after EOF, getChar continues to return EOF
TEST_F(ASCII85EncoderTest_214, GetCharReturnsEOFAfterEnd_214) {
    const char data[] = "";
    auto obj = Object(objNull);
    MemStream *memStr = new MemStream(const_cast<char*>(data), 0, 0, std::move(obj));
    
    ASCII85Encoder encoder(memStr);
    encoder.rewind();
    
    // Read until EOF
    int c;
    while ((c = encoder.getChar()) != EOF) {
        // consume
    }
    
    // Additional calls should still return EOF
    EXPECT_EQ(encoder.getChar(), EOF);
    EXPECT_EQ(encoder.getChar(), EOF);
}

// Test with larger data
TEST_F(ASCII85EncoderTest_214, LargerDataEncoding_214) {
    // Create a buffer with repeated pattern
    char data[256];
    for (int i = 0; i < 256; i++) {
        data[i] = static_cast<char>(i);
    }
    auto obj = Object(objNull);
    MemStream *memStr = new MemStream(data, 0, 256, std::move(obj));
    
    ASCII85Encoder encoder(memStr);
    encoder.rewind();
    
    std::string output;
    int c;
    while ((c = encoder.getChar()) != EOF) {
        output += static_cast<char>(c);
    }
    
    // Should produce valid output ending with ~>
    EXPECT_GE(output.size(), 2u);
    EXPECT_EQ(output.substr(output.size() - 2), "~>");
}

// Test with exactly 4 bytes (one full group)
TEST_F(ASCII85EncoderTest_214, ExactlyFourBytes_214) {
    const char data[] = "ABCD";
    auto obj = Object(objNull);
    MemStream *memStr = new MemStream(const_cast<char*>(data), 0, 4, std::move(obj));
    
    ASCII85Encoder encoder(memStr);
    encoder.rewind();
    
    std::string output;
    int c;
    while ((c = encoder.getChar()) != EOF) {
        output += static_cast<char>(c);
    }
    
    // 4 bytes encode to 5 ASCII85 chars + "~>"
    EXPECT_GE(output.size(), 7u); // 5 encoded + 2 for ~>
    EXPECT_EQ(output.substr(output.size() - 2), "~>");
}

// Test with 5 bytes (one full group + one partial)
TEST_F(ASCII85EncoderTest_214, FiveBytesPartialGroup_214) {
    const char data[] = "ABCDE";
    auto obj = Object(objNull);
    MemStream *memStr = new MemStream(const_cast<char*>(data), 0, 5, std::move(obj));
    
    ASCII85Encoder encoder(memStr);
    encoder.rewind();
    
    std::string output;
    int c;
    while ((c = encoder.getChar()) != EOF) {
        output += static_cast<char>(c);
    }
    
    EXPECT_GE(output.size(), 2u);
    EXPECT_EQ(output.substr(output.size() - 2), "~>");
}

#include <gtest/gtest.h>
#include <memory>
#include "Stream.h"

// Helper to create a minimal underlying stream for ASCIIHexStream.
// We use a MemStream or similar basic stream as the underlying stream.
// Based on the poppler codebase, we can use a MemStream for testing.

class ASCIIHexStreamTest_179 : public ::testing::Test {
protected:
    // Helper to create an ASCIIHexStream from a hex-encoded string
    std::unique_ptr<ASCIIHexStream> createStream(const char* data, int len) {
        // Create a copy of data that persists
        char* buf = new char[len];
        memcpy(buf, data, len);
        buffers.push_back(buf);
        
        Object dictObj;
        auto baseStream = std::make_unique<MemStream>(buf, 0, len, std::move(dictObj));
        return std::make_unique<ASCIIHexStream>(std::move(baseStream));
    }
    
    void TearDown() override {
        for (auto* buf : buffers) {
            delete[] buf;
        }
        buffers.clear();
    }
    
    std::vector<char*> buffers;
};

// Test that getKind returns strASCIIHex
TEST_F(ASCIIHexStreamTest_179, GetKindReturnsASCIIHex_179) {
    auto stream = createStream("48656C6C6F>", 12);
    EXPECT_EQ(stream->getKind(), strASCIIHex);
}

// Test decoding a simple ASCII hex string "Hello" = 48 65 6C 6C 6F
TEST_F(ASCIIHexStreamTest_179, DecodeSimpleHexString_179) {
    const char* hexData = "48656C6C6F>";
    auto stream = createStream(hexData, strlen(hexData));
    stream->reset();
    
    EXPECT_EQ(stream->getChar(), 'H');
    EXPECT_EQ(stream->getChar(), 'e');
    EXPECT_EQ(stream->getChar(), 'l');
    EXPECT_EQ(stream->getChar(), 'l');
    EXPECT_EQ(stream->getChar(), 'o');
    EXPECT_EQ(stream->getChar(), EOF);
}

// Test that lookChar returns the next character without consuming it
TEST_F(ASCIIHexStreamTest_179, LookCharDoesNotConsume_179) {
    const char* hexData = "41>";
    auto stream = createStream(hexData, strlen(hexData));
    stream->reset();
    
    int ch = stream->lookChar();
    EXPECT_EQ(ch, 'A');
    // lookChar should not consume the character
    int ch2 = stream->lookChar();
    EXPECT_EQ(ch2, 'A');
    // getChar should return the same character
    int ch3 = stream->getChar();
    EXPECT_EQ(ch3, 'A');
    // Now should be EOF
    EXPECT_EQ(stream->getChar(), EOF);
}

// Test empty hex stream (just the end-of-data marker)
TEST_F(ASCIIHexStreamTest_179, EmptyHexStream_179) {
    const char* hexData = ">";
    auto stream = createStream(hexData, strlen(hexData));
    stream->reset();
    
    EXPECT_EQ(stream->getChar(), EOF);
}

// Test hex stream with whitespace between hex digits
TEST_F(ASCIIHexStreamTest_179, HexStreamWithWhitespace_179) {
    const char* hexData = "48 65 6C 6C 6F>";
    auto stream = createStream(hexData, strlen(hexData));
    stream->reset();
    
    EXPECT_EQ(stream->getChar(), 'H');
    EXPECT_EQ(stream->getChar(), 'e');
    EXPECT_EQ(stream->getChar(), 'l');
    EXPECT_EQ(stream->getChar(), 'l');
    EXPECT_EQ(stream->getChar(), 'o');
    EXPECT_EQ(stream->getChar(), EOF);
}

// Test hex stream with odd number of hex digits (trailing nibble padded with 0)
TEST_F(ASCIIHexStreamTest_179, OddNumberOfHexDigits_179) {
    // "4" should be interpreted as "40" = 0x40 = '@'
    const char* hexData = "4>";
    auto stream = createStream(hexData, strlen(hexData));
    stream->reset();
    
    int ch = stream->getChar();
    EXPECT_EQ(ch, 0x40);
    EXPECT_EQ(stream->getChar(), EOF);
}

// Test rewind functionality
TEST_F(ASCIIHexStreamTest_179, RewindResetsStream_179) {
    const char* hexData = "4142>";
    auto stream = createStream(hexData, strlen(hexData));
    stream->reset();
    
    EXPECT_EQ(stream->getChar(), 'A');
    EXPECT_EQ(stream->getChar(), 'B');
    EXPECT_EQ(stream->getChar(), EOF);
    
    // Rewind and read again
    bool result = stream->reset();
    EXPECT_EQ(stream->getChar(), 'A');
    EXPECT_EQ(stream->getChar(), 'B');
    EXPECT_EQ(stream->getChar(), EOF);
}

// Test isBinary returns false (ASCII hex is not binary)
TEST_F(ASCIIHexStreamTest_179, IsBinaryReturnsFalse_179) {
    const char* hexData = "4142>";
    auto stream = createStream(hexData, strlen(hexData));
    
    EXPECT_FALSE(stream->isBinary(true));
    EXPECT_FALSE(stream->isBinary(false));
}

// Test hex stream with lowercase hex digits
TEST_F(ASCIIHexStreamTest_179, LowercaseHexDigits_179) {
    const char* hexData = "48656c6c6f>";
    auto stream = createStream(hexData, strlen(hexData));
    stream->reset();
    
    EXPECT_EQ(stream->getChar(), 'H');
    EXPECT_EQ(stream->getChar(), 'e');
    EXPECT_EQ(stream->getChar(), 'l');
    EXPECT_EQ(stream->getChar(), 'l');
    EXPECT_EQ(stream->getChar(), 'o');
    EXPECT_EQ(stream->getChar(), EOF);
}

// Test hex stream with mixed case hex digits
TEST_F(ASCIIHexStreamTest_179, MixedCaseHexDigits_179) {
    const char* hexData = "48656C6c6F>";
    auto stream = createStream(hexData, strlen(hexData));
    stream->reset();
    
    EXPECT_EQ(stream->getChar(), 'H');
    EXPECT_EQ(stream->getChar(), 'e');
    EXPECT_EQ(stream->getChar(), 'l');
    EXPECT_EQ(stream->getChar(), 'l');
    EXPECT_EQ(stream->getChar(), 'o');
    EXPECT_EQ(stream->getChar(), EOF);
}

// Test decoding 00 and FF boundary values
TEST_F(ASCIIHexStreamTest_179, BoundaryByteValues_179) {
    const char* hexData = "00FF>";
    auto stream = createStream(hexData, strlen(hexData));
    stream->reset();
    
    EXPECT_EQ(stream->getChar(), 0x00);
    EXPECT_EQ(stream->getChar(), 0xFF);
    EXPECT_EQ(stream->getChar(), EOF);
}

// Test multiple consecutive EOF reads
TEST_F(ASCIIHexStreamTest_179, MultipleEOFReads_179) {
    const char* hexData = "41>";
    auto stream = createStream(hexData, strlen(hexData));
    stream->reset();
    
    EXPECT_EQ(stream->getChar(), 'A');
    EXPECT_EQ(stream->getChar(), EOF);
    EXPECT_EQ(stream->getChar(), EOF);
    EXPECT_EQ(stream->getChar(), EOF);
}

// Test hex stream with tabs and newlines as whitespace
TEST_F(ASCIIHexStreamTest_179, WhitespaceVariants_179) {
    const char* hexData = "48\t65\n6C\r6C 6F>";
    auto stream = createStream(hexData, strlen(hexData));
    stream->reset();
    
    EXPECT_EQ(stream->getChar(), 'H');
    EXPECT_EQ(stream->getChar(), 'e');
    EXPECT_EQ(stream->getChar(), 'l');
    EXPECT_EQ(stream->getChar(), 'l');
    EXPECT_EQ(stream->getChar(), 'o');
    EXPECT_EQ(stream->getChar(), EOF);
}

// Test getPSFilter
TEST_F(ASCIIHexStreamTest_179, GetPSFilter_179) {
    const char* hexData = "4142>";
    auto stream = createStream(hexData, strlen(hexData));
    
    // PSFilter for level 2 and above should potentially return a filter string
    auto result = stream->getPSFilter(2, "");
    // We just verify it returns something or nothing without crashing
    // The exact behavior depends on implementation
}

// Test single byte decoding
TEST_F(ASCIIHexStreamTest_179, SingleByteDecoding_179) {
    const char* hexData = "FF>";
    auto stream = createStream(hexData, strlen(hexData));
    stream->reset();
    
    EXPECT_EQ(stream->getChar(), 0xFF);
    EXPECT_EQ(stream->getChar(), EOF);
}

// Test lookChar at EOF
TEST_F(ASCIIHexStreamTest_179, LookCharAtEOF_179) {
    const char* hexData = ">";
    auto stream = createStream(hexData, strlen(hexData));
    stream->reset();
    
    EXPECT_EQ(stream->lookChar(), EOF);
}

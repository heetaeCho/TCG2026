#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <string>
#include <optional>

#include "Stream.h"
#include "Object.h"

// Helper: Create a MemStream from a string buffer
// MemStream takes ownership semantics vary, so we manage carefully
class ASCIIHexStreamTest_180 : public ::testing::Test {
protected:
    std::unique_ptr<Stream> makeASCIIHexStream(const char* data, int len) {
        // We need to create a base stream. MemStream is typically available.
        // MemStream(const char *bufA, Goffset startA, Goffset lengthA, Object &&dictA)
        Object dict;
        auto memStream = std::make_unique<MemStream>(const_cast<char*>(data), 0, len, std::move(dict));
        return std::make_unique<ASCIIHexStream>(std::move(memStream));
    }
};

// Test that getChar returns EOF for empty input
TEST_F(ASCIIHexStreamTest_180, EmptyInput_ReturnsEOF_180) {
    const char* data = ">";
    auto stream = makeASCIIHexStream(data, 1);
    stream->reset();
    // '>' is the end-of-data marker for ASCIIHex
    int c = stream->getChar();
    EXPECT_EQ(c, EOF);
}

// Test decoding a simple hex pair
TEST_F(ASCIIHexStreamTest_180, SimpleHexPair_180) {
    // "48656C6C6F>" encodes "Hello"
    const char* data = "48656C6C6F>";
    auto stream = makeASCIIHexStream(data, 11);
    stream->reset();
    
    EXPECT_EQ(stream->getChar(), 'H');
    EXPECT_EQ(stream->getChar(), 'e');
    EXPECT_EQ(stream->getChar(), 'l');
    EXPECT_EQ(stream->getChar(), 'l');
    EXPECT_EQ(stream->getChar(), 'o');
    EXPECT_EQ(stream->getChar(), EOF);
}

// Test that lookChar does not consume the character
TEST_F(ASCIIHexStreamTest_180, LookCharDoesNotConsume_180) {
    const char* data = "41>";
    auto stream = makeASCIIHexStream(data, 3);
    stream->reset();
    
    int c1 = stream->lookChar();
    int c2 = stream->lookChar();
    EXPECT_EQ(c1, c2);
    EXPECT_EQ(c1, 'A'); // 0x41 = 'A'
    
    // Now consume it
    int c3 = stream->getChar();
    EXPECT_EQ(c3, 'A');
    EXPECT_EQ(stream->getChar(), EOF);
}

// Test that getChar returns lookChar value and then sets buf to EOF
TEST_F(ASCIIHexStreamTest_180, GetCharReturnsLookCharAndClearsBuf_180) {
    const char* data = "4142>";
    auto stream = makeASCIIHexStream(data, 5);
    stream->reset();
    
    // First call lookChar to populate buf
    int looked = stream->lookChar();
    EXPECT_EQ(looked, 0x41); // 'A'
    
    // getChar should return same value
    int got = stream->getChar();
    EXPECT_EQ(got, 0x41);
    
    // Next char should be 0x42
    EXPECT_EQ(stream->getChar(), 0x42); // 'B'
    EXPECT_EQ(stream->getChar(), EOF);
}

// Test odd number of hex digits (trailing nibble treated as X0)
TEST_F(ASCIIHexStreamTest_180, OddHexDigit_180) {
    // "4>" means single nibble '4', which should be interpreted as 0x40
    const char* data = "4>";
    auto stream = makeASCIIHexStream(data, 2);
    stream->reset();
    
    int c = stream->getChar();
    EXPECT_EQ(c, 0x40);
    EXPECT_EQ(stream->getChar(), EOF);
}

// Test whitespace in hex stream is ignored
TEST_F(ASCIIHexStreamTest_180, WhitespaceIgnored_180) {
    const char* data = "48 65 6C 6C 6F>";
    auto stream = makeASCIIHexStream(data, 15);
    stream->reset();
    
    EXPECT_EQ(stream->getChar(), 'H');
    EXPECT_EQ(stream->getChar(), 'e');
    EXPECT_EQ(stream->getChar(), 'l');
    EXPECT_EQ(stream->getChar(), 'l');
    EXPECT_EQ(stream->getChar(), 'o');
    EXPECT_EQ(stream->getChar(), EOF);
}

// Test uppercase and lowercase hex digits
TEST_F(ASCIIHexStreamTest_180, MixedCaseHexDigits_180) {
    // "4a4A>" should decode to 0x4A 0x4A
    const char* data = "4a4A>";
    auto stream = makeASCIIHexStream(data, 5);
    stream->reset();
    
    EXPECT_EQ(stream->getChar(), 0x4A);
    EXPECT_EQ(stream->getChar(), 0x4A);
    EXPECT_EQ(stream->getChar(), EOF);
}

// Test rewind resets the stream
TEST_F(ASCIIHexStreamTest_180, RewindResetsStream_180) {
    const char* data = "4142>";
    auto stream = makeASCIIHexStream(data, 5);
    stream->reset();
    
    EXPECT_EQ(stream->getChar(), 0x41);
    EXPECT_EQ(stream->getChar(), 0x42);
    EXPECT_EQ(stream->getChar(), EOF);
    
    // Rewind and re-read
    stream->reset();
    EXPECT_EQ(stream->getChar(), 0x41);
    EXPECT_EQ(stream->getChar(), 0x42);
    EXPECT_EQ(stream->getChar(), EOF);
}

// Test getKind returns the correct stream kind
TEST_F(ASCIIHexStreamTest_180, GetKindReturnsCorrectKind_180) {
    const char* data = ">";
    auto stream = makeASCIIHexStream(data, 1);
    stream->reset();
    
    EXPECT_EQ(stream->getKind(), strASCIIHex);
}

// Test isBinary returns false (ASCIIHex produces ASCII-safe output context)
TEST_F(ASCIIHexStreamTest_180, IsBinary_180) {
    const char* data = ">";
    auto stream = makeASCIIHexStream(data, 1);
    stream->reset();
    
    // isBinary with last=true
    bool result = stream->isBinary(true);
    EXPECT_FALSE(result);
}

// Test all zeros
TEST_F(ASCIIHexStreamTest_180, AllZeros_180) {
    const char* data = "0000>";
    auto stream = makeASCIIHexStream(data, 5);
    stream->reset();
    
    EXPECT_EQ(stream->getChar(), 0x00);
    EXPECT_EQ(stream->getChar(), 0x00);
    EXPECT_EQ(stream->getChar(), EOF);
}

// Test FF values
TEST_F(ASCIIHexStreamTest_180, FFValues_180) {
    const char* data = "FFFF>";
    auto stream = makeASCIIHexStream(data, 5);
    stream->reset();
    
    EXPECT_EQ(stream->getChar(), 0xFF);
    EXPECT_EQ(stream->getChar(), 0xFF);
    EXPECT_EQ(stream->getChar(), EOF);
}

// Test no EOD marker - stream should still work until data exhausted
TEST_F(ASCIIHexStreamTest_180, NoEODMarker_180) {
    const char* data = "4142";
    auto stream = makeASCIIHexStream(data, 4);
    stream->reset();
    
    EXPECT_EQ(stream->getChar(), 0x41);
    EXPECT_EQ(stream->getChar(), 0x42);
    // Should eventually return EOF
    EXPECT_EQ(stream->getChar(), EOF);
}

// Test multiple whitespace types (tab, newline, carriage return)
TEST_F(ASCIIHexStreamTest_180, VariousWhitespace_180) {
    const char* data = "41\t42\n43\r44>";
    auto stream = makeASCIIHexStream(data, 12);
    stream->reset();
    
    EXPECT_EQ(stream->getChar(), 0x41);
    EXPECT_EQ(stream->getChar(), 0x42);
    EXPECT_EQ(stream->getChar(), 0x43);
    EXPECT_EQ(stream->getChar(), 0x44);
    EXPECT_EQ(stream->getChar(), EOF);
}

// Test consecutive getChar calls after EOF
TEST_F(ASCIIHexStreamTest_180, MultipleEOFCalls_180) {
    const char* data = "41>";
    auto stream = makeASCIIHexStream(data, 3);
    stream->reset();
    
    EXPECT_EQ(stream->getChar(), 0x41);
    EXPECT_EQ(stream->getChar(), EOF);
    EXPECT_EQ(stream->getChar(), EOF);
    EXPECT_EQ(stream->getChar(), EOF);
}

// Test getPSFilter
TEST_F(ASCIIHexStreamTest_180, GetPSFilter_180) {
    const char* data = "41>";
    auto stream = makeASCIIHexStream(data, 3);
    stream->reset();
    
    auto result = stream->getPSFilter(1, "");
    // We just check it returns something or nullopt - behavior depends on implementation
    // For level 1, ASCIIHexDecode should be available
    if (result.has_value()) {
        EXPECT_FALSE(result->empty());
    }
}

#include <gtest/gtest.h>
#include <memory>
#include <string>
#include <optional>
#include "Stream.h"

// Helper to create a MemStream or similar base stream for testing
// We need a concrete Stream to wrap in ASCII85Stream

class ASCII85StreamTest_181 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }

    // Helper to create an ASCII85Stream from a string of ASCII85-encoded data
    std::unique_ptr<ASCII85Stream> createASCII85Stream(const char* data, int len) {
        // Create a MemStream as the underlying stream
        // MemStream takes ownership of the buffer in some implementations,
        // but we need to be careful about lifetime
        char* buf = (char*)gmalloc(len);
        memcpy(buf, data, len);
        auto baseStream = std::make_unique<MemStream>(buf, 0, len, Object(objNull), true);
        return std::make_unique<ASCII85Stream>(std::move(baseStream));
    }
};

// Test that getKind returns strASCII85
TEST_F(ASCII85StreamTest_181, GetKindReturnsASCII85_181) {
    const char* data = "~>";
    auto stream = createASCII85Stream(data, 2);
    EXPECT_EQ(stream->getKind(), strASCII85);
}

// Test decoding empty ASCII85 stream (just end-of-data marker)
TEST_F(ASCII85StreamTest_181, EmptyStream_181) {
    const char* data = "~>";
    auto stream = createASCII85Stream(data, 2);
    stream->reset();
    int ch = stream->getChar();
    EXPECT_EQ(ch, EOF);
}

// Test decoding a simple ASCII85 encoded string
// "Hello" in ASCII85 is "87cURD]j7BEbo7" followed by "~>"
TEST_F(ASCII85StreamTest_181, DecodeHello_181) {
    const char* data = "87cURD]j7BEbo7~>";
    auto stream = createASCII85Stream(data, strlen(data));
    stream->reset();

    std::string result;
    int ch;
    while ((ch = stream->getChar()) != EOF) {
        result += (char)ch;
    }
    EXPECT_EQ(result, "Hello");
}

// Test that lookChar does not advance the stream position
TEST_F(ASCII85StreamTest_181, LookCharDoesNotAdvance_181) {
    const char* data = "87cURD]j7BEbo7~>";
    auto stream = createASCII85Stream(data, strlen(data));
    stream->reset();

    int first = stream->lookChar();
    int second = stream->lookChar();
    EXPECT_EQ(first, second);
    // Now getChar should return the same value
    int third = stream->getChar();
    EXPECT_EQ(first, third);
}

// Test rewind resets the stream
TEST_F(ASCII85StreamTest_181, RewindResetsStream_181) {
    const char* data = "87cURD]j7BEbo7~>";
    auto stream = createASCII85Stream(data, strlen(data));
    stream->reset();

    // Read first character
    int first = stream->getChar();
    EXPECT_NE(first, EOF);

    // Rewind
    bool ok = stream->reset();

    // Read first character again
    int afterRewind = stream->getChar();
    EXPECT_EQ(first, afterRewind);
}

// Test isBinary returns false (ASCII85 produces text-like output)
TEST_F(ASCII85StreamTest_181, IsBinaryReturnsFalse_181) {
    const char* data = "~>";
    auto stream = createASCII85Stream(data, 2);
    EXPECT_FALSE(stream->isBinary(true));
    EXPECT_FALSE(stream->isBinary(false));
}

// Test decoding the special 'z' character which represents four zero bytes
TEST_F(ASCII85StreamTest_181, DecodeZShortcut_181) {
    // 'z' in ASCII85 represents four null bytes
    const char* data = "z~>";
    auto stream = createASCII85Stream(data, strlen(data));
    stream->reset();

    std::string result;
    int ch;
    while ((ch = stream->getChar()) != EOF) {
        result += (char)ch;
    }
    EXPECT_EQ(result.size(), 4u);
    EXPECT_EQ(result[0], '\0');
    EXPECT_EQ(result[1], '\0');
    EXPECT_EQ(result[2], '\0');
    EXPECT_EQ(result[3], '\0');
}

// Test decoding multiple 'z' characters
TEST_F(ASCII85StreamTest_181, DecodeMultipleZ_181) {
    const char* data = "zz~>";
    auto stream = createASCII85Stream(data, strlen(data));
    stream->reset();

    std::string result;
    int ch;
    while ((ch = stream->getChar()) != EOF) {
        result += (char)ch;
    }
    EXPECT_EQ(result.size(), 8u);
    for (size_t i = 0; i < 8; i++) {
        EXPECT_EQ(result[i], '\0');
    }
}

// Test getPSFilter
TEST_F(ASCII85StreamTest_181, GetPSFilter_181) {
    const char* data = "~>";
    auto stream = createASCII85Stream(data, 2);
    auto filter = stream->getPSFilter(1, "");
    // We just verify it returns something or nothing - interface test
    // At PS level 1, ASCII85Decode might not be available
    // At PS level 2+, it should be available
    auto filter2 = stream->getPSFilter(2, "");
    if (filter2.has_value()) {
        EXPECT_FALSE(filter2->empty());
    }
}

// Test partial group (less than 5 characters before ~>)
TEST_F(ASCII85StreamTest_181, DecodePartialGroup_181) {
    // A partial group of 2 chars "!!" should decode to 1 byte
    const char* data = "!!~>";
    auto stream = createASCII85Stream(data, strlen(data));
    stream->reset();

    std::string result;
    int ch;
    while ((ch = stream->getChar()) != EOF) {
        result += (char)ch;
    }
    EXPECT_EQ(result.size(), 1u);
}

// Test that whitespace in the encoded data is ignored
TEST_F(ASCII85StreamTest_181, WhitespaceIgnored_181) {
    // "87cUR D]j7B Ebo7~>" with spaces should decode same as without
    const char* dataWithSpaces = "87cUR D]j7B Ebo7~>";
    const char* dataWithout = "87cURD]j7BEbo7~>";

    auto stream1 = createASCII85Stream(dataWithSpaces, strlen(dataWithSpaces));
    auto stream2 = createASCII85Stream(dataWithout, strlen(dataWithout));
    stream1->reset();
    stream2->reset();

    int ch1, ch2;
    while (true) {
        ch1 = stream1->getChar();
        ch2 = stream2->getChar();
        EXPECT_EQ(ch1, ch2);
        if (ch1 == EOF || ch2 == EOF) break;
    }
}

// Test getChar and lookChar interleaved
TEST_F(ASCII85StreamTest_181, InterleavedGetAndLook_181) {
    const char* data = "87cURD]j7BEbo7~>";
    auto stream = createASCII85Stream(data, strlen(data));
    stream->reset();

    // lookChar should return next char without consuming
    int looked = stream->lookChar();
    EXPECT_NE(looked, EOF);

    // getChar should return same char and consume it
    int got = stream->getChar();
    EXPECT_EQ(looked, got);

    // Next lookChar should be different (next char in stream)
    int looked2 = stream->lookChar();
    // It may or may not be different depending on data, but it should be valid
    int got2 = stream->getChar();
    EXPECT_EQ(looked2, got2);
}

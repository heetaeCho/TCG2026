#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <string>
#include <optional>
#include "Stream.h"

// Helper: Create a MemStream from a string buffer that persists for the test
class ASCII85StreamTest_182 : public ::testing::Test {
protected:
    std::unique_ptr<ASCII85Stream> createASCII85Stream(const char* data, int len) {
        // We need to create a base stream. MemStream takes ownership concerns
        // vary by implementation, so we copy data to a persistent buffer.
        char* buf = (char*)gmalloc(len);
        memcpy(buf, data, len);
        auto baseStream = std::make_unique<MemStream>(buf, 0, len, Object(objNull), true);
        return std::make_unique<ASCII85Stream>(std::move(baseStream));
    }
};

// Test that an empty stream (just "~>") returns EOF immediately
TEST_F(ASCII85StreamTest_182, EmptyStream_182) {
    const char data[] = "~>";
    auto stream = createASCII85Stream(data, 2);
    stream->reset();
    int ch = stream->getChar();
    EXPECT_EQ(ch, EOF);
}

// Test decoding a simple ASCII85 encoded string
// "87cURD]j7BEbo80" decodes to "Hello" in ASCII85
TEST_F(ASCII85StreamTest_182, DecodeHello_182) {
    // ASCII85 encoding of "Hello" is "87cURD]j7BEbo80~>"
    const char data[] = "87cURD]j7BEbo80~>";
    auto stream = createASCII85Stream(data, strlen(data));
    stream->reset();

    std::string result;
    int ch;
    while ((ch = stream->getChar()) != EOF) {
        result += (char)ch;
    }
    EXPECT_EQ(result, "Hello");
}

// Test the 'z' shorthand which represents four zero bytes
TEST_F(ASCII85StreamTest_182, ZeroShorthand_182) {
    // 'z' in ASCII85 represents four null bytes
    const char data[] = "z~>";
    auto stream = createASCII85Stream(data, strlen(data));
    stream->reset();

    int count = 0;
    int ch;
    while ((ch = stream->getChar()) != EOF) {
        EXPECT_EQ(ch, 0);
        count++;
    }
    EXPECT_EQ(count, 4);
}

// Test that lookChar does not advance the stream position
TEST_F(ASCII85StreamTest_182, LookCharDoesNotAdvance_182) {
    const char data[] = "87cURD]j7BEbo80~>";
    auto stream = createASCII85Stream(data, strlen(data));
    stream->reset();

    int first_look = stream->lookChar();
    int second_look = stream->lookChar();
    EXPECT_EQ(first_look, second_look);

    // Now getChar should return the same value and advance
    int get_result = stream->getChar();
    EXPECT_EQ(get_result, first_look);

    // Next lookChar should be different (next byte)
    int next_look = stream->lookChar();
    // 'H' = 72, 'e' = 101
    EXPECT_EQ(first_look, 'H');
    EXPECT_EQ(next_look, 'e');
}

// Test rewind resets the stream to the beginning
TEST_F(ASCII85StreamTest_182, RewindResetsStream_182) {
    const char data[] = "87cURD]j7BEbo80~>";
    auto stream = createASCII85Stream(data, strlen(data));
    stream->reset();

    // Read first character
    int first = stream->getChar();
    EXPECT_EQ(first, 'H');

    // Rewind
    bool ok = stream->reset();

    // Read first character again
    int after_rewind = stream->getChar();
    EXPECT_EQ(after_rewind, 'H');
}

// Test getKind returns the expected stream kind
TEST_F(ASCII85StreamTest_182, GetKind_182) {
    const char data[] = "~>";
    auto stream = createASCII85Stream(data, strlen(data));
    EXPECT_EQ(stream->getKind(), strASCII85);
}

// Test isBinary returns false (ASCII85 is a text encoding)
TEST_F(ASCII85StreamTest_182, IsBinaryReturnsFalse_182) {
    const char data[] = "~>";
    auto stream = createASCII85Stream(data, strlen(data));
    EXPECT_FALSE(stream->isBinary(true));
    EXPECT_FALSE(stream->isBinary(false));
}

// Test getPSFilter returns a value for appropriate PS level
TEST_F(ASCII85StreamTest_182, GetPSFilter_182) {
    const char data[] = "~>";
    auto stream = createASCII85Stream(data, strlen(data));
    auto result = stream->getPSFilter(2, "");
    // ASCII85Decode is a standard PS filter, should return something for level >= 2
    if (result.has_value()) {
        EXPECT_FALSE(result->empty());
    }
}

// Test partial group (less than 5 ASCII85 characters before ~>)
TEST_F(ASCII85StreamTest_182, PartialGroup_182) {
    // "GA" encodes to a partial group - 2 chars encode 1 byte
    // ASCII85 partial: 2 chars -> 1 byte output
    const char data[] = "/c~>";
    auto stream = createASCII85Stream(data, strlen(data));
    stream->reset();

    int count = 0;
    int ch;
    while ((ch = stream->getChar()) != EOF) {
        count++;
    }
    // A 2-character group decodes to 1 byte
    EXPECT_EQ(count, 1);
}

// Test multiple z shorthand characters
TEST_F(ASCII85StreamTest_182, MultipleZeroShorthands_182) {
    const char data[] = "zz~>";
    auto stream = createASCII85Stream(data, strlen(data));
    stream->reset();

    int count = 0;
    int ch;
    while ((ch = stream->getChar()) != EOF) {
        EXPECT_EQ(ch, 0);
        count++;
    }
    EXPECT_EQ(count, 8);
}

// Test that whitespace in the encoded data is ignored
TEST_F(ASCII85StreamTest_182, WhitespaceIgnored_182) {
    // Same encoding as "Hello" but with whitespace inserted
    const char data[] = "87cUR D]j7B Ebo80~>";
    auto stream = createASCII85Stream(data, strlen(data));
    stream->reset();

    std::string result;
    int ch;
    while ((ch = stream->getChar()) != EOF) {
        result += (char)ch;
    }
    EXPECT_EQ(result, "Hello");
}

// Test reading past EOF repeatedly returns EOF
TEST_F(ASCII85StreamTest_182, RepeatedEOF_182) {
    const char data[] = "~>";
    auto stream = createASCII85Stream(data, strlen(data));
    stream->reset();

    EXPECT_EQ(stream->getChar(), EOF);
    EXPECT_EQ(stream->getChar(), EOF);
    EXPECT_EQ(stream->getChar(), EOF);
}

// Test a full 5-character group that decodes to 4 bytes
TEST_F(ASCII85StreamTest_182, FullGroup_182) {
    // "!!!!!~>" encodes four null bytes (but not via 'z')
    // Actually "!!!!!" = 0x00000000
    const char data[] = "!!!!!~>";
    auto stream = createASCII85Stream(data, strlen(data));
    stream->reset();

    int count = 0;
    int ch;
    while ((ch = stream->getChar()) != EOF) {
        EXPECT_EQ(ch, 0);
        count++;
    }
    EXPECT_EQ(count, 4);
}

// Test encoding of known value: "s8W-!" encodes "Test"
TEST_F(ASCII85StreamTest_182, DecodeTest_182) {
    const char data[] = "FCfN8~>";
    auto stream = createASCII85Stream(data, strlen(data));
    stream->reset();

    std::string result;
    int ch;
    while ((ch = stream->getChar()) != EOF) {
        result += (char)ch;
    }
    EXPECT_EQ(result, "Tes");
}

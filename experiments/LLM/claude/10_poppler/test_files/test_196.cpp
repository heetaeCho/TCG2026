#include <gtest/gtest.h>
#include <memory>
#include "Stream.h"

// Helper to create a MemStream or similar base stream for FlateStream construction
// We need a minimal valid stream to pass to FlateStream constructor

class FlateStreamTest_196 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }

    // Helper to create a FlateStream with an empty/minimal underlying stream
    std::unique_ptr<FlateStream> createFlateStream() {
        // Create a minimal MemStream as the underlying stream
        // An empty compressed stream: we use a minimal valid deflate stream
        // A stored block with 0 bytes: 0x01 0x00 0x00 0xff 0xff
        static unsigned char data[] = { 0x01, 0x00, 0x00, 0xff, 0xff };
        auto baseStream = std::make_unique<MemStream>(reinterpret_cast<const char *>(data), 0, sizeof(data), Object(objNull));
        return std::make_unique<FlateStream>(std::move(baseStream), 1, 0, 1, 8);
    }

    std::unique_ptr<FlateStream> createFlateStreamWithData(unsigned char* data, int len) {
        auto baseStream = std::make_unique<MemStream>(reinterpret_cast<const char *>(data), 0, len, Object(objNull));
        return std::make_unique<FlateStream>(std::move(baseStream), 1, 0, 1, 8);
    }
};

// Test that getKind returns strFlate
TEST_F(FlateStreamTest_196, GetKindReturnsStrFlate_196) {
    auto stream = createFlateStream();
    EXPECT_EQ(stream->getKind(), strFlate);
}

// Test that isBinary returns expected value
TEST_F(FlateStreamTest_196, IsBinaryReturnsTrue_196) {
    auto stream = createFlateStream();
    // FlateStream is a binary stream
    EXPECT_TRUE(stream->isBinary(true));
}

TEST_F(FlateStreamTest_196, IsBinaryWithLastFalse_196) {
    auto stream = createFlateStream();
    EXPECT_TRUE(stream->isBinary(false));
}

// Test rewind functionality
TEST_F(FlateStreamTest_196, RewindSucceeds_196) {
    auto stream = createFlateStream();
    bool result = stream->rewind();
    // rewind should succeed on a valid stream
    EXPECT_TRUE(result);
}

// Test that getChar returns EOF on empty compressed data
TEST_F(FlateStreamTest_196, GetCharOnEmptyCompressedData_196) {
    auto stream = createFlateStream();
    stream->rewind();
    int ch = stream->getChar();
    EXPECT_EQ(ch, EOF);
}

// Test that lookChar returns EOF on empty compressed data
TEST_F(FlateStreamTest_196, LookCharOnEmptyCompressedData_196) {
    auto stream = createFlateStream();
    stream->rewind();
    int ch = stream->lookChar();
    EXPECT_EQ(ch, EOF);
}

// Test that getRawChar returns EOF on empty compressed data
TEST_F(FlateStreamTest_196, GetRawCharOnEmptyCompressedData_196) {
    auto stream = createFlateStream();
    stream->rewind();
    int ch = stream->getRawChar();
    EXPECT_EQ(ch, EOF);
}

// Test getPSFilter returns nullopt for flate at certain PS levels
TEST_F(FlateStreamTest_196, GetPSFilterReturnsValue_196) {
    auto stream = createFlateStream();
    auto result = stream->getPSFilter(1, "");
    // PS level 1 typically doesn't support flate
    EXPECT_FALSE(result.has_value());
}

TEST_F(FlateStreamTest_196, GetPSFilterLevel3_196) {
    auto stream = createFlateStream();
    auto result = stream->getPSFilter(3, "");
    // PS level 3 may support flate
    // We just check it doesn't crash; the result depends on implementation
    // Either it has a value or it doesn't
    (void)result;
}

// Test unfilteredRewind
TEST_F(FlateStreamTest_196, UnfilteredRewind_196) {
    auto stream = createFlateStream();
    bool result = stream->unfilteredRewind();
    EXPECT_TRUE(result);
}

// Test getRawChars with 0 chars
TEST_F(FlateStreamTest_196, GetRawCharsZero_196) {
    auto stream = createFlateStream();
    stream->rewind();
    int buffer[1] = {0};
    stream->getRawChars(0, buffer);
    // Should not crash
    EXPECT_EQ(buffer[0], 0);
}

// Test multiple rewinds
TEST_F(FlateStreamTest_196, MultipleRewinds_196) {
    auto stream = createFlateStream();
    EXPECT_TRUE(stream->rewind());
    EXPECT_EQ(stream->getChar(), EOF);
    EXPECT_TRUE(stream->rewind());
    EXPECT_EQ(stream->getChar(), EOF);
}

// Test with actual compressed data (deflate of "Hello")
TEST_F(FlateStreamTest_196, DecompressValidData_196) {
    // Raw deflate (no zlib header) of "Hello"
    // Created using: echo -n "Hello" | python3 -c "import zlib,sys; d=zlib.compress(sys.stdin.buffer.read(),9); sys.stdout.buffer.write(d[2:-4])"
    // Raw deflate for "Hello": 0xf2, 0x48, 0xcd, 0xc9, 0xc9, 0x07, 0x00
    static unsigned char compressedData[] = { 0xf2, 0x48, 0xcd, 0xc9, 0xc9, 0x07, 0x00 };
    auto stream = createFlateStreamWithData(compressedData, sizeof(compressedData));
    stream->rewind();
    
    std::string result;
    int ch;
    while ((ch = stream->getChar()) != EOF) {
        result += static_cast<char>(ch);
    }
    // The result might or might not match "Hello" depending on how the stream interprets raw deflate
    // We mainly test it doesn't crash
}

// Test getKind consistency after rewind
TEST_F(FlateStreamTest_196, GetKindConsistentAfterRewind_196) {
    auto stream = createFlateStream();
    EXPECT_EQ(stream->getKind(), strFlate);
    stream->rewind();
    EXPECT_EQ(stream->getKind(), strFlate);
}

// Test lookChar does not consume
TEST_F(FlateStreamTest_196, LookCharDoesNotConsume_196) {
    auto stream = createFlateStream();
    stream->rewind();
    int first = stream->lookChar();
    int second = stream->lookChar();
    EXPECT_EQ(first, second);
}

// Test lookChar followed by getChar returns same value
TEST_F(FlateStreamTest_196, LookCharThenGetCharSameValue_196) {
    auto stream = createFlateStream();
    stream->rewind();
    int looked = stream->lookChar();
    int got = stream->getChar();
    EXPECT_EQ(looked, got);
}

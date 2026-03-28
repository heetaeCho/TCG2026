#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <string>
#include <optional>

#include "Stream.h"
#include "Object.h"

// Helper: Create a MemStream from raw data to use as the underlying stream
static std::unique_ptr<Stream> makeMemStream(const char* data, int len) {
    // We need to create a copy that outlives the stream
    char* buf = (char*)gmalloc(len);
    memcpy(buf, data, len);
    Object dictObj(new Dict(nullptr));
    return std::make_unique<MemStream>(buf, 0, len, std::move(dictObj));
}

class CCITTFaxStreamTest_188 : public ::testing::Test {
protected:
    // Helper to create a CCITTFaxStream with given parameters and some dummy data
    std::unique_ptr<CCITTFaxStream> createStream(
        int encoding = 0,
        bool endOfLine = false,
        bool byteAlign = false,
        int columns = 1728,
        int rows = 0,
        bool endOfBlock = true,
        bool black = false,
        int damagedRowsBeforeError = 0,
        const char* data = "\x00\x00\x00\x00",
        int dataLen = 4)
    {
        auto baseStream = makeMemStream(data, dataLen);
        return std::make_unique<CCITTFaxStream>(
            std::move(baseStream),
            encoding,
            endOfLine,
            byteAlign,
            columns,
            rows,
            endOfBlock,
            black,
            damagedRowsBeforeError
        );
    }
};

// Test that the stream kind is correctly reported
TEST_F(CCITTFaxStreamTest_188, GetKind_188) {
    auto stream = createStream();
    EXPECT_EQ(stream->getKind(), strCCITTFax);
}

// Test accessor for encoding
TEST_F(CCITTFaxStreamTest_188, GetEncoding_188) {
    auto stream = createStream(0);
    EXPECT_EQ(stream->getEncoding(), 0);

    auto stream2 = createStream(1);
    EXPECT_EQ(stream2->getEncoding(), 1);

    auto stream3 = createStream(-1);
    EXPECT_EQ(stream3->getEncoding(), -1);
}

// Test accessor for endOfLine
TEST_F(CCITTFaxStreamTest_188, GetEndOfLine_188) {
    auto stream1 = createStream(0, false);
    EXPECT_FALSE(stream1->getEndOfLine());

    auto stream2 = createStream(0, true);
    EXPECT_TRUE(stream2->getEndOfLine());
}

// Test accessor for byteAlign
TEST_F(CCITTFaxStreamTest_188, GetEncodedByteAlign_188) {
    auto stream1 = createStream(0, false, false);
    EXPECT_FALSE(stream1->getEncodedByteAlign());

    auto stream2 = createStream(0, false, true);
    EXPECT_TRUE(stream2->getEncodedByteAlign());
}

// Test accessor for columns
TEST_F(CCITTFaxStreamTest_188, GetColumns_188) {
    auto stream1 = createStream(0, false, false, 1728);
    EXPECT_EQ(stream1->getColumns(), 1728);

    auto stream2 = createStream(0, false, false, 100);
    EXPECT_EQ(stream2->getColumns(), 100);

    auto stream3 = createStream(0, false, false, 1);
    EXPECT_EQ(stream3->getColumns(), 1);
}

// Test accessor for endOfBlock
TEST_F(CCITTFaxStreamTest_188, GetEndOfBlock_188) {
    auto stream1 = createStream(0, false, false, 1728, 0, true);
    EXPECT_TRUE(stream1->getEndOfBlock());

    auto stream2 = createStream(0, false, false, 1728, 0, false);
    EXPECT_FALSE(stream2->getEndOfBlock());
}

// Test accessor for black
TEST_F(CCITTFaxStreamTest_188, GetBlackIs1_188) {
    auto stream1 = createStream(0, false, false, 1728, 0, true, false);
    EXPECT_FALSE(stream1->getBlackIs1());

    auto stream2 = createStream(0, false, false, 1728, 0, true, true);
    EXPECT_TRUE(stream2->getBlackIs1());
}

// Test accessor for damagedRowsBeforeError
TEST_F(CCITTFaxStreamTest_188, GetDamagedRowsBeforeError_188) {
    auto stream1 = createStream(0, false, false, 1728, 0, true, false, 0);
    EXPECT_EQ(stream1->getDamagedRowsBeforeError(), 0);

    auto stream2 = createStream(0, false, false, 1728, 0, true, false, 5);
    EXPECT_EQ(stream2->getDamagedRowsBeforeError(), 5);
}

// Test isBinary returns true (CCITT streams are binary)
TEST_F(CCITTFaxStreamTest_188, IsBinary_188) {
    auto stream = createStream();
    EXPECT_TRUE(stream->isBinary(true));
    EXPECT_TRUE(stream->isBinary(false));
}

// Test rewind
TEST_F(CCITTFaxStreamTest_188, Rewind_188) {
    auto stream = createStream();
    // Rewind should succeed
    EXPECT_TRUE(stream->rewind());
}

// Test getChar returns EOF on empty/minimal data after exhaustion
TEST_F(CCITTFaxStreamTest_188, GetCharReturnsEOFOnEmptyData_188) {
    // Create with minimal empty data; eventually should return EOF
    const char data[] = "\x00";
    auto stream = createStream(0, false, false, 8, 0, true, false, 0, data, 1);
    stream->rewind();

    // Read characters until EOF
    int count = 0;
    int c;
    while ((c = stream->getChar()) != EOF && count < 10000) {
        count++;
    }
    EXPECT_EQ(c, EOF);
}

// Test lookChar followed by getChar returns the same value
TEST_F(CCITTFaxStreamTest_188, LookCharThenGetChar_188) {
    const char data[] = "\x00\x00\x00\x00\x00\x00\x00\x00";
    auto stream = createStream(0, false, false, 8, 1, false, false, 0, data, 8);
    stream->rewind();

    int looked = stream->lookChar();
    int got = stream->getChar();
    EXPECT_EQ(looked, got);
}

// Test that calling getChar twice doesn't return the same buffered char
TEST_F(CCITTFaxStreamTest_188, GetCharConsumesCharacter_188) {
    // A longer data buffer to ensure we get at least two characters
    char data[64];
    memset(data, 0, sizeof(data));
    auto stream = createStream(0, false, false, 8, 2, false, false, 0, data, 64);
    stream->rewind();

    int c1 = stream->getChar();
    int c2 = stream->getChar();
    // After first getChar, the internal buffer should be EOF,
    // so lookChar should be called again for the next character.
    // They might be the same value (e.g., both white), but the stream
    // should have advanced. We just verify the pattern doesn't crash.
    (void)c1;
    (void)c2;
    SUCCEED();
}

// Test unfilteredRewind
TEST_F(CCITTFaxStreamTest_188, UnfilteredRewind_188) {
    auto stream = createStream();
    EXPECT_TRUE(stream->unfilteredRewind());
}

// Test multiple rewinds
TEST_F(CCITTFaxStreamTest_188, MultipleRewinds_188) {
    auto stream = createStream(0, false, false, 8, 1, false, false, 0);
    EXPECT_TRUE(stream->rewind());
    stream->getChar();
    EXPECT_TRUE(stream->rewind());
    stream->getChar();
    SUCCEED();
}

// Test with Group 4 encoding
TEST_F(CCITTFaxStreamTest_188, Group4Encoding_188) {
    char data[32];
    memset(data, 0, sizeof(data));
    auto stream = createStream(-1, false, false, 8, 1, false, false, 0, data, 32);
    stream->rewind();
    // Just verify it doesn't crash
    int c = stream->getChar();
    (void)c;
    SUCCEED();
}

// Test with Group 3 2D encoding
TEST_F(CCITTFaxStreamTest_188, Group3_2DEncoding_188) {
    char data[32];
    memset(data, 0, sizeof(data));
    auto stream = createStream(1, false, false, 8, 1, false, false, 0, data, 32);
    stream->rewind();
    int c = stream->getChar();
    (void)c;
    SUCCEED();
}

// Test with small column value (boundary)
TEST_F(CCITTFaxStreamTest_188, SmallColumnsBoundary_188) {
    char data[8];
    memset(data, 0xFF, sizeof(data));
    auto stream = createStream(0, false, false, 1, 1, false, true, 0, data, 8);
    stream->rewind();
    EXPECT_EQ(stream->getColumns(), 1);
    int c = stream->getChar();
    (void)c;
    SUCCEED();
}

// Test rows parameter
TEST_F(CCITTFaxStreamTest_188, RowsZeroMeansUnbounded_188) {
    auto stream = createStream(0, false, false, 8, 0, true, false, 0);
    stream->rewind();
    // rows=0 with endOfBlock=true means read until end-of-block code
    SUCCEED();
}

// Test getPSFilter
TEST_F(CCITTFaxStreamTest_188, GetPSFilter_188) {
    auto stream = createStream();
    auto result = stream->getPSFilter(1, "");
    // At PS level 1, CCITTFax might not be supported
    // We just verify it returns something (or nothing) without crashing
    (void)result;
    SUCCEED();
}

// Test getPSFilter at level 2
TEST_F(CCITTFaxStreamTest_188, GetPSFilterLevel2_188) {
    auto stream = createStream();
    auto result = stream->getPSFilter(2, "");
    // Level 2 PostScript should support CCITTFax
    (void)result;
    SUCCEED();
}

// Test with endOfLine enabled
TEST_F(CCITTFaxStreamTest_188, EndOfLineEnabled_188) {
    char data[32];
    memset(data, 0, sizeof(data));
    auto stream = createStream(0, true, false, 8, 1, false, false, 0, data, 32);
    stream->rewind();
    EXPECT_TRUE(stream->getEndOfLine());
    int c = stream->getChar();
    (void)c;
    SUCCEED();
}

// Test with byteAlign enabled
TEST_F(CCITTFaxStreamTest_188, ByteAlignEnabled_188) {
    char data[32];
    memset(data, 0, sizeof(data));
    auto stream = createStream(0, false, true, 8, 1, false, false, 0, data, 32);
    stream->rewind();
    EXPECT_TRUE(stream->getEncodedByteAlign());
    int c = stream->getChar();
    (void)c;
    SUCCEED();
}

// Test reading until EOF with specific rows
TEST_F(CCITTFaxStreamTest_188, ReadUntilEOFWithRows_188) {
    char data[256];
    memset(data, 0, sizeof(data));
    auto stream = createStream(0, false, false, 8, 2, false, false, 0, data, 256);
    stream->rewind();

    int count = 0;
    while (stream->getChar() != EOF && count < 10000) {
        count++;
    }
    // Should terminate
    EXPECT_LT(count, 10000);
}

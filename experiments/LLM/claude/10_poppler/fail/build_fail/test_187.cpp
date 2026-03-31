#include <gtest/gtest.h>
#include <memory>
#include "Stream.h"

// Helper to create a minimal MemStream or similar base stream for CCITTFaxStream
// We need a concrete Stream to pass as the underlying stream.
// Using a MemStream with empty data as a minimal base stream.

class CCITTFaxStreamTest_187 : public ::testing::Test {
protected:
    // Helper to create a CCITTFaxStream with given parameters
    std::unique_ptr<CCITTFaxStream> createStream(
        int encoding = 0,
        bool endOfLine = false,
        bool byteAlign = false,
        int columns = 1728,
        int rows = 0,
        bool endOfBlock = true,
        bool black = false,
        int damagedRowsBeforeError = 0)
    {
        // Create a minimal underlying stream (MemStream with empty buffer)
        static unsigned char emptyBuf[1] = {0};
        auto baseStream = std::make_unique<MemStream>(reinterpret_cast<const char *>(emptyBuf), 0, 1, Object(objNull));
        return std::make_unique<CCITTFaxStream>(std::move(baseStream), encoding, endOfLine, byteAlign, columns, rows, endOfBlock, black, damagedRowsBeforeError);
    }
};

TEST_F(CCITTFaxStreamTest_187, GetKindReturnsCCITTFax_187) {
    auto stream = createStream();
    EXPECT_EQ(stream->getKind(), strCCITTFax);
}

TEST_F(CCITTFaxStreamTest_187, GetEncodingDefault_187) {
    auto stream = createStream(0);
    EXPECT_EQ(stream->getEncoding(), 0);
}

TEST_F(CCITTFaxStreamTest_187, GetEncodingGroup3_187) {
    auto stream = createStream(-1);
    EXPECT_EQ(stream->getEncoding(), -1);
}

TEST_F(CCITTFaxStreamTest_187, GetEncodingGroup4_187) {
    auto stream = createStream(-2);
    EXPECT_EQ(stream->getEncoding(), -2);
}

TEST_F(CCITTFaxStreamTest_187, GetEndOfLineFalse_187) {
    auto stream = createStream(0, false);
    EXPECT_FALSE(stream->getEndOfLine());
}

TEST_F(CCITTFaxStreamTest_187, GetEndOfLineTrue_187) {
    auto stream = createStream(0, true);
    EXPECT_TRUE(stream->getEndOfLine());
}

TEST_F(CCITTFaxStreamTest_187, GetEncodedByteAlignFalse_187) {
    auto stream = createStream(0, false, false);
    EXPECT_FALSE(stream->getEncodedByteAlign());
}

TEST_F(CCITTFaxStreamTest_187, GetEncodedByteAlignTrue_187) {
    auto stream = createStream(0, false, true);
    EXPECT_TRUE(stream->getEncodedByteAlign());
}

TEST_F(CCITTFaxStreamTest_187, GetColumnsDefault_187) {
    auto stream = createStream(0, false, false, 1728);
    EXPECT_EQ(stream->getColumns(), 1728);
}

TEST_F(CCITTFaxStreamTest_187, GetColumnsCustom_187) {
    auto stream = createStream(0, false, false, 100);
    EXPECT_EQ(stream->getColumns(), 100);
}

TEST_F(CCITTFaxStreamTest_187, GetEndOfBlockTrue_187) {
    auto stream = createStream(0, false, false, 1728, 0, true);
    EXPECT_TRUE(stream->getEndOfBlock());
}

TEST_F(CCITTFaxStreamTest_187, GetEndOfBlockFalse_187) {
    auto stream = createStream(0, false, false, 1728, 0, false);
    EXPECT_FALSE(stream->getEndOfBlock());
}

TEST_F(CCITTFaxStreamTest_187, GetBlackIs1False_187) {
    auto stream = createStream(0, false, false, 1728, 0, true, false);
    EXPECT_FALSE(stream->getBlackIs1());
}

TEST_F(CCITTFaxStreamTest_187, GetBlackIs1True_187) {
    auto stream = createStream(0, false, false, 1728, 0, true, true);
    EXPECT_TRUE(stream->getBlackIs1());
}

TEST_F(CCITTFaxStreamTest_187, GetDamagedRowsBeforeErrorDefault_187) {
    auto stream = createStream(0, false, false, 1728, 0, true, false, 0);
    EXPECT_EQ(stream->getDamagedRowsBeforeError(), 0);
}

TEST_F(CCITTFaxStreamTest_187, GetDamagedRowsBeforeErrorCustom_187) {
    auto stream = createStream(0, false, false, 1728, 0, true, false, 5);
    EXPECT_EQ(stream->getDamagedRowsBeforeError(), 5);
}

TEST_F(CCITTFaxStreamTest_187, IsBinaryReturnsTrue_187) {
    auto stream = createStream();
    EXPECT_TRUE(stream->isBinary(true));
}

TEST_F(CCITTFaxStreamTest_187, IsBinaryWithLastFalse_187) {
    auto stream = createStream();
    // CCITTFax is a binary stream regardless
    EXPECT_TRUE(stream->isBinary(false));
}

TEST_F(CCITTFaxStreamTest_187, RewindSucceeds_187) {
    auto stream = createStream();
    // Rewind should not crash and should return a boolean
    bool result = stream->rewind();
    // We just verify it doesn't crash; the result depends on the underlying stream
    (void)result;
}

TEST_F(CCITTFaxStreamTest_187, UnfilteredRewind_187) {
    auto stream = createStream();
    bool result = stream->unfilteredRewind();
    (void)result;
}

TEST_F(CCITTFaxStreamTest_187, LookCharOnEmptyStream_187) {
    auto stream = createStream();
    stream->rewind();
    int ch = stream->lookChar();
    // On an empty/minimal underlying stream, we expect EOF
    EXPECT_EQ(ch, EOF);
}

TEST_F(CCITTFaxStreamTest_187, GetCharOnEmptyStream_187) {
    auto stream = createStream();
    stream->rewind();
    int ch = stream->getChar();
    EXPECT_EQ(ch, EOF);
}

TEST_F(CCITTFaxStreamTest_187, GetPSFilterReturnsValue_187) {
    auto stream = createStream();
    auto result = stream->getPSFilter(1, "");
    // Level 1 PS might not support CCITTFax, so it could return nullopt
    // We just test it doesn't crash
    (void)result;
}

TEST_F(CCITTFaxStreamTest_187, GetPSFilterLevel2_187) {
    auto stream = createStream();
    auto result = stream->getPSFilter(2, "  ");
    // At level 2+, CCITTFaxDecode should be available
    if (result.has_value()) {
        EXPECT_FALSE(result->empty());
    }
}

TEST_F(CCITTFaxStreamTest_187, ColumnsOne_187) {
    auto stream = createStream(0, false, false, 1);
    EXPECT_EQ(stream->getColumns(), 1);
}

TEST_F(CCITTFaxStreamTest_187, LargeColumns_187) {
    auto stream = createStream(0, false, false, 10000);
    EXPECT_EQ(stream->getColumns(), 10000);
}

TEST_F(CCITTFaxStreamTest_187, AllParametersCombined_187) {
    auto stream = createStream(-1, true, true, 2048, 100, false, true, 3);
    EXPECT_EQ(stream->getKind(), strCCITTFax);
    EXPECT_EQ(stream->getEncoding(), -1);
    EXPECT_TRUE(stream->getEndOfLine());
    EXPECT_TRUE(stream->getEncodedByteAlign());
    EXPECT_EQ(stream->getColumns(), 2048);
    EXPECT_FALSE(stream->getEndOfBlock());
    EXPECT_TRUE(stream->getBlackIs1());
    EXPECT_EQ(stream->getDamagedRowsBeforeError(), 3);
}

TEST_F(CCITTFaxStreamTest_187, MultipleRewinds_187) {
    auto stream = createStream();
    stream->rewind();
    stream->rewind();
    stream->rewind();
    // Should not crash after multiple rewinds
    int ch = stream->lookChar();
    EXPECT_EQ(ch, EOF);
}

TEST_F(CCITTFaxStreamTest_187, GetCharAfterLookChar_187) {
    auto stream = createStream();
    stream->rewind();
    int looked = stream->lookChar();
    int got = stream->getChar();
    // lookChar should not consume, getChar should return same value
    EXPECT_EQ(looked, got);
}

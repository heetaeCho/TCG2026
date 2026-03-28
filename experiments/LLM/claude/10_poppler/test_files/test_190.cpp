#include <gtest/gtest.h>
#include <memory>
#include "Stream.h"

// Helper to create a minimal Stream for testing purposes.
// We need a concrete Stream to pass to CCITTFaxStream's constructor.
// Using a MemStream with minimal data.

class CCITTFaxStreamTest_190 : public ::testing::Test {
protected:
    // Helper function to create a CCITTFaxStream with given parameters
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
        // Create a minimal underlying stream - using a MemStream with some data
        static const char data[] = "\x00\x00\x00\x00";
        Object obj;
        auto memStream = std::make_unique<MemStream>(
            const_cast<char *>(data), 0, sizeof(data) - 1, std::move(obj));

        return std::make_unique<CCITTFaxStream>(
            std::move(memStream), encoding, endOfLine, byteAlign,
            columns, rows, endOfBlock, black, damagedRowsBeforeError);
    }
};

// Test getEndOfLine returns the value passed during construction (false)
TEST_F(CCITTFaxStreamTest_190, GetEndOfLine_False_190) {
    auto stream = createStream(0, false, false, 1728, 0, true, false, 0);
    EXPECT_FALSE(stream->getEndOfLine());
}

// Test getEndOfLine returns the value passed during construction (true)
TEST_F(CCITTFaxStreamTest_190, GetEndOfLine_True_190) {
    auto stream = createStream(0, true, false, 1728, 0, true, false, 0);
    EXPECT_TRUE(stream->getEndOfLine());
}

// Test getEncoding returns the value passed during construction
TEST_F(CCITTFaxStreamTest_190, GetEncoding_Default_190) {
    auto stream = createStream(0, false, false, 1728, 0, true, false, 0);
    EXPECT_EQ(stream->getEncoding(), 0);
}

// Test getEncoding with encoding = -1 (Group 3 2D)
TEST_F(CCITTFaxStreamTest_190, GetEncoding_Group3_2D_190) {
    auto stream = createStream(-1, false, false, 1728, 0, true, false, 0);
    EXPECT_EQ(stream->getEncoding(), -1);
}

// Test getEncoding with encoding = 2 (Group 3 1D)
TEST_F(CCITTFaxStreamTest_190, GetEncoding_Group3_1D_190) {
    auto stream = createStream(2, false, false, 1728, 0, true, false, 0);
    EXPECT_EQ(stream->getEncoding(), 2);
}

// Test getEncodedByteAlign returns false
TEST_F(CCITTFaxStreamTest_190, GetEncodedByteAlign_False_190) {
    auto stream = createStream(0, false, false, 1728, 0, true, false, 0);
    EXPECT_FALSE(stream->getEncodedByteAlign());
}

// Test getEncodedByteAlign returns true
TEST_F(CCITTFaxStreamTest_190, GetEncodedByteAlign_True_190) {
    auto stream = createStream(0, false, true, 1728, 0, true, false, 0);
    EXPECT_TRUE(stream->getEncodedByteAlign());
}

// Test getColumns returns the value passed during construction
TEST_F(CCITTFaxStreamTest_190, GetColumns_Default_190) {
    auto stream = createStream(0, false, false, 1728, 0, true, false, 0);
    EXPECT_EQ(stream->getColumns(), 1728);
}

// Test getColumns with a different value
TEST_F(CCITTFaxStreamTest_190, GetColumns_Custom_190) {
    auto stream = createStream(0, false, false, 2048, 0, true, false, 0);
    EXPECT_EQ(stream->getColumns(), 2048);
}

// Test getColumns with minimum value (1)
TEST_F(CCITTFaxStreamTest_190, GetColumns_MinValue_190) {
    auto stream = createStream(0, false, false, 1, 0, true, false, 0);
    EXPECT_EQ(stream->getColumns(), 1);
}

// Test getEndOfBlock returns true
TEST_F(CCITTFaxStreamTest_190, GetEndOfBlock_True_190) {
    auto stream = createStream(0, false, false, 1728, 0, true, false, 0);
    EXPECT_TRUE(stream->getEndOfBlock());
}

// Test getEndOfBlock returns false
TEST_F(CCITTFaxStreamTest_190, GetEndOfBlock_False_190) {
    auto stream = createStream(0, false, false, 1728, 0, false, false, 0);
    EXPECT_FALSE(stream->getEndOfBlock());
}

// Test getBlackIs1 returns false
TEST_F(CCITTFaxStreamTest_190, GetBlackIs1_False_190) {
    auto stream = createStream(0, false, false, 1728, 0, true, false, 0);
    EXPECT_FALSE(stream->getBlackIs1());
}

// Test getBlackIs1 returns true
TEST_F(CCITTFaxStreamTest_190, GetBlackIs1_True_190) {
    auto stream = createStream(0, false, false, 1728, 0, true, true, 0);
    EXPECT_TRUE(stream->getBlackIs1());
}

// Test getDamagedRowsBeforeError returns default value
TEST_F(CCITTFaxStreamTest_190, GetDamagedRowsBeforeError_Default_190) {
    auto stream = createStream(0, false, false, 1728, 0, true, false, 0);
    EXPECT_EQ(stream->getDamagedRowsBeforeError(), 0);
}

// Test getDamagedRowsBeforeError with a custom value
TEST_F(CCITTFaxStreamTest_190, GetDamagedRowsBeforeError_Custom_190) {
    auto stream = createStream(0, false, false, 1728, 0, true, false, 5);
    EXPECT_EQ(stream->getDamagedRowsBeforeError(), 5);
}

// Test getKind returns the correct stream kind for CCITTFax
TEST_F(CCITTFaxStreamTest_190, GetKind_190) {
    auto stream = createStream();
    EXPECT_EQ(stream->getKind(), strCCITTFax);
}

// Test isBinary returns true (CCITT fax is binary data)
TEST_F(CCITTFaxStreamTest_190, IsBinary_190) {
    auto stream = createStream();
    EXPECT_TRUE(stream->isBinary(true));
}

// Test isBinary with last=false
TEST_F(CCITTFaxStreamTest_190, IsBinary_NotLast_190) {
    auto stream = createStream();
    EXPECT_TRUE(stream->isBinary(false));
}

// Test rewind succeeds
TEST_F(CCITTFaxStreamTest_190, Rewind_190) {
    auto stream = createStream();
    EXPECT_TRUE(stream->rewind());
}

// Test unfilteredRewind succeeds
TEST_F(CCITTFaxStreamTest_190, UnfilteredRewind_190) {
    auto stream = createStream();
    EXPECT_TRUE(stream->unfilteredRewind());
}

// Test that all boolean parameters can be set independently
TEST_F(CCITTFaxStreamTest_190, AllParametersCombination_190) {
    auto stream = createStream(
        -1,    // encoding
        true,  // endOfLine
        true,  // byteAlign
        2560,  // columns
        100,   // rows
        false, // endOfBlock
        true,  // black
        3      // damagedRowsBeforeError
    );
    EXPECT_EQ(stream->getEncoding(), -1);
    EXPECT_TRUE(stream->getEndOfLine());
    EXPECT_TRUE(stream->getEncodedByteAlign());
    EXPECT_EQ(stream->getColumns(), 2560);
    EXPECT_FALSE(stream->getEndOfBlock());
    EXPECT_TRUE(stream->getBlackIs1());
    EXPECT_EQ(stream->getDamagedRowsBeforeError(), 3);
}

// Test lookChar after rewind on minimal data
TEST_F(CCITTFaxStreamTest_190, LookChar_AfterRewind_190) {
    auto stream = createStream();
    stream->rewind();
    // lookChar should return a value (either EOF or a valid byte)
    int ch = stream->lookChar();
    EXPECT_TRUE(ch == EOF || (ch >= 0 && ch <= 255));
}

// Test getChar after rewind on minimal data
TEST_F(CCITTFaxStreamTest_190, GetChar_AfterRewind_190) {
    auto stream = createStream();
    stream->rewind();
    int ch = stream->getChar();
    EXPECT_TRUE(ch == EOF || (ch >= 0 && ch <= 255));
}

// Test lookChar is idempotent (calling it multiple times returns the same value)
TEST_F(CCITTFaxStreamTest_190, LookChar_Idempotent_190) {
    auto stream = createStream();
    stream->rewind();
    int ch1 = stream->lookChar();
    int ch2 = stream->lookChar();
    EXPECT_EQ(ch1, ch2);
}

// Test getPSFilter at PS level 1 (likely returns nullopt since CCITTFax may not be supported at level 1)
TEST_F(CCITTFaxStreamTest_190, GetPSFilter_Level1_190) {
    auto stream = createStream();
    auto result = stream->getPSFilter(1, "");
    // Level 1 PostScript may not support CCITTFaxDecode
    // We just verify it returns something valid (either a string or nullopt)
    // No crash is the main concern
}

// Test getPSFilter at PS level 2
TEST_F(CCITTFaxStreamTest_190, GetPSFilter_Level2_190) {
    auto stream = createStream();
    auto result = stream->getPSFilter(2, "");
    // At level 2, CCITTFaxDecode should be available
    // We just verify no crash and the result is valid
}

// Test getPSFilter at PS level 3
TEST_F(CCITTFaxStreamTest_190, GetPSFilter_Level3_190) {
    auto stream = createStream();
    auto result = stream->getPSFilter(3, "  ");
    // No crash expected
}

// Test with zero columns (boundary condition)
TEST_F(CCITTFaxStreamTest_190, ZeroColumns_190) {
    // Zero columns is a boundary condition
    auto stream = createStream(0, false, false, 0, 0, true, false, 0);
    EXPECT_EQ(stream->getColumns(), 0);
}

// Test with large damagedRowsBeforeError
TEST_F(CCITTFaxStreamTest_190, LargeDamagedRows_190) {
    auto stream = createStream(0, false, false, 1728, 0, true, false, 1000);
    EXPECT_EQ(stream->getDamagedRowsBeforeError(), 1000);
}

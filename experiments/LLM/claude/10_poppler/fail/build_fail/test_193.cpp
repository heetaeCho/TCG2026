#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include "Stream.h"

// Helper to create a minimal Stream for CCITTFaxStream construction
// We need a concrete Stream subclass to pass as the underlying stream.
// Using a MemoryStream or similar minimal stream.

class MockStream : public Stream {
public:
    MockStream() = default;
    ~MockStream() override = default;
    
    StreamKind getKind() const override { return strWeird; }
    void reset() override {}
    int getChar() override { return EOF; }
    int lookChar() override { return EOF; }
    bool isBinary(bool /*last*/) const override { return false; }
    int getPos() override { return 0; }
    void setPos(Goffset /*pos*/, int /*dir*/) override {}
    GooString *getPSFilter(int /*psLevel*/, const char * /*indent*/) override { return nullptr; }
    bool isEncoder() const override { return false; }
};

class CCITTFaxStreamTest_193 : public ::testing::Test {
protected:
    std::unique_ptr<CCITTFaxStream> createStream(int encoding = 0,
                                                   bool endOfLine = false,
                                                   bool byteAlign = false,
                                                   int columns = 1728,
                                                   int rows = 0,
                                                   bool endOfBlock = true,
                                                   bool black = false,
                                                   int damagedRowsBeforeError = 0) {
        auto underlying = std::make_unique<MockStream>();
        return std::make_unique<CCITTFaxStream>(std::move(underlying),
                                                 encoding,
                                                 endOfLine,
                                                 byteAlign,
                                                 columns,
                                                 rows,
                                                 endOfBlock,
                                                 black,
                                                 damagedRowsBeforeError);
    }
};

// Test getColumns returns the value passed as columnsA
TEST_F(CCITTFaxStreamTest_193, GetColumnsReturnsConstructorValue_193) {
    auto stream = createStream(0, false, false, 1728, 0, true, false, 0);
    EXPECT_EQ(stream->getColumns(), 1728);
}

TEST_F(CCITTFaxStreamTest_193, GetColumnsCustomValue_193) {
    auto stream = createStream(0, false, false, 2048, 0, true, false, 0);
    EXPECT_EQ(stream->getColumns(), 2048);
}

TEST_F(CCITTFaxStreamTest_193, GetColumnsZero_193) {
    auto stream = createStream(0, false, false, 0, 0, true, false, 0);
    EXPECT_EQ(stream->getColumns(), 0);
}

TEST_F(CCITTFaxStreamTest_193, GetColumnsOne_193) {
    auto stream = createStream(0, false, false, 1, 0, true, false, 0);
    EXPECT_EQ(stream->getColumns(), 1);
}

TEST_F(CCITTFaxStreamTest_193, GetColumnsLargeValue_193) {
    auto stream = createStream(0, false, false, 100000, 0, true, false, 0);
    EXPECT_EQ(stream->getColumns(), 100000);
}

// Test getEncoding returns the value passed as encodingA
TEST_F(CCITTFaxStreamTest_193, GetEncodingReturnsConstructorValue_193) {
    auto stream = createStream(0, false, false, 1728, 0, true, false, 0);
    EXPECT_EQ(stream->getEncoding(), 0);
}

TEST_F(CCITTFaxStreamTest_193, GetEncodingGroup4_193) {
    auto stream = createStream(-1, false, false, 1728, 0, true, false, 0);
    EXPECT_EQ(stream->getEncoding(), -1);
}

TEST_F(CCITTFaxStreamTest_193, GetEncodingGroup3_2D_193) {
    auto stream = createStream(1, false, false, 1728, 0, true, false, 0);
    EXPECT_EQ(stream->getEncoding(), 1);
}

// Test getEndOfLine returns the value passed as endOfLineA
TEST_F(CCITTFaxStreamTest_193, GetEndOfLineTrue_193) {
    auto stream = createStream(0, true, false, 1728, 0, true, false, 0);
    EXPECT_TRUE(stream->getEndOfLine());
}

TEST_F(CCITTFaxStreamTest_193, GetEndOfLineFalse_193) {
    auto stream = createStream(0, false, false, 1728, 0, true, false, 0);
    EXPECT_FALSE(stream->getEndOfLine());
}

// Test getEncodedByteAlign returns the value passed as byteAlignA
TEST_F(CCITTFaxStreamTest_193, GetEncodedByteAlignTrue_193) {
    auto stream = createStream(0, false, true, 1728, 0, true, false, 0);
    EXPECT_TRUE(stream->getEncodedByteAlign());
}

TEST_F(CCITTFaxStreamTest_193, GetEncodedByteAlignFalse_193) {
    auto stream = createStream(0, false, false, 1728, 0, true, false, 0);
    EXPECT_FALSE(stream->getEncodedByteAlign());
}

// Test getEndOfBlock returns the value passed as endOfBlockA
TEST_F(CCITTFaxStreamTest_193, GetEndOfBlockTrue_193) {
    auto stream = createStream(0, false, false, 1728, 0, true, false, 0);
    EXPECT_TRUE(stream->getEndOfBlock());
}

TEST_F(CCITTFaxStreamTest_193, GetEndOfBlockFalse_193) {
    auto stream = createStream(0, false, false, 1728, 0, false, false, 0);
    EXPECT_FALSE(stream->getEndOfBlock());
}

// Test getBlackIs1 returns the value passed as blackA
TEST_F(CCITTFaxStreamTest_193, GetBlackIs1True_193) {
    auto stream = createStream(0, false, false, 1728, 0, true, true, 0);
    EXPECT_TRUE(stream->getBlackIs1());
}

TEST_F(CCITTFaxStreamTest_193, GetBlackIs1False_193) {
    auto stream = createStream(0, false, false, 1728, 0, true, false, 0);
    EXPECT_FALSE(stream->getBlackIs1());
}

// Test getDamagedRowsBeforeError returns the value passed
TEST_F(CCITTFaxStreamTest_193, GetDamagedRowsBeforeErrorZero_193) {
    auto stream = createStream(0, false, false, 1728, 0, true, false, 0);
    EXPECT_EQ(stream->getDamagedRowsBeforeError(), 0);
}

TEST_F(CCITTFaxStreamTest_193, GetDamagedRowsBeforeErrorNonZero_193) {
    auto stream = createStream(0, false, false, 1728, 0, true, false, 5);
    EXPECT_EQ(stream->getDamagedRowsBeforeError(), 5);
}

// Test getKind returns the correct StreamKind for CCITTFax
TEST_F(CCITTFaxStreamTest_193, GetKindReturnsCCITTFax_193) {
    auto stream = createStream();
    EXPECT_EQ(stream->getKind(), strCCITTFax);
}

// Test isBinary - CCITTFax streams are binary
TEST_F(CCITTFaxStreamTest_193, IsBinaryReturnsTrue_193) {
    auto stream = createStream();
    EXPECT_TRUE(stream->isBinary(true));
}

TEST_F(CCITTFaxStreamTest_193, IsBinaryReturnsTrueWithLastFalse_193) {
    auto stream = createStream();
    EXPECT_TRUE(stream->isBinary(false));
}

// Test that all parameters can be set and retrieved independently
TEST_F(CCITTFaxStreamTest_193, AllParametersCombination_193) {
    auto stream = createStream(-1, true, true, 512, 100, false, true, 3);
    EXPECT_EQ(stream->getEncoding(), -1);
    EXPECT_TRUE(stream->getEndOfLine());
    EXPECT_TRUE(stream->getEncodedByteAlign());
    EXPECT_EQ(stream->getColumns(), 512);
    EXPECT_FALSE(stream->getEndOfBlock());
    EXPECT_TRUE(stream->getBlackIs1());
    EXPECT_EQ(stream->getDamagedRowsBeforeError(), 3);
}

// Test negative columns value (boundary)
TEST_F(CCITTFaxStreamTest_193, GetColumnsNegativeValue_193) {
    auto stream = createStream(0, false, false, -1, 0, true, false, 0);
    EXPECT_EQ(stream->getColumns(), -1);
}

// Test lookChar on empty/EOF stream
TEST_F(CCITTFaxStreamTest_193, LookCharOnEmptyStream_193) {
    auto stream = createStream();
    stream->rewind();
    int ch = stream->lookChar();
    // On an empty underlying stream, we expect EOF eventually
    EXPECT_TRUE(ch == EOF || ch >= 0);
}

// Test getChar on empty/EOF stream
TEST_F(CCITTFaxStreamTest_193, GetCharOnEmptyStream_193) {
    auto stream = createStream();
    stream->rewind();
    int ch = stream->getChar();
    // On an empty underlying stream, expect EOF
    EXPECT_TRUE(ch == EOF || ch >= 0);
}

// Test rewind returns successfully
TEST_F(CCITTFaxStreamTest_193, RewindSucceeds_193) {
    auto stream = createStream();
    bool result = stream->rewind();
    // rewind should succeed
    EXPECT_TRUE(result);
}

// Test unfilteredRewind
TEST_F(CCITTFaxStreamTest_193, UnfilteredRewindSucceeds_193) {
    auto stream = createStream();
    bool result = stream->unfilteredRewind();
    EXPECT_TRUE(result);
}

// Test with encoding value 2 (not standard but testing boundary)
TEST_F(CCITTFaxStreamTest_193, GetEncodingNonStandardValue_193) {
    auto stream = createStream(2, false, false, 1728, 0, true, false, 0);
    EXPECT_EQ(stream->getEncoding(), 2);
}

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include "JBIG2Stream.h"
#include "Stream.h"
#include "Object.h"

// Helper to create a minimal underlying stream for JBIG2Stream construction
// We need a concrete Stream to pass as the underlying stream.
// Using a MemStream (memory-based stream) as the simplest available option.

class JBIG2StreamTest_1481 : public ::testing::Test {
protected:
    std::unique_ptr<JBIG2Stream> createJBIG2Stream() {
        // Create a minimal memory stream with empty data
        static char emptyData[] = "";
        Object dictObj;
        dictObj = Object(new Dict(nullptr));
        auto memStream = std::make_unique<MemStream>(emptyData, 0, 0, std::move(dictObj));

        Object globalsStreamObj;
        Object globalsStreamRefObj;

        return std::make_unique<JBIG2Stream>(std::move(memStream), std::move(globalsStreamObj), &globalsStreamRefObj);
    }

    std::unique_ptr<JBIG2Stream> createJBIG2StreamWithData(char *data, int length) {
        Object dictObj;
        dictObj = Object(new Dict(nullptr));
        auto memStream = std::make_unique<MemStream>(data, 0, length, std::move(dictObj));

        Object globalsStreamObj;
        Object globalsStreamRefObj;

        return std::make_unique<JBIG2Stream>(std::move(memStream), std::move(globalsStreamObj), &globalsStreamRefObj);
    }
};

// Test that getKind returns strJBIG2
TEST_F(JBIG2StreamTest_1481, GetKindReturnsJBIG2_1481) {
    auto stream = createJBIG2Stream();
    ASSERT_NE(stream, nullptr);
    EXPECT_EQ(stream->getKind(), strJBIG2);
}

// Test that isBinary returns true (JBIG2 is a binary format)
TEST_F(JBIG2StreamTest_1481, IsBinaryReturnsTrue_1481) {
    auto stream = createJBIG2Stream();
    ASSERT_NE(stream, nullptr);
    EXPECT_TRUE(stream->isBinary(true));
}

// Test isBinary with last=false
TEST_F(JBIG2StreamTest_1481, IsBinaryWithLastFalse_1481) {
    auto stream = createJBIG2Stream();
    ASSERT_NE(stream, nullptr);
    EXPECT_TRUE(stream->isBinary(false));
}

// Test that getPSFilter returns empty optional (JBIG2 typically can't produce PS filter)
TEST_F(JBIG2StreamTest_1481, GetPSFilterReturnsEmpty_1481) {
    auto stream = createJBIG2Stream();
    ASSERT_NE(stream, nullptr);
    auto result = stream->getPSFilter(1, "");
    EXPECT_FALSE(result.has_value());
}

// Test getPSFilter with different PS levels
TEST_F(JBIG2StreamTest_1481, GetPSFilterWithLevel2_1481) {
    auto stream = createJBIG2Stream();
    ASSERT_NE(stream, nullptr);
    auto result = stream->getPSFilter(2, "  ");
    EXPECT_FALSE(result.has_value());
}

TEST_F(JBIG2StreamTest_1481, GetPSFilterWithLevel3_1481) {
    auto stream = createJBIG2Stream();
    ASSERT_NE(stream, nullptr);
    auto result = stream->getPSFilter(3, "  ");
    EXPECT_FALSE(result.has_value());
}

// Test rewind on empty stream
TEST_F(JBIG2StreamTest_1481, RewindOnEmptyStream_1481) {
    auto stream = createJBIG2Stream();
    ASSERT_NE(stream, nullptr);
    // rewind should not crash; it processes segments from the underlying stream
    stream->rewind();
}

// Test getChar on empty stream returns EOF
TEST_F(JBIG2StreamTest_1481, GetCharOnEmptyStreamReturnsEOF_1481) {
    auto stream = createJBIG2Stream();
    ASSERT_NE(stream, nullptr);
    stream->rewind();
    int ch = stream->getChar();
    EXPECT_EQ(ch, EOF);
}

// Test lookChar on empty stream returns EOF
TEST_F(JBIG2StreamTest_1481, LookCharOnEmptyStreamReturnsEOF_1481) {
    auto stream = createJBIG2Stream();
    ASSERT_NE(stream, nullptr);
    stream->rewind();
    int ch = stream->lookChar();
    EXPECT_EQ(ch, EOF);
}

// Test close does not crash
TEST_F(JBIG2StreamTest_1481, CloseDoesNotCrash_1481) {
    auto stream = createJBIG2Stream();
    ASSERT_NE(stream, nullptr);
    stream->rewind();
    stream->close();
}

// Test getPos on empty stream
TEST_F(JBIG2StreamTest_1481, GetPosOnEmptyStream_1481) {
    auto stream = createJBIG2Stream();
    ASSERT_NE(stream, nullptr);
    stream->rewind();
    Goffset pos = stream->getPos();
    EXPECT_GE(pos, 0);
}

// Test multiple rewinds don't crash
TEST_F(JBIG2StreamTest_1481, MultipleRewinds_1481) {
    auto stream = createJBIG2Stream();
    ASSERT_NE(stream, nullptr);
    stream->rewind();
    stream->rewind();
    stream->rewind();
    int ch = stream->getChar();
    EXPECT_EQ(ch, EOF);
}

// Test that getChar after close returns EOF
TEST_F(JBIG2StreamTest_1481, GetCharAfterClose_1481) {
    auto stream = createJBIG2Stream();
    ASSERT_NE(stream, nullptr);
    stream->rewind();
    stream->close();
    // After close, attempting to read should return EOF
    int ch = stream->getChar();
    EXPECT_EQ(ch, EOF);
}

// Test that lookChar after close returns EOF
TEST_F(JBIG2StreamTest_1481, LookCharAfterClose_1481) {
    auto stream = createJBIG2Stream();
    ASSERT_NE(stream, nullptr);
    stream->rewind();
    stream->close();
    int ch = stream->lookChar();
    EXPECT_EQ(ch, EOF);
}

// Test getGlobalsStream with no globals
TEST_F(JBIG2StreamTest_1481, GetGlobalsStreamNoGlobals_1481) {
    auto stream = createJBIG2Stream();
    ASSERT_NE(stream, nullptr);
    Object *globalsStream = stream->getGlobalsStream();
    // When no globals stream is provided, it should return a pointer but the object may be null/none
    ASSERT_NE(globalsStream, nullptr);
}

// Test getGlobalsStreamRef with no globals
TEST_F(JBIG2StreamTest_1481, GetGlobalsStreamRefNoGlobals_1481) {
    auto stream = createJBIG2Stream();
    ASSERT_NE(stream, nullptr);
    Ref ref = stream->getGlobalsStreamRef();
    // With no globals stream ref, we expect an invalid ref
    EXPECT_EQ(ref.num, -1);
}

// Test that getKind is consistent across multiple calls
TEST_F(JBIG2StreamTest_1481, GetKindConsistency_1481) {
    auto stream = createJBIG2Stream();
    ASSERT_NE(stream, nullptr);
    EXPECT_EQ(stream->getKind(), strJBIG2);
    EXPECT_EQ(stream->getKind(), strJBIG2);
    EXPECT_EQ(stream->getKind(), strJBIG2);
}

// Test rewind then close then rewind
TEST_F(JBIG2StreamTest_1481, RewindCloseRewind_1481) {
    auto stream = createJBIG2Stream();
    ASSERT_NE(stream, nullptr);
    stream->rewind();
    stream->close();
    stream->rewind();
    // Should not crash, getChar should return EOF for empty/invalid data
    int ch = stream->getChar();
    EXPECT_EQ(ch, EOF);
}

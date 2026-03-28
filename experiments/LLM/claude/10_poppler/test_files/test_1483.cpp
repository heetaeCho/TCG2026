#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

#include "JBIG2Stream.h"
#include "Stream.h"
#include "Object.h"

// Helper to create a minimal underlying stream for JBIG2Stream construction
static std::unique_ptr<Stream> createMemStream(const char* data, int len) {
    // Create a MemStream or similar; we need a valid Stream object
    char* buf = (char*)gmalloc(len);
    memcpy(buf, data, len);
    Object dictObj(objNull);
    return std::make_unique<MemStream>(buf, 0, len, std::move(dictObj));
}

class JBIG2StreamTest_1483 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }

    std::unique_ptr<JBIG2Stream> createJBIG2Stream(Object* globalsStreamRefObj = nullptr) {
        // Minimal empty data
        const char data[] = "";
        auto baseStream = createMemStream(data, 0);
        Object globalsStreamObj;
        globalsStreamObj = Object(objNull);
        return std::make_unique<JBIG2Stream>(std::move(baseStream), std::move(globalsStreamObj), globalsStreamRefObj);
    }

    std::unique_ptr<JBIG2Stream> createJBIG2StreamWithData(const char* data, int len, Object* globalsStreamRefObj = nullptr) {
        auto baseStream = createMemStream(data, len);
        Object globalsStreamObj;
        globalsStreamObj = Object(objNull);
        return std::make_unique<JBIG2Stream>(std::move(baseStream), std::move(globalsStreamObj), globalsStreamRefObj);
    }
};

// Test getGlobalsStreamRef returns default/invalid Ref when no globals stream ref is provided
TEST_F(JBIG2StreamTest_1483, GetGlobalsStreamRefDefault_1483) {
    auto stream = createJBIG2Stream(nullptr);
    Ref ref = stream->getGlobalsStreamRef();
    // When no globals stream ref is provided, expect an invalid ref
    EXPECT_EQ(ref.num, -1);
    EXPECT_EQ(ref.gen, -1);
}

// Test getGlobalsStreamRef returns the provided Ref
TEST_F(JBIG2StreamTest_1483, GetGlobalsStreamRefProvided_1483) {
    Object refObj;
    refObj = Object(Ref{42, 7});
    auto baseStream = createMemStream("", 0);
    Object globalsStreamObj(objNull);
    auto stream = std::make_unique<JBIG2Stream>(std::move(baseStream), std::move(globalsStreamObj), &refObj);
    Ref ref = stream->getGlobalsStreamRef();
    EXPECT_EQ(ref.num, 42);
    EXPECT_EQ(ref.gen, 7);
}

// Test getKind returns the correct stream kind
TEST_F(JBIG2StreamTest_1483, GetKind_1483) {
    auto stream = createJBIG2Stream(nullptr);
    EXPECT_EQ(stream->getKind(), strJBIG2);
}

// Test isBinary returns true (JBIG2 is a binary format)
TEST_F(JBIG2StreamTest_1483, IsBinary_1483) {
    auto stream = createJBIG2Stream(nullptr);
    EXPECT_TRUE(stream->isBinary(true));
    EXPECT_TRUE(stream->isBinary(false));
}

// Test getPSFilter returns empty optional (JBIG2 typically has no PS filter)
TEST_F(JBIG2StreamTest_1483, GetPSFilter_1483) {
    auto stream = createJBIG2Stream(nullptr);
    auto result = stream->getPSFilter(1, "");
    EXPECT_FALSE(result.has_value());
}

// Test rewind on empty stream
TEST_F(JBIG2StreamTest_1483, RewindEmptyStream_1483) {
    auto stream = createJBIG2Stream(nullptr);
    // rewind should not crash and should return
    bool result = stream->rewind();
    // After rewind, stream should be in a valid state (even if empty)
    (void)result;
}

// Test getChar on empty/no-data stream returns EOF
TEST_F(JBIG2StreamTest_1483, GetCharEmptyStream_1483) {
    auto stream = createJBIG2Stream(nullptr);
    stream->rewind();
    int c = stream->getChar();
    EXPECT_EQ(c, EOF);
}

// Test lookChar on empty/no-data stream returns EOF
TEST_F(JBIG2StreamTest_1483, LookCharEmptyStream_1483) {
    auto stream = createJBIG2Stream(nullptr);
    stream->rewind();
    int c = stream->lookChar();
    EXPECT_EQ(c, EOF);
}

// Test close does not crash
TEST_F(JBIG2StreamTest_1483, CloseDoesNotCrash_1483) {
    auto stream = createJBIG2Stream(nullptr);
    stream->rewind();
    EXPECT_NO_FATAL_FAILURE(stream->close());
}

// Test getPos on empty stream
TEST_F(JBIG2StreamTest_1483, GetPosEmptyStream_1483) {
    auto stream = createJBIG2Stream(nullptr);
    stream->rewind();
    Goffset pos = stream->getPos();
    EXPECT_GE(pos, 0);
}

// Test getGlobalsStream with null globals
TEST_F(JBIG2StreamTest_1483, GetGlobalsStreamNull_1483) {
    auto stream = createJBIG2Stream(nullptr);
    Object* globalsStream = stream->getGlobalsStream();
    ASSERT_NE(globalsStream, nullptr);
    // The globals stream object should be null type since we passed objNull
    EXPECT_TRUE(globalsStream->isNull());
}

// Test multiple rewind calls don't crash
TEST_F(JBIG2StreamTest_1483, MultipleRewinds_1483) {
    auto stream = createJBIG2Stream(nullptr);
    stream->rewind();
    stream->rewind();
    stream->rewind();
    int c = stream->getChar();
    EXPECT_EQ(c, EOF);
}

// Test close then rewind cycle
TEST_F(JBIG2StreamTest_1483, CloseAndRewind_1483) {
    auto stream = createJBIG2Stream(nullptr);
    stream->rewind();
    stream->close();
    stream->rewind();
    int c = stream->getChar();
    EXPECT_EQ(c, EOF);
}

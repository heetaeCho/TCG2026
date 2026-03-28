#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "poppler/JBIG2Stream.h"
#include "poppler/Stream.h"
#include "poppler/Object.h"

// Helper: Create a minimal Stream for JBIG2Stream construction
// We need a concrete Stream subclass to pass to JBIG2Stream
class DummyStream : public Stream {
public:
    DummyStream() : Stream() {}
    ~DummyStream() override = default;
    StreamKind getKind() const override { return strWeird; }
    void reset() override {}
    int getChar() override { return EOF; }
    int lookChar() override { return EOF; }
    Goffset getPos() override { return 0; }
    GooString *getPSFilter(int /*psLevel*/, const char * /*indent*/) override { return nullptr; }
    bool isBinary(bool /*last*/) override { return false; }
};

class JBIG2StreamTest_1482 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that getGlobalsStream returns a non-null pointer when constructed with a null globals stream
TEST_F(JBIG2StreamTest_1482, GetGlobalsStreamReturnsNonNull_1482) {
    auto baseStr = std::make_unique<DummyStream>();
    Object globalsObj;
    JBIG2Stream jbig2Stream(std::move(baseStr), std::move(globalsObj), nullptr);

    Object *globalsStream = jbig2Stream.getGlobalsStream();
    ASSERT_NE(globalsStream, nullptr);
}

// Test that getGlobalsStream returns an object of type objNull when no globals stream is provided
TEST_F(JBIG2StreamTest_1482, GetGlobalsStreamDefaultIsNull_1482) {
    auto baseStr = std::make_unique<DummyStream>();
    Object globalsObj;
    JBIG2Stream jbig2Stream(std::move(baseStr), std::move(globalsObj), nullptr);

    Object *globalsStream = jbig2Stream.getGlobalsStream();
    ASSERT_NE(globalsStream, nullptr);
    EXPECT_TRUE(globalsStream->isNull() || globalsStream->isNone());
}

// Test that getKind returns strJBIG2
TEST_F(JBIG2StreamTest_1482, GetKindReturnsJBIG2_1482) {
    auto baseStr = std::make_unique<DummyStream>();
    Object globalsObj;
    JBIG2Stream jbig2Stream(std::move(baseStr), std::move(globalsObj), nullptr);

    EXPECT_EQ(jbig2Stream.getKind(), strJBIG2);
}

// Test that isBinary returns true (JBIG2 is a binary format)
TEST_F(JBIG2StreamTest_1482, IsBinaryReturnsTrue_1482) {
    auto baseStr = std::make_unique<DummyStream>();
    Object globalsObj;
    JBIG2Stream jbig2Stream(std::move(baseStr), std::move(globalsObj), nullptr);

    EXPECT_TRUE(jbig2Stream.isBinary(true));
    EXPECT_TRUE(jbig2Stream.isBinary(false));
}

// Test that getChar returns EOF on empty/reset stream
TEST_F(JBIG2StreamTest_1482, GetCharOnEmptyStream_1482) {
    auto baseStr = std::make_unique<DummyStream>();
    Object globalsObj;
    JBIG2Stream jbig2Stream(std::move(baseStr), std::move(globalsObj), nullptr);

    // After construction without reset, getChar behavior
    int ch = jbig2Stream.getChar();
    // On an empty underlying stream, we expect EOF
    EXPECT_EQ(ch, EOF);
}

// Test that lookChar returns EOF on empty/reset stream
TEST_F(JBIG2StreamTest_1482, LookCharOnEmptyStream_1482) {
    auto baseStr = std::make_unique<DummyStream>();
    Object globalsObj;
    JBIG2Stream jbig2Stream(std::move(baseStr), std::move(globalsObj), nullptr);

    int ch = jbig2Stream.lookChar();
    EXPECT_EQ(ch, EOF);
}

// Test that rewind can be called without crashing
TEST_F(JBIG2StreamTest_1482, RewindDoesNotCrash_1482) {
    auto baseStr = std::make_unique<DummyStream>();
    Object globalsObj;
    JBIG2Stream jbig2Stream(std::move(baseStr), std::move(globalsObj), nullptr);

    // rewind should not crash on a stream with empty underlying data
    bool result = jbig2Stream.rewind();
    // We just check it doesn't crash; the return value depends on implementation
    (void)result;
}

// Test that close can be called without crashing
TEST_F(JBIG2StreamTest_1482, CloseDoesNotCrash_1482) {
    auto baseStr = std::make_unique<DummyStream>();
    Object globalsObj;
    JBIG2Stream jbig2Stream(std::move(baseStr), std::move(globalsObj), nullptr);

    // close should not crash
    EXPECT_NO_FATAL_FAILURE(jbig2Stream.close());
}

// Test that getPos returns a valid position
TEST_F(JBIG2StreamTest_1482, GetPosInitialValue_1482) {
    auto baseStr = std::make_unique<DummyStream>();
    Object globalsObj;
    JBIG2Stream jbig2Stream(std::move(baseStr), std::move(globalsObj), nullptr);

    Goffset pos = jbig2Stream.getPos();
    // Position should be non-negative or 0 initially
    EXPECT_GE(pos, 0);
}

// Test that getPSFilter returns nullopt for JBIG2 (no PS filter representation)
TEST_F(JBIG2StreamTest_1482, GetPSFilterReturnsNullopt_1482) {
    auto baseStr = std::make_unique<DummyStream>();
    Object globalsObj;
    JBIG2Stream jbig2Stream(std::move(baseStr), std::move(globalsObj), nullptr);

    auto result = jbig2Stream.getPSFilter(1, "");
    EXPECT_FALSE(result.has_value());
}

// Test that getGlobalsStreamRef works when constructed with nullptr ref
TEST_F(JBIG2StreamTest_1482, GetGlobalsStreamRefWithNullRef_1482) {
    auto baseStr = std::make_unique<DummyStream>();
    Object globalsObj;
    JBIG2Stream jbig2Stream(std::move(baseStr), std::move(globalsObj), nullptr);

    Ref ref = jbig2Stream.getGlobalsStreamRef();
    // When constructed with nullptr for globalsStreamRefA, the ref should be invalid
    EXPECT_EQ(ref.num, -1);
}

// Test that getGlobalsStreamRef works when constructed with a valid ref
TEST_F(JBIG2StreamTest_1482, GetGlobalsStreamRefWithValidRef_1482) {
    auto baseStr = std::make_unique<DummyStream>();
    Object globalsObj;
    Ref testRef = {42, 0};
    Object refObj = Object(testRef);
    JBIG2Stream jbig2Stream(std::move(baseStr), std::move(globalsObj), &refObj);

    Ref ref = jbig2Stream.getGlobalsStreamRef();
    // The ref should match what was passed in (if the implementation stores it)
    // This tests observable behavior through the public interface
    (void)ref; // At minimum, this should not crash
}

// Test multiple getChar calls on empty stream all return EOF
TEST_F(JBIG2StreamTest_1482, MultipleGetCharCallsReturnEOF_1482) {
    auto baseStr = std::make_unique<DummyStream>();
    Object globalsObj;
    JBIG2Stream jbig2Stream(std::move(baseStr), std::move(globalsObj), nullptr);

    for (int i = 0; i < 10; ++i) {
        EXPECT_EQ(jbig2Stream.getChar(), EOF);
    }
}

// Test rewind followed by getChar on empty stream
TEST_F(JBIG2StreamTest_1482, RewindThenGetChar_1482) {
    auto baseStr = std::make_unique<DummyStream>();
    Object globalsObj;
    JBIG2Stream jbig2Stream(std::move(baseStr), std::move(globalsObj), nullptr);

    jbig2Stream.rewind();
    int ch = jbig2Stream.getChar();
    EXPECT_EQ(ch, EOF);
}

// Test close followed by rewind
TEST_F(JBIG2StreamTest_1482, CloseFollowedByRewind_1482) {
    auto baseStr = std::make_unique<DummyStream>();
    Object globalsObj;
    JBIG2Stream jbig2Stream(std::move(baseStr), std::move(globalsObj), nullptr);

    jbig2Stream.close();
    // After close, rewind should still be callable
    EXPECT_NO_FATAL_FAILURE(jbig2Stream.rewind());
}

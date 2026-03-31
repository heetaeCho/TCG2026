#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Stream.h"
#include "Object.h"
#include "Dict.h"

// We need a concrete Stream subclass to act as the underlying stream for FilterStream.
// Since FilterStream is abstract (or at least needs a concrete derived class to test),
// we need to create minimal concrete implementations.

// A minimal concrete BaseStream for testing
class MockBaseStream : public Stream {
public:
    MockBaseStream() { }
    ~MockBaseStream() override { }

    StreamKind getKind() const override { return strFile; }
    void reset() override { }
    void close() override { }
    int getChar() override { return EOF; }
    int lookChar() override { return EOF; }
    int getRawChar() override { return EOF; }
    int getUnfilteredChar() override { return EOF; }
    bool unfilteredRewind() override { return true; }
    GooString *getPSFilter(int /*psLevel*/, const char * /*indent*/) override { return nullptr; }
    bool isBinary(bool /*last*/) override { return false; }
    Goffset getPos() override { return 0; }
    void setPos(Goffset /*pos*/, int /*dir*/) override { }
    BaseStream *getBaseStream() override { return nullptr; }
    Stream *getUndecodedStream() override { return this; }
    Dict *getDict() override { return nullptr; }
    Object *getDictObject() override { return nullptr; }
};

// A concrete FilterStream subclass for testing, since FilterStream itself may be abstract
// (it doesn't implement getChar, lookChar, etc.)
class TestFilterStream : public FilterStream {
public:
    explicit TestFilterStream(Stream *strA) : FilterStream(strA) { }
    ~TestFilterStream() override { }

    StreamKind getKind() const override { return strWeird; }
    void reset() override { }
    int getChar() override { return str->getChar(); }
    int lookChar() override { return str->lookChar(); }
    int getRawChar() override { return str->getRawChar(); }
    GooString *getPSFilter(int /*psLevel*/, const char * /*indent*/) override { return nullptr; }
    bool isBinary(bool /*last*/) override { return false; }
};

class FilterStreamTest_144 : public ::testing::Test {
protected:
    void SetUp() override {
        baseStream = new MockBaseStream();
        filterStream = new TestFilterStream(baseStream);
    }

    void TearDown() override {
        // FilterStream destructor should handle deleting the underlying stream
        delete filterStream;
    }

    MockBaseStream *baseStream;
    TestFilterStream *filterStream;
};

// Test that getNextStream returns the stream passed in the constructor
TEST_F(FilterStreamTest_144, GetNextStreamReturnsUnderlyingStream_144) {
    EXPECT_EQ(filterStream->getNextStream(), baseStream);
}

// Test that getNextStream returns non-null when a valid stream is passed
TEST_F(FilterStreamTest_144, GetNextStreamReturnsNonNull_144) {
    EXPECT_NE(filterStream->getNextStream(), nullptr);
}

// Test that getPos delegates to the underlying stream
TEST_F(FilterStreamTest_144, GetPosDelegatesToUnderlyingStream_144) {
    Goffset pos = filterStream->getPos();
    // The MockBaseStream returns 0 from getPos
    EXPECT_EQ(pos, 0);
}

// Test that getBaseStream delegates to the underlying stream
TEST_F(FilterStreamTest_144, GetBaseStreamDelegatesToUnderlyingStream_144) {
    BaseStream *bs = filterStream->getBaseStream();
    // MockBaseStream::getBaseStream returns nullptr
    EXPECT_EQ(bs, nullptr);
}

// Test that getUndecodedStream delegates to the underlying stream
TEST_F(FilterStreamTest_144, GetUndecodedStreamDelegatesToUnderlyingStream_144) {
    Stream *undecodedStream = filterStream->getUndecodedStream();
    // MockBaseStream::getUndecodedStream returns itself (baseStream)
    EXPECT_EQ(undecodedStream, baseStream);
}

// Test that getDict delegates to the underlying stream
TEST_F(FilterStreamTest_144, GetDictDelegatesToUnderlyingStream_144) {
    Dict *dict = filterStream->getDict();
    // MockBaseStream::getDict returns nullptr
    EXPECT_EQ(dict, nullptr);
}

// Test that getDictObject delegates to the underlying stream
TEST_F(FilterStreamTest_144, GetDictObjectDelegatesToUnderlyingStream_144) {
    Object *dictObj = filterStream->getDictObject();
    // MockBaseStream::getDictObject returns nullptr
    EXPECT_EQ(dictObj, nullptr);
}

// Test that getUnfilteredChar delegates to the underlying stream
TEST_F(FilterStreamTest_144, GetUnfilteredCharDelegatesToUnderlyingStream_144) {
    int ch = filterStream->getUnfilteredChar();
    // MockBaseStream::getUnfilteredChar returns EOF
    EXPECT_EQ(ch, EOF);
}

// Test that unfilteredRewind delegates to the underlying stream
TEST_F(FilterStreamTest_144, UnfilteredRewindDelegatesToUnderlyingStream_144) {
    bool result = filterStream->unfilteredRewind();
    // MockBaseStream::unfilteredRewind returns true
    EXPECT_TRUE(result);
}

// Test that getChar delegates through to the underlying stream
TEST_F(FilterStreamTest_144, GetCharReturnsEOFFromEmptyStream_144) {
    int ch = filterStream->getChar();
    EXPECT_EQ(ch, EOF);
}

// Test that lookChar delegates through to the underlying stream
TEST_F(FilterStreamTest_144, LookCharReturnsEOFFromEmptyStream_144) {
    int ch = filterStream->lookChar();
    EXPECT_EQ(ch, EOF);
}

// Test setPos doesn't crash (smoke test for delegation)
TEST_F(FilterStreamTest_144, SetPosDoesNotCrash_144) {
    EXPECT_NO_THROW(filterStream->setPos(0, 0));
}

// Test close doesn't crash (smoke test for delegation)
TEST_F(FilterStreamTest_144, CloseDoesNotCrash_144) {
    EXPECT_NO_THROW(filterStream->close());
}

// Test that getNextStream is const-correct and consistently returns the same pointer
TEST_F(FilterStreamTest_144, GetNextStreamConsistentlyReturnsSamePointer_144) {
    Stream *first = filterStream->getNextStream();
    Stream *second = filterStream->getNextStream();
    EXPECT_EQ(first, second);
    EXPECT_EQ(first, baseStream);
}

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Stream.h"
#include "Object.h"

using ::testing::Return;
using ::testing::_;

// Mock for the underlying Stream that FilterStream wraps
class MockStream : public Stream {
public:
    MOCK_METHOD(StreamKind, getKind, (), (const, override));
    MOCK_METHOD(bool, rewind, (), (override));
    MOCK_METHOD(void, close, (), (override));
    MOCK_METHOD(int, getChar, (), (override));
    MOCK_METHOD(int, lookChar, (), (override));
    MOCK_METHOD(int, getRawChar, (), (override));
    MOCK_METHOD(void, getRawChars, (int nChars, int *buffer), (override));
    MOCK_METHOD(int, getUnfilteredChar, (), (override));
    MOCK_METHOD(bool, unfilteredRewind, (), (override));
    MOCK_METHOD(Goffset, getPos, (), (override));
    MOCK_METHOD(void, setPos, (Goffset pos, int dir), (override));
    MOCK_METHOD(bool, isBinary, (bool last), (const, override));
    MOCK_METHOD(BaseStream*, getBaseStream, (), (override));
    MOCK_METHOD(Stream*, getUndecodedStream, (), (override));
    MOCK_METHOD(Dict*, getDict, (), (override));
    MOCK_METHOD(Object*, getDictObject, (), (override));
    MOCK_METHOD(Stream*, getNextStream, (), (const, override));
    MOCK_METHOD(bool, hasGetChars, (), (override));
    MOCK_METHOD(int, getChars, (int nChars, unsigned char *buffer), (override));
    MOCK_METHOD(bool, isEncoder, (), (const, override));
    MOCK_METHOD(void, getImageParams, (int*, StreamColorSpaceMode*, bool*), (override));
};

// Concrete subclass of FilterStream for testing purposes
// FilterStream is abstract because it doesn't implement getChar, lookChar, etc.
class ConcreteFilterStream : public FilterStream {
public:
    explicit ConcreteFilterStream(Stream *strA) : FilterStream(strA) {}
    ~ConcreteFilterStream() override {
        // Prevent FilterStream destructor from deleting the mock
        str = nullptr;
    }

    StreamKind getKind() const override { return streamKind; }
    bool rewind() override { return true; }
    int getChar() override { return -1; }
    int lookChar() override { return -1; }
    int getRawChar() override { return -1; }
    bool isBinary(bool last) const override { return false; }

private:
    StreamKind streamKind = strWeird;
};

class FilterStreamTest_146 : public ::testing::Test {
protected:
    void SetUp() override {
        mockStream = new MockStream();
        filterStream = new ConcreteFilterStream(mockStream);
    }

    void TearDown() override {
        delete filterStream;
        delete mockStream;
    }

    MockStream *mockStream;
    ConcreteFilterStream *filterStream;
};

// Test unfilteredRewind delegates to underlying stream and returns true
TEST_F(FilterStreamTest_146, UnfilteredRewindDelegatesToUnderlyingStream_ReturnsTrue_146) {
    EXPECT_CALL(*mockStream, unfilteredRewind())
        .WillOnce(Return(true));

    bool result = filterStream->unfilteredRewind();
    EXPECT_TRUE(result);
}

// Test unfilteredRewind delegates to underlying stream and returns false
TEST_F(FilterStreamTest_146, UnfilteredRewindDelegatesToUnderlyingStream_ReturnsFalse_146) {
    EXPECT_CALL(*mockStream, unfilteredRewind())
        .WillOnce(Return(false));

    bool result = filterStream->unfilteredRewind();
    EXPECT_FALSE(result);
}

// Test getUnfilteredChar delegates to underlying stream
TEST_F(FilterStreamTest_146, GetUnfilteredCharDelegatesToUnderlyingStream_146) {
    EXPECT_CALL(*mockStream, getUnfilteredChar())
        .WillOnce(Return(42));

    int result = filterStream->getUnfilteredChar();
    EXPECT_EQ(result, 42);
}

// Test getUnfilteredChar returns EOF from underlying stream
TEST_F(FilterStreamTest_146, GetUnfilteredCharReturnsEOF_146) {
    EXPECT_CALL(*mockStream, getUnfilteredChar())
        .WillOnce(Return(EOF));

    int result = filterStream->getUnfilteredChar();
    EXPECT_EQ(result, EOF);
}

// Test close delegates to underlying stream
TEST_F(FilterStreamTest_146, CloseDelegatesToUnderlyingStream_146) {
    EXPECT_CALL(*mockStream, close())
        .Times(1);

    filterStream->close();
}

// Test setPos delegates to underlying stream
TEST_F(FilterStreamTest_146, SetPosDelegatesToUnderlyingStream_146) {
    EXPECT_CALL(*mockStream, setPos(100, 0))
        .Times(1);

    filterStream->setPos(100, 0);
}

// Test setPos with negative direction
TEST_F(FilterStreamTest_146, SetPosWithNegativeDirection_146) {
    EXPECT_CALL(*mockStream, setPos(0, -1))
        .Times(1);

    filterStream->setPos(0, -1);
}

// Test getPos delegates to underlying stream
TEST_F(FilterStreamTest_146, GetPosDelegatesToUnderlyingStream_146) {
    EXPECT_CALL(*mockStream, getPos())
        .WillOnce(Return(500));

    Goffset pos = filterStream->getPos();
    EXPECT_EQ(pos, 500);
}

// Test getPos returns zero position
TEST_F(FilterStreamTest_146, GetPosReturnsZero_146) {
    EXPECT_CALL(*mockStream, getPos())
        .WillOnce(Return(0));

    Goffset pos = filterStream->getPos();
    EXPECT_EQ(pos, 0);
}

// Test getBaseStream delegates to underlying stream
TEST_F(FilterStreamTest_146, GetBaseStreamDelegatesToUnderlyingStream_146) {
    BaseStream *expectedBase = nullptr;
    EXPECT_CALL(*mockStream, getBaseStream())
        .WillOnce(Return(expectedBase));

    BaseStream *result = filterStream->getBaseStream();
    EXPECT_EQ(result, expectedBase);
}

// Test getUndecodedStream delegates to underlying stream
TEST_F(FilterStreamTest_146, GetUndecodedStreamDelegatesToUnderlyingStream_146) {
    EXPECT_CALL(*mockStream, getUndecodedStream())
        .WillOnce(Return(mockStream));

    Stream *result = filterStream->getUndecodedStream();
    EXPECT_EQ(result, mockStream);
}

// Test getDict delegates to underlying stream
TEST_F(FilterStreamTest_146, GetDictDelegatesToUnderlyingStream_146) {
    Dict *expectedDict = nullptr;
    EXPECT_CALL(*mockStream, getDict())
        .WillOnce(Return(expectedDict));

    Dict *result = filterStream->getDict();
    EXPECT_EQ(result, expectedDict);
}

// Test getDictObject delegates to underlying stream
TEST_F(FilterStreamTest_146, GetDictObjectDelegatesToUnderlyingStream_146) {
    Object *expectedObj = nullptr;
    EXPECT_CALL(*mockStream, getDictObject())
        .WillOnce(Return(expectedObj));

    Object *result = filterStream->getDictObject();
    EXPECT_EQ(result, expectedObj);
}

// Test getNextStream returns the underlying stream
TEST_F(FilterStreamTest_146, GetNextStreamReturnsUnderlyingStream_146) {
    Stream *result = filterStream->getNextStream();
    EXPECT_EQ(result, mockStream);
}

// Test unfilteredRewind called multiple times
TEST_F(FilterStreamTest_146, UnfilteredRewindCalledMultipleTimes_146) {
    EXPECT_CALL(*mockStream, unfilteredRewind())
        .WillOnce(Return(true))
        .WillOnce(Return(false))
        .WillOnce(Return(true));

    EXPECT_TRUE(filterStream->unfilteredRewind());
    EXPECT_FALSE(filterStream->unfilteredRewind());
    EXPECT_TRUE(filterStream->unfilteredRewind());
}

// Test setPos with boundary position values
TEST_F(FilterStreamTest_146, SetPosWithLargeOffset_146) {
    Goffset largeOffset = 1000000000LL;
    EXPECT_CALL(*mockStream, setPos(largeOffset, 0))
        .Times(1);

    filterStream->setPos(largeOffset, 0);
}

// Test getPos with large value
TEST_F(FilterStreamTest_146, GetPosWithLargeValue_146) {
    Goffset largePos = 999999999LL;
    EXPECT_CALL(*mockStream, getPos())
        .WillOnce(Return(largePos));

    Goffset result = filterStream->getPos();
    EXPECT_EQ(result, largePos);
}

// Test getUnfilteredChar with various byte values
TEST_F(FilterStreamTest_146, GetUnfilteredCharWithMaxByteValue_146) {
    EXPECT_CALL(*mockStream, getUnfilteredChar())
        .WillOnce(Return(255));

    int result = filterStream->getUnfilteredChar();
    EXPECT_EQ(result, 255);
}

// Test getUnfilteredChar with zero
TEST_F(FilterStreamTest_146, GetUnfilteredCharWithZero_146) {
    EXPECT_CALL(*mockStream, getUnfilteredChar())
        .WillOnce(Return(0));

    int result = filterStream->getUnfilteredChar();
    EXPECT_EQ(result, 0);
}

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Stream.h"
#include "Object.h"

using ::testing::Return;
using ::testing::_;

// Mock Stream to serve as the underlying stream for FilterStream
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
    MOCK_METHOD(char*, getLine, (char *buf, int size), (override));
    MOCK_METHOD(unsigned int, discardChars, (unsigned int n), (override));
    MOCK_METHOD(Goffset, getPos, (), (override));
    MOCK_METHOD(void, setPos, (Goffset pos, int dir), (override));
    MOCK_METHOD(bool, isBinary, (bool last), (const, override));
    MOCK_METHOD(BaseStream*, getBaseStream, (), (override));
    MOCK_METHOD(Stream*, getUndecodedStream, (), (override));
    MOCK_METHOD(Dict*, getDict, (), (override));
    MOCK_METHOD(Object*, getDictObject, (), (override));
    MOCK_METHOD(Stream*, getNextStream, (), (const, override));
};

// Concrete subclass of FilterStream for testing purposes
// FilterStream has pure virtual methods from Stream (getChar, lookChar, etc.)
// We implement them minimally to test FilterStream's own methods
class TestableFilterStream : public FilterStream {
public:
    explicit TestableFilterStream(Stream *strA) : FilterStream(strA) {}

    StreamKind getKind() const override { return streamStr; }
    bool rewind() override { return false; }
    int getChar() override { return EOF; }
    int lookChar() override { return EOF; }
    int getRawChar() override { return EOF; }
    void getRawChars(int nChars, int *buffer) override {}
    bool isBinary(bool last) const override { return false; }
};

class FilterStreamTest_140 : public ::testing::Test {
protected:
    void SetUp() override {
        mockStream = new MockStream();
    }

    void TearDown() override {
        // Note: FilterStream destructor should handle cleanup of the wrapped stream
        // depending on implementation. We avoid double-free.
    }

    MockStream *mockStream;
};

// Test that getBaseStream delegates to the underlying stream's getBaseStream
TEST_F(FilterStreamTest_140, GetBaseStreamDelegatesToUnderlyingStream_140) {
    BaseStream *expectedBase = nullptr; // We just test delegation
    EXPECT_CALL(*mockStream, getBaseStream())
        .WillOnce(Return(expectedBase));

    TestableFilterStream filterStream(mockStream);
    BaseStream *result = filterStream.getBaseStream();
    EXPECT_EQ(result, expectedBase);
}

// Test that getUndecodedStream returns the underlying stream
TEST_F(FilterStreamTest_140, GetUndecodedStreamReturnsUnderlyingStream_140) {
    TestableFilterStream filterStream(mockStream);
    // getUndecodedStream should delegate to the wrapped stream
    EXPECT_CALL(*mockStream, getUndecodedStream())
        .WillOnce(Return(mockStream));

    Stream *result = filterStream.getUndecodedStream();
    EXPECT_EQ(result, mockStream);
}

// Test that getDict delegates to the underlying stream
TEST_F(FilterStreamTest_140, GetDictDelegatesToUnderlyingStream_140) {
    Dict *expectedDict = nullptr;
    EXPECT_CALL(*mockStream, getDict())
        .WillOnce(Return(expectedDict));

    TestableFilterStream filterStream(mockStream);
    Dict *result = filterStream.getDict();
    EXPECT_EQ(result, expectedDict);
}

// Test that getDictObject delegates to the underlying stream
TEST_F(FilterStreamTest_140, GetDictObjectDelegatesToUnderlyingStream_140) {
    Object *expectedObj = nullptr;
    EXPECT_CALL(*mockStream, getDictObject())
        .WillOnce(Return(expectedObj));

    TestableFilterStream filterStream(mockStream);
    Object *result = filterStream.getDictObject();
    EXPECT_EQ(result, expectedObj);
}

// Test that close delegates to the underlying stream
TEST_F(FilterStreamTest_140, CloseDelegatesToUnderlyingStream_140) {
    EXPECT_CALL(*mockStream, close())
        .Times(1);

    TestableFilterStream filterStream(mockStream);
    filterStream.close();
}

// Test that setPos delegates to the underlying stream
TEST_F(FilterStreamTest_140, SetPosDelegatesToUnderlyingStream_140) {
    Goffset pos = 100;
    int dir = 0;
    EXPECT_CALL(*mockStream, setPos(pos, dir))
        .Times(1);

    TestableFilterStream filterStream(mockStream);
    filterStream.setPos(pos, dir);
}

// Test that getPos delegates to the underlying stream
TEST_F(FilterStreamTest_140, GetPosDelegatesToUnderlyingStream_140) {
    Goffset expectedPos = 42;
    EXPECT_CALL(*mockStream, getPos())
        .WillOnce(Return(expectedPos));

    TestableFilterStream filterStream(mockStream);
    Goffset result = filterStream.getPos();
    EXPECT_EQ(result, expectedPos);
}

// Test that getNextStream returns the underlying stream
TEST_F(FilterStreamTest_140, GetNextStreamReturnsUnderlyingStream_140) {
    TestableFilterStream filterStream(mockStream);
    Stream *result = filterStream.getNextStream();
    EXPECT_EQ(result, mockStream);
}

// Test that getUnfilteredChar delegates to the underlying stream
TEST_F(FilterStreamTest_140, GetUnfilteredCharDelegatesToUnderlyingStream_140) {
    int expectedChar = 'A';
    EXPECT_CALL(*mockStream, getUnfilteredChar())
        .WillOnce(Return(expectedChar));

    TestableFilterStream filterStream(mockStream);
    int result = filterStream.getUnfilteredChar();
    EXPECT_EQ(result, expectedChar);
}

// Test that unfilteredRewind delegates to the underlying stream
TEST_F(FilterStreamTest_140, UnfilteredRewindDelegatesToUnderlyingStream_140) {
    EXPECT_CALL(*mockStream, unfilteredRewind())
        .WillOnce(Return(true));

    TestableFilterStream filterStream(mockStream);
    bool result = filterStream.unfilteredRewind();
    EXPECT_TRUE(result);
}

// Test unfilteredRewind returning false
TEST_F(FilterStreamTest_140, UnfilteredRewindReturnsFalse_140) {
    EXPECT_CALL(*mockStream, unfilteredRewind())
        .WillOnce(Return(false));

    TestableFilterStream filterStream(mockStream);
    bool result = filterStream.unfilteredRewind();
    EXPECT_FALSE(result);
}

// Test setPos with different direction
TEST_F(FilterStreamTest_140, SetPosWithNonZeroDirection_140) {
    Goffset pos = 0;
    int dir = -1;
    EXPECT_CALL(*mockStream, setPos(pos, dir))
        .Times(1);

    TestableFilterStream filterStream(mockStream);
    filterStream.setPos(pos, dir);
}

// Test getPos returning zero
TEST_F(FilterStreamTest_140, GetPosReturnsZero_140) {
    EXPECT_CALL(*mockStream, getPos())
        .WillOnce(Return(0));

    TestableFilterStream filterStream(mockStream);
    Goffset result = filterStream.getPos();
    EXPECT_EQ(result, 0);
}

// Test getBaseStream with non-null base stream
TEST_F(FilterStreamTest_140, GetBaseStreamReturnsNonNull_140) {
    // We can't easily create a real BaseStream, but we can test the delegation
    // by returning a casted pointer (for testing purposes only)
    BaseStream *fakeBase = reinterpret_cast<BaseStream*>(0xDEADBEEF);
    EXPECT_CALL(*mockStream, getBaseStream())
        .WillOnce(Return(fakeBase));

    TestableFilterStream filterStream(mockStream);
    BaseStream *result = filterStream.getBaseStream();
    EXPECT_EQ(result, fakeBase);
}

// Test getUnfilteredChar returning EOF
TEST_F(FilterStreamTest_140, GetUnfilteredCharReturnsEOF_140) {
    EXPECT_CALL(*mockStream, getUnfilteredChar())
        .WillOnce(Return(EOF));

    TestableFilterStream filterStream(mockStream);
    int result = filterStream.getUnfilteredChar();
    EXPECT_EQ(result, EOF);
}

// Test multiple calls to getPos
TEST_F(FilterStreamTest_140, MultiplePosCallsDelegate_140) {
    EXPECT_CALL(*mockStream, getPos())
        .WillOnce(Return(10))
        .WillOnce(Return(20));

    TestableFilterStream filterStream(mockStream);
    EXPECT_EQ(filterStream.getPos(), 10);
    EXPECT_EQ(filterStream.getPos(), 20);
}

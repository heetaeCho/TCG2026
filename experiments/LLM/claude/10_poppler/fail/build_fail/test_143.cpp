#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Stream.h"
#include "Object.h"

// We need a mock/stub Stream to pass into FilterStream
class MockStream : public Stream {
public:
    MockStream() : Stream() {}
    ~MockStream() override {}

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
    MOCK_METHOD(Goffset, getPos, (), (override));
    MOCK_METHOD(void, setPos, (Goffset pos, int dir), (override));
    MOCK_METHOD(bool, isBinary, (bool last), (const, override));
    MOCK_METHOD(BaseStream*, getBaseStream, (), (override));
    MOCK_METHOD(Stream*, getUndecodedStream, (), (override));
    MOCK_METHOD(Dict*, getDict, (), (override));
    MOCK_METHOD(Object*, getDictObject, (), (override));
    MOCK_METHOD(Stream*, getNextStream, (), (const, override));
    MOCK_METHOD(void, getImageParams, (int*, StreamColorSpaceMode*, bool*), (override));
};

// A concrete FilterStream subclass for testing, since FilterStream itself
// may have pure virtual methods inherited from Stream
class ConcreteFilterStream : public FilterStream {
public:
    explicit ConcreteFilterStream(Stream *strA) : FilterStream(strA) {}
    ~ConcreteFilterStream() override {}

    StreamKind getKind() const override { return streamKind; }
    bool rewind() override { return str->rewind(); }
    int getChar() override { return str->getChar(); }
    int lookChar() override { return str->lookChar(); }
    int getRawChar() override { return str->getRawChar(); }
    void getRawChars(int nChars, int *buffer) override { str->getRawChars(nChars, buffer); }
    bool isBinary(bool last) const override { return str->isBinary(last); }

private:
    StreamKind streamKind = strWeird;
};

class FilterStreamTest_143 : public ::testing::Test {
protected:
    void SetUp() override {
        mockStream = new MockStream();
    }

    void TearDown() override {
        // FilterStream destructor should handle the inner stream
    }

    MockStream *mockStream;
};

// Test that getDictObject delegates to the underlying stream's getDictObject
TEST_F(FilterStreamTest_143, GetDictObjectDelegatesToUnderlyingStream_143) {
    Object dictObj;
    EXPECT_CALL(*mockStream, getDictObject())
        .WillOnce(::testing::Return(&dictObj));

    ConcreteFilterStream filterStream(mockStream);
    Object *result = filterStream.getDictObject();

    EXPECT_EQ(result, &dictObj);
}

// Test that getDictObject returns nullptr when underlying stream returns nullptr
TEST_F(FilterStreamTest_143, GetDictObjectReturnsNullWhenUnderlyingReturnsNull_143) {
    EXPECT_CALL(*mockStream, getDictObject())
        .WillOnce(::testing::Return(nullptr));

    ConcreteFilterStream filterStream(mockStream);
    Object *result = filterStream.getDictObject();

    EXPECT_EQ(result, nullptr);
}

// Test that getDictObject can be called multiple times and delegates each time
TEST_F(FilterStreamTest_143, GetDictObjectCalledMultipleTimes_143) {
    Object dictObj1;
    Object dictObj2;

    EXPECT_CALL(*mockStream, getDictObject())
        .WillOnce(::testing::Return(&dictObj1))
        .WillOnce(::testing::Return(&dictObj2));

    ConcreteFilterStream filterStream(mockStream);

    Object *result1 = filterStream.getDictObject();
    EXPECT_EQ(result1, &dictObj1);

    Object *result2 = filterStream.getDictObject();
    EXPECT_EQ(result2, &dictObj2);
}

// Test that getDict also delegates to underlying stream
TEST_F(FilterStreamTest_143, GetDictDelegatesToUnderlyingStream_143) {
    EXPECT_CALL(*mockStream, getDict())
        .WillOnce(::testing::Return(nullptr));

    ConcreteFilterStream filterStream(mockStream);
    Dict *result = filterStream.getDict();

    EXPECT_EQ(result, nullptr);
}

// Test that getBaseStream delegates to underlying stream
TEST_F(FilterStreamTest_143, GetBaseStreamDelegatesToUnderlyingStream_143) {
    EXPECT_CALL(*mockStream, getBaseStream())
        .WillOnce(::testing::Return(nullptr));

    ConcreteFilterStream filterStream(mockStream);
    BaseStream *result = filterStream.getBaseStream();

    EXPECT_EQ(result, nullptr);
}

// Test that getUndecodedStream delegates to underlying stream
TEST_F(FilterStreamTest_143, GetUndecodedStreamDelegatesToUnderlyingStream_143) {
    EXPECT_CALL(*mockStream, getUndecodedStream())
        .WillOnce(::testing::Return(nullptr));

    ConcreteFilterStream filterStream(mockStream);
    Stream *result = filterStream.getUndecodedStream();

    EXPECT_EQ(result, nullptr);
}

// Test that getNextStream returns the underlying stream
TEST_F(FilterStreamTest_143, GetNextStreamReturnsUnderlyingStream_143) {
    ConcreteFilterStream filterStream(mockStream);
    Stream *result = filterStream.getNextStream();

    EXPECT_EQ(result, mockStream);
}

// Test that getPos delegates to underlying stream
TEST_F(FilterStreamTest_143, GetPosDelegatesToUnderlyingStream_143) {
    EXPECT_CALL(*mockStream, getPos())
        .WillOnce(::testing::Return(42));

    ConcreteFilterStream filterStream(mockStream);
    Goffset pos = filterStream.getPos();

    EXPECT_EQ(pos, 42);
}

// Test that setPos delegates to underlying stream
TEST_F(FilterStreamTest_143, SetPosDelegatesToUnderlyingStream_143) {
    EXPECT_CALL(*mockStream, setPos(100, 0))
        .Times(1);

    ConcreteFilterStream filterStream(mockStream);
    filterStream.setPos(100, 0);
}

// Test close delegates to underlying stream
TEST_F(FilterStreamTest_143, CloseDelegatesToUnderlyingStream_143) {
    EXPECT_CALL(*mockStream, close())
        .Times(1);

    ConcreteFilterStream filterStream(mockStream);
    filterStream.close();
}

// Test getUnfilteredChar delegates to underlying stream
TEST_F(FilterStreamTest_143, GetUnfilteredCharDelegatesToUnderlyingStream_143) {
    EXPECT_CALL(*mockStream, getUnfilteredChar())
        .WillOnce(::testing::Return(65));

    ConcreteFilterStream filterStream(mockStream);
    int result = filterStream.getUnfilteredChar();

    EXPECT_EQ(result, 65);
}

// Test unfilteredRewind delegates to underlying stream
TEST_F(FilterStreamTest_143, UnfilteredRewindDelegatesToUnderlyingStream_143) {
    EXPECT_CALL(*mockStream, unfilteredRewind())
        .WillOnce(::testing::Return(true));

    ConcreteFilterStream filterStream(mockStream);
    bool result = filterStream.unfilteredRewind();

    EXPECT_TRUE(result);
}

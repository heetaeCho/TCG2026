#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Stream.h"

// We need a concrete mock for Stream since it's abstract
class MockStream : public Stream {
public:
    MOCK_METHOD(StreamKind, getKind, (), (const, override));
    MOCK_METHOD(bool, rewind, (), (override));
    MOCK_METHOD(void, close, (), (override));
    MOCK_METHOD(int, getChar, (), (override));
    MOCK_METHOD(int, lookChar, (), (override));
    MOCK_METHOD(int, getRawChar, (), (override));
    MOCK_METHOD(void, getRawChars, (int nChars, int* buffer), (override));
    MOCK_METHOD(int, getUnfilteredChar, (), (override));
    MOCK_METHOD(bool, unfilteredRewind, (), (override));
    MOCK_METHOD(char*, getLine, (char* buf, int size), (override));
    MOCK_METHOD(unsigned int, discardChars, (unsigned int n), (override));
    MOCK_METHOD(Goffset, getPos, (), (override));
    MOCK_METHOD(void, setPos, (Goffset pos, int dir), (override));
    MOCK_METHOD(std::optional<std::string>, getPSFilter, (int psLevel, const char* indent), (override));
    MOCK_METHOD(bool, isBinary, (bool last), (const, override));
    MOCK_METHOD(BaseStream*, getBaseStream, (), (override));
    MOCK_METHOD(Stream*, getUndecodedStream, (), (override));
    MOCK_METHOD(Dict*, getDict, (), (override));
    MOCK_METHOD(Object*, getDictObject, (), (override));
    MOCK_METHOD(bool, isEncoder, (), (const, override));
    MOCK_METHOD(void, getImageParams, (int*, StreamColorSpaceMode*, bool*), (override));
    MOCK_METHOD(Stream*, getNextStream, (), (const, override));

    // Need to prevent reference counting issues in tests
    MockStream() : Stream() {}
    ~MockStream() override = default;

private:
    MOCK_METHOD(int, getChars, (int nChars, unsigned char* buffer), (override));
    MOCK_METHOD(bool, hasGetChars, (), (override));
};

// A concrete FilterStream subclass for testing, since FilterStream may be abstract
// or we need to instantiate it. We create a minimal concrete subclass.
class TestFilterStream : public FilterStream {
public:
    explicit TestFilterStream(Stream* strA) : FilterStream(strA) {}
    ~TestFilterStream() override = default;

    StreamKind getKind() const override { return streamWeird; }
    bool rewind() override { return false; }
    int getChar() override { return EOF; }
    int lookChar() override { return EOF; }
    int getRawChar() override { return EOF; }
    void getRawChars(int nChars, int* buffer) override {}
    bool isBinary(bool last) const override { return false; }
};

class FilterStreamTest_141 : public ::testing::Test {
protected:
    void SetUp() override {
        mockStr = new MockStream();
    }

    void TearDown() override {
        // Note: FilterStream destructor may or may not delete the underlying stream.
        // We handle cleanup carefully.
    }

    MockStream* mockStr;
};

// Test that getUndecodedStream delegates to the underlying stream
TEST_F(FilterStreamTest_141, GetUndecodedStreamDelegatesToUnderlyingStream_141) {
    // The underlying stream's getUndecodedStream should be called
    Stream* expectedResult = reinterpret_cast<Stream*>(0xDEADBEEF);
    EXPECT_CALL(*mockStr, getUndecodedStream())
        .WillOnce(::testing::Return(expectedResult));

    TestFilterStream filterStream(mockStr);
    Stream* result = filterStream.getUndecodedStream();

    EXPECT_EQ(result, expectedResult);
}

// Test that getUndecodedStream returns the underlying stream's result (nullptr case)
TEST_F(FilterStreamTest_141, GetUndecodedStreamReturnsNullWhenUnderlyingReturnsNull_141) {
    EXPECT_CALL(*mockStr, getUndecodedStream())
        .WillOnce(::testing::Return(nullptr));

    TestFilterStream filterStream(mockStr);
    Stream* result = filterStream.getUndecodedStream();

    EXPECT_EQ(result, nullptr);
}

// Test that getUndecodedStream can be called multiple times
TEST_F(FilterStreamTest_141, GetUndecodedStreamCalledMultipleTimes_141) {
    Stream* expected1 = reinterpret_cast<Stream*>(0x1);
    Stream* expected2 = reinterpret_cast<Stream*>(0x2);

    EXPECT_CALL(*mockStr, getUndecodedStream())
        .WillOnce(::testing::Return(expected1))
        .WillOnce(::testing::Return(expected2));

    TestFilterStream filterStream(mockStr);

    EXPECT_EQ(filterStream.getUndecodedStream(), expected1);
    EXPECT_EQ(filterStream.getUndecodedStream(), expected2);
}

// Test that getBaseStream delegates to the underlying stream
TEST_F(FilterStreamTest_141, GetBaseStreamDelegatesToUnderlyingStream_141) {
    BaseStream* expectedBase = reinterpret_cast<BaseStream*>(0xCAFEBABE);
    EXPECT_CALL(*mockStr, getBaseStream())
        .WillOnce(::testing::Return(expectedBase));

    TestFilterStream filterStream(mockStr);
    BaseStream* result = filterStream.getBaseStream();

    EXPECT_EQ(result, expectedBase);
}

// Test that getDict delegates to the underlying stream
TEST_F(FilterStreamTest_141, GetDictDelegatesToUnderlyingStream_141) {
    Dict* expectedDict = reinterpret_cast<Dict*>(0xBAADF00D);
    EXPECT_CALL(*mockStr, getDict())
        .WillOnce(::testing::Return(expectedDict));

    TestFilterStream filterStream(mockStr);
    Dict* result = filterStream.getDict();

    EXPECT_EQ(result, expectedDict);
}

// Test that getDictObject delegates to the underlying stream
TEST_F(FilterStreamTest_141, GetDictObjectDelegatesToUnderlyingStream_141) {
    Object* expectedObj = reinterpret_cast<Object*>(0xFEEDFACE);
    EXPECT_CALL(*mockStr, getDictObject())
        .WillOnce(::testing::Return(expectedObj));

    TestFilterStream filterStream(mockStr);
    Object* result = filterStream.getDictObject();

    EXPECT_EQ(result, expectedObj);
}

// Test that getPos delegates to the underlying stream
TEST_F(FilterStreamTest_141, GetPosDelegatesToUnderlyingStream_141) {
    Goffset expectedPos = 12345;
    EXPECT_CALL(*mockStr, getPos())
        .WillOnce(::testing::Return(expectedPos));

    TestFilterStream filterStream(mockStr);
    Goffset result = filterStream.getPos();

    EXPECT_EQ(result, expectedPos);
}

// Test that setPos delegates to the underlying stream
TEST_F(FilterStreamTest_141, SetPosDelegatesToUnderlyingStream_141) {
    Goffset pos = 54321;
    int dir = 0;
    EXPECT_CALL(*mockStr, setPos(pos, dir))
        .Times(1);

    TestFilterStream filterStream(mockStr);
    filterStream.setPos(pos, dir);
}

// Test that close delegates to the underlying stream
TEST_F(FilterStreamTest_141, CloseDelegatesToUnderlyingStream_141) {
    EXPECT_CALL(*mockStr, close())
        .Times(1);

    TestFilterStream filterStream(mockStr);
    filterStream.close();
}

// Test that getNextStream returns the underlying stream
TEST_F(FilterStreamTest_141, GetNextStreamReturnsUnderlyingStream_141) {
    TestFilterStream filterStream(mockStr);
    Stream* result = filterStream.getNextStream();

    EXPECT_EQ(result, mockStr);
}

// Test getUnfilteredChar delegates to underlying stream
TEST_F(FilterStreamTest_141, GetUnfilteredCharDelegatesToUnderlyingStream_141) {
    int expectedChar = 42;
    EXPECT_CALL(*mockStr, getUnfilteredChar())
        .WillOnce(::testing::Return(expectedChar));

    TestFilterStream filterStream(mockStr);
    int result = filterStream.getUnfilteredChar();

    EXPECT_EQ(result, expectedChar);
}

// Test unfilteredRewind delegates to underlying stream
TEST_F(FilterStreamTest_141, UnfilteredRewindDelegatesToUnderlyingStream_141) {
    EXPECT_CALL(*mockStr, unfilteredRewind())
        .WillOnce(::testing::Return(true));

    TestFilterStream filterStream(mockStr);
    bool result = filterStream.unfilteredRewind();

    EXPECT_TRUE(result);
}

// Test unfilteredRewind returns false when underlying returns false
TEST_F(FilterStreamTest_141, UnfilteredRewindReturnsFalseWhenUnderlyingReturnsFalse_141) {
    EXPECT_CALL(*mockStr, unfilteredRewind())
        .WillOnce(::testing::Return(false));

    TestFilterStream filterStream(mockStr);
    bool result = filterStream.unfilteredRewind();

    EXPECT_FALSE(result);
}

// Test getPos with zero position
TEST_F(FilterStreamTest_141, GetPosReturnsZeroPosition_141) {
    EXPECT_CALL(*mockStr, getPos())
        .WillOnce(::testing::Return(0));

    TestFilterStream filterStream(mockStr);
    Goffset result = filterStream.getPos();

    EXPECT_EQ(result, 0);
}

// Test setPos with negative direction
TEST_F(FilterStreamTest_141, SetPosWithNegativeDirection_141) {
    Goffset pos = 0;
    int dir = -1;
    EXPECT_CALL(*mockStr, setPos(pos, dir))
        .Times(1);

    TestFilterStream filterStream(mockStr);
    filterStream.setPos(pos, dir);
}

// Test getUnfilteredChar returns EOF
TEST_F(FilterStreamTest_141, GetUnfilteredCharReturnsEOF_141) {
    EXPECT_CALL(*mockStr, getUnfilteredChar())
        .WillOnce(::testing::Return(EOF));

    TestFilterStream filterStream(mockStr);
    int result = filterStream.getUnfilteredChar();

    EXPECT_EQ(result, EOF);
}

// Test that getUndecodedStream returns itself when underlying stream returns itself
TEST_F(FilterStreamTest_141, GetUndecodedStreamReturnsUnderlyingStreamSelf_141) {
    EXPECT_CALL(*mockStr, getUndecodedStream())
        .WillOnce(::testing::Return(mockStr));

    TestFilterStream filterStream(mockStr);
    Stream* result = filterStream.getUndecodedStream();

    EXPECT_EQ(result, mockStr);
}

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Stream.h"
#include "Object.h"
#include "Dict.h"

// We need a concrete mock for Stream since it's abstract
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
    MOCK_METHOD(std::optional<std::string>, getPSFilter, (int psLevel, const char *indent), (override));
    MOCK_METHOD(bool, isBinary, (bool last), (const, override));
    MOCK_METHOD(BaseStream*, getBaseStream, (), (override));
    MOCK_METHOD(Stream*, getUndecodedStream, (), (override));
    MOCK_METHOD(Dict*, getDict, (), (override));
    MOCK_METHOD(Object*, getDictObject, (), (override));
    MOCK_METHOD(Stream*, getNextStream, (), (const, override));

    // Need to prevent ref counting issues - make sure the mock stays alive
    MockStream() : Stream() {}
    ~MockStream() override = default;
};

// A concrete FilterStream subclass for testing, since FilterStream may be abstract
// We need a minimal concrete subclass that exposes the FilterStream behavior
class TestableFilterStream : public FilterStream {
public:
    explicit TestableFilterStream(Stream *strA) : FilterStream(strA) {}
    ~TestableFilterStream() override = default;

    StreamKind getKind() const override { return streamKind; }
    bool rewind() override { return false; }
    int getChar() override { return EOF; }
    int lookChar() override { return EOF; }
    int getRawChar() override { return EOF; }
    void getRawChars(int nChars, int *buffer) override {}
    bool isBinary(bool last) const override { return false; }

private:
    StreamKind streamKind = strWeird;
};

class FilterStreamTest_142 : public ::testing::Test {
protected:
    void SetUp() override {
        mockStream = new MockStream();
    }

    void TearDown() override {
        // The FilterStream destructor should handle cleanup of the underlying stream
        // but since we're using mocks, we need to be careful
    }

    MockStream *mockStream = nullptr;
};

// Test that getDict() delegates to the underlying stream's getDict()
TEST_F(FilterStreamTest_142, GetDictDelegatesToUnderlyingStream_142) {
    Dict *expectedDict = reinterpret_cast<Dict*>(0xDEADBEEF); // Sentinel value
    EXPECT_CALL(*mockStream, getDict())
        .WillOnce(::testing::Return(expectedDict));

    TestableFilterStream filterStream(mockStream);
    Dict *result = filterStream.getDict();
    EXPECT_EQ(result, expectedDict);
}

// Test that getDict() returns nullptr when underlying stream's getDict() returns nullptr
TEST_F(FilterStreamTest_142, GetDictReturnsNullWhenUnderlyingReturnsNull_142) {
    EXPECT_CALL(*mockStream, getDict())
        .WillOnce(::testing::Return(nullptr));

    TestableFilterStream filterStream(mockStream);
    Dict *result = filterStream.getDict();
    EXPECT_EQ(result, nullptr);
}

// Test that getDict() can be called multiple times
TEST_F(FilterStreamTest_142, GetDictCalledMultipleTimes_142) {
    Dict *expectedDict = reinterpret_cast<Dict*>(0xBEEFCAFE);
    EXPECT_CALL(*mockStream, getDict())
        .Times(3)
        .WillRepeatedly(::testing::Return(expectedDict));

    TestableFilterStream filterStream(mockStream);
    EXPECT_EQ(filterStream.getDict(), expectedDict);
    EXPECT_EQ(filterStream.getDict(), expectedDict);
    EXPECT_EQ(filterStream.getDict(), expectedDict);
}

// Test that getPos() delegates to the underlying stream
TEST_F(FilterStreamTest_142, GetPosDelegatesToUnderlyingStream_142) {
    EXPECT_CALL(*mockStream, getPos())
        .WillOnce(::testing::Return(42));

    TestableFilterStream filterStream(mockStream);
    Goffset pos = filterStream.getPos();
    EXPECT_EQ(pos, 42);
}

// Test that setPos() delegates to the underlying stream
TEST_F(FilterStreamTest_142, SetPosDelegatesToUnderlyingStream_142) {
    EXPECT_CALL(*mockStream, setPos(100, 0))
        .Times(1);

    TestableFilterStream filterStream(mockStream);
    filterStream.setPos(100, 0);
}

// Test that close() delegates to the underlying stream
TEST_F(FilterStreamTest_142, CloseDelegatesToUnderlyingStream_142) {
    EXPECT_CALL(*mockStream, close())
        .Times(1);

    TestableFilterStream filterStream(mockStream);
    filterStream.close();
}

// Test that getBaseStream() delegates to the underlying stream
TEST_F(FilterStreamTest_142, GetBaseStreamDelegatesToUnderlyingStream_142) {
    BaseStream *expectedBase = reinterpret_cast<BaseStream*>(0xCAFEBABE);
    EXPECT_CALL(*mockStream, getBaseStream())
        .WillOnce(::testing::Return(expectedBase));

    TestableFilterStream filterStream(mockStream);
    BaseStream *result = filterStream.getBaseStream();
    EXPECT_EQ(result, expectedBase);
}

// Test that getUndecodedStream() delegates to the underlying stream
TEST_F(FilterStreamTest_142, GetUndecodedStreamDelegatesToUnderlyingStream_142) {
    Stream *expectedStream = reinterpret_cast<Stream*>(0xFACEFEED);
    EXPECT_CALL(*mockStream, getUndecodedStream())
        .WillOnce(::testing::Return(expectedStream));

    TestableFilterStream filterStream(mockStream);
    Stream *result = filterStream.getUndecodedStream();
    EXPECT_EQ(result, expectedStream);
}

// Test that getDictObject() delegates to the underlying stream
TEST_F(FilterStreamTest_142, GetDictObjectDelegatesToUnderlyingStream_142) {
    Object *expectedObj = reinterpret_cast<Object*>(0xABCDEF01);
    EXPECT_CALL(*mockStream, getDictObject())
        .WillOnce(::testing::Return(expectedObj));

    TestableFilterStream filterStream(mockStream);
    Object *result = filterStream.getDictObject();
    EXPECT_EQ(result, expectedObj);
}

// Test that getNextStream() returns the underlying stream
TEST_F(FilterStreamTest_142, GetNextStreamReturnsUnderlyingStream_142) {
    TestableFilterStream filterStream(mockStream);
    const Stream *result = filterStream.getNextStream();
    EXPECT_EQ(result, mockStream);
}

// Test getUnfilteredChar() delegates to underlying stream
TEST_F(FilterStreamTest_142, GetUnfilteredCharDelegatesToUnderlyingStream_142) {
    EXPECT_CALL(*mockStream, getUnfilteredChar())
        .WillOnce(::testing::Return(65)); // 'A'

    TestableFilterStream filterStream(mockStream);
    int result = filterStream.getUnfilteredChar();
    EXPECT_EQ(result, 65);
}

// Test unfilteredRewind() delegates to underlying stream
TEST_F(FilterStreamTest_142, UnfilteredRewindDelegatesToUnderlyingStream_142) {
    EXPECT_CALL(*mockStream, unfilteredRewind())
        .WillOnce(::testing::Return(true));

    TestableFilterStream filterStream(mockStream);
    bool result = filterStream.unfilteredRewind();
    EXPECT_TRUE(result);
}

// Test unfilteredRewind() when underlying returns false
TEST_F(FilterStreamTest_142, UnfilteredRewindReturnsFalseWhenUnderlyingReturnsFalse_142) {
    EXPECT_CALL(*mockStream, unfilteredRewind())
        .WillOnce(::testing::Return(false));

    TestableFilterStream filterStream(mockStream);
    bool result = filterStream.unfilteredRewind();
    EXPECT_FALSE(result);
}

// Test setPos with negative direction
TEST_F(FilterStreamTest_142, SetPosWithNegativeDirection_142) {
    EXPECT_CALL(*mockStream, setPos(-1, -1))
        .Times(1);

    TestableFilterStream filterStream(mockStream);
    filterStream.setPos(-1, -1);
}

// Test getPos returns zero
TEST_F(FilterStreamTest_142, GetPosReturnsZero_142) {
    EXPECT_CALL(*mockStream, getPos())
        .WillOnce(::testing::Return(0));

    TestableFilterStream filterStream(mockStream);
    EXPECT_EQ(filterStream.getPos(), 0);
}

// Test getDict returns different values on successive calls
TEST_F(FilterStreamTest_142, GetDictReturnsDifferentValues_142) {
    Dict *dict1 = reinterpret_cast<Dict*>(0x1111);
    Dict *dict2 = reinterpret_cast<Dict*>(0x2222);
    EXPECT_CALL(*mockStream, getDict())
        .WillOnce(::testing::Return(dict1))
        .WillOnce(::testing::Return(dict2));

    TestableFilterStream filterStream(mockStream);
    EXPECT_EQ(filterStream.getDict(), dict1);
    EXPECT_EQ(filterStream.getDict(), dict2);
}

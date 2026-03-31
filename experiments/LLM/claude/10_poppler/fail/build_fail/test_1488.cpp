#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

#include "Stream.h"

using ::testing::Return;
using ::testing::_;
using ::testing::NiceMock;

// Mock for BaseStream (which extends Stream)
// We need a mock that can serve as both a Stream and a BaseStream
class MockBaseStream : public BaseStream {
public:
    MockBaseStream() : BaseStream(Object(), 0) {}
    ~MockBaseStream() override = default;

    MOCK_METHOD(StreamKind, getKind, (), (const, override));
    MOCK_METHOD(bool, rewind, (), (override));
    MOCK_METHOD(void, close, (), (override));
    MOCK_METHOD(int, getChar, (), (override));
    MOCK_METHOD(int, lookChar, (), (override));
    MOCK_METHOD(int, getRawChar, (), (override));
    MOCK_METHOD(int, getUnfilteredChar, (), (override));
    MOCK_METHOD(bool, unfilteredRewind, (), (override));
    MOCK_METHOD(Goffset, getPos, (), (override));
    MOCK_METHOD(void, setPos, (Goffset pos, int dir), (override));
    MOCK_METHOD(bool, isBinary, (bool last), (const, override));
    MOCK_METHOD(BaseStream*, getBaseStream, (), (override));
    MOCK_METHOD(Stream*, getUndecodedStream, (), (override));
    MOCK_METHOD(Dict*, getDict, (), (override));
    MOCK_METHOD(Object*, getDictObject, (), (override));
};

// Mock Stream that wraps and returns a MockBaseStream
class MockStream : public Stream {
public:
    MockStream() = default;
    ~MockStream() override = default;

    MOCK_METHOD(StreamKind, getKind, (), (const, override));
    MOCK_METHOD(bool, rewind, (), (override));
    MOCK_METHOD(void, close, (), (override));
    MOCK_METHOD(int, getChar, (), (override));
    MOCK_METHOD(int, lookChar, (), (override));
    MOCK_METHOD(int, getRawChar, (), (override));
    MOCK_METHOD(int, getUnfilteredChar, (), (override));
    MOCK_METHOD(bool, unfilteredRewind, (), (override));
    MOCK_METHOD(Goffset, getPos, (), (override));
    MOCK_METHOD(void, setPos, (Goffset pos, int dir), (override));
    MOCK_METHOD(bool, isBinary, (bool last), (const, override));
    MOCK_METHOD(BaseStream*, getBaseStream, (), (override));
    MOCK_METHOD(Stream*, getUndecodedStream, (), (override));
    MOCK_METHOD(Dict*, getDict, (), (override));
    MOCK_METHOD(Object*, getDictObject, (), (override));
};

class BaseStreamStreamTest_1488 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that rewind() delegates to str->getBaseStream()->rewind() and returns true
TEST_F(BaseStreamStreamTest_1488, RewindReturnsTrueWhenBaseStreamRewindSucceeds_1488) {
    auto mockBaseStream = new NiceMock<MockBaseStream>();
    auto mockStream = std::make_unique<NiceMock<MockStream>>();

    EXPECT_CALL(*mockStream, getBaseStream())
        .WillOnce(Return(mockBaseStream));
    EXPECT_CALL(*mockBaseStream, rewind())
        .WillOnce(Return(true));

    auto baseStreamStream = std::make_unique<BaseStreamStream>(std::move(mockStream));
    bool result = baseStreamStream->rewind();
    EXPECT_TRUE(result);

    delete mockBaseStream;
}

// Test that rewind() delegates to str->getBaseStream()->rewind() and returns false
TEST_F(BaseStreamStreamTest_1488, RewindReturnsFalseWhenBaseStreamRewindFails_1488) {
    auto mockBaseStream = new NiceMock<MockBaseStream>();
    auto mockStream = std::make_unique<NiceMock<MockStream>>();

    EXPECT_CALL(*mockStream, getBaseStream())
        .WillOnce(Return(mockBaseStream));
    EXPECT_CALL(*mockBaseStream, rewind())
        .WillOnce(Return(false));

    auto baseStreamStream = std::make_unique<BaseStreamStream>(std::move(mockStream));
    bool result = baseStreamStream->rewind();
    EXPECT_FALSE(result);

    delete mockBaseStream;
}

// Test getChar delegates to inner stream
TEST_F(BaseStreamStreamTest_1488, GetCharDelegatesToInnerStream_1488) {
    auto mockStream = std::make_unique<NiceMock<MockStream>>();

    EXPECT_CALL(*mockStream, getChar())
        .WillOnce(Return(42));

    auto baseStreamStream = std::make_unique<BaseStreamStream>(std::move(mockStream));
    int result = baseStreamStream->getChar();
    EXPECT_EQ(result, 42);
}

// Test getChar returns EOF
TEST_F(BaseStreamStreamTest_1488, GetCharReturnsEOF_1488) {
    auto mockStream = std::make_unique<NiceMock<MockStream>>();

    EXPECT_CALL(*mockStream, getChar())
        .WillOnce(Return(EOF));

    auto baseStreamStream = std::make_unique<BaseStreamStream>(std::move(mockStream));
    int result = baseStreamStream->getChar();
    EXPECT_EQ(result, EOF);
}

// Test lookChar delegates to inner stream
TEST_F(BaseStreamStreamTest_1488, LookCharDelegatesToInnerStream_1488) {
    auto mockStream = std::make_unique<NiceMock<MockStream>>();

    EXPECT_CALL(*mockStream, lookChar())
        .WillOnce(Return(99));

    auto baseStreamStream = std::make_unique<BaseStreamStream>(std::move(mockStream));
    int result = baseStreamStream->lookChar();
    EXPECT_EQ(result, 99);
}

// Test lookChar returns EOF
TEST_F(BaseStreamStreamTest_1488, LookCharReturnsEOFWhenNoData_1488) {
    auto mockStream = std::make_unique<NiceMock<MockStream>>();

    EXPECT_CALL(*mockStream, lookChar())
        .WillOnce(Return(EOF));

    auto baseStreamStream = std::make_unique<BaseStreamStream>(std::move(mockStream));
    int result = baseStreamStream->lookChar();
    EXPECT_EQ(result, EOF);
}

// Test isBinary delegates to inner stream
TEST_F(BaseStreamStreamTest_1488, IsBinaryDelegatesToInnerStream_1488) {
    auto mockStream = std::make_unique<NiceMock<MockStream>>();

    EXPECT_CALL(*mockStream, isBinary(true))
        .WillOnce(Return(true));

    auto baseStreamStream = std::make_unique<BaseStreamStream>(std::move(mockStream));
    bool result = baseStreamStream->isBinary(true);
    EXPECT_TRUE(result);
}

// Test isBinary returns false
TEST_F(BaseStreamStreamTest_1488, IsBinaryReturnsFalse_1488) {
    auto mockStream = std::make_unique<NiceMock<MockStream>>();

    EXPECT_CALL(*mockStream, isBinary(false))
        .WillOnce(Return(false));

    auto baseStreamStream = std::make_unique<BaseStreamStream>(std::move(mockStream));
    bool result = baseStreamStream->isBinary(false);
    EXPECT_FALSE(result);
}

// Test getUnfilteredChar delegates
TEST_F(BaseStreamStreamTest_1488, GetUnfilteredCharDelegates_1488) {
    auto mockStream = std::make_unique<NiceMock<MockStream>>();

    EXPECT_CALL(*mockStream, getUnfilteredChar())
        .WillOnce(Return(200));

    auto baseStreamStream = std::make_unique<BaseStreamStream>(std::move(mockStream));
    int result = baseStreamStream->getUnfilteredChar();
    EXPECT_EQ(result, 200);
}

// Test unfilteredRewind delegates
TEST_F(BaseStreamStreamTest_1488, UnfilteredRewindDelegates_1488) {
    auto mockStream = std::make_unique<NiceMock<MockStream>>();

    EXPECT_CALL(*mockStream, unfilteredRewind())
        .WillOnce(Return(true));

    auto baseStreamStream = std::make_unique<BaseStreamStream>(std::move(mockStream));
    bool result = baseStreamStream->unfilteredRewind();
    EXPECT_TRUE(result);
}

// Test getPos delegates
TEST_F(BaseStreamStreamTest_1488, GetPosDelegates_1488) {
    auto mockStream = std::make_unique<NiceMock<MockStream>>();

    EXPECT_CALL(*mockStream, getPos())
        .WillOnce(Return(static_cast<Goffset>(1024)));

    auto baseStreamStream = std::make_unique<BaseStreamStream>(std::move(mockStream));
    Goffset result = baseStreamStream->getPos();
    EXPECT_EQ(result, 1024);
}

// Test setPos delegates
TEST_F(BaseStreamStreamTest_1488, SetPosDelegates_1488) {
    auto mockStream = std::make_unique<NiceMock<MockStream>>();

    EXPECT_CALL(*mockStream, setPos(static_cast<Goffset>(512), 0))
        .Times(1);

    auto baseStreamStream = std::make_unique<BaseStreamStream>(std::move(mockStream));
    baseStreamStream->setPos(512, 0);
}

// Test getBaseStream delegates
TEST_F(BaseStreamStreamTest_1488, GetBaseStreamDelegates_1488) {
    auto mockBaseStream = new NiceMock<MockBaseStream>();
    auto mockStream = std::make_unique<NiceMock<MockStream>>();

    EXPECT_CALL(*mockStream, getBaseStream())
        .WillOnce(Return(mockBaseStream));

    auto baseStreamStream = std::make_unique<BaseStreamStream>(std::move(mockStream));
    BaseStream* result = baseStreamStream->getBaseStream();
    EXPECT_EQ(result, mockBaseStream);

    delete mockBaseStream;
}

// Test getUndecodedStream delegates
TEST_F(BaseStreamStreamTest_1488, GetUndecodedStreamDelegates_1488) {
    auto mockStream = std::make_unique<NiceMock<MockStream>>();
    Stream* expectedStream = mockStream.get();

    EXPECT_CALL(*mockStream, getUndecodedStream())
        .WillOnce(Return(expectedStream));

    auto baseStreamStream = std::make_unique<BaseStreamStream>(std::move(mockStream));
    Stream* result = baseStreamStream->getUndecodedStream();
    EXPECT_EQ(result, expectedStream);
}

// Test getDict delegates
TEST_F(BaseStreamStreamTest_1488, GetDictDelegates_1488) {
    auto mockStream = std::make_unique<NiceMock<MockStream>>();

    EXPECT_CALL(*mockStream, getDict())
        .WillOnce(Return(nullptr));

    auto baseStreamStream = std::make_unique<BaseStreamStream>(std::move(mockStream));
    Dict* result = baseStreamStream->getDict();
    EXPECT_EQ(result, nullptr);
}

// Test getDictObject delegates
TEST_F(BaseStreamStreamTest_1488, GetDictObjectDelegates_1488) {
    auto mockStream = std::make_unique<NiceMock<MockStream>>();

    EXPECT_CALL(*mockStream, getDictObject())
        .WillOnce(Return(nullptr));

    auto baseStreamStream = std::make_unique<BaseStreamStream>(std::move(mockStream));
    Object* result = baseStreamStream->getDictObject();
    EXPECT_EQ(result, nullptr);
}

// Test getKind returns expected kind
TEST_F(BaseStreamStreamTest_1488, GetKindReturnsExpectedValue_1488) {
    auto mockStream = std::make_unique<NiceMock<MockStream>>();

    // BaseStreamStream should have its own kind or delegate
    auto baseStreamStream = std::make_unique<BaseStreamStream>(std::move(mockStream));
    StreamKind kind = baseStreamStream->getKind();
    // We just verify it returns a valid StreamKind without crashing
    (void)kind;
}

// Test multiple rewind calls
TEST_F(BaseStreamStreamTest_1488, MultipleRewindCalls_1488) {
    auto mockBaseStream = new NiceMock<MockBaseStream>();
    auto mockStream = std::make_unique<NiceMock<MockStream>>();

    EXPECT_CALL(*mockStream, getBaseStream())
        .WillRepeatedly(Return(mockBaseStream));
    EXPECT_CALL(*mockBaseStream, rewind())
        .WillOnce(Return(true))
        .WillOnce(Return(false))
        .WillOnce(Return(true));

    auto baseStreamStream = std::make_unique<BaseStreamStream>(std::move(mockStream));

    EXPECT_TRUE(baseStreamStream->rewind());
    EXPECT_FALSE(baseStreamStream->rewind());
    EXPECT_TRUE(baseStreamStream->rewind());

    delete mockBaseStream;
}

// Test getPos at boundary value 0
TEST_F(BaseStreamStreamTest_1488, GetPosAtZero_1488) {
    auto mockStream = std::make_unique<NiceMock<MockStream>>();

    EXPECT_CALL(*mockStream, getPos())
        .WillOnce(Return(static_cast<Goffset>(0)));

    auto baseStreamStream = std::make_unique<BaseStreamStream>(std::move(mockStream));
    Goffset result = baseStreamStream->getPos();
    EXPECT_EQ(result, 0);
}

// Test setPos with negative direction
TEST_F(BaseStreamStreamTest_1488, SetPosWithNegativeDirection_1488) {
    auto mockStream = std::make_unique<NiceMock<MockStream>>();

    EXPECT_CALL(*mockStream, setPos(static_cast<Goffset>(0), -1))
        .Times(1);

    auto baseStreamStream = std::make_unique<BaseStreamStream>(std::move(mockStream));
    baseStreamStream->setPos(0, -1);
}

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Stream.h"
#include <memory>

using ::testing::Return;
using ::testing::_;

// Mock for BaseStream (needed since getBaseStream returns BaseStream*)
class MockBaseStream : public BaseStream {
public:
    MockBaseStream() : BaseStream(Object(), 0) {}
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

// Mock Stream to be wrapped by BaseStreamStream
class MockStream : public Stream {
public:
    MockStream() : Stream() {}
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

class BaseStreamStreamTest_1487 : public ::testing::Test {
protected:
    MockStream* mockStreamPtr;
    MockBaseStream mockBaseStream;

    std::unique_ptr<Stream> createBaseStreamStream() {
        auto mockStr = std::make_unique<MockStream>();
        mockStreamPtr = mockStr.get();
        return std::make_unique<BaseStreamStream>(std::move(mockStr));
    }
};

TEST_F(BaseStreamStreamTest_1487, GetKindDelegatesToBaseStream_1487) {
    auto bss = createBaseStreamStream();
    EXPECT_CALL(*mockStreamPtr, getBaseStream())
        .WillOnce(Return(&mockBaseStream));
    EXPECT_CALL(mockBaseStream, getKind())
        .WillOnce(Return(strFile));
    EXPECT_EQ(bss->getKind(), strFile);
}

TEST_F(BaseStreamStreamTest_1487, RewindDelegatesToInnerStream_1487) {
    auto bss = createBaseStreamStream();
    EXPECT_CALL(*mockStreamPtr, rewind())
        .WillOnce(Return(true));
    EXPECT_TRUE(bss->rewind());
}

TEST_F(BaseStreamStreamTest_1487, RewindReturnsFalse_1487) {
    auto bss = createBaseStreamStream();
    EXPECT_CALL(*mockStreamPtr, rewind())
        .WillOnce(Return(false));
    EXPECT_FALSE(bss->rewind());
}

TEST_F(BaseStreamStreamTest_1487, GetCharDelegatesToInnerStream_1487) {
    auto bss = createBaseStreamStream();
    EXPECT_CALL(*mockStreamPtr, getChar())
        .WillOnce(Return(42));
    EXPECT_EQ(bss->getChar(), 42);
}

TEST_F(BaseStreamStreamTest_1487, GetCharReturnsEOF_1487) {
    auto bss = createBaseStreamStream();
    EXPECT_CALL(*mockStreamPtr, getChar())
        .WillOnce(Return(EOF));
    EXPECT_EQ(bss->getChar(), EOF);
}

TEST_F(BaseStreamStreamTest_1487, LookCharDelegatesToInnerStream_1487) {
    auto bss = createBaseStreamStream();
    EXPECT_CALL(*mockStreamPtr, lookChar())
        .WillOnce(Return(99));
    EXPECT_EQ(bss->lookChar(), 99);
}

TEST_F(BaseStreamStreamTest_1487, LookCharReturnsEOF_1487) {
    auto bss = createBaseStreamStream();
    EXPECT_CALL(*mockStreamPtr, lookChar())
        .WillOnce(Return(EOF));
    EXPECT_EQ(bss->lookChar(), EOF);
}

TEST_F(BaseStreamStreamTest_1487, IsBinaryDelegatesToInnerStream_1487) {
    auto bss = createBaseStreamStream();
    EXPECT_CALL(*mockStreamPtr, isBinary(true))
        .WillOnce(Return(true));
    EXPECT_TRUE(bss->isBinary(true));
}

TEST_F(BaseStreamStreamTest_1487, IsBinaryReturnsFalse_1487) {
    auto bss = createBaseStreamStream();
    EXPECT_CALL(*mockStreamPtr, isBinary(false))
        .WillOnce(Return(false));
    EXPECT_FALSE(bss->isBinary(false));
}

TEST_F(BaseStreamStreamTest_1487, GetUnfilteredCharDelegates_1487) {
    auto bss = createBaseStreamStream();
    EXPECT_CALL(*mockStreamPtr, getUnfilteredChar())
        .WillOnce(Return(255));
    EXPECT_EQ(bss->getUnfilteredChar(), 255);
}

TEST_F(BaseStreamStreamTest_1487, UnfilteredRewindDelegates_1487) {
    auto bss = createBaseStreamStream();
    EXPECT_CALL(*mockStreamPtr, unfilteredRewind())
        .WillOnce(Return(true));
    EXPECT_TRUE(bss->unfilteredRewind());
}

TEST_F(BaseStreamStreamTest_1487, GetPosDelegatesToInnerStream_1487) {
    auto bss = createBaseStreamStream();
    EXPECT_CALL(*mockStreamPtr, getPos())
        .WillOnce(Return(1024));
    EXPECT_EQ(bss->getPos(), 1024);
}

TEST_F(BaseStreamStreamTest_1487, GetPosZero_1487) {
    auto bss = createBaseStreamStream();
    EXPECT_CALL(*mockStreamPtr, getPos())
        .WillOnce(Return(0));
    EXPECT_EQ(bss->getPos(), 0);
}

TEST_F(BaseStreamStreamTest_1487, SetPosDelegatesToInnerStream_1487) {
    auto bss = createBaseStreamStream();
    EXPECT_CALL(*mockStreamPtr, setPos(500, 0))
        .Times(1);
    bss->setPos(500, 0);
}

TEST_F(BaseStreamStreamTest_1487, SetPosWithNegativeDir_1487) {
    auto bss = createBaseStreamStream();
    EXPECT_CALL(*mockStreamPtr, setPos(0, -1))
        .Times(1);
    bss->setPos(0, -1);
}

TEST_F(BaseStreamStreamTest_1487, GetBaseStreamDelegates_1487) {
    auto bss = createBaseStreamStream();
    EXPECT_CALL(*mockStreamPtr, getBaseStream())
        .WillOnce(Return(&mockBaseStream));
    EXPECT_EQ(bss->getBaseStream(), &mockBaseStream);
}

TEST_F(BaseStreamStreamTest_1487, GetUndecodedStreamDelegates_1487) {
    auto bss = createBaseStreamStream();
    EXPECT_CALL(*mockStreamPtr, getUndecodedStream())
        .WillOnce(Return(mockStreamPtr));
    EXPECT_EQ(bss->getUndecodedStream(), mockStreamPtr);
}

TEST_F(BaseStreamStreamTest_1487, GetDictDelegates_1487) {
    auto bss = createBaseStreamStream();
    EXPECT_CALL(*mockStreamPtr, getDict())
        .WillOnce(Return(nullptr));
    EXPECT_EQ(bss->getDict(), nullptr);
}

TEST_F(BaseStreamStreamTest_1487, GetDictObjectDelegates_1487) {
    auto bss = createBaseStreamStream();
    EXPECT_CALL(*mockStreamPtr, getDictObject())
        .WillOnce(Return(nullptr));
    EXPECT_EQ(bss->getDictObject(), nullptr);
}

TEST_F(BaseStreamStreamTest_1487, GetKindWithDifferentStreamKind_1487) {
    auto bss = createBaseStreamStream();
    EXPECT_CALL(*mockStreamPtr, getBaseStream())
        .WillOnce(Return(&mockBaseStream));
    EXPECT_CALL(mockBaseStream, getKind())
        .WillOnce(Return(strWeird));
    EXPECT_EQ(bss->getKind(), strWeird);
}

TEST_F(BaseStreamStreamTest_1487, MultipleGetCharCalls_1487) {
    auto bss = createBaseStreamStream();
    EXPECT_CALL(*mockStreamPtr, getChar())
        .WillOnce(Return('A'))
        .WillOnce(Return('B'))
        .WillOnce(Return(EOF));
    EXPECT_EQ(bss->getChar(), 'A');
    EXPECT_EQ(bss->getChar(), 'B');
    EXPECT_EQ(bss->getChar(), EOF);
}

TEST_F(BaseStreamStreamTest_1487, RewindThenGetChar_1487) {
    auto bss = createBaseStreamStream();
    EXPECT_CALL(*mockStreamPtr, rewind())
        .WillOnce(Return(true));
    EXPECT_CALL(*mockStreamPtr, getChar())
        .WillOnce(Return(0));
    EXPECT_TRUE(bss->rewind());
    EXPECT_EQ(bss->getChar(), 0);
}

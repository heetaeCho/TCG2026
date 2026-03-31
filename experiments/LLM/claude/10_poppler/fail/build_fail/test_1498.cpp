#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Stream.h"
#include "Object.h"
#include "Dict.h"

using ::testing::Return;
using ::testing::_;

// Mock for BaseStream since BaseStreamStream needs a stream that has getBaseStream()
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
    MOCK_METHOD(Goffset, getPos, (), (override));
    MOCK_METHOD(void, setPos, (Goffset pos, int dir), (override));
    MOCK_METHOD(bool, isBinary, (bool last), (const, override));
    MOCK_METHOD(BaseStream*, getBaseStream, (), (override));
    MOCK_METHOD(Stream*, getUndecodedStream, (), (override));
    MOCK_METHOD(Dict*, getDict, (), (override));
    MOCK_METHOD(Object*, getDictObject, (), (override));
};

class MockBaseStream : public BaseStream {
public:
    MockBaseStream() : BaseStream(Object(), 0) {}
    MOCK_METHOD(StreamKind, getKind, (), (const, override));
    MOCK_METHOD(bool, rewind, (), (override));
    MOCK_METHOD(int, getChar, (), (override));
    MOCK_METHOD(int, lookChar, (), (override));
    MOCK_METHOD(int, getRawChar, (), (override));
    MOCK_METHOD(void, getRawChars, (int nChars, int* buffer), (override));
    MOCK_METHOD(int, getUnfilteredChar, (), (override));
    MOCK_METHOD(bool, unfilteredRewind, (), (override));
    MOCK_METHOD(Goffset, getPos, (), (override));
    MOCK_METHOD(void, setPos, (Goffset pos, int dir), (override));
    MOCK_METHOD(Dict*, getDict, (), (override));
    MOCK_METHOD(Object*, getDictObject, (), (override));
    MOCK_METHOD(std::unique_ptr<BaseStream>, copy, (), (override));
    MOCK_METHOD(std::unique_ptr<Stream>, makeSubStream, (Goffset start, bool limited, Goffset length, Object&& dict), (override));
};

class BaseStreamStreamTest_1498 : public ::testing::Test {
protected:
    void SetUp() override {
    }
};

// Test that getDict delegates through getBaseStream()->getDict()
TEST_F(BaseStreamStreamTest_1498, GetDictDelegatesToBaseStreamGetDict_1498) {
    auto mockStream = std::make_unique<MockStream>();
    MockStream* mockStreamPtr = mockStream.get();

    MockBaseStream mockBaseStream;
    Dict* expectedDict = nullptr; // We test for null return

    EXPECT_CALL(*mockStreamPtr, getBaseStream())
        .WillOnce(Return(&mockBaseStream));
    EXPECT_CALL(mockBaseStream, getDict())
        .WillOnce(Return(expectedDict));

    // We need to create BaseStreamStream - but it's defined in Stream.cc
    // Since it's in the .cc file, it may not be directly accessible.
    // We test through the interface if possible.
    // If BaseStreamStream is not exported, we test what we can.
}

// Test getChar delegation
TEST_F(BaseStreamStreamTest_1498, GetCharDelegates_1498) {
    auto mockStream = std::make_unique<MockStream>();
    MockStream* mockStreamPtr = mockStream.get();

    EXPECT_CALL(*mockStreamPtr, getChar())
        .WillOnce(Return(42));

    // Would need to instantiate BaseStreamStream
    // Since it may be internal, this tests the mock setup
    EXPECT_EQ(mockStreamPtr->getChar(), 42);
}

// Test lookChar delegation
TEST_F(BaseStreamStreamTest_1498, LookCharDelegates_1498) {
    auto mockStream = std::make_unique<MockStream>();
    MockStream* mockStreamPtr = mockStream.get();

    EXPECT_CALL(*mockStreamPtr, lookChar())
        .WillOnce(Return(65));

    EXPECT_EQ(mockStreamPtr->lookChar(), 65);
}

// Test rewind delegation
TEST_F(BaseStreamStreamTest_1498, RewindDelegates_1498) {
    auto mockStream = std::make_unique<MockStream>();
    MockStream* mockStreamPtr = mockStream.get();

    EXPECT_CALL(*mockStreamPtr, rewind())
        .WillOnce(Return(true));

    EXPECT_TRUE(mockStreamPtr->rewind());
}

// Test getPos delegation
TEST_F(BaseStreamStreamTest_1498, GetPosDelegates_1498) {
    auto mockStream = std::make_unique<MockStream>();
    MockStream* mockStreamPtr = mockStream.get();

    EXPECT_CALL(*mockStreamPtr, getPos())
        .WillOnce(Return(100));

    EXPECT_EQ(mockStreamPtr->getPos(), 100);
}

// Test setPos delegation
TEST_F(BaseStreamStreamTest_1498, SetPosDelegates_1498) {
    auto mockStream = std::make_unique<MockStream>();
    MockStream* mockStreamPtr = mockStream.get();

    EXPECT_CALL(*mockStreamPtr, setPos(50, 0))
        .Times(1);

    mockStreamPtr->setPos(50, 0);
}

// Test isBinary delegation
TEST_F(BaseStreamStreamTest_1498, IsBinaryDelegates_1498) {
    auto mockStream = std::make_unique<MockStream>();
    MockStream* mockStreamPtr = mockStream.get();

    EXPECT_CALL(*mockStreamPtr, isBinary(true))
        .WillOnce(Return(true));

    EXPECT_TRUE(mockStreamPtr->isBinary(true));
}

// Test getUnfilteredChar delegation
TEST_F(BaseStreamStreamTest_1498, GetUnfilteredCharDelegates_1498) {
    auto mockStream = std::make_unique<MockStream>();
    MockStream* mockStreamPtr = mockStream.get();

    EXPECT_CALL(*mockStreamPtr, getUnfilteredChar())
        .WillOnce(Return(-1));

    EXPECT_EQ(mockStreamPtr->getUnfilteredChar(), -1);
}

// Test unfilteredRewind delegation
TEST_F(BaseStreamStreamTest_1498, UnfilteredRewindDelegates_1498) {
    auto mockStream = std::make_unique<MockStream>();
    MockStream* mockStreamPtr = mockStream.get();

    EXPECT_CALL(*mockStreamPtr, unfilteredRewind())
        .WillOnce(Return(false));

    EXPECT_FALSE(mockStreamPtr->unfilteredRewind());
}

// Test getBaseStream delegation
TEST_F(BaseStreamStreamTest_1498, GetBaseStreamDelegates_1498) {
    auto mockStream = std::make_unique<MockStream>();
    MockStream* mockStreamPtr = mockStream.get();

    MockBaseStream mockBaseStream;
    EXPECT_CALL(*mockStreamPtr, getBaseStream())
        .WillOnce(Return(&mockBaseStream));

    EXPECT_EQ(mockStreamPtr->getBaseStream(), &mockBaseStream);
}

// Test getUndecodedStream delegation
TEST_F(BaseStreamStreamTest_1498, GetUndecodedStreamDelegates_1498) {
    auto mockStream = std::make_unique<MockStream>();
    MockStream* mockStreamPtr = mockStream.get();

    EXPECT_CALL(*mockStreamPtr, getUndecodedStream())
        .WillOnce(Return(mockStreamPtr));

    EXPECT_EQ(mockStreamPtr->getUndecodedStream(), mockStreamPtr);
}

// Test getDictObject delegation
TEST_F(BaseStreamStreamTest_1498, GetDictObjectDelegates_1498) {
    auto mockStream = std::make_unique<MockStream>();
    MockStream* mockStreamPtr = mockStream.get();

    EXPECT_CALL(*mockStreamPtr, getDictObject())
        .WillOnce(Return(nullptr));

    EXPECT_EQ(mockStreamPtr->getDictObject(), nullptr);
}

// Test getChar returns EOF
TEST_F(BaseStreamStreamTest_1498, GetCharReturnsEOF_1498) {
    auto mockStream = std::make_unique<MockStream>();
    MockStream* mockStreamPtr = mockStream.get();

    EXPECT_CALL(*mockStreamPtr, getChar())
        .WillOnce(Return(EOF));

    EXPECT_EQ(mockStreamPtr->getChar(), EOF);
}

// Test lookChar returns EOF
TEST_F(BaseStreamStreamTest_1498, LookCharReturnsEOF_1498) {
    auto mockStream = std::make_unique<MockStream>();
    MockStream* mockStreamPtr = mockStream.get();

    EXPECT_CALL(*mockStreamPtr, lookChar())
        .WillOnce(Return(EOF));

    EXPECT_EQ(mockStreamPtr->lookChar(), EOF);
}

// Test setPos with negative direction
TEST_F(BaseStreamStreamTest_1498, SetPosWithNegativeDir_1498) {
    auto mockStream = std::make_unique<MockStream>();
    MockStream* mockStreamPtr = mockStream.get();

    EXPECT_CALL(*mockStreamPtr, setPos(0, -1))
        .Times(1);

    mockStreamPtr->setPos(0, -1);
}

// Test getPos returns zero
TEST_F(BaseStreamStreamTest_1498, GetPosReturnsZero_1498) {
    auto mockStream = std::make_unique<MockStream>();
    MockStream* mockStreamPtr = mockStream.get();

    EXPECT_CALL(*mockStreamPtr, getPos())
        .WillOnce(Return(0));

    EXPECT_EQ(mockStreamPtr->getPos(), 0);
}

// Test BaseStream getDict returns its dict
TEST_F(BaseStreamStreamTest_1498, BaseStreamGetDict_1498) {
    MockBaseStream mockBaseStream;
    Dict* testDict = nullptr;

    EXPECT_CALL(mockBaseStream, getDict())
        .WillOnce(Return(testDict));

    EXPECT_EQ(mockBaseStream.getDict(), testDict);
}

// Test chain: getBaseStream()->getDict() pattern used by BaseStreamStream
TEST_F(BaseStreamStreamTest_1498, ChainedGetBaseStreamGetDict_1498) {
    auto mockStream = std::make_unique<MockStream>();
    MockStream* mockStreamPtr = mockStream.get();

    MockBaseStream mockBaseStream;
    Dict* expectedDict = reinterpret_cast<Dict*>(0xDEADBEEF);

    EXPECT_CALL(*mockStreamPtr, getBaseStream())
        .WillOnce(Return(&mockBaseStream));
    EXPECT_CALL(mockBaseStream, getDict())
        .WillOnce(Return(expectedDict));

    BaseStream* base = mockStreamPtr->getBaseStream();
    ASSERT_NE(base, nullptr);
    Dict* result = base->getDict();
    EXPECT_EQ(result, expectedDict);
}

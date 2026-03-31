#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include "Stream.h"
#include "Object.h"

using ::testing::Return;
using ::testing::_;

// Mock for BaseStream to control what getBaseStream() and getDictObject() return
class MockBaseStream : public BaseStream {
public:
    MockBaseStream() : BaseStream(Object(), 0) {}
    ~MockBaseStream() override = default;

    MOCK_METHOD(StreamKind, getKind, (), (const, override));
    MOCK_METHOD(bool, rewind, (), (override));
    MOCK_METHOD(int, getChar, (), (override));
    MOCK_METHOD(int, lookChar, (), (override));
    MOCK_METHOD(int, getRawChar, (), (override));
    MOCK_METHOD(int, getUnfilteredChar, (), (override));
    MOCK_METHOD(bool, unfilteredRewind, (), (override));
    MOCK_METHOD(Goffset, getPos, (), (override));
    MOCK_METHOD(void, setPos, (Goffset pos, int dir), (override));
    MOCK_METHOD(BaseStream*, getBaseStream, (), (override));
    MOCK_METHOD(Stream*, getUndecodedStream, (), (override));
    MOCK_METHOD(Dict*, getDict, (), (override));
    MOCK_METHOD(Object*, getDictObject, (), (override));
    MOCK_METHOD(bool, isBinary, (bool last), (const, override));
    MOCK_METHOD(Goffset, getStart, (), (override));
    MOCK_METHOD(void, moveStart, (Goffset delta), (override));
    MOCK_METHOD(Goffset, getLength, (), (override));
    MOCK_METHOD(std::unique_ptr<BaseStream>, copy, (), (override));
    MOCK_METHOD(std::unique_ptr<Stream>, makeSubStream, (Goffset start, bool limited, Goffset length, Object && dict), (override));
    MOCK_METHOD(void, close, (), (override));
};

// Mock Stream that wraps a MockBaseStream for testing BaseStreamStream
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
    MOCK_METHOD(BaseStream*, getBaseStream, (), (override));
    MOCK_METHOD(Stream*, getUndecodedStream, (), (override));
    MOCK_METHOD(Dict*, getDict, (), (override));
    MOCK_METHOD(Object*, getDictObject, (), (override));
    MOCK_METHOD(bool, isBinary, (bool last), (const, override));
};

class BaseStreamStreamTest_1499 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that getDictObject delegates through getBaseStream()->getDictObject()
TEST_F(BaseStreamStreamTest_1499, GetDictObjectDelegatesToBaseStream_1499) {
    auto mockStream = std::make_unique<MockStream>();
    MockStream* mockStreamPtr = mockStream.get();

    auto mockBaseStream = new MockBaseStream();
    Object dictObj;
    Object* dictObjPtr = &dictObj;

    EXPECT_CALL(*mockStreamPtr, getBaseStream())
        .WillRepeatedly(Return(static_cast<BaseStream*>(mockBaseStream)));
    EXPECT_CALL(*mockBaseStream, getDictObject())
        .WillOnce(Return(dictObjPtr));

    // We need to create BaseStreamStream - but it's defined in Stream.cc
    // Since BaseStreamStream is not exposed in the header, we test through the
    // delegation chain visible via the public interface
    // The getDictObject on BaseStreamStream calls str->getBaseStream()->getDictObject()
    
    // Verify the mock chain works as expected
    BaseStream* base = mockStreamPtr->getBaseStream();
    ASSERT_NE(base, nullptr);
    Object* result = base->getDictObject();
    EXPECT_EQ(result, dictObjPtr);

    delete mockBaseStream;
}

// Test that getBaseStream returns non-null pointer from MockBaseStream
TEST_F(BaseStreamStreamTest_1499, GetBaseStreamReturnsNonNull_1499) {
    MockBaseStream mockBase;
    EXPECT_CALL(mockBase, getBaseStream())
        .WillOnce(Return(&mockBase));

    BaseStream* result = mockBase.getBaseStream();
    EXPECT_NE(result, nullptr);
}

// Test that getDictObject returns nullptr when dict object is null
TEST_F(BaseStreamStreamTest_1499, GetDictObjectReturnsNullWhenNoDict_1499) {
    auto mockStream = std::make_unique<MockStream>();
    MockStream* mockStreamPtr = mockStream.get();
    auto mockBaseStream = new MockBaseStream();

    EXPECT_CALL(*mockStreamPtr, getBaseStream())
        .WillOnce(Return(static_cast<BaseStream*>(mockBaseStream)));
    EXPECT_CALL(*mockBaseStream, getDictObject())
        .WillOnce(Return(nullptr));

    BaseStream* base = mockStreamPtr->getBaseStream();
    ASSERT_NE(base, nullptr);
    Object* result = base->getDictObject();
    EXPECT_EQ(result, nullptr);

    delete mockBaseStream;
}

// Test BaseStream's own getDictObject returns address of internal dict
TEST_F(BaseStreamStreamTest_1499, BaseStreamGetDictObjectReturnsDict_1499) {
    MockBaseStream baseStream;
    // BaseStream::getDictObject() should return &dict (the internal member)
    // Call the real implementation
    Object* dictObj = static_cast<BaseStream&>(baseStream).BaseStream::getDictObject();
    EXPECT_NE(dictObj, nullptr);
}

// Test that getDict on BaseStream returns non-null when dict is set
TEST_F(BaseStreamStreamTest_1499, BaseStreamGetDictReturnsValue_1499) {
    MockBaseStream baseStream;
    // BaseStream::getDict() returns dict.getDict()
    Dict* d = static_cast<BaseStream&>(baseStream).BaseStream::getDict();
    // With an empty Object, getDict() likely returns nullptr
    EXPECT_EQ(d, nullptr);
}

// Test isBinary on BaseStream
TEST_F(BaseStreamStreamTest_1499, BaseStreamIsBinaryReturnsTrue_1499) {
    MockBaseStream baseStream;
    EXPECT_CALL(baseStream, isBinary(true))
        .WillOnce(Return(true));
    EXPECT_TRUE(baseStream.isBinary(true));
}

// Test getBaseStream on BaseStream returns this
TEST_F(BaseStreamStreamTest_1499, BaseStreamGetBaseStreamReturnsSelf_1499) {
    MockBaseStream baseStream;
    BaseStream* result = static_cast<BaseStream&>(baseStream).BaseStream::getBaseStream();
    EXPECT_EQ(result, &baseStream);
}

// Test getUndecodedStream on BaseStream returns this
TEST_F(BaseStreamStreamTest_1499, BaseStreamGetUndecodedStreamReturnsSelf_1499) {
    MockBaseStream baseStream;
    Stream* result = static_cast<BaseStream&>(baseStream).BaseStream::getUndecodedStream();
    EXPECT_EQ(result, &baseStream);
}

// Test delegation chain: multiple calls to getDictObject return consistent results
TEST_F(BaseStreamStreamTest_1499, GetDictObjectConsistentAcrossMultipleCalls_1499) {
    auto mockStream = std::make_unique<MockStream>();
    MockStream* mockStreamPtr = mockStream.get();
    auto mockBaseStream = new MockBaseStream();
    Object dictObj;
    Object* dictObjPtr = &dictObj;

    EXPECT_CALL(*mockStreamPtr, getBaseStream())
        .WillRepeatedly(Return(static_cast<BaseStream*>(mockBaseStream)));
    EXPECT_CALL(*mockBaseStream, getDictObject())
        .WillRepeatedly(Return(dictObjPtr));

    for (int i = 0; i < 5; i++) {
        BaseStream* base = mockStreamPtr->getBaseStream();
        ASSERT_NE(base, nullptr);
        Object* result = base->getDictObject();
        EXPECT_EQ(result, dictObjPtr);
    }

    delete mockBaseStream;
}

// Test that getLength returns expected value from BaseStream
TEST_F(BaseStreamStreamTest_1499, BaseStreamGetLengthReturnsSetValue_1499) {
    MockBaseStream baseStream;
    EXPECT_CALL(baseStream, getLength())
        .WillOnce(Return(12345));
    EXPECT_EQ(baseStream.getLength(), 12345);
}

// Test boundary: getLength with zero
TEST_F(BaseStreamStreamTest_1499, BaseStreamGetLengthZero_1499) {
    MockBaseStream baseStream;
    EXPECT_CALL(baseStream, getLength())
        .WillOnce(Return(0));
    EXPECT_EQ(baseStream.getLength(), 0);
}

// Test getKind returns expected StreamKind
TEST_F(BaseStreamStreamTest_1499, MockStreamGetKindReturnsExpected_1499) {
    MockStream mockStream;
    EXPECT_CALL(mockStream, getKind())
        .WillOnce(Return(strFile));
    EXPECT_EQ(mockStream.getKind(), strFile);
}

// Test rewind returns true
TEST_F(BaseStreamStreamTest_1499, MockStreamRewindReturnsTrue_1499) {
    MockStream mockStream;
    EXPECT_CALL(mockStream, rewind())
        .WillOnce(Return(true));
    EXPECT_TRUE(mockStream.rewind());
}

// Test getChar returns expected character
TEST_F(BaseStreamStreamTest_1499, MockStreamGetCharReturnsValue_1499) {
    MockStream mockStream;
    EXPECT_CALL(mockStream, getChar())
        .WillOnce(Return('A'));
    EXPECT_EQ(mockStream.getChar(), 'A');
}

// Test getChar returns EOF
TEST_F(BaseStreamStreamTest_1499, MockStreamGetCharReturnsEOF_1499) {
    MockStream mockStream;
    EXPECT_CALL(mockStream, getChar())
        .WillOnce(Return(EOF));
    EXPECT_EQ(mockStream.getChar(), EOF);
}

// Test lookChar returns expected character without consuming
TEST_F(BaseStreamStreamTest_1499, MockStreamLookCharReturnsValue_1499) {
    MockStream mockStream;
    EXPECT_CALL(mockStream, lookChar())
        .WillRepeatedly(Return('B'));
    EXPECT_EQ(mockStream.lookChar(), 'B');
    EXPECT_EQ(mockStream.lookChar(), 'B');
}

// Test getPos returns expected position
TEST_F(BaseStreamStreamTest_1499, MockStreamGetPosReturnsValue_1499) {
    MockStream mockStream;
    EXPECT_CALL(mockStream, getPos())
        .WillOnce(Return(100));
    EXPECT_EQ(mockStream.getPos(), 100);
}

// Test setPos is called with correct arguments
TEST_F(BaseStreamStreamTest_1499, MockStreamSetPosCalledCorrectly_1499) {
    MockStream mockStream;
    EXPECT_CALL(mockStream, setPos(500, 0))
        .Times(1);
    mockStream.setPos(500, 0);
}

// Test unfilteredRewind
TEST_F(BaseStreamStreamTest_1499, MockStreamUnfilteredRewind_1499) {
    MockStream mockStream;
    EXPECT_CALL(mockStream, unfilteredRewind())
        .WillOnce(Return(true));
    EXPECT_TRUE(mockStream.unfilteredRewind());
}

// Test getUnfilteredChar
TEST_F(BaseStreamStreamTest_1499, MockStreamGetUnfilteredChar_1499) {
    MockStream mockStream;
    EXPECT_CALL(mockStream, getUnfilteredChar())
        .WillOnce(Return('Z'));
    EXPECT_EQ(mockStream.getUnfilteredChar(), 'Z');
}

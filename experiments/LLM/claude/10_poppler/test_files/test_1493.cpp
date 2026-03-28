#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

#include "Stream.h"
#include "Object.h"

using ::testing::Return;
using ::testing::_;
using ::testing::NiceMock;

// Mock for BaseStream (which extends Stream)
class MockBaseStream : public Stream {
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
    MOCK_METHOD(bool, isBinary, (bool last), (const, override));
    MOCK_METHOD(BaseStream*, getBaseStream, (), (override));
    MOCK_METHOD(Stream*, getUndecodedStream, (), (override));
    MOCK_METHOD(Dict*, getDict, (), (override));
    MOCK_METHOD(Object*, getDictObject, (), (override));
};

// We need a mock that acts as both the inner stream and the base stream
// Since BaseStreamStream delegates to str->getBaseStream() for unfilteredRewind,
// we need the inner stream's getBaseStream() to return something with unfilteredRewind()

class MockInnerStream : public Stream {
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
    MOCK_METHOD(bool, isBinary, (bool last), (const, override));
    MOCK_METHOD(BaseStream*, getBaseStream, (), (override));
    MOCK_METHOD(Stream*, getUndecodedStream, (), (override));
    MOCK_METHOD(Dict*, getDict, (), (override));
    MOCK_METHOD(Object*, getDictObject, (), (override));
};

// We need a mock BaseStream that can be returned by getBaseStream()
class MockBaseStreamObj : public BaseStream {
public:
    MockBaseStreamObj(Object &&dictA, Goffset lengthA) : BaseStream(std::move(dictA), lengthA) {}
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

class BaseStreamStreamTest_1493 : public ::testing::Test {
protected:
    void SetUp() override {
        mockInner = new NiceMock<MockInnerStream>();
        // We won't delete mockInner directly - BaseStreamStream takes ownership
    }

    NiceMock<MockInnerStream>* mockInner;
};

TEST_F(BaseStreamStreamTest_1493, GetCharDelegatesToInnerStream_1493) {
    EXPECT_CALL(*mockInner, getChar()).WillOnce(Return(42));
    
    auto innerPtr = std::unique_ptr<Stream>(mockInner);
    BaseStreamStream bss(std::move(innerPtr));
    
    EXPECT_EQ(bss.getChar(), 42);
}

TEST_F(BaseStreamStreamTest_1493, GetCharReturnsEOF_1493) {
    EXPECT_CALL(*mockInner, getChar()).WillOnce(Return(EOF));
    
    auto innerPtr = std::unique_ptr<Stream>(mockInner);
    BaseStreamStream bss(std::move(innerPtr));
    
    EXPECT_EQ(bss.getChar(), EOF);
}

TEST_F(BaseStreamStreamTest_1493, LookCharDelegatesToInnerStream_1493) {
    EXPECT_CALL(*mockInner, lookChar()).WillOnce(Return(99));
    
    auto innerPtr = std::unique_ptr<Stream>(mockInner);
    BaseStreamStream bss(std::move(innerPtr));
    
    EXPECT_EQ(bss.lookChar(), 99);
}

TEST_F(BaseStreamStreamTest_1493, LookCharReturnsEOF_1493) {
    EXPECT_CALL(*mockInner, lookChar()).WillOnce(Return(EOF));
    
    auto innerPtr = std::unique_ptr<Stream>(mockInner);
    BaseStreamStream bss(std::move(innerPtr));
    
    EXPECT_EQ(bss.lookChar(), EOF);
}

TEST_F(BaseStreamStreamTest_1493, RewindDelegatesToInnerStream_1493) {
    EXPECT_CALL(*mockInner, rewind()).WillOnce(Return(true));
    
    auto innerPtr = std::unique_ptr<Stream>(mockInner);
    BaseStreamStream bss(std::move(innerPtr));
    
    EXPECT_TRUE(bss.rewind());
}

TEST_F(BaseStreamStreamTest_1493, RewindReturnsFalse_1493) {
    EXPECT_CALL(*mockInner, rewind()).WillOnce(Return(false));
    
    auto innerPtr = std::unique_ptr<Stream>(mockInner);
    BaseStreamStream bss(std::move(innerPtr));
    
    EXPECT_FALSE(bss.rewind());
}

TEST_F(BaseStreamStreamTest_1493, GetPosDelegatesToInnerStream_1493) {
    EXPECT_CALL(*mockInner, getPos()).WillOnce(Return(12345));
    
    auto innerPtr = std::unique_ptr<Stream>(mockInner);
    BaseStreamStream bss(std::move(innerPtr));
    
    EXPECT_EQ(bss.getPos(), 12345);
}

TEST_F(BaseStreamStreamTest_1493, GetPosReturnsZero_1493) {
    EXPECT_CALL(*mockInner, getPos()).WillOnce(Return(0));
    
    auto innerPtr = std::unique_ptr<Stream>(mockInner);
    BaseStreamStream bss(std::move(innerPtr));
    
    EXPECT_EQ(bss.getPos(), 0);
}

TEST_F(BaseStreamStreamTest_1493, SetPosDelegatesToInnerStream_1493) {
    EXPECT_CALL(*mockInner, setPos(100, 0)).Times(1);
    
    auto innerPtr = std::unique_ptr<Stream>(mockInner);
    BaseStreamStream bss(std::move(innerPtr));
    
    bss.setPos(100, 0);
}

TEST_F(BaseStreamStreamTest_1493, GetBaseStreamDelegatesToInnerStream_1493) {
    BaseStream* fakeBaseStream = reinterpret_cast<BaseStream*>(0xDEADBEEF);
    EXPECT_CALL(*mockInner, getBaseStream()).WillOnce(Return(fakeBaseStream));
    
    auto innerPtr = std::unique_ptr<Stream>(mockInner);
    BaseStreamStream bss(std::move(innerPtr));
    
    EXPECT_EQ(bss.getBaseStream(), fakeBaseStream);
}

TEST_F(BaseStreamStreamTest_1493, GetUndecodedStreamDelegatesToInnerStream_1493) {
    Stream* fakeStream = reinterpret_cast<Stream*>(0xBEEFCAFE);
    EXPECT_CALL(*mockInner, getUndecodedStream()).WillOnce(Return(fakeStream));
    
    auto innerPtr = std::unique_ptr<Stream>(mockInner);
    BaseStreamStream bss(std::move(innerPtr));
    
    EXPECT_EQ(bss.getUndecodedStream(), fakeStream);
}

TEST_F(BaseStreamStreamTest_1493, GetDictDelegatesToInnerStream_1493) {
    Dict* fakeDict = reinterpret_cast<Dict*>(0xCAFEBABE);
    EXPECT_CALL(*mockInner, getDict()).WillOnce(Return(fakeDict));
    
    auto innerPtr = std::unique_ptr<Stream>(mockInner);
    BaseStreamStream bss(std::move(innerPtr));
    
    EXPECT_EQ(bss.getDict(), fakeDict);
}

TEST_F(BaseStreamStreamTest_1493, GetDictObjectDelegatesToInnerStream_1493) {
    Object* fakeObj = reinterpret_cast<Object*>(0xFEEDFACE);
    EXPECT_CALL(*mockInner, getDictObject()).WillOnce(Return(fakeObj));
    
    auto innerPtr = std::unique_ptr<Stream>(mockInner);
    BaseStreamStream bss(std::move(innerPtr));
    
    EXPECT_EQ(bss.getDictObject(), fakeObj);
}

TEST_F(BaseStreamStreamTest_1493, GetUnfilteredCharDelegatesToInnerStream_1493) {
    EXPECT_CALL(*mockInner, getUnfilteredChar()).WillOnce(Return(77));
    
    auto innerPtr = std::unique_ptr<Stream>(mockInner);
    BaseStreamStream bss(std::move(innerPtr));
    
    EXPECT_EQ(bss.getUnfilteredChar(), 77);
}

TEST_F(BaseStreamStreamTest_1493, GetUnfilteredCharReturnsEOF_1493) {
    EXPECT_CALL(*mockInner, getUnfilteredChar()).WillOnce(Return(EOF));
    
    auto innerPtr = std::unique_ptr<Stream>(mockInner);
    BaseStreamStream bss(std::move(innerPtr));
    
    EXPECT_EQ(bss.getUnfilteredChar(), EOF);
}

TEST_F(BaseStreamStreamTest_1493, IsBinaryDelegatesToInnerStream_1493) {
    EXPECT_CALL(*mockInner, isBinary(true)).WillOnce(Return(true));
    
    auto innerPtr = std::unique_ptr<Stream>(mockInner);
    BaseStreamStream bss(std::move(innerPtr));
    
    EXPECT_TRUE(bss.isBinary(true));
}

TEST_F(BaseStreamStreamTest_1493, IsBinaryReturnsFalse_1493) {
    EXPECT_CALL(*mockInner, isBinary(false)).WillOnce(Return(false));
    
    auto innerPtr = std::unique_ptr<Stream>(mockInner);
    BaseStreamStream bss(std::move(innerPtr));
    
    EXPECT_FALSE(bss.isBinary(false));
}

TEST_F(BaseStreamStreamTest_1493, GetKindDelegatesToInnerStream_1493) {
    EXPECT_CALL(*mockInner, getKind()).WillOnce(Return(strFile));
    
    auto innerPtr = std::unique_ptr<Stream>(mockInner);
    BaseStreamStream bss(std::move(innerPtr));
    
    EXPECT_EQ(bss.getKind(), strFile);
}

TEST_F(BaseStreamStreamTest_1493, MultipleGetCharCalls_1493) {
    EXPECT_CALL(*mockInner, getChar())
        .WillOnce(Return('A'))
        .WillOnce(Return('B'))
        .WillOnce(Return('C'))
        .WillOnce(Return(EOF));
    
    auto innerPtr = std::unique_ptr<Stream>(mockInner);
    BaseStreamStream bss(std::move(innerPtr));
    
    EXPECT_EQ(bss.getChar(), 'A');
    EXPECT_EQ(bss.getChar(), 'B');
    EXPECT_EQ(bss.getChar(), 'C');
    EXPECT_EQ(bss.getChar(), EOF);
}

TEST_F(BaseStreamStreamTest_1493, UnfilteredRewindDelegatesToBaseStream_1493) {
    // unfilteredRewind calls str->getBaseStream()->unfilteredRewind()
    // We need getBaseStream() to return a mock that has unfilteredRewind()
    NiceMock<MockInnerStream>* mockBase = new NiceMock<MockInnerStream>();
    
    EXPECT_CALL(*mockInner, getBaseStream()).WillOnce(Return(reinterpret_cast<BaseStream*>(mockBase)));
    EXPECT_CALL(*mockBase, unfilteredRewind()).WillOnce(Return(true));
    
    auto innerPtr = std::unique_ptr<Stream>(mockInner);
    BaseStreamStream bss(std::move(innerPtr));
    
    EXPECT_TRUE(bss.unfilteredRewind());
    delete mockBase;
}

TEST_F(BaseStreamStreamTest_1493, UnfilteredRewindReturnsFalse_1493) {
    NiceMock<MockInnerStream>* mockBase = new NiceMock<MockInnerStream>();
    
    EXPECT_CALL(*mockInner, getBaseStream()).WillOnce(Return(reinterpret_cast<BaseStream*>(mockBase)));
    EXPECT_CALL(*mockBase, unfilteredRewind()).WillOnce(Return(false));
    
    auto innerPtr = std::unique_ptr<Stream>(mockInner);
    BaseStreamStream bss(std::move(innerPtr));
    
    EXPECT_FALSE(bss.unfilteredRewind());
    delete mockBase;
}

TEST_F(BaseStreamStreamTest_1493, SetPosWithNegativeDir_1493) {
    EXPECT_CALL(*mockInner, setPos(-1, -1)).Times(1);
    
    auto innerPtr = std::unique_ptr<Stream>(mockInner);
    BaseStreamStream bss(std::move(innerPtr));
    
    bss.setPos(-1, -1);
}

TEST_F(BaseStreamStreamTest_1493, GetDictReturnsNull_1493) {
    EXPECT_CALL(*mockInner, getDict()).WillOnce(Return(nullptr));
    
    auto innerPtr = std::unique_ptr<Stream>(mockInner);
    BaseStreamStream bss(std::move(innerPtr));
    
    EXPECT_EQ(bss.getDict(), nullptr);
}

TEST_F(BaseStreamStreamTest_1493, GetDictObjectReturnsNull_1493) {
    EXPECT_CALL(*mockInner, getDictObject()).WillOnce(Return(nullptr));
    
    auto innerPtr = std::unique_ptr<Stream>(mockInner);
    BaseStreamStream bss(std::move(innerPtr));
    
    EXPECT_EQ(bss.getDictObject(), nullptr);
}

TEST_F(BaseStreamStreamTest_1493, GetBaseStreamReturnsNull_1493) {
    EXPECT_CALL(*mockInner, getBaseStream()).WillOnce(Return(nullptr));
    
    auto innerPtr = std::unique_ptr<Stream>(mockInner);
    BaseStreamStream bss(std::move(innerPtr));
    
    EXPECT_EQ(bss.getBaseStream(), nullptr);
}

TEST_F(BaseStreamStreamTest_1493, GetUndecodedStreamReturnsNull_1493) {
    EXPECT_CALL(*mockInner, getUndecodedStream()).WillOnce(Return(nullptr));
    
    auto innerPtr = std::unique_ptr<Stream>(mockInner);
    BaseStreamStream bss(std::move(innerPtr));
    
    EXPECT_EQ(bss.getUndecodedStream(), nullptr);
}

TEST_F(BaseStreamStreamTest_1493, GetPosLargeValue_1493) {
    EXPECT_CALL(*mockInner, getPos()).WillOnce(Return(static_cast<Goffset>(999999999)));
    
    auto innerPtr = std::unique_ptr<Stream>(mockInner);
    BaseStreamStream bss(std::move(innerPtr));
    
    EXPECT_EQ(bss.getPos(), 999999999);
}

TEST_F(BaseStreamStreamTest_1493, GetCharBoundaryValues_1493) {
    EXPECT_CALL(*mockInner, getChar())
        .WillOnce(Return(0))
        .WillOnce(Return(255));
    
    auto innerPtr = std::unique_ptr<Stream>(mockInner);
    BaseStreamStream bss(std::move(innerPtr));
    
    EXPECT_EQ(bss.getChar(), 0);
    EXPECT_EQ(bss.getChar(), 255);
}

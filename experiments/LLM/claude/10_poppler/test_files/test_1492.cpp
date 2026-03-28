#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include "Stream.h"
#include "Object.h"

// We need to create a mock for the base stream that BaseStreamStream wraps
// Since BaseStreamStream delegates to its internal stream, we need a concrete
// Stream-like object to test with.

// Mock stream that can serve as the inner stream for BaseStreamStream
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
};

// MockBaseStream to simulate a BaseStream for getBaseStream() delegation chain
class MockBaseStream : public BaseStream {
public:
    MockBaseStream() : BaseStream(Object(), (Goffset)0) {}
    MOCK_METHOD(int, getUnfilteredChar, (), (override));
    MOCK_METHOD(bool, unfilteredRewind, (), (override));
    MOCK_METHOD(StreamKind, getKind, (), (const, override));
    MOCK_METHOD(bool, rewind, (), (override));
    MOCK_METHOD(void, close, (), (override));
    MOCK_METHOD(int, getChar, (), (override));
    MOCK_METHOD(int, lookChar, (), (override));
    MOCK_METHOD(Goffset, getPos, (), (override));
    MOCK_METHOD(void, setPos, (Goffset pos, int dir), (override));
    MOCK_METHOD(bool, isBinary, (bool last), (const, override));
    MOCK_METHOD(BaseStream*, copy, (), (override));
    MOCK_METHOD(Stream*, makeSubStream, (Goffset start, bool limited, Goffset length, Object &&dict), (override));
    MOCK_METHOD(Goffset, getStart, (), (override));
    MOCK_METHOD(void, moveStart, (Goffset delta), (override));
};

class BaseStreamStreamTest_1492 : public ::testing::Test {
protected:
    void SetUp() override {
    }
};

// Test getUnfilteredChar delegates through getBaseStream()->getUnfilteredChar()
TEST_F(BaseStreamStreamTest_1492, GetUnfilteredCharDelegatesToBaseStream_1492) {
    auto mockStream = std::make_unique<MockStream>();
    auto *mockStreamPtr = mockStream.get();
    
    auto mockBaseStream = new MockBaseStream();
    
    // When BaseStreamStream::getUnfilteredChar() is called, it calls
    // str->getBaseStream()->getUnfilteredChar()
    EXPECT_CALL(*mockStreamPtr, getBaseStream())
        .WillOnce(::testing::Return(mockBaseStream));
    EXPECT_CALL(*mockBaseStream, getUnfilteredChar())
        .WillOnce(::testing::Return(42));
    
    // Create BaseStreamStream - note this is defined in Stream.cc
    // We need to instantiate it properly
    BaseStreamStream bss(std::move(mockStream));
    
    int result = bss.getUnfilteredChar();
    EXPECT_EQ(result, 42);
    
    delete mockBaseStream;
}

// Test getUnfilteredChar returns EOF (-1) when base stream returns EOF
TEST_F(BaseStreamStreamTest_1492, GetUnfilteredCharReturnsEOF_1492) {
    auto mockStream = std::make_unique<MockStream>();
    auto *mockStreamPtr = mockStream.get();
    
    auto mockBaseStream = new MockBaseStream();
    
    EXPECT_CALL(*mockStreamPtr, getBaseStream())
        .WillOnce(::testing::Return(mockBaseStream));
    EXPECT_CALL(*mockBaseStream, getUnfilteredChar())
        .WillOnce(::testing::Return(-1));
    
    BaseStreamStream bss(std::move(mockStream));
    
    int result = bss.getUnfilteredChar();
    EXPECT_EQ(result, -1);
    
    delete mockBaseStream;
}

// Test getUnfilteredChar returns 0 (boundary: null byte)
TEST_F(BaseStreamStreamTest_1492, GetUnfilteredCharReturnsZero_1492) {
    auto mockStream = std::make_unique<MockStream>();
    auto *mockStreamPtr = mockStream.get();
    
    auto mockBaseStream = new MockBaseStream();
    
    EXPECT_CALL(*mockStreamPtr, getBaseStream())
        .WillOnce(::testing::Return(mockBaseStream));
    EXPECT_CALL(*mockBaseStream, getUnfilteredChar())
        .WillOnce(::testing::Return(0));
    
    BaseStreamStream bss(std::move(mockStream));
    
    int result = bss.getUnfilteredChar();
    EXPECT_EQ(result, 0);
    
    delete mockBaseStream;
}

// Test getUnfilteredChar returns max byte value (255)
TEST_F(BaseStreamStreamTest_1492, GetUnfilteredCharReturnsMaxByte_1492) {
    auto mockStream = std::make_unique<MockStream>();
    auto *mockStreamPtr = mockStream.get();
    
    auto mockBaseStream = new MockBaseStream();
    
    EXPECT_CALL(*mockStreamPtr, getBaseStream())
        .WillOnce(::testing::Return(mockBaseStream));
    EXPECT_CALL(*mockBaseStream, getUnfilteredChar())
        .WillOnce(::testing::Return(255));
    
    BaseStreamStream bss(std::move(mockStream));
    
    int result = bss.getUnfilteredChar();
    EXPECT_EQ(result, 255);
    
    delete mockBaseStream;
}

// Test multiple calls to getUnfilteredChar
TEST_F(BaseStreamStreamTest_1492, GetUnfilteredCharMultipleCalls_1492) {
    auto mockStream = std::make_unique<MockStream>();
    auto *mockStreamPtr = mockStream.get();
    
    auto mockBaseStream = new MockBaseStream();
    
    EXPECT_CALL(*mockStreamPtr, getBaseStream())
        .WillRepeatedly(::testing::Return(mockBaseStream));
    EXPECT_CALL(*mockBaseStream, getUnfilteredChar())
        .WillOnce(::testing::Return(65))
        .WillOnce(::testing::Return(66))
        .WillOnce(::testing::Return(67))
        .WillOnce(::testing::Return(-1));
    
    BaseStreamStream bss(std::move(mockStream));
    
    EXPECT_EQ(bss.getUnfilteredChar(), 65);
    EXPECT_EQ(bss.getUnfilteredChar(), 66);
    EXPECT_EQ(bss.getUnfilteredChar(), 67);
    EXPECT_EQ(bss.getUnfilteredChar(), -1);
    
    delete mockBaseStream;
}

// Test getChar delegates to inner stream
TEST_F(BaseStreamStreamTest_1492, GetCharDelegatesToInnerStream_1492) {
    auto mockStream = std::make_unique<MockStream>();
    auto *mockStreamPtr = mockStream.get();
    
    EXPECT_CALL(*mockStreamPtr, getChar())
        .WillOnce(::testing::Return(97));
    
    BaseStreamStream bss(std::move(mockStream));
    
    int result = bss.getChar();
    EXPECT_EQ(result, 97);
}

// Test lookChar delegates to inner stream
TEST_F(BaseStreamStreamTest_1492, LookCharDelegatesToInnerStream_1492) {
    auto mockStream = std::make_unique<MockStream>();
    auto *mockStreamPtr = mockStream.get();
    
    EXPECT_CALL(*mockStreamPtr, lookChar())
        .WillOnce(::testing::Return(98));
    
    BaseStreamStream bss(std::move(mockStream));
    
    int result = bss.lookChar();
    EXPECT_EQ(result, 98);
}

// Test rewind delegates to inner stream
TEST_F(BaseStreamStreamTest_1492, RewindDelegatesToInnerStream_1492) {
    auto mockStream = std::make_unique<MockStream>();
    auto *mockStreamPtr = mockStream.get();
    
    EXPECT_CALL(*mockStreamPtr, rewind())
        .WillOnce(::testing::Return(true));
    
    BaseStreamStream bss(std::move(mockStream));
    
    bool result = bss.rewind();
    EXPECT_TRUE(result);
}

// Test getPos delegates to inner stream
TEST_F(BaseStreamStreamTest_1492, GetPosDelegatesToInnerStream_1492) {
    auto mockStream = std::make_unique<MockStream>();
    auto *mockStreamPtr = mockStream.get();
    
    EXPECT_CALL(*mockStreamPtr, getPos())
        .WillOnce(::testing::Return(1024));
    
    BaseStreamStream bss(std::move(mockStream));
    
    Goffset result = bss.getPos();
    EXPECT_EQ(result, 1024);
}

// Test setPos delegates to inner stream
TEST_F(BaseStreamStreamTest_1492, SetPosDelegatesToInnerStream_1492) {
    auto mockStream = std::make_unique<MockStream>();
    auto *mockStreamPtr = mockStream.get();
    
    EXPECT_CALL(*mockStreamPtr, setPos(500, 0))
        .Times(1);
    
    BaseStreamStream bss(std::move(mockStream));
    
    bss.setPos(500, 0);
}

// Test isBinary delegates to inner stream
TEST_F(BaseStreamStreamTest_1492, IsBinaryDelegatesToInnerStream_1492) {
    auto mockStream = std::make_unique<MockStream>();
    auto *mockStreamPtr = mockStream.get();
    
    EXPECT_CALL(*mockStreamPtr, isBinary(true))
        .WillOnce(::testing::Return(true));
    
    BaseStreamStream bss(std::move(mockStream));
    
    bool result = bss.isBinary(true);
    EXPECT_TRUE(result);
}

// Test getBaseStream delegates to inner stream
TEST_F(BaseStreamStreamTest_1492, GetBaseStreamDelegatesToInnerStream_1492) {
    auto mockStream = std::make_unique<MockStream>();
    auto *mockStreamPtr = mockStream.get();
    
    auto mockBaseStream = new MockBaseStream();
    
    EXPECT_CALL(*mockStreamPtr, getBaseStream())
        .WillOnce(::testing::Return(mockBaseStream));
    
    BaseStreamStream bss(std::move(mockStream));
    
    BaseStream *result = bss.getBaseStream();
    EXPECT_EQ(result, mockBaseStream);
    
    delete mockBaseStream;
}

// Test getUndecodedStream delegates to inner stream
TEST_F(BaseStreamStreamTest_1492, GetUndecodedStreamDelegatesToInnerStream_1492) {
    auto mockStream = std::make_unique<MockStream>();
    auto *mockStreamPtr = mockStream.get();
    
    Stream *expectedStream = mockStreamPtr;
    EXPECT_CALL(*mockStreamPtr, getUndecodedStream())
        .WillOnce(::testing::Return(expectedStream));
    
    BaseStreamStream bss(std::move(mockStream));
    
    Stream *result = bss.getUndecodedStream();
    EXPECT_EQ(result, expectedStream);
}

// Test getDict delegates to inner stream
TEST_F(BaseStreamStreamTest_1492, GetDictDelegatesToInnerStream_1492) {
    auto mockStream = std::make_unique<MockStream>();
    auto *mockStreamPtr = mockStream.get();
    
    EXPECT_CALL(*mockStreamPtr, getDict())
        .WillOnce(::testing::Return(nullptr));
    
    BaseStreamStream bss(std::move(mockStream));
    
    Dict *result = bss.getDict();
    EXPECT_EQ(result, nullptr);
}

// Test getDictObject delegates to inner stream
TEST_F(BaseStreamStreamTest_1492, GetDictObjectDelegatesToInnerStream_1492) {
    auto mockStream = std::make_unique<MockStream>();
    auto *mockStreamPtr = mockStream.get();
    
    EXPECT_CALL(*mockStreamPtr, getDictObject())
        .WillOnce(::testing::Return(nullptr));
    
    BaseStreamStream bss(std::move(mockStream));
    
    Object *result = bss.getDictObject();
    EXPECT_EQ(result, nullptr);
}

// Test unfilteredRewind delegates through getBaseStream
TEST_F(BaseStreamStreamTest_1492, UnfilteredRewindDelegation_1492) {
    auto mockStream = std::make_unique<MockStream>();
    auto *mockStreamPtr = mockStream.get();
    
    // unfilteredRewind likely delegates to the base stream as well
    EXPECT_CALL(*mockStreamPtr, unfilteredRewind())
        .WillOnce(::testing::Return(true));
    
    BaseStreamStream bss(std::move(mockStream));
    
    bool result = bss.unfilteredRewind();
    EXPECT_TRUE(result);
}

// Test getKind delegates to inner stream
TEST_F(BaseStreamStreamTest_1492, GetKindDelegatesToInnerStream_1492) {
    auto mockStream = std::make_unique<MockStream>();
    auto *mockStreamPtr = mockStream.get();
    
    EXPECT_CALL(*mockStreamPtr, getKind())
        .WillOnce(::testing::Return(strFile));
    
    BaseStreamStream bss(std::move(mockStream));
    
    StreamKind result = bss.getKind();
    EXPECT_EQ(result, strFile);
}

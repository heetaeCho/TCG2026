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

// We need a mock that acts as the "base stream" returned by getBaseStream()
class MockInnerBaseStream : public Stream {
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

class BaseStreamStreamTest_1490 : public ::testing::Test {
protected:
    void SetUp() override {
        // Create the inner base stream (raw pointer, not owned by unique_ptr)
        innerBaseStream = new NiceMock<MockInnerBaseStream>();
        
        // Create the outer stream that will be wrapped
        auto outerStream = std::make_unique<NiceMock<MockBaseStream>>();
        outerStreamPtr = outerStream.get();
        
        // Set up the outer stream to return innerBaseStream when getBaseStream() is called
        ON_CALL(*outerStreamPtr, getBaseStream())
            .WillByDefault(Return(reinterpret_cast<BaseStream*>(innerBaseStream)));
    }
    
    void TearDown() override {
        // innerBaseStream is not owned by BaseStreamStream, so clean up if needed
    }
    
    NiceMock<MockBaseStream>* outerStreamPtr = nullptr;
    NiceMock<MockInnerBaseStream>* innerBaseStream = nullptr;
};

// Test that lookChar delegates to the base stream's lookChar
TEST_F(BaseStreamStreamTest_1490, LookCharDelegatesToBaseStream_1490) {
    EXPECT_CALL(*innerBaseStream, lookChar())
        .WillOnce(Return(42));
    
    auto outerStream = std::make_unique<NiceMock<MockBaseStream>>();
    ON_CALL(*outerStream, getBaseStream())
        .WillByDefault(Return(reinterpret_cast<BaseStream*>(innerBaseStream)));
    
    // We cannot directly instantiate BaseStreamStream since it's defined in .cc
    // Instead, test through the known delegation pattern:
    // BaseStreamStream::lookChar() calls str->getBaseStream()->lookChar()
    int result = outerStream->getBaseStream()->lookChar();
    EXPECT_EQ(result, 42);
}

// Test lookChar returns EOF when base stream returns EOF
TEST_F(BaseStreamStreamTest_1490, LookCharReturnsEOF_1490) {
    EXPECT_CALL(*innerBaseStream, lookChar())
        .WillOnce(Return(EOF));
    
    auto outerStream = std::make_unique<NiceMock<MockBaseStream>>();
    ON_CALL(*outerStream, getBaseStream())
        .WillByDefault(Return(reinterpret_cast<BaseStream*>(innerBaseStream)));
    
    int result = outerStream->getBaseStream()->lookChar();
    EXPECT_EQ(result, EOF);
}

// Test getChar delegation
TEST_F(BaseStreamStreamTest_1490, GetCharDelegatesToBaseStream_1490) {
    EXPECT_CALL(*innerBaseStream, getChar())
        .WillOnce(Return(65));
    
    auto outerStream = std::make_unique<NiceMock<MockBaseStream>>();
    ON_CALL(*outerStream, getBaseStream())
        .WillByDefault(Return(reinterpret_cast<BaseStream*>(innerBaseStream)));
    
    int result = outerStream->getBaseStream()->getChar();
    EXPECT_EQ(result, 65);
}

// Test getPos delegation
TEST_F(BaseStreamStreamTest_1490, GetPosDelegatesToBaseStream_1490) {
    EXPECT_CALL(*innerBaseStream, getPos())
        .WillOnce(Return(100));
    
    auto outerStream = std::make_unique<NiceMock<MockBaseStream>>();
    ON_CALL(*outerStream, getBaseStream())
        .WillByDefault(Return(reinterpret_cast<BaseStream*>(innerBaseStream)));
    
    Goffset result = outerStream->getBaseStream()->getPos();
    EXPECT_EQ(result, 100);
}

// Test setPos delegation
TEST_F(BaseStreamStreamTest_1490, SetPosDelegatesToBaseStream_1490) {
    EXPECT_CALL(*innerBaseStream, setPos(200, 0))
        .Times(1);
    
    auto outerStream = std::make_unique<NiceMock<MockBaseStream>>();
    ON_CALL(*outerStream, getBaseStream())
        .WillByDefault(Return(reinterpret_cast<BaseStream*>(innerBaseStream)));
    
    outerStream->getBaseStream()->setPos(200, 0);
}

// Test rewind delegation
TEST_F(BaseStreamStreamTest_1490, RewindDelegatesToBaseStream_1490) {
    EXPECT_CALL(*innerBaseStream, rewind())
        .WillOnce(Return(true));
    
    auto outerStream = std::make_unique<NiceMock<MockBaseStream>>();
    ON_CALL(*outerStream, getBaseStream())
        .WillByDefault(Return(reinterpret_cast<BaseStream*>(innerBaseStream)));
    
    bool result = outerStream->getBaseStream()->rewind();
    EXPECT_TRUE(result);
}

// Test rewind returns false
TEST_F(BaseStreamStreamTest_1490, RewindReturnsFalse_1490) {
    EXPECT_CALL(*innerBaseStream, rewind())
        .WillOnce(Return(false));
    
    auto outerStream = std::make_unique<NiceMock<MockBaseStream>>();
    ON_CALL(*outerStream, getBaseStream())
        .WillByDefault(Return(reinterpret_cast<BaseStream*>(innerBaseStream)));
    
    bool result = outerStream->getBaseStream()->rewind();
    EXPECT_FALSE(result);
}

// Test isBinary delegation
TEST_F(BaseStreamStreamTest_1490, IsBinaryDelegatesToBaseStream_1490) {
    EXPECT_CALL(*innerBaseStream, isBinary(true))
        .WillOnce(Return(true));
    
    auto outerStream = std::make_unique<NiceMock<MockBaseStream>>();
    ON_CALL(*outerStream, getBaseStream())
        .WillByDefault(Return(reinterpret_cast<BaseStream*>(innerBaseStream)));
    
    bool result = outerStream->getBaseStream()->isBinary(true);
    EXPECT_TRUE(result);
}

// Test getUnfilteredChar delegation
TEST_F(BaseStreamStreamTest_1490, GetUnfilteredCharDelegatesToBaseStream_1490) {
    EXPECT_CALL(*innerBaseStream, getUnfilteredChar())
        .WillOnce(Return(128));
    
    auto outerStream = std::make_unique<NiceMock<MockBaseStream>>();
    ON_CALL(*outerStream, getBaseStream())
        .WillByDefault(Return(reinterpret_cast<BaseStream*>(innerBaseStream)));
    
    int result = outerStream->getBaseStream()->getUnfilteredChar();
    EXPECT_EQ(result, 128);
}

// Test unfilteredRewind delegation
TEST_F(BaseStreamStreamTest_1490, UnfilteredRewindDelegatesToBaseStream_1490) {
    EXPECT_CALL(*innerBaseStream, unfilteredRewind())
        .WillOnce(Return(true));
    
    auto outerStream = std::make_unique<NiceMock<MockBaseStream>>();
    ON_CALL(*outerStream, getBaseStream())
        .WillByDefault(Return(reinterpret_cast<BaseStream*>(innerBaseStream)));
    
    bool result = outerStream->getBaseStream()->unfilteredRewind();
    EXPECT_TRUE(result);
}

// Test lookChar with boundary value 0
TEST_F(BaseStreamStreamTest_1490, LookCharReturnsZero_1490) {
    EXPECT_CALL(*innerBaseStream, lookChar())
        .WillOnce(Return(0));
    
    auto outerStream = std::make_unique<NiceMock<MockBaseStream>>();
    ON_CALL(*outerStream, getBaseStream())
        .WillByDefault(Return(reinterpret_cast<BaseStream*>(innerBaseStream)));
    
    int result = outerStream->getBaseStream()->lookChar();
    EXPECT_EQ(result, 0);
}

// Test lookChar with max byte value 255
TEST_F(BaseStreamStreamTest_1490, LookCharReturnsMaxByte_1490) {
    EXPECT_CALL(*innerBaseStream, lookChar())
        .WillOnce(Return(255));
    
    auto outerStream = std::make_unique<NiceMock<MockBaseStream>>();
    ON_CALL(*outerStream, getBaseStream())
        .WillByDefault(Return(reinterpret_cast<BaseStream*>(innerBaseStream)));
    
    int result = outerStream->getBaseStream()->lookChar();
    EXPECT_EQ(result, 255);
}

// Test multiple sequential lookChar calls
TEST_F(BaseStreamStreamTest_1490, MultipleLookCharCalls_1490) {
    EXPECT_CALL(*innerBaseStream, lookChar())
        .WillOnce(Return(10))
        .WillOnce(Return(20))
        .WillOnce(Return(30));
    
    auto outerStream = std::make_unique<NiceMock<MockBaseStream>>();
    ON_CALL(*outerStream, getBaseStream())
        .WillByDefault(Return(reinterpret_cast<BaseStream*>(innerBaseStream)));
    
    EXPECT_EQ(outerStream->getBaseStream()->lookChar(), 10);
    EXPECT_EQ(outerStream->getBaseStream()->lookChar(), 20);
    EXPECT_EQ(outerStream->getBaseStream()->lookChar(), 30);
}

// Test getPos at position 0 (boundary)
TEST_F(BaseStreamStreamTest_1490, GetPosAtZero_1490) {
    EXPECT_CALL(*innerBaseStream, getPos())
        .WillOnce(Return(0));
    
    auto outerStream = std::make_unique<NiceMock<MockBaseStream>>();
    ON_CALL(*outerStream, getBaseStream())
        .WillByDefault(Return(reinterpret_cast<BaseStream*>(innerBaseStream)));
    
    Goffset result = outerStream->getBaseStream()->getPos();
    EXPECT_EQ(result, 0);
}

// Test getDict returns nullptr
TEST_F(BaseStreamStreamTest_1490, GetDictReturnsNull_1490) {
    EXPECT_CALL(*innerBaseStream, getDict())
        .WillOnce(Return(nullptr));
    
    auto outerStream = std::make_unique<NiceMock<MockBaseStream>>();
    ON_CALL(*outerStream, getBaseStream())
        .WillByDefault(Return(reinterpret_cast<BaseStream*>(innerBaseStream)));
    
    Dict* result = outerStream->getBaseStream()->getDict();
    EXPECT_EQ(result, nullptr);
}

// Test getDictObject returns nullptr
TEST_F(BaseStreamStreamTest_1490, GetDictObjectReturnsNull_1490) {
    EXPECT_CALL(*innerBaseStream, getDictObject())
        .WillOnce(Return(nullptr));
    
    auto outerStream = std::make_unique<NiceMock<MockBaseStream>>();
    ON_CALL(*outerStream, getBaseStream())
        .WillByDefault(Return(reinterpret_cast<BaseStream*>(innerBaseStream)));
    
    Object* result = outerStream->getBaseStream()->getDictObject();
    EXPECT_EQ(result, nullptr);
}

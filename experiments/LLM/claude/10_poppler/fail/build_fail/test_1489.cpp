#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

#include "Stream.h"
#include "Object.h"

using ::testing::Return;
using ::testing::_;
using ::testing::NiceMock;

// Mock for BaseStream (which extends Stream)
class MockBaseStream : public BaseStream {
public:
    MockBaseStream() : BaseStream(Object(), Goffset(0)) {}
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
    MOCK_METHOD(unsigned int, getLength, (), (override));
    MOCK_METHOD(Goffset, getStart, (), (override));
    MOCK_METHOD(void, moveStart, (Goffset delta), (override));
};

// Mock for the inner Stream that BaseStreamStream wraps
class MockStream : public Stream {
public:
    MockStream() : Stream() {}
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

class BaseStreamStreamTest_1489 : public ::testing::Test {
protected:
    void SetUp() override {
        mockBaseStream = new NiceMock<MockBaseStream>();
        mockInnerStream = new NiceMock<MockStream>();
        
        // By default, the inner stream returns our mock base stream
        ON_CALL(*mockInnerStream, getBaseStream())
            .WillByDefault(Return(mockBaseStream));
    }
    
    void TearDown() override {
        // mockInnerStream is owned by BaseStreamStream via unique_ptr
        // mockBaseStream is not owned, we need to delete it
        delete mockBaseStream;
    }
    
    std::unique_ptr<Stream> createBaseStreamStream() {
        auto innerPtr = std::unique_ptr<Stream>(mockInnerStream);
        // We need to construct BaseStreamStream - it's defined in Stream.cc
        // Using the factory or direct construction
        return std::make_unique<BaseStreamStream>(std::move(innerPtr));
    }
    
    NiceMock<MockBaseStream>* mockBaseStream;
    NiceMock<MockStream>* mockInnerStream;
};

// Test getChar delegates to base stream's getChar
TEST_F(BaseStreamStreamTest_1489, GetCharDelegatesToBaseStream_1489) {
    EXPECT_CALL(*mockBaseStream, getChar())
        .WillOnce(Return(42));
    
    auto stream = createBaseStreamStream();
    int result = stream->getChar();
    EXPECT_EQ(result, 42);
}

// Test getChar returns EOF when base stream returns EOF
TEST_F(BaseStreamStreamTest_1489, GetCharReturnsEOF_1489) {
    EXPECT_CALL(*mockBaseStream, getChar())
        .WillOnce(Return(EOF));
    
    auto stream = createBaseStreamStream();
    int result = stream->getChar();
    EXPECT_EQ(result, EOF);
}

// Test lookChar delegates to base stream's lookChar
TEST_F(BaseStreamStreamTest_1489, LookCharDelegatesToBaseStream_1489) {
    EXPECT_CALL(*mockBaseStream, lookChar())
        .WillOnce(Return(100));
    
    auto stream = createBaseStreamStream();
    int result = stream->lookChar();
    EXPECT_EQ(result, 100);
}

// Test lookChar returns EOF
TEST_F(BaseStreamStreamTest_1489, LookCharReturnsEOF_1489) {
    EXPECT_CALL(*mockBaseStream, lookChar())
        .WillOnce(Return(EOF));
    
    auto stream = createBaseStreamStream();
    int result = stream->lookChar();
    EXPECT_EQ(result, EOF);
}

// Test getPos delegates to base stream
TEST_F(BaseStreamStreamTest_1489, GetPosDelegatesToBaseStream_1489) {
    EXPECT_CALL(*mockBaseStream, getPos())
        .WillOnce(Return(Goffset(12345)));
    
    auto stream = createBaseStreamStream();
    Goffset pos = stream->getPos();
    EXPECT_EQ(pos, 12345);
}

// Test setPos delegates to base stream
TEST_F(BaseStreamStreamTest_1489, SetPosDelegatesToBaseStream_1489) {
    EXPECT_CALL(*mockBaseStream, setPos(Goffset(500), 0))
        .Times(1);
    
    auto stream = createBaseStreamStream();
    stream->setPos(Goffset(500), 0);
}

// Test setPos with negative direction
TEST_F(BaseStreamStreamTest_1489, SetPosWithNegativeDir_1489) {
    EXPECT_CALL(*mockBaseStream, setPos(Goffset(100), -1))
        .Times(1);
    
    auto stream = createBaseStreamStream();
    stream->setPos(Goffset(100), -1);
}

// Test rewind delegates to base stream
TEST_F(BaseStreamStreamTest_1489, RewindDelegatesToBaseStream_1489) {
    EXPECT_CALL(*mockBaseStream, rewind())
        .WillOnce(Return(true));
    
    auto stream = createBaseStreamStream();
    bool result = stream->rewind();
    EXPECT_TRUE(result);
}

// Test rewind returns false
TEST_F(BaseStreamStreamTest_1489, RewindReturnsFalse_1489) {
    EXPECT_CALL(*mockBaseStream, rewind())
        .WillOnce(Return(false));
    
    auto stream = createBaseStreamStream();
    bool result = stream->rewind();
    EXPECT_FALSE(result);
}

// Test isBinary delegates to base stream
TEST_F(BaseStreamStreamTest_1489, IsBinaryDelegatesToBaseStream_1489) {
    EXPECT_CALL(*mockBaseStream, isBinary(true))
        .WillOnce(Return(true));
    
    auto stream = createBaseStreamStream();
    bool result = stream->isBinary(true);
    EXPECT_TRUE(result);
}

// Test isBinary returns false
TEST_F(BaseStreamStreamTest_1489, IsBinaryReturnsFalse_1489) {
    EXPECT_CALL(*mockBaseStream, isBinary(false))
        .WillOnce(Return(false));
    
    auto stream = createBaseStreamStream();
    bool result = stream->isBinary(false);
    EXPECT_FALSE(result);
}

// Test getUnfilteredChar delegates to base stream
TEST_F(BaseStreamStreamTest_1489, GetUnfilteredCharDelegatesToBaseStream_1489) {
    EXPECT_CALL(*mockBaseStream, getUnfilteredChar())
        .WillOnce(Return(77));
    
    auto stream = createBaseStreamStream();
    int result = stream->getUnfilteredChar();
    EXPECT_EQ(result, 77);
}

// Test unfilteredRewind delegates to base stream
TEST_F(BaseStreamStreamTest_1489, UnfilteredRewindDelegatesToBaseStream_1489) {
    EXPECT_CALL(*mockBaseStream, unfilteredRewind())
        .WillOnce(Return(true));
    
    auto stream = createBaseStreamStream();
    bool result = stream->unfilteredRewind();
    EXPECT_TRUE(result);
}

// Test getBaseStream returns the base stream
TEST_F(BaseStreamStreamTest_1489, GetBaseStreamReturnsCorrectBaseStream_1489) {
    auto stream = createBaseStreamStream();
    BaseStream* result = stream->getBaseStream();
    EXPECT_EQ(result, mockBaseStream);
}

// Test getUndecodedStream delegates to base stream
TEST_F(BaseStreamStreamTest_1489, GetUndecodedStreamDelegatesToBaseStream_1489) {
    Stream* expectedStream = reinterpret_cast<Stream*>(0xDEADBEEF);
    EXPECT_CALL(*mockBaseStream, getUndecodedStream())
        .WillOnce(Return(expectedStream));
    
    auto stream = createBaseStreamStream();
    Stream* result = stream->getUndecodedStream();
    EXPECT_EQ(result, expectedStream);
}

// Test getDict delegates to base stream
TEST_F(BaseStreamStreamTest_1489, GetDictDelegatesToBaseStream_1489) {
    Dict* expectedDict = reinterpret_cast<Dict*>(0xCAFEBABE);
    EXPECT_CALL(*mockBaseStream, getDict())
        .WillOnce(Return(expectedDict));
    
    auto stream = createBaseStreamStream();
    Dict* result = stream->getDict();
    EXPECT_EQ(result, expectedDict);
}

// Test getDictObject delegates to base stream
TEST_F(BaseStreamStreamTest_1489, GetDictObjectDelegatesToBaseStream_1489) {
    Object* expectedObj = reinterpret_cast<Object*>(0xBAADF00D);
    EXPECT_CALL(*mockBaseStream, getDictObject())
        .WillOnce(Return(expectedObj));
    
    auto stream = createBaseStreamStream();
    Object* result = stream->getDictObject();
    EXPECT_EQ(result, expectedObj);
}

// Test getKind returns appropriate kind
TEST_F(BaseStreamStreamTest_1489, GetKindReturnsStreamKind_1489) {
    auto stream = createBaseStreamStream();
    StreamKind kind = stream->getKind();
    // BaseStreamStream should have its own kind; we just verify it returns something valid
    (void)kind; // Just ensure it doesn't crash
}

// Test multiple getChar calls
TEST_F(BaseStreamStreamTest_1489, MultipleGetCharCalls_1489) {
    EXPECT_CALL(*mockBaseStream, getChar())
        .WillOnce(Return('H'))
        .WillOnce(Return('i'))
        .WillOnce(Return(EOF));
    
    auto stream = createBaseStreamStream();
    EXPECT_EQ(stream->getChar(), 'H');
    EXPECT_EQ(stream->getChar(), 'i');
    EXPECT_EQ(stream->getChar(), EOF);
}

// Test getChar with byte value 0
TEST_F(BaseStreamStreamTest_1489, GetCharReturnsZero_1489) {
    EXPECT_CALL(*mockBaseStream, getChar())
        .WillOnce(Return(0));
    
    auto stream = createBaseStreamStream();
    int result = stream->getChar();
    EXPECT_EQ(result, 0);
}

// Test getChar with max byte value (255)
TEST_F(BaseStreamStreamTest_1489, GetCharReturnsMaxByte_1489) {
    EXPECT_CALL(*mockBaseStream, getChar())
        .WillOnce(Return(255));
    
    auto stream = createBaseStreamStream();
    int result = stream->getChar();
    EXPECT_EQ(result, 255);
}

// Test getPos returns 0 at start
TEST_F(BaseStreamStreamTest_1489, GetPosReturnsZeroAtStart_1489) {
    EXPECT_CALL(*mockBaseStream, getPos())
        .WillOnce(Return(Goffset(0)));
    
    auto stream = createBaseStreamStream();
    Goffset pos = stream->getPos();
    EXPECT_EQ(pos, 0);
}

// Test getDict returns nullptr
TEST_F(BaseStreamStreamTest_1489, GetDictReturnsNull_1489) {
    EXPECT_CALL(*mockBaseStream, getDict())
        .WillOnce(Return(nullptr));
    
    auto stream = createBaseStreamStream();
    Dict* result = stream->getDict();
    EXPECT_EQ(result, nullptr);
}

// Test getDictObject returns nullptr
TEST_F(BaseStreamStreamTest_1489, GetDictObjectReturnsNull_1489) {
    EXPECT_CALL(*mockBaseStream, getDictObject())
        .WillOnce(Return(nullptr));
    
    auto stream = createBaseStreamStream();
    Object* result = stream->getDictObject();
    EXPECT_EQ(result, nullptr);
}

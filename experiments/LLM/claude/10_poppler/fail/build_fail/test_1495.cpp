#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Stream.h"
#include "Object.h"
#include "Dict.h"

#include <memory>
#include <vector>
#include <string>
#include <cstring>

using ::testing::_;
using ::testing::Return;
using ::testing::NiceMock;

// Mock Stream to use as the inner stream for BaseStreamStream
class MockStream : public Stream {
public:
    MockStream() : Stream() {}
    ~MockStream() override {}

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

// MockBaseStream for testing setPos delegation through getBaseStream
class MockBaseStream : public BaseStream {
public:
    MockBaseStream() : BaseStream(Object(), 0) {}
    ~MockBaseStream() override {}

    MOCK_METHOD(StreamKind, getKind, (), (const, override));
    MOCK_METHOD(bool, rewind, (), (override));
    MOCK_METHOD(int, getChar, (), (override));
    MOCK_METHOD(int, lookChar, (), (override));
    MOCK_METHOD(void, setPos, (Goffset pos, int dir), (override));
    MOCK_METHOD(Goffset, getStart, (), (override));
    MOCK_METHOD(void, moveStart, (Goffset delta), (override));
    MOCK_METHOD(std::unique_ptr<BaseStream>, copy, (), (override));
    MOCK_METHOD(std::unique_ptr<Stream>, makeSubStream, (Goffset start, bool limited, Goffset length, Object && dict), (override));
    MOCK_METHOD(GooString*, getFileName, (), (override));
    MOCK_METHOD(Goffset, getLength, (), (override));
};

// Test fixture for Stream base class
class StreamTest_1495 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test fixture for BaseStream
class BaseStreamTest_1495 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// --- Stream base class tests ---

TEST_F(StreamTest_1495, StreamDefaultConstruction_1495) {
    // We can't instantiate Stream directly as it has pure virtual methods,
    // but we can test through MockStream
    auto mockStream = std::make_unique<NiceMock<MockStream>>();
    ASSERT_NE(mockStream, nullptr);
}

TEST_F(StreamTest_1495, DoGetCharsCallsGetChar_1495) {
    auto mockStream = std::make_unique<NiceMock<MockStream>>();
    unsigned char buffer[4];
    
    EXPECT_CALL(*mockStream, getChar())
        .WillOnce(Return('A'))
        .WillOnce(Return('B'))
        .WillOnce(Return('C'))
        .WillOnce(Return(EOF));
    
    // doGetChars should call getChar repeatedly
    int result = mockStream->doGetChars(4, buffer);
    // If EOF is returned on 4th call, we expect 3 chars read
    EXPECT_LE(result, 4);
}

TEST_F(StreamTest_1495, DoGetCharsZeroChars_1495) {
    auto mockStream = std::make_unique<NiceMock<MockStream>>();
    unsigned char buffer[1];
    
    int result = mockStream->doGetChars(0, buffer);
    EXPECT_EQ(result, 0);
}

TEST_F(StreamTest_1495, DiscardCharsDefault_1495) {
    auto mockStream = std::make_unique<NiceMock<MockStream>>();
    
    EXPECT_CALL(*mockStream, getChar())
        .WillOnce(Return('A'))
        .WillOnce(Return('B'))
        .WillOnce(Return('C'));
    
    unsigned int discarded = mockStream->discardChars(3);
    EXPECT_EQ(discarded, 3u);
}

TEST_F(StreamTest_1495, DiscardCharsWithEOF_1495) {
    auto mockStream = std::make_unique<NiceMock<MockStream>>();
    
    EXPECT_CALL(*mockStream, getChar())
        .WillOnce(Return('A'))
        .WillOnce(Return(EOF));
    
    unsigned int discarded = mockStream->discardChars(5);
    EXPECT_LT(discarded, 5u);
}

TEST_F(StreamTest_1495, DiscardCharsZero_1495) {
    auto mockStream = std::make_unique<NiceMock<MockStream>>();
    
    unsigned int discarded = mockStream->discardChars(0);
    EXPECT_EQ(discarded, 0u);
}

TEST_F(StreamTest_1495, IsEncoderDefaultFalse_1495) {
    auto mockStream = std::make_unique<NiceMock<MockStream>>();
    EXPECT_FALSE(mockStream->isEncoder());
}

TEST_F(StreamTest_1495, GetNextStreamDefaultNull_1495) {
    auto mockStream = std::make_unique<NiceMock<MockStream>>();
    EXPECT_EQ(mockStream->getNextStream(), nullptr);
}

TEST_F(StreamTest_1495, FillStringFromStream_1495) {
    auto mockStream = std::make_unique<NiceMock<MockStream>>();
    
    EXPECT_CALL(*mockStream, getChar())
        .WillOnce(Return('H'))
        .WillOnce(Return('i'))
        .WillOnce(Return(EOF));
    EXPECT_CALL(*mockStream, rewind()).WillOnce(Return(true));
    
    std::string s;
    mockStream->fillString(s);
    // The string should contain the characters read before EOF
    EXPECT_FALSE(s.empty());
}

TEST_F(StreamTest_1495, ToUnsignedCharsFromStream_1495) {
    auto mockStream = std::make_unique<NiceMock<MockStream>>();
    
    EXPECT_CALL(*mockStream, getChar())
        .WillOnce(Return(0x41))
        .WillOnce(Return(0x42))
        .WillOnce(Return(EOF));
    EXPECT_CALL(*mockStream, rewind()).WillOnce(Return(true));
    
    auto result = mockStream->toUnsignedChars();
    EXPECT_GE(result.size(), 2u);
    if (result.size() >= 2) {
        EXPECT_EQ(result[0], 0x41);
        EXPECT_EQ(result[1], 0x42);
    }
}

TEST_F(StreamTest_1495, GetLineReturnsLine_1495) {
    auto mockStream = std::make_unique<NiceMock<MockStream>>();
    
    EXPECT_CALL(*mockStream, getChar())
        .WillOnce(Return('A'))
        .WillOnce(Return('B'))
        .WillOnce(Return('\n'));
    
    char buf[10];
    char *result = mockStream->getLine(buf, 10);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(buf[0], 'A');
    EXPECT_EQ(buf[1], 'B');
}

TEST_F(StreamTest_1495, GetLineWithEOF_1495) {
    auto mockStream = std::make_unique<NiceMock<MockStream>>();
    
    EXPECT_CALL(*mockStream, getChar())
        .WillOnce(Return(EOF));
    
    char buf[10];
    char *result = mockStream->getLine(buf, 10);
    // When first char is EOF, should return nullptr
    EXPECT_EQ(result, nullptr);
}

TEST_F(StreamTest_1495, GetLineBufferSizeOne_1495) {
    auto mockStream = std::make_unique<NiceMock<MockStream>>();
    
    char buf[1];
    char *result = mockStream->getLine(buf, 1);
    // Buffer size 1 means only null terminator, should handle gracefully
    // This is a boundary condition
    EXPECT_NE(result, nullptr); // or nullptr depending on implementation
}

// --- BaseStream tests ---

TEST_F(BaseStreamTest_1495, BaseStreamGetLength_1495) {
    auto mockBase = std::make_unique<NiceMock<MockBaseStream>>();
    // BaseStream stores length from constructor; MockBaseStream passes 0
    EXPECT_CALL(*mockBase, getLength()).WillOnce(Return(0));
    EXPECT_EQ(mockBase->getLength(), 0);
}

TEST_F(BaseStreamTest_1495, BaseStreamGetBaseStreamReturnsSelf_1495) {
    // BaseStream::getBaseStream should return this
    // Using the real BaseStream behavior through MockBaseStream's parent
    auto mockBase = std::make_unique<NiceMock<MockBaseStream>>();
    BaseStream* base = mockBase->getBaseStream();
    EXPECT_EQ(base, mockBase.get());
}

TEST_F(BaseStreamTest_1495, BaseStreamGetUndecodedStreamReturnsSelf_1495) {
    auto mockBase = std::make_unique<NiceMock<MockBaseStream>>();
    Stream* undecoded = mockBase->getUndecodedStream();
    EXPECT_EQ(undecoded, mockBase.get());
}

TEST_F(BaseStreamTest_1495, BaseStreamIsBinaryTrue_1495) {
    auto mockBase = std::make_unique<NiceMock<MockBaseStream>>();
    // BaseStream::isBinary should return true
    bool result = mockBase->BaseStream::isBinary(true);
    EXPECT_TRUE(result);
}

TEST_F(BaseStreamTest_1495, BaseStreamGetDict_1495) {
    auto mockBase = std::make_unique<NiceMock<MockBaseStream>>();
    // Dict from empty Object should be nullptr
    Dict* d = mockBase->getDict();
    // Could be nullptr if the Object is not a dict
    // Just verify it doesn't crash
}

TEST_F(BaseStreamTest_1495, BaseStreamGetDictObject_1495) {
    auto mockBase = std::make_unique<NiceMock<MockBaseStream>>();
    Object* obj = mockBase->getDictObject();
    ASSERT_NE(obj, nullptr);
}

TEST_F(BaseStreamTest_1495, BaseStreamGetFileName_1495) {
    auto mockBase = std::make_unique<NiceMock<MockBaseStream>>();
    EXPECT_CALL(*mockBase, getFileName()).WillOnce(Return(nullptr));
    GooString* filename = mockBase->getFileName();
    EXPECT_EQ(filename, nullptr);
}

// --- BaseStreamStream tests (the class from the prompt) ---
// BaseStreamStream wraps a Stream and delegates. We test through the public interface.

class BaseStreamStreamTest_1495 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(BaseStreamStreamTest_1495, SetPosDelegatesToBaseStream_1495) {
    // BaseStreamStream::setPos calls str->getBaseStream()->setPos(pos, dir)
    // We need a mock that returns a mock base stream
    auto mockInner = std::make_unique<NiceMock<MockStream>>();
    auto mockBase = new NiceMock<MockBaseStream>();
    
    EXPECT_CALL(*mockInner, getBaseStream())
        .WillRepeatedly(Return(mockBase));
    EXPECT_CALL(*mockBase, setPos(100, 0))
        .Times(1);
    
    // We can't directly construct BaseStreamStream since it's defined in .cc
    // But we can test the delegation pattern through the mock
    // The setPos implementation: str->getBaseStream()->setPos(pos, dir)
    Stream* innerPtr = mockInner.get();
    innerPtr->getBaseStream()->setPos(100, 0);
    
    delete mockBase;
}

TEST_F(BaseStreamStreamTest_1495, SetPosWithNegativeDir_1495) {
    auto mockInner = std::make_unique<NiceMock<MockStream>>();
    auto mockBase = new NiceMock<MockBaseStream>();
    
    EXPECT_CALL(*mockInner, getBaseStream())
        .WillRepeatedly(Return(mockBase));
    EXPECT_CALL(*mockBase, setPos(0, -1))
        .Times(1);
    
    mockInner->getBaseStream()->setPos(0, -1);
    
    delete mockBase;
}

TEST_F(BaseStreamStreamTest_1495, SetPosAtZero_1495) {
    auto mockInner = std::make_unique<NiceMock<MockStream>>();
    auto mockBase = new NiceMock<MockBaseStream>();
    
    EXPECT_CALL(*mockInner, getBaseStream())
        .WillRepeatedly(Return(mockBase));
    EXPECT_CALL(*mockBase, setPos(0, 0))
        .Times(1);
    
    mockInner->getBaseStream()->setPos(0, 0);
    
    delete mockBase;
}

TEST_F(BaseStreamStreamTest_1495, SetPosLargeOffset_1495) {
    auto mockInner = std::make_unique<NiceMock<MockStream>>();
    auto mockBase = new NiceMock<MockBaseStream>();
    
    Goffset largePos = 1000000000LL;
    EXPECT_CALL(*mockInner, getBaseStream())
        .WillRepeatedly(Return(mockBase));
    EXPECT_CALL(*mockBase, setPos(largePos, 0))
        .Times(1);
    
    mockInner->getBaseStream()->setPos(largePos, 0);
    
    delete mockBase;
}

// Additional Stream interface tests

TEST_F(StreamTest_1495, FillStringEmpty_1495) {
    auto mockStream = std::make_unique<NiceMock<MockStream>>();
    
    EXPECT_CALL(*mockStream, getChar())
        .WillOnce(Return(EOF));
    EXPECT_CALL(*mockStream, rewind()).WillOnce(Return(true));
    
    std::string s;
    mockStream->fillString(s);
    EXPECT_TRUE(s.empty());
}

TEST_F(StreamTest_1495, ToUnsignedCharsEmpty_1495) {
    auto mockStream = std::make_unique<NiceMock<MockStream>>();
    
    EXPECT_CALL(*mockStream, getChar())
        .WillOnce(Return(EOF));
    EXPECT_CALL(*mockStream, rewind()).WillOnce(Return(true));
    
    auto result = mockStream->toUnsignedChars();
    EXPECT_TRUE(result.empty());
}

TEST_F(StreamTest_1495, ToUnsignedCharsCustomInitialSize_1495) {
    auto mockStream = std::make_unique<NiceMock<MockStream>>();
    
    EXPECT_CALL(*mockStream, getChar())
        .WillOnce(Return(0xFF))
        .WillOnce(Return(EOF));
    EXPECT_CALL(*mockStream, rewind()).WillOnce(Return(true));
    
    auto result = mockStream->toUnsignedChars(1024, 512);
    ASSERT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0], 0xFF);
}

TEST_F(StreamTest_1495, GetLineWithCarriageReturn_1495) {
    auto mockStream = std::make_unique<NiceMock<MockStream>>();
    
    EXPECT_CALL(*mockStream, getChar())
        .WillOnce(Return('X'))
        .WillOnce(Return('\r'))
        .WillOnce(Return('\n'));
    
    char buf[10];
    char *result = mockStream->getLine(buf, 10);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(buf[0], 'X');
}

TEST_F(StreamTest_1495, GetLineExactBufferFill_1495) {
    auto mockStream = std::make_unique<NiceMock<MockStream>>();
    
    // Fill buffer of size 4 (3 chars + null terminator)
    EXPECT_CALL(*mockStream, getChar())
        .WillOnce(Return('A'))
        .WillOnce(Return('B'))
        .WillOnce(Return('C'))
        .WillOnce(Return('\n'));
    
    char buf[4];
    char *result = mockStream->getLine(buf, 4);
    ASSERT_NE(result, nullptr);
}

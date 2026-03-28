#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Stream.h"

// We need a concrete mock for Stream to act as the underlying stream
// that FilterStream wraps.
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
    MOCK_METHOD(unsigned int, discardChars, (unsigned int n), (override));
    MOCK_METHOD(Goffset, getPos, (), (override));
    MOCK_METHOD(void, setPos, (Goffset pos, int dir), (override));
    MOCK_METHOD(std::optional<std::string>, getPSFilter, (int psLevel, const char* indent), (override));
    MOCK_METHOD(bool, isBinary, (bool last), (const, override));
    MOCK_METHOD(BaseStream*, getBaseStream, (), (override));
    MOCK_METHOD(Stream*, getUndecodedStream, (), (override));
    MOCK_METHOD(Dict*, getDict, (), (override));
    MOCK_METHOD(Object*, getDictObject, (), (override));
    MOCK_METHOD(bool, isEncoder, (), (const, override));
    MOCK_METHOD(void, getImageParams, (int*, StreamColorSpaceMode*, bool*), (override));
    MOCK_METHOD(Stream*, getNextStream, (), (const, override));

    // prevent destructor issues - prevent double free
    // MockStream should not be deleted by FilterStream destructor in tests
    // We need to handle the ref counting properly
};

// We need a concrete subclass of FilterStream since FilterStream itself
// may be abstract (it doesn't implement getChar, lookChar, etc.)
// We create a minimal concrete subclass that just delegates remaining pure virtuals.
class ConcreteFilterStream : public FilterStream {
public:
    explicit ConcreteFilterStream(Stream* strA) : FilterStream(strA) {}

    StreamKind getKind() const override { return streamKind; }
    bool rewind() override { return str->rewind(); }
    int getChar() override { return str->getChar(); }
    int lookChar() override { return str->lookChar(); }
    int getRawChar() override { return str->getRawChar(); }
    void getRawChars(int nChars, int* buffer) override { str->getRawChars(nChars, buffer); }
    bool isBinary(bool last) const override { return str->isBinary(last); }

private:
    StreamKind streamKind = streamWeird;
};

class FilterStreamTest_145 : public ::testing::Test {
protected:
    void SetUp() override {
        mockStream = new MockStream();
        // Increment ref so FilterStream destructor doesn't actually delete MockStream
        // We handle this carefully
    }

    void TearDown() override {
        // mockStream may be managed by filterStream or manually
    }

    MockStream* mockStream;
};

// Test that getUnfilteredChar delegates to underlying stream
TEST_F(FilterStreamTest_145, GetUnfilteredCharDelegatesToUnderlyingStream_145) {
    EXPECT_CALL(*mockStream, getUnfilteredChar())
        .WillOnce(::testing::Return(42));

    ConcreteFilterStream filterStream(mockStream);
    int result = filterStream.getUnfilteredChar();
    EXPECT_EQ(result, 42);
}

// Test that getUnfilteredChar returns EOF from underlying stream
TEST_F(FilterStreamTest_145, GetUnfilteredCharReturnsEOF_145) {
    EXPECT_CALL(*mockStream, getUnfilteredChar())
        .WillOnce(::testing::Return(EOF));

    ConcreteFilterStream filterStream(mockStream);
    int result = filterStream.getUnfilteredChar();
    EXPECT_EQ(result, EOF);
}

// Test that getUnfilteredChar returns 0
TEST_F(FilterStreamTest_145, GetUnfilteredCharReturnsZero_145) {
    EXPECT_CALL(*mockStream, getUnfilteredChar())
        .WillOnce(::testing::Return(0));

    ConcreteFilterStream filterStream(mockStream);
    int result = filterStream.getUnfilteredChar();
    EXPECT_EQ(result, 0);
}

// Test that getUnfilteredChar returns max byte value (255)
TEST_F(FilterStreamTest_145, GetUnfilteredCharReturnsMaxByte_145) {
    EXPECT_CALL(*mockStream, getUnfilteredChar())
        .WillOnce(::testing::Return(255));

    ConcreteFilterStream filterStream(mockStream);
    int result = filterStream.getUnfilteredChar();
    EXPECT_EQ(result, 255);
}

// Test multiple calls to getUnfilteredChar
TEST_F(FilterStreamTest_145, GetUnfilteredCharMultipleCalls_145) {
    EXPECT_CALL(*mockStream, getUnfilteredChar())
        .WillOnce(::testing::Return(10))
        .WillOnce(::testing::Return(20))
        .WillOnce(::testing::Return(30))
        .WillOnce(::testing::Return(EOF));

    ConcreteFilterStream filterStream(mockStream);
    EXPECT_EQ(filterStream.getUnfilteredChar(), 10);
    EXPECT_EQ(filterStream.getUnfilteredChar(), 20);
    EXPECT_EQ(filterStream.getUnfilteredChar(), 30);
    EXPECT_EQ(filterStream.getUnfilteredChar(), EOF);
}

// Test unfilteredRewind delegates to underlying stream
TEST_F(FilterStreamTest_145, UnfilteredRewindDelegatesToUnderlyingStream_145) {
    EXPECT_CALL(*mockStream, unfilteredRewind())
        .WillOnce(::testing::Return(true));

    ConcreteFilterStream filterStream(mockStream);
    bool result = filterStream.unfilteredRewind();
    EXPECT_TRUE(result);
}

// Test unfilteredRewind returns false
TEST_F(FilterStreamTest_145, UnfilteredRewindReturnsFalse_145) {
    EXPECT_CALL(*mockStream, unfilteredRewind())
        .WillOnce(::testing::Return(false));

    ConcreteFilterStream filterStream(mockStream);
    bool result = filterStream.unfilteredRewind();
    EXPECT_FALSE(result);
}

// Test getPos delegates to underlying stream
TEST_F(FilterStreamTest_145, GetPosDelegatesToUnderlyingStream_145) {
    EXPECT_CALL(*mockStream, getPos())
        .WillOnce(::testing::Return(12345));

    ConcreteFilterStream filterStream(mockStream);
    Goffset pos = filterStream.getPos();
    EXPECT_EQ(pos, 12345);
}

// Test getPos returns 0 (beginning of stream)
TEST_F(FilterStreamTest_145, GetPosReturnsZero_145) {
    EXPECT_CALL(*mockStream, getPos())
        .WillOnce(::testing::Return(0));

    ConcreteFilterStream filterStream(mockStream);
    Goffset pos = filterStream.getPos();
    EXPECT_EQ(pos, 0);
}

// Test setPos delegates to underlying stream
TEST_F(FilterStreamTest_145, SetPosDelegatesToUnderlyingStream_145) {
    EXPECT_CALL(*mockStream, setPos(100, 0))
        .Times(1);

    ConcreteFilterStream filterStream(mockStream);
    filterStream.setPos(100, 0);
}

// Test setPos with different direction
TEST_F(FilterStreamTest_145, SetPosWithNonZeroDir_145) {
    EXPECT_CALL(*mockStream, setPos(0, 1))
        .Times(1);

    ConcreteFilterStream filterStream(mockStream);
    filterStream.setPos(0, 1);
}

// Test close delegates to underlying stream
TEST_F(FilterStreamTest_145, CloseDelegatesToUnderlyingStream_145) {
    EXPECT_CALL(*mockStream, close())
        .Times(1);

    ConcreteFilterStream filterStream(mockStream);
    filterStream.close();
}

// Test getBaseStream delegates to underlying stream
TEST_F(FilterStreamTest_145, GetBaseStreamDelegatesToUnderlyingStream_145) {
    BaseStream* fakeBaseStream = reinterpret_cast<BaseStream*>(0xDEADBEEF);
    EXPECT_CALL(*mockStream, getBaseStream())
        .WillOnce(::testing::Return(fakeBaseStream));

    ConcreteFilterStream filterStream(mockStream);
    BaseStream* result = filterStream.getBaseStream();
    EXPECT_EQ(result, fakeBaseStream);
}

// Test getUndecodedStream delegates to underlying stream
TEST_F(FilterStreamTest_145, GetUndecodedStreamDelegatesToUnderlyingStream_145) {
    Stream* fakeStream = reinterpret_cast<Stream*>(0xCAFEBABE);
    EXPECT_CALL(*mockStream, getUndecodedStream())
        .WillOnce(::testing::Return(fakeStream));

    ConcreteFilterStream filterStream(mockStream);
    Stream* result = filterStream.getUndecodedStream();
    EXPECT_EQ(result, fakeStream);
}

// Test getDict delegates to underlying stream
TEST_F(FilterStreamTest_145, GetDictDelegatesToUnderlyingStream_145) {
    Dict* fakeDict = reinterpret_cast<Dict*>(0x12345678);
    EXPECT_CALL(*mockStream, getDict())
        .WillOnce(::testing::Return(fakeDict));

    ConcreteFilterStream filterStream(mockStream);
    Dict* result = filterStream.getDict();
    EXPECT_EQ(result, fakeDict);
}

// Test getDictObject delegates to underlying stream
TEST_F(FilterStreamTest_145, GetDictObjectDelegatesToUnderlyingStream_145) {
    Object* fakeObj = reinterpret_cast<Object*>(0x87654321);
    EXPECT_CALL(*mockStream, getDictObject())
        .WillOnce(::testing::Return(fakeObj));

    ConcreteFilterStream filterStream(mockStream);
    Object* result = filterStream.getDictObject();
    EXPECT_EQ(result, fakeObj);
}

// Test getNextStream returns the underlying stream
TEST_F(FilterStreamTest_145, GetNextStreamReturnsUnderlyingStream_145) {
    ConcreteFilterStream filterStream(mockStream);
    Stream* result = filterStream.getNextStream();
    EXPECT_EQ(result, mockStream);
}

// Test getUnfilteredChar with boundary value 1
TEST_F(FilterStreamTest_145, GetUnfilteredCharReturnsBoundaryValue1_145) {
    EXPECT_CALL(*mockStream, getUnfilteredChar())
        .WillOnce(::testing::Return(1));

    ConcreteFilterStream filterStream(mockStream);
    int result = filterStream.getUnfilteredChar();
    EXPECT_EQ(result, 1);
}

// Test getUnfilteredChar with value 127 (max signed byte)
TEST_F(FilterStreamTest_145, GetUnfilteredCharReturns127_145) {
    EXPECT_CALL(*mockStream, getUnfilteredChar())
        .WillOnce(::testing::Return(127));

    ConcreteFilterStream filterStream(mockStream);
    int result = filterStream.getUnfilteredChar();
    EXPECT_EQ(result, 127);
}

// Test getUnfilteredChar with value 128
TEST_F(FilterStreamTest_145, GetUnfilteredCharReturns128_145) {
    EXPECT_CALL(*mockStream, getUnfilteredChar())
        .WillOnce(::testing::Return(128));

    ConcreteFilterStream filterStream(mockStream);
    int result = filterStream.getUnfilteredChar();
    EXPECT_EQ(result, 128);
}

// Test setPos with negative position (if meaningful, e.g., seeking from end)
TEST_F(FilterStreamTest_145, SetPosWithNegativeDir_145) {
    EXPECT_CALL(*mockStream, setPos(50, -1))
        .Times(1);

    ConcreteFilterStream filterStream(mockStream);
    filterStream.setPos(50, -1);
}

// Test getBaseStream returns null
TEST_F(FilterStreamTest_145, GetBaseStreamReturnsNull_145) {
    EXPECT_CALL(*mockStream, getBaseStream())
        .WillOnce(::testing::Return(nullptr));

    ConcreteFilterStream filterStream(mockStream);
    BaseStream* result = filterStream.getBaseStream();
    EXPECT_EQ(result, nullptr);
}

// Test getDict returns null
TEST_F(FilterStreamTest_145, GetDictReturnsNull_145) {
    EXPECT_CALL(*mockStream, getDict())
        .WillOnce(::testing::Return(nullptr));

    ConcreteFilterStream filterStream(mockStream);
    Dict* result = filterStream.getDict();
    EXPECT_EQ(result, nullptr);
}

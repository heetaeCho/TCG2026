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

    // prevent destructor issues
    ~MockStream() override = default;

private:
    MOCK_METHOD(int, getChars, (int nChars, unsigned char* buffer), (override));
    MOCK_METHOD(bool, hasGetChars, (), (override));
};

// We need a concrete subclass of FilterStream since FilterStream may be abstract
// (it doesn't implement getChar, lookChar, etc.). We'll create a minimal concrete version.
class ConcreteFilterStream : public FilterStream {
public:
    explicit ConcreteFilterStream(Stream* strA) : FilterStream(strA) {}
    ~ConcreteFilterStream() override {
        // Don't let FilterStream destructor delete our mock
        str = nullptr;
    }

    StreamKind getKind() const override { return streamKind; }
    int getChar() override { return str ? str->getChar() : EOF; }
    int lookChar() override { return str ? str->lookChar() : EOF; }
    int getRawChar() override { return str ? str->getRawChar() : EOF; }
    bool rewind() override { return str ? str->rewind() : false; }
    bool isBinary(bool last) const override { return false; }

private:
    StreamKind streamKind = strWeird;
};

class FilterStreamTest_139 : public ::testing::Test {
protected:
    void SetUp() override {
        mockStream = new MockStream();
    }

    void TearDown() override {
        delete mockStream;
    }

    MockStream* mockStream;
};

// Test that getPos() delegates to the underlying stream's getPos()
TEST_F(FilterStreamTest_139, GetPosDelegatesToUnderlyingStream_139) {
    EXPECT_CALL(*mockStream, getPos())
        .WillOnce(::testing::Return(42));

    ConcreteFilterStream filterStream(mockStream);
    Goffset pos = filterStream.getPos();
    EXPECT_EQ(pos, 42);
}

// Test that getPos() returns 0 when underlying stream returns 0
TEST_F(FilterStreamTest_139, GetPosReturnsZero_139) {
    EXPECT_CALL(*mockStream, getPos())
        .WillOnce(::testing::Return(0));

    ConcreteFilterStream filterStream(mockStream);
    EXPECT_EQ(filterStream.getPos(), 0);
}

// Test that getPos() handles large offset values
TEST_F(FilterStreamTest_139, GetPosLargeOffset_139) {
    Goffset largePos = 1000000000LL;
    EXPECT_CALL(*mockStream, getPos())
        .WillOnce(::testing::Return(largePos));

    ConcreteFilterStream filterStream(mockStream);
    EXPECT_EQ(filterStream.getPos(), largePos);
}

// Test that getPos() returns negative values if the underlying stream does
TEST_F(FilterStreamTest_139, GetPosNegativeValue_139) {
    EXPECT_CALL(*mockStream, getPos())
        .WillOnce(::testing::Return(-1));

    ConcreteFilterStream filterStream(mockStream);
    EXPECT_EQ(filterStream.getPos(), -1);
}

// Test that close() delegates to the underlying stream
TEST_F(FilterStreamTest_139, CloseDelegatesToUnderlyingStream_139) {
    EXPECT_CALL(*mockStream, close())
        .Times(1);

    ConcreteFilterStream filterStream(mockStream);
    filterStream.close();
}

// Test that setPos() delegates to the underlying stream
TEST_F(FilterStreamTest_139, SetPosDelegatesToUnderlyingStream_139) {
    EXPECT_CALL(*mockStream, setPos(100, 0))
        .Times(1);

    ConcreteFilterStream filterStream(mockStream);
    filterStream.setPos(100, 0);
}

// Test setPos with direction parameter
TEST_F(FilterStreamTest_139, SetPosWithDirection_139) {
    EXPECT_CALL(*mockStream, setPos(0, -1))
        .Times(1);

    ConcreteFilterStream filterStream(mockStream);
    filterStream.setPos(0, -1);
}

// Test that getBaseStream() delegates to the underlying stream
TEST_F(FilterStreamTest_139, GetBaseStreamDelegates_139) {
    BaseStream* fakeBase = reinterpret_cast<BaseStream*>(0xDEADBEEF);
    EXPECT_CALL(*mockStream, getBaseStream())
        .WillOnce(::testing::Return(fakeBase));

    ConcreteFilterStream filterStream(mockStream);
    EXPECT_EQ(filterStream.getBaseStream(), fakeBase);
}

// Test that getUndecodedStream() delegates to the underlying stream
TEST_F(FilterStreamTest_139, GetUndecodedStreamDelegates_139) {
    Stream* fakeStream = reinterpret_cast<Stream*>(0xCAFEBABE);
    EXPECT_CALL(*mockStream, getUndecodedStream())
        .WillOnce(::testing::Return(fakeStream));

    ConcreteFilterStream filterStream(mockStream);
    EXPECT_EQ(filterStream.getUndecodedStream(), fakeStream);
}

// Test that getDict() delegates to the underlying stream
TEST_F(FilterStreamTest_139, GetDictDelegates_139) {
    Dict* fakeDict = reinterpret_cast<Dict*>(0x12345678);
    EXPECT_CALL(*mockStream, getDict())
        .WillOnce(::testing::Return(fakeDict));

    ConcreteFilterStream filterStream(mockStream);
    EXPECT_EQ(filterStream.getDict(), fakeDict);
}

// Test that getDictObject() delegates to the underlying stream
TEST_F(FilterStreamTest_139, GetDictObjectDelegates_139) {
    Object* fakeObj = reinterpret_cast<Object*>(0xABCDEF01);
    EXPECT_CALL(*mockStream, getDictObject())
        .WillOnce(::testing::Return(fakeObj));

    ConcreteFilterStream filterStream(mockStream);
    EXPECT_EQ(filterStream.getDictObject(), fakeObj);
}

// Test that getNextStream() returns the underlying stream
TEST_F(FilterStreamTest_139, GetNextStreamReturnsUnderlyingStream_139) {
    ConcreteFilterStream filterStream(mockStream);
    EXPECT_EQ(filterStream.getNextStream(), mockStream);
}

// Test that getUnfilteredChar() delegates to the underlying stream
TEST_F(FilterStreamTest_139, GetUnfilteredCharDelegates_139) {
    EXPECT_CALL(*mockStream, getUnfilteredChar())
        .WillOnce(::testing::Return(65));

    ConcreteFilterStream filterStream(mockStream);
    EXPECT_EQ(filterStream.getUnfilteredChar(), 65);
}

// Test that getUnfilteredChar() returns EOF when underlying returns EOF
TEST_F(FilterStreamTest_139, GetUnfilteredCharReturnsEOF_139) {
    EXPECT_CALL(*mockStream, getUnfilteredChar())
        .WillOnce(::testing::Return(EOF));

    ConcreteFilterStream filterStream(mockStream);
    EXPECT_EQ(filterStream.getUnfilteredChar(), EOF);
}

// Test that unfilteredRewind() delegates to the underlying stream
TEST_F(FilterStreamTest_139, UnfilteredRewindDelegates_139) {
    EXPECT_CALL(*mockStream, unfilteredRewind())
        .WillOnce(::testing::Return(true));

    ConcreteFilterStream filterStream(mockStream);
    EXPECT_TRUE(filterStream.unfilteredRewind());
}

// Test unfilteredRewind returns false when underlying returns false
TEST_F(FilterStreamTest_139, UnfilteredRewindReturnsFalse_139) {
    EXPECT_CALL(*mockStream, unfilteredRewind())
        .WillOnce(::testing::Return(false));

    ConcreteFilterStream filterStream(mockStream);
    EXPECT_FALSE(filterStream.unfilteredRewind());
}

// Test multiple getPos() calls delegate each time
TEST_F(FilterStreamTest_139, MultipleGetPosCalls_139) {
    EXPECT_CALL(*mockStream, getPos())
        .WillOnce(::testing::Return(0))
        .WillOnce(::testing::Return(100))
        .WillOnce(::testing::Return(200));

    ConcreteFilterStream filterStream(mockStream);
    EXPECT_EQ(filterStream.getPos(), 0);
    EXPECT_EQ(filterStream.getPos(), 100);
    EXPECT_EQ(filterStream.getPos(), 200);
}

// Test getDict returns nullptr when underlying returns nullptr
TEST_F(FilterStreamTest_139, GetDictReturnsNullptr_139) {
    EXPECT_CALL(*mockStream, getDict())
        .WillOnce(::testing::Return(nullptr));

    ConcreteFilterStream filterStream(mockStream);
    EXPECT_EQ(filterStream.getDict(), nullptr);
}

// Test getDictObject returns nullptr when underlying returns nullptr
TEST_F(FilterStreamTest_139, GetDictObjectReturnsNullptr_139) {
    EXPECT_CALL(*mockStream, getDictObject())
        .WillOnce(::testing::Return(nullptr));

    ConcreteFilterStream filterStream(mockStream);
    EXPECT_EQ(filterStream.getDictObject(), nullptr);
}

// Test getBaseStream returns nullptr when underlying returns nullptr
TEST_F(FilterStreamTest_139, GetBaseStreamReturnsNullptr_139) {
    EXPECT_CALL(*mockStream, getBaseStream())
        .WillOnce(::testing::Return(nullptr));

    ConcreteFilterStream filterStream(mockStream);
    EXPECT_EQ(filterStream.getBaseStream(), nullptr);
}

// Test setPos with zero offset and positive direction
TEST_F(FilterStreamTest_139, SetPosZeroOffsetPositiveDir_139) {
    EXPECT_CALL(*mockStream, setPos(0, 1))
        .Times(1);

    ConcreteFilterStream filterStream(mockStream);
    filterStream.setPos(0, 1);
}

// Test very large position value
TEST_F(FilterStreamTest_139, GetPosVeryLargeValue_139) {
    Goffset veryLarge = static_cast<Goffset>(9223372036854775807LL); // max int64
    EXPECT_CALL(*mockStream, getPos())
        .WillOnce(::testing::Return(veryLarge));

    ConcreteFilterStream filterStream(mockStream);
    EXPECT_EQ(filterStream.getPos(), veryLarge);
}

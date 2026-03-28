#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Stream.h"
#include <vector>
#include <climits>

// Mock class that derives from Stream to test doGetChars behavior
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

    // We need to control hasGetChars and getChars behavior
    bool mockHasGetChars = false;
    
    // For the case when hasGetChars returns true
    MOCK_METHOD(int, mockGetChars, (int nChars, unsigned char* buffer));

private:
    bool hasGetChars() override {
        return mockHasGetChars;
    }

    int getChars(int nChars, unsigned char* buffer) override {
        return mockGetChars(nChars, buffer);
    }
};

// Test fixture
class StreamDoGetCharsTest_119 : public ::testing::Test {
protected:
    MockStream stream;
};

// Test: When hasGetChars() is false and all getChar() calls succeed
TEST_F(StreamDoGetCharsTest_119, NormalOperation_NoGetChars_AllCharsAvailable_119) {
    stream.mockHasGetChars = false;
    
    EXPECT_CALL(stream, getChar())
        .Times(5)
        .WillOnce(::testing::Return('A'))
        .WillOnce(::testing::Return('B'))
        .WillOnce(::testing::Return('C'))
        .WillOnce(::testing::Return('D'))
        .WillOnce(::testing::Return('E'));

    unsigned char buffer[5];
    int result = stream.doGetChars(5, buffer);

    EXPECT_EQ(result, 5);
    EXPECT_EQ(buffer[0], 'A');
    EXPECT_EQ(buffer[1], 'B');
    EXPECT_EQ(buffer[2], 'C');
    EXPECT_EQ(buffer[3], 'D');
    EXPECT_EQ(buffer[4], 'E');
}

// Test: When hasGetChars() is false and getChar() returns EOF immediately
TEST_F(StreamDoGetCharsTest_119, NoGetChars_ImmediateEOF_119) {
    stream.mockHasGetChars = false;
    
    EXPECT_CALL(stream, getChar())
        .WillOnce(::testing::Return(EOF));

    unsigned char buffer[5] = {0};
    int result = stream.doGetChars(5, buffer);

    EXPECT_EQ(result, 0);
}

// Test: When hasGetChars() is false and getChar() returns EOF partway through
TEST_F(StreamDoGetCharsTest_119, NoGetChars_PartialRead_119) {
    stream.mockHasGetChars = false;
    
    EXPECT_CALL(stream, getChar())
        .WillOnce(::testing::Return('X'))
        .WillOnce(::testing::Return('Y'))
        .WillOnce(::testing::Return(EOF));

    unsigned char buffer[5] = {0};
    int result = stream.doGetChars(5, buffer);

    EXPECT_EQ(result, 2);
    EXPECT_EQ(buffer[0], 'X');
    EXPECT_EQ(buffer[1], 'Y');
}

// Test: When hasGetChars() is true, delegates to getChars
TEST_F(StreamDoGetCharsTest_119, HasGetChars_DelegatesToGetChars_119) {
    stream.mockHasGetChars = true;
    
    EXPECT_CALL(stream, mockGetChars(5, ::testing::_))
        .WillOnce([](int nChars, unsigned char* buffer) -> int {
            for (int i = 0; i < nChars; i++) {
                buffer[i] = 'A' + i;
            }
            return nChars;
        });

    unsigned char buffer[5] = {0};
    int result = stream.doGetChars(5, buffer);

    EXPECT_EQ(result, 5);
    EXPECT_EQ(buffer[0], 'A');
    EXPECT_EQ(buffer[1], 'B');
    EXPECT_EQ(buffer[2], 'C');
    EXPECT_EQ(buffer[3], 'D');
    EXPECT_EQ(buffer[4], 'E');
}

// Test: When hasGetChars() is true and getChars returns partial
TEST_F(StreamDoGetCharsTest_119, HasGetChars_PartialRead_119) {
    stream.mockHasGetChars = true;
    
    EXPECT_CALL(stream, mockGetChars(10, ::testing::_))
        .WillOnce([](int nChars, unsigned char* buffer) -> int {
            buffer[0] = 'Z';
            buffer[1] = 'Q';
            return 2;
        });

    unsigned char buffer[10] = {0};
    int result = stream.doGetChars(10, buffer);

    EXPECT_EQ(result, 2);
    EXPECT_EQ(buffer[0], 'Z');
    EXPECT_EQ(buffer[1], 'Q');
}

// Test: Zero chars requested, no getChar should be called
TEST_F(StreamDoGetCharsTest_119, ZeroCharsRequested_NoGetChars_119) {
    stream.mockHasGetChars = false;
    
    EXPECT_CALL(stream, getChar()).Times(0);

    unsigned char buffer[1] = {0};
    int result = stream.doGetChars(0, buffer);

    EXPECT_EQ(result, 0);
}

// Test: Zero chars requested with hasGetChars true
TEST_F(StreamDoGetCharsTest_119, ZeroCharsRequested_HasGetChars_119) {
    stream.mockHasGetChars = true;
    
    EXPECT_CALL(stream, mockGetChars(0, ::testing::_))
        .WillOnce(::testing::Return(0));

    unsigned char buffer[1] = {0};
    int result = stream.doGetChars(0, buffer);

    EXPECT_EQ(result, 0);
}

// Test: Single char requested successfully
TEST_F(StreamDoGetCharsTest_119, SingleCharSuccess_119) {
    stream.mockHasGetChars = false;
    
    EXPECT_CALL(stream, getChar())
        .WillOnce(::testing::Return(0x42));

    unsigned char buffer[1] = {0};
    int result = stream.doGetChars(1, buffer);

    EXPECT_EQ(result, 1);
    EXPECT_EQ(buffer[0], 0x42);
}

// Test: Single char requested but EOF
TEST_F(StreamDoGetCharsTest_119, SingleCharEOF_119) {
    stream.mockHasGetChars = false;
    
    EXPECT_CALL(stream, getChar())
        .WillOnce(::testing::Return(EOF));

    unsigned char buffer[1] = {0xFF};
    int result = stream.doGetChars(1, buffer);

    EXPECT_EQ(result, 0);
}

// Test: Binary data (all byte values 0-255) through getChar path
TEST_F(StreamDoGetCharsTest_119, BinaryData_119) {
    stream.mockHasGetChars = false;
    
    EXPECT_CALL(stream, getChar())
        .WillOnce(::testing::Return(0x00))
        .WillOnce(::testing::Return(0xFF))
        .WillOnce(::testing::Return(0x80))
        .WillOnce(::testing::Return(0x7F));

    unsigned char buffer[4] = {0};
    int result = stream.doGetChars(4, buffer);

    EXPECT_EQ(result, 4);
    EXPECT_EQ(buffer[0], 0x00);
    EXPECT_EQ(buffer[1], 0xFF);
    EXPECT_EQ(buffer[2], 0x80);
    EXPECT_EQ(buffer[3], 0x7F);
}

// Test: Large number of chars requested but EOF after a few
TEST_F(StreamDoGetCharsTest_119, LargeRequest_EarlyEOF_119) {
    stream.mockHasGetChars = false;
    
    EXPECT_CALL(stream, getChar())
        .WillOnce(::testing::Return('a'))
        .WillOnce(::testing::Return(EOF));

    unsigned char buffer[1000] = {0};
    int result = stream.doGetChars(1000, buffer);

    EXPECT_EQ(result, 1);
    EXPECT_EQ(buffer[0], 'a');
}

// Test: getChars returns zero when hasGetChars is true
TEST_F(StreamDoGetCharsTest_119, HasGetChars_ReturnsZero_119) {
    stream.mockHasGetChars = true;
    
    EXPECT_CALL(stream, mockGetChars(5, ::testing::_))
        .WillOnce(::testing::Return(0));

    unsigned char buffer[5] = {0};
    int result = stream.doGetChars(5, buffer);

    EXPECT_EQ(result, 0);
}

// Test: Verify getChar is called exactly the right number of times on full read
TEST_F(StreamDoGetCharsTest_119, GetCharCalledExactTimes_119) {
    stream.mockHasGetChars = false;
    
    EXPECT_CALL(stream, getChar())
        .Times(3)
        .WillOnce(::testing::Return(10))
        .WillOnce(::testing::Return(20))
        .WillOnce(::testing::Return(30));

    unsigned char buffer[3] = {0};
    int result = stream.doGetChars(3, buffer);

    EXPECT_EQ(result, 3);
    EXPECT_EQ(buffer[0], 10);
    EXPECT_EQ(buffer[1], 20);
    EXPECT_EQ(buffer[2], 30);
}

// Test: EOF at the last position
TEST_F(StreamDoGetCharsTest_119, EOFAtLastPosition_119) {
    stream.mockHasGetChars = false;
    
    EXPECT_CALL(stream, getChar())
        .WillOnce(::testing::Return('A'))
        .WillOnce(::testing::Return('B'))
        .WillOnce(::testing::Return('C'))
        .WillOnce(::testing::Return(EOF));

    unsigned char buffer[4] = {0};
    int result = stream.doGetChars(4, buffer);

    EXPECT_EQ(result, 3);
    EXPECT_EQ(buffer[0], 'A');
    EXPECT_EQ(buffer[1], 'B');
    EXPECT_EQ(buffer[2], 'C');
}

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Stream.h"

// We need to test the function: static int getCharFromStream(void *data)
// This function is defined in CMap.cc and calls ((Stream *)data)->getChar()
// Since it's a static function in CMap.cc, we need to either include the relevant
// header or declare it externally. We'll declare it as extern if possible,
// or we replicate the function signature for testing purposes.

// The function under test
static int getCharFromStream(void *data) { return ((Stream *)data)->getChar(); }

// Mock Stream class to test getCharFromStream
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
    MOCK_METHOD(bool, isBinary, (bool last), (const, override));
    MOCK_METHOD(BaseStream*, getBaseStream, (), (override));
    MOCK_METHOD(Stream*, getUndecodedStream, (), (override));
    MOCK_METHOD(Dict*, getDict, (), (override));
    MOCK_METHOD(Object*, getDictObject, (), (override));
};

class GetCharFromStreamTest_1506 : public ::testing::Test {
protected:
    MockStream mockStream;
};

// Test normal operation: getCharFromStream returns the value from Stream::getChar()
TEST_F(GetCharFromStreamTest_1506, ReturnsCharFromStream_1506) {
    EXPECT_CALL(mockStream, getChar())
        .WillOnce(::testing::Return(65)); // ASCII 'A'

    int result = getCharFromStream(&mockStream);
    EXPECT_EQ(result, 65);
}

// Test that getCharFromStream returns EOF (-1) when stream is at end
TEST_F(GetCharFromStreamTest_1506, ReturnsEOFWhenStreamEnds_1506) {
    EXPECT_CALL(mockStream, getChar())
        .WillOnce(::testing::Return(-1)); // EOF

    int result = getCharFromStream(&mockStream);
    EXPECT_EQ(result, -1);
}

// Test with zero byte value
TEST_F(GetCharFromStreamTest_1506, ReturnsZeroByte_1506) {
    EXPECT_CALL(mockStream, getChar())
        .WillOnce(::testing::Return(0));

    int result = getCharFromStream(&mockStream);
    EXPECT_EQ(result, 0);
}

// Test with maximum byte value (255)
TEST_F(GetCharFromStreamTest_1506, ReturnsMaxByteValue_1506) {
    EXPECT_CALL(mockStream, getChar())
        .WillOnce(::testing::Return(255));

    int result = getCharFromStream(&mockStream);
    EXPECT_EQ(result, 255);
}

// Test with value 1 (minimum positive byte)
TEST_F(GetCharFromStreamTest_1506, ReturnsMinPositiveByte_1506) {
    EXPECT_CALL(mockStream, getChar())
        .WillOnce(::testing::Return(1));

    int result = getCharFromStream(&mockStream);
    EXPECT_EQ(result, 1);
}

// Test with value 127 (max signed byte)
TEST_F(GetCharFromStreamTest_1506, ReturnsMaxSignedByte_1506) {
    EXPECT_CALL(mockStream, getChar())
        .WillOnce(::testing::Return(127));

    int result = getCharFromStream(&mockStream);
    EXPECT_EQ(result, 127);
}

// Test with value 128 (first value beyond signed byte range)
TEST_F(GetCharFromStreamTest_1506, ReturnsBeyondSignedByteRange_1506) {
    EXPECT_CALL(mockStream, getChar())
        .WillOnce(::testing::Return(128));

    int result = getCharFromStream(&mockStream);
    EXPECT_EQ(result, 128);
}

// Test multiple consecutive calls
TEST_F(GetCharFromStreamTest_1506, MultipleConsecutiveCalls_1506) {
    EXPECT_CALL(mockStream, getChar())
        .WillOnce(::testing::Return(72))   // 'H'
        .WillOnce(::testing::Return(101))  // 'e'
        .WillOnce(::testing::Return(108))  // 'l'
        .WillOnce(::testing::Return(-1));  // EOF

    EXPECT_EQ(getCharFromStream(&mockStream), 72);
    EXPECT_EQ(getCharFromStream(&mockStream), 101);
    EXPECT_EQ(getCharFromStream(&mockStream), 108);
    EXPECT_EQ(getCharFromStream(&mockStream), -1);
}

// Test that getChar is called exactly once per invocation
TEST_F(GetCharFromStreamTest_1506, CallsGetCharExactlyOnce_1506) {
    EXPECT_CALL(mockStream, getChar())
        .Times(1)
        .WillOnce(::testing::Return(42));

    getCharFromStream(&mockStream);
}

// Test with a different negative value (some implementations may return other negative values)
TEST_F(GetCharFromStreamTest_1506, ReturnsNegativeValue_1506) {
    EXPECT_CALL(mockStream, getChar())
        .WillOnce(::testing::Return(-2));

    int result = getCharFromStream(&mockStream);
    EXPECT_EQ(result, -2);
}

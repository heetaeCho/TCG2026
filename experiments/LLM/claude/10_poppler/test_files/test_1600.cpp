#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Stream.h"

// We need to access the static function aesReadBlock from Decrypt.cc
// Since it's file-static, we include the cc file to bring it into this translation unit.
// This is a common technique for testing static functions.

// First, create a mock Stream class
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

// Include the implementation to get access to the static function
// We need to forward-declare or handle dependencies of Decrypt.cc
#include "Decrypt.cc"

using ::testing::Return;
using ::testing::InSequence;

class AesReadBlockTest_1600 : public ::testing::Test {
protected:
    MockStream mockStream;
    unsigned char buffer[16];

    void SetUp() override {
        memset(buffer, 0, sizeof(buffer));
    }
};

// Test: Full 16 bytes read successfully, returns true
TEST_F(AesReadBlockTest_1600, FullBlockRead_ReturnsTrue_1600) {
    InSequence seq;
    for (int i = 0; i < 16; ++i) {
        EXPECT_CALL(mockStream, getChar()).WillOnce(Return(i));
    }

    bool result = aesReadBlock(&mockStream, buffer, false);

    EXPECT_TRUE(result);
    for (int i = 0; i < 16; ++i) {
        EXPECT_EQ(buffer[i], static_cast<unsigned char>(i));
    }
}

// Test: Empty stream (EOF immediately), no padding, returns false
TEST_F(AesReadBlockTest_1600, EmptyStreamNoPadding_ReturnsFalse_1600) {
    EXPECT_CALL(mockStream, getChar()).WillRepeatedly(Return(EOF));

    bool result = aesReadBlock(&mockStream, buffer, false);

    EXPECT_FALSE(result);
}

// Test: Empty stream with padding, buffer filled with 16s
TEST_F(AesReadBlockTest_1600, EmptyStreamWithPadding_PadsEntireBlock_1600) {
    EXPECT_CALL(mockStream, getChar()).WillRepeatedly(Return(EOF));

    bool result = aesReadBlock(&mockStream, buffer, true);

    EXPECT_FALSE(result);
    for (int i = 0; i < 16; ++i) {
        EXPECT_EQ(buffer[i], 16);
    }
}

// Test: Partial read (5 bytes) with padding
TEST_F(AesReadBlockTest_1600, PartialReadWithPadding_1600) {
    InSequence seq;
    for (int i = 0; i < 5; ++i) {
        EXPECT_CALL(mockStream, getChar()).WillOnce(Return(0xAA));
    }
    EXPECT_CALL(mockStream, getChar()).WillRepeatedly(Return(EOF));

    bool result = aesReadBlock(&mockStream, buffer, true);

    EXPECT_FALSE(result);
    for (int i = 0; i < 5; ++i) {
        EXPECT_EQ(buffer[i], 0xAA);
    }
    // Padding value should be 16 - 5 = 11
    for (int i = 5; i < 16; ++i) {
        EXPECT_EQ(buffer[i], 11);
    }
}

// Test: Partial read (5 bytes) without padding, returns false
TEST_F(AesReadBlockTest_1600, PartialReadNoPadding_ReturnsFalse_1600) {
    InSequence seq;
    for (int i = 0; i < 5; ++i) {
        EXPECT_CALL(mockStream, getChar()).WillOnce(Return(0x42));
    }
    EXPECT_CALL(mockStream, getChar()).WillRepeatedly(Return(EOF));

    bool result = aesReadBlock(&mockStream, buffer, false);

    EXPECT_FALSE(result);
    // First 5 bytes should be set
    for (int i = 0; i < 5; ++i) {
        EXPECT_EQ(buffer[i], 0x42);
    }
}

// Test: 15 bytes read with padding (boundary: one byte short)
TEST_F(AesReadBlockTest_1600, FifteenBytesWithPadding_1600) {
    InSequence seq;
    for (int i = 0; i < 15; ++i) {
        EXPECT_CALL(mockStream, getChar()).WillOnce(Return(i + 1));
    }
    EXPECT_CALL(mockStream, getChar()).WillOnce(Return(EOF));

    bool result = aesReadBlock(&mockStream, buffer, true);

    EXPECT_FALSE(result);
    for (int i = 0; i < 15; ++i) {
        EXPECT_EQ(buffer[i], static_cast<unsigned char>(i + 1));
    }
    // Padding: 16 - 15 = 1
    EXPECT_EQ(buffer[15], 1);
}

// Test: 1 byte read with padding
TEST_F(AesReadBlockTest_1600, OneByteWithPadding_1600) {
    InSequence seq;
    EXPECT_CALL(mockStream, getChar()).WillOnce(Return(0xFF));
    EXPECT_CALL(mockStream, getChar()).WillRepeatedly(Return(EOF));

    bool result = aesReadBlock(&mockStream, buffer, true);

    EXPECT_FALSE(result);
    EXPECT_EQ(buffer[0], 0xFF);
    // Padding: 16 - 1 = 15
    for (int i = 1; i < 16; ++i) {
        EXPECT_EQ(buffer[i], 15);
    }
}

// Test: Full block with all zeros
TEST_F(AesReadBlockTest_1600, FullBlockAllZeros_1600) {
    EXPECT_CALL(mockStream, getChar()).Times(16).WillRepeatedly(Return(0));

    bool result = aesReadBlock(&mockStream, buffer, false);

    EXPECT_TRUE(result);
    for (int i = 0; i < 16; ++i) {
        EXPECT_EQ(buffer[i], 0);
    }
}

// Test: Full block with all 0xFF
TEST_F(AesReadBlockTest_1600, FullBlockAllFF_1600) {
    EXPECT_CALL(mockStream, getChar()).Times(16).WillRepeatedly(Return(0xFF));

    bool result = aesReadBlock(&mockStream, buffer, true);

    EXPECT_TRUE(result);
    for (int i = 0; i < 16; ++i) {
        EXPECT_EQ(buffer[i], 0xFF);
    }
}

// Test: Full block read - addPadding flag should not matter when 16 bytes available
TEST_F(AesReadBlockTest_1600, FullBlockWithPaddingFlag_StillReturnsTrue_1600) {
    InSequence seq;
    for (int i = 0; i < 16; ++i) {
        EXPECT_CALL(mockStream, getChar()).WillOnce(Return(i * 2));
    }

    bool result = aesReadBlock(&mockStream, buffer, true);

    EXPECT_TRUE(result);
    for (int i = 0; i < 16; ++i) {
        EXPECT_EQ(buffer[i], static_cast<unsigned char>(i * 2));
    }
}

// Test: 8 bytes (half block) with padding
TEST_F(AesReadBlockTest_1600, HalfBlockWithPadding_1600) {
    InSequence seq;
    for (int i = 0; i < 8; ++i) {
        EXPECT_CALL(mockStream, getChar()).WillOnce(Return(0x30 + i));
    }
    EXPECT_CALL(mockStream, getChar()).WillRepeatedly(Return(EOF));

    bool result = aesReadBlock(&mockStream, buffer, true);

    EXPECT_FALSE(result);
    for (int i = 0; i < 8; ++i) {
        EXPECT_EQ(buffer[i], static_cast<unsigned char>(0x30 + i));
    }
    // Padding: 16 - 8 = 8
    for (int i = 8; i < 16; ++i) {
        EXPECT_EQ(buffer[i], 8);
    }
}

// Test: 15 bytes without padding
TEST_F(AesReadBlockTest_1600, FifteenBytesNoPadding_ReturnsFalse_1600) {
    InSequence seq;
    for (int i = 0; i < 15; ++i) {
        EXPECT_CALL(mockStream, getChar()).WillOnce(Return(0xBB));
    }
    EXPECT_CALL(mockStream, getChar()).WillOnce(Return(EOF));

    bool result = aesReadBlock(&mockStream, buffer, false);

    EXPECT_FALSE(result);
    for (int i = 0; i < 15; ++i) {
        EXPECT_EQ(buffer[i], 0xBB);
    }
}

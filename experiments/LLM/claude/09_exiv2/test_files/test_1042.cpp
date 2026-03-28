#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <exiv2/basicio.hpp>
#include <exiv2/bmpimage.hpp>
#include <array>
#include <cstring>

using namespace Exiv2;

// Mock class for BasicIo
class MockBasicIo : public BasicIo {
public:
    MOCK_METHOD(int, open, (), (override));
    MOCK_METHOD(int, close, (), (override));
    MOCK_METHOD(size_t, write, (const byte* data, size_t wcount), (override));
    MOCK_METHOD(size_t, write, (BasicIo& src), (override));
    MOCK_METHOD(int, putb, (byte data), (override));
    MOCK_METHOD(DataBuf, read, (size_t rcount), (override));
    MOCK_METHOD(size_t, read, (byte* buf, size_t rcount), (override));
    MOCK_METHOD(int, getb, (), (override));
    MOCK_METHOD(void, transfer, (BasicIo& src), (override));
    MOCK_METHOD(int, seek, (int64_t offset, Position pos), (override));
    MOCK_METHOD(byte*, mmap, (bool isWriteable), (override));
    MOCK_METHOD(int, munmap, (), (override));
    MOCK_METHOD(const size_t, tell, (), (const, override));
    MOCK_METHOD(const size_t, size, (), (const, override));
    MOCK_METHOD(const bool, isopen, (), (const, override));
    MOCK_METHOD(const int, error, (), (const, override));
    MOCK_METHOD(const bool, eof, (), (const, override));
    MOCK_METHOD(const std::string&, path, (), (const, override));
    MOCK_METHOD(void, populateFakeData, (), (override));
};

class IsBmpTypeTest_1042 : public ::testing::Test {
protected:
    MockBasicIo mockIo;
};

// Test: Valid BMP header with advance=true should return true and NOT seek back
TEST_F(IsBmpTypeTest_1042, ValidBmpHeaderAdvanceTrue_1042) {
    EXPECT_CALL(mockIo, read(::testing::_, 2))
        .WillOnce(::testing::Invoke([](byte* buf, size_t /*rcount*/) -> size_t {
            buf[0] = 'B';
            buf[1] = 'M';
            return 2;
        }));
    EXPECT_CALL(mockIo, error()).WillOnce(::testing::Return(0));
    EXPECT_CALL(mockIo, eof()).WillOnce(::testing::Return(false));
    // When advance is true and matched, seek should NOT be called
    EXPECT_CALL(mockIo, seek(::testing::_, ::testing::_)).Times(0);

    bool result = isBmpType(mockIo, true);
    EXPECT_TRUE(result);
}

// Test: Valid BMP header with advance=false should return true and seek back
TEST_F(IsBmpTypeTest_1042, ValidBmpHeaderAdvanceFalse_1042) {
    EXPECT_CALL(mockIo, read(::testing::_, 2))
        .WillOnce(::testing::Invoke([](byte* buf, size_t /*rcount*/) -> size_t {
            buf[0] = 'B';
            buf[1] = 'M';
            return 2;
        }));
    EXPECT_CALL(mockIo, error()).WillOnce(::testing::Return(0));
    EXPECT_CALL(mockIo, eof()).WillOnce(::testing::Return(false));
    // When advance is false, even if matched, seek back should be called
    EXPECT_CALL(mockIo, seek(-2, BasicIo::cur)).WillOnce(::testing::Return(0));

    bool result = isBmpType(mockIo, false);
    EXPECT_TRUE(result);
}

// Test: Invalid header with advance=true should return false and seek back
TEST_F(IsBmpTypeTest_1042, InvalidHeaderAdvanceTrue_1042) {
    EXPECT_CALL(mockIo, read(::testing::_, 2))
        .WillOnce(::testing::Invoke([](byte* buf, size_t /*rcount*/) -> size_t {
            buf[0] = 'P';
            buf[1] = 'N';
            return 2;
        }));
    EXPECT_CALL(mockIo, error()).WillOnce(::testing::Return(0));
    EXPECT_CALL(mockIo, eof()).WillOnce(::testing::Return(false));
    // Not matched, so seek back should be called
    EXPECT_CALL(mockIo, seek(-2, BasicIo::cur)).WillOnce(::testing::Return(0));

    bool result = isBmpType(mockIo, true);
    EXPECT_FALSE(result);
}

// Test: Invalid header with advance=false should return false and seek back
TEST_F(IsBmpTypeTest_1042, InvalidHeaderAdvanceFalse_1042) {
    EXPECT_CALL(mockIo, read(::testing::_, 2))
        .WillOnce(::testing::Invoke([](byte* buf, size_t /*rcount*/) -> size_t {
            buf[0] = 'X';
            buf[1] = 'Y';
            return 2;
        }));
    EXPECT_CALL(mockIo, error()).WillOnce(::testing::Return(0));
    EXPECT_CALL(mockIo, eof()).WillOnce(::testing::Return(false));
    EXPECT_CALL(mockIo, seek(-2, BasicIo::cur)).WillOnce(::testing::Return(0));

    bool result = isBmpType(mockIo, false);
    EXPECT_FALSE(result);
}

// Test: Read error should return false
TEST_F(IsBmpTypeTest_1042, ReadErrorReturnsFalse_1042) {
    EXPECT_CALL(mockIo, read(::testing::_, 2))
        .WillOnce(::testing::Invoke([](byte* buf, size_t /*rcount*/) -> size_t {
            buf[0] = 'B';
            buf[1] = 'M';
            return 2;
        }));
    EXPECT_CALL(mockIo, error()).WillOnce(::testing::Return(1));  // error occurred

    bool result = isBmpType(mockIo, true);
    EXPECT_FALSE(result);
}

// Test: EOF condition should return false
TEST_F(IsBmpTypeTest_1042, EofReturnsFalse_1042) {
    EXPECT_CALL(mockIo, read(::testing::_, 2))
        .WillOnce(::testing::Invoke([](byte* buf, size_t /*rcount*/) -> size_t {
            buf[0] = 0;
            buf[1] = 0;
            return 0;
        }));
    EXPECT_CALL(mockIo, error()).WillOnce(::testing::Return(0));
    EXPECT_CALL(mockIo, eof()).WillOnce(::testing::Return(true));

    bool result = isBmpType(mockIo, true);
    EXPECT_FALSE(result);
}

// Test: First byte matches but second doesn't - should return false
TEST_F(IsBmpTypeTest_1042, PartialMatchFirstByteOnly_1042) {
    EXPECT_CALL(mockIo, read(::testing::_, 2))
        .WillOnce(::testing::Invoke([](byte* buf, size_t /*rcount*/) -> size_t {
            buf[0] = 'B';
            buf[1] = 'X';
            return 2;
        }));
    EXPECT_CALL(mockIo, error()).WillOnce(::testing::Return(0));
    EXPECT_CALL(mockIo, eof()).WillOnce(::testing::Return(false));
    EXPECT_CALL(mockIo, seek(-2, BasicIo::cur)).WillOnce(::testing::Return(0));

    bool result = isBmpType(mockIo, true);
    EXPECT_FALSE(result);
}

// Test: Second byte matches but first doesn't - should return false
TEST_F(IsBmpTypeTest_1042, PartialMatchSecondByteOnly_1042) {
    EXPECT_CALL(mockIo, read(::testing::_, 2))
        .WillOnce(::testing::Invoke([](byte* buf, size_t /*rcount*/) -> size_t {
            buf[0] = 'X';
            buf[1] = 'M';
            return 2;
        }));
    EXPECT_CALL(mockIo, error()).WillOnce(::testing::Return(0));
    EXPECT_CALL(mockIo, eof()).WillOnce(::testing::Return(false));
    EXPECT_CALL(mockIo, seek(-2, BasicIo::cur)).WillOnce(::testing::Return(0));

    bool result = isBmpType(mockIo, true);
    EXPECT_FALSE(result);
}

// Test: Null bytes should return false
TEST_F(IsBmpTypeTest_1042, NullBytesReturnFalse_1042) {
    EXPECT_CALL(mockIo, read(::testing::_, 2))
        .WillOnce(::testing::Invoke([](byte* buf, size_t /*rcount*/) -> size_t {
            buf[0] = 0;
            buf[1] = 0;
            return 2;
        }));
    EXPECT_CALL(mockIo, error()).WillOnce(::testing::Return(0));
    EXPECT_CALL(mockIo, eof()).WillOnce(::testing::Return(false));
    EXPECT_CALL(mockIo, seek(-2, BasicIo::cur)).WillOnce(::testing::Return(0));

    bool result = isBmpType(mockIo, true);
    EXPECT_FALSE(result);
}

// Test: Both error and eof true should return false
TEST_F(IsBmpTypeTest_1042, BothErrorAndEofReturnFalse_1042) {
    EXPECT_CALL(mockIo, read(::testing::_, 2))
        .WillOnce(::testing::Invoke([](byte* buf, size_t /*rcount*/) -> size_t {
            buf[0] = 'B';
            buf[1] = 'M';
            return 1;
        }));
    EXPECT_CALL(mockIo, error()).WillOnce(::testing::Return(1));

    bool result = isBmpType(mockIo, true);
    EXPECT_FALSE(result);
}

// Test: Lowercase 'b' and 'm' should not match
TEST_F(IsBmpTypeTest_1042, LowercaseBmNotMatched_1042) {
    EXPECT_CALL(mockIo, read(::testing::_, 2))
        .WillOnce(::testing::Invoke([](byte* buf, size_t /*rcount*/) -> size_t {
            buf[0] = 'b';
            buf[1] = 'm';
            return 2;
        }));
    EXPECT_CALL(mockIo, error()).WillOnce(::testing::Return(0));
    EXPECT_CALL(mockIo, eof()).WillOnce(::testing::Return(false));
    EXPECT_CALL(mockIo, seek(-2, BasicIo::cur)).WillOnce(::testing::Return(0));

    bool result = isBmpType(mockIo, true);
    EXPECT_FALSE(result);
}

// Test using MemIo for integration-level validation with valid BMP data
TEST(IsBmpTypeMemIoTest_1042, ValidBmpWithMemIoAdvanceTrue_1042) {
    byte data[] = {'B', 'M', 0x00, 0x00};
    MemIo memIo(data, sizeof(data));

    bool result = isBmpType(memIo, true);
    EXPECT_TRUE(result);
    // After advance=true and match, position should be after the 2-byte header
    EXPECT_EQ(memIo.tell(), 2u);
}

TEST(IsBmpTypeMemIoTest_1042, ValidBmpWithMemIoAdvanceFalse_1042) {
    byte data[] = {'B', 'M', 0x00, 0x00};
    MemIo memIo(data, sizeof(data));

    bool result = isBmpType(memIo, false);
    EXPECT_TRUE(result);
    // After advance=false, position should be back to start
    EXPECT_EQ(memIo.tell(), 0u);
}

TEST(IsBmpTypeMemIoTest_1042, InvalidDataWithMemIoAdvanceTrue_1042) {
    byte data[] = {'P', 'N', 'G', 0x00};
    MemIo memIo(data, sizeof(data));

    bool result = isBmpType(memIo, true);
    EXPECT_FALSE(result);
    // After not matched, position should be back to start
    EXPECT_EQ(memIo.tell(), 0u);
}

TEST(IsBmpTypeMemIoTest_1042, EmptyMemIoReturnsFalse_1042) {
    MemIo memIo;

    bool result = isBmpType(memIo, true);
    EXPECT_FALSE(result);
}

TEST(IsBmpTypeMemIoTest_1042, SingleByteMemIoReturnsFalse_1042) {
    byte data[] = {'B'};
    MemIo memIo(data, sizeof(data));

    bool result = isBmpType(memIo, true);
    EXPECT_FALSE(result);
}

TEST(IsBmpTypeMemIoTest_1042, ExactTwoBytesValidBmp_1042) {
    byte data[] = {'B', 'M'};
    MemIo memIo(data, sizeof(data));

    bool result = isBmpType(memIo, true);
    EXPECT_TRUE(result);
    EXPECT_EQ(memIo.tell(), 2u);
}

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <exiv2/basicio.hpp>
#include <exiv2/mrwimage.hpp>
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
    MOCK_METHOD(const size_t, tell, (), (override));
    MOCK_METHOD(const size_t, size, (), (override));
    MOCK_METHOD(const bool, isopen, (), (override));
    MOCK_METHOD(const int, error, (), (override));
    MOCK_METHOD(const bool, eof, (), (override));
    MOCK_METHOD(const std::string&, path, (), (override));
    MOCK_METHOD(void, populateFakeData, (), (override));
};

class IsMrwTypeTest_984 : public ::testing::Test {
protected:
    MockBasicIo mockIo;
    const std::array<byte, 4> validMrwHeader = {0x00, 0x4d, 0x52, 0x4d};
};

// Test: Valid MRW header with advance=true should return true and NOT seek back
TEST_F(IsMrwTypeTest_984, ValidMrwHeaderAdvanceTrue_984) {
    EXPECT_CALL(mockIo, read(::testing::_, 4))
        .WillOnce([this](byte* buf, size_t rcount) -> size_t {
            std::memcpy(buf, validMrwHeader.data(), 4);
            return 4;
        });
    EXPECT_CALL(mockIo, error()).WillRepeatedly(::testing::Return(0));
    EXPECT_CALL(mockIo, eof()).WillRepeatedly(::testing::Return(false));
    // Should NOT seek back when advance is true and header is valid
    EXPECT_CALL(mockIo, seek(::testing::_, ::testing::_)).Times(0);

    bool result = isMrwType(mockIo, true);
    EXPECT_TRUE(result);
}

// Test: Valid MRW header with advance=false should return true and seek back
TEST_F(IsMrwTypeTest_984, ValidMrwHeaderAdvanceFalse_984) {
    EXPECT_CALL(mockIo, read(::testing::_, 4))
        .WillOnce([this](byte* buf, size_t rcount) -> size_t {
            std::memcpy(buf, validMrwHeader.data(), 4);
            return 4;
        });
    EXPECT_CALL(mockIo, error()).WillRepeatedly(::testing::Return(0));
    EXPECT_CALL(mockIo, eof()).WillRepeatedly(::testing::Return(false));
    // Should seek back when advance is false
    EXPECT_CALL(mockIo, seek(-4, BasicIo::cur)).WillOnce(::testing::Return(0));

    bool result = isMrwType(mockIo, false);
    EXPECT_TRUE(result);
}

// Test: Invalid header with advance=true should return false and seek back
TEST_F(IsMrwTypeTest_984, InvalidHeaderAdvanceTrue_984) {
    const std::array<byte, 4> invalidHeader = {0x00, 0x00, 0x00, 0x00};
    EXPECT_CALL(mockIo, read(::testing::_, 4))
        .WillOnce([&invalidHeader](byte* buf, size_t rcount) -> size_t {
            std::memcpy(buf, invalidHeader.data(), 4);
            return 4;
        });
    EXPECT_CALL(mockIo, error()).WillRepeatedly(::testing::Return(0));
    EXPECT_CALL(mockIo, eof()).WillRepeatedly(::testing::Return(false));
    // Should seek back since result is false
    EXPECT_CALL(mockIo, seek(-4, BasicIo::cur)).WillOnce(::testing::Return(0));

    bool result = isMrwType(mockIo, true);
    EXPECT_FALSE(result);
}

// Test: Invalid header with advance=false should return false and seek back
TEST_F(IsMrwTypeTest_984, InvalidHeaderAdvanceFalse_984) {
    const std::array<byte, 4> invalidHeader = {0xFF, 0xFF, 0xFF, 0xFF};
    EXPECT_CALL(mockIo, read(::testing::_, 4))
        .WillOnce([&invalidHeader](byte* buf, size_t rcount) -> size_t {
            std::memcpy(buf, invalidHeader.data(), 4);
            return 4;
        });
    EXPECT_CALL(mockIo, error()).WillRepeatedly(::testing::Return(0));
    EXPECT_CALL(mockIo, eof()).WillRepeatedly(::testing::Return(false));
    EXPECT_CALL(mockIo, seek(-4, BasicIo::cur)).WillOnce(::testing::Return(0));

    bool result = isMrwType(mockIo, false);
    EXPECT_FALSE(result);
}

// Test: Read error should return false
TEST_F(IsMrwTypeTest_984, ReadErrorReturnsFalse_984) {
    EXPECT_CALL(mockIo, read(::testing::_, 4))
        .WillOnce([](byte* buf, size_t rcount) -> size_t {
            return 0;
        });
    EXPECT_CALL(mockIo, error()).WillRepeatedly(::testing::Return(1));
    EXPECT_CALL(mockIo, eof()).WillRepeatedly(::testing::Return(false));

    bool result = isMrwType(mockIo, true);
    EXPECT_FALSE(result);
}

// Test: EOF during read should return false
TEST_F(IsMrwTypeTest_984, EofDuringReadReturnsFalse_984) {
    EXPECT_CALL(mockIo, read(::testing::_, 4))
        .WillOnce([](byte* buf, size_t rcount) -> size_t {
            return 2; // partial read
        });
    EXPECT_CALL(mockIo, error()).WillRepeatedly(::testing::Return(0));
    EXPECT_CALL(mockIo, eof()).WillRepeatedly(::testing::Return(true));

    bool result = isMrwType(mockIo, true);
    EXPECT_FALSE(result);
}

// Test: Header that differs by one byte should return false
TEST_F(IsMrwTypeTest_984, HeaderDiffersByOneByte_984) {
    // Change last byte from 0x4d to 0x4e
    const std::array<byte, 4> almostValidHeader = {0x00, 0x4d, 0x52, 0x4e};
    EXPECT_CALL(mockIo, read(::testing::_, 4))
        .WillOnce([&almostValidHeader](byte* buf, size_t rcount) -> size_t {
            std::memcpy(buf, almostValidHeader.data(), 4);
            return 4;
        });
    EXPECT_CALL(mockIo, error()).WillRepeatedly(::testing::Return(0));
    EXPECT_CALL(mockIo, eof()).WillRepeatedly(::testing::Return(false));
    EXPECT_CALL(mockIo, seek(-4, BasicIo::cur)).WillOnce(::testing::Return(0));

    bool result = isMrwType(mockIo, true);
    EXPECT_FALSE(result);
}

// Test: Header differs in first byte
TEST_F(IsMrwTypeTest_984, HeaderDiffersFirstByte_984) {
    const std::array<byte, 4> badFirstByte = {0x01, 0x4d, 0x52, 0x4d};
    EXPECT_CALL(mockIo, read(::testing::_, 4))
        .WillOnce([&badFirstByte](byte* buf, size_t rcount) -> size_t {
            std::memcpy(buf, badFirstByte.data(), 4);
            return 4;
        });
    EXPECT_CALL(mockIo, error()).WillRepeatedly(::testing::Return(0));
    EXPECT_CALL(mockIo, eof()).WillRepeatedly(::testing::Return(false));
    EXPECT_CALL(mockIo, seek(-4, BasicIo::cur)).WillOnce(::testing::Return(0));

    bool result = isMrwType(mockIo, false);
    EXPECT_FALSE(result);
}

// Test: Both error and eof set should return false
TEST_F(IsMrwTypeTest_984, BothErrorAndEofReturnsFalse_984) {
    EXPECT_CALL(mockIo, read(::testing::_, 4))
        .WillOnce([](byte* buf, size_t rcount) -> size_t {
            return 0;
        });
    EXPECT_CALL(mockIo, error()).WillRepeatedly(::testing::Return(1));
    EXPECT_CALL(mockIo, eof()).WillRepeatedly(::testing::Return(true));

    bool result = isMrwType(mockIo, false);
    EXPECT_FALSE(result);
}

// Test: JPEG header should not match MRW
TEST_F(IsMrwTypeTest_984, JpegHeaderDoesNotMatchMrw_984) {
    const std::array<byte, 4> jpegHeader = {0xFF, 0xD8, 0xFF, 0xE0};
    EXPECT_CALL(mockIo, read(::testing::_, 4))
        .WillOnce([&jpegHeader](byte* buf, size_t rcount) -> size_t {
            std::memcpy(buf, jpegHeader.data(), 4);
            return 4;
        });
    EXPECT_CALL(mockIo, error()).WillRepeatedly(::testing::Return(0));
    EXPECT_CALL(mockIo, eof()).WillRepeatedly(::testing::Return(false));
    EXPECT_CALL(mockIo, seek(-4, BasicIo::cur)).WillOnce(::testing::Return(0));

    bool result = isMrwType(mockIo, true);
    EXPECT_FALSE(result);
}

// Test: All zeros header should return false (first byte matches but others don't)
TEST_F(IsMrwTypeTest_984, AllZerosHeader_984) {
    const std::array<byte, 4> zeros = {0x00, 0x00, 0x00, 0x00};
    EXPECT_CALL(mockIo, read(::testing::_, 4))
        .WillOnce([&zeros](byte* buf, size_t rcount) -> size_t {
            std::memcpy(buf, zeros.data(), 4);
            return 4;
        });
    EXPECT_CALL(mockIo, error()).WillRepeatedly(::testing::Return(0));
    EXPECT_CALL(mockIo, eof()).WillRepeatedly(::testing::Return(false));
    EXPECT_CALL(mockIo, seek(-4, BasicIo::cur)).WillOnce(::testing::Return(0));

    bool result = isMrwType(mockIo, true);
    EXPECT_FALSE(result);
}

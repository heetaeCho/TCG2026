#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <exiv2/basicio.hpp>
#include <exiv2/psdimage.hpp>
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

class IsPsdTypeTest_1189 : public ::testing::Test {
protected:
    MockBasicIo mockIo;
};

// Test: Valid PSD header with advance=true returns true and does NOT seek back
TEST_F(IsPsdTypeTest_1189, ValidPsdHeaderAdvanceTrue_1189) {
    const std::array<byte, 6> psdHeader{'8', 'B', 'P', 'S', 0, 1};

    EXPECT_CALL(mockIo, read(::testing::_, 6))
        .WillOnce([&psdHeader](byte* buf, size_t rcount) -> size_t {
            std::memcpy(buf, psdHeader.data(), 6);
            return 6;
        });
    EXPECT_CALL(mockIo, error()).WillRepeatedly(::testing::Return(0));
    EXPECT_CALL(mockIo, eof()).WillRepeatedly(::testing::Return(false));
    // Should NOT seek back when advance=true and matched
    EXPECT_CALL(mockIo, seek(::testing::_, ::testing::_)).Times(0);

    bool result = isPsdType(mockIo, true);
    EXPECT_TRUE(result);
}

// Test: Valid PSD header with advance=false returns true and seeks back
TEST_F(IsPsdTypeTest_1189, ValidPsdHeaderAdvanceFalse_1189) {
    const std::array<byte, 6> psdHeader{'8', 'B', 'P', 'S', 0, 1};

    EXPECT_CALL(mockIo, read(::testing::_, 6))
        .WillOnce([&psdHeader](byte* buf, size_t rcount) -> size_t {
            std::memcpy(buf, psdHeader.data(), 6);
            return 6;
        });
    EXPECT_CALL(mockIo, error()).WillRepeatedly(::testing::Return(0));
    EXPECT_CALL(mockIo, eof()).WillRepeatedly(::testing::Return(false));
    // Should seek back when advance=false even if matched
    EXPECT_CALL(mockIo, seek(-6, BasicIo::cur)).WillOnce(::testing::Return(0));

    bool result = isPsdType(mockIo, false);
    EXPECT_TRUE(result);
}

// Test: Invalid header with advance=true returns false and seeks back
TEST_F(IsPsdTypeTest_1189, InvalidHeaderAdvanceTrue_1189) {
    const std::array<byte, 6> invalidHeader{'X', 'Y', 'Z', 'W', 0, 0};

    EXPECT_CALL(mockIo, read(::testing::_, 6))
        .WillOnce([&invalidHeader](byte* buf, size_t rcount) -> size_t {
            std::memcpy(buf, invalidHeader.data(), 6);
            return 6;
        });
    EXPECT_CALL(mockIo, error()).WillRepeatedly(::testing::Return(0));
    EXPECT_CALL(mockIo, eof()).WillRepeatedly(::testing::Return(false));
    // Should seek back when not matched
    EXPECT_CALL(mockIo, seek(-6, BasicIo::cur)).WillOnce(::testing::Return(0));

    bool result = isPsdType(mockIo, true);
    EXPECT_FALSE(result);
}

// Test: Invalid header with advance=false returns false and seeks back
TEST_F(IsPsdTypeTest_1189, InvalidHeaderAdvanceFalse_1189) {
    const std::array<byte, 6> invalidHeader{'A', 'B', 'C', 'D', 'E', 'F'};

    EXPECT_CALL(mockIo, read(::testing::_, 6))
        .WillOnce([&invalidHeader](byte* buf, size_t rcount) -> size_t {
            std::memcpy(buf, invalidHeader.data(), 6);
            return 6;
        });
    EXPECT_CALL(mockIo, error()).WillRepeatedly(::testing::Return(0));
    EXPECT_CALL(mockIo, eof()).WillRepeatedly(::testing::Return(false));
    EXPECT_CALL(mockIo, seek(-6, BasicIo::cur)).WillOnce(::testing::Return(0));

    bool result = isPsdType(mockIo, false);
    EXPECT_FALSE(result);
}

// Test: IO error returns false
TEST_F(IsPsdTypeTest_1189, IoErrorReturnsFalse_1189) {
    EXPECT_CALL(mockIo, read(::testing::_, 6))
        .WillOnce([](byte* buf, size_t rcount) -> size_t {
            return 0;
        });
    EXPECT_CALL(mockIo, error()).WillRepeatedly(::testing::Return(1));
    EXPECT_CALL(mockIo, eof()).WillRepeatedly(::testing::Return(false));

    bool result = isPsdType(mockIo, true);
    EXPECT_FALSE(result);
}

// Test: EOF returns false
TEST_F(IsPsdTypeTest_1189, EofReturnsFalse_1189) {
    EXPECT_CALL(mockIo, read(::testing::_, 6))
        .WillOnce([](byte* buf, size_t rcount) -> size_t {
            return 3; // partial read
        });
    EXPECT_CALL(mockIo, error()).WillRepeatedly(::testing::Return(0));
    EXPECT_CALL(mockIo, eof()).WillRepeatedly(::testing::Return(true));

    bool result = isPsdType(mockIo, true);
    EXPECT_FALSE(result);
}

// Test: Header differs only in version byte (byte 5 is 2 instead of 1)
TEST_F(IsPsdTypeTest_1189, WrongVersionByte_1189) {
    const std::array<byte, 6> wrongVersion{'8', 'B', 'P', 'S', 0, 2};

    EXPECT_CALL(mockIo, read(::testing::_, 6))
        .WillOnce([&wrongVersion](byte* buf, size_t rcount) -> size_t {
            std::memcpy(buf, wrongVersion.data(), 6);
            return 6;
        });
    EXPECT_CALL(mockIo, error()).WillRepeatedly(::testing::Return(0));
    EXPECT_CALL(mockIo, eof()).WillRepeatedly(::testing::Return(false));
    EXPECT_CALL(mockIo, seek(-6, BasicIo::cur)).WillOnce(::testing::Return(0));

    bool result = isPsdType(mockIo, true);
    EXPECT_FALSE(result);
}

// Test: Header differs only in the 4th byte (byte index 4 is 1 instead of 0)
TEST_F(IsPsdTypeTest_1189, WrongByte4_1189) {
    const std::array<byte, 6> wrongByte4{'8', 'B', 'P', 'S', 1, 1};

    EXPECT_CALL(mockIo, read(::testing::_, 6))
        .WillOnce([&wrongByte4](byte* buf, size_t rcount) -> size_t {
            std::memcpy(buf, wrongByte4.data(), 6);
            return 6;
        });
    EXPECT_CALL(mockIo, error()).WillRepeatedly(::testing::Return(0));
    EXPECT_CALL(mockIo, eof()).WillRepeatedly(::testing::Return(false));
    EXPECT_CALL(mockIo, seek(-6, BasicIo::cur)).WillOnce(::testing::Return(0));

    bool result = isPsdType(mockIo, true);
    EXPECT_FALSE(result);
}

// Test: Header with first byte wrong
TEST_F(IsPsdTypeTest_1189, WrongFirstByte_1189) {
    const std::array<byte, 6> wrongFirst{'9', 'B', 'P', 'S', 0, 1};

    EXPECT_CALL(mockIo, read(::testing::_, 6))
        .WillOnce([&wrongFirst](byte* buf, size_t rcount) -> size_t {
            std::memcpy(buf, wrongFirst.data(), 6);
            return 6;
        });
    EXPECT_CALL(mockIo, error()).WillRepeatedly(::testing::Return(0));
    EXPECT_CALL(mockIo, eof()).WillRepeatedly(::testing::Return(false));
    EXPECT_CALL(mockIo, seek(-6, BasicIo::cur)).WillOnce(::testing::Return(0));

    bool result = isPsdType(mockIo, true);
    EXPECT_FALSE(result);
}

// Test: All zero bytes
TEST_F(IsPsdTypeTest_1189, AllZeroBytes_1189) {
    const std::array<byte, 6> zeros{0, 0, 0, 0, 0, 0};

    EXPECT_CALL(mockIo, read(::testing::_, 6))
        .WillOnce([&zeros](byte* buf, size_t rcount) -> size_t {
            std::memcpy(buf, zeros.data(), 6);
            return 6;
        });
    EXPECT_CALL(mockIo, error()).WillRepeatedly(::testing::Return(0));
    EXPECT_CALL(mockIo, eof()).WillRepeatedly(::testing::Return(false));
    EXPECT_CALL(mockIo, seek(-6, BasicIo::cur)).WillOnce(::testing::Return(0));

    bool result = isPsdType(mockIo, false);
    EXPECT_FALSE(result);
}

// Test: Both error and eof set returns false
TEST_F(IsPsdTypeTest_1189, BothErrorAndEof_1189) {
    EXPECT_CALL(mockIo, read(::testing::_, 6))
        .WillOnce([](byte* buf, size_t rcount) -> size_t {
            return 0;
        });
    EXPECT_CALL(mockIo, error()).WillRepeatedly(::testing::Return(1));
    EXPECT_CALL(mockIo, eof()).WillRepeatedly(::testing::Return(true));

    bool result = isPsdType(mockIo, false);
    EXPECT_FALSE(result);
}

// Test with MemIo for integration-style testing (valid PSD)
TEST(IsPsdTypeMemIoTest_1189, ValidPsdWithMemIo_1189) {
    const byte psdHeader[] = {'8', 'B', 'P', 'S', 0, 1};
    MemIo memIo(psdHeader, 6);

    bool result = isPsdType(memIo, true);
    EXPECT_TRUE(result);
    // After advance=true and matched, position should be at 6
    EXPECT_EQ(memIo.tell(), 6u);
}

// Test with MemIo: valid PSD, advance=false should reset position
TEST(IsPsdTypeMemIoTest_1189, ValidPsdNoAdvanceWithMemIo_1189) {
    const byte psdHeader[] = {'8', 'B', 'P', 'S', 0, 1};
    MemIo memIo(psdHeader, 6);

    bool result = isPsdType(memIo, false);
    EXPECT_TRUE(result);
    // After advance=false, position should be reset to 0
    EXPECT_EQ(memIo.tell(), 0u);
}

// Test with MemIo: invalid data, advance=true
TEST(IsPsdTypeMemIoTest_1189, InvalidDataWithMemIo_1189) {
    const byte data[] = {'N', 'O', 'T', 'P', 'S', 'D'};
    MemIo memIo(data, 6);

    bool result = isPsdType(memIo, true);
    EXPECT_FALSE(result);
    // Position should be reset since not matched
    EXPECT_EQ(memIo.tell(), 0u);
}

// Test with MemIo: too short data (less than 6 bytes)
TEST(IsPsdTypeMemIoTest_1189, TooShortDataWithMemIo_1189) {
    const byte data[] = {'8', 'B', 'P'};
    MemIo memIo(data, 3);

    bool result = isPsdType(memIo, true);
    EXPECT_FALSE(result);
}

// Test with MemIo: empty data
TEST(IsPsdTypeMemIoTest_1189, EmptyDataWithMemIo_1189) {
    MemIo memIo;

    bool result = isPsdType(memIo, true);
    EXPECT_FALSE(result);
}

// Test with MemIo: valid PSD header followed by extra data
TEST(IsPsdTypeMemIoTest_1189, ValidPsdWithExtraDataAdvance_1189) {
    const byte data[] = {'8', 'B', 'P', 'S', 0, 1, 0xFF, 0xFF, 0xFF};
    MemIo memIo(data, 9);

    bool result = isPsdType(memIo, true);
    EXPECT_TRUE(result);
    EXPECT_EQ(memIo.tell(), 6u);
}

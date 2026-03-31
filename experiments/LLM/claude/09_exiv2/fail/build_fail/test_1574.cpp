#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cstring>

// Include necessary headers
#include "exiv2/basicio.hpp"
#include "helper_functions.hpp"

// We need to include the header that declares isAsfType
// Based on the code, it's in the Exiv2 namespace
namespace Exiv2 {
bool isAsfType(BasicIo& iIo, bool advance);
}

// The ASF header GUID is: 30 26 B2 75 8E 66 CF 11 A6 D9 00 AA 00 62 CE 6C
static const unsigned char ASF_HEADER_GUID[16] = {
    0x30, 0x26, 0xB2, 0x75, 0x8E, 0x66, 0xCF, 0x11,
    0xA6, 0xD9, 0x00, 0xAA, 0x00, 0x62, 0xCE, 0x6C
};

// Mock class for BasicIo
class MockBasicIo : public Exiv2::BasicIo {
public:
    MOCK_METHOD(int, open, (), (override));
    MOCK_METHOD(int, close, (), (override));
    MOCK_METHOD(size_t, write, (const Exiv2::byte* data, size_t wcount), (override));
    MOCK_METHOD(size_t, write, (Exiv2::BasicIo& src), (override));
    MOCK_METHOD(int, putb, (Exiv2::byte data), (override));
    MOCK_METHOD(Exiv2::DataBuf, read, (size_t rcount), (override));
    MOCK_METHOD(size_t, read, (Exiv2::byte* buf, size_t rcount), (override));
    MOCK_METHOD(int, getb, (), (override));
    MOCK_METHOD(void, transfer, (Exiv2::BasicIo& src), (override));
    MOCK_METHOD(int, seek, (int64_t offset, Position pos), (override));
    MOCK_METHOD(Exiv2::byte*, mmap, (bool isWriteable), (override));
    MOCK_METHOD(int, munmap, (), (override));
    MOCK_METHOD(const size_t, tell, (), (const, override));
    MOCK_METHOD(const size_t, size, (), (const, override));
    MOCK_METHOD(const bool, isopen, (), (const, override));
    MOCK_METHOD(const int, error, (), (const, override));
    MOCK_METHOD(const bool, eof, (), (const, override));
    MOCK_METHOD(const std::string&, path, (), (const, override));
    MOCK_METHOD(void, populateFakeData, (), (override));
};

using ::testing::_;
using ::testing::Return;
using ::testing::DoAll;
using ::testing::SetArrayArgument;
using ::testing::Invoke;

class IsAsfTypeTest_1574 : public ::testing::Test {
protected:
    MockBasicIo mockIo;
};

// Test: Valid ASF type with advance=true should return true and NOT seek back
TEST_F(IsAsfTypeTest_1574, ValidAsfTypeWithAdvanceTrue_1574) {
    EXPECT_CALL(mockIo, read(_, 16))
        .WillOnce(DoAll(
            SetArrayArgument<0>(ASF_HEADER_GUID, ASF_HEADER_GUID + 16),
            Return(16)));
    EXPECT_CALL(mockIo, error())
        .WillOnce(Return(0));
    EXPECT_CALL(mockIo, eof())
        .WillOnce(Return(false));
    // Should NOT call seek when advance=true and matched
    EXPECT_CALL(mockIo, seek(_, _)).Times(0);

    bool result = Exiv2::isAsfType(mockIo, true);
    EXPECT_TRUE(result);
}

// Test: Valid ASF type with advance=false should return true and seek back to beginning
TEST_F(IsAsfTypeTest_1574, ValidAsfTypeWithAdvanceFalse_1574) {
    EXPECT_CALL(mockIo, read(_, 16))
        .WillOnce(DoAll(
            SetArrayArgument<0>(ASF_HEADER_GUID, ASF_HEADER_GUID + 16),
            Return(16)));
    EXPECT_CALL(mockIo, error())
        .WillOnce(Return(0));
    EXPECT_CALL(mockIo, eof())
        .WillOnce(Return(false));
    // Should seek back when advance=false
    EXPECT_CALL(mockIo, seek(0, Exiv2::BasicIo::beg))
        .WillOnce(Return(0));

    bool result = Exiv2::isAsfType(mockIo, false);
    EXPECT_TRUE(result);
}

// Test: Invalid (non-ASF) data with advance=true should return false and seek back
TEST_F(IsAsfTypeTest_1574, InvalidAsfTypeWithAdvanceTrue_1574) {
    unsigned char invalidData[16] = {0};
    EXPECT_CALL(mockIo, read(_, 16))
        .WillOnce(DoAll(
            SetArrayArgument<0>(invalidData, invalidData + 16),
            Return(16)));
    EXPECT_CALL(mockIo, error())
        .WillOnce(Return(0));
    EXPECT_CALL(mockIo, eof())
        .WillOnce(Return(false));
    // Should seek back when not matched
    EXPECT_CALL(mockIo, seek(0, Exiv2::BasicIo::beg))
        .WillOnce(Return(0));

    bool result = Exiv2::isAsfType(mockIo, true);
    EXPECT_FALSE(result);
}

// Test: Invalid (non-ASF) data with advance=false should return false and seek back
TEST_F(IsAsfTypeTest_1574, InvalidAsfTypeWithAdvanceFalse_1574) {
    unsigned char invalidData[16] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
                                      0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
    EXPECT_CALL(mockIo, read(_, 16))
        .WillOnce(DoAll(
            SetArrayArgument<0>(invalidData, invalidData + 16),
            Return(16)));
    EXPECT_CALL(mockIo, error())
        .WillOnce(Return(0));
    EXPECT_CALL(mockIo, eof())
        .WillOnce(Return(false));
    EXPECT_CALL(mockIo, seek(0, Exiv2::BasicIo::beg))
        .WillOnce(Return(0));

    bool result = Exiv2::isAsfType(mockIo, false);
    EXPECT_FALSE(result);
}

// Test: IO error on read should return false
TEST_F(IsAsfTypeTest_1574, IoErrorOnRead_1574) {
    EXPECT_CALL(mockIo, read(_, 16))
        .WillOnce(Return(0));
    EXPECT_CALL(mockIo, error())
        .WillOnce(Return(1));  // Error occurred

    bool result = Exiv2::isAsfType(mockIo, true);
    EXPECT_FALSE(result);
}

// Test: EOF on read should return false
TEST_F(IsAsfTypeTest_1574, EofOnRead_1574) {
    EXPECT_CALL(mockIo, read(_, 16))
        .WillOnce(Return(0));
    EXPECT_CALL(mockIo, error())
        .WillOnce(Return(0));
    EXPECT_CALL(mockIo, eof())
        .WillOnce(Return(true));  // EOF reached

    bool result = Exiv2::isAsfType(mockIo, true);
    EXPECT_FALSE(result);
}

// Test: Partial ASF GUID (one byte off) should return false
TEST_F(IsAsfTypeTest_1574, PartialMatchAsfGuid_1574) {
    unsigned char almostAsf[16];
    std::memcpy(almostAsf, ASF_HEADER_GUID, 16);
    almostAsf[15] = 0x00;  // Change last byte

    EXPECT_CALL(mockIo, read(_, 16))
        .WillOnce(DoAll(
            SetArrayArgument<0>(almostAsf, almostAsf + 16),
            Return(16)));
    EXPECT_CALL(mockIo, error())
        .WillOnce(Return(0));
    EXPECT_CALL(mockIo, eof())
        .WillOnce(Return(false));
    EXPECT_CALL(mockIo, seek(0, Exiv2::BasicIo::beg))
        .WillOnce(Return(0));

    bool result = Exiv2::isAsfType(mockIo, true);
    EXPECT_FALSE(result);
}

// Test: First byte different should not match
TEST_F(IsAsfTypeTest_1574, FirstByteDifferent_1574) {
    unsigned char data[16];
    std::memcpy(data, ASF_HEADER_GUID, 16);
    data[0] = 0x31;  // Change first byte

    EXPECT_CALL(mockIo, read(_, 16))
        .WillOnce(DoAll(
            SetArrayArgument<0>(data, data + 16),
            Return(16)));
    EXPECT_CALL(mockIo, error())
        .WillOnce(Return(0));
    EXPECT_CALL(mockIo, eof())
        .WillOnce(Return(false));
    EXPECT_CALL(mockIo, seek(0, Exiv2::BasicIo::beg))
        .WillOnce(Return(0));

    bool result = Exiv2::isAsfType(mockIo, true);
    EXPECT_FALSE(result);
}

// Test: Both error and eof set should return false
TEST_F(IsAsfTypeTest_1574, BothErrorAndEof_1574) {
    EXPECT_CALL(mockIo, read(_, 16))
        .WillOnce(Return(0));
    EXPECT_CALL(mockIo, error())
        .WillOnce(Return(1));

    bool result = Exiv2::isAsfType(mockIo, false);
    EXPECT_FALSE(result);
}

// Test: All zeros data should return false
TEST_F(IsAsfTypeTest_1574, AllZerosData_1574) {
    unsigned char zeros[16] = {0};

    EXPECT_CALL(mockIo, read(_, 16))
        .WillOnce(DoAll(
            SetArrayArgument<0>(zeros, zeros + 16),
            Return(16)));
    EXPECT_CALL(mockIo, error())
        .WillOnce(Return(0));
    EXPECT_CALL(mockIo, eof())
        .WillOnce(Return(false));
    EXPECT_CALL(mockIo, seek(0, Exiv2::BasicIo::beg))
        .WillOnce(Return(0));

    bool result = Exiv2::isAsfType(mockIo, true);
    EXPECT_FALSE(result);
}

// Test: Random non-ASF data should return false
TEST_F(IsAsfTypeTest_1574, RandomNonAsfData_1574) {
    unsigned char randomData[16] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
                                     0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10};

    EXPECT_CALL(mockIo, read(_, 16))
        .WillOnce(DoAll(
            SetArrayArgument<0>(randomData, randomData + 16),
            Return(16)));
    EXPECT_CALL(mockIo, error())
        .WillOnce(Return(0));
    EXPECT_CALL(mockIo, eof())
        .WillOnce(Return(false));
    EXPECT_CALL(mockIo, seek(0, Exiv2::BasicIo::beg))
        .WillOnce(Return(0));

    bool result = Exiv2::isAsfType(mockIo, false);
    EXPECT_FALSE(result);
}

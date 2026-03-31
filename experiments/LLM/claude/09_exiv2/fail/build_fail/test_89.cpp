#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <array>
#include <cstring>

#include "exiv2/basicio.hpp"
#include "exiv2/jp2image.hpp"

using namespace Exiv2;
using ::testing::_;
using ::testing::Return;
using ::testing::DoAll;
using ::testing::SetArrayArgument;
using ::testing::Invoke;

// The JP2 signature bytes
static const std::array<byte, 12> kJp2Signature = {0, 0, 0, 12, 106, 80, 32, 32, 13, 10, 135, 10};

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

class IsJp2TypeTest_89 : public ::testing::Test {
protected:
    MockBasicIo mockIo;
};

// Test: Valid JP2 signature with advance=true should return true and NOT seek back
TEST_F(IsJp2TypeTest_89, ValidSignatureAdvanceTrue_89) {
    EXPECT_CALL(mockIo, read(_, 12))
        .WillOnce(DoAll(
            Invoke([](byte* buf, size_t rcount) {
                std::memcpy(buf, kJp2Signature.data(), rcount);
            }),
            Return(12)));
    EXPECT_CALL(mockIo, error())
        .WillRepeatedly(Return(0));
    EXPECT_CALL(mockIo, eof())
        .WillRepeatedly(Return(false));
    // When advance is true and matched, seek should NOT be called
    EXPECT_CALL(mockIo, seek(_, _)).Times(0);

    bool result = isJp2Type(mockIo, true);
    EXPECT_TRUE(result);
}

// Test: Valid JP2 signature with advance=false should return true and seek back
TEST_F(IsJp2TypeTest_89, ValidSignatureAdvanceFalse_89) {
    EXPECT_CALL(mockIo, read(_, 12))
        .WillOnce(DoAll(
            Invoke([](byte* buf, size_t rcount) {
                std::memcpy(buf, kJp2Signature.data(), rcount);
            }),
            Return(12)));
    EXPECT_CALL(mockIo, error())
        .WillRepeatedly(Return(0));
    EXPECT_CALL(mockIo, eof())
        .WillRepeatedly(Return(false));
    // When advance is false, even if matched, seek should be called to go back
    EXPECT_CALL(mockIo, seek(-12, BasicIo::cur))
        .WillOnce(Return(0));

    bool result = isJp2Type(mockIo, false);
    EXPECT_TRUE(result);
}

// Test: Invalid signature with advance=true should return false and seek back
TEST_F(IsJp2TypeTest_89, InvalidSignatureAdvanceTrue_89) {
    std::array<byte, 12> badSig = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    EXPECT_CALL(mockIo, read(_, 12))
        .WillOnce(DoAll(
            Invoke([&badSig](byte* buf, size_t rcount) {
                std::memcpy(buf, badSig.data(), rcount);
            }),
            Return(12)));
    EXPECT_CALL(mockIo, error())
        .WillRepeatedly(Return(0));
    EXPECT_CALL(mockIo, eof())
        .WillRepeatedly(Return(false));
    // Not matched => should seek back
    EXPECT_CALL(mockIo, seek(-12, BasicIo::cur))
        .WillOnce(Return(0));

    bool result = isJp2Type(mockIo, true);
    EXPECT_FALSE(result);
}

// Test: Invalid signature with advance=false should return false and seek back
TEST_F(IsJp2TypeTest_89, InvalidSignatureAdvanceFalse_89) {
    std::array<byte, 12> badSig = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    EXPECT_CALL(mockIo, read(_, 12))
        .WillOnce(DoAll(
            Invoke([&badSig](byte* buf, size_t rcount) {
                std::memcpy(buf, badSig.data(), rcount);
            }),
            Return(12)));
    EXPECT_CALL(mockIo, error())
        .WillRepeatedly(Return(0));
    EXPECT_CALL(mockIo, eof())
        .WillRepeatedly(Return(false));
    EXPECT_CALL(mockIo, seek(-12, BasicIo::cur))
        .WillOnce(Return(0));

    bool result = isJp2Type(mockIo, false);
    EXPECT_FALSE(result);
}

// Test: IO error during read should return false
TEST_F(IsJp2TypeTest_89, IoErrorDuringRead_89) {
    EXPECT_CALL(mockIo, read(_, 12))
        .WillOnce(Return(12));
    EXPECT_CALL(mockIo, error())
        .WillRepeatedly(Return(1));  // Simulate an error
    EXPECT_CALL(mockIo, eof())
        .WillRepeatedly(Return(false));

    bool result = isJp2Type(mockIo, true);
    EXPECT_FALSE(result);
}

// Test: EOF during read should return false
TEST_F(IsJp2TypeTest_89, EofDuringRead_89) {
    EXPECT_CALL(mockIo, read(_, 12))
        .WillOnce(Return(12));
    EXPECT_CALL(mockIo, error())
        .WillRepeatedly(Return(0));
    EXPECT_CALL(mockIo, eof())
        .WillRepeatedly(Return(true));  // Simulate EOF

    bool result = isJp2Type(mockIo, true);
    EXPECT_FALSE(result);
}

// Test: Short read (fewer bytes than signature size) should return false
TEST_F(IsJp2TypeTest_89, ShortRead_89) {
    EXPECT_CALL(mockIo, read(_, 12))
        .WillOnce(Return(5));  // Only 5 bytes read
    EXPECT_CALL(mockIo, error())
        .WillRepeatedly(Return(0));
    EXPECT_CALL(mockIo, eof())
        .WillRepeatedly(Return(false));

    bool result = isJp2Type(mockIo, true);
    EXPECT_FALSE(result);
}

// Test: Zero bytes read should return false
TEST_F(IsJp2TypeTest_89, ZeroBytesRead_89) {
    EXPECT_CALL(mockIo, read(_, 12))
        .WillOnce(Return(0));
    EXPECT_CALL(mockIo, error())
        .WillRepeatedly(Return(0));
    EXPECT_CALL(mockIo, eof())
        .WillRepeatedly(Return(false));

    bool result = isJp2Type(mockIo, false);
    EXPECT_FALSE(result);
}

// Test: Signature differs by one byte should return false
TEST_F(IsJp2TypeTest_89, SignatureDiffersByOneByte_89) {
    std::array<byte, 12> almostSig = kJp2Signature;
    almostSig[11] = 0x0B;  // Change last byte from 0x0A to 0x0B

    EXPECT_CALL(mockIo, read(_, 12))
        .WillOnce(DoAll(
            Invoke([&almostSig](byte* buf, size_t rcount) {
                std::memcpy(buf, almostSig.data(), rcount);
            }),
            Return(12)));
    EXPECT_CALL(mockIo, error())
        .WillRepeatedly(Return(0));
    EXPECT_CALL(mockIo, eof())
        .WillRepeatedly(Return(false));
    EXPECT_CALL(mockIo, seek(-12, BasicIo::cur))
        .WillOnce(Return(0));

    bool result = isJp2Type(mockIo, true);
    EXPECT_FALSE(result);
}

// Test: First byte differs should return false
TEST_F(IsJp2TypeTest_89, FirstByteDiffers_89) {
    std::array<byte, 12> almostSig = kJp2Signature;
    almostSig[0] = 0xFF;  // Change first byte

    EXPECT_CALL(mockIo, read(_, 12))
        .WillOnce(DoAll(
            Invoke([&almostSig](byte* buf, size_t rcount) {
                std::memcpy(buf, almostSig.data(), rcount);
            }),
            Return(12)));
    EXPECT_CALL(mockIo, error())
        .WillRepeatedly(Return(0));
    EXPECT_CALL(mockIo, eof())
        .WillRepeatedly(Return(false));
    EXPECT_CALL(mockIo, seek(-12, BasicIo::cur))
        .WillOnce(Return(0));

    bool result = isJp2Type(mockIo, true);
    EXPECT_FALSE(result);
}

// Test: Both error and eof set should return false
TEST_F(IsJp2TypeTest_89, ErrorAndEof_89) {
    EXPECT_CALL(mockIo, read(_, 12))
        .WillOnce(Return(12));
    EXPECT_CALL(mockIo, error())
        .WillRepeatedly(Return(1));
    EXPECT_CALL(mockIo, eof())
        .WillRepeatedly(Return(true));

    bool result = isJp2Type(mockIo, true);
    EXPECT_FALSE(result);
}

// Test: Read exactly 11 bytes (one less than signature) should return false
TEST_F(IsJp2TypeTest_89, ReadElevenBytes_89) {
    EXPECT_CALL(mockIo, read(_, 12))
        .WillOnce(Return(11));
    EXPECT_CALL(mockIo, error())
        .WillRepeatedly(Return(0));
    EXPECT_CALL(mockIo, eof())
        .WillRepeatedly(Return(false));

    bool result = isJp2Type(mockIo, true);
    EXPECT_FALSE(result);
}

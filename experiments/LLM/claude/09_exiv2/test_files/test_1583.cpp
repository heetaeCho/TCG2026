#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "exiv2/basicio.hpp"
#include "rw2image.hpp"
#include "rw2image_int.hpp"

using namespace Exiv2;
using ::testing::_;
using ::testing::Return;
using ::testing::DoAll;
using ::testing::SetArrayArgument;
using ::testing::Invoke;
using ::testing::AtLeast;

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
    MOCK_METHOD(size_t, tell, (), (const, override));
    MOCK_METHOD(size_t, size, (), (const, override));
    MOCK_METHOD(bool, isopen, (), (const, override));
    MOCK_METHOD(int, error, (), (const, override));
    MOCK_METHOD(bool, eof, (), (const, override));
    MOCK_METHOD(const std::string&, path, (), (const, override));
    MOCK_METHOD(void, populateFakeData, (), (override));
};

class IsRw2TypeTest_1583 : public ::testing::Test {
protected:
    MockBasicIo mockIo;
};

// Helper to create a valid RW2 header buffer
// RW2 header: little-endian byte order (0x4949), tag 0x0055, offset 0x00000018
static void fillValidRw2Header(byte* buf) {
    // Byte order: little endian = "II" (0x49, 0x49)
    buf[0] = 0x49;
    buf[1] = 0x49;
    // Tag: 0x0055 in little endian
    buf[2] = 0x55;
    buf[3] = 0x00;
    // Offset: 0x00000018 in little endian
    buf[4] = 0x18;
    buf[5] = 0x00;
    buf[6] = 0x00;
    buf[7] = 0x00;
    // Rest can be zeros
    for (int i = 8; i < 24; i++) {
        buf[i] = 0x00;
    }
}

// Test: Valid RW2 data with advance=true returns true and does not seek back
TEST_F(IsRw2TypeTest_1583, ValidRw2DataAdvanceTrue_1583) {
    byte validHeader[24];
    fillValidRw2Header(validHeader);

    EXPECT_CALL(mockIo, read(_, 24))
        .WillOnce(DoAll(
            Invoke([&validHeader](byte* buf, size_t /*rcount*/) {
                std::memcpy(buf, validHeader, 24);
            }),
            Return(24)));
    EXPECT_CALL(mockIo, error()).WillRepeatedly(Return(0));
    EXPECT_CALL(mockIo, eof()).WillRepeatedly(Return(false));
    // With advance=true and valid header, seek should NOT be called
    EXPECT_CALL(mockIo, seek(_, _)).Times(0);

    bool result = isRw2Type(mockIo, true);
    EXPECT_TRUE(result);
}

// Test: Valid RW2 data with advance=false returns true and seeks back
TEST_F(IsRw2TypeTest_1583, ValidRw2DataAdvanceFalse_1583) {
    byte validHeader[24];
    fillValidRw2Header(validHeader);

    EXPECT_CALL(mockIo, read(_, 24))
        .WillOnce(DoAll(
            Invoke([&validHeader](byte* buf, size_t /*rcount*/) {
                std::memcpy(buf, validHeader, 24);
            }),
            Return(24)));
    EXPECT_CALL(mockIo, error()).WillRepeatedly(Return(0));
    EXPECT_CALL(mockIo, eof()).WillRepeatedly(Return(false));
    // With advance=false, seek should be called to go back
    EXPECT_CALL(mockIo, seek(-24, BasicIo::cur)).WillOnce(Return(0));

    bool result = isRw2Type(mockIo, false);
    EXPECT_TRUE(result);
}

// Test: Invalid data returns false and seeks back regardless of advance
TEST_F(IsRw2TypeTest_1583, InvalidDataAdvanceTrue_1583) {
    byte invalidHeader[24];
    std::memset(invalidHeader, 0, 24);

    EXPECT_CALL(mockIo, read(_, 24))
        .WillOnce(DoAll(
            Invoke([&invalidHeader](byte* buf, size_t /*rcount*/) {
                std::memcpy(buf, invalidHeader, 24);
            }),
            Return(24)));
    EXPECT_CALL(mockIo, error()).WillRepeatedly(Return(0));
    EXPECT_CALL(mockIo, eof()).WillRepeatedly(Return(false));
    // rc is false, so seek back should be called even with advance=true
    EXPECT_CALL(mockIo, seek(-24, BasicIo::cur)).WillOnce(Return(0));

    bool result = isRw2Type(mockIo, true);
    EXPECT_FALSE(result);
}

// Test: Invalid data with advance=false returns false and seeks back
TEST_F(IsRw2TypeTest_1583, InvalidDataAdvanceFalse_1583) {
    byte invalidHeader[24];
    std::memset(invalidHeader, 0xFF, 24);

    EXPECT_CALL(mockIo, read(_, 24))
        .WillOnce(DoAll(
            Invoke([&invalidHeader](byte* buf, size_t /*rcount*/) {
                std::memcpy(buf, invalidHeader, 24);
            }),
            Return(24)));
    EXPECT_CALL(mockIo, error()).WillRepeatedly(Return(0));
    EXPECT_CALL(mockIo, eof()).WillRepeatedly(Return(false));
    EXPECT_CALL(mockIo, seek(-24, BasicIo::cur)).WillOnce(Return(0));

    bool result = isRw2Type(mockIo, false);
    EXPECT_FALSE(result);
}

// Test: IO error during read returns false
TEST_F(IsRw2TypeTest_1583, IoErrorReturnsFalse_1583) {
    EXPECT_CALL(mockIo, read(_, 24)).WillOnce(Return(0));
    EXPECT_CALL(mockIo, error()).WillRepeatedly(Return(1));
    EXPECT_CALL(mockIo, eof()).WillRepeatedly(Return(false));

    bool result = isRw2Type(mockIo, true);
    EXPECT_FALSE(result);
}

// Test: EOF during read returns false
TEST_F(IsRw2TypeTest_1583, EofReturnsFalse_1583) {
    EXPECT_CALL(mockIo, read(_, 24)).WillOnce(Return(0));
    EXPECT_CALL(mockIo, error()).WillRepeatedly(Return(0));
    EXPECT_CALL(mockIo, eof()).WillRepeatedly(Return(true));

    bool result = isRw2Type(mockIo, true);
    EXPECT_FALSE(result);
}

// Test: Both error and eof returns false
TEST_F(IsRw2TypeTest_1583, ErrorAndEofReturnsFalse_1583) {
    EXPECT_CALL(mockIo, read(_, 24)).WillOnce(Return(0));
    EXPECT_CALL(mockIo, error()).WillRepeatedly(Return(1));
    EXPECT_CALL(mockIo, eof()).WillRepeatedly(Return(true));

    bool result = isRw2Type(mockIo, true);
    EXPECT_FALSE(result);
}

// Test: Partial TIFF-like header (e.g., correct byte order but wrong tag) returns false
TEST_F(IsRw2TypeTest_1583, TiffHeaderNotRw2ReturnsFalse_1583) {
    byte tiffHeader[24];
    std::memset(tiffHeader, 0, 24);
    // Standard TIFF: "II" byte order, tag 0x002A (regular TIFF, not RW2's 0x0055)
    tiffHeader[0] = 0x49;
    tiffHeader[1] = 0x49;
    tiffHeader[2] = 0x2A;
    tiffHeader[3] = 0x00;
    tiffHeader[4] = 0x08;
    tiffHeader[5] = 0x00;
    tiffHeader[6] = 0x00;
    tiffHeader[7] = 0x00;

    EXPECT_CALL(mockIo, read(_, 24))
        .WillOnce(DoAll(
            Invoke([&tiffHeader](byte* buf, size_t /*rcount*/) {
                std::memcpy(buf, tiffHeader, 24);
            }),
            Return(24)));
    EXPECT_CALL(mockIo, error()).WillRepeatedly(Return(0));
    EXPECT_CALL(mockIo, eof()).WillRepeatedly(Return(false));
    EXPECT_CALL(mockIo, seek(-24, BasicIo::cur)).WillOnce(Return(0));

    bool result = isRw2Type(mockIo, true);
    EXPECT_FALSE(result);
}

// Test: Big-endian byte order with RW2 tag - check if Rw2Header accepts this
TEST_F(IsRw2TypeTest_1583, BigEndianByteOrderWithRw2Tag_1583) {
    byte header[24];
    std::memset(header, 0, 24);
    // Big endian: "MM" (0x4D, 0x4D)
    header[0] = 0x4D;
    header[1] = 0x4D;
    // Tag 0x0055 in big endian
    header[2] = 0x00;
    header[3] = 0x55;
    // Offset 0x00000018 in big endian
    header[4] = 0x00;
    header[5] = 0x00;
    header[6] = 0x00;
    header[7] = 0x18;

    EXPECT_CALL(mockIo, read(_, 24))
        .WillOnce(DoAll(
            Invoke([&header](byte* buf, size_t /*rcount*/) {
                std::memcpy(buf, header, 24);
            }),
            Return(24)));
    EXPECT_CALL(mockIo, error()).WillRepeatedly(Return(0));
    EXPECT_CALL(mockIo, eof()).WillRepeatedly(Return(false));
    // We don't know the exact result, so we allow seek to be called or not
    EXPECT_CALL(mockIo, seek(_, _)).Times(::testing::AnyNumber());

    // Just verify it doesn't crash - result depends on implementation
    isRw2Type(mockIo, true);
}

// Test: Random garbage data returns false
TEST_F(IsRw2TypeTest_1583, RandomGarbageReturnsFalse_1583) {
    byte garbage[24];
    for (int i = 0; i < 24; i++) {
        garbage[i] = static_cast<byte>(i * 37 + 13);
    }

    EXPECT_CALL(mockIo, read(_, 24))
        .WillOnce(DoAll(
            Invoke([&garbage](byte* buf, size_t /*rcount*/) {
                std::memcpy(buf, garbage, 24);
            }),
            Return(24)));
    EXPECT_CALL(mockIo, error()).WillRepeatedly(Return(0));
    EXPECT_CALL(mockIo, eof()).WillRepeatedly(Return(false));
    EXPECT_CALL(mockIo, seek(-24, BasicIo::cur)).WillOnce(Return(0));

    bool result = isRw2Type(mockIo, false);
    EXPECT_FALSE(result);
}

// Test Rw2Header construction and basic properties
class Rw2HeaderTest_1583 : public ::testing::Test {
protected:
    Internal::Rw2Header header;
};

TEST_F(Rw2HeaderTest_1583, DefaultConstruction_1583) {
    EXPECT_EQ(header.tag(), 0x0055);
    EXPECT_EQ(header.size(), 24u);
    EXPECT_EQ(header.byteOrder(), littleEndian);
    EXPECT_EQ(header.offset(), 0x00000018u);
}

TEST_F(Rw2HeaderTest_1583, ReadValidRw2Header_1583) {
    byte validHeader[24];
    fillValidRw2Header(validHeader);
    
    bool result = header.read(validHeader, 24);
    EXPECT_TRUE(result);
}

TEST_F(Rw2HeaderTest_1583, ReadInvalidHeader_1583) {
    byte invalidHeader[24];
    std::memset(invalidHeader, 0, 24);
    
    bool result = header.read(invalidHeader, 24);
    EXPECT_FALSE(result);
}

TEST_F(Rw2HeaderTest_1583, ReadTooSmallBuffer_1583) {
    byte smallBuf[4] = {0x49, 0x49, 0x55, 0x00};
    
    bool result = header.read(smallBuf, 4);
    EXPECT_FALSE(result);
}

TEST_F(Rw2HeaderTest_1583, WriteReturnsData_1583) {
    DataBuf buf = header.write();
    // The write method should return some data (possibly empty for RW2)
    // We just verify it doesn't crash
}

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <exiv2/basicio.hpp>
#include <exiv2/crwimage.hpp>
#include <cstring>

using namespace Exiv2;
using ::testing::_;
using ::testing::Return;
using ::testing::DoAll;
using ::testing::SetArrayArgument;
using ::testing::Invoke;

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

class IsCrwTypeTest_1819 : public ::testing::Test {
protected:
    MockBasicIo mockIo;
    
    // Helper to build a valid CRW header (little-endian)
    void buildValidCrwHeader(byte* buf) {
        // Byte order: 'II' for little-endian
        buf[0] = 'I';
        buf[1] = 'I';
        // Bytes 2-5: some data (offset or other fields)
        buf[2] = 0x00;
        buf[3] = 0x00;
        buf[4] = 0x00;
        buf[5] = 0x00;
        // Bytes 6-13: CiffHeader signature "HEAPCCDR"
        const char* sig = "HEAPCCDR";
        std::memcpy(buf + 6, sig, 8);
    }
    
    // Helper to build a valid CRW header (big-endian)
    void buildValidCrwHeaderBigEndian(byte* buf) {
        buf[0] = 'M';
        buf[1] = 'M';
        buf[2] = 0x00;
        buf[3] = 0x00;
        buf[4] = 0x00;
        buf[5] = 0x00;
        const char* sig = "HEAPCCDR";
        std::memcpy(buf + 6, sig, 8);
    }
};

// Test: Valid CRW file with little-endian byte order, advance=true
TEST_F(IsCrwTypeTest_1819, ValidLittleEndianAdvanceTrue_1819) {
    byte header[14];
    buildValidCrwHeader(header);
    
    EXPECT_CALL(mockIo, read(_, 14))
        .WillOnce(DoAll(
            Invoke([&header](byte* buf, size_t) {
                std::memcpy(buf, header, 14);
            }),
            Return(14)));
    EXPECT_CALL(mockIo, error()).WillRepeatedly(Return(0));
    EXPECT_CALL(mockIo, eof()).WillRepeatedly(Return(false));
    // When advance=true and result=true, seek should NOT be called
    EXPECT_CALL(mockIo, seek(_, _)).Times(0);
    
    bool result = isCrwType(mockIo, true);
    EXPECT_TRUE(result);
}

// Test: Valid CRW file with little-endian byte order, advance=false
TEST_F(IsCrwTypeTest_1819, ValidLittleEndianAdvanceFalse_1819) {
    byte header[14];
    buildValidCrwHeader(header);
    
    EXPECT_CALL(mockIo, read(_, 14))
        .WillOnce(DoAll(
            Invoke([&header](byte* buf, size_t) {
                std::memcpy(buf, header, 14);
            }),
            Return(14)));
    EXPECT_CALL(mockIo, error()).WillRepeatedly(Return(0));
    EXPECT_CALL(mockIo, eof()).WillRepeatedly(Return(false));
    // When advance=false, seek should be called to go back
    EXPECT_CALL(mockIo, seek(-14, BasicIo::cur)).WillOnce(Return(0));
    
    bool result = isCrwType(mockIo, false);
    EXPECT_TRUE(result);
}

// Test: Valid CRW file with big-endian byte order, advance=true
TEST_F(IsCrwTypeTest_1819, ValidBigEndianAdvanceTrue_1819) {
    byte header[14];
    buildValidCrwHeaderBigEndian(header);
    
    EXPECT_CALL(mockIo, read(_, 14))
        .WillOnce(DoAll(
            Invoke([&header](byte* buf, size_t) {
                std::memcpy(buf, header, 14);
            }),
            Return(14)));
    EXPECT_CALL(mockIo, error()).WillRepeatedly(Return(0));
    EXPECT_CALL(mockIo, eof()).WillRepeatedly(Return(false));
    EXPECT_CALL(mockIo, seek(_, _)).Times(0);
    
    bool result = isCrwType(mockIo, true);
    EXPECT_TRUE(result);
}

// Test: Valid CRW file with big-endian byte order, advance=false
TEST_F(IsCrwTypeTest_1819, ValidBigEndianAdvanceFalse_1819) {
    byte header[14];
    buildValidCrwHeaderBigEndian(header);
    
    EXPECT_CALL(mockIo, read(_, 14))
        .WillOnce(DoAll(
            Invoke([&header](byte* buf, size_t) {
                std::memcpy(buf, header, 14);
            }),
            Return(14)));
    EXPECT_CALL(mockIo, error()).WillRepeatedly(Return(0));
    EXPECT_CALL(mockIo, eof()).WillRepeatedly(Return(false));
    EXPECT_CALL(mockIo, seek(-14, BasicIo::cur)).WillOnce(Return(0));
    
    bool result = isCrwType(mockIo, false);
    EXPECT_TRUE(result);
}

// Test: IO error during read
TEST_F(IsCrwTypeTest_1819, IoErrorDuringRead_1819) {
    EXPECT_CALL(mockIo, read(_, 14))
        .WillOnce(Return(0));
    EXPECT_CALL(mockIo, error()).WillRepeatedly(Return(1));
    EXPECT_CALL(mockIo, eof()).WillRepeatedly(Return(false));
    
    bool result = isCrwType(mockIo, true);
    EXPECT_FALSE(result);
}

// Test: EOF during read
TEST_F(IsCrwTypeTest_1819, EofDuringRead_1819) {
    EXPECT_CALL(mockIo, read(_, 14))
        .WillOnce(Return(0));
    EXPECT_CALL(mockIo, error()).WillRepeatedly(Return(0));
    EXPECT_CALL(mockIo, eof()).WillRepeatedly(Return(true));
    
    bool result = isCrwType(mockIo, true);
    EXPECT_FALSE(result);
}

// Test: Invalid byte order marker
TEST_F(IsCrwTypeTest_1819, InvalidByteOrderMarker_1819) {
    byte header[14];
    buildValidCrwHeader(header);
    // Corrupt byte order
    header[0] = 'X';
    header[1] = 'Y';
    
    EXPECT_CALL(mockIo, read(_, 14))
        .WillOnce(DoAll(
            Invoke([&header](byte* buf, size_t) {
                std::memcpy(buf, header, 14);
            }),
            Return(14)));
    EXPECT_CALL(mockIo, error()).WillRepeatedly(Return(0));
    EXPECT_CALL(mockIo, eof()).WillRepeatedly(Return(false));
    // result is false, so seek should be called regardless of advance
    EXPECT_CALL(mockIo, seek(-14, BasicIo::cur)).WillOnce(Return(0));
    
    bool result = isCrwType(mockIo, true);
    EXPECT_FALSE(result);
}

// Test: Invalid byte order marker with advance=false
TEST_F(IsCrwTypeTest_1819, InvalidByteOrderAdvanceFalse_1819) {
    byte header[14];
    buildValidCrwHeader(header);
    header[0] = 'A';
    header[1] = 'B';
    
    EXPECT_CALL(mockIo, read(_, 14))
        .WillOnce(DoAll(
            Invoke([&header](byte* buf, size_t) {
                std::memcpy(buf, header, 14);
            }),
            Return(14)));
    EXPECT_CALL(mockIo, error()).WillRepeatedly(Return(0));
    EXPECT_CALL(mockIo, eof()).WillRepeatedly(Return(false));
    EXPECT_CALL(mockIo, seek(-14, BasicIo::cur)).WillOnce(Return(0));
    
    bool result = isCrwType(mockIo, false);
    EXPECT_FALSE(result);
}

// Test: Valid byte order but invalid signature
TEST_F(IsCrwTypeTest_1819, ValidByteOrderInvalidSignature_1819) {
    byte header[14];
    buildValidCrwHeader(header);
    // Corrupt the signature
    header[6] = 'X';
    header[7] = 'X';
    header[8] = 'X';
    header[9] = 'X';
    header[10] = 'X';
    header[11] = 'X';
    header[12] = 'X';
    header[13] = 'X';
    
    EXPECT_CALL(mockIo, read(_, 14))
        .WillOnce(DoAll(
            Invoke([&header](byte* buf, size_t) {
                std::memcpy(buf, header, 14);
            }),
            Return(14)));
    EXPECT_CALL(mockIo, error()).WillRepeatedly(Return(0));
    EXPECT_CALL(mockIo, eof()).WillRepeatedly(Return(false));
    EXPECT_CALL(mockIo, seek(-14, BasicIo::cur)).WillOnce(Return(0));
    
    bool result = isCrwType(mockIo, true);
    EXPECT_FALSE(result);
}

// Test: Valid byte order but partially corrupted signature
TEST_F(IsCrwTypeTest_1819, ValidByteOrderPartiallyCorrruptedSignature_1819) {
    byte header[14];
    buildValidCrwHeader(header);
    // Corrupt just one byte of signature
    header[13] = 'X';
    
    EXPECT_CALL(mockIo, read(_, 14))
        .WillOnce(DoAll(
            Invoke([&header](byte* buf, size_t) {
                std::memcpy(buf, header, 14);
            }),
            Return(14)));
    EXPECT_CALL(mockIo, error()).WillRepeatedly(Return(0));
    EXPECT_CALL(mockIo, eof()).WillRepeatedly(Return(false));
    EXPECT_CALL(mockIo, seek(-14, BasicIo::cur)).WillOnce(Return(0));
    
    bool result = isCrwType(mockIo, true);
    EXPECT_FALSE(result);
}

// Test: Mixed byte order - first byte 'I', second byte 'M' (invalid)
TEST_F(IsCrwTypeTest_1819, MixedByteOrderIM_1819) {
    byte header[14];
    buildValidCrwHeader(header);
    header[0] = 'I';
    header[1] = 'M';
    
    EXPECT_CALL(mockIo, read(_, 14))
        .WillOnce(DoAll(
            Invoke([&header](byte* buf, size_t) {
                std::memcpy(buf, header, 14);
            }),
            Return(14)));
    EXPECT_CALL(mockIo, error()).WillRepeatedly(Return(0));
    EXPECT_CALL(mockIo, eof()).WillRepeatedly(Return(false));
    EXPECT_CALL(mockIo, seek(-14, BasicIo::cur)).WillOnce(Return(0));
    
    bool result = isCrwType(mockIo, true);
    EXPECT_FALSE(result);
}

// Test: Mixed byte order - first byte 'M', second byte 'I' (invalid)
TEST_F(IsCrwTypeTest_1819, MixedByteOrderMI_1819) {
    byte header[14];
    buildValidCrwHeader(header);
    header[0] = 'M';
    header[1] = 'I';
    
    EXPECT_CALL(mockIo, read(_, 14))
        .WillOnce(DoAll(
            Invoke([&header](byte* buf, size_t) {
                std::memcpy(buf, header, 14);
            }),
            Return(14)));
    EXPECT_CALL(mockIo, error()).WillRepeatedly(Return(0));
    EXPECT_CALL(mockIo, eof()).WillRepeatedly(Return(false));
    EXPECT_CALL(mockIo, seek(-14, BasicIo::cur)).WillOnce(Return(0));
    
    bool result = isCrwType(mockIo, true);
    EXPECT_FALSE(result);
}

// Test: All zeros in header
TEST_F(IsCrwTypeTest_1819, AllZerosHeader_1819) {
    byte header[14];
    std::memset(header, 0, 14);
    
    EXPECT_CALL(mockIo, read(_, 14))
        .WillOnce(DoAll(
            Invoke([&header](byte* buf, size_t) {
                std::memcpy(buf, header, 14);
            }),
            Return(14)));
    EXPECT_CALL(mockIo, error()).WillRepeatedly(Return(0));
    EXPECT_CALL(mockIo, eof()).WillRepeatedly(Return(false));
    EXPECT_CALL(mockIo, seek(-14, BasicIo::cur)).WillOnce(Return(0));
    
    bool result = isCrwType(mockIo, true);
    EXPECT_FALSE(result);
}

// Test: Both error and eof set
TEST_F(IsCrwTypeTest_1819, BothErrorAndEof_1819) {
    EXPECT_CALL(mockIo, read(_, 14))
        .WillOnce(Return(0));
    EXPECT_CALL(mockIo, error()).WillRepeatedly(Return(1));
    EXPECT_CALL(mockIo, eof()).WillRepeatedly(Return(true));
    
    bool result = isCrwType(mockIo, false);
    EXPECT_FALSE(result);
}

// Test: Invalid signature with advance=false causes seek back
TEST_F(IsCrwTypeTest_1819, InvalidSignatureAdvanceFalseSeeksBack_1819) {
    byte header[14];
    buildValidCrwHeader(header);
    // Corrupt signature
    header[8] = 'Z';
    
    EXPECT_CALL(mockIo, read(_, 14))
        .WillOnce(DoAll(
            Invoke([&header](byte* buf, size_t) {
                std::memcpy(buf, header, 14);
            }),
            Return(14)));
    EXPECT_CALL(mockIo, error()).WillRepeatedly(Return(0));
    EXPECT_CALL(mockIo, eof()).WillRepeatedly(Return(false));
    EXPECT_CALL(mockIo, seek(-14, BasicIo::cur)).WillOnce(Return(0));
    
    bool result = isCrwType(mockIo, false);
    EXPECT_FALSE(result);
}

// Test: Using MemIo for integration-like test with valid CRW data
TEST_F(IsCrwTypeTest_1819, MemIoValidCrwAdvanceTrue_1819) {
    byte data[14];
    buildValidCrwHeader(data);
    
    MemIo memIo(data, 14);
    
    bool result = isCrwType(memIo, true);
    EXPECT_TRUE(result);
    // After advance=true with valid result, position should be at 14
    EXPECT_EQ(memIo.tell(), 14u);
}

// Test: Using MemIo with valid CRW data, advance=false
TEST_F(IsCrwTypeTest_1819, MemIoValidCrwAdvanceFalse_1819) {
    byte data[14];
    buildValidCrwHeader(data);
    
    MemIo memIo(data, 14);
    
    bool result = isCrwType(memIo, false);
    EXPECT_TRUE(result);
    // After advance=false, position should be back to 0
    EXPECT_EQ(memIo.tell(), 0u);
}

// Test: Using MemIo with too short data (less than 14 bytes)
TEST_F(IsCrwTypeTest_1819, MemIoTooShortData_1819) {
    byte data[5] = {0};
    
    MemIo memIo(data, 5);
    
    bool result = isCrwType(memIo, true);
    EXPECT_FALSE(result);
}

// Test: Using MemIo with invalid data, advance=true still seeks back
TEST_F(IsCrwTypeTest_1819, MemIoInvalidDataAdvanceTrue_1819) {
    byte data[14];
    std::memset(data, 0xFF, 14);
    
    MemIo memIo(data, 14);
    
    bool result = isCrwType(memIo, true);
    EXPECT_FALSE(result);
    // When result is false, seek back happens regardless of advance
    EXPECT_EQ(memIo.tell(), 0u);
}

// Test: Using MemIo with empty data
TEST_F(IsCrwTypeTest_1819, MemIoEmptyData_1819) {
    MemIo memIo;
    
    bool result = isCrwType(memIo, true);
    EXPECT_FALSE(result);
}

// Test: Using MemIo with big-endian valid CRW
TEST_F(IsCrwTypeTest_1819, MemIoValidBigEndian_1819) {
    byte data[14];
    buildValidCrwHeaderBigEndian(data);
    
    MemIo memIo(data, 14);
    
    bool result = isCrwType(memIo, true);
    EXPECT_TRUE(result);
}

// Test: Exactly 14 bytes with valid header followed by more data
TEST_F(IsCrwTypeTest_1819, MemIoValidHeaderWithExtraData_1819) {
    byte data[100];
    std::memset(data, 0, 100);
    buildValidCrwHeader(data);
    
    MemIo memIo(data, 100);
    
    bool result = isCrwType(memIo, true);
    EXPECT_TRUE(result);
    EXPECT_EQ(memIo.tell(), 14u);
}

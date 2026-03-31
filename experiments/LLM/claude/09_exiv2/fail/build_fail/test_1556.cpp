#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <exiv2/basicio.hpp>
#include <exiv2/orfimage.hpp>
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

class IsOrfTypeTest_1556 : public ::testing::Test {
protected:
    MockBasicIo mockIo;
};

// Test: Valid ORF file with little-endian byte order, advance=true
TEST_F(IsOrfTypeTest_1556, ValidOrfLittleEndianAdvanceTrue_1556) {
    // ORF header: "II" (little-endian), 0x4F52 tag, offset 0x00000008
    // "II" = 0x49, 0x49
    // Tag in little-endian: 0x52, 0x4F (0x4F52)
    // Offset in little-endian: 0x08, 0x00, 0x00, 0x00
    byte orfHeader[] = {0x49, 0x49, 0x52, 0x4F, 0x08, 0x00, 0x00, 0x00};

    EXPECT_CALL(mockIo, read(_, 8))
        .WillOnce(DoAll(
            Invoke([&orfHeader](byte* buf, size_t rcount) {
                std::memcpy(buf, orfHeader, 8);
            }),
            Return(8)));
    EXPECT_CALL(mockIo, error()).WillRepeatedly(Return(0));
    EXPECT_CALL(mockIo, eof()).WillRepeatedly(Return(false));

    bool result = isOrfType(mockIo, true);
    EXPECT_TRUE(result);
}

// Test: Valid ORF file with big-endian byte order, advance=true
TEST_F(IsOrfTypeTest_1556, ValidOrfBigEndianAdvanceTrue_1556) {
    // "MM" = 0x4D, 0x4D (big-endian)
    // Tag in big-endian: 0x4F, 0x52 (0x4F52)
    // Offset in big-endian: 0x00, 0x00, 0x00, 0x08
    byte orfHeader[] = {0x4D, 0x4D, 0x4F, 0x52, 0x00, 0x00, 0x00, 0x08};

    EXPECT_CALL(mockIo, read(_, 8))
        .WillOnce(DoAll(
            Invoke([&orfHeader](byte* buf, size_t rcount) {
                std::memcpy(buf, orfHeader, 8);
            }),
            Return(8)));
    EXPECT_CALL(mockIo, error()).WillRepeatedly(Return(0));
    EXPECT_CALL(mockIo, eof()).WillRepeatedly(Return(false));

    bool result = isOrfType(mockIo, true);
    EXPECT_TRUE(result);
}

// Test: Valid ORF file with advance=false should seek back
TEST_F(IsOrfTypeTest_1556, ValidOrfAdvanceFalseSeeksBack_1556) {
    byte orfHeader[] = {0x49, 0x49, 0x52, 0x4F, 0x08, 0x00, 0x00, 0x00};

    EXPECT_CALL(mockIo, read(_, 8))
        .WillOnce(DoAll(
            Invoke([&orfHeader](byte* buf, size_t rcount) {
                std::memcpy(buf, orfHeader, 8);
            }),
            Return(8)));
    EXPECT_CALL(mockIo, error()).WillRepeatedly(Return(0));
    EXPECT_CALL(mockIo, eof()).WillRepeatedly(Return(false));
    EXPECT_CALL(mockIo, seek(-8, BasicIo::cur)).WillOnce(Return(0));

    bool result = isOrfType(mockIo, false);
    EXPECT_TRUE(result);
}

// Test: Invalid header (not ORF, e.g. regular TIFF) with advance=true should seek back
TEST_F(IsOrfTypeTest_1556, InvalidHeaderAdvanceTrueSeeksBack_1556) {
    // Regular TIFF header: "II", 0x002A, offset
    byte tiffHeader[] = {0x49, 0x49, 0x2A, 0x00, 0x08, 0x00, 0x00, 0x00};

    EXPECT_CALL(mockIo, read(_, 8))
        .WillOnce(DoAll(
            Invoke([&tiffHeader](byte* buf, size_t rcount) {
                std::memcpy(buf, tiffHeader, 8);
            }),
            Return(8)));
    EXPECT_CALL(mockIo, error()).WillRepeatedly(Return(0));
    EXPECT_CALL(mockIo, eof()).WillRepeatedly(Return(false));
    EXPECT_CALL(mockIo, seek(-8, BasicIo::cur)).WillOnce(Return(0));

    bool result = isOrfType(mockIo, true);
    EXPECT_FALSE(result);
}

// Test: Invalid header with advance=false should seek back
TEST_F(IsOrfTypeTest_1556, InvalidHeaderAdvanceFalseSeeksBack_1556) {
    byte randomData[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07};

    EXPECT_CALL(mockIo, read(_, 8))
        .WillOnce(DoAll(
            Invoke([&randomData](byte* buf, size_t rcount) {
                std::memcpy(buf, randomData, 8);
            }),
            Return(8)));
    EXPECT_CALL(mockIo, error()).WillRepeatedly(Return(0));
    EXPECT_CALL(mockIo, eof()).WillRepeatedly(Return(false));
    EXPECT_CALL(mockIo, seek(-8, BasicIo::cur)).WillOnce(Return(0));

    bool result = isOrfType(mockIo, false);
    EXPECT_FALSE(result);
}

// Test: IO error during read
TEST_F(IsOrfTypeTest_1556, IoErrorDuringRead_1556) {
    EXPECT_CALL(mockIo, read(_, 8)).WillOnce(Return(0));
    EXPECT_CALL(mockIo, error()).WillRepeatedly(Return(1));
    EXPECT_CALL(mockIo, eof()).WillRepeatedly(Return(false));

    bool result = isOrfType(mockIo, true);
    EXPECT_FALSE(result);
}

// Test: EOF during read
TEST_F(IsOrfTypeTest_1556, EofDuringRead_1556) {
    EXPECT_CALL(mockIo, read(_, 8)).WillOnce(Return(4));
    EXPECT_CALL(mockIo, error()).WillRepeatedly(Return(0));
    EXPECT_CALL(mockIo, eof()).WillRepeatedly(Return(true));

    bool result = isOrfType(mockIo, true);
    EXPECT_FALSE(result);
}

// Test: All zeros data - should not be recognized as ORF
TEST_F(IsOrfTypeTest_1556, AllZerosData_1556) {
    byte zeros[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

    EXPECT_CALL(mockIo, read(_, 8))
        .WillOnce(DoAll(
            Invoke([&zeros](byte* buf, size_t rcount) {
                std::memcpy(buf, zeros, 8);
            }),
            Return(8)));
    EXPECT_CALL(mockIo, error()).WillRepeatedly(Return(0));
    EXPECT_CALL(mockIo, eof()).WillRepeatedly(Return(false));
    EXPECT_CALL(mockIo, seek(-8, BasicIo::cur)).WillOnce(Return(0));

    bool result = isOrfType(mockIo, true);
    EXPECT_FALSE(result);
}

// Test: Correct byte order markers but wrong tag
TEST_F(IsOrfTypeTest_1556, CorrectByteOrderWrongTag_1556) {
    // "II" byte order but tag is 0x0042 instead of 0x4F52
    byte wrongTag[] = {0x49, 0x49, 0x42, 0x00, 0x08, 0x00, 0x00, 0x00};

    EXPECT_CALL(mockIo, read(_, 8))
        .WillOnce(DoAll(
            Invoke([&wrongTag](byte* buf, size_t rcount) {
                std::memcpy(buf, wrongTag, 8);
            }),
            Return(8)));
    EXPECT_CALL(mockIo, error()).WillRepeatedly(Return(0));
    EXPECT_CALL(mockIo, eof()).WillRepeatedly(Return(false));
    EXPECT_CALL(mockIo, seek(-8, BasicIo::cur)).WillOnce(Return(0));

    bool result = isOrfType(mockIo, true);
    EXPECT_FALSE(result);
}

// Test: Both error and eof set
TEST_F(IsOrfTypeTest_1556, BothErrorAndEof_1556) {
    EXPECT_CALL(mockIo, read(_, 8)).WillOnce(Return(0));
    EXPECT_CALL(mockIo, error()).WillRepeatedly(Return(1));
    EXPECT_CALL(mockIo, eof()).WillRepeatedly(Return(true));

    bool result = isOrfType(mockIo, false);
    EXPECT_FALSE(result);
}

// Test: Valid ORF big-endian with advance=false
TEST_F(IsOrfTypeTest_1556, ValidOrfBigEndianAdvanceFalse_1556) {
    byte orfHeader[] = {0x4D, 0x4D, 0x4F, 0x52, 0x00, 0x00, 0x00, 0x08};

    EXPECT_CALL(mockIo, read(_, 8))
        .WillOnce(DoAll(
            Invoke([&orfHeader](byte* buf, size_t rcount) {
                std::memcpy(buf, orfHeader, 8);
            }),
            Return(8)));
    EXPECT_CALL(mockIo, error()).WillRepeatedly(Return(0));
    EXPECT_CALL(mockIo, eof()).WillRepeatedly(Return(false));
    EXPECT_CALL(mockIo, seek(-8, BasicIo::cur)).WillOnce(Return(0));

    bool result = isOrfType(mockIo, false);
    EXPECT_TRUE(result);
}

// Test: Partial ORF-like data with wrong byte order marker
TEST_F(IsOrfTypeTest_1556, WrongByteOrderMarker_1556) {
    // Neither "II" nor "MM"
    byte wrongBOM[] = {0x41, 0x42, 0x52, 0x4F, 0x08, 0x00, 0x00, 0x00};

    EXPECT_CALL(mockIo, read(_, 8))
        .WillOnce(DoAll(
            Invoke([&wrongBOM](byte* buf, size_t rcount) {
                std::memcpy(buf, wrongBOM, 8);
            }),
            Return(8)));
    EXPECT_CALL(mockIo, error()).WillRepeatedly(Return(0));
    EXPECT_CALL(mockIo, eof()).WillRepeatedly(Return(false));
    EXPECT_CALL(mockIo, seek(-8, BasicIo::cur)).WillOnce(Return(0));

    bool result = isOrfType(mockIo, true);
    EXPECT_FALSE(result);
}

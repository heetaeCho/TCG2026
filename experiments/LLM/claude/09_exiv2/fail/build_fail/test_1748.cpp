#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <exiv2/basicio.hpp>
#include <exiv2/cr2image.hpp>
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
    MOCK_METHOD(size_t, tell, (), (const, override));
    MOCK_METHOD(size_t, size, (), (const, override));
    MOCK_METHOD(bool, isopen, (), (const, override));
    MOCK_METHOD(int, error, (), (const, override));
    MOCK_METHOD(bool, eof, (), (const, override));
    MOCK_METHOD(const std::string&, path, (), (const, override));
    MOCK_METHOD(void, populateFakeData, (), (override));
};

class IsCr2TypeTest_1748 : public ::testing::Test {
protected:
    MockBasicIo mockIo;
};

// Test: When read returns an error, isCr2Type should return false
TEST_F(IsCr2TypeTest_1748, ReturnsFalseOnReadError_1748) {
    EXPECT_CALL(mockIo, read(_, 16))
        .WillOnce(Return(0));
    EXPECT_CALL(mockIo, error())
        .WillOnce(Return(1));  // simulate error
    // Should not call eof if error is true, but we allow it
    EXPECT_CALL(mockIo, eof())
        .Times(::testing::AnyNumber())
        .WillRepeatedly(Return(false));
    // Since it fails, it should return false (no seek back needed for error case)
    EXPECT_CALL(mockIo, seek(_, _))
        .Times(::testing::AnyNumber())
        .WillRepeatedly(Return(0));

    bool result = isCr2Type(mockIo, false);
    EXPECT_FALSE(result);
}

// Test: When read hits EOF, isCr2Type should return false
TEST_F(IsCr2TypeTest_1748, ReturnsFalseOnEof_1748) {
    EXPECT_CALL(mockIo, read(_, 16))
        .WillOnce(Return(0));
    EXPECT_CALL(mockIo, error())
        .WillOnce(Return(0));  // no error
    EXPECT_CALL(mockIo, eof())
        .WillOnce(Return(true));  // but EOF
    EXPECT_CALL(mockIo, seek(_, _))
        .Times(::testing::AnyNumber())
        .WillRepeatedly(Return(0));

    bool result = isCr2Type(mockIo, false);
    EXPECT_FALSE(result);
}

// Test: With invalid CR2 data and advance=false, should seek back and return false
TEST_F(IsCr2TypeTest_1748, ReturnsFalseForNonCr2Data_1748) {
    byte invalidData[16] = {0};  // All zeros - not valid CR2

    EXPECT_CALL(mockIo, read(_, 16))
        .WillOnce(DoAll(
            SetArrayArgument<0>(invalidData, invalidData + 16),
            Return(16)));
    EXPECT_CALL(mockIo, error())
        .WillOnce(Return(0));
    EXPECT_CALL(mockIo, eof())
        .WillOnce(Return(false));
    // Should seek back since advance=false or rc=false
    EXPECT_CALL(mockIo, seek(-16, BasicIo::cur))
        .WillOnce(Return(0));

    bool result = isCr2Type(mockIo, false);
    EXPECT_FALSE(result);
}

// Test: With invalid CR2 data and advance=true, should seek back (rc is false)
TEST_F(IsCr2TypeTest_1748, ReturnsFalseForNonCr2DataAdvanceTrue_1748) {
    byte invalidData[16] = {0};

    EXPECT_CALL(mockIo, read(_, 16))
        .WillOnce(DoAll(
            SetArrayArgument<0>(invalidData, invalidData + 16),
            Return(16)));
    EXPECT_CALL(mockIo, error())
        .WillOnce(Return(0));
    EXPECT_CALL(mockIo, eof())
        .WillOnce(Return(false));
    // Since rc=false, seek back regardless of advance
    EXPECT_CALL(mockIo, seek(-16, BasicIo::cur))
        .WillOnce(Return(0));

    bool result = isCr2Type(mockIo, true);
    EXPECT_FALSE(result);
}

// Test: With valid CR2 header data and advance=true, should NOT seek back, return true
TEST_F(IsCr2TypeTest_1748, ReturnsTrueForValidCr2DataAdvanceTrue_1748) {
    // Valid CR2 header: little-endian TIFF header + CR2 magic
    // Byte order: II (little-endian) = 0x49 0x49
    // TIFF magic: 42 = 0x002A (LE)
    // Offset to first IFD: 0x00000010
    // CR2 magic: "CR" = 0x43 0x52, major version 2, minor version 0
    byte validCr2[16] = {
        0x49, 0x49,       // "II" - little endian
        0x2A, 0x00,       // TIFF magic 42
        0x10, 0x00, 0x00, 0x00, // offset to IFD0 = 16
        0x43, 0x52,       // "CR"
        0x02, 0x00,       // CR2 version 2.0
        0x00, 0x00, 0x00, 0x00  // offset2
    };

    EXPECT_CALL(mockIo, read(_, 16))
        .WillOnce(DoAll(
            SetArrayArgument<0>(validCr2, validCr2 + 16),
            Return(16)));
    EXPECT_CALL(mockIo, error())
        .WillOnce(Return(0));
    EXPECT_CALL(mockIo, eof())
        .WillOnce(Return(false));
    // With advance=true and valid CR2, should NOT seek back
    EXPECT_CALL(mockIo, seek(_, _))
        .Times(0);

    bool result = isCr2Type(mockIo, true);
    EXPECT_TRUE(result);
}

// Test: With valid CR2 header data and advance=false, should seek back, return true
TEST_F(IsCr2TypeTest_1748, ReturnsTrueForValidCr2DataAdvanceFalse_1748) {
    byte validCr2[16] = {
        0x49, 0x49,       // "II" - little endian
        0x2A, 0x00,       // TIFF magic 42
        0x10, 0x00, 0x00, 0x00, // offset to IFD0 = 16
        0x43, 0x52,       // "CR"
        0x02, 0x00,       // CR2 version 2.0
        0x00, 0x00, 0x00, 0x00  // offset2
    };

    EXPECT_CALL(mockIo, read(_, 16))
        .WillOnce(DoAll(
            SetArrayArgument<0>(validCr2, validCr2 + 16),
            Return(16)));
    EXPECT_CALL(mockIo, error())
        .WillOnce(Return(0));
    EXPECT_CALL(mockIo, eof())
        .WillOnce(Return(false));
    // With advance=false, should seek back even though it's valid CR2
    EXPECT_CALL(mockIo, seek(-16, BasicIo::cur))
        .WillOnce(Return(0));

    bool result = isCr2Type(mockIo, false);
    EXPECT_TRUE(result);
}

// Test: Valid CR2 header with big-endian byte order
TEST_F(IsCr2TypeTest_1748, ReturnsTrueForValidCr2BigEndian_1748) {
    byte validCr2BE[16] = {
        0x4D, 0x4D,       // "MM" - big endian
        0x00, 0x2A,       // TIFF magic 42 (big endian)
        0x00, 0x00, 0x00, 0x10, // offset to IFD0 = 16 (big endian)
        0x43, 0x52,       // "CR"
        0x02, 0x00,       // CR2 version 2.0
        0x00, 0x00, 0x00, 0x00  // offset2
    };

    EXPECT_CALL(mockIo, read(_, 16))
        .WillOnce(DoAll(
            SetArrayArgument<0>(validCr2BE, validCr2BE + 16),
            Return(16)));
    EXPECT_CALL(mockIo, error())
        .WillOnce(Return(0));
    EXPECT_CALL(mockIo, eof())
        .WillOnce(Return(false));
    EXPECT_CALL(mockIo, seek(_, _))
        .Times(0);

    bool result = isCr2Type(mockIo, true);
    EXPECT_TRUE(result);
}

// Test: Data with correct TIFF header but wrong CR2 magic
TEST_F(IsCr2TypeTest_1748, ReturnsFalseForTiffButNotCr2_1748) {
    // Valid TIFF header but no CR2 signature
    byte tiffOnly[16] = {
        0x49, 0x49,       // "II" - little endian
        0x2A, 0x00,       // TIFF magic 42
        0x08, 0x00, 0x00, 0x00, // offset to IFD0 = 8
        0x00, 0x00,       // NOT "CR"
        0x00, 0x00,
        0x00, 0x00, 0x00, 0x00
    };

    EXPECT_CALL(mockIo, read(_, 16))
        .WillOnce(DoAll(
            SetArrayArgument<0>(tiffOnly, tiffOnly + 16),
            Return(16)));
    EXPECT_CALL(mockIo, error())
        .WillOnce(Return(0));
    EXPECT_CALL(mockIo, eof())
        .WillOnce(Return(false));
    EXPECT_CALL(mockIo, seek(-16, BasicIo::cur))
        .WillOnce(Return(0));

    bool result = isCr2Type(mockIo, true);
    EXPECT_FALSE(result);
}

// Test: Data with wrong byte order marker
TEST_F(IsCr2TypeTest_1748, ReturnsFalseForWrongByteOrder_1748) {
    byte wrongByteOrder[16] = {
        0x00, 0x00,       // Invalid byte order
        0x2A, 0x00,
        0x10, 0x00, 0x00, 0x00,
        0x43, 0x52,
        0x02, 0x00,
        0x00, 0x00, 0x00, 0x00
    };

    EXPECT_CALL(mockIo, read(_, 16))
        .WillOnce(DoAll(
            SetArrayArgument<0>(wrongByteOrder, wrongByteOrder + 16),
            Return(16)));
    EXPECT_CALL(mockIo, error())
        .WillOnce(Return(0));
    EXPECT_CALL(mockIo, eof())
        .WillOnce(Return(false));
    EXPECT_CALL(mockIo, seek(-16, BasicIo::cur))
        .WillOnce(Return(0));

    bool result = isCr2Type(mockIo, false);
    EXPECT_FALSE(result);
}

// Test: Both error and eof are true
TEST_F(IsCr2TypeTest_1748, ReturnsFalseOnBothErrorAndEof_1748) {
    EXPECT_CALL(mockIo, read(_, 16))
        .WillOnce(Return(0));
    EXPECT_CALL(mockIo, error())
        .WillOnce(Return(1));
    EXPECT_CALL(mockIo, eof())
        .Times(::testing::AnyNumber())
        .WillRepeatedly(Return(true));
    EXPECT_CALL(mockIo, seek(_, _))
        .Times(::testing::AnyNumber())
        .WillRepeatedly(Return(0));

    bool result = isCr2Type(mockIo, true);
    EXPECT_FALSE(result);
}

// Test: Partial read (less than 16 bytes) but no error/eof flags
// The header.read might fail due to insufficient/corrupted data
TEST_F(IsCr2TypeTest_1748, ReturnsFalseForPartialReadNoFlags_1748) {
    byte partialData[16] = {0x49, 0x49, 0x2A, 0x00, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    EXPECT_CALL(mockIo, read(_, 16))
        .WillOnce(DoAll(
            SetArrayArgument<0>(partialData, partialData + 16),
            Return(8)));  // only 8 bytes actually read
    EXPECT_CALL(mockIo, error())
        .WillOnce(Return(0));
    EXPECT_CALL(mockIo, eof())
        .WillOnce(Return(false));
    // Header read may succeed or fail depending on implementation
    // but we expect seek back in case of failure
    EXPECT_CALL(mockIo, seek(_, _))
        .Times(::testing::AnyNumber())
        .WillRepeatedly(Return(0));

    // We just verify it doesn't crash
    isCr2Type(mockIo, false);
}

// Integration-like test using MemIo with valid CR2 data
TEST(IsCr2TypeMemIoTest_1748, ValidCr2WithMemIoAdvanceTrue_1748) {
    byte validCr2[16] = {
        0x49, 0x49,
        0x2A, 0x00,
        0x10, 0x00, 0x00, 0x00,
        0x43, 0x52,
        0x02, 0x00,
        0x00, 0x00, 0x00, 0x00
    };

    MemIo memIo(validCr2, 16);
    bool result = isCr2Type(memIo, true);
    EXPECT_TRUE(result);
    // After advance=true with valid data, position should be at 16 (past the header)
    EXPECT_EQ(memIo.tell(), 16u);
}

TEST(IsCr2TypeMemIoTest_1748, ValidCr2WithMemIoAdvanceFalse_1748) {
    byte validCr2[16] = {
        0x49, 0x49,
        0x2A, 0x00,
        0x10, 0x00, 0x00, 0x00,
        0x43, 0x52,
        0x02, 0x00,
        0x00, 0x00, 0x00, 0x00
    };

    MemIo memIo(validCr2, 16);
    bool result = isCr2Type(memIo, false);
    EXPECT_TRUE(result);
    // After advance=false, position should be back at 0
    EXPECT_EQ(memIo.tell(), 0u);
}

TEST(IsCr2TypeMemIoTest_1748, InvalidDataWithMemIo_1748) {
    byte invalidData[16] = {0};

    MemIo memIo(invalidData, 16);
    bool result = isCr2Type(memIo, true);
    EXPECT_FALSE(result);
    // Position should be back at 0 since rc was false
    EXPECT_EQ(memIo.tell(), 0u);
}

TEST(IsCr2TypeMemIoTest_1748, EmptyMemIo_1748) {
    MemIo memIo;
    bool result = isCr2Type(memIo, true);
    EXPECT_FALSE(result);
}

TEST(IsCr2TypeMemIoTest_1748, TooSmallData_1748) {
    byte smallData[8] = {0x49, 0x49, 0x2A, 0x00, 0x10, 0x00, 0x00, 0x00};

    MemIo memIo(smallData, 8);
    bool result = isCr2Type(memIo, true);
    EXPECT_FALSE(result);
}

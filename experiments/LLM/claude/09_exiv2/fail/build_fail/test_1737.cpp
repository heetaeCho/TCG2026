#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <exiv2/basicio.hpp>
#include <exiv2/image.hpp>
#include <cstring>

// We need access to isTiffType
namespace Exiv2 {
bool isTiffType(BasicIo& iIo, bool advance);
}

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
    MOCK_METHOD(size_t, tell, (), (const, override));
    MOCK_METHOD(size_t, size, (), (const, override));
    MOCK_METHOD(bool, isopen, (), (const, override));
    MOCK_METHOD(int, error, (), (const, override));
    MOCK_METHOD(bool, eof, (), (const, override));
    MOCK_METHOD(const std::string&, path, (), (const, override));
    MOCK_METHOD(void, populateFakeData, (), (override));
};

using ::testing::_;
using ::testing::Return;
using ::testing::DoAll;
using ::testing::SetArrayArgument;
using ::testing::Invoke;

class IsTiffTypeTest_1737 : public ::testing::Test {
protected:
    MockBasicIo mockIo;
};

// Valid little-endian TIFF header: "II" + 42 (0x2A00) + offset 8 (0x08000000)
static const Exiv2::byte validTiffLE[] = {0x49, 0x49, 0x2A, 0x00, 0x08, 0x00, 0x00, 0x00};

// Valid big-endian TIFF header: "MM" + 42 (0x002A) + offset 8 (0x00000008)
static const Exiv2::byte validTiffBE[] = {0x4D, 0x4D, 0x00, 0x2A, 0x00, 0x00, 0x00, 0x08};

// Invalid header - random bytes
static const Exiv2::byte invalidTiff[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

// Test: Valid little-endian TIFF with advance=true should return true and not seek back
TEST_F(IsTiffTypeTest_1737, ValidLittleEndianTiffAdvanceTrue_1737) {
    EXPECT_CALL(mockIo, read(_, 8))
        .WillOnce(DoAll(
            Invoke([](Exiv2::byte* buf, size_t) {
                std::memcpy(buf, validTiffLE, 8);
            }),
            Return(8)));
    EXPECT_CALL(mockIo, error()).WillRepeatedly(Return(0));
    EXPECT_CALL(mockIo, eof()).WillRepeatedly(Return(false));
    // With advance=true and valid TIFF, seek should NOT be called
    EXPECT_CALL(mockIo, seek(_, _)).Times(0);

    bool result = Exiv2::isTiffType(mockIo, true);
    EXPECT_TRUE(result);
}

// Test: Valid big-endian TIFF with advance=true should return true
TEST_F(IsTiffTypeTest_1737, ValidBigEndianTiffAdvanceTrue_1737) {
    EXPECT_CALL(mockIo, read(_, 8))
        .WillOnce(DoAll(
            Invoke([](Exiv2::byte* buf, size_t) {
                std::memcpy(buf, validTiffBE, 8);
            }),
            Return(8)));
    EXPECT_CALL(mockIo, error()).WillRepeatedly(Return(0));
    EXPECT_CALL(mockIo, eof()).WillRepeatedly(Return(false));
    EXPECT_CALL(mockIo, seek(_, _)).Times(0);

    bool result = Exiv2::isTiffType(mockIo, true);
    EXPECT_TRUE(result);
}

// Test: Valid TIFF with advance=false should return true but seek back
TEST_F(IsTiffTypeTest_1737, ValidTiffAdvanceFalse_1737) {
    EXPECT_CALL(mockIo, read(_, 8))
        .WillOnce(DoAll(
            Invoke([](Exiv2::byte* buf, size_t) {
                std::memcpy(buf, validTiffLE, 8);
            }),
            Return(8)));
    EXPECT_CALL(mockIo, error()).WillRepeatedly(Return(0));
    EXPECT_CALL(mockIo, eof()).WillRepeatedly(Return(false));
    // With advance=false, should seek back even if valid
    EXPECT_CALL(mockIo, seek(-8, Exiv2::BasicIo::cur)).WillOnce(Return(0));

    bool result = Exiv2::isTiffType(mockIo, false);
    EXPECT_TRUE(result);
}

// Test: Invalid TIFF data with advance=true should return false and seek back
TEST_F(IsTiffTypeTest_1737, InvalidTiffAdvanceTrue_1737) {
    EXPECT_CALL(mockIo, read(_, 8))
        .WillOnce(DoAll(
            Invoke([](Exiv2::byte* buf, size_t) {
                std::memcpy(buf, invalidTiff, 8);
            }),
            Return(8)));
    EXPECT_CALL(mockIo, error()).WillRepeatedly(Return(0));
    EXPECT_CALL(mockIo, eof()).WillRepeatedly(Return(false));
    // When rc is false, should seek back regardless of advance
    EXPECT_CALL(mockIo, seek(-8, Exiv2::BasicIo::cur)).WillOnce(Return(0));

    bool result = Exiv2::isTiffType(mockIo, true);
    EXPECT_FALSE(result);
}

// Test: Invalid TIFF data with advance=false should return false and seek back
TEST_F(IsTiffTypeTest_1737, InvalidTiffAdvanceFalse_1737) {
    EXPECT_CALL(mockIo, read(_, 8))
        .WillOnce(DoAll(
            Invoke([](Exiv2::byte* buf, size_t) {
                std::memcpy(buf, invalidTiff, 8);
            }),
            Return(8)));
    EXPECT_CALL(mockIo, error()).WillRepeatedly(Return(0));
    EXPECT_CALL(mockIo, eof()).WillRepeatedly(Return(false));
    EXPECT_CALL(mockIo, seek(-8, Exiv2::BasicIo::cur)).WillOnce(Return(0));

    bool result = Exiv2::isTiffType(mockIo, false);
    EXPECT_FALSE(result);
}

// Test: IO error during read should return false
TEST_F(IsTiffTypeTest_1737, IoErrorDuringRead_1737) {
    EXPECT_CALL(mockIo, read(_, 8))
        .WillOnce(Return(0));
    EXPECT_CALL(mockIo, error()).WillRepeatedly(Return(1)); // error occurred
    EXPECT_CALL(mockIo, eof()).WillRepeatedly(Return(false));

    bool result = Exiv2::isTiffType(mockIo, true);
    EXPECT_FALSE(result);
}

// Test: EOF during read should return false
TEST_F(IsTiffTypeTest_1737, EofDuringRead_1737) {
    EXPECT_CALL(mockIo, read(_, 8))
        .WillOnce(Return(0));
    EXPECT_CALL(mockIo, error()).WillRepeatedly(Return(0));
    EXPECT_CALL(mockIo, eof()).WillRepeatedly(Return(true));

    bool result = Exiv2::isTiffType(mockIo, true);
    EXPECT_FALSE(result);
}

// Test: Both IO error and EOF should return false
TEST_F(IsTiffTypeTest_1737, IoErrorAndEof_1737) {
    EXPECT_CALL(mockIo, read(_, 8))
        .WillOnce(Return(0));
    EXPECT_CALL(mockIo, error()).WillRepeatedly(Return(1));
    EXPECT_CALL(mockIo, eof()).WillRepeatedly(Return(true));

    bool result = Exiv2::isTiffType(mockIo, true);
    EXPECT_FALSE(result);
}

// Test: Wrong byte order marker should return false
TEST_F(IsTiffTypeTest_1737, WrongByteOrderMarker_1737) {
    // "XX" instead of "II" or "MM"
    Exiv2::byte wrongBOM[] = {0x58, 0x58, 0x2A, 0x00, 0x08, 0x00, 0x00, 0x00};
    EXPECT_CALL(mockIo, read(_, 8))
        .WillOnce(DoAll(
            Invoke([&wrongBOM](Exiv2::byte* buf, size_t) {
                std::memcpy(buf, wrongBOM, 8);
            }),
            Return(8)));
    EXPECT_CALL(mockIo, error()).WillRepeatedly(Return(0));
    EXPECT_CALL(mockIo, eof()).WillRepeatedly(Return(false));
    EXPECT_CALL(mockIo, seek(-8, Exiv2::BasicIo::cur)).WillOnce(Return(0));

    bool result = Exiv2::isTiffType(mockIo, true);
    EXPECT_FALSE(result);
}

// Test: Wrong magic number (not 42) should return false
TEST_F(IsTiffTypeTest_1737, WrongMagicNumber_1737) {
    // "II" with magic 43 instead of 42
    Exiv2::byte wrongMagic[] = {0x49, 0x49, 0x2B, 0x00, 0x08, 0x00, 0x00, 0x00};
    EXPECT_CALL(mockIo, read(_, 8))
        .WillOnce(DoAll(
            Invoke([&wrongMagic](Exiv2::byte* buf, size_t) {
                std::memcpy(buf, wrongMagic, 8);
            }),
            Return(8)));
    EXPECT_CALL(mockIo, error()).WillRepeatedly(Return(0));
    EXPECT_CALL(mockIo, eof()).WillRepeatedly(Return(false));
    EXPECT_CALL(mockIo, seek(-8, Exiv2::BasicIo::cur)).WillOnce(Return(0));

    bool result = Exiv2::isTiffType(mockIo, true);
    EXPECT_FALSE(result);
}

// Test: Using MemIo with valid TIFF little-endian data
TEST_F(IsTiffTypeTest_1737, MemIoValidTiffLE_1737) {
    Exiv2::MemIo memIo(validTiffLE, 8);
    bool result = Exiv2::isTiffType(memIo, true);
    EXPECT_TRUE(result);
}

// Test: Using MemIo with valid TIFF big-endian data
TEST_F(IsTiffTypeTest_1737, MemIoValidTiffBE_1737) {
    Exiv2::MemIo memIo(validTiffBE, 8);
    bool result = Exiv2::isTiffType(memIo, true);
    EXPECT_TRUE(result);
}

// Test: Using MemIo with invalid data
TEST_F(IsTiffTypeTest_1737, MemIoInvalidData_1737) {
    Exiv2::MemIo memIo(invalidTiff, 8);
    bool result = Exiv2::isTiffType(memIo, true);
    EXPECT_FALSE(result);
}

// Test: Using MemIo with valid data and advance=false should seek back
TEST_F(IsTiffTypeTest_1737, MemIoValidTiffAdvanceFalseSeeksBack_1737) {
    Exiv2::MemIo memIo(validTiffLE, 8);
    bool result = Exiv2::isTiffType(memIo, false);
    EXPECT_TRUE(result);
    // After advance=false, position should be back to 0
    EXPECT_EQ(memIo.tell(), 0u);
}

// Test: Using MemIo with valid data and advance=true should advance position
TEST_F(IsTiffTypeTest_1737, MemIoValidTiffAdvanceTrueAdvancesPosition_1737) {
    Exiv2::MemIo memIo(validTiffLE, 8);
    bool result = Exiv2::isTiffType(memIo, true);
    EXPECT_TRUE(result);
    // After advance=true with valid TIFF, position should be at 8
    EXPECT_EQ(memIo.tell(), 8u);
}

// Test: Using MemIo with invalid data and advance=true should seek back
TEST_F(IsTiffTypeTest_1737, MemIoInvalidDataAdvanceTrueSeeksBack_1737) {
    Exiv2::MemIo memIo(invalidTiff, 8);
    bool result = Exiv2::isTiffType(memIo, false);
    EXPECT_FALSE(result);
    // Position should be back to 0 since rc was false
    EXPECT_EQ(memIo.tell(), 0u);
}

// Test: Empty MemIo should return false (not enough data)
TEST_F(IsTiffTypeTest_1737, EmptyMemIo_1737) {
    Exiv2::MemIo memIo;
    bool result = Exiv2::isTiffType(memIo, true);
    EXPECT_FALSE(result);
}

// Test: MemIo with less than 8 bytes should return false
TEST_F(IsTiffTypeTest_1737, TooSmallData_1737) {
    Exiv2::byte smallData[] = {0x49, 0x49, 0x2A, 0x00};
    Exiv2::MemIo memIo(smallData, 4);
    bool result = Exiv2::isTiffType(memIo, true);
    EXPECT_FALSE(result);
}

// Test: Mixed byte order markers (e.g., "IM") should be invalid
TEST_F(IsTiffTypeTest_1737, MixedByteOrderMarkers_1737) {
    Exiv2::byte mixedBOM[] = {0x49, 0x4D, 0x2A, 0x00, 0x08, 0x00, 0x00, 0x00};
    Exiv2::MemIo memIo(mixedBOM, 8);
    bool result = Exiv2::isTiffType(memIo, true);
    EXPECT_FALSE(result);
}

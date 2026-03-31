#include <gtest/gtest.h>
#include <cstring>
#include <vector>
#include <cstdint>

// We need to include the relevant headers from exiv2
#include "makernote_int.hpp"
#include "types.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class FujiMnHeaderTest_1458 : public ::testing::Test {
protected:
    FujiMnHeader header_;
};

// Test that read returns false when pData is nullptr
TEST_F(FujiMnHeaderTest_1458, ReadNullPointerReturnsFalse_1458) {
    bool result = header_.read(nullptr, 100, littleEndian);
    EXPECT_FALSE(result);
}

// Test that read returns false when size is 0
TEST_F(FujiMnHeaderTest_1458, ReadZeroSizeReturnsFalse_1458) {
    byte data[1] = {0};
    bool result = header_.read(data, 0, littleEndian);
    EXPECT_FALSE(result);
}

// Test that read returns false when size is less than the signature size
TEST_F(FujiMnHeaderTest_1458, ReadSizeTooSmallReturnsFalse_1458) {
    // The Fuji signature is "FUJIFILM" (8 bytes) + 4 bytes for offset = 12 bytes typically
    // sizeOfSignature() should return the minimum required size
    byte data[4] = {0x46, 0x55, 0x4A, 0x49}; // "FUJI" partial
    bool result = header_.read(data, 4, littleEndian);
    EXPECT_FALSE(result);
}

// Test that read returns false when data doesn't match the Fuji signature
TEST_F(FujiMnHeaderTest_1458, ReadInvalidSignatureReturnsFalse_1458) {
    // Create data that is large enough but has wrong signature
    std::vector<byte> data(12, 0);
    // Fill with garbage that doesn't match "FUJIFILM"
    data[0] = 'N';
    data[1] = 'O';
    data[2] = 'T';
    data[3] = 'F';
    data[4] = 'U';
    data[5] = 'J';
    data[6] = 'I';
    data[7] = '!';
    // offset bytes
    data[8] = 0x0C;
    data[9] = 0x00;
    data[10] = 0x00;
    data[11] = 0x00;

    bool result = header_.read(data.data(), data.size(), littleEndian);
    EXPECT_FALSE(result);
}

// Test that read succeeds with valid Fuji MakerNote header
TEST_F(FujiMnHeaderTest_1458, ReadValidFujiHeaderReturnsTrue_1458) {
    // Fuji MakerNote signature: "FUJIFILM" followed by a 4-byte offset (little-endian in Fuji's own byte order)
    std::vector<byte> data(12, 0);
    // "FUJIFILM"
    data[0] = 'F';
    data[1] = 'U';
    data[2] = 'J';
    data[3] = 'I';
    data[4] = 'F';
    data[5] = 'I';
    data[6] = 'L';
    data[7] = 'M';
    // Offset (little-endian): 12 = 0x0C
    data[8] = 0x0C;
    data[9] = 0x00;
    data[10] = 0x00;
    data[11] = 0x00;

    bool result = header_.read(data.data(), data.size(), littleEndian);
    EXPECT_TRUE(result);
}

// Test that read returns false when only first part of signature matches
TEST_F(FujiMnHeaderTest_1458, ReadPartialSignatureReturnsFalse_1458) {
    std::vector<byte> data(12, 0);
    // "FUJIFIL" + wrong last byte
    data[0] = 'F';
    data[1] = 'U';
    data[2] = 'J';
    data[3] = 'I';
    data[4] = 'F';
    data[5] = 'I';
    data[6] = 'L';
    data[7] = 'X'; // Should be 'M'
    data[8] = 0x0C;
    data[9] = 0x00;
    data[10] = 0x00;
    data[11] = 0x00;

    bool result = header_.read(data.data(), data.size(), littleEndian);
    EXPECT_FALSE(result);
}

// Test that read works with exactly the minimum required size
TEST_F(FujiMnHeaderTest_1458, ReadExactMinimumSizeReturnsTrue_1458) {
    // sizeOfSignature() is typically 12 for Fuji
    std::vector<byte> data(12);
    data[0] = 'F';
    data[1] = 'U';
    data[2] = 'J';
    data[3] = 'I';
    data[4] = 'F';
    data[5] = 'I';
    data[6] = 'L';
    data[7] = 'M';
    data[8] = 0x0C;
    data[9] = 0x00;
    data[10] = 0x00;
    data[11] = 0x00;

    bool result = header_.read(data.data(), 12, littleEndian);
    EXPECT_TRUE(result);
}

// Test that read works with larger data containing valid header
TEST_F(FujiMnHeaderTest_1458, ReadLargerDataWithValidHeaderReturnsTrue_1458) {
    std::vector<byte> data(256, 0);
    data[0] = 'F';
    data[1] = 'U';
    data[2] = 'J';
    data[3] = 'I';
    data[4] = 'F';
    data[5] = 'I';
    data[6] = 'L';
    data[7] = 'M';
    data[8] = 0x0C;
    data[9] = 0x00;
    data[10] = 0x00;
    data[11] = 0x00;

    bool result = header_.read(data.data(), data.size(), littleEndian);
    EXPECT_TRUE(result);
}

// Test with size exactly one less than signature size
TEST_F(FujiMnHeaderTest_1458, ReadOneByteLessThanSignatureSizeReturnsFalse_1458) {
    std::vector<byte> data(11, 0);
    data[0] = 'F';
    data[1] = 'U';
    data[2] = 'J';
    data[3] = 'I';
    data[4] = 'F';
    data[5] = 'I';
    data[6] = 'L';
    data[7] = 'M';
    data[8] = 0x0C;
    data[9] = 0x00;
    data[10] = 0x00;

    bool result = header_.read(data.data(), data.size(), littleEndian);
    EXPECT_FALSE(result);
}

// Test read with all zeros (wrong signature)
TEST_F(FujiMnHeaderTest_1458, ReadAllZerosReturnsFalse_1458) {
    std::vector<byte> data(12, 0);
    bool result = header_.read(data.data(), data.size(), littleEndian);
    EXPECT_FALSE(result);
}

// Test that read can be called multiple times (re-read with valid data)
TEST_F(FujiMnHeaderTest_1458, ReadCanBeCalledMultipleTimes_1458) {
    std::vector<byte> validData(12, 0);
    validData[0] = 'F';
    validData[1] = 'U';
    validData[2] = 'J';
    validData[3] = 'I';
    validData[4] = 'F';
    validData[5] = 'I';
    validData[6] = 'L';
    validData[7] = 'M';
    validData[8] = 0x0C;
    validData[9] = 0x00;
    validData[10] = 0x00;
    validData[11] = 0x00;

    // First read with invalid data
    std::vector<byte> invalidData(12, 0);
    bool result1 = header_.read(invalidData.data(), invalidData.size(), littleEndian);
    EXPECT_FALSE(result1);

    // Second read with valid data
    bool result2 = header_.read(validData.data(), validData.size(), littleEndian);
    EXPECT_TRUE(result2);
}

// Test with different byte order parameter (bigEndian) - the byte order parameter
// might not affect Fuji since it uses its own internal byte order
TEST_F(FujiMnHeaderTest_1458, ReadWithBigEndianByteOrder_1458) {
    std::vector<byte> data(12, 0);
    data[0] = 'F';
    data[1] = 'U';
    data[2] = 'J';
    data[3] = 'I';
    data[4] = 'F';
    data[5] = 'I';
    data[6] = 'L';
    data[7] = 'M';
    data[8] = 0x0C;
    data[9] = 0x00;
    data[10] = 0x00;
    data[11] = 0x00;

    // Fuji uses its own byte order internally, so the passed byte order may not matter
    bool result = header_.read(data.data(), data.size(), bigEndian);
    EXPECT_TRUE(result);
}

// Test with size = 1 (well below signature size)
TEST_F(FujiMnHeaderTest_1458, ReadSizeOneReturnsFalse_1458) {
    byte data[1] = {'F'};
    bool result = header_.read(data, 1, littleEndian);
    EXPECT_FALSE(result);
}

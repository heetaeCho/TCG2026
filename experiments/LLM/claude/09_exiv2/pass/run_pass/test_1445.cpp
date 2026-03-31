#include <gtest/gtest.h>
#include <cstring>

// Include necessary Exiv2 headers
#include "makernote_int.hpp"
#include "types.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class Olympus2MnHeaderTest_1445 : public ::testing::Test {
protected:
    Olympus2MnHeader header_;
};

// Test that read returns false when pData is nullptr
TEST_F(Olympus2MnHeaderTest_1445, ReadNullPointerReturnsFalse_1445) {
    bool result = header_.read(nullptr, 100, littleEndian);
    EXPECT_FALSE(result);
}

// Test that read returns false when size is 0
TEST_F(Olympus2MnHeaderTest_1445, ReadZeroSizeReturnsFalse_1445) {
    const byte data[1] = {0};
    bool result = header_.read(data, 0, littleEndian);
    EXPECT_FALSE(result);
}

// Test that read returns false when size is less than signature size
TEST_F(Olympus2MnHeaderTest_1445, ReadSizeTooSmallReturnsFalse_1445) {
    const byte data[5] = {0x4F, 0x4C, 0x59, 0x4D, 0x50};
    bool result = header_.read(data, 5, littleEndian);
    EXPECT_FALSE(result);
}

// Test that read returns false when data doesn't match signature
TEST_F(Olympus2MnHeaderTest_1445, ReadWrongSignatureReturnsFalse_1445) {
    // Provide enough data but with wrong signature
    const byte data[12] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    bool result = header_.read(data, 12, littleEndian);
    EXPECT_FALSE(result);
}

// Test that read returns true with valid Olympus II signature
// The Olympus II MakerNote signature is "OLYMPUS\0II"
TEST_F(Olympus2MnHeaderTest_1445, ReadValidSignatureReturnsTrue_1445) {
    // "OLYMPUS\0II" = {0x4F, 0x4C, 0x59, 0x4D, 0x50, 0x55, 0x53, 0x00, 0x49, 0x49}
    const byte data[12] = {0x4F, 0x4C, 0x59, 0x4D, 0x50, 0x55, 0x53, 0x00, 0x49, 0x49, 0x03, 0x00};
    bool result = header_.read(data, 12, littleEndian);
    EXPECT_TRUE(result);
}

// Test with exact minimum size matching signature
TEST_F(Olympus2MnHeaderTest_1445, ReadExactSignatureSizeReturnsTrue_1445) {
    const byte data[10] = {0x4F, 0x4C, 0x59, 0x4D, 0x50, 0x55, 0x53, 0x00, 0x49, 0x49};
    // sizeOfSignature() should be at least 10 based on the cmpBytes call
    bool result = header_.read(data, 10, littleEndian);
    EXPECT_TRUE(result);
}

// Test with big endian byte order - should still match same signature
TEST_F(Olympus2MnHeaderTest_1445, ReadValidSignatureBigEndian_1445) {
    const byte data[12] = {0x4F, 0x4C, 0x59, 0x4D, 0x50, 0x55, 0x53, 0x00, 0x49, 0x49, 0x03, 0x00};
    bool result = header_.read(data, 12, bigEndian);
    EXPECT_TRUE(result);
}

// Test that partially correct signature fails
TEST_F(Olympus2MnHeaderTest_1445, ReadPartiallyCorrectSignatureFails_1445) {
    // "OLYMPUS\0" correct but last two bytes wrong
    const byte data[12] = {0x4F, 0x4C, 0x59, 0x4D, 0x50, 0x55, 0x53, 0x00, 0x4D, 0x4D, 0x03, 0x00};
    bool result = header_.read(data, 12, littleEndian);
    EXPECT_FALSE(result);
}

// Test with size = 1, which should be less than sizeOfSignature
TEST_F(Olympus2MnHeaderTest_1445, ReadSize1ReturnsFalse_1445) {
    const byte data[1] = {0x4F};
    bool result = header_.read(data, 1, littleEndian);
    EXPECT_FALSE(result);
}

// Test that read can be called multiple times on the same object
TEST_F(Olympus2MnHeaderTest_1445, ReadCalledMultipleTimes_1445) {
    // First call with invalid data
    const byte badData[12] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    EXPECT_FALSE(header_.read(badData, 12, littleEndian));

    // Second call with valid data
    const byte goodData[12] = {0x4F, 0x4C, 0x59, 0x4D, 0x50, 0x55, 0x53, 0x00, 0x49, 0x49, 0x03, 0x00};
    EXPECT_TRUE(header_.read(goodData, 12, littleEndian));
}

// Test with nullptr and zero size
TEST_F(Olympus2MnHeaderTest_1445, ReadNullPointerZeroSizeReturnsFalse_1445) {
    bool result = header_.read(nullptr, 0, littleEndian);
    EXPECT_FALSE(result);
}

// Test with large buffer containing valid signature at start
TEST_F(Olympus2MnHeaderTest_1445, ReadLargeBufferWithValidSignature_1445) {
    byte data[1024] = {};
    data[0] = 0x4F; // O
    data[1] = 0x4C; // L
    data[2] = 0x59; // Y
    data[3] = 0x4D; // M
    data[4] = 0x50; // P
    data[5] = 0x55; // U
    data[6] = 0x53; // S
    data[7] = 0x00; // \0
    data[8] = 0x49; // I
    data[9] = 0x49; // I
    bool result = header_.read(data, 1024, littleEndian);
    EXPECT_TRUE(result);
}

// Test where the first byte of signature is wrong
TEST_F(Olympus2MnHeaderTest_1445, ReadFirstByteWrongReturnsFalse_1445) {
    const byte data[12] = {0x00, 0x4C, 0x59, 0x4D, 0x50, 0x55, 0x53, 0x00, 0x49, 0x49, 0x03, 0x00};
    bool result = header_.read(data, 12, littleEndian);
    EXPECT_FALSE(result);
}

#include <gtest/gtest.h>
#include <cstring>
#include <vector>

// We need to include the relevant Exiv2 headers to access the class under test
#include "makernote_int.hpp"
#include "types.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class PentaxDngMnHeaderTest_1482 : public ::testing::Test {
protected:
    PentaxDngMnHeader header_;
};

// Test that read returns false when pData is nullptr
TEST_F(PentaxDngMnHeaderTest_1482, ReadNullPointerReturnsFalse_1482) {
    bool result = header_.read(nullptr, 100, littleEndian);
    EXPECT_FALSE(result);
}

// Test that read returns false when size is 0
TEST_F(PentaxDngMnHeaderTest_1482, ReadZeroSizeReturnsFalse_1482) {
    const byte data[] = {0x41, 0x4F, 0x43, 0x00, 0x4D, 0x4D, 0x00};
    bool result = header_.read(data, 0, littleEndian);
    EXPECT_FALSE(result);
}

// Test that read returns false when size is less than the signature size
TEST_F(PentaxDngMnHeaderTest_1482, ReadSizeTooSmallReturnsFalse_1482) {
    const byte data[] = {0x41, 0x4F, 0x43};
    bool result = header_.read(data, 3, littleEndian);
    EXPECT_FALSE(result);
}

// Test that read returns false when data doesn't match the signature
TEST_F(PentaxDngMnHeaderTest_1482, ReadInvalidSignatureReturnsFalse_1482) {
    // Create data that definitely doesn't match any known Pentax DNG signature
    std::vector<byte> data(72, 0x00);
    bool result = header_.read(data.data(), data.size(), littleEndian);
    EXPECT_FALSE(result);
}

// Test that read returns true with the correct Pentax DNG maker note signature
// The Pentax DNG signature is "AOC\0MM\0" (7 bytes)
TEST_F(PentaxDngMnHeaderTest_1482, ReadValidSignatureReturnsTrue_1482) {
    // "AOC\0MM\0" is the known Pentax DNG maker note signature
    std::vector<byte> data = {0x41, 0x4F, 0x43, 0x00, 0x4D, 0x4D, 0x00};
    // Pad to a reasonable size
    data.resize(72, 0x00);
    bool result = header_.read(data.data(), data.size(), bigEndian);
    EXPECT_TRUE(result);
}

// Test that read with exactly the signature size works for valid signature
TEST_F(PentaxDngMnHeaderTest_1482, ReadExactSignatureSizeValidData_1482) {
    // Minimum required: at least sizeOfSignature() bytes
    // The signature is 7 bytes: "AOC\0MM\0"
    std::vector<byte> data = {0x41, 0x4F, 0x43, 0x00, 0x4D, 0x4D, 0x00};
    // sizeOfSignature() is likely larger than 7, so we need to figure out the actual size
    // Based on the code, header_.alloc(sizeOfSignature()) and cmpBytes checks first 7 bytes
    // We'll try with sufficient data
    data.resize(100, 0x00);
    bool result = header_.read(data.data(), data.size(), littleEndian);
    EXPECT_TRUE(result);
}

// Test that read with partially matching signature returns false
TEST_F(PentaxDngMnHeaderTest_1482, ReadPartiallyMatchingSignatureReturnsFalse_1482) {
    // "AOC\0" followed by incorrect bytes
    std::vector<byte> data = {0x41, 0x4F, 0x43, 0x00, 0x00, 0x00, 0x00};
    data.resize(72, 0x00);
    bool result = header_.read(data.data(), data.size(), littleEndian);
    EXPECT_FALSE(result);
}

// Test read with different byte orders - the signature check should be byte-order independent
TEST_F(PentaxDngMnHeaderTest_1482, ReadValidSignatureBigEndian_1482) {
    std::vector<byte> data = {0x41, 0x4F, 0x43, 0x00, 0x4D, 0x4D, 0x00};
    data.resize(72, 0x00);
    bool result = header_.read(data.data(), data.size(), bigEndian);
    EXPECT_TRUE(result);
}

TEST_F(PentaxDngMnHeaderTest_1482, ReadValidSignatureLittleEndian_1482) {
    std::vector<byte> data = {0x41, 0x4F, 0x43, 0x00, 0x4D, 0x4D, 0x00};
    data.resize(72, 0x00);
    bool result = header_.read(data.data(), data.size(), littleEndian);
    EXPECT_TRUE(result);
}

// Test that read returns false when data is all 0xFF
TEST_F(PentaxDngMnHeaderTest_1482, ReadAllOnesReturnsFalse_1482) {
    std::vector<byte> data(72, 0xFF);
    bool result = header_.read(data.data(), data.size(), littleEndian);
    EXPECT_FALSE(result);
}

// Test with size exactly 1 (less than signature size)
TEST_F(PentaxDngMnHeaderTest_1482, ReadSizeOneReturnsFalse_1482) {
    const byte data[] = {0x41};
    bool result = header_.read(data, 1, littleEndian);
    EXPECT_FALSE(result);
}

// Test with size exactly 6 (one less than 7-byte signature comparison)
TEST_F(PentaxDngMnHeaderTest_1482, ReadSizeSixReturnsFalse_1482) {
    const byte data[] = {0x41, 0x4F, 0x43, 0x00, 0x4D, 0x4D};
    bool result = header_.read(data, 6, littleEndian);
    EXPECT_FALSE(result);
}

// Test sizeOfSignature accessor
TEST_F(PentaxDngMnHeaderTest_1482, SizeOfSignatureIsPositive_1482) {
    EXPECT_GT(header_.sizeOfSignature(), static_cast<size_t>(0));
}

// Test that calling read multiple times works (object can be reused)
TEST_F(PentaxDngMnHeaderTest_1482, ReadCanBeCalledMultipleTimes_1482) {
    // First call with invalid data
    std::vector<byte> invalidData(72, 0x00);
    EXPECT_FALSE(header_.read(invalidData.data(), invalidData.size(), littleEndian));

    // Second call with valid data
    std::vector<byte> validData = {0x41, 0x4F, 0x43, 0x00, 0x4D, 0x4D, 0x00};
    validData.resize(72, 0x00);
    EXPECT_TRUE(header_.read(validData.data(), validData.size(), littleEndian));
}

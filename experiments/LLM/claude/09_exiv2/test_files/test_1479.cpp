#include <gtest/gtest.h>
#include "makernote_int.hpp"
#include "types.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class PentaxDngMnHeaderTest_1479 : public ::testing::Test {
protected:
    PentaxDngMnHeader header_;
};

// Test that a default-constructed PentaxDngMnHeader has a specific size
TEST_F(PentaxDngMnHeaderTest_1479, DefaultConstructorSize_1479) {
    // The header should have a well-defined size after construction
    size_t sz = header_.size();
    // sizeOfSignature() is a static method that returns the signature size
    size_t sigSize = PentaxDngMnHeader::sizeOfSignature();
    // The size should be at least as large as the signature
    EXPECT_GE(sz, sigSize);
}

// Test sizeOfSignature returns a consistent value
TEST_F(PentaxDngMnHeaderTest_1479, SizeOfSignatureConsistent_1479) {
    size_t sig1 = PentaxDngMnHeader::sizeOfSignature();
    size_t sig2 = PentaxDngMnHeader::sizeOfSignature();
    EXPECT_EQ(sig1, sig2);
    EXPECT_GT(sig1, 0u);
}

// Test that size() returns a non-zero value (the header_ member should have content)
TEST_F(PentaxDngMnHeaderTest_1479, SizeNonZero_1479) {
    EXPECT_GT(header_.size(), 0u);
}

// Test ifdOffset returns a value (typically 0 for Pentax DNG headers or the signature size)
TEST_F(PentaxDngMnHeaderTest_1479, IfdOffset_1479) {
    size_t offset = header_.ifdOffset();
    // ifdOffset should be a reasonable value, at least 0
    EXPECT_GE(offset, 0u);
}

// Test baseOffset with mnOffset = 0
TEST_F(PentaxDngMnHeaderTest_1479, BaseOffsetZero_1479) {
    size_t base = header_.baseOffset(0);
    EXPECT_GE(base, 0u);
}

// Test baseOffset with a non-zero mnOffset
TEST_F(PentaxDngMnHeaderTest_1479, BaseOffsetNonZero_1479) {
    size_t base = header_.baseOffset(100);
    EXPECT_GE(base, 0u);
}

// Test read with nullptr data and zero size - should fail gracefully
TEST_F(PentaxDngMnHeaderTest_1479, ReadNullDataZeroSize_1479) {
    bool result = header_.read(nullptr, 0, littleEndian);
    EXPECT_FALSE(result);
}

// Test read with data that is too small for the signature
TEST_F(PentaxDngMnHeaderTest_1479, ReadTooSmallData_1479) {
    byte smallData[] = {0x00, 0x01};
    bool result = header_.read(smallData, sizeof(smallData), littleEndian);
    EXPECT_FALSE(result);
}

// Test read with valid Pentax DNG signature "PENTAX \0"
// The Pentax DNG maker note signature is typically "PENTAX \0" (with a space after PENTAX)
TEST_F(PentaxDngMnHeaderTest_1479, ReadValidSignature_1479) {
    // Pentax DNG signature: "PENTAX \0" followed by version bytes
    // Typical signature is: 50 45 4E 54 41 58 20 00 (PENTAX \0)
    const byte validData[] = {
        'P', 'E', 'N', 'T', 'A', 'X', ' ', '\0',
        // Some additional data to make it large enough
        0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };
    bool result = header_.read(validData, sizeof(validData), littleEndian);
    // If the signature matches, read should return true
    EXPECT_TRUE(result);
}

// Test read with invalid signature
TEST_F(PentaxDngMnHeaderTest_1479, ReadInvalidSignature_1479) {
    const byte invalidData[] = {
        'N', 'O', 'T', 'P', 'E', 'N', 'T', 'X',
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };
    bool result = header_.read(invalidData, sizeof(invalidData), littleEndian);
    EXPECT_FALSE(result);
}

// Test read with big endian byte order
TEST_F(PentaxDngMnHeaderTest_1479, ReadBigEndian_1479) {
    const byte validData[] = {
        'P', 'E', 'N', 'T', 'A', 'X', ' ', '\0',
        0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };
    bool result = header_.read(validData, sizeof(validData), bigEndian);
    EXPECT_TRUE(result);
}

// Test read with exact signature size data
TEST_F(PentaxDngMnHeaderTest_1479, ReadExactSignatureSize_1479) {
    size_t sigSize = PentaxDngMnHeader::sizeOfSignature();
    std::vector<byte> data(sigSize);
    // Fill with Pentax DNG signature
    const char* sig = "PENTAX \0";
    size_t copyLen = std::min(sigSize, (size_t)8);
    std::memcpy(data.data(), sig, copyLen);
    
    bool result = header_.read(data.data(), data.size(), littleEndian);
    // With exact signature size, it might or might not succeed depending on implementation
    // We just verify it doesn't crash
    (void)result;
}

// Test that size is consistent before and after a failed read
TEST_F(PentaxDngMnHeaderTest_1479, SizeConsistentAfterFailedRead_1479) {
    size_t sizeBefore = header_.size();
    byte invalidData[] = {0x00};
    header_.read(invalidData, 1, littleEndian);
    size_t sizeAfter = header_.size();
    EXPECT_EQ(sizeBefore, sizeAfter);
}

// Test that size is consistent after a successful read
TEST_F(PentaxDngMnHeaderTest_1479, SizeAfterSuccessfulRead_1479) {
    const byte validData[] = {
        'P', 'E', 'N', 'T', 'A', 'X', ' ', '\0',
        0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };
    bool result = header_.read(validData, sizeof(validData), littleEndian);
    if (result) {
        EXPECT_GT(header_.size(), 0u);
    }
}

// Test baseOffset with large mnOffset
TEST_F(PentaxDngMnHeaderTest_1479, BaseOffsetLargeMnOffset_1479) {
    size_t base = header_.baseOffset(1000000);
    // Should return some deterministic value
    EXPECT_GE(base, 0u);
}

// Test multiple reads - second read should work correctly
TEST_F(PentaxDngMnHeaderTest_1479, MultipleReads_1479) {
    const byte validData[] = {
        'P', 'E', 'N', 'T', 'A', 'X', ' ', '\0',
        0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };
    
    bool result1 = header_.read(validData, sizeof(validData), littleEndian);
    bool result2 = header_.read(validData, sizeof(validData), littleEndian);
    EXPECT_EQ(result1, result2);
}

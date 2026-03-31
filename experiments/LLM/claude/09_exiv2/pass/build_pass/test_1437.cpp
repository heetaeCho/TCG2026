#include <gtest/gtest.h>
#include "makernote_int.hpp"
#include "types.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class OlympusMnHeaderTest_1437 : public ::testing::Test {
protected:
    OlympusMnHeader header_;
};

// Test that default-constructed header has a non-zero size (should contain the Olympus signature)
TEST_F(OlympusMnHeaderTest_1437, DefaultConstructorSize_1437) {
    EXPECT_GT(header_.size(), 0u);
}

// Test that sizeOfSignature returns a reasonable value
TEST_F(OlympusMnHeaderTest_1437, SizeOfSignature_1437) {
    size_t sigSize = OlympusMnHeader::sizeOfSignature();
    EXPECT_GT(sigSize, 0u);
}

// Test that size() is consistent and returns the same value on repeated calls
TEST_F(OlympusMnHeaderTest_1437, SizeIsConsistent_1437) {
    size_t s1 = header_.size();
    size_t s2 = header_.size();
    EXPECT_EQ(s1, s2);
}

// Test that ifdOffset returns a value (typically the size of signature for Olympus)
TEST_F(OlympusMnHeaderTest_1437, IfdOffsetReturnsValue_1437) {
    size_t offset = header_.ifdOffset();
    // ifdOffset should be >= 0 and likely related to sizeOfSignature
    EXPECT_GE(offset, 0u);
}

// Test that ifdOffset is consistent with sizeOfSignature
TEST_F(OlympusMnHeaderTest_1437, IfdOffsetRelatedToSignatureSize_1437) {
    size_t offset = header_.ifdOffset();
    size_t sigSize = OlympusMnHeader::sizeOfSignature();
    // For Olympus, the IFD offset typically equals the signature size
    EXPECT_EQ(offset, sigSize);
}

// Test read with null pointer or zero size returns false
TEST_F(OlympusMnHeaderTest_1437, ReadWithNullDataReturnsFalse_1437) {
    bool result = header_.read(nullptr, 0, littleEndian);
    EXPECT_FALSE(result);
}

// Test read with data too small for the signature
TEST_F(OlympusMnHeaderTest_1437, ReadWithTooSmallDataReturnsFalse_1437) {
    const byte smallData[] = {0x00, 0x01};
    bool result = header_.read(smallData, sizeof(smallData), littleEndian);
    EXPECT_FALSE(result);
}

// Test read with valid Olympus MakerNote signature "OLYMP\0"
TEST_F(OlympusMnHeaderTest_1437, ReadWithValidOlympusSignature_1437) {
    // Olympus MakerNote signature is "OLYMP\0" followed by version bytes
    // The signature is typically "OLYMP\0" + 2 bytes = 8 bytes total, or "OLYMPUS\0II" = 10 bytes
    // Let's try with the known Olympus signature
    const byte olympusData[] = {
        'O', 'L', 'Y', 'M', 'P', '\0',  // "OLYMP\0"
        0x01, 0x00,                        // version
        0x00, 0x00, 0x00, 0x00             // extra padding
    };
    size_t sigSize = OlympusMnHeader::sizeOfSignature();
    if (sigSize <= sizeof(olympusData)) {
        bool result = header_.read(olympusData, sizeof(olympusData), littleEndian);
        // The result depends on whether the signature matches exactly
        // We just verify it doesn't crash
        (void)result;
    }
}

// Test read with invalid signature data
TEST_F(OlympusMnHeaderTest_1437, ReadWithInvalidSignatureReturnsFalse_1437) {
    const byte invalidData[] = {
        'N', 'O', 'T', 'O', 'L', 'Y', 'M', 'P',
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };
    bool result = header_.read(invalidData, sizeof(invalidData), littleEndian);
    EXPECT_FALSE(result);
}

// Test read with size exactly equal to sizeOfSignature but wrong content
TEST_F(OlympusMnHeaderTest_1437, ReadWithExactSizeButWrongContent_1437) {
    size_t sigSize = OlympusMnHeader::sizeOfSignature();
    std::vector<byte> data(sigSize + 10, 0x00);
    bool result = header_.read(data.data(), data.size(), littleEndian);
    EXPECT_FALSE(result);
}

// Test read with big endian byte order
TEST_F(OlympusMnHeaderTest_1437, ReadWithBigEndianByteOrder_1437) {
    const byte olympusData[] = {
        'O', 'L', 'Y', 'M', 'P', '\0',
        0x01, 0x00,
        0x00, 0x00, 0x00, 0x00
    };
    bool result = header_.read(olympusData, sizeof(olympusData), bigEndian);
    // Just verify no crash; behavior may vary
    (void)result;
}

// Test that size matches the header_ internal DataBuf size
TEST_F(OlympusMnHeaderTest_1437, SizeMatchesExpectedHeaderSize_1437) {
    size_t headerSize = header_.size();
    size_t sigSize = OlympusMnHeader::sizeOfSignature();
    // size() should be at least as large as sizeOfSignature
    EXPECT_GE(headerSize, sigSize);
}

// Test that reading with size less than sizeOfSignature fails
TEST_F(OlympusMnHeaderTest_1437, ReadWithSizeLessThanSignatureFails_1437) {
    size_t sigSize = OlympusMnHeader::sizeOfSignature();
    if (sigSize > 1) {
        std::vector<byte> data(sigSize - 1, 'O');
        bool result = header_.read(data.data(), data.size(), littleEndian);
        EXPECT_FALSE(result);
    }
}

// Test multiple reads - second read should work independently
TEST_F(OlympusMnHeaderTest_1437, MultipleReadsAreIndependent_1437) {
    const byte invalidData[] = {
        'N', 'O', 'T', 'O', 'L', 'Y', 'M', 'P',
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };
    bool result1 = header_.read(invalidData, sizeof(invalidData), littleEndian);
    bool result2 = header_.read(invalidData, sizeof(invalidData), bigEndian);
    // Both should consistently fail with invalid data
    EXPECT_EQ(result1, result2);
}

// Test that size doesn't change after a failed read
TEST_F(OlympusMnHeaderTest_1437, SizeUnchangedAfterFailedRead_1437) {
    size_t sizeBefore = header_.size();
    const byte invalidData[] = {0x00, 0x01, 0x02};
    header_.read(invalidData, sizeof(invalidData), littleEndian);
    size_t sizeAfter = header_.size();
    EXPECT_EQ(sizeBefore, sizeAfter);
}

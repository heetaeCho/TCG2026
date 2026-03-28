#include <gtest/gtest.h>
#include "makernote_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class Nikon3MnHeaderTest_1467 : public ::testing::Test {
protected:
    Nikon3MnHeader header_;
};

// Test that default construction sets ifdOffset to sizeOfSignature
TEST_F(Nikon3MnHeaderTest_1467, DefaultConstructorSetsIfdOffset_1467) {
    EXPECT_EQ(header_.ifdOffset(), Nikon3MnHeader::sizeOfSignature());
}

// Test that size() returns a reasonable value (at least as large as signature)
TEST_F(Nikon3MnHeaderTest_1467, SizeIsAtLeastSignatureSize_1467) {
    EXPECT_GE(header_.size(), Nikon3MnHeader::sizeOfSignature());
}

// Test that sizeOfSignature returns a non-zero value
TEST_F(Nikon3MnHeaderTest_1467, SizeOfSignatureIsNonZero_1467) {
    EXPECT_GT(Nikon3MnHeader::sizeOfSignature(), 0u);
}

// Test that byteOrder returns a valid byte order after default construction
TEST_F(Nikon3MnHeaderTest_1467, DefaultByteOrder_1467) {
    ByteOrder bo = header_.byteOrder();
    // Should be one of the valid byte orders
    EXPECT_TRUE(bo == littleEndian || bo == bigEndian || bo == invalidByteOrder);
}

// Test that baseOffset returns mnOffset (typical Nikon behavior)
TEST_F(Nikon3MnHeaderTest_1467, BaseOffsetReturnsExpectedValue_1467) {
    size_t mnOffset = 100;
    size_t result = header_.baseOffset(mnOffset);
    // baseOffset typically returns mnOffset for Nikon3
    EXPECT_EQ(result, mnOffset);
}

// Test baseOffset with zero offset
TEST_F(Nikon3MnHeaderTest_1467, BaseOffsetWithZero_1467) {
    size_t result = header_.baseOffset(0);
    EXPECT_EQ(result, 0u);
}

// Test read with nullptr data returns false
TEST_F(Nikon3MnHeaderTest_1467, ReadWithNullptrReturnsFalse_1467) {
    bool result = header_.read(nullptr, 0, littleEndian);
    EXPECT_FALSE(result);
}

// Test read with too small data returns false
TEST_F(Nikon3MnHeaderTest_1467, ReadWithTooSmallDataReturnsFalse_1467) {
    byte data[1] = {0};
    bool result = header_.read(data, 1, littleEndian);
    EXPECT_FALSE(result);
}

// Test read with valid Nikon3 signature
TEST_F(Nikon3MnHeaderTest_1467, ReadWithValidNikonSignature_1467) {
    // Nikon3 maker note signature is "Nikon\0" followed by version info
    // The signature is typically: "Nikon\0\2\x10\0\0" (10 bytes) + additional header bytes
    const byte nikonSig[] = {
        'N', 'i', 'k', 'o', 'n', '\0',  // "Nikon\0"
        0x02, 0x10, 0x00, 0x00,          // Version and padding
        0x4D, 0x4D,                       // MM (big endian) or 0x49 0x49 for II
        0x00, 0x2A,                       // TIFF magic
        0x00, 0x00, 0x00, 0x08            // Offset to IFD
    };
    bool result = header_.read(nikonSig, sizeof(nikonSig), bigEndian);
    EXPECT_TRUE(result);
}

// Test read with invalid signature data
TEST_F(Nikon3MnHeaderTest_1467, ReadWithInvalidSignature_1467) {
    byte invalidData[18] = {0};
    bool result = header_.read(invalidData, sizeof(invalidData), littleEndian);
    EXPECT_FALSE(result);
}

// Test setByteOrder changes byte order
TEST_F(Nikon3MnHeaderTest_1467, SetByteOrderChangesOrder_1467) {
    header_.setByteOrder(bigEndian);
    EXPECT_EQ(header_.byteOrder(), bigEndian);

    header_.setByteOrder(littleEndian);
    EXPECT_EQ(header_.byteOrder(), littleEndian);
}

// Test that ifdOffset is consistent after valid read
TEST_F(Nikon3MnHeaderTest_1467, IfdOffsetAfterValidRead_1467) {
    const byte nikonSig[] = {
        'N', 'i', 'k', 'o', 'n', '\0',
        0x02, 0x10, 0x00, 0x00,
        0x4D, 0x4D,
        0x00, 0x2A,
        0x00, 0x00, 0x00, 0x08
    };
    if (header_.read(nikonSig, sizeof(nikonSig), bigEndian)) {
        // After a valid read, ifdOffset should be updated based on the data
        size_t offset = header_.ifdOffset();
        EXPECT_GT(offset, 0u);
    }
}

// Test read with exact minimum size
TEST_F(Nikon3MnHeaderTest_1467, ReadWithExactMinimumSize_1467) {
    size_t sigSize = Nikon3MnHeader::sizeOfSignature();
    // Data exactly the size of signature - may or may not be enough
    std::vector<byte> data(sigSize, 0);
    // Fill with Nikon signature prefix
    const char* sig = "Nikon";
    if (sigSize >= 6) {
        std::memcpy(data.data(), sig, 5);
        data[5] = 0;
    }
    bool result = header_.read(data.data(), data.size(), littleEndian);
    // With just the signature and no TIFF header, this should likely fail
    // But we're testing boundary behavior
    // Just verify it doesn't crash
    (void)result;
}

// Test multiple setByteOrder calls
TEST_F(Nikon3MnHeaderTest_1467, MultipleSetByteOrderCalls_1467) {
    header_.setByteOrder(bigEndian);
    EXPECT_EQ(header_.byteOrder(), bigEndian);

    header_.setByteOrder(littleEndian);
    EXPECT_EQ(header_.byteOrder(), littleEndian);

    header_.setByteOrder(bigEndian);
    EXPECT_EQ(header_.byteOrder(), bigEndian);
}

// Test baseOffset with large value
TEST_F(Nikon3MnHeaderTest_1467, BaseOffsetWithLargeValue_1467) {
    size_t largeOffset = 0xFFFFFF;
    size_t result = header_.baseOffset(largeOffset);
    EXPECT_EQ(result, largeOffset);
}

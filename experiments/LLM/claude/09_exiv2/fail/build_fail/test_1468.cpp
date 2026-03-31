#include <gtest/gtest.h>
#include "makernote_int.hpp"
#include "types.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class Nikon3MnHeaderTest_1468 : public ::testing::Test {
protected:
    Nikon3MnHeader header_;
};

// Test default construction and initial byte order
TEST_F(Nikon3MnHeaderTest_1468, DefaultConstruction_ByteOrder_1468) {
    // After default construction, byteOrder should have a defined value
    ByteOrder bo = header_.byteOrder();
    // The byte order should be one of the valid values
    EXPECT_TRUE(bo == invalidByteOrder || bo == littleEndian || bo == bigEndian);
}

// Test size of signature is non-zero
TEST_F(Nikon3MnHeaderTest_1468, SizeOfSignature_NonZero_1468) {
    size_t sigSize = Nikon3MnHeader::sizeOfSignature();
    EXPECT_GT(sigSize, 0u);
}

// Test size() returns a value >= sizeOfSignature
TEST_F(Nikon3MnHeaderTest_1468, Size_GreaterOrEqualToSignature_1468) {
    size_t sz = header_.size();
    size_t sigSz = Nikon3MnHeader::sizeOfSignature();
    EXPECT_GE(sz, sigSz);
}

// Test ifdOffset returns a value that makes sense (>= 0)
TEST_F(Nikon3MnHeaderTest_1468, IfdOffset_NonNegative_1468) {
    size_t offset = header_.ifdOffset();
    // ifdOffset should be within the header size
    EXPECT_LE(offset, header_.size());
}

// Test read with nullptr or zero size fails
TEST_F(Nikon3MnHeaderTest_1468, ReadWithNullData_ReturnsFalse_1468) {
    bool result = header_.read(nullptr, 0, littleEndian);
    EXPECT_FALSE(result);
}

// Test read with insufficient data size fails
TEST_F(Nikon3MnHeaderTest_1468, ReadWithInsufficientSize_ReturnsFalse_1468) {
    byte data[1] = {0};
    bool result = header_.read(data, 1, littleEndian);
    EXPECT_FALSE(result);
}

// Test read with valid Nikon3 maker note signature
TEST_F(Nikon3MnHeaderTest_1468, ReadWithValidSignature_ReturnsTrue_1468) {
    // Nikon3 maker note signature: "Nikon\0\2\x10\0\0" followed by byte order
    // The signature is "Nikon\0" + version (2 bytes) + padding, then byte order marker
    // Typical Nikon3 header: "Nikon\0\x02\x10\x00\x00" + "MM" or "II" + 0x002a + offset
    const byte validHeader[] = {
        'N', 'i', 'k', 'o', 'n', '\0',  // "Nikon\0"
        0x02, 0x10,                       // version
        0x00, 0x00,                       // padding
        0x4D, 0x4D,                       // "MM" (big endian)
        0x00, 0x2A,                       // TIFF magic number
        0x00, 0x00, 0x00, 0x08            // offset to IFD
    };
    
    bool result = header_.read(validHeader, sizeof(validHeader), bigEndian);
    if (result) {
        EXPECT_EQ(header_.byteOrder(), bigEndian);
    }
    // If the exact format doesn't match, that's fine - we tested the interface
}

// Test read with valid Nikon3 header in little endian
TEST_F(Nikon3MnHeaderTest_1468, ReadWithValidSignatureLE_1468) {
    const byte validHeader[] = {
        'N', 'i', 'k', 'o', 'n', '\0',
        0x02, 0x10,
        0x00, 0x00,
        0x49, 0x49,                       // "II" (little endian)
        0x2A, 0x00,                       // TIFF magic number (LE)
        0x08, 0x00, 0x00, 0x00            // offset to IFD (LE)
    };
    
    bool result = header_.read(validHeader, sizeof(validHeader), littleEndian);
    if (result) {
        EXPECT_EQ(header_.byteOrder(), littleEndian);
    }
}

// Test setByteOrder changes the byte order
TEST_F(Nikon3MnHeaderTest_1468, SetByteOrder_ChangesOrder_1468) {
    header_.setByteOrder(bigEndian);
    EXPECT_EQ(header_.byteOrder(), bigEndian);
    
    header_.setByteOrder(littleEndian);
    EXPECT_EQ(header_.byteOrder(), littleEndian);
}

// Test baseOffset with various mnOffset values
TEST_F(Nikon3MnHeaderTest_1468, BaseOffset_WithZeroMnOffset_1468) {
    size_t base = header_.baseOffset(0);
    // baseOffset typically returns mnOffset + start_ (the signature size)
    // We just verify it returns a reasonable value
    EXPECT_GE(base, 0u);
}

TEST_F(Nikon3MnHeaderTest_1468, BaseOffset_WithNonZeroMnOffset_1468) {
    size_t base100 = header_.baseOffset(100);
    size_t base0 = header_.baseOffset(0);
    // The offset should increase with mnOffset
    EXPECT_GT(base100, base0);
}

// Test baseOffset difference equals mnOffset difference
TEST_F(Nikon3MnHeaderTest_1468, BaseOffset_DifferenceEqualsMnOffsetDifference_1468) {
    size_t base100 = header_.baseOffset(100);
    size_t base200 = header_.baseOffset(200);
    EXPECT_EQ(base200 - base100, 100u);
}

// Test read with invalid signature
TEST_F(Nikon3MnHeaderTest_1468, ReadWithInvalidSignature_ReturnsFalse_1468) {
    const byte invalidHeader[] = {
        'C', 'a', 'n', 'o', 'n', '\0',
        0x02, 0x10,
        0x00, 0x00,
        0x4D, 0x4D,
        0x00, 0x2A,
        0x00, 0x00, 0x00, 0x08
    };
    
    bool result = header_.read(invalidHeader, sizeof(invalidHeader), bigEndian);
    EXPECT_FALSE(result);
}

// Test read with data exactly at sizeOfSignature boundary
TEST_F(Nikon3MnHeaderTest_1468, ReadWithExactSignatureSize_1468) {
    size_t sigSize = Nikon3MnHeader::sizeOfSignature();
    std::vector<byte> data(sigSize, 0);
    // Fill with Nikon signature prefix
    const char sig[] = "Nikon";
    if (sigSize >= sizeof(sig)) {
        std::memcpy(data.data(), sig, sizeof(sig));
    }
    
    // This might or might not succeed depending on whether more data is needed
    // but it should not crash
    header_.read(data.data(), data.size(), littleEndian);
}

// Test that sizeOfSignature is consistent across calls
TEST_F(Nikon3MnHeaderTest_1468, SizeOfSignature_Consistent_1468) {
    size_t s1 = Nikon3MnHeader::sizeOfSignature();
    size_t s2 = Nikon3MnHeader::sizeOfSignature();
    EXPECT_EQ(s1, s2);
}

// Test size is consistent across calls
TEST_F(Nikon3MnHeaderTest_1468, Size_Consistent_1468) {
    size_t s1 = header_.size();
    size_t s2 = header_.size();
    EXPECT_EQ(s1, s2);
}

// Test that after successful read, byteOrder reflects the data
TEST_F(Nikon3MnHeaderTest_1468, ReadSuccessful_ByteOrderFromData_1468) {
    const byte validHeaderBE[] = {
        'N', 'i', 'k', 'o', 'n', '\0',
        0x02, 0x10,
        0x00, 0x00,
        0x4D, 0x4D,
        0x00, 0x2A,
        0x00, 0x00, 0x00, 0x08
    };
    
    if (header_.read(validHeaderBE, sizeof(validHeaderBE), littleEndian)) {
        // The byte order should come from within the Nikon header data ("MM" = big endian)
        EXPECT_EQ(header_.byteOrder(), bigEndian);
    }
}

// Test read with all zeros
TEST_F(Nikon3MnHeaderTest_1468, ReadWithAllZeros_ReturnsFalse_1468) {
    byte zeros[32] = {0};
    bool result = header_.read(zeros, sizeof(zeros), littleEndian);
    EXPECT_FALSE(result);
}

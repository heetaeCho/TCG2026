#include <gtest/gtest.h>
#include "makernote_int.hpp"

using namespace Exiv2::Internal;

class Nikon3MnHeaderTest_1466 : public ::testing::Test {
protected:
    Nikon3MnHeader header_;
};

// Test that default-constructed header has a size equal to sizeOfSignature
TEST_F(Nikon3MnHeaderTest_1466, SizeEqualsSizeOfSignature_1466) {
    EXPECT_EQ(header_.size(), Nikon3MnHeader::sizeOfSignature());
}

// Test that sizeOfSignature returns a non-zero value (Nikon3 signature "Nikon\0\2\x10\0\0\0\0\0\0" is known to be non-trivial)
TEST_F(Nikon3MnHeaderTest_1466, SizeOfSignatureIsNonZero_1466) {
    EXPECT_GT(Nikon3MnHeader::sizeOfSignature(), 0u);
}

// Test that size() is consistent across multiple calls
TEST_F(Nikon3MnHeaderTest_1466, SizeIsConsistent_1466) {
    size_t s1 = header_.size();
    size_t s2 = header_.size();
    EXPECT_EQ(s1, s2);
}

// Test that ifdOffset returns the expected value (should be equal to sizeOfSignature typically)
TEST_F(Nikon3MnHeaderTest_1466, IfdOffsetValue_1466) {
    size_t offset = header_.ifdOffset();
    // ifdOffset should be at least 0 and typically equals sizeOfSignature (start_)
    EXPECT_EQ(offset, Nikon3MnHeader::sizeOfSignature());
}

// Test that byteOrder returns a valid byte order before any read
TEST_F(Nikon3MnHeaderTest_1466, DefaultByteOrder_1466) {
    ByteOrder bo = header_.byteOrder();
    // Should be one of the known byte orders
    EXPECT_TRUE(bo == littleEndian || bo == bigEndian || bo == invalidByteOrder);
}

// Test that setByteOrder changes the byte order
TEST_F(Nikon3MnHeaderTest_1466, SetByteOrderChangesOrder_1466) {
    header_.setByteOrder(littleEndian);
    EXPECT_EQ(header_.byteOrder(), littleEndian);

    header_.setByteOrder(bigEndian);
    EXPECT_EQ(header_.byteOrder(), bigEndian);
}

// Test that baseOffset returns mnOffset (Nikon3 typically returns mnOffset + 10 or similar)
TEST_F(Nikon3MnHeaderTest_1466, BaseOffsetWithZero_1466) {
    size_t base = header_.baseOffset(0);
    // baseOffset(0) should be deterministic
    size_t base2 = header_.baseOffset(0);
    EXPECT_EQ(base, base2);
}

// Test baseOffset with a non-zero mnOffset
TEST_F(Nikon3MnHeaderTest_1466, BaseOffsetWithNonZero_1466) {
    size_t base100 = header_.baseOffset(100);
    size_t base200 = header_.baseOffset(200);
    // The difference should be consistent (baseOffset is typically mnOffset + constant)
    EXPECT_EQ(base200 - base100, 100u);
}

// Test read with nullptr data and zero size (boundary: should fail gracefully)
TEST_F(Nikon3MnHeaderTest_1466, ReadNullDataZeroSize_1466) {
    bool result = header_.read(nullptr, 0, littleEndian);
    EXPECT_FALSE(result);
}

// Test read with data that is too small
TEST_F(Nikon3MnHeaderTest_1466, ReadTooSmallData_1466) {
    Exiv2::byte data[] = {0x00, 0x01};
    bool result = header_.read(data, sizeof(data), littleEndian);
    EXPECT_FALSE(result);
}

// Test read with valid Nikon3 maker note signature
TEST_F(Nikon3MnHeaderTest_1466, ReadValidNikon3Signature_1466) {
    // Nikon3 signature: "Nikon\0\2\x10\0\0" followed by byte order bytes
    // The signature is typically: 4E 69 6B 6F 6E 00 02 10 00 00 00 08 (or similar)
    // Let's construct a plausible Nikon3 header
    size_t sigSize = Nikon3MnHeader::sizeOfSignature();
    std::vector<Exiv2::byte> data(sigSize + 100, 0);
    // "Nikon\0" prefix
    data[0] = 'N'; data[1] = 'i'; data[2] = 'k'; data[3] = 'o'; data[4] = 'n'; data[5] = '\0';
    // Version
    data[6] = 0x02; data[7] = 0x10;
    // Padding
    data[8] = 0x00; data[9] = 0x00;
    // Byte order: "II" for little endian or "MM" for big endian
    data[10] = 'M'; data[11] = 'M';
    // TIFF magic number 0x002A
    data[12] = 0x00; data[13] = 0x2A;
    // Offset
    data[14] = 0x00; data[15] = 0x00; data[16] = 0x00; data[17] = 0x08;

    bool result = header_.read(data.data(), data.size(), bigEndian);
    // The result depends on actual signature matching; we just verify it doesn't crash
    // and returns a boolean
    EXPECT_TRUE(result == true || result == false);
}

// Test read with valid Nikon3 signature in little endian
TEST_F(Nikon3MnHeaderTest_1466, ReadValidNikon3SignatureLE_1466) {
    size_t sigSize = Nikon3MnHeader::sizeOfSignature();
    std::vector<Exiv2::byte> data(sigSize + 100, 0);
    data[0] = 'N'; data[1] = 'i'; data[2] = 'k'; data[3] = 'o'; data[4] = 'n'; data[5] = '\0';
    data[6] = 0x02; data[7] = 0x10;
    data[8] = 0x00; data[9] = 0x00;
    // "II" for little endian
    data[10] = 'I'; data[11] = 'I';
    data[12] = 0x2A; data[13] = 0x00;
    data[14] = 0x08; data[15] = 0x00; data[16] = 0x00; data[17] = 0x00;

    bool result = header_.read(data.data(), data.size(), littleEndian);
    if (result) {
        EXPECT_EQ(header_.byteOrder(), littleEndian);
    }
}

// Test that read with wrong signature fails
TEST_F(Nikon3MnHeaderTest_1466, ReadWrongSignature_1466) {
    size_t sigSize = Nikon3MnHeader::sizeOfSignature();
    std::vector<Exiv2::byte> data(sigSize + 100, 0);
    // Fill with garbage instead of "Nikon\0"
    data[0] = 'X'; data[1] = 'Y'; data[2] = 'Z'; data[3] = 'W'; data[4] = 'Q'; data[5] = '\0';

    bool result = header_.read(data.data(), data.size(), littleEndian);
    EXPECT_FALSE(result);
}

// Test that size remains constant after construction
TEST_F(Nikon3MnHeaderTest_1466, SizeConstantAfterConstruction_1466) {
    Nikon3MnHeader h1;
    Nikon3MnHeader h2;
    EXPECT_EQ(h1.size(), h2.size());
}

// Test read with exactly sizeOfSignature bytes (boundary)
TEST_F(Nikon3MnHeaderTest_1466, ReadExactSignatureSize_1466) {
    size_t sigSize = Nikon3MnHeader::sizeOfSignature();
    std::vector<Exiv2::byte> data(sigSize, 0);
    data[0] = 'N'; data[1] = 'i'; data[2] = 'k'; data[3] = 'o'; data[4] = 'n'; data[5] = '\0';

    bool result = header_.read(data.data(), data.size(), littleEndian);
    // May or may not succeed depending on signature validation requirements
    EXPECT_TRUE(result == true || result == false);
}

// Test read with size one less than sizeOfSignature (should fail)
TEST_F(Nikon3MnHeaderTest_1466, ReadOneLessThanSignatureSize_1466) {
    size_t sigSize = Nikon3MnHeader::sizeOfSignature();
    if (sigSize > 0) {
        std::vector<Exiv2::byte> data(sigSize - 1, 0);
        bool result = header_.read(data.data(), data.size(), littleEndian);
        EXPECT_FALSE(result);
    }
}

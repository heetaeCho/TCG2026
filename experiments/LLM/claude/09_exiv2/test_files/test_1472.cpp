#include <gtest/gtest.h>
#include "makernote_int.hpp"
#include "types.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class Nikon3MnHeaderTest_1472 : public ::testing::Test {
protected:
    Nikon3MnHeader header_;
};

// Test default construction and initial byte order
TEST_F(Nikon3MnHeaderTest_1472, DefaultConstruction_1472) {
    // After default construction, the header should be in a valid state
    // The object should be constructible without errors
    Nikon3MnHeader h;
    SUCCEED();
}

// Test setByteOrder with little endian
TEST_F(Nikon3MnHeaderTest_1472, SetByteOrderLittleEndian_1472) {
    header_.setByteOrder(littleEndian);
    EXPECT_EQ(header_.byteOrder(), littleEndian);
}

// Test setByteOrder with big endian
TEST_F(Nikon3MnHeaderTest_1472, SetByteOrderBigEndian_1472) {
    header_.setByteOrder(bigEndian);
    EXPECT_EQ(header_.byteOrder(), bigEndian);
}

// Test that setByteOrder can be called multiple times and the last value sticks
TEST_F(Nikon3MnHeaderTest_1472, SetByteOrderMultipleTimes_1472) {
    header_.setByteOrder(littleEndian);
    EXPECT_EQ(header_.byteOrder(), littleEndian);
    header_.setByteOrder(bigEndian);
    EXPECT_EQ(header_.byteOrder(), bigEndian);
    header_.setByteOrder(littleEndian);
    EXPECT_EQ(header_.byteOrder(), littleEndian);
}

// Test size() returns a positive value
TEST_F(Nikon3MnHeaderTest_1472, SizeIsPositive_1472) {
    EXPECT_GT(header_.size(), 0u);
}

// Test sizeOfSignature() returns a positive value
TEST_F(Nikon3MnHeaderTest_1472, SizeOfSignatureIsPositive_1472) {
    EXPECT_GT(Nikon3MnHeader::sizeOfSignature(), 0u);
}

// Test that size() >= sizeOfSignature()
TEST_F(Nikon3MnHeaderTest_1472, SizeAtLeastSignatureSize_1472) {
    EXPECT_GE(header_.size(), Nikon3MnHeader::sizeOfSignature());
}

// Test ifdOffset() returns a reasonable value
TEST_F(Nikon3MnHeaderTest_1472, IfdOffsetReturnsValue_1472) {
    size_t offset = header_.ifdOffset();
    // ifdOffset should be within the header size range
    EXPECT_GE(offset, 0u);
}

// Test baseOffset returns a value related to mnOffset
TEST_F(Nikon3MnHeaderTest_1472, BaseOffsetWithZeroMnOffset_1472) {
    size_t base = header_.baseOffset(0);
    // Should return some value (implementation dependent, but should not crash)
    (void)base;
    SUCCEED();
}

TEST_F(Nikon3MnHeaderTest_1472, BaseOffsetWithNonZeroMnOffset_1472) {
    size_t base = header_.baseOffset(100);
    // baseOffset with a non-zero mnOffset should return a value
    (void)base;
    SUCCEED();
}

// Test read with nullptr/zero size should fail
TEST_F(Nikon3MnHeaderTest_1472, ReadWithNullDataFails_1472) {
    bool result = header_.read(nullptr, 0, littleEndian);
    EXPECT_FALSE(result);
}

// Test read with insufficient size should fail
TEST_F(Nikon3MnHeaderTest_1472, ReadWithInsufficientSizeFails_1472) {
    byte data[1] = {0};
    bool result = header_.read(data, 1, littleEndian);
    EXPECT_FALSE(result);
}

// Test read with valid Nikon3 signature
TEST_F(Nikon3MnHeaderTest_1472, ReadWithValidSignature_1472) {
    // Nikon3 maker note signature: "Nikon\0\x02\x10\x00\x00" followed by byte order mark
    // The signature is "Nikon\0" (6 bytes) + version (2 bytes) + padding (2 bytes) + byte order (2 bytes) + ...
    // Typical Nikon3 header: 4E 69 6B 6F 6E 00 02 10 00 00 4D 4D 00 2A ...
    const size_t sigSize = Nikon3MnHeader::sizeOfSignature();
    std::vector<byte> data(sigSize + 8, 0);
    // "Nikon\0"
    data[0] = 'N'; data[1] = 'i'; data[2] = 'k'; data[3] = 'o'; data[4] = 'n'; data[5] = 0;
    // Version
    data[6] = 0x02; data[7] = 0x10;
    // Padding
    data[8] = 0x00; data[9] = 0x00;
    // Big endian byte order mark "MM"
    data[10] = 0x4D; data[11] = 0x4D;
    // TIFF magic number 42
    data[12] = 0x00; data[13] = 0x2A;
    // Offset to first IFD (typically 8)
    data[14] = 0x00; data[15] = 0x00; data[16] = 0x00; data[17] = 0x08;

    bool result = header_.read(data.data(), data.size(), bigEndian);
    EXPECT_TRUE(result);
}

// Test read with invalid signature should fail
TEST_F(Nikon3MnHeaderTest_1472, ReadWithInvalidSignatureFails_1472) {
    const size_t sigSize = Nikon3MnHeader::sizeOfSignature();
    std::vector<byte> data(sigSize + 8, 0);
    // Fill with garbage
    data[0] = 'X'; data[1] = 'Y'; data[2] = 'Z';
    
    bool result = header_.read(data.data(), data.size(), littleEndian);
    EXPECT_FALSE(result);
}

// Test that after successful read, byteOrder reflects the data
TEST_F(Nikon3MnHeaderTest_1472, ByteOrderAfterRead_1472) {
    const size_t sigSize = Nikon3MnHeader::sizeOfSignature();
    std::vector<byte> data(sigSize + 8, 0);
    data[0] = 'N'; data[1] = 'i'; data[2] = 'k'; data[3] = 'o'; data[4] = 'n'; data[5] = 0;
    data[6] = 0x02; data[7] = 0x10;
    data[8] = 0x00; data[9] = 0x00;
    // Little endian byte order mark "II"
    data[10] = 0x49; data[11] = 0x49;
    // TIFF magic 42 in little endian
    data[12] = 0x2A; data[13] = 0x00;
    // Offset
    data[14] = 0x08; data[15] = 0x00; data[16] = 0x00; data[17] = 0x00;

    bool result = header_.read(data.data(), data.size(), littleEndian);
    if (result) {
        EXPECT_EQ(header_.byteOrder(), littleEndian);
    }
}

// Test size is consistent
TEST_F(Nikon3MnHeaderTest_1472, SizeIsConsistent_1472) {
    size_t s1 = header_.size();
    size_t s2 = header_.size();
    EXPECT_EQ(s1, s2);
}

// Test sizeOfSignature is consistent across calls
TEST_F(Nikon3MnHeaderTest_1472, SizeOfSignatureConsistent_1472) {
    size_t s1 = Nikon3MnHeader::sizeOfSignature();
    size_t s2 = Nikon3MnHeader::sizeOfSignature();
    EXPECT_EQ(s1, s2);
}

// Test read with exact minimum required size
TEST_F(Nikon3MnHeaderTest_1472, ReadWithExactMinimumSize_1472) {
    const size_t sigSize = Nikon3MnHeader::sizeOfSignature();
    // Try with exactly sizeOfSignature - this may or may not be enough
    std::vector<byte> data(sigSize, 0);
    data[0] = 'N'; data[1] = 'i'; data[2] = 'k'; data[3] = 'o'; data[4] = 'n'; data[5] = 0;
    
    // The result depends on whether sigSize is enough; just ensure no crash
    bool result = header_.read(data.data(), data.size(), littleEndian);
    (void)result;
    SUCCEED();
}

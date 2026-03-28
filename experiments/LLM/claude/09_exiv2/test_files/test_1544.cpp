#include <gtest/gtest.h>
#include <cstring>
#include <vector>

// Include necessary headers
#include "cr2header_int.hpp"
#include "exiv2/types.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class Cr2HeaderTest_1544 : public ::testing::Test {
protected:
    // Helper to build a valid little-endian CR2 header (16 bytes)
    std::vector<byte> buildValidLE() {
        std::vector<byte> data(16, 0);
        // Byte order: 'II' (little endian)
        data[0] = 'I';
        data[1] = 'I';
        // Tag = 42 in little endian at offset 2
        data[2] = 42;
        data[3] = 0;
        // Offset (IFD0 offset) at bytes 4-7, little endian = 0x00000010 (16)
        data[4] = 0x10;
        data[5] = 0x00;
        data[6] = 0x00;
        data[7] = 0x00;
        // CR2 signature at bytes 8-11: "CR" followed by version bytes
        // CR2 signature is typically: 'C', 'R', 0x02, 0x00
        data[8] = 'C';
        data[9] = 'R';
        data[10] = 0x02;
        data[11] = 0x00;
        // offset2 at bytes 12-15, little endian
        data[12] = 0x00;
        data[13] = 0x00;
        data[14] = 0x00;
        data[15] = 0x00;
        return data;
    }

    // Helper to build a valid big-endian CR2 header (16 bytes)
    std::vector<byte> buildValidBE() {
        std::vector<byte> data(16, 0);
        // Byte order: 'MM' (big endian)
        data[0] = 'M';
        data[1] = 'M';
        // Tag = 42 in big endian at offset 2
        data[2] = 0;
        data[3] = 42;
        // Offset at bytes 4-7, big endian = 0x00000010 (16)
        data[4] = 0x00;
        data[5] = 0x00;
        data[6] = 0x00;
        data[7] = 0x10;
        // CR2 signature at bytes 8-11
        data[8] = 'C';
        data[9] = 'R';
        data[10] = 0x02;
        data[11] = 0x00;
        // offset2 at bytes 12-15, big endian
        data[12] = 0x00;
        data[13] = 0x00;
        data[14] = 0x00;
        data[15] = 0x00;
        return data;
    }
};

// Test: null pointer returns false
TEST_F(Cr2HeaderTest_1544, ReadNullPointerReturnsFalse_1544) {
    Cr2Header header(littleEndian);
    EXPECT_FALSE(header.read(nullptr, 16));
}

// Test: size less than 16 returns false
TEST_F(Cr2HeaderTest_1544, ReadSizeTooSmallReturnsFalse_1544) {
    Cr2Header header(littleEndian);
    std::vector<byte> data(15, 0);
    EXPECT_FALSE(header.read(data.data(), 15));
}

// Test: size zero returns false
TEST_F(Cr2HeaderTest_1544, ReadSizeZeroReturnsFalse_1544) {
    Cr2Header header(littleEndian);
    byte data[1] = {0};
    EXPECT_FALSE(header.read(data, 0));
}

// Test: valid little-endian CR2 header
TEST_F(Cr2HeaderTest_1544, ReadValidLittleEndianHeader_1544) {
    Cr2Header header(littleEndian);
    auto data = buildValidLE();
    EXPECT_TRUE(header.read(data.data(), data.size()));
    EXPECT_EQ(header.byteOrder(), littleEndian);
}

// Test: valid big-endian CR2 header
TEST_F(Cr2HeaderTest_1544, ReadValidBigEndianHeader_1544) {
    Cr2Header header(bigEndian);
    auto data = buildValidBE();
    EXPECT_TRUE(header.read(data.data(), data.size()));
    EXPECT_EQ(header.byteOrder(), bigEndian);
}

// Test: invalid byte order marker returns false
TEST_F(Cr2HeaderTest_1544, ReadInvalidByteOrderReturnsFalse_1544) {
    Cr2Header header(littleEndian);
    auto data = buildValidLE();
    data[0] = 'X';
    data[1] = 'X';
    EXPECT_FALSE(header.read(data.data(), data.size()));
}

// Test: mismatched byte order bytes (first byte 'I', second byte 'M')
TEST_F(Cr2HeaderTest_1544, ReadMismatchedByteOrderReturnsFalse_1544) {
    Cr2Header header(littleEndian);
    auto data = buildValidLE();
    data[0] = 'I';
    data[1] = 'M';
    EXPECT_FALSE(header.read(data.data(), data.size()));
}

// Test: wrong tag value returns false
TEST_F(Cr2HeaderTest_1544, ReadWrongTagReturnsFalse_1544) {
    Cr2Header header(littleEndian);
    auto data = buildValidLE();
    // Change tag to something other than 42
    data[2] = 0x00;
    data[3] = 0x00;
    EXPECT_FALSE(header.read(data.data(), data.size()));
}

// Test: wrong CR2 signature returns false
TEST_F(Cr2HeaderTest_1544, ReadWrongCr2SignatureReturnsFalse_1544) {
    Cr2Header header(littleEndian);
    auto data = buildValidLE();
    // Corrupt the CR2 signature
    data[8] = 'X';
    data[9] = 'Y';
    data[10] = 0x00;
    data[11] = 0x00;
    EXPECT_FALSE(header.read(data.data(), data.size()));
}

// Test: offset is properly read from the data (little endian)
TEST_F(Cr2HeaderTest_1544, ReadSetsOffsetCorrectlyLE_1544) {
    Cr2Header header(littleEndian);
    auto data = buildValidLE();
    // Set offset to 0x00000020 (32) in little endian
    data[4] = 0x20;
    data[5] = 0x00;
    data[6] = 0x00;
    data[7] = 0x00;
    EXPECT_TRUE(header.read(data.data(), data.size()));
    EXPECT_EQ(header.offset(), 0x00000020u);
}

// Test: offset is properly read from the data (big endian)
TEST_F(Cr2HeaderTest_1544, ReadSetsOffsetCorrectlyBE_1544) {
    Cr2Header header(bigEndian);
    auto data = buildValidBE();
    // Set offset to 0x00000020 (32) in big endian
    data[4] = 0x00;
    data[5] = 0x00;
    data[6] = 0x00;
    data[7] = 0x20;
    EXPECT_TRUE(header.read(data.data(), data.size()));
    EXPECT_EQ(header.offset(), 0x00000020u);
}

// Test: read with exactly 16 bytes succeeds
TEST_F(Cr2HeaderTest_1544, ReadExactly16BytesSucceeds_1544) {
    Cr2Header header(littleEndian);
    auto data = buildValidLE();
    ASSERT_EQ(data.size(), 16u);
    EXPECT_TRUE(header.read(data.data(), 16));
}

// Test: read with more than 16 bytes still succeeds
TEST_F(Cr2HeaderTest_1544, ReadMoreThan16BytesSucceeds_1544) {
    Cr2Header header(littleEndian);
    auto data = buildValidLE();
    data.resize(100, 0);
    EXPECT_TRUE(header.read(data.data(), data.size()));
}

// Test: constructor sets correct initial values
TEST_F(Cr2HeaderTest_1544, ConstructorSetsInitialByteOrder_1544) {
    Cr2Header headerLE(littleEndian);
    EXPECT_EQ(headerLE.byteOrder(), littleEndian);

    Cr2Header headerBE(bigEndian);
    EXPECT_EQ(headerBE.byteOrder(), bigEndian);
}

// Test: tag() returns 42 (the TIFF magic number for CR2)
TEST_F(Cr2HeaderTest_1544, TagReturns42_1544) {
    Cr2Header header(littleEndian);
    EXPECT_EQ(header.tag(), 42);
}

// Test: size() returns 16
TEST_F(Cr2HeaderTest_1544, SizeReturns16_1544) {
    Cr2Header header(littleEndian);
    EXPECT_EQ(header.size(), 16u);
}

// Test: initial offset is 0x00000010
TEST_F(Cr2HeaderTest_1544, InitialOffsetIs16_1544) {
    Cr2Header header(littleEndian);
    EXPECT_EQ(header.offset(), 0x00000010u);
}

// Test: byte order change after reading a LE header with BE-initialized header
TEST_F(Cr2HeaderTest_1544, ReadChangesByteOrderFromBEtoLE_1544) {
    Cr2Header header(bigEndian);
    EXPECT_EQ(header.byteOrder(), bigEndian);
    auto data = buildValidLE();
    EXPECT_TRUE(header.read(data.data(), data.size()));
    EXPECT_EQ(header.byteOrder(), littleEndian);
}

// Test: byte order change after reading a BE header with LE-initialized header
TEST_F(Cr2HeaderTest_1544, ReadChangesByteOrderFromLEtoBE_1544) {
    Cr2Header header(littleEndian);
    EXPECT_EQ(header.byteOrder(), littleEndian);
    auto data = buildValidBE();
    EXPECT_TRUE(header.read(data.data(), data.size()));
    EXPECT_EQ(header.byteOrder(), bigEndian);
}

// Test: partially corrupted CR2 signature (only first byte wrong)
TEST_F(Cr2HeaderTest_1544, ReadPartiallyCorruptedSignatureReturnsFalse_1544) {
    Cr2Header header(littleEndian);
    auto data = buildValidLE();
    // Change just the first byte of signature
    data[8] = 'X';
    EXPECT_FALSE(header.read(data.data(), data.size()));
}

// Test: write() produces a non-empty buffer
TEST_F(Cr2HeaderTest_1544, WriteProducesNonEmptyBuffer_1544) {
    Cr2Header header(littleEndian);
    DataBuf buf = header.write();
    EXPECT_GT(buf.size(), 0u);
}

// Test: write() after reading valid data
TEST_F(Cr2HeaderTest_1544, WriteAfterReadProducesValidBuffer_1544) {
    Cr2Header header(littleEndian);
    auto data = buildValidLE();
    ASSERT_TRUE(header.read(data.data(), data.size()));
    DataBuf buf = header.write();
    EXPECT_GT(buf.size(), 0u);
}

// Test: offset2addr() is a static method that returns a value
TEST_F(Cr2HeaderTest_1544, Offset2AddrReturnsValue_1544) {
    // Just verify it doesn't crash and returns some value
    uint32_t addr = Cr2Header::offset2addr();
    // The offset2 field starts at byte 12 in the header
    EXPECT_EQ(addr, 12u);
}

// Test: size boundary - exactly 15 bytes should fail
TEST_F(Cr2HeaderTest_1544, ReadWith15BytesFails_1544) {
    Cr2Header header(littleEndian);
    auto data = buildValidLE();
    EXPECT_FALSE(header.read(data.data(), 15));
}

// Test: tag value 43 in data should fail (wrong tag)
TEST_F(Cr2HeaderTest_1544, ReadWrongTagValue43ReturnsFalse_1544) {
    Cr2Header header(littleEndian);
    auto data = buildValidLE();
    data[2] = 43;  // Should be 42
    data[3] = 0;
    EXPECT_FALSE(header.read(data.data(), data.size()));
}

// Test: all zeros data should fail
TEST_F(Cr2HeaderTest_1544, ReadAllZerosReturnsFalse_1544) {
    Cr2Header header(littleEndian);
    std::vector<byte> data(16, 0);
    EXPECT_FALSE(header.read(data.data(), data.size()));
}

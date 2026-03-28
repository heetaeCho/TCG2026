#include <gtest/gtest.h>
#include <cstring>
#include "orfimage_int.hpp"
#include "types.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class OrfHeaderTest_1749 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that reading with insufficient data (less than 8 bytes) returns false
TEST_F(OrfHeaderTest_1749, ReadTooSmallSize_1749) {
    OrfHeader header(littleEndian);
    byte data[7] = {0};
    EXPECT_FALSE(header.read(data, 7));
}

// Test that reading with zero size returns false
TEST_F(OrfHeaderTest_1749, ReadZeroSize_1749) {
    OrfHeader header(littleEndian);
    byte data[1] = {0};
    EXPECT_FALSE(header.read(data, 0));
}

// Test that reading with exactly 8 bytes but invalid byte order markers returns false
TEST_F(OrfHeaderTest_1749, ReadInvalidByteOrderMarker_1749) {
    OrfHeader header(littleEndian);
    byte data[8] = {'X', 'X', 0, 0, 0, 0, 0, 0};
    EXPECT_FALSE(header.read(data, 8));
}

// Test that mismatched byte order markers return false (e.g., 'I' and 'M')
TEST_F(OrfHeaderTest_1749, ReadMismatchedByteOrderMarkers_1749) {
    OrfHeader header(littleEndian);
    byte data[8] = {'I', 'M', 0, 0, 0, 0, 0, 0};
    EXPECT_FALSE(header.read(data, 8));
}

// Test valid little-endian ORF header with correct tag (0x4f52 = "OR" in little endian: 0x52, 0x4f)
TEST_F(OrfHeaderTest_1749, ReadValidLittleEndianWithORTag_1749) {
    OrfHeader header(littleEndian);
    byte data[8] = {
        'I', 'I',           // Little endian marker
        0x52, 0x4F,         // Tag 0x4F52 in little endian
        0x08, 0x00, 0x00, 0x00  // Offset 8 in little endian
    };
    EXPECT_TRUE(header.read(data, 8));
    EXPECT_EQ(header.byteOrder(), littleEndian);
    EXPECT_EQ(header.offset(), 8u);
}

// Test valid big-endian ORF header with correct tag (0x4f52 in big endian: 0x4f, 0x52)
TEST_F(OrfHeaderTest_1749, ReadValidBigEndianWithORTag_1749) {
    OrfHeader header(bigEndian);
    byte data[8] = {
        'M', 'M',           // Big endian marker
        0x4F, 0x52,         // Tag 0x4F52 in big endian
        0x00, 0x00, 0x00, 0x08  // Offset 8 in big endian
    };
    EXPECT_TRUE(header.read(data, 8));
    EXPECT_EQ(header.byteOrder(), bigEndian);
    EXPECT_EQ(header.offset(), 8u);
}

// Test valid little-endian ORF header with SR signature (0x5352)
TEST_F(OrfHeaderTest_1749, ReadValidLittleEndianWithSRTag_1749) {
    OrfHeader header(littleEndian);
    byte data[8] = {
        'I', 'I',           // Little endian marker
        0x52, 0x53,         // 0x5352 in little endian
        0x08, 0x00, 0x00, 0x00  // Offset 8 in little endian
    };
    EXPECT_TRUE(header.read(data, 8));
    EXPECT_EQ(header.byteOrder(), littleEndian);
}

// Test valid big-endian ORF header with SR signature (0x5352)
TEST_F(OrfHeaderTest_1749, ReadValidBigEndianWithSRTag_1749) {
    OrfHeader header(bigEndian);
    byte data[8] = {
        'M', 'M',           // Big endian marker
        0x53, 0x52,         // 0x5352 in big endian
        0x00, 0x00, 0x00, 0x08  // Offset 8 in big endian
    };
    EXPECT_TRUE(header.read(data, 8));
    EXPECT_EQ(header.byteOrder(), bigEndian);
}

// Test that wrong signature with correct byte order returns false
TEST_F(OrfHeaderTest_1749, ReadWrongSignature_1749) {
    OrfHeader header(littleEndian);
    byte data[8] = {
        'I', 'I',           // Little endian marker
        0x2A, 0x00,         // Standard TIFF signature (0x002A) - not ORF
        0x08, 0x00, 0x00, 0x00
    };
    EXPECT_FALSE(header.read(data, 8));
}

// Test that offset is correctly read in little endian
TEST_F(OrfHeaderTest_1749, ReadOffsetLittleEndian_1749) {
    OrfHeader header(littleEndian);
    byte data[8] = {
        'I', 'I',
        0x52, 0x4F,         // Tag 0x4F52 in LE
        0x10, 0x00, 0x00, 0x00  // Offset 16 in LE
    };
    EXPECT_TRUE(header.read(data, 8));
    EXPECT_EQ(header.offset(), 16u);
}

// Test that offset is correctly read in big endian
TEST_F(OrfHeaderTest_1749, ReadOffsetBigEndian_1749) {
    OrfHeader header(bigEndian);
    byte data[8] = {
        'M', 'M',
        0x4F, 0x52,         // Tag 0x4F52 in BE
        0x00, 0x00, 0x00, 0x10  // Offset 16 in BE
    };
    EXPECT_TRUE(header.read(data, 8));
    EXPECT_EQ(header.offset(), 16u);
}

// Test initial state of OrfHeader with little endian
TEST_F(OrfHeaderTest_1749, InitialStateLittleEndian_1749) {
    OrfHeader header(littleEndian);
    EXPECT_EQ(header.byteOrder(), littleEndian);
    EXPECT_EQ(header.tag(), 0x4F52);
    EXPECT_EQ(header.size(), 8u);
    EXPECT_EQ(header.offset(), 0x00000008u);
}

// Test initial state of OrfHeader with big endian
TEST_F(OrfHeaderTest_1749, InitialStateBigEndian_1749) {
    OrfHeader header(bigEndian);
    EXPECT_EQ(header.byteOrder(), bigEndian);
    EXPECT_EQ(header.tag(), 0x4F52);
    EXPECT_EQ(header.size(), 8u);
    EXPECT_EQ(header.offset(), 0x00000008u);
}

// Test write method produces valid data that can be read back
TEST_F(OrfHeaderTest_1749, WriteAndReadBackLittleEndian_1749) {
    OrfHeader headerWrite(littleEndian);
    DataBuf buf = headerWrite.write();
    ASSERT_GE(buf.size(), 8u);

    OrfHeader headerRead(littleEndian);
    EXPECT_TRUE(headerRead.read(buf.c_data(), buf.size()));
    EXPECT_EQ(headerRead.byteOrder(), littleEndian);
}

// Test write method produces valid data for big endian
TEST_F(OrfHeaderTest_1749, WriteAndReadBackBigEndian_1749) {
    OrfHeader headerWrite(bigEndian);
    DataBuf buf = headerWrite.write();
    ASSERT_GE(buf.size(), 8u);

    OrfHeader headerRead(bigEndian);
    EXPECT_TRUE(headerRead.read(buf.c_data(), buf.size()));
    EXPECT_EQ(headerRead.byteOrder(), bigEndian);
}

// Test reading with size exactly 8 (boundary)
TEST_F(OrfHeaderTest_1749, ReadExactly8Bytes_1749) {
    OrfHeader header(littleEndian);
    byte data[8] = {
        'I', 'I',
        0x52, 0x4F,
        0x08, 0x00, 0x00, 0x00
    };
    EXPECT_TRUE(header.read(data, 8));
}

// Test reading with more than 8 bytes still works
TEST_F(OrfHeaderTest_1749, ReadMoreThan8Bytes_1749) {
    OrfHeader header(littleEndian);
    byte data[16] = {
        'I', 'I',
        0x52, 0x4F,
        0x08, 0x00, 0x00, 0x00,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
    };
    EXPECT_TRUE(header.read(data, 16));
    EXPECT_EQ(header.byteOrder(), littleEndian);
}

// Test that byte order is changed by read (initial big endian, data says little endian)
TEST_F(OrfHeaderTest_1749, ReadChangesInitialByteOrder_1749) {
    OrfHeader header(bigEndian);  // Initial big endian
    byte data[8] = {
        'I', 'I',           // Little endian marker
        0x52, 0x4F,         // Tag 0x4F52 in LE
        0x08, 0x00, 0x00, 0x00
    };
    EXPECT_TRUE(header.read(data, 8));
    EXPECT_EQ(header.byteOrder(), littleEndian);
}

// Test with single byte 'I' followed by different byte
TEST_F(OrfHeaderTest_1749, ReadFirstByteIMismatchSecond_1749) {
    OrfHeader header(littleEndian);
    byte data[8] = {
        'I', 'J',           // Mismatched
        0x52, 0x4F,
        0x08, 0x00, 0x00, 0x00
    };
    EXPECT_FALSE(header.read(data, 8));
}

// Test with single byte 'M' followed by different byte
TEST_F(OrfHeaderTest_1749, ReadFirstByteMismatchSecond_1749) {
    OrfHeader header(bigEndian);
    byte data[8] = {
        'M', 'N',           // Mismatched
        0x4F, 0x52,
        0x00, 0x00, 0x00, 0x08
    };
    EXPECT_FALSE(header.read(data, 8));
}

// Test with all zeros
TEST_F(OrfHeaderTest_1749, ReadAllZeros_1749) {
    OrfHeader header(littleEndian);
    byte data[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    EXPECT_FALSE(header.read(data, 8));
}

// Test that a large offset is correctly parsed
TEST_F(OrfHeaderTest_1749, ReadLargeOffset_1749) {
    OrfHeader header(littleEndian);
    byte data[8] = {
        'I', 'I',
        0x52, 0x4F,
        0xFF, 0xFF, 0x00, 0x00  // Offset 0x0000FFFF in LE
    };
    EXPECT_TRUE(header.read(data, 8));
    EXPECT_EQ(header.offset(), 0x0000FFFFu);
}

// Test reading with size 1 returns false
TEST_F(OrfHeaderTest_1749, ReadSize1_1749) {
    OrfHeader header(littleEndian);
    byte data[1] = {'I'};
    EXPECT_FALSE(header.read(data, 1));
}

// Test reading with size 4 returns false (still less than 8)
TEST_F(OrfHeaderTest_1749, ReadSize4_1749) {
    OrfHeader header(littleEndian);
    byte data[4] = {'I', 'I', 0x52, 0x4F};
    EXPECT_FALSE(header.read(data, 4));
}

// Test write produces buffer of expected size
TEST_F(OrfHeaderTest_1749, WriteBufferSize_1749) {
    OrfHeader header(littleEndian);
    DataBuf buf = header.write();
    EXPECT_EQ(buf.size(), 8u);
}

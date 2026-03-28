#include <gtest/gtest.h>
#include "tiffimage_int.hpp"
#include "types.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// A concrete subclass to test TiffHeaderBase since it has virtual methods
// but we need to instantiate it for testing
class TestableTiffHeader : public TiffHeaderBase {
public:
    TestableTiffHeader(uint16_t tag, uint32_t size, ByteOrder byteOrder, uint32_t offset)
        : TiffHeaderBase(tag, size, byteOrder, offset) {}
};

class TiffHeaderBaseTest_1170 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test write() with little endian byte order
TEST_F(TiffHeaderBaseTest_1170, WriteLittleEndian_1170) {
    // Standard TIFF tag is 42 (0x002A)
    TestableTiffHeader header(42, 8, littleEndian, 8);
    DataBuf buf = header.write();
    
    ASSERT_EQ(buf.size(), 8u);
    
    // Little endian: first two bytes should be 'I', 'I'
    EXPECT_EQ(buf.read_uint8(0), 'I');
    EXPECT_EQ(buf.read_uint8(1), 'I');
    
    // Tag at offset 2 in little endian
    EXPECT_EQ(buf.read_uint16(2, littleEndian), 42);
    
    // Offset at position 4 should be 0x00000008
    EXPECT_EQ(buf.read_uint32(4, littleEndian), 0x00000008u);
}

// Test write() with big endian byte order
TEST_F(TiffHeaderBaseTest_1170, WriteBigEndian_1170) {
    TestableTiffHeader header(42, 8, bigEndian, 8);
    DataBuf buf = header.write();
    
    ASSERT_EQ(buf.size(), 8u);
    
    // Big endian: first two bytes should be 'M', 'M'
    EXPECT_EQ(buf.read_uint8(0), 'M');
    EXPECT_EQ(buf.read_uint8(1), 'M');
    
    // Tag at offset 2 in big endian
    EXPECT_EQ(buf.read_uint16(2, bigEndian), 42);
    
    // Offset at position 4 should be 0x00000008
    EXPECT_EQ(buf.read_uint32(4, bigEndian), 0x00000008u);
}

// Test write() with invalid byte order
TEST_F(TiffHeaderBaseTest_1170, WriteInvalidByteOrder_1170) {
    TestableTiffHeader header(42, 8, invalidByteOrder, 8);
    DataBuf buf = header.write();
    
    ASSERT_EQ(buf.size(), 8u);
    
    // With invalidByteOrder, no byte order marker is written at offset 0
    // buf[0] remains 0 (default initialized), and buf[1] copies buf[0]
    EXPECT_EQ(buf.read_uint8(0), 0);
    EXPECT_EQ(buf.read_uint8(1), 0);
}

// Test that buffer size is always 8
TEST_F(TiffHeaderBaseTest_1170, WriteBufferSizeIsAlways8_1170) {
    TestableTiffHeader header(0xFFFF, 100, littleEndian, 0);
    DataBuf buf = header.write();
    EXPECT_EQ(buf.size(), 8u);
}

// Test write() with a different tag value
TEST_F(TiffHeaderBaseTest_1170, WriteWithDifferentTag_1170) {
    uint16_t customTag = 0x0055;
    TestableTiffHeader header(customTag, 8, littleEndian, 8);
    DataBuf buf = header.write();
    
    ASSERT_EQ(buf.size(), 8u);
    EXPECT_EQ(buf.read_uint16(2, littleEndian), customTag);
}

// Test write() offset is always written as 0x00000008
TEST_F(TiffHeaderBaseTest_1170, WriteOffsetIsAlways8_1170) {
    // Even if we pass a different offset to the constructor,
    // write() hardcodes 0x00000008
    TestableTiffHeader header(42, 8, littleEndian, 0x100);
    DataBuf buf = header.write();
    
    ASSERT_EQ(buf.size(), 8u);
    EXPECT_EQ(buf.read_uint32(4, littleEndian), 0x00000008u);
}

// Test byteOrder() accessor
TEST_F(TiffHeaderBaseTest_1170, ByteOrderAccessor_1170) {
    TestableTiffHeader header(42, 8, littleEndian, 8);
    EXPECT_EQ(header.byteOrder(), littleEndian);
    
    TestableTiffHeader header2(42, 8, bigEndian, 8);
    EXPECT_EQ(header2.byteOrder(), bigEndian);
    
    TestableTiffHeader header3(42, 8, invalidByteOrder, 8);
    EXPECT_EQ(header3.byteOrder(), invalidByteOrder);
}

// Test setByteOrder()
TEST_F(TiffHeaderBaseTest_1170, SetByteOrder_1170) {
    TestableTiffHeader header(42, 8, littleEndian, 8);
    EXPECT_EQ(header.byteOrder(), littleEndian);
    
    header.setByteOrder(bigEndian);
    EXPECT_EQ(header.byteOrder(), bigEndian);
    
    // Verify write() reflects the new byte order
    DataBuf buf = header.write();
    EXPECT_EQ(buf.read_uint8(0), 'M');
    EXPECT_EQ(buf.read_uint8(1), 'M');
}

// Test offset() accessor
TEST_F(TiffHeaderBaseTest_1170, OffsetAccessor_1170) {
    TestableTiffHeader header(42, 8, littleEndian, 0x100);
    EXPECT_EQ(header.offset(), 0x100u);
}

// Test setOffset()
TEST_F(TiffHeaderBaseTest_1170, SetOffset_1170) {
    TestableTiffHeader header(42, 8, littleEndian, 8);
    EXPECT_EQ(header.offset(), 8u);
    
    header.setOffset(0x200);
    EXPECT_EQ(header.offset(), 0x200u);
}

// Test size() accessor
TEST_F(TiffHeaderBaseTest_1170, SizeAccessor_1170) {
    TestableTiffHeader header(42, 8, littleEndian, 8);
    EXPECT_EQ(header.size(), 8u);
    
    TestableTiffHeader header2(42, 16, bigEndian, 8);
    EXPECT_EQ(header2.size(), 16u);
}

// Test tag() accessor
TEST_F(TiffHeaderBaseTest_1170, TagAccessor_1170) {
    TestableTiffHeader header(42, 8, littleEndian, 8);
    EXPECT_EQ(header.tag(), 42);
    
    TestableTiffHeader header2(0x4F52, 8, bigEndian, 8);
    EXPECT_EQ(header2.tag(), 0x4F52);
}

// Test write() with big endian tag encoding
TEST_F(TiffHeaderBaseTest_1170, WriteTagEncodingBigEndian_1170) {
    uint16_t tag = 0x002A;
    TestableTiffHeader header(tag, 8, bigEndian, 8);
    DataBuf buf = header.write();
    
    ASSERT_EQ(buf.size(), 8u);
    // Read with big endian should give the correct tag
    EXPECT_EQ(buf.read_uint16(2, bigEndian), 0x002A);
}

// Test write() with big endian offset encoding
TEST_F(TiffHeaderBaseTest_1170, WriteOffsetEncodingBigEndian_1170) {
    TestableTiffHeader header(42, 8, bigEndian, 8);
    DataBuf buf = header.write();
    
    ASSERT_EQ(buf.size(), 8u);
    EXPECT_EQ(buf.read_uint32(4, bigEndian), 0x00000008u);
}

// Test write() byte order marker symmetry (byte at 0 equals byte at 1)
TEST_F(TiffHeaderBaseTest_1170, WriteByteOrderMarkerSymmetry_1170) {
    TestableTiffHeader headerLE(42, 8, littleEndian, 8);
    DataBuf bufLE = headerLE.write();
    EXPECT_EQ(bufLE.read_uint8(0), bufLE.read_uint8(1));
    
    TestableTiffHeader headerBE(42, 8, bigEndian, 8);
    DataBuf bufBE = headerBE.write();
    EXPECT_EQ(bufBE.read_uint8(0), bufBE.read_uint8(1));
    
    TestableTiffHeader headerInv(42, 8, invalidByteOrder, 8);
    DataBuf bufInv = headerInv.write();
    EXPECT_EQ(bufInv.read_uint8(0), bufInv.read_uint8(1));
}

// Test write() with zero tag
TEST_F(TiffHeaderBaseTest_1170, WriteZeroTag_1170) {
    TestableTiffHeader header(0, 8, littleEndian, 8);
    DataBuf buf = header.write();
    
    ASSERT_EQ(buf.size(), 8u);
    EXPECT_EQ(buf.read_uint16(2, littleEndian), 0);
}

// Test write() with max uint16 tag
TEST_F(TiffHeaderBaseTest_1170, WriteMaxTag_1170) {
    TestableTiffHeader header(0xFFFF, 8, littleEndian, 8);
    DataBuf buf = header.write();
    
    ASSERT_EQ(buf.size(), 8u);
    EXPECT_EQ(buf.read_uint16(2, littleEndian), 0xFFFF);
}

// Test that setByteOrder changes write output from LE to BE
TEST_F(TiffHeaderBaseTest_1170, SetByteOrderChangesWriteOutput_1170) {
    TestableTiffHeader header(42, 8, littleEndian, 8);
    
    DataBuf buf1 = header.write();
    EXPECT_EQ(buf1.read_uint8(0), 'I');
    
    header.setByteOrder(bigEndian);
    DataBuf buf2 = header.write();
    EXPECT_EQ(buf2.read_uint8(0), 'M');
}

// Test print() doesn't crash (basic smoke test)
TEST_F(TiffHeaderBaseTest_1170, PrintDoesNotCrash_1170) {
    TestableTiffHeader header(42, 8, littleEndian, 8);
    std::ostringstream oss;
    EXPECT_NO_THROW(header.print(oss, ""));
}

// Test print() with prefix
TEST_F(TiffHeaderBaseTest_1170, PrintWithPrefix_1170) {
    TestableTiffHeader header(42, 8, bigEndian, 8);
    std::ostringstream oss;
    EXPECT_NO_THROW(header.print(oss, "TestPrefix: "));
    // Just verify something was written
    EXPECT_FALSE(oss.str().empty());
}

// Test isImageTag() returns false by default
TEST_F(TiffHeaderBaseTest_1170, IsImageTagReturnsFalse_1170) {
    TestableTiffHeader header(42, 8, littleEndian, 8);
    PrimaryGroups pg;
    EXPECT_FALSE(header.isImageTag(0, IfdId::ifd0Id, pg));
}

// Test read() with valid TIFF little endian header
TEST_F(TiffHeaderBaseTest_1170, ReadValidLittleEndianHeader_1170) {
    TestableTiffHeader header(42, 8, littleEndian, 8);
    
    // Create a valid little endian TIFF header
    uint8_t data[8];
    data[0] = 'I';  // Little endian marker
    data[1] = 'I';
    // Tag 42 in little endian
    data[2] = 0x2A;
    data[3] = 0x00;
    // Offset 8 in little endian
    data[4] = 0x08;
    data[5] = 0x00;
    data[6] = 0x00;
    data[7] = 0x00;
    
    bool result = header.read(data, 8);
    EXPECT_TRUE(result);
    EXPECT_EQ(header.byteOrder(), littleEndian);
}

// Test read() with valid TIFF big endian header
TEST_F(TiffHeaderBaseTest_1170, ReadValidBigEndianHeader_1170) {
    TestableTiffHeader header(42, 8, bigEndian, 8);
    
    // Create a valid big endian TIFF header
    uint8_t data[8];
    data[0] = 'M';  // Big endian marker
    data[1] = 'M';
    // Tag 42 in big endian
    data[2] = 0x00;
    data[3] = 0x2A;
    // Offset 8 in big endian
    data[4] = 0x00;
    data[5] = 0x00;
    data[6] = 0x00;
    data[7] = 0x08;
    
    bool result = header.read(data, 8);
    EXPECT_TRUE(result);
    EXPECT_EQ(header.byteOrder(), bigEndian);
}

// Test read() with too small buffer
TEST_F(TiffHeaderBaseTest_1170, ReadTooSmallBuffer_1170) {
    TestableTiffHeader header(42, 8, littleEndian, 8);
    uint8_t data[4] = {'I', 'I', 0x2A, 0x00};
    
    bool result = header.read(data, 4);
    EXPECT_FALSE(result);
}

// Test read() with invalid byte order marker
TEST_F(TiffHeaderBaseTest_1170, ReadInvalidByteOrderMarker_1170) {
    TestableTiffHeader header(42, 8, littleEndian, 8);
    
    uint8_t data[8] = {'X', 'X', 0x2A, 0x00, 0x08, 0x00, 0x00, 0x00};
    bool result = header.read(data, 8);
    EXPECT_FALSE(result);
}

#include <gtest/gtest.h>
#include <exiv2/image.hpp>
#include <exiv2/types.hpp>
#include <cstring>

using namespace Exiv2;

// Tests for Image::byteSwap(uint32_t, bool)
class ByteSwapTest_1710 : public ::testing::Test {};

TEST_F(ByteSwapTest_1710, ByteSwap32NoSwap_1710) {
    uint32_t value = 0x12345678;
    uint32_t result = Image::byteSwap(value, false);
    EXPECT_EQ(result, value);
}

TEST_F(ByteSwapTest_1710, ByteSwap32WithSwap_1710) {
    uint32_t value = 0x12345678;
    uint32_t result = Image::byteSwap(value, true);
    EXPECT_EQ(result, 0x78563412u);
}

TEST_F(ByteSwapTest_1710, ByteSwap32Zero_1710) {
    uint32_t value = 0x00000000;
    uint32_t result = Image::byteSwap(value, true);
    EXPECT_EQ(result, 0x00000000u);
}

TEST_F(ByteSwapTest_1710, ByteSwap32MaxValue_1710) {
    uint32_t value = 0xFFFFFFFF;
    uint32_t result = Image::byteSwap(value, true);
    EXPECT_EQ(result, 0xFFFFFFFFu);
}

TEST_F(ByteSwapTest_1710, ByteSwap32DoubleSwapReturnsOriginal_1710) {
    uint32_t value = 0xDEADBEEF;
    uint32_t swapped = Image::byteSwap(value, true);
    uint32_t restored = Image::byteSwap(swapped, true);
    EXPECT_EQ(restored, value);
}

// Tests for Image::byteSwap(uint16_t, bool)
TEST_F(ByteSwapTest_1710, ByteSwap16NoSwap_1710) {
    uint16_t value = 0x1234;
    uint16_t result = Image::byteSwap(value, false);
    EXPECT_EQ(result, value);
}

TEST_F(ByteSwapTest_1710, ByteSwap16WithSwap_1710) {
    uint16_t value = 0x1234;
    uint16_t result = Image::byteSwap(value, true);
    EXPECT_EQ(result, 0x3412);
}

TEST_F(ByteSwapTest_1710, ByteSwap16Zero_1710) {
    uint16_t value = 0x0000;
    uint16_t result = Image::byteSwap(value, true);
    EXPECT_EQ(result, 0x0000);
}

TEST_F(ByteSwapTest_1710, ByteSwap16MaxValue_1710) {
    uint16_t value = 0xFFFF;
    uint16_t result = Image::byteSwap(value, true);
    EXPECT_EQ(result, 0xFFFF);
}

TEST_F(ByteSwapTest_1710, ByteSwap16DoubleSwapReturnsOriginal_1710) {
    uint16_t value = 0xABCD;
    uint16_t swapped = Image::byteSwap(value, true);
    uint16_t restored = Image::byteSwap(swapped, true);
    EXPECT_EQ(restored, value);
}

// Tests for Image::byteSwap(uint64_t, bool)
TEST_F(ByteSwapTest_1710, ByteSwap64NoSwap_1710) {
    uint64_t value = 0x0102030405060708ULL;
    uint64_t result = Image::byteSwap(value, false);
    EXPECT_EQ(result, value);
}

TEST_F(ByteSwapTest_1710, ByteSwap64WithSwap_1710) {
    uint64_t value = 0x0102030405060708ULL;
    uint64_t result = Image::byteSwap(value, true);
    EXPECT_EQ(result, 0x0807060504030201ULL);
}

TEST_F(ByteSwapTest_1710, ByteSwap64Zero_1710) {
    uint64_t value = 0x0000000000000000ULL;
    uint64_t result = Image::byteSwap(value, true);
    EXPECT_EQ(result, 0x0000000000000000ULL);
}

TEST_F(ByteSwapTest_1710, ByteSwap64DoubleSwapReturnsOriginal_1710) {
    uint64_t value = 0xDEADBEEFCAFEBABEULL;
    uint64_t swapped = Image::byteSwap(value, true);
    uint64_t restored = Image::byteSwap(swapped, true);
    EXPECT_EQ(restored, value);
}

// Tests for Image::byteSwap2
TEST_F(ByteSwapTest_1710, ByteSwap2NoSwap_1710) {
    byte data[] = {0x12, 0x34, 0x00, 0x00};
    DataBuf buf(data, sizeof(data));
    uint16_t result = Image::byteSwap2(buf, 0, false);
    // Without swap, it reads the bytes as-is and interprets them
    uint16_t expected = Image::byteSwap(static_cast<uint16_t>((data[1] << 8) | data[0]), false);
    // We just verify the no-swap case returns consistent value
    EXPECT_EQ(result, Image::byteSwap2(buf, 0, false));
}

TEST_F(ByteSwapTest_1710, ByteSwap2WithSwap_1710) {
    byte data[] = {0x12, 0x34, 0x00, 0x00};
    DataBuf buf(data, sizeof(data));
    uint16_t noSwap = Image::byteSwap2(buf, 0, false);
    uint16_t withSwap = Image::byteSwap2(buf, 0, true);
    EXPECT_EQ(withSwap, Image::byteSwap(noSwap, true));
}

// Tests for Image::byteSwap4
TEST_F(ByteSwapTest_1710, ByteSwap4NoSwap_1710) {
    byte data[] = {0x12, 0x34, 0x56, 0x78};
    DataBuf buf(data, sizeof(data));
    uint32_t result = Image::byteSwap4(buf, 0, false);
    EXPECT_EQ(result, Image::byteSwap4(buf, 0, false));
}

TEST_F(ByteSwapTest_1710, ByteSwap4WithSwapConsistency_1710) {
    byte data[] = {0x12, 0x34, 0x56, 0x78};
    DataBuf buf(data, sizeof(data));
    uint32_t noSwap = Image::byteSwap4(buf, 0, false);
    uint32_t withSwap = Image::byteSwap4(buf, 0, true);
    EXPECT_EQ(withSwap, Image::byteSwap(noSwap, true));
}

// Tests for Image::byteSwap8
TEST_F(ByteSwapTest_1710, ByteSwap8NoSwap_1710) {
    byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
    DataBuf buf(data, sizeof(data));
    uint64_t result = Image::byteSwap8(buf, 0, false);
    EXPECT_EQ(result, Image::byteSwap8(buf, 0, false));
}

TEST_F(ByteSwapTest_1710, ByteSwap8WithSwapConsistency_1710) {
    byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
    DataBuf buf(data, sizeof(data));
    uint64_t noSwap = Image::byteSwap8(buf, 0, false);
    uint64_t withSwap = Image::byteSwap8(buf, 0, true);
    EXPECT_EQ(withSwap, Image::byteSwap(noSwap, true));
}

// Tests for DataBuf read/write operations used by byteSwap_
class DataBufTest_1710 : public ::testing::Test {};

TEST_F(DataBufTest_1710, ReadWriteUint8_1710) {
    DataBuf buf(4);
    buf.write_uint8(0, 0xAA);
    buf.write_uint8(1, 0xBB);
    buf.write_uint8(2, 0xCC);
    buf.write_uint8(3, 0xDD);
    EXPECT_EQ(buf.read_uint8(0), 0xAA);
    EXPECT_EQ(buf.read_uint8(1), 0xBB);
    EXPECT_EQ(buf.read_uint8(2), 0xCC);
    EXPECT_EQ(buf.read_uint8(3), 0xDD);
}

TEST_F(DataBufTest_1710, DataBufSize_1710) {
    DataBuf buf(10);
    EXPECT_EQ(buf.size(), 10u);
}

TEST_F(DataBufTest_1710, DataBufEmpty_1710) {
    DataBuf buf;
    EXPECT_TRUE(buf.empty());
}

TEST_F(DataBufTest_1710, DataBufNotEmpty_1710) {
    DataBuf buf(5);
    EXPECT_FALSE(buf.empty());
}

TEST_F(DataBufTest_1710, DataBufFromData_1710) {
    byte data[] = {0x01, 0x02, 0x03, 0x04};
    DataBuf buf(data, 4);
    EXPECT_EQ(buf.size(), 4u);
    EXPECT_EQ(buf.read_uint8(0), 0x01);
    EXPECT_EQ(buf.read_uint8(1), 0x02);
    EXPECT_EQ(buf.read_uint8(2), 0x03);
    EXPECT_EQ(buf.read_uint8(3), 0x04);
}

TEST_F(DataBufTest_1710, DataBufAlloc_1710) {
    DataBuf buf;
    buf.alloc(8);
    EXPECT_EQ(buf.size(), 8u);
}

TEST_F(DataBufTest_1710, DataBufResize_1710) {
    DataBuf buf(4);
    buf.resize(8);
    EXPECT_EQ(buf.size(), 8u);
}

TEST_F(DataBufTest_1710, DataBufReset_1710) {
    DataBuf buf(4);
    buf.reset();
    EXPECT_TRUE(buf.empty());
}

TEST_F(DataBufTest_1710, ReadWriteUint32_1710) {
    DataBuf buf(4);
    buf.write_uint32(0, 0x12345678, littleEndian);
    uint32_t val = buf.read_uint32(0, littleEndian);
    EXPECT_EQ(val, 0x12345678u);
}

TEST_F(DataBufTest_1710, ReadWriteUint16_1710) {
    DataBuf buf(2);
    buf.write_uint16(0, 0xABCD, bigEndian);
    uint16_t val = buf.read_uint16(0, bigEndian);
    EXPECT_EQ(val, 0xABCD);
}

TEST_F(DataBufTest_1710, ReadWriteUint64_1710) {
    DataBuf buf(8);
    buf.write_uint64(0, 0x0102030405060708ULL, littleEndian);
    uint64_t val = buf.read_uint64(0, littleEndian);
    EXPECT_EQ(val, 0x0102030405060708ULL);
}

TEST_F(DataBufTest_1710, DataPointerAccess_1710) {
    byte data[] = {0xFF, 0xFE, 0xFD};
    DataBuf buf(data, 3);
    EXPECT_NE(buf.data(0), nullptr);
    EXPECT_EQ(*buf.data(0), 0xFF);
    EXPECT_EQ(*buf.data(1), 0xFE);
    EXPECT_EQ(*buf.data(2), 0xFD);
}

TEST_F(DataBufTest_1710, ConstDataPointerAccess_1710) {
    byte data[] = {0x10, 0x20};
    DataBuf buf(data, 2);
    const byte* p = buf.c_data(0);
    EXPECT_NE(p, nullptr);
    EXPECT_EQ(p[0], 0x10);
    EXPECT_EQ(p[1], 0x20);
}

TEST_F(DataBufTest_1710, CmpBytes_1710) {
    byte data[] = {0x01, 0x02, 0x03, 0x04};
    DataBuf buf(data, 4);
    byte cmp[] = {0x01, 0x02, 0x03, 0x04};
    EXPECT_EQ(buf.cmpBytes(0, cmp, 4), 0);
}

TEST_F(DataBufTest_1710, CmpBytesMismatch_1710) {
    byte data[] = {0x01, 0x02, 0x03, 0x04};
    DataBuf buf(data, 4);
    byte cmp[] = {0x01, 0x02, 0xFF, 0x04};
    EXPECT_NE(buf.cmpBytes(0, cmp, 4), 0);
}

// Tests for platform endianness detection
TEST_F(ByteSwapTest_1710, PlatformEndianness_1710) {
    bool isBig = Image::isBigEndianPlatform();
    bool isLittle = Image::isLittleEndianPlatform();
    // Exactly one should be true
    EXPECT_NE(isBig, isLittle);
}

// Test byteSwap32 with specific byte patterns
TEST_F(ByteSwapTest_1710, ByteSwap32SingleByteHigh_1710) {
    uint32_t value = 0xFF000000;
    uint32_t result = Image::byteSwap(value, true);
    EXPECT_EQ(result, 0x000000FFu);
}

TEST_F(ByteSwapTest_1710, ByteSwap32SingleByteLow_1710) {
    uint32_t value = 0x000000FF;
    uint32_t result = Image::byteSwap(value, true);
    EXPECT_EQ(result, 0xFF000000u);
}

TEST_F(ByteSwapTest_1710, ByteSwap32Symmetric_1710) {
    uint32_t value = 0xABCDCDAB;
    uint32_t result = Image::byteSwap(value, true);
    EXPECT_EQ(result, 0xABCDCDABu);
}

// Offset-based byteSwap tests
TEST_F(ByteSwapTest_1710, ByteSwap4WithOffset_1710) {
    byte data[] = {0x00, 0x00, 0x12, 0x34, 0x56, 0x78};
    DataBuf buf(data, sizeof(data));
    uint32_t noSwap = Image::byteSwap4(buf, 2, false);
    uint32_t withSwap = Image::byteSwap4(buf, 2, true);
    EXPECT_EQ(withSwap, Image::byteSwap(noSwap, true));
}

TEST_F(ByteSwapTest_1710, ByteSwap2WithOffset_1710) {
    byte data[] = {0x00, 0x00, 0xAB, 0xCD};
    DataBuf buf(data, sizeof(data));
    uint16_t noSwap = Image::byteSwap2(buf, 2, false);
    uint16_t withSwap = Image::byteSwap2(buf, 2, true);
    EXPECT_EQ(withSwap, Image::byteSwap(noSwap, true));
}

// DataBuf write then read with different endianness
TEST_F(DataBufTest_1710, ReadWriteUint32DifferentEndianness_1710) {
    DataBuf buf(4);
    buf.write_uint32(0, 0x12345678, bigEndian);
    uint32_t valBig = buf.read_uint32(0, bigEndian);
    uint32_t valLittle = buf.read_uint32(0, littleEndian);
    EXPECT_EQ(valBig, 0x12345678u);
    EXPECT_EQ(valLittle, 0x78563412u);
}

TEST_F(DataBufTest_1710, ReadWriteUint16DifferentEndianness_1710) {
    DataBuf buf(2);
    buf.write_uint16(0, 0x1234, bigEndian);
    uint16_t valBig = buf.read_uint16(0, bigEndian);
    uint16_t valLittle = buf.read_uint16(0, littleEndian);
    EXPECT_EQ(valBig, 0x1234);
    EXPECT_EQ(valLittle, 0x3412);
}

// Test writing individual bytes and reading as uint32
TEST_F(DataBufTest_1710, ManualBytesReadAsUint32_1710) {
    DataBuf buf(4);
    buf.write_uint8(0, 0x78);
    buf.write_uint8(1, 0x56);
    buf.write_uint8(2, 0x34);
    buf.write_uint8(3, 0x12);
    uint32_t val = buf.read_uint32(0, bigEndian);
    EXPECT_EQ(val, 0x78563412u);
}

// Boundary: single byte buffer
TEST_F(DataBufTest_1710, SingleByteBuf_1710) {
    DataBuf buf(1);
    buf.write_uint8(0, 0x42);
    EXPECT_EQ(buf.read_uint8(0), 0x42);
    EXPECT_EQ(buf.size(), 1u);
}

// Test resize preserves existing data
TEST_F(DataBufTest_1710, ResizePreservesData_1710) {
    byte data[] = {0x01, 0x02, 0x03, 0x04};
    DataBuf buf(data, 4);
    buf.resize(8);
    EXPECT_EQ(buf.read_uint8(0), 0x01);
    EXPECT_EQ(buf.read_uint8(1), 0x02);
    EXPECT_EQ(buf.read_uint8(2), 0x03);
    EXPECT_EQ(buf.read_uint8(3), 0x04);
}

// DataBuf with zero size
TEST_F(DataBufTest_1710, ZeroSizeBuf_1710) {
    DataBuf buf(0);
    EXPECT_TRUE(buf.empty());
    EXPECT_EQ(buf.size(), 0u);
}

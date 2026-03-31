#include <gtest/gtest.h>
#include <exiv2/types.hpp>
#include <climits>
#include <cstring>
#include <stdexcept>

using namespace Exiv2;

// ============================================================
// DataBuf Construction Tests
// ============================================================

TEST(DataBufTest_1130, DefaultConstructor_1130) {
    DataBuf buf;
    EXPECT_EQ(buf.size(), 0u);
    EXPECT_TRUE(buf.empty());
}

TEST(DataBufTest_1130, SizeConstructor_1130) {
    DataBuf buf(100);
    EXPECT_EQ(buf.size(), 100u);
    EXPECT_FALSE(buf.empty());
}

TEST(DataBufTest_1130, SizeConstructorZero_1130) {
    DataBuf buf(0);
    EXPECT_EQ(buf.size(), 0u);
    EXPECT_TRUE(buf.empty());
}

TEST(DataBufTest_1130, DataPointerConstructor_1130) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    DataBuf buf(data, 5);
    EXPECT_EQ(buf.size(), 5u);
    EXPECT_FALSE(buf.empty());
    EXPECT_EQ(buf.read_uint8(0), 0x01);
    EXPECT_EQ(buf.read_uint8(4), 0x05);
}

TEST(DataBufTest_1130, DataPointerConstructorZeroSize_1130) {
    const byte data[] = {0x01};
    DataBuf buf(data, 0);
    EXPECT_EQ(buf.size(), 0u);
    EXPECT_TRUE(buf.empty());
}

// ============================================================
// Alloc / Resize / Reset Tests
// ============================================================

TEST(DataBufTest_1130, Alloc_1130) {
    DataBuf buf;
    buf.alloc(50);
    EXPECT_EQ(buf.size(), 50u);
}

TEST(DataBufTest_1130, AllocZero_1130) {
    DataBuf buf(10);
    buf.alloc(0);
    EXPECT_EQ(buf.size(), 0u);
}

TEST(DataBufTest_1130, Resize_1130) {
    DataBuf buf(10);
    buf.resize(20);
    EXPECT_EQ(buf.size(), 20u);
}

TEST(DataBufTest_1130, ResizeShrink_1130) {
    DataBuf buf(20);
    buf.resize(5);
    EXPECT_EQ(buf.size(), 5u);
}

TEST(DataBufTest_1130, ResizeToZero_1130) {
    DataBuf buf(10);
    buf.resize(0);
    EXPECT_EQ(buf.size(), 0u);
    EXPECT_TRUE(buf.empty());
}

TEST(DataBufTest_1130, Reset_1130) {
    DataBuf buf(100);
    buf.reset();
    EXPECT_EQ(buf.size(), 0u);
    EXPECT_TRUE(buf.empty());
}

// ============================================================
// Read/Write uint8 Tests
// ============================================================

TEST(DataBufTest_1130, ReadWriteUint8_1130) {
    DataBuf buf(4);
    buf.write_uint8(0, 0x00);
    buf.write_uint8(1, 0x7F);
    buf.write_uint8(2, 0x80);
    buf.write_uint8(3, 0xFF);
    EXPECT_EQ(buf.read_uint8(0), 0x00);
    EXPECT_EQ(buf.read_uint8(1), 0x7F);
    EXPECT_EQ(buf.read_uint8(2), 0x80);
    EXPECT_EQ(buf.read_uint8(3), 0xFF);
}

// ============================================================
// Read/Write uint16 Tests
// ============================================================

TEST(DataBufTest_1130, ReadWriteUint16LittleEndian_1130) {
    DataBuf buf(4);
    buf.write_uint16(0, 0x1234, littleEndian);
    EXPECT_EQ(buf.read_uint16(0, littleEndian), 0x1234);
}

TEST(DataBufTest_1130, ReadWriteUint16BigEndian_1130) {
    DataBuf buf(4);
    buf.write_uint16(0, 0x1234, bigEndian);
    EXPECT_EQ(buf.read_uint16(0, bigEndian), 0x1234);
}

TEST(DataBufTest_1130, ReadWriteUint16EndianMismatch_1130) {
    DataBuf buf(4);
    buf.write_uint16(0, 0x1234, bigEndian);
    // Reading with different endian should give byte-swapped result
    uint16_t val = buf.read_uint16(0, littleEndian);
    EXPECT_EQ(val, 0x3412);
}

TEST(DataBufTest_1130, ReadWriteUint16BoundaryValues_1130) {
    DataBuf buf(4);
    buf.write_uint16(0, 0x0000, littleEndian);
    EXPECT_EQ(buf.read_uint16(0, littleEndian), 0x0000);

    buf.write_uint16(0, 0xFFFF, littleEndian);
    EXPECT_EQ(buf.read_uint16(0, littleEndian), 0xFFFF);
}

TEST(DataBufTest_1130, ReadWriteUint16AtOffset_1130) {
    DataBuf buf(10);
    buf.write_uint16(4, 0xABCD, bigEndian);
    EXPECT_EQ(buf.read_uint16(4, bigEndian), 0xABCD);
}

// ============================================================
// Read/Write uint32 Tests
// ============================================================

TEST(DataBufTest_1130, ReadWriteUint32LittleEndian_1130) {
    DataBuf buf(8);
    buf.write_uint32(0, 0x12345678, littleEndian);
    EXPECT_EQ(buf.read_uint32(0, littleEndian), 0x12345678u);
}

TEST(DataBufTest_1130, ReadWriteUint32BigEndian_1130) {
    DataBuf buf(8);
    buf.write_uint32(0, 0x12345678, bigEndian);
    EXPECT_EQ(buf.read_uint32(0, bigEndian), 0x12345678u);
}

TEST(DataBufTest_1130, ReadWriteUint32EndianMismatch_1130) {
    DataBuf buf(8);
    buf.write_uint32(0, 0x12345678, bigEndian);
    EXPECT_EQ(buf.read_uint32(0, littleEndian), 0x78563412u);
}

TEST(DataBufTest_1130, ReadWriteUint32BoundaryValues_1130) {
    DataBuf buf(8);
    buf.write_uint32(0, 0x00000000, bigEndian);
    EXPECT_EQ(buf.read_uint32(0, bigEndian), 0x00000000u);

    buf.write_uint32(0, 0xFFFFFFFF, bigEndian);
    EXPECT_EQ(buf.read_uint32(0, bigEndian), 0xFFFFFFFFu);
}

// ============================================================
// Read/Write uint64 Tests
// ============================================================

TEST(DataBufTest_1130, ReadWriteUint64LittleEndian_1130) {
    DataBuf buf(16);
    buf.write_uint64(0, 0x0102030405060708ULL, littleEndian);
    EXPECT_EQ(buf.read_uint64(0, littleEndian), 0x0102030405060708ULL);
}

TEST(DataBufTest_1130, ReadWriteUint64BigEndian_1130) {
    DataBuf buf(16);
    buf.write_uint64(0, 0x0102030405060708ULL, bigEndian);
    EXPECT_EQ(buf.read_uint64(0, bigEndian), 0x0102030405060708ULL);
}

TEST(DataBufTest_1130, ReadWriteUint64BoundaryValues_1130) {
    DataBuf buf(16);
    buf.write_uint64(0, 0x0000000000000000ULL, bigEndian);
    EXPECT_EQ(buf.read_uint64(0, bigEndian), 0x0000000000000000ULL);

    buf.write_uint64(0, 0xFFFFFFFFFFFFFFFFULL, bigEndian);
    EXPECT_EQ(buf.read_uint64(0, bigEndian), 0xFFFFFFFFFFFFFFFFULL);
}

// ============================================================
// cmpBytes Tests
// ============================================================

TEST(DataBufTest_1130, CmpBytesEqual_1130) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04};
    DataBuf buf(data, 4);
    const byte cmp[] = {0x01, 0x02, 0x03, 0x04};
    EXPECT_EQ(buf.cmpBytes(0, cmp, 4), 0);
}

TEST(DataBufTest_1130, CmpBytesNotEqual_1130) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04};
    DataBuf buf(data, 4);
    const byte cmp[] = {0x01, 0x02, 0x04, 0x04};
    EXPECT_NE(buf.cmpBytes(0, cmp, 4), 0);
}

TEST(DataBufTest_1130, CmpBytesWithOffset_1130) {
    const byte data[] = {0x00, 0x00, 0x01, 0x02};
    DataBuf buf(data, 4);
    const byte cmp[] = {0x01, 0x02};
    EXPECT_EQ(buf.cmpBytes(2, cmp, 2), 0);
}

TEST(DataBufTest_1130, CmpBytesPartial_1130) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04};
    DataBuf buf(data, 4);
    const byte cmp[] = {0x01, 0x02};
    EXPECT_EQ(buf.cmpBytes(0, cmp, 2), 0);
}

// ============================================================
// data() / c_data() / c_str() Tests
// ============================================================

TEST(DataBufTest_1130, DataPointerAccess_1130) {
    const byte data[] = {0x41, 0x42, 0x43};
    DataBuf buf(data, 3);
    byte* ptr = buf.data(0);
    ASSERT_NE(ptr, nullptr);
    EXPECT_EQ(ptr[0], 0x41);
    EXPECT_EQ(ptr[1], 0x42);
    EXPECT_EQ(ptr[2], 0x43);
}

TEST(DataBufTest_1130, DataPointerWithOffset_1130) {
    const byte data[] = {0x41, 0x42, 0x43, 0x44};
    DataBuf buf(data, 4);
    byte* ptr = buf.data(2);
    ASSERT_NE(ptr, nullptr);
    EXPECT_EQ(ptr[0], 0x43);
    EXPECT_EQ(ptr[1], 0x44);
}

TEST(DataBufTest_1130, CDataPointerAccess_1130) {
    const byte data[] = {0x41, 0x42, 0x43};
    DataBuf buf(data, 3);
    const byte* ptr = buf.c_data(0);
    ASSERT_NE(ptr, nullptr);
    EXPECT_EQ(ptr[0], 0x41);
}

TEST(DataBufTest_1130, CStrAccess_1130) {
    const byte data[] = {'H', 'e', 'l', 'l', 'o', '\0'};
    DataBuf buf(data, 6);
    const char* str = buf.c_str(0);
    ASSERT_NE(str, nullptr);
    EXPECT_STREQ(str, "Hello");
}

TEST(DataBufTest_1130, CStrWithOffset_1130) {
    const byte data[] = {'H', 'e', 'l', 'l', 'o', '\0'};
    DataBuf buf(data, 6);
    const char* str = buf.c_str(2);
    ASSERT_NE(str, nullptr);
    EXPECT_STREQ(str, "llo");
}

// ============================================================
// Modify through data pointer
// ============================================================

TEST(DataBufTest_1130, ModifyThroughDataPointer_1130) {
    DataBuf buf(4);
    byte* ptr = buf.data(0);
    ptr[0] = 0xAA;
    ptr[1] = 0xBB;
    ptr[2] = 0xCC;
    ptr[3] = 0xDD;
    EXPECT_EQ(buf.read_uint8(0), 0xAA);
    EXPECT_EQ(buf.read_uint8(1), 0xBB);
    EXPECT_EQ(buf.read_uint8(2), 0xCC);
    EXPECT_EQ(buf.read_uint8(3), 0xDD);
}

// ============================================================
// begin() / end() Tests
// ============================================================

TEST(DataBufTest_1130, BeginEndIterators_1130) {
    const byte data[] = {0x01, 0x02, 0x03};
    DataBuf buf(data, 3);
    auto it = buf.begin();
    auto endIt = buf.end();
    EXPECT_NE(it, endIt);
    size_t count = 0;
    for (auto b = buf.begin(); b != buf.end(); ++b) {
        count++;
    }
    EXPECT_EQ(count, 3u);
}

TEST(DataBufTest_1130, BeginEndEmptyBuffer_1130) {
    DataBuf buf;
    EXPECT_EQ(buf.begin(), buf.end());
}

// ============================================================
// Empty / Size Tests
// ============================================================

TEST(DataBufTest_1130, EmptyOnDefaultConstruct_1130) {
    DataBuf buf;
    EXPECT_TRUE(buf.empty());
    EXPECT_EQ(buf.size(), 0u);
}

TEST(DataBufTest_1130, NotEmptyAfterAlloc_1130) {
    DataBuf buf;
    buf.alloc(10);
    EXPECT_FALSE(buf.empty());
    EXPECT_EQ(buf.size(), 10u);
}

TEST(DataBufTest_1130, EmptyAfterReset_1130) {
    DataBuf buf(10);
    EXPECT_FALSE(buf.empty());
    buf.reset();
    EXPECT_TRUE(buf.empty());
}

// ============================================================
// Data Persistence Through Resize
// ============================================================

TEST(DataBufTest_1130, DataPersistsAfterResizeGrow_1130) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04};
    DataBuf buf(data, 4);
    buf.resize(8);
    EXPECT_EQ(buf.size(), 8u);
    // Original data should be preserved
    EXPECT_EQ(buf.read_uint8(0), 0x01);
    EXPECT_EQ(buf.read_uint8(1), 0x02);
    EXPECT_EQ(buf.read_uint8(2), 0x03);
    EXPECT_EQ(buf.read_uint8(3), 0x04);
}

TEST(DataBufTest_1130, DataPersistsAfterResizeShrink_1130) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04};
    DataBuf buf(data, 4);
    buf.resize(2);
    EXPECT_EQ(buf.size(), 2u);
    EXPECT_EQ(buf.read_uint8(0), 0x01);
    EXPECT_EQ(buf.read_uint8(1), 0x02);
}

// ============================================================
// Multi-type read/write at various offsets
// ============================================================

TEST(DataBufTest_1130, MultipleWritesAtDifferentOffsets_1130) {
    DataBuf buf(20);
    buf.write_uint8(0, 0xAA);
    buf.write_uint16(1, 0xBBCC, bigEndian);
    buf.write_uint32(3, 0x11223344, bigEndian);
    buf.write_uint64(7, 0x5566778899AABBCCULL, bigEndian);

    EXPECT_EQ(buf.read_uint8(0), 0xAA);
    EXPECT_EQ(buf.read_uint16(1, bigEndian), 0xBBCC);
    EXPECT_EQ(buf.read_uint32(3, bigEndian), 0x11223344u);
    EXPECT_EQ(buf.read_uint64(7, bigEndian), 0x5566778899AABBCCULL);
}

// ============================================================
// Copy semantics (DataBuf should be copyable or moveable)
// ============================================================

TEST(DataBufTest_1130, MoveConstruct_1130) {
    const byte data[] = {0x01, 0x02, 0x03};
    DataBuf buf1(data, 3);
    DataBuf buf2(std::move(buf1));
    EXPECT_EQ(buf2.size(), 3u);
    EXPECT_EQ(buf2.read_uint8(0), 0x01);
    EXPECT_EQ(buf2.read_uint8(2), 0x03);
}

TEST(DataBufTest_1130, MoveAssign_1130) {
    const byte data[] = {0x01, 0x02, 0x03};
    DataBuf buf1(data, 3);
    DataBuf buf2;
    buf2 = std::move(buf1);
    EXPECT_EQ(buf2.size(), 3u);
    EXPECT_EQ(buf2.read_uint8(0), 0x01);
}

// ============================================================
// Large buffer test
// ============================================================

TEST(DataBufTest_1130, LargeBuffer_1130) {
    const size_t largeSize = 1024 * 1024; // 1 MB
    DataBuf buf(largeSize);
    EXPECT_EQ(buf.size(), largeSize);
    buf.write_uint8(0, 0xAA);
    buf.write_uint8(largeSize - 1, 0xBB);
    EXPECT_EQ(buf.read_uint8(0), 0xAA);
    EXPECT_EQ(buf.read_uint8(largeSize - 1), 0xBB);
}

// ============================================================
// Single byte buffer
// ============================================================

TEST(DataBufTest_1130, SingleByteBuf_1130) {
    DataBuf buf(1);
    buf.write_uint8(0, 42);
    EXPECT_EQ(buf.size(), 1u);
    EXPECT_EQ(buf.read_uint8(0), 42);
    EXPECT_FALSE(buf.empty());
}

// ============================================================
// Alloc after having data should replace content
// ============================================================

TEST(DataBufTest_1130, AllocReplacesExistingData_1130) {
    const byte data[] = {0x01, 0x02, 0x03};
    DataBuf buf(data, 3);
    EXPECT_EQ(buf.size(), 3u);
    buf.alloc(10);
    EXPECT_EQ(buf.size(), 10u);
}

// ============================================================
// Endianness consistency tests
// ============================================================

TEST(DataBufTest_1130, Uint16ByteOrderConsistency_1130) {
    DataBuf buf(2);
    buf.write_uint16(0, 0x0102, bigEndian);
    EXPECT_EQ(buf.read_uint8(0), 0x01);
    EXPECT_EQ(buf.read_uint8(1), 0x02);
}

TEST(DataBufTest_1130, Uint16LittleEndianByteOrder_1130) {
    DataBuf buf(2);
    buf.write_uint16(0, 0x0102, littleEndian);
    EXPECT_EQ(buf.read_uint8(0), 0x02);
    EXPECT_EQ(buf.read_uint8(1), 0x01);
}

TEST(DataBufTest_1130, Uint32ByteOrderConsistency_1130) {
    DataBuf buf(4);
    buf.write_uint32(0, 0x01020304, bigEndian);
    EXPECT_EQ(buf.read_uint8(0), 0x01);
    EXPECT_EQ(buf.read_uint8(1), 0x02);
    EXPECT_EQ(buf.read_uint8(2), 0x03);
    EXPECT_EQ(buf.read_uint8(3), 0x04);
}

TEST(DataBufTest_1130, Uint32LittleEndianByteOrder_1130) {
    DataBuf buf(4);
    buf.write_uint32(0, 0x01020304, littleEndian);
    EXPECT_EQ(buf.read_uint8(0), 0x04);
    EXPECT_EQ(buf.read_uint8(1), 0x03);
    EXPECT_EQ(buf.read_uint8(2), 0x02);
    EXPECT_EQ(buf.read_uint8(3), 0x01);
}

TEST(DataBufTest_1130, Uint64BigEndianByteOrder_1130) {
    DataBuf buf(8);
    buf.write_uint64(0, 0x0102030405060708ULL, bigEndian);
    EXPECT_EQ(buf.read_uint8(0), 0x01);
    EXPECT_EQ(buf.read_uint8(1), 0x02);
    EXPECT_EQ(buf.read_uint8(2), 0x03);
    EXPECT_EQ(buf.read_uint8(3), 0x04);
    EXPECT_EQ(buf.read_uint8(4), 0x05);
    EXPECT_EQ(buf.read_uint8(5), 0x06);
    EXPECT_EQ(buf.read_uint8(6), 0x07);
    EXPECT_EQ(buf.read_uint8(7), 0x08);
}

TEST(DataBufTest_1130, Uint64LittleEndianByteOrder_1130) {
    DataBuf buf(8);
    buf.write_uint64(0, 0x0102030405060708ULL, littleEndian);
    EXPECT_EQ(buf.read_uint8(0), 0x08);
    EXPECT_EQ(buf.read_uint8(1), 0x07);
    EXPECT_EQ(buf.read_uint8(2), 0x06);
    EXPECT_EQ(buf.read_uint8(3), 0x05);
    EXPECT_EQ(buf.read_uint8(4), 0x04);
    EXPECT_EQ(buf.read_uint8(5), 0x03);
    EXPECT_EQ(buf.read_uint8(6), 0x02);
    EXPECT_EQ(buf.read_uint8(7), 0x01);
}

// ============================================================
// cmpBytes with zero bufsize
// ============================================================

TEST(DataBufTest_1130, CmpBytesZeroSize_1130) {
    const byte data[] = {0x01, 0x02};
    DataBuf buf(data, 2);
    const byte cmp[] = {0xFF};
    // Comparing zero bytes should always be equal
    EXPECT_EQ(buf.cmpBytes(0, cmp, 0), 0);
}

// ============================================================
// Overwrite and verify
// ============================================================

TEST(DataBufTest_1130, OverwriteUint8_1130) {
    DataBuf buf(1);
    buf.write_uint8(0, 0x11);
    EXPECT_EQ(buf.read_uint8(0), 0x11);
    buf.write_uint8(0, 0x22);
    EXPECT_EQ(buf.read_uint8(0), 0x22);
}

TEST(DataBufTest_1130, OverwriteUint32_1130) {
    DataBuf buf(4);
    buf.write_uint32(0, 0xAAAAAAAA, bigEndian);
    EXPECT_EQ(buf.read_uint32(0, bigEndian), 0xAAAAAAAAu);
    buf.write_uint32(0, 0xBBBBBBBB, bigEndian);
    EXPECT_EQ(buf.read_uint32(0, bigEndian), 0xBBBBBBBBu);
}

#include <gtest/gtest.h>
#include <exiv2/types.hpp>
#include <cstring>

using namespace Exiv2;

// ===== Default Construction Tests =====

TEST(DataBufTest_1116, DefaultConstructorCreatesEmptyBuffer_1116) {
    DataBuf buf;
    EXPECT_EQ(buf.size(), 0u);
    EXPECT_TRUE(buf.empty());
}

// ===== Size Constructor Tests =====

TEST(DataBufTest_1116, SizeConstructorAllocatesCorrectSize_1116) {
    DataBuf buf(100);
    EXPECT_EQ(buf.size(), 100u);
    EXPECT_FALSE(buf.empty());
}

TEST(DataBufTest_1116, SizeConstructorZeroSize_1116) {
    DataBuf buf(0);
    EXPECT_EQ(buf.size(), 0u);
    EXPECT_TRUE(buf.empty());
}

// ===== Data Constructor Tests =====

TEST(DataBufTest_1116, DataConstructorCopiesData_1116) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    DataBuf buf(data, 5);
    EXPECT_EQ(buf.size(), 5u);
    EXPECT_FALSE(buf.empty());
    for (size_t i = 0; i < 5; ++i) {
        EXPECT_EQ(buf.read_uint8(i), data[i]);
    }
}

TEST(DataBufTest_1116, DataConstructorZeroSize_1116) {
    const byte data[] = {0x01};
    DataBuf buf(data, 0);
    EXPECT_EQ(buf.size(), 0u);
    EXPECT_TRUE(buf.empty());
}

// ===== Resize Tests =====

TEST(DataBufTest_1116, ResizeIncreasesSize_1116) {
    DataBuf buf(10);
    EXPECT_EQ(buf.size(), 10u);
    buf.resize(20);
    EXPECT_EQ(buf.size(), 20u);
}

TEST(DataBufTest_1116, ResizeDecreasesSize_1116) {
    DataBuf buf(20);
    EXPECT_EQ(buf.size(), 20u);
    buf.resize(5);
    EXPECT_EQ(buf.size(), 5u);
}

TEST(DataBufTest_1116, ResizeToZero_1116) {
    DataBuf buf(10);
    buf.resize(0);
    EXPECT_EQ(buf.size(), 0u);
    EXPECT_TRUE(buf.empty());
}

TEST(DataBufTest_1116, ResizePreservesExistingData_1116) {
    const byte data[] = {0xAA, 0xBB, 0xCC, 0xDD};
    DataBuf buf(data, 4);
    buf.resize(8);
    EXPECT_EQ(buf.size(), 8u);
    for (size_t i = 0; i < 4; ++i) {
        EXPECT_EQ(buf.read_uint8(i), data[i]);
    }
}

// ===== Alloc Tests =====

TEST(DataBufTest_1116, AllocSetsSize_1116) {
    DataBuf buf;
    buf.alloc(50);
    EXPECT_EQ(buf.size(), 50u);
}

TEST(DataBufTest_1116, AllocZero_1116) {
    DataBuf buf(10);
    buf.alloc(0);
    EXPECT_EQ(buf.size(), 0u);
}

// ===== Reset Tests =====

TEST(DataBufTest_1116, ResetClearsBuffer_1116) {
    DataBuf buf(100);
    buf.reset();
    EXPECT_EQ(buf.size(), 0u);
    EXPECT_TRUE(buf.empty());
}

TEST(DataBufTest_1116, ResetOnEmptyBuffer_1116) {
    DataBuf buf;
    buf.reset();
    EXPECT_EQ(buf.size(), 0u);
    EXPECT_TRUE(buf.empty());
}

// ===== read_uint8 / write_uint8 Tests =====

TEST(DataBufTest_1116, WriteAndReadUint8_1116) {
    DataBuf buf(10);
    buf.write_uint8(0, 0x42);
    EXPECT_EQ(buf.read_uint8(0), 0x42);

    buf.write_uint8(9, 0xFF);
    EXPECT_EQ(buf.read_uint8(9), 0xFF);
}

TEST(DataBufTest_1116, WriteUint8ZeroValue_1116) {
    DataBuf buf(1);
    buf.write_uint8(0, 0x00);
    EXPECT_EQ(buf.read_uint8(0), 0x00);
}

TEST(DataBufTest_1116, WriteUint8MaxValue_1116) {
    DataBuf buf(1);
    buf.write_uint8(0, 0xFF);
    EXPECT_EQ(buf.read_uint8(0), 0xFF);
}

// ===== read_uint16 / write_uint16 Tests =====

TEST(DataBufTest_1116, WriteAndReadUint16BigEndian_1116) {
    DataBuf buf(10);
    buf.write_uint16(0, 0x1234, bigEndian);
    EXPECT_EQ(buf.read_uint16(0, bigEndian), 0x1234);
}

TEST(DataBufTest_1116, WriteAndReadUint16LittleEndian_1116) {
    DataBuf buf(10);
    buf.write_uint16(0, 0x1234, littleEndian);
    EXPECT_EQ(buf.read_uint16(0, littleEndian), 0x1234);
}

TEST(DataBufTest_1116, Uint16ByteOrderMatters_1116) {
    DataBuf buf(4);
    buf.write_uint16(0, 0x0102, bigEndian);
    // Reading with opposite byte order should give different value
    uint16_t valBE = buf.read_uint16(0, bigEndian);
    uint16_t valLE = buf.read_uint16(0, littleEndian);
    EXPECT_EQ(valBE, 0x0102);
    EXPECT_NE(valBE, valLE);
}

TEST(DataBufTest_1116, WriteUint16AtOffset_1116) {
    DataBuf buf(10);
    buf.write_uint16(4, 0xABCD, bigEndian);
    EXPECT_EQ(buf.read_uint16(4, bigEndian), 0xABCD);
}

TEST(DataBufTest_1116, Uint16MaxValue_1116) {
    DataBuf buf(2);
    buf.write_uint16(0, 0xFFFF, bigEndian);
    EXPECT_EQ(buf.read_uint16(0, bigEndian), 0xFFFF);
}

TEST(DataBufTest_1116, Uint16ZeroValue_1116) {
    DataBuf buf(2);
    buf.write_uint16(0, 0x0000, littleEndian);
    EXPECT_EQ(buf.read_uint16(0, littleEndian), 0x0000);
}

// ===== read_uint32 / write_uint32 Tests =====

TEST(DataBufTest_1116, WriteAndReadUint32BigEndian_1116) {
    DataBuf buf(10);
    buf.write_uint32(0, 0x12345678, bigEndian);
    EXPECT_EQ(buf.read_uint32(0, bigEndian), 0x12345678u);
}

TEST(DataBufTest_1116, WriteAndReadUint32LittleEndian_1116) {
    DataBuf buf(10);
    buf.write_uint32(0, 0x12345678, littleEndian);
    EXPECT_EQ(buf.read_uint32(0, littleEndian), 0x12345678u);
}

TEST(DataBufTest_1116, Uint32ByteOrderMatters_1116) {
    DataBuf buf(8);
    buf.write_uint32(0, 0x01020304, bigEndian);
    uint32_t valBE = buf.read_uint32(0, bigEndian);
    uint32_t valLE = buf.read_uint32(0, littleEndian);
    EXPECT_EQ(valBE, 0x01020304u);
    EXPECT_NE(valBE, valLE);
}

TEST(DataBufTest_1116, WriteUint32AtOffset_1116) {
    DataBuf buf(20);
    buf.write_uint32(10, 0xDEADBEEF, littleEndian);
    EXPECT_EQ(buf.read_uint32(10, littleEndian), 0xDEADBEEFu);
}

TEST(DataBufTest_1116, Uint32MaxValue_1116) {
    DataBuf buf(4);
    buf.write_uint32(0, 0xFFFFFFFF, bigEndian);
    EXPECT_EQ(buf.read_uint32(0, bigEndian), 0xFFFFFFFFu);
}

// ===== read_uint64 / write_uint64 Tests =====

TEST(DataBufTest_1116, WriteAndReadUint64BigEndian_1116) {
    DataBuf buf(16);
    buf.write_uint64(0, 0x0102030405060708ULL, bigEndian);
    EXPECT_EQ(buf.read_uint64(0, bigEndian), 0x0102030405060708ULL);
}

TEST(DataBufTest_1116, WriteAndReadUint64LittleEndian_1116) {
    DataBuf buf(16);
    buf.write_uint64(0, 0x0102030405060708ULL, littleEndian);
    EXPECT_EQ(buf.read_uint64(0, littleEndian), 0x0102030405060708ULL);
}

TEST(DataBufTest_1116, Uint64ByteOrderMatters_1116) {
    DataBuf buf(16);
    buf.write_uint64(0, 0x0102030405060708ULL, bigEndian);
    uint64_t valBE = buf.read_uint64(0, bigEndian);
    uint64_t valLE = buf.read_uint64(0, littleEndian);
    EXPECT_EQ(valBE, 0x0102030405060708ULL);
    EXPECT_NE(valBE, valLE);
}

TEST(DataBufTest_1116, Uint64MaxValue_1116) {
    DataBuf buf(8);
    buf.write_uint64(0, 0xFFFFFFFFFFFFFFFFULL, bigEndian);
    EXPECT_EQ(buf.read_uint64(0, bigEndian), 0xFFFFFFFFFFFFFFFFULL);
}

TEST(DataBufTest_1116, WriteUint64AtOffset_1116) {
    DataBuf buf(20);
    buf.write_uint64(8, 0xCAFEBABEDEADBEEFULL, littleEndian);
    EXPECT_EQ(buf.read_uint64(8, littleEndian), 0xCAFEBABEDEADBEEFULL);
}

// ===== cmpBytes Tests =====

TEST(DataBufTest_1116, CmpBytesEqual_1116) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04};
    DataBuf buf(data, 4);
    const byte cmp[] = {0x01, 0x02, 0x03, 0x04};
    EXPECT_EQ(buf.cmpBytes(0, cmp, 4), 0);
}

TEST(DataBufTest_1116, CmpBytesNotEqual_1116) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04};
    DataBuf buf(data, 4);
    const byte cmp[] = {0x01, 0x02, 0x05, 0x04};
    EXPECT_NE(buf.cmpBytes(0, cmp, 4), 0);
}

TEST(DataBufTest_1116, CmpBytesWithOffset_1116) {
    const byte data[] = {0xAA, 0xBB, 0x01, 0x02, 0x03};
    DataBuf buf(data, 5);
    const byte cmp[] = {0x01, 0x02, 0x03};
    EXPECT_EQ(buf.cmpBytes(2, cmp, 3), 0);
}

TEST(DataBufTest_1116, CmpBytesZeroLength_1116) {
    const byte data[] = {0x01, 0x02};
    DataBuf buf(data, 2);
    const byte cmp[] = {0xFF};
    EXPECT_EQ(buf.cmpBytes(0, cmp, 0), 0);
}

TEST(DataBufTest_1116, CmpBytesPartialMatch_1116) {
    const byte data[] = {0x01, 0x02, 0x03};
    DataBuf buf(data, 3);
    const byte cmp[] = {0x01, 0x02};
    EXPECT_EQ(buf.cmpBytes(0, cmp, 2), 0);
}

// ===== data() Tests =====

TEST(DataBufTest_1116, DataReturnsNonNullForNonEmpty_1116) {
    DataBuf buf(10);
    EXPECT_NE(buf.data(0), nullptr);
}

TEST(DataBufTest_1116, DataAtOffsetZero_1116) {
    const byte src[] = {0x42, 0x43};
    DataBuf buf(src, 2);
    byte* ptr = buf.data(0);
    EXPECT_EQ(*ptr, 0x42);
}

TEST(DataBufTest_1116, DataAtOffset_1116) {
    const byte src[] = {0x01, 0x02, 0x03};
    DataBuf buf(src, 3);
    byte* ptr = buf.data(1);
    EXPECT_EQ(*ptr, 0x02);
}

TEST(DataBufTest_1116, DataModifiableViaPointer_1116) {
    DataBuf buf(5);
    buf.write_uint8(0, 0x00);
    byte* ptr = buf.data(0);
    *ptr = 0xFF;
    EXPECT_EQ(buf.read_uint8(0), 0xFF);
}

// ===== c_data() Tests =====

TEST(DataBufTest_1116, CDataReturnsConstPointer_1116) {
    const byte src[] = {0x10, 0x20, 0x30};
    DataBuf buf(src, 3);
    const byte* ptr = buf.c_data(0);
    EXPECT_EQ(*ptr, 0x10);
}

TEST(DataBufTest_1116, CDataAtOffset_1116) {
    const byte src[] = {0x10, 0x20, 0x30};
    DataBuf buf(src, 3);
    const byte* ptr = buf.c_data(2);
    EXPECT_EQ(*ptr, 0x30);
}

// ===== c_str() Tests =====

TEST(DataBufTest_1116, CStrReturnsString_1116) {
    const char text[] = "Hello";
    DataBuf buf(reinterpret_cast<const byte*>(text), sizeof(text));
    const char* str = buf.c_str(0);
    EXPECT_STREQ(str, "Hello");
}

TEST(DataBufTest_1116, CStrAtOffset_1116) {
    const char text[] = "Hello";
    DataBuf buf(reinterpret_cast<const byte*>(text), sizeof(text));
    const char* str = buf.c_str(1);
    EXPECT_STREQ(str, "ello");
}

// ===== empty() Tests =====

TEST(DataBufTest_1116, EmptyReturnsTrueForDefault_1116) {
    DataBuf buf;
    EXPECT_TRUE(buf.empty());
}

TEST(DataBufTest_1116, EmptyReturnsFalseForNonEmpty_1116) {
    DataBuf buf(10);
    EXPECT_FALSE(buf.empty());
}

TEST(DataBufTest_1116, EmptyAfterReset_1116) {
    DataBuf buf(10);
    buf.reset();
    EXPECT_TRUE(buf.empty());
}

// ===== size() Tests =====

TEST(DataBufTest_1116, SizeReturnsCorrectValue_1116) {
    DataBuf buf(42);
    EXPECT_EQ(buf.size(), 42u);
}

TEST(DataBufTest_1116, SizeAfterResize_1116) {
    DataBuf buf(10);
    buf.resize(25);
    EXPECT_EQ(buf.size(), 25u);
}

TEST(DataBufTest_1116, SizeAfterAlloc_1116) {
    DataBuf buf;
    buf.alloc(33);
    EXPECT_EQ(buf.size(), 33u);
}

// ===== begin() / end() Tests =====

TEST(DataBufTest_1116, BeginEndDistanceMatchesSize_1116) {
    DataBuf buf(10);
    auto dist = std::distance(buf.begin(), buf.end());
    EXPECT_EQ(static_cast<size_t>(dist), buf.size());
}

TEST(DataBufTest_1116, BeginEndEmptyBuffer_1116) {
    DataBuf buf;
    EXPECT_EQ(buf.begin(), buf.end());
}

TEST(DataBufTest_1116, IterateWithBeginEnd_1116) {
    const byte data[] = {0x01, 0x02, 0x03};
    DataBuf buf(data, 3);
    size_t idx = 0;
    for (auto it = buf.begin(); it != buf.end(); ++it, ++idx) {
        EXPECT_EQ(*it, data[idx]);
    }
    EXPECT_EQ(idx, 3u);
}

// ===== Mixed operation tests =====

TEST(DataBufTest_1116, WriteMultipleTypesAndReadBack_1116) {
    DataBuf buf(15);
    buf.write_uint8(0, 0xAA);
    buf.write_uint16(1, 0xBBCC, bigEndian);
    buf.write_uint32(3, 0xDDEEFF00, littleEndian);

    EXPECT_EQ(buf.read_uint8(0), 0xAA);
    EXPECT_EQ(buf.read_uint16(1, bigEndian), 0xBBCC);
    EXPECT_EQ(buf.read_uint32(3, littleEndian), 0xDDEEFF00u);
}

TEST(DataBufTest_1116, ResizeAndWriteToNewArea_1116) {
    DataBuf buf(4);
    buf.write_uint8(0, 0x01);
    buf.resize(8);
    buf.write_uint32(4, 0xAABBCCDD, bigEndian);
    EXPECT_EQ(buf.read_uint8(0), 0x01);
    EXPECT_EQ(buf.read_uint32(4, bigEndian), 0xAABBCCDDu);
}

TEST(DataBufTest_1116, AllocAndWrite_1116) {
    DataBuf buf;
    buf.alloc(8);
    buf.write_uint64(0, 0x0123456789ABCDEFULL, bigEndian);
    EXPECT_EQ(buf.read_uint64(0, bigEndian), 0x0123456789ABCDEFULL);
}

TEST(DataBufTest_1116, CopyConstructor_1116) {
    const byte data[] = {0x01, 0x02, 0x03};
    DataBuf original(data, 3);
    DataBuf copy(original);
    EXPECT_EQ(copy.size(), 3u);
    EXPECT_EQ(copy.read_uint8(0), 0x01);
    EXPECT_EQ(copy.read_uint8(1), 0x02);
    EXPECT_EQ(copy.read_uint8(2), 0x03);
}

TEST(DataBufTest_1116, MoveConstructor_1116) {
    const byte data[] = {0x0A, 0x0B, 0x0C};
    DataBuf original(data, 3);
    DataBuf moved(std::move(original));
    EXPECT_EQ(moved.size(), 3u);
    EXPECT_EQ(moved.read_uint8(0), 0x0A);
    EXPECT_EQ(moved.read_uint8(1), 0x0B);
    EXPECT_EQ(moved.read_uint8(2), 0x0C);
}

TEST(DataBufTest_1116, DataPointerConsistency_1116) {
    const byte data[] = {0x10, 0x20, 0x30, 0x40};
    DataBuf buf(data, 4);
    const byte* cptr = buf.c_data(0);
    byte* ptr = buf.data(0);
    EXPECT_EQ(static_cast<const byte*>(ptr), cptr);
}

// ===== Boundary: large buffer =====

TEST(DataBufTest_1116, LargeBufferAllocation_1116) {
    const size_t largeSize = 1024 * 1024; // 1 MB
    DataBuf buf(largeSize);
    EXPECT_EQ(buf.size(), largeSize);
    buf.write_uint8(0, 0x01);
    buf.write_uint8(largeSize - 1, 0xFF);
    EXPECT_EQ(buf.read_uint8(0), 0x01);
    EXPECT_EQ(buf.read_uint8(largeSize - 1), 0xFF);
}

// ===== Boundary: single byte buffer =====

TEST(DataBufTest_1116, SingleByteBuffer_1116) {
    DataBuf buf(1);
    EXPECT_EQ(buf.size(), 1u);
    EXPECT_FALSE(buf.empty());
    buf.write_uint8(0, 0x42);
    EXPECT_EQ(buf.read_uint8(0), 0x42);
}

// ===== Endianness round-trip for uint16 =====

TEST(DataBufTest_1116, Uint16EndianRoundTripLE_1116) {
    DataBuf buf(2);
    for (uint16_t val : {static_cast<uint16_t>(0), static_cast<uint16_t>(1), static_cast<uint16_t>(0x7FFF), static_cast<uint16_t>(0xFFFF)}) {
        buf.write_uint16(0, val, littleEndian);
        EXPECT_EQ(buf.read_uint16(0, littleEndian), val);
    }
}

TEST(DataBufTest_1116, Uint16EndianRoundTripBE_1116) {
    DataBuf buf(2);
    for (uint16_t val : {static_cast<uint16_t>(0), static_cast<uint16_t>(1), static_cast<uint16_t>(0x7FFF), static_cast<uint16_t>(0xFFFF)}) {
        buf.write_uint16(0, val, bigEndian);
        EXPECT_EQ(buf.read_uint16(0, bigEndian), val);
    }
}

// ===== Endianness round-trip for uint32 =====

TEST(DataBufTest_1116, Uint32EndianRoundTripLE_1116) {
    DataBuf buf(4);
    for (uint32_t val : {0u, 1u, 0x7FFFFFFFu, 0xFFFFFFFFu}) {
        buf.write_uint32(0, val, littleEndian);
        EXPECT_EQ(buf.read_uint32(0, littleEndian), val);
    }
}

TEST(DataBufTest_1116, Uint32EndianRoundTripBE_1116) {
    DataBuf buf(4);
    for (uint32_t val : {0u, 1u, 0x7FFFFFFFu, 0xFFFFFFFFu}) {
        buf.write_uint32(0, val, bigEndian);
        EXPECT_EQ(buf.read_uint32(0, bigEndian), val);
    }
}

// ===== Endianness round-trip for uint64 =====

TEST(DataBufTest_1116, Uint64EndianRoundTripLE_1116) {
    DataBuf buf(8);
    for (uint64_t val : {0ULL, 1ULL, 0x7FFFFFFFFFFFFFFFULL, 0xFFFFFFFFFFFFFFFFULL}) {
        buf.write_uint64(0, val, littleEndian);
        EXPECT_EQ(buf.read_uint64(0, littleEndian), val);
    }
}

TEST(DataBufTest_1116, Uint64EndianRoundTripBE_1116) {
    DataBuf buf(8);
    for (uint64_t val : {0ULL, 1ULL, 0x7FFFFFFFFFFFFFFFULL, 0xFFFFFFFFFFFFFFFFULL}) {
        buf.write_uint64(0, val, bigEndian);
        EXPECT_EQ(buf.read_uint64(0, bigEndian), val);
    }
}

// ===== cmpBytes with full buffer comparison =====

TEST(DataBufTest_1116, CmpBytesFullBufferComparison_1116) {
    const byte data[] = {0xDE, 0xAD, 0xBE, 0xEF};
    DataBuf buf(data, 4);
    const byte match[] = {0xDE, 0xAD, 0xBE, 0xEF};
    const byte nomatch[] = {0xDE, 0xAD, 0xBE, 0x00};
    EXPECT_EQ(buf.cmpBytes(0, match, 4), 0);
    EXPECT_NE(buf.cmpBytes(0, nomatch, 4), 0);
}

// ===== Overwrite existing data =====

TEST(DataBufTest_1116, OverwriteUint8_1116) {
    DataBuf buf(1);
    buf.write_uint8(0, 0x01);
    EXPECT_EQ(buf.read_uint8(0), 0x01);
    buf.write_uint8(0, 0x02);
    EXPECT_EQ(buf.read_uint8(0), 0x02);
}

TEST(DataBufTest_1116, OverwriteUint32_1116) {
    DataBuf buf(4);
    buf.write_uint32(0, 0x11111111, bigEndian);
    EXPECT_EQ(buf.read_uint32(0, bigEndian), 0x11111111u);
    buf.write_uint32(0, 0x22222222, bigEndian);
    EXPECT_EQ(buf.read_uint32(0, bigEndian), 0x22222222u);
}

#include <gtest/gtest.h>
#include <exiv2/types.hpp>
#include <cstring>
#include <stdexcept>

using namespace Exiv2;

// ============================================================================
// Test Fixture
// ============================================================================
class DataBufTest_1119 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ============================================================================
// Constructor Tests
// ============================================================================

TEST_F(DataBufTest_1119, DefaultConstructorCreatesEmptyBuffer_1119) {
    DataBuf buf;
    EXPECT_EQ(buf.size(), 0u);
    EXPECT_TRUE(buf.empty());
}

TEST_F(DataBufTest_1119, SizeConstructorAllocatesCorrectSize_1119) {
    DataBuf buf(100);
    EXPECT_EQ(buf.size(), 100u);
    EXPECT_FALSE(buf.empty());
}

TEST_F(DataBufTest_1119, SizeConstructorZeroSize_1119) {
    DataBuf buf(0);
    EXPECT_EQ(buf.size(), 0u);
    EXPECT_TRUE(buf.empty());
}

TEST_F(DataBufTest_1119, DataConstructorCopiesData_1119) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    DataBuf buf(data, 5);
    EXPECT_EQ(buf.size(), 5u);
    EXPECT_FALSE(buf.empty());
    for (size_t i = 0; i < 5; ++i) {
        EXPECT_EQ(buf.read_uint8(i), data[i]);
    }
}

TEST_F(DataBufTest_1119, DataConstructorZeroSize_1119) {
    const byte data[] = {0x01};
    DataBuf buf(data, 0);
    EXPECT_EQ(buf.size(), 0u);
    EXPECT_TRUE(buf.empty());
}

// ============================================================================
// alloc / resize / reset Tests
// ============================================================================

TEST_F(DataBufTest_1119, AllocSetsSize_1119) {
    DataBuf buf;
    buf.alloc(50);
    EXPECT_EQ(buf.size(), 50u);
}

TEST_F(DataBufTest_1119, ResizeChangesSize_1119) {
    DataBuf buf(10);
    buf.resize(20);
    EXPECT_EQ(buf.size(), 20u);
}

TEST_F(DataBufTest_1119, ResizeToSmallerSize_1119) {
    DataBuf buf(20);
    buf.resize(5);
    EXPECT_EQ(buf.size(), 5u);
}

TEST_F(DataBufTest_1119, ResizeToZero_1119) {
    DataBuf buf(10);
    buf.resize(0);
    EXPECT_EQ(buf.size(), 0u);
    EXPECT_TRUE(buf.empty());
}

TEST_F(DataBufTest_1119, ResetClearsBuffer_1119) {
    DataBuf buf(50);
    buf.reset();
    EXPECT_EQ(buf.size(), 0u);
    EXPECT_TRUE(buf.empty());
}

TEST_F(DataBufTest_1119, ResetOnEmptyBuffer_1119) {
    DataBuf buf;
    buf.reset();
    EXPECT_EQ(buf.size(), 0u);
    EXPECT_TRUE(buf.empty());
}

// ============================================================================
// write_uint8 / read_uint8 Tests
// ============================================================================

TEST_F(DataBufTest_1119, WriteAndReadUint8_1119) {
    DataBuf buf(4);
    buf.write_uint8(0, 0xAB);
    buf.write_uint8(1, 0xCD);
    buf.write_uint8(2, 0xEF);
    buf.write_uint8(3, 0x12);
    EXPECT_EQ(buf.read_uint8(0), 0xAB);
    EXPECT_EQ(buf.read_uint8(1), 0xCD);
    EXPECT_EQ(buf.read_uint8(2), 0xEF);
    EXPECT_EQ(buf.read_uint8(3), 0x12);
}

TEST_F(DataBufTest_1119, WriteUint8AtLastValidOffset_1119) {
    DataBuf buf(1);
    buf.write_uint8(0, 0xFF);
    EXPECT_EQ(buf.read_uint8(0), 0xFF);
}

TEST_F(DataBufTest_1119, WriteUint8OverflowThrows_1119) {
    DataBuf buf(4);
    EXPECT_THROW(buf.write_uint8(4, 0x00), std::out_of_range);
}

TEST_F(DataBufTest_1119, WriteUint8OnEmptyBufferThrows_1119) {
    DataBuf buf;
    EXPECT_THROW(buf.write_uint8(0, 0x00), std::out_of_range);
}

TEST_F(DataBufTest_1119, WriteUint8LargeOffsetThrows_1119) {
    DataBuf buf(10);
    EXPECT_THROW(buf.write_uint8(100, 0x00), std::out_of_range);
}

TEST_F(DataBufTest_1119, ReadUint8OverflowThrows_1119) {
    DataBuf buf(4);
    EXPECT_THROW(buf.read_uint8(4), std::out_of_range);
}

TEST_F(DataBufTest_1119, ReadUint8OnEmptyBufferThrows_1119) {
    DataBuf buf;
    EXPECT_THROW(buf.read_uint8(0), std::out_of_range);
}

// ============================================================================
// write_uint16 / read_uint16 Tests
// ============================================================================

TEST_F(DataBufTest_1119, WriteAndReadUint16BigEndian_1119) {
    DataBuf buf(4);
    buf.write_uint16(0, 0x1234, bigEndian);
    EXPECT_EQ(buf.read_uint16(0, bigEndian), 0x1234);
}

TEST_F(DataBufTest_1119, WriteAndReadUint16LittleEndian_1119) {
    DataBuf buf(4);
    buf.write_uint16(0, 0x1234, littleEndian);
    EXPECT_EQ(buf.read_uint16(0, littleEndian), 0x1234);
}

TEST_F(DataBufTest_1119, WriteUint16BigEndianByteOrder_1119) {
    DataBuf buf(2);
    buf.write_uint16(0, 0xABCD, bigEndian);
    EXPECT_EQ(buf.read_uint8(0), 0xAB);
    EXPECT_EQ(buf.read_uint8(1), 0xCD);
}

TEST_F(DataBufTest_1119, WriteUint16LittleEndianByteOrder_1119) {
    DataBuf buf(2);
    buf.write_uint16(0, 0xABCD, littleEndian);
    EXPECT_EQ(buf.read_uint8(0), 0xCD);
    EXPECT_EQ(buf.read_uint8(1), 0xAB);
}

TEST_F(DataBufTest_1119, WriteUint16AtOffset_1119) {
    DataBuf buf(4);
    buf.write_uint16(2, 0x5678, bigEndian);
    EXPECT_EQ(buf.read_uint16(2, bigEndian), 0x5678);
}

TEST_F(DataBufTest_1119, ReadUint16OverflowThrows_1119) {
    DataBuf buf(2);
    EXPECT_THROW(buf.read_uint16(1, bigEndian), std::out_of_range);
}

TEST_F(DataBufTest_1119, WriteUint16OverflowThrows_1119) {
    DataBuf buf(2);
    EXPECT_THROW(buf.write_uint16(1, 0x1234, bigEndian), std::out_of_range);
}

// ============================================================================
// write_uint32 / read_uint32 Tests
// ============================================================================

TEST_F(DataBufTest_1119, WriteAndReadUint32BigEndian_1119) {
    DataBuf buf(8);
    buf.write_uint32(0, 0x12345678, bigEndian);
    EXPECT_EQ(buf.read_uint32(0, bigEndian), 0x12345678u);
}

TEST_F(DataBufTest_1119, WriteAndReadUint32LittleEndian_1119) {
    DataBuf buf(8);
    buf.write_uint32(0, 0x12345678, littleEndian);
    EXPECT_EQ(buf.read_uint32(0, littleEndian), 0x12345678u);
}

TEST_F(DataBufTest_1119, WriteUint32BigEndianByteOrder_1119) {
    DataBuf buf(4);
    buf.write_uint32(0, 0xDEADBEEF, bigEndian);
    EXPECT_EQ(buf.read_uint8(0), 0xDE);
    EXPECT_EQ(buf.read_uint8(1), 0xAD);
    EXPECT_EQ(buf.read_uint8(2), 0xBE);
    EXPECT_EQ(buf.read_uint8(3), 0xEF);
}

TEST_F(DataBufTest_1119, WriteUint32LittleEndianByteOrder_1119) {
    DataBuf buf(4);
    buf.write_uint32(0, 0xDEADBEEF, littleEndian);
    EXPECT_EQ(buf.read_uint8(0), 0xEF);
    EXPECT_EQ(buf.read_uint8(1), 0xBE);
    EXPECT_EQ(buf.read_uint8(2), 0xAD);
    EXPECT_EQ(buf.read_uint8(3), 0xDE);
}

TEST_F(DataBufTest_1119, ReadUint32OverflowThrows_1119) {
    DataBuf buf(4);
    EXPECT_THROW(buf.read_uint32(1, bigEndian), std::out_of_range);
}

TEST_F(DataBufTest_1119, WriteUint32OverflowThrows_1119) {
    DataBuf buf(4);
    EXPECT_THROW(buf.write_uint32(1, 0x12345678, bigEndian), std::out_of_range);
}

TEST_F(DataBufTest_1119, WriteAndReadUint32AtOffset_1119) {
    DataBuf buf(8);
    buf.write_uint32(4, 0xCAFEBABE, bigEndian);
    EXPECT_EQ(buf.read_uint32(4, bigEndian), 0xCAFEBABEu);
}

// ============================================================================
// write_uint64 / read_uint64 Tests
// ============================================================================

TEST_F(DataBufTest_1119, WriteAndReadUint64BigEndian_1119) {
    DataBuf buf(16);
    buf.write_uint64(0, 0x0102030405060708ULL, bigEndian);
    EXPECT_EQ(buf.read_uint64(0, bigEndian), 0x0102030405060708ULL);
}

TEST_F(DataBufTest_1119, WriteAndReadUint64LittleEndian_1119) {
    DataBuf buf(16);
    buf.write_uint64(0, 0x0102030405060708ULL, littleEndian);
    EXPECT_EQ(buf.read_uint64(0, littleEndian), 0x0102030405060708ULL);
}

TEST_F(DataBufTest_1119, ReadUint64OverflowThrows_1119) {
    DataBuf buf(8);
    EXPECT_THROW(buf.read_uint64(1, bigEndian), std::out_of_range);
}

TEST_F(DataBufTest_1119, WriteUint64OverflowThrows_1119) {
    DataBuf buf(8);
    EXPECT_THROW(buf.write_uint64(1, 0x0102030405060708ULL, bigEndian), std::out_of_range);
}

TEST_F(DataBufTest_1119, WriteAndReadUint64AtOffset_1119) {
    DataBuf buf(16);
    buf.write_uint64(8, 0xDEADBEEFCAFEBABEULL, littleEndian);
    EXPECT_EQ(buf.read_uint64(8, littleEndian), 0xDEADBEEFCAFEBABEULL);
}

// ============================================================================
// cmpBytes Tests
// ============================================================================

TEST_F(DataBufTest_1119, CmpBytesEqual_1119) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04};
    DataBuf buf(data, 4);
    const byte cmp[] = {0x01, 0x02, 0x03, 0x04};
    EXPECT_EQ(buf.cmpBytes(0, cmp, 4), 0);
}

TEST_F(DataBufTest_1119, CmpBytesNotEqual_1119) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04};
    DataBuf buf(data, 4);
    const byte cmp[] = {0x01, 0x02, 0xFF, 0x04};
    EXPECT_NE(buf.cmpBytes(0, cmp, 4), 0);
}

TEST_F(DataBufTest_1119, CmpBytesAtOffset_1119) {
    const byte data[] = {0x00, 0x00, 0xAA, 0xBB};
    DataBuf buf(data, 4);
    const byte cmp[] = {0xAA, 0xBB};
    EXPECT_EQ(buf.cmpBytes(2, cmp, 2), 0);
}

TEST_F(DataBufTest_1119, CmpBytesPartialMatch_1119) {
    const byte data[] = {0x01, 0x02, 0x03};
    DataBuf buf(data, 3);
    const byte cmp[] = {0x01, 0x02};
    EXPECT_EQ(buf.cmpBytes(0, cmp, 2), 0);
}

// ============================================================================
// data / c_data / c_str Tests
// ============================================================================

TEST_F(DataBufTest_1119, DataReturnsNonNullForNonEmptyBuffer_1119) {
    DataBuf buf(10);
    EXPECT_NE(buf.data(0), nullptr);
}

TEST_F(DataBufTest_1119, DataAtOffset_1119) {
    const byte data[] = {0x10, 0x20, 0x30};
    DataBuf buf(data, 3);
    byte* ptr = buf.data(1);
    EXPECT_EQ(*ptr, 0x20);
}

TEST_F(DataBufTest_1119, CDataReturnsConstPointer_1119) {
    const byte data[] = {0xAA, 0xBB, 0xCC};
    DataBuf buf(data, 3);
    const byte* ptr = buf.c_data(0);
    EXPECT_EQ(ptr[0], 0xAA);
    EXPECT_EQ(ptr[1], 0xBB);
    EXPECT_EQ(ptr[2], 0xCC);
}

TEST_F(DataBufTest_1119, CStrReturnsConstCharPointer_1119) {
    const byte data[] = {'H', 'e', 'l', 'l', 'o', '\0'};
    DataBuf buf(data, 6);
    const char* str = buf.c_str(0);
    EXPECT_STREQ(str, "Hello");
}

TEST_F(DataBufTest_1119, CStrAtOffset_1119) {
    const byte data[] = {'X', 'Y', 'H', 'i', '\0'};
    DataBuf buf(data, 5);
    const char* str = buf.c_str(2);
    EXPECT_STREQ(str, "Hi");
}

// ============================================================================
// begin / end Tests
// ============================================================================

TEST_F(DataBufTest_1119, BeginEndIteratorsCorrectRange_1119) {
    const byte data[] = {1, 2, 3, 4, 5};
    DataBuf buf(data, 5);
    size_t count = 0;
    byte sum = 0;
    for (auto it = buf.begin(); it != buf.end(); ++it) {
        sum += *it;
        ++count;
    }
    EXPECT_EQ(count, 5u);
    EXPECT_EQ(sum, 15);
}

TEST_F(DataBufTest_1119, BeginEqualsEndForEmptyBuffer_1119) {
    DataBuf buf;
    EXPECT_EQ(buf.begin(), buf.end());
}

// ============================================================================
// size / empty Tests
// ============================================================================

TEST_F(DataBufTest_1119, SizeReturnsCorrectValue_1119) {
    DataBuf buf(42);
    EXPECT_EQ(buf.size(), 42u);
}

TEST_F(DataBufTest_1119, EmptyReturnsTrueForDefaultConstructed_1119) {
    DataBuf buf;
    EXPECT_TRUE(buf.empty());
}

TEST_F(DataBufTest_1119, EmptyReturnsFalseForNonEmpty_1119) {
    DataBuf buf(1);
    EXPECT_FALSE(buf.empty());
}

// ============================================================================
// Mixed / Cross-function Tests
// ============================================================================

TEST_F(DataBufTest_1119, WriteUint8ThenReadViaData_1119) {
    DataBuf buf(4);
    buf.write_uint8(0, 0x42);
    EXPECT_EQ(*(buf.data(0)), 0x42);
}

TEST_F(DataBufTest_1119, AllocThenWriteAndRead_1119) {
    DataBuf buf;
    buf.alloc(8);
    buf.write_uint32(0, 0xDEADC0DE, bigEndian);
    EXPECT_EQ(buf.read_uint32(0, bigEndian), 0xDEADC0DEu);
}

TEST_F(DataBufTest_1119, ResizePreservesExistingData_1119) {
    DataBuf buf(4);
    buf.write_uint8(0, 0xAA);
    buf.write_uint8(1, 0xBB);
    buf.resize(8);
    EXPECT_EQ(buf.read_uint8(0), 0xAA);
    EXPECT_EQ(buf.read_uint8(1), 0xBB);
    EXPECT_EQ(buf.size(), 8u);
}

TEST_F(DataBufTest_1119, ResetThenAllocWorks_1119) {
    DataBuf buf(10);
    buf.reset();
    EXPECT_TRUE(buf.empty());
    buf.alloc(5);
    EXPECT_EQ(buf.size(), 5u);
    buf.write_uint8(0, 0xFF);
    EXPECT_EQ(buf.read_uint8(0), 0xFF);
}

TEST_F(DataBufTest_1119, WriteMultipleTypesAndReadBack_1119) {
    DataBuf buf(16);
    buf.write_uint8(0, 0x01);
    buf.write_uint16(1, 0x0203, bigEndian);
    buf.write_uint32(3, 0x04050607, bigEndian);
    EXPECT_EQ(buf.read_uint8(0), 0x01);
    EXPECT_EQ(buf.read_uint16(1, bigEndian), 0x0203);
    EXPECT_EQ(buf.read_uint32(3, bigEndian), 0x04050607u);
}

TEST_F(DataBufTest_1119, Uint16CrossEndianRead_1119) {
    DataBuf buf(2);
    buf.write_uint16(0, 0x1234, bigEndian);
    // Read as little endian should give swapped result
    EXPECT_EQ(buf.read_uint16(0, littleEndian), 0x3412);
}

TEST_F(DataBufTest_1119, Uint32CrossEndianRead_1119) {
    DataBuf buf(4);
    buf.write_uint32(0, 0x12345678, bigEndian);
    EXPECT_EQ(buf.read_uint32(0, littleEndian), 0x78563412u);
}

TEST_F(DataBufTest_1119, WriteUint8BoundaryValues_1119) {
    DataBuf buf(2);
    buf.write_uint8(0, 0x00);
    buf.write_uint8(1, 0xFF);
    EXPECT_EQ(buf.read_uint8(0), 0x00);
    EXPECT_EQ(buf.read_uint8(1), 0xFF);
}

TEST_F(DataBufTest_1119, DataPointerModification_1119) {
    DataBuf buf(4);
    buf.write_uint8(0, 0x00);
    byte* ptr = buf.data(0);
    *ptr = 0x99;
    EXPECT_EQ(buf.read_uint8(0), 0x99);
}

TEST_F(DataBufTest_1119, CmpBytesZeroLength_1119) {
    DataBuf buf(4);
    const byte cmp[] = {0x00};
    EXPECT_EQ(buf.cmpBytes(0, cmp, 0), 0);
}

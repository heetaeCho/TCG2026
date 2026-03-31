#include <gtest/gtest.h>
#include <exiv2/types.hpp>
#include <cstring>
#include <stdexcept>

using namespace Exiv2;

// ============================================================
// Tests for makeSlice
// ============================================================

class MakeSliceTest_1131 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(MakeSliceTest_1131, NormalSliceFromDataBuf_1131) {
    DataBuf buf(10);
    for (size_t i = 0; i < 10; ++i) {
        buf.write_uint8(i, static_cast<uint8_t>(i));
    }
    auto slice = makeSlice(buf, 0, 10);
    EXPECT_EQ(slice.size(), 10u);
    for (size_t i = 0; i < 10; ++i) {
        EXPECT_EQ(slice.at(i), static_cast<byte>(i));
    }
}

TEST_F(MakeSliceTest_1131, SliceSubrange_1131) {
    DataBuf buf(10);
    for (size_t i = 0; i < 10; ++i) {
        buf.write_uint8(i, static_cast<uint8_t>(i * 2));
    }
    auto slice = makeSlice(buf, 2, 5);
    EXPECT_EQ(slice.size(), 3u);
    EXPECT_EQ(slice.at(0), 4);
    EXPECT_EQ(slice.at(1), 6);
    EXPECT_EQ(slice.at(2), 8);
}

TEST_F(MakeSliceTest_1131, EmptySlice_1131) {
    DataBuf buf(10);
    auto slice = makeSlice(buf, 5, 5);
    EXPECT_EQ(slice.size(), 0u);
}

TEST_F(MakeSliceTest_1131, SliceFromBeginning_1131) {
    DataBuf buf(5);
    for (size_t i = 0; i < 5; ++i) {
        buf.write_uint8(i, static_cast<uint8_t>(100 + i));
    }
    auto slice = makeSlice(buf, 0, 3);
    EXPECT_EQ(slice.size(), 3u);
    EXPECT_EQ(slice.at(0), 100);
    EXPECT_EQ(slice.at(1), 101);
    EXPECT_EQ(slice.at(2), 102);
}

TEST_F(MakeSliceTest_1131, SliceEndBeyondBufSizeThrows_1131) {
    DataBuf buf(5);
    EXPECT_THROW(makeSlice(buf, 0, 6), std::out_of_range);
}

TEST_F(MakeSliceTest_1131, SliceEndFarBeyondBufSizeThrows_1131) {
    DataBuf buf(5);
    EXPECT_THROW(makeSlice(buf, 0, 100), std::out_of_range);
}

TEST_F(MakeSliceTest_1131, SliceFromEmptyBufEndZero_1131) {
    DataBuf buf;
    auto slice = makeSlice(buf, 0, 0);
    EXPECT_EQ(slice.size(), 0u);
}

TEST_F(MakeSliceTest_1131, SliceFromEmptyBufEndNonZeroThrows_1131) {
    DataBuf buf;
    EXPECT_THROW(makeSlice(buf, 0, 1), std::out_of_range);
}

TEST_F(MakeSliceTest_1131, SliceModifiesOriginalData_1131) {
    DataBuf buf(10);
    for (size_t i = 0; i < 10; ++i) {
        buf.write_uint8(i, static_cast<uint8_t>(0));
    }
    auto slice = makeSlice(buf, 2, 5);
    slice.at(0) = 42;
    EXPECT_EQ(buf.read_uint8(2), 42);
}

TEST_F(MakeSliceTest_1131, SliceFullBuffer_1131) {
    DataBuf buf(1);
    buf.write_uint8(0, 0xFF);
    auto slice = makeSlice(buf, 0, 1);
    EXPECT_EQ(slice.size(), 1u);
    EXPECT_EQ(slice.at(0), 0xFF);
}

// ============================================================
// Tests for DataBuf
// ============================================================

class DataBufTest_1131 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(DataBufTest_1131, DefaultConstructorCreatesEmptyBuf_1131) {
    DataBuf buf;
    EXPECT_EQ(buf.size(), 0u);
    EXPECT_TRUE(buf.empty());
}

TEST_F(DataBufTest_1131, SizeConstructorAllocatesCorrectSize_1131) {
    DataBuf buf(100);
    EXPECT_EQ(buf.size(), 100u);
    EXPECT_FALSE(buf.empty());
}

TEST_F(DataBufTest_1131, SizeConstructorZeroSize_1131) {
    DataBuf buf(0);
    EXPECT_EQ(buf.size(), 0u);
    EXPECT_TRUE(buf.empty());
}

TEST_F(DataBufTest_1131, DataConstructorCopiesData_1131) {
    byte data[] = {1, 2, 3, 4, 5};
    DataBuf buf(data, 5);
    EXPECT_EQ(buf.size(), 5u);
    for (size_t i = 0; i < 5; ++i) {
        EXPECT_EQ(buf.read_uint8(i), data[i]);
    }
}

TEST_F(DataBufTest_1131, AllocChangesSize_1131) {
    DataBuf buf;
    buf.alloc(50);
    EXPECT_EQ(buf.size(), 50u);
}

TEST_F(DataBufTest_1131, ResizeChangesSize_1131) {
    DataBuf buf(10);
    buf.resize(20);
    EXPECT_EQ(buf.size(), 20u);
}

TEST_F(DataBufTest_1131, ResizeToZero_1131) {
    DataBuf buf(10);
    buf.resize(0);
    EXPECT_EQ(buf.size(), 0u);
    EXPECT_TRUE(buf.empty());
}

TEST_F(DataBufTest_1131, ResetMakesBufEmpty_1131) {
    DataBuf buf(10);
    buf.reset();
    EXPECT_EQ(buf.size(), 0u);
    EXPECT_TRUE(buf.empty());
}

TEST_F(DataBufTest_1131, ReadWriteUint8_1131) {
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

TEST_F(DataBufTest_1131, ReadWriteUint16LittleEndian_1131) {
    DataBuf buf(4);
    buf.write_uint16(0, 0x1234, littleEndian);
    buf.write_uint16(2, 0xABCD, littleEndian);
    EXPECT_EQ(buf.read_uint16(0, littleEndian), 0x1234);
    EXPECT_EQ(buf.read_uint16(2, littleEndian), 0xABCD);
}

TEST_F(DataBufTest_1131, ReadWriteUint16BigEndian_1131) {
    DataBuf buf(4);
    buf.write_uint16(0, 0x1234, bigEndian);
    buf.write_uint16(2, 0xABCD, bigEndian);
    EXPECT_EQ(buf.read_uint16(0, bigEndian), 0x1234);
    EXPECT_EQ(buf.read_uint16(2, bigEndian), 0xABCD);
}

TEST_F(DataBufTest_1131, ReadWriteUint32LittleEndian_1131) {
    DataBuf buf(8);
    buf.write_uint32(0, 0x12345678, littleEndian);
    buf.write_uint32(4, 0xDEADBEEF, littleEndian);
    EXPECT_EQ(buf.read_uint32(0, littleEndian), 0x12345678u);
    EXPECT_EQ(buf.read_uint32(4, littleEndian), 0xDEADBEEFu);
}

TEST_F(DataBufTest_1131, ReadWriteUint32BigEndian_1131) {
    DataBuf buf(4);
    buf.write_uint32(0, 0x12345678, bigEndian);
    EXPECT_EQ(buf.read_uint32(0, bigEndian), 0x12345678u);
}

TEST_F(DataBufTest_1131, ReadWriteUint64LittleEndian_1131) {
    DataBuf buf(8);
    uint64_t val = 0x0102030405060708ULL;
    buf.write_uint64(0, val, littleEndian);
    EXPECT_EQ(buf.read_uint64(0, littleEndian), val);
}

TEST_F(DataBufTest_1131, ReadWriteUint64BigEndian_1131) {
    DataBuf buf(8);
    uint64_t val = 0xFEDCBA9876543210ULL;
    buf.write_uint64(0, val, bigEndian);
    EXPECT_EQ(buf.read_uint64(0, bigEndian), val);
}

TEST_F(DataBufTest_1131, EndianConsistencyUint16_1131) {
    DataBuf buf(2);
    buf.write_uint16(0, 0x0102, bigEndian);
    // Reading with different endian should give different result
    uint16_t bigVal = buf.read_uint16(0, bigEndian);
    uint16_t littleVal = buf.read_uint16(0, littleEndian);
    EXPECT_EQ(bigVal, 0x0102);
    // In little endian, bytes 01 02 would be read as 0x0201
    EXPECT_EQ(littleVal, 0x0201);
}

TEST_F(DataBufTest_1131, CmpBytesEqual_1131) {
    byte data[] = {0x01, 0x02, 0x03, 0x04};
    DataBuf buf(data, 4);
    byte cmp[] = {0x01, 0x02, 0x03, 0x04};
    EXPECT_EQ(buf.cmpBytes(0, cmp, 4), 0);
}

TEST_F(DataBufTest_1131, CmpBytesNotEqual_1131) {
    byte data[] = {0x01, 0x02, 0x03, 0x04};
    DataBuf buf(data, 4);
    byte cmp[] = {0x01, 0x02, 0x05, 0x04};
    EXPECT_NE(buf.cmpBytes(0, cmp, 4), 0);
}

TEST_F(DataBufTest_1131, CmpBytesWithOffset_1131) {
    byte data[] = {0x00, 0x01, 0x02, 0x03};
    DataBuf buf(data, 4);
    byte cmp[] = {0x01, 0x02, 0x03};
    EXPECT_EQ(buf.cmpBytes(1, cmp, 3), 0);
}

TEST_F(DataBufTest_1131, DataPointerNotNull_1131) {
    DataBuf buf(10);
    EXPECT_NE(buf.data(0), nullptr);
}

TEST_F(DataBufTest_1131, CDataPointerNotNull_1131) {
    DataBuf buf(10);
    EXPECT_NE(buf.c_data(0), nullptr);
}

TEST_F(DataBufTest_1131, CStrPointerNotNull_1131) {
    DataBuf buf(10);
    EXPECT_NE(buf.c_str(0), nullptr);
}

TEST_F(DataBufTest_1131, DataWithOffset_1131) {
    byte data[] = {10, 20, 30, 40, 50};
    DataBuf buf(data, 5);
    byte* ptr = buf.data(2);
    EXPECT_EQ(*ptr, 30);
}

TEST_F(DataBufTest_1131, CDataWithOffset_1131) {
    byte data[] = {10, 20, 30, 40, 50};
    DataBuf buf(data, 5);
    const byte* ptr = buf.c_data(3);
    EXPECT_EQ(*ptr, 40);
}

TEST_F(DataBufTest_1131, BeginEndIterators_1131) {
    byte data[] = {1, 2, 3};
    DataBuf buf(data, 3);
    size_t count = 0;
    byte sum = 0;
    for (auto it = buf.begin(); it != buf.end(); ++it) {
        sum += *it;
        ++count;
    }
    EXPECT_EQ(count, 3u);
    EXPECT_EQ(sum, 6);
}

TEST_F(DataBufTest_1131, ResizePreservesExistingData_1131) {
    byte data[] = {1, 2, 3, 4, 5};
    DataBuf buf(data, 5);
    buf.resize(10);
    EXPECT_EQ(buf.size(), 10u);
    for (size_t i = 0; i < 5; ++i) {
        EXPECT_EQ(buf.read_uint8(i), data[i]);
    }
}

TEST_F(DataBufTest_1131, WriteViaDataPointer_1131) {
    DataBuf buf(5);
    byte* ptr = buf.data(0);
    ptr[0] = 0xAA;
    ptr[1] = 0xBB;
    EXPECT_EQ(buf.read_uint8(0), 0xAA);
    EXPECT_EQ(buf.read_uint8(1), 0xBB);
}

TEST_F(DataBufTest_1131, EmptyBufIsEmpty_1131) {
    DataBuf buf;
    EXPECT_TRUE(buf.empty());
    EXPECT_EQ(buf.size(), 0u);
}

TEST_F(DataBufTest_1131, NonEmptyBufIsNotEmpty_1131) {
    DataBuf buf(1);
    EXPECT_FALSE(buf.empty());
}

TEST_F(DataBufTest_1131, AllocZeroSize_1131) {
    DataBuf buf(10);
    buf.alloc(0);
    EXPECT_EQ(buf.size(), 0u);
}

TEST_F(DataBufTest_1131, MultipleAllocCalls_1131) {
    DataBuf buf;
    buf.alloc(10);
    EXPECT_EQ(buf.size(), 10u);
    buf.alloc(20);
    EXPECT_EQ(buf.size(), 20u);
    buf.alloc(5);
    EXPECT_EQ(buf.size(), 5u);
}

TEST_F(DataBufTest_1131, Uint16BoundaryValues_1131) {
    DataBuf buf(2);
    buf.write_uint16(0, 0x0000, littleEndian);
    EXPECT_EQ(buf.read_uint16(0, littleEndian), 0x0000);
    buf.write_uint16(0, 0xFFFF, littleEndian);
    EXPECT_EQ(buf.read_uint16(0, littleEndian), 0xFFFF);
}

TEST_F(DataBufTest_1131, Uint32BoundaryValues_1131) {
    DataBuf buf(4);
    buf.write_uint32(0, 0x00000000, bigEndian);
    EXPECT_EQ(buf.read_uint32(0, bigEndian), 0x00000000u);
    buf.write_uint32(0, 0xFFFFFFFF, bigEndian);
    EXPECT_EQ(buf.read_uint32(0, bigEndian), 0xFFFFFFFFu);
}

TEST_F(DataBufTest_1131, Uint64BoundaryValues_1131) {
    DataBuf buf(8);
    buf.write_uint64(0, 0x0000000000000000ULL, bigEndian);
    EXPECT_EQ(buf.read_uint64(0, bigEndian), 0x0000000000000000ULL);
    buf.write_uint64(0, 0xFFFFFFFFFFFFFFFFULL, bigEndian);
    EXPECT_EQ(buf.read_uint64(0, bigEndian), 0xFFFFFFFFFFFFFFFFULL);
}

TEST_F(DataBufTest_1131, CmpBytesPartialMatch_1131) {
    byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    DataBuf buf(data, 5);
    byte cmp[] = {0x01, 0x02};
    EXPECT_EQ(buf.cmpBytes(0, cmp, 2), 0);
}

TEST_F(DataBufTest_1131, LargeBuffer_1131) {
    const size_t largeSize = 100000;
    DataBuf buf(largeSize);
    EXPECT_EQ(buf.size(), largeSize);
    buf.write_uint8(0, 0x01);
    buf.write_uint8(largeSize - 1, 0xFF);
    EXPECT_EQ(buf.read_uint8(0), 0x01);
    EXPECT_EQ(buf.read_uint8(largeSize - 1), 0xFF);
}

TEST_F(DataBufTest_1131, MakeSliceBeginGreaterThanEndThrows_1131) {
    DataBuf buf(10);
    // begin > end should be an error
    EXPECT_THROW(makeSlice(buf, 5, 3), std::out_of_range);
}

TEST_F(DataBufTest_1131, MakeSliceExactEnd_1131) {
    DataBuf buf(10);
    // end == size should be fine
    auto slice = makeSlice(buf, 0, 10);
    EXPECT_EQ(slice.size(), 10u);
}

TEST_F(DataBufTest_1131, MakeSliceEndOneOverThrows_1131) {
    DataBuf buf(10);
    EXPECT_THROW(makeSlice(buf, 0, 11), std::out_of_range);
}

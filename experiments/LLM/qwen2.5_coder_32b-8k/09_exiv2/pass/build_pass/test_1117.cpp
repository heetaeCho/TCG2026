#include <gtest/gtest.h>

#include "exiv2/types.hpp"



using namespace Exiv2;



TEST(DataBufTest_1117, DefaultConstructorCreatesEmptyBuffer_1117) {

    DataBuf buf;

    EXPECT_EQ(buf.size(), 0);

    EXPECT_TRUE(buf.empty());

}



TEST(DataBufTest_1117, ConstructorWithSizeCreatesCorrectBufferSize_1117) {

    size_t size = 10;

    DataBuf buf(size);

    EXPECT_EQ(buf.size(), size);

    EXPECT_FALSE(buf.empty());

}



TEST(DataBufTest_1117, ConstructorWithDataAndSizeCopiesData_1117) {

    const byte data[] = {1, 2, 3, 4, 5};

    size_t size = sizeof(data) / sizeof(data[0]);

    DataBuf buf(data, size);

    EXPECT_EQ(buf.size(), size);

    for (size_t i = 0; i < size; ++i) {

        EXPECT_EQ(buf.c_data(0)[i], data[i]);

    }

}



TEST(DataBufTest_1117, AllocSetsCorrectBufferSize_1117) {

    DataBuf buf;

    size_t size = 20;

    buf.alloc(size);

    EXPECT_EQ(buf.size(), size);

    EXPECT_FALSE(buf.empty());

}



TEST(DataBufTest_1117, ResizeChangesBufferSize_1117) {

    DataBuf buf(5);

    size_t newSize = 10;

    buf.resize(newSize);

    EXPECT_EQ(buf.size(), newSize);

    EXPECT_FALSE(buf.empty());

}



TEST(DataBufTest_1117, ResetClearsBuffer_1117) {

    DataBuf buf(10);

    buf.reset();

    EXPECT_EQ(buf.size(), 0);

    EXPECT_TRUE(buf.empty());

}



TEST(DataBufTest_1117, ReadWriteUint8WorksCorrectly_1117) {

    DataBuf buf(1);

    uint8_t value = 42;

    size_t offset = 0;

    buf.write_uint8(offset, value);

    EXPECT_EQ(buf.read_uint8(offset), value);

}



TEST(DataBufTest_1117, ReadWriteUint16WorksCorrectly_1117) {

    DataBuf buf(2);

    uint16_t value = 4242;

    size_t offset = 0;

    ByteOrder byteOrder = littleEndian;

    buf.write_uint16(offset, value, byteOrder);

    EXPECT_EQ(buf.read_uint16(offset, byteOrder), value);

}



TEST(DataBufTest_1117, ReadWriteUint32WorksCorrectly_1117) {

    DataBuf buf(4);

    uint32_t value = 42424242;

    size_t offset = 0;

    ByteOrder byteOrder = littleEndian;

    buf.write_uint32(offset, value, byteOrder);

    EXPECT_EQ(buf.read_uint32(offset, byteOrder), value);

}



TEST(DataBufTest_1117, ReadWriteUint64WorksCorrectly_1117) {

    DataBuf buf(8);

    uint64_t value = 42424242424242;

    size_t offset = 0;

    ByteOrder byteOrder = littleEndian;

    buf.write_uint64(offset, value, byteOrder);

    EXPECT_EQ(buf.read_uint64(offset, byteOrder), value);

}



TEST(DataBufTest_1117, CmpBytesComparesCorrectly_1117) {

    const byte data[] = {1, 2, 3};

    DataBuf buf(data, sizeof(data));

    size_t offset = 0;

    EXPECT_EQ(buf.cmpBytes(offset, data, sizeof(data)), 0);

}



TEST(DataBufTest_1117, CmpBytesFailsOnDifferentData_1117) {

    const byte data[] = {1, 2, 3};

    DataBuf buf(data, sizeof(data));

    size_t offset = 0;

    const byte differentData[] = {4, 5, 6};

    EXPECT_NE(buf.cmpBytes(offset, differentData, sizeof(differentData)), 0);

}



TEST(DataBufTest_1117, CmpBytesFailsOnDifferentSize_1117) {

    const byte data[] = {1, 2, 3};

    DataBuf buf(data, sizeof(data));

    size_t offset = 0;

    const byte smallerData[] = {1, 2};

    EXPECT_NE(buf.cmpBytes(offset, smallerData, sizeof(smallerData)), 0);

}



TEST(DataBufTest_1117, CmpBytesFailsOnOffsetOutofBounds_1117) {

    const byte data[] = {1, 2, 3};

    DataBuf buf(data, sizeof(data));

    size_t offset = 4;

    EXPECT_NE(buf.cmpBytes(offset, data, sizeof(data)), 0);

}



TEST(DataBufTest_1117, CmpBytesFailsOnNullData_1117) {

    const byte data[] = {1, 2, 3};

    DataBuf buf(data, sizeof(data));

    size_t offset = 0;

    EXPECT_NE(buf.cmpBytes(offset, nullptr, sizeof(data)), 0);

}



TEST(DataBufTest_1117, DataReturnsPointerToData_1117) {

    const byte data[] = {1, 2, 3};

    DataBuf buf(data, sizeof(data));

    size_t offset = 0;

    EXPECT_EQ(buf.data(offset)[0], data[offset]);

}



TEST(DataBufTest_1117, CDataReturnsConstPointerToData_1117) {

    const byte data[] = {1, 2, 3};

    DataBuf buf(data, sizeof(data));

    size_t offset = 0;

    EXPECT_EQ(buf.c_data(offset)[0], data[offset]);

}



TEST(DataBufTest_1117, CStringReturnsPointerToDataAsCString_1117) {

    const char data[] = "hello";

    DataBuf buf(reinterpret_cast<const byte*>(data), sizeof(data));

    size_t offset = 0;

    EXPECT_STREQ(buf.c_str(offset), data);

}



TEST(DataBufTest_1117, BeginEndIteratorsWorkCorrectly_1117) {

    const byte data[] = {1, 2, 3};

    DataBuf buf(data, sizeof(data));

    auto itBegin = buf.begin();

    auto itEnd = buf.end();

    for (size_t i = 0; i < sizeof(data); ++i) {

        EXPECT_EQ(*itBegin++, data[i]);

    }

    EXPECT_EQ(itBegin, itEnd);

}



TEST(DataBufTest_1117, SizeReturnsCorrectSize_1117) {

    const byte data[] = {1, 2, 3};

    DataBuf buf(data, sizeof(data));

    EXPECT_EQ(buf.size(), sizeof(data));

}



TEST(DataBufTest_1117, EmptyReturnsTrueForEmptyBuffer_1117) {

    DataBuf buf;

    EXPECT_TRUE(buf.empty());

}



TEST(DataBufTest_1117, EmptyReturnsFalseForNonEmptyBuffer_1117) {

    const byte data[] = {1, 2, 3};

    DataBuf buf(data, sizeof(data));

    EXPECT_FALSE(buf.empty());

}

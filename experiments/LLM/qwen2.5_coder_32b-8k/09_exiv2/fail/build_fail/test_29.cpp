#include <gtest/gtest.h>

#include "exiv2/types.hpp"



using namespace Exiv2;



TEST(DataBufTest_29, DefaultConstructorCreatesEmptyBuffer_29) {

    DataBuf buffer;

    EXPECT_TRUE(buffer.empty());

}



TEST(DataBufTest_29, ConstructorWithSizeCreatesNonEmptyBuffer_29) {

    size_t size = 10;

    DataBuf buffer(size);

    EXPECT_FALSE(buffer.empty());

    EXPECT_EQ(buffer.size(), size);

}



TEST(DataBufTest_29, ConstructorWithDataAndSizeCopiesData_29) {

    const byte data[] = {1, 2, 3, 4, 5};

    size_t size = sizeof(data) / sizeof(data[0]);

    DataBuf buffer(data, size);

    EXPECT_FALSE(buffer.empty());

    EXPECT_EQ(buffer.size(), size);

    for (size_t i = 0; i < size; ++i) {

        EXPECT_EQ(buffer.read_uint8(i), data[i]);

    }

}



TEST(DataBufTest_29, AllocResizesBufferToSpecifiedSize_29) {

    DataBuf buffer;

    size_t newSize = 15;

    buffer.alloc(newSize);

    EXPECT_FALSE(buffer.empty());

    EXPECT_EQ(buffer.size(), newSize);

}



TEST(DataBufTest_29, ResizeChangesBufferSize_29) {

    DataBuf buffer(10);

    size_t newSize = 20;

    buffer.resize(newSize);

    EXPECT_FALSE(buffer.empty());

    EXPECT_EQ(buffer.size(), newSize);

}



TEST(DataBufTest_29, ResetMakesBufferEmpty_29) {

    DataBuf buffer(10);

    buffer.reset();

    EXPECT_TRUE(buffer.empty());

    EXPECT_EQ(buffer.size(), 0);

}



TEST(DataBufTest_29, ReadWriteUint8WorksCorrectly_29) {

    DataBuf buffer(1);

    uint8_t value = 42;

    buffer.write_uint8(0, value);

    EXPECT_EQ(buffer.read_uint8(0), value);

}



TEST(DataBufTest_29, ReadWriteUint16WorksCorrectly_29) {

    DataBuf buffer(2);

    uint16_t value = 12345;

    ByteOrder byteOrder = littleEndian;

    buffer.write_uint16(0, value, byteOrder);

    EXPECT_EQ(buffer.read_uint16(0, byteOrder), value);

}



TEST(DataBufTest_29, ReadWriteUint32WorksCorrectly_29) {

    DataBuf buffer(4);

    uint32_t value = 123456789;

    ByteOrder byteOrder = bigEndian;

    buffer.write_uint32(0, value, byteOrder);

    EXPECT_EQ(buffer.read_uint32(0, byteOrder), value);

}



TEST(DataBufTest_29, ReadWriteUint64WorksCorrectly_29) {

    DataBuf buffer(8);

    uint64_t value = 123456789012345;

    ByteOrder byteOrder = littleEndian;

    buffer.write_uint64(0, value, byteOrder);

    EXPECT_EQ(buffer.read_uint64(0, byteOrder), value);

}



TEST(DataBufTest_29, CmpBytesReturnsCorrectResult_29) {

    const byte data[] = {1, 2, 3, 4};

    DataBuf buffer(data, sizeof(data));

    const void* cmpData = data;

    size_t cmpSize = sizeof(data);

    EXPECT_EQ(buffer.cmpBytes(0, cmpData, cmpSize), 0);



    const byte differentData[] = {1, 2, 3, 5};

    EXPECT_NE(buffer.cmpBytes(0, differentData, cmpSize), 0);

}



TEST(DataBufTest_29, DataMethodsReturnCorrectPointers_29) {

    size_t size = 5;

    byte expectedData[size] = {1, 2, 3, 4, 5};

    DataBuf buffer(expectedData, size);



    const byte* cdata = buffer.c_data(0);

    EXPECT_EQ(std::memcmp(cdata, expectedData, size), 0);



    const char* cstr = buffer.c_str(0);

    EXPECT_EQ(std::memcmp(cstr, expectedData, size), 0);



    byte* data = buffer.data(0);

    EXPECT_EQ(std::memcmp(data, expectedData, size), 0);

}



TEST(DataBufTest_29, IteratorsWorkCorrectly_29) {

    const byte data[] = {1, 2, 3};

    DataBuf buffer(data, sizeof(data));



    auto itBegin = buffer.begin();

    auto itEnd = buffer.end();



    size_t i = 0;

    for (auto it = itBegin; it != itEnd; ++it) {

        EXPECT_EQ(*it, data[i++]);

    }

}



TEST(DataBufTest_29, AccessingOutOfBoundsThrowsException_29) {

    DataBuf buffer(1);

    uint8_t value = 42;

    buffer.write_uint8(0, value);



    EXPECT_THROW(buffer.read_uint8(1), std::out_of_range);

    EXPECT_THROW(buffer.write_uint8(1, value), std::out_of_range);

}

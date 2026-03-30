#include <gtest/gtest.h>

#include "exiv2/types.hpp"



using namespace Exiv2;



TEST(DataBufTest_27, DefaultConstructorInitializesEmptyBuffer_27) {

    DataBuf buffer;

    EXPECT_EQ(buffer.size(), 0);

    EXPECT_TRUE(buffer.empty());

}



TEST(DataBufTest_27, SizeConstructorAllocatesCorrectSize_27) {

    DataBuf buffer(10);

    EXPECT_EQ(buffer.size(), 10);

    EXPECT_FALSE(buffer.empty());

}



TEST(DataBufTest_27, PointerSizeConstructorCopiesData_27) {

    const byte data[] = {1, 2, 3, 4, 5};

    DataBuf buffer(data, sizeof(data));

    EXPECT_EQ(buffer.size(), sizeof(data));

    for (size_t i = 0; i < sizeof(data); ++i) {

        EXPECT_EQ(buffer.c_data(i), &data[i]);

    }

}



TEST(DataBufTest_27, AllocResizesBuffer_27) {

    DataBuf buffer;

    buffer.alloc(20);

    EXPECT_EQ(buffer.size(), 20);

}



TEST(DataBufTest_27, ResizeChangesBufferSize_27) {

    DataBuf buffer(10);

    buffer.resize(5);

    EXPECT_EQ(buffer.size(), 5);



    buffer.resize(15);

    EXPECT_EQ(buffer.size(), 15);

}



TEST(DataBufTest_27, ResetEmptiesBuffer_27) {

    DataBuf buffer(10);

    buffer.reset();

    EXPECT_EQ(buffer.size(), 0);

    EXPECT_TRUE(buffer.empty());

}



TEST(DataBufTest_27, ReadWriteUInt8WorksCorrectly_27) {

    DataBuf buffer(1);

    buffer.write_uint8(0, 42);

    EXPECT_EQ(buffer.read_uint8(0), 42);

}



TEST(DataBufTest_27, ReadWriteUInt16WorksCorrectly_27) {

    DataBuf buffer(2);

    buffer.write_uint16(0, 0x1234, littleEndian);

    EXPECT_EQ(buffer.read_uint16(0, littleEndian), 0x1234);



    buffer.write_uint16(0, 0x1234, bigEndian);

    EXPECT_EQ(buffer.read_uint16(0, bigEndian), 0x1234);

}



TEST(DataBufTest_27, ReadWriteUInt32WorksCorrectly_27) {

    DataBuf buffer(4);

    buffer.write_uint32(0, 0x12345678, littleEndian);

    EXPECT_EQ(buffer.read_uint32(0, littleEndian), 0x12345678);



    buffer.write_uint32(0, 0x12345678, bigEndian);

    EXPECT_EQ(buffer.read_uint32(0, bigEndian), 0x12345678);

}



TEST(DataBufTest_27, ReadWriteUInt64WorksCorrectly_27) {

    DataBuf buffer(8);

    buffer.write_uint64(0, 0x123456789ABCDEF0, littleEndian);

    EXPECT_EQ(buffer.read_uint64(0, littleEndian), 0x123456789ABCDEF0);



    buffer.write_uint64(0, 0x123456789ABCDEF0, bigEndian);

    EXPECT_EQ(buffer.read_uint64(0, bigEndian), 0x123456789ABCDEF0);

}



TEST(DataBufTest_27, CmpBytesReturnsCorrectValue_27) {

    const byte data[] = {1, 2, 3};

    DataBuf buffer(data, sizeof(data));

    

    EXPECT_EQ(buffer.cmpBytes(0, data, sizeof(data)), 0);



    const byte diffData[] = {1, 2, 4};

    EXPECT_NE(buffer.cmpBytes(0, diffData, sizeof(diffData)), 0);

}



TEST(DataBufTest_27, DataPointerPointsToCorrectLocation_27) {

    const byte data[] = {1, 2, 3};

    DataBuf buffer(data, sizeof(data));

    for (size_t i = 0; i < sizeof(data); ++i) {

        EXPECT_EQ(buffer.data(i), &data[i]);

    }

}



TEST(DataBufTest_27, ConstDataPointerPointsToCorrectLocation_27) {

    const byte data[] = {1, 2, 3};

    DataBuf buffer(data, sizeof(data));

    for (size_t i = 0; i < sizeof(data); ++i) {

        EXPECT_EQ(buffer.c_data(i), &data[i]);

    }

}



TEST(DataBufTest_27, CStringPointsToCorrectLocation_27) {

    const char data[] = "abc";

    DataBuf buffer(reinterpret_cast<const byte*>(data), sizeof(data));

    EXPECT_STREQ(buffer.c_str(0), data);

}

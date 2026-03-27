#include <gtest/gtest.h>

#include "exiv2/types.hpp"



using namespace Exiv2;



class DataBufTest_1129 : public ::testing::Test {

protected:

    void SetUp() override {

        // Initialization if necessary

    }



    void TearDown() override {

        // Cleanup if necessary

    }

};



TEST_F(DataBufTest_1129, DefaultConstructorCreatesEmptyBuffer_1129) {

    DataBuf buffer;

    EXPECT_TRUE(buffer.empty());

    EXPECT_EQ(buffer.size(), 0u);

}



TEST_F(DataBufTest_1129, SizeConstructorCreatesBufferWithGivenSize_1129) {

    size_t size = 10;

    DataBuf buffer(size);

    EXPECT_FALSE(buffer.empty());

    EXPECT_EQ(buffer.size(), size);

}



TEST_F(DataBufTest_1129, DataConstructorCreatesBufferWithGivenData_1129) {

    const byte data[] = {1, 2, 3};

    size_t size = sizeof(data) / sizeof(byte);

    DataBuf buffer(data, size);

    EXPECT_FALSE(buffer.empty());

    EXPECT_EQ(buffer.size(), size);

}



TEST_F(DataBufTest_1129, AllocResizesBufferToGivenSize_1129) {

    DataBuf buffer;

    size_t newSize = 5;

    buffer.alloc(newSize);

    EXPECT_EQ(buffer.size(), newSize);

}



TEST_F(DataBufTest_1129, ResizeChangesBufferSize_1129) {

    DataBuf buffer(3);

    size_t newSize = 7;

    buffer.resize(newSize);

    EXPECT_EQ(buffer.size(), newSize);

}



TEST_F(DataBufTest_1129, ResetEmptiesBuffer_1129) {

    DataBuf buffer(5);

    buffer.reset();

    EXPECT_TRUE(buffer.empty());

    EXPECT_EQ(buffer.size(), 0u);

}



TEST_F(DataBufTest_1129, ReadWriteUInt8WorksCorrectly_1129) {

    DataBuf buffer(1);

    uint8_t value = 42;

    buffer.write_uint8(0, value);

    EXPECT_EQ(buffer.read_uint8(0), value);

}



TEST_F(DataBufTest_1129, ReadWriteUInt16WorksCorrectly_1129) {

    DataBuf buffer(2);

    uint16_t value = 42;

    ByteOrder byteOrder = littleEndian;

    buffer.write_uint16(0, value, byteOrder);

    EXPECT_EQ(buffer.read_uint16(0, byteOrder), value);

}



TEST_F(DataBufTest_1129, ReadWriteUInt32WorksCorrectly_1129) {

    DataBuf buffer(4);

    uint32_t value = 42;

    ByteOrder byteOrder = littleEndian;

    buffer.write_uint32(0, value, byteOrder);

    EXPECT_EQ(buffer.read_uint32(0, byteOrder), value);

}



TEST_F(DataBufTest_1129, ReadWriteUInt64WorksCorrectly_1129) {

    DataBuf buffer(8);

    uint64_t value = 42;

    ByteOrder byteOrder = littleEndian;

    buffer.write_uint64(0, value, byteOrder);

    EXPECT_EQ(buffer.read_uint64(0, byteOrder), value);

}



TEST_F(DataBufTest_1129, CmpBytesComparesCorrectly_1129) {

    const byte data[] = {1, 2, 3};

    DataBuf buffer(data, sizeof(data));

    EXPECT_EQ(buffer.cmpBytes(0, data, sizeof(data)), 0);

    EXPECT_NE(buffer.cmpBytes(0, &data[1], sizeof(data)), 0);

}



TEST_F(DataBufTest_1129, CStrReturnsPointerToData_1129) {

    const byte data[] = {'h', 'e', 'l', 'l', 'o'};

    DataBuf buffer(data, sizeof(data));

    EXPECT_STREQ(buffer.c_str(0), reinterpret_cast<const char*>(data));

}



TEST_F(DataBufTest_1129, CStrThrowsForOffsetOutOfBound_1129) {

    DataBuf buffer(5);

    EXPECT_THROW(buffer.c_str(6), std::out_of_range);

}

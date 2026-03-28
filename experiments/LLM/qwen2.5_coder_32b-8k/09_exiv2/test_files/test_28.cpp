#include <gtest/gtest.h>

#include "exiv2/types.hpp"



using namespace Exiv2;



class DataBufTest_28 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code if needed

    }



    void TearDown() override {

        // Teardown code if needed

    }

};



TEST_F(DataBufTest_28, DefaultConstructorCreatesEmptyBuffer_28) {

    DataBuf buffer;

    EXPECT_EQ(buffer.size(), 0);

    EXPECT_TRUE(buffer.empty());

}



TEST_F(DataBufTest_28, ConstructorWithSizeAllocatesCorrectSize_28) {

    const size_t expectedSize = 10;

    DataBuf buffer(expectedSize);

    EXPECT_EQ(buffer.size(), expectedSize);

    EXPECT_FALSE(buffer.empty());

}



TEST_F(DataBufTest_28, ConstructorWithDataAndSizeCopiesData_28) {

    const byte testData[] = {0x01, 0x02, 0x03};

    const size_t dataSize = sizeof(testData);

    DataBuf buffer(testData, dataSize);

    EXPECT_EQ(buffer.size(), dataSize);

    for (size_t i = 0; i < dataSize; ++i) {

        EXPECT_EQ(buffer.data(i)[0], testData[i]);

    }

}



TEST_F(DataBufTest_28, AllocIncreasesSize_28) {

    DataBuf buffer;

    const size_t newSize = 5;

    buffer.alloc(newSize);

    EXPECT_EQ(buffer.size(), newSize);

    EXPECT_FALSE(buffer.empty());

}



TEST_F(DataBufTest_28, ResizeChangesSize_28) {

    const size_t initialSize = 3;

    DataBuf buffer(initialSize);

    const size_t newSize = 7;

    buffer.resize(newSize);

    EXPECT_EQ(buffer.size(), newSize);

}



TEST_F(DataBufTest_28, ResetEmptiesBuffer_28) {

    const size_t initialSize = 5;

    DataBuf buffer(initialSize);

    buffer.reset();

    EXPECT_EQ(buffer.size(), 0);

    EXPECT_TRUE(buffer.empty());

}



TEST_F(DataBufTest_28, ReadWriteUint8Works_28) {

    DataBuf buffer(1);

    uint8_t value = 42;

    buffer.write_uint8(0, value);

    EXPECT_EQ(buffer.read_uint8(0), value);

}



TEST_F(DataBufTest_28, ReadWriteUint16Works_28) {

    DataBuf buffer(2);

    uint16_t value = 0x1234;

    ByteOrder byteOrder = littleEndian;

    buffer.write_uint16(0, value, byteOrder);

    EXPECT_EQ(buffer.read_uint16(0, byteOrder), value);

}



TEST_F(DataBufTest_28, ReadWriteUint32Works_28) {

    DataBuf buffer(4);

    uint32_t value = 0x12345678;

    ByteOrder byteOrder = bigEndian;

    buffer.write_uint32(0, value, byteOrder);

    EXPECT_EQ(buffer.read_uint32(0, byteOrder), value);

}



TEST_F(DataBufTest_28, ReadWriteUint64Works_28) {

    DataBuf buffer(8);

    uint64_t value = 0x123456789ABCDEF0;

    ByteOrder byteOrder = littleEndian;

    buffer.write_uint64(0, value, byteOrder);

    EXPECT_EQ(buffer.read_uint64(0, byteOrder), value);

}



TEST_F(DataBufTest_28, CmpBytesComparesCorrectly_28) {

    const byte testData[] = {0x01, 0x02, 0x03};

    DataBuf buffer(testData, sizeof(testData));

    EXPECT_EQ(buffer.cmpBytes(0, testData, sizeof(testData)), 0);

}



TEST_F(DataBufTest_28, AccessorsReturnCorrectPointers_28) {

    const byte testData[] = {0x01, 0x02, 0x03};

    DataBuf buffer(testData, sizeof(testData));

    EXPECT_EQ(memcmp(buffer.data(0), testData, sizeof(testData)), 0);

    EXPECT_EQ(memcmp(buffer.c_data(0), testData, sizeof(testData)), 0);

    EXPECT_STREQ(buffer.c_str(0), reinterpret_cast<const char*>(testData));

}



TEST_F(DataBufTest_28, IteratorsWork_28) {

    const byte testData[] = {0x01, 0x02, 0x03};

    DataBuf buffer(testData, sizeof(testData));

    auto it = buffer.begin();

    for (size_t i = 0; i < sizeof(testData); ++i, ++it) {

        EXPECT_EQ(*it, testData[i]);

    }

    EXPECT_EQ(it, buffer.end());

}



TEST_F(DataBufTest_28, OutOfBoundsAccessThrows_28) {

    DataBuf buffer(1);

    EXPECT_THROW(buffer.read_uint8(1), std::out_of_range);

    EXPECT_THROW(buffer.write_uint8(1, 0x42), std::out_of_range);

}



TEST_F(DataBufTest_28, EmptyBufferOperationsSafe_28) {

    DataBuf buffer;

    EXPECT_NO_THROW(buffer.reset());

    EXPECT_NO_THROW(buffer.alloc(0));

    EXPECT_NO_THROW(buffer.resize(0));

}

#include <gtest/gtest.h>

#include "exiv2/types.hpp"



using namespace Exiv2;



class DataBufTest : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code if needed

    }



    void TearDown() override {

        // Teardown code if needed

    }

};



TEST_F(DataBufTest_1116, DefaultConstructorCreatesEmptyBuffer_1116) {

    DataBuf dataBuf;

    EXPECT_EQ(dataBuf.size(), 0);

    EXPECT_TRUE(dataBuf.empty());

}



TEST_F(DataBufTest_1116, SizeConstructorInitializesCorrectSize_1116) {

    size_t initialSize = 10;

    DataBuf dataBuf(initialSize);

    EXPECT_EQ(dataBuf.size(), initialSize);

    EXPECT_FALSE(dataBuf.empty());

}



TEST_F(DataBufTest_1116, DataConstructorInitializesWithData_1116) {

    byte testData[] = {1, 2, 3, 4, 5};

    size_t dataSize = sizeof(testData) / sizeof(byte);

    DataBuf dataBuf(testData, dataSize);

    EXPECT_EQ(dataBuf.size(), dataSize);

    for (size_t i = 0; i < dataSize; ++i) {

        EXPECT_EQ(dataBuf.read_uint8(i), testData[i]);

    }

}



TEST_F(DataBufTest_1116, ResizeIncreasesBufferSize_1116) {

    DataBuf dataBuf;

    size_t newSize = 20;

    dataBuf.resize(newSize);

    EXPECT_EQ(dataBuf.size(), newSize);

}



TEST_F(DataBufTest_1116, ResizeDecreasesBufferSize_1116) {

    size_t initialSize = 30;

    DataBuf dataBuf(initialSize);

    size_t newSize = 10;

    dataBuf.resize(newSize);

    EXPECT_EQ(dataBuf.size(), newSize);

}



TEST_F(DataBufTest_1116, ResetEmptiesBuffer_1116) {

    size_t initialSize = 25;

    DataBuf dataBuf(initialSize);

    dataBuf.reset();

    EXPECT_EQ(dataBuf.size(), 0);

    EXPECT_TRUE(dataBuf.empty());

}



TEST_F(DataBufTest_1116, WriteReadUint8WorksCorrectly_1116) {

    DataBuf dataBuf(1);

    uint8_t value = 42;

    dataBuf.write_uint8(0, value);

    EXPECT_EQ(dataBuf.read_uint8(0), value);

}



TEST_F(DataBufTest_1116, WriteReadUint16WorksCorrectly_1116) {

    DataBuf dataBuf(2);

    uint16_t value = 1234;

    ByteOrder byteOrder = littleEndian;

    dataBuf.write_uint16(0, value, byteOrder);

    EXPECT_EQ(dataBuf.read_uint16(0, byteOrder), value);

}



TEST_F(DataBufTest_1116, WriteReadUint32WorksCorrectly_1116) {

    DataBuf dataBuf(4);

    uint32_t value = 56789;

    ByteOrder byteOrder = bigEndian;

    dataBuf.write_uint32(0, value, byteOrder);

    EXPECT_EQ(dataBuf.read_uint32(0, byteOrder), value);

}



TEST_F(DataBufTest_1116, WriteReadUint64WorksCorrectly_1116) {

    DataBuf dataBuf(8);

    uint64_t value = 987654321;

    ByteOrder byteOrder = littleEndian;

    dataBuf.write_uint64(0, value, byteOrder);

    EXPECT_EQ(dataBuf.read_uint64(0, byteOrder), value);

}



TEST_F(DataBufTest_1116, CmpBytesReturnsCorrectResult_1116) {

    byte testData[] = {1, 2, 3};

    size_t dataSize = sizeof(testData) / sizeof(byte);

    DataBuf dataBuf(testData, dataSize);

    EXPECT_EQ(dataBuf.cmpBytes(0, testData, dataSize), 0);

}



TEST_F(DataBufTest_1116, OffsetAccessorsWorkCorrectly_1116) {

    size_t initialSize = 5;

    DataBuf dataBuf(initialSize);

    byte* ptr = dataBuf.data();

    const byte* cPtr = dataBuf.c_data();

    EXPECT_EQ(ptr, cPtr);

}



TEST_F(DataBufTest_1116, IteratorsReturnCorrectPointers_1116) {

    size_t initialSize = 5;

    DataBuf dataBuf(initialSize);

    EXPECT_NE(dataBuf.begin(), dataBuf.end());

}

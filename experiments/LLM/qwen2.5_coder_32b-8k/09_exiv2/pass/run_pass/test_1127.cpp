#include <gtest/gtest.h>

#include "exiv2/types.hpp"



using namespace Exiv2;



class DataBufTest_1127 : public ::testing::Test {

protected:

    void SetUp() override {

        // Initialization if needed

    }



    void TearDown() override {

        // Cleanup if needed

    }

};



TEST_F(DataBufTest_1127, DefaultConstructorCreatesEmptyBuffer_1127) {

    DataBuf dataBuf;

    EXPECT_EQ(dataBuf.size(), 0u);

    EXPECT_TRUE(dataBuf.empty());

}



TEST_F(DataBufTest_1127, SizeConstructorAllocatesCorrectSize_1127) {

    const size_t size = 10;

    DataBuf dataBuf(size);

    EXPECT_EQ(dataBuf.size(), size);

    EXPECT_FALSE(dataBuf.empty());

}



TEST_F(DataBufTest_1127, PointerSizeConstructorCopiesData_1127) {

    const byte testData[] = {1, 2, 3, 4, 5};

    const size_t dataSize = sizeof(testData) / sizeof(testData[0]);

    DataBuf dataBuf(testData, dataSize);

    EXPECT_EQ(dataBuf.size(), dataSize);

    for (size_t i = 0; i < dataSize; ++i) {

        EXPECT_EQ(dataBuf.data(0)[i], testData[i]);

    }

}



TEST_F(DataBufTest_1127, AllocResizesBufferCorrectly_1127) {

    DataBuf dataBuf;

    const size_t newSize = 20;

    dataBuf.alloc(newSize);

    EXPECT_EQ(dataBuf.size(), newSize);

}



TEST_F(DataBufTest_1127, ResizeIncreasesBufferSize_1127) {

    DataBuf dataBuf(5);

    const size_t newSize = 10;

    dataBuf.resize(newSize);

    EXPECT_EQ(dataBuf.size(), newSize);

}



TEST_F(DataBufTest_1127, ResetEmptiesBuffer_1127) {

    DataBuf dataBuf(10);

    dataBuf.reset();

    EXPECT_EQ(dataBuf.size(), 0u);

    EXPECT_TRUE(dataBuf.empty());

}



TEST_F(DataBufTest_1127, ReadWriteUint8WorksCorrectly_1127) {

    DataBuf dataBuf(1);

    const uint8_t value = 42;

    dataBuf.write_uint8(0, value);

    EXPECT_EQ(dataBuf.read_uint8(0), value);

}



TEST_F(DataBufTest_1127, ReadWriteUint16WorksCorrectly_1127) {

    DataBuf dataBuf(2);

    const uint16_t value = 42;

    ByteOrder byteOrder = littleEndian;

    dataBuf.write_uint16(0, value, byteOrder);

    EXPECT_EQ(dataBuf.read_uint16(0, byteOrder), value);

}



TEST_F(DataBufTest_1127, ReadWriteUint32WorksCorrectly_1127) {

    DataBuf dataBuf(4);

    const uint32_t value = 42;

    ByteOrder byteOrder = littleEndian;

    dataBuf.write_uint32(0, value, byteOrder);

    EXPECT_EQ(dataBuf.read_uint32(0, byteOrder), value);

}



TEST_F(DataBufTest_1127, ReadWriteUint64WorksCorrectly_1127) {

    DataBuf dataBuf(8);

    const uint64_t value = 42;

    ByteOrder byteOrder = littleEndian;

    dataBuf.write_uint64(0, value, byteOrder);

    EXPECT_EQ(dataBuf.read_uint64(0, byteOrder), value);

}



TEST_F(DataBufTest_1127, CmpBytesMatchesEqualData_1127) {

    const byte testData[] = {1, 2, 3};

    DataBuf dataBuf(testData, sizeof(testData));

    EXPECT_EQ(dataBuf.cmpBytes(0, testData, sizeof(testData)), 0);

}



TEST_F(DataBufTest_1127, CmpBytesDetectsDifferentData_1127) {

    const byte testData1[] = {1, 2, 3};

    const byte testData2[] = {4, 5, 6};

    DataBuf dataBuf(testData1, sizeof(testData1));

    EXPECT_NE(dataBuf.cmpBytes(0, testData2, sizeof(testData2)), 0);

}



TEST_F(DataBufTest_1127, DataCDataMethodsReturnSamePointer_1127) {

    const size_t size = 10;

    DataBuf dataBuf(size);

    EXPECT_EQ(dataBuf.data(), dataBuf.c_data());

}



TEST_F(DataBufTest_1127, CStrMethodReturnsValidString_1127) {

    const char testData[] = "hello";

    DataBuf dataBuf(reinterpret_cast<const byte*>(testData), sizeof(testData));

    EXPECT_STREQ(dataBuf.c_str(), testData);

}

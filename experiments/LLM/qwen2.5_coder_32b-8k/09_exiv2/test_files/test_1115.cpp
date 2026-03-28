#include <gtest/gtest.h>

#include "exiv2/types.hpp"



using namespace Exiv2;



class DataBufTest : public ::testing::Test {

protected:

    DataBuf dataBuf;

};



TEST_F(DataBufTest_1115, DefaultConstructorInitializesEmptyBuffer_1115) {

    EXPECT_EQ(dataBuf.size(), 0);

    EXPECT_TRUE(dataBuf.empty());

}



TEST_F(DataBufTest_1115, ParameterizedConstructorInitializesWithSize_1115) {

    DataBuf dataBuf(10);

    EXPECT_EQ(dataBuf.size(), 10);

    EXPECT_FALSE(dataBuf.empty());

}



TEST_F(DataBufTest_1115, AllocResizesBuffer_1115) {

    dataBuf.alloc(20);

    EXPECT_EQ(dataBuf.size(), 20);

    EXPECT_FALSE(dataBuf.empty());



    dataBuf.alloc(0);

    EXPECT_EQ(dataBuf.size(), 0);

    EXPECT_TRUE(dataBuf.empty());

}



TEST_F(DataBufTest_1115, ResizeChangesBufferSize_1115) {

    dataBuf.resize(30);

    EXPECT_EQ(dataBuf.size(), 30);



    dataBuf.resize(0);

    EXPECT_EQ(dataBuf.size(), 0);

    EXPECT_TRUE(dataBuf.empty());

}



TEST_F(DataBufTest_1115, ResetClearsBuffer_1115) {

    dataBuf.alloc(40);

    dataBuf.reset();

    EXPECT_EQ(dataBuf.size(), 0);

    EXPECT_TRUE(dataBuf.empty());

}



TEST_F(DataBufTest_1115, ReadWriteUint8_1115) {

    dataBuf.resize(1);

    dataBuf.write_uint8(0, 255);

    EXPECT_EQ(dataBuf.read_uint8(0), 255);

}



TEST_F(DataBufTest_1115, ReadWriteUint16_1115) {

    dataBuf.resize(2);

    uint16_t value = 0xABCD;

    ByteOrder byteOrder = littleEndian;

    dataBuf.write_uint16(0, value, byteOrder);

    EXPECT_EQ(dataBuf.read_uint16(0, byteOrder), value);

}



TEST_F(DataBufTest_1115, ReadWriteUint32_1115) {

    dataBuf.resize(4);

    uint32_t value = 0xABCDEF01;

    ByteOrder byteOrder = bigEndian;

    dataBuf.write_uint32(0, value, byteOrder);

    EXPECT_EQ(dataBuf.read_uint32(0, byteOrder), value);

}



TEST_F(DataBufTest_1115, ReadWriteUint64_1115) {

    dataBuf.resize(8);

    uint64_t value = 0xABCDEF0123456789;

    ByteOrder byteOrder = littleEndian;

    dataBuf.write_uint64(0, value, byteOrder);

    EXPECT_EQ(dataBuf.read_uint64(0, byteOrder), value);

}



TEST_F(DataBufTest_1115, CmpBytesMatchesBuffer_1115) {

    dataBuf.resize(3);

    uint8_t cmpData[] = { 0x01, 0x02, 0x03 };

    std::memcpy(dataBuf.data(0), cmpData, sizeof(cmpData));

    EXPECT_EQ(dataBuf.cmpBytes(0, cmpData, sizeof(cmpData)), 0);

}



TEST_F(DataBufTest_1115, DataPointersReturnCorrectAddress_1115) {

    dataBuf.resize(1);

    EXPECT_NE(dataBuf.data(0), nullptr);

    EXPECT_NE(dataBuf.c_data(0), nullptr);

    EXPECT_NE(dataBuf.c_str(0), nullptr);

}



TEST_F(DataBufTest_1115, IteratorsReturnCorrectRange_1115) {

    dataBuf.resize(5);

    auto begin = dataBuf.begin();

    auto end = dataBuf.end();

    EXPECT_EQ(std::distance(begin, end), 5);

}

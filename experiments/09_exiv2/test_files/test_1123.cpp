#include <gtest/gtest.h>

#include "exiv2/types.hpp"



using namespace Exiv2;



class DataBufTest_1123 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup can be done here if needed

    }



    void TearDown() override {

        // Cleanup can be done here if needed

    }

};



TEST_F(DataBufTest_1123, WriteUint32WithinBounds_BE_1123) {

    DataBuf dataBuf(4);

    uint32_t value = 0x12345678;

    ByteOrder byteOrder = littleEndian; // using littleEndian for test purpose

    dataBuf.write_uint32(0, value, byteOrder);



    EXPECT_EQ(dataBuf.read_uint32(0, byteOrder), value);

}



TEST_F(DataBufTest_1123, WriteUint32WithinBounds_LE_1123) {

    DataBuf dataBuf(4);

    uint32_t value = 0x12345678;

    ByteOrder byteOrder = bigEndian; // using bigEndian for test purpose

    dataBuf.write_uint32(0, value, byteOrder);



    EXPECT_EQ(dataBuf.read_uint32(0, byteOrder), value);

}



TEST_F(DataBufTest_1123, WriteUint32AtOffset_BE_1123) {

    DataBuf dataBuf(8);

    uint32_t value = 0x12345678;

    ByteOrder byteOrder = littleEndian; // using littleEndian for test purpose

    size_t offset = 4;

    dataBuf.write_uint32(offset, value, byteOrder);



    EXPECT_EQ(dataBuf.read_uint32(offset, byteOrder), value);

}



TEST_F(DataBufTest_1123, WriteUint32AtOffset_LE_1123) {

    DataBuf dataBuf(8);

    uint32_t value = 0x12345678;

    ByteOrder byteOrder = bigEndian; // using bigEndian for test purpose

    size_t offset = 4;

    dataBuf.write_uint32(offset, value, byteOrder);



    EXPECT_EQ(dataBuf.read_uint32(offset, byteOrder), value);

}



TEST_F(DataBufTest_1123, WriteUint32BoundaryCondition_BE_1123) {

    DataBuf dataBuf(4);

    uint32_t value = 0x12345678;

    ByteOrder byteOrder = littleEndian; // using littleEndian for test purpose

    size_t offset = 0;



    EXPECT_NO_THROW(dataBuf.write_uint32(offset, value, byteOrder));

}



TEST_F(DataBufTest_1123, WriteUint32BoundaryCondition_LE_1123) {

    DataBuf dataBuf(4);

    uint32_t value = 0x12345678;

    ByteOrder byteOrder = bigEndian; // using bigEndian for test purpose

    size_t offset = 0;



    EXPECT_NO_THROW(dataBuf.write_uint32(offset, value, byteOrder));

}



TEST_F(DataBufTest_1123, WriteUint32OverflowError_BE_1123) {

    DataBuf dataBuf(4);

    uint32_t value = 0x12345678;

    ByteOrder byteOrder = littleEndian; // using littleEndian for test purpose

    size_t offset = 1;



    EXPECT_THROW(dataBuf.write_uint32(offset, value, byteOrder), std::out_of_range);

}



TEST_F(DataBufTest_1123, WriteUint32OverflowError_LE_1123) {

    DataBuf dataBuf(4);

    uint32_t value = 0x12345678;

    ByteOrder byteOrder = bigEndian; // using bigEndian for test purpose

    size_t offset = 1;



    EXPECT_THROW(dataBuf.write_uint32(offset, value, byteOrder), std::out_of_range);

}



TEST_F(DataBufTest_1123, WriteUint32SizeTooSmall_BE_1123) {

    DataBuf dataBuf(3);

    uint32_t value = 0x12345678;

    ByteOrder byteOrder = littleEndian; // using littleEndian for test purpose

    size_t offset = 0;



    EXPECT_THROW(dataBuf.write_uint32(offset, value, byteOrder), std::out_of_range);

}



TEST_F(DataBufTest_1123, WriteUint32SizeTooSmall_LE_1123) {

    DataBuf dataBuf(3);

    uint32_t value = 0x12345678;

    ByteOrder byteOrder = bigEndian; // using bigEndian for test purpose

    size_t offset = 0;



    EXPECT_THROW(dataBuf.write_uint32(offset, value, byteOrder), std::out_of_range);

}

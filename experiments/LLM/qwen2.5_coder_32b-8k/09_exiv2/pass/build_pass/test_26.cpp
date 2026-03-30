#include <gtest/gtest.h>

#include "exiv2/types.hpp"



using namespace Exiv2;



// Test suite for DataBuf class

class DataBufTest_26 : public ::testing::Test {

protected:

    void SetUp() override {

        // Initialize any necessary variables or objects before each test

    }



    void TearDown() override {

        // Clean up any necessary variables or objects after each test

    }

};



// Test normal allocation and size check

TEST_F(DataBufTest_26, AllocAndSizeCheck_26) {

    DataBuf buf(10);

    EXPECT_EQ(buf.size(), 10);

}



// Test default constructor and empty check

TEST_F(DataBufTest_26, DefaultConstructorAndEmptyCheck_26) {

    DataBuf buf;

    EXPECT_TRUE(buf.empty());

}



// Test reset functionality

TEST_F(DataBufTest_26, ResetFunctionality_26) {

    DataBuf buf(10);

    buf.reset();

    EXPECT_TRUE(buf.empty());

}



// Test resize functionality

TEST_F(DataBufTest_26, ResizeFunctionality_26) {

    DataBuf buf;

    buf.resize(5);

    EXPECT_EQ(buf.size(), 5);

}



// Test reading and writing uint8_t

TEST_F(DataBufTest_26, ReadWriteUint8_26) {

    DataBuf buf(1);

    buf.write_uint8(0, 0xFF);

    EXPECT_EQ(buf.read_uint8(0), 0xFF);

}



// Test reading and writing uint16_t with BigEndian

TEST_F(DataBufTest_26, ReadWriteUint16BigEndian_26) {

    DataBuf buf(2);

    buf.write_uint16(0, 0xFFFF, bigEndian);

    EXPECT_EQ(buf.read_uint16(0, bigEndian), 0xFFFF);

}



// Test reading and writing uint32_t with LittleEndian

TEST_F(DataBufTest_26, ReadWriteUint32LittleEndian_26) {

    DataBuf buf(4);

    buf.write_uint32(0, 0xFFFFFFFF, littleEndian);

    EXPECT_EQ(buf.read_uint32(0, littleEndian), 0xFFFFFFFF);

}



// Test reading and writing uint64_t with BigEndian

TEST_F(DataBufTest_26, ReadWriteUint64BigEndian_26) {

    DataBuf buf(8);

    buf.write_uint64(0, 0xFFFFFFFFFFFFFFFFULL, bigEndian);

    EXPECT_EQ(buf.read_uint64(0, bigEndian), 0xFFFFFFFFFFFFFFFFULL);

}



// Test cmpBytes with matching bytes

TEST_F(DataBufTest_26, CmpBytesMatching_26) {

    byte arr[] = {0x1, 0x2, 0x3};

    DataBuf buf(arr, 3);

    EXPECT_EQ(buf.cmpBytes(0, arr, 3), 0);

}



// Test cmpBytes with non-matching bytes

TEST_F(DataBufTest_26, CmpBytesNonMatching_26) {

    byte arr1[] = {0x1, 0x2, 0x3};

    byte arr2[] = {0x4, 0x5, 0x6};

    DataBuf buf(arr1, 3);

    EXPECT_NE(buf.cmpBytes(0, arr2, 3), 0);

}



// Test data and c_data access

TEST_F(DataBufTest_26, DataAndCDataAccess_26) {

    byte arr[] = {0x1, 0x2, 0x3};

    DataBuf buf(arr, 3);

    EXPECT_EQ(buf.data(0)[0], arr[0]);

    EXPECT_EQ(buf.c_data(0)[0], arr[0]);

}



// Test c_str access

TEST_F(DataBufTest_26, CStrAccess_26) {

    const char* str = "test";

    DataBuf buf(reinterpret_cast<const byte*>(str), 4);

    EXPECT_STREQ(buf.c_str(0), str);

}



// Test boundary condition for reading uint8_t

TEST_F(DataBufTest_26, ReadUint8Boundary_26) {

    DataBuf buf(1);

    buf.write_uint8(0, 0xFF);

    EXPECT_THROW(buf.read_uint8(1), std::out_of_range); // Out of range access

}



// Test boundary condition for writing uint8_t

TEST_F(DataBufTest_26, WriteUint8Boundary_26) {

    DataBuf buf(1);

    buf.write_uint8(0, 0xFF);

    EXPECT_THROW(buf.write_uint8(1, 0x00), std::out_of_range); // Out of range access

}



// Test boundary condition for reading uint16_t

TEST_F(DataBufTest_26, ReadUint16Boundary_26) {

    DataBuf buf(2);

    buf.write_uint16(0, 0xFFFF, bigEndian);

    EXPECT_THROW(buf.read_uint16(1, bigEndian), std::out_of_range); // Out of range access

}



// Test boundary condition for writing uint16_t

TEST_F(DataBufTest_26, WriteUint16Boundary_26) {

    DataBuf buf(2);

    buf.write_uint16(0, 0xFFFF, bigEndian);

    EXPECT_THROW(buf.write_uint16(1, 0x0000, bigEndian), std::out_of_range); // Out of range access

}



// Test boundary condition for reading uint32_t

TEST_F(DataBufTest_26, ReadUint32Boundary_26) {

    DataBuf buf(4);

    buf.write_uint32(0, 0xFFFFFFFF, littleEndian);

    EXPECT_THROW(buf.read_uint32(1, littleEndian), std::out_of_range); // Out of range access

}



// Test boundary condition for writing uint32_t

TEST_F(DataBufTest_26, WriteUint32Boundary_26) {

    DataBuf buf(4);

    buf.write_uint32(0, 0xFFFFFFFF, littleEndian);

    EXPECT_THROW(buf.write_uint32(1, 0x00000000, littleEndian), std::out_of_range); // Out of range access

}



// Test boundary condition for reading uint64_t

TEST_F(DataBufTest_26, ReadUint64Boundary_26) {

    DataBuf buf(8);

    buf.write_uint64(0, 0xFFFFFFFFFFFFFFFFULL, bigEndian);

    EXPECT_THROW(buf.read_uint64(1, bigEndian), std::out_of_range); // Out of range access

}



// Test boundary condition for writing uint64_t

TEST_F(DataBufTest_26, WriteUint64Boundary_26) {

    DataBuf buf(8);

    buf.write_uint64(0, 0xFFFFFFFFFFFFFFFFULL, bigEndian);

    EXPECT_THROW(buf.write_uint64(1, 0x0000000000000000ULL, bigEndian), std::out_of_range); // Out of range access

}



// Test boundary condition for cmpBytes with offset out of range

TEST_F(DataBufTest_26, CmpBytesOffsetBoundary_26) {

    byte arr[] = {0x1, 0x2, 0x3};

    DataBuf buf(arr, 3);

    EXPECT_THROW(buf.cmpBytes(4, arr, 3), std::out_of_range); // Out of range access

}



// Test boundary condition for data with offset out of range

TEST_F(DataBufTest_26, DataOffsetBoundary_26) {

    byte arr[] = {0x1, 0x2, 0x3};

    DataBuf buf(arr, 3);

    EXPECT_THROW(buf.data(4), std::out_of_range); // Out of range access

}



// Test boundary condition for c_data with offset out of range

TEST_F(DataBufTest_26, CDataOffsetBoundary_26) {

    byte arr[] = {0x1, 0x2, 0x3};

    DataBuf buf(arr, 3);

    EXPECT_THROW(buf.c_data(4), std::out_of_range); // Out of range access

}



// Test boundary condition for c_str with offset out of range

TEST_F(DataBufTest_26, CStrOffsetBoundary_26) {

    const char* str = "test";

    DataBuf buf(reinterpret_cast<const byte*>(str), 4);

    EXPECT_THROW(buf.c_str(5), std::out_of_range); // Out of range access

}

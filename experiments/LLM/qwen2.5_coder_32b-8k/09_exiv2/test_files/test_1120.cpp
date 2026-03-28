#include <gtest/gtest.h>

#include "exiv2/types.hpp"



using namespace Exiv2;



class DataBufTest_1120 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup can be done here if needed, but we don't have any internal state to set up.

    }

};



TEST_F(DataBufTest_1120, ReadUInt16_NormalOperation_LittleEndian_1120) {

    DataBuf buffer(2);

    buffer.write_uint8(0, 0x34); // Little Endian: 0x1234 -> 0x34 0x12

    buffer.write_uint8(1, 0x12);



    EXPECT_EQ(buffer.read_uint16(0, littleEndian), 0x1234);

}



TEST_F(DataBufTest_1120, ReadUInt16_NormalOperation_BigEndian_1120) {

    DataBuf buffer(2);

    buffer.write_uint8(0, 0x12); // Big Endian: 0x1234 -> 0x12 0x34

    buffer.write_uint8(1, 0x34);



    EXPECT_EQ(buffer.read_uint16(0, bigEndian), 0x1234);

}



TEST_F(DataBufTest_1120, ReadUInt16_BoundaryCondition_StartOffset_1120) {

    DataBuf buffer(2);

    buffer.write_uint8(0, 0x12); // Big Endian: 0x1234 -> 0x12 0x34

    buffer.write_uint8(1, 0x34);



    EXPECT_EQ(buffer.read_uint16(0, bigEndian), 0x1234);

}



TEST_F(DataBufTest_1120, ReadUInt16_BoundaryCondition_EndOffset_1120) {

    DataBuf buffer(3);

    buffer.write_uint8(1, 0x12); // Big Endian: 0x1234 -> 0x12 0x34

    buffer.write_uint8(2, 0x34);



    EXPECT_EQ(buffer.read_uint16(1, bigEndian), 0x1234);

}



TEST_F(DataBufTest_1120, ReadUInt16_OutOfRange_TooSmall_1120) {

    DataBuf buffer(1); // Not enough space for uint16_t

    EXPECT_THROW(buffer.read_uint16(0, littleEndian), std::out_of_range);

}



TEST_F(DataBufTest_1120, ReadUInt16_OutOfRange_OffsetTooLarge_1120) {

    DataBuf buffer(3); // Not enough space to read uint16_t starting at offset 2

    EXPECT_THROW(buffer.read_uint16(2, littleEndian), std::out_of_range);

}



TEST_F(DataBufTest_1120, ReadUInt16_OutOfRange_OffsetOnBoundary_1120) {

    DataBuf buffer(2); // Not enough space to read uint16_t starting at offset 1

    EXPECT_THROW(buffer.read_uint16(1, littleEndian), std::out_of_range);

}

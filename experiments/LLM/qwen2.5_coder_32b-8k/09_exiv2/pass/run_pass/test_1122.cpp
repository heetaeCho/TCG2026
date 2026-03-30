#include <gtest/gtest.h>

#include "exiv2/types.hpp"

#include <stdexcept>



using namespace Exiv2;



class DataBufTest_1122 : public ::testing::Test {

protected:

    DataBuf dataBuf;

};



TEST_F(DataBufTest_1122, ReadUInt32NormalOperation_1122) {

    const uint8_t testData[] = {0x12, 0x34, 0x56, 0x78};

    DataBuf db(testData, sizeof(testData));

    EXPECT_EQ(db.read_uint32(0, littleEndian), 0x78563412);

    EXPECT_EQ(db.read_uint32(0, bigEndian), 0x12345678);

}



TEST_F(DataBufTest_1122, ReadUInt32BoundaryConditionStart_1122) {

    const uint8_t testData[] = {0x12, 0x34, 0x56, 0x78};

    DataBuf db(testData, sizeof(testData));

    EXPECT_EQ(db.read_uint32(0, littleEndian), 0x78563412);

}



TEST_F(DataBufTest_1122, ReadUInt32BoundaryConditionEnd_1122) {

    const uint8_t testData[] = {0xAB, 0xCD, 0xEF, 0x01};

    DataBuf db(testData, sizeof(testData));

    EXPECT_EQ(db.read_uint32(0, littleEndian), 0x01EFCDAB);

}



TEST_F(DataBufTest_1122, ReadUInt32OutOfBoundExceptionStart_1122) {

    const uint8_t testData[] = {0x12, 0x34};

    DataBuf db(testData, sizeof(testData));

    EXPECT_THROW(db.read_uint32(0, littleEndian), std::out_of_range);

}



TEST_F(DataBufTest_1122, ReadUInt32OutOfBoundExceptionEnd_1122) {

    const uint8_t testData[] = {0x12, 0x34};

    DataBuf db(testData, sizeof(testData));

    EXPECT_THROW(db.read_uint32(1, littleEndian), std::out_of_range);

}



TEST_F(DataBufTest_1122, ReadUInt32OutOfBoundExceptionPastEnd_1122) {

    const uint8_t testData[] = {0x12, 0x34};

    DataBuf db(testData, sizeof(testData));

    EXPECT_THROW(db.read_uint32(2, littleEndian), std::out_of_range);

}



TEST_F(DataBufTest_1122, ReadUInt32EmptyBuffer_1122) {

    DataBuf db;

    EXPECT_THROW(db.read_uint32(0, littleEndian), std::out_of_range);

}

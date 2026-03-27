#include <gtest/gtest.h>

#include "exiv2/types.hpp"



using namespace Exiv2;



class DataBufTest_1124 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup can be used to initialize common objects or states if necessary.

    }



    void TearDown() override {

        // Cleanup can be done here if necessary.

    }

};



TEST_F(DataBufTest_1124, ReadUInt64_NormalOperation_1124) {

    uint8_t buffer[8] = {0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC, 0xDE, 0xF0};

    DataBuf dataBuf(buffer, sizeof(buffer));



    EXPECT_EQ(0x123456789ABCDEF0ULL, dataBuf.read_uint64(0, bigEndian));

}



TEST_F(DataBufTest_1124, ReadUInt64_BigEndian_1124) {

    uint8_t buffer[8] = {0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC, 0xDE, 0xF0};

    DataBuf dataBuf(buffer, sizeof(buffer));



    EXPECT_EQ(0x123456789ABCDEF0ULL, dataBuf.read_uint64(0, bigEndian));

}



TEST_F(DataBufTest_1124, ReadUInt64_LittleEndian_1124) {

    uint8_t buffer[8] = {0xF0, 0xDE, 0xBC, 0x9A, 0x78, 0x56, 0x34, 0x12};

    DataBuf dataBuf(buffer, sizeof(buffer));



    EXPECT_EQ(0x123456789ABCDEF0ULL, dataBuf.read_uint64(0, littleEndian));

}



TEST_F(DataBufTest_1124, ReadUInt64_OffsetWithinBounds_1124) {

    uint8_t buffer[16] = {0x00, 0x00, 0x00, 0x00, 0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC, 0xDE, 0xF0, 0x00, 0x00, 0x00, 0x00};

    DataBuf dataBuf(buffer, sizeof(buffer));



    EXPECT_EQ(0x123456789ABCDEF0ULL, dataBuf.read_uint64(4, bigEndian));

}



TEST_F(DataBufTest_1124, ReadUInt64_OffsetAtBoundary_1124) {

    uint8_t buffer[8] = {0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC, 0xDE, 0xF0};

    DataBuf dataBuf(buffer, sizeof(buffer));



    EXPECT_EQ(0x123456789ABCDEF0ULL, dataBuf.read_uint64(0, bigEndian));

}



TEST_F(DataBufTest_1124, ReadUInt64_OutOfRangeTooSmall_1124) {

    uint8_t buffer[4] = {0x12, 0x34, 0x56, 0x78};

    DataBuf dataBuf(buffer, sizeof(buffer));



    EXPECT_THROW(dataBuf.read_uint64(0, bigEndian), std::out_of_range);

}



TEST_F(DataBufTest_1124, ReadUInt64_OutOfRangeTooLarge_1124) {

    uint8_t buffer[8] = {0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC, 0xDE, 0xF0};

    DataBuf dataBuf(buffer, sizeof(buffer));



    EXPECT_THROW(dataBuf.read_uint64(1, bigEndian), std::out_of_range);

}



TEST_F(DataBufTest_1124, ReadUInt64_OutOfRangeExactFit_1124) {

    uint8_t buffer[8] = {0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC, 0xDE, 0xF0};

    DataBuf dataBuf(buffer, sizeof(buffer));



    EXPECT_NO_THROW(dataBuf.read_uint64(0, bigEndian));

}



TEST_F(DataBufTest_1124, ReadUInt64_OutOfRangeOffsetAtEnd_1124) {

    uint8_t buffer[8] = {0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC, 0xDE, 0xF0};

    DataBuf dataBuf(buffer, sizeof(buffer));



    EXPECT_THROW(dataBuf.read_uint64(8, bigEndian), std::out_of_range);

}

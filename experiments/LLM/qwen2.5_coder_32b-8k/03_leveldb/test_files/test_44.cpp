#include <gtest/gtest.h>

#include "util/coding.h"



namespace leveldb {



class CodingTest_44 : public ::testing::Test {

protected:

    char buffer[4];

};



TEST_F(CodingTest_44, DecodeFixed32_ZeroBuffer_44) {

    memset(buffer, 0, sizeof(buffer));

    EXPECT_EQ(0u, DecodeFixed32(buffer));

}



TEST_F(CodingTest_44, DecodeFixed32_MaxValue_44) {

    buffer[0] = 0xFF;

    buffer[1] = 0xFF;

    buffer[2] = 0xFF;

    buffer[3] = 0xFF;

    EXPECT_EQ(0xFFFFFFFFu, DecodeFixed32(buffer));

}



TEST_F(CodingTest_44, DecodeFixed32_SingleByteSet_44) {

    buffer[0] = 0x12;

    buffer[1] = 0x00;

    buffer[2] = 0x00;

    buffer[3] = 0x00;

    EXPECT_EQ(0x12u, DecodeFixed32(buffer));

}



TEST_F(CodingTest_44, DecodeFixed32_MultiByteSet_44) {

    buffer[0] = 0x12;

    buffer[1] = 0x34;

    buffer[2] = 0x56;

    buffer[3] = 0x78;

    EXPECT_EQ(0x78563412u, DecodeFixed32(buffer));

}



TEST_F(CodingTest_44, DecodeFixed32_BoundaryCondition_44) {

    buffer[0] = 0x00;

    buffer[1] = 0x00;

    buffer[2] = 0x00;

    buffer[3] = 0x01;

    EXPECT_EQ(0x01000000u, DecodeFixed32(buffer));

}



TEST_F(CodingTest_44, DecodeFixed32_NegativeAsUnsigned_44) {

    buffer[0] = 0xFF;

    buffer[1] = 0xFF;

    buffer[2] = 0xFF;

    buffer[3] = 0x7F;

    EXPECT_EQ(0x7FFFFFFFu, DecodeFixed32(buffer));

}



}  // namespace leveldb

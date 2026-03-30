#include <gtest/gtest.h>

#include "exiv2/types.hpp"



using namespace Exiv2;



class DataBufTest_1118 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup any common initial state if necessary

    }



    void TearDown() override {

        // Clean up any resources if necessary

    }

};



TEST_F(DataBufTest_1118, ReadUint8_NormalOperation_1118) {

    DataBuf buffer(3);

    buffer.write_uint8(0, 42);

    buffer.write_uint8(1, 84);

    buffer.write_uint8(2, 126);



    EXPECT_EQ(buffer.read_uint8(0), 42);

    EXPECT_EQ(buffer.read_uint8(1), 84);

    EXPECT_EQ(buffer.read_uint8(2), 126);

}



TEST_F(DataBufTest_1118, ReadUint8_BoundaryCondition_Start_1118) {

    DataBuf buffer(1);

    buffer.write_uint8(0, 255);



    EXPECT_EQ(buffer.read_uint8(0), 255);

}



TEST_F(DataBufTest_1118, ReadUint8_BoundaryCondition_End_1118) {

    DataBuf buffer(1);

    buffer.write_uint8(0, 255);



    EXPECT_THROW(buffer.read_uint8(1), std::out_of_range);

}



TEST_F(DataBufTest_1118, ReadUint8_ExceptionalCase_EmptyBuffer_1118) {

    DataBuf buffer;



    EXPECT_THROW(buffer.read_uint8(0), std::out_of_range);

}

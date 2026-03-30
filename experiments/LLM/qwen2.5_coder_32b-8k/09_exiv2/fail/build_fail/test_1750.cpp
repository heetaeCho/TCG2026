#include <gtest/gtest.h>

#include "exiv2/types.hpp"

#include "./TestProjects/exiv2/src/orfimage_int.hpp"



using namespace Exiv2::Internal;



class OrfHeaderTest_1750 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code, if necessary

    }



    void TearDown() override {

        // Teardown code, if necessary

    }

};



TEST_F(OrfHeaderTest_1750, Write_LittleEndian_1750) {

    OrfHeader header(littleEndian);

    DataBuf result = header.write();

    EXPECT_EQ(result.size(), 8u);

    EXPECT_EQ(result.read_uint8(0), 'I');

    EXPECT_EQ(result.read_uint8(1), 'I');

    EXPECT_EQ(result.read_uint16(2, littleEndian), 20306u);

    EXPECT_EQ(result.read_uint32(4, littleEndian), 8u);

}



TEST_F(OrfHeaderTest_1750, Write_BigEndian_1750) {

    OrfHeader header(bigEndian);

    DataBuf result = header.write();

    EXPECT_EQ(result.size(), 8u);

    EXPECT_EQ(result.read_uint8(0), 'M');

    EXPECT_EQ(result.read_uint8(1), 'M');

    EXPECT_EQ(result.read_uint16(2, bigEndian), 20306u);

    EXPECT_EQ(result.read_uint32(4, bigEndian), 8u);

}



TEST_F(OrfHeaderTest_1750, Write_DefaultByteOrder_1750) {

    OrfHeader header(invalidByteOrder);

    DataBuf result = header.write();

    EXPECT_EQ(result.size(), 8u);

    EXPECT_NE(result.read_uint8(0), 'I');

    EXPECT_NE(result.read_uint8(0), 'M');

    EXPECT_EQ(result.read_uint16(2, littleEndian), 20306u);

    EXPECT_EQ(result.read_uint32(4, littleEndian), 8u);

}

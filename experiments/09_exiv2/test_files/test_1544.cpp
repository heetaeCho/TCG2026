#include <gtest/gtest.h>

#include "cr2header_int.hpp"



using namespace Exiv2::Internal;



class Cr2HeaderTest : public ::testing::Test {

protected:

    Cr2HeaderTest() : cr2Header(Exiv2::littleEndian) {}

    Cr2Header cr2Header;

};



TEST_F(Cr2HeaderTest_1544, ReadValidDataLittleEndian_1544) {

    byte data[] = {'I', 'I', 0x00, 0x2A, 0x10, 0x00, 0x00, 0x00, 'C', 'R', '2', 'H', 0x20, 0x00, 0x00, 0x00};

    EXPECT_TRUE(cr2Header.read(data, sizeof(data)));

    EXPECT_EQ(cr2Header.byteOrder(), Exiv2::littleEndian);

    EXPECT_EQ(cr2Header.tag(), 42);

    EXPECT_EQ(cr2Header.offset(), 16);

}



TEST_F(Cr2HeaderTest_1544, ReadValidDataBigEndian_1544) {

    byte data[] = {'M', 'M', 0x2A, 0x00, 0x00, 0x00, 0x10, 0x00, 'C', 'R', '2', 'H', 0x00, 0x00, 0x00, 0x20};

    EXPECT_TRUE(cr2Header.read(data, sizeof(data)));

    EXPECT_EQ(cr2Header.byteOrder(), Exiv2::bigEndian);

    EXPECT_EQ(cr2Header.tag(), 42);

    EXPECT_EQ(cr2Header.offset(), 16);

}



TEST_F(Cr2HeaderTest_1544, ReadInvalidDataTooSmall_1544) {

    byte data[] = {'I', 'I'};

    EXPECT_FALSE(cr2Header.read(data, sizeof(data)));

}



TEST_F(Cr2HeaderTest_1544, ReadInvalidDataWrongSignature_1544) {

    byte data[] = {'I', 'I', 0x00, 0x2A, 0x10, 0x00, 0x00, 0x00, 'W', 'R', 'O', 'N', 0x20, 0x00, 0x00, 0x00};

    EXPECT_FALSE(cr2Header.read(data, sizeof(data)));

}



TEST_F(Cr2HeaderTest_1544, ReadInvalidDataMismatchTag_1544) {

    byte data[] = {'I', 'I', 0xFF, 0xFF, 0x10, 0x00, 0x00, 0x00, 'C', 'R', '2', 'H', 0x20, 0x00, 0x00, 0x00};

    EXPECT_FALSE(cr2Header.read(data, sizeof(data)));

}



TEST_F(Cr2HeaderTest_1544, ReadNullPointer_1544) {

    EXPECT_FALSE(cr2Header.read(nullptr, 16));

}

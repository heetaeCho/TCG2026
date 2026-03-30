#include <gtest/gtest.h>

#include "exiv2/types.hpp"

#include "TestProjects/exiv2/src/orfimage_int.hpp"



using namespace Exiv2;

using namespace Exiv2::Internal;



class OrfHeaderTest_1749 : public ::testing::Test {

protected:

    OrfHeader orfHeaderLittle{littleEndian};

    OrfHeader orfHeaderBig{bigEndian};



    const byte validDataLE[8] = {'I', 'I', 0x52, 0x53, 0x08, 0x00, 0x00, 0x00}; // II SR

    const byte validDataBE[8] = {'M', 'M', 0x52, 0x53, 0x00, 0x00, 0x00, 0x08}; // MM SR

    const byte invalidData1[7] = {'I', 'I', 0x52, 0x53, 0x08, 0x00, 0x00};     // too short

    const byte invalidData2[8] = {'A', 'B', 0x52, 0x53, 0x08, 0x00, 0x00, 0x00}; // neither II nor MM

    const byte invalidData3[8] = {'I', 'M', 0x52, 0x53, 0x08, 0x00, 0x00, 0x00}; // mismatched bytes

};



TEST_F(OrfHeaderTest_1749, ReadValidDataLittleEndian_1749) {

    EXPECT_TRUE(orfHeaderLittle.read(validDataLE, sizeof(validDataLE)));

    EXPECT_EQ(littleEndian, orfHeaderLittle.byteOrder());

    EXPECT_EQ(0x5352, orfHeaderLittle.tag());

    EXPECT_EQ(8u, orfHeaderLittle.size());

    EXPECT_EQ(0x00000008u, orfHeaderLittle.offset());

}



TEST_F(OrfHeaderTest_1749, ReadValidDataBigEndian_1749) {

    EXPECT_TRUE(orfHeaderBig.read(validDataBE, sizeof(validDataBE)));

    EXPECT_EQ(bigEndian, orfHeaderBig.byteOrder());

    EXPECT_EQ(0x5352, orfHeaderBig.tag());

    EXPECT_EQ(8u, orfHeaderBig.size());

    EXPECT_EQ(0x00000008u, orfHeaderBig.offset());

}



TEST_F(OrfHeaderTest_1749, ReadInvalidDataTooShort_1749) {

    EXPECT_FALSE(orfHeaderLittle.read(invalidData1, sizeof(invalidData1)));

}



TEST_F(OrfHeaderTest_1749, ReadInvalidDataMismatchedBytes_1749) {

    EXPECT_FALSE(orfHeaderLittle.read(invalidData3, sizeof(invalidData3)));

}



TEST_F(OrfHeaderTest_1749, ReadInvalidDataNeitherIINorMM_1749) {

    EXPECT_FALSE(orfHeaderLittle.read(invalidData2, sizeof(invalidData2)));

}

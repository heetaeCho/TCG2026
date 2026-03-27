#include <gtest/gtest.h>

#include "tiffimage_int.hpp"

#include "exiv2/types.hpp"



using namespace Exiv2::Internal;

using namespace Exiv2;



class TiffHeaderBaseTest_1169 : public ::testing::Test {

protected:

    const byte validDataII[] = { 'I', 'I', 0x4A, 0x46, 0x00, 0x08, 0x00, 0x08 };

    const byte validDataMM[] = { 'M', 'M', 0x00, 0x2A, 0x00, 0x08, 0x00, 0x08 };

    const byte invalidData[] = { 'X', 'Y', 0x4A, 0x46, 0x00, 0x08, 0x00, 0x08 };

};



TEST_F(TiffHeaderBaseTest_1169, ReadValidII_1169) {

    TiffHeaderBase header(0, 0, invalidByteOrder, 0);

    EXPECT_TRUE(header.read(validDataII, sizeof(validDataII)));

    EXPECT_EQ(littleEndian, header.byteOrder());

}



TEST_F(TiffHeaderBaseTest_1169, ReadValidMM_1169) {

    TiffHeaderBase header(0, 0, invalidByteOrder, 0);

    EXPECT_TRUE(header.read(validDataMM, sizeof(validDataMM)));

    EXPECT_EQ(bigEndian, header.byteOrder());

}



TEST_F(TiffHeaderBaseTest_1169, ReadInvalidMagic_1169) {

    TiffHeaderBase header(0, 0, invalidByteOrder, 0);

    EXPECT_FALSE(header.read(invalidData, sizeof(invalidData)));

}



TEST_F(TiffHeaderBaseTest_1169, ReadTooSmall_1169) {

    TiffHeaderBase header(0, 0, invalidByteOrder, 0);

    EXPECT_FALSE(header.read(validDataII, sizeof(validDataII) - 1));

}



TEST_F(TiffHeaderBaseTest_1169, ReadNullPointer_1169) {

    TiffHeaderBase header(0, 0, invalidByteOrder, 0);

    EXPECT_FALSE(header.read(nullptr, sizeof(validDataII)));

}



TEST_F(TiffHeaderBaseTest_1169, ReadInvalidTag_1169) {

    byte data[] = { 'I', 'I', 0x4A, 0x47, 0x00, 0x08, 0x00, 0x08 };

    TiffHeaderBase header(0, 0, invalidByteOrder, 0);

    EXPECT_FALSE(header.read(data, sizeof(data)));

}



TEST_F(TiffHeaderBaseTest_1169, ReadJPEGXRTag_1169) {

    byte data[] = { 'I', 'I', 0x01, 0xBE, 0x00, 0x08, 0x00, 0x08 };

    TiffHeaderBase header(0, 0, invalidByteOrder, 0);

    EXPECT_TRUE(header.read(data, sizeof(data)));

}



TEST_F(TiffHeaderBaseTest_1169, ReadDCPTag_1169) {

    byte data[] = { 'I', 'I', 0x43, 0x52, 0x00, 0x08, 0x00, 0x08 };

    TiffHeaderBase header(0, 0, invalidByteOrder, 0);

    EXPECT_TRUE(header.read(data, sizeof(data)));

}



TEST_F(TiffHeaderBaseTest_1169, ReadValidOffset_1169) {

    byte data[] = { 'I', 'I', 0x4A, 0x46, 0x00, 0x08, 0x00, 0x08 };

    TiffHeaderBase header(0, 0, invalidByteOrder, 0);

    EXPECT_TRUE(header.read(data, sizeof(data)));

    EXPECT_EQ(0x00080008U, header.offset());

}

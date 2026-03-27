#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "tiffimage_int.hpp"

#include <sstream>



using namespace Exiv2::Internal;

using namespace testing;



TEST_F(TiffHeaderBaseTest_1171, PrintWithLittleEndian_1171) {

    TiffHeaderBase header(0x0001, 8, littleEndian, 0x12345678);

    std::ostringstream os;

    header.print(os, "Prefix: ");

    EXPECT_EQ("Prefix: TIFF header, offset = 0x12345678, little endian encoded\n", os.str());

}



TEST_F(TiffHeaderBaseTest_1171, PrintWithBigEndian_1171) {

    TiffHeaderBase header(0x0001, 8, bigEndian, 0x12345678);

    std::ostringstream os;

    header.print(os, "Prefix: ");

    EXPECT_EQ("Prefix: TIFF header, offset = 0x12345678, big endian encoded\n", os.str());

}



TEST_F(TiffHeaderBaseTest_1171, PrintWithInvalidByteOrder_1171) {

    TiffHeaderBase header(0x0001, 8, invalidByteOrder, 0x12345678);

    std::ostringstream os;

    header.print(os, "Prefix: ");

    EXPECT_EQ("Prefix: TIFF header, offset = 0x12345678\n", os.str());

}



TEST_F(TiffHeaderBaseTest_1171, SetAndGetByteOrder_1171) {

    TiffHeaderBase header(0x0001, 8, littleEndian, 0x12345678);

    header.setByteOrder(bigEndian);

    EXPECT_EQ(bigEndian, header.byteOrder());

}



TEST_F(TiffHeaderBaseTest_1171, SetAndGetOffset_1171) {

    TiffHeaderBase header(0x0001, 8, littleEndian, 0x12345678);

    header.setOffset(0x87654321);

    EXPECT_EQ(0x87654321u, header.offset());

}



TEST_F(TiffHeaderBaseTest_1171, BoundaryConditionForOffset_1171) {

    TiffHeaderBase header(0x0001, 8, littleEndian, 0);

    EXPECT_EQ(0u, header.offset());

    header.setOffset(UINT32_MAX);

    EXPECT_EQ(UINT32_MAX, header.offset());

}



TEST_F(TiffHeaderBaseTest_1171, BoundaryConditionForSize_1171) {

    TiffHeaderBase header(0x0001, 0, littleEndian, 0x12345678);

    EXPECT_EQ(0u, header.size());

    header = TiffHeaderBase(0x0001, UINT32_MAX, littleEndian, 0x12345678);

    EXPECT_EQ(UINT32_MAX, header.size());

}

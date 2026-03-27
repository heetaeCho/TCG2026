#include <gtest/gtest.h>

#include "exiv2/exif.hpp"

#include "exiv2/iptc.hpp"

#include "exiv2/xmp_exiv2.hpp"

#include "TestProjects/exiv2/src/orfimage.hpp"



using namespace Exiv2;



class OrfParserTest : public ::testing::Test {

protected:

    ExifData exifData;

    IptcData iptcData;

    XmpData xmpData;

    std::vector<byte> data;

};



TEST_F(OrfParserTest_NormalOperation_1553, DecodeValidData_ReturnsCorrectByteOrder_1553) {

    // Arrange

    byte validData[] = { 0x4F, 0x52, 0x00, 0x08 }; // ORF header with little-endian

    data.assign(validData, validData + sizeof(validData));



    // Act

    ByteOrder byteOrder = OrfParser::decode(exifData, iptcData, xmpData, data.data(), data.size());



    // Assert

    EXPECT_EQ(byteOrder, littleEndian);

}



TEST_F(OrfParserTest_NormalOperation_1553, DecodeValidBigEndianData_ReturnsCorrectByteOrder_1553) {

    // Arrange

    byte validData[] = { 0x4F, 0x52, 0x08, 0x00 }; // ORF header with big-endian

    data.assign(validData, validData + sizeof(validData));



    // Act

    ByteOrder byteOrder = OrfParser::decode(exifData, iptcData, xmpData, data.data(), data.size());



    // Assert

    EXPECT_EQ(byteOrder, bigEndian);

}



TEST_F(OrfParserTest_BoundaryConditions_1553, DecodeEmptyData_ReturnsInvalidByteOrder_1553) {

    // Arrange & Act

    ByteOrder byteOrder = OrfParser::decode(exifData, iptcData, xmpData, data.data(), 0);



    // Assert

    EXPECT_EQ(byteOrder, invalidByteOrder);

}



TEST_F(OrfParserTest_BoundaryConditions_1553, DecodeShortHeader_ReturnsInvalidByteOrder_1553) {

    // Arrange

    byte shortData[] = { 0x4F, 0x52 };

    data.assign(shortData, shortData + sizeof(shortData));



    // Act

    ByteOrder byteOrder = OrfParser::decode(exifData, iptcData, xmpData, data.data(), data.size());



    // Assert

    EXPECT_EQ(byteOrder, invalidByteOrder);

}



TEST_F(OrfParserTest_ErrorCases_1553, DecodeInvalidSignature_ReturnsInvalidByteOrder_1553) {

    // Arrange

    byte invalidData[] = { 0x4F, 0x52, 0x08, 0x09 }; // ORF header with invalid signature

    data.assign(invalidData, invalidData + sizeof(invalidData));



    // Act

    ByteOrder byteOrder = OrfParser::decode(exifData, iptcData, xmpData, data.data(), data.size());



    // Assert

    EXPECT_EQ(byteOrder, invalidByteOrder);

}



TEST_F(OrfParserTest_ErrorCases_1553, DecodeNullPointer_ReturnsInvalidByteOrder_1553) {

    // Arrange & Act

    ByteOrder byteOrder = OrfParser::decode(exifData, iptcData, xmpData, nullptr, 0);



    // Assert

    EXPECT_EQ(byteOrder, invalidByteOrder);

}

#include <gtest/gtest.h>

#include <gmock/gmock.h>



#include "cr2image.hpp"

#include "exiv2/exif.hpp"

#include "exiv2/iptc.hpp"

#include "exiv2/xmp_exiv2.hpp"



using namespace Exiv2;



class Cr2ParserTest : public ::testing::Test {

protected:

    ExifData exifData;

    IptcData iptcData;

    XmpData xmpData;

    const byte testData[] = {0x49, 0x49, 0x2A, 0x00}; // Example data to simulate CR2 file

    size_t dataSize = sizeof(testData);

};



TEST_F(Cr2ParserTest_1745, DecodeValidData_1745) {

    ByteOrder byteOrder = Cr2Parser::decode(exifData, iptcData, xmpData, testData, dataSize);

    EXPECT_NE(byteOrder, invalidByteOrder); // Assuming valid data should not return invalidByteOrder

}



TEST_F(Cr2ParserTest_1745, DecodeEmptyData_1745) {

    const byte emptyData[] = {};

    size_t emptySize = sizeof(emptyData);



    ByteOrder byteOrder = Cr2Parser::decode(exifData, iptcData, xmpData, emptyData, emptySize);

    EXPECT_EQ(byteOrder, invalidByteOrder); // Assuming empty data should return invalidByteOrder

}



TEST_F(Cr2ParserTest_1745, DecodeLargeData_1745) {

    std::vector<byte> largeData(1024 * 1024, 0x00); // 1MB of data



    ByteOrder byteOrder = Cr2Parser::decode(exifData, iptcData, xmpData, largeData.data(), largeData.size());

    EXPECT_NE(byteOrder, invalidByteOrder); // Assuming valid large data should not return invalidByteOrder

}



TEST_F(Cr2ParserTest_1745, DecodeInvalidMagicNumber_1745) {

    const byte invalidMagicData[] = {0x49, 0x49, 0x2B, 0x00}; // Invalid magic number

    size_t invalidSize = sizeof(invalidMagicData);



    ByteOrder byteOrder = Cr2Parser::decode(exifData, iptcData, xmpData, invalidMagicData, invalidSize);

    EXPECT_EQ(byteOrder, invalidByteOrder); // Assuming invalid magic number should return invalidByteOrder

}



TEST_F(Cr2ParserTest_1745, DecodeBoundarySize_1745) {

    const byte boundaryData[] = {0x49, 0x49}; // Minimum size data that can't be a valid CR2 header



    ByteOrder byteOrder = Cr2Parser::decode(exifData, iptcData, xmpData, boundaryData, sizeof(boundaryData));

    EXPECT_EQ(byteOrder, invalidByteOrder); // Assuming too small data should return invalidByteOrder

}

#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/exif.hpp"

#include "exiv2/iptc.hpp"

#include "exiv2/xmp_exiv2.hpp"

#include "exiv2/tiffimage.hpp"



namespace Exiv2 {



class MockLogMsgHandler {

public:

    MOCK_METHOD(void, handle, (int level, const char* s));

};



TEST_F(ExifParserTest_784, DecodeReturnsBigEndian_784) {

    ExifData exifData;

    byte data[] = {0x4D, 0x4D}; // Big Endian TIFF header

    ByteOrder result = ExifParser().decode(exifData, data, sizeof(data));

    EXPECT_EQ(result, bigEndian);

}



TEST_F(ExifParserTest_784, DecodeReturnsLittleEndian_784) {

    ExifData exifData;

    byte data[] = {0x49, 0x49}; // Little Endian TIFF header

    ByteOrder result = ExifParser().decode(exifData, data, sizeof(data));

    EXPECT_EQ(result, littleEndian);

}



TEST_F(ExifParserTest_784, DecodeIgnoresNonEmptyIptcData_784) {

    MockLogMsgHandler mockHandler;

    LogMsg::setHandler([&mockHandler](int level, const char* s) { mockHandler.handle(level, s); });



    ExifData exifData;

    IptcData iptcData;

    iptcData.add(IptcKey("IPTC", "1#005"), new Value("Creator"));



    byte data[] = {0x4D, 0x4D}; // Big Endian TIFF header

    EXPECT_CALL(mockHandler, handle(LogMsg::warn, testing::ContainsSubstring("Ignoring IPTC information encoded in the Exif data.")));

    ExifParser().decode(exifData, data, sizeof(data));

}



TEST_F(ExifParserTest_784, DecodeIgnoresNonEmptyXmpData_784) {

    MockLogMsgHandler mockHandler;

    LogMsg::setHandler([&mockHandler](int level, const char* s) { mockHandler.handle(level, s); });



    ExifData exifData;

    XmpData xmpData;

    xmpData.add(XmpKey("XMP", "x:xmpmeta"), new Value("<x:xmpmeta/>"));



    byte data[] = {0x4D, 0x4D}; // Big Endian TIFF header

    EXPECT_CALL(mockHandler, handle(LogMsg::warn, testing::ContainsSubstring("Ignoring XMP information encoded in the Exif data.")));

    ExifParser().decode(exifData, data, sizeof(data));

}



TEST_F(ExifParserTest_784, DecodeWithZeroSizeData_784) {

    ExifData exifData;

    byte data[] = {};

    ByteOrder result = ExifParser().decode(exifData, data, sizeof(data));

    EXPECT_EQ(result, invalidByteOrder);

}



TEST_F(ExifParserTest_784, DecodeWithInvalidTiffHeader_784) {

    ExifData exifData;

    byte data[] = {0x12, 0x34}; // Invalid TIFF header

    ByteOrder result = ExifParser().decode(exifData, data, sizeof(data));

    EXPECT_EQ(result, invalidByteOrder);

}



TEST_F(ExifParserTest_784, DecodeWithEmptyIptcAndXmpData_784) {

    ExifData exifData;

    byte data[] = {0x4D, 0x4D}; // Big Endian TIFF header

    ByteOrder result = ExifParser().decode(exifData, data, sizeof(data));

    EXPECT_EQ(result, bigEndian);

}



} // namespace Exiv2

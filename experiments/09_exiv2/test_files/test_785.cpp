#include <gtest/gtest.h>

#include "exiv2/exif.hpp"

#include "exiv2/iptc.hpp"

#include "exiv2/xmp_exiv2.hpp"

#include "exiv2/basicio.hpp"

#include "exiv2/error.hpp"



using namespace Exiv2;



class ExifParserTest_785 : public ::testing::Test {

protected:

    Blob blob;

    byte pData[1024];

    size_t dataSize = sizeof(pData);

    ByteOrder byteOrder = littleEndian;

    ExifData exifData;

};



TEST_F(ExifParserTest_785, EncodeNormalOperation_785) {

    WriteMethod wm = ExifParser::encode(blob, pData, dataSize, byteOrder, exifData);

    EXPECT_TRUE(wm == wmIntrusive || wm == wmNonIntrusive);

}



TEST_F(ExifParserTest_785, EncodeEmptyExifData_785) {

    exifData.clear();

    WriteMethod wm = ExifParser::encode(blob, pData, dataSize, byteOrder, exifData);

    EXPECT_TRUE(wm == wmNonIntrusive);

}



TEST_F(ExifParserTest_785, EncodeLargeExifTags_785) {

    for (int i = 0; i < 100; ++i) {

        ExifKey key("Exif.Image.TestTag" + std::to_string(i));

        exifData.add(key, Value::create(TypeId::asciiString, "TestValue"));

    }

    WriteMethod wm = ExifParser::encode(blob, pData, dataSize, byteOrder, exifData);

    EXPECT_TRUE(wm == wmIntrusive || wm == wmNonIntrusive);

}



TEST_F(ExifParserTest_785, EncodeWithFilteredTags_785) {

    for (const auto& tag : ExifParser::filteredIfd0Tags) {

        exifData.add(tag, Value::create(TypeId::asciiString, "TestValue"));

    }

    WriteMethod wm = ExifParser::encode(blob, pData, dataSize, byteOrder, exifData);

    EXPECT_TRUE(wm == wmIntrusive || wm == wmNonIntrusive);



    for (const auto& tag : ExifParser::filteredIfd0Tags) {

        EXPECT_EQ(exifData.findKey(ExifKey(tag)), exifData.end());

    }

}



TEST_F(ExifParserTest_785, EncodeWithLargePreviewTag_785) {

    exifData.add("Exif.Minolta.ThumbnailLength", Value::create(TypeId::unsignedLong, static_cast<uint32_t>(60000)));

    WriteMethod wm = ExifParser::encode(blob, pData, dataSize, byteOrder, exifData);

    EXPECT_TRUE(wm == wmIntrusive || wm == wmNonIntrusive);



    EXPECT_EQ(exifData.findKey(ExifKey("Exif.Minolta.ThumbnailLength")), exifData.end());

}



TEST_F(ExifParserTest_785, EncodeWithLargeCustomTag_785) {

    ExifKey customTag("Exif.Image.CustomTag");

    exifData.add(customTag, Value::create(TypeId::asciiString, std::string(10000, 'A')));

    WriteMethod wm = ExifParser::encode(blob, pData, dataSize, byteOrder, exifData);

    EXPECT_TRUE(wm == wmIntrusive || wm == wmNonIntrusive);



    auto entry = exifData.findKey(customTag);

    EXPECT_NE(entry, exifData.end());

    EXPECT_EQ(entry->value()->toString(), std::string(10000, 'A'));

}



TEST_F(ExifParserTest_785, EncodeWithFilteredIFDs_785) {

    for (const auto& ifd : ExifParser::filteredIfds) {

        exifData.add("Exif.Image.TestTag", Value::create(TypeId::asciiString, "TestValue"), ifd);

    }

    WriteMethod wm = ExifParser::encode(blob, pData, dataSize, byteOrder, exifData);

    EXPECT_TRUE(wm == wmIntrusive || wm == wmNonIntrusive);



    for (const auto& ifd : ExifParser::filteredIfds) {

        EXPECT_EQ(exifData.findKey(ExifKey("Exif.Image.TestTag"), ifd), exifData.end());

    }

}

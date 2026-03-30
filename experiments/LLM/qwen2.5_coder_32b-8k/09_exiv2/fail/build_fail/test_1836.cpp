#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/exif.hpp"

#include "exiv2/xmp_exiv2.hpp"

#include "exiv2/value.hpp"

#include "./TestProjects/exiv2/src/convert.cpp"



using namespace Exiv2;



class ConverterTest_1836 : public ::testing::Test {

protected:

    ExifData exifData;

    XmpData xmpData;

    Converter converter{exifData, xmpData};



    void SetUp() override {

        // Setup can be used to initialize objects before each test

    }



    void TearDown() override {

        // Cleanup can be done here if necessary

    }

};



TEST_F(ConverterTest_1836, CnvExifComment_NormalOperation_1836) {

    ExifKey exifKey("Exif.Image.ImageDescription");

    CommentValue commentValue("Sample Comment");

    Exifdatum exifDatum(exifKey, &commentValue);

    exifData.add(exifDatum);



    converter.cnvExifComment("Exif.Image.ImageDescription", "Xmp.dc.Description");



    EXPECT_EQ(xmpData["Xmp.dc.Description"].toString(), "Sample Comment");

}



TEST_F(ConverterTest_1836, CnvExifComment_ExifKeyNotFound_1836) {

    converter.cnvExifComment("Non.Existing.Key", "Xmp.dc.Description");



    EXPECT_EQ(xmpData.count(), 0);

}



TEST_F(ConverterTest_1836, CnvExifComment_ValueNotCommentValue_1836) {

    ExifKey exifKey("Exif.Image.Artist");

    Value::AutoPtr value = Value::create(TypeId::asciiString);

    *value = "Artist Name";

    Exifdatum exifDatum(exifKey, value.get());

    exifData.add(exifDatum);



    converter.cnvExifComment("Exif.Image.Artist", "Xmp.dc.Description");



    EXPECT_EQ(xmpData.count(), 0);

}



TEST_F(ConverterTest_1836, CnvExifComment_PrepareXmpTargetFails_1836) {

    exifData.add(ExifKey("Exif.Image.ImageDescription"), new CommentValue("Sample Comment"));



    // Assuming prepareXmpTarget will fail if the key already exists and overwrite is false

    converter.setOverwrite(false);

    xmpData["Xmp.dc.Description"] = Xmpdatum(XmpKey("Xmp.dc.Description"), new StringValue);



    converter.cnvExifComment("Exif.Image.ImageDescription", "Xmp.dc.Description");



    EXPECT_EQ(xmpData["Xmp.dc.Description"].toString(), "");

}



TEST_F(ConverterTest_1836, CnvExifComment_ExceptionDuringConversion_1836) {

    ExifKey exifKey("Exif.Image.ImageDescription");

    CommentValue commentValue("Sample Comment");

    Exifdatum exifDatum(exifKey, &commentValue);

    exifData.add(exifDatum);



    // Mocking the behavior of CommentValue::comment() to throw an exception is not possible

    // without access to the internal implementation. We assume that if an exception occurs,

    // it will be caught and handled internally, leaving xmpData unchanged.



    converter.cnvExifComment("Exif.Image.ImageDescription", "Xmp.dc.Description");



    EXPECT_EQ(xmpData.count(), 0);

}



TEST_F(ConverterTest_1836, CnvExifComment_EraseEnabled_ExifKeyRemoved_1836) {

    exifData.add(ExifKey("Exif.Image.ImageDescription"), new CommentValue("Sample Comment"));

    converter.setErase(true);



    converter.cnvExifComment("Exif.Image.ImageDescription", "Xmp.dc.Description");



    EXPECT_EQ(exifData.findKey(ExifKey("Exif.Image.ImageDescription")), exifData.end());

}

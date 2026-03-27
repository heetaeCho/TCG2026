#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "convert.cpp"

#include "exif.hpp"

#include "xmp_exiv2.hpp"

#include "value.hpp"



using namespace Exiv2;

using namespace testing;



class ConverterTest_1846 : public Test {

protected:

    void SetUp() override {

        exifData.clear();

        xmpData.clear();

        converter = new Converter(exifData, xmpData);

    }



    void TearDown() override {

        delete converter;

    }



    ExifData exifData;

    XmpData xmpData;

    Converter* converter;

};



TEST_F(ConverterTest_1846, CnvXmpDate_NormalOperation_1846) {

    Xmpdatum xmpDatum("Xmp.exif.DateTimeOriginal", new Value);

    xmpDatum.setValue("2023-10-15T14:48:00+02:00");

    xmpData["Xmp.exif.DateTimeOriginal"] = xmpDatum;



    converter->cnvXmpDate("Xmp.exif.DateTimeOriginal", "Exif.Photo.DateTimeOriginal");



    EXPECT_EQ(exifData.findKey("Exif.Photo.DateTimeOriginal")->toString(), "2023:10:15 14:48:00");

}



TEST_F(ConverterTest_1846, CnvXmpDate_BoundaryCondition_EmptyFromKey_1846) {

    converter->cnvXmpDate("", "Exif.Photo.DateTimeOriginal");



    EXPECT_EQ(exifData.findKey("Exif.Photo.DateTimeOriginal"), exifData.end());

}



TEST_F(ConverterTest_1846, CnvXmpDate_BoundaryCondition_EmptyToKey_1846) {

    Xmpdatum xmpDatum("Xmp.exif.DateTimeOriginal", new Value);

    xmpDatum.setValue("2023-10-15T14:48:00+02:00");

    xmpData["Xmp.exif.DateTimeOriginal"] = xmpDatum;



    converter->cnvXmpDate("Xmp.exif.DateTimeOriginal", "");



    EXPECT_EQ(exifData.findKey("Exif.Photo.DateTimeOriginal"), exifData.end());

}



TEST_F(ConverterTest_1846, CnvXmpDate_ErrorCase_ValueNotOk_1846) {

    Xmpdatum xmpDatum("Xmp.exif.DateTimeOriginal", new Value);

    xmpDatum.value().ok_ = false;

    xmpData["Xmp.exif.DateTimeOriginal"] = xmpDatum;



    converter->cnvXmpDate("Xmp.exif.DateTimeOriginal", "Exif.Photo.DateTimeOriginal");



    EXPECT_EQ(exifData.findKey("Exif.Photo.DateTimeOriginal"), exifData.end());

}



TEST_F(ConverterTest_1846, CnvXmpDate_ErrorCase_ConversionFailure_1846) {

    Xmpdatum xmpDatum("Xmp.exif.DateTimeOriginal", new Value);

    xmpDatum.setValue("InvalidDateTime");

    xmpData["Xmp.exif.DateTimeOriginal"] = xmpDatum;



    converter->cnvXmpDate("Xmp.exif.DateTimeOriginal", "Exif.Photo.DateTimeOriginal");



    EXPECT_EQ(exifData.findKey("Exif.Photo.DateTimeOriginal"), exifData.end());

}



TEST_F(ConverterTest_1846, CnvXmpDate_GPSTimeStamp_NormalOperation_1846) {

    Xmpdatum xmpDatum("Xmp.exif.GPSTimeStamp", new Value);

    xmpDatum.setValue("2023-10-15T14:48:00+02:00");

    xmpData["Xmp.exif.GPSTimeStamp"] = xmpDatum;



    converter->cnvXmpDate("Xmp.exif.GPSTimeStamp", "Exif.GPSInfo.GPSTimeStamp");



    EXPECT_EQ(exifData.findKey("Exif.GPSInfo.GPSTimeStamp")->toString(), "14/1 2928/60 0/1");

}



TEST_F(ConverterTest_1846, CnvXmpDate_SubSecTimeDigitized_NormalOperation_1846) {

    Xmpdatum xmpDatum("Xmp.exif.DateTimeOriginal", new Value);

    xmpDatum.setValue("2023-10-15T14:48:00.123+02:00");

    xmpData["Xmp.exif.DateTimeOriginal"] = xmpDatum;



    converter->cnvXmpDate("Xmp.exif.DateTimeOriginal", "Exif.Photo.DateTimeOriginal");



    EXPECT_EQ(exifData.findKey("Exif.Photo.SubSecTimeDigitized")->toString(), "123000000");

}



TEST_F(ConverterTest_1846, CnvXmpDate_GPSTimeStampWithNanoSecond_NormalOperation_1846) {

    Xmpdatum xmpDatum("Xmp.exif.GPSTimeStamp", new Value);

    xmpDatum.setValue("2023-10-15T14:48:00.123+02:00");

    xmpData["Xmp.exif.GPSTimeStamp"] = xmpDatum;



    converter->cnvXmpDate("Xmp.exif.GPSTimeStamp", "Exif.GPSInfo.GPSTimeStamp");



    EXPECT_EQ(exifData.findKey("Exif.GPSInfo.GPSTimeStamp")->toString(), "14/1 2928/60 123000000/1");

}

#include <gtest/gtest.h>

#include "exiv2/exif.hpp"

#include "exiv2/xmp_exiv2.hpp"

#include "exiv2/convert.cpp"



using namespace Exiv2;



class ConverterTest_1838 : public ::testing::Test {

protected:

    ExifData exifData;

    XmpData xmpData;

    Converter converter{exifData, xmpData};



    void setUpExifKey(const std::string& key, const std::string& value) {

        Exifdatum datum(ExifKey(key), new StringValue);

        datum.setValue(value);

        exifData.add(datum);

    }



    bool checkXmpValue(const std::string& key, const std::string& expectedValue) {

        auto it = xmpData.findKey(XmpKey(key));

        if (it == xmpData.end()) return false;

        return it->toString() == expectedValue;

    }

};



TEST_F(ConverterTest_1838, NormalOperation_ConvertsExifDateToXmp_1838) {

    setUpExifKey("Exif.Image.DateTime", "2023:10:05 14:30:45");

    converter.cnvExifDate("Exif.Image.DateTime", "Xmp.xmp.DateCreated");



    EXPECT_TRUE(checkXmpValue("Xmp.xmp.DateCreated", "2023-10-05T14:30:45"));

}



TEST_F(ConverterTest_1838, BoundaryCondition_EmptyExifDate_1838) {

    setUpExifKey("Exif.Image.DateTime", "");

    converter.cnvExifDate("Exif.Image.DateTime", "Xmp.xmp.DateCreated");



    EXPECT_FALSE(checkXmpValue("Xmp.xmp.DateCreated", ""));

}



TEST_F(ConverterTest_1838, BoundaryCondition_InvalidDateFormat_1838) {

    setUpExifKey("Exif.Image.DateTime", "2023-10-05 14:30:45");

    converter.cnvExifDate("Exif.Image.DateTime", "Xmp.xmp.DateCreated");



    EXPECT_FALSE(checkXmpValue("Xmp.xmp.DateCreated", ""));

}



TEST_F(ConverterTest_1838, BoundaryCondition_ExifKeyNotFound_1838) {

    converter.cnvExifDate("Exif.Nonexistent.Key", "Xmp.xmp.DateCreated");



    EXPECT_FALSE(checkXmpValue("Xmp.xmp.DateCreated", ""));

}



TEST_F(ConverterTest_1838, ExceptionalCase_ValueNotOk_1838) {

    Exifdatum datum(ExifKey("Exif.Image.DateTime"), new StringValue);

    exifData.add(datum); // No value set, so it's not ok

    converter.cnvExifDate("Exif.Image.DateTime", "Xmp.xmp.DateCreated");



    EXPECT_FALSE(checkXmpValue("Xmp.xmp.DateCreated", ""));

}



TEST_F(ConverterTest_1838, NormalOperation_ConvertsGPSTimeStampToXmp_1838) {

    setUpExifKey("Exif.GPSInfo.GPSTimeStamp", "14/1 30/1 45/1");

    setUpExifKey("Exif.GPSInfo.GPSDateStamp", "2023:10:05");



    converter.cnvExifDate("Exif.GPSInfo.GPSTimeStamp", "Xmp.xmp.DateCreated");



    EXPECT_TRUE(checkXmpValue("Xmp.xmp.DateCreated", "2023-10-05T14:30:45"));

}



TEST_F(ConverterTest_1838, ExceptionalCase_GPSTimeStampInvalidCount_1838) {

    setUpExifKey("Exif.GPSInfo.GPSTimeStamp", "14/1 30/1");

    setUpExifKey("Exif.GPSInfo.GPSDateStamp", "2023:10:05");



    converter.cnvExifDate("Exif.GPSInfo.GPSTimeStamp", "Xmp.xmp.DateCreated");



    EXPECT_FALSE(checkXmpValue("Xmp.xmp.DateCreated", ""));

}



TEST_F(ConverterTest_1838, ExceptionalCase_GPSTimeStampZeroDenominator_1838) {

    setUpExifKey("Exif.GPSInfo.GPSTimeStamp", "14/0 30/1 45/1");

    setUpExifKey("Exif.GPSInfo.GPSDateStamp", "2023:10:05");



    converter.cnvExifDate("Exif.GPSInfo.GPSTimeStamp", "Xmp.xmp.DateCreated");



    EXPECT_FALSE(checkXmpValue("Xmp.xmp.DateCreated", ""));

}



TEST_F(ConverterTest_1838, ExceptionalCase_DateStampNotFound_1838) {

    setUpExifKey("Exif.GPSInfo.GPSTimeStamp", "14/1 30/1 45/1");



    converter.cnvExifDate("Exif.GPSInfo.GPSTimeStamp", "Xmp.xmp.DateCreated");



    EXPECT_FALSE(checkXmpValue("Xmp.xmp.DateCreated", ""));

}

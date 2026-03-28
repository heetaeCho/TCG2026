#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/exif.hpp"

#include "exiv2/xmp_exiv2.hpp"

#include "exiv2/value.hpp"

#include "TestProjects/exiv2/src/convert.cpp"



using namespace Exiv2;



class ConverterTest_1848 : public ::testing::Test {

protected:

    ExifData exifData_;

    XmpData xmpData_;

    Converter converter_{exifData_, xmpData_};



    void SetUp() override {

        // Clear any existing data

        exifData_.clear();

        xmpData_.clear();

    }

};



TEST_F(ConverterTest_1848, CnvXmpGPSVersion_NormalOperation_1848) {

    XmpKey key("Xmp.GPSInfo.GPSVersionID");

    std::unique_ptr<Value> value(Value::create(string));

    value->read("5.00");

    xmpData_.add(key, value.get());



    converter_.cnvXmpGPSVersion("Xmp.GPSInfo.GPSVersionID", "Exif.GPSInfo.GPSVersionID");



    EXPECT_EQ(exifData_["Exif.GPSInfo.GPSVersionID"].toString(), "5 00");

}



TEST_F(ConverterTest_1848, CnvXmpGPSVersion_NotFoundInXmp_1848) {

    converter_.cnvXmpGPSVersion("Xmp.GPSInfo.GPSVersionID", "Exif.GPSInfo.GPSVersionID");



    EXPECT_EQ(exifData_.findKey(ExifKey("Exif.GPSInfo.GPSVersionID")), exifData_.end());

}



TEST_F(ConverterTest_1848, CnvXmpGPSVersion_ValueNotOk_1848) {

    XmpKey key("Xmp.GPSInfo.GPSVersionID");

    std::unique_ptr<Value> value(Value::create(string));

    xmpData_.add(key, value.get());



    converter_.cnvXmpGPSVersion("Xmp.GPSInfo.GPSVersionID", "Exif.GPSInfo.GPSVersionID");



    EXPECT_EQ(exifData_.findKey(ExifKey("Exif.GPSInfo.GPSVersionID")), exifData_.end());

}



TEST_F(ConverterTest_1848, CnvXmpGPSVersion_EraseEnabled_1848) {

    XmpKey key("Xmp.GPSInfo.GPSVersionID");

    std::unique_ptr<Value> value(Value::create(string));

    value->read("5.00");

    xmpData_.add(key, value.get());



    converter_.setErase(true);

    converter_.cnvXmpGPSVersion("Xmp.GPSInfo.GPSVersionID", "Exif.GPSInfo.GPSVersionID");



    EXPECT_EQ(xmpData_.findKey(XmpKey("Xmp.GPSInfo.GPSVersionID")), xmpData_.end());

}



TEST_F(ConverterTest_1848, CnvXmpGPSVersion_BoundaryCondition_EmptyString_1848) {

    XmpKey key("Xmp.GPSInfo.GPSVersionID");

    std::unique_ptr<Value> value(Value::create(string));

    value->read("");

    xmpData_.add(key, value.get());



    converter_.cnvXmpGPSVersion("Xmp.GPSInfo.GPSVersionID", "Exif.GPSInfo.GPSVersionID");



    EXPECT_EQ(exifData_["Exif.GPSInfo.GPSVersionID"].toString(), "");

}
